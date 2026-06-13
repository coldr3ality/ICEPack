
	#include	"SwCASE_IC2AB_init16.h"
	#include	"SwCASE_IC2AB_vec.h"
	#include	"SwCASE_IC2AB_inc.h"
	#include	"SwCASE_IC2AB_R2L.h"
	#include	"SwCASE_IC2AB_R2L_dec.h"
	#include	"SwCASE_IC2A1B_init16.h"
//	#include	"SwCASE_IC2A1B_vecx_incQ.h"
//	#include	"SwCASE_IC2Ape1B_incxQ.h"

	#include	"lluiCAST.h"
	#include	"SwCASE_AB2IC_t0_inc.h"
//	#include	"SwCASE_AB2IC_t1_inc.h"
//	#include	"SwCASE_AB2IC_t2_inc.h"
	#include	"SwCASE_AB2IC_t3_inc.h"

#define	zcOf(	$cube)	7-( 	__builtin_clzll( *( (ui64*)	$cube)	) >>3)
#define	zOf( 	$a)		7-( 	__builtin_clzll(			 $a		) >>3)
#if defined( DEBUG_MOD_L3 )
	#define 	dBUG_ReICE($SUFFIX, $u )	if( O[ $u ]==0 ){ cS= sprintf( aString, "\n!	ReICE%s( ... ): mx step u does not seem to have been read-in (O[%d]==0)\n\n", $SUFFIX, $u );	AvDBUG_PUSH( aString, cS );	}
#else
	#define 	dBUG_ReICE($SUFFIX, $u )
#endif


#define	ReICEuO(		$u, $v)			dBUG_ReICE("uO", $u );									Ox[$u] = O[$u];	\
	if( A[$u]< 8){	if( B[$u]< 8 ){	H[$u] =/*		0x00 |*/	(			B[$u]    << 3 ) |			A[$u];		Ox[$v] = O[$u];	Q[$u]=0;			}	\
				else		{	H[$u] =  		0x80 |( (	q=zOf(		B[$u] ) )<< 3 ) |			A[$u];		Ox[$v] = O[$u] +(	Q[$u]=1 +q		);	}	\
	}else{		if( B[$u]< 8 ){	H[$u] =  		0x40 |(				B[$u]    << 3 ) | ( q=zOf(  	A[$u] ) );		Ox[$v] = O[$u] +(	Q[$u]=1 +q		);	}	\
				else		{	H[$u] =  		0xC0 |( (	q1=zOf(		B[$u] ) )<< 3 ) | ( q0=zOf(	A[$u] ) );		Ox[$v] = O[$u] +(	Q[$u]=2 +q0 +q1	);	}	\
		}

#define	ReICEuOx(		$u, $v )			dBUG_ReICE("uOx", $u );	\
	if( A[$u]< 8){	if( B[$u]< 8 ){	H[$u] =/* 	0x00 |*/	(			B[$u]    << 3 ) |			A[$u];		Ox[$v] = Ox[$u];	Q[$u]=0;			}	\
				else		{	H[$u] =  		0x80 |( (	q=zOf(		B[$u] ) )<< 3 ) |			A[$u];		Ox[$v] = Ox[$u] +(	Q[$u]=1 +q		);	}	\
	}else{		if( B[$u]< 8 ){	H[$u] =  		0x40 |(				B[$u]    << 3 ) | ( q=zOf(  	A[$u] ) );		Ox[$v] = Ox[$u] +(	Q[$u]=1 +q		);	}	\
				else		{	H[$u] =  		0xC0 |( (	q1=zOf( 		B[$u] ) )<< 3 ) | ( q0=zOf( 	A[$u] ) );		Ox[$v] = Ox[$u] +(	Q[$u]=2 +q0 +q1	);	}	\
		}

#define	ReICEzSv(			$v )			dBUG_ReICEzSv($v );		\
	if( A[$v]< 8){	if( B[$v]< 8 ){	cube[zc]=/*	0x00 |*/	(			B[$v]    << 3 ) |			A[$v];		CS-=Q[$v];					Q[$v]=0;			}	\
				else		{	cube[zc]= 	0x80 |( (	q=zOf( 		B[$v] ) )<< 3 ) |			A[$v];		cS=CS-Q[$v];	Qc=Q[$v];	Q[$v]=1 +q;		CS=cS+Q[$v];	if(Qc< Q[$v] ) cube= SvGROW( sv, CS+1	);	pqz=cube+cS;	switch( q ){ lluiCASTa(	B[$v],			pqz ); }	}	\
	}else{		if( B[$v]< 8 ){	cube[zc]=  	0x40 |(				B[$v]    << 3 ) | ( q=zOf(  	A[$v] ) );		cS=CS-Q[$v];	Qc=Q[$v];	Q[$v]=1 +q;		CS=cS+Q[$v];	if(Qc< Q[$v] ) cube= SvGROW( sv, CS+1	);	pqz=cube+cS;	switch( q ){ lluiCASTa(			A[$v],	pqz ); }	}	\
				else		{	cube[zc]=  	0xC0 |(	q=( (	q1=zOf( 	B[$v] ) )<< 3 ) | ( q0=zOf( 	A[$v] ) ) );	cS=CS-Q[$v];	Qc=Q[$v];	Q[$v]=2 +q0 +q1;	CS=cS+Q[$v];	if(Qc< Q[$v] ) cube= SvGROW( sv, CS+1	);	pqz=cube+cS;	switch( q ){ lluiCASTab(	B[$v],	A[$v], 	pqz ); }	}	\
		}		dBUG_SvCUR(CS, "CS" );	\
	SvCUR_set( sv,	CS );	cube[CS]=0;

#define	ReICEzSvZ(			$v )			dBUG_ReICEzSvZ($v );		\
	if( A[$v]< 8){	if( B[$v]< 8 ){	cubeZ[zcZ]=/*	0x00 |*/	(			B[$v]    << 3 ) |			A[$v];		CSZ-=Q[$v];					Q[$v]=0;			}	\
				else		{	cubeZ[zcZ]=  	0x80 |( (	q=zOf( 		B[$v] ) )<< 3 ) |			A[$v];		cS=CSZ-Q[$v];	Qc=Q[$v];	Q[$v]=1 +q;		CSZ=cS+Q[$v];	if(Qc< Q[$v] ) cubeZ= SvGROW( svZ, CSZ+1	);	pqz=cubeZ+cS;	switch( q ){ lluiCASTa(	B[$v],			pqz ); }	}	\
	}else{		if( B[$v]< 8 ){	cubeZ[zcZ]=  	0x40 |(				B[$v]    << 3 ) | ( q=zOf(  	A[$v] ) );		cS=CSZ-Q[$v];	Qc=Q[$v];	Q[$v]=1 +q;		CSZ=cS+Q[$v];	if(Qc< Q[$v] ) cubeZ= SvGROW( svZ, CSZ+1	);	pqz=cubeZ+cS;	switch( q ){ lluiCASTa(			A[$v],	pqz ); }	}	\
				else		{	cubeZ[zcZ]=  	0xC0 |(	q=( (	q1=zOf( 	B[$v] ) )<< 3 ) | ( q0=zOf( 	A[$v] ) ) );	cS=CSZ-Q[$v];	Qc=Q[$v];	Q[$v]=2 +q0 +q1;	CSZ=cS+Q[$v];	if(Qc< Q[$v] ) cubeZ= SvGROW( svZ, CSZ+1	);	pqz=cubeZ+cS;	switch( q ){ lluiCASTab(	B[$v],	A[$v], 	pqz ); }	}	\
		}		dBUG_SvCUR(CSZ, "CSZ" );	\
	SvCUR_set( svZ,	CSZ );	cubeZ[CSZ]=0;


#define	reICE( $a, $b, $pk, $pq)			\
	if( $a< 8){	if( $b< 8	){	*$pk++	= /*	0x00 |*/	(			$b    << 3 ) |			$a;															}	\
				else		{	*$pk++	=  	0x80 |( (	q=zOf( 		$b ) )<< 3 ) |			$a;		switch( q ){ lluiCASTa(	$b,		$pq ); }	$pq +=1 +q;		}	\
	}else{		if( $b< 8	){	*$pk++	=  	0x40 |(				$b    << 3 ) | ( q=zOf(  	$a ) );	switch( q ){ lluiCASTa(		$a,	$pq ); }	$pq +=1 +q;		}	\
				else		{	*$pk++	=  	0xC0 |(	q=( (	q1=zOf( 	$b ) )<< 3 ) | ( q0=zOf( 	$a ) ) );	switch( q ){ lluiCASTab(	$b,	$a,	$pq ); }	$pq +=2 +q0 +q1;	}	\
		}
#define	reICEx( $a, $b, $pk, $pq)			\
	if( $a< 8){	if( $b< 8	){	*$pk	= /*	0x00 |*/	(			$b    << 3 ) |			$a;															}	\
				else		{	*$pk	=  	0x80 |( (	q=zOf( 		$b ) )<< 3 ) |			$a;		switch( q ){ lluiCASTa(	$b,		$pq ); }					}	\
	}else{		if( $b< 8	){	*$pk	=  	0x40 |(				$b    << 3 ) | ( q=zOf(  	$a ) );	switch( q ){ lluiCASTa(		$a,	$pq ); }					}	\
				else		{	*$pk	=  	0xC0 |(	q=( (	q1=zOf( 	$b ) )<< 3 ) | ( q0=zOf( 	$a ) ) );	switch( q ){ lluiCASTab(	$b,	$a,	$pq ); }					}	\
		}
#define	reICE0(  $a, $b, $pk, $pq) $pq =$pk +16;							\
	if( $a< 8){	if( $b< 8	){	*$pk	= /*	0x00 |*/	(			$b    << 3 ) |			$a;															}	\
				else		{	*$pk	=  	0x80 |( (	q=zOf( 		$b ) )<< 3 ) |			$a;		switch( q ){ lluiCASTa(	$b,		$pq ); }	$pq +=1 +q;		}	\
	}else{		if( $b< 8	){	*$pk	=  	0x40 |(				$b    << 3 ) | ( q=zOf(  	$a ) );	switch( q ){ lluiCASTa(		$a,	$pq ); }	$pq +=1 +q;		}	\
				else		{	*$pk	=  	0xC0 |(	q=( (	q1=zOf( 	$b ) )<< 3 ) | ( q0=zOf( 	$a ) ) );	switch( q ){ lluiCASTab(	$b,	$a,	$pq ); }	$pq +=2 +q0 +q1;	}	\
		}
/*	experiment pending SwCASE_ICxBdec.h	
#define _chopICEz(	$cube,	$CS,	$H,		$pq, 	$Q,		$A,		$B )		\
	Kc =$H &0x87	\
	if( $a< 8){	if( $b< 8	){	*$pk++	= /*	0x00 |*//*	(			$b    << 3 ) |			$a;															}	\
				else		{	*$pk++	=  	0x80 |( (	q=zOf( 		$b ) )<< 3 ) |			$a;		switch( q ){ lluiCASTa(	$b,		$pq ); }	$pq +=1 +q;		}	\
	}else{		if( $b< 8	){	*$pk++	=  	0x40 |(				$b    << 3 ) | ( q=zOf(  	$a ) );	switch( q ){ lluiCASTa(		$a,	$pq ); }	$pq +=1 +q;		}	\
				else		{	*$pk++	=  	0xC0 |(	q=( (	q1=zOf( 	$b ) )<< 3 ) | ( q0=zOf( 	$a ) ) );	switch( q ){ lluiCASTab(	$b,	$a,	$pq ); }	$pq +=2 +q0 +q1;	}	\
		}
*/

#ifdef DEBUG_ACCESS_L3
	#define dBUG_DeICEz	if( zc==-1 ){	cS = sprintf(aString, 	"\r! 	%s line %lld: cube #%lld is empty.		\n",									__FILE__, __LINE__, iC				);	AvDBUG_PUSH( aString, cS );	}
#else
	#define dBUG_DeICEz
#endif

#define _DeICE0u(	$cube, $CS, $u, $v )										pq=$cube+16;	O[ $u ] =16;			\
	switch( $cube[ 0 ]	){	SwCASE_IC2AB_init16(		Q[ $u ],	A[ $u ],	B[ $u ],	pq,			O[ $v ]			); }	

#define _DeICEv(	$cube, $CS, $u, $v )	w = $v+1; 							pq=	$cube +	O[ $v ];				\
	switch( $cube[ ic ]	){	SwCASE_IC2AB_vec(		Q[ $v ],	A[ $v ],	B[ $v ],	pq,			O[ $v ],	O[ w ]	); }

#define _DeICEzu(	$cube, $CS, $zc, $u )		dBUG_DeICEz;					pqz= $cube +	$CS;				\
	switch( $cube[ $zc ]	){	SwCASE_IC2AB_R2L(		Q[ $u ],	A[ $u ],	B[ $u ],	pqz							); }	O[ $u ]=$CS -Q[ $u ];

/*
#define _DeICEv1( $cube, $CS, $u, $v )		w = $v+1; /*	streamlines ( +1) to A[v]		pq=$cube+16;*//*O[ $v ] =16;			\
	switch( $cube[ ic ]	){	SwCASE_IC2A1B_init16(		Q[ $v ],	A[$v],	B[ $v ],	pq,			O[ w ]			); }

*/

/*
#define	_DeICE0v( $cube,	$CS,	$u, $v )	w = $v+1;						pq=$cube+16;	O[ $v ] =16;			\
	switch( $cube[ 0 ]	){	SwCASE_IC2AB_init16(		Q[ $v ],	A[ $v ],	B[ $v ],	pq,			O[ w ]	); }

#define	_DeICEu(	$cube,	$CS,	$u, $v )									pq=	$cube  +	O[ $u ];				\
	switch( $cube[ ic ]	){	SwCASE_IC2AB_vec(		Q[ $u ],	A[ $u ],	B[ $u ],	pq,			O[ $u ],	O[ $v ]	); }
*/


#define	_deICE0(	$cube,	$CS,	$H,		$pq, 	$Q,		$A,		$B )		$pq = $cube +16;	\
	switch(	$H		){	SwCASE_IC2AB_inc(		$Q,  	$A,  	$B,		$pq,	$pq	);	}

#define	_deICE(	$cube,	$CS,	$H,		$pq, 	$Q,		$A,		$B )		\
	switch(	$H		){	SwCASE_IC2AB_inc(		$Q,  	$A,  	$B,		$pq,	$pq	 	);	}

#define	_deICEr(	$cube,	$CS,	$H,		$pq, 	$Q,		$A,		$B )		\
	switch(	$H		){	SwCASE_IC2AB_R2L_dec(	$Q,  	$A,  	$B,		$pq,	$pq	 );	}

#define	deICE0(									$Q,		$A,		$B )		\
		_deICE0(	cube,	CS,  	cube[0],	pq,		$Q,		$A,		$B )

#define	deICE(					$H,				$Q,		$A,		$B )		\
		_deICE(	cube,	CS,  	$H,		pq,		$Q,		$A,		$B )

#define	deICEr(					$H,				$Q,		$A,		$B )		\
		_deICEr(	cube,	CS,  	$H,		pq,		$Q,		$A,		$B )



#define	deICE0_(									$Q,		$A,		$B )		\
		_deICE0(	cubeZ,	CSZ,	cubeZ[0],	pqz,		$Q,		$A,		$B )

#define	deICE_(					$H,				$Q,		$A,		$B )		\
		_deICE(	cubeZ,	CSZ,	$H,		pq,		$Q,		$A,		$B )


//	#define DeICEu(		$u,	$v	) _DeICEu(  		cube, 	CS,				$u,	$v	);
	#define DeICEv1(		$u,	$v	) _DeICEv1(  		cube, 	CS,				$u,	$v	);
	#define DeICEv(		$u,	$v	) _DeICEv(  		cube, 	CS,				$u,	$v	);
	#define DeICE0u(		$u,	$v	) _DeICE0u(		cube, 	CS,				$u,	$v	);
//	#define DeICE0v(		$u,	$v	) _DeICE0v(		cube, 	CS,				$u,	$v	);
	#define DeICEzu(		$u		) _DeICEzu(		cube, 	CS,		zc,		$u		);		RW[ $u ]=ok;

//	#define DeICEu_(		$u,	$v	) _DeICEu(  		cubeZ, 	CSZ,			$u,	$v	);
	#define DeICEv_(		$u,	$v	) _DeICEv(  		cubeZ, 	CSZ,			$u,	$v	);
	#define DeICE0u_(		$u,	$v	) _DeICE0u(		cubeZ, 	CSZ,			$u,	$v	);
//	#define DeICE0v_(		$u,	$v	) _DeICE0v(		cubeZ, 	CSZ,			$u,	$v	);
	#define DeICEzu_(		$u		) _DeICEzu(		cubeZ, 	CSZ,	zcZ,		$u		);


//	#define DeICEu_K(		$u,	$v	) H[$u] = cube[	++ic	];					DeICEu(		$u,	$v	);	RW[ $u ]=ok;
	#define DeICEv1_KI(	$u,	$v	) H[$v] = cube[	++ic	];					DeICEv1( 	$u,	$v	);	RW[ $v ]=mod; 						I[ $v ] =ic;
//	#define DeICEv1_KEI(	$u,	$v	) H[$v] = cube[	++ic	];					DeICEv1( 	$u,	$v	);	RW[ $v ]=mod; E[$v] =A[$v] +B[$v] +E[$u];	I[ $v ] =ic;
//	#define DeICEv_K(		$u,	$v	) H[$v] = cube[	++ic	];					DeICEv(		$u,	$v	);	RW[ $v ]=ok;
	#define DeICEv_I(   	$u,	$v	)				++ic;					DeICEv(		$u,	$v	);	RW[ $v ]=ok;							I[ $v ] =ic;	//	I[ $v ] =I[ $u ]+1;
	#define DeICEv_EI( 	$u,	$v	) 				++ic;					DeICEv(		$u,	$v	);	RW[ $v ]=ok;	E[$v] =A[$v] +B[$v] +E[$u];	I[ $v ] =ic;	//	I[ $v ] =I[ $u ]+1;
	#define DeICEv_E(  	$u,	$v	) 				++ic;					DeICEv(		$u,	$v	);	RW[ $v ]=ok;	E[$v] =A[$v] +B[$v] +E[$u];
	#define DeICEv_K( 	$u,	$v	) H[$v]	= cube[	++ic	];					DeICEv(		$u,	$v	);	RW[ $v ]=ok;							
	#define DeICEv_KE(	$u,	$v	) H[$v]	= cube[	++ic	];					DeICEv(		$u,	$v	);	RW[ $v ]=ok;	E[$v] =A[$v] +B[$v] +E[$u];
	#define DeICEv_KEI(	$u,	$v	) H[$v]	= cube[	++ic	];					DeICEv(		$u,	$v	);	RW[ $v ]=ok;	E[$v] =A[$v] +B[$v] +E[$u];	I[ $v ] =ic;	//	I[ $v ] =I[ $u ]+1;
	#define DeICE0u_K(	$u,	$v	) H[0]	= cube[	ic=0	];					DeICE0u(		$u,	$v	);	RW[ $u ]=ok;	
	#define DeICE0u_KE(	$u,	$v	) 								ic=0;	DeICE0u(		$u,	$v	);	RW[ $u ]=ok;	E[$u] =A[$u] +B[$u] +*( (ui64*) cubeZ+1 );
	#define DeICE0u_KEI(	$u,	$v	) 								ic=0;	DeICE0u(		$u,	$v	);	RW[ $u ]=ok;	E[$u] =A[$u] +B[$u] +*( (ui64*) cubeZ+1 );	I[$u]=0;
	#define DeICE0u_E(	$u,	$v	) 								ic=0;	DeICE0u(		$u,	$v	);	RW[ $u ]=ok;	E[$u] =A[$u] +B[$u] +*( (ui64*) cubeZ+1 );
//	#define DeICE0v_K(	$u,	$v	) /* *( (ui64*) (H+$v) )=*( (ui64*) cube ); */ ic=0;	DeICE0v(		$u,	$v	);	RW[ $v ]=ok;	
	#define DeICE0v_KE(	$u,	$v	) /* *( (ui64*) (H+$v) )=*( (ui64*) cube ); */ ic=0;	DeICE0v(		$u,	$v	);	RW[ $v ]=ok;	E[$v] =A[$v] +B[$v] +E[$u];
//	#define DeICE0v_KEI(	$u,	$v	) /* *( (ui64*) (H+$v) )=*( (ui64*) cube ); */ ic=0;	DeICE0v(		$u,	$v	);	RW[ $v ]=ok;	E[$v] =A[$v] +B[$v] +E[$u];	I[ $v ] =ic;	//	I[ $v ] =I[ $u ]+1;
//	#define DeICEzu_K(	$u,	$v	) H[$u] = cube[	ic=zc ];					DeICEzu(		$u		);				
	#define DeICEzu_KEI(	$u		) H[$u] = cube[	ic=zc ];					DeICEzu(		$u		);	RW[ $u ]=ok;	E[$u] =*( (ui64*) cube+1);	I[ $u ] =zc;
//	#define DeICEru_KEI(	$u		) H[$u] = cube[	--ic	];					DeICEru(		$u		);	RW[ $u ]=ok;	E[$u] =E[$v] -A[$u] -B[$u];	I[ $u ] =ic;
	#define DeICEru_KI(	$u		) H[$u] = cube[	--ic	];					DeICEru(		$u		);	RW[ $u ]=ok;							I[ $u ] =ic;

//	#define DeICEzu_KEI(	$u,	$v	) H[$u] = cube[	ic=zc ];					DeICEzu(		$u		);				E[$v] =A[$v] +B[$v] +E[$u];	I[ $v ] =zc; 	//this is not consistent with the incremental statement "[ $v ] =I[ $u ]+1"; zx_KEI variants are impracticable!

//	#define DeICEv_KE_(	$u,	$v	) H[$v] = cubeZ[	++ic ];					DeICEv_(	 	$u,	$v	);	RW[ $v ]=ok;	E[$v] =A[$v] +B[$v] +E[$u];	I[ $v ] =ic;	//	I[ $v ] =I[ $u ]+1;
//	#define DeICEv_KEI_(	$u,	$v	) H[$v] = cubeZ[	++ic ];					DeICEv_(	 	$u,	$v	);	RW[ $v ]=ok;	E[$v] =A[$v] +B[$v] +E[$u];	I[ $v ] =ic;	//	I[ $v ] =I[ $u ]+1;
//	#define DeICEzu_K_(	$u,	$v	) H[$u]=cubeZ[	zcZ	];					DeICEzu_(	$u		);				
	#define DeICEzu_E_(	$u		) 										DeICEzu_(	$u		);				E[$u] =*( (ui64*) cubeZ+1 );
	#define DeICEzu_KE_(	$u		) H[$u]=cubeZ[	zcZ	];					DeICEzu_(	$u		);				E[$u] =*( (ui64*) cubeZ+1 );
//	#define DeICEzu_KEI_(	$u,	$v	) H[$u]=cubeZ[	zcZ	];					DeICEzu_(	$u		);				E[$v] =A[$v] +B[$v] +E[$u];	I[ $v ] =ic;	//	I[ $v ] =I[ $u ]+1;


	#define deICEzc_KE(	$zc		)										deICEr( cube[ $zc ],	Qc, Ac, Bc );			Ec =*( (ui64*) cube+1);



#define AvEXT( $avICE, $cube, $pk, $pq, $avArg, $a, $za, $E0 )	/* "Cube" an ascending list of unsigned integers	*/					\
/*	printf("\r<AvEXT	starting at arg %lld/%lld	E_( %llu ) <	x( %llu ) 		\n", a, za, $E0, x );	*/									\
											zc = 0;			Ac =x-$E0;	Bc =1;										\
	if( $a >=$za){	/* no  args	*/						reICE0(	Ac,			Bc,		$cube, $pq );	*( (ui64*)	$cube+1 ) =x+1;	*pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	pSv0=AvARRAY( $avICE );	/* push new cube with only x		*/	\
	}else{									zc = -1;																		\
		do	{			Ec	=	x +1;		pSv= AvARRAY( $avArg ) + ++$a;												\
			if( SvIOK( *pSv ) ){		x= SvIVX(   *	pSv );																	\
				if(		Ec ==	x )	{								  ++	Bc;	  				}						/*	=+|$	*/	\
				else if(	Ec < 	x )	{	if(	zc==7 ){											*( (ui64*)	$cube+1) = $E0;	*$pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	pSv0=AvARRAY( $avICE );	/* push new cube		*/	\
											zc=0;								$pk=$cube+1;	*( (ui64*)	$cube ) =0;													/* reset cube buffer	*/	\
													reICE0(	Ac,			Bc,		$cube,	$pq );  						/* encode x in cyclum 0	*/	\
										}else{ ++zc;	reICE(	Ac,			Bc,		$pk,	 	$pq );  						/* encode x in cyclum zc */	\
											}				Ac =x -Ec;	Bc=1;	$E0=Ec;								/*	_+|$	*/	\
									}																				\
			}	}	while( $a< $za );																			\
		if(	SvIOK( *pSv ) ){				if(	zc==7 ){											*( (ui64*)	$cube+1) = $E0;	*$pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	pSv0=AvARRAY( $avICE );	/* push new cube		*/	\
																				$pk=$cube+1;	*( (ui64*) $cube ) =0;													/* reset cube buffer	*/	\
													reICE0(	Ac,			Bc,		$cube,$pq );  						/* encode x in cyclum 0	*/	\
										}else{		reICE(	Ac,			Bc,		$pk,  $pq );  						/* encode x in cyclum zc */	\
											}												*( (ui64*)	$cube+1 ) =x+1;	*$pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	pSv0=AvARRAY( $avICE );	/* push new cube		*/	\
		}				}


#define AvNEW( $avICE, $cube, $pk, $pq, $avArg, $a, $za, $E0 )	/* "Cube" an ascending list of unsigned integers	*/					\
	if( pSv0 != AvARRAY( avICE )  ){	printf("\npSv0 is out of sync with avICE going into AvNEW\n");	pSv0=AvARRAY( avICE );	}		\
/*	printf("\r<AvNEW	starting at arg %lld/%lld	E_( %llu ) <	x( %llu ) 		\n", a, za, $E0, x );	*/									\
															Ac =x-$E0;	Bc =1;										\
	if( $a >=$za){	/* no  args	*/				zc = 0;	reICE0(	Ac,			Bc,		$cube, $pq );	*( (ui64*)	$cube+1 ) =x+1;	*pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	pSv0=AvARRAY( $avICE );	/* push new cube with only x		*/	\
	}else{									zc = -1;																		\
		do	{			Ec	=	x +1;		pSv= AvARRAY( $avArg ) + ++$a;												\
			if( SvIOK( *pSv ) ){		x= SvIVX(   *	pSv );																	\
				if(		Ec ==	x )	{								  ++	Bc;	  				}						/*	=+|$	*/	\
				else if(	Ec < 	x )	{	if(	zc==7 ){											*( (ui64*)	$cube+1) = $E0;	*$pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	pSv0=AvARRAY( $avICE );	/* push new cube		*/	\
											zc=0;								$pk=$cube+1;	*( (ui64*)	$cube ) =0;													/* reset cube buffer	*/	\
													reICE0(	Ac,			Bc,		$cube,	$pq );  						/* encode x in cyclum 0	*/	\
										}else{ ++zc;	reICE(	Ac,			Bc,		$pk,	 	$pq );  						/* encode x in cyclum zc */	\
											}				Ac =x -Ec;	Bc=1;	$E0=Ec;								/*	_+|$	*/	\
									}																				\
			/* !SvIOK on argument x treated as a cube boundary directive	*/\
			}else{						if(	zc==7 ){											*( (ui64*)	$cube+1) = $E0;	*$pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	pSv0=AvARRAY( $avICE );	/* push new cube		*/	\
																							*( (ui64*)	$cube ) =0;															/* reset cube buffer	*/	\
													reICE0(	Ac,			Bc,		$cube, $pq );  	*( (ui64*)	$cube+1) = Ec;	*$pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	pSv0=AvARRAY( $avICE );	/* push new cube		*/	\
										}else{		reICE(	Ac,			Bc,		$pk,	 $pq );  	*( (ui64*)	$cube+1) = Ec;	*$pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	pSv0=AvARRAY( $avICE );	/* push new cube		*/	\
											}zc=-1;								$pk=$cube;	*( (ui64*)	$cube ) =0;													/* reset cube buffer	*/	\
			/* ...but we must ignore consecutive !SvIOK's				*/				$pq=$cube +16;						\
				while(	$a< $za )	if( SvIOK( *( pSv= AvARRAY( $avArg ) + ++$a ) ) )										\
								{																			\
								x= SvIVX(   *	pSv );			Ac =x -Ec;	Bc=1;	$E0=Ec;	break;				\
								}																			\
			}	}	while( $a< $za );																			\
		if(	SvIOK( *pSv ) ){				if(	zc==7 ){											*( (ui64*)	$cube+1) = $E0;	*$pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	pSv0=AvARRAY( $avICE );	/* push new cube		*/	\
																				$pk=$cube+1;	*( (ui64*) $cube ) =0;													/* reset cube buffer	*/	\
													reICE0(	Ac,			Bc,		$cube,$pq );  						/* encode x in cyclum 0	*/	\
										}else{		reICE(	Ac,			Bc,		$pk,  $pq );  						/* encode x in cyclum zc */	\
											}												*( (ui64*)	$cube+1 ) =x+1;	*$pq=0;	av_push( $avICE, newSVpvn( $cube, $pq -$cube ) );	pSv0=AvARRAY( $avICE );	/* push new cube		*/	\
		}				}/*	printf("\r	</AvNEW>\n");	*/
