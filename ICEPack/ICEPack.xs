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

const char* const svtype_names[] = {
	/* [SVt_NULL]: */		"SVt_NULL",		/*	0	undefined								*/
	/* [SVt_IV]: */			"SVt_IV",			/*	1	integer									*/
	/* [SVt_NV]: */		"SVt_NV",		/*	2	double/number							*/
	/* [SVt_PV]: */			"SVt_PV",		/*	3	string (PV)								*/
	/* [SVt_INVLIST]: */		"SVt_INVLIST",	/*	4	internal invlist (implemented as PV)			*/
	/* [SVt_PVIV]: */		"SVt_PVIV",		/*	5	PV that also holds an IV						*/
	/* [SVt_PVNV]: */		"SVt_PVNV",		/*	6	PV that also holds an NV					*/
	/* [SVt_PVMG]: */		"SVt_PVMG",		/*	7	normal scalar (may be magical/blessed)		*/
	/* [SVt_REGEXP]: */	"SVt_REGEXP",	/*	8	regular expression							*/
	/* [SVt_PVGV]: */		"SVt_PVGV",		/*	9	typeglob (GV)								*/
	/* [SVt_PVLV]: */		"SVt_PVLV",		/*	10	lvalue-like scalar (delegating)					*/
	/* [SVt_PVAV]: */		"SVt_PVAV",		/*	11	array (AV)								*/
	/* [SVt_PVHV]: */		"SVt_PVHV",		/*	12	hash (HV)								*/
	/* [SVt_PVCV]: */		"SVt_PVCV",		/*	13	code (CV)								*/
	/* [SVt_PVFM]: */		"SVt_PVFM",		/*	14	format (FM)								*/
	/* [SVt_PVIO]: */		"SVt_PVIO",		/*	15	I/O object / filehandle						*/
	/* [SVt_LAST]: */		"SVt_LAST",		/*	16	marker for last enum value (used to size arrays)	*/
	};
const char* const svtype_names_ref[] = {
	/* [SVt_NULL]: */		"ref/SVt_NULL",		/*	0	undefined								*/
	/* [SVt_IV]: */			"ref/SVt_IV",			/*	1	integer									*/
	/* [SVt_NV]: */		"ref/SVt_NV",			/*	2	double/number							*/
	/* [SVt_PV]: */			"ref/SVt_PV",			/*	3	string (PV)								*/
	/* [SVt_INVLIST]: */		"ref/SVt_INVLIST",		/*	4	internal invlist (implemented as PV)			*/
	/* [SVt_PVIV]: */		"ref/SVt_PVIV",		/*	5	PV that also holds an IV						*/
	/* [SVt_PVNV]: */		"ref/SVt_PVNV",		/*	6	PV that also holds an NV					*/
	/* [SVt_PVMG]: */		"ref/SVt_PVMG",		/*	7	normal scalar (may be magical/blessed)		*/
	/* [SVt_REGEXP]: */	"ref/SVt_REGEXP",		/*	8	regular expression							*/
	/* [SVt_PVGV]: */		"ref/SVt_PVGV",		/*	9	typeglob (GV)								*/
	/* [SVt_PVLV]: */		"ref/SVt_PVLV",		/*	10	lvalue-like scalar (delegating)					*/
	/* [SVt_PVAV]: */		"ref/SVt_PVAV",		/*	11	array (AV)								*/
	/* [SVt_PVHV]: */		"ref/SVt_PVHV",		/*	12	hash (HV)								*/
	/* [SVt_PVCV]: */		"ref/SVt_PVCV",		/*	13	code (CV)								*/
	/* [SVt_PVFM]: */		"ref/SVt_PVFM",		/*	14	format (FM)								*/
	/* [SVt_PVIO]: */		"ref/SVt_PVIO",		/*	15	I/O object / filehandle						*/
	/* [SVt_LAST]: */		"ref/SVt_LAST",		/*	16	marker for last enum value (used to size arrays)	*/
	};
const ui08	svtype_cnt= sizeof(svtype_names) / sizeof(svtype_names[0] );

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

	if( (t0= SvTYPE(	rvICE ) )	!= SVt_RV || ! SvROK(	rvICE ) )	{ printf( usage_err[0],  	t0< svtype_cnt? svtype_names[	t0 ]: "UNKNOWN", t1< svtype_cnt? svtype_names[t1 ]: "UNKNOWN", t2< svtype_cnt? svtype_names[t2 ]: "UNKNOWN" );		return &PL_sv_no;	}
					avICE 	= (AV*)		SvRV(	rvICE );	
	if( (t0= SvTYPE(	avICE )	!= SVt_PVAV ) )				{ printf( usage_err[0],  	t0< svtype_cnt? svtype_names_ref[t0 ]: "UNKNOWN", t1< svtype_cnt? svtype_names[t1 ]: "UNKNOWN", t2< svtype_cnt? svtype_names[t2 ]: "UNKNOWN" );		return &PL_sv_no; 	}

	SV*				C0=*AvARRAY( avICE );
	min=SvUVX(	svMIN);
	run=SvUVX(	svRUN);

	if( AvFILLp( avICE)==0 ){
		cube = SvPVbyte( C0, CS );
		zc=zcOf( cube );

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

	if( ! SvROK( rvICE) ){	L =sprintf( aString, arg_err,	svt< svtype_cnt? svtype_names[svt ]: "UNKNOWN" );		av_push( avOut, newSVpvn( aString, L ) );	return rvOut; }
	avICE	= (AV*) SvRV(	rvICE	);	/*	dereference argument									*/

	svt= SvTYPE(avICE);				/*	check type of supposed perl object at dereferenced address	*/
	if( svt != SVt_PVAV ){	L =sprintf( aString, arg_err,	svt< svtype_cnt? svtype_names_ref[svt ]: "UNKNOWN" );	av_push( avOut, newSVpvn( aString, L ) );	return rvOut; }
	if( AvFILLp( avICE ) !=-1) _toText();
	return rvOut;
	}
SV*	upsortQ(		SV* rvArg,	SV* svQx	){
	const char	*	arg0_err	= "\r!       ICEPack::upsortQ( <%s>, <%s> ): arg[0] must be an arrayref.\n\t",
				*	arg1_err	= "\r!       ICEPack::upsortQ( <%s>, <%s> ): arg[1] must be a packed quad.\n\t";
	svtype			t0 = SvTYPE( rvArg ),
					t1 = SvTYPE( svQx	);
	if( t0 != SVt_RV || !SvROK(	rvArg	) ){	printf( arg0_err,  t0< svtype_cnt? svtype_names[t0 ]: "UNKNOWN",		t1< svtype_cnt? svtype_names[t1 ]: "UNKNOWN" );		return &PL_sv_yes; }
	if( t1 != SVt_PV || !SvOK(	svQx	) ){	printf( arg1_err,  t0< svtype_cnt? svtype_names[t0 ]: "UNKNOWN",		t1< svtype_cnt? svtype_names[t1 ]: "UNKNOWN" );		return &PL_sv_yes; }
	avArg	= (AV*) SvRV(    	rvArg );	t0 = SvTYPE( avArg );
	if( t0 != SVt_PVAV ){					printf( arg0_err,  t0< svtype_cnt? svtype_names_ref[t0 ]: "UNKNOWN",  	t1< svtype_cnt? svtype_names[t1 ]: "UNKNOWN" );		return &PL_sv_yes; }

	SV			*	svQ,
				**	src,
				**	dst,
				**	sv0	= AvARRAY( avArg );
	ui08			*	pq;
	const ui08	*	pqx= SvPVbyte_nolen( svQx );
	const long long	x	= *( (ui64*) pqx );

	SSize_t			displacement;
	long long			lb	= 0,
					ub	= AvFILLp( avArg )+1,	i= ub >>1;		if( ub==0	){		svQ=newSVpvn( pqx, 8 );  SvINIT( avArg, svQ );			return &PL_sv_no;	}

						pq = SvPVbyte_nolen( svQ=	*( sv0 +i ) );
	while(	x !=	*( (ui64*)	pq )	){
		if(	x >	*( (ui64*)	pq )	){	lb=i;			i=( i +ub	)>>1;	if( i==lb	){ ++i;	svQ=newSVpvn( pqx, 8 );  SvINS( avArg, svQ, i ); 		return &PL_sv_no;  }
		}else{					ub=i;		i=( lb + i	)>>1;	if( i==ub	){		svQ=newSVpvn( pqx, 8 );  SvINS( avArg, svQ, i );			return &PL_sv_no;  }
			}			pq = SvPVbyte_nolen( svQ=	*( sv0 +i ) );
		}
	return &PL_sv_yes; 	// return true: given packed quad is already present in sorted array
	}
SV*	insortIV(		SV* rvArg,	SV* svX		){
	const char	*	arg0_err	= "\r!       ICEPack::insortIV( <%s>, <%s> ): arg[0] must be an arrayref.\n\t",
				*	arg1_err	= "\r!       ICEPack::insortIV( <%s>, <%s> ): arg[1] must be a positive / unsigned integer.	SvTYPE( svX )==%d; SVt_IV==%d\n\t";
	svtype			t0 = SvTYPE(	rvArg ),
					t1 = SvTYPE(	svX	);
	if(	t0 != SVt_RV		|| !SvROK(	rvArg	) ){	printf( arg0_err,  t0< svtype_cnt? svtype_names[t0 ]: "UNKNOWN",		t1< svtype_cnt? svtype_names[t1 ]: "UNKNOWN" );						return &PL_sv_yes; }
	if( (	t1 != SVt_IV &&
		t1 != SVt_PVIV )	|| !SvIOK(	svX		) ){	printf( arg1_err,  t0< svtype_cnt? svtype_names[t0 ]: "UNKNOWN",		t1< svtype_cnt? svtype_names[t1 ]: "UNKNOWN", SvTYPE( svX), SVt_IV );		return &PL_sv_yes; }
	avArg = (AV*)	SvRV(	rvArg );
	t0 = SvTYPE(			avArg );
	if( t0 != SVt_PVAV ){							printf( arg0_err,  t0< svtype_cnt? svtype_names_ref[t0 ]: "UNKNOWN",  	t1< svtype_cnt? svtype_names[t1 ]: "UNKNOWN" );						return &PL_sv_yes; }

	const long long	x	= SvIVX( svX );
	SSize_t			displacement;
	long long int		lb	= 0,
					ub	= AvFILLp( avArg )+1,	i= ub >>1;			if( ub==0	){		svX=newSViv( x );  SvINIT( avArg, svX );				return &PL_sv_no;	}

	SV				**	src,
					**	dst,
					**	svA0= AvARRAY( avArg ),
					*	svA	= *(svA0 +i );
	while(	x !=	SvIVX(	svA ) ){
		if(	x >	SvIVX(	svA ) ){		lb=i;			i=( i +ub	)>>1;	if( i==lb	){ ++i;	svX=newSViv( x );  SvINS( avArg, svX, i );			return &PL_sv_no;  }
		}else{						ub=i;		i=( lb + i	)>>1;	if( i==ub	){		svX=newSViv( x );  SvINS( avArg, svX, i );			return &PL_sv_no;  }
			}			svA	= *(svA0 +i );
		}
	return &PL_sv_yes; 	// return true: given integer is already present in sorted array
	}
SV*	checks(		SV* rvICE	){
	svtype	rt0,	t0 = SvTYPE( rvICE );
	const char	*	arg_err	= "\r!       ICEPack::checks( <%s> ): arg[%d] must be an arrayref <ICEPack>.\n\t";
	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg_err,  t0< svtype_cnt? svtype_names[t0 ]: "UNKNOWN", 0 );	return &PL_sv_no; }
	avICE	= (AV*) SvRV(    	rvICE );
		rt0 = SvTYPE( avICE );
	if(	rt0 != SVt_PVAV ){				printf( arg_err,  rt0< svtype_cnt? svtype_names_ref[rt0 ]: "UNKNOWN", 0 );	return &PL_sv_no; }
	bool err=_checks();
	return err? &PL_sv_yes: &PL_sv_no;
	}
SV*	has(			SV* rvICE,	SV* rvArg	){ //	count matches in avArgs.	best for large objects with few args.	return true = total inclusivity.
	const char *	arg_err	= "\r!       ICEPack::has( <%s>, <%s> ): arg[%d] must be an arrayref.\n\t";
	svtype		rt0, rt1;

	svtype const 	t0 = SvTYPE(	rvICE ),
				t1 = SvTYPE(	rvArg );

	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg_err,  t0< svtype_cnt? svtype_names[t0 ]: "UNKNOWN",  	t1< svtype_cnt? svtype_names[t1 ]: "UNKNOWN", 0 );  return &PL_sv_no; }
	if( t1 != SVt_RV || !SvROK(	rvArg) ){	printf( arg_err,  t0< svtype_cnt? svtype_names[t0 ]: "UNKNOWN", 	t1< svtype_cnt? svtype_names[t1 ]: "UNKNOWN", 0 );  return &PL_sv_no; }

	avICE	= (AV*) SvRV(    	rvICE );	rt0 = SvTYPE( avICE );
	avArg	= (AV*) SvRV(    	rvArg );	rt1 = SvTYPE( avArg );

	if( rt0 != SVt_PVAV ){				printf( arg_err,  rt0< svtype_cnt? svtype_names_ref[rt0 ]: "UNKNOWN",  	rt1< svtype_cnt? svtype_names_ref[rt1 ]: "UNKNOWN", 1 );  return &PL_sv_no; }
	if( rt1 != SVt_PVAV ){				printf( arg_err,  rt0< svtype_cnt? svtype_names_ref[rt0 ]: "UNKNOWN",  	rt1< svtype_cnt? svtype_names_ref[rt1 ]: "UNKNOWN", 1 );  return &PL_sv_no; }

	return _has() ? &PL_sv_yes: &PL_sv_no;
	}
SV*	clears(		SV* rvICE,	SV* rvArg	){ //	cut matches from avArgs.	best for large objects with few args.	return true = total inclusivity.
	const char *	arg_err	= "\r!       ICEPack::clears( <%s>, <%s> ): arg[%d] must be an arrayref.\n\t";
	svtype		rt0, rt1;

	svtype const 	t0 = SvTYPE(	rvICE ),
				t1 = SvTYPE(	rvArg );

	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg_err,  t0< svtype_cnt? svtype_names[t0 ]: "UNKNOWN",  	t1< svtype_cnt? svtype_names[t1 ]: "UNKNOWN", 0 );  return &PL_sv_no; }
	if( t1 != SVt_RV || !SvROK(	rvArg) ){	printf( arg_err,  t0< svtype_cnt? svtype_names[t0 ]: "UNKNOWN", 	t1< svtype_cnt? svtype_names[t1 ]: "UNKNOWN", 0 );  return &PL_sv_no; }

	avICE	= (AV*) SvRV(    	rvICE );	rt0 = SvTYPE( avICE );
	avArg	= (AV*) SvRV(    	rvArg );	rt1 = SvTYPE( avArg );

	if( rt0 != SVt_PVAV ){				printf( arg_err,  rt0< svtype_cnt? svtype_names_ref[rt0 ]: "UNKNOWN",  	rt1< svtype_cnt? svtype_names_ref[rt1 ]: "UNKNOWN", 1 );  return &PL_sv_no; }
	if( rt1 != SVt_PVAV ){				printf( arg_err,  rt0< svtype_cnt? svtype_names_ref[rt0 ]: "UNKNOWN",  	rt1< svtype_cnt? svtype_names_ref[rt1 ]: "UNKNOWN", 1 );  return &PL_sv_no; }

	return _clears()? &PL_sv_yes: &PL_sv_no;
	}
SV*	fits(			SV* rvICE,	SV* rvArg	){ //	count matches in avArgs.	best for small objects with many args.	return true = total inclusivity.
	const char *	arg_err	= "\r!       ICEPack::fits( <%s>, <%s> ): arg[%d] must be an arrayref.\n\t";
	svtype		rt0, rt1;

	svtype const 	t0 = SvTYPE(	rvICE ),
				t1 = SvTYPE(	rvArg );

	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg_err,  t0< svtype_cnt? svtype_names[t0 ]: "UNKNOWN",  	t1< svtype_cnt? svtype_names[t1 ]: "UNKNOWN", 0 );  return &PL_sv_no; }
	if( t1 != SVt_RV || !SvROK(	rvArg) ){	printf( arg_err,  t0< svtype_cnt? svtype_names[t0 ]: "UNKNOWN", 	t1< svtype_cnt? svtype_names[t1 ]: "UNKNOWN", 0 );  return &PL_sv_no; }

	avICE	= (AV*) SvRV(    	rvICE );	rt0 = SvTYPE( avICE );
	avArg	= (AV*) SvRV(    	rvArg );	rt1 = SvTYPE( avArg );

	if( rt0 != SVt_PVAV ){				printf( arg_err,  rt0< svtype_cnt? svtype_names_ref[rt0 ]: "UNKNOWN",  	rt1< svtype_cnt? svtype_names_ref[rt1 ]: "UNKNOWN", 1 );  return &PL_sv_no; }
	if( rt1 != SVt_PVAV ){				printf( arg_err,  rt0< svtype_cnt? svtype_names_ref[rt0 ]: "UNKNOWN",  	rt1< svtype_cnt? svtype_names_ref[rt1 ]: "UNKNOWN", 1 );  return &PL_sv_no; }

	return _fits()? &PL_sv_yes: &PL_sv_no;
	}
SV*	strikes(		SV* rvICE,	SV* rvArg	){ //	cut matches from avArgs.	best for small objects with many args.	return true = total inclusivity.
	const char *	arg_err	= "\r!       ICEPack::strikes( <%s>, <%s> ): arg[%d] must be an arrayref.\n\t";
	svtype		rt0, rt1;

	svtype const 	t0 = SvTYPE(	rvICE ),
				t1 = SvTYPE(	rvArg );

	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg_err,  t0< svtype_cnt? svtype_names[t0 ]: "UNKNOWN",  	t1< svtype_cnt? svtype_names[t1 ]: "UNKNOWN", 0 );  return &PL_sv_no; }
	if( t1 != SVt_RV || !SvROK(	rvArg) ){	printf( arg_err,  t0< svtype_cnt? svtype_names[t0 ]: "UNKNOWN", 	t1< svtype_cnt? svtype_names[t1 ]: "UNKNOWN", 0 );  return &PL_sv_no; }

	avICE	= (AV*) SvRV(    	rvICE );	rt0 = SvTYPE( avICE );
	avArg	= (AV*) SvRV(    	rvArg );	rt1 = SvTYPE( avArg );

	if( rt0 != SVt_PVAV ){				printf( arg_err,  rt0< svtype_cnt? svtype_names_ref[rt0 ]: "UNKNOWN",  	rt1< svtype_cnt? svtype_names_ref[rt1 ]: "UNKNOWN", 1 );  return &PL_sv_no; }
	if( rt1 != SVt_PVAV ){				printf( arg_err,  rt0< svtype_cnt? svtype_names_ref[rt0 ]: "UNKNOWN",  	rt1< svtype_cnt? svtype_names_ref[rt1 ]: "UNKNOWN", 1 );  return &PL_sv_no; }

	return _strikes()? &PL_sv_yes: &PL_sv_no;
	}
SV*	set(			SV* rvICE,	SV* rvArg	){

	svtype	rt0, rt1,	t0 = SvTYPE( rvICE ),
					t1 = SvTYPE( rvArg );
	const char	*	arg_err	= "\r!       ICEPack::set( <%s>, <%s> ): arg[%d] must be an arrayref.\n\t";

	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg_err,  t0< svtype_cnt? svtype_names[t0 ]: "UNKNOWN",  	t1< svtype_cnt? svtype_names[t1 ]: "UNKNOWN", 0 );  return &PL_sv_no; }
	if( t1 != SVt_RV || !SvROK(	rvArg) ){	printf( arg_err,  t0< svtype_cnt? svtype_names[t0 ]: "UNKNOWN", 	t1< svtype_cnt? svtype_names[t1 ]: "UNKNOWN", 0 );  return &PL_sv_no; }

	avICE	= (AV*) SvRV(    	rvICE );	rt0 = SvTYPE( avICE );
	avArg	= (AV*) SvRV(    	rvArg );	rt1 = SvTYPE( avArg );

	if( rt0 != SVt_PVAV ){				printf( arg_err,  rt0< svtype_cnt? svtype_names_ref[rt0 ]: "UNKNOWN",  	rt1< svtype_cnt? svtype_names_ref[rt1 ]: "UNKNOWN", 1 );  return &PL_sv_no; }
	if( rt1 != SVt_PVAV ){				printf( arg_err,  rt0< svtype_cnt? svtype_names_ref[rt0 ]: "UNKNOWN",  	rt1< svtype_cnt? svtype_names_ref[rt1 ]: "UNKNOWN", 1 );  return &PL_sv_no; }

	_set240();

	return newSViv( za +1 -hit );
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
void snapshot(		SV*	rvICE	){	// —Stores one single copy of any given <ICE> object in global AV* avICE_.
	SV			*	sv,				// designed for memory efficiency while being called from within an indefinite loop
				*	sv_;
	const char	*	arg_err	= "\r!       ICEPack::snapshot( <%s> ): arg[%d] must be an arrayref <ICEPack>.\n\t";
	svtype const		t 		= SvTYPE(		rvICE );


	if( t != SVt_RV || !	SvROK(					rvICE ) ){	printf( arg_err,  t< svtype_cnt? svtype_names[t ]: "UNKNOWN",	0 );	return;	}
	AV			*	avICE = (AV*)	SvRV(		rvICE );
	if(	SvTYPE(		avICE ) !=	SVt_PVAV ){			printf( arg_err,  svtype_names_ref[	SvTYPE( avICE ) ] );	return; }
	SV			**	pSvC0	=	AvARRAY(	avICE );

	long long unsigned	Ec		=0;
	long long int		iC		=0,
					zC		=	AvFILLp(		avICE ),
					zC_,
					nC		=	zC+1;
	if( !AvALLOC( avICE_ ) || AvMAX( avICE_ )<=0	){
			zC_=-1;	av_extend(	avICE_, zC		);
					AvFILLp(		avICE_			) =	zC;
	}else{	zC_ =	AvFILLp(		avICE_ );
		if(	zC_< zC ){
					av_extend(	avICE_, zC		);
					AvFILLp(		avICE_			) =	zC;
		}			}

	SV			**	pSvC0_	=	AvARRAY(	avICE_		);
	if( zC_ > zC ) zC_=zC;

	for(;	iC<= zC_;	++iC ){	sv =*( pSvC0 +iC );
		if(		NULL ==	sv || !SvPOK( sv ) || SvCUR( sv )< 16 )	{
			if(	NULL ==( sv_=*( pSvC0_+iC ) ) || !SvPOK( sv_) )	{			*( pSvC0_ +iC )= newSVpvn(	nube, 16 );	printf("\nsnapshot() glitch at #%d line %lld\n", iC, __LINE__);
			}else											sv_setpv( *( pSvC0_ +iC ),			nube );	//	printf("\nsnapshot() set SV #%lld/%lld	NULL\n", iC, zC );
		/*	*( (ui64*) nube +1) =	Ec;	*/
		}else{				/*	Ec =	*( (ui64*) SvPVbyte_nolen( sv ) +1);	*/
			if(	NULL ==( sv_=*( pSvC0_+iC ) ) || !SvPOK( sv_) )	{			*( pSvC0_ +iC )= newSVsv(	sv );			printf("\nsnapshot() glitch at #%d line %lld\n", iC, __LINE__);
			}else											sv_setsv(	*( pSvC0_ +iC ),		 	sv );		//	printf("\nsnapshot() set SV #%lld/%lld\n", iC, zC );
		}	}
	for(;	iC<= zC;	++iC ){	sv =*( pSvC0 +iC );
		if(		NULL ==	sv || !SvPOK( sv ) || SvCUR( sv )< 16 )	{
		/*	*( (ui64*) nube +1) =	Ec;	*/								*( pSvC0_ +iC )= newSVpvn(	nube, 16 );	printf("\nsnapshot() glitch at #%d line %lld\n", iC, __LINE__);
		}else{				/*	Ec =	*( (ui64*) SvPVbyte_nolen( sv ) +1);	*/
																	*( pSvC0_ +iC )= newSVsv(	sv );
		}	}

	zCs=zC;
	}
SV*	getSnapshot(){	AvFILLp( avICE_ )=zCs;
	SV*	rvICE_ = newRV_inc( (SV*)	avICE_ );
	avICE_=newAV();
	return rvICE_;
	}

#ifdef ENABLE_EXPERIMENTAL
/* 
SV*	toHash(		SV* rvICE	){
	svtype	rt0,		t0 = SvTYPE( rvICE );
	static const char	*	arg0_err	= "\r!       ICEPack::toHash( <%s> ): arg[1] must be an arrayref <ICEPack>.\n\t";

	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg0_err,  t0< svtype_cnt? svtype_names[t0 ]: "UNKNOWN"	);  return &PL_sv_no; }
	avICE	= (AV*) SvRV(    	rvICE );	rt0 = SvTYPE( avICE );
	if( rt0 != SVt_PVAV ){				printf( arg0_err,  rt0< svtype_cnt? svtype_names_ref[rt0 ]: "UNKNOWN"	);  return &PL_sv_no; }

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

	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg0_err,  t0< svtype_cnt? svtype_names[t0 ]: "UNKNOWN",  		t1< svtype_cnt? svtype_names[t1 ]: "UNKNOWN" );  return &PL_sv_no; }
	if( t1 != SVt_RV || !SvROK(	rvArg) ){	printf( arg1_err,  t0< svtype_cnt? svtype_names[t0 ]: "UNKNOWN", 			t1< svtype_cnt? svtype_names[t1 ]: "UNKNOWN" );  return &PL_sv_no; }
	avICE	= (AV*) SvRV(    	rvICE );	rt0 = SvTYPE( avICE );
	hvArg	= (HV*) SvRV(    	rvArg );	rt1 = SvTYPE( hvArg );
	if( rt0 != SVt_PVAV ){				printf( arg0_err,  rt0< svtype_cnt? svtype_names_ref[rt0 ]: "UNKNOWN",  	rt1< svtype_cnt? svtype_names_ref[rt1 ]: "UNKNOWN" );  return &PL_sv_no; }
	if( rt1 != SVt_PVHV ){				printf( arg1_err,  rt0< svtype_cnt? svtype_names_ref[rt0 ]: "UNKNOWN",  	rt1< svtype_cnt? svtype_names_ref[rt1 ]: "UNKNOWN" );  return &PL_sv_no; }
	_filterHV();
	svOut = newSViv( N );
	return svOut;
	}
SV*	alloc(		SV* rvICE	){
	SV* svA;
	const svtype t0 = SvTYPE( rvICE );
	const char	*	arg_err	= "\r!       ICEPack::alloc( <%s> ): arg[%d] must be an arrayref <ICEPack>.\n\t";
	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg_err,  t0< svtype_cnt? svtype_names[t0 ]: "UNKNOWN", 0 );	return &PL_sv_undef; }
	avICE	= (AV*) SvRV(    	rvICE );
	const svtype rt0 = SvTYPE( avICE );
	if(	rt0 != SVt_PVAV ){				printf( arg_err,  rt0< svtype_cnt? svtype_names_ref[rt0 ]: "UNKNOWN", 0 );	return &PL_sv_undef; }

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

SV *
toHex (rvICE)
	SV *	rvICE

void
snapshot(rvICE)
	SV *	rvICE

SV *
getSnapshot()
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
		if( t != SVt_RV || !	SvROK(					rvICE ) ){	printf( arg_err,  t< svtype_cnt? svtype_names[t ]: "UNKNOWN",	0 );
															RETVAL =&PL_sv_undef;
		}else{
			AV		*	AvSPV	= (AV*)	SvRV( 	rvICE );

			svtype const	rt		=	SvTYPE(		AvSPV );
					if(	rt		!=	SVt_PVAV ){				printf( arg_err,  rt< svtype_cnt? svtype_names_ref[rt ]: "UNKNOWN",	1 );  RETVAL =&PL_sv_undef; return; }
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
av2ICE (rvArg)
	SV *	rvArg

