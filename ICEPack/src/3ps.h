#define	cui8	const	unsigned	char	
#define	ui08			unsigned	char	
#define	ui16			unsigned	short 
#define	ui32		long	unsigned	int 
#define	si64	long long			int 
#define	ui64	long long	unsigned	int 
#define	ui64	long long	unsigned	int 

	#include	"_ICE.h"

#define	ARG( $a )	SvIVX( *(	psvA0 + $a )	)
#define	ARG0		SvIVX( *	psvA0		)

extern char	* cube_err[],
			* svtype_err,
			* malloc_err,
			* usage_err[];
extern AV	*	avDBUG;	extern long long int	zd;
extern AV	*	avICE;		extern long long int	iC, iCI, iCO, iCx, post_C, zC, zzC, post_zC, rel_iC, less_iC;  	//	iC is the index of the current cube.  zC is the array index of the ending cube.
extern AV	*	avArg;		extern long long int	a, za; 					//	a list of integer value[s] to operate on.
extern char		aString[];
extern void		deIceV_KEI();
extern STRLEN	cS, CS;
