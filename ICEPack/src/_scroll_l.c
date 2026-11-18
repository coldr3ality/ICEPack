#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "dBUG.h"
#include "_scroll_l.h"

void _scroll_l_it(		ui64 _0, ui64 x00, ui64 x10, char *ctx ){	/*	left-shift the leading fill boundary captured by [x..y00-1] by s;	*/
	ui64	Cv;
	si64	Bu, q, a, b, D, d;	//I think these can be chars
	ui64		x;

	//First, cases with x10 interference.  All rare, but they don't care if RW[ v ]==null.
						d =	E[ u ]-x00 -B[ u ];
	if( x10 >=	E[ u ] ){						/*	pre-op run-length B[u] does not intersect upper boundary x10			*/
		if( RW[ v ]==null )	{	if(		ic != zc )	{								deIce_vKEI( u, v );
							}else if(	iC!=zC )	{	ReINTERLOC;		TRACK_iC;	DeICE0_vKEI(u,v);
/*	EOD CASES			*/	}else		/*	THERE IS NO VECTOR V - HIT END OF DATA (EOD)					*/
			{	if(		d>=0 ){			/*	pre-op run-length B[u] does not intersect lower boundary x00  (either)	*/
					if(	d>=_0 )		{	/*	post-op run-length B[u] is not shifted far enough to intersect x00 (still)	*/
/*	_>_-_<$	(no clip)	*/				OpSz1	E[ u ]-=_0;		A[ u ]-=_0;					uMOD
					}else{	q =_0 - d;
						if(	q< B[u] )	{	/*	post-op run-length B[u] DOES intersect x00; lower part is clipped		*/
/*	_>-__<$	(clipped)	*/				OpSz2	E[ u ]-=_0;		A[ u ]-=d;		B[ u ]-=q;			uMOD
						}else		{	/*	post-op run-length B[u] shifts past x00 entirely; post-op vector u is null	*/
/*	_>___<$	(floored) 	*/ --	xcª;			OpSz3	E[ u ]-=A[u]+B[u];								uNUL
						}			}
				}else if( x00!=E[ u ])	{		/*	pre-op run-length B[u] DOES intersect lower boundary x00				*/
							b=B[ u ]+d;	/*	b is the part of pre-op run-length B[u] which is above x00				*/
/*	->-__<$	(clipped)	*/	if(	b >_0)	{	/*	some of b will remain post-op (after shifting b left by _0)				*/
									OpSz4	E[ u ]-=_0;	/* no v @ EOD */	B[ u ]-=_0;		uMOD
/*	->___<$	(floored) 	*/	}else		{	/*	none of b will remain post-op, but b limits _0; we'll shift by b instead of _0	*/
									OpSz5	E[ u ]-= b;	/* no v @ EOD */	B[ u ]-= b;		uMOD
									}
				}else				{	/*	x00==E[ u ], so vector v is target— but there is no vector v at EOD		*/
					++	miss;		OpSx														RT	*ctx=0;	return;
									}															RT	*ctx=1;	return;
			}			}

/*	NORMAL CASES	*/					/*	"𝘋𝘰 𝘪𝘵 𝘵𝘩𝘦 𝘴𝘢𝘮𝘦, 𝘣𝘶𝘵, 𝘶𝘩, 𝘣𝘦𝘵𝘵𝘦𝘳."						—Bop-It Guy		*/
		if(				d>=0 ){			/*	pre-op run-length B[u] does not intersect lower boundary x00  (either)	*/
			if(			d>=_0 )		{	/*	post-op run-length B[u] is not shifted far enough to intersect x00 (still)	*/
/*	_>_-_<_	(no clip)	*/				OpS1	E[ u ]-=_0;		A[ u ]-=_0;					uvMOD
															A[ v ]+=_0;
			}else		{	q =_0 - d;  	/*	q is the post-op high side of run-length B[u], clipped by x00				*/
						if(	q< B[u] )	{	/*	post-op run-length B[u] intersects x00 and is partially clipped			*/
/*	_>-__<_	(clipped)	*/				OpS2	E[ u ]-=_0;		A[ u ]-=d;		B[ u ]-=q;			uvMOD
															A[ v ]+=_0;
						}else		{	/*	post-op run-length B[u] shifts past x00 entirely; vector u goes null		*/
/*	_>___<_	(floored)	*/				OpS3	E[ u ]=E[ v ];		A[u]+=B[u]+A[v]; B[ u ]=B[ v ];		uMOD
					--	xcª;																vNUL	O[v]=O[v+1];	L[v]=L[v+1];
						}			}
		}else if(		x00!=E[ u ])	{		/*	pre-op run-length B[u] DOES intersect lower boundary x00				*/
							b=B[ u ]+d;	/*	b is the part of pre-op run-length B[u] which is within x00..x0F			*/
						if(	b >_0 )	{	/*	some of b will remain post-op (after shifting left by _0)				*/
/*	->-__<_	(clipped)	*/				OpS4	E[ u ]-=_0;		A[ v ]+=_0;	B[ u ]-=_0;		uvMOD
						}else		{	/*	none of b will remain post-op, but b limits _0; we'll shift by b instead of _0	*/
/*	->___<_	(floored) 	*/				OpS5	E[ u ]=x00;		A[ v ]+= b;	B[ u ]= -d;		uvMOD
									}
		}else{			D =	E[ v ]-x10;	/*	(+D) is the part of pre-op vector v clipped by upper boundary x10		*/
			if(0< D ){		d =	B[ v ]-D;		/*	(+d) is the part of pre-op run-length B[v] which is within x00..x10 bounds	*/
				if( 0< d ){	q =	A[ v ]-_0;		/*	(-q) is the dif btw pre- and post-op B[v]								*/
					if( 0< q )			{	/*	(+q) is post-op pad-length A[v]; it implies vector v is split in two at x10	*/
									if(		ixM!=0xFF )	{				ReICEuOx(	u,	v );	}
									else if(	RW[u] >ok )	{		 MkIn;	ReICEuO(	u,	v );	}	u=v++;

/*	->_-_<-	*/		++	xcª;			OpS11	E[ u ]=x10-_0;		A[ u ]=q;		B[ u ]=d;			uMOD	O[v+1]=O[ v ];
															A[ v ]=_0;		B[ v ]=D;			vNEW	O[ v ]=O[ u ];	I[ v ] = I[ u ];	L[ v ]=0;
					}else if(	-q<	d )	{	/*	(-q+d) is post-op high part of pre-op low part of B[v], clipped twice now	*/
/*	->-__<- 	*/				q +=	d;	OpS12	E[ u ]+=q;						B[ u ]+=q;
															A[ v ]=_0;		B[ v ]=D;			uvMOD			
					}else			{	/*	there is no second clip; shifted part of B[v] disappears over x00 entirely	*/
/*	->___<-	*/						OpS13					A[ v ]+=d;	B[ v ]=D;			uvMOD
									}
				}else				{	/*	no part of pre-op run-length B[v] is within x00..x0F, so do nothing		*/
					++	miss;		OpSx													 	RT	*ctx=0;	return;
									}

			}else{						/*	(-D) may not measure anything useful, but it implies an ablative region.	*/
						q =	A[ v ]-_0;		/*	(+q) is post-op pad-length A[v]; it implies vector v is split in two at x10	*/
				if(	0<	q){				/*	vector v fragment will not shift left far enough to couple with vector u	*/
					if( ixM!=0xFF )		{									ReICEuOx(	u,	v );	}
					else if( RW[u] >ok )	{							 MkIn;	ReICEuO(	u,	v );	}	u=v++;
						
											E[ u ]-=_0;		A[ u ]=q;						uMOD
					if( RW[ v ]==null ){
						if(		ic != zc )	{								deIce_vKEI(	u, v );
						}else if(	iC != zC )	{		ReINTERLOC;	TRACK_iC;	DeICE0_vKEI(	u, v);
/*	_>_-<$	*/			}else		{
									OpSz14														RT	*ctx=1;	return;
/*	_>_-<_	*/			}			}
									OpS14					A[ v ]+=_0;					vMOD;
		
				}else	{	d =	B[ v ]+q;	/*	unite U and V or absorb V	*/				/*	vNUL */	
						if(0<	d ){				E[ u ]+=d;	     Cv =	A[ v ]	+d;	B[ u ]+=d;		uMOD
						}else						     Cv =	A[ v ]	+	B[ v ];
					--	xcª;	
						if(		ic != zc )	{								deIce_vKEI(	v, v );
						}else if(	iC != zC )	{		ReINTERLOC;	TRACK_iC;	DeICE0_vKEI(	v, v );
/*	->-<$ 	*/			}else		{
									OpSz15												vNUL	RT	*ctx=1;	return;
/*	-><_  	*/						}
									OpS15					A[ v ]+= Cv;					vMOD	O[v]=O[v+1];	L[v]=L[v+1];
			}	}		}
	}else{				D =	E[ u ]-x10;	//	"upper boundary x10 intersects with vector u"
		if(		B[ u ] >	D ){			Bu = B[ u ]-D;
			if(	0	>	d ){	q = _0 -	Bu;					//	"if lower boundary x00 cuts off part of vector u from the left"
/*	-><-		*/	if(		d<=	q )	{	OpS6	E[ u ]=x10-A[ v ];				B[ u ] =-d;		uMOD	//	"if the middle part of vector u captured by [x00..x10-1] will shift left far enough to be erased"
											E[ v ]=E[ u ];		A[ v ]=Bu+d;	B[ v ] =D;			vMOD
/*	->-<-	*/	}else			{	OpS7	E[ u ] =x10 -A[ v ];				B[ u ] =-q;		uMOD	//	"the middle part of vector u captured by [x00..x10-1] will NOT shift left far enough to be erased"
											E[ v ] =E[ u ];		A[ v ]=_0;		B[ v ] =D;			vMOD
														/*	A[ v ]=Bu+q;*/	
								if( Bu+q  != _0 ){ printf( lightning); printf("\n Bu+q != _0 %s line %d\n\n", __FILE__, __LINE__ );	}
								}
			}else if(	_0 >	d ){	q=_0-d;
/*	_>-_<-	*/	if(	Bu >	q )	{	OpS8	E[ u ] =x10-_0;					B[ u ] =Bu-q;		uMOD	//	"if the lower part of vector u captured by [x00..x10-1] will not shift left far enough to be clipped by x00 entirely"
											E[ v ]=E[ u ];		A[ v ]=_0;		B[ v ] =D;			vMOD
/*	_>_<-	*/	}else			{	OpS9					A[ u ]+=Bu;	B[ u ] =D;			uMOD
								}
			}else				{	OpS10	E[ u ] =x10-_0;					B[ u ] =Bu;		uMOD	//	"if the lower part of vector u captured by [x00..x10-1] will NOT shift left far enough to be clipped by x00 at all"
/*	_>_-_<-	*/								E[ v ]=E[ u ];		A[ v ]=_0;		B[ v ] =D;			vMOD
								}
		}else{		++	miss;		OpSx	*ctx=0;	return;	//	"if no part of vector u is captured by x00..x0F, do nothing"
		}	}	/*					Op#	E []				A []			B []				RW []	O/I []		L []	*/
																								*ctx=1;	return;
/*	STOP	*/
/*	MAKING	*/
/*	THAT	*/
/*	BIG		*/
/*	FACE!!!	*/
	}


void	_lscroll(){																dBUGavCLR	dBUGinit_mx
	char ctx=0;
	ui64 x, x00, x0F, x__, _0;
	za =	AvFILLp(	avArg);								if( za ==-1)	/*	no args */		return;
	for( a=0; a<= za; ++a ){			x =	ARG( a );
						x00	=	x &	0xFFFFFFFFFFFFFFF8;
						x0F	=	x |	0x0000000000000007;
						x__ 	=	x &	0x0000000000000007;
		printf("\r%s:	_scroll_l_it(	_0: %d,	x00: 0x%llX,	x0F: 0x%llX,	&(ctx: %d) );\n",
			__FUNCTION__,		_0,		x00,			x0F,			ctx	);

		_scroll_l_it( 0, x00, x0F, &ctx );
		}								SvCOMMIT;
	if( dsc || rSeqIns[0] || rSeqCut[0] ) 		_av_commit();
	}
