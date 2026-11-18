#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "dBUG.h"
#include "_xalloc.h"

void _xalloc_ea_norebal(	ui64 _0, ui64 x00, ui64 x0F, char *ctx ){	ui64 x;
	switch( *ctx ){
		case 0:	_start:		zzC=(	zC =	AvFILLp(	avICE ) )-1;	hi =	nC=zC+1;	Aº = AvARRAY( avICE );
			INIT_MxRACK(64);	hit =lo =0;						/*	^ value to reset upper boundary (hi) to	*/
			INIT_AvCOMMIT;
			if( zC==-1){ 		x =	x00|_0;		E[ 0 ]	=	(	A[ 0 ]=x	)+(	B[ 0 ]=1	);		RW[ 0 ]=new;	RT	*ctx=2;	return;	}

										cube	=	SvPVbyte_nolen(		*	Aº );
			if( 				x00 >*Edge(	cube	) ){							iC= hi >>1;			goto	_search;
			}else{	/*	E[0] requires special initialization */				PRIMOLOC;
				if(			x00 ==*Edge(	cube	) ){											GI	goto	_inter;	}
				else{																		GL	goto	_loca;	}
				}
		case 1:	/* continuing inter-local opscope.					*/								GI	goto	_inter;	
		case 2:	/* continuing epi-local opscope.	commit pending.	*/								GE	goto	_epi;	
		case 3:	/* continuing intra-local opscope.	commit pending.	*/
/* * * *	non-rebalancing locus	* * * */
		    if(					x00< *Edge(	cube ) ){						CoINTRaLOC_gteq( x00 );		goto	_intra;
		    }else{			/*	iC< zzC is the normal case, but we can't use		SvCOMMIT	til iC==zC is isolated. */
				if(			iC< zzC){									SvCOMMIT;
										cube	=	SvPVbyte_nolen(	sv = *(++	iC +Aº ) );
/*	search	*/		if(		x00 >*Edge(	cube	) ){	lo =iC+1;	hi=zC+1;			iC= ( lo+hi )>>1;	GS	goto	_search;	}
					}else if(	iC == zC ){														GE	goto	_epi;
					}else{											SvCOMMIT;
/*	epi-op	*/							cube	=	SvPVbyte_nolen(	sv = *(++	iC +Aº ) );
						if(	x00 >=*Edge(	cube	) ){	MxINIT;			INTERLOC_NX;
							x =	x00|_0;								CoANTELOC();				GE	goto	_epi;
					}	}
/*	roll		*/
			if(				x00 != *Edge(	cubeΩ	) ){
				if(			x00 != *Edge(	cube	) ){	CS = SvCUR(		sv );						GL	goto	_loca;	}
				else{																		GA	goto	_ante;	}
			}else				{															AL	goto	_anteloc;
			}					}
		}

  _search:
  do	{/*	search	*/						cube	=	SvPVbyte_nolen(	sv=*(	iC+	Aº ) );
	if(						x00 ==*Edge(	cube	) ){														_inter:	dBUGvxINTER;
		if( iC != zC ){	_ante:		cubeΩ =	cube;		CSΩ=SvCUR(svΩ=	sv ); zcΩ = zcOf( cube );	_anteloc:	ANTELOC;
/*	_interloc:	*/							cube	=	SvPVbyte_nolen(	sv=*( ++	iC+	Aº ) );	_interloc:	INTERLOC_NX;
			if( _0 ){	GIa goto	_intra_uv;	} /*	op is not interlocal if  value  >1	*/	

			ui64		Zv = E[ 0 ]-B[ 0 ];/*	Op#	E []				A []			B []				RW []	O/I []		L []	*/
			if(		Zv >x0F )	{	/* vector x INIT	*/		
				if(		A[0] >1 )	{	OpV0 ++	*Edge(	cubeΩ);--A[ 0 ];	   ++	B[ 255 ];		ReICEΩz;
/*			*/	}else if(	A[0]==1 )	{							A[ 0 ]=A[255];	B[ 0 ]+=B[255]+1;				
/*	!|+=		*/		if(	zcΩ<1)	    {	OpV1;	 										AvCUT1B4( iC );	
/*	=|+=	*/		}else		    {	OpV2;	*Edge(	cubeΩ )-= A[ 255 ]	+	B[ 255 ];		cubeΩ[		O[255] ]=0;	dBUGsvCUR( svΩ, O[255] );
/*			*/					/* delete end cyclum */	SvCUR_set( svΩ, O[255] );			cubeΩ[		zcΩ-- ]=0;
/*			*/					    }																
/*	=|==	*/	}else/*	A[0]==0*/{	OpVn;	/* Abnormal encoding: null padding at non-origin.  Non-fatal and self-healing.	*/
/*			*/		++	hit;		}																	RT	*ctx=1;	return;
			}else if(	Zv< x0F )	{	printf("\r is (Zv: %d )< (x0F: %d)?	line %d\n", Zv, x0F, __LINE__ );
								/* vector x ADD	*/	deIce_vKEI(	0, 1	);	u=0;	v=1;
/*	=>|_	*/	if(		A[1] >1 )	{	OpV3; ++E[ 0 ];		  ++	A[ 0 ]; /*INTERLOC_NX already did: RW[0]=mod;	*/
														  --	A[ 1 ];						RW[1]=mod;
/*	=>|=	*/	}else			{	OpV4;	E[ 0 ] =E[ 1 ];	  ++	A[ 0 ];						RW[1]=null;	O[1]=O[2];	L[1]=L[2];
					--	xcª;								if(	A[1]==1	)	B[0]+=B[1];
														else				B[0]+=B[1]-1;
								}																	RT	*ctx=3;	return;
			}else  /*	Zv==x0F*/	{/* vector x MAX	*/										dBUGvMax;	RT	*ctx=1;	return;
								}
		}else	{																						_epiloc:
			bal_iC=0;		ocª= oc= ixº= 0;				CS = SvCUR(		sv );
			MxINIT;		xcª =xc =zc =zcOf(	cube	);	DeICEz_uKEI( xcª );	v=( u=xcª )+1;							_epi:
							x=x00|_0;
				if(	E[u]<	x )	{	OpV9;	E[ v ] =x+1;		A[ v ]=x-E[u];	B[ v ]=1;			vNEW;	I[ v ]=zc;		L[ v ]=0;
					++	xcª;																		O[ v ]=O[ v+1 ]=CS;
				}else if(E[u]==	x )	{	OpV5;++ E[ u ];					  ++	B[ u ];			uMOD;
								}																	RT	*ctx=2;	return;
/*	=>|$	*/	}			/*		Op#	E []				A []			B []				RW []	O/I []		L []	*/
	}else if(					x00< *Edge(	cube	) ){	iC=(( hi = iC )+lo	)>>1;  if(	iC==hi ){	INTRaLOC;	goto	_loca; 	}
	}else{				/*	x00 >*Edge(	cube)	*/	iC=(( lo = iC )+hi	)>>1;  if(	iC==lo ){	INTRaLOC1Up;		_loca:	//dBUGvxLOCA;
		ui64		Zu;
		bal_iC=0;			ocª= oc= ixº= 0;
		MxINIT; 		  	xcª=	xc=zc= zcOf(	cube	);	DeICE0_uKE(	0, 1	);	u=0;	v=1;					I[ 0 ]=0;
		while(		E[ u ]<	x00 ){					DeICE_vKEI(	u, v	);	u=	v++; 	}					_intra:
				/*		THE 00.125% INTRALOCUTOR EDGE CASE Of The VECTOR ARITHMETIC METHODS		*/
				/*		If the vector key one-less-than x00 exists and is maxed out (value: 0x7), and
						if the current vector key (x00) does not exist and must be initialized to (0x0), then
						their serialized key-value representations are numerically serial as well, and thusly,
						both vectors will be compressed within the same cyclum, represented as one continuous run.
						Furthermore, this cyclum will be found at u-1 (figuratively, cyclum "t").					*/

		if( _0 ||		E[ u ]!=	x00 ){	/*	Edge case missed:												*/	_intra_uv:
					Zu=	E[ u ]-B[ u ];	/*	Either we would not be initializing x00 to 0x0		(initialization tbd next),	or
										the key one-less-than x00 (x00 - 0x10)  is not max ( Zu & 0x7 != 0x7 ).	*/
		}else	{/* figuratively we're at cycla [t, u],  not [u, v] */	deIce_vKEI(	u, v	);
					Zu=	E[ v ]-B[ v ];
				if(	Zu<= x0F ){		/*	Edge case missed: key x00 exists */	u=	v++;
/*	=+_=	*/	}else if(	 A[ v ] >1){	OpT  ++	E[ u ];		--	A[ v ];	  ++	B[ u ];			uvMOD;		RT	*ctx=3;	return;
/*	=+==	*/	}else{				OpT0	E[ u ] =E[ v ];	  ++	A[ u ];						RW[v]=null;	O[v]=O[v+1];	L[v]=L[v+1];
					--	xcª;								if(	A[v]==1	)	B[u]+=B[v];
														else				B[u]+=B[v]-1;					RT	*ctx=3;	return;
				}	}
			

		if(		Zu >x0F )	{	x =	x00+_0;																		dBUGvec_x( x00, 3);
		long long int		d = Zu -	x00;	/*	inclusion operation to initialize vector field x00..x0F with value _0					*/
/*		vector x does not exist			Op#	E []				A []			B []				RW []	O/I []		L []	*/
/*	_+_		*/	if(		d >1	){		OpV6;	E[ v ]=E[ u ];		A[ v ] = d -1;	B[ v ] = B[ u ];		vNEW;	I[ v ] = I[ u ];	L[ v ]=0;
/*			*/		 ++	xcª;					E[ u ]=x+1;		A[ u ] -= d;	B[ u ] = 1;		uMOD;	O[ v+1 ]=O[ v ];
/*	_+=		*/	}else if(	d==1 ){		OpV7;				    --	A[ u ];	   ++	B[ u ];			uMOD;					
/*	===		*/	}else{ ++	hit;			OpV8;
/*			*/		}																				RT	*ctx=3;	return;
		}else if(	Zu==x0F){																dBUGvMax;	RT	*ctx=3;	return;	}

/*		vector x DOES exist.	.	.	*/
/*		vector x DOES exist..	..	..	*/
/*		vector x DOES exist...	...	...	*/
/*		vector x DOES exist....	....	....	*/
/*		vector x DOES exist.....	.....	.....	*/
		ui64							_1=_0+1;	/*	[one-based] increment is [zero-based] initial value [plus one]	*/
		if( x00<=	Zu )	{		x = Zu +	_1;		/*	99.99%:	Zu is the current value of vector field x00..x0F		*/		dBUGvec_x( Zu,	3);
		}else		{		x = x00+	_1;		/*	0.01%:	x00 intersects Zu..E[ u ]-1; current value is 0			*/		dBUGvec_x( x00,	3);
					}

		if(					x >=	E[ u ] ){	/* step v req'd */				//	printf("\rstep v req'd	(x: %lld) >= (E[u: %d]: %lld)\n", x, u, E[u] );
			if( RW[ v ] == null )	{	if(		ic != zc )	{	deIce_vKEI( u, v );	//	printf("\rstep v via deIce_vKEI( u: %d, v: %d )\n", u, v);
								}else if(	iC!=zC )	{	ReINTERLOC;		TRACK_iC;		DeICE0_vKEI(u,v);
								}else			{									GE			goto	_epiloc;
							}					}
			if(				x < E[ v ]		){		/*	normal prefix-sum structure: exactly one cyclum captured by vector field x00..x0F		*/
			}else if(			x < *Edge(	cube ) ){							printf("\nextraneous cycla, but no extraneous cubes\n");
												/*	prime the "_ablate" loop: 	*/		E[ v ]=E[ u ];
	_ablate:		do	{	/*discard extraneous ic */		deICE_E(	cube[ ++ic ], A[v], B[v], L[v],	E[ v ] );
					} while(	x >= E[ v ] );				K[ v ] =	cube[ ic ];								I[	v	]= ic;
																								O[	v	]=O[ v+1]-L[ v ];
																								O[	v+1	]=pq-cube;
			}else  if(		iC< zzC	){		cube	=	SvPVbyte_nolen(	sv =*(++	iC +Aº ) );		printf("\n_abloc: iC< zzC\n");
			    if(				x > *Edge(	cube ) ){	/*	x is more than two cubes up		*/		printf("\n_abloc: x is 3+ cubes up\n");
	_v_search:	ui64					_lo =iC+1, _hi=nC;	iC= ( _lo+_hi )>>1;
				do	{					cube	=	SvPVbyte_nolen(	sv =*(	iC +Aº ) );
					if(		x <	*Edge(	cube ) )	{	iC=( ( _hi = iC )+_lo )>>1;	  if(	iC !=_hi )	continue;
						E[ v ] =	*Edge( (	cube¹	=	SvPVbyte_nolen(	*( Aº+	iC-1 )) ));	ReABLOC_nocube;
					}else{
						if(	x !=	*Edge(	cube ) )	{	iC=( ( _lo = iC )+_hi )>>1;	  if(	iC !=_lo )	continue;
												}
						E[ v ] =	*Edge(	cube  );										ReABLOC;
						}
					if(	iC !=	zC){														TRACK_iC;	goto	_ablate;	}
					else{																	GE	goto	_epiloc;	}

					} while( 1 );																			dBUGvec_ABS
			    }else	{	E[ v ] =	*Edge( (	cubeΩ	=	SvPVbyte_nolen(	*( Aº+	iC-1 ) ) ) );
					}
			}else	{	E[ v ] =	*Edge(	cube );
					if(	iC != zC	){		cube	=	SvPVbyte_nolen(	sv =*(++	iC +Aº ) );
	_v_1up:				if(	x <	*Edge(	cube	) ){					dBUGvec_AB1Up;
	_v_2up:				}else{																GE	goto	_epiloc;	}
					}else	{																GE	goto	_epiloc;	}
					}
		/*	The "_ablate" loop discards extraneous ICE datums beyond the first one in vector field x00..x0F— only the 1st is significant.
			These would be abnormal for ICEPack's prefix-sum structure, but it isn't necessarily an error, because
			this function could feasibly be used as a clear-and-reset operator in some application apart from prefix-sum structures.

				>	While it's not a critical concern from a computational complexity standpoint within the intended application,
					it would be more efficient to shift the extraneous region than clear it, as this causes work for _sv_commit_1x().
				>	The shift approach would preserve some evidence in case the extra data actually is erroneous.
				>	The shift approach would require a lot more engineering than this simple one-liner.		*/

	_op_v:	ui64					Yv	=	E[ v ]-B[ v ]-1;
			if(	x00<=Zu	){/*	x = Zu +	_1;		99.99%:	Zu is the current value of vector field x00..x0F		*/	
/*		encoding unit u swept 			Op#	E []				A []			B []				RW []	O/I []		L []	*/
															A[ u ]+=_1;
/*	_>_=	*/	if(			x <	Yv )	{OpV_uv	E[ u ]=x+1;		A[ v ]=Yv-x;	B[ u ]=1;			vMOD;				
/*	_>=_	*/	}else if(		x != Yv )	{OpV_u	E[ u ]=E[ v ];	/*	A[ v ]=0;	*/	B[ u ]=E[ v ]-x;		vNUL;	O[v]=O[v+1];	L[v]=L[v+1];
					  --	xcª;			
/*	_>==	*/	}else				{OpV_u1	E[ u ]=E[ v ];	/*	A[ v ]=0;	*/	B[ u ]=B[ v ]+1;	vNUL;	O[v]=O[v+1];	L[v]=L[v+1];
					  --	xcª;			}
			}else		{/*	x = x00+	_1;		0.01%:	x00 originates in Zu..E[ u ]-1; current value is 0		*/
/*		encoding unit u splits 			Op#	E []				A []			B []				RW []	O/I []		L []	*/
															A[ v ]=_1;						
/*	=>_=	*/	if(			x <	Yv )	{		w=v+1;
									OpVuvw	E[ w ]=E[ v ];		A[ w ]=Yv-x;	B[ w ]=B[ v ];		wNEW;	O[w+1]=O[ w ];
					++	xcª;					E[ v ]=x+1;					B[ v ]=1;			vMOD;	O[ w ]=O[ v ];	I[ w ] = I[ v ];	L[ w ]=0;
											E[ u ]=x00;					B[ u ]=x00-Zu;		uMOD;	printf( lightning ); printf("\n did it work?	line %d\n", __LINE__ );
					if( ixM == 0xFF){	MkIn;				reIce_uO(	u, v );	}				/*	O[w+1]=O[ w ]=O[ v ];	questionable	*/
					else{								reIce_uOx(	u, v );	}u=v++;				RT	*ctx=3;	return;

/*	=_>=	*/	}else if(		x!=	Yv )	{OpVuv/* E[ v ]=E[ v ]	*/				B[ v ]=E[ v ]-x;							
/*	=>==	*/	}else				{OpVuv1/*E[ v ]=E[ v ]	*/				B[ v ]+=1;							
									}		E[ u ]=x00;					B[ u ]=x00-Zu;		uMOD;	RT	*ctx=3;	return;
						}
		}else{/*				x >=	E[ u ]:	* step v NOT req'd */
/*	_>=_ */   	if(	x00<=Zu ){			OpV_t/*	E[ u ]=E[ u ]	*/	A[ u ]+=_1;	B[ u ]-=_1;							
/*	=>=_ */	}else 		{			OpVv	E[ v ]=E[ u ];		A[ v ]=_1;		B[ v ]=E[ u ]-x;		vNEW;	O[v+1]=O[ v ];	
					++	xcª;					E[ u ]=x00;	/*	A[ u ]+=0	*/	B[ u ]=x00-Zu;				O[ v ]=O[ u ];	I[ v ] = I[ u ];	L[ v ]=0;
			}			}																uMOD;	RT	*ctx=3;	return;

	    }	}   } while( 1 );	/* main search loop */															RT	*ctx=3;	return;
	}
void	_xalloc0x7(){															dBUGavCLR	dBUGinit_mx
	char ctx=0;
	ui64 x, x00, x0F, x__, _0;
	za =	AvFILLp(	avArg);								if( za ==-1)	/*	no args */		return;
	for( a=0; a<= za; ++a ){			x =	ARG( a );
						x00	=	x &	0xFFFFFFFFFFFFFFF8;
						x0F	=	x |	0x0000000000000007;
						x__ 	=	x &	0x0000000000000007;
		printf("\r%s:	_xalloc_ea_norebal(	_0: %d,	x00: 0x%llX,	x0F: 0x%llX,	&(ctx: %d) );\n",
			__FUNCTION__,		_0,		x00,			x0F,			ctx	);

		_xalloc_ea_norebal( 0, x00, x0F, &ctx );
		}								SvCOMMIT;
	if( dsc || rSeqIns[0] || rSeqCut[0] ) 		_av_commit();
	}



/*	you are alive.	*/
/*	I am alive.	*/
/*	I am alive	*/