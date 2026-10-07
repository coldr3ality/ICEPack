#include	"_ICE.h"
#include	"_AvSEQ.h"
#include "access.h"	
#include "access_extern.h"


extern ui64 const	unit0x3[		32 ],	unit0x7[		22 ],		unit0xF[		16 ],
				hmask0x3[	32 ],	hmask0x7[	22 ],		hmask0xF[	16 ];


#ifdef DEBUG_ACCESS_L2X			//	audit nominal activity
	#define OpVn		cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	=|== 	null boundary between cubes %lld, %lld	line %d\n\t", a, x, x, iC-1, iC, __LINE__ );	 AvDBUG_PUSH( aString, cS );
	#define OpV0		cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	=+|_ 	line %d\n\t", a, x, x, __LINE__  );	 AvDBUG_PUSH( aString, cS );
	#define OpV1		cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	!|+= 	line %d\n\t", a, x, x, __LINE__  );	 AvDBUG_PUSH( aString, cS );
	#define OpV2		cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	=|+= 	line %d\n\t", a, x, x, __LINE__  );	 AvDBUG_PUSH( aString, cS );
	#define OpV3		cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	=>|_ 	line %d\n\t", a, x, x, __LINE__  );	 AvDBUG_PUSH( aString, cS );
	#define OpV4		cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	=>|= 	line %d\n\t", a, x, x, __LINE__  );	 AvDBUG_PUSH( aString, cS );
	#define OpV5		cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	=>|$ 	line %d\n\t", a, x, x, __LINE__  );	 AvDBUG_PUSH( aString, cS );
	#define OpV9		cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	_>|$ 	line %d\n\t", a, x, x, __LINE__  );	 AvDBUG_PUSH( aString, cS );

	#define OpVt		cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	=+_= 	line %d\n\t", a, x, x, __LINE__  );	 AvDBUG_PUSH( aString, cS );
	#define OpVt0	cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	=+== 	line %d\n\t", a, x, x, __LINE__  );	 AvDBUG_PUSH( aString, cS );
	#define OpV6		cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	_+_  	line %d	icI..icO: %d..%d \n\t", a, x, x, __LINE__ , I[ixM], icO);	 AvDBUG_PUSH( aString, cS );
	#define OpV7		cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	_+=  	line %d\n\t", a, x, x, __LINE__  );	 AvDBUG_PUSH( aString, cS );
	#define OpV8		cS=sprintf(aString, "\r_vec_add:	x[%lld]: %lld ( 0x%llX )	===  	line %d\n\t", a, x, x, __LINE__  );	AvDBUG_PUSH( aString, cS );

	#define OpVu		cS=sprintf(aString, "\rvec_add:	x[%lld]: %lld ( 0x%llX )	_>=  	line %d\n\t", a, x, x, __LINE__  );	AvDBUG_PUSH( aString, cS );
	#define OpVtu	cS=sprintf(aString, "\rvec_add:	x[%lld]: %lld ( 0x%llX )	=>=  	line %d\n\t", a, x, x, __LINE__  );	AvDBUG_PUSH( aString, cS );

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
	#define OpVt
	#define OpVt0
	#define OpV6
	#define OpV7
	#define OpV8

	#define OpVu
	#define OpVtu
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
	#define dBUGvMax	cS=sprintf(aString, "\r!	sweep vector field 0x%llX..0x%llX  is maxed out, line %d\n", x00, xFF, __LINE__ );	 AvDBUG_PUSH( aString, cS );
#else
	#define Op9
	#define dBUGvMax
#endif
