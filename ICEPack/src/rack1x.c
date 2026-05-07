/*	Copyright 2026 Peter Arlen Schmidt
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



/*######	CREATE:	HIGH CUBE [iC+1] 	######		(CASE 1F3)		######							*/
		/*	[iC+Z]:	HIGH CUBE		SUBCASE 1: 	HIGHPASS				*/
#define NEW_CUBE_Z_AS_HIGHPASS(		$dBUG_XLOAD)				hpZ_q=CS-O[ ex_z ];					\
														CSZ=16+	hpZ_q;								\
			pqZ=( cubeZ	= SvPVbyte_nolen(	svZ = newSVpvz(	CSZ |0x6 ) ) )+16;	SvCUR_set( svZ, CSZ );			dBUG_SvCUR(	CSZ,	"CSZ"	);	\
																									*( (ui64*) cubeZ+1 ) = *( (ui64*) cube +1 );	/* set Epsilon of high cube	(there is a displacement, so Epsilon of pre-op cube is conserved)	*/\
			switch(	zcZ		){		SwCASE_LOWPASS_1I(	*( (ui64*)( cube +I[	ex_z ] ) ),						*( (ui64*) cubeZ )	);	 }		\
								/*	^inline lowpass		^high passthrough src							^lowpass output	*/			\
			if(		hpZ_q )	{		XLOAD(	pqZ,	O[ ex_z ],	hpZ_q,								dBUG_XLOAD_1F3MH_hpZ );	\
		/*	} */				}	/*	^crossload (hpZ_q) high-pass bytes from *(cube+O[ ex_z ] ) to *pqZ		*/


		/*	[iC+Z]:	HIGH CUBE		SUBCASE 2: 	MODS x HIGHPASS		*/
#define NEW_CUBE_Z_AS_MODSxHPASS(	$dBUG_hiCAST, $dBUG_hiCAST_i,			$dBUG_XLOAD	)	\
																hpZ_q=CS-O[ ixN ];						\
			postZ_q	=	Ox[	ixN ]	-	Ox[	ex_z ];		CSZ=16+	hpZ_q + postZ_q;						\
			pqZ=( cubeZ	= SvPVbyte_nolen(	svZ = newSVpvz(	CSZ |0x6 ) ) )+16;	SvCUR_set( svZ, CSZ );			dBUG_SvCUR(	CSZ,	"CSZ"	);	\
			postZ_xc	= 		ixZ		-		ex_z;		\
			preZ_c	= 		icN		-	I[	ex_z ];		\
			relZ_c	= 	1+	postZ_xc	-		preZ_c;		\
		/*	hpZ_i	=	I[	ex_z ]	-		relZ_c;	*/	\
			hpZ_c	=		zc		-		icZ;			\
			\
			if( hpZ_c ){	enXhp	=	postZ_xc| ( hpZ_c<< 3 );					hpZ_i = I[ ex_z ] -relZ_c;								*( (ui64*) cubeZ+1 ) = *( (ui64*) cube +1 );	/* Epsilon of [iC] is conserved */	\
				switch(	enXhp	){	SwCASE_LPXOVER_10Y( *( (ui64*)( cube +	hpZ_i ) ), 	*( (ui64*)( H +ex_z ) ),	*( (ui64*) cubeZ )  )  	}				\
			}else{				/*	^lowpass crossover wye	 ^high passthrough, shifted	^low inclusion src		^wye output		*/	*( (ui64*) cubeZ+1 ) = E[ ixZ ];			/* Epsilon changed			*/	\
				switch(	postZ_xc ){	SwCASE_LOWPASS_1I(							*( (ui64*)( H +ex_z ) ),	*( (ui64*) cubeZ )	)	}				\
				}				/*	^lowpass inline assignment						^definitive src			^low passthrough	*/	\
			if(		postZ_q )	{		iCEpACK( pqZ,	ex_z, ixZ, ixN,										$dBUG_hiCAST, $dBUG_hiCAST_i );	\
							}	/*	^re-pack modified q-data vectors ex_z..ixZ to cubeZ[ 16..16+postZ_q-1 ]	*/									\
			if(		hpZ_q )	{		XLOAD(	pqZ,	O[ ixN ],		hpZ_q,								$dBUG_XLOAD );				\
		/*	} */				}	/*	^crossload (hpZ_q) high-pass bytes from *(cube+O[ ixN ] ) to *pqZ		*/



/*######	UPDATE:	LOW CUBE [iC+0] 	######		(CASE 1F3)		######							*/
		/*	[iC+0]:	LOW CUBE		SUBCASE 1: 	LOWPASS				*/
#define MOD_CUBE_0_AS_LPASS( 		$en )	/*	if( ix0 >zc0 ){	*/\
				switch(		zc0 ){	SwCASE_LOWPASS_1IS(	*( (ui64*) cube0 )	)		}					\
				if( CS != O[	$en ] ){			SvCUR_set(	sv0,	O[	$en ] );	cube0[	O[	$en ] ]=0;			dBUG_SvCUR(	O[	$en], "O[$en]" );	}\
		/*	} */


		/*	[iC+0]:	LOW CUBE		SUBCASE 2: 	LOWPASS x MODS			*/
#define MOD_CUBE_0_AS_LPASSxMODS( $en,		$dBUG_hiCAST, $dBUG_hiCAST_i	)	\
				if( CS <  Ox[	$en ] ){ cube0 =	SvGROW(	sv0,	Ox[	$en ] +1 );							\
											SvCUR_set(	sv0,	Ox[	$en ] );	cube0[	Ox[	$en ] ]=0;			dBUG_SvCUR(	Ox[	$en ], "Ox[ $en ]"	);	}	\
			else	if( CS != Ox[	$en ] ){			SvCUR_set(	sv0,	Ox[	$en ] );	cube0[	Ox[	$en ] ]=0;			dBUG_SvCUR(	Ox[	$en ], "Ox[ $en ]"	);	}	\
			\
			pq0 =cube0 +O[	ix0 ];			post0_xc	= zc0 - ix0;										\
						lpXen	=	ic0 |(	post0_xc<< 3 );											\
			switch(		lpXen	){	SwCASE_LPXOVER_01T( *( (ui64*) H ),									*( (ui64*) cube0)  );  }							\
								/*	^lowpass crossover tee	^high inclusion src								^low passthrough / tee output	*/				\
					post0_q		=	Ox[	$en	]	-	Ox[ 	ix0	];																					\
			if(		post0_q )	{		ICEPACK( pq0, 	ix0, zc0, $en,										$dBUG_hiCAST, $dBUG_hiCAST_i );	}	\
		/*	} */					/*	^re-pack modified q-data vectors ix0..zc0 to cube0[ O[ ix0 ]..O[ zc0 ] ]	*/





void _rack1x( ){	/*  "—1x" the basic variant to handle single-cube mod ranges.	*/
/*	(6) distinct modes for racking:
		| Condition:												| Effect:
	#1.	| rel_c is neutral.											| Overwrite cycles ic0..icZ in cube iC.  No change in cycle count.
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
			*	cube1	=NULL,		*pq1,	en_1,	enZ1,	/*	second	post-rack output cube	*/
			*	cube2	=NULL,		*pq2,					/*	second	post-rack output cube	*/
			*	cubeX	=NULL,		*pqX,	en_x,	enZx,	/*	second	post-rack output cube	*/
			*	cubeY	=NULL,		*pqY,	en_y,	enZy,	/*	second	post-rack output cube	*/
		/*	*	cubeZ	=NULL,*/		*pqZ,	ex_z,			/*	(global)	secondary active cube	*/
				tena_nc,
				ix, iz, i, h, bs,
				lpXen, enXhp,
				exo_c,																	/*	cycla count				balances		the terminating fragment	in	char *	SvPVbyte( *( AvARRAY( avICE ) +iCZ), CS )	*/
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
		zc0,	zc1,	zcx, ncX,
		rel_q,/*	rel0_q,		rel1_q,		rel2_q,		relX_q,		relY_q,		relZ_q,*/		/*	q-data length difference		compares	pre & post op q-data totals	in	matrix { A[], B[], E[], Q[] }	*/
		rel_c, /*	rel0_c,	*/	rel1_c,		rel2_c,		relX_c,		relY_c,		relZ_c;		/*	cycla count difference		compares	pre & post op cyclum counts	in	matrix { A[], B[], E[], Q[] }	*/



/*	Going in, we expect (SV*) sv  to equal *( AvARRAY( iC ) ), and (char*) cube to equal SvPVbyte( sv... ).
	In the 'operating' state,	(SV*) sv,  	(char*) cube,   	(int) iC, 	and (uchar) zc 	represent "this" 'pre-operational' cube.
	The "Z" aliases:		(SV*) svZ, 	(char*) cubeZ,  	(int) iCZ,	and (uchar) zcZ	represent the cube preceding that one.

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

	pre_q		= O[ 	icN	]	-	O[	ic0	];
	post_q		= Ox[	ixN	]	-	Ox[  ix0	];
	rel_q		= Ox[	ixN	]	-	O[	ixN	];

	if(		/*****		CASE 1A0	*****/	tena_zc< 0	)	{ /* One cube is annihilated.				*/	dBUGrackCALL(	0 );
	/*	mark element iC for deletion		*/
		AvCUT( iC );

		//get entire length of  cube # iC and  add it to the negative phase of cyclum 0 in cube iC +1
		cube0= SvPVbyte(	sv0	= *( pSv0 + iC -1	), CS0  );
		cubeZ = SvPVbyte(	svZ	= *( pSv0 + ++iC	),  CSZ );
		Ec = *( (ui64*) cube +1 ) -*( (ui64*) cube +1 );
		printf("	The total namespace inside cube %d is (was) %lld\n", Ec );

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
		post_xc		=		ixZ		-		ix0;		/* post-op endogenous cycla	(zero-based—	it is used as a vector.)	*/
		post_c		=		ixN		-		ix0;		/* post-op engodenous cycla	(one-based —	it is used as a numeral.)	*/
		pre_c		=		icN		-		ic0;		/* pre-op ablative cycla		(one-based)						*/
		rel_c		=		post_c	-		pre_c;	/* pre-to-post relative difference								*/
		hp_q		=		CS		-	O[	ixN	];	/* high passthrough q-bytes	*/
		hp_c		=		zc		-		icZ;		/* high passthrough cycla	*/						dBUG_1F1

		

/*######	UPDATE ORIGINAL CUBE [iC]:	HIGH-SIDE PASSES THROUGH PERISTALSIS IN-SITU								*/
		if(				rel_q==0	){	CSZ= CS;		cubeZ =	cube;			
		}else{						CSZ= CS +rel_q;		SvCUR_set(	svZ,	O[ ix0 ]  	); // prevent copying old data
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
				if(					hp_q >0 ){			ix = Ox[ ixN ];  		i = O[ ixN ];				dBUG_bSHIFT_1F1_DN;
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
						lpXen	=	ic0 |( post_xc<< 3 );
		if(		rel_c ){
			if(	rel_c >0){				bs =   rel_c	<< 3;	hipa = *( (ui64*) cube )<< bs;	}
			else{					bs = ( -rel_c )	<< 3;	hipa = *( (ui64*) cube ) >>bs;	}
			switch(		lpXen	){	SwCASE_XXOVER_01K(	hipa, 					*( (ui64*) H ),			*( (ui64*) cubeZ )	) 	}
		}else{	//					^dbl-xover dbl-tee		^high passthrough, shifted	^endo inclusion src		^low passthrough / tee output
			switch(		lpXen	){	SwCASE_XXOVER_01T(							*( (ui64*) H ),			*( (ui64*) cubeZ )	)	}
			}	// displacement		^double crossover tee							^endo inclusion src		^exo passthrough / tee output

		/*	[iC ]:		PACK NEW Q-DATA				(CASE 1F1)							*/
		if(		post_q	)	{					pqZ = cubeZ +O[ ix0 ];
									ICEPACK(	pqZ, 	ix0, ixZ, ixN,									dBUG_hiCAST_1F1_post,	dBUG_hiCAST_1F1_post_i );
							}	/*	^re-pack modified q-data vectors [ ix0..ixN ] in-situ			*/			dBUGmxEO(		8	);

		}/*		so.







*/
	else if( 	/*****		CASE 1F2	*****/	tena_zc< 11	)	{ /* One cube splits in two.				*/	dBUGrackCALL(	2 );

		zcZ		= tena_zc >>1;	ex_z =tena_zc	-zcZ;													dBUGmxB4(		16 );
		zc0		= ex_z -1;

		/*	retain char * pointer and char * length of pre-op cube iC for final step later	*/
		cube0	= cube;
		sv0		= *(pSv0 +iC );

		if(		/*	CASE 1F2L  	*/	ixZ< 	ex_z )	{	/* mod range contained in left fragment.		*/
		/*	read up to fragment boundary if cursor (u) hasn't read that far	*/
			if(			u< ex_z ){	/*	Ox[v]=Ox[u]+Q[u];  	*/	if( RW[ v ] == null )	deIceV_KEI();
				while(	v< ex_z ){ u=v++;	Ox[v]=Ox[u]+Q[u];							DeICEv_KEI( u, v );	
				}	}

			post_xc	=		ixZ		-		ix0; 	/*	post_xc is zero-based—	it is used as a bitvector.		*/
			post_c	=		ixN		-		ix0; 	/*	post_c is one-based—	it is used in arithmetic.		*/
			pre_c	=		icN		-		ic0;
			rel_c	=		post_c	-		pre_c;
//			totaZ_q	=		CS		-	O[	ex_z ];
					//		CS0		=	Ox[ 	ex_z ];
			hp0_q	=	Ox[ 	ex_z ]	-	Ox[ 	ixN	];
/*######	CREATE HIGH CUBE [iC+1]:	SV SETUP		(CASE 1F2L)									*/	{
									NEW_CUBE_Z_AS_HIGHPASS(										dBUG_XLOAD_1F2L_tota1 );
			*( (ui64*) cube0 +1 ) =		E[ zc0	];		/* set Epsilon of low cube while we're at it			*/	dBUG_SvCUR(CSZ, "CSZ" );
			AvPOST( iC, svZ );							/* defer inserting the new element to (AV*) avICE	*/

/*######	[iC+0]:	SPLICE KEYBYTE SECTION			(CASE 1F2L)									*/
		/*	crossover modified key data (as uquad* H ) with unaltered leading / trailing in-situ    					*/
							lpXen =	ic0 |( post_xc<< 3 );
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
			if(			rel_q >0 )	{							SvCUR_set(	sv0, O[	ix0] );	// to prevent copying old data
													cube0 =	SvGROW(	sv0, Ox[	ex_z ] +1	);
				if(					hp0_q >0 ){		ix = Ox[	ex_z ];		i =	O[	ex_z ];				dBUG_bSHIFT_1F2L_UP
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
					}							//	cube0[ Ox[ex_z] ] = 0;	SvCUR_set( sv0, Ox[ex_z] );
			}else if(		rel_q< 0 )	{
				if(					hp0_q >0 )	{	ix = O[ ixN ]+rel_q;		i = O[ ixN ];					dBUG_bSHIFT_1F2L_DN;
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
					}							//	cube0[ Ox[ex_z] ] = 0;	SvCUR_set( sv0, Ox[ex_z] );		dBUG_SvCUR(Ox[ex_z], "Ox[ex_z]" );
			}										cube0[ Ox[ex_z] ] = 0;	SvCUR_set( sv0, Ox[ex_z] );		dBUG_SvCUR(Ox[ex_z], "Ox[ex_z]" );

		/*	[iC+0]:  RE-PACK MOD Q-DATA				(CASE 1F2L)									*/
			if(	post_q	)	{				pq0 = cube0 +O[ ix0 ];
									ICEPACK( pq0, 	ix0, zc0, ex_z,										dBUG_hiCAST_1F2L_post,	dBUG_hiCAST_1F2L_post_i );
			}				}	/*	^re-pack modified q-data vectors ix0..zc0 to cube0[ O[ ix0 ]..Ox[ ex_z ]-1 ] */	}
		else if(	/*	CASE 1F2H  	*/	ix0 >=	ex_z )	{	/* mod range contained in right fragment.		*/
			post_xc	=		ixZ		-		ix0;
			post_c	=		ixN		-		ix0;
			pre_c	=		icN		-		ic0;
			rel_c	=		post_c	-		pre_c;
			relZ_c	=		rel_c	-	I[	ex_z ];

		//					CS0		=	O[  	ex_z ];
			tota0_q	=	O[	ex_z ]	-		16;		// only used once
			lpZ_c	=		ix0		-		ex_z;
			lpZ_q	=	O[	ix0	]	-	O[	ex_z ];
			hpZ_q	=		CS		-	O[	ixN	];
		//	hpZ_i	=	I[	ex_z ]	-		rel_c;


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
			if(		zc == icZ	){	/*	no high passthrough;	ixZ is the new end			Epsilon changes -->	*/	*( (ui64*) cubeZ+1 )	= E[ ixZ ];
				switch(	lpXen	){	SwCASE_LPXOVER_01Y( *( (ui64*) ( H +ex_z ) ),		*( (ui64*)(cube+I[ex_z])),	*( (ui64*) cubeZ )  )  }
			//						^lowpass xover wye	^high inclusion src			^low passthrough src	^ wye output

			}else if(	relZ_c==0 ){	/*	high passthrough not shifted		*/									*( (ui64*) cubeZ+1 )	= *( (ui64*) cube +1 );
				switch(	lpXen	){	SwCASE_XXOVER_01Y(	*( (ui64*)(cube+I[ex_z])),		*( (ui64*)( H +ex_z ) ),	*( (ui64*) cubeZ )  )  }
			//						^double crossover wye	^exo passthrough src		^endo inclusion src		^ wye output
			}else{	/*	shift		*/																	*( (ui64*) cubeZ+1 )	= *( (ui64*) cube +1 );
				if(	relZ_c >0	){		bs =   relZ_c	<< 3;	hipa = *( (ui64*) cube )<< bs;	}
				else{				bs = ( -relZ_c )	<< 3;	hipa = *( (ui64*) cube ) >>bs;	}
				switch(	lpXen	){	SwCASE_XXOVER_01W(	hipa,  					*( (ui64*)( H +ex_z ) ),	*( (ui64*)(cube+I[ex_z])),	*( (ui64*) cubeZ )  )  }
				}//					^dbl xover dbl tee		^high passthrough, shifted	^endo inclusion src		^low passthrough src	^double-wye output

		/*	[iC+1]:	ASSEMBLE 3-PART Q-DATA SECTION 	(CASE 1F2H)									*/
			pqZ  = cubeZ +16;
			if(	lpZ_q	)	{		XLOAD(	pqZ,	O[ex_z],	lpZ_q,									dBUG_XLOAD_1F2H_lp1 );
						}		/*	^crossload (lpZ_q) low-pass bytes from *(cube+O[ ex_z ]) to *pqZ		*/
			if(	post_q	)	{		ICEPACK( pqZ, 	ix0, ixZ, ixN,										dBUG_hiCAST_1F2H_post,	dBUG_hiCAST_1F2H_post_i );
							}	/*	^re-pack modified q-data vectors ex_z..ixZ to cubeZ[ 16+lpZ_q..16+lpZ_q+post_q-1 ] 	*/
			if(	hpZ_q	)	{		XLOAD(	pqZ,	O[ ixN ],	hpZ_q,									dBUG_XLOAD_1F2H_hpZ );
							}	/*	^crossload (hpZ_q) high-pass bytes from *(cube+O[ ixN ] ) to *pqZ		*/

/*######	UPDATE LOW CUBE [iC+0]					(CASE 1F2H)									*/
			*( (ui64*) cube0+1 )=E[ zc0 ];	MOD_CUBE_0_AS_LPASS(	ex_z );
			}
		else		/*	CASE 1F2S	*/					{	/* mod range crosses both fragments.  		*/
									NEW_CUBE_Z_AS_MODSxHPASS(									dBUG_hiCAST_1F2S_postZ,	dBUG_hiCAST_1F2S_postZ_i ,	dBUG_XLOAD_1F2S_hpZ);
			*( (ui64*) cube0+1)= E[ zc0 ];	MOD_CUBE_0_AS_LPASSxMODS(	ex_z,							dBUG_hiCAST_1F2S_postZ,	dBUG_hiCAST_1F2S_postZ_i );
			cubeZ[ CSZ	] = 0;		AvPOST( iC, svZ );		/* defer inserting the new element to (AV*) avICE*/	dBUG_1F2S
			}																						dBUGmxEO(		16	);
		}/*




*/
	else if( 	/*****		CASE 1F3	*****/	tena_zc< 22	)	{ /* One cube splits in three.				*/	dBUGrackCALL(	3 );
		/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*/	tena_nc	= tena_zc +1;
		/*	*	*	*	*	*	*	*	*	*	*	*	*/	zcZ = (	tena_nc /3) -1;		/* 4..7  */
		/*	*	*	*	*	*	*	*	*/	ex_z = tena_zc -	zcZ;
		/*	*	*/	enZ1	/*	*/	=		ex_z -1;
		/*	*	*	*	*/	ncX		=		ex_z >>1;
		zcx		=	/*	*/	ncX		-1;	/* 4..7  */
		zc0		=	enZ1 -	ncX;			/* 4..7  */
		en_1		=	zc0		+1;																			dBUG_1F3_TENA_ZC

		post_c= ixZ-ix0;	cube0 = cube; 	sv0 = *(pSv0 +iC );

		if( range[ix0][0] > post_c )	range[ix0][0]=post_c;
		if( range[ix0][1] < post_c )	range[ix0][1]=post_c;


#ifdef DEBUG_RACK_L1	// process audit (brief)
		avdbuginx_dmarkcase=AvFILLp( avDBUG );	av_push( avDBUG, &PL_sv_undef );	//reserve a point in the debug output for dBUG1F3 messages
#endif
	/*	read ahead to last fragment boundary if cursor (u) hasn't read that far	*/
		if(			u< ex_z ){/*	O[v]=O[u]+Q[u];	*/	if( RW[ v ] == null )	deIceV_KEI();
			do	{	u=v++;		Ox[v]=Ox[u]+Q[u];	O[v]=O[u]+Q[u];		DeICEv_KEI( u, v );	} while( u< ex_z );
			}																						dBUGmxB4( 	tena_zc );	


/*######	CREATE:	MEDIAL CUBE [iC+1] 	######		(CASE 1F3)		######						*/
		if( ix0 >en_1 ){						CS1 = 16 +Ox[ ex_z ] - O[ en_1 ];
			sv1		= newSVpvz(	0x6 |	CS1	);
			SvCUR_set(				sv1,	CS1	);														dBUG_SvCUR(CS1, "CS1" );
			cube1  	= SvPVbyte_nolen(	sv1	);		pq1  = cube1 +16;										*( (ui64*)	cube1+1	)	= E[ enZ1 ];

						lp1_q	=	O[	ix0 ]	-	O[	en_1 ];
			if(			lp1_q )	{	XLOAD(	pq1,	O[	en_1 ],	lp1_q,									dBUG_XLOAD_1F3_lp1 );		
								}/*	^crossload (hp1_q) low-pass bytes from *(cube+O[ en_1 ] ) to *pq1		*/
						lp1_c	=		ix0	-		en_1;
		
		/*	[iC+1]:	SUBCASE 1F3-0:	NEW CUBE 1 AS LOWPASS x MODS x HIGHPASS	(N/A)			*/
		/*	if( ixZ< enZ1 ){		//	DELETED!!!	see backups prior to 2026-05-02						*/

		/*	[iC+1]:	SUBCASE 1F3-1:	NEW CUBE 1 AS LOWPASS x MODS								*/
		/*	}else{ */	if( ixZ==enZ1)	{	NEW_CUBE_Z_AS_HIGHPASS(										dBUG_XLOAD_1F3MH_hpZ );
					}else  		{	NEW_CUBE_Z_AS_MODSxHPASS(									dBUG_hiCAST_1F3_postZ,	dBUG_hiCAST_1F3_postZ_i,	dBUG_XLOAD_1F3M_hpZ);
								}				post1_xc = enZ1 -ix0;
							lpXen=		lp1_c| (	post1_xc<< 3 );
					switch(	lpXen){	SwCASE_LPXOVER_01Y( *( (ui64*) ( H +en_1 ) ),							*( (ui64*)(cube+I[en_1] )),	*( (ui64*) cube1 )  )  }
			//						^lowpass xover wye	^high inclusion src								^low passthrough src	^ wye output
					post1_q	=		Ox[	ex_z ]	-	Ox[	ix0	];
				if(	post1_q )	{		iCEPACK( pq1, 	ix0, enZ1, ex_z,									dBUG_hiCAST_1F3LM_post1,	dBUG_hiCAST_1F3LM_post1_i );
		/*		}	*/		}	/*	^re-pack modified q-data vectors ix0..enZ1 to cube1[ 16..16+post1_q-1 ]  	*/
		*( (ui64*) cube0+1)	= E[ zc0 ];	// update cube0 epsilon only now that old value can have been conserved
									MOD_CUBE_0_AS_LPASS(	en_1 );

		}else{							CS1 = 16 +Ox[ ex_z ] - Ox[ en_1 ];
			sv1		= newSVpvz(	0x6 |	CS1	);
			SvCUR_set(				sv1,	CS1	);														dBUG_SvCUR(CS1, "CS1" );
			cube1  	= SvPVbyte_nolen(	sv1	);		pq1  = cube1 +16;										*( (ui64*)	cube1+1	)	= E[ enZ1 ];

		/*	[iC+1]:	SUBCASE 1F3-2:	NEW CUBE 1 AS MODS x HIGHPASS								*/
			if( ixZ< enZ1)	{			NEW_CUBE_Z_AS_HIGHPASS(										dBUG_XLOAD_1F3MH_hpZ );
						hp1_c	=		enZ1	-		ixN;
						pre1_c	=	I[	ixN	]	-	I[	en_1 ];
						post1_c	=		ixN		-		en_1;
						rel1_c	= 		post1_c	-		pre1_c;
							enXhp=		post1_c |(		hp1_c<< 3 );
				if(		rel1_c ){	/*	high passthrough shifts	*/				hp1_i = I[ en_1 ] -rel1_c;
					switch(	enXhp ){	SwCASE_LPXOVER_10Y( *( (ui64*)(cube +	hp1_i ) ),	*( (ui64*)( H +en_1 ) ),	*( (ui64*) cube1 )  )  }
				}else{		/*		^lowpass crossover wye	^high passthrough, shifted	^low inclusion src		^wye output		*/
					switch(	enXhp ){	SwCASE_LPXOVER_10Y( *( (ui64*)(cube+I[en_1] )),	*( (ui64*)( H +en_1 ) ),	*( (ui64*) cube1 )  )  }
					}		/*		^lowpass crossover wye	^high passthrough src		^low inclusion src		^ wye output		*/
					post1_q	=		Ox[ ixN ]	- Ox[	en_1 ];
				if(	post1_q )	{		iCEPACK( pq1, 	en_1, ixZ, ixN,										dBUG_hiCAST_1F3MH_post1,	dBUG_hiCAST_1F3MH_post1_i );
							}	/*	^re-pack modified q-data vectors en_1..ixZ to cube1[ 16..16+post1_q-1 ]  	*/
						hp1_q	=	O[ ex_z ]	-	O[ ixN ];
				if(		hp1_q )	{	XLOAD(	pq1,	O[ ixN ],	hp1_q,										dBUG_XLOAD_1F3MH_hp1 );
								}/*	^crossload (hp1_q) high-pass bytes from *(cube+O[ ixN ] ) to *pq1		*/

		/*	[iC+1]:	SUBCASE 1F3-3:	NEW CUBE 1 AS MODS 										*/
			}else{	if( ixZ==enZ1)	{	NEW_CUBE_Z_AS_HIGHPASS(										dBUG_XLOAD_1F3MH_hpZ );
					}else  		{	NEW_CUBE_Z_AS_MODSxHPASS(									dBUG_hiCAST_1F3_postZ,	dBUG_hiCAST_1F3_postZ_i,	dBUG_XLOAD_1F3M_hpZ);
								}
					switch(enZ1-en_1){	SwCASE_LOWPASS_1I(							*( (ui64*)( H +en_1 ) ),	*( (ui64*) cube1 )  )  }
								/*	^inline lowpass								^definitive src			^lowpass out		*/
					post1_q	=		Ox[ ex_z ] - Ox[	en_1 ];
				if(	post1_q )	{		iCEPACK( pq1, 	en_1, enZ1, ex_z,									dBUG_hiCAST_1F3M_post1,	dBUG_hiCAST_1F3M_post1_i );
				}			}	/*	^re-pack modified q-data vectors en_1..enZ1 to cube1[ 16..16+post1_q-1 ]  	*/

		*( (ui64*) cube0+1)	= E[ zc0 ];	// update cube0 epsilon only now that old value can have been conserved
			if( ix0 >zc0 )	{			MOD_CUBE_0_AS_LPASS(		en_1 );
			}else 		{			MOD_CUBE_0_AS_LPASSxMODS( en_1, 								dBUG_hiCAST_1F3_post0,	dBUG_hiCAST_1F3_post0_i);
			}			}

		cube1[ CS1 ] = 0;	AvPOST( iC, sv1 );	
		cubeZ[ CSZ ]=0;	AvPOST( iC, svZ );																dBUG_1F3
																									dBUGmxEO(		21	);
															}/*





*/
	else if( 	/*****		CASE 1F4	*****/			tena_zc< 32	)	{ /* One cube splits in 4+.				*/	dBUGrackCALL(	3 );
										endo_C = (	tena_zc /7 )-1;	if(endo_C< 0 )	printf("!	invalid tena_zc for rack case 1F4: %d\n", tena_zc );
								endo_c =	endo_C *7;
				exo_c = tena_zc -	endo_c -22;
		switch(	exo_c ){
			case 0:	/*	6, 6; 5, 5	*/	zc0=5;	zc1=5;	zcx=4;	zcZ=4;	en_1=6;		en_x=12;			en_y=12+endo_c;	ex_z=18+endo_c;	break;
			case 1:	/*	6, 6; 6, 5	*/	zc0=5;	zc1=5;	zcx=5;	zcZ=4;	en_1=6;		en_x=12;			en_y=12+endo_c;	ex_z=19+endo_c;	break;
			case 2:	/*	6, 6; 6, 6	*/	zc0=5;	zc1=5;	zcx=5;	zcZ=5;	en_1=6;		en_x=12;			en_y=12+endo_c;	ex_z=19+endo_c;	break;
			case 3:	/*	7, 6; 6, 6	*/	zc0=6;	zc1=5;	zcx=5;	zcZ=5;	en_1=7;		en_x=13;			en_y=13+endo_c;	ex_z=20+endo_c;	break;
			case 4:	/*	7, 7; 6, 6	*/	zc0=6;	zc1=6;	zcx=5;	zcZ=5;	en_1=7;		en_x=14;			en_y=14+endo_c;	ex_z=21+endo_c;	break;
			case 5:	/*	7, 7; 7, 6	*/	zc0=6;	zc1=6;	zcx=6;	zcZ=5;	en_1=7;		en_x=14;			en_y=14+endo_c;	ex_z=22+endo_c;	break;
			case 6:	/*	7, 7; 7, 7	*/	zc0=6;	zc1=6;	zcx=6;	zcZ=6;	en_1=7;		en_x=14;			en_y=14+endo_c;	ex_z=22+endo_c; /*	break;	*/
			}															enZ1 =	en_x-1;	enZx =	en_y-1;	enZy =	ex_z-1;

printf("\r	CASE 1F4 is not stable yet!	>_O\n\n");
#ifdef DEBUG_RACK_L1	// process audit (brief)
		avdbuginx_dmarkcase=AvFILLp( avDBUG );	av_push( avDBUG, &PL_sv_undef );
#endif
	/*	read ahead to last fragment boundary if cursor (u) hasn't read that far	*/
		if(			u< ex_z ){ /*	O[v]=O[u]+Q[u];	*/	if( RW[ v ] == null )	deIceV_KEI();
			do	{	u=v++;		Ox[v]=Ox[u]+Q[u];	O[v]=O[u]+Q[u];		DeICEv_KEI( u, v );	} while( u< ex_z );
			}																						dBUGmxB4( 	tena_zc );	


		/*	[iC+1]:	SUBCASE 1F4L-1:	NEW CUBE 1 AS LOWPASS x MODS								*/
		if( ix0 >en_1 ){						CS1 = 16 +Ox[ en_x ] - O[ en_1 ];
			sv1		= newSVpvz(	0x6 |	CS1	);
			SvCUR_set(				sv1,	CS1	);														dBUG_SvCUR(CS1, "CS1" );
			cube1  	= SvPVbyte_nolen(	sv1	);	pq1  = cube1 +16;											*( (ui64*)	cube1+1	)	= E[ enZ1 ];

						lp1_q	=	O[	ix0 ]	-	O[	en_1 ];
			if(			lp1_q )	{	XLOAD(	pq1,	O[	en_1 ],	lp1_q,									dBUG_XLOAD_1F4_lp1 );		
								}/*	^crossload (hp1_q) low-pass bytes from *(cube+O[ en_1 ] ) to *pq1		*/
						lp1_c	=		ix0	-		en_1;

												post1_xc = enZ1 -ix0;
							lpXen=		lp1_c| (	post1_xc<< 3 );
					switch(	lpXen){	SwCASE_LPXOVER_01Y( *( (ui64*) ( H +en_1 ) ),							*( (ui64*)(cube+I[en_1] )),	*( (ui64*) cube1 )  )  }
			//						^lowpass xover wye	^high inclusion src								^low passthrough src	^ wye output
					post1_q	=		Ox[	en_x	] -	Ox[	ix0	];
			if(		post1_q )	{		iCEPACK( pq1, 	ix0, enZ1,	en_x,								dBUG_hiCAST_1F4LM_post1,	dBUG_hiCAST_1F4LM_post1_i );
		/*		}	*/		}	/*	^re-pack modified q-data vectors ix0..enZ1 to cube1[ 16..16+post1_q-1 ]  	*/
									MOD_CUBE_0_AS_LPASS(		en_1 );

		/*	[iC+1]:	SUBCASE 1F4L-2:	NEW CUBE 1 AS MODS 										*/
		}else{							CS1 = 16 +Ox[ en_x ] - Ox[ en_1 ];
			sv1		= newSVpvz(	0x6 |	CS1	);
			SvCUR_set(				sv1,	CS1	);														dBUG_SvCUR(CS1, "CS1" );
			cube1  	= SvPVbyte_nolen(	sv1	);	pq1  = cube1 +16;											*( (ui64*)	cube1+1	)	= E[ enZ1 ];

					switch(enZ1-en_1){	SwCASE_LOWPASS_1I(							*( (ui64*)( H +en_1 ) ),	*( (ui64*) cube1 )  )  }
								/*	^inline lowpass								^definitive src			^lowpass out		*/
					post1_q	=		Ox[ en_x ] - Ox[	en_1	];
			if(		post1_q )	{		iCEPACK( pq1, 	en_1, enZ1, 	en_x,								dBUG_hiCAST_1F4M_post1,	dBUG_hiCAST_1F4M_post1_i );
							}	/*	^re-pack modified q-data vectors en_1..enZ1 to cube1[ 16..16+post1_q-1 ]  	*/
			if(	ix0 >zc0 )	{			MOD_CUBE_0_AS_LPASS(		en_1 );
			}else 		{			MOD_CUBE_0_AS_LPASSxMODS( en_1, 								dBUG_hiCAST_1F4_post0,	dBUG_hiCAST_1F4_post0_i);
			}			}




									CSY = 16 +Ox[ ex_z ] - Ox[ en_y ];
		svY		= newSVpvz(	0x6 |	CSY	);
		SvCUR_set(				svY,	CSY	);															dBUG_SvCUR(CSY, "CSY" );
		cubeY  	= SvPVbyte_nolen(	svY	);		pqY  = cubeY +16;											*( (ui64*)	cubeY+1	)	= E[ enZ1 ];


		/*	[iC+1]:	SUBCASE 1F4H-1:	NEW CUBE Y AS MODS x HIGHPASS								*/
		if( ixZ< enZy )	{				NEW_CUBE_Z_AS_HIGHPASS(										dBUG_XLOAD_1F4MH_hpZ );
						hpY_c	=		enZy	-		ixN;
						preY_c	=	I[	ixN	]	-	I[	en_y	];
						postY_c	=		ixN		-		en_y;
						relY_c	= 		postY_c	-		preY_c;
							enXhp=		postY_c |(		hpY_c<< 3 );

			if(			relY_c ){	/*	high passthrough shifts	*/				hpY_i = I[ en_y ] -relY_c;
					switch(	enXhp ){	SwCASE_LPXOVER_10Y( *( (ui64*)(cube +	hpY_i ) ),	*( (ui64*)( H +en_y ) ),	*( (ui64*) cubeY )  )  }
			}else	{		/*		^lowpass crossover wye	^high passthrough, shifted	^low inclusion src		^wye output		*/
					switch(	enXhp ){	SwCASE_LPXOVER_10Y( *( (ui64*)(cube+I[en_y] )),		*( (ui64*)( H +en_y ) ),	*( (ui64*) cubeY )  )  }
					}		/*		^lowpass crossover wye	^high passthrough src		^low inclusion src		^ wye output		*/

					postY_q	=		Ox[ ixN ]	- Ox[	en_y	];
			if(		postY_q )	{		iCEPACK( pqY, 	en_y, ixZ, ixN,										dBUG_hiCAST_1F4MH_postY,	dBUG_hiCAST_1F4MH_postY_i );
							}	/*	^re-pack modified q-data vectors en_y..ixZ to cubeY[ 16..16+postY_q-1 ]  	*/
						hpY_q	=	O[ ex_z ]		-	O[ ixN ];
			if(			hpY_q )	{	XLOAD(	pqY,	O[ ixN ],	hpY_q,									dBUG_XLOAD_1F4MH_hpY );
								}/*	^crossload (hpY_q) high-pass bytes from *(cube+O[ ixN ] ) to *pqY		*/

		/*	[iC+1]:	SUBCASE 1F4H-2:	NEW CUBE Y AS MODS 										*/
		}else{		if( ixZ==enZy)	{	NEW_CUBE_Z_AS_HIGHPASS(										dBUG_XLOAD_1F4MH_hpZ );
					}else  		{	NEW_CUBE_Z_AS_MODSxHPASS(									dBUG_hiCAST_1F4_postZ,	dBUG_hiCAST_1F4_postZ_i,	dBUG_XLOAD_1F4M_hpZ);
								}
					switch( enZy-en_y){	SwCASE_LOWPASS_1I(							*( (ui64*)( H +en_y ) ),	*( (ui64*) cubeY )  )  }
								/*	^inline lowpass								^definitive src			^lowpass out		*/
					postY_q	=		Ox[ ex_z ] - Ox[	en_y	];
			if(		postY_q )	{		iCEPACK( pqY, 	en_y, enZy, ex_z,									dBUG_hiCAST_1F4M_post1,	dBUG_hiCAST_1F4M_post1_i );
			}				}	/*	^re-pack modified q-data vectors en_y..enZy to cubeY[ 16..16+postY_q-1 ]  	*/


		cube1[ CS1	] = 0;	AvPOST( iC, sv1 );	
		cubeY[ CSY	] = 0;	AvPOST( iC, svY );
		cubeZ[ CSZ	] = 0;	AvPOST( iC, svZ );															dBUG_1F4
																									dBUGmxEO(		21	);
															}/*





*/

_end:		
	ix0=0xFF;
	}
/* booooofe	*/