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

/*	NOTE:  THE SUBTLE NUANCE OF "inM" VS. "ixH"
		· izM is the last vector in the modification range.
		· inM is the upper boundary of the modification range (izM+1).
		· ixH is the startting vector of the highpass (unmodified trailing) range.

	As such, inM is always izM+1, and since the modification range always leads into the unmodified high-passthrough range,
	inM and ixH are [nearly] always equal.

	However, while ixH and inM are nearly always equal, izM and inM can be diminished if the ending vector is deleted outright.
	This delete condition is the only reason the mod/highpass boundary is treated with separate variables in the pre/post contexts.
	As of 2026-08-06, there are only two setters developed beyond alpha, and neither of them bring rise to this.
	—	however, I do anticipate that [un]sweep() and the _vec...() series of methods do fundamentally require it,
		especially to support self-healing of the higher level prefix-sum structure to be encapsulated by this base class.

		· All  "pre" calculations	must use ixH-1	as the ending index.
		· All "post" calculations	must use izM  	as the ending index.
	
	For example, pre_c and post_c are almost always calcuated together, for example:
		pre_c	= ixM..ixH-1;	// "up to but not including the first highpass cycle"
							// —versus—
		post_c	= ixM..izM;	// "up to and including the last modified cycle",
							
	—	which almost always describe the same cycle.  As long as we treat pre- and post- separately this way,
		deletions will work.
	*/
/*	NOTE:  ON "PERISTALSIS" vs "COMPACTION / EXPANSION":
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
#include	"_sv_commit_1x.h"
#include	"_AvSEQ.h"
#include	"SwCASE.h"	
#include	"access_extern.h"

void _sv_commit_1x( ){	//printf("\n_sv_commit_1x()\n");
//	if( xcª -ixº <1 ||trace){ trace=1;	printf( "\r	%s() enter	%s line %d\n", __FUNCTION__, __FILE__, __LINE__ ); }
	SV/* *sv, */	*sv0,		*sv¹,		*svⁿ,		*sv²;	/*	svΩ [global]	*/
	STRLEN		CSº, 		CS¹,			CSⁿ,		CS²;	/*	CSΩ	[global]	*/			
	si64			endo_C;								
	ui64		head, body, tail, hipa, iCx;
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
			pre_q,																/*	q-data length sum			specs		the pre-op  mod. cycla		in	char *	cube				*/
			post_q,	postº_q,		post¹_q,		postⁿ_q,		post²_q,		postΩ_q,		/*	q-data length sum			measures	the post-op mod. cycla		in	char *	cube				*/
					cubeº_q,		tota1_q,		totaX_q,		totaY_q,		totaZ_q,
			hp_q,	hpº_q,		hp¹_q,		hpⁿ_y,		hp²_q,		hpΩ_q,		/*	q-data length				defines		the "high pass" range	 	in	char *	cube				*/
								lp¹_q,		lpⁿ_q,		lp²_q,		lpΩ_q;		/*	q-data length				defines		the "low pass" range	 	in	char *	cube				*/
	short	hp_i,				hp¹_i,		hpⁿ_i,		hp²_i,		hpΩ_i,		tcª =xcª -ixº, ncª;
	char 			zcº,			zc¹,			zcⁿ,	ncⁿ,		zc²,
			post_xc,	postº_xc, 	post¹_xc, 	postⁿ_xc, 	post²_xc, 	postΩ_xc,	/*	cycla count	(zero-based )	defines		the post-op mod. range		in	char *	cube				*/
			post_c,	postº_c,		post¹_c,		postⁿ_c,		post²_c,		postΩ_c,		/*	cycla count				defines		the post-op mod. range		in	char *	cube				*/
			pre_c,	preº_c,		pre¹_c,		preⁿ_c,		pre²_c,		preΩ_c,		/*	cycla count				measures	the pre-op mod. range		in	char *	cube				*/
			pre_xc,	preº_xc,		pre¹_xc,		preⁿ_xc,		pre²_xc,		preΩ_xc,		/*	cycla count	(zero-based )	measures	the pre-op mod. range		in	char *	cube				*/
								lp¹_c,		lpⁿ_c,		lp²_c,		lpΩ_c,		/*	cycla count				defines		the "low pass" range		in	char *	cube				*/
			hp_c,				hp¹_c,		hpⁿ_c,		hp²_c,		hpΩ_c,		/*	cycla count				defines		the "high pass" range		in	char *	cube				*/
								pre¹_q,								preΩ_q,
			rel_q,/*	relº_q,	*/	rel¹_q,	/*	relⁿ_q,		rel²_q,		relΩ_q,	*/	/*	q-data length difference		compares	pre & post op q-data totals	in	matrix { A[], B[], E[], L[] }	*/
			rel_c, /*	relº_c,	*/	rel¹_c,		relⁿ_c,		rel²_c,		relΩ_c;		/*	cycla count difference		compares	pre & post op cyclum counts	in	matrix { A[], B[], E[], L[] }	*/
#ifndef ReBAL_ENABLE
	assert( ixº==0 );
//	__builtin_assume( ixº == 0 );		
//	__builtin_assume( zcº == izº );
#endif

#ifdef DEBUG_SvCOMMIT_L1	// ƒsub audit (brief)
	subcase=0;
	av_push( avDBUG, &PL_sv_undef );	avdbuginx_dmarkcase=AvFILLp( avDBUG );	//reserve a point in the debug output for dBUG1X3 messages
#endif

	char icI	= I[ ixM	];

//	char	icO	= I[ ixH-1	];	// that'll work, and
//	char icO	= I[ izM	];	// that won't; because izM can be less than ixH-1 if _sv_commit_?x() is passed a null mod range (ablative). 


	if(		/*****	ƒsub 1X0   	*****/	tcª< 0	)		{ /* One cube is annihilated.					*/	dBUGrackCALL(	0 );
	/*	mark element iC for deletion		*/																dBUGmx( xcª+4, ocª, ocª );
		if( xcª -ixº <1 ||trace){ trace=1;printf( "\r	1X0 enter	%s line %d\n",  __FILE__, __LINE__ ); }
		//get entire length of  cube # iC and  add it to the negative phase of cyclum 0 in cube iC +1
		if( iC != zC ){
			printf("\n%s case 1X0 iC#%lld		in %s line %d \n", __FUNCTION__, iC, __FILE__, __LINE__ );
			if( iC!=0)						cubeΩ =	SvPVbyte_nolen(	*(Aº+ iC-1 ) );
			else							cubeΩ =	nube;
			;							cubeⁿ =	cube;
			;							cube =	SvPVbyte(	sv = *(Aº+ ++iC ),	CS );
		/*	MxINIT;	*/	xcª =	zc=zcOf(	cube); 				AvCUT(	iC );					
			;										pq=cube+16;						O[ 0 ] =16;	I[0]=0;
			switch( cube[ 0 ] ){ SwCASE_IC2ABQ_init16p(	pq,	A[0],	B[0],	L[0],	cube, pq,	O[ 1 ]		); }
			;											A[0] += *Edge( cubeⁿ ) - *Edge( cubeΩ );
			u=0; icO=v=1;					ReICEuO( 0,	1 );
			ixM=0; izM=0; inM=ixH=1; 		goto _1X1;

		}else{
			printf("\n%s case 1X0-Z iC#%lld		in %s line %d \n", __FUNCTION__, iC, __FILE__, __LINE__ );
			SvREFCNT_dec( *( Aº +zC ) );		zC=--AvFILLp( avICE);
			svΩ=*( Aº +zC );
			cubeΩ= SvPVbyte( svΩ, CSΩ );	zcΩ = zcOf(	cubeΩ );
			}

		}/*






*/
	else if(	/*****	ƒsub 1X1   	*****/	tcª< 8	)		{ /* One cube in, one cube out.				*/	dBUGrackCALL(	1 );
	//	if( xcª -ixº <1 ||trace){ trace=1;printf( "\r	1X1 enter	%s line %d\n",  __FILE__, __LINE__ ); }
		svΩ			=		sv;																		dBUGmx( xcª+4, ocª, ocª );
		zcΩ			=		tcª;																		_1X1:
		post_xc		=		izM		-		ixM;		/* post-op endogenous cycla	(zero-based—	it is used as a vector.)	*/
	//	pre_xc		= oc	||	icI==-1	?	icO:	icO	-icI;	/* pre mod range limited to last cube in the run		*/
		pre_xc		=		icO		-		icI;
		rel_c		=		post_xc	-		pre_xc;	
	//	rel_c		=		xcª		-		xc;		/* pre-to-post relative difference								*/
		hp_q		=		CS		-	O[	ixH	];	/* high passthrough q-bytes	*/
		hp_c		=		zc		-		icO;		/* high passthrough cycla	*/						dBUG_1X1
		rel_q		=	Oª[	inM	]	-	O[	ixH	];	/* relative difference in q pre-to-post op	only used in 1X1 and 1X2L		(where highpass in low cube shifts) */
		post_q		=	Oª[	inM	]	-	Oª[	ixM	];	/* length of q data to be modified. 		only used in 1X1, 1X2L and 1X2H	(where mod range is confined 	*/

		if( hp_c==0 ){	 *Edge( cube )=E[ izM ];	}


/*######	UPDATE ORIGINAL CUBE [iC]	######		(ƒsub 1X1)									*/
		/*	[iC ]:		OFFSET HIGH PASSTHROUGH VIA  IN-SITU PERISTALSIS	(SHIFT THE DAMN DATA)		*/
		if(				rel_q >0 )	{	/*	expand	*/				SvCUR_set(	svΩ, 	O[ ixM ]  	);	/* prevent copying obsolete data	*/
			CSΩ = CS +	rel_q;							cubeΩ =	SvGROW(	svΩ, 	CSΩ+1);
									ReFLOW_DX(	cube,	cubeΩ,	rel_q, hp_q,	CSΩ,	CS,		__LINE__ );	dBUG_SvCUR( svΩ, CSΩ );
									cubeΩ[ CSΩ ]=0;				SvCUR_set(	svΩ, 	CSΩ );
		}else if(			rel_q< 0 )	{	/*	compact	*/		
			CSΩ = CS +	rel_q;							cubeΩ =	cube;
									ReFLOW_AC(	cube,	cubeΩ,	rel_q, hp_q,	Oª[ ixH],	O[ ixH],	__LINE__);	dBUG_SvCUR( svΩ, CSΩ );
									cubeΩ[ CSΩ ]=0;				SvCUR_set(	svΩ, 	CSΩ );
		}else			{			/*	shunt	*/
			CSΩ= CS;									cubeΩ =	cube;
						}

		/*	[iC ]:		SPLICE KEYBYTE SECTION			(ƒsub 1X1)									*/
		/*			double-crossover of endogenous data with high and low passthrough data, in-situ			*/
						lpXen	=	icI |( post_xc<< 3 );
		if(		rel_c ){
			if(	rel_c< 0){				bs = ( -rel_c )	<< 3;	hipa = *( (ui64*) cube ) >>bs;	}
			else{					bs =   rel_c	<< 3;	hipa = *( (ui64*) cube )<< bs;	}
			switch(		lpXen	){	SwCASE_XXOVER_01K(	hipa, 					*( (ui64*) (K +ixº) ),		*( (ui64*) cubeΩ )	) 	}
		}else{	//					^dbl-xover dbl-tee		^high passthrough, shifted	^endo inclusion src		^low passthrough / tee output
			switch(		lpXen	){	SwCASE_XXOVER_01T(							*( (ui64*) (K +ixº) ),		*( (ui64*) cubeΩ )	)	}
			}	// displacement		^double crossover tee							^endo inclusion src		^exo passthrough / tee output

		/*	[iC ]:		PACK NEW Q-DATA				(ƒsub 1X1)									*/
		if(		post_q	)	{				pΩ = cubeΩ +16 +O[ ixM ] -oCS;
									ICEPACK( pΩ, 	ixM, izM, inM,		cubeΩ );
							}	/*	^re-pack modified q-data vectors [ ixM..inM ] in-situ					*/	
	//	if( xcª -ixº <1 ||trace){ trace=1;	printf( "\r	1X1 exit	%s line %d\n", __FILE__, __LINE__ ); }
		}/*		so.







*/
	else if( 	/*****	ƒsub 1X2   	*****/	tcª< 14	)		{ /* One cube splits in two.					*/	dBUGrackCALL(	2 );
		zcΩ =	tcª >>1;	ixΩ =	xcª-	zcΩ;
				izº = 	ixΩ -1;			
		zcº =	izº -ixº;																				dBUGmx( xcª+4, ocª, ixΩ );

		/*	retain char * pointer and char * length of pre-op cube iC for final step.  "SvGROW" may reallocate.		*/
		cubeº	= cube;
		sv0		= *(Aº +iC );

		if(		/*	ƒsub 1X2L  	*/	izM< 	ixΩ )	{	/* mod range contained in left fragment.		*/
			/*	read up to fragment boundary (ixΩ) if cube iC hasn't been read that far						*/
			if(							u<	ixΩ )	{					if( RW[ v ] == null )	deIce_vKEI();
				if( ixM!=0xFF)	do	{		u=v++;		Oª[v] =Oª[u] +L[u];		/* nerf	*/	deIce_vKEI( u, v );	
								} while(	u<	ixΩ );
				else  		do	{		u=v++;	/*	Oª[v] =Oª[u] +Lx[u]; */	/*nothin'	*/	deIce_vKEI( u, v );	
								} while(	u<	ixΩ );	}

			post_xc	=		izM		-		ixM; 	/*	post_xc is zero-based—	it is used as a bitvector.		*/
		/*	post_c	=		inM		-		ixM; *.	/*	post_c is one-based—	it is used in arithmetic.		*/
		//	pre_xc	=		icO		-		icI;
			pre_xc	= oc	?	icO:	icO	-		icI;		/* limit pre mod range to last cube in the run		*/
			rel_c	=		post_xc	-		pre_xc;
			rel_q	=	Oª[	inM	]	-	O[	ixH	];	/* relative difference in q pre-to-post op	only used in 1X1 and 1X2L		(where highpass in low cube shifts) */
			post_q	=	Oª[	inM	]	-	Oª[	ixM	];	/* length of q data to be modified. 		only used in 1X1, 1X2L and 1X2H	(where mod range is confined 	*/
			hpº_q	=	Oª[ 	ixΩ	]	-	Oª[ 	ixH	];
/*######	CREATE HIGH CUBE [iC+1]:	SV SETUP		(ƒsub 1X2L)									*/	{	
									NEW_CUBE_Ω_AS_HIGHPASS();
			*Edge( cubeº ) =E[	izº	];					/* set Edge of low cube while we're at it			*/
			AvPOST( iC, svΩ );							/* defer inserting the new element to (AV*) avICE	*/

/*######	[iC+0]:	SPLICE KEYBYTE SECTION			(ƒsub 1X2L)									*/
		/*	crossover modified key data (as uquad* K ) with unaltered leading / trailing in-situ    					*/
							lpXen =	icI |( post_xc<< 3 );
			if(		rel_c ){ //	shift
/*shift up	*/	if(	rel_c >0){			bs =   rel_c	<< 3;	hipa = *( (ui64*) cubeº )<< bs; }
/*shift down	*/	else{				bs = ( -rel_c )	<< 3;	hipa = *( (ui64*) cubeº ) >>bs; }
				switch(		lpXen ){	SwCASE_XXOVER_01K(	hipa,  					*( (ui64*) (K +ixº) ),		*( (ui64*) cubeº )	) 	}
			}else{	//		no shift	^dbl crossover dbl tee	^high passthrough, shifted	^endo inclusion src		^low passthrough + tee output
				switch(		lpXen ){	SwCASE_XXOVER_01T(							*( (ui64*) (K +ixº) ),		*( (ui64*) cubeº )	)	}
				}	//				^double crossover tee							^endo inclusion src		^exo passthrough + tee output
		/*	trim everything off the low cube that went to the high cube.					*/
			switch(		zcº	){		SwCASE_LOWPASS_1IS(	*( (ui64*) cubeº )	);		}


		/*	[iC+0]:	IN-SITU Q-DATA SHIFT				(ƒsub 1X2L )									*/
			if(		rel_q >0 )	{							SvCUR_set(	sv0, 	O[ ixM ]  	);			/* prevent copying obsolete data	*/
			/*		expand	*/					cubeº =	SvGROW(	sv0, 	Oª[ ixΩ]+1);
							ReFLOW_DX(	cube,	cubeº,	rel_q, hpº_q,	Oª[ ixΩ],	O[ ixΩ],					__LINE__ );
			}else if(	rel_q< 0 )	{
			/*		compact	*/					cubeº =	cube;
							ReFLOW_AC(	cube,	cubeº,	rel_q, hpº_q,	Oª[ ixH],	O[ ixH],					__LINE__ );
			}else			{
			/*		bypass	*/					cubeº =	cube;										dBUG_SvCUR( sv0, Oª[ixΩ] );
							} cubeº[ Oª[ixΩ] ]=0;			SvCUR_set(	sv0, 	Oª[ixΩ] );

		/*	[iC+0]:  RE-PACK MOD Q-DATA				(ƒsub 1X2L)									*/
			if(	post_q	)	{				pº = cubeº +O[ ixM ];
									ICEPACK( pº, 	ixM, izM, inM,		cubeº );
							}	/*	^re-pack modified q-data vectors ixM..izº to cubeº[ O[ ixM ]..Oª[ ixΩ ]-1 ] */ }	dBUG_1X2L
			}
		else if(	/*	ƒsub 1X2H  	*/	ixM >=	ixΩ )	{	/* mod range contained in right fragment.		*/
			post_q	=	Oª[	inM	]	-	Oª[	ixM	];	/* length of q data to be modified. 		only used in 1X1, 1X2L and 1X2H	(where mod range is confined 	*/
			post_xc	=		izM		-		ixM;
		/*	post_c	=		inM		-		ixM;		*/
			pre_xc	=		icO		-		icI;
			rel_c	=		post_xc	-		pre_xc;
			relΩ_c	=		rel_c	-	I[	ixΩ ];

			cubeº_q	=	O[	ixΩ	]	-		16;		// only used once
			lpΩ_c	=		ixM		-		ixΩ;
			lpΩ_q	=	O[	ixM	]	-	O[	ixΩ ];
			hpΩ_q	=		CS		-	O[	ixH	];
		//	hpΩ_i	=	I[	ixΩ ]	-		rel_c;

/*######	CREATE HIGH CUBE [iC+1]:	SV SETUP		(ƒsub 1X2H)									*/
		/*	create new cube to serve as the higher fragment											*/
		//	CSΩ		= CS +rel_q   	-cubeº_q;
			CSΩ	= Oª[ inM ] + hpΩ_q -cubeº_q;	/* we are excluding deleted q between inM..ixH			*/	dBUG_SvCUR( svΩ, CSΩ );
			svΩ		= newSVpvz(		0x6 |	CSΩ	);	/* round to nearest 64-bit modulus +0 / -1		*/
			SvCUR_set(				svΩ,	CSΩ	);
			cubeΩ  	= SvPVbyte_nolen(	svΩ	); 
			cubeΩ[ CSΩ ] = 0;
									AvPOST( iC, svΩ );		/* defer inserting the new element to (AV*) avICE*/	dBUG_1X2H

		/*	[iC+1]:	SPLICE KEYBYTE SECTION			(ƒsub 1X2H)									*/
		/*	cross high half of modified key data (from K) with passthrough (from char * cubeº)					*/
						lpXen	=	lpΩ_c| ( post_xc<< 3 );
			if(		zc == icO	){	/*	no high passthrough;	izM is the new end			Edge changes -->	*/											*Edge( cubeΩ )	= E[ izM ];
				switch(	lpXen	){	SwCASE_LPXOVER_01Y( *( (ui64*) ( K +ixΩ ) ),							*( (ui64*)(cube+I[ixΩ])),	*( (ui64*) cubeΩ )  )  }
			//						^lowpass xover wye	^high inclusion src								^low passthrough src	^ wye output
			}else if(	relΩ_c==0 ){	/*	high passthrough not shifted										*/											*Edge( cubeΩ )	= *Edge( cube );
				switch(	lpXen	){	SwCASE_XXOVER_01Y(	*( (ui64*)(cube+I[ixΩ])),		*( (ui64*)( K +ixΩ ) ),						*( (ui64*) cubeΩ )  )  }
			//						^double crossover wye	^exo passthrough src		^endo inclusion src							^ wye output
			}else{	/*	shift		*/																											*Edge( cubeΩ )	= *Edge( cube );
				if(	relΩ_c >0	){		bs =   relΩ_c	<< 3;	hipa = *( (ui64*) cube )<< bs;	}
				else{				bs = ( -relΩ_c )	<< 3;	hipa = *( (ui64*) cube ) >>bs;	}
				switch(	lpXen	){	SwCASE_XXOVER_01W(	hipa,  					*( (ui64*)( K +ixΩ ) ),	*( (ui64*)(cube+I[ixΩ])),	*( (ui64*) cubeΩ )  )  }	//				printf( "\nhigh passthrough (shifted)	lpXen=0x%02X\n	Hx:	0x%016llx\n	cubeΩ:	0x%16llX\n	hipa:	0x%16llX\n	Hx>>:	0x%16llX\n	lopa:	0x%16llX\n	cubeº:	0x%16llX\n",
			}//						^dbl xover dbl tee		^high passthrough, shifted	^endo inclusion src		^low passthrough src	^double-wye output	//												lpXen,				 *( (ui64*) K ), *( (ui64*) cubeΩ ),		 hipa,				 *( (ui64*)( K +ixΩ ) ),	*( (ui64*)(cube+I[ixΩ])),	*( (ui64*) cube ) );

		/*	[iC+1]:	ASSEMBLE 3-PART Q-DATA SECTION 	(ƒsub 1X2H)									*/
														i=16;
			if(	lpΩ_q	)	{		XLOADi(	cubeΩ, cube,	i, O[ ixΩ ], lpΩ_q );
							}	/*	^crossload (lpΩ_q) low-pass bytes from *(cube+O[ ixΩ ]) to *pΩ			*/
			pΩ=cubeΩ+i;
			if(	post_q	)	{		ICEPACK( pΩ,	ixM, izM, inM,				cubeΩ	);
							}	/*	^re-pack modified q-data vectors ixΩ..izM to cubeΩ[ 16+lpΩ_q..16+lpΩ_q+post_q-1 ] 	*/
			if(	hpΩ_q	)	{		XLOAD(	pΩ,	O[ ixH ],	hpΩ_q,	cube,	cubeΩ );				/*	dBUG_XLOAD_1X2H_hpΩ );	*/
							}	/*	^crossload (hpΩ_q) high-pass bytes from *(cube+O[ ixH ] ) to *pΩ		*/

/*######	UPDATE LOW CUBE [iC+0]					(ƒsub 1X2H)									*/
			*( (ui64*) cubeº+1 )=E[ izº ];	MOD_CUBE_0_AS_LPASS(	ixΩ );									
			}
		else		/*	ƒsub 1X2M	*/					{	/* mod range crosses both fragments.  		*/
									NEW_CUBE_Ω_AS_MODSxHPASS();//									dBUG_hiCAST_1X2M_postΩ,	dBUG_hiCAST_1X2M_postΩ_i ,	dBUG_XLOAD_1X2M_hpΩ);
			*( (ui64*) cubeº+1)= E[ izº ];	MOD_CUBE_0_AS_LPASSxMODS(	ixΩ);//,							dBUG_hiCAST_1X2M_postº,	dBUG_hiCAST_1X2M_postº_i );
			cubeΩ[ CSΩ	] = 0;		AvPOST( iC, svΩ );		/* defer inserting the new element to (AV*) avICE*/	dBUG_1X2M
			}																						
		}/*




*/
	else if( 	/*****	ƒsub 1X3   	*****/	tcª< 21	)		{ /* One cube splits in three.					*/	dBUGrackCALL(	3 );
		/*	*	*	*	*	*	*	*	*	*	*	*/	ncª	= tcª +1;
		/*	*	*	*	*	*	*	*	*	*/	zcΩ = (	ncª /3) -1;		/* 4..7  */
		/*	*	*	*	*	*	*/	ixΩ = xcª -	zcΩ;
		/*	*	*	*/	iz¹ =			ixΩ -1;		
		/*	*	*	*	*/	ncⁿ	=(	ixΩ -ixº ) >>1;
		zc¹ =				ncⁿ -1;	/* 4..7  */ /* not used!  seriously! not in NX3, NX4, 1x3, or 1x4! */
		/*	*/	izº =		iz¹  -	ncⁿ;		/* 4..7  */ /* only used in NX4 to set "*Edge(	cubeº ) =E[ izº	];".  */
		zcº =	izº - ixº;
		ix¹ = 	izº +1;																				dBUG_1X3_XCª_SW
																									dBUGmx( xcª+4, ix¹, iz¹ );
		cubeº = cube; 	sv0 = *(Aº +iC );

	/*	read ahead to last fragment boundary if cursor (u) hasn't read that far	*/
		if(								u< ixΩ )	{					if( RW[ v ] == null )	deIce_vKEI();
			if( ixM!=0xFF)		do	{		u= v++;		Oª[v] =Oª[u] +L[u];					DeICE_vKEI( u, v );	
								} while(	u< ixΩ );
			else				do	{		u= v++;	/*	Oª[v] =Oª[u] +Lx[u];	*/			DeICE_vKEI( u, v );	
								} while(	u< ixΩ );	}

/*######	CREATE:	MEDIAL CUBE [iC+1] 	######		(ƒsub 1X3)		######						*/
		if( ixM >ix¹ ){						CS¹ = 16 +Oª[ ixΩ ] - O[ ix¹ ];										dBUG_SvCUR( sv¹, CS¹ );
			sv¹		= newSVpvz(	0x6 |	CS¹	);					
			SvCUR_set(				sv¹,	CS¹	);
			cube¹  	= SvPVbyte_nolen(	sv¹	);	p¹  = cube¹ +16;											*( (ui64*)	cube¹+1	)	= E[ iz¹ ];
			;		post¹_q	=	Oª[	ixΩ	]	-	Oª[	ixM	];
			;		lp¹_c	=		ixM    	-		ix¹;
			;		lp¹_q	=	O[	ixM	] 	-	O[	ix¹	];											dBUG_1X3
											//	^	oCS better?
			if(		lp¹_q )	{		XLOAD(	p¹,	O[	ix¹	],	lp¹_q,	cube,	cube¹ );				
							}	/*	^crossload (lp¹_q) low-pass bytes from *(cube+O[ ix¹ ] ) to *p¹			*/
		
		/*	[iC+1]:	SUBCASE 1X3xx:	MEDIAL CUBE IS LOWPASS, MODS & HIGHPASS	(N/A)			*/
		/*	if( izM< iz¹ ){	High and low passthrough never combine when there are (3) or more output cubes.		*/
		/*				This is because 1X2 intercepts all cases where xcª< 14.							*/

		/*	[iC+1]:	SUBCASE 1X3a:	MEDIAL CUBE IS LOWPASS & MODS								*/	ƒSUB¹_B
		/*	}else{ */	if( izM==iz¹)	{	NEW_CUBE_Ω_AS_HIGHPASS();										ƒSUBΩ_E
					}else  		{	NEW_CUBE_Ω_AS_MODSxHPASS();									ƒSUBΩ_D
								}			post¹_xc = iz¹ -ixM;											
					;		lpXen=	lp¹_c| (	post¹_xc<< 3 );
					switch(	lpXen){	SwCASE_LPXOVER_01Y( *( (ui64*) ( K +ix¹ ) ),							*( (ui64*)(cube+I[ix¹] )),	*( (ui64*) cube¹ )  )  }
			//						^lowpass xover wye	^high inclusion src								^low passthrough src	^ wye output
				if(	post¹_q )	{		iCEPACK( p¹, 	ixM, iz¹, ixΩ,		cube¹ );
		/*		}	*/		}	/*	^re-pack modified q-data vectors ixM..iz¹ to cube¹[ 16..16+post¹_q-1 ]  	*/
			*Edge(	cubeº ) = E[ izº ];	MOD_CUBE_0_AS_LPASS(	ix¹ );										ƒSUBº_A

		}else{							CS¹ = 16 +Oª[ ixΩ ] - Oª[ ix¹ ];									dBUG_SvCUR( sv¹, CS¹ );
			sv¹		= newSVpvz(	0x6 |	CS¹	);					
			SvCUR_set(				sv¹,	CS¹	);
			cube¹  	= SvPVbyte_nolen(	sv¹	);	p¹  = cube¹ +16;											*( (ui64*)	cube¹+1	)	= E[ iz¹ ];

		/*	[iC+1]:	SUBCASE 1X3b:	MEDIAL CUBE IS MODS & HIGHPASS								*/	
			if( izM< iz¹)	{			NEW_CUBE_Ω_AS_HIGHPASS();										ƒSUB¹_D
				;	hp¹_c	=		ixΩ		-		ixH;
				;	pre¹_xc	=	I[	ixH	]-1	-		oc;		/*	are you sure this is good? I[inM] is not in the pre-mod range...	*/
				;	post¹_xc	=		izM		-		ix¹;		/*	fucking magic, bruh.  don't question it.  See precursur #92.		*/
				;	rel¹_c	= 		post¹_xc	-		pre¹_xc;	/*	it just about killed me 2026-08-31.  */
				;	hp¹_i	= 	I[	ix¹	]	-		rel¹_c;	/*	Dude, the trick is the "-1".  We're talking about "up to but not incliding the first byte of vector ixH".	*/
				;	hp¹_q	=	O[	ixΩ	]	-	O[	ixH	];	/*	f-yea, brah.	*/
				;	post¹_q	=	Oª[	inM	]	-	Oª[	ix¹	];
							enXhp=	post¹_xc |(		hp¹_c<< 3 );										dBUG_1X3

				if(	rel¹_c ){
				    if(	rel¹_c< 0){		bs = ( -rel¹_c )	<< 3;	hipa = *( (ui64*) cube ) >>bs;	}
				    else{				bs =   rel¹_c	<< 3;	hipa = *( (ui64*) cube )<< bs;	}
				    switch(		enXhp ){	SwCASE_LPXOVER_10Y( hipa,					*( (ui64*)( K +ix¹ ) ), 	*( (ui64*) cube¹ )  )  }
				}else{			/*	^lowpass crossover wye	^high passthrough, shifted	^low inclusion src		^wye output		*/
				    switch( 	enXhp ){	SwCASE_LPXOVER_10Y( *( (ui64*) cube ),		 	*( (ui64*)( K +ix¹ ) ), 	*( (ui64*) cube¹ )  )  }	
				    }				/*	^lowpass crossover wye	 ^high passthrough			^low inclusion src		^wye output		*/	

				if(	post¹_q )	{		iCEpACK( p¹, 	ix¹,	izM, inM,			cube¹	);						
							}	/*	^re-pack modified q-data vectors ix¹..izM to cube¹[ 16..16+post¹_q-1 ]  	*/
				if(	hp¹_q )	{		XLOAD(	p¹,	O[	ixH	],	hp¹_q,	cube,	cube¹ );				
							}	/*	^crossload (hp¹_q) high-pass bytes from *(cube+O[ ixH ] ) to *p¹			*/

		/*	[iC1 ]:	SUBCASE 1X3c:	MEDIAL CUBE IS ALL MODS 										*/	
			}else{																					ƒSUB¹_C
				if( izM< ixΩ )	{		NEW_CUBE_Ω_AS_HIGHPASS();										ƒSUBΩ_E
				}else  		{		NEW_CUBE_Ω_AS_MODSxHPASS();									ƒSUBΩ_D
							}
					switch(iz¹-ix¹){	SwCASE_LOWPASS_1I(							*( (ui64*)( K +ix¹ ) ),	*( (ui64*) cube¹ )  )  }
								/*	^inline lowpass							^definitive src		^lowpass out		*/
					post¹_q	=	Oª[	ixΩ	]	-	Oª[	ix¹	];											dBUG_1X3
				if(	post¹_q )	{		iCEPACK( p¹, 	ix¹,	iz¹, ixΩ,			cube¹	);						
				}			}	/*	^re-pack modified q-data vectors ix¹..iz¹ to cube¹[ 16..16+post¹_q-1 ]  	*/	

			*Edge( cubeº ) = E[ izº ];/* lastly */
			if( ixM == ix¹ )	{			MOD_CUBE_0_AS_LPASS(		ix¹ );									ƒSUBº_A
			}else 		{			MOD_CUBE_0_AS_LPASSxMODS( ix¹ ); 								ƒSUBº_B
			}			}

		cube¹[ CS¹	] =0;	AvPOST( iC, sv¹ );	
		cubeΩ[ CSΩ	] =0;	AvPOST( iC, svΩ );																
															}/*





*/
	else if(   	/*****	ƒsub 1X4/N	******/	tcª< 255	)		{ /* One cube splits into four plus.				*/	dBUGrackCALL(	4 );
		int						nCª=(	tcª /7 )-3;													dBUGnCª
					endo_c	=	nCª *7;																	
					exo_c	=	tcª %7;
//		if( iCx )	{
			switch(	exo_c ){								/*	zcⁿ=6;	*/
	/* 6, 6; 5, 5 */	case 0:	zcº=5; zc¹=5; zc²=4; zcΩ=4;	ix¹=6;	iz¹=11;			ixⁿ=12;	izⁿ=18;		ix²=12+endo_c;	ixΩ=17+endo_c;	break;
	/* 6, 6; 6, 5 */	case 1:	zcº=5; zc¹=5; zc²=5; zcΩ=4;	ix¹=6;	iz¹=11;			ixⁿ=12;	izⁿ=18;		ix²=12+endo_c;	ixΩ=18+endo_c;	break;
	/* 6, 6; 6, 6 */	case 2:	zcº=5; zc¹=5; zc²=5; zcΩ=5;	ix¹=6;	iz¹=11;			ixⁿ=12;	izⁿ=18;		ix²=12+endo_c;	ixΩ=18+endo_c;	break;
	/* 7, 6; 6, 6 */	case 3:	zcº=6; zc¹=5; zc²=5; zcΩ=5;	ix¹=7;	iz¹=12;			ixⁿ=13;	izⁿ=19;		ix²=13+endo_c;	ixΩ=19+endo_c;	break;
	/* 7, 7; 6, 6 */	case 4:	zcº=6; zc¹=6; zc²=5; zcΩ=5;	ix¹=7;	iz¹=13;			ixⁿ=14;	izⁿ=20;		ix²=14+endo_c;	ixΩ=20+endo_c;	break;
	/* 7, 7; 7, 6 */	case 5:	zcº=6; zc¹=6; zc²=6; zcΩ=5;	ix¹=7;	iz¹=13;			ixⁿ=14;	izⁿ=20;		ix²=14+endo_c;	ixΩ=21+endo_c;	break;
	/* 7, 7; 7, 7 */	case 6:	zcº=6; zc¹=6; zc²=6; zcΩ=6;	ix¹=7;	iz¹=13;			ixⁿ=14;	izⁿ=20;		ix²=14+endo_c;	ixΩ=21+endo_c;	break;
				}	izº=zcº;																				iz² =	ixΩ-1;	dBUGmx( xcª+4, ix¹, iz² );
//		}else{
//			switch(	exo_c ){								//	zcⁿ=-1;
//	/* 6, 6; 5, 5 */	case 0:	zcº=5; zc¹=5; zc²=4; zcΩ=4;	ix¹=6;	iz¹= izⁿ= 11;		ixⁿ=					ix²=12;			ixΩ=17;				break;
//	/* 6, 6; 6, 5 */	case 1:	zcº=5; zc¹=5; zc²=5; zcΩ=4;	ix¹=6;	iz¹= izⁿ= 11;		ixⁿ=					ix²=12;			ixΩ=18;				break;
//	/* 6, 6; 6, 6 */	case 2:	zcº=5; zc¹=5; zc²=5; zcΩ=5;	ix¹=6;	iz¹= izⁿ= 11;		ixⁿ=					ix²=12;			ixΩ=18;				break;
//	/* 7, 6; 6, 6 */	case 3:	zcº=6; zc¹=5; zc²=5; zcΩ=5;	ix¹=7;	iz¹= izⁿ= 12;		ixⁿ=					ix²=13;			ixΩ=19;				break;
//	/* 7, 7; 6, 6 */	case 4:	zcº=6; zc¹=6; zc²=5; zcΩ=5;	ix¹=7;	iz¹= izⁿ= 13;		ixⁿ=					ix²=14;			ixΩ=20;				break;
//	/* 7, 7; 7, 6 */	case 5:	zcº=6; zc¹=6; zc²=6; zcΩ=5;	ix¹=7;	iz¹= izⁿ= 13;		ixⁿ=					ix²=14;			ixΩ=21;				break;
//	/* 7, 7; 7, 7 */	case 6:	zcº=6; zc¹=6; zc²=6; zcΩ=6;	ix¹=7;	iz¹= izⁿ= 13;		ixⁿ=					ix²=14;			ixΩ=21;				break;
//				}																						iz² =	ixΩ-1;
//			}	

		cubeº	= cube;
		sv0		= *(Aº +iC );

	/*	read ahead to last fragment boundary if cursor (u) hasn't read that far	*/
		if(			u< ixΩ ){ /*	O[v]=O[u]+L[u];	*/	if( RW[ v ] == null )	deIce_vKEI();
			do	{	u=v++;		Oª[v]=Oª[u]+L[u];	O[v]=O[u]+L[u];		DeICE_vKEI( u, v );	} while( u< ixΩ );
			}	
									CS² = 16 +Oª[ ixΩ ] - Oª[ ix² ];										dBUG_SvCUR( sv², CS² );
		sv²		= newSVpvz(	0x6 |	CS²	);					
		SvCUR_set(				sv²,	CS²	);
		cube²  	= SvPVbyte_nolen(	sv²	);		p²  = cube² +16;											*Edge( cube² ) = E[ iz² ];

		/*	[iC+1]:	SUBCASE 1X4H-1:	NEW CUBE² AS MODS x HIGHPASS								*/
		if( izM< iz² )	{				NEW_CUBE_Ω_AS_HIGHPASS();										ƒSUBΩ_E
			;		hp²_c	=		iz²   	-		ixH;													ƒSUB²_D
			;		pre²_xc	=	I[	izM	]	-	I[	ix²	];	/*	no evidence of errant behavior, but I think (pre...) metrics are supposed to originate at  I[ ixH-1 ].	*/
		//	;		pre¹_xc	=	I[	ixH-1]	-	I[	ix²	];	/*	trouble is, this breaks test #60		*/
			;		post²_xc	=		izM		-		ix²;
			;		post²_c	=	1+	post²_xc;
			;		rel²_c	= 		post²_xc	-		pre²_xc;	//	printf("\n1X4H-MH	I[ix²]=%d	rel²_c=%d\n", I[ix²], rel²_c);
			;				enXhp=	post²_c |(		hp²_c<< 3 );
			if(		rel²_c ){	/*	high passthrough shift	*/					hp²_i = I[ ix² ] -rel²_c;
					switch(	enXhp ){	SwCASE_LPXOVER_10Y( *( (ui64*)(cube +	hp²_i ) ),	*( (ui64*)( K +ix² ) ),	*( (ui64*) cube² )  )  }	
			}else	{		/*		^lowpass crossover wye	^high passthrough, shifted	^low inclusion src		^wye output		*/
					switch(	enXhp ){	SwCASE_LPXOVER_10Y( *( (ui64*)(cube+I[ ix²] ) ), 	*( (ui64*)( K +ix² ) ),	*( (ui64*) cube² )  )  }
					}		/*		^lowpass crossover wye	^high passthrough src		^low inclusion src		^ wye output		*/
			;		post²_q	=	Oª[	inM	]	-	Oª[	ix²	];
			if(		post²_q )	{		iCEpACK( p², 	ix²,	izM, inM,		cube² );
							}	/*	^re-pack modified q-data vectors ix²..izM to cube²[ 16..16+post²_q-1 ]  	*/
			;		hp²_q	=	O[	ixΩ	]	-	O[	ixH	];
			if(		hp²_q	)	{	XLOAD(	p², O[	ixH	],	hp²_q,	cube,	cube² );
								}/*	^crossload (hp²_q) high-pass bytes from *(cube+O[ ixH ] ) to *p²			*/

		/*	[iC+1]:	SUBCASE 1X4H-2:	NEW CUBE² AS MODS 											*/
		}else{		if( izM==iz²)	{	NEW_CUBE_Ω_AS_HIGHPASS();										ƒSUBΩ_E
					}else  		{	NEW_CUBE_Ω_AS_MODSxHPASS();									ƒSUBΩ_D
								}																	ƒSUB²_C
					switch( iz²-ix²){	SwCASE_LOWPASS_1I(							*( (ui64*)( K +ix² ) ),	*( (ui64*) cube² )  )  }
								/*	^inline lowpass								^definitive src			^lowpass out		*/
			;		post²_q	=		Oª[ ixΩ ] - Oª[	ix²	];
			if(		post²_q )	{		iCEpACK(	p², 	ix², iz², ixΩ,		cube² );
							}	/*	^re-pack modified q-data vectors ix²..iz² to cube²[ 16..16+post²_q-1 ]  	*/
			}
		*( (ui64*) cubeº+1)	= E[ izº ];	// update cubeº epsilon only now that old value may have been conserved


		/*	[iC+1]:	SUBCASE 1X4L-1:	NEW CUBE 1 AS LOWPASS x MODS								*/
		if( ixM >ix¹ ){						CS¹ = 16 +Oª[ ixⁿ ] - O[ ix¹ ];										dBUG_SvCUR( sv¹, CS¹ );
			sv¹		= newSVpvz(	0x6 |	CS¹	);														ƒSUB¹_B
			SvCUR_set(				sv¹,	CS¹	);
			cube¹  	= SvPVbyte_nolen(	sv¹	);	p¹  = cube¹ +16;											*Edge( cube¹ ) = E[ iz¹ ];
			;		lp¹_c	=		ixM		-		ix¹;
			;		lp¹_q	=	O[	ixM	]	-	O[	ix¹	];
			if(		lp¹_q )	{		XLOAD(	p¹,	O[	ix¹	],	lp¹_q,	cube,	cube¹ );
							}	/*	^crossload (hp¹_q) low-pass bytes from *(cube+O[ ix¹ ] ) to *p¹			*/
											post¹_xc = iz¹ -ixM;
							lpXen=	lp¹_c| (	post¹_xc<< 3 );
					switch(	lpXen){	SwCASE_LPXOVER_01Y( *( (ui64*) ( K +ix¹ ) ),							*( (ui64*)(cube+I[ix¹] )),	*( (ui64*) cube¹ )  )  }
			//						^lowpass xover wye	^high inclusion src								^low passthrough src	^ wye output
			;		post¹_q	=	Oª[	ixⁿ	]	-	Oª[	ixM	];
			if(		post¹_q )	{		iCEpACK( p¹, 	ixM,	iz¹, 	ixⁿ,		cube¹ );
							}	/*	^re-pack modified q-data vectors ixM..iz¹ to cube¹[ 16..16+post¹_q-1 ]  	*/
									MOD_CUBE_0_AS_LPASS(	ix¹ );	 									ƒSUBº_A

		/*	[iC+1]:	SUBCASE 1X4L-2:	NEW CUBE 1 AS MODS 										*/
		}else{							CS¹ = 16 +Oª[ ixⁿ ] - Oª[	ix¹ ];										dBUG_SvCUR( sv¹, CS¹ );
			sv¹		= newSVpvz(	0x6 |	CS¹	);														ƒSUB¹_C
			SvCUR_set(				sv¹,	CS¹	);
			cube¹  	= SvPVbyte_nolen(	sv¹	);	p¹  = cube¹ +16;											*Edge( cube¹ ) = E[ iz¹ ];
					switch( zc¹ ){		SwCASE_LOWPASS_1I(							*( (ui64*)( K +ix¹ ) ),		*( (ui64*) cube¹ )  )  }
								/*	^inline lowpass								^definitive src			^lowpass out		*/
			;		post¹_q	=	Oª[	ixⁿ	]	 -	Oª[	ix¹	];
			if(		post¹_q )	{		iCEpACK( p¹, 	ix¹,	iz¹, 	ixⁿ,		cube¹ );
							}	/*	^re-pack modified q-data vectors ix¹..iz¹ to cube¹[ 16..16+post¹_q-1 ]  	*/

			if( ixM ==ix¹ )	{			MOD_CUBE_0_AS_LPASS(		ix¹ );	 								ƒSUBº_A
			}else 		{			MOD_CUBE_0_AS_LPASSxMODS( ix¹ ); 								ƒSUBº_B
			}			}


		cube¹[ CS¹	] = 0;	AvPOST( iC, sv¹ );

		/*	[iC+X]:	SUBCASE 1X4X:	NEW CUBE X AS MODS 										*/
		if( nCª){		
		  do	{		_ixⁿ = ixⁿ+7;
										CSⁿ = 16 +Oª[ _ixⁿ ] - Oª[ ixⁿ ];									dBUG_SvCUR( svⁿ, CSⁿ );
			svⁿ		= newSVpvz(	0x6 |	CSⁿ	);					
			SvCUR_set(				svⁿ,	CSⁿ	);
			cubeⁿ  	= SvPVbyte_nolen(	svⁿ	);	pⁿ  = cubeⁿ +16;											*Edge( cubeⁿ ) = E[ izⁿ ];
									*( (ui64*) cubeⁿ ) = *( (ui64*)( K +ixⁿ ) ) &0x00FFFFFFFFFFFFFF;
								/*	^inline lowpass (we're just gonna hardcode this one since it's constant)	*/
					postⁿ_q	=		Oª[ _ixⁿ ] - Oª[	ixⁿ	];
			if(		postⁿ_q )	{		iCEpACK(	pⁿ, 	ixⁿ, izⁿ, 	_ixⁿ,	cubeⁿ );
							}	/*	^re-pack modified q-data vectors ixⁿ..izⁿ to cubeⁿ[ 16..16+postⁿ_q-1 ]  	*/
			ixⁿ+=7;	izⁿ+=7;
			cubeⁿ[	CSⁿ		] = 0;	AvPOST( iC, svⁿ );
			} while( --nCª );
			}

		cube²[		CS²		] = 0;	AvPOST( iC, sv² );
		cubeΩ[		CSΩ	] = 0;	AvPOST( iC, svΩ );														
																									dBUG_1X4;
		}
	else	{	cS = 	sprintf(	aString,		lightning );
			cS +=	sprintf(	aString +cS,	"\n	%s: ( tc\xA6: %d) overflows vector map!  Cannot commit changes!\n\n", __FUNCTION__, tcª );
			AvDBUG_PUSH(	aString, cS );
			return;
		}																							dBUGmx( xcª+4, ocª, ixΩ );
//	if( xcª -ixº <1 ||trace){ trace=1;	printf( "\r	%s() exit	%s line %d\n", __FUNCTION__, __FILE__, __LINE__ ); }
	}

/* **	***	***	MEXICAN FIESTA	***	***	***	***	*** 	***	***	*/