/*	Copyright 2026 Peter Arlen Schmidt

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	    http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/


//	void _sv_commit() updates or fragments source cube into 2, 3, or 4+ parts.  The overlap of fragment boundaries and modification range boundaries further differentiates these four main cases.
//	void _av_commit() conducts a streamlined batch splice on AV* avICE by unwrapping the rSeq schedule as a sequence of mixed ascending/descending ranges.
/*	"PERISTALSIS" vs "COMPACTION / EXPANSION":
Me:	Given the familiarity to systems programming, I am satisfied that "compaction" is the most well-chosen term
	to use in documentation, but to answer your question precisely, I do not actually think that it describes the concept perfectly.
	In my mind, the characterizing aspects of this procedure are the fact that
	•	shifting the trailing data must be handled in a sufficiently granular unit, equal to or smaller than the offset, and that
	•	the unit assignments must be iterated in either ascending or descending order
		depending on whether compaction or expansion is being performed, respectively.

	This describes peristaltic action, and it cannot be done any other way.

Claude Haiku 4.5:
	You've identified something important here that "compaction" glosses over.
	You're absolutely right—the ordering constraint is the characterizing feature.
	When you're moving overlapping regions of the same buffer, the direction of iteration isn't a choice; it's a necessity.
	Move forward during compaction, backward during expansion, or you corrupt unread source data.
	That iterative directionality is the operation's defining constraint, and it's what makes it fundamentally different
	from a simple copy or memcpy.

	That's genuinely peristaltic—a directed, sequential wave of movement where the order of units matters structurally,
	not just for performance.

	Here's my refined suggestion: Use "compaction" in public-facing documentation and function signatures
	(to meet the systems programming audience), but preserve "peristaltic" in internal code comments and algorithm descriptions
	where you're explaining the why of the implementation—specifically, why the iteration direction is mandatory
	and what would break if reversed.
	*/

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "dBUG.h"
#include	"_ICE.h"
#include	"xv_commit.h"

size_t	avdbuginx_dmarkcase;
char 	subcase,
		subcase1F4=0,
		subcase1F4_=0;
char		trace[]	={ 0, 0, 0, 0, 0, 0, 0, 0 },
		trace_[]	={ 0, 0, 0, 0, 0, 0, 0, 0 };

void _sv_commit( ){
	SV/* *sv, */	*sv0,		*sv1,		*svX,		*svY;	/*	svZ [global]	*/
	STRLEN		CS0,		CS1,		CSX,		CSY;	/*	CSZ	[global]	*/			
	si64			endo_C;								
	ui64		head, body, tail, hipa;						
	ui08 /*	*	cube	=NULL,		*pq_,					/*	original (global)	primary active cube		*/
			*	cube0	=NULL,		*pq0,					/*	first				post-commit output cube 	*/
			*	cube1	=NULL,		*pq1,	ix1,  	iz1,		/*	second			post-commit output cube	*/
			*	cubeX	=NULL,		*pqX,	ixX, _ixX,	izX,		/*	endo			post-commit output cube	*/
			*	cubeY	=NULL,		*pqY,	ixY,		izY,		/*	next-to-last		post-commit output cube	*/
		/*	*	cubeZ	=NULL,*/		*pqZ,	ixZ,		izZ,		/*	last	(global)		secondary active cube		*/
				tena_nc,
				ix, iz, i, h, bs,
				lpXen, enXhp,
				exo_c,														/*	cycla count				balances		the terminating fragment	in	char *	SvPVbyte( *( AvARRAY( avICE ) +iCO), CS )	*/
				endo_c,														/*	cycla count				balances		the endogenous fragment[s]	in	char *	SvPVbyte( *( AvARRAY( avICE ) +iCX), CS )	*/
		pre_q,																/*	q-data length sum			specs		the pre-op  mod. cycla		in	char *	cube				*/
		post_q,	post0_q,		post1_q,		postX_q,		postY_q,		postZ_q,		/*	q-data length sum			measures	the post-op mod. cycla		in	char *	cube				*/
				tota0_q,		tota1_q,		totaX_q,		totaY_q,		totaZ_q,
		hp_q,	hp0_q,		hp1_q,		hpX_y,		hpY_q,		hpZ_q;		/*	q-data length				defines		the "high pass" range	 	in	char *	cube				*/

	char	post_xc,	post0_xc,	post1_xc,	postX_xc,	postY_xc,	postZ_xc,	/*	cycla count	(zero-based )	defines		the post-op mod. range		in	char *	cube				*/
		post_c,	post0_c,		post1_c,		postX_c,		postY_c,		postZ_c,		/*	cycla count				defines		the post-op mod. range		in	char *	cube				*/
		pre_c,	pre0_c,		pre1_c,		preX_c,		preY_c,		preZ_c,		/*	cycla count				measures	the pre-op mod. range		in	char *	cube				*/
		pre_xc,	pre0_xc,		pre1_xc,		preX_xc,		preY_xc,		preZ_xc,		/*	cycla count	(zero-based )	measures	the pre-op mod. range		in	char *	cube				*/
							lp1_c,		lpX_c,		lpY_c,		lpZ_c,		/*	cycla count				defines		the "low pass" range		in	char *	cube				*/
							lp1_q,		lpX_q,		lpY_q,		lpZ_q,		/*	q-data length				defines		the "low pass" range	 	in	char *	cube				*/
		hp_c,				hp1_c,		hpX_c,		hpY_c,		hpZ_c,		/*	cycla count				defines		the "high pass" range		in	char *	cube				*/
		hp_i,				hp1_i,		hpX_i,		hpY_i,		hpZ_i,
		zc0,	zc1,	zcX, zcY, ncX,
		rel_q,/*	rel0_q,		rel1_q,		relX_q,		relY_q,		relZ_q,*/		/*	q-data length difference		compares	pre & post op q-data totals	in	matrix { A[], B[], E[], Q[] }	*/
		rel_c, /*	rel0_c,	*/	rel1_c,		relX_c,		relY_c,		relZ_c;		/*	cycla count difference		compares	pre & post op cyclum counts	in	matrix { A[], B[], E[], Q[] }	*/


	long long temp_x;	short temp_a;		// temporarily tracing the extremely improbable 1F4 subcases to make sure they work

/*	Going in, we expect (SV*) sv  to equal *( AvARRAY( iC ) ), and (char*) cube to equal SvPVbyte( sv... ).
	In the 'operating' state,	(SV*) sv,  	(char*) cube,   	(int) iC, 	and (uchar) zc 	represent "this" 'pre-operational' cube.
	The "Z" aliases:		(SV*) svZ, 	(char*) cubeZ,  	(int) iCO,	and (uchar) zcZ	represent the cube preceding that one.

	However, upon return, this cube changes state to 'post-operational',thus then it is shunted down to the trailing-underscore analogs.
	It is not determined here whether this post-operational cube will precede the next to be operated on, but it may.

	The INTERLOC operations use both sets, since they operate within the namespace gap between two cubes.
	However, those operations do not require committing, since those mutations are direct in-situ assignments.


	The following cases handle different numbers of output fragments.
	"Sequestration" is when the entire mod range falls within one single fragment, and it is only possible in 1F2.
	It is not possible in 1F3 because in order to expand the input cube enough to cause it to split three ways,
	you have to add more cycla than can fit in any one fragment.
	Thus in 1F2, you have three subcases: left-sequestered, right-sequestered, and of course unsequestered.
	However, in 1F3, you have other complexity.  

	*/
//	cube= SvPVbyte_nolen(	*( pSv0 + iC ) );

#ifdef DEBUG_SvCOMMIT_L1	// process audit (brief)
	av_push( avDBUG, &PL_sv_undef );	avdbuginx_dmarkcase=AvFILLp( avDBUG );	//reserve a point in the debug output for dBUG1F3 messages
#endif
//	pre_q		= O[ 	icN	]	-	O[	icI	];	//once used to calculate rel_q by subtracting from post_q
//	post_q		= Ox[	inM	]	-	Ox[  ixM	];	//only used in 1F1, 1F2L and 1F2H	(where mod range is confined)
//	rel_q		= Ox[	inM	]	-	O[	inM	];	//only used in 1F1 and 1F2L		(where highpass in low cube shifts)

	if(		/*****		CASE 1A0	*****/	tena_zc< 0	)	{ /* One cube is annihilated.				*/	dBUGrackCALL(	0 );
	/*	mark element iC for deletion		*/																dBUGmxB4(		8 );



		//get entire length of  cube # iC and  add it to the negative phase of cyclum 0 in cube iC +1
		if( iC != zC ){
			printf("\n%s case 1F0 iC#%lld		in %s line %lld \n", __FUNCTION__, iC, __FILE__, __LINE__ );
			if( iC!=0)						cube0 =	SvPVbyte_nolen(	*(pSv0+ iC-1 ) );
			else							cube0 =	nube;
										cubeX =	cube;
										cube =	SvPVbyte(	sv = *(pSv0+ ++iC ),	CS );
		/*	MxINIT;	*/	tena_zc=zc=zcOf(	cube); 				AvCUT_B4(	iC );					
																	pq=cube+16;	O[ 0 ] =16;	I[0]=0;
			switch( cube[ 0 ] ){ SwCASE_IC2AB_init16( Q[0],	A[0],	B[0],	pq,			O[ 1 ]	); }
													A[0] += *Epsilon( cubeX ) - *Epsilon( cube0 );
			icI=u=0; icO=v=1;			ReICEuO( 0,	1 );
			ixM=0; izM=0; inM=ixH=1; 		goto _1F1;

		}else{
			printf("\n%s case 1F0-Z iC#%lld		in %s line %lld \n", __FUNCTION__, iC, __FILE__, __LINE__ );
			SvREFCNT_dec( *( pSv0 +zC ) );	zC=--AvFILLp( avICE);
			svZ=*( pSv0 +zC );
			cubeZ= SvPVbyte( svZ, CSZ );	zcZ = zcOf(	cubeZ );
			}
			
	
/*	Faced with a decision here.
	We either have to add the entire virtual namespace encompassed within annihilating cub #iC (call it "iCvac") to [iC+1][0].A,
	or we have to remove  [iC+1][0] (still add the NS of #iC) and add it to the end of [iC-1].
	At that rate, why don't we just widen the mod range to cube iC-1 and treat it like a 1F2H?	
	I guess it all depends on whether [iC+1][0].A can be increased without expanding it's q-data allcation.

	It just occurred to me that the exact code for av_commit() will work exactly the same for string data in C.
	

					cubeZ = SvPVbyte(	SvZ=	*( pSv0 + --iC ), CSZ );
		_deICE0(		cubeZ, CSZ, cubeZ[0], pqZ, Qc, Ac, Bc );
		if( iC )	{	cube0 = SvPVbyte_nolen(	*( pSv0 + iC -1 ) );		Ac += *( (ui64*) cube +1 ) -*( (ui64*) cube +1 );
				}											else	Ac += *( (ui64*) cube +1 );

		
		printf("	tena_zc=%d	The total namespace inside cube %d is (was) %lld\n", tena_zc, iC, Ec );

		deICE0_( Qc, Ac, Bc );			Ac += Ec;
		*( (ui64*) buf )=0;
		reICEx( Ac, Bc, cubeZ, buf );
		sv_insert( svZ, 16, Qc, buf, q );
		
		if( q!=Qc ){	rel_q =q- Qc;	CSZ += rel_q;	}
*/
	
		}/*






*/
	else if(	/*****		CASE 1F1	*****/	tena_zc< 8	)	{ /* One cube in, one cube out.			*/	dBUGrackCALL(	1 );
		svZ			=		sv;																		dBUGmxB4(		12	);
		zcZ			=		tena_zc;																	_1F1:
		post_xc		=		izM		-		ixM;		/* post-op endogenous cycla	(zero-based—	it is used as a vector.)	*/
		pre_xc		=		icO		-		icI;		/* pre-op ablative cycla		(one-based)						*/
		rel_c		=		post_xc	-		pre_xc;	/* pre-to-post relative difference								*/
		hp_q		=		CS		-	O[	ixH	];	/* high passthrough q-bytes	*/
		hp_c		=		zc		-		icO;		/* high passthrough cycla	*/						dBUG_1F1
		rel_q		= Ox[	inM	]	-	O[	inM	];	/* relative difference in q pre-to-post op	only used in 1F1 and 1F2L		(where highpass in low cube shifts) */
		post_q		= Ox[	inM	]	-	Ox[	ixM	];	/* length of q data to be modified. 		only used in 1F1, 1F2L and 1F2H	(where mod range is confined 	*/

/*######	UPDATE ORIGINAL CUBE [iC]	######		(CASE 1F1)									*/
		/*	[iC ]:		DISPLACE HIGH END VIA PERISTALSIS IN-SITU										*/

		if(				rel_q==0	){	CSZ= CS;		cubeZ =	cube;			
		}else{						CSZ= CS +rel_q;		SvCUR_set(	svZ,	O[ ixM ]  	); // prevent copying old data
/*expand*/	if( 			rel_q >0 ) 	{			cubeZ =	SvGROW(	svZ,	CSZ+1	);
				if(					hp_q >0 ){			ix = CSZ;				i = CS;					dBUG_bSHIFT_1F1_UP
					if(	rel_q< 2 )	goto lift_1x;
					if(	rel_q< 4 )	goto lift_2x;
					if(	rel_q< 8 )	goto lift_4x;

					if(  /* lift_8x:	*/	hp_q >7	){	do{	ix-=8; i-=8;	*( (ui64*) ( cubeZ+ix ) )=*( (ui64*) ( cube+i ) );				hp_q-=8;	} while( hp_q >7 );
								if(	hp_q &4	){		ix-=4; i-=4;	*( (ui32*) ( cubeZ+ix ) )=*( (ui32*) ( cube+i ) );				hp_q-=4;	}
								if(	hp_q &2	){		ix-=2; i-=2;	*( (ui16*) ( cubeZ+ix ) )=*( (ui16*) ( cube+i ) );				hp_q-=2;	}
								if(	hp_q &1	){		ix-=1; i-=1;	*( (ui08*) ( cubeZ+ix ) )=*( (ui08*) ( cube+i ) );				hp_q-=1;	}
					}else lift_4x:	if(	hp_q >3	){ 	do{	ix-=4; i-=4;	*( (ui32*) ( cubeZ+ix ) )=*( (ui32*) ( cube+i ) );				hp_q-=4;	} while( hp_q >3 );
								if(	hp_q &2	){		ix-=2; i-=2;	*( (ui16*) ( cubeZ+ix ) )=*( (ui16*) ( cube+i ) );				hp_q-=2;	}
								if(	hp_q &1	){		ix-=1; i-=1;	*( (ui08*) ( cubeZ+ix ) )=*( (ui08*) ( cube+i ) );				hp_q-=1;	}
					}else lift_2x:	if(	hp_q >1	){ 	do{	ix-=2; i-=2;	*( (ui16*) ( cubeZ+ix ) )=*( (ui16*) ( cube+i ) );				hp_q-=2;	} while( hp_q >1 );
								if(	hp_q &1	){		ix-=1; i-=1;	*( (ui08*) ( cubeZ+ix ) )=*( (ui08*) ( cube+i ) );				hp_q-=1;	}
					}else lift_1x:				 	do{	ix-=1; i-=1;	*( (ui08*) ( cubeZ+ix ) )=*( (ui08*) ( cube+i ) );				hp_q-=1;	} while( hp_q >0 );
					}
/*compact*/	}else{									cubeZ =	cube;
				if(					hp_q >0 ){			ix = Ox[ ixH ];  		i = O[ ixH ];				dBUG_bSHIFT_1F1_DN;
					if(	rel_q >-2 )	goto drop_1x;
					if(	rel_q >-4 )	goto drop_2x;
					if(	rel_q >-8 )	goto drop_4x;

					if(  /* drop_8x: */	hp_q >7 ){	do{				*( (ui64*) ( cubeZ+ix ) )=*( (ui64*) ( cube+i ) );	ix+=8; i+=8;	hp_q-=8;	} while( hp_q >7 );
								if(	hp_q >3 ){					*( (ui32*) ( cubeZ+ix ) )=*( (ui32*) ( cube+i ) );	ix+=4; i+=4;	hp_q-=4;	}
								if(	hp_q >1 ){					*( (ui16*) ( cubeZ+ix ) )=*( (ui16*) ( cube+i ) );	ix+=2; i+=2;	hp_q-=2;	}
								if(	hp_q >0 ){					*( (ui08*) ( cubeZ+ix ) )=*( (ui08*) ( cube+i ) );	ix+=1; i+=1;	hp_q-=1;	}
					}else drop_4x:	if(	hp_q >3 ){	do{				*( (ui32*) ( cubeZ+ix ) )=*( (ui32*) ( cube+i ) );	ix+=4; i+=4;	hp_q-=4;	} while( hp_q >3 );
								if(	hp_q >1 ){					*( (ui16*) ( cubeZ+ix ) )=*( (ui16*) ( cube+i ) );	ix+=2; i+=2;	hp_q-=2;	}
								if(	hp_q >0 ){					*( (ui08*) ( cubeZ+ix ) )=*( (ui08*) ( cube+i ) );	ix+=1; i+=1;	hp_q-=1;	}
					}else drop_2x:	if(	hp_q >1 ){	do{				*( (ui16*) ( cubeZ+ix ) )=*( (ui16*) ( cube+i ) );	ix+=2; i+=2;	hp_q-=2;	} while( hp_q >1 );
								if(	hp_q >0 ){					*( (ui08*) ( cubeZ+ix ) )=*( (ui08*) ( cube+i ) );	ix+=1; i+=1;	hp_q-=1;	}
					}else drop_1x:					do{				*( (ui08*) ( cubeZ+ix ) )=*( (ui08*) ( cube+i ) );	ix+=1; i+=1;	hp_q-=1;	} while( hp_q >0 );
				}	}								cubeZ[ CSZ	] =0;	SvCUR_set(	svZ,	CSZ  	);		dBUG_SvCUR(CSZ, "CSZ" );
			}

		/*	[iC ]:		SPLICE KEYBYTE SECTION			(CASE 1F1)									*/
		/*			double-crossover of endogenous data with high and low passthrough data, in-situ			*/
						lpXen	=	icI |( post_xc<< 3 );
		if(		rel_c ){
			if(	rel_c< 0){				bs = ( -rel_c )	<< 3;	hipa = *( (ui64*) cube ) >>bs;	}
			else{					bs =   rel_c	<< 3;	hipa = *( (ui64*) cube )<< bs;	}
			switch(		lpXen	){	SwCASE_XXOVER_01K(	hipa, 					*( (ui64*) H ),			*( (ui64*) cubeZ )	) 	}
		}else{	//					^dbl-xover dbl-tee		^high passthrough, shifted	^endo inclusion src		^low passthrough / tee output
			switch(		lpXen	){	SwCASE_XXOVER_01T(							*( (ui64*) H ),			*( (ui64*) cubeZ )	)	}
			}	// displacement		^double crossover tee							^endo inclusion src		^exo passthrough / tee output

		/*	[iC ]:		PACK NEW Q-DATA				(CASE 1F1)									*/
		if(		post_q	)	{					pqZ = cubeZ +O[ ixM ];
									ICEPACK(	pqZ, 	ixM, izM, inM,									dBUG_hiCAST_1F1_post,	dBUG_hiCAST_1F1_post_i );
							}	/*	^re-pack modified q-data vectors [ ixM..inM ] in-situ					*/	dBUGmxEO(		12	);

		}/*		so.







*/
	else if( 	/*****		CASE 1F2	*****/	tena_zc< 14	)	{ /* One cube splits in two.				*/	dBUGrackCALL(	2 );
		zcZ		= tena_zc >>1;	ixZ =tena_zc	-zcZ;													dBUGmxB4(		18 );
		zc0		= ixZ -1;

		/*	retain char * pointer and char * length of pre-op cube iC for final step later	*/
		cube0	= cube;
		sv0		= *(pSv0 +iC );

		if(		/*	CASE 1F2L  	*/	izM< 	ixZ )	{	/* mod range contained in left fragment.			*/
		/*	read up to fragment boundary if cursor (u) hasn't read that far	*/
			if(			u< ixZ ){		/*	Ox[v]=Ox[u]+Q[u];  	*/	if( RW[ v ] == null )	deIceV_KEI();
				while(	v< ixZ ){ u=v++;	Ox[v]=Ox[u]+Q[u];							DeICEv_KEI( u, v );	
				}	}
			post_xc	=		izM		-		ixM; 	/*	post_xc is zero-based—	it is used as a bitvector.		*/
			post_c	=		inM		-		ixM; 	/*	post_c is one-based—	it is used in arithmetic.		*/
			pre_xc	=		icO		-		icI;
			rel_c	=		post_xc	-		pre_xc;
			rel_q	=	Ox[	inM	]	-	O[	inM	];	/* relative difference in q pre-to-post op	only used in 1F1 and 1F2L		(where highpass in low cube shifts) */
			post_q	=	Ox[	inM	]	-	Ox[	ixM	];	/* length of q data to be modified. 		only used in 1F1, 1F2L and 1F2H	(where mod range is confined 	*/
			hp0_q	=	Ox[ 	ixZ	]	-	Ox[ 	ixH	];
/*######	CREATE HIGH CUBE [iC+1]:	SV SETUP		(CASE 1F2L)									*/	{	
									NEW_CUBE_Z_AS_HIGHPASS(										dBUG_XLOAD_1F2L_tota1 );
			*( (ui64*) cube0 +1 ) =		E[ zc0	];		/* set Epsilon of low cube while we're at it			*/	dBUG_SvCUR(CSZ, "CSZ" );
			AvPOST( iC, svZ );							/* defer inserting the new element to (AV*) avICE	*/

/*######	[iC+0]:	SPLICE KEYBYTE SECTION			(CASE 1F2L)									*/
		/*	crossover modified key data (as uquad* H ) with unaltered leading / trailing in-situ    					*/
							lpXen =	icI |( post_xc<< 3 );
			if(		rel_c ){ //	shift
/*shift up	*/	if(	rel_c >0){			bs =   rel_c	<< 3;	hipa = *( (ui64*) cube0 )<< bs; }
/*shift down	*/	else{				bs = ( -rel_c )	<< 3;	hipa = *( (ui64*) cube0 ) >>bs; }
				switch(		lpXen ){	SwCASE_XXOVER_01K(	hipa,  					*( (ui64*) H ),			*( (ui64*) cube0 )	) 	}
			}else{	//		no shift	^dbl crossover dbl tee	^high passthrough, shifted	^endo inclusion src		^low passthrough + tee output
				switch(		lpXen ){	SwCASE_XXOVER_01T(							*( (ui64*) H ),			*( (ui64*) cube0 )	)	}
				}	//				^double crossover tee							^endo inclusion src		^exo passthrough + tee output
		/*	trim everything off the low cube that went to the high cube.					*/
			switch(		zc0 ){		SwCASE_LOWPASS_1IS(	*( (ui64*) cube0 )	);		}


		/*	[iC+0]:	IN-SITU Q-DATA SHIFT				(CASE 1F2L )									*/
/*expand*/	if(			rel_q >0 )	{							SvCUR_set(	sv0, O[	ixM] );	// to prevent copying old data
													cube0 =	SvGROW(	sv0, Ox[	ixZ ] +1	);
				if(					hp0_q >0 ){		ix = Ox[	ixZ ];		i =	O[	ixZ ];				dBUG_bSHIFT_1F2L_UP
					if(	rel_q< 2 )	goto lift01x;
					if(	rel_q< 4 )	goto lift02x;
					if(	rel_q< 8 )	goto lift04x;

					if(  /* lift08x: */	hp0_q >7 ){	do{	ix-=8; i-=8;	*( (ui64*) ( cube0+ix ) )=*( (ui64*) ( cube+i ) );					hp0_q-=8; } while( hp0_q >7 );
								if(	hp0_q &4 ){		ix-=4; i-=4;	*( (ui32*) ( cube0+ix ) )=*( (ui32*) ( cube+i ) );					hp0_q-=4; }
								if(	hp0_q &2 ){		ix-=2; i-=2;	*( (ui16*) ( cube0+ix ) )=*( (ui16*) ( cube+i ) );					hp0_q-=2; }
								if(	hp0_q &1 ){		ix-=1; i-=1;	*( (ui08*) ( cube0+ix ) )=*( (ui08*) ( cube+i ) );					hp0_q-=1; }
					}else lift04x:	if(	hp0_q >3 ){ 	do{	ix-=4; i-=4;	*( (ui32*) ( cube0+ix ) )=*( (ui32*) ( cube+i ) );					hp0_q-=4; } while( hp0_q >3 );
								if(	hp0_q &2 ){		ix-=2; i-=2;	*( (ui16*) ( cube0+ix ) )=*( (ui16*) ( cube+i ) );					hp0_q-=2; }
								if(	hp0_q &1 ){		ix-=1; i-=1;	*( (ui08*) ( cube0+ix ) )=*( (ui08*) ( cube+i ) );					hp0_q-=1; }
					}else lift02x:	if(	hp0_q >1 ){	do{	ix-=2; i-=2;	*( (ui16*) ( cube0+ix ) )=*( (ui16*) ( cube+i ) );					hp0_q-=2; } while( hp0_q >1 );
								if(	hp0_q &1 ){		ix-=1; i-=1;	*( (ui08*) ( cube0+ix ) )=*( (ui08*) ( cube+i ) );					hp0_q-=1; }
					}else lift01x:				 	do{	ix-=1; i-=1;	*( (ui08*) ( cube0+ix ) )=*( (ui08*) ( cube+i ) );					hp0_q-=1; } while( hp0_q >0 );
					}							//	cube0[ Ox[ixZ] ] = 0;	SvCUR_set( sv0, Ox[ixZ] );
/*compact*/	}else if(		rel_q< 0 )	{
				if(					hp0_q >0 )	{	ix = O[ ixH ]+rel_q;		i = O[ ixH ];					dBUG_bSHIFT_1F2L_DN;
					if(	rel_q >-2 )	goto drop01x;
					if(	rel_q >-4 )	goto drop02x;
					if(	rel_q >-8 )	goto drop04x;

					if(  /* drop08x: */	hp0_q >7 ){	do{				*( (ui64*) ( cube0+ix ) )=*( (ui64*) ( cube+i ) ); 	ix+=8; i+=8;	hp0_q-=8; } while( hp0_q >7 );
								if(	hp0_q >3 ){					*( (ui32*) ( cube0+ix ) )=*( (ui32*) ( cube+i ) ); 	ix+=4; i+=4;	hp0_q-=4; }
								if(	hp0_q >1 ){					*( (ui16*) ( cube0+ix ) )=*( (ui16*) ( cube+i ) ); 	ix+=2; i+=2;	hp0_q-=2; }
								if(	hp0_q >0 ){					*( (ui08*) ( cube0+ix ) )=*( (ui08*) ( cube+i ) ); 	ix+=1; i+=1;	hp0_q-=1; }
					}else drop04x:	if(	hp0_q >3 ){	do{				*( (ui32*) ( cube0+ix ) )=*( (ui32*) ( cube+i ) ); 	ix+=4; i+=4;	hp0_q-=4; } while( hp0_q >3 );
								if(	hp0_q >1 ){					*( (ui16*) ( cube0+ix ) )=*( (ui16*) ( cube+i ) ); 	ix+=2; i+=2;	hp0_q-=2; }
								if(	hp0_q >0 ){					*( (ui08*) ( cube0+ix ) )=*( (ui08*) ( cube+i ) ); 	ix+=1; i+=1;	hp0_q-=1; }
					}else drop02x:	if(	hp0_q >1 ){	do{				*( (ui16*) ( cube0+ix ) )=*( (ui16*) ( cube+i ) ); 	ix+=2; i+=2;	hp0_q-=2; } while( hp0_q >1 );
								if(	hp0_q >0 ){					*( (ui08*) ( cube0+ix ) )=*( (ui08*) ( cube+i ) ); 	ix+=1; i+=1;	hp0_q-=1; }
					}else drop01x:					do{				*( (ui08*) ( cube0+ix ) )=*( (ui08*) ( cube+i ) ); 	ix+=1; i+=1;	hp0_q-=1; } while( hp0_q >0 );
					} 							//	cube0[ Ox[ixZ] ] = 0;	SvCUR_set( sv0, Ox[ixZ] );		dBUG_SvCUR(Ox[ixZ], "Ox[ixZ]" );
			}										cube0[ Ox[ixZ] ] = 0;	SvCUR_set( sv0, Ox[ixZ] );		dBUG_SvCUR(Ox[ixZ], "Ox[ixZ]" );

		/*	[iC+0]:  RE-PACK MOD Q-DATA				(CASE 1F2L)									*/
			if(	post_q	)	{				pq0 = cube0 +O[ ixM ];
									ICEPACK( pq0, 	ixM, zc0, ixZ,										dBUG_hiCAST_1F2L_post,	dBUG_hiCAST_1F2L_post_i );
							}	/*	^re-pack modified q-data vectors ixM..zc0 to cube0[ O[ ixM ]..Ox[ ixZ ]-1 ] */ }	dBUG_1F2L
			}
		else if(	/*	CASE 1F2H  	*/	ixM >=	ixZ )	{	/* mod range contained in right fragment.		*/
			post_q	=	Ox[	inM	]	-	Ox[	ixM	];	/* length of q data to be modified. 		only used in 1F1, 1F2L and 1F2H	(where mod range is confined 	*/
			post_xc	=		izM		-		ixM;
			post_c	=		inM		-		ixM;
			pre_xc	=		icO		-		icI;
			rel_c	=		post_xc	-		pre_xc;
			relZ_c	=		rel_c	-	I[	ixZ ];

			tota0_q	=	O[	ixZ	]	-		16;		// only used once
			lpZ_c	=		ixM		-		ixZ;
			lpZ_q	=	O[	ixM	]	-	O[	ixZ ];
			hpZ_q	=		CS		-	O[	ixH	];
		//	hpZ_i	=	I[	ixZ ]	-		rel_c;

/*######	CREATE HIGH CUBE [iC+1]:	SV SETUP		(CASE 1F2H)									*/
		/*	create new cube to serve as the higher fragment											*/
		//	CSZ		= CS +rel_q   	-tota0_q;
			CSZ		= Ox[ inM ] + hpZ_q -tota0_q;	// we are excluding deleted q between Ox[ inM ]+Q[ inM ] .. Ox[ ixH ]-1.
			svZ		= newSVpvz(	0x6 |	CSZ	);	// round svZ allocation up to the nearest quad, +0 / -1
			SvCUR_set(				svZ,	CSZ	);
			cubeZ  	= SvPVbyte_nolen(	svZ	); 
			cubeZ[ CSZ ] = 0;																			dBUG_SvCUR(CSZ, "CSZ" );
									AvPOST( iC, svZ );		/* defer inserting the new element to (AV*) avICE*/	dBUG_1F2H

		/*	[iC+1]:	SPLICE KEYBYTE SECTION			(CASE 1F2H)									*/
		/*	cross high half of modified key data (from H) with passthrough (from char * cube0)					*/
						lpXen	=	lpZ_c| ( post_xc<< 3 );
			if(		zc == icO	){	/*	no high passthrough;	izM is the new end			Epsilon changes -->	*/	*( (ui64*) cubeZ+1 )	= E[ izM ];
				switch(	lpXen	){	SwCASE_LPXOVER_01Y( *( (ui64*) ( H +ixZ ) ),		*( (ui64*)(cube+I[ixZ])),	*( (ui64*) cubeZ )  )  }
			//						^lowpass xover wye	^high inclusion src			^low passthrough src	^ wye output

			}else if(	relZ_c==0 ){	/*	high passthrough not shifted		*/									*( (ui64*) cubeZ+1 )	= *( (ui64*) cube +1 );
				switch(	lpXen	){	SwCASE_XXOVER_01Y(	*( (ui64*)(cube+I[ixZ])),		*( (ui64*)( H +ixZ ) ),	*( (ui64*) cubeZ )  )  }
			//						^double crossover wye	^exo passthrough src		^endo inclusion src		^ wye output
			}else{	/*	shift		*/																	*( (ui64*) cubeZ+1 )	= *( (ui64*) cube +1 );
				if(	relZ_c >0	){		bs =   relZ_c	<< 3;	hipa = *( (ui64*) cube )<< bs;	}
				else{				bs = ( -relZ_c )	<< 3;	hipa = *( (ui64*) cube ) >>bs;	}
				switch(	lpXen	){	SwCASE_XXOVER_01W(	hipa,  					*( (ui64*)( H +ixZ ) ),	*( (ui64*)(cube+I[ixZ])),	*( (ui64*) cubeZ )  )  }		//				printf( "\nhigh passthrough (shifted)	lpXen=0x%02X\n	Hx:	0x%016llx\n	cubeZ:	0x%16llX\n	hipa:	0x%16llX\n	Hx>>:	0x%16llX\n	lopa:	0x%16llX\n	cube0:	0x%16llX\n",
				}//					^dbl xover dbl tee		^high passthrough, shifted	^endo inclusion src		^low passthrough src	^double-wye output		//												lpXen,				 *( (ui64*) H ), *( (ui64*) cubeZ ),		 hipa,				 *( (ui64*)( H +ixZ ) ),	*( (ui64*)(cube+I[ixZ])),	*( (ui64*) cube ) );

		/*	[iC+1]:	ASSEMBLE 3-PART Q-DATA SECTION 	(CASE 1F2H)									*/
			pqZ  = cubeZ +16;
			if(	lpZ_q	)	{		XLOAD(	pqZ,	O[ixZ],	lpZ_q,									dBUG_XLOAD_1F2H_lp1 );
						}		/*	^crossload (lpZ_q) low-pass bytes from *(cube+O[ ixZ ]) to *pqZ			*/
			if(	post_q	)	{		ICEPACK( pqZ, 	ixM, izM, ixH,										dBUG_hiCAST_1F2H_post,	dBUG_hiCAST_1F2H_post_i );
							}	/*	^re-pack modified q-data vectors ixZ..izM to cubeZ[ 16+lpZ_q..16+lpZ_q+post_q-1 ] 	*/
			if(	hpZ_q	)	{		XLOAD(	pqZ,	O[ ixH ],	hpZ_q,									dBUG_XLOAD_1F2H_hpZ );
							}	/*	^crossload (hpZ_q) high-pass bytes from *(cube+O[ ixH ] ) to *pqZ		*/

/*######	UPDATE LOW CUBE [iC+0]					(CASE 1F2H)									*/
			*( (ui64*) cube0+1 )=E[ zc0 ];	MOD_CUBE_0_AS_LPASS(	ixZ );									
			}
		else		/*	CASE 1F2S	*/					{	/* mod range crosses both fragments.  		*/
									NEW_CUBE_Z_AS_MODSxHPASS(									dBUG_hiCAST_1F2S_postZ,	dBUG_hiCAST_1F2S_postZ_i ,	dBUG_XLOAD_1F2S_hpZ);
			*( (ui64*) cube0+1)= E[ zc0 ];	MOD_CUBE_0_AS_LPASSxMODS(	ixZ,								dBUG_hiCAST_1F2S_post0,	dBUG_hiCAST_1F2S_post0_i );
			cubeZ[ CSZ	] = 0;		AvPOST( iC, svZ );		/* defer inserting the new element to (AV*) avICE*/	dBUG_1F2S
			}																						dBUGmxEO(		16	);
		}/*




*/
	else if( 	/*****		CASE 1F3	*****/	tena_zc< 21	)	{ /* One cube splits in three.				*/	dBUGrackCALL(	3 );
		/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*/	tena_nc	= tena_zc +1;
		/*	*	*	*	*	*	*	*	*	*	*	*	*/	zcZ = (	tena_nc /3) -1;		/* 4..7  */
		/*	*	*	*	*	*	*	*	*/	ixZ = tena_zc -	zcZ;
		/*	*	*/	iz1	/*	*	*/	=		ixZ -1;
		/*	*	*	*	*/	ncX		=		ixZ >>1;
		zcY		=	/*	*/	ncX		-1;	/* 4..7  */
		zc0		=	iz1  -	ncX;			/* 4..7  */
		ix1		=	zc0		+1;																		dBUG_1F3_TENA_ZC

		post_c= izM-ixM;	cube0 = cube; 	sv0 = *(pSv0 +iC );

	/*	read ahead to last fragment boundary if cursor (u) hasn't read that far	*/
		if(			u< ixZ ){/*	O[v]=O[u]+Q[u];	*/	if( RW[ v ] == null )	deIceV_KEI();
			do	{	u=v++;		Ox[v]=Ox[u]+Q[u];	O[v]=O[u]+Q[u];		DeICEv_KEI( u, v );	} while( u< ixZ );
			}

/*######	CREATE:	MEDIAL CUBE [iC+1] 	######		(CASE 1F3)		######						*/
		if( ixM >ix1 ){						CS1 = 16 +Ox[ ixZ ] - O[ ix1 ];
			sv1		= newSVpvz(	0x6 |	CS1	);
			SvCUR_set(				sv1,	CS1	);														dBUG_SvCUR(CS1, "CS1" );
			cube1  	= SvPVbyte_nolen(	sv1	);		pq1  = cube1 +16;										*( (ui64*)	cube1+1	)	= E[ iz1 ];

						lp1_q	=	O[	ixM ] -	O[	ix1 ];
			if(			lp1_q )	{	XLOAD(	pq1,	O[	ix1 ],	lp1_q,									dBUG_XLOAD_1F3_lp1 );		
								}/*	^crossload (hp1_q) low-pass bytes from *(cube+O[ ix1 ] ) to *pq1		*/
						lp1_c	=		ixM	-		ix1;
		
		/*	[iC+1]:	SUBCASE 1F3-0:	NEW CUBE 1 AS LOWPASS x MODS x HIGHPASS	(N/A)			*/
		/*	if( izM< iz1 ){		//	DELETED!!!	see backups prior to 2026-05-02						*/

		/*	[iC+1]:	SUBCASE 1F3-1:	NEW CUBE 1 AS LOWPASS x MODS								*/
		/*	}else{ */	if( izM==iz1)	{	NEW_CUBE_Z_AS_HIGHPASS(										dBUG_XLOAD_1F3MH_hpZ );
					}else  		{	NEW_CUBE_Z_AS_MODSxHPASS(									dBUG_hiCAST_1F3_postZ,	dBUG_hiCAST_1F3_postZ_i,	dBUG_XLOAD_1F3M_hpZ);
								}				post1_xc = iz1 -ixM;
							lpXen=		lp1_c| (	post1_xc<< 3 );
					switch(	lpXen){	SwCASE_LPXOVER_01Y( *( (ui64*) ( H +ix1 ) ),							*( (ui64*)(cube+I[ix1] )),	*( (ui64*) cube1 )  )  }
			//						^lowpass xover wye	^high inclusion src								^low passthrough src	^ wye output
					post1_q	=		Ox[	ixZ ]	-	Ox[	ixM	];
				if(	post1_q )	{		iCEPACK( pq1, 	ixM, iz1, ixZ,										dBUG_hiCAST_1F3LM_post1,	dBUG_hiCAST_1F3LM_post1_i );
		/*		}	*/		}	/*	^re-pack modified q-data vectors ixM..iz1 to cube1[ 16..16+post1_q-1 ]  	*/
		*( (ui64*) cube0+1)	= E[ zc0 ];	MOD_CUBE_0_AS_LPASS(	ix1 );

		}else{							CS1 = 16 +Ox[ ixZ ] - Ox[ ix1 ];
			sv1		= newSVpvz(	0x6 |	CS1	);
			SvCUR_set(				sv1,	CS1	);														dBUG_SvCUR(CS1, "CS1" );
			cube1  	= SvPVbyte_nolen(	sv1	);		pq1  = cube1 +16;										*( (ui64*)	cube1+1	)	= E[ iz1 ];

		/*	[iC+1]:	SUBCASE 1F3-2:	NEW CUBE 1 AS MODS x HIGHPASS								*/
			if( izM< iz1)	{			NEW_CUBE_Z_AS_HIGHPASS(										dBUG_XLOAD_1F3MH_hpZ );
						hp1_c	=		iz1		-		ixH;
						pre1_xc	=	I[	izM	]	-	I[	ix1 ];
						post1_c	=		izM		-		zc0;
						rel1_c	= 		post1_c	- 1 -		pre1_xc;		//	printf("\ncool\n");
							enXhp=		post1_c |(		hp1_c<< 3 );
				if(		rel1_c ){	/*	high passthrough shifts	*/				hp1_i = I[ ix1 ] -rel1_c;
					switch(	enXhp ){	SwCASE_LPXOVER_10Y( *( (ui64*)(cube +	hp1_i ) ),	*( (ui64*)( H +ix1 ) ),	*( (ui64*) cube1 )  )  }
				}else{		/*		^lowpass crossover wye	^high passthrough, shifted	^low inclusion src		^wye output		*/
					switch(	enXhp ){	SwCASE_LPXOVER_10Y( *( (ui64*)(cube+I[ ix1 ] )),	*( (ui64*)( H +ix1 ) ),	*( (ui64*) cube1 )  )  }
					}		/*		^lowpass crossover wye	^high passthrough src		^low inclusion src		^ wye output		*/
					post1_q	=		Ox[ ixH ]	- Ox[	ix1 ];
				if(	post1_q )	{		iCEPACK( pq1, 	ix1, izM, ixH,										dBUG_hiCAST_1F3MH_post1,	dBUG_hiCAST_1F3MH_post1_i );
							}	/*	^re-pack modified q-data vectors ix1..izM to cube1[ 16..16+post1_q-1 ]  	*/
						hp1_q	=	O[ ixZ ]	-	O[ ixH ];
				if(		hp1_q )	{	XLOAD(	pq1,	O[ ixH ],	hp1_q,										dBUG_XLOAD_1F3MH_hp1 );
								}/*	^crossload (hp1_q) high-pass bytes from *(cube+O[ ixH ] ) to *pq1		*/

		/*	[iC+1]:	SUBCASE 1F3-3:	NEW CUBE 1 AS MODS 										*/
			}else{	if( izM==iz1)	{	NEW_CUBE_Z_AS_HIGHPASS(										dBUG_XLOAD_1F3MH_hpZ );
					}else  		{	NEW_CUBE_Z_AS_MODSxHPASS(									dBUG_hiCAST_1F3_postZ,	dBUG_hiCAST_1F3_postZ_i,	dBUG_XLOAD_1F3M_hpZ);
								}
					switch(iz1-ix1){	SwCASE_LOWPASS_1I(							*( (ui64*)( H +ix1 ) ),	*( (ui64*) cube1 )  )  }
								/*	^inline lowpass								^definitive src			^lowpass out		*/
					post1_q	=		Ox[ ixZ ] - Ox[	ix1 ];
				if(	post1_q )	{		iCEPACK( pq1, 	ix1, iz1, ixZ,										dBUG_hiCAST_1F3M_post1,	dBUG_hiCAST_1F3M_post1_i );
				}			}	/*	^re-pack modified q-data vectors ix1..iz1 to cube1[ 16..16+post1_q-1 ]  	*/

		*( (ui64*) cube0+1)	= E[ zc0 ];	// update cube0 epsilon only now that old value can have been conserved
			if( ixM >zc0 )	{			MOD_CUBE_0_AS_LPASS(		ix1 );
			}else 		{			MOD_CUBE_0_AS_LPASSxMODS( ix1, 									dBUG_hiCAST_1F3_post0,	dBUG_hiCAST_1F3_post0_i);
			}			}

		cube1[ CS1	] =0;	AvPOST( iC, sv1 );	
		cubeZ[ CSZ	] =0;	AvPOST( iC, svZ );																dBUG_1F3
																									dBUGmxEO(		21	);
															}/*





*/
	else if( 	/*****		CASE 1F4	*****/	tena_zc< 246	)	{ /* One cube splits in 4+.				*/	dBUGrackCALL(	4 );
		int							nCx=(	tena_zc /7 )-3;
							endo_c =	nCx *7;
					exo_c = tena_zc %7;
//		if( iCx )	{
			switch(	exo_c ){								/*	zcX=6;	*/
	/* 6, 6; 5, 5 */	case 0:	zc0=5; zc1=5; zcY=4; zcZ=4;	ix1=6;	iz1=11;	ixX=12;	izX=18;	ixY=12+endo_c;	ixZ=17+endo_c;	break;
	/* 6, 6; 6, 5 */	case 1:	zc0=5; zc1=5; zcY=5; zcZ=4;	ix1=6;	iz1=11;	ixX=12;	izX=18;	ixY=12+endo_c;	ixZ=18+endo_c;	break;
	/* 6, 6; 6, 6 */	case 2:	zc0=5; zc1=5; zcY=5; zcZ=5;	ix1=6;	iz1=11;	ixX=12;	izX=18;	ixY=12+endo_c;	ixZ=18+endo_c;	break;
	/* 7, 6; 6, 6 */	case 3:	zc0=6; zc1=5; zcY=5; zcZ=5;	ix1=7;	iz1=12;	ixX=13;	izX=19;	ixY=13+endo_c;	ixZ=19+endo_c;	break;
	/* 7, 7; 6, 6 */	case 4:	zc0=6; zc1=6; zcY=5; zcZ=5;	ix1=7;	iz1=13;	ixX=14;	izX=20;	ixY=14+endo_c;	ixZ=20+endo_c;	break;
	/* 7, 7; 7, 6 */	case 5:	zc0=6; zc1=6; zcY=6; zcZ=5;	ix1=7;	iz1=13;	ixX=14;	izX=20;	ixY=14+endo_c;	ixZ=21+endo_c;	break;
	/* 7, 7; 7, 7 */	case 6:	zc0=6; zc1=6; zcY=6; zcZ=6;	ix1=7;	iz1=13;	ixX=14;	izX=20;	ixY=14+endo_c;	ixZ=21+endo_c;	break;
				}																		izY =	ixZ-1;
//		}else{
//			switch(	exo_c ){								//	zcX=-1;
//	/* 6, 6; 5, 5 */	case 0:	zc0=5; zc1=5; zcY=4; zcZ=4;	ix1=6;	ixX=						ixY=12;			ixZ=17;			break;
//	/* 6, 6; 6, 5 */	case 1:	zc0=5; zc1=5; zcY=5; zcZ=4;	ix1=6;	ixX=						ixY=12;			ixZ=18;			break;
//	/* 6, 6; 6, 6 */	case 2:	zc0=5; zc1=5; zcY=5; zcZ=5;	ix1=6;	ixX=						ixY=12;			ixZ=18;			break;
//	/* 7, 6; 6, 6 */	case 3:	zc0=6; zc1=5; zcY=5; zcZ=5;	ix1=7;	ixX=						ixY=13;			ixZ=19;			break;
//	/* 7, 7; 6, 6 */	case 4:	zc0=6; zc1=6; zcY=5; zcZ=5;	ix1=7;	ixX=						ixY=14;			ixZ=20;			break;
//	/* 7, 7; 7, 6 */	case 5:	zc0=6; zc1=6; zcY=6; zcZ=5;	ix1=7;	ixX=						ixY=14;			ixZ=21;			break;
//	/* 7, 7; 7, 7 */	case 6:	zc0=6; zc1=6; zcY=6; zcZ=6;	ix1=7;	ixX=						ixY=14;			ixZ=21;			break;
//				}								iz1 =					izX =	ixY-1;	izY =	ixZ-1;
//			}	

//		cS=sprintf( aString, "\rCASE 1F4		ixM..O: %d..%d		endo_c: %d	nCx: %d	tena_zc: %d	nCx: %d	zc0: %d	zc1: %d	zcX: %d	zcY:	%d	zcZ: %d		ix1: %d	ixX: %d	ixY: %d	ixZ: %d	\n",
//											ixM, izM,			endo_c,		nCx,	tena_zc,		nCx,	zc0,		zc1,		zcX,		zcY,		zcZ,			ix1,		ixX,		ixY,		ixZ	);
//		av_push( avDBUG, newSVpvn( aString, cS ) );


		cube0	= cube;
		sv0		= *(pSv0 +iC );

	/*	read ahead to last fragment boundary if cursor (u) hasn't read that far	*/
		if(			u< ixZ ){ /*	O[v]=O[u]+Q[u];	*/	if( RW[ v ] == null )	deIceV_KEI();
			do	{	u=v++;		Ox[v]=Ox[u]+Q[u];	O[v]=O[u]+Q[u];		DeICEv_KEI( u, v );	} while( u< ixZ );
			}	
									CSY = 16 +Ox[ ixZ ] - Ox[ ixY ];
		svY		= newSVpvz(	0x6 |	CSY	);
		SvCUR_set(				svY,	CSY	);															dBUG_SvCUR(CSY, "CSY" );
		cubeY  	= SvPVbyte_nolen(	svY	);		pqY  = cubeY +16;											*( (ui64*)	cubeY+1	)	= E[ izY ];

		/*	[iC+1]:	SUBCASE 1F4H-1:	NEW CUBE Y AS MODS x HIGHPASS								*/
		if( izM< izY )	{				NEW_CUBE_Z_AS_HIGHPASS(										dBUG_XLOAD_1F4MH_hpZ );
						hpY_c	=		izY   	-		ixH;											dBUG_SUBc1F4x1;
						preY_xc	=	I[	izM	]	-	I[	ixY	];
						postY_xc	=		izM		-		ixY;
						postY_c	=	1+	postY_xc;
						relY_c	= 		postY_xc	-		preY_xc;		printf("\nsupacool	I[ixY]=%d	relY_c=%d\n", I[ixY], relY_c);
							enXhp=		postY_c |(		hpY_c<< 3 );

			if(			relY_c ){	/*	high passthrough shifts	*/				hpY_i = I[ ixY ] -relY_c;
					switch(	enXhp ){	SwCASE_LPXOVER_10Y( *( (ui64*)(cube +	hpY_i ) ),	*( (ui64*)( H +ixY ) ),	*( (ui64*) cubeY )  )  }									dBUG_TRACE3x1;
			}else	{		/*		^lowpass crossover wye	^high passthrough, shifted	^low inclusion src		^wye output		*/
					switch(	enXhp ){	SwCASE_LPXOVER_10Y( *( (ui64*)(cube+I[ ixY] ) ), 	*( (ui64*)( H +ixY ) ),	*( (ui64*) cubeY )  )  }
					}		/*		^lowpass crossover wye	^high passthrough src		^low inclusion src		^ wye output		*/
					postY_q	=		Ox[ ixH ]	- Ox[	ixY	];
			if(		postY_q )	{		iCEpACK( pqY, 	ixY, izM, ixH,										dBUG_hiCAST_1F4MH_postY, dBUG_hiCAST_1F4MH_postY_i );	dBUG_TRACE3x2
							}	/*	^re-pack modified q-data vectors ixY..izM to cubeY[ 16..16+postY_q-1 ]  	*/
						hpY_q	=	O[ ixZ ]		-	O[ ixH ];
			if(			hpY_q )	{	XLOAD(	pqY,	O[ ixH ],	hpY_q,									dBUG_XLOAD_1F4MH_hpY );							dBUG_TRACE3x4;
								}/*	^crossload (hpY_q) high-pass bytes from *(cube+O[ ixH ] ) to *pqY		*/

		/*	[iC+1]:	SUBCASE 1F4H-2:	NEW CUBE Y AS MODS 										*/
		}else{
					if( izM==izY)	{	NEW_CUBE_Z_AS_HIGHPASS(										dBUG_XLOAD_1F4MH_hpZ );
					}else  		{	NEW_CUBE_Z_AS_MODSxHPASS(									dBUG_hiCAST_1F4_postZ,	dBUG_hiCAST_1F4_postZ_i,	dBUG_XLOAD_1F4M_hpZ);	dBUG_SUBc1F4x2
								}
					switch( izY-ixY){	SwCASE_LOWPASS_1I(							*( (ui64*)( H +ixY ) ),	*( (ui64*) cubeY )  )  }
								/*	^inline lowpass								^definitive src			^lowpass out		*/
					postY_q	=		Ox[ ixZ ] - Ox[	ixY	];
			if(		postY_q )	{		iCEpACK( pqY, 	ixY, izY, ixZ,										dBUG_hiCAST_1F4M_postY,	dBUG_hiCAST_1F4M_postY_i );	dBUG_TRACE3x8;
							}	/*	^re-pack modified q-data vectors ixY..izY to cubeY[ 16..16+postY_q-1 ]  	*/
			}
		*( (ui64*) cube0+1)	= E[ zc0 ];	// update cube0 epsilon only now that old value can have been conserved

		/*	[iC+1]:	SUBCASE 1F4L-1:	NEW CUBE 1 AS LOWPASS x MODS								*/
		if( ixM >ix1 ){						CS1 = 16 +Ox[ ixX ] - O[ ix1 ];										dBUG_SUBc1F4x4;
										sv1		= newSVpvz(	0x6 |	CS1	);
			SvCUR_set(				sv1,	CS1	);														dBUG_SvCUR(CS1, "CS1" );
			cube1  	= SvPVbyte_nolen(	sv1	);	pq1  = cube1 +16;											*( (ui64*)	cube1+1	)	= E[ iz1 ];

						lp1_q	=	O[	ixM]	-	O[	ix1 ];
			if(			lp1_q )	{	XLOAD(	pq1,	O[	ix1 ],	lp1_q,									dBUG_XLOAD_1F4_lp1 );								dBUG_TRACE1x1;
								}/*	^crossload (hp1_q) low-pass bytes from *(cube+O[ ix1 ] ) to *pq1		*/
						lp1_c	=		ixM	-		ix1;
												post1_xc = iz1 -ixM;
							lpXen=		lp1_c| (	post1_xc<< 3 );
					switch(	lpXen){	SwCASE_LPXOVER_01Y( *( (ui64*) ( H +ix1 ) ),							*( (ui64*)(cube+I[ix1] )),	*( (ui64*) cube1 )  )  }
			//						^lowpass xover wye	^high inclusion src								^low passthrough src	^ wye output
					post1_q	=		Ox[	ixX	] -	Ox[	ixM	];
			if(		post1_q )	{		iCEpACK( pq1, 	ixM, iz1, 	ixX,										dBUG_hiCAST_1F4LM_post1,	dBUG_hiCAST_1F4LM_post1_i );	dBUG_TRACE1x2;
							}	/*	^re-pack modified q-data vectors ixM..iz1 to cube1[ 16..16+post1_q-1 ]  	*/
									MOD_CUBE_0_AS_LPASS(		ix1 );

		/*	[iC+1]:	SUBCASE 1F4L-2:	NEW CUBE 1 AS MODS 										*/
		}else{							CS1 = 16 +Ox[ ixX ] - Ox[	ix1 ];
			sv1		= newSVpvz(	0x6 |	CS1	);
			SvCUR_set(				sv1,	CS1	);														dBUG_SvCUR(CS1, "CS1" );
			cube1  	= SvPVbyte_nolen(	sv1	);	pq1  = cube1 +16;											*( (ui64*)	cube1+1	)	= E[ iz1 ];
					switch(iz1-ix1){	SwCASE_LOWPASS_1I(							*( (ui64*)( H +ix1 ) ),	*( (ui64*) cube1 )  )  }
								/*	^inline lowpass								^definitive src			^lowpass out		*/
					post1_q	=		Ox[ ixX ]  - Ox[	ix1	];
			if(		post1_q )	{		iCEpACK( pq1, 	ix1, iz1, 	ixX,										dBUG_hiCAST_1F4M_post1,	dBUG_hiCAST_1F4M_post1_i );	dBUG_TRACE1x4;
							}	/*	^re-pack modified q-data vectors ix1..iz1 to cube1[ 16..16+post1_q-1 ]  	*/

			if( ixM >zc0 )	{			MOD_CUBE_0_AS_LPASS(		ix1 );	
			}else 		{			MOD_CUBE_0_AS_LPASSxMODS( ix1, 									dBUG_hiCAST_1F4_post0,	dBUG_hiCAST_1F4_post0_i );		dBUG_SUBc1F4x8;
			}			}
		cube1[ CS1	] = 0;	AvPOST( iC, sv1 );

		/*	[iC+X]:	SUBCASE 1F4X:	NEW CUBE X AS MODS 										*/
		if( nCx){		dBUG_TRACE2x1
		  do	{		_ixX = ixX+7;
										CSX = 16 +Ox[ _ixX ] - Ox[ ixX ];
			svX		= newSVpvz(	0x6 |	CSX	);
			SvCUR_set(				svX,	CSX	);														dBUG_SvCUR(CSX, "CSX" );
			cubeX  	= SvPVbyte_nolen(	svX	);	pqX  = cubeX +16;											*( (ui64*) cubeX+1	)	= E[ izX ];
									*( (ui64*) cubeX ) = *( (ui64*)( H +ixX ) ) &0x00FFFFFFFFFFFFFF;
								/*	^inline lowpass (we're just gonna hardcode this one since it's constant)	*/
					postX_q	=		Ox[ _ixX ] - Ox[	ixX	];
			if(		postX_q )	{		iCEpACK( pqX, 	ixX, izX, 	_ixX,									dBUG_hiCAST_1F4_postX,	dBUG_hiCAST_1F4_postX_i );		dBUG_TRACE2x2;
							}	/*	^re-pack modified q-data vectors ixX..izX to cubeX[ 16..16+postX_q-1 ]  	*/
			ixX+=7;	izX+=7;
			cubeX[	CSX	] = 0;	AvPOST( iC, svX );
			} while( --nCx );
			}

		cubeY[		CSY	] = 0;	AvPOST( iC, svY );
		cubeZ[		CSZ	] = 0;	AvPOST( iC, svZ );														dBUG_TRACE_1F4;
																									dBUG_1F4;
																									dBUGmxEO(		32	);
																}/*





*/
	else{ printf("\ntena_zc too great: %d\n\n", tena_zc);	}
_end: ixM=0xFF;
	}
void _av_commit(){	/* 	does batch splice on avICE, swapping new/old fragments. */

/*	word up: the algorithmic action of compaction and expansion is charicterized by "peristalsis"—
	a directed, sequential wave of movement where the order of units matters structurally,
	not just for performance.

	When you're moving overlapping regions of the same buffer, the direction of iteration isn't a choice; it's a necessity.
	Move forward during compaction, backward during expansion, or you corrupt unread source data.
	That iterative directionality is the operation's defining constraint, and it's what makes it fundamentally different
	from a simple copy or memcpy.

	*/
	long long int	asc, /*dsc, */ zsc, xsc, juke, pmo, rel, Rel;
	
	#ifdef DEBUG_AvCOMMIT_L2		//	verbose audit of nominal activity	
		long long int iRz;
		#define dBUGiniA		{		cS=sprintf( aString, "\n starting in ascending mode at step #%lld/%lld for %lld iterations\n\n",   	asc, zsc, juke);		AvDBUG_PUSH( aString, cS );	}
		#define dBUGiniD		{		cS=sprintf( aString, "\n starting in descending mode at step #%lld/%lld for %lld iterations\n\n", 	dsc, zsc, juke);		AvDBUG_PUSH( aString, cS );	}
		#define dBUGriniA		{		cS=sprintf( aString, "\n switching to ascending mode at step #%lld/%lld for %lld iterations\n\n",	asc, zsc, juke	);	AvDBUG_PUSH( aString, cS );	}
		#define dBUGriniD		{		cS=sprintf( aString, "\n switching to descending mode at step #%lld/%lld for %lld iterations\n\n",	dsc, zsc, juke	);	AvDBUG_PUSH( aString, cS );	}

		#define dBUGinsA  	{		cS=sprintf( aString, "\r+I+	avICE[ %4lld ]	= SV%-4lld			asc: %lld/%lld	juke: %lld	src/dst: %lld/%lld\n",				dst-pSv0-1, 	rSeq_iR[asc]-$insA, 	asc,	zsc, juke, src-pSv0, dst-pSv0 ); 	AvDBUG_PUSH( aString, cS );	}
		#define dBUGcutA  	{		cS=sprintf( aString, "\r-X-	avICE[ %4lld ]	= NULL				asc: %lld/%lld	juke: %lld	src/dst: %lld/%lld\n",				src-pSv0, 				  		asc,	zsc, juke, src-pSv0, dst-pSv0 );	AvDBUG_PUSH( aString, cS );	}
		#define dBUGjmpA  	{/*<<_*/	cS=sprintf( aString, "\r%c%c_	avICE[ %4lld ]	=	avICE[ %4lld ];		asc: %lld/%lld	juke: %lld	src/dst: %lld/%lld\n",	174,174, 		dst-pSv0-1, 		src-pSv0-1,	  	asc,	zsc, juke, src-pSv0, dst-pSv0 );	AvDBUG_PUSH( aString, cS );	}
		#define dBUGlocA  	{		cS=sprintf( aString, "\r|%c%c	avICE[ %4lld ]	=	avICE[ %4lld ]; [T]	asc: %lld/%lld	juke: %lld	src/dst: %lld/%lld\n",	174,174,		dst-pSv0, 		$srcA,  			asc,	zsc, juke, src-pSv0, dst-pSv0 );	AvDBUG_PUSH( aString, cS );	}

		#define dBUGinsD  	{		cS=sprintf( aString, "\r+I+	avICE[ %4d ]	= SV%-4d			dsc: %lld/%lld	juke: %lld	src/dst: %lld/%lld\n",			1+	dst-pSv0,	rSeq_iR[dsc]+1,	 	dsc,	zsc, juke, src-pSv0, dst-pSv0);  	AvDBUG_PUSH( aString, cS );	}
		#define dBUGcutD  	{		cS=sprintf( aString, "\r-X-	avICE[ %4d ]	= NULL				dsc: %lld/%lld	juke: %lld	src/dst: %lld/%lld\n",				src-pSv0,							dsc,	zsc, juke, src-pSv0, dst-pSv0);	AvDBUG_PUSH( aString, cS );	}
		#define dBUGjmpD  	{/*_>>*/	cS=sprintf( aString, "\r_%c%c	avICE[ %4d ]	=	avICE[ %4d ];		dsc: %lld/%lld	juke: %lld	src/dst: %lld/%lld\n",	175,175,	1+	dst-pSv0,	1+	src-pSv0,  		dsc,	zsc, juke, src-pSv0, dst-pSv0);	AvDBUG_PUSH( aString, cS );	}
		#define dBUGlocD  	{		cS=sprintf( aString, "\r%c%c|	avICE[ %4d ]	=	avICE[ %4d ]; [T]	dsc: %lld/%lld	juke: %lld	src/dst: %lld/%lld\n",	175,175,		dst-pSv0-$insD,	$srcD,  			dsc,	zsc, juke, src-pSv0, dst-pSv0);	AvDBUG_PUSH( aString, cS );	}
																																		
		#define dBUGlocDx	{		cS=sprintf( aString, "\r_%c|	avICE[ %4d ]	=	avICE[ %4d ]; [Tx]	dsc: %lld/%lld	\n", 							175,			$dstD, 			$srcD,			dsc,	zsc						);	AvDBUG_PUSH( aString, cS );	}
		#define dBUGjmpE		{		cS=sprintf( aString, "\r__%c	avICE[ %4d ]	=	avICE[ %4d ];		dsc: %lld/%lld	juke: %lld	src/dst: %lld/%lld\n",	175, 	1+	dst-pSv0,	1+	src-pSv0,  		dsc,	zsc, juke, src-pSv0, dst-pSv0);	AvDBUG_PUSH( aString, cS );	}

		#define dBUG_AvCOMMIT_SCHED_PRE	\
		{	cS =sprintf( aString,	"\ncommit schedule (pre process):\n	#\t\t");													\
													for( iRz=0; iRz<=7; ++iRz )	cS+=sprintf( aString +cS, "#%-7lld", 		iRz ); 	\
			cS+=sprintf( aString +cS, "\n	rSeq_iR:\t"	);	for( iRz=0; iRz<=7; ++iRz )	cS+=sprintf( aString +cS, " %-7lld",	rSeq_iR[ 	iRz ]	);	\
			cS+=sprintf( aString +cS, "\n	rSeqIns:\t"	);	for( iRz=0; iRz<=7; ++iRz )	cS+=sprintf( aString +cS, " %-7lld",	rSeqIns[ 	iRz ]	);	\
			cS+=sprintf( aString +cS, "\n	rSeqCut:\t"	);	for( iRz=0; iRz<=7; ++iRz )	cS+=sprintf( aString +cS, " %-7lld",	rSeqCut[	iRz ]	);	\
			cS+=sprintf( aString +cS, "\n	rSeqSrc:\t"	);	for( iRz=0; iRz<=7; ++iRz )	cS+=sprintf( aString +cS, " %-7lld",	rSeqSrc[	iRz ]	);	\
			cS+=sprintf( aString +cS, "\n	rSeqDst:\t"	);	for( iRz=0; iRz<=7; ++iRz )	cS+=sprintf( aString +cS, " %-7lld",	rSeqDst[	iRz ]	);	\
			cS+=sprintf( aString +cS, "\n\n");				AvDBUG_PUSH( aString, cS );	\
		}
		#define dBUG_AvCOMMIT_SCHED_POST	\
		{	cS =sprintf( aString,    	"\ncommit schedule (post process):\n	#\t\t");													\
													for( iRz=0; iRz<=7; ++iRz ) cS+=sprintf( aString +cS, "#%-7lld", 			iRz );	\
			cS+=sprintf( aString +cS, "\n	rSeq_iR:\t"	);	for( iRz=0; iRz<=7; ++iRz ) cS+=sprintf( aString +cS, " %-7lld",	rSeq_iR[ 	iRz ]	);	\
			cS+=sprintf( aString +cS, "\n	rSeqIns:\t"	);	for( iRz=0; iRz<=7; ++iRz ) cS+=sprintf( aString +cS, " %-7lld",	rSeqIns[ 	iRz ]	);	\
			cS+=sprintf( aString +cS, "\n	rSeqCut:\t"	);	for( iRz=0; iRz<=7; ++iRz ) cS+=sprintf( aString +cS, " %-7lld",	rSeqCut[	iRz ]	);	\
			cS+=sprintf( aString +cS, "\n	rSeqSrc:\t"	);	for( iRz=0; iRz<=7; ++iRz ) cS+=sprintf( aString +cS, " %-7lld",	rSeqSrc[	iRz ]	);	\
			cS+=sprintf( aString +cS, "\n	rSeqDst:\t"	);	for( iRz=0; iRz<=7; ++iRz ) cS+=sprintf( aString +cS, " %-7lld",	rSeqDst[	iRz ]	);	\
			cS+=sprintf( aString +cS, "\n\n");				AvDBUG_PUSH( aString, cS );	\
		}
	#else
		#define dBUGiniA
		#define dBUGiniD
		#define dBUGriniA
		#define dBUGriniD

		#define dBUGinsA
		#define dBUGcutA
		#define dBUGjmpA
		#define dBUGlocA
		#define dBUGinsD
		#define dBUGcutD
		#define dBUGjmpD
		#define dBUGlocD
		#define dBUGlocDx
		#define dBUGjmpE
		#define dBUG_AvCOMMIT_SCHED_PRE
		#define dBUG_AvCOMMIT_SCHED_POST
	#endif
	#ifdef DEBUG_AvCOMMIT_L3		//	paranoid integrity checks which are silent until there's a problem
		#define dBUGdscDIR	if(dsc<0 || dsc>zsc)	{	cS=sprintf( aString,		"\n!	dsc is out of bounds 0..%lld (%lld)\n", zsc, dsc);		AvDBUG_PUSH( aString, cS );	}	\
							if(src >dst )	{		cS=sprintf( aString,		"\n!	going in the wrong direction in \"_desc\" block pf function %s, file %s line %lld	src( %lld ) > dst( %lld ), step #%d/%d;	rSeqCut[%lld]: %d	rSeqSrc[%lld]: %d	rSeqDst[%lld]: %d\n",	\
																										__FUNCTION__, __FILE__, __LINE__,	src - pSv0, dst -pSv0,	dsc, zsc,		dsc, rSeqCut[dsc],	dsc, rSeqSrc[dsc],	dsc, rSeqDst[dsc]		);	AvDBUG_PUSH( aString, cS );	\
										}
		#define dBUG_JMP( $LBL)  if( pmo< 0 )	{		cS=sprintf( aString,		"\n!	\"pmo\" is negative ( %lld ) in \"%s\" block of function %s, file %s line %lld \n",				\
																						pmo,		$LBL,	__FUNCTION__, __FILE__, __LINE__		);	AvDBUG_PUSH( aString, cS );	\
										if( -pmo< src-pSv0 ){ exit_code=1; } 	\
										}
		#define dBUGascDIR	if(asc<0 || asc>zsc){	cS=sprintf( aString, 	"\n!	asc is out of bounds 0..%lld (%lld)\n", zsc, asc);	AvDBUG_PUSH( aString, cS );	}	\
							if(src< dst )	{		cS=sprintf( aString, 	"\n!	going in the wrong direction in \"_asce\" block of function %s, file %s line %lld    	src( %lld ) < dst( %lld ), step #%d/%d;	rSeqCut[%lld]: %d	rSeqSrc[%lld]: %d	rSeqDst[%lld]: %d\n", 	\
																										__FUNCTION__, __FILE__, __LINE__,	src - pSv0, dst -pSv0,	asc, zsc,		asc, rSeqCut[asc],	asc, rSeqSrc[asc],	asc, rSeqDst[asc]		);	AvDBUG_PUSH( aString, cS );	\
										}
		if( zC!= AvFILLp( avICE ) ){zzC=( zC = AvFILLp( avICE ) )-1;	cS=sprintf( aString, 	"\n!	zC( %llu ) was out-of-sync with AvFILLp( avICE )( %llu )\n", zC, AvFILLp( avICE ) );	AvDBUG_PUSH( aString, cS );			}
		if(dsc<0){											cS=sprintf( aString, 	"\n!	dsc( %llu )< 0\n", dsc );													AvDBUG_PUSH( aString, cS );	return;	}
	#else
		#define dBUG_JMP( $LBL)
		#define dBUGdscDIR
		#define dBUGascDIR
	#endif
	
/*	TODO:	Reformulate zero-cross detection logic to occur earlier on the event-driven basis of the AvPOSTxxx macros,
			to eliminate (2) second-order nested loops in the critical path	*/
/*	NOTES:

	The "_av_commit()" function finalizes all deferred array splices without copying any shifted elements more than once.
	It is only called once to finalize all insertions and deletions made by _sv_commit(), which can run many times per accessor call.

	The parameters of all deferred splices are aggregated and temporarily stored in these (4) global arrays:
		> rSeqSrc 	—the absolute index number of the operand element in the pre-operational array.
		> rSeqDst 	—the absolute index number of the operand element in the post-operational array.
		> rSeqIns 	—the number of elements to be inserted at destination index.
		> rSeqCut 	—the number of elements to be removed at source index.

	These (4) arrays align to form the "resequencing schedule", a 4x256 matrix where iterators (asc) and (dsc) each select a 1x4 vector.
	The schedule contains the relative offsets, lengths, and count parameters necessary to do multiple concurrent splices.
	It is populated left-to-right, but it is processed as a descending series of ascending / descending runs, right-to-left overall.
	The running balance of elements in the pre-op vs post-op array can go positive or negative after any consecutive splice, so,	
	the main loop is actually two main loops which flip-flop at those junctures where the running balance changes signs, crossing zero.
	The specific comparison which yields this sign is: (source index post-cut) <=> (destination index pre-insert).
	This is due to the diference in ordinality of cuts and inserts which translates the control index from where it is when first registered;
	both are determined only after the cursor register "rack_iC" has passed the reference index, yet to-be-cut elements are already there,
	whereas to-be-inserted elements are not— therefore the scheduled control index leads its cuts and trails its inserts.

	Prior to getting here, consecutive splice ops are aggregated into "batch steps" by common "control index".
	Each step defines a single shift-insert-cut iteration which affects one or many splice operations for a given control index.
	
	
	The loop starts by determining which direction to iterate in depending on whether the new length is greater than the old length.
	Actually, the direction of iteration will reverse every time the relative difference between source and destination index crosses zero.
	When flipping to "ascending mode", the (asc) iterator jumps its entire step run all at once, back tracking to (dsc-1) step-by-step;
	upon returning to (dsc-1), it jumps that amount again, flopping over to "descending mode" which picks up one element down
	from where "ascending mode" last began.  Descending mode simply iterates, while ascending mode "jukes".

	Overall though, the flip-flopping iteration pattern starts at the high end of the rSeq schedule and works leftwards to zero.
	The transitional boundary from descending to ascending shift requires special control logic (labeled "_edge").

	This text-based illustration helped me wrap my mind around the process:

dsc:		 0                    1     2               3            4        5            6    7    8    9
	---------|--------------------|-----|---------------|------------|--------|------------|----|----|----|
src:	.......xx|...............xxxxx|...xx|............xxx|....xxxxxxxx|.......x|...........x|xxxx|....|...x|..........$
		2-2                  3-5   8-2             3-3          1-8      2-1          6-1  8-4  1-0  0-1
		 0                   -2     4               4           -3       -2            3    7    8    7
dst:	.......|+‡...............|++‡...|+++++++‡............|++‡....|‡.......|+‡...........|+++++‡|+++++++‡....|‡...|..........$
	       0                 1      2                    3       4        5             6      7            8    9


	In ascending mode, the order of operations per step is:
		> cut deleted elements
		> shift intermediate elements
		> shift operand element
		> insert new elements

	In descending mode, the order of operations per step (*with one caveat) is:
		> shift intermediate elements
		> insert new elements
		> shift operand element
		> cut deleted elements

	* The first descending step after flopping from ascending mode does not shift the operand element (special case labeled "_descx").
	Rather, that assignment is preempted by the first step of the preceding ascending run and prioritized to prevent potential clobbering.

	Inserts and cuts are defined immediately upon call to AvPOST AvCUT and AvPOST_retro,
	but the shift parameter can only be computed in-between instantiations of steps.
	Obviously the final call is never followed by another, so to actually get things started here, the first thing we do is finalize the last step.

	*/
	/* finalize the last step		*/
			rSeq_iR[	dsc ]	=	iR;
			rSeqSrc[	dsc ]	=	rack_iC;			rel_iC -=	rSeqCut[ dsc ];
			rSeqDst[	dsc ]	=	rack_iC 		+	rel_iC;
							post_zC=zC		+	rel_iC +	rSeqIns[ dsc ];	if( post_zC< 0 ){	AvFILLp( avICE ) =-1;	return;	}

	/* unless the last step targets the last element, append a terminating null step to align with the pre-op and post-op array lengths */
	if(	rack_iC!=	zC ){
++	dsc;		rSeqDst[	dsc ]	=	post_zC;
			rSeqSrc[	dsc ]	=	zC;
			rSeq_iR[	dsc ]	=	-1;
			rSeqIns[	dsc ]	=	0;
			rSeqCut[	dsc ]	=	0;
//	}else{	rSeqDst[	dsc ]	-=	rSeqCut[ dsc ];
//			rSeqCut[	dsc ]	=	0;
		}
	zsc=dsc;
	/* compute destination array size and return now if it's lt/eq zero, or extend if it's gt AvMAX  (AvFILLp is set last of all) */
	if( zC< post_zC ){	av_extend(	avICE,	post_zC+1 );	pSv0=AvARRAY( avICE );	}

	#define $insD		rSeqIns[	dsc ]
	#define $cutD		rSeqCut[	dsc ]
	#define $srcD 	rSeqSrc[	dsc ]
	#define $srcutD 	rSeqSrc[	dsc ] - rSeqCut[	dsc ]
	#define $srcinsD 	rSeqSrc[	dsc ] + rSeqIns[	dsc ]
	#define $dstD 	rSeqDst[	dsc ]

	#define $insA		rSeqIns[	asc ]
	#define $cutA		rSeqCut[	asc ]
	#define $srcA		rSeqSrc[	asc ]
	#define $srcutA	rSeqSrc[	asc ] - rSeqCut[	asc ]
	#define $dstA 	rSeqDst[	asc ]

	#define $srcutX	rSeqSrc[	xsc ] - rSeqCut[	xsc ]
	#define $srcX  	rSeqSrc[	xsc ]
	#define $dstX 	rSeqDst[	xsc ]
																						dBUG_AvCOMMIT_SCHED_PRE	
	for( xsc=asc=dsc;	xsc && $srcutX==$dstX; --xsc );

	if(				$srcutX> $dstX ){
		do	{	/*	ascending start */	if( dsc ) --dsc;	else	{	src=				dst=pSv0;
														juke = asc+1;		asc=0;	dsc=-1;	dBUGiniA;	goto _asce;
													}
			} while(	$srcutD>=$dstD );						src= pSv0+$srcD;	dst=pSv0+$dstD;
														juke = asc -dsc;	asc=1+	dsc;		dBUGiniA;	goto _asce;

	}else	{	/*	descending start */						src = pSv0 +zC;	dst = pSv0 +post_zC;
			while(	$srcutA<=$dstA )	 if( asc ) --asc; else	{	juke = dsc+1;						dBUGiniD; 	goto _desc;
			}										}	juke = dsc-asc;					dBUGiniD;

	do		{	/*	as-needed reversal of normally-descending processing order	("juke" action)	*/			
	_desc:	do	{	pmo = ( src-pSv0) -$srcD;					/*	descending expansion	*/	dBUGdscDIR;	dBUG_JMP("_desc");
			//	if(0<	pmo ) if( src != dst )	do	{  *	dst-- 	= *	src--;/*	peristaltic move up		*/	dBUGjmpD;	} while( -- pmo );
				if(		0< pmo ){
						if( src != dst )	do	{  *	dst-- 	= *	src--;/*	peristaltic move up		*/	dBUGjmpD;	} while( -- pmo );
			/*		^?*/	else			{		dst -= pmo;	src -= pmo;	/*	( or not )		*/	}

				}else if(	0 >pmo ){			dst=pSv0+$dstD;src= pSv0+$srcD;
					printf("\rpmo=%lld	src-psv=	%lld	dst-psv=	%lld	zC=%lld\n	rSeqSrc[%d]=	%lld	rSeqDst[%d]=	%lld		post_zC=%lld\n\n",
						pmo,		src-pSv0,		dst-pSv0,	zC,			dsc, 			$srcD,	dsc,			$dstD,	post_zC );

					}


				if( dst -$insD != src )	{	  *(	dst-$insD)= *	src;	/*	the erratic control index	*/	dBUGlocD;	}
				while(	$insD--	)	{	  *	dst-- 	=	rSeq_SV[	rSeq_iR[ dsc ]--];			dBUGinsD;	}
				if(		$cutD	)	{					src -=$cutD +1;	$cutD=0;			}
				else									--	src;
										--	dst;
	--dsc;		} while( --juke );	if( dsc< 0) break;

	_edge:	if( src != dst )	{	pmo = (src-pSv0) -$srcD;			/*	finish to zero-crossing	*/	dBUG_JMP("_edge");
						if(0<	pmo )	do {  *	dst--	=  *	src--;							dBUGjmpE;	} while( -- pmo );
						}
			asc	= dsc;										/*	seek asc start index 	*/
			while(	$srcutD >= $dstD )	if( dsc ) --dsc;	else
				{	src=				dst=pSv0;			juke = asc+1;		asc=0;	dsc=-1;	dBUGriniA;	goto _asce;
				}	src= pSv0+$srcD;	dst=pSv0+$dstD;		juke = asc -dsc;	asc=1+	dsc;		dBUGriniA;

	_asce:	do	{											/*	ascending compaction	*/	dBUGascDIR;
				if(	$cutA ){	pmo=( $srcA -$cutA )		-	(src -pSv0);		$cutA=0;			}
				else			pmo= $srcA				-	(src -pSv0);						dBUG_JMP("_asce");
				if(0<	pmo ) if ( src!=dst )	{ do	{ *	dst++	= *	src++;/*	peristaltic move down  	*/	dBUGjmpA;	} while( -- pmo );
						}else  		{		dst += pmo;									}

				if(	dst-pSv0 != $srcA )	{	  *	dst		= *(	pSv0 +$srcA );						dBUGlocA;	}
										++	dst;			src = pSv0 +$srcA +1;
				while( $insA )			{	  *	dst++	=	rSeq_SV[	rSeq_iR[ asc ] - --$insA ];		dBUGinsA;	}

	++asc;		} while( --juke ); 	if( dsc< 0) break;

			src = dst	= pSv0 +$dstD;	/* cursor re-jumps past start (-1) of now-complete asc run	*/
			asc = dsc;
			while(	$srcutA <= $dstA ) if( asc ) --asc; 	else	{	juke = dsc;						dBUGriniD;	goto _descx;
													}	juke = dsc-asc-1;					dBUGriniD;

	_descx:			pmo = (src-pSv0) -$srcD;					/*	transversal to _desc		*/	dBUGdscDIR;	dBUG_JMP("_descx");
				if(0<	pmo )					dst -= pmo;
			//		^ pmo can go negative here, failing unset() crash precursor #7
				while(	$insD--	)	{	  *	dst-- 	=	rSeq_SV[	rSeq_iR[ dsc ]--];			dBUGinsD;	}
														/*	the erratic control index		*/
			/*! ! ! 	In _descx, we complete the "juke" by re-jumping to where _asce started,		*/
			/*		in order to resume _desc.											*/
			/*		While this is like _desc in that it does process one step of the splice schedule,	*/
			/*		there is nothing to shift because _edge already took care of that.			*/
			/*		This means there is no "peristaltic move down" or "erratic control index" line.	*/
			/*		Furthermore, while all (3) blocks evaluate the breaking point for the main loop,	*/
			/*		the main loop logically breaks a litte earlier here:							*/
			if(	dsc==0 ) break;			--	dst;
				if(		$cutD	)	{					src =pSv0 +($srcutD) -1;	$cutD=0; }
				else										src =pSv0 +$srcD -1;

	--dsc;	} while( 1 ); /*main loop */														dBUG_AvCOMMIT_SCHED_POST
	dsc=asc=juke=0;

	if( AvFILLp( avICE ) != post_zC ) AvFILLp( avICE ) = post_zC;
	}


/* **	***	***	MEXICAN FIESTA	***	***	***	***	*** .f,.gw33ff.*/