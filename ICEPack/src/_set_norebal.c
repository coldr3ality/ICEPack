#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "dBUG.h"
#include	"_set.h"

void	_set_norebal(){
	oCS	= 16;				Aº	= AvARRAY(	avICE );	a =	hit =0;							dBUGavCLR	dBUGinit_mx
	ui64						x	= ARG0;				za =	AvFILLp(	avArg);	if( za ==-1){	/*	no args */	return;	}
	_start:			zzC=(	zC	= AvFILLp(	avICE ) )-1;					if( zC ==-1){	a=E_=0;	AvICExt( x, pq, pk, buf, E_, avArg, a, za );	return;	}
	ui64				nC = 	zC+1,					lo=0, hi=nC;		//	if( za >=247 ){	printf("!	%s: too many arguments for non-rebalancing variant (%lld > 246 )\n", __FUNCTION__, za);	return;	}
	ixM=0xFF;			/*	^ value to reset upper boundary (hi) to	*/									
	INIT_AvCOMMIT;						cube	=	SvPVbyte_nolen(	*Aº );	// so, x is probably not in cube 0, but we handle it now to eliminate a special case within INTRaLOC, which is a search entrance.
 if( 	/*	x not in cube 0	*/	x > *Edge(	cube	) ){							iC= hi>>1;
   do	{_search:				sv=*( Aº+	iC );	cube	=	SvPVbyte_nolen(	sv );				
	if(						x == *Edge(	cube	) ){					zcΩ = zcOf( cube );
		if( iC != zC ){				cubeΩ =	cube;  	CSΩ =	SvCUR( svΩ=	sv ); 	_anteloc:	ANTELOC;
						sv=*( Aº+ ++iC );	cube	=	SvPVbyte_nolen(	sv );		_interloc:	INTERLOC_1X;
			do	{				/*	Op#	E []				A []			B []				RW []	O/I []		L []	*/
	_inter:		if(			A[0] >1)	{
/*	=+|_	*/						Op0; ++	*Edge(	cubeΩ); --A[ 0 ];	   ++	B[ 255 ];		if(za==a)		goto	_exit_0;
				}else if(		A[0]==1 )	{						A[ 0 ]=A[255];	B[ 0 ]+=B[255]+1;				
/*	!|+=		*/		if(		zcΩ< 1 )	{Op1;	 										AvCUT1B4( iC );	zcΩ=-1;
/*	=|+=	*/		}else			{Op2;	*Edge(	cubeΩ )-= A[ 255 ]	+	B[ 255 ];
					/*NUL-terminate	*/	cubeΩ[	O[255] ]=0;							dBUGsvCUR(	svΩ, O[255] );
					/*del keybyte zcΩ	*/	cubeΩ[	zcΩ-- ] =0; 							SvCUR_set(	svΩ, O[255] );
									}													uMOD;	goto	_next_a;
/*	=|==	*/	}else{ ++	hit;/*A[0]==0*/ Op9;														goto	_next_a;
					}				/*^ Abnormal encoding: null padding at non-origin.  Non-fatal and self-healing.	*/
				} while(	(	x = ARG( ++a ) ) ==	*Edge(	cubeΩ ) );						ReICEΩz;	goto	_next_x;
		}else					{	Op3;  cubeΩ	=	SvPVbyte_nolen( *( Aº +	iC-1) );							_epiloc:
								MxINIT;												INTERLOC_1X;		_co_epiloc:
																					CoEPILOC( );
																					EPIGEN_1X(	u, v );
								if( dsc || rSeqIns[0] || rSeqCut[0] )  						_av_commit();	return;
								}
	}else if(					x <	*Edge(	cube	) ){	iC=(( hi	= iC )+lo	)>>1;  if(	iC==hi ){	INTRaLOC;	goto	_loca; 	}
	}else{				/*	x >	*Edge(	cube)*/		iC=(( lo	= iC )+hi	)>>1;  if(	iC==lo  ){	INTRaLOC1Up;		_loca:

		MxINIT; 		  	xcª= 	zc= zcOf(	cube	);	DeICE0_uE(	0, 1	);	u=0;	v=1;					I[ 0 ]=0;
		while( x >E[ u ] ){								DeICE_vEI(	u, v	);	u =	v++;		}			

		do	{				/*		Op#	E []				A []			B []				RW []	O/I []		L []	*/
	_intra:	if(				x !=E[u] ){
				long long int	d = E[u] -B[u] -x;
/*	_+_		*/	if(			d >1	){	Op6;	E[v]=E[u];			A[ v ] = d -1;	B[ v ] = B[ u ];		vMOD;	O[ v+1 ]=O[ v ];	
					 ++	xcª;					E[u]=x+1;			A[ u ] -= d;	B[ u ] = 1;		uNEW;	O[ v ]=O[ u ];		I[ v ] = I[ u ];	L[ v ]=0;
					//	xcª_HARD_OVERRUN_PROTECT;	

/*	_+=		*/	}else if(		d==1 ){	Op7;				    --	A[ u ];	   ++	B[ u ];			uMOD;/* ^mono-scalar version doesn't require "O[v]=O[u]" */		/*		in fact it might be better just to add a conditional to test: " if( RW[ ixH ] >ok ) O[ ixH ]=O[ izM ]; ", retroactively updating this when necessary */
/*	===		*/	}else{ ++	hit;			Op8;												
					}		/*		Op#	E []				A []			B []				RW []	O/I []		L []	*/
			}else{ if( !RW[ v ] )	deIce_vKEI();																	_intra_v:
/*	=+_		*/	if(		A[v] >1	){	Op4;  ++	E[ u ];		    --	A[ v ];	   ++	B[ u ];			uvMOD;	
/*	=+=		*/	}else{  --	xcª;			Op5; 	E[ u ] =E[ v ];					B[ u ]+= A[v]+B[v];	uMOD;	O[ v ] =O[ v+1 ];	//	O[ v ]+=L[ v ];		/*	I[u]=I[v]; fails precursor #43	*/
					if(	A[ v ]!=1	) ++	hit;													vNUL;	L[ v ] =L[ v+1 ];	//	I[ u ] =I[ v ];
				}	}/*	^ Abnormal encoding: null padding at non-origin.  Non-fatal and self-healing.	*/

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
					}else	{														ANTELOC;	goto	_interloc;
				}	}		}														else			goto	_exit_1;
/*	_intra */	} while( 1 );
	}	}	} while( 1 );	/* search	*/
  }else if( /* E[0] initialization */	x ==*Edge(	cube	) ){	
		if( zC )	{	zcΩ = zcOf( (	cubeΩ =	cube ) );	CSΩ =	SvCUR( svΩ=*Aº );				iC=0;		goto	_anteloc;	}
		else 	{					Op3;											PRIMOLOC;	goto	_epiloc;	}
  }else			{																	PRIMOLOC;	goto	_loca;
				}
	_exit_0:																			ReICEΩz;
	_exit_1:																			SvCOMMIT;
	_exit_2:						if( dsc || rSeqIns[0] || rSeqCut[0] ) 						_av_commit();

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


/*	cat	cat cat cat	cat	*/