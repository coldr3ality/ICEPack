#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "dBUG.h"
#include	"_set.h"

struct CTX	{	bool	bal_iC;
				short		oc,	xc,
							ocª,	xcª,
							u, v, w,			/*	matrix indeces	iterate		the modification range		in	matrix { A[], B[], E[], L[] }	*/
							ixº,	ixΩ,			/*	matrix indeces	mark in		fragment boundaries		in	matrix { A[], B[], E[], L[] }	*/
							izº,	izΩ,			/*	matrix indeces	mark out		fragment boundaries		in	matrix { A[], B[], E[], L[] }	*/
							ixM, izM,			/*	matrix indeces	mark in/out	the Modification range		in	matrix { A[], B[], E[], L[] }	*/
							inM,				/*	matrix index		high-bounds	the Modification range		in	matrix { A[], B[], E[], L[] }	*/
							ixH;				/*	matrix index		marks in		the High-passthrough range	in	matrix { A[], B[], E[], L[] }	
												for inclusion-based methods, izM is always ixH -1.
												for exclusion-based methods, izM can be less than that, as cycla in-between are dropped.	*/
				SV *		rSeq_SV[	512 ]; 	/*	temporary holding of SvPVbyte(...) char* "cubes" awaiting batch splice-insertion to AV* avICE	*/
				long long int	rSeq_iR[	512	], iR,	/*	source index of rSeq_SV 		after the destination index	(for each step [asc|dsc] )	*/
							rSeqIns[	512	],	/*	number of trailing SVs to insert	after the destination index	('')						*/
							rSeqCut[	512	],	/*	number of leading SVs to remove before the destination index	('')						*/
							rSeqSrc[	512	],	/*	source index						*/
							rSeqDst[	512	],	/*	destination index					*/
							rel_iC,			/*	relative difference in active cube index since control index of current step was initialized
												—This is especially used by AvPOST(...); AvCUT1B4[2](...) to compute running dest. indeces.	*/
							cut_iC,
							step_iC;			/*	running destination index counter		*/

				enum opStat	RW[	512 ];		/* read/write status enumerator			*/

		unsigned	long long int	A[	512 ],		/* relative coord.s	which define	each negative cyclum phase	in	matrix { A[], B[], E[], L[] }	*/
							B[	512 ],		/* relative coord.s	which define	each positive cyclum phase	in	matrix { A[], B[], E[], L[] }	*/
							E[	512 ];		/* "Edge" values	which bound	the absolute coordinates	in	matrix { A[], B[], E[], L[] }	*/
					//		Zc[	512 ];		/* cube lengths, pre-re-fragmentation  	*/
					ui08 	I[	512 ],		/* cycla indeces	which align	pre/post op keybytes		in	char *	cube			*/
							K[	512 ],		/* header codes	which encode	variable q-data layout		in	char *	cube			*/
							L[	512 ]; 		/* q-data lengths	which define	each read increment		in	char *	cube			*/
					ui16		O[	512 ],		/* q-data offsets	which mark	each read position			in	char *	cube			*/
							Oª[	512 ];		/* q-data offsets	which mark	each write position			in	char *	cube			*/
			};

void	_ctx_commit(	char *ctx ){	ui64 x;//for debugging
	switch( *ctx ){
		case 0:/*	*ctx==0; nothing to commit	*/															RT	return;
		case 1:	*ctx=0;														++iC;	ReICEΩz;		GSv	goto	_sv_commit;
		case 2:	*ctx=0;										O[ v	]=oCS+CS-16;			ReICEuOx( u, v );
				MkOutZ(0);									Oª[ v+1	]=Oª[ v ]+L[ v ];
				if( bal_iC && iCI< iC ) _sv_commit_nx();  else _sv_commit_1x();	ixM=0xFF;
				if( dsc || rSeqIns[0] || rSeqCut[0] )			_av_commit();										RT	return;
		case 3:	*ctx=0;
	_sv_commit:	SvCOMMIT;
				if( dsc || rSeqIns[0] || rSeqCut[0] )			_av_commit();
	} RT	}

#define	CHK_CTX( $n )	if( *ctx != $n ){	printf("\n!	*ctx was expected to be %d here	%s line %d\n", $n, __FILE__, __LINE__ ); *ctx=$n;	}


void	_set_ea(		ui64 x, char *ctx ){
    switch( *ctx ){
	case 0:	
	_start:			zzC=(	zC =	AvFILLp(	avICE ) )-1;		if( zC ==-1) {	a=E_=0;	AvICExt( x, pq, pk, buf, E_, avArg, a, za );
																									RT	return;	}
			ixM=0xFF;			lo =0;	hi =	nC=zC+1;					Aº = AvARRAY( avICE );									*ctx=3;
			INIT_AvCOMMIT;				cube	=	SvPVbyte_nolen(	*	Aº );	// so, x is probably not in cube 0, but we handle it now to eliminate a special case within INTRaLOC, which is a search entrance.
			if(				x >	*Edge(	cube	) ){							iC= hi>>1;			GS	goto	_search;
			}else if(			x !=	*Edge(	cube	) ){									PRIMOLOC;	GL	goto	_loca;
			}else if( zC ){ zcΩ =zcOf( ( cubeΩ=	cube ) ); CSΩ=	SvCUR(	svΩ = 	*	Aº );	iC=0;				GA	goto	_anteloc;
			}else				{Op3;	  			 								PRIMOLOC;	GE	goto	_epiloc;
								}
	case 1:	if(				x !=	*Edge(	cubeΩ	) ){							++iC; *ctx=3; ReICEΩz;	GX	goto	_next_x;	}
			if(	iC != zC )	{	/*	Op#		E []				A []			B []				RW []	O/I []		L []	*/
	_inter:																				
/*	=+|_	*/	if(		A[0] >1)	{Op0;	 ++	*Edge(	cubeΩ); --A[ 0 ];	   ++	B[ 255 ];
				}else{		/*	returning to intralocal context post-op:	*/			++iC; *ctx=3;	RW[ 0 ]=mod;
					if(	A[0]==1 )	{							A[ 0 ]=A[255];	B[ 0 ]+=B[255]+1;
/*	!|+=		*/		    if( zcΩ< 1 )	{Op1;	zcΩ=-1; 										AvCUT1B4( iC );
/*	=|+=	*/		    }else		{Op2;		*Edge(	cubeΩ )-= A[ 255 ]	+	B[ 255 ];
					/*NUL-terminate	*/	cubeΩ[	O[255]	]=0;							dBUGsvCUR(	svΩ, O[255] );
					/*del keybyte zcΩ	*/	cubeΩ[	zcΩ--	]=0; 							SvCUR_set(	svΩ, O[255] );
								}
/*	=|==	*/		}else/* !A[0] */{Op9;
					++	hit;		}/*^ Abnormal encoding: null padding at non-origin.  Self-healing. */
																			
					}																			RT		return;
			}else				{Op3;	cubeΩ	=	SvPVbyte_nolen(	   *(	Aº+	iC++ ) );						_epiloc:
/*	=+|$	*/										MxINIT;							INTERLOC_NX;
								while( ic< zc ){			DeICE_vEI(	u, v	);	u=v++; }		MkIn;		Oª[ u ] =O [ u ];
																								Oª[ v ] =O [ u ] +L[ u ];
			/* fallthrough 	*/		}											*ctx=2;		uMOD;
	case 2:	/* continuing epiloc.	Op#		E []				A []			B []				RW []	O/I []		L []	*/
#define EPIGEN_EA()	if(		x > E[ u ] ){		E[ v ] = x+1;		A[ v ]=x-E[ u ];	B[ v ]=1;			vNEW;	I[ v ]=xc;	\
					++	xcª;							ReICEuOx(	u, v ); 	u=v++;			\
					    if(	xcª >=224	){				ReICEuOx(	u, v ); 							O[	v	]=oCS+CS-16;		dBUG_OVERRUN_HARD(224);	\
						MkOutZ(0);																Oª[	v+1	]=Oª[ v ]+L[ v ];	\
						if( bal_iC && iCI!=iC ) _sv_commit_nx();  else _sv_commit_1x();	ixM=0xFF;									\
						if( dsc || rSeqIns[0] || rSeqCut[0] ) 	_av_commit();						*ctx=0;			RT	return;		\
						}			\
					}else if(	x ==E[ u ] ){	++	E[ u ];					  ++	B[ u ];		}

																					EPIGEN_EA();	RT		return;
	case 3:	/* continuing intraloc.		*/
	_next_x:	if(				x >=	*Edge(	cube ) ){		/*	cube¹ is a lookahead for cube	*/	
			    if(				iC< zzC){		cube¹	=	SvPVbyte_nolen(	*(	Aº+ 	iC+1 ) );
/*	search	*/	if(			x >	*Edge(	cube¹ ) )	{	/*	commit & search		*/		SvCOMMIT;
														lo =iC+2;	hi =nC;		iC= ( lo+hi )>>1;
	_search:		    do{					cube	=	SvPVbyte_nolen( (sv=*(	Aº+	iC ) ) );
					if(		x ==	*Edge(	cube	) ){	zcΩ = zcOf( cube );
					    if( iC != zC )	{cubeΩ =	cube; CSΩ =	SvCUR(	svΩ= sv	);		_anteloc:	ANTELOC;	*ctx=1;
										cube	=	SvPVbyte_nolen( sv=*(	Aº+	iC+1 ) );	INTERLOC_EA; GI	goto	_inter;
/*	=+|$	*/		    }else		{Op3;	cubeΩ	=	SvPVbyte_nolen(	   *(	Aº+	iC-1 ) );				GE	goto	_epiloc;
								}
					}else if(	x <	*Edge(	cube	) ){	iC=(( hi	= iC )+lo	)>>1;  if(	iC==hi ){	INTRaLOC;	GL	goto	_loca; 	}
					}else{ /*	x > *Edge(	cube)*/		iC=(( lo	= iC )+hi	)>>1;  if(	iC==lo  ){	INTRaLOC1Up;			_loca:
	/* intraloc	*/		ocª= oc= ixº= 0;	bal_iC=0;		MxINIT;
						xcª=	xc=zc= zcOf(	cube	);	DeICE0_uE(	0, 1	);	u=0;	v=1;					I[ 0 ]=0;
						while( x >	E[ u ] ){				DeICE_vEI(	u, v	);	u=	v++;		}			GIa	goto	_intra;
						} }
	/* search		*/	} while( 1 );					}
				}else if(		iC != zC ){	cube¹	=	SvPVbyte_nolen(	*(	Aº+	iC+1 ) );
	/* co-epiloc	*/	if(		x >=	*Edge(	cube¹ ) )	{	CoANTELOC();		ReINTERLOC¹;  	RUN_iC;		GcE	goto	_co_epiloc;	}
				}else _co_epiloc:	{					CoEPILOC();				*ctx=2;		uMOD;
																					EPIGEN_EA();	RT			return;
								}
				xcª_SOFT_OVERRUN_PROTECT;			CoANTELOC();		ReINTERLOC¹;
				if(			x !=	E[ u ] )	{											RUN_iC;
					if(	 	x !=	*Edge(	cube¹ ) )	{/*	CoINTRaLOC(x)	*/	
					}else	/* x on 2nd edge	*/	{	CoANTELOC();		ReINTERLOC;		TRACK_iC;
													DeICE0_vKEI(u,v);								GV	goto	_intra_v;
												}
				}else		/* x on 1st edge	*/	{									TRACK_iC;
													DeICE0_vKEI(u,v);								GV	goto	_intra_v;
				}								}	CoINTRaLOC(x);
	_intra:	/*					Op#		E []				A []			B []				RW []	O/I []		L []	*/
			if(				x !=	E[ u ] ){
				long long int	d =	E[ u ] -B[ u ] -x;
/*	_+_		*/	if(		1<	d )	{Op6;		E[v]=E[u];			A[ v ] = d -1;	B[ v ] = B[ u ];		vMOD;	O[ v+1 ]=O[ v ];	
					 ++	xcª;					E[u]=x+1;			A[ u ] -= d;	B[ u ] = 1;		uNEW;	O[ v ]=O[ u ];	I[ v ] = I[ u ];	L[ v ]=0;
					//	xcª_HARD_OVERRUN_PROTECT_EA;
			/*					Op#		E []				A []			B []				RW []	O/I []		L []	*/
/*	_+=		*/	}else if(	1==d )	{Op7;					    --	A[ u ];	   ++	B[ u ];			uMOD;/* ^mono-scalar version doesn't require "O[v]=O[u]" */		/*		in fact it might be better just to add a conditional to test: " if( RW[ ixH ] >ok ) O[ ixH ]=O[ izM ]; ", retroactively updating this when necessary */
/*	===		*/	}else			{Op8;												
					 ++	hit;		}
			}else{				if( !RW[ v ] )	deIce_vKEI();														_intra_v:
/*	=+_		*/	if(		A[v] >1 )	{Op4;	 ++	E[ u ];		    --	A[ v ];	   ++	B[ u ];			uvMOD;	
/*	=+=		*/	}else			{Op5; 		E[ u ] =E[ v ];					B[ u ]+= A[v]+B[v];	uMOD;	O[ v ] =O[ v+1 ];	//	O[ v ]+=L[ v ];		/*	I[u]=I[v]; fails precursor #43	*/
					if(	A[ v ]!=1	) ++	hit;													vNUL;	L[ v ] =L[ v+1 ];	//	I[ u ] =I[ v ];
					--	xcª;	/*	Op#		E []				A []			B []				RW []	O/I []		L []	*/
				}	}/*	^ Abnormal encoding: null padding at non-origin. Self-healing.	*/								return;
		}
	printf("\n!	%s: switch broken %s line %d\n", __FUNCTION__, __FILE__, __LINE__ );	*ctx=0;
	RT	}

void	_set_all(){															dBUGavCLR	dBUGinit_mx
	char ctx=0;	hit =0;
	ui64 x;
	za =	AvFILLp(	avArg);								if( za ==-1)	/*	no args */		return;
	for( a=0; a<= za; ++a )	{			x =	ARG( a );
							_set_ea(	x,	&ctx );
						}	_ctx_commit(	&ctx );
	}
//	eddedddrdddddddddddddddwedddddddddddsdddddd