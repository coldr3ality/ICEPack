#include	"_ICE.h"
#include	"_AvSEQ.h"
#include "access.h"	
#include "access_extern.h"

#define RT	printf("\r	return at line %d\n\n\n", __LINE__ );
#define GI	printf("\ngoto _inter	line %d\n", __LINE__ );
#define GE	printf("\ngoto _epi		line %d\n", __LINE__ );
#define GS	printf("\ngoto _search	line %d\n", __LINE__ );
#define GL	printf("\ngoto _loca 	line %d\n", __LINE__ );
#define GA	printf("\ngoto _ante	line %d\n", __LINE__ );
#define AL	printf("\ngoto _anteloc	line %d\n", __LINE__ );
#define GIa	printf("\ngoto _intra	line %d\n", __LINE__ );

#ifdef DEBUG_ACCESS_L2X			//	audit logical operations
	#define OpS1		cS=sprintf(aString, "\r_>_-_<_	x[%lld]: %lld ( 0x%llX )	_>_-_<_	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
	#define OpS2		cS=sprintf(aString, "\r_>-_<_	x[%lld]: %lld ( 0x%llX )	_>-_<_	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
	#define OpS3		cS=sprintf(aString, "\r_>_<_	x[%lld]: %lld ( 0x%llX )	_>_<_	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
	#define OpS4		cS=sprintf(aString, "\r_->_<_	x[%lld]: %lld ( 0x%llX )	_->_<_	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
	#define OpS5		cS=sprintf(aString, "\r_->-_<_	x[%lld]: %lld ( 0x%llX )	_->-_<_	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );

	#define OpSz1	cS=sprintf(aString, "\r_>_-_<$	x[%lld]: %lld ( 0x%llX )	_>_-_<$	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
	#define OpSz2	cS=sprintf(aString, "\r_>-_<$	x[%lld]: %lld ( 0x%llX )	_>-_<$	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
	#define OpSz3	cS=sprintf(aString, "\r_>_<$	x[%lld]: %lld ( 0x%llX )	_>_<$	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
	#define OpSz4	cS=sprintf(aString, "\r_->_<$	x[%lld]: %lld ( 0x%llX )	_->_<$	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
	#define OpSz5	cS=sprintf(aString, "\r_->-_<$	x[%lld]: %lld ( 0x%llX )	_->-_<$	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );

	#define OpS6		cS=sprintf(aString, "\r_->_<- 	x[%lld]: %lld ( 0x%llX )	_->_<-	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
	#define OpS7		cS=sprintf(aString, "\r_->-_<-	x[%lld]: %lld ( 0x%llX )	_->-_<-	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
	#define OpS8		cS=sprintf(aString, "\r_>-_<-	x[%lld]: %lld ( 0x%llX )	_>-_<-	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
	#define OpS9		cS=sprintf(aString, "\r_>_<-	x[%lld]: %lld ( 0x%llX )	_>_<-	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
	#define OpS10	cS=sprintf(aString, "\r_>_-_<-	x[%lld]: %lld ( 0x%llX )	_>_-_<-	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );

	#define OpS11	cS=sprintf(aString, "\r->_-_<- 	x[%lld]: %lld ( 0x%llX )	->_-_<-	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
	#define OpS12	cS=sprintf(aString, "\r->-__<- 	x[%lld]: %lld ( 0x%llX )	->-__<-	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
	#define OpS13	cS=sprintf(aString, "\r->___<-	x[%lld]: %lld ( 0x%llX )	->___<-	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );

	#define OpS14
	#define OpS15
	#define OpS16
	#define OpSx
	#define OpSz11
	#define OpSz14
	#define OpSz15
#else
	#define OpS1
	#define OpS2
	#define OpS3
	#define OpS4
	#define OpS5

	#define OpSz1
	#define OpSz2
	#define OpSz3
	#define OpSz4
	#define OpSz5

	#define OpS6
	#define OpS7
	#define OpS8
	#define OpS9
	#define OpS10

	#define OpS11
	#define OpS12
	#define OpS13
	#define OpS14
	#define OpS15
	#define OpS16
	#define OpSx

	#define OpSz11
	#define OpSz14
	#define OpSz15
#endif