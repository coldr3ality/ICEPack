#include	"_ICE.h"
extern char	* cube_err[],
			* svtype_err,
			* malloc_err,
			* usage_err[];
extern AV	*	avDBUG;	extern long long int	zd;
extern AV	*	avICE;		extern long long int	iC, iCI, iCO, post_C, zC, zzC, rel_iC, less_iC;  	//	iC is the index of the current cube.  zC is the array index of the ending cube.
extern AV	*	avArg;		extern long long int	a, za; 					//	a list of integer value[s] to operate on.
extern char		aString[];
extern void		deIce_vKEI();
extern STRLEN	cS, CS;
extern ui08		nube[	16];