#include "_AvMOD.h"
#include	"_ICE.h"

extern ui08	ixOmax, ixOmin, ixImax, ixImin;
extern ui08	range[24][2];

extern HV	*	hvICE,
			*	hvArg,
			*	hvOut;
extern AV	*	avOut,
			*	avDBUG;	extern long long int	zd;
extern AV	*	avICE;		extern long long int	iC, iCI, iCO, iCx, post_C, zC, zzC, post_zC, rel_iC, less_iC;  	//	iC is the index of the current cube.  zC is the array index of the ending cube.
extern AV	*	avICE_;		extern long long int	zCs;
extern AV	*	avArg;		extern long long int	a, za; 					//	a list of integer value[s] to operate on.
extern SV	*	rvOut,				/*	arrayref to AV* avOut									*/
			*	rvArg,				/*	arrayref to AV* avArg									*/
			*	rvICE,				/*	arrayref to AV* avICE									*/
			*	rvICE_,				/*	arrayref to AV* avICE_									*/
			**	src,
			**	dst,
			**	pSv0;
extern long long int	displacement;
extern ui08		*pk,		*pq,
			/*	*pkz, */	*pqz,
				*pk_,	*pq_,	
			/*	*pkx, */	*pqx,
				q, q0, q1,		/*	q-field lengths, used generically	*/
				buf[];
extern const ui08	nube[16];		/*	null cube / new cube			*/
extern char		aString[],	ic, zc;
extern void		_icepack_init(),
				_toText(),
				_set8x(),
				_printHex( 	SV* rvICE);
extern	SV	*	toHex(		SV* rvICE);
extern bool		_checks(),
				_has(),
				_clears(),
				_fits(),
				_strikes();
extern ui64		x, y, z,				/*	common method arguments													*/
				Ac, Bc, Ec, E_,
				skip, hit, miss;			/*	the number of misses or collissions counted as a method processes arguments  		*/
