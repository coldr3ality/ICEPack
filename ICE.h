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

	#define DEBUG_ReSEQ_L2

#if defined(DEBUG_ReSEQ_L2)
	#define dBUG_SvINS(		$iC, $sv )		cS=sprintf(aString, "\r%c	in step #%d:	insertion after index %lld (%lld)	rel_iC=%d	(rSeq_SV[ %d ])\n\n",	241, dsc, $iC, $iC+1, 	rel_iC, iR );	av_push( avDBUG, newSVpvn(  aString, cS ) );
	#define dBUG_SvCUT(		$iC, $sv )		cS=sprintf(aString, "\r%c	in step #%d:	deletion at index %lld			rel_iC=%d\n\n",					241,	dsc, $iC, 			rel_iC );		av_push( avDBUG, newSVpvn(  aString, cS ) );
	#define dBUG_SvReCUT(	$iC, $sv )		cS=sprintf(aString, "\r%c	in step #%d:	deletion before index %lld (%lld)	rel_iC=%d\n\n",					241, dsc, $iC, $iC-1, 	rel_iC );		av_push( avDBUG, newSVpvn(  aString, cS ) );
#else
	#define dBUG_SvINS(		$iC, $sv )
	#define dBUG_SvCUT(		$iC, $sv )
	#define dBUG_SvReCUT(	$iC, $sv )
#endif

void _init_h(){
#if defined(DEBUG_ReSEQ_L2)
	printf("\r	DEBUG_ReSEQ_L2 is defined in ICE.h: auditing nominal activity of AvPOST, AvPOSTcut, and AvPOSTcut_retro\n");
#endif
	}

#define BUF( $px, $pz )		q =$pz -$px;				/*	Find the length of q data		*/		\
						while( q >7){				/*	Append the q data to the buffer.	*/		\
								*( (ui64*) pqx) = *( (ui64*) $px); $px+=8;    q-=8;    pqx+=8;    }		\
						if( q!=0){															\
								CASTq2p( pqx, $px, q); 	pqx += q;								\
								}




#define	AvPOSTins( $iC, $sv )																		\
		if(	rack_iC == $iC ){							++	rSeqIns[ dsc ];								\
		}else{	rSeq_iR[	dsc ]	=	iR;															\
				rSeqSrc[	dsc ]	=	rack_iC;		rel_iC -=					rSeqCut[ dsc ];			\
				rSeqDst[	dsc ]	=	rack_iC 	+	rel_iC;											\
												rel_iC +=	rSeqIns[ dsc ];								\
/* new step	*/		++	dsc;			rack_iC = $iC;			rSeqIns[ dsc ]=1;	rSeqCut[ dsc ] = 0;			\
			}	rSeq_SV[ ++iR ]=$sv;																dBUG_SvINS( $iC, $sv )


#define	AvPOSTcut( $iC )		SvREFCNT_dec(*( pSv0+$iC ) );	/* automatically increments iC			*/	\
		if(	rack_iC == $iC	){											++	rSeqCut[ dsc ];			\
		}else{	rSeq_iR[	dsc ]	=	iR;															\
				rSeqSrc[	dsc ]	=	rack_iC;		rel_iC -=					rSeqCut[ dsc ];			\
				rSeqDst[	dsc ]	=	rack_iC 	+	rel_iC;											\
												rel_iC +=	rSeqIns[ dsc ];								\
/* new step	*/		++	dsc;								rSeqIns[ dsc ]=0;	rSeqCut[ dsc ] = 1;			\
			}						rack_iC = ++$iC;												dBUG_SvCUT( $iC, $sv )


#define	AvPOSTcut_retro( $iC )								/* assumes iC is incremented already		*/	\
		if(	rack_iC == $iC-1 ){	SvREFCNT_dec(*( pSv0+rack_iC ) );		++	rSeqCut[ dsc ];				\
		}else{	rSeq_iR[	dsc ]	=	iR;															\
				rSeqSrc[	dsc ]	=	rack_iC;		rel_iC -=					rSeqCut[ dsc ];			\
				rSeqDst[	dsc ]	=	rack_iC 	+	rel_iC;											\
												rel_iC +=	rSeqIns[ dsc ];								\
/* new  step	*/		++	dsc;	SvREFCNT_dec(*( pSv0+$iC-1 ) );	rSeqIns[ dsc ]=0;	rSeqCut[ dsc ] = 1;			\
			}						rack_iC = $iC;													dBUG_SvReCUT( $iC, $sv )





#define AvCUBE( $avICE, $cube, $pk, $pq, $avArg, $a, $za, $E0 )	/* "Cube" an ascending list of unsigned integers	*/					\
	if( pSv0 != AvARRAY( avICE )  ){	printf("\npSv0 is out of sync with avICE going into AvCUBE\n");	pSv0=AvARRAY( avICE );	}		\
/*	printf("\r<AvCUBE	starting at arg %lld/%lld	E_( %llu ) <	x( %llu ) 		\n", a, za, $E0, x );		*/								\
															Ax =x-$E0;	Bx =1;										\
	if( $a >=$za){	/* no  args	*/				zc = 0;	reICE0(	Ax,			Bx,		$cube, $pq );	*( (ui64*)	$cube+1 ) =x+1;	*pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	pSv0=AvARRAY( $avICE );	/* push new cube with only x		*/	\
	}else{									zc = -1;																		\
		do	{			Ex	=	x +1;		pSv= AvARRAY( $avArg ) + ++$a;												\
			if( SvIOK( *pSv ) ){		x= SvIVX(   *	pSv );																	\
				if(		Ex ==	x )	{								  ++	Bx;	  				}						/*	=+|$	*/	\
				else if(	Ex < 	x )	{	if(	zc==7 ){											*( (ui64*)	$cube+1) = $E0;	*$pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	pSv0=AvARRAY( $avICE );	/* push new cube		*/	\
											zc=0;								$pk=$cube+1;	*( (ui64*)	$cube ) =0;													/* reset cube buffer	*/	\
													reICE0(	Ax,			Bx,		$cube,	$pq );  						/* encode x in cyclum 0	*/	\
										}else{ ++zc;	reICE(	Ax,			Bx,		$pk,	 	$pq );  						/* encode x in cyclum zc */	\
											}				Ax =x -Ex;	Bx=1;	$E0=Ex;								/*	_+|$	*/	\
									}																				\
			/* !SvIOK on argument x treated as a cube boundary directive	*/\
			}else{						if(	zc==7 ){											*( (ui64*)	$cube+1) = $E0;	*$pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	pSv0=AvARRAY( $avICE );	/* push new cube		*/	\
																							*( (ui64*)	$cube ) =0;															/* reset cube buffer	*/	\
													reICE0(	Ax,			Bx,		$cube, $pq );  	*( (ui64*)	$cube+1) = Ex;	*$pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	pSv0=AvARRAY( $avICE );	/* push new cube		*/	\
										}else{		reICE(	Ax,			Bx,		$pk,	 $pq );  	*( (ui64*)	$cube+1) = Ex;	*$pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	pSv0=AvARRAY( $avICE );	/* push new cube		*/	\
											}zc=-1;								$pk=$cube;	*( (ui64*)	$cube ) =0;													/* reset cube buffer	*/	\
			/* ...but we must ignore consecutive !SvIOK's				*/				$pq=$cube +16;						\
				while(	$a< $za )	if( SvIOK( *( pSv= AvARRAY( $avArg ) + ++$a ) ) )										\
								{																			\
								x= SvIVX(   *	pSv );			Ax =x -Ex;	Bx=1;	$E0=Ex;	break;				\
								}																			\
			}	}	while( $a< $za );																			\
		if(	SvIOK( *pSv ) ){				if(	zc==7 ){											*( (ui64*)	$cube+1) = $E0;	*$pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	pSv0=AvARRAY( $avICE );	/* push new cube		*/	\
																				$pk=$cube+1;	*( (ui64*) $cube ) =0;													/* reset cube buffer	*/	\
													reICE0(	Ax,			Bx,		$cube,$pq );  						/* encode x in cyclum 0	*/	\
										}else{		reICE(	Ax,			Bx,		$pk,  $pq );  						/* encode x in cyclum zc */	\
											}												*( (ui64*)	$cube+1 ) =x+1;	*$pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	pSv0=AvARRAY( $avICE );	/* push new cube		*/	\
		}				}/*	printf("\r	</AvCUBE>\n");	*/



#define AvEXT( $avICE, $cube, $pk, $pq, $avArg, $a, $za, $E0 )	/* "Cube" an ascending list of unsigned integers	*/					\
	if( pSv0 != AvARRAY( avICE )  ){	printf("\npSv0 is out of sync with avICE going into AvCUBE\n");	pSv0=AvARRAY( avICE );	}		\
/*	printf("\r<AvCUBE	starting at arg %lld/%lld	E_( %llu ) <	x( %llu ) 		\n", a, za, $E0, x );		*/								\
											zc = 0;				Ax =x-$E0;	Bx =1;										\
	if( $a >=$za){	/* no  args	*/						reICE0(	Ax,			Bx,		$cube, $pq );	*( (ui64*)	$cube+1 ) =x+1;	*pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	pSv0=AvARRAY( $avICE );	/* push new cube with only x		*/	\
	}else{									zc = -1;																		\
		do	{			Ex	=	x +1;		pSv= AvARRAY( $avArg ) + ++$a;												\
			if( SvIOK( *pSv ) ){		x= SvIVX(   *	pSv );																	\
				if(		Ex ==	x )	{								  ++	Bx;	  				}						/*	=+|$	*/	\
				else if(	Ex < 	x )	{	if(	zc==7 ){											*( (ui64*)	$cube+1) = $E0;	*$pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	pSv0=AvARRAY( $avICE );	/* push new cube		*/	\
											zc=0;								$pk=$cube+1;	*( (ui64*)	$cube ) =0;													/* reset cube buffer	*/	\
													reICE0(	Ax,			Bx,		$cube,	$pq );  						/* encode x in cyclum 0	*/	\
										}else{ ++zc;	reICE(	Ax,			Bx,		$pk,	 	$pq );  						/* encode x in cyclum zc */	\
											}				Ax =x -Ex;	Bx=1;	$E0=Ex;								/*	_+|$	*/	\
									}																				\
			}	}	while( $a< $za );																			\
		if(	SvIOK( *pSv ) ){				if(	zc==7 ){											*( (ui64*)	$cube+1) = $E0;	*$pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	pSv0=AvARRAY( $avICE );	/* push new cube		*/	\
																				$pk=$cube+1;	*( (ui64*) $cube ) =0;													/* reset cube buffer	*/	\
													reICE0(	Ax,			Bx,		$cube,$pq );  						/* encode x in cyclum 0	*/	\
										}else{		reICE(	Ax,			Bx,		$pk,  $pq );  						/* encode x in cyclum zc */	\
											}												*( (ui64*)	$cube+1 ) =x+1;	*$pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	pSv0=AvARRAY( $avICE );	/* push new cube		*/	\
		}				}


#define NEW( $E0 )															pSv0=AvARRAY( avICE );	\
	*( (ui64*) 		buf		)=0;											\
	*( (ui64*) 		buf+1	)=0;	pk =buf;	pq =buf +16;		a=0; 	E_=0;	\
	AvEXT(  avICE,	buf,			pk,		pq,		avArg,	a, za,	E_ 		);

#define ENDO( $E0 )														\
	if( dsc || rSeqIns[0] || rSeqCut[0] )	_reseqence(2);					else		pSv0=AvARRAY( avICE );	\
	*( (ui64*)			buf		)=0;											\
	*( (ui64*)			buf+1	)=0;	pk =buf;	pq =buf +16;						\
	AvEXT(  avICE,	buf,			pk,		pq,		avArg,	a, za,	$E0		);

#define ENDOcp( $E0 )														\
	if( dsc || rSeqIns[0] || rSeqCut[0] )	_reseqence(3);					else		pSv0=AvARRAY( avICE );	\
	*( (ui64*)			buf		)=0;											\
	*( (ui64*)			buf+1	)=0;	pk =buf;	pq =buf +16;				E_=$E0;	\
	AvEXT(  avICE,	buf,			pk,		pq,		avArg,	a, za,	E_		);










#define AvINIT1( $av)			if( !AvALLOC( $av ) || AvMAX( $av )<=0 ) 	av_extend( $av, 0);							\
							AvFILLp( $av)=0;

#define AvINSERT1( $av, $I )			displacement = 1+AvFILLp( $av ) -i;										\
							if(	displacement <0 ){					/* not that much array */		\
								displacement =0;												\
								if (!AvALLOC( $av ) )	av_extend( $av , 0);								\
								}															\
							/* push up or down? */												\
							if ( $I< displacement && 1 <= AvARRAY( $av ) - AvALLOC( $av ) ){	/*slide left*/		\
								if( $I) {														\
									src = AvARRAY( $av );											\
									dst = src	-1;												\
									Move(src, dst, $I, SV*);										\
									}														\
								--AvARRAY( $av );												\
								++AvMAX( $av );													\
								++AvFILLp( $av );													\
							}else{											/*slide right*/		\
								if (AvFILLp( $av )	+1 >= AvMAX( $av ) )	av_extend( $av ,	AvFILLp( $av ) +1);		\
																		++AvFILLp( $av );			\
								if( displacement ){												\
									dst = AvARRAY( $av ) + AvFILLp( $av );								\
									src = dst	-1;												\
									while(displacement--)	*dst-- = *src--;						\
								}	}

#define AvINSERT( $av, $I, $N){		displacement = 1+AvFILLp( $av) -$I;										\
							if(	displacement< 0 ){						/*	extend empty array		*/	\
								if (!AvALLOC( $av) )	av_extend( $av, $N -1);								\
							\
							}else if (	$I < displacement	&&				/*	lower elements shift down	*/	\
									$N <= AvARRAY( $av) - AvALLOC( $av) ){								\
								if( $I) {																\
									src = AvARRAY( $av);												\
									dst = src	-$N;														\
									Move(src, dst, $I, SV*);												\
									}																\
								AvARRAY(	$av) +=$N;												\
								AvMAX(		$av) -=$N;												\
							}else{									/*	higher elements shift up 	*/	\
								if (AvFILLp( $av) +$N >=AvMAX( $av) ) av_extend( $av,  AvFILLp( $av) +$N);		\
								if( displacement ){														\
									src = AvARRAY( $av) + AvFILLp( $av);									\
									dst = src +$N;														\
									while(displacement--)	*dst-- = *src--;								\
							}	}	}										AvFILLp( $av)+=$N

#define AvDELETE( $av, $I, $N)	displacement = 1+AvFILLp( $av) -$I -$N;										\
							for( i= $I; i <$N; ++i)	SvREFCNT_dec( *( AvARRAY( $av) +i	) );					\
							if ($I <displacement) {	pSv	= AvARRAY( $av);	/*	lower elements shift up		*/	\
								if( $I>0){		src=	pSv +$I -1;											\
										dst=	src +$N;													\
									while(	src >pSv )	*dst--	= *src--;								\
														*dst--	= *src;								\
								}else	dst=	pSv +$N -1;												\
								while(	dst >pSv )		*dst--	= NULL;								\
														*dst  	= NULL;								\
								AvARRAY(	$av) +=$N;												\
								AvMAX(		$av) -=$N;												\
							}else{									/*	higher elements shift down */	\
												pSv	= AvARRAY( $av) +AvFILLp( $av);					\
								if (displacement) {	dst	= AvARRAY( $av) +$I;							\
											src=	dst +$N;											\
									while(	src <pSv )	*dst++	= *src++;							\
														*dst++ 	= *src;							\
								}else	dst	= AvARRAY( $av) +$I +$N -1;								\
								while(	dst <pSv )		*dst++	= NULL;							\
														*dst 	= NULL;							\
								}AvFILLp( $av) -=$N
#define AvDELETE1( $av, $I ) 	displacement = /* 1+ */ AvFILLp( $av) -$I /* -$N */;							\
						/*	for( i= $I; i <$N; ++i)	SvREFCNT_dec( *( AvARRAY( $av) +i	) );	*/			\
						/*~*/					SvREFCNT_dec( *( AvARRAY( $av) +$I	) );				\
							if ($I <displacement) {	pSv	= AvARRAY( $av);	/*	lower elements shift up	*/	\
								if( $I>0){		src=	pSv +$I -1;										\
						/*				dst=	src +$N;					*/							\
						/*~*/			dst=	src +1;												\
									while(	src >pSv )	*dst--	= *src--;							\
														*dst--	= *src;							\
								}else	dst=	pSv/* +$N -1 */;										\
								while(	dst >pSv )		*dst--	= NULL;							\
														*dst  	= NULL;							\
							++	AvARRAY(	$av)/* +=$N*/;										\
							--	AvMAX(		$av)/* -=$N*/;										\
							}else{									/* higher elements shift down */	\
												pSv	= AvARRAY( $av) +AvFILLp( $av);					\
								if (displacement) {	dst	= AvARRAY( $av) +$I;							\
						/*					src=	dst +$N;				*/							\
						/*~*/				src=	dst +1;											\
									while(	src <pSv )	*dst++	= *src++;							\
														*dst++ 	= *src;							\
						/*		}else	dst	= AvARRAY( $av) +$I +$N -1;	*/							\
						/*~*/	}else	dst	= AvARRAY( $av) +$I;									\
								while(	dst <pSv )		*dst++	= NULL;							\
														*dst 	= NULL;							\
						/*		}AvFILLp( $av) -=$N					*/							\
						/*~*/	}--AvFILLp( $av);

#define _deICE(  	$cube, $CS, $K, $pq, $q, $A, $B )	\
			f = $K >>6;					\
	switch(	f){							\
		case 0x0:	$q=	0;											$A= $K &7;			$B =( $K >>3) &7; /*	$pq+=0;	*/	break;	\
		case 0x1:	$q=	1 +($K		&7);					    CASTq2i(	$A, $pq, $q);			$B =( $K >>3) &7;		$pq+=$q; 	break;	\
		case 0x2:	$q=	1 +( ($K >>3)	&7);								$A= $K &7;	CASTq2i(	$B, $pq, $q);			$pq+=$q; 	break;	\
		case 0x3:	q0=	1 +($K		&7);					    CASTq2i(	$A, $pq, q0);													\
					q1=	1 +( ($K >>3)	&7);																							\
					$q=	q0 +q1; 			$pq+=$q;									rCASTq2i( $B, $pq, q1);								\
		}
#define _deICE0(	$cube, $CS, $K, $pq, $q, $A, $B )	\
			f = $K >>6;					\
	switch(	f ){							\
		case 0x0:	$q=	0;				$pq =$cube +16;    				$A= $K &7;			$B =( $K >>3) &7;					break;	\
		case 0x1:	$q=	1 +($K		&7);	$pq =$cube +16 +$q;	rCASTq2i( $A, $pq, $q);			$B =( $K >>3) &7;					break;	\
		case 0x2:	$q=	1 +( ($K >>3)	&7);	$pq =$cube +16 +$q;			$A= $K &7;	rCASTq2i( $B, $pq, $q);						break;	\
		case 0x3:	q0=	1 +($K		&7);	$pq =$cube +16;   		CASTq2i(	$A, $pq, q0);													\
					q1=	1 +( ($K >>3)	&7);																							\
					$q=	q0 +q1; 			$pq+=$q;									rCASTq2i( $B, $pq, q1);								\
		}
#define _deICEz(	$cube, $CS, $K, $pq, $q, $A, $B )	\
			f = $K >>6;					$pq=$cube +$CS;	\
	switch(	f ){							\
		case 0x0:	$q=	0;											$A= $K &7;			$B =( $K >>3) &7;					break;	\
		case 0x1:	$q=	1 +($K		&7);						rCASTq2i( $A, $pq, $q);			$B =( $K >>3) &7;					break;	\
		case 0x2:	$q=	1 +( ($K >>3)	&7);								$A= $K &7;	rCASTq2i( $B, $pq, $q);						break;	\
		case 0x3:	q0=	1 +($K		&7);																							\
					q1=	1 +( ($K >>3)	&7);											rCASTq2i( $B, $pq, q1);								\
					$q=	q0 +q1; 			_pq=$pq -$q;			CASTq2i( $A, _pq, q0);													\
		}
#define _deICEr(	$cube, $CS, $K, $pq, $q, $A, $B )						if( ic==0)	printf("\r!	STEPb on step 0 of cube %d\n\t", iC);						\
			f = $K >>6;					$pq-=$q;				/*	Each keybyte defines [A, B] for a single cyclum;  			*/				\
	switch(	f ){												/*	either literally (if q<8) or as "q" byte[s] starting at *p.   	*/				\
		case 0x0:	$q=	0;											$A= $K &7;			$B =( $K >>3) &7;					break;	\
		case 0x1:	$q=	1 +($K		&7);						CASTq2i(	$A, $pq, $q);			$B =( $K >>3) &7;					break;	\
		case 0x2:	$q=	1 +( ($K >>3)	&7);								$A= $K &7;	rCASTq2i( $B, $pq, $q );						break;	\
		case 0x3:	q1=	1 +( ($K >>3)	&7);											rCASTq2i( $B, $pq, q1 );								\
					q0=	1 +($K		&7);		  																					\
					$q=	q0 +q1; 			_pq=$pq -$q;			CASTq2i(	$A, )pq, q0);													\
		}

#define deICE(  	$q, $A, $B	) _deICE(  		cube, 	CS,	Ki,	pq,		$q,		$A,		$B		)
#define deICE0(	$q, $A, $B	) _deICE0(		cube, 	CS,	Ki,	pq,		$q,		$A,		$B		)
#define deICEz(	$q, $A, $B	) _deICEz(		cube, 	CS,	Ki,	pq,		$q,		$A,		$B		)
#define deICEb(	$q, $A, $B	) _deICEr(		cube, 	CS,	Ki,	pq,		$q,		$A,		$B		)

#define deICE_(  	$q, $A, $B	) _deICE(  		cube_,	CS_, Ki,	pq_,		$q,		$A,		$B		)
#define deICE0_(	$q, $A, $B	) _deICE0(		cube_,	CS_, Ki,	pq_,		$q,		$A,		$B		)
#define deICEz_(	$q, $A, $B	) _deICEz(		cube_,	CS_, Ki,	pq_,		$q,		$A,		$B		)
#define deICEb_(	$q, $A, $B	) _deICEr(		cube_,	CS_, Ki,	pq_,		$q,		$A,		$B		)


#define _DeICEu( 	$cube, $CS, $K, $u, $v )					Hx[$u]=$K;	/*<-- these (2) assignments are for temp. debug */\
			f = $K >>6;								\
	switch(	f){										\
		case 0:	Q[$u]=0;				O[$v] =O[$u];									A[$u]= $K &7;					B[$u] =( $K >>3) &7;			break;	\
		case 1:	Q[$u]=1+	( $K		&7);	O[$v] =O[$u] +Q[$u];	_pq=$cube +O[$u]; CASTq2i(	A[$u], _pq, Q[$u] );				B[$u] =( $K >>3) &7;			break;	\
		case 2:	Q[$u]=1+	(($K>>3)	&7);	O[$v] =O[$u] +Q[$u];	_pq=$cube +O[$u];			A[$u]= $K &7;		CASTq2i(		B[$u], _pq, Q[$u] );				break;	\
		case 3:	q0	= 1+	( $K		&7);						_pq=$cube +O[$u] +q0;																		\
				q1	= 1+	(($K>>3)	&7);										rCASTq2i( A[$u], _pq, q0 );	CASTq2i(		B[$u], _pq, q1	);						\
				Q[$u] =q0 +q1; 		O[$v] =O[$u] +Q[$u];																							\
		}
#define _DeICEv( 	$cube, $CS, $K, $u, $v )	w = $v+1;		Hx[$v]=$K;	/*<-- these (2) assignments are for temp. debug */\
			f = $K >>6;								\
	switch(	f){										\
		case 0:	Q[$v]=0;				O[w] =O[$v];									A[$v]= $K &7;					B[$v] =( $K >>3) &7;			break;	\
		case 1:	Q[$v]=1+	( $K		&7);	O[w] =O[$v] +Q[$v];	_pq=$cube+O[$v];	CASTq2i(	A[$v], _pq, Q[$v] );				B[$v] =( $K >>3) &7;			break;	\
		case 2:	Q[$v]=1+	(($K>>3)	&7);	O[w] =O[$v] +Q[$v];	_pq=$cube+O[$v];			A[$v]= $K &7;		CASTq2i(		B[$v], _pq, Q[$v] );				break;	\
		case 3:	q0	= 1+	( $K		&7);						_pq=$cube+O[$v] +q0;																		\
				q1	= 1+	(($K>>3)	&7);										rCASTq2i( A[$v], _pq, q0 );	CASTq2i(		B[$v], _pq, q1	);						\
				Q[$v] =q0 +q1; 		O[w] =O[$v] +Q[$v];																							\
		}
#define _DeICE0u(	$cube, $CS, $K, $u, $v )					Hx[$u]=$K;	/*<-- these (2) assignments are for temp. debug */\
			f = $K >>6;				O[$u] =16;		\
	switch(	f ){										\
		case 0:	Q[$u]=0;				O[$v] =16;    									A[$u]= $K &7;					B[$u] =( $K >>3) &7;			break;	\
		case 1:	Q[$u]=1+	( $K		&7);	O[$v] =16 +Q[$u];		_pq=$cube+16;	CASTq2i(	A[$u], _pq, Q[$u] );				B[$u] =( $K >>3) &7;			break;	\
		case 2:	Q[$u]=1+	(($K>>3)	&7);	O[$v] =16 +Q[$u];		_pq=$cube+16;			A[$u]= $K &7;		CASTq2i(		B[$u], _pq, Q[$u] );				break;	\
		case 3:	q0	=1+	( $K		&7);				  		_pq=$cube+16 +q0;																		\
				q1	=1+	(($K>>3)	&7);										rCASTq2i( A[$u], _pq, q0 );	CASTq2i(		B[$u], _pq, q1	);						\
				Q[$u] =q0 +q1; 		O[$v] =16 +Q[$u];																								\
		}
#define _DeICE0v(	$cube, $CS, $K, $u, $v )	w = $v+1;		Hx[$v]=$K;	/*<-- these (2) assignments are for temp. debug */\
			f = $K >>6;				O[$v] =16;		\
	switch(	f ){										\
		case 0:	Q[$v]=0;				O[w] =16;    									A[$v]= $K &7;					B[$v] =( $K >>3) &7;			break;	\
		case 1:	Q[$v]=1+	( $K		&7);	O[w] =16 +Q[$v];		_pq=$cube+16;	CASTq2i( 	A[$v], _pq, Q[$v]);				B[$v] =( $K >>3) &7;			break;	\
		case 2:	Q[$v]=1+	(($K>>3)	&7);	O[w] =16 +Q[$v];		_pq=$cube+16;			A[$v]= $K &7;		CASTq2i(		B[$v], _pq, Q[$v] );				break;	\
		case 3:	q0	=1+	( $K		&7);				 		_pq=$cube+16 +q0;																		\
				q1	=1+	(($K>>3)	&7);										rCASTq2i( A[$v], _pq, q0);	CASTq2i(		B[$v], _pq, q1 );						\
				Q[$v] =q0 +q1; 		O[w] =16 +Q[$v];																								\
		}
#define _DeICEzu(	$cube, $CS, $K, $u		)				Hx[$u]=$K;	/*<-- these (2) assignments are for temp. debug */\
			f = $K >>6;								\
	switch(	f ){										\
		case 0:	Q[$u]=0;				O[$u]=$CS;			pqz=$cube+O[$u];			A[$u]= $K &7;					B[$u] =( $K >>3) &7;			break;	\
		case 1:	Q[$u]=1+	( $K		&7);	O[$u]=$CS -Q[$u];		pqz=$cube+O[$u];	CASTq2i( A[$u], pqz, Q[$u] );				B[$u] =( $K >>3) &7;			break;	\
		case 2:	Q[$u]=1+	(($K>>3)	&7);	O[$u]=$CS -Q[$u];		pqz=$cube+O[$u];			A[$u]= $K &7;		CASTq2i(		B[$u], pqz, Q[$u] );				break;	\
		case 3:	q0    =1+	( $K		&7);																												\
				q1    =1+	(($K>>3)	&7);																												\
				Q[$u] =q0 +q1; 		O[$u]=$CS -Q[$u];		pqz=$cube+O[$u];	CASTq2i( A[$u], pqz, q0 );pqz+=q0;	CASTq2i(	B[$u], pqz , q1);						\
		}

#define DeICEu(		$u,	$v	) _DeICEu(  	cube, 	CS,	Ki,		$u,	$v	);
#define DeICEv(		$u,	$v	) _DeICEv(  	cube, 	CS,	Ki,		$u,	$v	);
#define DeICE0u(		$u,	$v	) _DeICE0u(	cube, 	CS,	Ki,		$u,	$v	);	//pk =cube;
#define DeICE0v(		$u,	$v	) _DeICE0v(	cube, 	CS,	Ki,		$u,	$v	);	pk =cube;
#define DeICEzu(		$u		) _DeICEzu(	cube, 	CS,	Ki,		$u		);	pkz =cube +zc;	F[ $u ]=ok;

#define DeICEu_(		$u,	$v	) _DeICEu(  	cube_, 	CS_,	Ki,		$u,	$v	);
#define DeICEv_(		$u,	$v	) _DeICEv(  	cube_, 	CS_,	Ki,		$u,	$v	);
#define DeICE0u_(		$u,	$v	) _DeICE0u(	cube_, 	CS_,	Ki,		$u,	$v	);	pk_ =cube_;
#define DeICE0v_(		$u,	$v	) _DeICE0v(	cube_, 	CS_,	Ki,		$u,	$v	);	pk_ =cube_;
#define DeICEzu_(		$u		) _DeICEzu(	cube_, 	CS_,	Ki,		$u		);	pkz =cube_ +zc_;

#define DeICEv_E(		$u,	$v	)					DeICEv(	$u,	$v	);	F[ $v ]=ok;	E[$v] =A[$v] +B[$v] +E[$u];
#define DeICEu_K(		$u,	$v	) Ki = cube[ ++ic	];	DeICEu(	$u,	$v	);	F[ $u ]=ok;
#define DeICEv_K(		$u,	$v	) Ki = cube[ ++ic	];	DeICEv(	$u,	$v	);	F[ $v ]=ok;
#define DeICEv_KI(	$u,	$v	) Ki = cube[ ++ic	];	DeICEv(	$u,	$v	);	F[ $v ]=ok;							I[ $v ] =ic;
#define DeICEv_KE(	$u,	$v	) Ki = cube[ ++ic	];	DeICEv(	$u,	$v	);	F[ $v ]=ok;	E[$v] =A[$v] +B[$v] +E[$u];
#define DeICEv_KEI(	$u,	$v	) Ki = cube[ ++ic	];	DeICEv(	$u,	$v	);	F[ $v ]=ok;	E[$v] =A[$v] +B[$v] +E[$u];	I[ $v ] =ic;
#define DeICE0u_K(	$u,	$v	) Ki = cube[ ic=0	];	DeICE0u(	$u,	$v	);	F[ $u ]=ok;	
#define DeICE0v_K(	$u,	$v	) Ki = cube[ ic=0	];	DeICE0v(	$u,	$v	);	F[ $v ]=ok;	
#define DeICE0v_KE(	$u,	$v	) Ki = cube[ ic=0	];	DeICE0v(	$u,	$v	);	F[ $v ]=ok;	E[$v] =A[$v] +B[$v] +E[$u];
#define DeICEzu_K(	$u,	$v	) Ki = cube[ ic=zc	];	DeICEzu(	$u		);				
#define DeICEzu_KE(	$u,	$v	) Ki = cube[ ic=zc	];	DeICEzu(	$u		);				E[$v] =A[$v] +B[$v] +E[$u];

#define DeICEzu_K_(	$u,	$v	) Ki = cube_[ zc_	];	DeICEzu_( $u		);				
#define DeICEzu_KE_(	$u,	$v	) Ki = cube_[ zc_	];	DeICEzu_( $u		);				E[$v] =A[$v] +B[$v] +E[$u];




#define deICEk(	$q, $A, $B	) ++ic;	Ki = cube[ ic ];	deICE(	$q,		$A,		$B);
#define deICEe(	$q, $A, $B, $E	)					deICE(	$q,		$A,		$B);				$E +=$A +$B;
#define deICEke(	$q, $A, $B, $E	) ++ic;	Ki = cube[ ic ];	deICE(	$q,		$A,		$B);				$E +=$A +$B;
#define deICE0k(	$q, $A, $B	) ic =0;	Ki = cube[ 0 ]; 	deICE0(	$q,		$A,		$B);							/*pk = cube;*/
#define deICE0ke(	$q, $A, $B, $E	) ic =0;	Ki = cube[ 0 ]; 	deICE0(	$q,		$A,		$B);				$E +=$A +$B;	/*pk = cube;*/
#define deICEzk(	$q, $A, $B	) ic =zc;	Ki = cube[ zc ];	deICEz(	$q,		$A,		$B);							pk = cube +zc;
#define deICEbk(	$q, $A, $B	) --ic;	Ki = cube[ ic ];	deICEb(	$q,		$A,		$B);							--pk;

#define						OVERSTEP( $q,	$A,	$B,	$E,	$F)		ic=zc; 								\
										$A=						0xFFFFFFFFFFFFFFFF -$E;		$F= over;		\
								$q=0;	$B=0;			$E=		0xFFFFFFFFFFFFFFFF;
/*								^		^ 				^								^ flag the error state.
								Set		|				* E (or "Epsilon") is the absolute value which bounds the cyclum.
								field		|				   Past end of the avICE, the maximum integer is the final frontier.
								lengths	* A and B are the relative phase values (negative and positive, respectively).
								to null.	   These define a logical cyclum.
								This is	   To set the negative phase value to the maximum integer minus Epsilon
								a fake	   and to make the positive value null, is to set a false point at infinity (practically)
								data	   so that any accessor functions which actually attempt to operate on this over-cyclum
								point.	   will not generate garbage output.
*/
#define mxOVERSTEP( $v )		OVERSTEP( Q[$v], A[$v], B[$v], E[$v], F[$v] );




#define MkIn( $mx0 )				\
	if(	mx0==0xFF)	mx0= $mx0;		\
	else{																	\
		printf( lightning );														\
		printf("\n!	 ^MkIn( %d )	cube%-3d: %3d..%-3d\n\t\t	matrix : %3d..%-3d	!	already marked in!\n\n",	\
					$mx0,		iC,		mc0, mcZ,		mx0, mxZ		);	\
		}

#define MkOut( $v, $ic ) 	mxZ = $v;	mcZ = $ic;	\
						mxE = $v +1;	mcE = $ic +1;


/*		ENDOLOC		/*	Vector (U) low-bounds mod scope of x as cyclum (zc) at end of cube iC				*/
#define	ENDOLOC		/*	Vector (U) low-bounds mod scope of x as cyclum (zc) at end of cube iC				*/	\
		_init_mx();					post_zc= 0;	zc_ = zIndexOf(  	*( (ui64*) cube_ ) );							\
		Ki = cube_[ zc_];		DeICEzu_(   	255		);		E[ 255 ] =	*( (ui64*) cube_+1 );						/*	printf(	"\r........ENDOLOC        	cubes %3lld..%-3lld\t\tx( %5llu )\t	cube E( %5llu )		CS: %lld	sv( %llx )		cube_E( %5llu )	CS_: %lld	sv_( %llx )	\n\t",	*/\
																										/*								iC,	iC+1,		x,			*( (ui64*) cube+1),	CS,		&*sv,		*( (ui64*) cube_+1),	CS_,		&*sv_		 );		*/\

/*		INTERLOC			Vector (V) high-bounds mod scope of x as cyclum (0) at start of cube iC+1				*/
#define	INTERLOC		/*	Vector (V) high-bounds mod scope of x as cyclum (0) at start of cube iC+1				*/	\
	CS = SvCUR(	sv );					post_zc= 		zc = zIndexOf(  	*( (ui64*) cube ) );							\
	u=0; v=1; Ki = cube[ 0];		DeICE0u(   	0,	1	);		E[ 0 ] =	*( (ui64*) cube_+1 )	+A[0] +B[0];				/*	printf(	"\r........INTERLOC       	cubes %3lld..%-3lld\t\tx( %5llu )\t	cube E( %5llu )		CS: %lld	sv( %llx )		cube_E( %5llu )	CS_: %lld	sv_( %llx )	\n\t",	*/\
	I[0] =mc0 =ic =0;										F[ 0  ]= mod;										/*								iC,	iC+1,		x,			*( (ui64*) cube+1),	CS,		&*sv,		*( (ui64*) cube_+1),	CS_,		&*sv_		 );		*/\

/*		INTRALOC			Vectors (U, V) scan cube iC					tracking reset						*/
#define	INTRALOC		/*	Vectors (U, V) intralocate mod scope of x as cycla (ic-1, ic) in cube iC					*/	/*	printf(	"\r........INTRALOC       	cube %3lld		x( %5llu )		cube E( %5llu )		CS: %lld	sv( %llx )\n\t",	*/\
	_init_mx();		CS=SvCUR(	sv );																		/*								iC,				x,			*( (ui64*) cube+1),	CS,		&*sv );		*/\
	u=0; v=1; 				DeICE0u_K(	0,	1 );															\
	if(			iC==0)									E[ 0 ] = 					 A[ 0 ] +B[ 0 ];				\
	else{ sv_=	iC==1	? *( AvARRAY( avICE)		)														\
						: *( AvARRAY( avICE) +( iC -1 ) );														\
		cube_= SvPVbyte_nolen(	sv_ );						/*	printf(".");*/								\
					CS_ =SvCUR(	sv );							/*	printf("%c", 181);*/							\
														E[ 0 ] =	*( (ui64*)	cube_+1)	+A[ 0 ] +B[ 0 ]; 			\
		}							post_zc= 		zc=zIndexOf(		*( (ui64*)	cube ) );							\
	while( x >E[ u ] ){			DeICEv_KI(	u,	v	);		E[ v ] =	E[ u ]			+A[ v ] +B[ v ];  u=v++; }		\
	I[ u] =mc0 =ic;

/*		INTRALOC1Up		Vectors (U, V) intralocate mod scope of x as cycla (ic-1, ic) in cube iC+1				*/
#define	INTRALOC1Up	/*	Vectors (U, V) intralocate mod scope of x as cycla (ic-1, ic) in cube iC+1				*/	/*	printf("\r........INTRALOC1Up    	cube %3lld+1		x( %5llu )		cube E( %5llu )		CS: %lld	sv( %llx )\n\t",	*/\
	_init_mx();																							/*								iC,				x,			*( (ui64*) cube+1),	CS,		&*sv );		*/\
	u=0;  v=1;											Ev =		*( (ui64*) cube +1);							\
	if( zC  ==	iC){		CS =SvCUR(	sv );				ENDO(	Ev );								return dBUGr;		\
	}else{ cube_=cube;	CS_=SvCUR(	sv );	sv_=sv;  		zc_=zIndexOf(		*( (ui64*) cube_ ) );							\
		  cube = SvPVbyte_nolen( 	sv =*( pSv0 + ++iC ));			/*	printf(".");*/								\
					CS =SvCUR(	sv );							/*	printf("%c", 198);*/							\
									post_zc= 		zc=zIndexOf(		*( (ui64*) cube ) );							\
							DeICE0u_K(	0, 	1	);		E[ 0 ] = 	Ev				+A[ 0 ] +B[ 0 ];				\
		while( x >E[ u ] ){		DeICEv_KI(	u,	v	);		E[ v ] =	E[ u ]			+A[ v ] +B[ v ];  u=v++; }		\
		I[ u] =mc0 =ic;			\
		}


/*		ReINTRALOC			Vectors (U, V) intralocate mod scope of next x as cycla (ic-1, ic) in following cube (++iC)	*/
#define	ReINTRALOC		/*	Vectors (U, V) intralocate mod scope of next x as cycla (ic-1, ic) in following cube (++iC)	*/	/*	printf("\r........ReINTRALOC    	cube %3lld  		x( %5llu )		cube E( %5llu )		CS: %lld	sv( %llx )\n\t",	*/\
	_init_mx();																							/*								iC,				x,			*( (ui64*) cube+1),	CS,		&*sv );		*/\
	u=0; v=1; 				DeICE0u_K(	0,	1 );			E[ 0 ] =	*( (ui64*)	cube_+1)	+A[ 0 ] +B[ 0 ]; 			\
									post_zc=		zc=zIndexOf(		*( (ui64*)	cube ) );							\
	while( x >E[ u ] ){			DeICEv_KI(	u,	v	);		E[ v ] =	E[ u ]			+A[ v ] +B[ v ];  u=v++; }		\
	I[ u] =mc0 =ic;

/*		CoINTRALOC			Vectors (U, V) intralocate mod scope of next x as cycla (ic-1, ic) in current cube (iC)		*/
#define	CoINTRALOC		/*	Vectors (U, V) intralocate mod scope of next x as cycla (ic-1, ic) in current cube (iC)		*/	/*	printf("\r........CoINTRALOC     	cube %3lld		x( %5llu )		cube E( %5llu )		CS: %lld	sv( %llx )	path: ",	*/\
																										/*								iC,				x,			*( (ui64*) cube+1),	CS,		&*sv );		*/\
	/*	>	It is given that x is less-than the Epsilon value of the cube, or INTERLOC would have fired instead.		
			Therefore, as long as x >E[ u ], we cannot overrun the cube.											
																									
		>	On the basis that an inclusion op can only modify up to two steps (u, v) at a time,						
			we only re-encode the inversion cycle if it is within (2) steps of where we started;				
			if x is greater-than E[ v ], there is no chance of an incident realignment since those cycla are unaltered.		*/	\
	if(							x >E[ u ]	){																\
		/* mx range starts.	*/																			\
		if( mx0==0xFF){																					\
			if(		F[ v ]&mod )	{MkIn( u );			ReICEuO(  u, v );											/*	printf("1\n");	*/\
						while (	x >E[ v ] ){	u=v++;	ReICEuOx( u, v );						DeICEv_KEI( u, v );	}	\
			}else if(	F[ u ]&mod )	{MkIn( u );			ReICEuO( u, v );		if( F[ v ] == null )	deIceV_KEI();			/*	printf("2\n");	*/\
						while (	x >E[ v ] ){	u=v++;	ReICEuOx( u, v );						DeICEv_KEI( u, v );	}	\
			}else{									/*_O[v]=_O[u]+Q[u];*/	if( F[ v ] == null )	deIceV_KEI();			/*	printf("3\n");	*/\
						while (	x >E[ v ] ){	u=v++;	/*_O[v]=_O[u]+Q[u];*/					DeICEv_KEI( u, v );	}	mc0 =ic; \
				}																						\
		/* mx range continues.	*/\
		}else if(		F[ v ]&mod )	{					ReICEuOx( u, v );											/*	printf("4\n");	*/\
						while (	x >E[ v ] ){	u=v++;	ReICEuOx( u, v );						DeICEv_KEI( u, v );	}	\
		}else if(		F[ u ]&mod )	{					ReICEuOx( u, v );		if( F[ v ] == null )	deIceV_KEI();			/*	printf("5\n");	*/\
						while (	x >E[ v ] ){	u=v++;	ReICEuOx( u, v );						DeICEv_KEI( u, v );	}	\
		}else					{					_O[v]=_O[u]+Q[u];		if( F[ v ] == null )	deIceV_KEI();			/*	printf("6\n");	*/\
						while (	x >E[ v ] ){	u=v++;	_O[v]=_O[u]+Q[u];						DeICEv_KEI( u, v );	}	\
		} u=v++;					}																	/*	else		printf("7 (dwell)	A[u]: %4lld	B[u]=%4lld\n", A[u], B[u] );	*/



/*		EXTRICATE			Envelop the grouping of modified cycla in cube iC and call _rack() to re-encode the SV[s]	*/
#define	EXTRICATE		/*	Envelop the grouping of modified cycla in cube iC and call _rack() to re-encode the SV[s]	*/	/*	printf(	"\r........EXTRICATE         	cube %3lld		x( %5llu )		cube E( %5llu )		CS: %lld	sv( %llx )	path: ",	*/\
																										/*								iC,				x,			*( (ui64*) cube+1),	CS,		&*sv );		*/\
	if( mx0==0xFF ){	/* envelope not marked in yet 	*/														\
		if(			F[ v ]&mod )	{MkIn( u );			ReICEuO( u, v );	u=v++; ReICEuOx( u, v );	MkOut( u, ic );	_rack(100);	/*	printf("1\n");	*/\
		}else if(		F[ u ]&mod )	{MkIn( u );			ReICEuO( u, v );							MkOut( u, ic );	_rack(101);	/*	printf("2\n");	*/\
		}else		/* no mods */	{ /* shunt pointers	*/	cube_= cube; CS_=CS; sv_=sv; zc_= zc;			/* nothing to rack */		/*	printf("3\n");	*/\
								}					\
	}else if(			F[ v ]&mod )	{					ReICEuOx( u, v );	u=v++; ReICEuOx( u, v );	MkOut( u, ic );	_rack(102);	/*	printf("4\n");	*/\
	}else if(			F[ u ]&mod )	{					ReICEuOx( u, v );							MkOut( u, ic );	_rack(103);	/*	printf("5\n");	*/\
	}else						{					_O[v]=_O[u] +Q[u];							MkOut( u, ic );	_rack(104);	/*	printf("6\n");	*/\
								}



#define kUNiSTEP(  $cube, $uK, $Qu, $Au, $Bu,	$vK, $Qv, $Av, $Bv,	$Fv	)	\
				Ki = cube[ ++ic ];		\
			f =	Ki >>6;				\
	switch(	f){						\
		case 0x0:	$Qv= 0;						 $Av =Ki &7;		if( $Av <2 ){					$Bu+=1+( ( Ki >>3) &7 );			   ++	$uK; 				}						\
																else{  --$Av;					$Bv = 1+( ( Ki >>3) &7 );				$vK=1;	$Fv=mod;	}/*	pq+=0;	*/	break;	\
		case 0x1:	$Qv= 1 +(Ki		&7);	  CASTq2i( $Av, pq, $Qv );								$Bv = 1+( ( Ki >>3) &7 );				$vK=1;	$Fv=mod;		pq+=$Qv;	break;	\
																																										\
		case 0x2:	$Qv= 1 +( (Ki >>3)	&7);			 $Av =Ki &7;		if( $Av <2 ){	CASTq2i_plus1inc(	$Bu, pq, $Qv );	$Qu += $Qv;	   ++	$uK; 				}						\
																else{  --$Av;	CASTq2i_plus1(	$Bv, pq, $Qv );					$vK=1;	$Fv=mod;	}	pq+=$Qv;	break;	\
		case 0x3:	$Qv= 1 +(Ki		&7);	  CASTq2i( $Av, pq, $Qv);																											\
					q2=    1 +( (Ki >>3)	&7);				pq+=$Qv;				CASTq2i_plus1(	$Bv, pq, q2 );		$Qv+= q2;		$vK=1;	$Fv=mod;		pq+=q2;				\
		}



















#define 	FRAG_LoC_8p1 \
/*	FRAGMENT CUBE [FROM LEFT OR CENTER]	*/																		\
/*	A cube can contain up to (8) cycla, but now we have (1 +8).
	Fragment the unmodified cube at its medial cyclum [3] by:
		> copying the unmodified pre-medial data (cycla [1..3] ) to the buffer, to be cycla [2..4] of the lower fragment;
		> creating a new SV* from the buffered data and prepending it to AV* avICE, as the lower fragment;
		> trimming the lower cycla [0..3] off of the original cube in-situ, to transform it into the higher fragment.
	*/\
	*( (ui64*) buf) &= 0x000000FFFFFFFFFF;		/*	Mask off the upper (24) bits of the keybyte section of the buffer				
											to erase the upper (3) keys.											*/	\
	pq_	=pq;								/*	Copy the q pointer where we left off reading char* cube, to be an iterator.	*/	\
	while( ic<3){ deICEke( Qv, Av, Bv, Ev ); }	/*	Read ahead to find the medial cyclum of the pre-modifed cube.				*/	\
	oq0	=pq -cube;						/*	Find the q offset to the medial cyclum.	For use with sv_insert().				*/	\
	*pEx = Ev;							/*	Set the Epsilon value of the lower cube fragment to match the medial cyclum. 	*/	\
	BUF( pq_, pq);							/*	Append the pre-medial q-data to the buffer.							*/	\
						oqx= pqx -buf;	/*	Find the q offset where we left off buffering data. 						*/	\
	svLbf = newSVpvn( buf,	oqx );			/*	Create a new SV* cube from the data in the buffer.						*/	\
		   ++	rel_iC;						/*	increment rel_iC once to account for the new SV* lower cube fragment		*/	\
	if(		rel_iC >0 ){	AvINSERT( avICE, 0, rel_iC	);	}															\
	else if(	rel_iC <0 ){	AvDELETE( avICE, 0, -rel_iC	);	}															\
	*AvARRAY( avICE )=svLbf;																						\
/*	This concludes structuring the data for the lower fragment, and prepending it to AV* avICE as a new SV*.
	Now, we delete the lower (4) cycla of the original cube to transform it into the upper cube fragment.
	*/\
	sv_insert( sv, 16, oq0 -16, "", 0);			/*	Erase all q data before oq0, shifting trailing data down.					*/	\
	*( (ui64*) cube ) >>=32					/*	Right-shift the key-byte section by (32) bits to erase the lower (4) keys.		*/



