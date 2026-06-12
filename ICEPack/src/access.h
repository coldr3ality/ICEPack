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
			_sv_commitx(),
			_print_mx( unsigned char mx_max, short ix1, short izZ ),
			_init_mx();

#ifdef DEBUG_SvCOMMIT_L1
	#define dBUG_MkIn	cS=sprintf( aString, "\r^MkIn  	line: %lld	ixM: %d	iCI: %lld	icI: %d\n",	__LINE__, u, iCI, icI );	AvDBUG_PUSH( aString, cS );
	#define dBUG_MkOut	cS=sprintf( aString, "\r^MkOut 	line: %lld	izM: %d	iCO: %lld	icO: %d\n",	__LINE__, u, iCO, icO );	AvDBUG_PUSH( aString, cS );
	#define dBUG_MkOutx	cS=sprintf( aString, "\r^MkOutx 	line: %lld	izM: %d	iCO: %lld	icO: %d\n",	__LINE__, u, iCO, icO );	AvDBUG_PUSH( aString, cS );
#else
	#define dBUG_MkIn
	#define dBUG_MkOut
	#define dBUG_MkOutx
#endif

#define MkIn		ixM	= u;														dBUG_MkIn;
#define MkOut	izM=u;	inM=v;	ixH=v; /*	icH=ic+1;	*/	icO = ic;			iCO = iC;	dBUG_MkOut;
#define MkOutx	izM=u-1;	inM=u;	ixH=v; /*	icH=ic+1;	*/	icO = ic;			iCO = iC;	dBUG_MkOutx;
#ifdef		DEBUG_ACCESS_L2
	#ifdef	DEBUG_ACCESS_L3

		#define	dBUG_xINTRALOC( $MACRO_NAME)	cS=	sprintf( aString, "\r........%16s line %lld:	*Epsilon( cube%lld ): %-5llu ( 0x%llX) 		x: %5llu ( 0x%llX )			CS: %lld	sv( %llx )\n\t",		\
															$MACRO_NAME,	__LINE__,	iC,	*Epsilon( cube ),*Epsilon( cube ),		x,		x,				CS,		&*sv		);	AvDBUG_PUSH( aString, cS );	\
				if( zc !=	zcOf(	cube ) )	{	cS =	sprintf( aString, "\r!	%s: zc (was) out of sync with (char*) cube.\n", $MACRO_NAME);							AvDBUG_PUSH( aString, cS );	\
					zc =	zcOf(	cube ); 	}
	#else
		#define	dBUG_xINTRALOC( $MACRO_NAME)	cS =	sprintf( aString, "\r........%16s line %lld:	*Epsilon( cube%lld ): %-5llu ( 0x%llX) 		x: %5llu ( 0x%llX )			CS: %lld	sv( %llx )\n\t",		\
															$MACRO_NAME, __LINE__,	iC,	*Epsilon( cube ),*Epsilon( cube ),		x,		x,				CS,		&*sv		);	AvDBUG_PUSH( aString, cS );
	#endif
	#define		dBUG_xINTERLOC(	$MACRO_NAME )	cS=	sprintf( aString, "\r........%16s line %lld:	cubes %3lld..%-3lld\t\tx( %5llu )\t	cube E( %5llu )		CS: %lld	sv( %llx )		cube_E( %5llu )	CSZ: %lld	svZ( %llx )	\n\t",			\
															$MACRO_NAME,  __LINE__,	iC,	iC+1,		x,			*( (ui64*) cube+1),	CS,		&*sv,	*( (ui64*) cubeZ+1),	CSZ,	&*svZ		);	AvDBUG_PUSH( aString, cS );
#else
	#define		dBUG_xINTERLOC(	$MACRO_NAME )
	#ifdef		DEBUG_ACCESS_L3
		#define	dBUG_xINTRALOC( $MACRO_NAME)	if( zc != zcOf(	cube )	{	\
												cS =	sprintf( aString, "\r!	%s: zc (was) out of sync with (char*) cube.\n", $MACRO_NAME);						AvDBUG_PUSH( aString, cS );	\
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
	I[0] =icI =ic =0;	iCI=iC;		RW[ 0  ]= mod;



/*		INTRALOC			Vectors (U, V) scan cube iC					tracking reset							*/
#define	INTRALOC		/*	Vectors (U, V) intralocate mod scope of x as cycla (ic-1, ic) in cube iC						*/	\
							CS=SvCUR( sv );	svZ=*( AvARRAY( avICE) +( iC -1 ) );									\
		iCI = iC;	cubeZ= SvPVbyte(	svZ, CSZ );												zcZ=zcOf( cubeZ );		dBUG_xINTRALOC("INTRALOC");	\


/*		INTRALOC1Up		Vectors (U, V) intralocate mod scope of x as cycla (ic-1, ic) in cube iC+1					*/
#define	INTRALOC1Up	/*	Vectors (U, V) intralocate mod scope of x as cycla (ic-1, ic) in cube iC+1					*/	\
	if( zC  !=	iC ){	cubeZ=cube;	CSZ=SvCUR(	sv );	svZ=sv;	cube = SvPVbyte( sv =*( pSv0 + ++iC ), CS );	zcZ=zcOf( cubeZ );		\
	}else{					CS =SvCUR(	sv );			E_ = 	*( (ui64*) cube +1);				goto	_epiloc;		\
		} iCI = iC;																								dBUG_xINTRALOC("INTRALOC1Up");

/*		INTRALOC1Up_EX		Vectors (U, V) intralocate mod scope of x as cycla (ic-1, ic) in cube iC+1  (exclusion op ver.)	*/
#define	INTRALOC1Up_EX	/*	Vectors (U, V) intralocate mod scope of x as cycla (ic-1, ic) in cube iC+1  (exclusion op ver.)	*/	\
	if( zC !=	iC ){	cubeZ=cube;	CSZ=SvCUR(	sv );	svZ=sv;	cube = SvPVbyte( sv =*( pSv0 + ++iC ), CS );	zcZ=zcOf( cubeZ );		\
	}else{					CS =SvCUR(	sv );			miss+=1+za-a;					E1	goto	_exit_2;		\
		}  iCI = iC;																							dBUG_xINTRALOC("INTRALOC1Up_EX");








/*		ReINTRALOC			Vectors (U, V) intralocate mod scope of next x as cycla (ic-1, ic) in following cube (++iC)		*/
#define	ReINTRALOC		/*	Vectors (U, V) intralocate mod scope of next x as cycla (ic-1, ic) in following cube (++iC)		*/	dBUG_xINTRALOC("ReINTRALOC");	\
/*	iCI	=	iC;	<--negatori; cube run continues */\
						/*	tena_zc = 	zc=zcOf(	cube );														\
							DeICE0u_K(	0,	1 );			E[ 0 ] =	*( (ui64*)	cubeZ+1)	+A[ 0 ] +B[ 0 ]; 				\
	while( x >E[ u ] ){			DeICEv_I(	u,	v	);		E[ v ] =	E[ u ]			+A[ v ] +B[ v ];  u=v++; }			\
	I[ u] =icI =ic;			*/	/*so, this was entirely redundant and does nothing now, but	*/
							/*I'll keep it for the uniformity of the debugging macros		*/





/*		CoINTRaLOC($x)			Vectors (U, V) intralocate mod scope of next x as cycla (ic-1, ic) in current cube (iC)		*/
#define	CoINTRaLOC($x)		/*	Vectors (U, V) intralocate mod scope of next x as cycla (ic-1, ic) in current cube (iC)		*/	dBUG_xINTRALOC("CoINTRaLOC");	\
	if(							$x >E[ u ]	){																	\
/* mod range starts.	*/																						\
		if( ixM == 0xFF){																						\
			if(		RW[ v ] >ok ){	MkIn;		ReICEuO(	u, v );										u=v++;	\
				if(				$x >E[ u ] ){	ReICEuOx(	u, v );					deIceV_KEI();			u=v++;	\
					while(		$x >E[ u ] ){	Ox[v]=Ox[u]+Q[u];						DeICEv_KEI( u, v );		u=v++; }	\
					}\
			}else if(	RW[ u ] >ok ){	MkIn;		ReICEuO(	u, v );	if( RW[ v ] == null )	deIceV_KEI();			u=v++;	\
				while(			$x >E[ u ] ){	Ox[v]=Ox[u]+Q[u];						DeICEv_KEI( u, v );		u=v++; }	\
\
/* nvm. */	}else{						 /*	Ox[v]=Ox[u]+Q[u];*/	if( RW[ v ] == null )	deIceV_KEI();			u=v++;	\
				while(			$x >E[ u ] ){ /*	Ox[v]=Ox[u]+Q[u];*/					DeICEv_KEI( u, v );		u=v++; }	icI =ic; \
				}																							\
/* mod range continues.	*/																					\
		}else if(		RW[ v ] >ok ){				ReICEuOx(	u, v );										u=v++;	\
				if(				$x >E[ u ] ){	ReICEuOx(	u, v );					deIceV_KEI();			u=v++;	\
					while(		$x >E[ u ] ){	Ox[v]=Ox[u]+Q[u];						DeICEv_KEI( u, v );		u=v++; }	\
					}\
		}else if(		RW[ u ] >ok ){				ReICEuOx(	u, v );	if( RW[ v ] == null )	deIceV_KEI();			u=v++;	\
				while (			$x >E[ u ] ){	Ox[v]=Ox[u]+Q[u];						DeICEv_KEI( u, v );		u=v++; }	\
\
		}else							{	Ox[v]=Ox[u]+Q[u];		if( RW[ v ] == null )	deIceV_KEI();			u=v++;	\
				while (			$x >E[ u ] ){	Ox[v]=Ox[u]+Q[u];						DeICEv_KEI( u, v );		u=v++; }	\
		}								}																



							/*	Vectors (U, V) interlocate mod scope of next x as cycla (zc, 0), bridging cubes ( iC, iC+1 ).	*/
#define	CoINTERLOC			/*	Vectors (U, V) interlocate mod scope of next x as cycla (zc, 0), bridging cubes ( iC, iC+1 ).	*/	dBUG_xINTRALOC("CoINTERLOC");	\
	if(							ic< zc	){																	\
		/* mod range starts.	*/																				\
		if( ixM == 0xFF){																						iCI=iC;	\
			if(		RW[ v ] >ok ){	MkIn;		ReICEuO(	u, v );										u=v++;	\
				if(				ic< zc	){	ReICEuOx(	u, v );					deIceV_KEI();			u=v++;	\
					while(		ic< zc	){	Ox[v]=Ox[u]+Q[u];						DeICEv_KEI(	u, v );	u=v++; }	\
					}\
			}else if(	RW[ u ] >ok ){	MkIn; 	  	ReICEuO(	u, v );	if( RW[ v ] == null )	deIceV_KEI();			u=v++;	\
				while(			ic< zc	){	Ox[v]=Ox[u]+Q[u];						DeICEv_KEI(	u, v );	u=v++; }	\
\
			}else	/* false start.	*/	{	I[ tena_zc ] =I[u] +( tena_zc-u); v=( u=tena_zc )+1;	DeICEzu_KE(	u, v );	icI =zc;	\
									}																	\
		/* mod range continues.	*/\
		}else if(		RW[ v ] >ok ){				ReICEuOx(	u, v );										u=v++;	\
				if(				ic< zc	){	ReICEuOx(	u, v );					deIceV_KEI();			u=v++;	\
					while(		ic< zc	){	Ox[v]=Ox[u]+Q[u];						DeICEv_KEI(	u, v );	u=v++; }	\
					}\
		}else if(		RW[ u ] >ok ){				ReICEuOx(	u, v );	if( RW[ v ] == null )	deIceV_KEI();			u=v++;	\
				while(			ic< zc	){	Ox[v]=Ox[u]+Q[u];						DeICEv_KEI(	u, v );	u=v++; }	\
\
		}else							{	Ox[v]=Ox[u]+Q[u];		if( RW[ v ] == null )	deIceV_KEI();			u=v++;	\
				while(			ic< zc	){	Ox[v]=Ox[u]+Q[u];						DeICEv_KEI(	u, v );	u=v++; }	\
		}								}																	\
	tena_zc +=zc +1;




#define _EPILOC	/* printf("\nEPILOC	ixM: %d	izM: %d	icI: %d	icO: %d\n", ixM, izM, icI, icO );	*/\
		if( ixM == 0xFF){		MkIn;			}															\
		do	{	if(	x ==	E[ u ] )	{				++	B[ u ];	  ++	E[ u ];		}							\
				else		{	uMOD;	A[ v ] =x -E[ u ];	B[ v ]=1;		E[ v ] =x+1;	ReICEuOx( u, v );	u=v++;	}	\
				if(	za == a )	break;																		\
					x =	ARG( ++	a );	\
			} while( 1 );		MkOut;											ReICEuOx( u, v );







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
#define	SvCOMMIT			/*	Mark-out the modification range and call _sv_commit() to re-encode the SV[s]					*/	dBUG_xINTRALOC( "SvCOMMIT" );	\
	if( ixM == 0xFF ){	/* envelope not marked in yet 	*/															\
		if(		RW[ v ] >ok	)	{	MkIn;			ReICEuO( u, v );	u=v++; ReICEuOx( u, v );	MkOut;	_sv_commit();	\
		}else if(	RW[ u ] >ok	)	{	MkIn;			ReICEuO( u, v );							MkOut;	_sv_commit();	\
		}else		/* no mods */	{ /* shunt pointers	*/	cubeZ= cube; CSZ=CS; svZ=sv; zcZ= zc;		/* nothing to commit */		\
								}					\
	}else if(		RW[ v ] >ok	 )	{					ReICEuOx( u, v );	u=v++; ReICEuOx( u, v );	MkOut;	_sv_commit();	\
	}else if(		RW[ u ] >ok	 )	{					ReICEuOx( u, v );							MkOut;	_sv_commit();	\
	}else						{					Ox[v]=Ox[u] +Q[u];							MkOut;	_sv_commit();	\
								}




/*		SvCOMMITx				Mark-out the modification range and call _sv_commit() to re-encode the SV[s]					*/
#define	SvCOMMITx			/*	Mark-out the modification range and call _sv_commit() to re-encode the SV[s]					*/	dBUG_xINTRALOC( "SvCOMMITx" );	\
	if( ixM == 0xFF ){	/* envelope not marked in yet 	*/															\
		if(		RW[ v ] >ok	)	{	MkIn;			ReICEuO( u, v );	u=v++; ReICEuOx( u, v );	MkOut;		_sv_commit();	\
		}else if(	RW[ v ]==del	)	{	MkIn;			ReICEuO( u, v );	u=v++; Ox[v]=Ox[u];		MkOutx;		_sv_commitx();	\
		}else if(	RW[ u ] >ok	)	{	MkIn;			ReICEuO( u, v );							MkOut;		_sv_commit();	\
		}else if(	RW[ u ]==del	)	{	MkIn;			Ox[v]=Ox[u]=O[u];							MkOutx;		_sv_commitx();	\
		}else		/* no mods */	{ /* shunt pointers	*/	cubeZ= cube; CSZ=CS; svZ=sv; zcZ= zc;		/* nothing to commit */		\
								}					\
	}else if(		RW[ v ] >ok	 )	{					ReICEuOx( u, v );	u=v++; ReICEuOx( u, v );	MkOut;		_sv_commit();	\
	}else if(		RW[ v ]==del	 )	{					ReICEuOx( u, v );	u=v++; Ox[v]=Ox[u];		MkOutx;		_sv_commitx();	\
	}else if(		RW[ u ] >ok	 )	{					ReICEuOx( u, v );							MkOut;		_sv_commit();	\
	}else if(		RW[ u ]==del	 )	{					Ox[v]=Ox[u]=O[u];							MkOutx;		_sv_commitx();	\
	}else						{					Ox[v]=Ox[u] +Q[u];							MkOut;		_sv_commit();	\
								}
/*
	_sv_commitx will require
		SwCASE_XXOVER_00K	(done)
		SwCASE_XXOVER_00T
		SwCASE_LOWPASS_1IS	(done)
		SwCASE_LPXOVER_00Y
		SwCASE_XXOVER_00Y
		SwCASE_XXOVER_00W
		
*/