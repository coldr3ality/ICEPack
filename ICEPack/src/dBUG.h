
/*	THE (3) LEVELS Of DEBUG:
	L1:	audit nominal activity
	L2:	audit nominal activity (more verbosely)
	L3:	silently check integrity, reporting only errors
	*/

/*	WARNING.  Most of these log new SV's to AV* avDBUG, causing memory runaway.
	It helps to use the version of "AvPUSHdBUG" which just prints to screen, but it's much slower.
	*/

//	#define DEBUG_RACK_L0
//	#define DEBUG_RACK_L1
//	#define DEBUG_RACK_L2
//	#define DEBUG_RACK_L3
//	#define DEBUG_RACK_L4	// mining for 1F4 triggers
//	#define DEBUG_ReSEQ_L1
//	#define DEBUG_ReSEQ_L2
//	#define DEBUG_ReSEQ_L3
//	#define DEBUG_SET_L1
//	#define DEBUG_SET_L2
//	#define DEBUG_SET_L3
//	#define DEBUG_TRUTH_L1
//	#define DEBUG_TRUTH_L3


#if	defined( DEBUG_RACK_L1)	||	defined( DEBUG_RACK_L2) 	||	defined( DEBUG_RACK_L3)	||	defined( DEBUG_RACK_L4)	\
||	defined( DEBUG_ReSEQ_L1)	||	defined( DEBUG_ReSEQ_L2)	||	defined( DEBUG_ReSEQ_L3)	\
||	defined( DEBUG_SET_L1)	||	defined( DEBUG_SET_L2)	||	defined( DEBUG_SET_L3)	\
||	defined( DEBUG_TRUTH_L1)	||	defined( DEBUG_TRUTH_L2)	||	defined( DEBUG_TRUTH_L3)
	#define	DEBUG
	#define	dBUGavCLR	av_clear( avDBUG );
	#define	AvPUSHdBUG( $str, $len )	av_push( avDBUG, newSVpvn( $str, $len ) );
//	#define	AvPUSHdBUG( $str, $len )	printf( $str );
#else
	#define	dBUGavCLR
	#define	AvPUSHdBUG( $str, $len )	printf( $str );
#endif