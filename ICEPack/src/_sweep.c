#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "dBUG.h"
#include "_sweep.h"

#define	dBUGvec_x( $x_origin )	if( x >xFF ){ printf("\r!	new value for x breaches vector boundary ( 0x%llX+%d > 0x%llX)	%s line %d\n",	\
																			$x_origin, _0+1,		xFF,		__FILE__, __LINE__ );	return ctx;	}
#define	dBUGvxSRCH			printf("\r	search line %d\n",					__LINE__ );
#define	dBUGvxINTER		printf("\r	_inter line %d\n",					__LINE__ );
#define	dBUGvxLOCA			printf("\r	_loca line %d\n",					__LINE__ );
#define	dBUGvxINTRA		printf("\n	_intra line %d	E[ %d ] ==%lld	\n",		__LINE__, u, E[u]);
#define	dBUGvxINTERnoINTRA	printf("\r	from _inter to _intra line %d\n",		__LINE__ );

#define	dBUGvec_ABS		printf("\r	b4 _abloc:	_ab_wayUp yields E[v]==%lld\n", 	E[v]	);
#define	dBUGvec_AB1Up   	printf("\r	b4 _abloc:	_ab_1Up yields E[v]==%lld\n",	E[v]	);
#define	dBUGvec_AB2Up   	printf("\r	b4 _abloc:	_ab_2Up returns 2\n"				);
#define	dBUGvec_ABprox   	printf("\r	b4 _abloc:	deIce_vKEI yields E[v]==%lld\n",	E[v]	);					\
		/*hax*/	}else{		printf("\n! cycle v non-null while locating opscope of vector field 0x%llX..0x%llX, line %d\n", x00, xFF, __LINE__ );	\
					}

#define RT	printf("\r	return at line %d\n\n\n", __LINE__ );
#define GI	printf("\ngoto _inter	line %d\n", __LINE__ );
#define GE	printf("\ngoto _epi_op	line %d\n", __LINE__ );
#define GS	printf("\ngoto _search	line %d\n", __LINE__ );
#define GL	printf("\ngoto _loca 	line %d\n", __LINE__ );
#define GA	printf("\ngoto _ante	line %d\n", __LINE__ );
#define AL	printf("\ngoto _anteloc	line %d\n", __LINE__ );
#define GIa	printf("\ngoto _intra	line %d\n", __LINE__ );

char _vec0x7_add(	ui64 x00,	ui64 xFF,	ui64 _0, char ctx ){	/*	right-shift the leading fill boundary captured by [x..y00-1] by s;	if none exists, create one at x00+s-1	*/
	ui64		x,		nC, lo, hi,					FF	=	xFF -x00;		bool	run_iC;
	char					bit = 64-__builtin_clzll(	FF );
	ui64		pow2 = 1<<	bit,
		ff =	pow2-1;	
	if(	ff !=	FF	){	
		char		digit	=	8-( __builtin_clzll( FF ) >>3);
				printf("\r!	%s: vector range is not in bitwise alignment %s line %d:\n	FF:	0x%016llX\n	bit:	%d\n	digit:	%d\n	ff:	0x%016llX\n	x00:	0x%016llX\n	xFF:	0x%016llX\n	x__:	0x%016llX\n\n",
					__FUNCTION__,					__FILE__,	__LINE__, 	FF,				bit,			digit,			ff,				x00,				xFF,				_0 );	return ctx;	}
//	printf("\n\n\n\n\n\n\n_vec0x7_add(...): ctx=%d	x00..xFF: %lld..%lld ( 0x%llX..0x%..X )	+%lld\n", ctx, x00, xFF, x00, xFF, _0 );
	switch( ctx ){
		case 0:	/*	ctx state 0:	initializing; there is no previous opscope context.			*/
							zzC=(	zC =	AvFILLp(	avICE ) )-1;	hi =	nC=zC+1;	Aº = AvARRAY( avICE );
			INIT_MxRACK;	hit =lo =0;						/*	^ value to reset upper boundary (hi) to	*/
			INIT_AvCOMMIT;
			if( zC==-1){ 	x =	x00|_0;			E[ 0 ]	=	(	A[ 0 ]=x	)+(	B[ 0 ]=1	);		RW[ 0 ]=new;	RT	return 2;	}

										cube	=	SvPVbyte_nolen(		*	Aº );
			if( 				x00 >*Edge(	cube	) ){							iC= hi>>1;			goto	_search;
			}else{ /* When in cube #0, cubeΩ is null	*/	CS = SvCUR(	sv=*Aº );	iC=0;
								cubeΩ =	nube;		CSΩ=16;		svΩ=NULL; zcΩ = -1;
				if(			x00 ==*Edge(	cube	) ){											GI	goto	_inter;	}
				else{																		GL	goto	_loca;	}
				}
		case 1:	/* continuing inter-local opscope.					*/								GI	goto	_inter;	
		case 2:	/* continuing epi-local opscope.	commit pending.	*/								GE	goto	_epi_op;	
		case 3:	/* continuing intra-local opscope.	commit pending.	*/
/* * * *	ReSCOPE	* * * */
		    if(					x00< *Edge(	cube ) ){										CoINTRaLOC( x00); goto _intra;
		    }else{			/*	iC< zzC is the 99% case for entropic args, but we can't use			SvCOMMIT1x	til iC==zC is isolated. */
			if(				iC< zzC){													SvCOMMIT1x;
										cube	=	SvPVbyte_nolen(	sv = *(++	iC +Aº ) );
/*	search	*/	if(			x00 >*Edge(	cube	) ){	lo =iC+1;	hi=zC+1;			iC= ( lo+hi )>>1;	GS	goto	_search;	}
			}else if(			iC == zC ){														GE	goto	_epi_op;
			}else{ 																	SvCOMMIT1x;
/*	epi-op	*/							cube	=	SvPVbyte_nolen(	sv = *(++	iC +Aº ) );
				if(			x00 >=*Edge(	cube	) ){	MxINIT;							INTERLOC(0, 1);
						x =	x00|_0;													CoANTELOC(__LINE__);	GE goto	_epi_op;
				}	}
/*	roll		*/
		    if(					x00 != *Edge(	cubeΩ	) ){
			if(				x00 != *Edge(	cube	) ){	CS = SvCUR(		sv );		/*	ReINTRaLOC;*/GL	goto	_loca;	}
			else{																			GA	goto	_ante;	}
		    }else				{																AL	goto	_anteloc;
		    }					}
		}

  _search:
  do	{/*	search	*/						cube	=	SvPVbyte_nolen(	sv=*(	iC+	Aº ) );
	if(						x00 ==*Edge(	cube	) ){														_inter:	dBUGvxINTER;
		if( iC != zC ){	_ante:		cubeΩ =	cube;		CSΩ=SvCUR( svΩ =	sv ); zcΩ = zcOf( cube );	_anteloc:	ANTELOC(255);
/*	_interloc:	*/							cube	=	SvPVbyte_nolen(	sv=*( ++	iC+	Aº ) );	_interloc:	INTERLOC(0, 1);
			if( _0 ){	GIa goto	_intra;	} /*	op is not interlocal if  value  >1	*/	

			ui64		Zv = E[ 0 ]-B[ 0 ];/*	Op#	E []				A []			B []				RW []	O/I []		L []	*/
			if(		Zv >xFF )	{	/* vector x INIT	*/		
				if(		A[0] >1 )	{	OpV0 ++	*Edge(	cubeΩ);--A[ 0 ];	   ++	B[ 255 ];		ReICEz(255);		
/*			*/	}else if(	A[0]==1 )	{							A[ 0 ]=A[255];	B[ 0 ]+=B[255]+1;				
/*	!|+=		*/		if(	zcΩ<1)		{OpV1;	 										AvCUT( iC );	
/*	=|+=	*/		}else			{OpV2;	*Edge(	cubeΩ )-= A[ 255 ]	+	B[ 255 ];		cubeΩ[		O[255] ]=0;	dBUG_SvCUR( svΩ, O[255] );
/*			*/					/* delete end cyclum */	SvCUR_set( svΩ, O[255] );			cubeΩ[		zcΩ-- ]=0;
/*			*/						}																
/*	=|==	*/	}else/*	A[0]==0*/{	OpVn;	/* Abnormal encoding: null padding at non-origin	*/		
/*			*/		++	hit;		}																	RT	return 1;
			}else if(	Zv< xFF )	{ 	/* vector x ADD	*/	deIce_vKEI(	0, 1	);	u=0;	v=1;
/*	=>|_	*/	if(		A[1] >1 )	{	OpV3; ++E[ 0 ];		  ++	A[ 0 ]; /* INTERLOC already did:	RW[0]=mod;	*/
														  --	A[ 1 ];						RW[1]=mod;
/*	=>|=	*/	}else			{	OpV4;	E[ 0 ] =E[ 1 ];	  ++	A[ 0 ];		B[0]+=B[1]-( !A[1] );	RW[1]=null;	O[ 1 ]=O[ 0 ];
					--	xcª;		}																	RT	return 3;
			}else  /*	Zv==xFF*/	{/* vector x MAX	*/										dBUGvMax;	RT	return 1;
								}
		}else	{	_epiloc:							CS = SvCUR(		sv );
			MxINIT;	xcª =xc =zc =zcOf(	cube	);	DeICEz_uKEI( xcª );	v=( u=xcª )+1;							_epi_op:
						x=x00|_0;/*	Op#	E []				A []			B []				RW []	O/I []		L []	*/
					if(	x >	E[ u ] )	{OpV9;	E[ v ] =x+1;		A[ v ]=x-E[u];	B[ v ]=1;			vNEW;	I[ v ]=zc;		L[ v ]=0;
				++	xcª;																			O[ v ]=O[ v+1 ]=CS;
				}else if(	x == E[ u ] )	{OpV5;++ E[ u ];					  ++	B[ u ];			uMOD;
									}																RT	return 2;
/*	=>|$	*/	}
	}else if(					x00< *Edge(	cube	) ){	iC=(( hi = iC )+lo	)>>1;  if(	iC==hi ){	INTRaLOC;	goto	_loca; 	}
	}else{				/*	x00 >*Edge(	cube)	*/	iC=(( lo = iC )+hi	)>>1;  if(	iC==lo ){	INTRaLOC1Up;		_loca:	//dBUGvxLOCA;
		ui64		Zu;
		MxINIT;			xc=xcª=zc=zcOf(	cube	);	DeICE0_uKE(	0, 1	);	u=0;	v=1;
		while(		E[ u ]<	x00 ){					DeICE_vKEI(	u, v	);	u =	v++;	}								//dBUGvxINTRA;
		if( _0 ||		E[ u ]!=	x00 ){	/*	The 99% case in the critical path	*	*	*	*	*	*	*	*	*/	_intra:
				Zu=	E[ u ]-B[ u ];		//	if( ixM==0xFF ) icI=ic;	/* ..w. */
		}else{/*	we're at t..u not u..v	*/				deIce_vKEI(	u, v	);	/* just pretend */				
				Zu=	E[ v ]-B[ v ];
			if(	Zu<= xFF ){			//	if( ixM==0xFF ) icI =ic;
			}else{					//	if( ixM==0xFF ) icI =ic -1;	elimiated icI in favor of localizing I[ ixM ], so now what?
									/*	<1% edge case when storing high-entropy keys in a prefix-sum structure.
										If the logical value of the vector numerically preceding this one is maxed out,
										and this value is being initialized to zero, they will share the same encoding unit.
										The opscope of this operation directly precedes u..v (better expressed as t..u).
										*/
/*	=+_=	*/	if(	 A[ v ] >0 )	{	OpVt  ++	E[ u ];		--	A[ v ];	  ++	B[ u ];			uvMOD;		RT return 3;
/*	=+== 	*/	}else			{	OpVt0	/*	bad form for prefix-sum structure		*/
								}			/*TOOOOOODOOOOOOOOOOOOO	*/
			}	u = v++;			}

		if(		Zu>	xFF ){	x =	x00+_0;																		dBUGvec_x( x00 );
		long long int		d = Zu -	x00;	/*	inclusion operation to initialize vector field x00..xFF with value _0					*/
/*		vector x does not exist			Op#	E []				A []			B []				RW []	O/I []		L []	*/
/*	_+_		*/	if(		d >1	){		OpV6;	E[ v ]=E[ u ];		A[ v ] = d -1;	B[ v ] = B[ u ];		vNEW;	I[ v ] = I[ u ];	L[ v ]=0;
/*			*/		 ++	xcª;					E[ u ]=x+1;		A[ u ] -= d;	B[ u ] = 1;		uMOD;	O[ v+1 ]=O[ v ];
/*	_+=		*/	}else if(	d==1 ){		OpV7;				    --	A[ u ];	   ++	B[ u ];			uMOD;					
/*	===		*/	}else{ ++	hit;			OpV8;
/*			*/		}																						RT return 3;
				}
		else if(	Zu==xFF){																		dBUGvMax;	RT return 3;	}

/*		vector x DOES exist.	.	.	*/
/*		vector x DOES exist..	..	..	*/
/*		vector x DOES exist...	...	...	*/
/*		vector x DOES exist....	....	....	*/
/*		vector x DOES exist.....	.....	.....	*/
		ui64							_1=_0+1;	/*	[one-based] increment is [zero-based] initial value [plus one]	*/
		if( x00<=	Zu )	{		x = Zu +	_1;		/*	99.99%:	Zu is the current value of vector field x00..xFF		*/		dBUGvec_x( Zu );
		}else		{		x = x00+	_1;		/*	0.01%:	x00 intersects Zu..E[ u ]-1; current value is 0			*/		dBUGvec_x( x00 );
					}

		if(					x >=	E[ u ] ){	/* step v req'd */
			if(		ic != zc	){	if( RW[ v ]==null ){		deIce_vKEI( u, v );	}
			}else{	/*	prime the "_ablate" loop: 	*/	E[ v ]=E[ u ];	goto _abloc;	}


//			}else if(	!_0		){ /*		Op#	E []				A []			B []				RW []	O/I []		L []	*/
//				if(	iC != zC ){	ui64 Av, Bv;											SvCOMMIT1x;
//					MxINIT;				cube	=  SvPVbyte(	sv=*( ++	iC+	Aº ), CS );
//						xcª = zc = zcOf(	cube );		pq =	cube+16;							RW[ 0 ]=mod;
//	/*bypass	decode*/	if( (cube[0]&0x47)< 2){				deICE( cube[ 0 ], Av, Bv, L[0] );
//						E[ 0 ]=	*Edge(	cubeΩ	)	+		Av		+	Bv;
//	/*	!|+=	 */			if(zcΩ>0){ *Edge(	cubeΩ	)	-=		A[ u ]	+	B[ u ];		cubeΩ[		O[ u ] ]=0;
//								OpV2;	cubeΩ[ zcΩ-- ]=0;		dBUG_SvCUR( svΩ, O[ u ] );	SvCUR_set( svΩ, O[ u ] );	
//	/*	=|+= */			}else{	OpV1;		 										AvCUT( iC );	}
//														/* ¿	u =!= 0 ?  */	B[ 0 ]=Bv+B[ u ] -( !Av );
//															A[ 0 ]=A[ u ]+1;
//					}else{								++	A[ u ];					ReICEz( u );
//								OpV3;				deICE( cube[0], Av,	B[0],	L[0] );							if( Av< 2){ printf( lightning ); printf("\n bypass of DeICE...() did not work; Av< 1 (%lld )!		cube[0]&0x47 == %lld\n\n", Av, cube[0]&0x47);	}
//						E[ 0 ]=	*Edge(	cubeΩ	)	+			Av+	B[0];
//							  ++	*Edge(	cubeΩ	);			A[ 0 ]=Av  -1;
//						}
//					ic = icI=I[ 0 ]=0; u=0; v=1;		/*	K[ 0 ]=cube[ 0 ];	*/						O[1]=L[0]+16;	RT return 3;
//	/*	=>|$ */	}else	{		OpV5;	++	E[ u ];		++	A[ u ];						uMOD;			RT return 2;
//						}
//			}else if(	iC !=zC	){			cube	=	SvPVbyte_nolen(	sv =*(++	iC +Aº ) );
//					ic=-1;icI-= zc;		pq =	cube+16;		CS = SvCUR(		sv );
//							zc = zcOf(	cube	);	deIce_vKEI( u, v );
//			}else			{				E[ u ]=x+1;					B[ u ]=1;			vNUL;	RT return 2;
//					  --	xcª;	}

			if(				x >= E[ v ]			){	/*	abnormal prefix-sum structure: practically impossible	*/
			    printf( lightning );	printf("\n_abloc: mitigating abnormal prefix-sum structure\n\n");
			    if(				x < *Edge(	cube	) ){	/*	prime the "_ablate" loop: 	*/	E[ v ]=E[ u ];
			    }else{
				
	_abloc:		ui64	iCx=iC, xC;
				if( iC< zzC	){			cube	=	SvPVbyte_nolen(	sv =*(++	iC +Aº ) );		printf("\n_abloc: iC< zzC\n");
				    if(			x > *Edge(	cube	) ){	/*	way far-out						*/	printf("\n_abloc: way far-out\n");
	_ab_wayUp:		ui64								_lo =iC+1, _hi=zC+1;		iC= ( _lo+_hi )>>1;
/*	_ab_search*/	  do	{					cube 	=	SvPVbyte_nolen(	sv =*(++	iC +Aº ) );
/*	ABERLOC	*/	if(		x ==*Edge(	cube	) ){						if(	iC !=	zC){	cube¹=SvPVbyte_nolen( *( Aº+iC-1 ) ); E[ v ]=*Edge( cube¹ );	break;	}//	E[ v ]=*EC(	iC-1);	break;	}
					  --	xcª;							AvCUT2(	zC, iCx );		GE	goto _epiloc;	//B[ u ]=1;		E[ u ]=x+1;	vNUL;	RT return 2;
/*	ABRALOC	*/	}else if(	x <	*Edge(	cube	) ){	iC=( ( _hi = iC )+_lo )>>1;  if(	iC==_hi ){	cube¹=SvPVbyte_nolen( *( Aº+iC-1 ) ); E[ v ]=*Edge( cube¹ );	break;	}//E[ v ]=*EC(	iC-1 );  	break;	}
/*	ABRALOC1up	*/	}else{/*	x >	*Edge(	cube)	*/	iC=( ( _lo = iC )+_hi )>>1;  if(	iC==_lo ){
																		if(	iC != zC){	cube¹=SvPVbyte_nolen( *( Aº+iC++ ) ); E[ v ]=*Edge( cube¹ );	break;	}//E[ v ]=*EC(	iC++ ); 	break;	}
					  --	xcª;							AvCUT2(	zC, iCx );		GE	goto _epiloc;	}	//B[ u ]=1;		E[ u ]=x+1;	vNUL;	RT return 2;	}
						}
					} while( 1 );																			dBUGvec_ABS
					}
				}else if( iC == zC ){
					  --	xcª;							AvCUT2(	zC, iCx );		GE	goto _epiloc;
				}else{					cube	=	SvPVbyte_nolen(	sv =*(++	iC +Aº ) );
	_ab_1Up:			if(		x <	*Edge(	cube	) ){									E[ v ]=*Edge( cube );	dBUGvec_AB1Up
	_ab_2Up:			}else{							AvCUT(	zC	);										dBUGvec_AB2Up
					--	xcª;												GE	goto _epiloc;
					}	}							AvCUT2( iC, iCx );
			    ;		ic=-1;	/*icI-=zc;*/	pq =	cube+16;		CS = SvCUR(		sv );
			    ocª=xcª+1;	xcª+=1+(	zc=zcOf( 	cube	) );	deIce_vKEI( u, v );
			    oc =xc +1;	xc +=1+	zc;
		/*	The "_ablate" loop discards extraneous ICE datums beyond the first one in vector field x00..xFF— only the 1st is significant.
			These would be abnormal for ICEPack's prefix-sum structure, but it isn't necessarily an error, because
			this function could feasibly be used as a clear-and-reset operator in some application apart from prefix-sum structures.

				>	While it's not a critical concern from a computational complexity standpoint within the intended application,
					it would be more efficient to shift the extraneous region than clear it, as this causes work for _sv_commit_1x().
				>	The shift approach would preserve some evidence in case the extra data actually is erroneous.
				>	The shift approach would require a lot more engineering than this simple one-liner.
			*/
	_ablate:	    while(			x >= E[ v ] )	{			deICE_E(	cube[ ++ic ], A[v], B[v], L[v],	E[ v ] ); }		I[ v   	]= ic;
			    /*discard erroneous v's */					K[ v ]=	cube[ ic ];								O[ v+1 	]=pq-cube;
																								O[ v   	]=O[ v+1]-L[ v ];
			    }	}

			ui64					Yv	=	E[ v ]-B[ v ]-1;
			if(	x00<=Zu	){/*	x = Zu +	_1;		99.99%:	Zu is the current value of vector field x00..xFF		*/	
/*		encoding unit u swept 			Op#	E []				A []			B []				RW []	O/I []		L []	*/
															A[ u ]+=_1;
/*	_>_=	*/	if(			x <	Yv )	{OpV_uv	E[ u ]=x+1;		A[ v ]=Yv-x;	B[ u ]=1;			vMOD;				
/*	_>=_	*/	}else if(		x != Yv )	{OpV_u	E[ u ]=E[ v ];	/*	A[ v ]=0;	*/	B[ u ]=E[ v ]-x;		vNUL;	O[v]=O[u];
					  --	xcª;			
/*	_>==	*/	}else				{OpV_u1	E[ u ]=E[ v ];	/*	A[ v ]=0;	*/	B[ u ]=B[ v ]+1;	vNUL;	O[v]=O[u];
					  --	xcª;			}
			}else		{/*	x = x00+	_1;		0.01%:	x00 originates in Zu..E[ u ]-1; current value is 0		*/
/*		encoding unit u splits 			Op#	E []				A []			B []				RW []	O/I []		L []	*/
															A[ v ]=_1;						
/*	=>_=	*/	if(			x <	Yv )	{		w=v+1;
									OpVuvw	E[ w ]=E[ v ];		A[ w ]=Yv-x;	B[ w ]=B[ v ];		wNEW;	I[ w ]=I[ v ];	L[ w ]=0;
					++	xcª;					E[ v ]=x+1;					B[ v ]=1;			vMOD;	
											E[ u ]=x00;					B[ u ]=x00-Zu;		uMOD;	
					if( ixM == 0xFF){	MkIn;				reIce_uO(	u, v );	}
					else{								reIce_uOx(	u, v );	}u=v++;				O[w+1]=O[ w ]=O[ v ];	RT return 3;
/*	=_>=	*/	}else if(		x!=	Yv )	{OpVuv/* E[ v ]=E[ v ]	*/				B[ v ]=E[ v ]-x;							
/*	=>==	*/	}else				{OpVuv1/*E[ v ]=E[ v ]	*/				B[ v ]+=1;							
									}		E[ u ]=x00;					B[ u ]=x00-Zu;		uMOD;				RT return 3;
						}
		}else{/*				x >=	E[ u ]:	* step v NOT req'd */
/*	_>=_ */   	if(	x00<=Zu ){			OpV_t/*	E[ u ]=E[ u ]	*/	A[ u ]+=_1;	B[ u ]-=_1;							
/*	=>=_ */	}else 		{			OpVv	E[ v ]=E[ u ];		A[ v ]=_1;		B[ v ]=E[ u ]-x;		vNEW;	I[ v ]=I[ u ];	L[ v ]=0;
					++	xcª;					E[ u ]=x00;	/*	A[ u ]+=0	*/	B[ u ]=x00-Zu;				O[v+1]=O[ v ]=O[ u ];
			}			}																uMOD;				RT return 3;

	    }	}   } while( 1 );	/* main search loop */																		RT return 3;
	}

void	_sweep(){																dBUGavCLR	dBUGinit_mx
	char ctx=0;
	ui64 x, x00, xFF, x__;
	za =	AvFILLp(	avArg);								if( za ==-1)	/*	no args */		return;
	for( a=0; a<= za; ++a ){			x =	ARG( a );
						x00	=	x &	0xFFFFFFFFFFFFFFF8;
						xFF	=	x |	0x0000000000000007;
						x__ 	=	x &	0x0000000000000007;
		printf("\r%s:	_vec0x7_add( 0x%llX, 0x%llX, 0, ctx:%d );		%llu..%llu +1\n",
			__FUNCTION__,			x00,		xFF,		ctx,			x00, xFF );

		ctx=_vec0x7_add( x00, xFF,	0, ctx );
		}						SvCOMMIT1x;	printf("\rfinal SvCOMMIT1x at line %d\n", __LINE__ );
	if( dsc || rSeqIns[0] || rSeqCut[0] ) 		_av_commit();
	}



/*	you are alive.	*/
/*	I am alive.	*/