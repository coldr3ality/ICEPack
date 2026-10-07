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
ui08 	Qc,	*pqz;	/* for ReICEz */
si64		d;
	SV ** pSv;		Aº =	    AvARRAY(	avICE );								dBUGavCLR	dBUGinit_mx
ui64	x = ARG0,	a =	miss=0;	za =	AvFILLp(	avArg);					if( za ==-1){	/*	no args	*/		return;	}
					zzC=(	zC =	AvFILLp(	avICE ) )-1;				if( zC ==-1){	/*	no ICE	*/		return;	}
ui64	x1 = x+1,			nC=		zC+1,				lo=0, hi=	nC;		if( za >=247 ){	printf("!	_set(): too many arguments (buffer rotation not yet implemented)\n");	return;	}
	bool	run_iC;
	INIT_MxRACK;		/*	^ value to reset upper boundary (hi) to	*/
	INIT_AvCOMMIT;						cube	=	SvPVbyte_nolen(	*Aº );	// so, x is probably not in cube 0, but we handle it now to eliminate checking for it constantly
if( 	/*	x1 not in cube 0	*/	x1>=*Edge(	cube	) ){							iC= hi>>1;
  do	{/*	search	*/						cube	=	SvPVbyte_nolen(	sv =*(	iC +Aº ) );
	if(						x1==*Edge(	cube	) ){					zcΩ = zcOf(	cube );
								cubeΩ =	cube;		CSΩ = SvCUR(	svΩ = sv ); 								_anteloc:
													DeICEzu_( 255 );
/* * * *	INTER-CUBE OpSCOPE	* * * *	Op#	E []				A []			B []				RW []	O/I []		L []	*/
		if( iC != zC ){						cube	=	SvPVbyte(		sv =*(++	iC +Aº ), CS );		iCI=iC;	_interloc:
			MxINIT;		xcª=xc=zc=zcOf(	cube	);	DeICE0_uKE( 0, 1 );		u=0;	v=1;					I[0]=0;
/* =x|_	*/	if(	B[255] >1 ){			OpA;  --	*Edge(	cubeΩ);++A[ 0 ];	   --	B[ 255 ];		ReICEz( 255 );
/* _x|_	*/	}else{											A[ 0]+=A[255]+B[ 255 ];
			    if(			zcΩ ){		OpB;	*Edge(	cubeΩ)-=	A[ 255 ]	+	B[ 255 ];		cubeΩ[		O[ 255 ] ]=0;	dBUG_SvCUR( svΩ, O[255] );
				cubeΩ[	zcΩ-- ]=0;													SvCUR_set( svΩ, O[ 255 ] );			
/* |x|_	*/	    }else			{		OpZ;	/*	cubeΩ is now empty	*/				AvCUT( iC );
				}			}															uMOD0;	goto	_next_a;
		}else{			miss +=za-a;
/* =x|$	*/	if(	B[255] >1 )	{		OpAz; --	*Edge(	cubeΩ);			   --	B[ 255 ];		ReICEz( 255 );
/* _x|$	*/ 	}else if(	0<	zcΩ)	{	OpBz;	*Edge(	cubeΩ)-=	A[ 255 ]	+	B[ 255 ];		cubeΩ[		O[ 255 ] ]=0;	dBUG_SvCUR( svΩ, O[255] );
				cubeΩ[	zcΩ-- ]=0;													SvCUR_set( svΩ, O[ 255 ] );
/* |x|$	*/	}else			{		OpZz;	/*	cubeΩ is now empty	*/				AvCUT( nC );
				if(zcΩ) ++miss;	}				/*	(it was the end cube)	*/							goto	_exit_2;
			}/*	^ cubeΩ was already empty, actually	(it's negative)			*/
	}else if(					x1<	*Edge(	cube	) ){	iC=(( hi	= iC )+lo	)>>1;  if(	iC==hi ){	INTRaLOC;	goto	_loca; 	}
	}else{				/*	x1>	*Edge(	cube	)*/	iC=(( lo	= iC )+hi	)>>1;  if(	iC==lo  ){	INTRaLOC1Up_EX;		_loca:
		
		MxINIT; 		  	xcª=xc=zc=zcOf(	cube	);	DeICE0_uKE(	0, 1	);	u=0;	v=1;					I[ 0 ]=0;
		while( x >E[ u ] ){								DeICE_vKEI(	u, v	);	u=	v++; 	}			

/* * * *	INTRA-CUBE OpSCOPE	* * * *	Op#	E []				A []			B []				RW []	O/I []		L []	*/
	_roll: do	{	d =E[u] -x;
			if(	d >=1&&	B[ u ] >=d ){														uMOD;
				if(		B[ u ] >1 ){
					if(	B[ u ] !=d ){
/* =x=	*/				if( 1	!=d ){	OpC;	E[ v ] = E[ u ];		A[ v ]=1;		B[ v ]=d-1;		vNEW;	O[v+1]=O[v];	L[v]=L[u];
					  ++	xcª;					E[ u ]-= d;		/*	i +=	*/	B[ u ]-=d;					I[ v ] = I[ u ];	L[u]=0;
/* =x_	*/				}else{		OpD;							if( !	RW[v] )		deIce_vKEI( u, v );
										    --	E[ u ];		  ++	A[ v ];	   --	B[ u ];			vMOD;
						}	}								/*	i +=    --	B[ u ];	*/
/* _x=	*/			else	{			OpE;				  ++	A[ u ];	   --	B[ u ];
						}
/* _x_	*/		}else{ --	xcª;			OpF;							if( !	RW[v] )		deIce_vKEI( u, v );
											E[ u ]+=A[v]+B[v];	A[u]+=A[v]+1;	B[ u ]=B[ v ];		vNUL;	O[v]+=L[v];	L[u]=0;
					}
/* ___	*/	}else	{ ++	miss;		OpX;
					}		/*		Op#	E []				A []			B []				RW []	O/I []		L []	*/

/* * * *	OpSCOPE:  LOCATE	* * * */
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
						if(	x1 != *Edge(	cube	) ){	CS=	SvCUR(	sv );				/*	ReINTRaLOC;*/	goto	_loca;	}
						else{	cubeΩ =	cube;		CSΩ=	SvCUR(	svΩ = sv ); zcΩ = zcOf(	cubeΩ );		goto	_anteloc;	}
					}else	{						CS=	SvCUR(	sv );						DeICEzu_(255); goto	_interloc;
			    	}	}		}															else			goto	_exit_1;
/*	roll	*/	} while( 1 );
	}	}	} while( 1 );		/* search	*/
/*	E[0] requires special initialization, so enter cube 0 here	*/
/*	to avoid checking for it at every cube entrance 		*/
  }else	{											CS=	SvCUR(	sv=*Aº );	iC=0;
/*	no cube before	cube 0 */ 	cubeΩ =	nube;		CSΩ=16;		svΩ=NULL; zcΩ = -1;				goto	_loca;
		}																					/*	no		loco_	*/
	_exit_1:					/*	*	*	*	*	*	*	*	*	*	*	*	*/		SvCOMMIT;
	_exit_2:					if( dsc || rSeqIns[0] || rSeqCut[0] ) 							_av_commit();
	}

/*	edddd2*/