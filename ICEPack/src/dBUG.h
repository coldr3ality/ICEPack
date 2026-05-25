
/*	THE (3) LEVELS Of DEBUG:
	L1:	audit nominal activity
	L2:	audit nominal activity (more verbosely)
	L3:	silently check integrity, reporting only errors
	*/

/*	WARNING.  Most of these log new SV's to AV* avDBUG, causing memory runaway.
	It helps to use the version of "AvDBUG_PUSH" which just prints to screen, but it's much slower.
	*/
#define DEBUG_STDOUT
	
//	#define DEBUG_SvCOMMIT_L0
//	#define DEBUG_SvCOMMIT_L1
//	#define DEBUG_SvCOMMIT_L2
//	#define DEBUG_SvCOMMIT_L3
	//	#define DEBUG_SvCOMMIT_L4	// mining for 1F4 triggers
//	#define DEBUG_AvCOMMIT_L1
//	#define DEBUG_AvCOMMIT_L2
//	#define DEBUG_AvCOMMIT_L3
//	#define DEBUG_ACCESS_L1
//	#define DEBUG_ACCESS_L2
//	#define DEBUG_ACCESS_L3
//	#define DEBUG_TRUTH_L1
//	#define DEBUG_TRUTH_L3


#if	defined( DEBUG_SvCOMMIT_L1)	||	defined( DEBUG_SvCOMMIT_L2) 	||	defined( DEBUG_SvCOMMIT_L3)	||	defined( DEBUG_SvCOMMIT_L4)	\
||	defined( DEBUG_AvCOMMIT_L1)	||	defined( DEBUG_AvCOMMIT_L2)	||	defined( DEBUG_AvCOMMIT_L3)	\
||	defined( DEBUG_ACCESS_L1)	||	defined( DEBUG_ACCESS_L2)	||	defined( DEBUG_ACCESS_L3)	\
||	defined( DEBUG_TRUTH_L1)		||	defined( DEBUG_TRUTH_L2)	||	defined( DEBUG_TRUTH_L3)
	#define		DEBUG
	#define		dBUGavCLR		av_clear( avDBUG );	

	#ifdef		DEBUG_STDOUT
		#define	AvDBUG_PUSH(			$str, $len	)	printf( $str );
		#define	AvDBUG_RESERVATION(	$str, $len, $i )	printf( $str );
	#else
		#define	AvDBUG_PUSH(			$str, $len )	av_push( avDBUG, newSVpvn( $str, $len ) );
		#define	AvDBUG_RESERVATION(	$str, $len, $i )	SvREFCNT_inc( *( AvARRAY( avDBUG) +$i ) =newSVpvn( $str, $len ) );
	#endif
#else		/*	DEBUG DISABLED							*/
	#define		AvDBUG_PUSH( $str, $len )	printf( $str );
	#define		AvDBUG_RESERVATION(	$str, $len, $i )	printf( $str );
	#define		dBUGavCLR	/*	av_clear( avDBUG );	*/
#endif