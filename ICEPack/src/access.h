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


extern	void	_av_commit(),
			_sv_commit(),
			_print_mx( unsigned char mx_max, short ix1, short izZ ),
			_init_mx();

#ifdef DEBUG_RACK_L1
	#define dBUG_MkIn(	$caller )	cS=sprintf( aString, "\r^MkIn(   	caller: %4d )	ixI: %d	iCI: %lld	icI: %d\n", $caller, u, iCI, icI );	AvPUSHdBUG( aString, cS );
	#define dBUG_MkOut(	$caller )	cS=sprintf( aString, "\r^MkOut(   	caller: %4d )	ixO: %d	iCO: %lld	icO: %d\n", $caller, u, iCO, icO );	AvPUSHdBUG( aString, cS );
#else
	#define dBUG_MkIn(	$caller )
	#define dBUG_MkOut(	$caller )	
#endif

#define MkIn(		$caller )	ixI =u;							dBUG_MkIn(	$caller );
#define MkOut(	$caller )	ixO =u;		icO =ic;		iCO=iC;	dBUG_MkOut(	$caller );	\
						ixH =u +1;	icH =ic +1;



#if defined( DEBUG_MOD_L3 )
	#define 	dBUG_ReICE($SUFFIX, $u )	if( O[ $u ]==0 ){ cS= sprintf( aString, "\n!	ReICE%s( ... ): mx step u does not seem to have been read-in (O[%d]==0)\n\n", $SUFFIX, $u );	AvPUSHdBUG( aString, cS );	}
#else
	#define 	dBUG_ReICE($SUFFIX, $u )
#endif


#ifdef		DEBUG_SET_L2
	#ifdef	DEBUG_SET_L3

		#define	dBUG_xINTRALOC( $MACRO_NAME)	cS=	sprintf( aString, "\r........%16s:	cube %3lld  		x( %5llu )		cube E( %5llu )		CS: %lld	sv( %llx )\n\t",		\
															$MACRO_NAME,		iC,				x,			*( (ui64*) cube+1),	CS,		&*sv		);	AvPUSHdBUG( aString, cS );	\
				if( zc !=	zcOf(	cube ) )	{	cS =	sprintf( aString, "\r!	%s: zc (was) out of sync with (char*) cube.\n", $MACRO_NAME);							AvPUSHdBUG( aString, cS );	\
					zc =	zcOf(	cube ); 	}
	#else
		#define	dBUG_xINTRALOC( $MACRO_NAME)	cS =	sprintf( aString, "\r........%16s:	cube %3lld  		x( %5llu )		cube E( %5llu )		CS: %lld	sv( %llx )\n\t",		\
															$MACRO_NAME,		iC,				x,			*( (ui64*) cube+1),	CS,		&*sv		);	AvPUSHdBUG( aString, cS );
	#endif
	#define		dBUG_xINTERLOC(	$MACRO_NAME )	cS=	sprintf( aString, "\r........%16s:	cubes %3lld..%-3lld\t\tx( %5llu )\t	cube E( %5llu )		CS: %lld	sv( %llx )		cube_E( %5llu )	CSZ: %lld	svZ( %llx )	\n\t",			\
															$MACRO_NAME,		iC,	iC+1,		x,			*( (ui64*) cube+1),	CS,		&*sv,	*( (ui64*) cubeZ+1),	CSZ,	&*svZ		);	AvPUSHdBUG( aString, cS );
#else
	#define		dBUG_xINTERLOC(	$MACRO_NAME )
	#ifdef	DEBUG_SET_L3
		#define	dBUG_xINTRALOC( $MACRO_NAME)	if( zc != zcOf(	cube )	{	\
												cS =	sprintf( aString, "\r!	%s: zc (was) out of sync with (char*) cube.\n", $MACRO_NAME);						AvPUSHdBUG( aString, cS );	\
												zc = zcOf(	cube );	}
	#else
		#define	dBUG_xINTRALOC( $MACRO_NAME)
	#endif
#endif


#define	MxINIT	while( tena_zc != -1 )	RW[ tena_zc-- ]=null;


/*		ANTELOC		/*	Vector (U) low-bounds mod scope of x as cyclum (zc) at end of cube iC					*/
#define	ANTELOC		/*	Vector (U) low-bounds mod scope of x as cyclum (zc) at end of cube iC					*/	\
		MxINIT;				DeICEzu_KE_( 255 );																dBUG_xINTERLOC("ANTELOC");

/*		INTERLOC			Vector (V) high-bounds mod scope of x as cyclum (0) at start of cube iC+1					*/
#define	INTERLOC		/*	Vector (V) high-bounds mod scope of x as cyclum (0) at start of cube iC+1					*/	\
	CS = SvCUR(	sv );			tena_zc = 	zc = zcOf(	cube );													\
	u=0; v=1; H[0] = cube[ 0];	DeICE0u(   	0,	1	);		E[ 0 ] =	*( (ui64*) cubeZ+1 )	+A[0] +B[0];				dBUG_xINTERLOC("INTERLOC");	\
	I[0] =icI =ic =0;	iCI=iC;								RW[ 0  ]= mod;



/*		INTRALOC			Vectors (U, V) scan cube iC					tracking reset							*/
#define	INTRALOC		/*	Vectors (U, V) intralocate mod scope of x as cycla (ic-1, ic) in cube iC						*/	dBUG_xINTRALOC("INTRALOC");	\
	iCI	=	iC;					CS=SvCUR( sv );			svZ=*( AvARRAY( avICE) +( iC -1 ) );						\
					cubeZ= SvPVbyte(	svZ, CSZ );			zcZ=zcOf(	cubeZ );				/*	goto	_loca;	*/


/*		INTRALOC1Up	new	Vectors (U, V) intralocate mod scope of x as cycla (ic-1, ic) in cube iC+1					*/
#define	INTRALOC1Up	/*	Vectors (U, V) intralocate mod scope of x as cycla (ic-1, ic) in cube iC+1					*/	dBUG_xINTRALOC("INTRALOC1Up");	\
	iCI	=	iC;				\
	if( zC  ==	iC){					CS =SvCUR(	sv );			E_ = 	*( (ui64*) cube +1);				goto	_epiloc;	\
	}else{ svZ=sv;		cubeZ=cube;	CSZ=SvCUR(	sv );			cube = SvPVbyte( 	sv =*( pSv0 + ++iC ), CS );					\
		 zcZ=zcOf(	cubeZ );	}/*																		_loca:	\
							tena_zc = 	zc=zcOf(		cube );													\
							DeICE0u_K(	0, 	1	);		E[ 0 ] = 	*( (ui64*) cubeZ+1)	+A[ 0 ] +B[ 0 ];					\
	while( x >E[ u ] ){			DeICEv_I(	u,	v	);		E[ v ] =	E[ u ]			+A[ v ] +B[ v ];  u=v++; }			\
	I[ u] =icI =ic;				*/
		







/*		ReINTRALOC			Vectors (U, V) intralocate mod scope of next x as cycla (ic-1, ic) in following cube (++iC)		*/
#define	ReINTRALOC		/*	Vectors (U, V) intralocate mod scope of next x as cycla (ic-1, ic) in following cube (++iC)		*/	dBUG_xINTRALOC("ReINTRALOC");	\
/*	iCI	=	iC;	<--negatori; cube run continues */\
						/*	tena_zc = 	zc=zcOf(	cube );														\
							DeICE0u_K(	0,	1 );			E[ 0 ] =	*( (ui64*)	cubeZ+1)	+A[ 0 ] +B[ 0 ]; 				\
	while( x >E[ u ] ){			DeICEv_I(	u,	v	);		E[ v ] =	E[ u ]			+A[ v ] +B[ v ];  u=v++; }			\
	I[ u] =icI =ic;			*/	/*so, this was entirely redundant and does nothing now, but	*/
							/*I'll keep it for the uniformity of the debugging macros		*/





/*		CoINTRaLOC				Vectors (U, V) intralocate mod scope of next x as cycla (ic-1, ic) in current cube (iC)		*/
#define	CoINTRaLOC			/*	Vectors (U, V) intralocate mod scope of next x as cycla (ic-1, ic) in current cube (iC)		*/	dBUG_xINTRALOC("CoINTRaLOC");	\
	if(							x >E[ u ]	){																	\
/* mod range starts.	*/																						\
		if( ixI == 0xFF){																						\
			if(		RW[ v ]&mod ){ MkIn(8);		ReICEuO(	u, v );										u=v++;	\
				if(				x >E[ u ] ){	ReICEuOx(	u, v );					deIceV_KEI();			u=v++;	\
					while(		x >E[ u ] ){	Ox[v]=Ox[u]+Q[u];						DeICEv_KEI( u, v );		u=v++; }	\
					}\
			}else if(	RW[ u ]&mod	){ MkIn(9);	ReICEuO(	u, v );	if( RW[ v ] == null )	deIceV_KEI();			u=v++;	\
				while(			x >E[ u ] ){	Ox[v]=Ox[u]+Q[u];						DeICEv_KEI( u, v );		u=v++; }	\
\
/* nvm. */	}else{						 /*	Ox[v]=Ox[u]+Q[u];*/	if( RW[ v ] == null )	deIceV_KEI();			u=v++;	\
				while(			x >E[ u ] ){ /*	Ox[v]=Ox[u]+Q[u];*/					DeICEv_KEI( u, v );		u=v++; }	icI =ic; \
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
		if( ixI == 0xFF){																						iCI=iC;	\
			if(		RW[ v ]&mod ){ MkIn(16);	ReICEuO(	u, v );										u=v++;	\
				if(				ic< zc	){	ReICEuOx(	u, v );					deIceV_KEI();			u=v++;	\
					while(		ic< zc	){	Ox[v]=Ox[u]+Q[u];						DeICEv_KEI(	u, v );	u=v++; }	\
					}\
			}else if(	RW[ u ]&mod	){ MkIn(17);	ReICEuO(	u, v );	if( RW[ v ] == null )	deIceV_KEI();			u=v++;	\
				while(			ic< zc	){	Ox[v]=Ox[u]+Q[u];						DeICEv_KEI(	u, v );	u=v++; }	\
\
			}else	/* false start.	*/	{	I[ tena_zc ] =I[u] +( tena_zc-u); v=( u=tena_zc )+1;	DeICEzu_KE(	u, v );	icI =zc;	\
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




#define _EPILOC	/* printf("\nEPILOC	ixI: %d	ixO: %d	icI: %d	icO: %d\n", ixI, ixO, icI, icO );	*/\
		if( ixI == 0xFF){		MkIn(32);			}															\
		do	{	if(	x ==	E[ u ] )	{				++	B[ u ];	  ++	E[ u ];		}							\
				else		{	uMOD;	A[ v ] =x -E[ u ];	B[ v ]=1;		E[ v ] =x+1;	ReICEuOx( u, v );	u=v++;	}	\
				if(	za == a )	break;																		\
					x =	ARG( ++	a );	\
			} while( 1 );		MkOut( 7 );										ReICEuOx( u, v );







#define NEW( $E0 )															pSv0=AvARRAY( avICE );	\
	*( (ui64*) 		buf		)=0;											\
	*( (ui64*) 		buf+1	)=0;	pk =buf;	pq =buf +16;		a=0; 	E_=0;	\
	AvEXT(  avICE,	buf,			pk,		pq,		avArg,	a, za,	E_ 		);

#define EPILOC( $E0 )														\
/*	if( dsc || rSeqIns[0] || rSeqCut[0] )	_av_commit();		*/			/*	else		pSv0=AvARRAY( avICE ); */	\
	*( (ui64*)			buf		)=0;											\
	*( (ui64*)			buf+1	)=0;	pk =buf;	pq =buf +16;						\
	AvEXT(  avICE,	buf,			pk,		pq,		avArg,	a, za,	$E0		);







/*		SvCOMMIT				Mark-out the modification range and call _sv_commit() to re-encode the SV[s]					*/
#define	SvCOMMIT			/*	Mark-out the modification range and call _sv_commit() to re-encode the SV[s]					*/	dBUG_xINTRALOC( "RACK" );	\
	if( ixI == 0xFF ){	/* envelope not marked in yet 	*/															\
		if(		RW[ v ]&mod )	{	MkIn( 1 );			ReICEuO( u, v );	u=v++; ReICEuOx( u, v );	MkOut( 1 );	_sv_commit();	\
		}else if(	RW[ u ]&mod )	{	MkIn( 2 );			ReICEuO( u, v );							MkOut( 2 );	_sv_commit();	\
		}else		/* no mods */	{ /* shunt pointers	*/	cubeZ= cube; CSZ=CS; svZ=sv; zcZ= zc;		/* nothing to rack */		\
								}					\
	}else if(		RW[ v ]&mod )	{					ReICEuOx( u, v );	u=v++; ReICEuOx( u, v );	MkOut( 4 );	_sv_commit();	\
	}else if(		RW[ u ]&mod )	{					ReICEuOx( u, v );							MkOut( 5 );	_sv_commit();	\
	}else						{					Ox[v]=Ox[u] +Q[u];							MkOut( 6 );	_sv_commit();	\
								}

