#define	cui8	const	unsigned	char	
#define	ui08			unsigned	char	
#define	ui16			unsigned	short 
#define	ui32		long	unsigned	int 
#define	si64	long long			int 
#define	ui64	long long	unsigned	int 
#define	ui64	long long	unsigned	int 

	#include	"_ICE.h"
	#include	"_AvMOD.h"
	#include	"_AvSEQ.h"	/*	function-like macros for array "resequencing"	*/	

/*
Dear Claude,

I am writing a Perl XS module in C which provides an object class to instantiate a mutable data structure I am categorically defining as a Compressed Truth Vector.  The intended purpose is to be used for working ID tables in mission critical server processes, which demands a high performance level.

*/

/*	Copyright 2026 Peter Arlen Schmidt

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	    http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

extern	void	_rack1x(),
			_print_mx( unsigned char mx_max),
			_init_mx();

#ifdef DEBUG_RACK_L1
	#define dBUG_MkIn(	$caller )	cS=sprintf( aString, "\r^MkIn(   	caller: %4d )	ix0: %d	iC0: %lld	ic0: %d\n", $caller, u, iC0, ic0 );	AvPUSHaSTRING( aString, cS );
	#define dBUG_MkOut(	$caller )	cS=sprintf( aString, "\r^MkOut(   	caller: %4d )	ixZ: %d	iCZ: %lld	icZ: %d\n", $caller, u, iCZ, icZ );	AvPUSHaSTRING( aString, cS );
#else
	#define dBUG_MkIn(	$caller )
	#define dBUG_MkOut(	$caller )	
#endif

#define MkIn(		$caller )	ix0 =u;							dBUG_MkIn(	$caller );
#define MkOut(	$caller )	ixZ =u;		icZ =ic;		iCZ=iC;	dBUG_MkOut(	$caller );	\
						ixN =u +1;	icN =ic +1;



#if defined( DEBUG_MOD_L3 )
	#define 	dBUG_ReICE($SUFFIX, $u )	if( O[ $u ]==0 ){ cS= sprintf( aString, "\n!	ReICE%s( ... ): mx step u does not seem to have been read-in (O[%d]==0)\n\n", $SUFFIX, $u );	AvPUSHaSTRING( aString, cS );	}
#else
	#define 	dBUG_ReICE($SUFFIX, $u )
#endif

#define						OVERSTEP( $Q,	$A,	$B,	$E,	$RW)	ic=zc; 								\
										$A=						0xFFFFFFFFFFFFFFFF -$E;		$RW= null;	\
								$Q=0;	$B=0;			$E=		0xFFFFFFFFFFFFFFFF;
/*								^		^ 				^								^ flag the error state.
								Set		|				* E (or "Epsilon") is the absolute value which bounds the cyclum.
								field		|				   Past end of the avICE, the maximum integer is the final frontier.
								lengths	* A and B are the relative phase values (negative and positive, respectively).
								to null.	   These define a logical cyclum.
								This is	   To set the negative phase value to the maximum integer minus Epsilon
								a fake	   and to make the positive value null, is to set a false point at infinity (practically)
								data	   so that any accessor functions which actually attempt to operate on this over-cyclum
								point.	   will not generate garbage output.
*/
#define mxOVERSTEP( $v )		OVERSTEP( Q[$v], A[$v], B[$v], E[$v], RW[$v] );
#ifdef		DEBUG_SET_L2
	#ifdef	DEBUG_SET_L3

		#define	dBUG_xINTRALOC( $MACRO_NAME)	cS=	sprintf( aString, "\r........%16s:	cube %3lld  		x( %5llu )		cube E( %5llu )		CS: %lld	sv( %llx )\n\t",		\
															$MACRO_NAME,		iC,				x,			*( (ui64*) cube+1),	CS,		&*sv		);	AvPUSHaSTRING( aString, cS );	\
				if( zc !=	zcOf( *( (ui64*) cube ) ) )	{	cS =	sprintf( aString, "\r!	%s: zc (was) out of sync with (char*) cube.\n", $MACRO_NAME);							AvPUSHaSTRING( aString, cS );	\
					zc =	zcOf( *( (ui64*) cube ) ); 	}
	#else
		#define	dBUG_xINTRALOC( $MACRO_NAME)	cS =	sprintf( aString, "\r........%16s:	cube %3lld  		x( %5llu )		cube E( %5llu )		CS: %lld	sv( %llx )\n\t",		\
															$MACRO_NAME,		iC,				x,			*( (ui64*) cube+1),	CS,		&*sv		);	AvPUSHaSTRING( aString, cS );
	#endif
	#define		dBUG_xINTERLOC(	$MACRO_NAME )	cS=	sprintf( aString, "\r........%16s:	cubes %3lld..%-3lld\t\tx( %5llu )\t	cube E( %5llu )		CS: %lld	sv( %llx )		cube_E( %5llu )	CSZ: %lld	svZ( %llx )	\n\t",			\
															$MACRO_NAME,		iC,	iC+1,		x,			*( (ui64*) cube+1),	CS,		&*sv,	*( (ui64*) cubeZ+1),	CSZ,	&*svZ		);	AvPUSHaSTRING( aString, cS );
#else
	#ifdef	DEBUG_SET_L3
		#define	dBUG_xINTRALOC( $MACRO_NAME)	if( zc != zcOf( *( (ui64*) cube ) ) )	{	\
												cS =	sprintf( aString, "\r!	%s: zc (was) out of sync with (char*) cube.\n", $MACRO_NAME);						AvPUSHaSTRING( aString, cS );	\
												zc = zcOf( *( (ui64*) cube ) );	}
	#else
		#define	dBUG_xINTRALOC( $MACRO_NAME)

	#define		dBUG_xINTERLOC(	$MACRO_NAME )
	#endif
#endif





/*		ANTELOC		/*	Vector (U) low-bounds mod scope of x as cyclum (zc) at end of cube iC					*/
#define	ANTELOC		/*	Vector (U) low-bounds mod scope of x as cyclum (zc) at end of cube iC					*/	\
		do RW[ tena_zc ]=null;  while( --tena_zc != -1 );	zcZ = zcOf(	  	*( (ui64*) cubeZ ) );								\
		*( (ui64*) Qx )=0;	*( (ui64*) Qx +1 )=0;				\
		H[ 255 ] = cubeZ[ zcZ];	DeICEzu_( 255 );				E[ 255 ] =	*( (ui64*) cubeZ+1 );							dBUG_xINTERLOC("ANTELOC");

/*		INTERLOC			Vector (V) high-bounds mod scope of x as cyclum (0) at start of cube iC+1					*/
#define	INTERLOC		/*	Vector (V) high-bounds mod scope of x as cyclum (0) at start of cube iC+1					*/	\
	CS = SvCUR(	sv );					tena_zc = 	zc = zcOf(	  	*( (ui64*) cube ) );								\
	u=0; v=1; H[0] = cube[ 0];	DeICE0u(   	0,	1	);		E[ 0 ] =	*( (ui64*) cubeZ+1 )	+A[0] +B[0];				dBUG_xINTERLOC("INTERLOC");	\
	I[0] =ic0 =ic =0;	iC0=iC;								RW[ 0  ]= mod;

/*		INTRALOC			Vectors (U, V) scan cube iC					tracking reset							*/
#define	INTRALOC		/*	Vectors (U, V) intralocate mod scope of x as cycla (ic-1, ic) in cube iC						*/	dBUG_xINTRALOC("INTRALOC");	\
	do RW[ tena_zc ]=null;  while( --tena_zc != -1 );	/* initialize matrix */							CS=SvCUR( sv );		\
	*( (ui64*) Qx )=0;	*( (ui64*) Qx +1 )=0;																		\
	u=0; v=1; 				DeICE0u_K(	0,	1 );																\
	if(			iC==0)									E[ 0 ] = 					 A[ 0 ] +B[ 0 ];					\
	else{ svZ=	iC==1	? *( AvARRAY( avICE)		)															\
						: *( AvARRAY( avICE) +( iC -1 ) );															\
		cubeZ= SvPVbyte_nolen(	svZ );						/*	printf(".");*/									\
					CSZ =SvCUR(	sv );							/*	printf("%c", 181);*/								\
														E[ 0 ] =	*( (ui64*)	cubeZ+1)	+A[ 0 ] +B[ 0 ]; 				\
		}							tena_zc = 	zc=zcOf(			*( (ui64*)	cube ) );								\
	while( x >E[ u ] ){			DeICEv_I(	u,	v	);		E[ v ] =	E[ u ]			+A[ v ] +B[ v ];  u=v++; }			\
	I[ u] =ic0 =ic;		iC0=iC;

/*		INTRALOC1Up		Vectors (U, V) intralocate mod scope of x as cycla (ic-1, ic) in cube iC+1					*/
#define	INTRALOC1Up	/*	Vectors (U, V) intralocate mod scope of x as cycla (ic-1, ic) in cube iC+1					*/	dBUG_xINTRALOC("INTRALOC1Up");	\
	do RW[ tena_zc ]=null;  while( --tena_zc != -1 );	/* initialize matrix */												\
	*( (ui64*) Qx )=0;	*( (ui64*) Qx +1 )=0;																		\
	u=0;  v=1;											Ev =		*( (ui64*) cube +1);								\
	if( zC  ==	iC){		CS =SvCUR(	sv );			EXTRALOC(	Ev );									return;			\
	}else{ cubeZ=cube;	CSZ=SvCUR(	sv );	svZ=sv;  		zcZ=zcOf(		*( (ui64*) cubeZ ) );								\
		  cube = SvPVbyte_nolen( 	sv =*( pSv0 + ++iC ));			/*	printf(".");*/									\
					CS =SvCUR(	sv );							/*	printf("%c", 198);*/								\
									tena_zc = 	zc=zcOf(			*( (ui64*) cube ) );								\
							DeICE0u_K(	0, 	1	);		E[ 0 ] = 	Ev				+A[ 0 ] +B[ 0 ];					\
		while( x >E[ u ] ){		DeICEv_I(	u,	v	);		E[ v ] =	E[ u ]			+A[ v ] +B[ v ];  u=v++; }			\
		I[ u] =ic0 =ic;	iC0=iC;	\
		}


/*		ReINTRALOC			Vectors (U, V) intralocate mod scope of next x as cycla (ic-1, ic) in following cube (++iC)		*/
#define	ReINTRALOC		/*	Vectors (U, V) intralocate mod scope of next x as cycla (ic-1, ic) in following cube (++iC)		*/	dBUG_xINTRALOC("ReINTRALOC");	\
	do RW[ tena_zc ]=null;  while( --tena_zc != -1 );	/* initialize matrix */												\
	*( (ui64*) Qx )=0;	*( (ui64*) Qx +1 )=0;					\
	u=0; v=1; 				DeICE0u_K(	0,	1 );			E[ 0 ] =	*( (ui64*)	cubeZ+1)	+A[ 0 ] +B[ 0 ]; 				\
									tena_zc = 	zc=zcOf(			*( (ui64*)	cube ) );								\
	while( x >E[ u ] ){			DeICEv_I(	u,	v	);		E[ v ] =	E[ u ]			+A[ v ] +B[ v ];  u=v++; }			\
	I[ u] =ic0 =ic;		iC0=iC;



/*		CoINTRaLOC				Vectors (U, V) intralocate mod scope of next x as cycla (ic-1, ic) in current cube (iC)		*/
#define	CoINTRaLOC			/*	Vectors (U, V) intralocate mod scope of next x as cycla (ic-1, ic) in current cube (iC)		*/	dBUG_xINTRALOC("CoINTRaLOC");	\
	if(							x >E[ u ]	){																	\
/* mod range starts.	*/																						\
		if( ix0 == 0xFF){																						\
			if(		RW[ v ]&mod ){ MkIn(8);	ReICEuO(	u, v );										u=v++;	\
				if(				x >E[ u ] ){	ReICEuOx(	u, v );					deIceV_KEI();			u=v++;	\
					while(		x >E[ u ] ){	Ox[v]=Ox[u]+Q[u];						DeICEv_KEI( u, v );		u=v++; }	\
					}\
			}else if(	RW[ u ]&mod	){ MkIn(9);	ReICEuO(	u, v );	if( RW[ v ] == null )	deIceV_KEI();			u=v++;	\
				while(			x >E[ u ] ){	Ox[v]=Ox[u]+Q[u];						DeICEv_KEI( u, v );		u=v++; }	\
\
/* nvm. */	}else{						 /*	Ox[v]=Ox[u]+Q[u];*/	if( RW[ v ] == null )	deIceV_KEI();			u=v++;	\
				while(			x >E[ u ] ){ /*	Ox[v]=Ox[u]+Q[u];*/					DeICEv_KEI( u, v );		u=v++; }	ic0 =ic; \
				}																							\
/* mod range continues.	*/																					\
		}else if(		RW[ v ]&mod ){			ReICEuOx(	u, v );										u=v++;	\
				if(				x >E[ u ] ){	ReICEuOx(	u, v );					deIceV_KEI();			u=v++;	\
					while(		x >E[ u ] ){	Ox[v]=Ox[u]+Q[u];						DeICEv_KEI( u, v );		u=v++; }	\
					}\
		}else if(		RW[ u ]&mod	){			ReICEuOx(	u, v );	if( RW[ v ] == null )	deIceV_KEI();			u=v++;	\
				while (			x >E[ u ] ){	Ox[v]=Ox[u]+Q[u];						DeICEv_KEI( u, v );		u=v++; }	\
\
		}else							{	Ox[v]=Ox[u]+Q[u];		if( RW[ v ] == null )	deIceV_KEI();			u=v++;	\
				while (			x >E[ u ] )	{	Ox[v]=Ox[u]+Q[u];						DeICEv_KEI( u, v );		u=v++; }	\
		}								}																



							/*	Vectors (U, V) interlocate mod scope of next x as cycla (zc, 0), bridging cubes ( iC, iC+1 ).	*/
#define	CoINTERLOC			/*	Vectors (U, V) interlocate mod scope of next x as cycla (zc, 0), bridging cubes ( iC, iC+1 ).	*/	dBUG_xINTRALOC("CoINTERLOC");	\
	if(							ic< zc	){																	\
		/* mod range starts.	*/																				\
		if( ix0 == 0xFF){																						iC0=iC;	\
			if(		RW[ v ]&mod ){ MkIn(16);	ReICEuO(	u, v );										u=v++;	\
				if(				ic< zc	){	ReICEuOx(	u, v );					deIceV_KEI();			u=v++;	\
					while(		ic< zc	){	Ox[v]=Ox[u]+Q[u];						DeICEv_KEI(	u, v );	u=v++; }	\
					}\
			}else if(	RW[ u ]&mod	){ MkIn(17);	ReICEuO(	u, v );	if( RW[ v ] == null )	deIceV_KEI();			u=v++;	\
				while(			ic< zc	){	Ox[v]=Ox[u]+Q[u];						DeICEv_KEI(	u, v );	u=v++; }	\
\
			}else	/* false start.	*/	{	I[ tena_zc ] =I[u] +( tena_zc-u); v=( u=tena_zc )+1;	DeICEzu_KE(	u, v );	ic0 =zc;	\
									}																	\
		/* mod range continues.	*/\
		}else if(		RW[ v ]&mod ){			ReICEuOx(	u, v );										u=v++;	\
				if(				ic< zc	){	ReICEuOx(	u, v );					deIceV_KEI();			u=v++;	\
					while(		ic< zc	){	Ox[v]=Ox[u]+Q[u];						DeICEv_KEI(	u, v );	u=v++; }	\
					}\
		}else if(		RW[ u ]&mod	){			ReICEuOx(	u, v );	if( RW[ v ] == null )	deIceV_KEI();			u=v++;	\
				while(			ic< zc	){	Ox[v]=Ox[u]+Q[u];						DeICEv_KEI(	u, v );	u=v++; }	\
\
		}else							{	Ox[v]=Ox[u]+Q[u];		if( RW[ v ] == null )	deIceV_KEI();			u=v++;	\
				while(			ic< zc	){	Ox[v]=Ox[u]+Q[u];						DeICEv_KEI(	u, v );	u=v++; }	\
		}								}																	\
	tena_zc +=zc +1;




#define EPILOC	printf("\nEPILOC	ix0: %d	ixZ: %d	ic0: %d	icZ: %d\n", ix0, ixZ, ic0, icZ );	\
		if( ix0 == 0xFF){		MkIn(32);			}															\
		do	{	if(	x ==	E[ u ] )	{				++	B[ u ];	  ++	E[ u ];		}							\
				else		{	uMOD;	A[ v ] =x -E[ u ];	B[ v ]=1;		E[ v ] =x+1;	ReICEuOx( u, v );	u=v++;	}	\
				if(	za == a )	break;																		\
					x =	ARG( ++	a );	\
			} while( 1 );		MkOut( 7 );										ReICEuOx( u, v );







#define NEW( $E0 )															pSv0=AvARRAY( avICE );	\
	*( (ui64*) 		buf		)=0;											\
	*( (ui64*) 		buf+1	)=0;	pk =buf;	pq =buf +16;		a=0; 	E_=0;	\
	AvEXT(  avICE,	buf,			pk,		pq,		avArg,	a, za,	E_ 		);

#define EXTRALOC( $E0 )														\
	if( dsc || rSeqIns[0] || rSeqCut[0] )	_av_commit();					/*	else		pSv0=AvARRAY( avICE ); */	\
	*( (ui64*)			buf		)=0;											\
	*( (ui64*)			buf+1	)=0;	pk =buf;	pq =buf +16;						\
	AvEXT(  avICE,	buf,			pk,		pq,		avArg,	a, za,	$E0		);

#define EXTRALOCcp( $E0 )														\
	if( dsc || rSeqIns[0] || rSeqCut[0] )	_av_commit();					/*	else		pSv0=AvARRAY( avICE ); */	\
	*( (ui64*)			buf		)=0;											\
	*( (ui64*)			buf+1	)=0;	pk =buf;	pq =buf +16;				E_=$E0;	\
	AvEXT(  avICE,	buf,			pk,		pq,		avArg,	a, za,	E_		);







/*		RACK				Mark-out the modification range and call _rack1x() to re-encode the SV[s]						*/
#define	RACK			/*	Mark-out the modification range and call _rack1x() to re-encode the SV[s]						*/	dBUG_xINTRALOC( "RACK" );	\
	if( ix0 == 0xFF ){	/* envelope not marked in yet 	*/															\
		if(		RW[ v ]&mod )	{	MkIn( 1 );			ReICEuO( u, v );	u=v++; ReICEuOx( u, v );	MkOut( 1 );	iC0==iCZ? _rack1x(): _rackXx();	\
		}else if(	RW[ u ]&mod )	{	MkIn( 2 );			ReICEuO( u, v );							MkOut( 2 );	iC0==iCZ? _rack1x(): _rackXx();	\
		}else		/* no mods */	{ /* shunt pointers	*/	cubeZ= cube; CSZ=CS; svZ=sv; zcZ= zc;			/* nothing to rack */		\
								}					\
	}else if(		RW[ v ]&mod )	{					ReICEuOx( u, v );	u=v++; ReICEuOx( u, v );	MkOut( 4 );	iC0==iCZ? _rack1x(): _rackXx();	\
	}else if(		RW[ u ]&mod )	{					ReICEuOx( u, v );							MkOut( 5 );	iC0==iCZ? _rack1x(): _rackXx();	\
	}else						{					Ox[v]=Ox[u] +Q[u];							MkOut( 6 );	iC0==iCZ? _rack1x(): _rackXx();	\
								}

