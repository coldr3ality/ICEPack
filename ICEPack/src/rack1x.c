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

//"rack" re-encodes ICE data and rebalances cube fragmentation.
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "dBUG.h"
#include	"_ICE.h"
#include	"rack1x.h"

// the following(4) macros are some typical cases that were able to be generalized and consolidate across cases 1F3 and 1F4.

/*######	CREATE:	HIGH CUBE [iC+1] 	######		(CASE 1F3)		######							*/
		/*	[iC+Z]:	HIGH CUBE		SUBCASE 1: 	HIGHPASS				*/
#define NEW_CUBE_Z_AS_HIGHPASS(		$dBUG_XLOAD)				hpZ_q=CS-O[ ixZ ];					\
														CSZ=16+	hpZ_q;								\
			pqZ=( cubeZ	= SvPVbyte_nolen(	svZ = newSVpvz(	CSZ |0x6 ) ) )+16;	SvCUR_set( svZ, CSZ );			dBUG_SvCUR(	CSZ,	"CSZ"	);	\
																									*( (ui64*) cubeZ+1 ) = *( (ui64*) cube +1 );	/* set Epsilon of high cube	(there is a displacement, so Epsilon of pre-op cube is conserved)	*/\
			switch(	zcZ		){		SwCASE_LOWPASS_1I(	*( (ui64*)( cube +I[	ixZ ] ) ),						*( (ui64*) cubeZ )	);	 }			\
								/*	^inline lowpass		^high passthrough src							^lowpass output	*/				\
			if(		hpZ_q )	{		XLOAD(	pqZ,	O[ ixZ ],	hpZ_q,									$dBUG_XLOAD );					dBUG_TRACE4x4;	\
							}	/*	^crossload (hpZ_q) high-pass bytes from *(cube+O[ ixZ ] ) to *pqZ		*/


		/*	[iC+Z]:	HIGH CUBE		SUBCASE 2: 	MODS x HIGHPASS		*/
#define NEW_CUBE_Z_AS_MODSxHPASS(	$dBUG_hiCAST, $dBUG_hiCAST_i,			$dBUG_XLOAD	)	\
																hpZ_q=CS-O[ ixH ];						\
			postZ_q	=	Ox[	ixH ]	-	Ox[	ixZ ];		CSZ=16+	hpZ_q + postZ_q;						\
			pqZ=( cubeZ	= SvPVbyte_nolen(	svZ = newSVpvz(	CSZ |0x6 ) ) )+16;	SvCUR_set( svZ, CSZ );			dBUG_SvCUR(	CSZ,	"CSZ"	);	\
			postZ_xc	= 		ixO		-		ixZ;		\
			preZ_c	= 		icH		-	I[	ixZ ];		\
			relZ_c	= 	1+	postZ_xc	-		preZ_c;		\
		/*	hpZ_i	=	I[	ixZ ] 	-		relZ_c;	*/	\
			hpZ_c	=		zc		-		icO;			\
			\
			if( hpZ_c ){	enXhp	=	postZ_xc| ( hpZ_c<< 3 );					hpZ_i = I[ ixZ ] -relZ_c;								*( (ui64*) cubeZ+1 ) = *( (ui64*) cube +1 );	/* Epsilon of [iC] is conserved */	\
				switch(	enXhp	){	SwCASE_LPXOVER_10Y( *( (ui64*)( cube +	hpZ_i ) ), 	*( (ui64*)( H +ixZ ) ),	*( (ui64*) cubeZ )  )  	}			dBUG_TRACE4x1		\
			}else{				/*	^lowpass crossover wye	 ^high passthrough, shifted	^low inclusion src		^wye output		*/	*( (ui64*) cubeZ+1 ) = E[ ixO ];			/* Epsilon changed			*/	\
				switch(	postZ_xc ){	SwCASE_LOWPASS_1I(							*( (ui64*)( H +ixZ ) ),	*( (ui64*) cubeZ )	)	}			\
				}				/*	^lowpass inline assignment						^definitive src			^low passthrough	*/	\
			if(		postZ_q )	{		iCEpACK( pqZ,	ixZ, ixO, ixH,										$dBUG_hiCAST, $dBUG_hiCAST_i );	dBUG_TRACE4x2;	\
							}	/*	^re-pack modified q-data vectors ixZ..ixO to cubeZ[ 16..16+postZ_q-1 ]	*/									\
			if(		hpZ_q )	{		XLOAD(	pqZ,	O[ ixH ],		hpZ_q,								$dBUG_XLOAD );					dBUG_TRACE4x4;	\
							}	/*	^crossload (hpZ_q) high-pass bytes from *(cube+O[ ixH ] ) to *pqZ		*/


/*######	UPDATE:	LOW CUBE [iC+0] 	######		(CASE 1F3)		######							*/
		/*	[iC+0]:	LOW CUBE		SUBCASE 1: 	LOWPASS				*/
#define MOD_CUBE_0_AS_LPASS( 		ix$ )	/*	if( ixI >zc0 ){	*/\
				switch(		zc0 ){	SwCASE_LOWPASS_1IS(	*( (ui64*) cube0 )	)		}					\
				if( CS != O[	ix$ ] ){			SvCUR_set(	sv,	O[	ix$ ] );	cube0[	O[	ix$ ] ]=0;			dBUG_SvCUR(	O[	ix$], "O[ix$]" );	}\
		/*	} */


		/*	[iC+0]:	LOW CUBE		SUBCASE 2: 	LOWPASS x MODS			*/
#define MOD_CUBE_0_AS_LPASSxMODS( ix$,		$dBUG_hiCAST, $dBUG_hiCAST_i	)	\
				if( CS <  Ox[	ix$ ] ){ cube0  =	SvGROW(	sv,	Ox[	ix$ ] +1 );							\
											SvCUR_set(	sv,	Ox[	ix$ ] );	cube0[	Ox[	ix$ ] ]=0;			dBUG_SvCUR(	Ox[	ix$ ], "Ox[ ix$ ]"	);	}	\
			else	if( CS != Ox[	ix$ ] ){			SvCUR_set(	sv,	Ox[	ix$ ] );	cube0[	Ox[	ix$ ] ]=0;			dBUG_SvCUR(	Ox[	ix$ ], "Ox[ ix$ ]"	);	}	\
			\
			pq0 =cube0 +O[	ixI	];			post0_xc	= zc0 - ixI;										\
						lpXen	=	icI |(	post0_xc<< 3 );											\
			switch(		lpXen	){	SwCASE_LPXOVER_01T( *( (ui64*) H ),									*( (ui64*) cube0)  );  }							\
								/*	^lowpass crossover tee	^high inclusion src								^low passthrough / tee output	*/				\
					post0_q		=	Ox[	ix$	]	-	Ox[ 	ixI	];																					\
			if(		post0_q )	{		iCEPACK( pq0, 	ixI, zc0, ix$,										$dBUG_hiCAST, $dBUG_hiCAST_i );	dBUG_TRACE0x1;	\
							}	/*	^re-pack modified q-data vectors ixI..zc0 to cube0[ O[ ixI ]..O[ zc0 ] ]	*/


void _rack1x( ){	/*  "—1x" the basic variant to handle single-cube mod ranges.	*/
/*	(6) distinct modes for racking:
		| Condition:												| Effect:
	#1.	| rel_c is neutral.											| Overwrite cycles icI..icO in cube iC.  No change in cycle count.
	#2.	| rel_c is positive;	(2+) new cubes must be inserted to make space.	| Fragment cube iC, and distribute endogenous cubes in-between.
	#3.	| rel_c is positive;	(1) new cube must be inserted to make space.	| Fragment cube iC in a similar way as in the _alloc() function.
	#4.	| rel_c is negative;	Cycle count drops to zero, extinguishing cube iC.	| Delete cube iC.
	#5.	| rel_c is negative;	Cycle count decreases, but still non-zero.		| Right-shift trailing cycles & overwrite medial cycles if any.
	#6.	| rel_c is positive.	cube iC has enough vacant capacity.			| Left-shift trailing cycles, insert new & overwrite medials.
	*/
	SV/* *sv, */	*sv0,		*sv1,		*sv2,		*svX,		*svY;	/*	svZ [global]	*/
	STRLEN		CS0,		CS1,		CS2,		CSX,		CSY;	/*	CSZ	[global]	*/			
	si64			endo_C;								
	ui64		head, body, tail, hipa;						
	ui08 /*	*	cube	=NULL,		*pq_,					/*	(global)	primary active cube	*/
			*	cube0	=NULL,		*pq0,					/*	first		post-rack output cube 	*/
			*	cube1	=NULL,		*pq1,	ix1,  	iz1,		/*	second	post-rack output cube	*/
			*	cube2	=NULL,		*pq2,	ix2,		iz2,		/*	second	post-rack output cube	*/
			*	cubeX	=NULL,		*pqX,	ixX, _ixX,	izX,		/*	second	post-rack output cube	*/
			*	cubeY	=NULL,		*pqY,	ixY,		izY,		/*	second	post-rack output cube	*/
		/*	*	cubeZ	=NULL,*/		*pqZ,	ixZ,		izZ,		/*	(global)	secondary active cube	*/
				tena_nc,
				ix, iz, i, h, bs,
				lpXen, enXhp,
				exo_c,																	/*	cycla count				balances		the terminating fragment	in	char *	SvPVbyte( *( AvARRAY( avICE ) +iCO), CS )	*/
				endo_c,																	/*	cycla count				balances		the endogenous fragment[s]	in	char *	SvPVbyte( *( AvARRAY( avICE ) +iCX), CS )	*/
	//	pre_xc,																			/*	cycla count	(zero-based )	measures	the pre-op mod. range		in	char *	cube				*/
		pre_q,																			/*	q-data length sum			specs		the pre-op  mod. cycla		in	char *	cube				*/
		post_q,	post0_q,		post1_q,		post2_q, 		postX_q,		postY_q,		postZ_q,		/*	q-data length sum			measures	the post-op mod. cycla		in	char *	cube				*/
				tota0_q,		tota1_q,		tota2_q,		totaX_q,		totaY_q,		totaZ_q,
		post_xc,	post0_xc,	post1_xc,	post2_xc,	postX_xc,	postY_xc,	postZ_xc,	/*	cycla count	(zero-based )	defines		the post-op mod. range		in	char *	cube				*/
		post_c,	post0_c,		post1_c,		post2_c,		postX_c,		postY_c,		postZ_c,		/*	cycla count				defines		the post-op mod. range		in	char *	cube				*/
		pre_c,	pre0_c,		pre1_c,		pre2_c,		preX_c,		preY_c,		preZ_c,		/*	cycla count				measures	the pre-op mod. range		in	char *	cube				*/
							lp1_c,		lp2_c,		lpX_c,		lpY_c,		lpZ_c,		/*	cycla count				defines		the "low pass" range		in	char *	cube				*/
							lp1_q,		lp2_q,		lpX_q,		lpY_q,		lpZ_q,		/*	q-data length				defines		the "low pass" range	 	in	char *	cube				*/
		hp_c,				hp1_c,		hp2_c,		hpX_c,		hpY_c,		hpZ_c,		/*	cycla count				defines		the "high pass" range		in	char *	cube				*/
		hp_q,	hp0_q,		hp1_q,		hp2_q,		hpX_y,		hpY_q,		hpZ_q;		/*	q-data length				defines		the "high pass" range	 	in	char *	cube				*/
	char	hp_i,				hp1_i,		hp2_i,		hpX_i,		hpY_i,		hpZ_i,
		zc0,	zc1,	zcX, zcY, ncX,
		rel_q,/*	rel0_q,		rel1_q,		rel2_q,		relX_q,		relY_q,		relZ_q,*/		/*	q-data length difference		compares	pre & post op q-data totals	in	matrix { A[], B[], E[], Q[] }	*/
		rel_c, /*	rel0_c,	*/	rel1_c,		rel2_c,		relX_c,		relY_c,		relZ_c;		/*	cycla count difference		compares	pre & post op cyclum counts	in	matrix { A[], B[], E[], Q[] }	*/


	short temp_a;
	long long temp_x;
/*	Going in, we expect (SV*) sv  to equal *( AvARRAY( iC ) ), and (char*) cube to equal SvPVbyte( sv... ).
	In the 'operating' state,	(SV*) sv,  	(char*) cube,   	(int) iC, 	and (uchar) zc 	represent "this" 'pre-operational' cube.
	The "Z" aliases:		(SV*) svZ, 	(char*) cubeZ,  	(int) iCO,	and (uchar) zcZ	represent the cube preceding that one.

	However, upon return, this cube changes state to 'post-operational',thus then it is shunted down to the trailing-underscore analogs.
	It is not determined here whether this post-operational cube will precede the next to be operated on, but it may.

	The INTERLOC operations use both sets, since they bridge the logical namespace gap between two cubes, operating on both at once.
	However, those operations do not require racking or extrication, since those mutations are simple and direct in-situ assignments.


	The following cases handle different numbers of output fragments.
	"Sequestration" is when the entire mod range falls within one single fragment, and it is only possible in 1F2.
	It is not possible in 1F3 because in order to expand the input cube enough to cause it to split three ways,
	you have to add more cycla than can fit in any one fragment.
	Thus in 1F2, you have three subcases: left-sequestered, right-sequestered, and of course unsequestered.
	However, in 1F3, you have other complexity.  

	*/
//	cube= SvPVbyte_nolen(	*( pSv0 + iC ) );

#ifdef DEBUG_RACK_L1	// process audit (brief)
	av_push( avDBUG, &PL_sv_undef );	avdbuginx_dmarkcase=AvFILLp( avDBUG );	//reserve a point in the debug output for dBUG1F3 messages
#endif
	pre_q		= O[ 	icH	]	-	O[	icI	];
	post_q		= Ox[	ixH	]	-	Ox[  ixI	];
	rel_q		= Ox[	ixH	]	-	O[	ixH	];

	if(		/*****		CASE 1A0	*****/	tena_zc< 0	)	{ /* One cube is annihilated.				*/	dBUGrackCALL(	0 );
	/*	mark element iC for deletion		*/																dBUGmxB4(		8 );
		AvCUT( iC );

		//get entire length of  cube # iC and  add it to the negative phase of cyclum 0 in cube iC +1
					cubeZ = SvPVbyte(			*( pSv0 + ++iC ), CSZ );
		_deICE0(		cubeZ, CSZ, cubeZ[0], pqZ, Qc, Ac, Bc );
		if( iC )	{	cube0 = SvPVbyte_nolen(	*( pSv0 + iC -1 ) );		Ac += *( (ui64*) cube +1 ) -*( (ui64*) cube +1 );
				}											else	Ac += *( (ui64*) cube +1 );

		
		printf("	tena_zc=%d	The total namespace inside cube %d is (was) %lld\n", tena_zc, iC, Ec );

		deICE0_( Qc, Ac, Bc );			Ac += Ec;
		*( (ui64*) buf )=0;
		reICEx( Ac, Bc, cubeZ, buf );
		sv_insert( svZ, 16, Qc, buf, q );
		
		if( q!=Qc ){	rel_q =q- Qc;	CSZ += rel_q;	}

	
		}/*






*/
	else if(	/*****		CASE 1F1	*****/	tena_zc< 8	)	{ /* One cube in, one cube out.			*/	dBUGrackCALL(	1 );
		svZ			=		sv;																		dBUGmxB4(		8	);
		zcZ			=		tena_zc;
		post_xc		=		ixO		-		ixI;		/* post-op endogenous cycla	(zero-based—	it is used as a vector.)	*/
		post_c		=		ixH		-		ixI;		/* post-op engodenous cycla	(one-based —	it is used as a numeral.)	*/
		pre_c		=		icH		-		icI;		/* pre-op ablative cycla		(one-based)						*/
		rel_c		=		post_c	-		pre_c;	/* pre-to-post relative difference								*/
		hp_q		=		CS		-	O[	ixH	];	/* high passthrough q-bytes	*/
		hp_c		=		zc		-		icO;		/* high passthrough cycla	*/						dBUG_1F1

		

/*######	UPDATE ORIGINAL CUBE [iC]:	HIGH-SIDE PASSES THROUGH PERISTALSIS IN-SITU								*/
		if(				rel_q==0	){	CSZ= CS;		cubeZ =	cube;			
		}else{						CSZ= CS +rel_q;		SvCUR_set(	svZ,	O[ ixI ]  	); // prevent copying old data
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

		/*	[iC ]:		SPLICE KEYBYTE SECTION			(CASE 1F1)							*/
		/*			double-crossover of endogenous data with high and low passthrough data, in-situ	*/
						lpXen	=	icI |( post_xc<< 3 );
		if(		rel_c ){
			if(	rel_c >0){				bs =   rel_c	<< 3;	hipa = *( (ui64*) cube )<< bs;	}
			else{					bs = ( -rel_c )	<< 3;	hipa = *( (ui64*) cube ) >>bs;	}
			switch(		lpXen	){	SwCASE_XXOVER_01K(	hipa, 					*( (ui64*) H ),			*( (ui64*) cubeZ )	) 	}
		}else{	//					^dbl-xover dbl-tee		^high passthrough, shifted	^endo inclusion src		^low passthrough / tee output
			switch(		lpXen	){	SwCASE_XXOVER_01T(							*( (ui64*) H ),			*( (ui64*) cubeZ )	)	}
			}	// displacement		^double crossover tee							^endo inclusion src		^exo passthrough / tee output

		/*	[iC ]:		PACK NEW Q-DATA				(CASE 1F1)							*/
		if(		post_q	)	{					pqZ = cubeZ +O[ ixI ];
									ICEPACK(	pqZ, 	ixI, ixO, ixH,									dBUG_hiCAST_1F1_post,	dBUG_hiCAST_1F1_post_i );
							}	/*	^re-pack modified q-data vectors [ ixI..ixH ] in-situ			*/			dBUGmxEO(		8	);

		}/*		so.







*/
	else if( 	/*****		CASE 1F2	*****/	tena_zc< 15	)	{ /* One cube splits in two.				*/	dBUGrackCALL(	2 );
		zcZ		= tena_zc >>1;	ixZ =tena_zc	-zcZ;													dBUGmxB4(		16 );
		zc0		= ixZ -1;

		/*	retain char * pointer and char * length of pre-op cube iC for final step later	*/
		cube0	= cube;
		sv0		= *(pSv0 +iC );

		if(		/*	CASE 1F2L  	*/	ixO< 	ixZ )	{	/* mod range contained in left fragment.		*/
		/*	read up to fragment boundary if cursor (u) hasn't read that far	*/
			if(			u< ixZ ){		/*	Ox[v]=Ox[u]+Q[u];  	*/	if( RW[ v ] == null )	deIceV_KEI();
				while(	v< ixZ ){ u=v++;	Ox[v]=Ox[u]+Q[u];							DeICEv_KEI( u, v );	
				}	}
			post_xc	=		ixO		-		ixI; 	/*	post_xc is zero-based—	it is used as a bitvector.		*/
			post_c	=		ixH		-		ixI; 	/*	post_c is one-based—	it is used in arithmetic.		*/
			pre_c	=		icH		-		icI;
			rel_c	=		post_c	-		pre_c;
//			totaZ_q	=		CS		-	O[	ixZ ];
					//		CS0		=	Ox[ 	ixZ ];
			hp0_q	=	Ox[ 	ixZ ]	-	Ox[ 	ixH	];
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
			if(			rel_q >0 )	{							SvCUR_set(	sv0, O[	ixI] );	// to prevent copying old data
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
			}else if(		rel_q< 0 )	{
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
					}							//	cube0[ Ox[ixZ] ] = 0;	SvCUR_set( sv0, Ox[ixZ] );		dBUG_SvCUR(Ox[ixZ], "Ox[ixZ]" );
			}										cube0[ Ox[ixZ] ] = 0;	SvCUR_set( sv0, Ox[ixZ] );		dBUG_SvCUR(Ox[ixZ], "Ox[ixZ]" );

		/*	[iC+0]:  RE-PACK MOD Q-DATA				(CASE 1F2L)									*/
			if(	post_q	)	{				pq0 = cube0 +O[ ixI ];
									ICEPACK( pq0, 	ixI, zc0, ixZ,										dBUG_hiCAST_1F2L_post,	dBUG_hiCAST_1F2L_post_i );
							}	/*	^re-pack modified q-data vectors ixI..zc0 to cube0[ O[ ixI ]..Ox[ ixZ ]-1 ]	*/}	dBUG_1F2L
			}
		else if(	/*	CASE 1F2H  	*/	ixI >=	ixZ )	{	/* mod range contained in right fragment.		*/
			post_xc	=		ixO		-		ixI;
			post_c	=		ixH		-		ixI;
			pre_c	=		icH		-		icI;
			rel_c	=		post_c	-		pre_c;
			relZ_c	=		rel_c	-	I[	ixZ ];

		//					CS0		=	O[  	ixZ ];
			tota0_q	=	O[	ixZ ]	-		16;		// only used once
			lpZ_c	=		ixI		-		ixZ;
			lpZ_q	=	O[	ixI	]	-	O[	ixZ ];
			hpZ_q	=		CS		-	O[	ixH	];
		//	hpZ_i	=	I[	ixZ ]	-		rel_c;

/*######	CREATE HIGH CUBE [iC+1]:	SV SETUP		(CASE 1F2H)									*/
		/*	create new cube to serve as the higher fragment											*/
			CSZ		= CS +rel_q   	-tota0_q;																
			svZ		= newSVpvz(	0x6 |	CSZ	);	// round svZ allocation up to the nearest quad, +0 / -1
			SvCUR_set(				svZ,	CSZ	);
			cubeZ  	= SvPVbyte_nolen(	svZ	); 
			cubeZ[ CSZ ] = 0;																			dBUG_SvCUR(CSZ, "CSZ" );
			cubeZ[ CSZ	] = 0;		AvPOST( iC, svZ );		/* defer inserting the new element to (AV*) avICE*/	dBUG_1F2H

		/*	[iC+1]:	SPLICE KEYBYTE SECTION			(CASE 1F2H)									*/
		/*	cross high half of modified key data (from H) with passthrough (from char * cube0)					*/
						lpXen	=	lpZ_c| ( post_xc<< 3 );
			if(		zc == icO	){	/*	no high passthrough;	ixO is the new end			Epsilon changes -->	*/	*( (ui64*) cubeZ+1 )	= E[ ixO ];
				switch(	lpXen	){	SwCASE_LPXOVER_01Y( *( (ui64*) ( H +ixZ ) ),		*( (ui64*)(cube+I[ixZ])),	*( (ui64*) cubeZ )  )  }
			//						^lowpass xover wye	^high inclusion src			^low passthrough src	^ wye output

			}else if(	relZ_c==0 ){	/*	high passthrough not shifted		*/									*( (ui64*) cubeZ+1 )	= *( (ui64*) cube +1 );
				switch(	lpXen	){	SwCASE_XXOVER_01Y(	*( (ui64*)(cube+I[ixZ])),		*( (ui64*)( H +ixZ ) ),	*( (ui64*) cubeZ )  )  }
			//						^double crossover wye	^exo passthrough src		^endo inclusion src		^ wye output
			}else{	/*	shift		*/																	*( (ui64*) cubeZ+1 )	= *( (ui64*) cube +1 );
				if(	relZ_c >0	){		bs =   relZ_c	<< 3;	hipa = *( (ui64*) cube )<< bs;	}
				else{				bs = ( -relZ_c )	<< 3;	hipa = *( (ui64*) cube ) >>bs;	}
				switch(	lpXen	){	SwCASE_XXOVER_01W(	hipa,  					*( (ui64*)( H +ixZ ) ),	*( (ui64*)(cube+I[ixZ])),	*( (ui64*) cubeZ )  )  }
				}//					^dbl xover dbl tee		^high passthrough, shifted	^endo inclusion src		^low passthrough src	^double-wye output

		/*	[iC+1]:	ASSEMBLE 3-PART Q-DATA SECTION 	(CASE 1F2H)									*/
			pqZ  = cubeZ +16;
			if(	lpZ_q	)	{		XLOAD(	pqZ,	O[ixZ],	lpZ_q,									dBUG_XLOAD_1F2H_lp1 );
						}		/*	^crossload (lpZ_q) low-pass bytes from *(cube+O[ ixZ ]) to *pqZ		*/
			if(	post_q	)	{		ICEPACK( pqZ, 	ixI, ixO, ixH,										dBUG_hiCAST_1F2H_post,	dBUG_hiCAST_1F2H_post_i );
							}	/*	^re-pack modified q-data vectors ixZ..ixO to cubeZ[ 16+lpZ_q..16+lpZ_q+post_q-1 ] 	*/
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
	else if( 	/*****		CASE 1F3	*****/	tena_zc< 22	)	{ /* One cube splits in three.				*/	dBUGrackCALL(	3 );
		/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*/	tena_nc	= tena_zc +1;
		/*	*	*	*	*	*	*	*	*	*	*	*	*/	zcZ = (	tena_nc /3) -1;		/* 4..7  */
		/*	*	*	*	*	*	*	*	*/	ixZ = tena_zc -	zcZ;
		/*	*	*/	iz1	/*	*	*/	=		ixZ -1;
		/*	*	*	*	*/	ncX		=		ixZ >>1;
		zcY		=	/*	*/	ncX		-1;	/* 4..7  */
		zc0		=	iz1  -	ncX;			/* 4..7  */
		ix1		=	zc0		+1;																		dBUG_1F3_TENA_ZC

		post_c= ixO-ixI;	cube0 = cube; 	sv0 = *(pSv0 +iC );

	/*	read ahead to last fragment boundary if cursor (u) hasn't read that far	*/
		if(			u< ixZ ){/*	O[v]=O[u]+Q[u];	*/	if( RW[ v ] == null )	deIceV_KEI();
			do	{	u=v++;		Ox[v]=Ox[u]+Q[u];	O[v]=O[u]+Q[u];		DeICEv_KEI( u, v );	} while( u< ixZ );
			}

/*######	CREATE:	MEDIAL CUBE [iC+1] 	######		(CASE 1F3)		######						*/
		if( ixI >ix1 ){						CS1 = 16 +Ox[ ixZ ] - O[ ix1 ];
			sv1		= newSVpvz(	0x6 |	CS1	);
			SvCUR_set(				sv1,	CS1	);														dBUG_SvCUR(CS1, "CS1" );
			cube1  	= SvPVbyte_nolen(	sv1	);		pq1  = cube1 +16;										*( (ui64*)	cube1+1	)	= E[ iz1 ];

						lp1_q	=	O[	ixI ]	-	O[	ix1 ];
			if(			lp1_q )	{	XLOAD(	pq1,	O[	ix1 ],	lp1_q,									dBUG_XLOAD_1F3_lp1 );		
								}/*	^crossload (hp1_q) low-pass bytes from *(cube+O[ ix1 ] ) to *pq1		*/
						lp1_c	=		ixI	-		ix1;
		
		/*	[iC+1]:	SUBCASE 1F3-0:	NEW CUBE 1 AS LOWPASS x MODS x HIGHPASS	(N/A)			*/
		/*	if( ixO< iz1 ){		//	DELETED!!!	see backups prior to 2026-05-02						*/

		/*	[iC+1]:	SUBCASE 1F3-1:	NEW CUBE 1 AS LOWPASS x MODS								*/
		/*	}else{ */	if( ixO==iz1)	{	NEW_CUBE_Z_AS_HIGHPASS(										dBUG_XLOAD_1F3MH_hpZ );
					}else  		{	NEW_CUBE_Z_AS_MODSxHPASS(									dBUG_hiCAST_1F3_postZ,	dBUG_hiCAST_1F3_postZ_i,	dBUG_XLOAD_1F3M_hpZ);
								}				post1_xc = iz1 -ixI;
							lpXen=		lp1_c| (	post1_xc<< 3 );
					switch(	lpXen){	SwCASE_LPXOVER_01Y( *( (ui64*) ( H +ix1 ) ),							*( (ui64*)(cube+I[ix1] )),	*( (ui64*) cube1 )  )  }
			//						^lowpass xover wye	^high inclusion src								^low passthrough src	^ wye output
					post1_q	=		Ox[	ixZ ]	-	Ox[	ixI	];
				if(	post1_q )	{		iCEPACK( pq1, 	ixI, iz1, ixZ,										dBUG_hiCAST_1F3LM_post1,	dBUG_hiCAST_1F3LM_post1_i );
		/*		}	*/		}	/*	^re-pack modified q-data vectors ixI..iz1 to cube1[ 16..16+post1_q-1 ]  	*/
		*( (ui64*) cube0+1)	= E[ zc0 ];	MOD_CUBE_0_AS_LPASS(	ix1 );

		}else{							CS1 = 16 +Ox[ ixZ ] - Ox[ ix1 ];
			sv1		= newSVpvz(	0x6 |	CS1	);
			SvCUR_set(				sv1,	CS1	);														dBUG_SvCUR(CS1, "CS1" );
			cube1  	= SvPVbyte_nolen(	sv1	);		pq1  = cube1 +16;										*( (ui64*)	cube1+1	)	= E[ iz1 ];

		/*	[iC+1]:	SUBCASE 1F3-2:	NEW CUBE 1 AS MODS x HIGHPASS								*/
			if( ixO< iz1)	{			NEW_CUBE_Z_AS_HIGHPASS(										dBUG_XLOAD_1F3MH_hpZ );
						hp1_c	=		iz1		-		ixH;
						pre1_c	=	I[	ixH	]	-	I[	ix1 ];
						post1_c	=		ixH		-		ix1;
						rel1_c	= 		post1_c	-		pre1_c;
							enXhp=		post1_c |(		hp1_c<< 3 );
				if(		rel1_c ){	/*	high passthrough shifts	*/				hp1_i = I[ ix1 ] -rel1_c;
					switch(	enXhp ){	SwCASE_LPXOVER_10Y( *( (ui64*)(cube +	hp1_i ) ),	*( (ui64*)( H +ix1 ) ),	*( (ui64*) cube1 )  )  }
				}else{		/*		^lowpass crossover wye	^high passthrough, shifted	^low inclusion src		^wye output		*/
					switch(	enXhp ){	SwCASE_LPXOVER_10Y( *( (ui64*)(cube+I[ ix1 ] )),	*( (ui64*)( H +ix1 ) ),	*( (ui64*) cube1 )  )  }
					}		/*		^lowpass crossover wye	^high passthrough src		^low inclusion src		^ wye output		*/
					post1_q	=		Ox[ ixH ]	- Ox[	ix1 ];
				if(	post1_q )	{		iCEPACK( pq1, 	ix1, ixO, ixH,										dBUG_hiCAST_1F3MH_post1,	dBUG_hiCAST_1F3MH_post1_i );
							}	/*	^re-pack modified q-data vectors ix1..ixO to cube1[ 16..16+post1_q-1 ]  	*/
						hp1_q	=	O[ ixZ ]	-	O[ ixH ];
				if(		hp1_q )	{	XLOAD(	pq1,	O[ ixH ],	hp1_q,										dBUG_XLOAD_1F3MH_hp1 );
								}/*	^crossload (hp1_q) high-pass bytes from *(cube+O[ ixH ] ) to *pq1		*/

		/*	[iC+1]:	SUBCASE 1F3-3:	NEW CUBE 1 AS MODS 										*/
			}else{	if( ixO==iz1)	{	NEW_CUBE_Z_AS_HIGHPASS(										dBUG_XLOAD_1F3MH_hpZ );
					}else  		{	NEW_CUBE_Z_AS_MODSxHPASS(									dBUG_hiCAST_1F3_postZ,	dBUG_hiCAST_1F3_postZ_i,	dBUG_XLOAD_1F3M_hpZ);
								}
					switch(iz1-ix1){	SwCASE_LOWPASS_1I(							*( (ui64*)( H +ix1 ) ),	*( (ui64*) cube1 )  )  }
								/*	^inline lowpass								^definitive src			^lowpass out		*/
					post1_q	=		Ox[ ixZ ] - Ox[	ix1 ];
				if(	post1_q )	{		iCEPACK( pq1, 	ix1, iz1, ixZ,										dBUG_hiCAST_1F3M_post1,	dBUG_hiCAST_1F3M_post1_i );
				}			}	/*	^re-pack modified q-data vectors ix1..iz1 to cube1[ 16..16+post1_q-1 ]  	*/

		*( (ui64*) cube0+1)	= E[ zc0 ];	// update cube0 epsilon only now that old value can have been conserved
			if( ixI >zc0 )	{			MOD_CUBE_0_AS_LPASS(		ix1 );
			}else 		{			MOD_CUBE_0_AS_LPASSxMODS( ix1, 									dBUG_hiCAST_1F3_post0,	dBUG_hiCAST_1F3_post0_i);
			}			}

		cube1[ CS1	] =0;	AvPOST( iC, sv1 );	
		cubeZ[ CSZ	] =0;	AvPOST( iC, svZ );																dBUG_1F3
																									dBUGmxEO(		21	);
															}/*





*/
	else if( 	/*****		CASE 1F4	*****/	tena_zc< 128	)	{ /* One cube splits in 4+.				*/	dBUGrackCALL(	4 );
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

//		cS=sprintf( aString, "\rCASE 1F4		ixI..O: %d..%d		endo_c: %d	nCx: %d	tena_zc: %d	nCx: %d	zc0: %d	zc1: %d	zcX: %d	zcY:	%d	zcZ: %d		ix1: %d	ixX: %d	ixY: %d	ixZ: %d	\n",
//							ixI, ixO,			endo_c,		nCx,	tena_zc,		nCx,	zc0,		zc1,		zcX,		zcY,		zcZ,			ix1,		ixX,		ixY,		ixZ	);
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
		if( ixO< izY )	{				NEW_CUBE_Z_AS_HIGHPASS(										dBUG_XLOAD_1F4MH_hpZ );
						hpY_c	=		izY   	-		ixH;											dBUG_SUBc1F4x1;
						preY_c	=	I[	ixH	]	-	I[	ixY	];
						postY_c	=		ixH		-		ixY;
						relY_c	= 		postY_c	-		preY_c;
							enXhp=		postY_c |(		hpY_c<< 3 );

			if(			relY_c ){	/*	high passthrough shifts	*/				hpY_i = I[ ixY ] -relY_c;
					switch(	enXhp ){	SwCASE_LPXOVER_10Y( *( (ui64*)(cube +	hpY_i ) ),	*( (ui64*)( H +ixY ) ),	*( (ui64*) cubeY )  )  }									dBUG_TRACE3x1;
			}else	{		/*		^lowpass crossover wye	^high passthrough, shifted	^low inclusion src		^wye output		*/
					switch(	enXhp ){	SwCASE_LPXOVER_10Y( *( (ui64*)(cube+I[ ixY] ) ), 	*( (ui64*)( H +ixY ) ),	*( (ui64*) cubeY )  )  }
					}		/*		^lowpass crossover wye	^high passthrough src		^low inclusion src		^ wye output		*/
					postY_q	=		Ox[ ixH ]	- Ox[	ixY	];
			if(		postY_q )	{		iCEpACK( pqY, 	ixY, ixO, ixH,										dBUG_hiCAST_1F4MH_postY, dBUG_hiCAST_1F4MH_postY_i );	dBUG_TRACE3x2
							}	/*	^re-pack modified q-data vectors ixY..ixO to cubeY[ 16..16+postY_q-1 ]  	*/
						hpY_q	=	O[ ixZ ]		-	O[ ixH ];
			if(			hpY_q )	{	XLOAD(	pqY,	O[ ixH ],	hpY_q,									dBUG_XLOAD_1F4MH_hpY );							dBUG_TRACE3x4;
								}/*	^crossload (hpY_q) high-pass bytes from *(cube+O[ ixH ] ) to *pqY		*/
		/*	[iC+1]:	SUBCASE 1F4H-2:	NEW CUBE Y AS MODS 										*/
		}else{
					if( ixO==izY)	{	NEW_CUBE_Z_AS_HIGHPASS(										dBUG_XLOAD_1F4MH_hpZ );
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
		if( ixI >ix1 ){						CS1 = 16 +Ox[ ixX ] - O[ ix1 ];										dBUG_SUBc1F4x4;
										sv1		= newSVpvz(	0x6 |	CS1	);
			SvCUR_set(				sv1,	CS1	);														dBUG_SvCUR(CS1, "CS1" );
			cube1  	= SvPVbyte_nolen(	sv1	);	pq1  = cube1 +16;											*( (ui64*)	cube1+1	)	= E[ iz1 ];

						lp1_q	=	O[	ixI ]	-	O[	ix1 ];
			if(			lp1_q )	{	XLOAD(	pq1,	O[	ix1 ],	lp1_q,									dBUG_XLOAD_1F4_lp1 );								dBUG_TRACE1x1;
								}/*	^crossload (hp1_q) low-pass bytes from *(cube+O[ ix1 ] ) to *pq1		*/
						lp1_c	=		ixI	-		ix1;
												post1_xc = iz1 -ixI;
							lpXen=		lp1_c| (	post1_xc<< 3 );
					switch(	lpXen){	SwCASE_LPXOVER_01Y( *( (ui64*) ( H +ix1 ) ),							*( (ui64*)(cube+I[ix1] )),	*( (ui64*) cube1 )  )  }
			//						^lowpass xover wye	^high inclusion src								^low passthrough src	^ wye output
					post1_q	=		Ox[	ixX	] -	Ox[	ixI	];
			if(		post1_q )	{		iCEpACK( pq1, 	ixI, iz1, 	ixX,										dBUG_hiCAST_1F4LM_post1,	dBUG_hiCAST_1F4LM_post1_i );	dBUG_TRACE1x2;
							}	/*	^re-pack modified q-data vectors ixI..iz1 to cube1[ 16..16+post1_q-1 ]  	*/
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

			if( ixI >zc0 )	{			MOD_CUBE_0_AS_LPASS(		ix1 );	
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





*/	else{ printf("\ntena_zc too great: %d\n\n", tena_zc);	}

_end:		
	ixI=0xFF;
	}
/* booooofe	*/