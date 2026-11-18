#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "dBUG.h"
#include	"_unset.h"

void	_unset(){
	bool		bal_iC;			Aº	= AvARRAY(	avICE );	a =	miss =0;							dBUGavCLR	dBUGinit_mx;
	ui64						x	= ARG0, x1 = x+1;		za =	AvFILLp(	avArg);	if( za ==-1){	/*	no args	*/	return;	}
	_start:			zzC=(	zC	= AvFILLp(	avICE ) )-1;					if( zC ==-1){	miss+=1+( za-a );	return;	}
	ui64				nC = 	zC+1,					lo=0, hi=nC;		
	INIT_MxRACK(64);		/*	^ value to reset upper boundary (hi) to	*/
	INIT_AvCOMMIT;						cube	=	SvPVbyte_nolen(	*Aº );	// so, x is probably not in cube 0, but we handle it now to eliminate checking for it constantly
if( 	/*	x1 not in cube 0	*/	x1>=*Edge(	cube	) ){							iC= hi>>1;
  do	{_search:								cube	=	SvPVbyte_nolen(	sv =*(	iC +Aº ) );
	if(						x1==*Edge(	cube	) ){					zcΩ = zcOf(	cube );
								cubeΩ =	cube;		CSΩ = SvCUR(	svΩ = sv ); 							_anteloc:
		/*	iCI=iC;	*/								DeICEzu_( 255 );
/*		INTERLOCAL OpSCOPE		Op#		E []				A []			B []				RW []	O/I []		L []	*/
		if( iC != zC ){						cube	=	SvPVbyte_nolen(	sv =*(++	iC +Aº ) );				iCI	= iC;
			bal_iC=0;		ocª=oc=ixº= 0;		CS		=	SvCUR(			sv );							oCS	= 16;
			MxINIT;		xcª=xc=zc=zcOf(	cube	);	DeICE0_uKE( 0, 1 );		u=0;	v=1;		RW[0]=mod;	I[ 0 ]	= 0;		dBUG_LOCUS("INTERLOC");
/* =x|_	*/	if(	B[255] >1 )		{OpA;	  --	*Edge(	cubeΩ);++A[ 0 ];	   --	B[ 255 ];		ReICEΩz;
/* _x|_	*/	}else{											A[ 0]+=A[255]+B[ 255 ];
			    if(			zcΩ )	{OpB;		*Edge(	cubeΩ)-=	A[ 255 ]	+	B[ 255 ];		cubeΩ[		O[ 255 ] ]=0;	dBUGsvCUR( svΩ, O[255] );
				cubeΩ[	zcΩ-- ]=0;													SvCUR_set( svΩ, O[ 255 ] );			
/* |x|_	*/	    }else				{OpZ;		/*	cubeΩ is now empty	*/				AvCUT1B4( iC );
				}				}																goto	_next_a;
		}else{			miss +=za-a;
/* =x|$	*/	if(		B[255] >1 )	{OpAz;	 --	*Edge(	cubeΩ);			   --	B[ 255 ];		ReICEΩz;
/* _x|$	*/ 	}else if( 0<	zcΩ)	{OpBz;		*Edge(	cubeΩ)-=	A[ 255 ]	+	B[ 255 ];		cubeΩ[		O[ 255 ] ]=0;	dBUGsvCUR( svΩ, O[255] );
				cubeΩ[	zcΩ-- ]=0;													SvCUR_set( svΩ, O[ 255 ] );
/* |x|$	*/	}else				{OpZz;		/*	cubeΩ is now empty	*/				AvCUT1B4( nC );
				if(zcΩ)++	miss;	}			/*	(it was the end cube)	*/							goto	_exit_2;
			}/*	^ cubeΩ was already empty, actually	(it's negative)			*/
	}else if(					x1<	*Edge(	cube	) ){	iC=(( hi	= iC )+lo	)>>1;  if(	iC==hi ){	INTRaLOC;	goto	_loca; 	}
	}else{				/*	x1>	*Edge(	cube	)*/	iC=(( lo	= iC )+hi	)>>1;  if(	iC==lo  ){	INTRaLOC1Up_EX;		_loca:
		bal_iC=0;			ocª= oc= ixº= 0;
		MxINIT; 		  	xcª=	xc=zc=zcOf(	cube	);	DeICE0_uE(	0, 1	);	u=0;	v=1;					I[ 0 ]=0;
		while( x >E[ u ] ){								DeICE_vEI(	u, v	);	u=	v++; 	}
		do	{			/*		Op#		E []				A []			B []				RW []	O/I []		L []	*/
	_intra: 	long long			d;// =E[u] -x;
			if(	E[ u ] !=	x ){	d =E[u] -x;
/*	=x=	*/		if(	B[ u ] >	d ){
					if( 1	!=	d )	{OpC;		E[ v ] = E[ u ];		A[ v ]=1;		B[ v ]=d-1;		vNEW;	O[v+1]=O[v];	L[v]=L[u];
					  ++	xcª;					E[ u ] = x; 		/*	i +=	*/	B[ u ]-=d;			uMOD;	O[ v ]=O[ u ];	I[ v ] = I[ u ];	L[ v ]=0;
						if( xcª >=	224	)	{											SvCOMMIT;
						/* HARD FLUSH */	if( dsc || rSeqIns[0] || rSeqCut[0] )					_av_commit();				dBUG_OVERRUN_PROTECT;
										if( za != a ){	x1=( x = ARG( ++a ) )+1;							goto	_start; }
										else   													return;
										}
/*	=x_	*/			}else		{													if( !	RW[v] )	deIce_vKEI( u, v );
	_op_d:						 OpD;	  --	E[ u ];		  ++	A[ v ];	   --	B[ u ];			uvMOD;
								}						/*	i +=    --	B[ u ];	*/
				}else if( B[u]==	d ){
/*	_x=	*/			if(	1 !=	d )	{OpE;					  ++	A[ u ];	   --	B[ u ];			uMOD;
/*	_x_	*/			}else		{													if( !	RW[v] )	deIce_vKEI( u, v );
	_op_f:			 --	xcª;		 OpF;		E[ u ]+=A[v]+B[v];	A[u]+=A[v]+1;	B[ u ]=B[ v ];		uMvN;	O[v]+=L[v];	L[u]=0;
					}
/*	___	*/		}else{ ++	miss;	 OpX;		// lands in vector u padding
					}
/*	___	*/	}else	{ ++	miss;	 OpX;		// lands in vector v padding
					}		/*	 Op#		E []				A []			B []				RW []	O/I []		L []	*/

	_next_a:	if( za != a ){		x1=(	x = ARG( ++a ) )+1;
	_next_x:	    if(				x1 >= *Edge(	cube ) ){		/*	cube¹ is a lookahead for cube	*/		
				if(			iC< zzC)	{	cube¹	=	SvPVbyte_nolen(	*(1+ 	iC +Aº ) );		
/*	search		*/	if(		x1 >	*Edge(	cube¹ ) )		{	/*	commit & search		*/		SvCOMMIT;
														lo =iC+2;	hi =nC;		iC= ( lo+hi )>>1;		break;
													}	/*	^ _set() uses "2" here	*/		
				}else if(		iC != zC )	{	cube¹	=	SvPVbyte_nolen(	*(1+		iC +Aº ) );		
					if(		x1 >	*Edge(	cube¹ ) )		{miss+=1	+za -a;								goto	_exit_1;	}
				}else if(		x1 !=*Edge(	cube  ) )	{	miss +=1	+za -a;								goto	_exit_1;	
/* 0th edge	*/	}else	/*	iC == zC*/{				CoANTELOC2();    	if( --	B[ u ] >0 )	{	uMOD;	
/* =x|$		*/					OpDz;	 --	E[ u ];	miss +=	 za -a;	}else			{	uDEL;//	oCS -= L[u];
/* _x|$		*/		--	xcª;		OpBz;				miss +=	 za -a	-	B[ u ];		}			goto	_exit_1;	
								}
				xcª_SOFT_OVERRUN_PROTECT;			CoANTELOC(); ReINTERLOC¹;
				if(			x1 != E[ u ] )		{								RUN_iC;		
					if(		x1 != *Edge(	cube¹ ) ){	/*	CoINTRaLOC(x)...	*/		
/* 2nd edge	*/		}else	{						CoANTELOC();				
							if(iC != zC ){							ReINTERLOC;	TRACK_iC;
/* =x_		*/										DeICE0_vKEI(u,v);	if(	B[ u ] >1 )				goto	_op_d;	
/* _x_		*/														else   						goto	_op_f;	

							}else{									if( --	B[ u ] >0 )	{	uMOD;	
/* =x|$		*/					OpDz;	 --	E[ u ];	miss +=	 za -a;	}else			{	uDEL;//	oCS -= L[u];	/* solved unset_precursor #11, tentatively
/* _x|$		*/		--	xcª;		OpBz;				miss +=	 za -a	-	B[ u ];		}			goto	_exit_1;	
							}	}									/*	^self-heal	*/
/* 1st edge	*/	}else 						{								TRACK_iC;
/* =x_		*/	;									DeICE0_vKEI(u,v);	if(	B[ u ] >1 )				goto	_op_d;	
/* _x_		*/														else   						goto	_op_f;	
			    }								}		CoINTRaLOC(x);
			}else																				goto	_exit_1;	



/*	roll	*/	} while( 1 );
	}	}	} while( 1 );		/* search	*/
  }else	{	/*	E[0] requires special initialization, so handle entering cube 0 with PRIMOLOC	*/	PRIMOLOC;	goto	_loca;	
		}
	_exit_1:					/*	*	*	*	*	*	*	*	*	*	*	*	*/		SvCOMMIT;	
	_exit_2:					if( dsc || rSeqIns[0] || rSeqCut[0] ) 							_av_commit();	
	}


/*	ok	.........................*/