#define	cui8	const	unsigned	char	
#define	ui08			unsigned	char	
#define	ui16			unsigned	short 
#define	ui32		long	unsigned	int 
#define	si64	long long			int 
#define	ui64	long long	unsigned	int 
#define	ui64	long long	unsigned	int 


//	#define PERL_NO_GET_CONTEXT		this seems to cause gcc to generate "error: 'my_perl' undeclared"
//	#include <stddef.h>
//	#include <stdbool.h>
//	#include <stdio.h>
//	#include <math.h>
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "dBUG.h"
#include "ICEPack.h"


static const char* svtype_names[] = {		"SVt_NULL",		"SVt_IV",		"SVt_NV",		"SVt_RV",		"SVt_PV",	"SVt_PVIV",		"SVt_PVNV",		"SVt_PVMG",		"SVt_INVLIST",		"SVt_REGEXP",		"SVt_PVGV",		"SVt_PVLV",		"SVt_PVAV",		"SVt_PVHV",		"SVt_PVCV",		"SVt_PVFM",		"SVt_PVIO",		"SVt_PVBM",		"SVt_PVGV",		"SVt_PVLV",		"SVt_PVAV",		"SVt_PVHV",		"SVt_PVCV",		"SVt_PVFM",		"SVt_PVIO",		"SVt_PVBM",		"SVt_PVGV",		"SVt_PVLV",		"SVt_PVAV",		"SVt_PVHV",		"SVt_PVCV",		"SVt_PVFM",		"SVt_PVIO",		"SVt_PVBM",		"SVt_PVGV",		"SVt_PVLV",		"SVt_PVAV",		"SVt_PVHV",		"SVt_PVCV",		"SVt_PVFM",		"SVt_PVIO",		"SVt_PVBM",		"SVt_PVGV",		"SVt_PVLV",		"SVt_PVAV",		"SVt_PVHV",		"SVt_PVCV",		"SVt_PVFM",		"SVt_PVIO",		"SVt_PVBM",		"SVt_PVGV",		"SVt_PVLV",		"SVt_PVAV",		"SVt_PVHV",		"SVt_PVCV",		"SVt_PVFM",		"SVt_PVIO",		"SVt_PVBM",		"SVt_PVGV",		"SVt_PVLV",		"SVt_PVAV",		"SVt_PVHV",		"SVt_PVCV",		"SVt_PVFM",		"SVt_PVIO",		"SVt_PVBM",		"SVt_PVGV",		"SVt_PVLV",		"SVt_PVAV",		"SVt_PVHV",		"SVt_PVCV",		"SVt_PVFM",		"SVt_PVIO",		"SVt_PVBM",		"SVt_PVGV",		"SVt_PVLV",		"SVt_PVAV",		"SVt_PVHV",		"SVt_PVCV",		"SVt_PVFM",		"SVt_PVIO",		"SVt_PVBM",		"SVt_PVGV",		"SVt_PVLV",		"SVt_PVAV",		"SVt_PVHV",		"SVt_PVCV",		"SVt_PVFM",		"SVt_PVIO",		"SVt_PVBM",		"SVt_PVGV",		"SVt_PVLV",		"SVt_PVAV",		"SVt_PVHV",		"SVt_PVCV",		"SVt_PVFM"		};
static const char* svtype_names_ref[] = {	"ref: SVt_NULL",	"ref: SVt_IV",	"ref: SVt_NV",	"ref: SVt_RV", 	"ref: SVt_PV",	"ref: SVt_PVIV",	"ref: SVt_PVNV",	"ref: SVt_PVMG",	"ref: SVt_INVLIST", 	"ref: SVt_REGEXP",	"ref: SVt_PVGV",	"ref: SVt_PVLV",	"ref: SVt_PVAV",	"ref: SVt_PVHV",	"ref: SVt_PVCV",	"ref: SVt_PVFM",	"ref: SVt_PVIO",	"ref: SVt_PVBM",	"ref: SVt_PVGV",	"ref: SVt_PVLV",	"ref: SVt_PVAV",	"ref: SVt_PVHV",	"ref: SVt_PVCV",	"ref: SVt_PVFM",	"ref: SVt_PVIO",	"ref: SVt_PVBM",	"ref: SVt_PVGV",	"ref: SVt_PVLV",	"ref: SVt_PVAV",	"ref: SVt_PVHV",	"ref: SVt_PVCV",	"ref: SVt_PVFM",	"ref: SVt_PVIO",	"ref: SVt_PVBM",	"ref: SVt_PVGV",	"ref: SVt_PVLV",	"ref: SVt_PVAV",	"ref: SVt_PVHV",	"ref: SVt_PVCV",	"ref: SVt_PVFM",	"ref: SVt_PVIO",	"ref: SVt_PVBM",	"ref: SVt_PVGV",	"ref: SVt_PVLV",	"ref: SVt_PVAV",	"ref: SVt_PVHV",	"ref: SVt_PVCV",	"ref: SVt_PVFM",	"ref: SVt_PVIO",	"ref: SVt_PVBM",	"ref: SVt_PVGV",	"ref: SVt_PVLV",	"ref: SVt_PVAV",	"ref: SVt_PVHV",	"ref: SVt_PVCV",	"ref: SVt_PVFM",	"ref: SVt_PVIO",	"ref: SVt_PVBM",	"ref: SVt_PVGV",	"ref: SVt_PVLV",	"ref: SVt_PVAV",	"ref: SVt_PVHV",	"ref: SVt_PVCV",	"ref: SVt_PVFM",	"ref: SVt_PVIO",	"ref: SVt_PVBM",	"ref: SVt_PVGV",	"ref: SVt_PVLV",	"ref: SVt_PVAV",	"ref: SVt_PVHV",	"ref: SVt_PVCV",	"ref: SVt_PVFM",	"ref: SVt_PVIO",	"ref: SVt_PVBM",	"ref: SVt_PVGV",	"ref: SVt_PVLV",	"ref: SVt_PVAV",	"ref: SVt_PVHV",	"ref: SVt_PVCV",	"ref: SVt_PVFM",	"ref: SVt_PVIO",	"ref: SVt_PVBM",	"ref: SVt_PVGV",	"ref: SVt_PVLV",	"ref: SVt_PVAV",	"ref: SVt_PVHV",	"ref: SVt_PVCV",	"ref: SVt_PVFM",	"ref: SVt_PVIO",	"ref: SVt_PVBM",	"ref: SVt_PVGV",	"ref: SVt_PVLV",	"ref: SVt_PVAV",	"ref: SVt_PVHV",	"ref: SVt_PVCV",	"ref: SVt_PVFM"	};

void icepack_init(){
	printf("\nICEPack is cold\n");
	_icepack_init();
	avICE_=newAV();
	rvICE_ = newRV_inc( (SV*) avICE_ );
	}

#ifdef	DEBUG
	SV*		getAvDBUG(){	SV* rv =newRV_inc( (SV*) avDBUG );	return rv;	}
	void		printAvDBUG(){
		size_t		a, za;
		SV		*	sv,
				**	pSv;
		char		*	pStr;
		STRLEN		cS;
		svtype		svt = SvTYPE( avDBUG );
		if(			svt != SVt_PVAV || AvFILLp( avDBUG ) ==-1)	return;

		pSv	= AvARRAY(	avDBUG );
		za	= AvFILLp(	avDBUG );

		for( a=0; a<= za; ++a ){	sv= *( pSv +a );
			if( SvPOK(		sv ) )	{	pStr= SvPVbyte( sv, cS );	if( cS >0) 	printf( pStr );
			}						}

		av_clear( avDBUG );	
		}
#else
	SV*  	getAvDBUG(){					printf("\n!	getAvDBUG():  	ICE has not been compiled with debug options set.\n");	}
	void  	printAvDBUG(){					printf("\n!	printAvDBUG():	ICE has not been compiled with debug options set.\n");	}
#endif

#define SvINIT( $AV, $SV )		AvINIT1(		$AV );				\
							*( AvARRAY(	$AV)	) =	$SV;	
#define SvINS( $AV, $SV, $I )		AvINSERT1(	$AV,	$I );			\
							*( AvARRAY(	$AV) +	$I )=	$SV;

#define WSPACE_UNSAFE($pr, $WS )	\
	while(	$WS >7 ){			*( (ui64*)(	$pr		) )=0x2020202020202020;	$pr += 8;	$WS-=8;	}	\
	switch(	$WS ){	case 0x0:												break;	\
					case 0x1:	*( (ui08*) (	$pr		) )=0x20;					break;	\
					case 0x2:	*( (ui16*) (	$pr		) )=0x2020;				break;	\
					case 0x3:	\
					case 0x4:	*( (ui32*) (	$pr		) )=0x20202020;			break;	\
					case 0x5:	\
					case 0x6:	\
					case 0x7:	*( (ui64*)(	$pr		) )=0x2020202020202020;			\
				}							$pr+=$WS;

#define WSPACE($pr, $WS )	\
	while(	$WS >7 ){			*( (ui64*)(	$pr		) )=0x2020202020202020;	$pr += 8;	$WS-=8;	}	\
	switch(	$WS ){	case 0x0:												break;	\
					case 0x1:	*( (ui08*) (	$pr		) )=0x20;					break;	\
					case 0x2:	*( (ui16*) (	$pr		) )=0x2020;				break;	\
					case 0x3:	*( (ui16*) (	$pr		) )=0x2020;						\
								*( (ui08*) (	$pr +2 	) )=0x20;					break;	\
					case 0x4:	*( (ui32*) (	$pr		) )=0x20202020;			break;	\
					case 0x5:	*( (ui32*) (	$pr		) )=0x20202020;					\
								*( (ui08*) (	$pr +4 	) )=0x20;					break;	\
					case 0x6:	*( (ui32*) (	$pr		) )=0x20202020;					\
								*( (ui16*) (	$pr +4 	) )=0x2020;				break;	\
					case 0x7:	*( (ui32*) (	$pr		) )=0x20202020;					\
								*( (ui16*) (	$pr +4 	) )=0x2020;						\
								*( (ui08*) (	$pr +6 	) )=0x20;							\
				}							$pr+=$WS;




#define	CUBE_(	$iC )   									SvPVbyte( *( AvARRAY( avICE) +$iC ), CSZ	)
#define	CUBE(	$iC )   									SvPVbyte( *( AvARRAY( avICE) +$iC ), CS	)
#define	CUBEvc(	$iC )(  		__builtin_clzll( *( (ui64*) (	cube =	SvPVbyte( *( AvARRAY( avICE) +$iC ), CS	) ) +1 ) )	>>3)

SV*	fills(			SV*	rvICE,	SV* svMIN, SV* svRUN	){		// matches object to given run length and index
	svtype			t0,
					t1=SvTYPE( svMIN),
					t2=SvTYPE( svRUN);
	const char	*	usage_err[]={	"\r!	ICEPack::fills( <%s>, <%s>, <%s> ):	arg[0] must be an arrayref <ICEPack>.\n",
								"\r!	ICEPack::fills( <%s>, <%s>, <%s> ):	arg[1] must be a scalar UV <low boundary>.\n",
								"\r!	ICEPack::fills( <%s>, <%s>, <%s> ):	arg[2] must be a scalar UV <run length>.\n"	};
	unsigned char	*	cube,
				*pk, *pq,
					zc;
	STRLEN			CS;
	ui08				Qc;
	ui64				Ac, Bc, min, run;

	if( (t0= SvTYPE(	rvICE ) )	!= SVt_RV || ! SvROK(	rvICE ) )	{ printf( usage_err[0],  	svtype_names[	t0 ], svtype_names[ t1 ], svtype_names[ t2 ] );		return &PL_sv_no;	}
					avICE 	= (AV*)		SvRV(	rvICE );	
	if( (t0= SvTYPE(	avICE )	!= SVt_PVAV ) )				{ printf( usage_err[0],  	svtype_names_ref[ t0 ], svtype_names[ t1 ], svtype_names[ t2 ] );		return &PL_sv_no; 	}

	SV*				C0=*AvARRAY( avICE );
	min=SvUVX(	svMIN);
	run=SvUVX(	svRUN);

	if( AvFILLp( avICE)==0 ){
		cube = SvPVbyte( C0, CS );
		zc=zcOf( *( (ui64*) cube ) );

		if( zc==0 )	{_deICE0( cube, CS, cube[0],	pq, Qc, Ac, Bc );	if( Ac==min && Bc==run ) 	return newSViv( Bc );
		}			}
	return &PL_sv_no;
	}
SV*	toText(		SV* rvICE	){
	const char	*	arg_err	= "\r!       ICEPack::toText( <%s> ): arg[0] must be an arrayref <ICEPack>.\n\t";
					avOut = newAV();
					rvOut = newRV_inc( (SV*) avOut );
	svtype			svt = SvTYPE( rvICE );
	STRLEN			L;

	if( ! SvROK( rvICE) ){	L =sprintf( aString, arg_err,	svtype_names[ svt ] );		av_push( avOut, newSVpvn( aString, L ) );	return rvOut; }
	avICE	= (AV*) SvRV(	rvICE	);	/*	dereference argument									*/

	svt= SvTYPE(avICE);				/*	check type of supposed perl object at dereferenced address	*/
	if( svt != SVt_PVAV ){	L =sprintf( aString, arg_err,	svtype_names_ref[ svt ] );	av_push( avOut, newSVpvn( aString, L ) );	return rvOut; }
	if( AvFILLp( avICE ) !=-1) _toText();
	return rvOut;
	}
SV*	upsortQ(		SV* rvArg,	SV* svQx	){
	const char	*	arg0_err	= "\r!       ICEPack::upsortQ( <%s>, <%s> ): arg[0] must be an arrayref.\n\t",
				*	arg1_err	= "\r!       ICEPack::upsortQ( <%s>, <%s> ): arg[1] must be a packed quad.\n\t";
	svtype			t0 = SvTYPE( rvArg ),
					t1 = SvTYPE( svQx	);
	if( t0 != SVt_RV || !SvROK(	rvArg	) ){	printf( arg0_err,  svtype_names[ t0 ],		svtype_names[ 0 ] );		return &PL_sv_no; }
	if( t1 != SVt_PV || !SvOK(	svQx	) ){	printf( arg1_err,  svtype_names[ t0 ],		svtype_names[ t1 ] );		return &PL_sv_no; }
	avArg	= (AV*) SvRV(    	rvArg );	t0 = SvTYPE( avArg );
	if( t0 != SVt_PVAV ){					printf( arg0_err,  svtype_names_ref[ t0 ],  	svtype_names[ t1 ] );		return &PL_sv_no; }

	SV			*	svQ,
				**	src,
				**	dst,
				**	sv0	= AvARRAY( avArg );
	ui08			*	pq;
	const ui08	*	pqx= SvPVbyte_nolen( svQx );
	const long long	x	= *( (ui64*) pqx );

	SSize_t			displacement;
	long long			lb	= 0,
					ub	= AvFILLp( avArg )+1,	i= ub >>1;		if( ub==0	){		svQ=newSVpvn( pqx, 8 );  SvINIT( avArg, svQ );	return &PL_sv_no;	}

						pq = SvPVbyte_nolen( svQ=	*( sv0 +i ) );
	while(	x !=	*( (ui64*)	pq )	){
		if(	x >	*( (ui64*)	pq )	){	lb=i;			i=( i +ub	)>>1;	if( i==lb	){ ++i;	svQ=newSVpvn( pqx, 8 );  SvINS( avArg, svQ, i ); 	return &PL_sv_no;  }
		}else{					ub=i;		i=( lb + i	)>>1;	if( i==ub	){		svQ=newSVpvn( pqx, 8 );  SvINS( avArg, svQ, i );	return &PL_sv_no;  }
			}			pq = SvPVbyte_nolen( svQ=	*( sv0 +i ) );
		}
	return &PL_sv_yes; 	// return true: given packed quad is already present in sorted array
	}
SV*	insortIV(		SV* rvArg,	SV* svX		){
	const char	*	arg0_err	= "\r!       ICEPack::insortIV( <%s>, <%s> ): arg[0] must be an arrayref.\n\t",
				*	arg1_err	= "\r!       ICEPack::insortIV( <%s>, <%s> ): arg[1] must be a positive / unsigned integer.	SvTYPE( svX )==%d; SVt_IV==%d\n\t";
	svtype			t0 = SvTYPE(	rvArg ),
					t1 = SvTYPE(	svX	);
	if(	t0 != SVt_RV		|| !SvROK(	rvArg	) ){	printf( arg0_err,  svtype_names[ t0 ],		svtype_names[ t1 ] );		return &PL_sv_no; }
	if( (	t1 != SVt_IV &&
		t1 != SVt_PVIV )	|| !SvOK(	svX		) ){	printf( arg1_err,  svtype_names[ t0 ],		svtype_names[ t1 ], SvTYPE( svX), SVt_IV );		return &PL_sv_no; }
	avArg = (AV*)	SvRV(	rvArg );
	t0 = SvTYPE(			avArg );
	if( t0 != SVt_PVAV ){							printf( arg0_err,  svtype_names_ref[ t0 ],  	svtype_names[ t1 ] );		return &PL_sv_no; }

	const long long	x	= SvIVX( svX );
	SSize_t			displacement;
	long long int		lb	= 0,
					ub	= AvFILLp( avArg )+1,	i= ub >>1;			if( ub==0	){		svX=newSViv( x );  SvINIT( avArg, svX );		return &PL_sv_no;	}

	SV				**	src,
					**	dst,
					**	svA0= AvARRAY( avArg ),
					*	svA	= *(svA0 +i );
	while(	x !=	SvIVX(	svA ) ){
		if(	x >	SvIVX(	svA ) ){		lb=i;			i=( i +ub	)>>1;	if( i==lb	){ ++i;	svX=newSViv( x );  SvINS( avArg, svX, i );	return &PL_sv_no;  }
		}else{						ub=i;		i=( lb + i	)>>1;	if( i==ub	){		svX=newSViv( x );  SvINS( avArg, svX, i );	return &PL_sv_no;  }
			}			svA	= *(svA0 +i );
		}
	return &PL_sv_yes; 	// return true: given integer is already present in sorted array
	}
SV*	checks(		SV* rvICE	){
	svtype	rt0,	t0 = SvTYPE( rvICE );
	const char	*	arg_err	= "\r!       ICEPack::checks( <%s> ): arg[%d] must be an arrayref <ICEPack>.\n\t";
	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg_err,  svtype_names[		t0 ], 0 );	return &PL_sv_no; }
	avICE	= (AV*) SvRV(    	rvICE );
		rt0 = SvTYPE( avICE );
	if(	rt0 != SVt_PVAV ){				printf( arg_err,  svtype_names_ref[	rt0 ], 0 );	return &PL_sv_no; }
	bool err=_checks();
	return err? &PL_sv_yes: &PL_sv_no;
	}
SV*	has(			SV* rvICE,	SV* rvArg	){ //	count matches in avArgs.	best for large objects with few args.	return true = total inclusivity.
	const char *	arg_err	= "\r!       ICEPack::has( <%s>, <%s> ): arg[%d] must be an arrayref.\n\t";
	svtype		rt0, rt1;

	svtype const 	t0 = SvTYPE(	rvICE ),
				t1 = SvTYPE(	rvArg );

	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg_err,  svtype_names[		t0 ],  	svtype_names[	t1	], 0 );  return &PL_sv_no; }
	if( t1 != SVt_RV || !SvROK(	rvArg) ){	printf( arg_err,  svtype_names[		t0 ], 	svtype_names[	t1	], 0 );  return &PL_sv_no; }

	avICE	= (AV*) SvRV(    	rvICE );	rt0 = SvTYPE( avICE );
	avArg	= (AV*) SvRV(    	rvArg );	rt1 = SvTYPE( avArg );

	if( rt0 != SVt_PVAV ){				printf( arg_err,  svtype_names_ref[	rt0 ],  	svtype_names_ref[	rt1	], 1 );  return &PL_sv_no; }
	if( rt1 != SVt_PVAV ){				printf( arg_err,  svtype_names_ref[	rt0 ],  	svtype_names_ref[	rt1	], 1 );  return &PL_sv_no; }

	return _has() ? &PL_sv_yes: &PL_sv_no;
	}
SV*	clears(		SV* rvICE,	SV* rvArg	){ //	cut matches from avArgs.	best for large objects with few args.	return true = total inclusivity.
	const char *	arg_err	= "\r!       ICEPack::clears( <%s>, <%s> ): arg[%d] must be an arrayref.\n\t";
	svtype		rt0, rt1;

	svtype const 	t0 = SvTYPE(	rvICE ),
				t1 = SvTYPE(	rvArg );

	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg_err,  svtype_names[		t0 ],  	svtype_names[	t1	], 0 );  return &PL_sv_no; }
	if( t1 != SVt_RV || !SvROK(	rvArg) ){	printf( arg_err,  svtype_names[		t0 ], 	svtype_names[	t1	], 0 );  return &PL_sv_no; }

	avICE	= (AV*) SvRV(    	rvICE );	rt0 = SvTYPE( avICE );
	avArg	= (AV*) SvRV(    	rvArg );	rt1 = SvTYPE( avArg );

	if( rt0 != SVt_PVAV ){				printf( arg_err,  svtype_names_ref[	rt0 ],  	svtype_names_ref[	rt1	], 1 );  return &PL_sv_no; }
	if( rt1 != SVt_PVAV ){				printf( arg_err,  svtype_names_ref[	rt0 ],  	svtype_names_ref[	rt1	], 1 );  return &PL_sv_no; }

	return _clears()? &PL_sv_yes: &PL_sv_no;
	}
SV*	fits(			SV* rvICE,	SV* rvArg	){ //	count matches in avArgs.	best for small objects with many args.	return true = total inclusivity.
	const char *	arg_err	= "\r!       ICEPack::fits( <%s>, <%s> ): arg[%d] must be an arrayref.\n\t";
	svtype		rt0, rt1;

	svtype const 	t0 = SvTYPE(	rvICE ),
				t1 = SvTYPE(	rvArg );

	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg_err,  svtype_names[		t0 ],  	svtype_names[	t1	], 0 );  return &PL_sv_no; }
	if( t1 != SVt_RV || !SvROK(	rvArg) ){	printf( arg_err,  svtype_names[		t0 ], 	svtype_names[	t1	], 0 );  return &PL_sv_no; }

	avICE	= (AV*) SvRV(    	rvICE );	rt0 = SvTYPE( avICE );
	avArg	= (AV*) SvRV(    	rvArg );	rt1 = SvTYPE( avArg );

	if( rt0 != SVt_PVAV ){				printf( arg_err,  svtype_names_ref[	rt0 ],  	svtype_names_ref[	rt1	], 1 );  return &PL_sv_no; }
	if( rt1 != SVt_PVAV ){				printf( arg_err,  svtype_names_ref[	rt0 ],  	svtype_names_ref[	rt1	], 1 );  return &PL_sv_no; }

	return _fits()? &PL_sv_yes: &PL_sv_no;
	}
SV*	strikes(		SV* rvICE,	SV* rvArg	){ //	cut matches from avArgs.	best for small objects with many args.	return true = total inclusivity.
	const char *	arg_err	= "\r!       ICEPack::strikes( <%s>, <%s> ): arg[%d] must be an arrayref.\n\t";
	svtype		rt0, rt1;

	svtype const 	t0 = SvTYPE(	rvICE ),
				t1 = SvTYPE(	rvArg );

	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg_err,  svtype_names[		t0 ],  	svtype_names[	t1	], 0 );  return &PL_sv_no; }
	if( t1 != SVt_RV || !SvROK(	rvArg) ){	printf( arg_err,  svtype_names[		t0 ], 	svtype_names[	t1	], 0 );  return &PL_sv_no; }

	avICE	= (AV*) SvRV(    	rvICE );	rt0 = SvTYPE( avICE );
	avArg	= (AV*) SvRV(    	rvArg );	rt1 = SvTYPE( avArg );

	if( rt0 != SVt_PVAV ){				printf( arg_err,  svtype_names_ref[	rt0 ],  	svtype_names_ref[	rt1	], 1 );  return &PL_sv_no; }
	if( rt1 != SVt_PVAV ){				printf( arg_err,  svtype_names_ref[	rt0 ],  	svtype_names_ref[	rt1	], 1 );  return &PL_sv_no; }

	return _strikes()? &PL_sv_yes: &PL_sv_no;
	}
SV*	set(			SV* rvICE,	SV* rvArg	){

	svtype	rt0, rt1,	t0 = SvTYPE( rvICE ),
					t1 = SvTYPE( rvArg );
	const char	*	arg_err	= "\r!       ICEPack::set( <%s>, <%s> ): arg[%d] must be an arrayref.\n\t";

	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg_err,  svtype_names[		t0 ],  	svtype_names[	t1	], 0 );  return &PL_sv_no; }
	if( t1 != SVt_RV || !SvROK(	rvArg) ){	printf( arg_err,  svtype_names[		t0 ], 	svtype_names[	t1	], 0 );  return &PL_sv_no; }

	avICE	= (AV*) SvRV(    	rvICE );	rt0 = SvTYPE( avICE );
	avArg	= (AV*) SvRV(    	rvArg );	rt1 = SvTYPE( avArg );

	if( rt0 != SVt_PVAV ){				printf( arg_err,  svtype_names_ref[	rt0 ],  	svtype_names_ref[	rt1	], 1 );  return &PL_sv_no; }
	if( rt1 != SVt_PVAV ){				printf( arg_err,  svtype_names_ref[	rt0 ],  	svtype_names_ref[	rt1	], 1 );  return &PL_sv_no; }

//	const int		zC		= AvFILLp(	avICE );
//	const SV**	pSv0	= AvARRAY(	avICE );
//	if(	zC!=-1 && *pSv0 !=NULL && SvIVX( *pSv0 ) > AvFILLp( avArg ) )
			_set8x();
//	else 	_set9up();


	return newSViv( za +1 -skip );
	}
SV*	toPerl(		SV* rvICE	){
	const char	*	usage_err	=	"#       ICEPack::toPerl( <%s> ): arg[0] must be an <arrayref (ICE object) >.\n",
				*	cube_err[]	={	"#       ICEPack::toPerl( <%s> ): array index #%lld is NULL.\n",										//0
									"#       ICEPack::toPerl( <%s> ): SV* at array index #%lld is NULL.\n",									//1
									"#       ICEPack::toPerl( <%s> ): XV at array index #%lld is not a scalar (!SvOK)	(&*%llX).\n",				//2
									"#       ICEPack::toPerl( <%s> ): scalar at array index #%lld is not a string (!SvPOK)	(&*%llX).\n",			//3
									"#       ICEPack::toPerl( <%s> ): string at array index #%lld is less-than 16 bytes (cube size: %lld byte[s]).\n",	//4
									"#       ICEPack::toPerl( <%s> ): cube at array index #%lld contains no keybytes (cube size: %lld byte[s]) .\n",	//5							//1
									},
				*	malloc_err	=	"#       ICEPack::toPerl( <%s> ): could not allocate memory for \"%s\" array.\n";
	AV*				avICE;
	SV			**	pai0,
				**	paiC,
				*	svC;
	unsigned char	WS,	s,	sizeX[	8	],
						sizeZ[	8	],
				*	pr,	row[  	384	], ic,
				*	cube,
				**	Mpk,
				**	Mpq;
	char			*	Mzc;
	unsigned	long long int	
				**	MX,
				**	MZ,				Qc, Ac, Bc, Zx;
			long long int	iC,	zC, nC;
	svtype			type;
	STRLEN			L, CS;

	if( (type	= SvTYPE(	rvICE ) )	!= SVt_RV || ! SvROK(	rvICE ) )										{ printf( usage_err,  	svtype_names[		type ] );			return  &PL_sv_undef;	}
						avICE 	= (AV*)		SvRV(	rvICE );	/*	dereference argument	*/
	if( (type	= SvTYPE(	avICE )	!= SVt_PVAV ) )													{ printf( usage_err,  	svtype_names_ref[ 	type ] );			return  &PL_sv_undef; 	}
	nC=( zC	= AvFILLp(	avICE ) ) +1;
	avOut	= newAV_alloc_x( nC +1 );		*( (ui64*) sizeX )=0;	*( (ui64*) sizeZ )=0;
	rvOut	= newRV_inc( (SV*) avOut );
	if( nC==0 )															{																				return	rvOut;	}
	pai0 	= AvARRAY(	avICE );

	Newx( Mzc,	nC,	ui08 	);								if( Mzc==NULL)	{ printf( malloc_err, "Mzc" );									return  &PL_sv_undef; 	}
	Newx( Mpq,	nC,	ui08*	);								if( Mpq==NULL)	{ printf( malloc_err, "Mpq" );									goto _free0; }
	Newx( Mpk,	nC,	ui08*	);								if( Mpk==NULL)	{ printf( malloc_err, "Mpk" );									goto _free1; }
	Newx( MX,	nC,	ui64*	);								if( MX==NULL) 	{ printf( malloc_err, "MX" );									goto _free2; }
	Newx( MZ,	nC,	ui64*	);								if( MZ==NULL) 	{ printf( malloc_err, "MZ" );									goto _free3; }

																						if( pai0==NULL)	{ printf( cube_err[0], 	svtype_names_ref[ 	type ], Zx=0		);	Mzc[0]=-1;	goto _2nd_cube; }
															svC =*	pai0;				if( svC==NULL)	{ printf( cube_err[1], 	svtype_names_ref[ 	type ], Zx=0		);	Mzc[0]=-1;	goto _2nd_cube; }
																						if( !SvOK( svC ) )	{ printf( cube_err[2], 	svtype_names_ref[ 	type ], Zx=0, &*svC );	Mzc[0]=-1;	goto _2nd_cube; }
																						if( !SvPOK( svC ) )	{ printf( cube_err[3], 	svtype_names_ref[ 	type ], Zx=0, &*svC );	Mzc[0]=-1;return	rvOut;	goto _2nd_cube; }
											cube = SvPVbyte(	svC, CS );					if( CS<16 )		{ printf( cube_err[4], 	svtype_names_ref[ 	type ], Zx=0,  CS	 );	Mzc[0]=-1;	goto _2nd_cube; }
			Mzc[		0	]= zcOf(	*( (ui64*)	cube	) );									if( Mzc[ 0 ]==-1 )	{ printf( cube_err[5], 	svtype_names_ref[ 	type ], Zx=0,  CS	 );	Mzc[0]=-1;	goto _2nd_cube; }
			Newx( MX[	0 ],	8,	ui64	);													if( MX[ 0 ]==NULL )	{ printf( malloc_err, "MX[0]" );  									goto _free4; }
			Newx( MZ[	0 ],	8,	ui64	);													if( MZ[ 0 ]==NULL ) { printf( malloc_err, "MZ[0]" );				Safefree( MX[ 0 ] ); 		goto _free4; }

			Mpk[ 0 ] =	cube;				Mpq[ 0 ] = cube+16;
			_deICE0(    	cube, CS,	*Mpk[ 0 ],	Mpq[ 0 ], Qc,  	Ac,								Bc );
			MX[	0 ][ 0 ] =									Ac;					MZ[ 0 ][ 0 ]=	Bc +Ac;			Zx= *( (ui64*)	cube +1	);
						s =	2+(char) ceil( log10l( (long double)	MX[ 0 ][ 0 ]	) );	if( s >sizeX[ 0 ] )	sizeX[ 0 ]=s;	
			if( Bc >1 ){	s =	2+(char) ceil( log10l( (long double)	MZ[ 0 ][ 0 ]-1	) );	if( s >sizeZ[ 0 ] )	sizeZ[ 0 ]=s;	}

	_2nd_cube:
	for(			iC=1;	iC< nC;	++	iC ){						svC =*(	pai0 +iC );			if( svC==NULL)	{ printf( cube_err[1], 	svtype_names_ref[ 	type ], iC		);		Mzc[iC]=-1;	continue; }
																						if( !SvOK( svC ) )	{ printf( cube_err[2], 	svtype_names_ref[ 	type ], iC, &*svC  );		Mzc[iC]=-1;	continue; }
																						if( !SvPOK( svC ) )	{ printf( cube_err[3], 	svtype_names_ref[ 	type ], iC, &*svC  );		Mzc[iC]=-1;	continue; }
											cube = SvPVbyte(	svC, CS );					if( CS<16 )		{ printf( cube_err[4], 	svtype_names_ref[ 	type ], iC, CS	);		Mzc[iC]=-1;	continue; }
			Mzc[		iC	]=zcOf(	*( (ui64*)	cube	) );									if( Mzc[ iC ]==-1 )	{ printf( cube_err[5], 	svtype_names_ref[ 	type ], iC, CS	);		Mzc[iC]=-1;	continue; }
			Newx( MX[	iC ],	8,	ui64 );													if( MX[ iC ]==NULL )	{ printf( malloc_err, "MX[..]" );	while( iC >0 )	{	Safefree( MX[ --iC ] );
																																					Safefree( MZ[ iC ] );
																																				}					 	goto _free4; }
			Newx( MZ[	iC ],	8,	ui64 );													if( MZ[ iC ]==NULL ) { printf( malloc_err, "MZ[..]" );	while( iC >0 )	{	Safefree( MX[ iC ] );
																																					Safefree( MZ[ --iC ] );
																																				}	Safefree( MX[ 0 ] ); 	goto _free4; }
			Mpk[ iC ]=	cube;				Mpq[ iC ] = cube+16;
			_deICE0(    	cube, CS,	*Mpk[ iC ],	Mpq[ iC ], Qc,  Ac,								Bc );
			MX[	iC ][0] =									Ac+	Zx;				MZ[ iC ][ 0 ]=	Bc +MX[ iC ][ 0 ];	Zx= *( (ui64*)	cube +1	);
/* decimal *///			s =	2+(char) ceil( log10l( (long double)	MX[ iC ][ 0 ]	) );	if( s >sizeX[ 0 ] )	sizeX[ 0 ]=s;	
/* decimal *///if( Bc >1 ){	s =	2+(char) ceil( log10l( (long double)	MZ[ iC ][ 0 ]-1	) );	if( s >sizeZ[ 0 ] )	sizeZ[ 0 ]=s;	}
/* hex	*/				s =	20-( 			__builtin_clzll(	MX[ iC ][ 0 ]	) >>2);	if( s >sizeX[ 0 ] )	sizeX[ 0 ]=s;	
/* hex	*/	if( Bc >1 ){	s =	20-( 			__builtin_clzll(	MZ[ iC ][ 0 ]-1	) >>2);	if( s >sizeZ[ 0 ] )	sizeZ[ 0 ]=s;	}
			}
			ic=1;
	do	{
		for(		iC=0;	iC< nC;	++	iC )
			if( ic<= Mzc[	iC ] )	{ 	++	Mpk[	iC ];
				_deICE(	 cube, CS,  *	Mpk[	iC ], Mpq[ iC ], Qc,	Ac,								Bc );
				MX[ iC ][ ic ]=									Ac+	MZ[ iC ][ ic-1 ];	MZ[ iC ][ ic ]=	Bc +MX[ iC ][ ic ];
/* decimal */	//				s =	2+(char) ceil( log10l( (long double)	MX[ iC ][ ic ]	) );	if( s >sizeX[ ic ] )	sizeX[ ic ]=s;	
/* decimal */	//	if( Bc >1 ){	s =	2+(char) ceil( log10l( (long double) 	MZ[ iC ][ ic ]-1	) );	if( s >sizeZ[ ic ] )	sizeZ[ ic ]=s;	}
/* hex	*/					s =	20-( 			__builtin_clzll(	MX[ iC ][ ic ]	) >>2);	if( s >sizeX[ ic ] )	sizeX[ ic ]=s;	
/* hex	*/		if( Bc >1 ){	s =	20-(				__builtin_clzll(	MZ[ iC ][ ic ]-1	) >>2);	if( s >sizeZ[ ic ] )	sizeZ[ ic ]=s;	}
				}
		} while( ++ic< 8 );

	for(			iC=0;	iC< zC;	++	iC	){		pr = row;
		if( Mzc[	iC ] ==-1 ){								L=	sprintf(	pr, "# [cube #%llu null]\n", iC );		av_push( avOut, newSVpvn(  row, L ) );
		}else{	ic=0;
			do	{
				if(	MX[ iC ][	ic ]+1 == MZ[ iC ][ ic ] )	pr +=(	L=	sprintf(	pr,	"0x%llX,",		MX[ iC ][ ic ]					) );
				else								pr +=(	L=	sprintf(	pr,	"0x%llX..0x%llX,",	MX[ iC ][ ic ],	MZ[ iC ][ ic ]-1		) );
									WS = sizeX[ ic ] +sizeZ[ ic ] -L;
				WSPACE_UNSAFE(	pr,	WS );
				} while(	++	ic <= Mzc[ iC ] );		*pr++ = 10;
			av_push( avOut, newSVpvn( row, pr-row ) );
		}	}
		
	// treat last cube specially, just to eliminate the trailing comma
	if(	Mzc[	iC ] ==-1 ){								L=	sprintf(	pr, "# [cube #%llu null]\n", iC );		av_push( avOut, newSVpvn(  row, L ) );
	}else{										pr = row;
		for(		ic=0;		ic < Mzc[ iC ];	++ic ){
			if(		MX[ iC ][	ic ]+1 == MZ[ iC ][ ic ] )	pr +=(	L=	sprintf(	pr,	"0x%llX,",		MX[ iC ][ ic ]					) );
			else									pr +=(	L=	sprintf(	pr,	"0x%llX..0x%llX,",	MX[ iC ][ ic ],	MZ[ iC ][ ic ]-1		) );
								WS = sizeX[ ic ] +sizeZ[ ic ] -L;
			WSPACE_UNSAFE( 	pr,	WS );
			}
		if(			MX[ iC ][ ic ]+1 == MZ[ iC ][ ic ] )	pr +=(	L=	sprintf(	pr,	"0x%llX",			MX[ iC ][ ic ]					) );
		else										pr +=(	L=	sprintf(	pr,	"0x%llX..0x%llX",	MX[ iC ][ ic ],	MZ[ iC ][ ic ]-1		) );
					WS = sizeX[ ic ] +sizeZ[ ic ] -L;
		WSPACE(	pr,	WS );						*pr	= 0;
		av_push( avOut, newSVpvn( row, pr-row ) );
		}


	_free5:	for( iC=0; iC< nC; ++iC ) if( Mzc[ iC ]!=-1) {	Safefree( MX[ iC ] );  Safefree( MZ[ iC ] );	}
	_free4:	Safefree( MZ ); 
	_free3:	Safefree( MX );
	_free2:	Safefree( Mpk );
	_free1:	Safefree( Mpq );
	_free0:	Safefree( Mzc );	if( AvFILLp( avOut ) ==-1 )	printf("\ntoPerl() returning empty array\n");
	return	rvOut;
	}
SV*	av2ICE(		SV* rvArg	){
	SV	*	svA,
		**	pSv;
	int		a, za;
	ui64		x, Ac, Bc, Ec, E_;
	char		zc, ic;
	ui08		*pk, *pq;
	const char	*	arg0_err	= "\r!       ICEPack::av2ICE( <%s> ): arg[0] must be an arrayref containing a sorted list of unsigned integers.\n\t";

	if(	SvTYPE(		rvArg ) !=		SVt_RV	||!	SvROK(	rvArg ) ){
															printf( arg0_err,  svtype_names[		SvTYPE( avArg ) ] );		return &PL_sv_no; }
					avArg = (AV*)	SvRV(				rvArg );
	if(	SvTYPE(		avArg ) !=	SVt_PVAV ){					printf( arg0_err,  svtype_names_ref[	SvTYPE( avArg ) ] );	return &PL_sv_no; }
					avICE = newAV_alloc_x( 1 );
	pSv0=AvARRAY(	avICE );
		za=  AvFILLp(	avArg);
	if(	za >=0 ){
		x =	SvIVX(  svA = *AvARRAY( avArg)  );
		*( (ui64*) 		buf		)=0;	
		*( (ui64*) 		buf+1	)=0;	pk =buf;	pq =buf +16;		a=0; 	E_=0;
		AvNEW( avICE,	buf,			pk,		pq,		avArg,	a,	za,	E_ );
		}
			svA = newRV_inc( (SV*)	avICE );
	sv_bless(	svA,					hvICE );
	return	svA;
	}
void backup(		SV*	rvICE	){
	SV			**	pSvC0_	=	AvARRAY(	avICE_	),
				*	sv,
				*	sv_;
	const char	*	arg_err	= "\r!       ICEPack::copy( <%s> ): arg[%d] must be an arrayref <ICEPack>.\n\t";
	svtype const		t 		= SvTYPE(		rvICE );


	if( t != SVt_RV || !	SvROK(					rvICE ) ){	printf( arg_err,  svtype_names[		t ],	0 );	return;	}
					avICE = (AV*)	SvRV(		rvICE );
	if(	SvTYPE(		avICE ) !=	SVt_PVAV ){			printf( arg_err,  svtype_names_ref[	SvTYPE( avICE ) ] );	return; }
	SV			**	pSvC0	=	AvARRAY(	avICE );

	long long int	iC		=0,
				zC		=	AvFILLp(		avICE );

	if( zC!=-1 ){	iC=AvFILLp( avICE_ )+1;		//	printf("\n backup: iC==%lld	zC ==%lld ", zC_, zC );
			if(	iC <= zC ){
				av_extend( avICE_, zC );	AvFILLp( avICE_) =zC;
				if( &AvARRAY( avICE_ ) != &pSvC0_ )		pSvC0_	=	AvARRAY(	avICE_ );

				if( iC==-1 ) iC=0;
				for(;	iC<= zC; ++iC ){		//	printf("\n backup: create	#%lld/%lld ", iC, zC );
				if(		NULL==( sv =	*( pSvC0 +iC ) ) || !SvPOK( sv ) )	*( pSvC0_ +iC )= newSVpv(			"", 1);
						else										*( pSvC0_ +iC )=newSVsv(			sv );
				}	}

			for(iC=0;		iC<= zC_; ++iC ){	//	printf("\n backup: set	#%lld/%lld ", iC, zC_ );
				if(		NULL==( sv =	*( pSvC0 +iC ) ) || !SvPOK( sv ) )	sv_setpv( *( pSvC0_ +iC ), 			 "");
				else	if(	NULL==( sv_=	*( pSvC0_+iC ) ) || !SvPOK( sv_) )			*( pSvC0_ +iC )=newSVsv(	sv );
				else												sv_setsv(	*( pSvC0_ +iC ),		 	sv );
		}	}
	zC_=zC;
	}
SV*	retrieve(){	AvFILLp( avICE_ )=zC_;
	SV*	rvICE_ = newRV_inc( (SV*)	avICE_ );
	return rvICE_;
	}

#ifdef ENABLE_EXPERIMENTAL
/* 
SV*	toHash(		SV* rvICE	){
	svtype	rt0,		t0 = SvTYPE( rvICE );
	static const char	*	arg0_err	= "\r!       ICEPack::toHash( <%s> ): arg[1] must be an arrayref <ICEPack>.\n\t";

	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg0_err,  svtype_names[		t0 ]	);  return &PL_sv_no; }
	avICE	= (AV*) SvRV(    	rvICE );	rt0 = SvTYPE( avICE );
	if( rt0 != SVt_PVAV ){				printf( arg0_err,  svtype_names_ref[	rt0 ]	);  return &PL_sv_no; }

	_toHash();
	rvOut = newRV_inc( (SV*) hvOut );
	return rvOut;
	}
SV*	filterHV(		SV* rvICE,	SV* rvArg	){
	SV*				svOut;
	svtype	rt0, rt1,	t0 = SvTYPE( rvICE ),
					t1 = SvTYPE( rvArg );
	static const char	*	arg0_err	= "\r!       ICEPack::filterHV( <%s>, <%s> ): arg[0] must be an arrayref <ICEPack>.\n\t",
					*	arg1_err	= "\r!       ICEPack::filterHV( <%s>, <%s> ): arg[1] must be a hashref.\n\t";

	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg0_err,  svtype_names[		t0 ],  	svtype_names[	t1	] );  return &PL_sv_no; }
	if( t1 != SVt_RV || !SvROK(	rvArg) ){	printf( arg1_err,  svtype_names[		t0 ], 	svtype_names[	t1	] );  return &PL_sv_no; }
	avICE	= (AV*) SvRV(    	rvICE );	rt0 = SvTYPE( avICE );
	hvArg	= (HV*) SvRV(    	rvArg );	rt1 = SvTYPE( hvArg );
	if( rt0 != SVt_PVAV ){				printf( arg0_err,  svtype_names_ref[	rt0 ],  	svtype_names_ref[	rt1	] );  return &PL_sv_no; }
	if( rt1 != SVt_PVHV ){				printf( arg1_err,  svtype_names_ref[	rt0 ],  	svtype_names_ref[	rt1	] );  return &PL_sv_no; }
	_filterHV();
	svOut = newSViv( N );
	return svOut;
	}
SV*	alloc(		SV* rvICE	){
	SV* svA;
	const svtype t0 = SvTYPE( rvICE );
	const char	*	arg_err	= "\r!       ICEPack::alloc( <%s> ): arg[%d] must be an arrayref <ICEPack>.\n\t";
	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg_err,  svtype_names[		t0 ], 0 );	return &PL_sv_undef; }
	avICE	= (AV*) SvRV(    	rvICE );
	const svtype rt0 = SvTYPE( avICE );
	if(	rt0 != SVt_PVAV ){				printf( arg_err,  svtype_names_ref[	rt0 ], 0 );	return &PL_sv_undef; }

	return svA = _alloc()? newSVuv( x): &PL_sv_undef;
	}
*/
#endif

MODULE = ICEPack  PACKAGE = ICEPack

BOOT:
	icepack_init();

SV *
getAvDBUG ()

void
printAvDBUG ()
        PREINIT:
        I32* temp;
        PPCODE:
        temp = PL_markstack_ptr++;
        printAvDBUG();
        if (PL_markstack_ptr != temp) {
          /* truly void, because dXSARGS not invoked */
          PL_markstack_ptr = temp;
          XSRETURN_EMPTY; /* return empty stack */
        }
        /* must have used dXSARGS; list context implied */
        return; /* assume stack size is correct */

SV *
fills (rvICE, svMIN, svRUN)
	SV *	rvICE
	SV *	svMIN
	SV *	svRUN

SV *
toText (rvICE)
	SV *	rvICE

void
backup(rvICE)
	SV *	rvICE

SV *
retrieve()
	SV* rvArg


SV*
copy(rvICE)
	SV	*	rvICE
	CODE:
	{
		AV			*	avICEcp;
		SV			**	pSvC0,
					*	sv;
		const char	*	arg_err	= "\r!       ICEPack::copy( <%s> ): arg[%d] must be an arrayref <ICEPack>.\n\t";
		svtype const		t 		= SvTYPE(		rvICE );
		if( t != SVt_RV || !	SvROK(					rvICE ) ){	printf( arg_err,  svtype_names[		t ],	0 );
															RETVAL =&PL_sv_undef;
		}else{
			AV		*	AvSPV	= (AV*)	SvRV( 	rvICE );

			svtype const	rt		=	SvTYPE(		AvSPV );
					if(	rt		!=	SVt_PVAV ){				printf( arg_err,  svtype_names_ref[	rt ],	1 );  RETVAL =&PL_sv_undef; return; }
			size_t		zC		=	AvFILLp(		AvSPV );

			if( zC==-1 ){	avICEcp	=	newAV();				AvFILLp( avICEcp )=-1;
			}else{
						avICEcp	= 	newAV_alloc_x( zC +1);	AvFILLp( avICEcp ) =zC;
						pSvC0	=	AvARRAY(	avICEcp );
		
				while( zC != -1 ){
					if( NULL!=( sv = *( AvARRAY(	AvSPV ) +zC ) ) && SvPOK( sv ) )		*( pSvC0 +zC )= newSVsv( sv );
					else	*( pSvC0 +zC )= &PL_sv_undef;
					--zC;
				}	}
			SV			*	rvICEcp = newRV_inc( (SV*) avICEcp );
			RETVAL =		rvICEcp;
		}	}
	OUTPUT:
	RETVAL

SV *
upsortQ (rvArg, svQx)
	SV *	rvArg
	SV *	svQx

SV *
insortIV (rvArg, svX)
	SV *	rvArg
	SV *	svX

SV *
checks (rvICE)
	SV *	rvICE

SV *
has (rvICE, rvArg)
	SV *	rvICE
	SV *	rvArg

SV *
clears (rvICE, rvArg)
	SV *	rvICE
	SV *	rvArg

SV *
fits (rvICE, rvArg)
	SV *	rvICE
	SV *	rvArg

SV *
strikes (rvICE, rvArg)
	SV *	rvICE
	SV *	rvArg

SV *
set (rvICE, rvArg)
	SV *	rvICE
	SV *	rvArg

SV *
toPerl (rvICE)
	SV *	rvICE

SV *
av2ICE (rvArg)
	SV *	rvArg

