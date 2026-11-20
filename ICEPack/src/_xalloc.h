#include	"_ICE.h"
#include	"_AvSEQ.h"
#include "access.h"	
#include "access_extern.h"


extern ui64 const	unit0x3[		32 ],	unit0x7[		22 ],		unit0xF[		16 ],
				hmask0x3[	32 ],	hmask0x7[	22 ],		hmask0xF[	16 ];

#define	dBUGvec_x( $x_origin, $ctx)	if( x >x0F ){ printf("\r!	new value for x breaches vector boundary ( 0x%llX+%d > 0x%llX)	%s line %d\n", 	\
																			$x_origin, _0+1,		x0F,		__FILE__, __LINE__ );	\
								*ctx = $ctx; return;	}
#define	dBUGvxSRCH			printf("\r	search line %d\n",					__LINE__ );
#define	dBUGvxINTER		printf("\r	_inter line %d\n",					__LINE__ );
#define	dBUGvxLOCA			printf("\r	_loca line %d\n",					__LINE__ );
#define	dBUGvxINTRA		printf("\n	_intra line %d	E[ %d ] ==%lld	\n",		__LINE__, u, E[u]);
#define	dBUGvxINTERnoINTRA	printf("\r	from _inter to _intra line %d\n",		__LINE__ );

#define	dBUGvec_ABS		printf("\r	b4 _abloc:	_v_search yields E[v]==%lld\n", 	E[v]	);
#define	dBUGvec_AB1Up   	printf("\r	b4 _abloc:	_v_1up yields E[v]==%lld\n",		E[v]	);
#define	dBUGvec_AB2Up   	printf("\r	b4 _abloc:	_v_2up returns 2\n"				);
#define	dBUGvec_ABprox   	printf("\r	b4 _abloc:	deIce_vKEI yields E[v]==%lld\n",	E[v]	);					\
		/*hax*/	}else{		printf("\n! cycle v non-null while locating opscope of vector field 0x%llX..0x%llX, line %d\n", x00, x0F, __LINE__ );	\
					}



#ifdef DEBUG_ACCESS_L0			//	audit nominal activity
	#define OpVn		cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	=|== 	null boundary between cubes %lld, %lld	line %d\n\t", a, x, x, iC-1, iC, __LINE__ );	 AvDBUG_PUSH( aString, cS );
	#define OpV0		cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	=+|_ 	line %d\n\t", a, x, x, __LINE__  );	 AvDBUG_PUSH( aString, cS );
	#define OpV1		cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	!|+= 	line %d\n\t", a, x, x, __LINE__  );	 AvDBUG_PUSH( aString, cS );
	#define OpV2		cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	=|+= 	line %d\n\t", a, x, x, __LINE__  );	 AvDBUG_PUSH( aString, cS );
	#define OpV3		cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	=>|_ 	line %d\n\t", a, x, x, __LINE__  );	 AvDBUG_PUSH( aString, cS );
	#define OpV4		cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	=>|= 	line %d\n\t", a, x, x, __LINE__  );	 AvDBUG_PUSH( aString, cS );
	#define OpV5		cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	=>|$ 	line %d\n\t", a, x, x, __LINE__  );	 AvDBUG_PUSH( aString, cS );
	#define OpV9		cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	_>|$ 	line %d\n\t", a, x, x, __LINE__  );	 AvDBUG_PUSH( aString, cS );

	#define OpT		cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	=+_= 	line %d\n\t", a, x, x, __LINE__  );	 AvDBUG_PUSH( aString, cS );
	#define OpT0  	cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	=+== 	line %d\n\t", a, x, x, __LINE__  );	 AvDBUG_PUSH( aString, cS );
	#define OpV6		cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	_+_  	line %d	icI..icO: %d..%d \n\t", a, x, x, __LINE__ , I[ixM], icO);	 AvDBUG_PUSH( aString, cS );
	#define OpV7		cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	_+=  	line %d\n\t", a, x, x, __LINE__  );	 AvDBUG_PUSH( aString, cS );
	#define OpV8		cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	===  	line %d\n\t", a, x, x, __LINE__  );	AvDBUG_PUSH( aString, cS );

	#define OpVu		cS=sprintf(aString, "\rvec_add:	x[%lld]: %lld ( 0x%llX )	_>=  	line %d\n\t", a, x, x, __LINE__  );	AvDBUG_PUSH( aString, cS );
	#define OpTu  	cS=sprintf(aString, "\rvec_add:	x[%lld]: %lld ( 0x%llX )	=>=  	line %d\n\t", a, x, x, __LINE__  );	AvDBUG_PUSH( aString, cS );

	#define OpV_uv	cS=sprintf(aString, 	"\rvec_add:	x[%lld]: %lld ( 0x%llX )	_>_=	line %d\n\t", a, x, x, __LINE__ );	AvDBUG_PUSH( aString, cS );
	#define OpV_u1	cS=sprintf(aString, 	"\rvec_add:	x[%lld]: %lld ( 0x%llX )	_>==  	line %d\n\t", a, x, x, __LINE__  );	AvDBUG_PUSH( aString, cS );
	#define OpV_u 	cS=sprintf(aString,	"\rvec_add:	x[%lld]: %lld ( 0x%llX )	_>=_	line %d\n\t", a, x, x, __LINE__ );	AvDBUG_PUSH( aString, cS );
	#define OpVuvw	cS=sprintf(aString,	"\rvec_add:	x[%lld]: %lld ( 0x%llX )	=>_= 	line %d\n\t", a, x, x, __LINE__ );	AvDBUG_PUSH( aString, cS );
	#define OpVuv1	cS=sprintf( aString,	"\rvec_add:	x[%lld]: %lld ( 0x%llX )	=>==	line %d\n\t", a, x, x, __LINE__ );	AvDBUG_PUSH( aString, cS );
	#define OpVuv  	cS=sprintf( aString,	"\rvec_add:	x[%lld]: %lld ( 0x%llX )	=_>=	line %d\n\t", a, x, x, __LINE__ );	AvDBUG_PUSH( aString, cS );
	#define OpV_t  	cS=sprintf( aString,	"\rvec_add:	x[%lld]: %lld ( 0x%llX )	_>=_	line %d\n\t", a, x, x, __LINE__ );	AvDBUG_PUSH( aString, cS );
	#define OpVv  	cS=sprintf( aString,	"\rvec_add:	x[%lld]: %lld ( 0x%llX )	=>=_	line %d\n\t", a, x, x, __LINE__ );	AvDBUG_PUSH( aString, cS );

	#define Op0		cS=sprintf(aString, "\r=+|_	x[%lld]: %lld ( 0x%llX )	=+|_ 	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
	#define Op1 		cS=sprintf(aString, "\r!|+=	x[%lld]: %lld ( 0x%llX )	!|+= 	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
	#define Op2		cS=sprintf(aString, "\r=|+=	x[%lld]: %lld ( 0x%llX )	=|+= 	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );


#else
	#define OpVn
	#define OpV0
	#define OpV1 
	#define OpV2
	#define OpV3
	#define OpV4
	#define OpV5
	#define OpV9
	#define OpT
	#define OpT0
	#define OpV6
	#define OpV7
	#define OpV8

	#define OpVu
	#define OpTu
	#define OpV_uv
	#define OpV_u1
	#define OpV_u
	#define OpVuvw
	#define OpVuv1
	#define OpVuv
	#define OpV_t
	#define OpVv

	#define Op0
	#define Op1
	#define Op2
#endif

#if defined( DEBUG_ACCESS_L1 ) || defined( DEBUG_ACCESS_L2 ) || defined( DEBUG_ACCESS_L2X ) || defined( $DEBUG_ACCESS_L3 )
	#define Op9			cS=sprintf(aString, "\r=|==	x[%lld]: %lld ( 0x%llX )	=|==  	\n\t", a, x, x );			AvDBUG_PUSH( aString, cS );
	#define dBUGvMax	cS=sprintf(aString, "\r!	xalloc vector field 0x%llX..0x%llX  is maxed out, line %d\n", x00, x0F, __LINE__ );	 AvDBUG_PUSH( aString, cS );
#else
	#define Op9
	#define dBUGvMax
#endif
