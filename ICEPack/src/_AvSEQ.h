#include "dBUG.h"
extern SV	*	rSeq_SV[	512 ]; 	// temporary holding of SV* cubes pending insertion into AV* avICE
extern long long int	rSeq_iR[	512	], iR,	// source index of rSeq_SV 				(for each control point)
				rSeqIns[	512	],	// the number of trailing SVs to insert		(for each control point)
				rSeqCut[	512	],	// the number of leading SVs to remove 	(for each control point)
				rSeqSrc[	512	],	// source index						(for each control point)
				rSeqDst[	512	],	// destination index						(for each control point)
				dsc, /* asc, zsc, juke, pmo, */
				rel_iC,
				cut_iC,
				step_iC;			// running control point iterator

#if defined(DEBUG_AvCOMMIT_L1)
	#define dBUG_AvPOST(		$iC,	$sv	)	cS=sprintf(aString, "\r%c	insert SV#%-6lld after #%3lld  (%+3lld %+3lld: %3lld)		in splice step %d \n",	241,	iR,		$iC, rel_iC, rSeqIns[ dsc ],    	$iC+rel_iC+rSeqIns[ dsc ],		dsc );	AvDBUG_PUSH( aString, cS );
	#define dBUG_AvCUT(		$iC		)	cS=sprintf(aString, "\r%c	delete ( 1)SV 	 before %3lld (%3lld )			\10	\10	in splice step %d \n",	241,			$iC,											$iC-1,	dsc );	AvDBUG_PUSH( aString, cS );
	#define dBUG_AvCUT2(		$iC,	$xC	)	cS=sprintf(aString, "\r%c	delete (%2d)SVs	 before %3lld (%3lld..%-3lld)			in splice step %d \n",	241,	$iC-$xC,	$iC,  					$xC,	      			$iC-1,	dsc );	AvDBUG_PUSH( aString, cS );
	#define dBUG_AvCUT2_xC(		$xC	)	cS=sprintf( aString, lightning ); cS+=sprintf( aString+cS, "\nAvCUT2: cannot delete elements less-than-or-equal-to last control index (xC: %lld ) < (step_iC: %lld).\n", $xC, step_iC ); AvDBUG_PUSH( aString, cS );
#else
	#define dBUG_AvPOST(		$iC,	$sv	)
	#define dBUG_AvCUT(		$iC		)
	#define dBUG_AvCUT2(		$iC,	$xC	)
	#define dBUG_AvCUT2_xC(		$xC	)
#endif

	#define dBUGdsc	if( dsc >=255 ){		cS=sprintf(aString, "\r	(dsc: %lld )>=255!\n",	dsc );	AvDBUG_PUSH( aString, cS );	}

#define	AvPOST( $iC, $sv )																			\
		if(	step_iC == $iC ){							++	rSeqIns[ dsc ];								\
		}else{	rSeq_iR[	dsc ]	=	iR;															\
				rSeqSrc[	dsc ]	=	step_iC;		rel_iC -=					rSeqCut[ dsc ];			\
				rSeqDst[	dsc ]	=	step_iC 	+	rel_iC;											\
												rel_iC +=	rSeqIns[ dsc ];								\
/* new step	*/		++	dsc;			step_iC = $iC;			rSeqIns[ dsc ]=1;	rSeqCut[ dsc ] = 0;			dBUGdsc;	\
			}	rSeq_SV[ ++iR ]=$sv;																dBUG_AvPOST( $iC, $sv )

#define	AvCUT( $iC )			SvREFCNT_dec(*( Aº+$iC-1 ) );	/* assumes iC is incremented already		*/	\
		if(	step_iC == $iC-1 ){											++	rSeqCut[ dsc ];			\
		}else{	rSeq_iR[	dsc ]	=	iR;															\
				rSeqSrc[	dsc ]	=	step_iC;		rel_iC -=					rSeqCut[ dsc ];			\
				rSeqDst[	dsc ]	=	step_iC 	+	rel_iC;											\
												rel_iC +=	rSeqIns[ dsc ];								\
/* new  step	*/		++	dsc;								rSeqIns[ dsc ]=0;	rSeqCut[ dsc ] = 1;			dBUGdsc;	\
			}						step_iC = $iC;													dBUG_AvCUT( $iC	);


#define	AvCUT2( $iC, $xC )									/*	$xC =$iC-$iCI;	*/						\
	if(		$xC<	$iC ){																		\
		if(	$xC<	step_iC )	{	dBUG_AvCUT2_xC( $xC );											\
			$xC=	step_iC;	}																	\
		if(		step_iC == $xC ){											rSeqCut[ dsc ]+= $iC-$xC;	\
		}else{ 	rSeq_iR[	dsc ]	=	iR;															\
				rSeqSrc[	dsc ]	=	step_iC;		rel_iC -=					rSeqCut[ dsc ];			\
				rSeqDst[	dsc ]	=	step_iC 	+	rel_iC;											\
												rel_iC +=	rSeqIns[ dsc ];								\
/* new  step	*/		++	dsc;								rSeqIns[ dsc ]=0;	rSeqCut[ dsc ] = $iC-$xC;	dBUGdsc;	\
			}						step_iC = $iC;													dBUG_AvCUT2( $iC, $xC	)	\
		do	{						/*	printf("\rAvCUT2: delete #%lld (\\w Edge: %016llX)   at %s line %d\n", $xC, *Edge( SvPVbyte_nolen( *( Aº+$xC ) ) ), __FILE__, __LINE__ );	*/	\
			SvREFCNT_dec(*( Aº+$xC ) );	++$xC;													\
			} while( $xC != $iC );																	\
		}
