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


//	void _sv_commit_nx() updates or fragments source cube into 2, 3, or 4+ parts.  The overlap of fragment boundaries and modification range boundaries further differentiates these four main cases.

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

#include	"_sv_commit.h"
#include	"_sv_commit_nx.h"
#include	"_AvSEQ.h"
#include	"SwCASE.h"	
#include	"access_extern.h"

void _sv_commit_nx( ){	//	if( xcª -ixº <1 ||trace){ trace=1;	printf( "\r	%s() enter	%s line %d\n", __FUNCTION__, __FILE__, __LINE__ ); }
	SV				*sv0,		*sv¹,		*svⁿ,		*sv²,				/*	svΩ 	[global]	*/	*svI	= *( AvARRAY( avICE) +iCI );
	STRLEN			CSº,   		CS¹,  		CSⁿ, 		CS²,			xCS,	/*	CSΩ	[global]	*/	CSI	= SvCUR( svI );
	si64			endo_C;								
	ui64			head, body, tail, hipa, iCx;
	unsigned short	ix,		iz,		/*buffer matrix scratch indeces	*/
				/*	ixº	*/	izº,		/*	last index					of first cube (cubeº_		*/
					ix¹,	  	iz¹,		/*	start/end vector map indeces	of second		post-commit output cube		*/
					ixⁿ, _ixⁿ,	izⁿ,		/*	start/end vector map indeces	of endogenous	post-commit output cube[s]		*/
					ix²,		iz²,		/*	start/end vector map indeces	next-to-last		post-commit output cube		*/
					ixΩ,		izΩ;		/*	start/end vector map indeces	of last (global)		post-commot output cube		*/
	unsigned char		i, o,		/* cube dbug scratch indeces		*/
			*p_, /*	*cube	=NULL,	*/							/*	last				pre-commit source cube (global)	*/
			*pº, 	*cubeº,										/*	first				post-commit output cube 		*/
			*p¹, 	*cube¹	=NULL,								/*	second			post-commit output cube		*/
			*pⁿ, 	*cubeⁿ	=NULL,								/*	endo			post-commit output cube		*/
			*p², 	*cube²	=NULL,								/*	next-to-last		post-commit output cube		*/
			*pΩ,/*	*cubeΩ	=NULL,*/								/*	last	(global)		secondary active cube			*/
					bs,
					lpXen, enXhp,
					exo_c,														/*	cycla count				balances		the terminating fragment	in	char *	SvPVbyte( *( AvARRAY( avICE ) +iCO), CS )	*/
					endo_c,														/*	cycla count				balances		the endogenous fragment[s]	in	char *	SvPVbyte( *( AvARRAY( avICE ) +iCX), CS )	*/
			pre_q,													preΩ_q,		/*	q-data length sum			specs		the pre-op  mod. cycla		in	char *	cube				*/
			post_q,	postº_q,		post¹_q,		postⁿ_q,		post²_q,		postΩ_q,		/*	q-data length sum			measures	the post-op mod. cycla		in	char *	cube				*/
								lp¹_q,		lpⁿ_q,		lp²_q,		lpΩ_q,		/*	q-data length				defines		the "low pass" range	 	in	char *	cube				*/
			hp_q,	hpº_q,		hp¹_q,					hp²_q,		hpΩ_q,		/*	q-data length				defines		the "high pass" range	 	in	char *	cube				*/
					hpº_o,		hp¹_o,					hp²_o,		hpΩ_o;
	short	hp_i,				hp¹_i,		hpⁿ_i,		hp²_i,		hpΩ_i,	tcª =xcª -ixº, ncª;
	char 			zcº,			zc¹,			zcⁿ,	ncⁿ,		zc²,
			post_xc,	postº_xc, 	post¹_xc, 	postⁿ_xc, 	post²_xc, 	postΩ_xc,	/*	cycla count	(zero-based )	defines		the post-op mod. range		in	char *	cube				*/
			post_c,	postº_c,		post¹_c,		postⁿ_c,		post²_c,		postΩ_c,		/*	cycla count				defines		the post-op mod. range		in	char *	cube				*/
			pre_c,	preº_c,		pre¹_c,		preⁿ_c,		pre²_c,		preΩ_c,		/*	cycla count				measures	the pre-op mod. range		in	char *	cube				*/
			pre_xc,	preº_xc,		pre¹_xc,		preⁿ_xc,		pre²_xc,		preΩ_xc,		/*	cycla count	(zero-based )	measures	the pre-op mod. range		in	char *	cube				*/
								lp¹_c,		lpⁿ_c,		lp²_c,		lpΩ_c,		/*	cycla count				defines		the "low pass" range		in	char *	cube				*/
			hp_c,				hp¹_c,		hpⁿ_c,		hp²_c,		hpΩ_c,		/*	cycla count				defines		the "high pass" range		in	char *	cube				*/
			rel_q,/*	relº_q,		rel¹_q,		relⁿ_q,		rel²_q,	*/	relΩ_q,		/*	q-data length difference		compares	pre & post op q-data totals	in	matrix { A[], B[], E[], L[] }	*/
			rel_c, /*	relº_c,	*/	rel¹_c,		relⁿ_c,		rel²_c,		relΩ_c;		/*	cycla count difference		compares	pre & post op cyclum counts	in	matrix { A[], B[], E[], L[] }	*/

#if defined( DEBUG_SvCOMMIT_L0 ) || defined( DEBUG_SvCOMMIT_L1 )
	subcase=0;
	av_push( avDBUG, &PL_sv_undef );	avdbuginx_dmarkcase=AvFILLp( avDBUG );	//reserve a point in the debug output for dBUGNX3 messages
#endif
	char icI	= I[ ixM ];

/*	char icO	= I[ izM ];		I once assumed icO was supposed to be equal to I[ izM ], but it is sometimes +1.
						This happens when ablative ops send a null op range; that is, "replace the op range with nothing".
						Given the mystery is solved, I might want to try this again, since local icO has greater optimization potential.
						The following should work:
	char icO	= I[ ixH-1 ];
						...but again, I might want to revisit the basis of ixH first, since I am so often terming (ixH-1).
*/


	if(		/*****	ƒsub NX0	*****/	tcª< 0	)		{ /* Multiple cubes annihilated.	*/	iCx=iCI;    	AvCUT2( iC+1,	iCx);	dBUGrackCALL(	0 );
	/*	mark element iC for deletion		*/																
		printf("\rCASE NX0:	xc(a)==%d	iCI..iC: %lld..%lld\n", xcª, iCI, iC );
		printf( lightning ); printf("\n!	CASE NX0 is not properly implemented, and it may have no ultimate use.  2026-09-05\n");	return;


		//get entire length of  cube # iC and  add it to the negative phase of cyclum 0 in cube iC +1
		if( iC != zC ){
			printf("\n%s case NX0 iC#%lld		in %s line %d \n", __FUNCTION__, iC, __FILE__, __LINE__ );
										cubeº = iC? (ui08*) SvPVbyte_nolen(	*(Aº+ iC-1 ) ):	nube;
										cubeⁿ =	cube;
										cube =	SvPVbyte(	sv = *(Aº+ ++iC ),	CS );
		/*	MxINIT;	*/	xcª =	zc=zcOf(	cube); 				AvCUT(	iC );					
													pq=cube+16;								O[ 0 ] =16;	I[0]=0;
			switch( cube[ 0 ] ){ SwCASE_IC2ABQ_init16p(	pq,	A[0],	B[0],	L[0], 		cube, pq,	O[ 1 ]	); }
														A[0] += *Edge( cubeⁿ ) - *Edge(	cubeº );
			u=0; icO=v=1;			ReICEuO( 0,	1 );
			ixM=0; izM=0; inM=ixH=1; 		goto _NX1;

		}else{
			printf("\n%s case NX0-Z iC#%lld		in %s line %d \n", __FUNCTION__, iC, __FILE__, __LINE__ );
			SvREFCNT_dec( *( Aº +zC ) );		zC=--AvFILLp( avICE);
			svΩ=*( Aº +zC );
			cubeΩ= SvPVbyte( svΩ, CSΩ );	zcΩ = zcOf(	cubeΩ );
			}
		}/*






*/
	else if(	/*****	ƒsub NX1	*****/	tcª< 8	)_NX1:	{ /* N cubes in, one cube out.	*/	iCx=iCI;		dBUGrackCALL(	1 );		
	//	if( xcª -ixº <1 || trace ){ trace=1;	printf( "\r	NX1 enter	%s line %d\n",  __FILE__, __LINE__ ); }
		cubeº = SvPVbyte_nolen( svI );																	dBUGmx( xcª+4, ocª, xcª );
		svΩ			=		sv;
	//	preΩ_xc		= oc	?	icO:	icO	-		icI;			/* limit pre mod range to last cube in the run		*/
		post_xc		=		izM		-		ixM;			/* post mod range covers the full run				*/
		xCS			=	CS+oCS-16;
		relΩ_c		=		tcª		-		zc;		//	alt:	relΩ_c		=		izM	-ixº	-		icO;
		rel_q		=	Oª[	inM	]	-	O[	ixH	];		/* rel. dif. in pre-to-post q for full cube run		*/
		CSΩ		=		xCS		+	rel_q;			/* cubeΩ consolidates "N" cubes				*/
		relΩ_q		=		CSΩ	-		CS;			/* rel. dif. in pre-to-post q for cube Ω			*/
		post_q		=	Oª[	inM	]	-	Oª[	ixM	];		/* length of mod q-data post-op.				*/
		hp_q		= 		xCS		-	O[	ixH	];		/* high passthrough q-bytes					*/
		lpΩ_q		=	O[	ixM	]-16;					/* low passthrough q-bytes					*/	dBUG_NX1

	//	relΩ_q=rel_q	+		oCS 	-		16;			/* relative difference in pre-to-post q for cube Ω		*/
	//	preΩ_q = inM>ocª?	O[	inM	]	-		oCS:	0;
	//	postΩ_q		=	Oª[	inM	]	-	O[	ixº	];
	//	hpΩ_q		=
	//		ocª< ixH	?		xCS		-	O[	ixH	]		/* high passthrough q-bytes						*/
	//				:		xCS		-	O[	ocª	];

	//	pre_q		=	O[	inM	]	-	O[	ixM	];		/* length of mod q-data pre-op.					*/

		/*	[iC+0]:	IN-SITU HIGHPASS REFLOW			(CASE NX1)									*/
		
		if(			relΩ_q >0 ){	/*	expand	*/					SvCUR_set(	svΩ, 	O[ ixM ]  	);	/* prevent copying obsolete data	*/
														cubeΩ =	SvGROW(	svΩ, 	CSΩ+1);
				if(	hp_q	)	{	ReFLOW_DX(	cube,	cubeΩ,	relΩ_q, hp_q,	CSΩ,	CS,				__LINE__ );	}
		}else if(		relΩ_q< 0 ){	/*	compact	*/			cubeΩ =	cube;				hpΩ_o =16 +O[ ixH ] -oCS;
				if(	hp_q	)	{	ReFLOW_AC(	cube,	cubeΩ,	relΩ_q, hp_q,	Oª[ ixH],	hpΩ_o,			__LINE__ );	}
		}else						/*	shunt	*/		cubeΩ =	cube;								dBUG_SvCUR( svΩ, CSΩ );
		cubeΩ[ CSΩ ]=0;											SvCUR_set(	svΩ, 	CSΩ );
		if( xcª == izM )							*Edge(	cubeΩ )=E[ izM ];

											pΩ = 16+cubeΩ;	
		if(		lpΩ_q	)	{		XLOAD( 	pΩ,	16,			lpΩ_q,	cubeº,	cubeΩ );				
							}	/*	^ crossload lowpass from cubeº (first) to cubeΩ (last)					*/

		/*	[iC+0]:	SPLICE KEYBYTE SECTION			(CASE NX1)									*/
		/*	double-crossover re-encoded keybytes with low passthrough from cubeº and high passthrough in-situ	*/
						lpXen	=	icI|( post_xc<< 3 );
		if(		relΩ_c ){
			if(	relΩ_c< 0){			bs = ( -relΩ_c ) << 3;	hipa = *( (ui64*) cube ) >>bs;	}
			else{					bs =   relΩ_c	<< 3;	hipa = *( (ui64*) cube )<< bs;	}
			switch(		lpXen	){	SwCASE_XXOVER_01W(	hipa, 					*( (ui64*) (K +ixº) ),		*( (ui64*) cubeº ),	*( (ui64*) cubeΩ )	) 	}
		}else{	//					^dbl-xover dbl-wye		^high passthrough, shifted	^endo inclusion src		^low passthrough	^dbl-wye output
			switch(		lpXen	){	SwCASE_XXOVER_01W(	*( (ui64*) cube ),			*( (ui64*) (K +ixº) ),		*( (ui64*) cubeº ),	*( (ui64*) cubeΩ )	) 	}
			}	//					^dbl-xover dbl-wye		^high passthrough			^endo inclusion src		^low passthrough	^dbl-wye output

		/*	[iC+0]:	PACK NEW Q-DATA				(CASE NX1)									*/
		if(		post_q	)	{				pΩ = cubeΩ +O[ ixM ];
									ICEPACK( pΩ, 	ixM, izM, inM,		cubeΩ );						
							}	/*	^re-pack modified q-data vectors [ ixM..inM ] in-situ					*/
	//	if( xcª -ixº <1 ||trace ){ trace=1;	printf( "\r	NX1 exit	%s line %d\n", __FILE__, __LINE__ ); }
		}/*		so.			







		*/
#define dBUG_ASSERT_relΩ_q_GTEQ_oCS	if( O[ ixΩ ] < oCS ){	cS=sprintf( aString, lightning ); cS+=sprintf( aString+CS, "\n!	impossible case for NX2L: ( O[ ix\xEA: %d]: %d ) < ( oCS: %lld )\n\n", ixΩ, O[ixΩ], oCS ); AvDBUG_PUSH( aString, cS );	}
	else if( 	/*****	ƒsub NX2x	*****/	tcª< 15	)		{ /* N cubes rebalance into two.	*/	iCx=iCI+1;	dBUGrackCALL(	2 );
		zcΩ =	tcª >>1;	ixΩ =	xcª-	zcΩ;
				izº = 	ixΩ -1;			
		zcº =	izº -ixº;							cubeΩ =	cube;										dBUGmx( xcª+4, izº, ixΩ );
		/*	do not shunt " cubeΩ = cube; " early on, because some of these cases will need to call "cubeΩ = SvGROW(...);"/	*/
		svΩ=sv;

/*NX2L*/	if(	/*****	ƒsub NX2L	*****/	izM< 	ixΩ )	{	/* mod range contained in left fragment.	*/
	//	if( xcª -ixº <1 || trace ){ trace=1;	printf( "\r	NX2L enter	%s line %d\n",  __FILE__, __LINE__ ); }
			/*	read up to fragment boundary (ixΩ) if cube iC hasn't been read that far						*/
			if(							u<	ixΩ ) 	{				if( RW[ v ] == null )	deIce_vKEI();
				if( ixM!=0xFF)	do	{		u=v++;		Oª[v] =Oª[u] +L[u];		/* nerf	*/	deIce_vKEI( u, v );	
								} while(	u<	ixΩ );
				else  		do	{		u=v++;	/*	Oª[v] =Oª[u] +Lx[u]; */	/*nothin'	*/	deIce_vKEI( u, v );	
								} while(	u<	ixΩ );	}
		/*	[iCI ]: 	RESIZE LOW CUBE 					(CASE NX2L )								*/	
			if(		CSI	<  Oª[ ixΩ ]	)	{					SvCUR_set(	svI,	 	O[ ixM ]  	);	/* prevent copying obsolete data	*/
					/*	 expand cubeº	*/			cubeº =		SvGROW(	svI,	 			Oª[ ixΩ]+1	);
			}else								cubeº =		SvPVbyte_nolen( svI );	cubeº[	Oª[ ixΩ] ]=0;	dBUG_SvCUR( svI, Oª[ixΩ] );
					/* set Edge of cubeº*/	*Edge(	cubeº )=E[ izº];	SvCUR_set(	svI,	/*	CSº = */	Oª[ ixΩ] );

		/*	[iCI ]: 	SPLICE LOW CUBEº KEYBYTE SECTION		(CASE NX2L)								*/
		/*	In NX2L only, I skip a heinous lot of ctrl logic by copying already-assembled K[ ixº..izº ] mod+hp keybytes	*/
			;				char			posthpº_xc = izº - ixM;
			if( icI >0){			lpXen =	icI |(	posthpº_xc<< 3 );
				switch(		lpXen ){	SwCASE_LPXOVER_01T(		*( (ui64*) (K +ixº) ),		*( (ui64*) cubeº )	)	}
			}else{	/*				^lowpass crossover tee		^post+highpass src   	^lowpass + tee out	*/
				switch(	posthpº_xc ){	SwCASE_LOWPASS_1I(		*( (ui64*)( K +ixº ) ), 	*( (ui64*) cubeº )	)	}
				}				/*	^lowpass inline assignment	^definitive src			^low passthrough	*/	

		/*	[iCI ]:	RE-ENCODE LOW CUBE MODS			(CASE NX2L)								*/
				post_q	=Oª[ inM ] -Oª[ ixM ];	pº=	cubeº +O[ ixM ];
			if(	post_q	)	{		ICEPACK( pº,	 	ixM, izM, inM,		cubeº );						
							}	/*	^re-pack vectors ixM..izM q-data to cubeº[ Oª[ ixM ]..Oª[ inM ]-1 ]		*/

		/*	[iCZ ]:	HIGH CUBE REFLOW and CROSSLOAD	(CASE NX2L )								*/
			if(			 O[	ixΩ ] >	oCS ){	/* rebalance shifts pre-q high-to-low; highpass may crossload down	*/
				relΩ_q	=O[	ixΩ ] -	oCS;											CSΩ = CS - relΩ_q;

			    if(			 O[	ixΩ ] >O[	ixH ] )	{	hpº_o=16+O[	ixH ] -oCS;
				hpº_q	=O[	ixΩ ] -O[	ixH ];	pº =	cubeº +	Oª[	ixH ];
									XLOAD(	pº,	hpº_o,	hpº_q,	cube,	cubeº	);
											}							hpΩ_q =	CSΩ-16;
			/*	Ω compaction	*/		ReFLOW_AC(	cube,	cubeΩ,	-relΩ_q,	hpΩ_q,	16,	16+relΩ_q,		__LINE__	);
			/* there is never highpass in pre-op low cube to crossload up		*/
			/* furthermore, high cube cannot expand in NX2L, it is all highpass	*/
			}else				{													CSΩ = CS;		dBUG_ASSERT_relΩ_q_GTEQ_oCS
								}							SvCUR_set(		svΩ,	CSΩ	);

		/*	[iCZ ]: 	UNSHIFT HIGH CUBE KEYBYTE SECTION	(CASE NX2L)								*/
			if(		oc<	I[ ixΩ ]	)	{	bs =( I[ ixΩ ] -oc )<< 3;	*( (ui64*) cubeΩ )>>= bs;
			}else if(	oc >I[ ixΩ ]	)	{	bs =( oc - I[ ixΩ ] )<< 3;	*( (ui64*) cubeΩ )<<= bs;
									}																dBUG_NX2L;
			}																						
/*NX2H*/else if(	/*	ƒsub NX2H  	*****/	ixM >=	ixΩ )	{	/* mod range contained in right fragment.	*/
	//	if( xcª -ixº <1 || trace ){ trace=1;	printf( "\r	NX2H enter	%s line %d\n",  __FILE__, __LINE__ ); }
			cubeº = SvPVbyte_nolen( svI );				*Edge(	cubeº ) =E[ izº	];	

			post_xc	=		izM		-		ixM;
			xCS		=	CS+oCS-16;
			hpΩ_q	=		xCS		-	O[	ixH	];
			CSΩ	=(	Oª[	inM	]	-	O[	ixΩ	]	)+16+hpΩ_q;
			relΩ_q	=		CSΩ	-		CS;
			relΩ_c	=		zcΩ		-		zc;
			lpΩ_c	=		ixM		-		ixΩ;
			lpΩ_q	=	O[	ixM	]	-	O[	ixΩ	];
			postΩ_q	=	Oª[	inM	]	-	Oª[	ixM	];	/* length of q data to be modified. 		only used in NX1, NX2L and NX2H	(where mod range is confined 	*/

											dBUG_NX2H
		/*	UPDATE HI-CUBE [ iC ]						(CASE NX2H)									*/
		/*	[iCZ ]:	IN-SITU HIGHPASS REFLOW			(CASE NX2H)									*/
			if(			relΩ_q >0) {	/*	expand	*/				SvCUR_set(	svΩ, 	O[ ixM ]  	);	/*	prevent copying obsolete data	*/
		//	if(			relΩ_q >0) {	/*	expand	*/				SvCUR_set(	svΩ, 	16  	);		/*	try this instead!	*/
														cubeΩ =	SvGROW(	svΩ, 	CSΩ+1);
									ReFLOW_DX(	cube,	cubeΩ,	relΩ_q, hpΩ_q,		CSΩ,	CS,		__LINE__ );
			}else if(		relΩ_q< 0) {	/*	compact	*/		cubeΩ =	cube;
									ReFLOW_AC(	cube,	cubeΩ,	relΩ_q, hpΩ_q,	16+Oª[ ixH]-O[ixΩ],	16+O[ ixH]-oCS,	__LINE__ );
			}else		{			/*	shunt	*/		cubeΩ =	cube;								dBUG_SvCUR( svΩ, CSΩ );
						} cubeΩ[ CSΩ ]=0;		pΩ 		=	cubeΩ+16; SvCUR_set(	svΩ, 	CSΩ );
											
#define dBUG_NX2H_ΩSw0	/*	cS=sprintf( aString, "\rNX2H \xEA SwCASE 0 lpXen: 0x%02X\n", lpXen ); AvDBUG_PUSH( aString, cS );	*/
#define dBUG_NX2H_ΩSw1	/*	cS=sprintf( aString, "\rNX2H \xEA SwCASE 1 lpXen: 0x%02X\n", lpXen ); AvDBUG_PUSH( aString, cS );	*/
#define dBUG_NX2H_ΩSw2	/*	cS=sprintf( aString, "\rNX2H \xEA SwCASE 2 lpXen: 0x%02X\n", lpXen); AvDBUG_PUSH( aString, cS );	*/
		/*	[ Ω ]: 	SPLICE KEYBYTE SECTION			(CASE NX2H)									*/
		/*	cross high half of modified key data (from K) with passthrough (from char * cubeº)					*/
						lpXen	=	lpΩ_c| ( post_xc<< 3 );
			if(		zc == icO	){	/*	no high passthrough;	izM is the new end			Edge changes -->	*/	dBUG_NX2H_ΩSw0								*Edge( cubeΩ )	= E[ izM ];
				switch(	lpXen	){	SwCASE_LPXOVER_01Y( *( (ui64*) ( K +ixΩ ) ),							*( (ui64*)(cubeº+I[ ixΩ])), *( (ui64*) cubeΩ )  )  }
			//						^lowpass xover wye	^high inclusion src								^low passthrough src	^ wye output
			}else if(	relΩ_c==0 ){	/*	high passthrough not shifted										*/	dBUG_NX2H_ΩSw1								*Edge( cubeΩ )	= *Edge( cube );
				switch(	lpXen	){	SwCASE_XXOVER_01W(	*( (ui64*) cube ),			*( (ui64*)( K +ixΩ ) ),	*( (ui64*)(cubeº+I[ ixΩ])), *( (ui64*) cubeΩ )  )  }
								/*	^dbl xover dbl wye		^high passthrough			^endo inclusion src		^low passthrough src	^double-wye output	*/
			}else{	/*	shift		*/																	dBUG_NX2H_ΩSw0								*Edge( cubeΩ )	= *Edge( cube );
				if(	relΩ_c >0	){	bs =   relΩ_c	<< 3;	hipa = *( (ui64*) cube )<< bs;	}
				else{				bs =	(-relΩ_c)	<< 3;	hipa = *( (ui64*) cube ) >>bs;	}
				switch(	lpXen	){	SwCASE_XXOVER_01W(	hipa,  					*( (ui64*)( K +ixΩ ) ),	*( (ui64*)(cubeº+I[ ixΩ])), *( (ui64*) cubeΩ )  )  }
			}					/*	^dbl xover dbl wye		^high passthrough, shifted	^endo inclusion src		^low passthrough src	^double-wye output	*/

		/*	[iCZ ]: 	CROSSLOAD LP & ENCODE MODS	(CASE NX2H)									*/
			if(	lpΩ_q	)	{		XLOAD(	pΩ,		O[ixΩ],	lpΩ_q,	cubeº,	cubeΩ	);
							}	/*	^crossload (lpΩ_q) low-pass bytes from *(cube+O[ ixΩ ]) to *pΩ			*/
			if(	postΩ_q	)	{		ICEPACK( pΩ, 	ixM, izM, inM,				cubeΩ	);
							}	/*	^re-pack modified q-data vectors ixΩ..izM to cubeΩ[ 16+lpΩ_q..16+lpΩ_q+postΩ_q-1 ] 	*/

		/*	UPDATE LOW CUBE [iCI ]					(CASE NX2H)									*/
									MOD_CUBE_I_AS_LPASS(	ixΩ );
		}
/*NX2M*/else		/*	ƒsub NX2M	*****/					{	/* mod range across both fragments.		*/
	//	if( xcª -ixº <1 || trace ){ trace=1;	printf( "\r	NX2M enter	%s line %d\n",  __FILE__, __LINE__ ); }
			cubeº = SvPVbyte_nolen( svI );			*Edge(	cubeº ) =E[ izº	];
			xCS		= oCS+CS-16;
		//	preΩ_xc	= 		icO		-(	I[	ixΩ	]-oc);
		//	preΩ_xc	= oc	?	icO:	icO	-		icI;	//		printf("\n NX2M pre\xEA_xc verification %s line %d\n", __FILE__, __LINE__ );
			postΩ_xc = 		izM		-		ixΩ;		//	relΩ_c	=		postΩ_xc	-	preΩ_xc;
			postΩ_q	=	Oª[	inM	]	-	Oª[	ixΩ	];	// from NX1:	relΩ_c	=		izM	-ixº	-		icO;
			hpΩ_c	=		zc		-		icO;			relΩ_c	=		zcΩ		-		zc;
			hpΩ_q	=		xCS		-	O[	ixH	];		/* high passthrough q-bytes	*/	
			CSΩ	= 16+ postΩ_q +hpΩ_q;					/* the one that works?  idk pls no hurt code monkey	*/
			relΩ_q	=		CSΩ	-		CS;
		//	preΩ_q	=	O[	ixH	]	-		oCS;
		//	relΩ_q	=		postΩ_q	-		preΩ_q;		/* alt. relΩ_q calc, dependent on preΩ_q			*/
									
		/*	[iCZ ]:	IN-SITU HIGH CUBE HIGHPASS REFLOW	(CASE NX2M)								*/
			if(			relΩ_q >0 ){	/*	expand	*/				SvCUR_set(	svΩ, 	O[ ixM ]  	);	/* prevent copying obsolete data	*/
														cubeΩ =	SvGROW(	svΩ, 	CSΩ+1);
									ReFLOW_DX(	cube,	cubeΩ,	relΩ_q, hpΩ_q, CSΩ,				CS,				__LINE__ );
			}else if(		relΩ_q< 0 ){	/*	compact	*/		cubeΩ =	cube;
									ReFLOW_AC(	cube,	cubeΩ,	relΩ_q, hpΩ_q, 16+Oª[ ixH]-Oª[ixΩ],	16+O[ ixH]-oCS,	__LINE__ );
			}else		{			/*	shunt	*/		cubeΩ =	cube;								dBUG_SvCUR( svΩ, CSΩ );
						}			cubeΩ[ CSΩ ]=0;				SvCUR_set(	svΩ, 	CSΩ );
			
		/*	[iCZ ]:	SPLICE KEYBYTE SECTION			(CASE NX2M)									*/
		/*			crossover endogenous data with high passthrough data, in-situ							*/
			if( hpΩ_c ){		enXhp =	postΩ_xc| ( hpΩ_c<< 3 );										/*	*Edge( cubeΩ ) = *Edge( cube ); 	Edge of [iC] unchanged	*/
				if(		relΩ_c ){	/*	can't use a pointer+index here; index may underrun pointer.	*/
					if(	relΩ_c< 0){	bs = ( -relΩ_c ) << 3;	hipa = *( (ui64*) cube ) >>bs;	}
					else{			bs =   relΩ_c	<< 3;	hipa = *( (ui64*) cube )<< bs;	}
					switch(	enXhp ){	SwCASE_LPXOVER_10Y( hipa,				 	*( (ui64*)( K +ixΩ ) ),	*( (ui64*) cubeΩ )  )  	}			
				}else{			/*	^lowpass crossover wye	 ^high passthrough, shifted	^low inclusion src		^wye output		*/	
					switch(	enXhp ){	SwCASE_LPXOVER_10Y( *( (ui64*) cube ),		 	*( (ui64*)( K +ixΩ ) ),	*( (ui64*) cubeΩ )  )  	}	
					}			/*	^lowpass crossover wye	 ^high passthrough			^low inclusion src		^wye output		*/	
			}else{	
				switch(	postΩ_xc ){	SwCASE_LOWPASS_1I(							*( (ui64*)( K +ixΩ ) ),	*( (ui64*) cubeΩ )	)	}*Edge( cubeΩ ) = E[ izM ];	/*	Edge changed			*/	
				}				/*	^lowpass inline assignment						^definitive src			^low passthrough	*/	
			if(		postΩ_q )	{			pΩ = cubeΩ+16;
									iCEpACK( pΩ,	ixΩ, izM, inM,		cubeΩ );
							}	/*	^re-pack modified q-data vectors ixΩ..izM to cubeΩ[ 16..16+postΩ_q-1 ]	*/									\

		/*	UPDATE LO-CUBE [ iCI ]						(CASE NX2M)									*/
									MOD_CUBE_I_AS_LPASSxMODS( 	ixΩ);							
			cubeΩ[ CSΩ	] = 0;																		dBUG_NX2M
			}
		}/*




*/
	else if( 	/*****	ƒsub NX3	*****/	tcª< 22	)		{ /* N cubes rebalance into three.	*/	iCx=iCI+1;	dBUGrackCALL(	3 );
	//	if( xcª -ixº <1 || trace ){ trace=1;	printf( "\r	NX3 enter	%s line %d\n",  __FILE__, __LINE__ ); }
		/*	*	*	*	*	*	*	*	*	*	*	*/	ncª	= tcª +1;
		/*	*	*	*	*	*	*	*	*	*/	zcΩ = (	ncª /3) -1;		/* 4..7  */
		/*	*	*	*	*	*	*/	ixΩ = xcª -	zcΩ;
		/*	*	*	*/	iz¹ =			ixΩ -1;		
		/*	*	*	*	*/	ncⁿ	=(	ixΩ -ixº ) >>1;
		zc¹ =				ncⁿ -1;	/* 4..7  */ /* not used!  seriously! not in NX3, NX4, 1x3, or 1x4! */
		/*	*/	izº =		iz¹  -	ncⁿ;		/* 4..7  */ /* only used in NX4 to set "*Edge(	cubeº ) =E[ izº	];".  */
		zcº =	izº - ixº;
		ix¹ = 	izº +1;
																									dBUG_NX3_XCª_SW
																									dBUGmx( xcª+4, ix¹, iz¹ );
	//	cS=sprintf( aString, "\n ix\xA7/iz\xA7, zc\xA7: %d/%d, %d	ix1/iz1, zc1: %d/%d, %d	ix\xEA/iz\xEA( xc\xA6), zc\xEA: %d/%d, %d\n\n", ixº,izº, zcº,  ix¹, iz¹, zc¹, ixΩ, xcª, zcΩ );	AvDBUG_PUSH( aString, cS );
	/*	read ahead to last fragment boundary if cursor (u) hasn't read that far	*/
		if(								u< ixΩ )	{					if( RW[ v ] == null )	deIce_vKEI();
			if( ixM!=0xFF)		do	{		u= v++;		Oª[v] =Oª[u] +L[u];					DeICE_vKEI( u, v );	
								} while(	u< ixΩ );
			else				do	{		u= v++;	/*	Oª[v] =Oª[u] +Lx[u];	*/			DeICE_vKEI( u, v );	
								} while(	u< ixΩ );	}
		cubeº = SvPVbyte_nolen( svI );						*Edge(	cubeº ) = E[ izº ];

		/*	CREATE:	MEDIAL CUBE [iC+1] 				(CASE NX3)								*/
		if( ixM >ix¹ ){ /* lowpass ix¹..ixM-1	*/	CS¹ = 16 +Oª[ ixΩ ] - O[ ix¹ ];
			sv¹		= newSVpvz(	0x6 |	CS¹	);														dBUG_SvCUR( sv¹, CS¹ );
			SvCUR_set(				sv¹,	CS¹	);
			cube¹  	= SvPVbyte_nolen(	sv¹	);	p¹  = cube¹ +16;											*Edge( cube¹ ) = E[ iz¹ ];
			;		post¹_q	=		Oª[	ixΩ ]	-	Oª[	ixM	];
			;		lp¹_c	=		ixM  	-		ix¹;
			;		lp¹_q	=	O[	ixM	]	-	O[	ix¹	];
			if(		lp¹_q )	{		XLOAD(	p¹,	O[	ix¹	], lp¹_q,	cubeº,	cube¹ );
							}	/*	^crossload (lp¹_q) low-pass bytes from *(cube+O[ ix¹ ] ) to *p¹			*/
			;							post¹_xc = iz¹ -ixM;
			;			lpXen=	lp¹_c| (	post¹_xc<< 3 );
			switch(		lpXen	){	SwCASE_LPXOVER_01Y( *( (ui64*) ( K +ix¹ ) ),							*( (ui64*)( cubeº+ I[ix¹] ) ),	*( (ui64*) cube¹ ) 	)  }
								/*	^lowpass xover wye	^high inclusion src								^low passthrough src		^ wye output		*/
			if(		post¹_q )	{		iCEPACK( p¹, 	ixM, iz¹, ixΩ,				cube¹ );
							}	/*	^re-pack modified q-data vectors ixM..iz¹ to cube¹[ 16..16+post¹_q-1 ]  	*/

		/*	[iC1 ]:	MEDIAL CUBES WILL NEVER CONTAIN BOTH LOWPASS & HIGHPASS, NOR JUST LOWPASS	*/
		/*			High and low passthrough never crossover when there are (3) or more output cubes.		*/
		/*			This is by architectural design, and it is true as long as:									*/
		/*				· 'X1 & 'X2 handle all cases where tcª< 14.										*/
		/*				· The RACK macro is consistently applied to reject leading unmodified cubes.			*/
		/*																						*/
		/*	NOTE:	Up to 2026-09-10, trailing unmodified cubes are not trimmed out of the cube run.			*/
		/*			ReICEuO and ReICEuOx are applied discriminatingly to avoid re-encoding unmodified vectors,	*/
		/*			but after the point of mark-in (MkIn), unmodified vectors are written-through indiscriminately.	*/
		/*			I have no plan to implement further stringency, because in my estimation:				*/
		/*																						*/
		/*				· The general currency of such architectural tradeoffs should be the "unit cube".		*/
		/*				· The real dead load of writing when no write is necessary is already eliminated.  		*/
		/*				· The remaining dead load should be somewhat avoidable at the application layer.		*/

		/*	[iC1 ]:	ƒsub NX3-xBx:	MEDIAL CUBE¹ IS LOWPASS & MODS (section B)						*/	ƒSUB¹_B
			if(	izM< ixΩ )	{		MOD_CUBE_Ω_AS_HIGHPASS();										ƒSUBΩ_E
			}else  			{		MOD_CUBE_Ω_AS_MODSxHPASS();									ƒSUBΩ_D
							}		MOD_CUBE_I_AS_LPASS(	ix¹ );										ƒSUBº_A;

		}else{ /* no lowpass */				CS¹ = 16 +Oª[ ixΩ ] - Oª[ ix¹ ];	//	printf("\n CS¹=16 +( O\xA6[ ix\xEA: %d ]: %d ) - ( O\xA6[ ix\xB9: %d ]: %d );\n\n", ixΩ, Oª[ixΩ], ix¹, Oª[ ix¹ ] );
			sv¹		= newSVpvz(	0x6 |	CS¹	);														dBUG_SvCUR( sv¹, CS¹ );
			SvCUR_set(				sv¹,	CS¹	);
			cube¹  	= SvPVbyte_nolen(	sv¹	);	p¹  = cube¹ +16;											*Edge( cube¹ ) = E[ iz¹ ];

		//	if( izM >=iz¹ )	/*   highpass	izM+1..iz¹	*/	assert( ixM<= ix¹ )	/*no lowpass					*/
		//	else			/*no highpass				*/	assert( ixM >ix¹ )	/*   lowpass	ix¹..ixM-1		*/
		/*	[iC1 ]:	ƒsub NX3-xDx:	MEDIAL CUBE¹ IS MODS & HIGHPASS (section E)   					*/	
			if( izM< iz¹)	{																			ƒSUB¹_D
				;	hp¹_c	=		ixΩ		-		ixH;
				;	pre¹_xc	=	I[	ixH	]-1	-		oc;		/*<	"	...up to but not including the 1st char of the 1st highpass vector ( O[ ixH ]-1 ), 	*/ 
				;	post¹_xc	=		izM		-		ix¹;		/*		from the 1st char of pre-op cube Ω ( oc ).	"							*/
				;	rel¹_c	= 		post¹_xc	-		pre¹_xc;
				;	hp¹_o	=16+O[	ixH	]	-		oCS;
				;	hp¹_q	=	O[	ixΩ	]	-	O[	ixH	];
				;	post¹_q	=	Oª[	inM	]	-	Oª[	ix¹	];
				;			enXhp=	post¹_xc	| (		hp¹_c<< 3 );
				if(	rel¹_c ){
				    if(	rel¹_c< 0){		bs = ( -rel¹_c )	<< 3;	hipa = *( (ui64*) cube ) >>bs;	}
				    else{				bs =   rel¹_c	<< 3;	hipa = *( (ui64*) cube )<< bs;	}
				    switch(		enXhp ){	SwCASE_LPXOVER_10Y( hipa,					*( (ui64*)( K +ix¹ ) ), 	*( (ui64*) cube¹ )  )  }
				}else{			/*	^lowpass crossover wye	^high passthrough, shifted	^low inclusion src		^wye output		*/
				    switch( 	enXhp ){	SwCASE_LPXOVER_10Y( *( (ui64*) cube ),		 	*( (ui64*)( K +ix¹ ) ), 	*( (ui64*) cube¹ )  )  }	
				    }				/*	^lowpass crossover wye	 ^high passthrough			^low inclusion src		^wye output		*/	

				if(	post¹_q )	{		iCEpACK( p¹, 	ix¹,	izM,	inM,					cube¹ );
							}	/*	^re-pack modified q-data vectors ix¹..izM to cube¹[ 16..16+post¹_q-1 ]  	*/
				if(	hp¹_q )	{		XLOAD(	p¹,	hp¹_o,		hp¹_q,	cube,	cube¹ );
							}	/*	^crossload (hp¹_q) high-pass bytes from *(cube+O[ ixH ] ) to *p¹			*/
				/* after XLOAD:	*/	MOD_CUBE_Ω_AS_HIGHPASS();										ƒSUBΩ_E

		/*	[iC1 ]:	ƒsub NX3c:	MEDIAL CUBE¹ IS ALL MODS 	(section C)   						*/
			}else{	switch( iz¹-ix¹ ){	SwCASE_LOWPASS_1I(							*( (ui64*)( K +ix¹ ) ), 	*( (ui64*) cube¹ )  )  }
								/*	^inline lowpass								^definitive src			^lowpass out		*/
				;	post¹_q	=	Oª[	ixΩ	]	-	Oª[	ix¹	];											
				if(	post¹_q )	{		iCEPACK( p¹, 		ix¹, iz¹, ixΩ,			cube¹ );
							}	/*	^re-pack modified q-data vectors ix¹..iz¹ to cube¹[ 16..16+post¹_q-1 ]  	*/	ƒSUB¹_C
				if( izM< ixΩ )	{		MOD_CUBE_Ω_AS_HIGHPASS();										ƒSUBΩ_E
				}else  		{		MOD_CUBE_Ω_AS_MODSxHPASS();									ƒSUBΩ_D
				}			}
	/*	UPDATE LO-CUBE [ iCI ]						(ƒsub NX3-Cxx)   								*/
			if( ixM >izº )	{			MOD_CUBE_I_AS_LPASS(		ix¹ );									ƒSUBº_A;
			}else 		{			MOD_CUBE_I_AS_LPASSxMODS(	ix¹ );									ƒSUBº_B
			}			}

		cube¹[ CS¹	] =0;		AvPOST( iCI, sv¹	); 														dBUG_NX3
															}/*






*/
	else if( 	/*****	ƒsub NX4/N	*****/	tcª< 255	)		{ /* One cube splits into four plus.	*/	iCx=iCI+1;	dBUGrackCALL(	4 );
	//	if( xcª -ixº <1 || trace ){ trace=1;	printf( "\r	NXN enter	%s line %d\n",  __FILE__, __LINE__ ); }
		int						nCª=(		tcª /7 )-3;													dBUGnCª
					endo_c	=	nCª *7;																	
					exo_c	=	tcª %7;
//		printf("\rCASE NX4:	xc(a)==%d	iCI..iC: %lld..%lld	oCS/CS: %d/%d\n", xcª, iCI, iC, oCS, CS);
//		if( iCx )	{
		if( ixº ) switch(	exo_c ){								/*	zcⁿ=6;	*/
	/* 6, 6; 5, 5 */	case 0:	zcº=5; zc¹=5; zc²=4; zcΩ=4;	ix¹=ixº+6;	iz¹=ixº+11;	ixⁿ=ixº+12;	izⁿ=ixº+18;	ix²=12+ixº+endo_c;	ixΩ=17+ixº+endo_c;	break;
	/* 6, 6; 6, 5 */	case 1:	zcº=5; zc¹=5; zc²=5; zcΩ=4;	ix¹=ixº+6;	iz¹=ixº+11;	ixⁿ=ixº+12;	izⁿ=ixº+18;	ix²=12+ixº+endo_c;	ixΩ=18+ixº+endo_c;	break;
	/* 6, 6; 6, 6 */	case 2:	zcº=5; zc¹=5; zc²=5; zcΩ=5;	ix¹=ixº+6;	iz¹=ixº+11;	ixⁿ=ixº+12;	izⁿ=ixº+18;	ix²=12+ixº+endo_c;	ixΩ=18+ixº+endo_c;	break;
	/* 7, 6; 6, 6 */	case 3:	zcº=6; zc¹=5; zc²=5; zcΩ=5;	ix¹=ixº+7;	iz¹=ixº+12;	ixⁿ=ixº+13;	izⁿ=ixº+19;	ix²=13+ixº+endo_c;	ixΩ=19+ixº+endo_c;	break;
	/* 7, 7; 6, 6 */	case 4:	zcº=6; zc¹=6; zc²=5; zcΩ=5;	ix¹=ixº+7;	iz¹=ixº+13;	ixⁿ=ixº+14;	izⁿ=ixº+20;	ix²=14+ixº+endo_c;	ixΩ=20+ixº+endo_c;	break;
	/* 7, 7; 7, 6 */	case 5:	zcº=6; zc¹=6; zc²=6; zcΩ=5;	ix¹=ixº+7;	iz¹=ixº+13;	ixⁿ=ixº+14;	izⁿ=ixº+20;	ix²=14+ixº+endo_c;	ixΩ=21+ixº+endo_c;	break;
	/* 7, 7; 7, 7 */	case 6:	zcº=6; zc¹=6; zc²=6; zcΩ=6;	ix¹=ixº+7;	iz¹=ixº+13;	ixⁿ=ixº+14;	izⁿ=ixº+20;	ix²=14+ixº+endo_c;	ixΩ=21+ixº+endo_c;	break;
		}else switch(	exo_c ){								/*	zcⁿ=6;	*/
	/* 6, 6; 5, 5 */	case 0:	zcº=5; zc¹=5; zc²=4; zcΩ=4;	ix¹=6;	iz¹=11;		ixⁿ=12;		izⁿ=18;		ix²=12+endo_c;	ixΩ=17+endo_c;	break;
	/* 6, 6; 6, 5 */	case 1:	zcº=5; zc¹=5; zc²=5; zcΩ=4;	ix¹=6;	iz¹=11;		ixⁿ=12;		izⁿ=18;		ix²=12+endo_c;	ixΩ=18+endo_c;	break;
	/* 6, 6; 6, 6 */	case 2:	zcº=5; zc¹=5; zc²=5; zcΩ=5;	ix¹=6;	iz¹=11;		ixⁿ=12;		izⁿ=18;		ix²=12+endo_c;	ixΩ=18+endo_c;	break;
	/* 7, 6; 6, 6 */	case 3:	zcº=6; zc¹=5; zc²=5; zcΩ=5;	ix¹=7;	iz¹=12;		ixⁿ=13;		izⁿ=19;		ix²=13+endo_c;	ixΩ=19+endo_c;	break;
	/* 7, 7; 6, 6 */	case 4:	zcº=6; zc¹=6; zc²=5; zcΩ=5;	ix¹=7;	iz¹=13;		ixⁿ=14;		izⁿ=20;		ix²=14+endo_c;	ixΩ=20+endo_c;	break;
	/* 7, 7; 7, 6 */	case 5:	zcº=6; zc¹=6; zc²=6; zcΩ=5;	ix¹=7;	iz¹=13;		ixⁿ=14;		izⁿ=20;		ix²=14+endo_c;	ixΩ=21+endo_c;	break;
	/* 7, 7; 7, 7 */	case 6:	zcº=6; zc¹=6; zc²=6; zcΩ=6;	ix¹=7;	iz¹=13;		ixⁿ=14;		izⁿ=20;		ix²=14+endo_c;	ixΩ=21+endo_c;	break;
			}									izº=ix¹-1;							iz² =	ixΩ-1;	dBUGmx( xcª+4, ix¹, iz² );



//		if( iCx ){	/*	const char	zcⁿ=6;	*/
//			if( ixº )	switch( exo_c )	{
//	/* 6, 6; 5, 5 */	case 0:	zcº=5; zc¹=5; zc²=4; zcΩ=4;	ix¹=ixº+6;	iz¹=ixº+11;		ixⁿ=iz¹+1;	izⁿ=ixº+18;	ix²=ixⁿ+endo_c;	ixΩ=17+ixº	+endo_c;	break;
//	/* 6, 6; 6, 5 */	case 1:	zcº=5; zc¹=5; zc²=5; zcΩ=4;	ix¹=ixº+6;	iz¹=ixº+11;		ixⁿ=iz¹+1;	izⁿ=ixº+18;	ix²=ixⁿ+endo_c;	ixΩ=izⁿ		+endo_c;	break;
//	/* 6, 6; 6, 6 */	case 2:	zcº=5; zc¹=5; zc²=5; zcΩ=5;	ix¹=ixº+6;	iz¹=ixº+11;		ixⁿ=iz¹+1;	izⁿ=ixº+18;	ix²=ixⁿ+endo_c;	ixΩ=izⁿ		+endo_c;	break;
//	/* 7, 6; 6, 6 */	case 3:	zcº=6; zc¹=5; zc²=5; zcΩ=5;	ix¹=ixº+7;	iz¹=ixº+12;		ixⁿ=iz¹+1;	izⁿ=ixº+19;	ix²=ixⁿ+endo_c;	ixΩ=izⁿ		+endo_c;	break;
//	/* 7, 7; 6, 6 */	case 4:	zcº=6; zc¹=6; zc²=5; zcΩ=5;	ix¹=ixº+7;	iz¹=ixº+13;		ixⁿ=iz¹+1;	izⁿ=ixº+20;	ix²=ixⁿ+endo_c;	ixΩ=izⁿ		+endo_c;	break;
//	/* 7, 7; 7, 6 */	case 5:	zcº=6; zc¹=6; zc²=6; zcΩ=5;	ix¹=ixº+7;	iz¹=ixº+13;		ixⁿ=iz¹+1;	izⁿ=ixº+20;	ix²=ixⁿ+endo_c;	ixΩ=21+ixº	+endo_c;	break;
//	/* 7, 7; 7, 7 */	case 6:	zcº=6; zc¹=6; zc²=6; zcΩ=6;	ix¹=ixº+7;	iz¹=ixº+13;		ixⁿ=iz¹+1;	izⁿ=ixº+20;	ix²=ixⁿ+endo_c;	ixΩ=21+ixº	+endo_c;	break;
//			}else	switch( exo_c )	{
//	/* 6, 6; 5, 5 */	case 0:	zcº=5; zc¹=5; zc²=4; zcΩ=4;	ix¹=6;	iz¹=11;			ixⁿ=12;	izⁿ=18;		ix²=12+endo_c;	ixΩ=17		+endo_c;	break;
//	/* 6, 6; 6, 5 */	case 1:	zcº=5; zc¹=5; zc²=5; zcΩ=4;	ix¹=6;	iz¹=11;			ixⁿ=12;	izⁿ=18;		ix²=12+endo_c;	ixΩ=18		+endo_c;	break;
//	/* 6, 6; 6, 6 */	case 2:	zcº=5; zc¹=5; zc²=5; zcΩ=5;	ix¹=6;	iz¹=11;			ixⁿ=12;	izⁿ=18;		ix²=12+endo_c;	ixΩ=18		+endo_c;	break;
//	/* 7, 6; 6, 6 */	case 3:	zcº=6; zc¹=5; zc²=5; zcΩ=5;	ix¹=7;	iz¹=12;			ixⁿ=13;	izⁿ=19;		ix²=13+endo_c;	ixΩ=19		+endo_c;	break;
//	/* 7, 7; 6, 6 */	case 4:	zcº=6; zc¹=6; zc²=5; zcΩ=5;	ix¹=7;	iz¹=13;			ixⁿ=14;	izⁿ=20;		ix²=14+endo_c;	ixΩ=20		+endo_c;	break;
//	/* 7, 7; 7, 6 */	case 5:	zcº=6; zc¹=6; zc²=6; zcΩ=5;	ix¹=7;	iz¹=13;			ixⁿ=14;	izⁿ=20;		ix²=14+endo_c;	ixΩ=21		+endo_c;	break;
//	/* 7, 7; 7, 7 */	case 6:	zcº=6; zc¹=6; zc²=6; zcΩ=6;	ix¹=7;	iz¹=13;			ixⁿ=14;	izⁿ=20;		ix²=14+endo_c;	ixΩ=21		+endo_c;	break;
//									}
//		}else{	
//			if( ixº )	switch( exo_c )	{
//	/* 6, 6; 5, 5 */	case 0:	zcº=5; zc¹=5; zc²=4; zcΩ=4;	ix¹=ixº+6;	iz¹= izⁿ= ixº+11;	ixⁿ=					ix²=iz¹+1;			ixΩ=17+ixº	+endo_c;	break;
//	/* 6, 6; 6, 5 */	case 1:	zcº=5; zc¹=5; zc²=5; zcΩ=4;	ix¹=ixº+6;	iz¹= izⁿ= ixº+11;	ixⁿ=					ix²=iz¹+1;			ixΩ=18+ixº	+endo_c;	break;
//	/* 6, 6; 6, 6 */	case 2:	zcº=5; zc¹=5; zc²=5; zcΩ=5;	ix¹=ixº+6;	iz¹= izⁿ= ixº+11;	ixⁿ=					ix²=iz¹+1;			ixΩ=18+ixº	+endo_c;	break;
//	/* 7, 6; 6, 6 */	case 3:	zcº=6; zc¹=5; zc²=5; zcΩ=5;	ix¹=ixº+7;	iz¹= izⁿ= ixº+12;	ixⁿ=					ix²=iz¹+1;			ixΩ=19+ixº	+endo_c;	break;
//	/* 7, 7; 6, 6 */	case 4:	zcº=6; zc¹=6; zc²=5; zcΩ=5;	ix¹=ixº+7;	iz¹= izⁿ= ixº+13;	ixⁿ=					ix²=iz¹+1;			ixΩ=20+ixº	+endo_c;	break;
//	/* 7, 7; 7, 6 */	case 5:	zcº=6; zc¹=6; zc²=6; zcΩ=5;	ix¹=ixº+7;	iz¹= izⁿ= ixº+13;	ixⁿ=					ix²=iz¹+1;			ixΩ=21+ixº	+endo_c;	break;
//	/* 7, 7; 7, 7 */	case 6:	zcº=6; zc¹=6; zc²=6; zcΩ=6;	ix¹=ixº+7;	iz¹= izⁿ= ixº+13;	ixⁿ=					ix²=iz¹+1;			ixΩ=21+ixº	+endo_c;	break;
//			}else	switch( exo_c )	{
//	/* 6, 6; 5, 5 */	case 0:	zcº=5; zc¹=5; zc²=4; zcΩ=4;	ix¹=6;	iz¹= izⁿ= 11;		ixⁿ=					ix²=12;			ixΩ=17;				break;
//	/* 6, 6; 6, 5 */	case 1:	zcº=5; zc¹=5; zc²=5; zcΩ=4;	ix¹=6;	iz¹= izⁿ= 11;		ixⁿ=					ix²=12;			ixΩ=18;				break;
//	/* 6, 6; 6, 6 */	case 2:	zcº=5; zc¹=5; zc²=5; zcΩ=5;	ix¹=6;	iz¹= izⁿ= 11;		ixⁿ=					ix²=12;			ixΩ=18;				break;
//	/* 7, 6; 6, 6 */	case 3:	zcº=6; zc¹=5; zc²=5; zcΩ=5;	ix¹=7;	iz¹= izⁿ= 12;		ixⁿ=					ix²=13;			ixΩ=19;				break;
//	/* 7, 7; 6, 6 */	case 4:	zcº=6; zc¹=6; zc²=5; zcΩ=5;	ix¹=7;	iz¹= izⁿ= 13;		ixⁿ=					ix²=14;			ixΩ=20;				break;
//	/* 7, 7; 7, 6 */	case 5:	zcº=6; zc¹=6; zc²=6; zcΩ=5;	ix¹=7;	iz¹= izⁿ= 13;		ixⁿ=					ix²=14;			ixΩ=21;				break;
//	/* 7, 7; 7, 7 */	case 6:	zcº=6; zc¹=6; zc²=6; zcΩ=6;	ix¹=7;	iz¹= izⁿ= 13;		ixⁿ=					ix²=14;			ixΩ=21;				break;
//			}						}		izº=	ix¹-1;												iz² =	ixΩ-1;	dBUGmx( xcª+4, ix¹, iz² );


	/*	read ahead to last fragment boundary if cursor (u) hasn't read that far	*/
		if(								u< ixΩ )	{				if( RW[ v ] == null )	deIce_vKEI();
		/*	if( ixM!=0xFF)		do	{		u= v++;		Oª[v] =Oª[u] +L[u];				DeICE_vKEI( u, v );	
								} while(	u< ixΩ );
			else	*/			do	{		u= v++;		Oª[v] =Oª[u] +L[u];
													O[v]	=O[u] +L[u];				DeICE_vKEI( u, v );	
								} while(	u< ixΩ );	}
		cubeº = SvPVbyte_nolen( svI );		*Edge(	cubeº ) =E[ izº	];


		/*	[iC+1]:	ƒsub NXN-xBxx:	NEW CUBE¹ AS LOWPASS x MODS								*/
		if( ixM >ix¹ ){						CS¹ = 16 +Oª[ ixⁿ ] - O[ ix¹ ];										ƒSUB¹_B	dBUG_SvCUR( sv¹, CS¹ );
			if( CS¹<16 || CS¹ >144 ){	printf( "\n(CS1: %lld) = 16 +( O\xA6[ ix\xFC: %d ]: %d ) - ( O\xA6[ ix1: %d]: %d );\n",	CS¹, ixⁿ, Oª[ ixⁿ ], ix¹, Oª[ ix¹ ] );	}
			sv¹		= newSVpvz(	0x6 |	CS¹	);								
			SvCUR_set(				sv¹,	CS¹	);
			cube¹  	= SvPVbyte_nolen(	sv¹	);	p¹  = cube¹ +16;											*Edge( cube¹ )= E[ iz¹ ];
			;		lp¹_c	=		ixM		-		ix¹;
			;		lp¹_q	=	O[	ixM	]	-	O[	ix¹	];
			if(		lp¹_q )	{		XLOAD(	p¹,	O[	ix¹	],	lp¹_q,	cubeº,	cube¹ );
							}	/*	^crossload (lp¹_q) low-pass bytes from *(cubeº+O[ ix¹ ] ) to *p¹			*/
											post¹_xc = iz¹ -ixM;
							lpXen=	lp¹_c| (	post¹_xc<< 3 );
					switch(	lpXen){	SwCASE_LPXOVER_01Y( *( (ui64*) ( K +ix¹ ) ),							*( (ui64*)(cubeº+I[ix¹] )),	*( (ui64*) cube¹ )  )  }
								/*	^lowpass xover wye	^high inclusion src								^low passthrough src	^ wye output			*/
			;		post¹_q	=	Oª[	ixⁿ	]	-	Oª[	ixM	];
			if(		post¹_q )	{		iCEpACK( p¹, 	ixM,	iz¹, 	ixⁿ,				cube¹ );
							}	/*	^re-pack modified q-data vectors ixM..iz¹ to cube¹[ 16..16+post¹_q-1 ]  	*/
									MOD_CUBE_I_AS_LPASS(	ix¹ );										ƒSUBº_A

		/*	[iC+1]:	ƒsub NXN-xCxx:	NEW CUBE¹ AS MODS 											*/
		}else{							CS¹ = 16 +Oª[ ixⁿ ] - Oª[	ix¹ ];
			if( CS¹<16 || CS¹ >144 ){	printf( "\n(CS1: %lld) = 16 +( O\xA6[ ix\xFC: %d ]: %d ) - ( O\xA6[ ix1: %d]: %d );\n",	CS¹, ixⁿ, Oª[ ixⁿ ], ix¹, Oª[ ix¹ ] );	}
																									ƒSUB¹_C;	dBUG_SvCUR( sv¹, CS¹ );
		//	if( xcª -ixº <1 ||trace){ trace=1;	printf( "\rNXN-xCxx	CS1: %lld\n", CS¹); }
			sv¹		= newSVpvz(	0x6 |	CS¹	);														
			SvCUR_set(				sv¹,	CS¹	);
			cube¹  	= SvPVbyte_nolen(	sv¹	);	p¹  = cube¹ +16;											*Edge( cube¹ ) = E[ iz¹ ];
					switch( iz¹-ix¹){	SwCASE_LOWPASS_1I(							*( (ui64*)( K +ix¹ ) ),	*( (ui64*) cube¹ )  )  }
								/*	^inline lowpass								^definitive src			^lowpass out		*/
			;		post¹_q	=	Oª[	ixⁿ	]	 -	Oª[	ix¹	];
			if(		post¹_q )	{		iCEpACK( p¹, 	ix¹,	iz¹, 	ixⁿ,				cube¹ );
							}	/*	^re-pack modified q-data vectors ix¹..iz¹ to cube¹[ 16..16+post¹_q-1 ]  	*/

			if( ixM==ix¹  )		{		MOD_CUBE_I_AS_LPASS(		ix¹ );									ƒSUBº_A
			}else 			{		MOD_CUBE_I_AS_LPASSxMODS(	ix¹ );									ƒSUBº_B
			}				}
		cube¹[ CS¹	] = 0;			AvPOST( iCI, sv¹ );													


		/*	[iC+1]:	ƒsub NXN-xxDx: 	NEW CUBE² AS MODS x HIGHPASS								*/
		if( izM< iz² ){																					ƒSUB²_D;
			;		hp²_c	=		ixΩ   	-		ixH;
			;		pre²_xc	=	I[	ixH	]-1	-		oc;		/*<	"	...up to but not including the 1st char of the 1st highpass vector ( O[ ixH ]-1 ), 	*/ 
			;		post²_xc	=		izM		-		ix²;
			;		rel²_c	= 		post²_xc	-		pre²_xc;
			;		hp²_o	=16+O[	ixH	]	-		oCS;
			;		hp²_q	=	O[	ixΩ	]	-	O[	ixH	];
										CS² =16+	hp²_q + Oª[ inM ] -Oª[ ix² ];
			if( CS²<16 || CS² >144 ){	printf( "\n(CS\xB2: %lld) = 16 +( hp\xB2_q: %d ) +( O\xA6[ ix\xEA: %d ]: %d ) - ( O\xA6[ ix\xB2: %d]: %d );\n",
											CS²,			hp²_q,			ixΩ, O[ ixΩ ],			ix², O[ ix² ] ); }

			sv²		= newSVpvz(	0x6 |	CS²	);														dBUG_SvCUR( sv², CS² );
			SvCUR_set(				sv²,	CS²	);	/*2026-09-24: differentiated xxDx CS² calc from xxCx	*/
			cube²  	= SvPVbyte_nolen(	sv²	);	p²  = cube² +16;

			;				enXhp=	post²_xc	| (		hp²_c<< 3 );
			if(		rel²_c ){
			    if( 	rel²_c< 0){		bs = ( -rel²_c )	<< 3;	hipa = *( (ui64*) cube ) >>bs;	}
			    else{					bs =   rel²_c	<< 3;	hipa = *( (ui64*) cube )<< bs;	}
			    switch(			enXhp ){	SwCASE_LPXOVER_10Y( hipa,					*( (ui64*)( K +ix² ) ),	*( (ui64*) cube² )  )  }
			}else{				/*	^lowpass crossover wye	^high passthrough, shifted	^low inclusion src		^wye output		*/
			    switch(			enXhp ){	SwCASE_LPXOVER_10Y( *( (ui64*) cube ),		 	*( (ui64*)( K +ix² ) ),	*( (ui64*) cube² )  )  }	
			    }					/*	^lowpass crossover wye	 ^high passthrough			^low inclusion src		^wye output		*/	

			;		post²_q	=	Oª[	inM	]	-	Oª[	ix²	];
			if(		post²_q )	{		iCEpACK( p², 	ix²,	izM,	inM,				cube²	);
							}	/*	^re-pack modified q-data vectors ix²..izM to cube²[ 16..16+post²_q-1 ]  	*/

			if(		hp²_q )	{		XLOAD(	p²,	hp²_o,	hp²_q,	cube,	cube²	);
							}	/*	^crossload (hp²_q) high-pass bytes from *(cube+O[ ixH ] ) to *p²			*/
			/* only after XLOAD:	*/	MOD_CUBE_Ω_AS_HIGHPASS();										ƒSUBΩ_E;

		/*	[iC+1]:	ƒsub NX4-xxCx: 	NEW CUBE² AS MODS											*/
		}else{							CS² = 16 +Oª[ ixΩ ] - Oª[ ix² ];									ƒSUB²_C;	dBUG_SvCUR( sv², CS² );
			if( CS²<16 || CS² >144 ){	printf( "\n(CS\xB2: %lld) = 16 +( O\xA6[ ix\xEA: %d ]: %d ) - ( O\xA6[ ix\xB2: %d]: %d );\n",
									CS²,					ixΩ, Oª[ ixΩ ], 		ix², Oª[ ix² ] );	}
		//	if( xcª -ixº <1 ||trace){ trace=1;	printf( "\rNXN-xxCx	CS2: %lld\n", CS²); }						
			sv²		= newSVpvz(	0x6 |	CS²	);								
			SvCUR_set(				sv²,	CS²	);
			cube²  	= SvPVbyte_nolen(	sv²	);	p²  = cube² +16;

			;		switch( iz²-ix²){	SwCASE_LOWPASS_1I(							*( (ui64*)( K +ix² ) ), 	*( (ui64*) cube² )  )  }
								/*	^inline lowpass								^definitive src			^lowpass out		*/
			;		post²_q	=	Oª[	ixH	]	-	Oª[	ix²	];
			if(		post²_q )	{		iCEpACK( p², 	ix²,	iz², ixΩ,	 			cube²	);
							}	/*	^re-pack modified q-data vectors ix²..iz² to cube²[ 16..16+post²_q-1 ]  	*/
			if(	izM< ixΩ)	{		MOD_CUBE_Ω_AS_HIGHPASS();										ƒSUBΩ_E;
			}else	  		{		MOD_CUBE_Ω_AS_MODSxHPASS();									ƒSUBΩ_D;
			}				}																		*Edge( cube² ) = E[ iz² ];

		/*	[iC+X]:	ƒsub NXN-xxAxx:	NEW CUBEⁿ AS MODS 											*/
		if( nCª){		
		  do	{		_ixⁿ = ixⁿ+7;			CSⁿ = 16 +Oª[ _ixⁿ ] - Oª[ ixⁿ ];
			if( CSⁿ<16 || CSⁿ >144 ){	printf( "\n(CS\xFC: %lld) = 16 +( O\xA6[ _ix\xFC: %d ]: %d ) - ( O\xA6[ ix\xFC: %d]: %d );\n",
										CS¹,					_ixⁿ, Oª[ _ixⁿ ], 		ixⁿ, Oª[ ixⁿ ] );	}
																									dBUG_SvCUR( svⁿ, CSⁿ );	//"CS\xFC"
			svⁿ		= newSVpvz(	0x6 |	CSⁿ	);														
			SvCUR_set(				svⁿ,	CSⁿ	);
			cubeⁿ  	= SvPVbyte_nolen(	svⁿ	);	pⁿ  = cubeⁿ +16;											*Edge( cubeⁿ )= E[ izⁿ ];
									*( (ui64*) cubeⁿ ) = *( (ui64*)( K +ixⁿ ) ) &0x00FFFFFFFFFFFFFF;
								/*	^inline lowpass (we're just gonna hardcode this one since it's constant)	*/
					postⁿ_q	=		Oª[ _ixⁿ ] - Oª[	ixⁿ	];
			if(		postⁿ_q )	{		iCEpACK( pⁿ,	ixⁿ, izⁿ, _ixⁿ, cubeⁿ );
							}	/*	^re-pack modified q-data vectors ixⁿ..izⁿ to cubeⁿ[ 16..16+postⁿ_q-1 ]  	*/
			ixⁿ+=7;	izⁿ+=7;
			cubeⁿ[	CSⁿ	] = 0;		AvPOST( iCI, svⁿ );
			} while( --nCª );
			}

		cube²[		CS²	] = 0;		AvPOST( iCI, sv² );													dBUG_NX4;
																}/*



*/
	else	{	cS = 	sprintf(	aString,		lightning );
			cS +=	sprintf(	aString +cS,	"\n	%s: ( tc\xA6: %d) overflows vector map!  Cannot commit changes!\n\n", __FUNCTION__, tcª );
			AvDBUG_PUSH(	aString, cS );
			return;
		}
//	if( xcª -ixº <1 ||trace){ trace=1;	printf( "\r	%s() exit, but first, AvCUT2( %lld, %lld )...	%s line %d\n", __FUNCTION__, iC, iCx, __FILE__, __LINE__ ); }
																			AvCUT2( iC,	iCx );		dBUGmx( xcª+4, ix¹, iz¹ );

	}

/* **	***	***	MEXICAN FIESTA	***	***	***	***	*** 	***	**/