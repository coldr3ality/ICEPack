#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "dBUG.h"
#include	"_set.h"
void	_set240(){	
							Aº	= AvARRAY(	avICE );	a =	hit =0;							dBUGavCLR	dBUGinit_mx
	ui64						x	= ARG0;				za =	AvFILLp(	avArg);	if( za ==-1){	/*	no args */	return;	}
	_start:			zzC=(	zC	= AvFILLp(	avICE ) )-1;					if( zC ==-1){	a=E_=0;	AvICExt( x, pq, pk, buf, E_, avArg, a, za );	return;	}
	ui64				nC = 	zC+1,					lo=0, hi=nC;		
	bool		run_iC;
//	if( xcª -ixº <1 ||trace ){ trace=1;	printf( "\r	_set init1 line %d\n", __FUNCTION__, __FILE__, __LINE__ ); }
	INIT_MxRACK;		/*	^ value to reset upper boundary (hi) to	*/
	INIT_AvCOMMIT;						cube	=	SvPVbyte_nolen(	*Aº );	// so, x is probably not in cube 0, but we handle it now to eliminate a special case within INTRaLOC, which is a search entrance.
 if( 	/*	x not in cube 0	*/	x >= *Edge(	cube	) ){							iC= hi>>1;
   do	{/*	search	*/		sv=*( Aº+	iC );	cube	=	SvPVbyte_nolen(	sv );				
	if(						x == *Edge(	cube	) ){					zcΩ = zcOf( cube );
		if( iC != zC ){				cubeΩ =	cube;  	CSΩ =	SvCUR( svΩ=	sv ); 	_anteloc:	ANTELOC(255);
						sv=*( Aº+ ++iC );	cube	=	SvPVbyte_nolen(	sv );		_interloc:	INTERLOC(0, 1);
			do	{
	_inter:		if(			A[0] >1){/*Op#	E []				A []			B []				RW []	O/I []		L []	*/
/*	=+|_	*/						Op0; ++	*Edge(	cubeΩ); --A[ 0 ];	   ++	B[ 255 ];		if(za==a)		goto	_exit_0;
				}else if(		A[0]==1 ){						A[ 0 ]=A[255];	B[ 0 ]+=B[255]+1;				
/*	!|+=		*/	    if(			zcΩ< 1 )	{Op1;	 										AvCUT( iC );	zcΩ=-1;
/*	=|+=	*/	    }else 				{Op2;	*Edge(	cubeΩ )-= A[ 255 ]	+	B[ 255 ];		cubeΩ[		O[255] ]=0;		dBUG_SvCUR( svΩ, O[255] );
					cubeΩ[	zcΩ-- ] =0;			/*delete last keybyte*/					SvCUR_set( svΩ, O[255] );
									}													uMOD;	goto	_next_a;
/*	=|==	*/	}else{ ++	hit;/* A[0]==0*/ Op9;														goto	_next_a;	}				
				/* 		^ Abnormal encoding: null padding at non-origin.  Non-fatal. */
				} while(	(	x = ARG( ++a ) ) ==	*Edge(	cubeΩ ) );						ReICEz(255);	goto	_next_x;
		}else					{	Op3;  cubeΩ	=	SvPVbyte_nolen( *( Aº +	iC-1) );							_epiloc:
								MxINIT;												INTERLOC(0, 1);		_co_epiloc:
																					CoEPILOC( __LINE__ );
																					EPIGEN(	u, v );
								if( dsc || rSeqIns[0] || rSeqCut[0] )  						_av_commit();	return;
								}
	}else if(					x <	*Edge(	cube	) ){	iC=(( hi	= iC )+lo	)>>1;  if(	iC==hi ){	INTRaLOC;	goto	_loca; 	}
	}else{				/*	x >	*Edge(	cube)*/		iC=(( lo	= iC )+hi	)>>1;  if(	iC==lo  ){	INTRaLOC1Up;		_loca:
		run_iC=0;			ocª= oc= ixº= 0;
		MxINIT; 		  	xcª=	xc=zc= zcOf(	cube	);	DeICE0_uE(	0, 1	);	u=0;	v=1;					I[ 0 ]=0;
		while( x >E[ u ] ){								DeICE_vEI(	u, v	);	u =	v++;		}			

		do	{				/*		Op#	E []				A []			B []				RW []	O/I []		L []	*/
	_intra:	if(				x !=E[u] ){
				long long int	d = E[u] -B[u] -x;
/*	_+_		*/	if(			d >1	){	Op6;	E[v]=E[u];			A[ v ] = d -1;	B[ v ] = B[ u ];		vMOD;	O[ v+1 ]=O[ v ];	
					 ++	xcª;					E[u]=x+1;			A[ u ] -= d;	B[ u ] = 1;		uNEW;	O[ v ]=O[ u ];		I[ v ] = I[ u ];	L[ v ]=0;
						xcª_HARD_OVERRUN_PROTECTION;	

/*	_+=		*/	}else if(		d==1 ){	Op7;				    --	A[ u ];	   ++	B[ u ];			uMOD;/* ^mono-scalar version doesn't require "O[v]=O[u]" */		/*		in fact it might be better just to add a conditional to test: " if( RW[ ixH ] >ok ) O[ ixH ]=O[ izM ]; ", retroactively updating this when necessary */
/*	===		*/	}else{ ++	hit;			Op8;												
					}		/*		Op#	E []				A []			B []				RW []	O/I []		L []	*/
			}else{ if( !RW[ v ] )	deIce_vKEI();																	_intra_v:
/*	=+_		*/	if(		A[v] >1	){	Op4;  ++	E[ u ];		    --	A[ v ];	   ++	B[ u ];			uvMOD;	
/*	=+=		*/	}else			{	Op5; 	E[ u ] =E[ v ]; if( 1!=	A[ v ] ) ++hit;	B[ u ]+= A[v]+B[v];	uMOD;	O[ v ] =O[ v+1 ];	//	O[ v ]+=L[ v ];		/*	I[u]=I[v]; fails precursor #43	*/
					--	xcª;	 			  			/*	^	*/							vNUL;	L[ v ] =L[ v+1 ];		//	I[ u ] =I[ v ];
				}				}	/*					^ Abnormal encoding: null padding at non-origin.  (self-healing)	*/

#ifdef	ReBAL_ENABLE
/* * * *	OpSCOPE:  LOCATE	* * * */
	_next_a:	if( za != a ){		x = ARG( ++a );			
	_next_x:		if(			x >=	*Edge(	cube ) ){		/*	cube¹ is a lookahead for cube	*/	
					if(		iC< zzC){		cube¹	=	SvPVbyte_nolen(	*(1+ 	iC +Aº ) );
/*	search		*/		if(	x >	*Edge(	cube¹ ) )	{	/*	commit & search		*/		SvCOMMIT;
														lo =iC+2;	hi =nC;		iC= ( lo+hi )>>1;		break;
												}
					}else if(	iC != zC ){	cube¹	=	SvPVbyte_nolen(	*(1+		iC +Aº ) );
/*	append		*/		if(	x >=	*Edge(	cube¹ ) )	{	CoANTELOC(__LINE__);	ReINTERLOC¹; RUN_iC;
							goto	_re_epiloc;	}
					}else{			_re_epiloc:		CoEPILOC(__LINE__);	EPIGEN( u, v );
						;							if( dsc || rSeqIns[0] || rSeqCut[0])	 	_av_commit();	return;
						}
					xcª_SOFT_OVERRUN_PROTECTION;	CoANTELOC(__LINE__);	ReINTERLOC¹;
					if(		x !=	E[ u ] )		{										RUN_iC;
					    if( 	x !=	*Edge(	cube¹ ) )	{		/*def	CoINTRaLOC(x)	*/	
					    }else	/* x on 2nd edge	*/	{	CoANTELOC(__LINE__);	ReINTERLOC;	RUN_iC__TRACK;
													DeICE0_vKEI(u,v);								goto	_intra_v;
												}
					}else	/* x on edge	*/	{										RUN_iC__TRACK;
													DeICE0_vKEI(u,v);								goto	_intra_v;
					}						}		CoINTRaLOC(x);
				}else																			goto	_exit_1;
#else	
///* * * *	OpSCOPE:  LOCATE	* * * */		2026-08-02: stable ver. before attempting ReINTRaLOC again...
	_next_a:	if( za != a ){		x = ARG( ++a );
	_next_x:		if(			x <	*Edge(	cube ) ){	  									CoINTRaLOC(x);
				}else{	/*	iC< zzC is the 99% case for entropic args, but we can't use			SvCOMMIT	til iC==zC is isolated. */
					if(		iC< zzC){													SvCOMMIT;
						;				cube	=	SvPVbyte_nolen(	sv = *(++	iC +Aº ) );
/*	search		*/		if(	x >	*Edge(	cube	) ){	lo =iC+1;	hi=nC;			iC= ( lo+hi )>>1;		break;	}
					}else if(	iC == zC )																goto	_co_epiloc;
					else	{															SvCOMMIT;
/*	append		*/		;				cube	=	SvPVbyte_nolen(	sv = *(++	iC +Aº ) );
						if(	x >=	*Edge(	cube	) )												goto	_epiloc;
						}
/*	roll to iC+1	*/
					if(		x != *Edge(	cubeΩ	) ){
						if(	x != *Edge(	cube	) ){	CS = SvCUR(		sv );							goto	_loca;	}
						else{	cubeΩ =	cube;		CSΩ=SvCUR( svΩ =sv ); zcΩ = zcOf(	cube );		goto	_anteloc;	}
					}else	{														ANTELOC(255);goto	_interloc;
				}	}		}														else			goto	_exit_1;
#endif
/*	_intra */	} while( 1 );	//	if( xcª -ixº <1 ||trace ){ trace=1;	printf( "\r	search breaks	%s %s line %d\n", __FUNCTION__, __FILE__, __LINE__ ); }
	}	}	} while( 1 );	/* search	*/
  }else	{	/*	E[0] requires special initialization, so handle entering cube 0 with PRIMOLOC	*/	PRIMOLOC;	goto	_loca;
		}
	_exit_0:																			ReICEz(255);
	_exit_1:																			SvCOMMIT;
	_exit_2:						if( dsc || rSeqIns[0] || rSeqCut[0] ) 						_av_commit();

	}

void _next_inc( ui64 x, ui08 call_lev ){
	
	
	}
/*					U+207B					U+00B9	U+00B2	U+00B3, U+2070,	U+2074–U+2079) and mathematical operators (U+207A, U+207B, U+207C, U+207D, U+207E
	U+0189	U+0177	8315	248		167		U+0185	U+0178	U+0179	³U+8304,	8308—8313
	½		±				°		º		¹		²		³		
	½										¹		²		³
											0185	0178	0179	#252
											¹		²		³		cubeⁿ
U+8304
	ö

*/


/*	cat	*/