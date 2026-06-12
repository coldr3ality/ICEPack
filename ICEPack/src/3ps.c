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
/*	3ps.c: third-person-singular present-tense methods which do not modify the operand, but rather, may modify the argument[s].	*/
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "dBUG.h"
#include "3ps.h"

#define Epsilon(	$cube) ( 	(ui64*) $cube+1)
bool _addsUp(){
	#if defined( DEBUG_TRUTH_L1 )
		#define dBUG3ps_NOPROB			cS = sprintf(aString, "\rok	%s in %s line %lld: %s encountered no error.\n",									__FUNCTION__, __FILE__, __LINE__				);	AvDBUG_PUSH( aString, cS );
		#define dBUG3ps_NOARG			cS = sprintf(aString, 	"\r! 	%s in %s line %lld: (AV*) avArg array is empty.\n",								__FUNCTION__, __FILE__, __LINE__				);	AvDBUG_PUSH( aString, cS );
		#define dBUG3ps_NOCUBE			cS = sprintf(aString, 	"\r! 	%s in %s line %lld: (AV*) avICE array is empty.\n",								__FUNCTION__, __FILE__, __LINE__				);	AvDBUG_PUSH( aString, cS );
		#define dBUGzc(		$iC )			cS = sprintf(aString, 	"\r! 	%s in %s line %lld: cube #%lld is empty.		\n",									__FUNCTION__, __FILE__, __LINE__, $iC				);	AvDBUG_PUSH( aString, cS );
		#define dBUG3ps_ic(	$iC )			cS = sprintf(aString,	"\r! 	%s in %s line %lld: cube #%lld checksum error.	\n",								__FUNCTION__, __FILE__, __LINE__, $iC				);	AvDBUG_PUSH( aString, cS );
		#define dBUG3ps_CS(	$iC )			cS = sprintf(aString,	"\r! 	%s in %s line %lld: cube #%lld STRLEN error.   	( computed: %llu 	stored: %llu  )\n",	__FUNCTION__, __FILE__, __LINE__, $iC, pq-cube, CS	);	AvDBUG_PUSH( aString, cS );
		#define dBUG3ps_svC(	$iC )			cS = sprintf(aString,	"\r! 	%s in %s line %lld: cube #%lld SV* pointer is null.	\n",								__FUNCTION__, __FILE__, __LINE__, $iC				);	AvDBUG_PUSH( aString, cS );
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

	SV		**	psvC0 = AvARRAY(	avICE ),				*svC=*psvC0;				if( svC==NULL){	dBUG3ps_svC(0);	return 0; }
	ui08							*	cube = SvPVbyte(	svC,	CS);
	char				ic,	zc = zcOf(	cube );	deICE0(			Qc, Ac, Bc );	Ec = Ac +Bc;
		for(	ic = 1;	ic<=	zc;	++ic )	{				deICE(cube[ ic ],	Qc, Ac, Bc );	Ec+=Ac +Bc;
									}		if(*( (ui64*)	cube +1 ) 				!=	Ec ){    		dBUG3ps_ic( iC );	return 0; }
											if(		pq -	cube!=	CS){								dBUG3ps_CS( iC );	return 0; }



	for(		iC=1;	iC<=	zC;	++iC ){							svC=*( psvC0 +iC ); 	if( svC==NULL){	dBUG3ps_svC(0);	return 0; }
									cube = SvPVbyte(	svC, CS );
						zc = zcOf(	cube );	deICE0(			Qc, Ac, Bc );	Ec+=Ac +Bc;
		for(	ic = 1;	ic<=	zc;	++ic )	{				deICE(cube[ ic ],	Qc, Ac, Bc );	Ec+=Ac +Bc;
									}		if(*( (ui64*)	cube +1 ) 				!=	Ec ){    		dBUG3ps_ic( iC );	return 0; }
											if(		pq -	cube!=	CS){								dBUG3ps_CS( iC );	return 0; }
		}
//	dBUG3ps_NOPROB
	return 1; // no prob.
	}
ui64 _has(	/* avArgs */ 	){ //	count matches in avArgs.	return number of hits.		Searches ICEPack;	iterates args. 		Best for large objects with few args.
	#define icOK(		$iC )	if( zc==ic ){dBUG3ps_ic( iC)	if( a == za )				goto _none_x; 	x = ARG( ++a );	continue;		}
	#define zcOK(		$iC )	if( zc==-1 ){	do{			if( a == za ){	dBUGzc( iC)	goto _none_x;	}	x = ARG( ++a ); }	while( x < *( (ui64*) cube +1) );	\
				iC =	$iC;										dBUGzc( iC)	goto _search;	}

	#define	CoINTRaLOCj		while( x >Ec ){		icOK(	iC );		deICE(cube[++ic],	Qc, Ac, Bc );  	Ec+=	Ac+Bc;	}


	#define	INTRALOCj						zc = zcOf(	cube );	ic=0;						\
		cubeZ= SvPVbyte_nolen( *( psvC0 +iC-1) );	zcOK(	iC );	deICE0(			Qc, Ac, Bc );  	Ec = Ac +Bc+	*( (ui64*)	cubeZ+1 );	\
							while( x >Ec ){		icOK(	iC );	deICE(cube[++ic],	Qc, Ac, Bc );  	Ec+= Ac+Bc;	}


	#define	INTRALOCj1Up	if( zC  ==	iC )		goto	_none_x;							Ec =			*( (ui64*) cube +1	);	\
		cube = SvPVbyte_nolen( *(++	iC +psvC0 ) );	zc = zcOf(	cube );	ic=0;			\
											zcOK(	iC );	deICE0(			Qc, Ac, Bc );  	Ec += Ac+Bc;  						\
							while( x >Ec ){		icOK(	iC );	deICE(cube[++ic],	Qc, Ac, Bc );  	Ec += Ac+Bc;	}

	ui64			Ac, Bc, Ec, x;
	ui08			Qc,
			*	cube,
			*	cubeZ,
			*	pq;
	ui64			off=0;
	STRLEN		CS;
	SV		**	psvC0 =	AvARRAY( avICE ), 	*svC,
			**	psvA0=	AvARRAY( avArg ),		*svA;

	long long int				za = AvFILLp(	avArg ),	a=0;				if( za==-1	){	dBUG3ps_NOARG			return 0;	}
	long long int		ub,	lb,	zC = AvFILLp(	avICE ),	iC;				if( zC==-1 ){	dBUG3ps_NOCUBE		return 0;	}
	char						zc,					ic=0;

/* handle all arguments located in cube (0) as special cases */
									cube = SvPVbyte_nolen(	*psvC0 );			x = ARG( 0 );
	if(					x <  *( (ui64*)	cube +1) ){	zc = zcOf(	cube );
								zcOK( 0 );	deICE0(			Qc, Ac, Bc );  	Ec=	Ac +Bc;
		do	{	while(	x >	Ec ){	icOK( 0 );		deICE( cube[++ic],	Qc, Ac, Bc );  	Ec+=Ac +Bc;	}
	/* hit?	*/	if(		x !=	Ec
				&&		x >=	Ec-Bc )					++off;		if( a != za )	x = ARG( ++a );	else	goto	_none_x;
			} while(		x < *( (ui64*)	cube +1) );
		}
				lb =1,	ub =zC +1,				iC= ub >>1;

	do	{							cube = SvPVbyte_nolen(	svC =*( psvC0+iC ) );
		if(				x <	*( (ui64*)	cube +1) ){ if( (	iC=( ( ub	= iC )+lb	)>>1 )==ub ){	INTRALOCj;			goto	_intra_op; }
		}else if(			x == *( (ui64*)	cube +1) || (	iC=( ( lb	= iC )+ub	)>>1 )==lb ){	INTRALOCj1Up;				_intra_op:
			do	{
	/* hit?	*/	if(		x !=	Ec
				&&		x >= Ec-Bc )					++off;		if( a != za )	x = ARG( ++a );	else	goto	_none_x;
				if(		x >	*( (ui64*)	cube +1) )	{				if( iC!= zC )	break;			else	goto	_none_x;	}
				if(		x == *( (ui64*)	cube +1) )	{							INTRALOCj1Up;	}
				else								{							CoINTRaLOCj;		}
				} while( 1 );
	_search:		lb =iC+1;	ub =zC +1;				iC=( lb+ub )>>1;
		}	} while( 1 );	/* search	*/
	_none_x:
	return off;	/* np. */
	}



#define	_INTRALOC					/* Initialize Ec with *Epsilon of the cube before the current cube.		*/\
									cubeZ= SvPVbyte( *( psvC0 +iC-1), CSZ );		if(		CSZ< 16		){	dBUG_6A( cube_err[4], __FUNCTION__, "", iC-1, CSZ,	__FILE__, __LINE__ );if( iC!=zC){ ++iC; continue; } else {	off=1+za-a; SvREFCNT_dec( *( dst = psvA0 +a ) ); NX;	goto _none_x;	}	}
#define	_INTRALOC1Up(	$CUBE_MISS )/* Initialize Ec with *Epsilon of current cube, then move one cube up.	*/\
						if(	iC!=zC ){	cubeZ=cube;								\
									cube = SvPVbyte( *(++iC +psvC0 ), CS );		if(		CS< 16		){	dBUG_6A( cube_err[4], __FUNCTION__, "", iC,	CS,	__FILE__, __LINE__ );	\
																								goto $CUBE_MISS;	}	\
						}else		{											NX;	goto _none_x;	}

#define	_nINTRALOC1Up				/* Initialize Ec with *Epsilon of current cube, then move one cube up.	*/\
						if(	iC!=zC ){	cubeZ=cube;								\
									cube = SvPVbyte( *(++iC +psvC0 ), CS );		if(		CS< 16		){	dBUG_6A( cube_err[4], __FUNCTION__, "", iC,	CS,	__FILE__, __LINE__ );	\
																								goto _cube_miss;	}	\
						}else		{					SvREFCNT_dec( *(	lim=	psvA0 +a ) );			\
		/* collapse void */				if(	off < lim-dst )	{				src=	dst+	off;					\
										do	{ *dst++ = *src++; } while(	src<	lim );					\
										}off +=1+za-a;								NX;	goto _none_x;	\
									}

#define _x0_nINTRALOC1Up				/* Initialize Ec with *Epsilon of current cube, then move one cube up.	*/\
						if(	iC!=zC ){	cubeZ=cube;								\
									cube = SvPVbyte( *(++iC +psvC0 ), CS );		if(		CS< 16		){	dBUG_6A( cube_err[4], __FUNCTION__, "", iC,	CS,	__FILE__, __LINE__ );	\
																								goto _x0_cube_miss;	}	\
						}else		{ off =1+za-a;	SvREFCNT_dec( *(	dst = psvA0 +a ) );	NX;	goto _none_x;	}



//bool _retains?

//	#define CR printf("	returns at line %lld (AvFILLp( avArg ) ==%lld)\n", __LINE__, AvFILLp( avArg ) );
//	#define NX printf("	goto _none_x at line %lld\n", __LINE__ );	
//	#define FM printf("	first miss at line %lld\n", __LINE__ );
//	#define BS printf("	break dwell loop at line %lld\n",	__LINE__ );
//	#define UP printf("	goto _intraloc1up at line %lld\n", 	__LINE__ );
//	#define Up printf("	goto _x0_intraloc1up at line %lld\n", 	__LINE__ );

	#define CR
	#define NX
	#define FM
	#define BS
	#define UP
	#define Up

//	"xMatchingOf"
//	"includes"
bool _includes(			/* avArgs */	){ //	cut non-matches from avArgs.	return true if any match.	Searches ICEPack;	iterates args. 		Best for large objects with few args.	
//	printf("\n_holds(): \n");
	ui08			Qc,
			*	cube,
			*	cubeZ,
			*	pq;
	STRLEN		CS, CSZ;

	long long int				za = AvFILLp(	avArg ),	a=0, a_;						if( za==-1	){	dBUG3ps_NOARG;		{CR;					return 0;	}	}
	long long int	lb,		ub,	zC = AvFILLp(	avICE ),	iC;/*=0;*/					if( zC==-1 ){	dBUG3ps_NOCUBE;	{CR; av_clear( avArg )	;return 0;	}	}
	char			zcZ,			zc,					ic=0;

	ui64			Ac, Bc, Ec, x,
				off=0;	/* running shift offset								*/
	SV		**	src,		/* earliest "hit" argument in queue to be shifted			*/
			**	dst,		/* earliest "miss" argument in queue to be overwritten	*/
			**	lim,		/* latest "limit" argument pending hit/miss evaluation while the shift queue buffers and possibly flushes*/
			**	psvA0 =	AvARRAY( avArg ),
			**	psvC0 =	AvARRAY( avICE ),				*svC=*psvC0;				if(		svC 	== NULL	){	dBUG_5A( cube_err[1], __FUNCTION__, "", iC,		__FILE__, __LINE__ );	if( zC) goto _x0_search;	else{CR; av_clear( avArg ); return 0;	}	}
																			else if(	!SvOK( 	svC)	){	dBUG_6A( cube_err[2], __FUNCTION__, "", iC, &*svC,	__FILE__, __LINE__ );	if( zC) goto _x0_search;	else{CR; av_clear( avArg ); return 0;	}	}
																			else if(	!SvPOK( 	svC)	){	dBUG_6A( cube_err[3], __FUNCTION__, "", iC, &*svC,	__FILE__, __LINE__ );	if( zC) goto _x0_search;	else{CR; av_clear( avArg ); return 0;	}	}
/*	######	######	######	######	######	######	######	######	######	######		*/
/*										BLOCK  1										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
/*					FIND THE FIRST MATCH TO MARK-IN ARRAY SHIFT RANGE					*/
/*			The conditional statements commented "x0 miss?" mark-in each AV shift range.			*/
/*			It is to isolate these cases implicitly that the search loop code is differentiated 4x here—		*/
/*			that, and to initialize *Epsilon of cube 0 specially, so to eliminate a branch.					*/

						x = ARG( 0 );	cube = SvPVbyte(	svC, CS );				if(		CS< 16		){	dBUG_6A( cube_err[4], __FUNCTION__, "", iC,	CS,	__FILE__, __LINE__ );	if( zC) goto _x0_search;	else{CR; av_clear( avArg ); return 0;	}	}
	if(					x <  *Epsilon(	cube ) ){
							zc=zcOf(	cube );
					if(		zc!=-1 ){	deICE0(				Qc, Ac, Bc );  	Ec=	Ac +Bc;
/*cube 0 err	*/		}else{																			dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Epsilon( cube),	__FILE__, __LINE__ );
												iC=0;											goto _x0_cube_miss;
						}						ic=0;
			do	{ while( x >Ec )	{
					if(		ic!=zc ){	deICE( cube[	++ic ],	Qc, Ac, Bc );  	Ec+=Ac +Bc;
/*cube 0 err	*/		}else{						iC=0;												dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Epsilon( cube),	__FILE__, __LINE__ );
																								goto _x0_cube_miss;
					}	}
/* x0 miss?	*/	if(		x ==	Ec
				||		x < Ec-Bc ){	off =1;			SvREFCNT_dec( *( dst = psvA0 +a ) );			FM;	goto _C0_next_x;	}

				if( a!=za )	x = ARG( ++a );										else					{CR;return 1;}
				} while(	x < *Epsilon(	cube ) );
			}
/*	######	######	######	######	######	######	######	######	######	######		*/
/*										BLOCK  2										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
/* 	######		1ST MATCH NOT FOUND IN CUBE 0;		SEARCHING CUBES >0		######		*/

_x0_search:					lb =1;	ub =zC +1;	iC= ub >>1;
	do	{											svC=*( psvC0 +iC ); 		if(		svC 	== NULL	){	dBUG_5A( cube_err[1], __FUNCTION__, "", iC,		__FILE__, __LINE__ ); if( iC!=zC){ ++iC; continue; } else {	off=1+za-a;	SvREFCNT_dec( *( dst = psvA0 +a ) );	NX;	goto _none_x;	}	}
																			else if(	!SvOK( 	svC)	){	dBUG_6A( cube_err[2], __FUNCTION__, "", iC,&*svC,	__FILE__, __LINE__ ); if( iC!=zC){ ++iC; continue; } else {	off=1+za-a;	SvREFCNT_dec( *( dst = psvA0 +a ) );	NX;	goto _none_x;	}	}
																			else if(	!SvPOK( 	svC)	){	dBUG_6A( cube_err[3], __FUNCTION__, "", iC,&*svC,	__FILE__, __LINE__ ); if( iC!=zC){ ++iC; continue; } else {	off=1+za-a;	SvREFCNT_dec( *( dst = psvA0 +a ) );	NX;	goto _none_x;	}	}
									cube = SvPVbyte(	svC, CS );				if(		CS< 16		){	dBUG_6A( cube_err[4], __FUNCTION__, "", iC,	CS,	__FILE__, __LINE__ ); if( iC!=zC){ ++iC; continue; } else {	off=1+za-a;	SvREFCNT_dec( *( dst = psvA0 +a ) );	NX;	goto _none_x;	}	}
		/* Now that we have verified cube iC, we are clear to read *Epsilon( cube ).		*/
		if(				x <	*Epsilon(	cube ) ){ if( (	iC=( ( ub	= iC )+lb	)>>1 )==ub ){	/*
_x0_intraloc: 	*/						cubeZ= SvPVbyte( *( psvC0 +iC-1), CSZ );		if(		CSZ< 16		){	dBUG_6A( cube_err[4], __FUNCTION__, "", iC-1, CSZ,	__FILE__, __LINE__ ); if( iC!=zC){ ++iC; continue; } else {	off=1+za-a;	SvREFCNT_dec( *( dst = psvA0 +a ) );	NX;	goto _none_x;	}	}
																								goto _x0_intra;	}
		}else if(			x == *Epsilon(	cube ) || (	iC=( ( lb	= iC )+ub	)>>1 )==lb ){	_x0_intraloc1up:
																			_x0_nINTRALOC1Up;
_x0_intra:	ic=0;  			zc=zcOf(	cube );
			if(				zc!=-1 ){	deICE0(				Qc, Ac, Bc );  	Ec = Ac+Bc+ *Epsilon( cubeZ );
			   do	{ while(	x >Ec ){
					if(		zc!=ic ){	deICE( cube[	++ic ],	Qc, Ac, Bc );  	Ec += Ac+Bc;
/*cube iC err	*/		}else{							SvREFCNT_dec( *(	dst = psvA0 +a ) );					dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Epsilon( cube),	__FILE__, __LINE__ );
																								goto _x0_cube_miss;
					}	}
/* x0 miss?	*/	if(		x ==	Ec
				||		x < Ec-Bc ){	off =1;			SvREFCNT_dec( *(	dst = psvA0 +a ) );			FM;	goto _next_x;			}

/* all args hit?	*/	if( a!=za )	x = ARG( ++a );	else return 1;	/* all args hit; none were cut from avArg */
				if(		x >	*Epsilon(	cube ) )	{	if( iC!= zC) break;
												else{ SvREFCNT_dec( *(	dst = psvA0 +a ) );off=1+za-a; NX;	goto _none_x;	}		}
				if(		x == *Epsilon(	cube ) )	{												Up;	goto _x0_intraloc1up;	}
				} while( 1 );	lb =iC+1;	/*
_x0_search:	*/						ub =zC +1;	iC=( lb+ub )>>1;
			}else		{/*cube iC empty; many miss.*/	SvREFCNT_dec( *(	dst = psvA0 +a ) );
_x0_cube_miss: 																						dBUG_6A( cube_err[5], __FUNCTION__, "", iC-1, CSZ,	__FILE__, __LINE__ );
_x0_cube_overrun: 		if(	iC!=zC )	{	a_=a;						
									do	{ if(a!=za)	x = ARG( ++a );				else{  off =1+za-a; NX;	goto _none_x;	}
																	SvREFCNT_dec( *(		psvA0 +a ) );
										} while(	x < *Epsilon( cube ) );	SvREFCNT_dec( *(	lim=	psvA0 +a ) );
/* collapse void	*/					if( off < lim-dst )	{							src=	dst+	off;
													do	{ *dst++ = *src++; } while(	src<	lim );
													}
/* all cube iC args miss	*/				  off=a-a_;	lb=iC+1;									FM;		goto _search;
/* remaining args miss	*/	}else		{ off=1+za-a;											FM;	NX;	goto _none_x;
			}			}			}
		} while( 1 );	/* search	*/

/*	######	######	######	######	######	######	######	######	######	######		*/
/*										BLOCK  3										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
/*	######		STILL IN CUBE 0:	FIRST MISMATCH HAS BEEN FOUND ( *dst )		######		*/
/*	######	ALL SUBSEQUENT [MIS]MATCHES MARK-OUT AN ARRAY SHIFT RANGE		######		*/
			do	{ while(	x >Ec ){
					if(		zc!=	ic ){	deICE( cube[	++ic ],	Qc, Ac, Bc );  	Ec += Ac+Bc; }else{	iC=0;		goto _cube_miss; }
					}
/* next miss?	*/	if(		x ==	Ec
				||		x <  Ec-Bc )	{								SvREFCNT_dec( *(	lim = psvA0 +a ) );
/* collapse void	*/					if( off < lim-dst )	{							src=	dst+	off;
													do	{ *dst++ = *src++; } while(	src<	lim );
													}
									++off;
									}
_C0_next_x:		if( a!=za )	x = ARG( ++a );	else /* return...	*	*	*	*	*	*	*	*/	{	NX;	goto _none_x;	}
				} while(	x < *Epsilon(	cube ) );

/*	######	######	######	######	######	######	######	######	######	######		*/
/*										BLOCK  4										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
/*	######			SPECIAL CASES HANDLED;	SEARCH AND SHIFT NORMALLY		######		*/
/*	Special cases to initialize the first shift range and *Epsilon of cube 0 were handled in blocks 1-3. 		*/

							lb =1;	ub =zC +1;	iC= ub >>1;
	do	{											svC=*( psvC0 +iC ); 		if(		svC 	== NULL	){	dBUG_5A( cube_err[1], __FUNCTION__, "", iC,		__FILE__, __LINE__ );	if( iC!=zC){ ++iC; continue; } else {	off+=1+za-a;	SvREFCNT_dec( *(	dst = psvA0 +a ) );	NX;	goto _none_x;	}	}
																			else if(	!SvOK( 	svC)	){	dBUG_6A( cube_err[2], __FUNCTION__, "", iC, &*svC,	__FILE__, __LINE__ );	if( iC!=zC){ ++iC; continue; } else {	off+=1+za-a;	SvREFCNT_dec( *(	dst = psvA0 +a ) );	NX;	goto _none_x;	}	}
																			else if(	!SvPOK( 	svC)	){	dBUG_6A( cube_err[3], __FUNCTION__, "", iC, &*svC,	__FILE__, __LINE__ );	if( iC!=zC){ ++iC; continue; } else {	off+=1+za-a;	SvREFCNT_dec( *(	dst = psvA0 +a ) );	NX;	goto _none_x;	}	}
									cube = SvPVbyte(	svC, CS );				if(		CS< 16		){	dBUG_6A( cube_err[4], __FUNCTION__, "", iC,  CS,	__FILE__, __LINE__ );	if( iC!=zC){ ++iC; continue; } else {	off+=1+za-a;	SvREFCNT_dec( *(	dst = psvA0 +a ) );	NX;	goto _none_x;	}	}
		if(				x <	*Epsilon(	cube ) ){ if( (	iC=( ( ub	= iC )+lb	)>>1 )==ub ){	/*
_x0_intraloc: 	*/						cubeZ= SvPVbyte( *( psvC0 +iC-1), CSZ );		if(		CSZ< 16		){	dBUG_6A( cube_err[4], __FUNCTION__, "", iC-1, CSZ,	__FILE__, __LINE__ );	if( iC!=zC){ ++iC; continue; } else {	off+=1+za-a;	SvREFCNT_dec( *(	dst = psvA0 +a ) );	NX;	goto _none_x;	}	}
																								goto _intra;		}
		}else if(			x == *Epsilon(	cube ) || (	iC=( ( lb	= iC )+ub	)>>1 )==lb ){	_intraloc1up:
																			_nINTRALOC1Up;
_intra:		ic=0;			zc=zcOf(	cube );
			if(				zc!=-1 ){	deICE0(				Qc, Ac, Bc );  	Ec = Ac+Bc+ *Epsilon( cubeZ );	
			   do	{ while(	x >Ec )	{
					if(		zc!=	ic ){	deICE( cube[	++ic ],	Qc, Ac, Bc );  	Ec += Ac+Bc;
					}else{																			dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Epsilon( cube),	__FILE__, __LINE__ );
																								goto _cube_overrun;
					}	}
/* miss?		*/	if(		x ==	Ec
				||		x <  Ec-Bc )				{					SvREFCNT_dec( *(	lim=	psvA0 +a ) );
/* collapse void */									if( off < lim-dst )	{				src=	dst+	off;
													do	{ *dst++ = *src++; } while(	src<	lim );
												} ++off;			}

_next_x:  		if( a!=za )	x = ARG( ++a );	else /* return...	*	*	*	*	*	*	*	*/	{	NX;	goto _none_x;	}
				if(		x >	*Epsilon(	cube ) ){	if( iC!= zC ){	BS;	break;}
											else{					SvREFCNT_dec( *(	lim=	psvA0 +a ) );
/* collapse void */									if( off < lim-dst )	{				src=	dst+	off;
													do	{ *dst++ = *src++; } while(	src<	lim );
												} off +=1+za-a;								NX;	goto _none_x;	}	}
				if(		x == *Epsilon(	cube ) )	{												UP;	goto _intraloc1up;	}
				} while( 1 );			lb =iC+1;
_search:								ub =zC +1;	iC=( lb+ub )>>1;
			}else		{ /* cube iC is empty.  all local args miss. */
_cube_miss:	 																						dBUG_6A( cube_err[5], __FUNCTION__, "", iC-1, CSZ,	__FILE__, __LINE__ );
_cube_overrun:				if(	iC!=zC )	{	a_ = a;
									do	{ if(a!=za)	x = ARG( ++a );				else 		{	NX;	goto _none_x;	}
																	SvREFCNT_dec( *(		psvA0 +a ) );
										} while(	x < *Epsilon( cube ) );	SvREFCNT_dec( *(	lim=	psvA0 +a ) );
/* collapse void	*/					if( off < lim-dst )	{							src=	dst+	off;
													do	{ *dst++ = *src++; } while(	src<	lim );
													}
/* all cube iC args miss		*/			off+=a-a_; lb=iC+1;												goto _search;
/* remaining args miss	*/	}else		{off+=1+za-a;												NX;	goto _none_x;

			}			}			}
		} while( 1 );	/* search	*/

/*	######	######	######	######	######	######	######	######	######	######		*/
/*										FINAL SHIFT										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
_none_x:
	src =dst +off;
	lim= psvA0 +za;
	while( src<=lim )	*dst++ = *src++;
			AvFILLp( avArg ) -=off;
	return (bool) (AvFILLp( avArg )!=-1);
	}
bool _excludes(		/* avArgs */	){ //	cut matches from avArgs.		return true if all hit.			Searches ICEPack;	iterates args. 		Best for large objects with few args.	
//	printf("\n_excludes(): ");
	ui08			Qc,
			*	cube,
			*	cubeZ,
			*	pq;
	STRLEN		CS, CSZ;

	long long int				za = AvFILLp(	avArg ),	a=0;							if( za==-1	){	dBUG3ps_NOARG;		CR;return 1;	}
	long long int	lb,		ub,	zC = AvFILLp(	avICE ),	iC;/*=0;*/					if( zC==-1 ){	dBUG3ps_NOCUBE;	CR;return 0;	}
	char			zcZ,			zc,					ic=0;

	ui64			Ac, Bc, Ec, x,
				off=0;	/* running shift offset								*/
	SV		**	src,		/* earliest "hit" argument in queue to be shifted			*/
			**	dst,		/* earliest "miss" argument in queue to be overwritten	*/
			**	lim,		/* latest "limit" argument pending hit/miss evaluation while the shift queue buffers and possibly flushes*/
			**	psvA0 =	AvARRAY( avArg ),
			**	psvC0 =	AvARRAY( avICE ),				*svC=*psvC0;				if(		svC 	== NULL	){	dBUG_5A( cube_err[1], __FUNCTION__, "", iC,		__FILE__, __LINE__ );	if( zC!=0) goto _x0_search; else{ CR;return 0;}	}
																			else if(	!SvOK( 	svC)	){	dBUG_6A( cube_err[2], __FUNCTION__, "", iC, &*svC,	__FILE__, __LINE__ );	if( zC!=0) goto _x0_search; else{ CR;return 0;}	}
																			else if(	!SvPOK( 	svC)	){	dBUG_6A( cube_err[3], __FUNCTION__, "", iC, &*svC,	__FILE__, __LINE__ );	if( zC!=0) goto _x0_search; else{ CR;return 0;}	}

/*	######	######	######	######	######	######	######	######	######	######		*/
/*										BLOCK  1										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
/*	######			FIND THE FIRST MATCH TO MARK-IN ARRAY SHIFT RANGE		######		*/
/*			The conditional statements commented "x0 hit?" mark-in each AV shift range.				*/
/*			It is to isolate these cases implicitly that the search loop code is differentiated 4x here—		*/
/*			that, and to handle all arguments located in cube (0) as special cases.						*/

						x = ARG( 0 );	cube = SvPVbyte(	svC, CS );				if(		CS< 16		){	dBUG_6A( cube_err[4], __FUNCTION__, "", iC,	CS,	__FILE__, __LINE__ );	if( zC!=0) goto _x0_search; else{CR;return 0;	}	}
	if(					x <  *Epsilon(	cube ) ){
							zc=zcOf(	cube );
					if(		zc!=-1 ){	deICE0(				Qc, Ac, Bc );  	Ec=	Ac +Bc;
/*cube 0 err	*/		}else{																			dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Epsilon( cube),	__FILE__, __LINE__ );
												iC=0;											goto _x0_cube_miss;
						}						ic=0;
			do	{ while( x >Ec )	{					
					if(		ic!=zc ){	deICE( cube[	++ic ],	Qc, Ac, Bc );  	Ec+=Ac +Bc;
/*cube 0 err	*/		}else{						iC=0;												dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Epsilon( cube),	__FILE__, __LINE__ );
																								goto _x0_cube_miss;
					}	}
/* x0 hit? 	*/	if(		x !=	Ec
				&&		x >= Ec-Bc ){	off =1;			SvREFCNT_dec( *( dst = psvA0 +a ) );				goto _C0_next_x;	}

				if( a!=za )	x = ARG( ++a );										else			{	CR;	return 0;	}
				} while(	x < *Epsilon(	cube ) );
			}

/*	######	######	######	######	######	######	######	######	######	######		*/
/*										BLOCK  2										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
/* 	######		1ST MATCH NOT FOUND IN CUBE 0;		SEARCHING CUBES >0		######		*/

_x0_search:		lb =1,	ub =zC +1,				iC= ub >>1;
	do	{											svC=*( psvC0 +iC ); 		if(		svC 	== NULL	){	dBUG_5A( cube_err[1], __FUNCTION__, "", iC,		__FILE__, __LINE__ );	if( iC!=zC){ ++iC; continue; } else{ CR;return 0;}	}
																			else if(	!SvOK( 	svC)	){	dBUG_6A( cube_err[2], __FUNCTION__, "", iC,&*svC,	__FILE__, __LINE__ );	if( iC!=zC){ ++iC; continue; } else{ CR;return 0;}	}
																			else if(	!SvPOK( 	svC)	){	dBUG_6A( cube_err[3], __FUNCTION__, "", iC,&*svC,	__FILE__, __LINE__ );	if( iC!=zC){ ++iC; continue; } else{ CR;return 0;}	}
									cube = SvPVbyte(	svC, CS );				if(		CS< 16		){	dBUG_6A( cube_err[4], __FUNCTION__, "", iC,	CS,	__FILE__, __LINE__ );	if( iC!=zC){ ++iC; continue; } else{ CR;return 0;}	}
		if(				x <	*Epsilon(	cube ) ){ if( (	iC=( ( ub	= iC )+lb	)>>1 )==ub ){	_INTRALOC;			goto _x0_intra;	}
		}else if(			x == *Epsilon(	cube ) || (	iC=( ( lb	= iC )+ub	)>>1 )==lb ){	_x0_intraloc1up:
																			_INTRALOC1Up( _x0_cube_miss );
_x0_intra:	ic=0;			zc=zcOf(	cube );
			if(				zc!=-1 ){	deICE0(				Qc, Ac, Bc );  	Ec = Ac+Bc+ *Epsilon( cubeZ );	
			   do	{ while(	x >Ec ){
					if(		zc!=	ic ){	deICE( cube[	++ic ],	Qc, Ac, Bc );  	Ec += Ac+Bc;	}else			{	dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Epsilon( cube),	__FILE__, __LINE__ );
																								goto _cube_miss;
					}																			}
/* x0 hit? 	*/	if(		x !=	Ec
				&&		x >= Ec-Bc ){	off =1;			SvREFCNT_dec( *( dst = psvA0 +a ) );				goto _next_x;	}

				if( a!=za )	x = ARG( ++a );										else			{	CR;	return 0;	}
				if(		x >	*Epsilon(	cube ) )	{	if( iC!= zC )			break;	else			{	CR;	return 0;	}	}
				if(		x == *Epsilon(	cube ) )	{													goto _x0_intraloc1up;		}
				} while( 1 );	lb =iC+1;	
_nth_search:							ub =zC +1;	iC=( lb+ub )>>1;
			}else		{ /* cube iC is empty.  all local args miss. */										 	dBUG_6A( cube_err[5], __FUNCTION__, "", iC-1, CSZ,	__FILE__, __LINE__ );
_x0_cube_miss:			if(	iC!=zC )	{
									do	{ if(a!=za)	x = ARG( ++a );				else 		{	NX;	goto _none_x;	}
										} while(	x < *Epsilon( cube ) );
/* all cube iC args miss		*/			lb=iC+1;	/* unlike in "v_includes()", we stay in this block 'til x0 hit. */	goto _nth_search;
/* remaining args miss	*/	}else		{														NX;	goto _none_x;
			}			}			}
		} while( 1 );	/* search	*/

/*	######	######	######	######	######	######	######	######	######	######		*/
/*										BLOCK  3										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
/*	######			STILL IN CUBE 0: FIRST MATCH HAS BEEN FOUND ( *dst )			######		*/
/*	######		ALL SUBSEQUENT MATCHES MARK-OUT AN ARRAY SHIFT RANGE		######		*/

			do	{ while(	x >Ec ){
					if(		zc!=	ic ){	deICE( cube[	++ic ],	Qc, Ac, Bc );  	Ec += Ac+Bc;
/*cube error		*/	}else{					/*	*	*	*	*	*	*	*	*	*	*/				dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Epsilon( cube),	__FILE__, __LINE__ );
/*not last cube	*/		if(	iC!=zC )	{ do	{ if(a!=za)	x = ARG( ++a );				else			{	NX;	goto _none_x;	}
										} while(	x < *Epsilon( cube ) );
/* all cube 0 args miss		*/	lb=iC+1;																goto _search;
/* all remaining args miss	*/			}	else /* return...	*	*	*	*	*	*	*	*/	{	NX;	goto _none_x;	}
					}	}

	/* hit?	*/	if(		x !=	Ec
				&&		x >= Ec-Bc )			{		SvREFCNT_dec( *( lim = psvA0 +a ) );	
	/* collapse void */	if(	lim-dst	>	off	)		{	src =dst +off;		do{ *dst++ = *src++; }			while( src< lim ); }
								++	off;		}

_C0_next_x:		if( a!=za )	x = ARG( ++a );										else			{	NX;	goto _none_x;	}
				} while(	x < *Epsilon(	cube ) );

/*	######	######	######	######	######	######	######	######	######	######		*/
/*										BLOCK  4										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
/*	printf("\n_excludes(): cube 0 handled; remaining cubes to be searched for arguments as normal.\n");		*/
							lb =1;	ub =zC +1;	iC= ub >>1;
	do	{											svC=*( psvC0 +iC ); 		if(		svC 	== NULL	){	dBUG_5A( cube_err[1], __FUNCTION__, "", iC,		__FILE__, __LINE__ );	if( iC!=zC){ ++iC; continue; } else {NX;	goto _none_x;	}	}
																			else if(	!SvOK( 	svC)	){	dBUG_6A( cube_err[2], __FUNCTION__, "", iC, &*svC,	__FILE__, __LINE__ );	if( iC!=zC){ ++iC; continue; } else {NX;	goto _none_x;	}	}
																			else if(	!SvPOK( 	svC)	){	dBUG_6A( cube_err[3], __FUNCTION__, "", iC, &*svC,	__FILE__, __LINE__ );	if( iC!=zC){ ++iC; continue; } else {NX;	goto _none_x;	}	}
									cube = SvPVbyte(	svC, CS );				if(		CS< 16		){	dBUG_6A( cube_err[4], __FUNCTION__, "", iC,  CS,	__FILE__, __LINE__ );	if( iC!=zC){ ++iC; continue; } else {NX;	goto _none_x;	}	}
		if(				x <	*Epsilon(	cube ) ){ if( (	iC=( ( ub	= iC )+lb	)>>1 )==ub ){	_INTRALOC;			goto _intra;	}
		}else if(			x == *Epsilon(	cube ) || (	iC=( ( lb	= iC )+ub	)>>1 )==lb ){	_intraloc1up:
																			_INTRALOC1Up( _cube_miss );
_intra:		ic=0;			zc=zcOf(	cube );
			if(				zc!=-1 ){	deICE0(				Qc, Ac, Bc );  	Ec = Ac+Bc+ *Epsilon( cubeZ );	
			   do	{ while(	x >Ec ){
					if(		zc!=	ic ){	deICE( cube[	++ic ],	Qc, Ac, Bc );  	Ec += Ac+Bc;	}else			{	dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Epsilon( cube),	__FILE__, __LINE__ );
																								goto _cube_miss;
					}																			}
	/* hit?	*/	if(		x !=	Ec
				&&		x >= Ec-Bc )			{		SvREFCNT_dec( *( lim = psvA0 +a ) );	
	/* collapse void */	if(	lim-dst	>	off	)		{	src =dst +off;		do{ *dst++ = *src++; }			while( src< lim ); }
								++	off;		}

_next_x:			if( a!=za )	x = ARG( ++a );										else			{	NX;	goto _none_x;	}
				if(		x >	*Epsilon(	cube ) )	{	if( iC!= zC )			break;	else			{	NX;	goto _none_x;	}	}
				if(		x == *Epsilon(	cube ) )	{						goto	_intraloc1up;							}
				}while(1);	lb =iC+1;	
_search:							ub =zC +1;		iC=( lb+ub )>>1;
			}else		{ /* cube iC is empty.  all local args miss. */										 	dBUG_6A( cube_err[5], __FUNCTION__, "", iC-1, CSZ,	__FILE__, __LINE__ );
_cube_miss:				if(	iC!=zC )	{
									do	{ if(a!=za)	x = ARG( ++a );				else 		{	NX;	goto _none_x;	}
										} while(	x < *Epsilon( cube ) );
/* all cube iC args miss		*/			lb=iC+1;														goto _search;
/* remaining args miss	*/	}else		{														NX;	goto _none_x;
			}			}			}
		} while( 1 );	/* search	*/

/*	######	######	######	######	######	######	######	######	######	######		*/
/*										FINAL SHIFT										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
_none_x:
	src =dst +off;
	lim= psvA0 +za;
	while( src<=lim )	*dst++ = *src++;
			AvFILLp( avArg ) -=off;
	return	AvFILLp( avArg ) ==-1? 1: 0;/* np. */
	}

ui64	_hits(			/* avArgs */ 	){ //	count matches in avArgs.		return number of hits.		Searches args;	iterates ICEPack. 	best for small objects with many args.	
	long long int	lb=0,	ub = AvFILLp(	avArg )+1;		if( ub==0	){	dBUG3ps_NOARG					return 0;	}
	long long int	a =		ub >>1,	iC = AvFILLp(	avICE );	if( iC==-1 ){	dBUG3ps_NOCUBE				return 0;	}
	long long int	Ub =	ub;

	SSize_t 		hit = 0;
	STRLEN		CS;
	SV		**	psviC0= AvARRAY(	avICE ),	**psviC,		*sviC;
	SV		**	psvA0= AvARRAY(	avArg ),				*svA=*( psvA0 +a );

	ui08		Qic,		*cube,	*pq, *pq16;
	ui64		Aic, Bic, Xic, Xa, Zic, Eic, x;
	char		ic;
	for(	;	iC!=-1; --iC ){					sviC=*( psviC0+iC );			if(	sviC 	== NULL	){ dBUG_5A( cube_err[1], __FUNCTION__, "", iC,			__FILE__, __LINE__ );		continue; }
																	if(	!SvOK( 	sviC	)	){ dBUG_6A( cube_err[2], __FUNCTION__, "", iC, &*sviC,	__FILE__, __LINE__ );		continue; }
																	if(	!SvPOK( 	sviC	)	){ dBUG_6A( cube_err[3], __FUNCTION__, "", iC, &*sviC,	__FILE__, __LINE__ );		continue; }
						cube=SvPVbyte(	sviC, CS );					if(	CS< 16			){ dBUG_6A( cube_err[4], __FUNCTION__, "", iC,  CS,		__FILE__, __LINE__ );		continue; }
		pq16	=16	+	cube;
		ic		= zcOf(  	cube );										if(	ic==-1			){ dBUG_6A( cube_err[5], __FUNCTION__, "", iC,  CS,		__FILE__, __LINE__ );		continue; }
		Eic	=*Epsilon(	cube );						pq=cube+CS;
		for(	; ic!=-1; --ic ){ _deICEr(	cube, CS,	cube[ ic ],		pq,	Qic, Aic, Bic );								/*	printf("hits: #%lld[%d]\n", iC, ic);					*/
				Zic =Eic -Bic;
			for(	Xic =Eic-1; Xic>=Zic; --Xic )	{	if( Xic&0x8000000000000000)	break;	//this routinely happens when ID#0 is set...
/* search	args */	while(	Xic !=SvIVX(	svA ) ){
					if(	Xic > SvIVX(	svA ) ){	lb =	a;	a=( lb+ub )>>1;	if(a==lb	){ ub=Ub;		goto _miss; }
					}else{					ub =	a;	a=( lb+ub )>>1;	if(a==ub	){ ub=Ub;		goto _miss; }
						}			svA = *(psvA0	+	a );
/* hit		*/		} ++	hit;											if( a==0 )				return hit;	// found last match 
				/* search window narrows */		ub=Ub=	a;
				/* next Xa in Xic..Eic?*/	svA = *( psvA0 +	a-1 );			if( Zic > SvIVX(	svA ) )	break;		// no more matches in this ic
_miss:			/* reset search	*/			lb=0;	a=( lb+ub )>>1;	svA =	*( psvA0 +	a );
				}													if(	pq< pq16			){ dBUG_5A( cube_err[6], __FUNCTION__,	iC,  CS,		__FILE__, __LINE__ );		goto _next_iC; }
			Eic =Zic -Aic;
			}								//						if(	Eic !=0			){  	printf("!	Eic!=0 (%lld)\n", Eic );		return hit; }
																	if(	pq !=pq16		){	printf("!	pq!=cube+16 (cube+%lld) function %s in %s line %lld\n", pq-cube, __FUNCTION__, __FILE__, __LINE__ );
																							return hit; }
_next_iC:	}
	return hit;
	}
bool	_fits(			/* avArgs */ 	){ //	count matches in avArgs.		return true if all hit.			Searches args;	iterates ICEPack. 	Best for small objects with many args.	
	printf("\n!	WARNING: _fits() needs work.  [2026-06-02: _hits() is now a suitable replacement]  \n\
				It currently cannot tolerate a read error.  Since it scans cycla in ascending order, computing epsilon as it goes, \n\
				if it cannot read a cube, it will not be able to continue computing epsilon.\n\
				It would be possible to recover from a cube error though, if it scanned cycla in descending order,\n\
				reinitializing epsilon upon entering each cube.\n\
				Fortunately, missing cubes do not introduce any ambiguity with the logical significance of the return value.\n\
				");
	#define	FIND_X_OR_MISS( $iC )	\
	while(	x !=SvIVX( svA ) ){	\
		if(	x > SvIVX( svA ) ){	lb=a;	a=( lb+ub )>>1; if(a==lb	){	lb=LB; ub=UB; a=( lb+ub )>>1;	svA =*( psvA0+a );	++miss; }	\
		}else{				ub=a;	a=( lb+ub )>>1; if(a==ub	){	lb=LB; ub=UB; a=( lb+ub )>>1;	svA =*( psvA0+a );	++miss; }	\
			}																			svA =*( psvA0+a );				\
/*hit*/	}											LB=a+1;	lb=LB; ub=UB; a=( lb+ub )>>1;	svA =*( psvA0+a );/*	goto ... ;	*/

	long long int	LB=0, 		UB = AvFILLp(	avArg )+1;								if( UB==0	){	dBUG3ps_NOARG					return 1;	}
	long long int	lb=LB,		ub=UB,
			iC,	zC = AvFILLp(	avICE ),					a =UB >>1;					if( zC==-1 ){	dBUG3ps_NOCUBE				return 0;	}

	SSize_t 		miss = 0;
	STRLEN		CS;
	SV		**	psvC0= AvARRAY(	avICE ),				*svC=*psvC0;				if(	svC==NULL){					dBUG3ps_svC(0);	return 0; }
	SV		**	psvA0= AvARRAY(	avArg ),				*svA=*psvA0;

	ui64			Ac, Bc, Ec, x;
	ui08		*	pq,		   *	cube = SvPVbyte(	svC,	CS),	Qc;

	char		ic,		zc =zcOf(	cube );			deICE0(			Qc, x,  Bc );			for(	Ec=x+Bc;  x< Ec;  ++x ){			FIND_X_OR_MISS( 0 );		}
	for(		ic=1; ic<=	zc;	++ic )	{			deICE( cube[ ic ],	Qc, Ac, Bc ); x=Ec+Ac;	for(	Ec=x+Bc;  x< Ec;  ++x ){			FIND_X_OR_MISS( 0 );		}
								} 												if(	Ec	!=*( (ui64*)	cube +1 )	){  	dBUG3ps_ic( iC );	return 0; }
																				if(	CS	!= pq 	-	cube	){	dBUG3ps_CS( iC );	return 0; }

	for(		iC=1;iC<=	zC;	++iC ){				svC=*( psvC0 +iC );						if( svC==NULL){					dBUG3ps_svC( iC );	return 0; }
							cube = SvPVbyte(	svC, CS );
					zc =zcOf(	cube );			deICE0(			Qc, Ac, Bc ); x=Ec+Ac;	for(	Ec=x+Bc;  x< Ec;  ++x ){			FIND_X_OR_MISS( iC );		}
		for(	ic=1; ic<=	zc;	++ic )	{			deICE( cube[ ic ],	Qc, Ac, Bc ); x=Ec+Ac;	for(	Ec=x+Bc;  x< Ec;  ++x ){			FIND_X_OR_MISS( iC );		}
								} 												if(	Ec	!=*( (ui64*)	cube +1 )	){  	dBUG3ps_ic( iC );	return 0; }
																				if(	CS	!= pq 	-	cube	){	dBUG3ps_CS( iC );	return 0; }
		}
	return miss==0? 1: 0;	/* np. */
	}
bool _strikes(	/* avArgs */	){ //	cut matches from avArgs.	return true if all hit.			Searches args;	iterates ICEPack. 	best for small objects with many args.	
	#define	PULL_X_OR_CONTINUE( $iC, $pSv )	\
	while(	x !=SvIVX( svA ) ){	\
		if(	x > SvIVX( svA ) ){	lb=a;	a=( lb+ub )>>1; if(a==lb	){	lb=LB; ub=UB; a=( lb+ub )>>1;	svA =*( psvA0+a );	continue; }	\
		}else{				ub=a;	a=( lb+ub )>>1; if(a==ub	){	lb=LB; ub=UB; a=( lb+ub )>>1;	svA =*( psvA0+a );	continue; }	\
			}																			svA =*( psvA0+a );				\
/*hit*/	} SvREFCNT_dec( svA );	$pSv=	psvA0+a; 		LB=a+1;	lb=LB; ub=UB; a=( lb+ub )>>1;	svA =*( psvA0+a );/*	goto ... ;	*/

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
			**	psvC0= AvARRAY( avICE ),		*	svC = *psvC0;   						if( svC==NULL){					dBUG3ps_svC(0);							return 0;		}
	SV		**	psvA0= AvARRAY( avArg ),		*	svA = *( psvA0 +a );
								cube = SvPVbyte(	svC, CS);
	char		ic,		zc = zcOf(	cube );		deICE0(			Qc, x, Bc );				for(	Ec=x+Bc;  x< Ec;  ++x ){			PULL_X_OR_CONTINUE( 0, dst );	hit=1;iC=0;	goto	_next_x;	}
		for(	ic=1; ic<=	zc;	++ic )	{			deICE( cube[ ic ],	Qc, Ac, Bc );  x=Ec+Ac;		for(	Ec=x+Bc;  x< Ec;  ++x ){			PULL_X_OR_CONTINUE( 0, dst );	hit=1;iC=0;	goto	_next_x;	}
								} 													if(	Ec	!=*( (ui64*)	cube +1 )	){  	dBUG3ps_ic( 0 );							return 0;		}
																					if(	CS	!= pq 	-	cube	){	dBUG3ps_CS( 0 );							return 0;		}

	for(		iC=1;iC<=	zC;	++iC ){					svC = *(psvC0 +iC );					if( svC==NULL){					dBUG3ps_svC( iC );							return 0;		}
								cube = SvPVbyte(	svC, CS );
			ic=0;	zc = zcOf(	cube );		deICE0(			Qc, Ac, Bc );  x=Ec+Ac;		for(	Ec=x+Bc;  x< Ec;  ++x ){			PULL_X_OR_CONTINUE( iC, dst );	hit=1;		goto	_next_x;	}
		for(	ic=1; ic<=	zc;	++ic )	{			deICE( cube[ ic ],	Qc, Ac, Bc );  x=Ec+Ac;		for(	Ec=x+Bc;  x< Ec;  ++x ){			PULL_X_OR_CONTINUE( iC, dst );	hit=1;		goto	_next_x;	}
								} 													if(	Ec	!=*( (ui64*)	cube +1 )	){  	dBUG3ps_ic( 0 );							return 0;		}
																					if(	CS	!= pq 	-	cube	){	dBUG3ps_CS( 0 );							return 0;		}
		}
	return 0;	/*	after iterating ICE object, a first matching argument was never found. */

	for(		;	iC<=	zC;	++iC ){					svC = *( psvC0 +iC );					if( svC==NULL){					dBUG3ps_svC( iC );							return 0;		}
								cube = SvPVbyte(	svC, CS );	pq=cube+16;
					zc = zcOf(	cube );				
		for(	ic=0; ic<=	zc;	++ic )	{			deICE(cube[ ic ],	Qc, Ac, Bc );  x = Ec+Ac;		for(	Ec=x+Bc;  x< Ec;  ++x )	{		PULL_X_OR_CONTINUE( iC, lim );

																					/* array shift to collapse void */		if(hit< lim-dst)	{	src =dst +hit;
																																	do	{ *dst++ = *src++;} while( src< lim );
																																}	++hit;							_next_x:	}
								}													if(	Ec	!=*( (ui64*)	cube +1 )	){  	dBUG3ps_ic( 0 );							return 0;		}
																					if(	CS	!= pq 	-	cube	){	dBUG3ps_CS( 0 );							return 0;		}
		}
_end:
	lim= psvA0 + AvFILLp(	avArg );
	src= psvA0 +lb;
	while( src<=lim )	*dst++=*src++;
			AvFILLp( avArg ) -=hit;
	return	AvFILLp( avArg ) ==-1? 1: 0;
	}
