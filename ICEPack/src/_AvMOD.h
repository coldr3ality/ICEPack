// These macros have been adapted from Perl 5.32's sv.c, I believe, and all credit goes where it is due.

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

