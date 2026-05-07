
/*	THE (3) LEVELS Of DEBUG:
	L1:	audit nominal activity
	L2:	audit nominal activity (more verbosely)
	L3:	silently check integrity, reporting only errors
	*/

	#define DEBUG_RACK_L0
//	#define DEBUG_RACK_L1
//	#define DEBUG_RACK_L2
//	#define DEBUG_RACK_L3
//	#define DEBUG_ReSEQ_L1
//	#define DEBUG_ReSEQ_L2
//	#define DEBUG_ReSEQ_L3
//	#define DEBUG_SET_L1
//	#define DEBUG_SET_L2
//	#define DEBUG_SET_L3
//	#define DEBUG_TRUTH_L1
//	#define DEBUG_TRUTH_L3


#if	defined( DEBUG_RACK_L1)	||	defined( DEBUG_RACK_L2) 	||	defined( DEBUG_RACK_L3)	\
||	defined( DEBUG_ReSEQ_L1)	||	defined( DEBUG_ReSEQ_L2)	||	defined( DEBUG_ReSEQ_L3)	\
||	defined( DEBUG_SET_L1)	||	defined( DEBUG_SET_L2)	||	defined( DEBUG_SET_L3)	\
||	defined( DEBUG_TRUTH_L1)	||	defined( DEBUG_TRUTH_L2)	||	defined( DEBUG_TRUTH_L3)
	#define	DEBUG
	#define	dBUGavCLR	av_clear( avDBUG );
#else
	#define	dBUGavCLR
#endif
//	#define	AvPUSHaSTRING( $str, $len )	av_push( avDBUG, newSVpvn( $str, $len ) );
	#define	AvPUSHaSTRING( $str, $len )	printf( $str );