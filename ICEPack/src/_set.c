#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "dBUG.h"
#include	"_set.h"

void	_set(){	
	bool		bal_iC;			Aº	= AvARRAY(	avICE );	a =	hit =0;							dBUGavCLR	dBUGinit_mx
	ui64						x	= ARG0;				za =	AvFILLp(	avArg);	if( za ==-1){	/*	no args */	return;	}
	_start:			zzC=(	zC	= AvFILLp(	avICE ) )-1;					if( zC ==-1){	a=E_=0;	AvICExt( x, pq, pk, buf, E_, avArg, a, za );	return;	}
	ui64				nC = 	zC+1,					lo=0, hi=nC;		
	INIT_MxRACK(64);		/*	^ value to reset upper boundary (hi) to	*/
	INIT_AvCOMMIT;						cube	=	SvPVbyte_nolen(	sv=*Aº );	// so, x is probably not in cube 0, but we handle it now to eliminate a special case within INTRaLOC, which is a search entrance.
 if( 	/*	x not in cube 0	*/	x >	*Edge(	cube	) ){							iC= hi>>1;
   do	{_search:								cube	=	SvPVbyte_nolen(	sv=*( Aº+ iC ) );
	if(		/* search hit 1	*/	x == *Edge(	cube	) ){	zcΩ = zcOf( cube );
		if( iC != zC ){				cubeΩ =	cube;  CSΩ =	SvCUR(	svΩ =	sv );		_anteloc:	ANTELOC;
										cube	=	SvPVbyte_nolen(	sv=*( Aº+ ++iC ) );	INTERLOC_NX;
	_inter:																				RW[ 0 ]=mod;
			do	{			/*	Op#		E []				A []			B []				RW []	O/I []		L []	*/
/*	=+|_	*/	if(		A[0] >1)	{Op0;	 ++	*Edge(	cubeΩ); --A[ 0 ];	   ++	B[ 255 ];		if(za==a)		goto	_exit_0;
				}else{		/*	returning to intralocal context post-op:	*/
					if(	A[0]==1 )	{							A[ 0 ]=A[255];	B[ 0 ]+=B[255]+1;
/*	!|+=		*/		    if( zcΩ< 1 )	{Op1;	zcΩ=-1; 										AvCUT1B4( iC );
/*	=|+=	*/		    }else		{Op2;		*Edge(	cubeΩ )-= A[ 255 ]	+	B[ 255 ];
					/*NUL-terminate	*/	cubeΩ[	O[255]	]=0;							dBUGsvCUR(	svΩ, O[255] );
					/*del keybyte zcΩ	*/	cubeΩ[	zcΩ--	]=0;	 						SvCUR_set(	svΩ, O[255] );
								}
/*	=|==	*/		}else/*! A[0]*/	{Op9;
					++	hit;		}/*^ Abnormal encoding: null padding at non-origin.  Self-healing. */			goto	_next_a;
					}
				} while(	(	x = ARG( ++a ) ) ==	*Edge(	cubeΩ ) );						ReICEΩz;	goto	_next_x;
		}else					{Op3;	cubeΩ	=	SvPVbyte_nolen(	   *(	Aº+	iC-1) );						_epiloc:
/*	=+|$	*/										MxINIT;							INTERLOC_NX;
								while( ic< zc ){			DeICE_vEI(	u, v	);	u=v++; }		MkIn;		Oª[ u ] =O [ u ];													\
																								Oª[ v ] =O [ u ] +L[ u ];
																					EPIGEN_NX( u, v );
								if( dsc || rSeqIns[0] || rSeqCut[0] )  						_av_commit();	return;
								}
	}else if(	/* search hit 2	*/	x <	*Edge(	cube	) ){	iC=(( hi	= iC )+lo	)>>1;  if(	iC==hi ){	INTRaLOC;	goto	_loca; 	}
	}else{	/* search hit 3		x >	*Edge(	cube)	*/	iC=(( lo	= iC )+hi	)>>1;  if(	iC==lo  ){	INTRaLOC1Up;		_loca:
		bal_iC=0;			ocª= oc= ixº= 0;				MxINIT;
		;				xcª=	xc=zc= zcOf(	cube	);	DeICE0_uE(	0, 1	);	u=0;	v=1;					I[ 0 ]=0;
		while( x >E[ u ] ){								DeICE_vEI(	u, v	);	u=	v++;		}			

		do	{			/*		Op#		E []				A []			B []				RW []	O/I []		L []	*/
	_intra:	if(				x !=E[u] ){
				long long int	d = E[u] -B[u] -x;
/*	_+_		*/	if(		1<	d )	{Op6;		E[v]=E[u];			A[ v ] = d -1;	B[ v ] = B[ u ];		vMOD;	O[ v+1 ]=O[ v ];	
					 ++	xcª;					E[u]=x+1;			A[ u ] -= d;	B[ u ] = 1;		uNEW;	O[ v ]=O[ u ];	I[ v ] = I[ u ];	L[ v ]=0;
						xcª_HARD_OVERRUN_PROTECT;
			/*					Op#		E []				A []			B []				RW []	O/I []		L []	*/
/*	_+=		*/	}else if(	1==	d )	{Op7;					    --	A[ u ];	   ++	B[ u ];			uMOD;/* ^mono-scalar version doesn't require "O[v]=O[u]" */		/*		in fact it might be better just to add a conditional to test: " if( RW[ ixH ] >ok ) O[ ixH ]=O[ izM ]; ", retroactively updating this when necessary */
/*	===		*/	}else			{Op8;
					 ++	hit;		}
			}else{ if( !RW[ v ] )	deIce_vKEI();																	_intra_v:
/*	=+_		*/	if(		A[v] >1 )	{Op4;	  ++	E[ u ];		    --	A[ v ];	   ++	B[ u ];			uvMOD;	
/*	=+=		*/	}else			{Op5;		E[ u ] =E[ v ];					B[ u ]+= A[v]+B[v];	uMOD;	O[ v ] =O[ v+1 ];	//	O[ v ]+=L[ v ];		/*	I[u]=I[v]; fails precursor #43	*/
					if(	A[ v ]!=1	) ++	hit;													vNUL;	L[ v ] =L[ v+1 ];	//	I[ u ] =I[ v ];
					--	xcª;	/*	^ Abnormal encoding: null padding at non-origin.  Non-fatal and self-healing.	*/
				}	}

/* * * *	OpSCOPE:  LOCATE	* * * */
	_next_a:	if( za != a ){		x = ARG( ++a );			
	_next_x:		if(			x >=	*Edge(	cube ) ){		/*	cube¹ is a lookahead for cube	*/	
					if(		iC< zzC){		cube¹	=	SvPVbyte_nolen(	*(1+ 	iC +Aº ) );
/*	search		*/		if(	x >	*Edge(	cube¹ ) )	{	/*	commit & search		*/		SvCOMMIT;
														lo =iC+2;	hi =nC;		iC= ( lo+hi )>>1;		break;
												}
					}else if(	iC != zC ){	cube¹	=	SvPVbyte_nolen(	*(1+		iC +Aº ) );
/*	append		*/		if(	x >=	*Edge(	cube¹ ) )	{	CoANTELOC();		ReINTERLOC¹;	RUN_iC;		goto	_co_epiloc;	}
					}else _co_epiloc:				{	CoEPILOC();						EPIGEN_NX( u, v );
												if( dsc || rSeqIns[0] || rSeqCut[0] )			_av_commit();	return;
												}
					xcª_SOFT_OVERRUN_PROTECT;		CoANTELOC();		ReINTERLOC¹;
					if(		x !=	E[ u ] )		{										RUN_iC;
					    if( 	x !=	*Edge(	cube¹ ) )	{/*	CoINTRaLOC(x)	*/	
					    }else	/* x on 2nd edge	*/	{	CoANTELOC();		ReINTERLOC;		TRACK_iC;
													DeICE0_vKEI(u,v);								goto	_intra_v;
												}
					}else	/* x on edge	*/	{										TRACK_iC;
													DeICE0_vKEI(u,v);								goto	_intra_v;
					}						}		CoINTRaLOC(x);
				}else																			goto	_exit_1;
/*	_intra */	} while( 1 );
	}	}	} while( 1 );	/* search	*/
/*	The following cases are all subsequent to x being located within cube #0.
	E[0] requires special initialization, because the cubeΩ pointer has no target (cube 0 -1 does not exist).
	Also, Op3 is complicated for the same reason.	*/
  }else if(						x != *Edge(	cube	) ){									PRIMOLOC;	goto	_loca;
  }else if(	zC )		{	zcΩ = zcOf( (	cubeΩ =	cube ) ); CSΩ=	SvCUR(	svΩ =	*	Aº );	iC=0;				goto	_anteloc;
  }else		 					{Op3;	  			 								PRIMOLOC;	goto	_epiloc;
								}
	_exit_0:																			ReICEΩz;
	_exit_1:																			SvCOMMIT;
	_exit_2:						if( dsc || rSeqIns[0] || rSeqCut[0] ) 						_av_commit();

	}
//d