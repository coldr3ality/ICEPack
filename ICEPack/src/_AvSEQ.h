#include "dBUG.h"
extern SV	*	rSeq_SV[	256 ]; 	// temporary holding of SV* cubes pending insertion into AV* avICE
extern long long int	rSeq_iR[	256	], iR,	// source index of rSeq_SV 				(for each control point)
				rSeqIns[	256	],	// the number of trailing SVs to insert		(for each control point)
				rSeqCut[	256	],	// the number of leading SVs to remove 	(for each control point)
				rSeqSrc[	256	],	// source index						(for each control point)
				rSeqDst[	256	],	// destination index						(for each control point)
	/*	rel_zC, */	dsc, /* asc, zsc, dial, jmp, */
				rack_iC;			// running control point iterator

#if defined(DEBUG_ReSEQ_L1)
	#define dBUG_SvINS(		$iC, $sv )		cS=sprintf(aString, "\r%c	in splice #%d:	insert SV#%-2lld to %lld %+lld %+lld (%lld)\t\n",	241,	dsc, iR,	$iC,		rel_iC,  rSeqIns[ dsc ],	$iC+rel_iC+rSeqIns[ dsc ]	);	AvPUSHdBUG( aString, cS );
	#define dBUG_SvCUT(		$iC, $sv )		cS=sprintf(aString, "\r%c	in splice #%d:	delete SV     at %lld %+lld (%lld)\n",			241,	dsc, 	$iC,		rel_iC,				$iC+rel_iC			);	AvPUSHdBUG( aString, cS );
	#define dBUG_SvReCUT(	$iC, $sv )		cS=sprintf(aString, "\r%c	in splice #%d:	delete SV before %lld %+d (%lld-1)\n",			241,	dsc, 	$iC,		rel_iC,				$iC+rel_iC			);	AvPUSHdBUG( aString, cS );
#else
	#define dBUG_SvINS(		$iC, $sv )
	#define dBUG_SvCUT(		$iC, $sv )
	#define dBUG_SvReCUT(	$iC, $sv )
#endif

#define	AvPOST( $iC, $sv )																			\
		if(	rack_iC == $iC ){							++	rSeqIns[ dsc ];								\
		}else{	rSeq_iR[	dsc ]	=	iR;															\
				rSeqSrc[	dsc ]	=	rack_iC;		rel_iC -=					rSeqCut[ dsc ];			\
				rSeqDst[	dsc ]	=	rack_iC 	+	rel_iC;											\
												rel_iC +=	rSeqIns[ dsc ];								\
/* new step	*/		++	dsc;			rack_iC = $iC;			rSeqIns[ dsc ]=1;	rSeqCut[ dsc ] = 0;			\
			}	rSeq_SV[ ++iR ]=$sv;																dBUG_SvINS( $iC, $sv )


#define	AvCUT(	$iC )			SvREFCNT_dec(*( pSv0+$iC ) );	/* automatically increments iC			*/	\
		if(	rack_iC == $iC	){											++	rSeqCut[ dsc ];			\
		}else{	rSeq_iR[	dsc ]	=	iR;															\
				rSeqSrc[	dsc ]	=	rack_iC;		rel_iC -=					rSeqCut[ dsc ];			\
				rSeqDst[	dsc ]	=	rack_iC 	+	rel_iC;											\
												rel_iC +=	rSeqIns[ dsc ];								\
/* new step	*/		++	dsc;								rSeqIns[ dsc ]=0;	rSeqCut[ dsc ] = 1;			\
			}						rack_iC = ++$iC;												dBUG_SvCUT( $iC, $sv )


#define	AvCUT_B4( $iC )		SvREFCNT_dec(*( pSv0+$iC-1 ) );	/* assumes iC is incremented already		*/	\
		if(	rack_iC == $iC-1 ){											++	rSeqCut[ dsc ];			\
		}else{	rSeq_iR[	dsc ]	=	iR;															\
				rSeqSrc[	dsc ]	=	rack_iC;		rel_iC -=					rSeqCut[ dsc ];			\
				rSeqDst[	dsc ]	=	rack_iC 	+	rel_iC;											\
												rel_iC +=	rSeqIns[ dsc ];								\
/* new  step	*/		++	dsc;								rSeqIns[ dsc ]=0;	rSeqCut[ dsc ] = 1;			\
			}						rack_iC = $iC;													dBUG_SvReCUT( $iC, $sv )
