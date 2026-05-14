/*	third-person-singular present-tense verb methods do not modify the operand, but some modify the argument[s].	*/
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
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "dBUG.h"
#include "3ps.h"

bool _checks(){
	#if defined( DEBUG_TRUTH_L1 )
		#define dBUG3ps_NOPROB( $FUNC )	cS = sprintf(aString, 	"\rok 	%s line %lld: %s encountered no error.\n",								__FILE__, __LINE__,	$FUNC			);	AvPUSHdBUG( aString, cS );
		#define dBUG3ps_NOARG			cS = sprintf(aString, 	"\r! 	%s line %lld: (AV*) avArg array is empty.\n",								__FILE__, __LINE__					);	AvPUSHdBUG( aString, cS );
		#define dBUG3ps_NOCUBE			cS = sprintf(aString, 	"\r! 	%s line %lld: (AV*) avICE array is empty.\n",									__FILE__, __LINE__					);	AvPUSHdBUG( aString, cS );
		#define dBUGzc(		$iC )			cS = sprintf(aString, 	"\r! 	%s line %lld: cube #%lld is empty.		\n",									__FILE__, __LINE__, $iC				);	AvPUSHdBUG( aString, cS );
		#define dBUG3ps_ic(	$iC )			cS = sprintf(aString,	"\r! 	%s line %lld: cube #%lld checksum error.	\n",								__FILE__, __LINE__, $iC				);	AvPUSHdBUG( aString, cS );
		#define dBUG3ps_CS(	$iC )			cS = sprintf(aString,	"\r! 	%s line %lld: cube #%lld STRLEN error.   	( computed: %llu 	stored: %llu  )\n",	__FILE__, __LINE__, $iC,	pq-cube, CS	);	AvPUSHdBUG( aString, cS );
		#define dBUG3ps_svC(	$iC )			cS = sprintf(aString,	"\r! 	%s line %lld: cube #%lld SV* pointer is null.	\n",								__FILE__, __LINE__, $iC				);	AvPUSHdBUG( aString, cS );
	#else
		#define dBUG3ps_NOPROB
		#define dBUG3ps_NOARG
		#define dBUG3ps_NOCUBE
		#define dBUGzc(	$iC )
		#define dBUG3ps_ic(	$iC )
		#define dBUG3ps_CS(	$iC )
		#define dBUG3ps_svC(	$iC )
	#endif
	ui64			Ac, Bc, Ec;
	ui08		*	pq,	Qc;									STRLEN	CS;
	long long	int	iC,	zC = AvFILLp(	avICE );								if( zC==-1 ){					dBUG3ps_NOCUBE; return 1; } // no prob.

	SV		**	pSvC0 = AvARRAY(	avICE ),					*svC=*pSvC0;		if( svC==NULL){	dBUG3ps_svC(0);	return 0; }
	ui08									*	cube = SvPVbyte(	svC,	CS);
	char				ic,	zc = zcOf(	*( (ui64*)	cube ) );	deICE0(			Qc, Ac, Bc );	Ec = Ac +Bc;
		for(	ic = 1;	ic<=	zc;	++ic )	{				deICE(cube[ ic ],	Qc, Ac, Bc );	Ec+=Ac +Bc;
									}		if(*( (ui64*)	cube +1 ) 				!=	Ec ){    		dBUG3ps_ic( iC );	return 0; }
											if(		pq -	cube!=	CS){								dBUG3ps_CS( iC );	return 0; }



	for(		iC=1;	iC<=	zC;	++iC ){							svC=*( pSvC0 +iC ); 	if( svC==NULL){	dBUG3ps_svC(0);	return 0; }
											cube = SvPVbyte(	svC, CS );
						zc = zcOf(	*( (ui64*)	cube ) );	deICE0(			Qc, Ac, Bc );	Ec+=Ac +Bc;
		for(	ic = 1;	ic<=	zc;	++ic )	{				deICE(cube[ ic ],	Qc, Ac, Bc );	Ec+=Ac +Bc;
									}		if(*( (ui64*)	cube +1 ) 				!=	Ec ){    		dBUG3ps_ic( iC );	return 0; }
											if(		pq -	cube!=	CS){								dBUG3ps_CS( iC );	return 0; }
		}
//	dBUG3ps_NOPROB("_checks()");
	return 1; // no prob.
	}
bool _has(	/* avArgs */ 	){ //	count matches in avArgs.	return true = object contains all arguments.				Searches ICEPack;	iterates args. 		Best for large objects with few args.
	#define icOK(		$iC )	if( zc==ic ){	dBUG3ps_ic( iC)	if( a == za )				goto _none_x; 	x = ARG( ++a );	continue;		}
	#define zcOK(		$iC )	if( zc==-1 ){	do{			if( a == za ){	dBUGzc( iC)	goto _none_x;	}	x = ARG( ++a ); }	while( x < *( (ui64*) cube +1) );	\
				iC =	$iC;										dBUGzc( iC)	goto _search;	}

	#define	CoINTRaLOCj		while( x >Ec ){		icOK(	iC );		deICE(cube[++ic],	Qc, Ac, Bc );  	Ec+=	Ac+Bc;	}


	#define	INTRALOCj						zc=zcOf(	*( (ui64*)	cube ) );	ic=0;						\
		cubeZ= SvPVbyte_nolen( *( pSvC0 +iC-1) );	zcOK(	iC );	deICE0(			Qc, Ac, Bc );  	Ec = Ac +Bc+	*( (ui64*)	cubeZ+1 );	\
							while( x >Ec ){		icOK(	iC );	deICE(cube[++ic],	Qc, Ac, Bc );  	Ec+= Ac+Bc;	}


	#define	INTRALOCj1Up	if( zC  ==	iC )		goto	_none_x;							Ec =			*( (ui64*) cube +1	);	\
		cube = SvPVbyte_nolen( *(++	iC +pSvC0 ) );	zc = zcOf( *( (ui64*) cube ) );	ic=0;			\
											zcOK(	iC );	deICE0(			Qc, Ac, Bc );  	Ec += Ac+Bc;  						\
							while( x >Ec ){		icOK(	iC );	deICE(cube[++ic],	Qc, Ac, Bc );  	Ec += Ac+Bc;	}

	ui64			Ac, Bc, Ec, x;
	ui08			Qc,
			*	cube,
			*	cubeZ,
			*	pq;
	SSize_t		hit = -1;
	STRLEN		CS;
	SV		**	pSvC0 =	AvARRAY( avICE ), 	*svC,
			**	pSvA0=	AvARRAY( avArg ),		*svA;

	long long int				za = AvFILLp(	avArg ),	a=0;				if( za==-1	){	dBUG3ps_NOARG			return 1;	}
	long long int		ub,	lb,	zC = AvFILLp(	avICE ),	iC;				if( zC==-1 ){	dBUG3ps_NOCUBE		return 0;	}
	char						zc,					ic=0;

/* handle all arguments located in cube (0) as special cases */
									cube = SvPVbyte_nolen(	*pSvC0 );			x = ARG( 0 );
	if(					x <  *( (ui64*)	cube +1) ){	zc = zcOf(	*( (ui64*)	cube ) );
								zcOK( 0 );	deICE0(			Qc, Ac, Bc );  	Ec=	Ac +Bc;
		do	{	while(	x >	Ec ){	icOK( 0 );		deICE( cube[++ic],	Qc, Ac, Bc );  	Ec+=Ac +Bc;	}
	/* hit?	*/	if(		x !=	Ec
				&&		x >=	Ec-Bc )					++hit;		if( a != za )	x = ARG( ++a );	else	goto	_none_x;
			} while(		x < *( (ui64*)	cube +1) );
		}
				lb =1,	ub =zC +1,				iC= ub >>1;

	do	{							cube = SvPVbyte_nolen(	svC =*( pSvC0+iC ) );
		if(				x <	*( (ui64*)	cube +1) ){ if( (	iC=( ( ub	= iC )+lb	)>>1 )==ub ){	INTRALOCj;			goto	_intra_op; }
		}else if(			x == *( (ui64*)	cube +1) || (	iC=( ( lb	= iC )+ub	)>>1 )==lb ){	INTRALOCj1Up;				_intra_op:
			do	{
	/* hit?	*/	if(		x !=	Ec
				&&		x >= Ec-Bc )					++hit;		if( a != za )	x = ARG( ++a );	else	goto	_none_x;
				if(		x >	*( (ui64*)	cube +1) )	{				if( iC!= zC )	break;			else	goto	_none_x;	}
				if(		x == *( (ui64*)	cube +1) )	{							INTRALOCj1Up;	}
				else								{							CoINTRaLOCj;		}
				} while( 1 );
	_search:		lb =iC+1;	ub =zC +1;				iC=( lb+ub )>>1;
		}	} while( 1 );	/* search	*/
	_none_x:
	return hit==za? 1: 0;	/* np. */
	}
bool _clears(	/* avArgs */	){ //	cut matches from avArgs.	return true = object is emptied.						Searches ICEPack;	iterates args. 		Best for large objects with few args.	
	#define zcC0OK(	$iC )	if( zc==-1 ){	do{	if( a == za ){	dBUGzc($iC)	goto _none_x;	}	x = ARG( ++a );	}	while( x < *( (ui64*) cube +1) );	\
				iC =	$iC;								dBUGzc($iC)	goto _Search;	}
	ui64			Ac, Bc, Ec, x;
	ui08			Qc,
			*	cube,
			*	cubeZ,
			*	pq;
	SSize_t		hit = 0;
	STRLEN		CS;

	long long int				za = AvFILLp(	avArg ),	a=0;				if( za==-1	){	dBUG3ps_NOARG					return 1;	}
	long long int	lb,		ub,	zC = AvFILLp(	avICE ),	iC;/*=0;*/		if( zC==-1 ){	dBUG3ps_NOCUBE				return 0;	}
	char						zc,					ic=0;
	SV		**	src,
			**	dst,
			**	lim,
			**	pSvC0 =	AvARRAY( avICE ),					*svC=*pSvC0;		if( svC==NULL){	dBUG3ps_svC(0);	return 0; }
	SV		**	pSvA0 =	AvARRAY( avArg ),		*svA;

/* ######	FIND THE FIRST MATCH TO MARK-IN ARRAY SHIFT RANGE	######	*/
/* handle all arguments located in cube (0) as special cases */
									cube = SvPVbyte_nolen(	svC );				x = ARG( 0 );
	if(					x <  *( (ui64*)	cube +1) ){	zc = zcOf(	*( (ui64*)	cube ) );
								zcC0OK(0);	deICE0(			Qc, Ac, Bc );  	Ec=	Ac +Bc;
		do	{	while (	x >	Ec ){	icOK(0);		deICE(cube[++ic],	Qc, Ac, Bc );  	Ec+=Ac +Bc;	}
	/* hit?	*/	if(		x !=	Ec
				&&		x >= Ec-Bc ){	hit=1;  	SvREFCNT_dec( *(dst = pSvA0 +a) );  									goto _next_0x;	}
																if( a != za )	x = ARG( ++a );	else				return 0;
			} while(		x < *( (ui64*)	cube +1) );
		}
				lb =1,	ub =zC +1,				iC= ub >>1;

	do	{												svC=*( pSvC0 +iC ); 	if( svC==NULL){	dBUG3ps_svC(iC);	return 0;	}
									cube = SvPVbyte_nolen(	svC );
		if(				x <	*( (ui64*)	cube +1) ){ if( (	iC=( ( ub	= iC )+lb	)>>1 )==ub ){	INTRALOCj;						goto _Intra;	}
		}else if(			x == *( (ui64*)	cube +1) || (	iC=( ( lb	= iC )+ub	)>>1 )==lb ){	INTRALOCj1Up;				
_Intra	:	do	{	//	printf("\n_Intra_op:	arg #%d (%4llu) ic #%d iC%lld	", a, x, ic, iC );
	/* hit?	*/	if(		x !=	Ec
				&&		x >= Ec-Bc ){	hit=1;  	SvREFCNT_dec( *(dst = pSvA0 +a) ); 									goto _next_x;	}
																if( a != za )	x = ARG( ++a );	else				return 0;
				if(		x >	*( (ui64*)	cube +1) )	{				if( iC!= zC )	break;			else				return 0;	}
				if(		x == *( (ui64*)	cube +1) )	{							INTRALOCj1Up;	}
				else								{							CoINTRaLOCj;		}
				} while( 1 );
_Search:			lb =iC+1;	ub =zC +1;				iC=( lb+ub )>>1;
		}	} while( 1 );	/* search	*/
	return 0;	/*	none of the arguments were found. */


/* ######	ALL SUBSEQUENT MATCHES MARK-OUT AN ARRAY SHIFT RANGE	######			*/
/* handle all arguments located in cube (0) as special cases */
/*									cube = SvPVbyte_nolen(	*pSvC0 );			x =*pSvA0;
	if(					x <  *( (ui64*)	cube +1) ){	zc = zcOf(	*( (ui64*)	cube ) );
								zcOK( 0 );	deICE0(			Qc, Ac, Bc );  	Ec=	Ac +Bc;	*/
		do	{	while (	x >	Ec ){	icOK( 0 );		deICE( cube[++ic],	Qc, Ac, Bc );  	Ec+=Ac +Bc;	}
	/* hit?	*/	if(		x !=	Ec
				&&		x >= Ec-Bc )		{	SvREFCNT_dec( *( lim = pSvA0 +a ) );	
	/* collapse void */	if(	lim-dst	>	hit	  ){	src =dst +hit;  do{ *dst++ = *src++; }	while( src< lim );	}
								++	hit;	}
_next_0x:														if( a != za )	x = ARG( ++a );	else			goto _none_x;		//{ AvFILLp( avArg )-=hit;	return AvFILLp( avArg ) ==-1? 1: 0; }
			} while(	x < *( (ui64*)	cube +1) );
/*		}																			*/
				lb =1,	ub =zC +1,				iC= ub >>1;

	do	{												svC=*( pSvC0 +iC ); 	if( svC==NULL){	dBUG3ps_svC(iC);	goto _none_x;	}
									cube = SvPVbyte_nolen(	svC );
		if(				x <	*( (ui64*)	cube +1) ){ if( (	iC=( ( ub	= iC )+lb	)>>1 )==ub ){	INTRALOCj;					goto _intra;	}
		}else if(			x == *( (ui64*)	cube +1) || (	iC=( ( lb	= iC )+ub	)>>1 )==lb ){	INTRALOCj1Up;
_intra:		do	{		//printf("\n_intra_op:	arg #%d (%4llu) ic #%d iC%lld	", a, x, ic, iC );
	/* hit?	*/	if(		x !=	Ec
				&&		x >= Ec-Bc )		{	SvREFCNT_dec( *( lim = pSvA0 +a ) );/*	printf("	hit #%d/%d: %llu\n", a, za, x ); */
	/* collapse void */	if(	lim-dst	>	hit	  ){	src =dst +hit;  do{ *dst++ = *src++; }	while( src< lim );	}
								++	hit;	}
_next_x:															if( a != za )	x = ARG( ++a );	else			goto _none_x;		//{ AvFILLp( avArg )-=hit;	return AvFILLp( avArg ) ==-1? 1: 0; }
				if(		x >	*( (ui64*)	cube +1) )	{				if( iC!= zC )	break;			else			goto _none_x;	}
				if(		x == *( (ui64*)	cube +1) )	{							INTRALOCj1Up;	}
				else								{							CoINTRaLOCj;		}
				} while( 1 );
_search:			lb =iC+1;	ub =zC +1;				iC=( lb+ub )>>1;
		}	} while( 1 );	/* search	*/

_none_x:
	src =dst +hit;
	lim= pSvA0 +za;
	while( src<=lim )	*dst++ = *src++;
			AvFILLp( avArg ) -=hit;
	return	AvFILLp( avArg ) ==-1? 1: 0;/* np. */
	}
bool	_fits(	/* avArgs */ 	){ //	count matches in avArgs.	return true = argument set includes all object members.	Searches args;	iterates ICEPack. 	Best for small objects with many args.	
	printf("\n!	WARNING: _fits() needs work.  \n\
				It currently cannot tolerate a read error.  Since it scans cycla in ascending order, computing epsilon as it goes, \n\
				if it cannot read a cube, it will not be able to continue computing epsilon.\n\
				It would be possible to recover from a cube error though, if it scanned cycla in descending order,\n\
				reinitializing epsilon upon entering each cube.\n\
				Fortunately, missing cubes do not introduce any ambiguity with the logical significance of the return value.\n\
				");
	#define	FIND_X_OR_MISS( $iC )	\
	while(	x !=SvIVX( svA ) ){	\
		if(	x > SvIVX( svA ) ){	lb=a;	a=( lb+ub )>>1; if(a==lb	){	lb=LB; ub=UB; a=( lb+ub )>>1;	svA =*( pSvA0+a );	++miss; }	\
		}else{				ub=a;	a=( lb+ub )>>1; if(a==ub	){	lb=LB; ub=UB; a=( lb+ub )>>1;	svA =*( pSvA0+a );	++miss; }	\
			}																			svA =*( pSvA0+a );				\
/*hit*/	}											LB=a+1;	lb=LB; ub=UB; a=( lb+ub )>>1;	svA =*( pSvA0+a );/*	goto ... ;	*/

	long long int	LB=0, 		UB = AvFILLp(	avArg )+1;								if( UB==0	){	dBUG3ps_NOARG					return 1;	}
	long long int	lb=LB,		ub=UB,
			iC,	zC = AvFILLp(	avICE ),					a =UB >>1;					if( zC==-1 ){	dBUG3ps_NOCUBE				return 0;	}

	SSize_t 		miss = 0;
	STRLEN		CS;
	SV		**	pSvC0= AvARRAY(	avICE ),				*svC=*pSvC0;				if(	svC==NULL){					dBUG3ps_svC(0);	return 0; }
	SV		**	pSvA0= AvARRAY(	avArg ),				*svA=*pSvA0;

	ui64			Ac, Bc, Ec, x;
	ui08		*	pq,				   *	cube = SvPVbyte(	svC,	CS),	Qc;

	char		ic,		zc =zcOf(*( (ui64*)	cube ) );	deICE0(			Qc, x,  Bc );			for(	Ec=x+Bc;  x< Ec;  ++x ){			FIND_X_OR_MISS( 0 );		}
	for(		ic=1; ic<=	zc;	++ic )	{			deICE( cube[ ic ],	Qc, Ac, Bc ); x=Ec+Ac;	for(	Ec=x+Bc;  x< Ec;  ++x ){			FIND_X_OR_MISS( 0 );		}
								} 												if(	Ec	!=*( (ui64*)	cube +1 )	){  	dBUG3ps_ic( iC );	return 0; }
																				if(	CS	!= pq 	-	cube	){	dBUG3ps_CS( iC );	return 0; }

	for(		iC=1;iC<=	zC;	++iC ){						svC=*( pSvC0 +iC );			if( svC==NULL){					dBUG3ps_svC( iC );	return 0; }
									cube = SvPVbyte(	svC, CS );
					zc =zcOf(*( (ui64*)	cube ) );	deICE0(			Qc, Ac, Bc ); x=Ec+Ac;	for(	Ec=x+Bc;  x< Ec;  ++x ){			FIND_X_OR_MISS( iC );		}
		for(	ic=1; ic<=	zc;	++ic )	{			deICE( cube[ ic ],	Qc, Ac, Bc ); x=Ec+Ac;	for(	Ec=x+Bc;  x< Ec;  ++x ){			FIND_X_OR_MISS( iC );		}
								} 												if(	Ec	!=*( (ui64*)	cube +1 )	){  	dBUG3ps_ic( iC );	return 0; }
																				if(	CS	!= pq 	-	cube	){	dBUG3ps_CS( iC );	return 0; }
		}
	return miss==0? 1: 0;	/* np. */
	}
bool _strikes(	/* avArgs */	){ //	cut matches from avArgs.	return true = argument set is emptied.					Searches args;	iterates ICEPack. 	best for small objects with many args.	
	#define	PULL_X_OR_CONTINUE( $iC, $pSv )	\
	while(	x !=SvIVX( svA ) ){	\
		if(	x > SvIVX( svA ) ){	lb=a;	a=( lb+ub )>>1; if(a==lb	){	lb=LB; ub=UB; a=( lb+ub )>>1;	svA =*( pSvA0+a );	continue; }	\
		}else{				ub=a;	a=( lb+ub )>>1; if(a==ub	){	lb=LB; ub=UB; a=( lb+ub )>>1;	svA =*( pSvA0+a );	continue; }	\
			}																			svA =*( pSvA0+a );				\
/*hit*/	} SvREFCNT_dec( svA );	$pSv=	pSvA0+a;		LB=a+1;	lb=LB; ub=UB; a=( lb+ub )>>1;	svA =*( pSvA0+a );/*	goto ... ;	*/

	ui64			Ac, Bc, Ec, x;
	ui08			Qc,
			*	cube,
			*	pq;
	SSize_t 		hit;	//displacement
	STRLEN		CS;

	long long int	LB=0,	UB=	AvFILLp(	avArg )+1;										if( UB==0	){	dBUG3ps_NOARG					return 1;	}
	long long int	lb=LB,	ub=UB,
			iC,		zC =		AvFILLp(	avICE ),			a =UB >>1;						if( zC==-1 ){	dBUG3ps_NOCUBE				return 0;	}
	SV		**	src,
			**	dst,
			**	lim,
			**	pSvC0= AvARRAY( avICE ),			*	svC = *pSvC0;					if( svC==NULL){					dBUG3ps_svC(0);							return 0;		}
	SV		**	pSvA0= AvARRAY( avArg ),			*	svA = *( pSvA0 +a );
									cube = SvPVbyte(	svC, CS);
	char		ic,		zc = zcOf(*( (ui64*)	cube ) );	deICE0(			Qc, x, Bc );				for(	Ec=x+Bc;  x< Ec;  ++x ){			PULL_X_OR_CONTINUE( 0, dst );	hit=1;iC=0;	goto	_next_x;	}
		for(	ic=1; ic<=	zc;	++ic )	{			deICE( cube[ ic ],	Qc, Ac, Bc );  x=Ec+Ac;		for(	Ec=x+Bc;  x< Ec;  ++x ){			PULL_X_OR_CONTINUE( 0, dst );	hit=1;iC=0;	goto	_next_x;	}
								} 													if(	Ec	!=*( (ui64*)	cube +1 )	){  	dBUG3ps_ic( 0 );							return 0;		}
																					if(	CS	!= pq 	-	cube	){	dBUG3ps_CS( 0 );							return 0;		}

	for(		iC=1;iC<=	zC;	++iC ){						svC = *(pSvC0 +iC );				if( svC==NULL){					dBUG3ps_svC( iC );							return 0;		}
									cube = SvPVbyte(	svC, CS );
			ic=0;	zc = zcOf(*( (ui64*)	cube ) );	deICE0(			Qc, Ac, Bc );  x=Ec+Ac;		for(	Ec=x+Bc;  x< Ec;  ++x ){			PULL_X_OR_CONTINUE( iC, dst );	hit=1;		goto	_next_x;	}
		for(	ic=1; ic<=	zc;	++ic )	{			deICE( cube[ ic ],	Qc, Ac, Bc );  x=Ec+Ac;		for(	Ec=x+Bc;  x< Ec;  ++x ){			PULL_X_OR_CONTINUE( iC, dst );	hit=1;		goto	_next_x;	}
								} 													if(	Ec	!=*( (ui64*)	cube +1 )	){  	dBUG3ps_ic( 0 );							return 0;		}
																					if(	CS	!= pq 	-	cube	){	dBUG3ps_CS( 0 );							return 0;		}
		}
	return 0;	/*	after iterating ICE object, a first matching argument was never found. */

	for(		;	iC<=	zC;	++iC ){						svC = *( pSvC0 +iC );				if( svC==NULL){					dBUG3ps_svC( iC );							return 0;		}
									cube = SvPVbyte(	svC, CS );	pq=cube+16;
					zc = zcOf(*( (ui64*)	cube ) );				
		for(	ic=0; ic<=	zc;	++ic )	{			deICE(cube[ ic ],	Qc, Ac, Bc );  x = Ec+Ac;		for(	Ec=x+Bc;  x< Ec;  ++x )	{		PULL_X_OR_CONTINUE( iC, lim );

																					/* array shift to collapse void */		if(hit< lim-dst)	{	src =dst +hit;
																																	do	{ *dst++ = *src++;} while( src< lim );
																																}	++hit;							_next_x:	}
								}													if(	Ec	!=*( (ui64*)	cube +1 )	){  	dBUG3ps_ic( 0 );							return 0;		}
																					if(	CS	!= pq 	-	cube	){	dBUG3ps_CS( 0 );							return 0;		}
		}
_end:
	lim= pSvA0 + AvFILLp(	avArg );
	src= pSvA0 +lb;
	while( src<=lim )	*dst++=*src++;
			AvFILLp( avArg ) -=hit;
	return	AvFILLp( avArg ) ==-1? 1: 0;
	}
