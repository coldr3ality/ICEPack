	#include	"SwCASE_IC2AB_inc.h"
	#include	"SwCASE_IC2ABQ_inc.h"
	#include	"SwCASE_IC2ABQ_init16p.h"
//	#include	"SwCASE_IC2ABQ_vec.h"
	#include	"SwCASE_IC2ABQ_inc_vec.h"
	#include	"SwCASE_IC2ABQ_R2L.h"
	#include	"SwCASE_IC2ABQ_R2L_dec.h"
	#include	"SwCASE_IC2A1BQ_init16.h"
//	#include	"SwCASE_IC2A1BQ_vecx_incQ.h"
//	#include	"SwCASE_IC2Ape1B_incxQ.h"

	#include	"lluiCAST.h"

#define	cui8	const	unsigned	char	
#define	ui08			unsigned	char	
#define	si08					char	
#define	ui16			unsigned	short 
#define	ui32		long	unsigned	int 
#define	si64	long long			int 
#define	ui64	long long	unsigned	int 
#define	ui64	long long	unsigned	int 

#define	Edge(	$cube	) 	( (ui64*) $cube+1)
#define	EC(  	$iC 		) 	( (ui64*) SvPVbyte_nolen( *( Aº+ $iC ) )+1);

#define	zOf( 	$a)		7-( 	__builtin_clzll(			 $a		) >>3)
#define	zcOf(	$cube)	7-( 	__builtin_clzll( *( (ui64*)	$cube)	) >>3)
#define	ncOf(	$cube)	8-( 	__builtin_clzll( *( (ui64*)	$cube)	) >>3)

#define	ARG( $a )	SvIVX( *(	AvARRAY(	avArg)+ $a	) )
#define	ARG0		SvIVX( *	AvARRAY(	avArg)		)



#if defined( DEBUG_MOD_L3 )
	#define 	dBUG_ReICE($SUFFIX, $u )	if( O[ $u ]==0 ){ cS= sprintf( aString, "\n!	ReICE%s( ... ): mx step u does not seem to have been read-in (O[%d]==0)\n\n", $SUFFIX, $u );	AvDBUG_PUSH( aString, cS );	}
#else
	#define 	dBUG_ReICE($SUFFIX, $u )
#endif

#ifdef DEBUG_DeICE
	#define dBUG0_vKEI(	$NAME )	cS=sprintf( aString, "\r	%s(): I[ v: %d ]= ( oc: %d );	K[v]=0x%02X		( E[ v: %d ]: %llX )= ( A[v]: %d )+( B[v]: %d )+( E[ u: %d ]: %llX );	%s line %d\n", $NAME,			v, oc,	K[v],			v, E[v], A[v], B[v], u, E[u], __FILE__, __LINE__ ); AvDBUG_PUSH( aString, cS );
	#define dBUG0(		$NAME )	cS=sprintf( aString, "\r	%s		%s line %d \n", $NAME, __FILE__, __LINE__ );
	#define dBUG_vEI(		$NAME )	cS=sprintf( aString, "\r	%s(): u/v: %d/%d		\10	\10	( E[v]: %llX )= ( A[v]: %d )+( B[v]: %d )+( E[ u: %d ]: %llX );	I[ v ]= ( oc: %d ) +( ic: %d );	%s line %d\n", $NAME,	u, v,			E[v], A[v], B[v], u, E[u], I[v], oc, ic,	__FILE__, __LINE__ ); AvDBUG_PUSH( aString, cS );
	#define dBUG_vKEI(	$NAME )	cS=sprintf( aString, "\r	%s(): u/v: %d/%d	K[v]: %02X	( E[v]: %llX )= ( A[v]: %d )+( B[v]: %d )+( E[ u: %d ]: %llX );	I[ v ]= ( oc: %d ) +( ic: %d );	%s line %d\n", $NAME,	u, v,  K[v],	E[v], A[v], B[v], u, E[u], I[v], oc, ic,	__FILE__, __LINE__ ); AvDBUG_PUSH( aString, cS );
	#define dBUG(		$NAME )	cS=sprintf( aString, "\r	%s		%s line %d \n", $NAME, __FILE__, __LINE__ );
	#define	dBUG__DeICE0u(		$A, $B, $L )	cS=sprintf( aString, "\r_DeICE0u		A/B/Q: %d/%d/%d\n", $A, $B, $L ); AvDBUG_PUSH( aString, cS );
	#define	dBUG__DeICEv(		$A, $B, $L )	cS=sprintf( aString, "\r_DeICEv 		A/B/Q: %d/%d/%d\n", $A, $B, $L ); AvDBUG_PUSH( aString, cS );
	#define	dBUG__DeICEz(		$A, $B, $L )	cS=sprintf( aString, "\r_DeICEz 		A/B/Q: %d/%d/%d\n", $A, $B, $L ); AvDBUG_PUSH( aString, cS );\
											if( zc==-1 ){	cS = sprintf(aString, 	"\r! 	%s line %d: cube #%lld is empty.		\n",									__FILE__, __LINE__, iC				);	AvDBUG_PUSH( aString, cS );	}
	#define	dBUG__DeICE_vaInc(	$A, $B, $L )	cS=sprintf( aString, "\r_DeICE_vaInc 	A/B/Q: %d/%d/%d\n", $A, $B, $L ); AvDBUG_PUSH( aString, cS );
	#define	dBUG__DeICE0v(		$A, $B, $L )	cS=sprintf( aString, "\r_DeICE0v 		A/B/Q: %d/%d/%d\n", $A, $B, $L ); AvDBUG_PUSH( aString, cS );

	#define	dBUGz(		$NAME )		cS=sprintf( aString, "\r	%s		%s line %d \n", $NAME, __FILE__, __LINE__ );
	#define dBUG_deICE0(	$A, $B, $L )	STRLEN cS=sprintf( aString, "\r_deICE0 	A/B/Q: %d/%d/%d\n", $A, $B, $L ); AvDBUG_PUSH( aString, cS );
	#define dBUG_deICE(	$A, $B, $L )	STRLEN cS=sprintf( aString, "\r_deICE  	A/B/Q: %d/%d/%d\n", $A, $B, $L ); AvDBUG_PUSH( aString, cS );
	#define dBUG_deICEr(	$A, $B, $L )	STRLEN cS=sprintf( aString, "\r_deICEr 	A/B/Q: %d/%d/%d\n", $A, $B, $L ); AvDBUG_PUSH( aString, cS );

#else

	#define dBUG0_vKEI(	$NAME )
	#define dBUG0(		$NAME )
	#define	dBUG__DeICE0u(		$A, $B, $L )
	#define	dBUG__DeICEv(		$A, $B, $L )
	#define	dBUG__DeICEz(		$A, $B, $L )
	#define	dBUG__DeICE_vaInc(	$A, $B, $L )
	#define	dBUG__DeICE0v(		$A, $B, $L )

	#define	dBUGz(		$NAME )

	#define dBUG_vEI(		$NAME )
	#define dBUG_vKEI(	$NAME )
	#define dBUG(		$NAME )
	#define dBUG_deICE0(	$A, $B, $L )
	#define dBUG_deICE(	$A, $B, $L )
	#define dBUG_deICEr(	$A, $B, $L )

#endif



#define	ReICEuO(		$u, $v)			dBUG_ReICE("uO", $u );									Oª[$u] = O[$u];	\
	if( A[$u]< 8){	if( B[$u]< 8 ){	K[$u] =/*		0x00 |*/	(			B[$u]    << 3 ) |			A[$u];		Oª[$v] = O[$u];	L[$u]=0;			}	\
				else		{	K[$u] =  		0x80 |( (	q=zOf(		B[$u] ) )<< 3 ) |			A[$u];		Oª[$v] = O[$u] +(	L[$u]=1 +q		);	}	\
	}else{		if( B[$u]< 8 ){	K[$u] =  		0x40 |(				B[$u]    << 3 ) | ( q=zOf(  	A[$u] ) );		Oª[$v] = O[$u] +(	L[$u]=1 +q		);	}	\
				else		{	K[$u] =  		0xC0 |( (	q1=zOf(		B[$u] ) )<< 3 ) | ( q0=zOf(	A[$u] ) );		Oª[$v] = O[$u] +(	L[$u]=2 +q0 +q1	);	}	\
		}

#define	ReICEuOx(		$u, $v )			dBUG_ReICE("uOx", $u );	\
	if( A[$u]< 8){	if( B[$u]< 8 ){	K[$u] =/* 	0x00 |*/	(			B[$u]    << 3 ) |			A[$u];		Oª[$v] = Oª[$u];	L[$u]=0;			}	\
				else		{	K[$u] =  		0x80 |( (	q=zOf(		B[$u] ) )<< 3 ) |			A[$u];		Oª[$v] = Oª[$u] +(	L[$u]=1 +q		);	}	\
	}else{		if( B[$u]< 8 ){	K[$u] =  		0x40 |(				B[$u]    << 3 ) | ( q=zOf(  	A[$u] ) );		Oª[$v] = Oª[$u] +(	L[$u]=1 +q		);	}	\
				else		{	K[$u] =  		0xC0 |( (	q1=zOf( 		B[$u] ) )<< 3 ) | ( q0=zOf( 	A[$u] ) );		Oª[$v] = Oª[$u] +(	L[$u]=2 +q0 +q1	);	}	\
		}

#define	ReICEz(				$v )			dBUG_ReICEz($v );		ui08	Qc,	*pqz;	\
	if( A[$v]< 8){	if( B[$v]< 8 ){	cubeΩ[zcΩ]=/*0x00 |*/	(			B[$v]    << 3 ) |			A[$v];		CSΩ-=L[$v];				L[$v]=0;			}	\
				else		{	cubeΩ[zcΩ]=  	0x80 |( (	q=zOf( 		B[$v] ) )<< 3 ) |			A[$v];		cS=CSΩ-L[$v];	Qc=L[$v];	L[$v]=1 +q;		CSΩ=cS+L[$v];	if(Qc< L[$v] ) cubeΩ= SvGROW( svΩ, CSΩ+1	);	pqz=cubeΩ+cS;	switch( q ){ lluiCASTa(	B[$v],			pqz ); }	}	\
	}else{		if( B[$v]< 8 ){	cubeΩ[zcΩ]=  	0x40 |(				B[$v]    << 3 ) | ( q=zOf(  	A[$v] ) );		cS=CSΩ-L[$v];	Qc=L[$v];	L[$v]=1 +q;		CSΩ=cS+L[$v];	if(Qc< L[$v] ) cubeΩ= SvGROW( svΩ, CSΩ+1	);	pqz=cubeΩ+cS;	switch( q ){ lluiCASTa(			A[$v],	pqz ); }	}	\
				else		{	cubeΩ[zcΩ]=  	0xC0 |(	q=( (	q1=zOf( 	B[$v] ) )<< 3 ) | ( q0=zOf( 	A[$v] ) ) );	cS=CSΩ-L[$v];	Qc=L[$v];	L[$v]=2 +q0 +q1;	CSΩ=cS+L[$v];	if(Qc< L[$v] ) cubeΩ= SvGROW( svΩ, CSΩ+1	);	pqz=cubeΩ+cS;	switch( q ){ lluiCASTab(	B[$v],	A[$v], 	pqz ); }	}	\
		}		dBUG_SvCUR(	svΩ, CSΩ);	\
	cubeΩ[CSΩ]=0;	SvCUR_set(	svΩ, CSΩ );


#define	reICE(	$pq, $pk, $a, $b )			\
	if( $a< 8){	if( $b< 8	){	*$pk++	= /*	0x00 |*/	(			$b    << 3 ) |			$a;															}	\
				else		{	*$pk++	=  	0x80 |( (	q=zOf( 		$b ) )<< 3 ) |			$a;		switch( q ){ lluiCASTa(	$b,		$pq ); }	$pq +=1 +q;		}	\
	}else{		if( $b< 8	){	*$pk++	=  	0x40 |(				$b    << 3 ) | ( q=zOf(  	$a ) );	switch( q ){ lluiCASTa(		$a,	$pq ); }	$pq +=1 +q;		}	\
				else		{	*$pk++	=  	0xC0 |(	q=( (	q1=zOf( 	$b ) )<< 3 ) | ( q0=zOf( 	$a ) ) );	switch( q ){ lluiCASTab(	$b,	$a,	$pq ); }	$pq +=2 +q0 +q1;	}	\
		}
#define	reICEx(	$pq, $pk, $a, $b )			\
	if( $a< 8){	if( $b< 8	){	*$pk	= /*	0x00 |*/	(			$b    << 3 ) |			$a;															}	\
				else		{	*$pk	=  	0x80 |( (	q=zOf( 		$b ) )<< 3 ) |			$a;		switch( q ){ lluiCASTa(	$b,		$pq ); }					}	\
	}else{		if( $b< 8	){	*$pk	=  	0x40 |(				$b    << 3 ) | ( q=zOf(  	$a ) );	switch( q ){ lluiCASTa(		$a,	$pq ); }					}	\
				else		{	*$pk	=  	0xC0 |(	q=( (	q1=zOf( 	$b ) )<< 3 ) | ( q0=zOf( 	$a ) ) );	switch( q ){ lluiCASTab(	$b,	$a,	$pq ); }					}	\
		}
#define	reICE0(	$pq, $pk, $a, $b ) $pq =$pk +16;							\
	if( $a< 8){	if( $b< 8	){	*$pk	= /*	0x00 |*/	(			$b    << 3 ) |			$a;															}	\
				else		{	*$pk	=  	0x80 |( (	q=zOf( 		$b ) )<< 3 ) |			$a;		switch( q ){ lluiCASTa(	$b,		$pq ); }	$pq +=1 +q;		}	\
	}else{		if( $b< 8	){	*$pk	=  	0x40 |(				$b    << 3 ) | ( q=zOf(  	$a ) );	switch( q ){ lluiCASTa(		$a,	$pq ); }	$pq +=1 +q;		}	\
				else		{	*$pk	=  	0xC0 |(	q=( (	q1=zOf( 	$b ) )<< 3 ) | ( q0=zOf( 	$a ) ) );	switch( q ){ lluiCASTab(	$b,	$a,	$pq ); }	$pq +=2 +q0 +q1;	}	\
		}
#define	reICE00(	$pq, $pk,	$a,	$b ) $pq =	$pk +16;		\
	if( $a< 8){	if( $b< 8 )	{*( (ui64*) $pk )=/*	0x00 |*/	(			$b    << 3 ) |			$a;															}	\
				else		{*( (ui64*) $pk )=	0x80 |( (	q=zOf( 		$b ) )<< 3 ) |			$a;		switch( q ){ lluiCASTa(	$b,		$pq ); }	$pq +=1 +q;		}	\
	}else{		if( $b< 8 )	{*( (ui64*) $pk )=	0x40 |(				$b    << 3 ) | ( q=zOf(  	$a ) );	switch( q ){ lluiCASTa(		$a,	$pq ); }	$pq +=1 +q;		}	\
				else		{*( (ui64*) $pk )=	0xC0 |(	q=( (	q1=zOf( 	$b ) )<< 3 ) | ( q0=zOf( 	$a ) ) );	switch( q ){ lluiCASTab(	$b,	$a,	$pq ); }	$pq +=2 +q0 +q1;	}	\
		}

#define	reICE00x(	$pq, $pk, $a, $b )		$pq =	$pk +16;	*( (ui64*)	$pk )=0;					\
	if( $a< 8){	if( $b< 8 )	{	*$pk	=/*	0x00 |*/	(			$b    << 3 ) |			$a;															}	\
				else		{	*$pk	=	0x80 |( (	q=zOf( 		$b ) )<< 3 ) |			$a;		switch( q ){ lluiCASTa(	$b,		$pq ); }	$pq +=1 +q;		}	\
	}else{		if( $b< 8 )	{	*$pk	=	0x40 |(				$b    << 3 ) | ( q=zOf(  	$a ) );	switch( q ){ lluiCASTa(		$a,	$pq ); }	$pq +=1 +q;		}	\
				else		{	*$pk	=	0xC0 |(	q=( (	q1=zOf( 	$b ) )<< 3 ) | ( q0=zOf( 	$a ) ) );	switch( q ){ lluiCASTab(	$b,	$a,	$pq ); }	$pq +=2 +q0 +q1;	}	\
		}
//	experiment pending SwCASE_ICxBdec.h	\
#define _chopICEz(	$cube,	$CS,	$K,		$pq, 	$A,		$B,		$L )		\
	Kc =$K &0x87	\
	if( $a< 8){	if( $b< 8	){	*$pk++	= /*	0x00 |*//*	(			$b    << 3 ) |			$a;															}	\
				else		{	*$pk++	=  	0x80 |( (	q=zOf( 		$b ) )<< 3 ) |			$a;		switch( q ){ lluiCASTa(	$b,		$pq ); }	$pq +=1 +q;		}	\
	}else{		if( $b< 8	){	*$pk++	=  	0x40 |(				$b    << 3 ) | ( q=zOf(  	$a ) );	switch( q ){ lluiCASTa(		$a,	$pq ); }	$pq +=1 +q;		}	\
				else		{	*$pk++	=  	0xC0 |(	q=( (	q1=zOf( 	$b ) )<< 3 ) | ( q0=zOf( 	$a ) ) );	switch( q ){ lluiCASTab(	$b,	$a,	$pq ); }	$pq +=2 +q0 +q1;	}	\
		}

#define _DeICE0u(		$cube, $pq, $CS, $u, $v )	$pq= $cube+16;							O[ $u ] =16;				\
	switch( $cube[ 0 ]	){ SwCASE_IC2ABQ_init16p(	$pq,	A[ $u ],	B[ $u ],	L[ $u ],	$cube,	$pq,	O[ $v ]			); }		dBUG__DeICE0u(		A[$u], B[$u], L[$u] );

#define _DeICEv(		$cube, $pq, $CS, $u, $v )														w = $v+1;	\
	switch( $cube[ ic ]	){ SwCASE_IC2ABQ_inc_vec(	$pq,	A[ $v ],	B[ $v ],	L[ $v ],			$pq,	O[ $v ],		O[ w ]	); }	dBUG__DeICEv(		A[$v], B[$v], L[$v] );

#define _DeICEzu(		$cube, $pq, $CS, $zc, $u )	$pq= $cube +$CS;								\
	switch( $cube[ $zc ]	){ SwCASE_IC2ABQ_R2L(	$pq,	A[ $u ],	B[ $u ],	L[ $u ]	); }			O[ $u ]=$CS -L[ $u ];		dBUG__DeICEz(		A[$u], B[$u], L[$u] );

/*	automatically adds ( +1) to A[v] */	
#define _DeICE_vaInc(	$cube, $pq, $CS, $u, $v )	$pq=$cube+16;	w = $v+1; 				O[ $v ] =16;				\
	switch( $cube[ ic ]	){ SwCASE_IC2A1BQ_init16(	$pq,	A[ $v ],	B[ $v ],	L[ $v ],				O[ w ]			); }		dBUG__DeICE_vaInc(	A[$v], B[$v], L[$v] );	


#define	_DeICE0v(	$cube, $pq,  $CS,	$u, $v )	$pq= $cube +16;							O[ $v ] = oCS;	w = $v+1;	\
	switch( $cube[ 0 ]	){ SwCASE_IC2ABQ_inc_vec(	$pq, A[ $v ],	B[ $v ],	L[ $v ],			$pq,	O[ $v ],		O[ w ] ); }		dBUG__DeICE0v(		A[$v], B[$v], L[$v] );

/*
#define	_DeICEu(		$cube, $pq, $CS,	$u, $v )		$pq= $cube  +	O[ $u ];						\
	switch( $cube[ ic ]	){	SwCASE_IC2ABQ_vec(		$pq,	A[ $u ],	B[ $u ],	L[ $u ],				O[ $u ],		O[ $v ]	); }
*/
#define	_deICE0(	$cube,	$CS,	$K,		$pq,		$A,		$B,		$L )	$pq = $cube +16;	dBUG_deICE0(	$A, $B, $L )	\
	switch(	$K	){	SwCASE_IC2ABQ_inc(	$pq,		$A,  	$B,		$L,	$pq	);	}

#define	_deICE(	$cube,	$CS,	$K,		$pq,		$A,		$B,		$L )					dBUG_deICE(		$A, $B, $L )\
	switch(	$K	){	SwCASE_IC2ABQ_inc(	$pq,		$A,  	$B,		$L,	$pq	 );		}

#define	_deICEr(	$cube,	$CS,	$K,		$pq,		$A,		$B,		$L )					dBUG_deICEr(		$A, $B, $L )\
	switch(	$K	){	SwCASE_IC2ABQ_R2L_dec( $pq,	$A,  	$B,		$L,	$pq	 );		}

#define	deICE0(									$A,		$B,		$L )		\
		_deICE0(	cube,	CS,  	cube[0],	pq,		$A,		$B,		$L )

#define	deICE(					$K,				$A,		$B,		$L )		\
		_deICE(	cube,	CS,  	$K,		pq,		$A,		$B,		$L )

#define	deICEr(					$K,				$A,		$B,		$L )		\
		_deICEr(	cube,	CS,  	$K,		pq,		$A,		$B,		$L )


#define	deICE0_(									$A,		$B,		$L )		\
		_deICE0(	cubeΩ,	CSΩ,	cubeΩ[0], pqz,	$A,		$B,		$L )

#define	deICE_(					$K,				$A,		$B,		$L )		\
		_deICE(	cubeΩ,	CSΩ,	$K,		pq,		$A,		$B,		$L )

#define deICE_E(					$K,				$A,		$B,		$L,		$E )		\
		_deICE(	cube,	CS,		$K,		pq,	 	$A,		$B,		$L ); 	$E+=$A+$B;

#define deICEzc_KE(	$zc		)										deICEr( cube[ $zc ],	Ac, Bc, Qc );			Ec =*( (ui64*) cube+1);


//	#define DeICEu(		$u,	$v	) _DeICEu(  		cube, pq,	CS,				$u,	$v	);
	#define DeICEvAinc(	$u,	$v	) _DeICE_vaInc(	cube, pq, CS,				$u,	$v	);
	#define DeICEv(		$u,	$v	) _DeICEv(  		cube, pq, CS,				$u,	$v	);
	#define DeICE0u(		$u,	$v	) _DeICE0u(		cube, pq, CS,				$u,	$v	);
	#define DeICE0v(		$u,	$v	) _DeICE0v(		cube, pq, CS,				$u,	$v	);
	#define DeICEzu(		$u		) _DeICEzu(		cube, pq, CS,		zc,		$u		);				RW[ $u ]=ok;

//	#define DeICEu_(		$u,	$v	) _DeICEu(  		cubeΩ, pΩ, CSΩ,			$u,	$v	);
	#define DeICEv_(		$u,	$v	) _DeICEv(  		cubeΩ, pΩ, CSΩ,			$u,	$v	);
	#define DeICE0u_(		$u,	$v	) _DeICE0u(		cubeΩ, pΩ, CSΩ,			$u,	$v	);
//	#define DeICE0v_(		$u,	$v	) _DeICE0v(		cubeΩ, pΩ, CSΩ,			$u,	$v	);
	#define DeICEzu_(		$u		) _DeICEzu(		cubeΩ, pΩ, CSΩ,	zcΩ,		$u		);

//	#define DeICE_uK(		$u,	$v	) K[$u]	= cube[	++ic	];					DeICEu(		$u,	$v	);	RW[ $u ]=ok;

	#define DeICEvAinc_K(	$u,	$v	) K[$v]	= cube[	++ic	];					DeICEvAinc( 	$u,	$v	); //	RW[ $v ]=mod;
	#define DeICEvAinc_KI($u,	$v	) K[$v]	= cube[	++ic	];					DeICEvAinc( 	$u,	$v	);	RW[ $v ]=mod; 								I[ $v ] =ic;
	#define DeICEvAinc_KEI($u,	$v	) K[$v]	= cube[	++ic	];					DeICEvAinc( 	$u,	$v	);	RW[ $v ]=mod; E[$v] =A[$v] +B[$v] +E[$u];			I[ $v ] =ic;

//	#define DeICE_vK(		$u,	$v	) K[$v]	= cube[	++ic	];					DeICEv(		$u,	$v	);	RW[ $v ]=ok;
	#define DeICE_vI(   	$u,	$v	)				++ic;					DeICEv(		$u,	$v	);	RW[ $v ]=ok;									I[ $v ] =ic+oc;	//	I[ $v ] =ic;//+xc-zc;
	#define DeICE_vEI( 	$u,	$v	) 				++ic;					DeICEv(		$u,	$v	);	RW[ $v ]=ok;	E[$v] =A[$v] +B[$v] +E[$u];			I[ $v ] =ic+oc;	//	I[ $v ] =ic;//+xc-zc;
	#define DeICE_vE(  	$u,	$v	) 				++ic;					DeICEv(		$u,	$v	);	RW[ $v ]=ok;	E[$v] =A[$v] +B[$v] +E[$u];
	#define DeICE_vEpInc(  	$u,	$v	) 				++ic;					DeICE_vpInc(	$u,	$v	);	RW[ $v ]=ok;	E[$v] =A[$v] +B[$v] +E[$u];
	#define DeICE_vK( 	$u,	$v	) K[$v]	= cube[	++ic	];					DeICEv(		$u,	$v	);	RW[ $v ]=ok;							
//	#define DeICE_vKI(	$u,	$v	) K[$v]	= cube[	++ic	];					DeICEv(		$u,	$v	);	RW[ $v ]=ok;									I[ $v ] =I[ $u ]+1;
	#define DeICE_vKE(	$u,	$v	) K[$v]	= cube[	++ic	];					DeICEv(		$u,	$v	);	RW[ $v ]=ok;	E[$v] =A[$v] +B[$v] +E[$u];
	#define DeICE_vKEI(	$u,	$v	) K[$v]	= cube[	++ic	];					DeICEv(		$u,	$v	);	RW[ $v ]=ok;	E[$v] =A[$v] +B[$v] +E[$u];			I[ $v ] =ic+oc;	 	dBUG_vKEI(	"DeICE_vKEI" 	);
//	#define DeICE_vKEI2(	$u,	$v	) K[$v]	= cube[	++ic	];					DeICEv(		$u,	$v	);	RW[ $v ]=ok;	E[$v] =A[$v] +B[$v] +E[$u];			I[ $v ] =I[$u]+1;



	#define DeICE0_uK(	$u,	$v	) K[$u]	= cube[	ic=0	];					DeICE0u(		$u,	$v	);	RW[ $u ]=ok;			
	#define DeICE0_uKE(	$u,	$v	) K[$u]	= cube[	ic=0	];					DeICE0u(		$u,	$v	);	RW[ $u ]=ok;	E[$u] =A[$u] +B[$u] +*Edge( cubeΩ );					dBUG0(		"DeICE0_uKE"	);
	#define DeICE0_uKEI(	$u,	$v	) K[$u]	= cube[	ic=0	];					DeICE0u(		$u,	$v	);	RW[ $u ]=ok;	E[$u] =A[$u] +B[$u] +*Edge( cubeΩ );	I[$u]=0;			dBUG0(		"DeICE0_uKEI"	);
	#define DeICE0_uE(	$u,	$v	) K[$u]	= cube[	ic=0	];					DeICE0u(		$u,	$v	);	RW[ $u ]=ok;	E[$u] =A[$u] +B[$u] +*Edge( cubeΩ );					dBUG0(		"DeICE0_uE"		);
	#define DeICE0_uEI(	$u,	$v	) 				ic=0						DeICE0u(		$u,	$v	);	RW[ $u ]=ok;	E[$u] =A[$u] +B[$u] +*Edge( cubeΩ );	I[$u]=ic=0;		dBUG0(		"DeICE0_uEI"		);
	#define DeICE0_vKEI(	$u,	$v	) K[$v]	= cube[	ic=0	];					DeICE0v(		$u,	$v	);	RW[ $v ]=ok;	E[$v] =A[$v] +B[$v] +E[$u];			I[$v] = oc;	 	dBUG0_vKEI(	"DeICE0_vKEI"	);
	#define DeICE0_vKE(	$u,	$v	) K[$v]	= cube[	ic=0	];					DeICE0v(		$u,	$v	);	RW[ $v ]=ok;	E[$v] =A[$v] +B[$v] +E[$u];			
//	^ All "_v" variants imply we have already aligned the buffer matrix with cube iC, and we're continuing that alignment.
//	The "0_v" variant is significant because this is the first decoder which pages matrix alignment into the next cube.

//	#define DeICEz_uK(	$u,	$v	) K[$u]	= cube[	ic=zc ];					DeICEzu(		$u		);				
	#define DeICEz_uKI(	$u		) K[$u]	= cube[	ic=zc ];					DeICEzu(		$u		);	RW[ $u ]=ok;							I[ $u ] =zc;				dBUG0(		"DeICE0_uK"  	);
	#define DeICEz_uKE(	$u		) K[$u]	= cube[	ic=zc ];					DeICEzu(		$u		);	RW[ $u ]=ok;	E[$u] =*Edge( cube );								dBUGz(		"DeICEz_uKE" 	);
	#define DeICEz_uKEI(	$u		) K[$u]	= cube[	ic=zc ];					DeICEzu(		$u		);	RW[ $u ]=ok;	E[$u] =*Edge( cube );		I[ $u ] =zc;				dBUGz(		"DeICEz_uKEI"	);
//	#define DeICEr_uKEI(	$u		) K[$u]	= cube[	--ic	];					DeICEru(		$u		);	RW[ $u ]=ok;	E[$u] =E[$v] -A[$u] -B[$u];	I[ $u ] =ic;
	#define DeICEr_uKI(	$u		) K[$u]	= cube[	--ic	];					DeICEru(		$u		);	RW[ $u ]=ok;							I[ $u ] =zc;				dBUGz(		"DeICEr_uKI()"	);


//	#define DeICE_vKE_(	$u,	$v	) K[$v]	= cubeΩ[	++ic ];					DeICEv_(	 	$u,	$v	);	RW[ $v ]=ok;	E[$v] =A[$v] +B[$v] +E[$u];	I[ $v ] =I[ $u ]+1;	
//	#define DeICE_vKEI_(	$u,		) K[$v]	= cubeΩ[	++ic ];					DeICEv_(	 	$u,	$v	);	RW[ $v ]=ok;	E[$v] =A[$v] +B[$v] +E[$u];	I[ $v ] =I[ $u ]+1;
//	#define DeICEz_uK_(	$u,	$v	) K[$u]	= cubeΩ[	zcΩ	];					DeICEzu_(	$u		);				
	#define DeICEz_uE_(	$u		) 										DeICEzu_(	$u		);				E[$u] =*Edge( cubeΩ );
	#define DeICEz_uKE_(	$u		) K[$u]	= cubeΩ[	zcΩ	];					DeICEzu_(	$u		);				E[$u] =*Edge( cubeΩ );								dBUGz(		"DeICEz_uKE_"  	);
//	#define DeICEz_uKEI_(	$u,	$v	) K[$u]	= cubeΩ[	zcΩ	];					DeICEzu_(	$u		);				E[$u] =*Edge( cubeΩ ); 		I[ $u ] =zc;	


#define INIT_AvEXT( $E0 )	zc=-1;	  	$pq =(	$pk =	$cube ) +	16;			/* reset cube buffer				*/	

#define			AvICExt_FIRST(	$x,	$pq, 	$pk, 	$cube,	$E0		)	\
						zc=-1;	  	$pq =(	$pk =	$cube ) +	16;			/* reset cube buffer				*/	\
						Ec	=	$x+1;				Ac =	$x -	$E0;	Bc=1;	/* init coordinates of first ic			*/	\

#define			AvICExt_NEXT(	$x,	$pq, 	$pk, 	$cube			)	\
				if(		Ec	<	$x	){									/* x starts next ic					*/	\
							reICE(	$pq,		$pk, 	Ac,			Bc	);	/* encode this ic					*/	\
													Ac =	$x -	Ec;	Bc=1;	/* init coordinates of next ic			*/	\
					if(++	zc==7 ){		*$pq=0;	*Edge(	$cube ) =	Ec;			/* finalize this cube; create this SV		*/	av_push( avICE, newSVpvn( $cube, $pq -$cube ) );	Aº=AvARRAY( avICE );	\
											*( (ui64*)	$cube ) =	0;			\
						zc=-1;  		$pq =(	$pk =	$cube ) +	16;			/* reset cube buffer				*/	\
						}												\
						Ec	=	$x+1;									\
				}else if(	Ec	==	$x	)	{   			   		  ++	Bc;		/* x extends this ic					*/	\
					 ++	Ec;				}																	\


#define			AvICExt_LAST(	$x,	$pq, 	$pk, 	$cube			)										\
				if(		Ec	<	$x	){									/* x starts last ic					*/	\
							reICE(	$pq,		$pk, 	Ac,			Bc	);	/* encode this ic					*/	\
													Ac =$x -	Ec;	Bc=1;	\
					if(6!=zc)	{reICE(	$pq,		$pk, 	Ac,			Bc	);	/* encode last ic					*/	\
					}else	{		*$pq=0;	*Edge(	$cube ) =	Ec;			/* finalize this cube; create this SV		*/	av_push( avICE, newSVpvn( $cube, $pq -$cube ) );	Aº=AvARRAY( avICE );	\
							reICE00(	$pq,		$cube,	Ac,			Bc	);	/* encode last ic as #0 of new cube	*/	\
							}		*$pq=0;	*Edge(	$cube ) =	$x+1;		/* finalize last cube; create last SV		*/	av_push( avICE, newSVpvn( $cube, $pq -$cube ) );	Aº=AvARRAY( avICE );	\
											*( (ui64*)	$cube ) =	0;			\
						Ec	=	$x+1;																		\
				}else{ if(	Ec	==	$x	)	{   			   		  ++	Bc;		/* x extends this ic					*/	\
					 ++	Ec;				}																	\
							reICE(	$pq,		$pk, 	Ac,			Bc	);	/* encode this/last ic				*/	\
									*$pq=0;	*Edge(	$cube ) =	Ec;			/* finalize last cube; create last SV		*/	av_push( avICE, newSVpvn( $cube, $pq -$cube ) );	Aº=AvARRAY( avICE );	\
					}

#define			AvICExt_ONLY(	$x,	$pq, 	$pk, 	$cube,	$E0		)	\
													Ac =$x -	$E0;	Bc=1;	\
							reICE00(	$pq,		$cube,	Ac,			Bc	);	\
									*$pq=0;	*Edge(	$cube ) =	$x+1;		/* create only cube; create only SV	*/	av_push( avICE, newSVpvn( $cube, $pq -$cube ) );	Aº=AvARRAY( avICE );

#define							CONCAT( a, b) a##b
#define SYM(	$name, $n	)	CONCAT( $name, $n)

#define	AvICExt_IMPL(	$n,		$x,	$pq, 	$pk, 	$cube,	$E0,	$avArg,		$a, $za )	\
	*( (ui64*)	buf ) = 0;						SV **	pSv;									\
	do		{ if(	$a>=$za){															/* if the first valid argument we find is also the last one, we're *only* extending by one */\
				AvICExt_ONLY(	$x,	$pq, 	$pk, 	$cube,	$E0	);					goto SYM(_end, $n );	\
				}								pSv = AvARRAY(	$avArg )+ ++	$a;	 	\
			}					while( !	SvIOK( *	pSv ) );								\
				AvICExt_FIRST(	$x,	$pq, 	$pk, 	$cube,	$E0	);					\
								$x = SvIVX(	*	pSv );								\
	do	{ do	{ if(	$a==$za)  goto SYM( _last, $n );		pSv = AvARRAY(	$avArg )+ ++	$a; 		\
			}					while( !	SvIOK( *	pSv ) );								\
				AvICExt_NEXT(	$x,	$pq, 	$pk, 	$cube		);					\
								$x = SvIVX(	*	pSv );								\
		} while(	$a< $za );															/*	printf("\nAvICExt: exit NEXT loop via default case	x: 0x%llX, Ac: 0x%llX, Bc: 0x%llX, Ec: 0x%llX\n\n", x, Ac, Bc, Ec);	*/	\
SYM(_last, $n):	AvICExt_LAST(	$x,	$pq, 	$pk, 	$cube		);					\
SYM(_end, $n):

#define	AvICExt(					$x,	$pq, 	$pk, 	$cube,	$E0,	$avArg,		$a, $za )	\
		AvICExt_IMPL(__COUNTER__,$x,	$pq, 	$pk, 	$cube,	$E0,	$avArg,		$a, $za )	


#define AvNEW( $avICE, $cube, $pk, $pq, $avArg, $a, $za, $E0 )	/* "Cube" an ascending list of unsigned integers	*/					\
	if( Aº != AvARRAY( avICE )  ){	printf("\npSv0 is out of sync with avICE going into AvNEW\n");	Aº=AvARRAY( avICE );	}		\
/*	printf("\r<AvNEW	starting at arg %lld/%lld	E_( %llu ) <	x( %llu ) 		\n", a, za, $E0, x );	*/									\
																		Ac =x-$E0;	Bc =1;										\
	if( $a >=$za){	/* no  args	*/				zc = 0;	reICE0(	$pq,	$cube,	Ac,			Bc );	*( (ui64*)	$cube+1 ) =x+1;	*pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	Aº=AvARRAY( $avICE );	/* push new cube with only x		*/	\
	}else{									zc = -1;																		\
		do	{			Ec	=	x +1;		pSv= AvARRAY( $avArg ) + ++$a;												\
			if( SvIOK( *pSv ) ){		x= SvIVX(   *	pSv );																	\
				if(		Ec ==	x )	{								  ++	Bc;	  				}						/*	=+|$	*/	\
				else if(	Ec < 	x )	{	if(	zc==7 ){											*( (ui64*)	$cube+1) = $E0;	*$pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	Aº=AvARRAY( $avICE );	/* push new cube		*/	\
											zc=0;								$pk=$cube+1;	*( (ui64*)	$cube ) =0;													/* reset cube buffer	*/	\
													reICE0(	$pq,	$cube,	Ac,			Bc );  							/* encode x in cyclum 0	*/	\
										}else{ ++zc;	reICE(	$pq,	$pk,		Ac,			Bc );  							/* encode x in cyclum zc */	\
											}							Ac =x -Ec;	Bc=1;	$E0=Ec;					/*	_+|$	*/	\
									}																				\
			/* !SvIOK of argument x treated as a cube separator	*/\
			}else{						if(	zc==7 ){											*( (ui64*)	$cube+1) = $E0;	*$pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	Aº=AvARRAY( $avICE );	/* push new cube		*/	\
																							*( (ui64*)	$cube ) =0;															/* reset cube buffer	*/	\
													reICE0(	$pq,	$cube,	Ac,			Bc );  	*( (ui64*)	$cube+1) = Ec;	*$pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	Aº=AvARRAY( $avICE );	/* push new cube		*/	\
										}else{		reICE(	$pq,	$pk,		Ac,			Bc );  	*( (ui64*)	$cube+1) = Ec;	*$pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	Aº=AvARRAY( $avICE );	/* push new cube		*/	\
											}zc=-1;											*( (ui64*)	$cube ) =0;													/* reset cube buffer	*/	\
			/* ...but we must ignore consecutive cube separators	*/	$pq=($pk=$cube)+16;								\
				while(	$a< $za )	if( SvIOK( *( pSv= AvARRAY( $avArg ) + ++$a ) ) )										\
								{																			\
								x= SvIVX(   *	pSv );			Ac =x -Ec;	Bc=1;	$E0=Ec;	break;				\
								}																			\
			}	}	while( $a< $za );																			\
		if(	SvIOK( *pSv ) ){				if(	zc==7 ){											*( (ui64*)	$cube+1) = $E0;	*$pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	Aº=AvARRAY( $avICE );	/* push new cube		*/	\
																				$pk=$cube+1;	*( (ui64*) $cube ) =0;													/* reset cube buffer	*/	\
													reICE0(	$pq,	$cube,	Ac,			Bc );  							/* encode x in cyclum 0	*/	\
										}else{		reICE(	$pq,	$pk,		Ac,			Bc );  							/* encode x in cyclum zc */	\
											}												*( (ui64*)	$cube+1 ) =x+1;	*$pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	Aº=AvARRAY( $avICE );	/* push new cube		*/	\
		}				}/*	printf("\r	</AvNEW>\n");	*/
