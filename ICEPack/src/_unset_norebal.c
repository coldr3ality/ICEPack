#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "dBUG.h"
#include	"_unset.h"

void	_unset_norebal(){
	oCS	= 16;				Aº	= AvARRAY(	avICE );	a =	miss =0;							dBUGavCLR	dBUGinit_mx;
	ui64						x	= ARG0, x1 = x+1;		za =	AvFILLp(	avArg);	if( za ==-1){	/*	no args	*/	return;	}
	_start:			zzC=(	zC	= AvFILLp(	avICE ) )-1;					if( zC ==-1){	miss+=1+( za-a );	return;	}
	ui64				nC = 	zC+1,					lo=0, hi=nC;			if( za >=247 ){	printf("!	%s: too many arguments for non-rebalancing variant (%lld > 246 )\n", __FUNCTION__, za);	return;	}
	INIT_MxRACK(64);		/*	^ value to reset upper boundary (hi) to	*/									
	INIT_AvCOMMIT;						cube	=	SvPVbyte_nolen(	*Aº );	// so, x is probably not in cube 0, but we handle it now to eliminate checking for it constantly
if( 	/*	x1 not in cube 0	*/	x1>=*Edge(	cube	) ){							iC= hi>>1;
  do	{_search:								cube	=	SvPVbyte_nolen(	sv =*(	iC +Aº ) );
	if(						x1==*Edge(	cube	) ){					zcΩ = zcOf(	cube );
								cubeΩ =	cube;		CSΩ = SvCUR(	svΩ = sv ); 							_anteloc:
													DeICEzu_( 255 );
/* * * *	INTER-CUBE OpSCOPE	* * * *	Op#	E []				A []			B []				RW []	O/I []		L []	*/
		if( iC != zC ){						cube	=	SvPVbyte_nolen(	sv =*(++	iC +Aº ) );				iCI	= iC;	_interloc:
		/*	bal_iC=0;		ocª=oc=ixº= 0;*/	CS		=	SvCUR(			sv );						/*	oCS	= 16;	*/
			MxINIT;/*xc=*/xcª=	zc=zcOf(	cube	);	DeICE0_uKE( 0, 1 );		u=0;	v=1;		RW[0]=mod;	I[ 0 ]	= 0;		dBUG_LOCUS("INTERLOC");
/* =x|_	*/	if(	B[255] >1 ){			OpA;  --	*Edge(	cubeΩ);++A[ 0 ];	   --	B[ 255 ];		ReICEΩz;
/* _x|_	*/	}else{											A[ 0]+=A[255]+B[ 255 ];
			    if(			zcΩ )	{	OpB;	*Edge(	cubeΩ)-=	A[ 255 ]	+	B[ 255 ];		cubeΩ[		O[ 255 ] ]=0;	dBUGsvCUR( svΩ, O[255] );
				cubeΩ[	zcΩ-- ]=0;													SvCUR_set( svΩ, O[ 255 ] );			
/* |x|_	*/	    }else				{	OpZ;	/*	cubeΩ is now empty	*/				AvCUT1B4( iC );
				}				}																goto	_next_a;
		}else{			miss +=za-a;
/* =x|$	*/	if(		B[255] >1 )	{	OpAz; --	*Edge(	cubeΩ);			   --	B[ 255 ];		ReICEΩz;
/* _x|$	*/ 	}else if( 0<	zcΩ)	{	OpBz;	*Edge(	cubeΩ)-=	A[ 255 ]	+	B[ 255 ];		cubeΩ[		O[ 255 ] ]=0;	dBUGsvCUR( svΩ, O[255] );
				cubeΩ[	zcΩ-- ]=0;													SvCUR_set( svΩ, O[ 255 ] );
/* |x|$	*/	}else				{	OpZz;	/*	cubeΩ is now empty	*/				AvCUT1B4( nC );
				if( zcΩ ) ++miss;	}			/*	(it was the end cube)	*/							goto	_exit_2;
			}/*	^ cubeΩ was already empty, actually	(it's negative)			*/
	}else if(					x1<	*Edge(	cube	) ){	iC=(( hi	= iC )+lo	)>>1;  if(	iC==hi ){	INTRaLOC;	goto	_loca; 	}
	}else{				/*	x1>	*Edge(	cube	)*/	iC=(( lo	= iC )+hi	)>>1;  if(	iC==lo  ){	INTRaLOC1Up_EX;		_loca:

		MxINIT; 		  	xcª= 	zc=zcOf(	cube	);	DeICE0_uKE(	0, 1	);	u=0;	v=1;					I[ 0 ]=0;
		while( x >E[ u ] ){								DeICE_vKEI(	u, v	);	u=	v++; 	}			
		do	{			/*			Op#	E []				A []			B []				RW []	O/I []		L []	*/
	_intra: 	long long				d =E[u] -x;
			if(			B[ u ] >=	d ){														uMOD;
				if(		B[ u ] >1 ){
					if(	B[ u ] !=	d ){
/* =x=	*/				if(	1<	d ){	OpC;	E[ v ] = E[ u ];		A[ v ]=1;		B[ v ]=d-1;		vNEW;	O[v+1]=O[v];	L[v]=L[u];
					  ++	xcª;					E[ u ] = x; 		/*	i +=	*/	B[ u ]-=d;					O[ v ]=O[ u ];	I[ v ] = I[ u ];	L[ v ]=0;//	L[u]=0;					
/* =x_	*/				}else if(1==d ){	OpD;							if( !	RW[ v ] )		deIce_vKEI( u, v );//^ added ,				^added,		^removed:	2026-10-08, during ReBAL_ENABLE port
										    --	E[ u ];		  ++	A[ v ];	   --	B[ u ];			vMOD;
/* ___	*/				}else	{	OpX;
					  ++	miss;	}							/*	i +=    --	B[ u ];	*/
/* _x=	*/			}else	{		OpE;				  ++	A[ u ];	   --	B[ u ];
							}
/* _x_	*/		}else{ --	xcª;			OpF;											if( !	RW[ v ] )	deIce_vKEI( u, v );
											E[ u ]+=A[v]+B[v];	A[u]+=A[v]+1;	B[ u ]=B[ v ];		vNUL;	O[v]+=L[v];	L[u]=0;
					}
/* ___	*/	}else	{ ++	miss;		OpX;
					}		/*		Op#	E []				A []			B []				RW []	O/I []		L []	*/






	_next_a:	if( za != a ){		x1=(	x = ARG( ++a ) )+1;
	_next_x:		if(			x1 < *Edge(	cube	) ){									CoINTRaLOC(x);
				}else{		/*	*	*	*	*	*	*	*	*	*	*	*	*/		SvCOMMIT;
					if(		iC< zzC){		cube =	SvPVbyte_nolen(	sv = *(++	iC +Aº ) );
/*	break roll; search	*/	if(	x1 >	*Edge(	cube	) ){	lo =iC+1;	hi=nC;		iC= ( lo+hi )>>1;			break;	}
					}else if(	iC != zC){		cube =	SvPVbyte(		sv = *(++	iC +Aº ),	CS );
						if(	x1 >	*Edge(	cube	) ){			miss+=1+( za-a );						goto	_exit_2;	}
					}else if(	x1 !=*Edge(	cubeΩ	) ){			miss+=1+( za-a );						goto	_exit_2;
					}else	{																	goto	_anteloc;
							}
					if(		x1 != *Edge(	cubeΩ	) ){
						if(	x1 != *Edge(	cube	) ){	CS=	SvCUR(	sv );								goto	_loca;	}
						else{	cubeΩ =	cube;		CSΩ=SvCUR(	svΩ = sv ); zcΩ = zcOf(	cubeΩ );		goto	_anteloc;	}
					}else	{						CS=	SvCUR(	sv );					DeICEzu_(255); goto	_interloc;
			    	}	}		}														else			goto	_exit_1;
/*	roll	*/	} while( 1 );
	}	}	} while( 1 );		/* search	*/
  }else	{	/*	E[0] requires special initialization, so handle entering cube 0 with PRIMOLOC	*/	PRIMOLOC;	goto	_loca;
		}
	_exit_1:					/*	*	*	*	*	*	*	*	*	*	*	*	*/		SvCOMMIT;
	_exit_2:					if( dsc || rSeqIns[0] || rSeqCut[0] ) 							_av_commit();
	}
/*	ok	.........................*/