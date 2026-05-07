#include "_AvMOD.h"
#include	"_ICE.h"

extern ui08	ixZmax, ixZmin, ix0max, ix0min;
extern ui08	range[24][2];

extern HV	*	hvICE,
			*	hvArg,
			*	hvOut;
extern AV	*	avOut,
			*	avDBUG;	extern long long int	zd;
extern AV	*	avICE;		extern long long int	iC, iC0, iCZ, iCx, post_C, zC, zzC, post_zC, rel_iC, less_iC;  	//	iC is the index of the current cube.  zC is the array index of the ending cube.
extern AV	*	avICE_;		extern long long int	zC_;
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
extern char		aString[],	ic, zc;
extern void		_icepack_init(),
				_toText(),
				_set8x();

extern bool		_checks(),
				_has(),
				_clears(),
				_fits(),
				_strikes();
extern ui64		x, y, z,				/*	common method arguments													*/
				Ac, Bc, Ec, E_,
				skip, hit, miss;			/*	the number of misses or collissions counted as a method processes arguments  		*/
