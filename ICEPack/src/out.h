#define	cui8	const	unsigned	char	
#define	ui08			unsigned	char	
#define	ui16			unsigned	short 
#define	ui32		long	unsigned	int 
#define	si64	long long			int 
#define	ui64	long long	unsigned	int 
#define	ui64	long long	unsigned	int 

	#include	"_ICE.h"

#define	ARG( $a )	SvIVX( *(	pSvA0 + $a )	)
#define	ARG0		SvIVX( *	pSvA0		)

#define	zcOf( $a)	7-( 	__builtin_clzll( $a)	>>3)
#define	ncOf( $a)	8-( 	__builtin_clzll( $a)	>>3)


extern AV	*	avOut,
			*	avDBUG,
			*	avICE,
			*	avArg;		extern long long int	a, za; 					//	a list of integer value[s] to operate on.
extern char		aString[];
