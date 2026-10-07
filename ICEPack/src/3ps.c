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

bool _addsUp(){
	#if defined( DEBUG_TRUTH_L1 )
		#define dBUG3ps_NOPROB			cS = sprintf(aString, "\rok	%s in %s line %d: %s encountered no error.\n",									__FUNCTION__, __FILE__, __LINE__				);	AvDBUG_PUSH( aString, cS );
		#define dBUG3ps_NOARG			cS = sprintf(aString, 	"\r! 	%s in %s line %d: (AV*) avArg array is empty.\n",								__FUNCTION__, __FILE__, __LINE__				);	AvDBUG_PUSH( aString, cS );
		#define dBUG3ps_NOCUBE			cS = sprintf(aString, 	"\r! 	%s in %s line %d: (AV*) avICE array is empty.\n",								__FUNCTION__, __FILE__, __LINE__				);	AvDBUG_PUSH( aString, cS );
		#define dBUGzc(		$iC )			cS = sprintf(aString, 	"\r! 	%s in %s line %d: cube #%lld is empty.		\n",									__FUNCTION__, __FILE__, __LINE__, $iC				);	AvDBUG_PUSH( aString, cS );
		#define dBUG3ps_ic(	$iC )			cS = sprintf(aString,	"\r! 	%s in %s line %d: cube #%lld checksum error.	\n",								__FUNCTION__, __FILE__, __LINE__, $iC				);	AvDBUG_PUSH( aString, cS );
		#define dBUG3ps_CS(	$iC )			cS = sprintf(aString,	"\r! 	%s in %s line %d: cube #%lld STRLEN error.   	( computed: %llu 	stored: %llu  )\n",	__FUNCTION__, __FILE__, __LINE__, $iC, pq-cube, CS	);	AvDBUG_PUSH( aString, cS );
		#define dBUG3ps_svC(	$iC )			cS = sprintf(aString,	"\r! 	%s in %s line %d: cube #%lld SV* pointer is null.	\n",								__FUNCTION__, __FILE__, __LINE__, $iC				);	AvDBUG_PUSH( aString, cS );
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

	SV		**	ICEº = AvARRAY(	avICE ),				*svC=*ICEº;				if( svC==NULL){		dBUG3ps_svC(0LL);	return 0; }
	ui08							*	cube = SvPVbyte(	svC,	CS);
	char				ic,	zc = zcOf(	cube );	deICE0(			Ac, Bc, Qc );	Ec = Ac +Bc;
		for(	ic = 1;	ic<=	zc;	++ic )	{		deICE(cube[ ic ],	Ac, Bc, Qc );	Ec+=Ac +Bc;
									}		if(*( (ui64*)	cube +1 ) 				!=	Ec ){    		dBUG3ps_ic(	0LL);	return 0; }
											if(		pq -	cube!=	CS){								dBUG3ps_CS(	0LL);	return 0; }

	for(		iC=1;	iC<=	zC;	++iC ){							svC=*( ICEº +iC ); 	if( svC==NULL){	dBUG3ps_svC( iC );	return 0; }
									cube = SvPVbyte(	svC, CS );
						zc = zcOf(	cube );	deICE0(			Ac, Bc, Qc );	Ec+=Ac +Bc;
		for(	ic = 1;	ic<=	zc;	++ic )	{		deICE(cube[ ic ],	Ac, Bc, Qc );	Ec+=Ac +Bc;
									}		if(*( (ui64*)	cube +1 ) 				!=	Ec ){    		dBUG3ps_ic( iC );	return 0; }
											if(		pq -	cube!=	CS){								dBUG3ps_CS( iC );	return 0; }
		}
//	dBUG3ps_NOPROB
	return 1; // no prob.
	}
ui64 _has(	/* avArgs */ 	){ //	count matches in avArgs.	return number of hits.		Searches ICEPack;	iterates args. 		Best for large objects with few args.
	#define icOK(		$iC )	if( zc==ic ){dBUG3ps_ic( iC)	if( a == za )				return off;	 	x = ARG( ++a );	continue;		}
	#define zcOK(		$iC )	if( zc==-1 ){	do{			if( a == za ){	dBUGzc( iC)	return off;	}	x = ARG( ++a ); }	while( x < *( (ui64*) cube +1) );	\
				iC =	$iC;										dBUGzc( iC)	goto _search;	}

	#define	CoINTRaLOCj		while( x >Ec ){		icOK(	iC );	deICE(cube[++ic],	Ac, Bc, Qc );  	Ec+=	Ac+Bc;	}


	#define	INTRaLOCj						zc = zcOf(	cube );	ic=0;						\
		cubeΩ= SvPVbyte_nolen( *( ICEº +iC-1) );	zcOK(	iC );	deICE0(			Ac, Bc, Qc );  	Ec = Ac +Bc+	*( (ui64*)	cubeΩ+1 );	\
							while( x >Ec ){		icOK(	iC );	deICE(cube[++ic],	Ac, Bc, Qc );  	Ec+= Ac+Bc;	}


	#define	INTRaLOCj1Up	if( zC  ==	iC )									return off;	Ec =			*( (ui64*) cube +1	);	\
		cube = SvPVbyte_nolen( *(++	iC +ICEº ) );	zc = zcOf(	cube );	ic=0;				\
											zcOK(	iC );	deICE0(			Ac, Bc, Qc );  	Ec += Ac+Bc;  						\
							while( x >Ec ){		icOK(	iC );	deICE(cube[++ic],	Ac, Bc, Qc );  	Ec += Ac+Bc;	}

	ui64			Ac, Bc, Ec, x;
	ui08			Qc,
			*	cube,
			*	cubeΩ,
			*	pq;
	ui64			off=0;
	STRLEN		CS;
	SV		**	ICEº =	AvARRAY( avICE ), 	*svC,
			**	ARGº=	AvARRAY( avArg ),		*svA;

	long long int				za = AvFILLp(	avArg ),	a=0;				if( za==-1	){	dBUG3ps_NOARG			return 0;	}
	long long int		hi,	lo,	zC = AvFILLp(	avICE ),	iC;				if( zC==-1 ){	dBUG3ps_NOCUBE		return 0;	}
	char						zc,					ic=0;

/* handle all arguments located in cube (0) as special cases */
								cube = SvPVbyte_nolen(	*ICEº );			x = ARG( 0 );
	if(				x <  *Edge(	cube  ) )	{	zc = zcOf(	cube );
							zcOK( 0 );		deICE0(			Ac, Bc, Qc );  	Ec=	Ac +Bc;
	   do	{	while(	x >	Ec ){	icOK( 0 );			deICE( cube[++ic],	Ac, Bc, Qc );  	Ec+=Ac +Bc;	}
	/* hit? */	if(		x !=	Ec	
			&&		x >=	Ec-Bc ){	++off; }	if(	a != za )						x = ARG( ++a );	else	return	off;
		} while(		x < *Edge(	cube ) );	}
													/*init search	*/		lo =1; hi =zC+1;	iC= hi >>1;

	do	{						cube = SvPVbyte_nolen(	svC =*( ICEº+iC ) );
		if(			x <	*Edge(	cube ) ){	if( (	iC=( ( hi =	iC )+lo	)>>1 )==hi ){	INTRaLOCj;			goto	_intra_op; }
		}else if(		x == *Edge(	cube )||(		iC=( ( lo =	iC )+hi	)>>1 )==lo ){	INTRaLOCj1Up;				_intra_op:
		   do	{
	/* hit? */	if(		x !=	Ec
			&&		x >= Ec-Bc ){	++off; }	if(	a != za )						x = ARG( ++a );		else	return	off;
			if(		x >	*Edge(	cube ) )	{ if(	iC!= zC ){	/*next search	*/		lo =iC+1;	hi =zC+1;	iC=( lo+hi )>>1;	}			else	return	off;	}
			if(		x == *Edge(	cube ) )	{								INTRaLOCj1Up;	}
			else							{								CoINTRaLOCj;		}
			} while( 1 );				/*seek loop	*/													_search:
					lo =iC+1;	hi =zC+1;	/*next search	*/	iC=( lo+hi )>>1;
		}	} while( 1 );				/*search	loop	*/
	_none_x:
	return off;	/* np. */
	}

#define	_INTRaLOC					/* Initialize Ec with *Edge of the cube before the current cube.		*/\
									cubeΩ= SvPVbyte( *( ICEº +iC-1), CSΩ );	if(	CSΩ< 16		){	dBUG_5A( cube_err[4], __FUNCTION__, iC-1, CSΩ,	__FILE__, __LINE__ );if( iC!=zC){ lo=++iC; continue; } else {	off=1+za-a;								NX;	goto _none_x;	}	}
#define	_nINTRaLOC					/* Initialize Ec with *Edge of the cube before the current cube.		*/\
									cubeΩ= SvPVbyte( *( ICEº +iC-1), CSΩ );	if(	CSΩ< 16		){	dBUG_5A( cube_err[4], __FUNCTION__, iC-1, CSΩ,	__FILE__, __LINE__ );if( iC!=zC){ lo=++iC; continue; } else {	off=1+za-a; SvREFCNT_dec( *( dst = ARGº +a ) ); NX;	goto _none_x;	}	}

#define	_INTRaLOC1Up(	$CUBE_MISS )/* Initialize Ec with *Edge of current cube, then move one cube up.	*/\
						if(	iC!=zC ){	cubeΩ=cube;								\
									cube = SvPVbyte( *(++iC +ICEº ), CS );		if(	CS< 16		){	dBUG_5A( cube_err[4], __FUNCTION__, iC,	CS,	__FILE__, __LINE__ );	\
																								goto $CUBE_MISS;	}	\
						}else		{											NX;	goto _none_x;	}

#define	_xa_nINTRaLOC1Up			/* Initialize Ec with *Edge of current cube, then move one cube up.	*/\
						if(	iC!=zC ){	cubeΩ=cube;								\
									cube = SvPVbyte( *(++iC +ICEº ), CS );		if(	CS< 16		){	dBUG_5A( cube_err[4], __FUNCTION__, iC,	CS,	__FILE__, __LINE__ );	\
																								goto _cube_miss;	}	\
						}else		{					SvREFCNT_dec( *(	lim=	ARGº +a ) );			\
		/* collapse void */				if(	off < lim-dst )	{				src=	dst+	off;					\
										do	{ *dst++ = *src++; } while(	src<	lim );					\
										}off +=1+za-a;								NX;	goto _none_x;	\
									}

#define _x0_nINTRaLOC1Up				/* Initialize Ec with *Edge of current cube, then move one cube up.	*/\
						if(	iC!=zC ){	cubeΩ=cube;								\
									cube = SvPVbyte( *(++iC +ICEº ), CS );		if(	CS< 16		){	dBUG_5A( cube_err[4], __FUNCTION__, iC,	CS,	__FILE__, __LINE__ );	\
																								goto _x0_cube_miss;	}	\
						}else		{ off =1+za-a;	SvREFCNT_dec( *(	dst = ARGº +a ) );	NX;	goto _none_x;	}

#define _nINTRaLOC1Up(	$CUBE_MISS	)/* Initialize Ec with *Edge of current cube, then move one cube up.	*/\
						if(	iC!=zC ){	cubeΩ=cube;								\
									cube = SvPVbyte( *(++iC +ICEº ), CS );		if(	CS< 16		){	dBUG_5A( cube_err[4], __FUNCTION__, iC,	CS,	__FILE__, __LINE__ );	\
																								goto $CUBE_MISS;	}	\
						}else		{ off +=1+za-a;								NX;	goto _none_x;	}


//bool _retains?

//	#define CR printf("	returns at line %d (AvFILLp( avArg ) ==%lld)\n", __LINE__, AvFILLp( avArg ) );
//	#define NX printf("	goto _none_x at line %d\n", __LINE__ );
//	#define FM printf("	first miss at line %d\n", __LINE__ );
//	#define BS printf("	break dwell loop at line %d\n",	__LINE__ );
//	#define UP printf("	goto _intraloc1up at line %d\n", 	__LINE__ );
//	#define Up printf("	goto _x0_intraloc1up at line %d\n", 	__LINE__ );

	#define CR
	#define NX
	#define FM
	#define BS
	#define UP
	#define Up

//	"xMatchingOf"
//	"includes"
bool _includes(			/* avArgs */	){ //	cut non-matches from avArgs.	return true if any match.	Searches ICEPack;	iterates args. 		Best for large objects with few args.	
/*	!!		there's a memory leak that really hits when unset() is trying to kill the last 0.1%		*/
	ui08			Qc,
			*	cube,
			*	cubeΩ,
			*	pq;
	STRLEN		CS, CSΩ;

	long long int				za = AvFILLp(	avArg ),	a=0, a_;						if( za==-1	){	dBUG3ps_NOARG;		{CR;					return 0;	}	}
	long long int	lo,		hi,	zC = AvFILLp(	avICE ),	iC;/*=0;*/					if( zC==-1 ){	dBUG3ps_NOCUBE;	{CR; av_clear( avArg );	return 0;	}	}
	char			zcΩ,			zc,					ic=0;

	ui64			Ac, Bc, Ec, x,
				off=0;	/* running shift offset								*/
	SV		**	src,		/* earliest "hit" argument in queue to be shifted			*/
			**	dst,		/* earliest "miss" argument in queue to be overwritten	*/
			**	lim,		/* latest "limit" argument pending hit/miss evaluation while the shift queue buffers and possibly flushes*/
			**	ARGº =	AvARRAY( avArg ),
			**	ICEº =	AvARRAY( avICE ),				*svC=*ICEº;				if(		svC 	== NULL	){	dBUG_5A( cube_err[1], __FUNCTION__, "", iC,		__FILE__, __LINE__ );	if( zC) goto _x0_search;	else{CR; av_clear( avArg ); return 0;	}	}
																			else if(	!SvOK( 	svC)	){	dBUG_6A( cube_err[2], __FUNCTION__, "", iC, &*svC,	__FILE__, __LINE__ );	if( zC) goto _x0_search;	else{CR; av_clear( avArg ); return 0;	}	}
																			else if(	!SvPOK( 	svC)	){	dBUG_6A( cube_err[3], __FUNCTION__, "", iC, &*svC,	__FILE__, __LINE__ );	if( zC) goto _x0_search;	else{CR; av_clear( avArg ); return 0;	}	}
/*	######	######	######	######	######	######	######	######	######	######		*/
/*										BLOCK  1										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
/*					FIND THE FIRST MATCH TO MARK-IN ARRAY SHIFT RANGE					*/
/*			The conditional statements commented "x0 miss?" mark-in each AV shift range.			*/
/*			It is to isolate these cases implicitly that the search loop code is differentiated 4x here—		*/
/*			that, and to initialize *Edge of cube 0 specially, so to eliminate a branch.					*/

						x = ARG( 0 );	cube = SvPVbyte(	svC, CS );		if(		CS< 16		){	dBUG_5A( cube_err[4], __FUNCTION__, iC,	CS,	__FILE__, __LINE__ );	if( zC) goto _x0_search;	else{CR; av_clear( avArg ); return 0;	}	}
	if(					x <  *Edge(	cube ) ){
							zc=zcOf(	cube );
					if(		zc!=-1 ){	deICE0(				Ac, Bc, Qc );  	Ec=	Ac +Bc;
/*cube 0 err	*/		}else{																			dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Edge( cube),	__FILE__, __LINE__ );
												iC=0;											goto _x0_cube_miss;
						}						ic=0;
			do	{ while( x >Ec )	{
					if(		ic!=zc ){	deICE( cube[	++ic ],	Ac, Bc, Qc );  	Ec+=Ac +Bc;
/*cube 0 err	*/		}else{						iC=0;												dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Edge( cube),	__FILE__, __LINE__ );
																								goto _x0_cube_miss;
					}	}
/* x0 miss?	*/	if(		x ==	Ec
				||		x < Ec-Bc ){	off =1;			SvREFCNT_dec( *( dst = ARGº +a ) );			FM;	goto _C0_next_x;	}

				if( a!=za )	x = ARG( ++a );										else					{CR;return 1;}
				} while(	x < *Edge(	cube ) );
			}
/*	######	######	######	######	######	######	######	######	######	######		*/
/*										BLOCK  2										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
/* 	######		1ST MATCH NOT FOUND IN CUBE 0;		SEARCHING CUBES >0		######		*/

_x0_search:					lo =1;	hi =zC +1;	iC= hi >>1;
	do	{											svC=*( ICEº +iC ); 			if(		svC 	== NULL	){	dBUG_4A( cube_err[1], __FUNCTION__,			iC,			__FILE__, __LINE__ ); if( iC!=zC){ lo=++iC; continue; } else {	off=1+za-a;	SvREFCNT_dec( *( dst = ARGº +a ) );	NX;	goto _none_x;	}	}
																			else if(	!SvOK( 	svC)	){	dBUG_6A( cube_err[2], __FUNCTION__, "svC",	iC,&*svC,	__FILE__, __LINE__ ); if( iC!=zC){ lo=++iC; continue; } else {	off=1+za-a;	SvREFCNT_dec( *( dst = ARGº +a ) );	NX;	goto _none_x;	}	}
																			else if(	!SvPOK( 	svC)	){	dBUG_6A( cube_err[3], __FUNCTION__, "svC",	iC,&*svC,	__FILE__, __LINE__ ); if( iC!=zC){ lo=++iC; continue; } else {	off=1+za-a;	SvREFCNT_dec( *( dst = ARGº +a ) );	NX;	goto _none_x;	}	}
									cube = SvPVbyte(	svC, CS );				if(		CS< 16		){	dBUG_5A( cube_err[4], __FUNCTION__,			 iC,	CS,		__FILE__, __LINE__ ); if( iC!=zC){ lo=++iC; continue; } else {	off=1+za-a;	SvREFCNT_dec( *( dst = ARGº +a ) );	NX;	goto _none_x;	}	}
		/* Now that we have verified cube iC, we are clear to read *Edge( cube ).		*/
		if(				x <	*Edge(	cube ) ){ if( (	iC=( ( hi	= iC )+lo	)>>1 )==hi ){	/*
_x0_intraloc: 	*/						cubeΩ= SvPVbyte( *( ICEº +iC-1), CSΩ );if(		CSΩ< 16		){	dBUG_5A( cube_err[4], __FUNCTION__, 		iC-1, CSΩ,	__FILE__, __LINE__ ); if( iC!=zC){ lo=++iC; continue; } else {	off=1+za-a;	SvREFCNT_dec( *( dst = ARGº +a ) );	NX;	goto _none_x;	}	}
																								goto _x0_intra;	}
		}else if(			x == *Edge(	cube ) || (	iC=( ( lo	= iC )+hi	)>>1 )==lo ){	_x0_intraloc1up:
																			_x0_nINTRaLOC1Up;
_x0_intra:	ic=0;  			zc=zcOf(	cube );
			if(				zc!=-1 ){	deICE0(				Ac, Bc, Qc );  	Ec = Ac+Bc+ *Edge( cubeΩ );
			   do	{ while(	x >Ec ){
					if(		zc!=ic ){	deICE( cube[	++ic ],	Ac, Bc, Qc );  	Ec += Ac+Bc;
/*cube iC err	*/		}else{							SvREFCNT_dec( *(	dst = ARGº +a ) );					dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Edge( cube),	__FILE__, __LINE__ );
																								goto _x0_cube_miss;
					}	}
/* x0 miss?	*/	if(		x ==	Ec
				||		x < Ec-Bc ){	off =1;			SvREFCNT_dec( *(	dst = ARGº +a ) );			FM;	goto _next_x;			}

/* all args hit?	*/	if( a!=za )	x = ARG( ++a );	else return 1;	/* all args hit; none were cut from avArg */
				if(		x >	*Edge(	cube ) )	{	if( iC!= zC) break;
												else{ SvREFCNT_dec( *(	dst = ARGº +a ) );off=1+za-a; NX;	goto _none_x;	}		}
				if(		x == *Edge(	cube ) )	{												Up;	goto _x0_intraloc1up;	}
				} while( 1 );	lo =iC+1;	/*
_x0_search:	*/						hi =zC +1;	iC=( lo+hi )>>1;
			}else		{/*cube iC empty; many miss.*/	SvREFCNT_dec( *(	dst = ARGº +a ) );
_x0_cube_miss: 																						dBUG_6A( cube_err[5], __FUNCTION__, "", iC-1, CSΩ,	__FILE__, __LINE__ );
_x0_cube_overrun: 		if(	iC!=zC )	{	a_=a;						
									do	{ if(a!=za)	x = ARG( ++a );				else{  off =1+za-a; NX;	goto _none_x;	}
																	SvREFCNT_dec( *(		ARGº +a ) );
										} while(	x < *Edge( cube ) ); 	SvREFCNT_dec( *(	lim=	ARGº +a ) );
/* collapse void	*/					if( off < lim-dst )	{							src=	dst+	off;
													do	{ *dst++ = *src++; } while(	src<	lim );
													}
/* all cube iC args miss	*/				  off=a-a_;	lo=iC+1;									FM;		goto _search;
/* remaining args miss	*/	}else		{ off=1+za-a;											FM;	NX;	goto _none_x;
			}			}			}
		} while( 1 );	/* search	*/

/*	######	######	######	######	######	######	######	######	######	######		*/
/*										BLOCK  3										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
/*	######		STILL IN CUBE 0:	FIRST MISMATCH HAS BEEN FOUND ( *dst )		######		*/
/*	######	ALL SUBSEQUENT [MIS]MATCHES MARK-OUT AN ARRAY SHIFT RANGE		######		*/
			do	{ while(	x >Ec ){
					if(		zc!=	ic ){	deICE( cube[	++ic ],	Ac, Bc, Qc );  	Ec += Ac+Bc; }else{	iC=0;		goto _cube_miss; }
					}
/* next miss?	*/	if(		x ==	Ec
				||		x <  Ec-Bc )	{								SvREFCNT_dec( *(	lim = ARGº +a ) );
/* collapse void	*/					if( off < lim-dst )	{							src=	dst+	off;
													do	{ *dst++ = *src++; } while(	src<	lim );
													}
									++off;
									}
_C0_next_x:		if( a!=za )	x = ARG( ++a );	else /* return...	*	*	*	*	*	*	*	*/	{	NX;	goto _none_x;	}
				} while(	x < *Edge(	cube ) );

/*	######	######	######	######	######	######	######	######	######	######		*/
/*										BLOCK  4										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
/*	######			SPECIAL CASES HANDLED;	SEARCH AND SHIFT NORMALLY		######		*/
/*	Special cases to initialize the first shift range and *Edge of cube 0 were handled in blocks 1-3. 		*/

							lo =1;	hi =zC +1;	iC= hi >>1;
	do	{											svC=*( ICEº +iC );	 		if(		svC 	== NULL	){	dBUG_4A( cube_err[1], __FUNCTION__,			iC,			__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else {	off+=1+za-a;	SvREFCNT_dec( *(	dst = ARGº +a ) );	NX;	goto _none_x;	}	}
																			else if(	!SvOK( 	svC)	){	dBUG_6A( cube_err[2], __FUNCTION__, "svC",	iC, &*svC,	__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else {	off+=1+za-a;	SvREFCNT_dec( *(	dst = ARGº +a ) );	NX;	goto _none_x;	}	}
																			else if(	!SvPOK( 	svC)	){	dBUG_6A( cube_err[3], __FUNCTION__, "svC",	iC, &*svC,	__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else {	off+=1+za-a;	SvREFCNT_dec( *(	dst = ARGº +a ) );	NX;	goto _none_x;	}	}
									cube = SvPVbyte(	svC, CS );				if(		CS< 16		){	dBUG_5A( cube_err[4], __FUNCTION__,			iC,  CS,		__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else {	off+=1+za-a;	SvREFCNT_dec( *(	dst = ARGº +a ) );	NX;	goto _none_x;	}	}
		if(				x <	*Edge(	cube ) ){ if( (	iC=( ( hi	= iC )+lo	)>>1 )==hi ){	/*
_x0_intraloc: 	*/						cubeΩ= SvPVbyte( *( ICEº +iC-1), CSΩ ); 		if(		CSΩ< 16		){	dBUG_5A( cube_err[4], __FUNCTION__,			iC-1, CSΩ,	__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else {	off+=1+za-a;	SvREFCNT_dec( *(	dst = ARGº +a ) );	NX;	goto _none_x;	}	}
																								goto _intra;		}
		}else if(			x == *Edge(	cube ) || (	iC=( ( lo	= iC )+hi	)>>1 )==lo ){	_intraloc1up:
																			_xa_nINTRaLOC1Up;
_intra:		ic=0;			zc=zcOf(	cube );
			if(				zc!=-1 ){	deICE0(				Ac, Bc, Qc );  	Ec = Ac+Bc+ *Edge( cubeΩ );	
			   do	{ while(	x >Ec )	{
					if(		zc!=	ic ){	deICE( cube[	++ic ],	Ac, Bc, Qc );  	Ec += Ac+Bc;
					}else{																			dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Edge( cube),	__FILE__, __LINE__ );
																								goto _cube_overrun;
					}	}
/* miss?		*/	if(		x ==	Ec
				||		x <  Ec-Bc )				{					SvREFCNT_dec( *(	lim=	ARGº +a ) );
/* collapse void */									if( off < lim-dst )	{				src=	dst+	off;
													do	{ *dst++ = *src++; } while(	src<	lim );
												} ++off;			}

_next_x:  		if( a!=za )	x = ARG( ++a );	else /* return...	*	*	*	*	*	*	*	*/	{	NX;	goto _none_x;	}
				if(		x >	*Edge(	cube ) ){	if( iC!= zC ){	BS;	break;}
											else{					SvREFCNT_dec( *(	lim=	ARGº +a ) );
/* collapse void */									if( off < lim-dst )	{				src=	dst+	off;
													do	{ *dst++ = *src++; } while(	src<	lim );
												} off +=1+za-a;								NX;	goto _none_x;	}	}
				if(		x == *Edge(	cube ) )	{												UP;	goto _intraloc1up;	}
				} while( 1 );			lo =iC+1;
_search:								hi =zC +1;	iC=( lo+hi )>>1;
			}else		{ /* cube iC is empty.  all local args miss. */
_cube_miss:	 																						dBUG_6A( cube_err[5], __FUNCTION__, "", iC-1, CSΩ,	__FILE__, __LINE__ );
_cube_overrun:				if(	iC!=zC )	{	a_ = a;
									do	{ if(a!=za)	x = ARG( ++a );				else 		{	NX;	goto _none_x;	}
																	SvREFCNT_dec( *(		ARGº +a ) );
										} while(	x < *Edge( cube ) ); 	SvREFCNT_dec( *(	lim=	ARGº +a ) );
/* collapse void	*/					if( off < lim-dst )	{							src=	dst+	off;
													do	{ *dst++ = *src++; } while(	src<	lim );
													}
/* all cube iC args miss		*/			off+=a-a_; lo=iC+1;												goto _search;
/* remaining args miss	*/	}else		{off+=1+za-a;												NX;	goto _none_x;

			}			}			}
		} while( 1 );	/* search	*/

/*	######	######	######	######	######	######	######	######	######	######		*/
/*										FINAL SHIFT										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
_none_x:
	src =dst +off;
	lim= ARGº +za;
	while( src<=lim )	*dst++ = *src++;
			AvFILLp( avArg ) -=off;
	return (bool) (AvFILLp( avArg )!=-1);
	}
bool _excludes(		/* avArgs */	){ //	cut matches from avArgs.		return true if all hit.			Searches ICEPack;	iterates args. 		Best for large objects with few args.	
//	printf("\n_excludes(): ");
	ui08			Qc,
			*	cube,
			*	cubeΩ = nube,
			*	pq;
	STRLEN		CS, CSΩ;

	long long int				za = AvFILLp(	avArg ),	a=0;							if( za==-1	){	dBUG3ps_NOARG;		CR;return 1;	}
	long long int	lo,		hi,	zC = AvFILLp(	avICE ),	iC;/*=0;*/					if( zC==-1 ){	dBUG3ps_NOCUBE;	CR;return 0;	}
	char			zcΩ,			zc,					ic=0;

	ui64			Ac, Bc, Ec, x,
				off=0;	/* running shift offset								*/
	SV		**	src,		/* earliest "hit" argument in queue to be shifted			*/
			**	dst,		/* earliest "miss" argument in queue to be overwritten	*/
			**	lim,		/* latest "limit" argument pending hit/miss evaluation while the shift queue buffers and possibly flushes*/
			**	ARGº =	AvARRAY( avArg ),
			**	ICEº =	AvARRAY( avICE ),				*svC=*ICEº;				if(		svC 	== NULL	){	dBUG_4A( cube_err[1], __FUNCTION__,			iC,			__FILE__, __LINE__ );	if( zC!=0) goto _x0_search; else{ CR;return 0;}	}
																			else if(	!SvOK( 	svC)	){	dBUG_6A( cube_err[2], __FUNCTION__, "svC",	iC, &*svC,	__FILE__, __LINE__ );	if( zC!=0) goto _x0_search; else{ CR;return 0;}	}
																			else if(	!SvPOK( 	svC)	){	dBUG_6A( cube_err[3], __FUNCTION__, "svC",	iC, &*svC,	__FILE__, __LINE__ );	if( zC!=0) goto _x0_search; else{ CR;return 0;}	}

/*	######	######	######	######	######	######	######	######	######	######		*/
/*										BLOCK  1										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
/*	######			FIND THE FIRST MATCH TO MARK-IN ARRAY SHIFT RANGE		######		*/
/*			The conditional statements commented "x0 hit?" mark-in each AV shift range.				*/
/*			It is to isolate these cases implicitly that the search loop code is differentiated 4x here—		*/
/*			that, and to handle all arguments located in cube (0) as special cases.						*/

						x = ARG( 0 );	cube = SvPVbyte( svC, CS );			if(		CS< 16		){	dBUG_5A( cube_err[4], __FUNCTION__,			iC,		CS,	__FILE__, __LINE__ );	if( zC!=0) goto _x0_search; else{CR;return 0;	}	}
	if(					x <  *Edge(	cube ) ){
							zc=zcOf(	cube );
					if(		zc!=-1 ){	deICE0(				Ac, Bc, Qc );  	Ec=	Ac +Bc;
/*cube 0 err	*/		}else{																			dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Edge( cube),	__FILE__, __LINE__ );
												iC=0;											goto _x0_cube_miss;
						}						ic=0;
			do	{ while( x >Ec )	{					
					if(		ic!=zc ){	deICE( cube[	++ic ],	Ac, Bc, Qc );  	Ec+=Ac +Bc;
/*cube 0 err	*/		}else{						iC=0;												dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Edge( cube),	__FILE__, __LINE__ );
																								goto _x0_cube_miss;
					}	}
/* x0 hit? 	*/	if(		x !=	Ec
				&&		x >= Ec-Bc ){	off =1;			SvREFCNT_dec( *( dst = ARGº +a ) );				goto _C0_next_x;	}

				if( a!=za )	x = ARG( ++a );										else			{	CR;	return 0;	}
				} while(	x < *Edge(	cube ) );
			}

/*	######	######	######	######	######	######	######	######	######	######		*/
/*										BLOCK  2										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
/* 	######		1ST MATCH NOT FOUND IN CUBE 0;		SEARCHING CUBES >0		######		*/

_x0_search:		lo =1,	hi =zC +1,				iC= hi >>1;
	do	{													svC=*( ICEº +iC );	if(		svC 	== NULL	){	dBUG_4A( cube_err[1], __FUNCTION__,			iC,			__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else{ CR;return 0;}	}
																			else if(	!SvOK( 	svC)	){	dBUG_6A( cube_err[2], __FUNCTION__, "svC",	iC,&*svC,	__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else{ CR;return 0;}	}
																			else if(	!SvPOK( 	svC)	){	dBUG_6A( cube_err[3], __FUNCTION__, "svC",	iC,&*svC,	__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else{ CR;return 0;}	}
									cube = SvPVbyte(	svC, CS );		if(		CS< 16		){	dBUG_5A( cube_err[4], __FUNCTION__,			iC,		CS,	__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else{ CR;return 0;}	}
		if(				x <	*Edge(	cube ) ){ if( (	iC=( ( hi	= iC )+lo	)>>1 )==hi ){	_INTRaLOC;			goto _x0_intra;	}
		}else if(			x == *Edge(	cube ) || (	iC=( ( lo	= iC )+hi	)>>1 )==lo ){	_x0_intraloc1up:
																			_INTRaLOC1Up( _x0_cube_miss );
_x0_intra:	ic=0;			zc=zcOf(	cube );
			if(				zc!=-1 ){	deICE0(				Ac, Bc, Qc );  	Ec = Ac+Bc+ *Edge( cubeΩ );	
			   do	{ while(	x >Ec ){
					if(		zc!=	ic ){	deICE( cube[	++ic ],	Ac, Bc, Qc );  	Ec += Ac+Bc;	}else			{	dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Edge( cube),	__FILE__, __LINE__ );
																								goto _cube_miss;
					}																			}
/* x0 hit? 	*/	if(		x !=	Ec
				&&		x >= Ec-Bc ){	off =1;			SvREFCNT_dec( *( dst = ARGº +a ) );				goto _next_x;	}

				if( a!=za )	x = ARG( ++a );										else			{	CR;	return 0;	}
				if(		x >	*Edge(	cube ) )	{	if( iC!= zC )			break;	else			{	CR;	return 0;	}	}
				if(		x == *Edge(	cube ) )	{													goto _x0_intraloc1up;		}
				} while( 1 );	lo =iC+1;	
_nth_search:							hi =zC +1;	iC=( lo+hi )>>1;
			}else		{ /* cube iC is empty.  all local args miss. */										 	dBUG_5A( cube_err[5], __FUNCTION__,		iC-1, CSΩ,	__FILE__, __LINE__ );
_x0_cube_miss:			if(	iC!=zC )	{
									do	{ if(a!=za)	x = ARG( ++a );				else 		{	NX;	goto _none_x;	}
										} while(	x < *Edge( cube ) );
/* all cube iC args miss		*/			lo=iC+1;	/* unlike in "v_includes()", we stay in this block 'til x0 hit. */	goto _nth_search;
/* remaining args miss	*/	}else		{														NX;	goto _none_x;
			}			}			}
		} while( 1 );	/* search	*/

/*	######	######	######	######	######	######	######	######	######	######		*/
/*										BLOCK  3										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
/*	######			STILL IN CUBE 0: FIRST MATCH HAS BEEN FOUND ( *dst )			######		*/
/*	######		ALL SUBSEQUENT MATCHES MARK-OUT AN ARRAY SHIFT RANGE		######		*/

			do	{ while(	x >Ec ){
					if(		zc!=	ic ){	deICE( cube[	++ic ],	Ac, Bc, Qc );  	Ec += Ac+Bc;
/*cube error		*/	}else{					/*	*	*	*	*	*	*	*	*	*	*/				dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Edge( cube),	__FILE__, __LINE__ );
/*not last cube	*/		if(	iC!=zC )	{ do	{ if(a!=za)	x = ARG( ++a );				else			{	NX;	goto _none_x;	}
										} while(	x < *Edge( cube ) );
/* all cube 0 args miss		*/	lo=iC+1;																goto _search;
/* all remaining args miss	*/			}	else /* return...	*	*	*	*	*	*	*	*/	{	NX;	goto _none_x;	}
					}	}

	/* hit?	*/	if(		x !=	Ec
				&&		x >= Ec-Bc )			{		SvREFCNT_dec( *( lim = ARGº +a ) );	
	/* collapse void */	if(	lim-dst	>	off	)		{	src =dst +off;		do{ *dst++ = *src++; }			while( src< lim ); }
								++	off;		}

_C0_next_x:		if( a!=za )	x = ARG( ++a );										else			{	NX;	goto _none_x;	}
				} while(	x < *Edge(	cube ) );

/*	######	######	######	######	######	######	######	######	######	######		*/
/*										BLOCK  4										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
/*	printf("\n_excludes(): cube 0 handled; remaining cubes to be searched for arguments as normal.\n");		*/
							lo =1;	hi =zC +1;	iC= hi >>1;
	do	{												svC=*( ICEº +iC ); 		if(		svC 	== NULL	){	dBUG_4A( cube_err[1], __FUNCTION__,			iC,			__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else {NX;	goto _none_x;	}	}
																			else if(	!SvOK( 	svC)	){	dBUG_6A( cube_err[2], __FUNCTION__, "svC",	iC, &*svC,	__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else {NX;	goto _none_x;	}	}
																			else if(	!SvPOK( 	svC)	){	dBUG_6A( cube_err[3], __FUNCTION__, "svC",	iC, &*svC,	__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else {NX;	goto _none_x;	}	}
									cube = SvPVbyte( svC, CS );			if(		CS< 16		){	dBUG_5A( cube_err[4], __FUNCTION__,			iC, 		 CS,	__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else {NX;	goto _none_x;	}	}
		if(				x <	*Edge(	cube ) ){ if( (	iC=( ( hi	= iC )+lo	)>>1 )==hi ){	_INTRaLOC;			goto _intra;	}
		}else if(			x == *Edge(	cube ) || (	iC=( ( lo	= iC )+hi	)>>1 )==lo ){	_intraloc1up:
																			_INTRaLOC1Up( _cube_miss );
_intra:		ic=0;			zc=zcOf(	cube );
			if(				zc!=-1 ){	deICE0(				Ac, Bc, Qc );  	Ec = Ac+Bc+ *Edge( cubeΩ );	
			   do	{ while(	x >Ec ){
					if(		zc!=	ic ){	deICE( cube[	++ic ],	Ac, Bc, Qc );  	Ec += Ac+Bc;	}else			{	dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Edge( cube),	__FILE__, __LINE__ );
																								goto _cube_miss;
					}																			}
	/* hit?	*/	if(		x !=	Ec
				&&		x >= Ec-Bc )			{		SvREFCNT_dec( *( lim = ARGº +a ) );	
	/* collapse void */	if(	lim-dst	>	off	)		{	src =dst +off;		do{ *dst++ = *src++; }			while( src< lim ); }
								++	off;		}

_next_x:			if( a!=za )	x = ARG( ++a );										else			{	NX;	goto _none_x;	}
				if(		x >	*Edge(	cube ) )	{	if( iC!= zC )			break;	else			{	NX;	goto _none_x;	}	}
				if(		x == *Edge(	cube ) )	{						goto	_intraloc1up;							}
				}while(1);	lo =iC+1;	
_search:							hi =zC +1;		iC=( lo+hi )>>1;
			}else		{ /* cube iC is empty.  all local args miss. */										 	dBUG_5A( cube_err[5], __FUNCTION__, iC-1, CSΩ,	__FILE__, __LINE__ );
_cube_miss:				if(	iC!=zC )	{
									do	{ if(a!=za)	x = ARG( ++a );				else 		{	NX;	goto _none_x;	}
										} while(	x < *Edge( cube ) );
/* all cube iC args miss		*/			lo=iC+1;														goto _search;
/* remaining args miss	*/	}else		{														NX;	goto _none_x;
			}			}			}
		} while( 1 );	/* search	*/

/*	######	######	######	######	######	######	######	######	######	######		*/
/*										FINAL SHIFT										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
_none_x:
	src =dst +off;
	lim= ARGº +za;
	while( src<=lim )	*dst++ = *src++;
			AvFILLp( avArg ) -=off;
	return	AvFILLp( avArg ) ==-1? 1: 0;/* np. */
	}


bool _contains(		/* avArgs */	){ //	count non-matches in avArgs.	return true if any match.	Searches ICEPack;	iterates args. 		Best for large objects with few args.	
	ui08			Qc,
			*	cube,
			*	cubeΩ,
			*	pq;
	STRLEN		CS, CSΩ;

	long long int				za = AvFILLp(	avArg ),	a=0, a_;						if( za==-1	){	dBUG3ps_NOARG;		{CR;					return 0;	}	}
	long long int	lo,		hi,	zC = AvFILLp(	avICE ),	iC;/*=0;*/					if( zC==-1 ){	dBUG3ps_NOCUBE;	{CR; av_clear( avArg );	return 0;	}	}
	char			zcΩ,			zc,					ic=0;

	ui64			Ac, Bc, Ec, x,
				off=0;	/* running shift offset								*/
	SV		**	ARGº =	AvARRAY( avArg ),
			**	ICEº =	AvARRAY( avICE ),					*svC=*ICEº;			if(		svC 	== NULL	){	dBUG_4A( cube_err[1], __FUNCTION__,			iC,			__FILE__, __LINE__ );	if( zC) goto _x0_search;	else{CR; av_clear( avArg ); return 0;	}	}
																			else if(	!SvOK( 	svC)	){	dBUG_6A( cube_err[2], __FUNCTION__, "svC",	iC, &*svC,	__FILE__, __LINE__ );	if( zC) goto _x0_search;	else{CR; av_clear( avArg ); return 0;	}	}
																			else if(	!SvPOK( 	svC)	){	dBUG_6A( cube_err[3], __FUNCTION__, "svC",	iC, &*svC,	__FILE__, __LINE__ );	if( zC) goto _x0_search;	else{CR; av_clear( avArg ); return 0;	}	}
/*	######	######	######	######	######	######	######	######	######	######		*/
/*										BLOCK  1										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
/*					FIND THE FIRST MATCH TO MARK-IN ARRAY SHIFT RANGE					*/
/*			The conditional statements commented "x0 miss?" mark-in each AV shift range.			*/
/*			It is to isolate these cases implicitly that the search loop code is differentiated 4x here—		*/
/*			that, and to initialize *Edge of cube 0 specially, so to eliminate a branch.					*/
						x = ARG( 0 );	cube = SvPVbyte( svC, CS );			if(		CS< 16		){	dBUG_5A( cube_err[4], __FUNCTION__,	iC,	CS,	__FILE__, __LINE__ );	if( zC) goto _x0_search;	else{CR; av_clear( avArg ); return 0;	}	}
	if(					x <  *Edge(	cube ) ){
							zc=zcOf(	cube );
					if(		zc!=-1 ){	deICE0(				Ac, Bc, Qc );  	Ec=	Ac +Bc;
/*cube 0 err	*/		}else{																			dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Edge( cube),	__FILE__, __LINE__ );
												iC=0;											goto _x0_cube_miss;
						}						ic=0;
			do	{ while( x >Ec )	{
					if(		ic!=zc ){	deICE( cube[	++ic ],	Ac, Bc, Qc );  	Ec+=Ac +Bc;
/*cube 0 err	*/		}else{						iC=0;												dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Edge( cube),	__FILE__, __LINE__ );
																								goto _x0_cube_miss;
					}	}
/* x0 miss?	*/	if(		x ==	Ec
				||		x < Ec-Bc ){	off =1;													FM;	goto _C0_next_x;	}

				if( a!=za )	x = ARG( ++a );										else					{CR;return 1;}
				} while(	x < *Edge(	cube ) );
			}
/*	######	######	######	######	######	######	######	######	######	######		*/
/*										BLOCK  2										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
/* 	######		1ST MATCH NOT FOUND IN CUBE 0;		SEARCHING CUBES >0		######		*/
_x0_search:					lo =1;	hi =zC +1;	iC= hi >>1;
	do	{												svC=*( ICEº +iC );		if(		svC 	== NULL	){	dBUG_4A( cube_err[1], __FUNCTION__,			iC,			__FILE__, __LINE__ ); if( iC!=zC){ lo=++iC; continue; } else {	off=1+za-a;	NX;	goto _none_x;	}	}
																			else if(	!SvOK( 	svC)	){	dBUG_6A( cube_err[2], __FUNCTION__, "svC",	iC,&*svC,	__FILE__, __LINE__ ); if( iC!=zC){ lo=++iC; continue; } else {	off=1+za-a;	NX;	goto _none_x;	}	}
																			else if(	!SvPOK( 	svC)	){	dBUG_6A( cube_err[3], __FUNCTION__, "svC",	iC,&*svC,	__FILE__, __LINE__ ); if( iC!=zC){ lo=++iC; continue; } else {	off=1+za-a;	NX;	goto _none_x;	}	}
									cube = SvPVbyte( svC, CS );					if(		CS< 16		){	dBUG_5A( cube_err[4], __FUNCTION__,			iC,	CS,		__FILE__, __LINE__ ); if( iC!=zC){ lo=++iC; continue; } else {	off=1+za-a;	NX;	goto _none_x;	}	}
		/* Now that we have verified cube iC, we are clear to read *Edge( cube ).		*/
		if(				x <	*Edge(	cube ) ){ if( (	iC=( ( hi	= iC )+lo	)>>1 )==hi ){	/*
_x0_intraloc: 	*/						cubeΩ= SvPVbyte( *( ICEº +iC-1), CSΩ );		 if(		CSΩ< 16		){	dBUG_5A( cube_err[4], __FUNCTION__,			iC-1, CSΩ,	__FILE__, __LINE__ ); if( iC!=zC){ lo=++iC; continue; } else {	off=1+za-a;	NX;	goto _none_x;	}	}
																								goto _x0_intra;	}
		}else if(			x == *Edge(	cube ) || (	iC=( ( lo	= iC )+hi	)>>1 )==lo ){	_x0_intraloc1up:
																			_nINTRaLOC1Up( _x0_cube_miss );
_x0_intra:	ic=0;  			zc=zcOf(	cube );
			if(				zc!=-1 ){	deICE0(				Ac, Bc, Qc );  	Ec = Ac+Bc+ *Edge( cubeΩ );
			   do	{ while(	x >Ec ){
					if(		zc!=ic ){	deICE( cube[	++ic ],	Ac, Bc, Qc );  	Ec += Ac+Bc;
/*cube iC err	*/		}else{																			dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Edge( cube),	__FILE__, __LINE__ );
																								goto _x0_cube_miss;
					}	}
/* x0 miss?	*/	if(		x ==	Ec
				||		x < Ec-Bc ){	off =1;													FM;	goto _next_x;			}

/* all args hit?	*/	if( a!=za )	x = ARG( ++a );	else return 1;	/* all args hit; none were cut from avArg */
				if(		x >	*Edge(	cube ) )	{	if( iC!= zC) break;
												else{ 							off=1+za-a;	NX;	goto _none_x;	}		}
				if(		x == *Edge(	cube ) )	{												Up;	goto _x0_intraloc1up;	}
				} while( 1 );	lo =iC+1;	/*
_x0_search:	*/						hi =zC +1;	iC=( lo+hi )>>1;
			}else		{/*cube iC empty; many miss.*/
_x0_cube_miss: 																						dBUG_5A( cube_err[5], __FUNCTION__, iC-1, CSΩ,	__FILE__, __LINE__ );
_x0_cube_overrun: 		if(	iC!=zC )	{	a_=a;						
									do	{ if(a!=za)	x = ARG( ++a );				else{  off =1+za-a; NX;	goto _none_x;	}
										} while(	x < *Edge( cube ) );
/* all cube iC args miss	*/				  off=a-a_;	lo=iC+1;									FM;		goto _search;
/* remaining args miss	*/	}else		{ off=1+za-a;											FM;	NX;	goto _none_x;
			}			}			}
		} while( 1 );	/* search	*/

/*	######	######	######	######	######	######	######	######	######	######		*/
/*										BLOCK  3										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
/*	######		STILL IN CUBE 0:	FIRST MISMATCH HAS BEEN FOUND ( *dst )		######		*/
/*	######	ALL SUBSEQUENT [MIS]MATCHES MARK-OUT AN ARRAY SHIFT RANGE		######		*/
			do	{ while(	x >Ec ){
					if(		zc!=	ic ){	deICE( cube[	++ic ],	Ac, Bc, Qc );  	Ec += Ac+Bc; }else{	iC=0;		goto _cube_miss; }
					}
/* next miss?	*/	if(		x ==	Ec
				||		x <  Ec-Bc )	++off;

_C0_next_x:		if( a!=za )	x = ARG( ++a );	else /* return...	*	*	*	*	*	*	*	*/	{	NX;	goto _none_x;	}
				} while(	x < *Edge(	cube ) );

/*	######	######	######	######	######	######	######	######	######	######		*/
/*										BLOCK  4										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
/*	######			SPECIAL CASES HANDLED;	SEARCH AND SHIFT NORMALLY		######		*/
/*	Special cases to initialize the first shift range and *Edge of cube 0 were handled in blocks 1-3. 		*/

							lo =1;	hi =zC +1;	iC= hi >>1;
	do	{												svC=*( ICEº +iC );	 	if(		svC 	== NULL	){	dBUG_4A( cube_err[1], __FUNCTION__,			iC,			__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else {	off+=1+za-a;	NX;	goto _none_x;	}	}
																			else if(	!SvOK( 	svC)	){	dBUG_6A( cube_err[2], __FUNCTION__, "svC",	iC, &*svC,	__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else {	off+=1+za-a;	NX;	goto _none_x;	}	}
																			else if(	!SvPOK( 	svC)	){	dBUG_6A( cube_err[3], __FUNCTION__, "svC",	iC, &*svC,	__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else {	off+=1+za-a;	NX;	goto _none_x;	}	}
									cube = SvPVbyte( svC, CS );					if(		CS< 16		){	dBUG_5A( cube_err[4], __FUNCTION__,			iC,  CS,		__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else {	off+=1+za-a;	NX;	goto _none_x;	}	}
		if(				x <	*Edge(	cube ) ){ if( (	iC=( ( hi	= iC )+lo	)>>1 )==hi ){	/*
_x0_intraloc: 	*/						cubeΩ= SvPVbyte( *( ICEº +iC-1), CSΩ );		 if(		CSΩ< 16		){	dBUG_5A( cube_err[4], __FUNCTION__,			iC-1, CSΩ,	__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else {	off+=1+za-a;	NX;	goto _none_x;	}	}
																								goto _intra;		}
		}else if(			x == *Edge(	cube ) || (	iC=( ( lo	= iC )+hi	)>>1 )==lo ){	_intraloc1up:
																			_nINTRaLOC1Up( _cube_miss );
_intra:		ic=0;			zc=zcOf(	cube );
			if(				zc!=-1 ){	deICE0(				Ac, Bc, Qc );  	Ec = Ac+Bc+ *Edge( cubeΩ );	
			   do	{ while(	x >Ec )	{
					if(		zc!=	ic ){	deICE( cube[	++ic ],	Ac, Bc, Qc );  	Ec += Ac+Bc;
					}else{																			dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Edge( cube),	__FILE__, __LINE__ );
																								goto _cube_overrun;
					}	}
/* miss?		*/	if(		x ==	Ec
				||		x <  Ec-Bc )				++off;

_next_x:  		if( a!=za )	x = ARG( ++a );	else /* return...	*	*	*	*	*	*	*	*/	{	NX;	goto _none_x;	}
				if(		x >	*Edge(	cube ) ){	if( iC!= zC ){	BS;	break;}
											else{ off +=1+za-a;									NX;	goto _none_x;	}	}
				if(		x == *Edge(	cube ) )	{												UP;	goto _intraloc1up;	}
				} while( 1 );			lo =iC+1;
_search:								hi =zC +1;	iC=( lo+hi )>>1;
			}else		{ /* cube iC is empty.  all local args miss. */
_cube_miss:	 																						dBUG_5A( cube_err[5], __FUNCTION__, iC-1, CSΩ,	__FILE__, __LINE__ );
_cube_overrun:				if(	iC!=zC )	{	a_ = a;
									do	{ if(a!=za)	x = ARG( ++a );				else 		{	NX;	goto _none_x;	}
										} while(	x < *Edge( cube ) );
/* all cube iC args miss		*/			off+=a-a_; lo=iC+1;												goto _search;
/* remaining args miss	*/	}else		{off+=1+za-a;												NX;	goto _none_x;

			}			}			}
		} while( 1 );	/* search	*/

/*	######	######	######	######	######	######	######	######	######	######		*/
/*										FINAL SHIFT										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
_none_x:
	return (bool) (AvFILLp( avArg )+1!=off);
	}
bool _encompasses(	/* avArgs */	){ //	count matches in avArgs.		return true if all hit.			Searches ICEPack;	iterates args. 		Best for large objects with few args.	
//	printf("\n_excludes(): ");
	ui08			Qc,
			*	cube,
			*	cubeΩ,
			*	pq;
	STRLEN		CS, CSΩ;

	long long int				za = AvFILLp(	avArg ),	a=0;							if( za==-1	){	dBUG3ps_NOARG;		CR;return 1;	}
	long long int	lo,		hi,	zC = AvFILLp(	avICE ),	iC;/*=0;*/					if( zC==-1 ){	dBUG3ps_NOCUBE;	CR;return 0;	}
	char			zcΩ,			zc,					ic=0;

	ui64			Ac, Bc, Ec, x,
				off=0;	/* running shift offset								*/
	SV		**	ARGº =	AvARRAY( avArg ),
			**	ICEº =	AvARRAY( avICE ),					*svC=*ICEº;			if(		svC 	== NULL	){	dBUG_4A( cube_err[1], __FUNCTION__,			iC,		__FILE__, __LINE__ );	if( zC!=0) goto _x0_search; else{ CR;return 0;}	}
																			else if(	!SvOK( 	svC)	){	dBUG_6A( cube_err[2], __FUNCTION__, "svC",	iC, &*svC,	__FILE__, __LINE__ );	if( zC!=0) goto _x0_search; else{ CR;return 0;}	}
																			else if(	!SvPOK( 	svC)	){	dBUG_6A( cube_err[3], __FUNCTION__, "svC",	iC, &*svC,	__FILE__, __LINE__ );	if( zC!=0) goto _x0_search; else{ CR;return 0;}	}

/*	######	######	######	######	######	######	######	######	######	######		*/
/*										BLOCK  1										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
/*	######			FIND THE FIRST MATCH TO MARK-IN ARRAY SHIFT RANGE		######		*/
/*			The conditional statements commented "x0 hit?" mark-in each AV shift range.				*/
/*			It is to isolate these cases implicitly that the search loop code is differentiated 4x here—		*/
/*			that, and to handle all arguments located in cube (0) as special cases.						*/

						x = ARG( 0 );	cube = SvPVbyte( svC, CS );			if(		CS< 16		){	dBUG_5A( cube_err[4], __FUNCTION__,			iC,	CS,	__FILE__, __LINE__ );	if( zC!=0) goto _x0_search; else{CR;return 0;	}	}
	if(					x <  *Edge(	cube ) ){
							zc=zcOf(	cube );
					if(		zc!=-1 ){	deICE0(				Ac, Bc, Qc );  	Ec=	Ac +Bc;
/*cube 0 err	*/		}else{																			dBUG_6A( cube_err[8], __FUNCTION__,	iC, Ec, *Edge( cube),	__FILE__, __LINE__ );
												iC=0;											goto _x0_cube_miss;
						}						ic=0;
			do	{ while( x >Ec )	{					
					if(		ic!=zc ){	deICE( cube[	++ic ],	Ac, Bc, Qc );  	Ec+=Ac +Bc;
/*cube 0 err	*/		}else{						iC=0;												dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Edge( cube),	__FILE__, __LINE__ );
																								goto _x0_cube_miss;
					}	}
/* x0 hit? 	*/	if(		x !=	Ec
				&&		x >= Ec-Bc ){	off =1;														goto _C0_next_x;	}

				if( a!=za )	x = ARG( ++a );										else			{	CR;	return 0;	}
				} while(	x < *Edge(	cube ) );
			}

/*	######	######	######	######	######	######	######	######	######	######		*/
/*										BLOCK  2										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
/* 	######		1ST MATCH NOT FOUND IN CUBE 0;		SEARCHING CUBES >0		######		*/

_x0_search:		lo =1,	hi =zC +1,				iC= hi >>1;
	do	{												svC=*( ICEº +iC );		if(		svC 	== NULL	){	dBUG_4A( cube_err[1], __FUNCTION__,			iC,			__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else{ CR;return 0;}	}
																			else if(	!SvOK( 	svC)	){	dBUG_6A( cube_err[2], __FUNCTION__, "svC",	iC,&*svC,	__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else{ CR;return 0;}	}
																			else if(	!SvPOK( 	svC)	){	dBUG_6A( cube_err[3], __FUNCTION__, "svC",	iC,&*svC,	__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else{ CR;return 0;}	}
									cube = SvPVbyte( svC, CS );			if(		CS< 16		){	dBUG_5A( cube_err[4], __FUNCTION__,			iC,	CS,		__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else{ CR;return 0;}	}
		if(				x <	*Edge(	cube ) ){ if( (	iC=( ( hi	= iC )+lo	)>>1 )==hi ){	_INTRaLOC;			goto _x0_intra;	}
		}else if(			x == *Edge(	cube ) || (	iC=( ( lo	= iC )+hi	)>>1 )==lo ){	_x0_intraloc1up:
																			_INTRaLOC1Up( _x0_cube_miss );
_x0_intra:	ic=0;			zc=zcOf(	cube );
			if(				zc!=-1 ){	deICE0(				Ac, Bc, Qc );  	Ec = Ac+Bc+ *Edge( cubeΩ );	
			   do	{ while(	x >Ec ){
					if(		zc!=	ic ){	deICE( cube[	++ic ],	Ac, Bc, Qc );  	Ec += Ac+Bc;	}else			{	dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Edge( cube),	__FILE__, __LINE__ );
																								goto _cube_miss;
					}																			}
/* x0 hit? 	*/	if(		x !=	Ec
				&&		x >= Ec-Bc ){	off =1;														goto _next_x;	}

				if( a!=za )	x = ARG( ++a );										else			{	CR;	return 0;	}
				if(		x >	*Edge(	cube ) )	{	if( iC!= zC )			break;	else			{	CR;	return 0;	}	}
				if(		x == *Edge(	cube ) )	{													goto _x0_intraloc1up;		}
				} while( 1 );	lo =iC+1;	
_nth_search:							hi =zC +1;	iC=( lo+hi )>>1;
			}else		{ /* cube iC is empty.  all local args miss. */										 	dBUG_5A( cube_err[5], __FUNCTION__, iC-1, CSΩ,	__FILE__, __LINE__ );
_x0_cube_miss:			if(	iC!=zC )	{
									do	{ if(a!=za)	x = ARG( ++a );				else 		{	NX;	goto _none_x;	}
										} while(	x < *Edge( cube ) );
/* all cube iC args miss		*/			lo=iC+1;	/* unlike in "v_includes()", we stay in this block 'til x0 hit. */	goto _nth_search;
/* remaining args miss	*/	}else		{														NX;	goto _none_x;
			}			}			}
		} while( 1 );	/* search	*/

/*	######	######	######	######	######	######	######	######	######	######		*/
/*										BLOCK  3										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
/*	######			STILL IN CUBE 0: FIRST MATCH HAS BEEN FOUND ( *dst )			######		*/
/*	######		ALL SUBSEQUENT MATCHES MARK-OUT AN ARRAY SHIFT RANGE		######		*/

			do	{ while(	x >Ec ){
					if(		zc!=	ic ){	deICE( cube[	++ic ],	Ac, Bc, Qc );  	Ec += Ac+Bc;
/*cube error		*/	}else{					/*	*	*	*	*	*	*	*	*	*	*/				dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Edge( cube),	__FILE__, __LINE__ );
/*not last cube	*/		if(	iC!=zC )	{ do	{ if(a!=za)	x = ARG( ++a );				else			{	NX;	goto _none_x;	}
										} while(	x < *Edge( cube ) );
/* all cube 0 args miss		*/	lo=iC+1;																goto _search;
/* all remaining args miss	*/			}	else /* return...	*	*	*	*	*	*	*	*/	{	NX;	goto _none_x;	}
					}	}

	/* hit?	*/	if(		x !=	Ec
				&&		x >= Ec-Bc )	++	off;

_C0_next_x:		if( a!=za )	x = ARG( ++a );										else			{	NX;	goto _none_x;	}
				} while(	x < *Edge(	cube ) );

/*	######	######	######	######	######	######	######	######	######	######		*/
/*										BLOCK  4										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
/*	printf("\n_excludes(): cube 0 handled; remaining cubes to be searched for arguments as normal.\n");		*/
							lo =1;	hi =zC +1;	iC= hi >>1;
	do	{												svC=*( ICEº +iC );		if(		svC 	== NULL	){	dBUG_4A( cube_err[1], __FUNCTION__,			iC,			__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else {NX;	goto _none_x;	}	}
																			else if(	!SvOK( 	svC)	){	dBUG_6A( cube_err[2], __FUNCTION__, "svC",	iC, &*svC,	__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else {NX;	goto _none_x;	}	}
																			else if(	!SvPOK( 	svC)	){	dBUG_6A( cube_err[3], __FUNCTION__, "svC",	iC, &*svC,	__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else {NX;	goto _none_x;	}	}
									cube = SvPVbyte( svC, CS );			if(		CS< 16		){	dBUG_5A( cube_err[4], __FUNCTION__,			iC,  CS,		__FILE__, __LINE__ );	if( iC!=zC){ lo=++iC; continue; } else {NX;	goto _none_x;	}	}
		if(				x <	*Edge(	cube ) ){ if( (	iC=( ( hi	= iC )+lo	)>>1 )==hi ){	_INTRaLOC;			goto _intra;	}
		}else if(			x == *Edge(	cube ) || (	iC=( ( lo	= iC )+hi	)>>1 )==lo ){	_intraloc1up:
																			_INTRaLOC1Up( _cube_miss );
_intra:		ic=0;			zc=zcOf(	cube );
			if(				zc!=-1 ){	deICE0(				Ac, Bc, Qc );  	Ec = Ac+Bc+ *Edge( cubeΩ );	
			   do	{ while(	x >Ec ){
					if(		zc!=	ic ){	deICE( cube[	++ic ],	Ac, Bc, Qc );  	Ec += Ac+Bc;	}else			{	dBUG_6A( cube_err[8], __FUNCTION__, iC, Ec, *Edge( cube),	__FILE__, __LINE__ );
																								goto _cube_miss;
					}																			}
	/* hit?	*/	if(		x !=	Ec
				&&		x >= Ec-Bc )	++	off;

_next_x:			if( a!=za )	x = ARG( ++a );										else			{	NX;	goto _none_x;	}
				if(		x >	*Edge(	cube ) )	{	if( iC!= zC )			break;	else			{	NX;	goto _none_x;	}	}
				if(		x == *Edge(	cube ) )	{						goto	_intraloc1up;							}
				}while(1);	lo =iC+1;	
_search:							hi =zC +1;		iC=( lo+hi )>>1;
			}else		{ /* cube iC is empty.  all local args miss. */										 	dBUG_6A( cube_err[5], __FUNCTION__, "", iC-1, CSΩ,	__FILE__, __LINE__ );
_cube_miss:				if(	iC!=zC )	{
									do	{ if(a!=za)	x = ARG( ++a );				else 		{	NX;	goto _none_x;	}
										} while(	x < *Edge( cube ) );
/* all cube iC args miss		*/			lo=iC+1;														goto _search;
/* remaining args miss	*/	}else		{														NX;	goto _none_x;
			}			}			}
		} while( 1 );	/* search	*/

/*	######	######	######	######	######	######	######	######	######	######		*/
/*										FINAL SHIFT										*/
/*	######	######	######	######	######	######	######	######	######	######		*/
_none_x:
	return	AvFILLp( avArg )+1 ==off? 1: 0;/* np. */
	}




ui64	_hits(			/* avArgs */ 	){ //	count matches in avArgs.		return number of hits.		Searches args;	iterates ICEPack. 	best for small objects with many args.	
	long long int	lo=0,	hi = AvFILLp(	avArg )+1;		if( hi==0	){	dBUG3ps_NOARG					return 0;	}
	long long int	a =		hi >>1,	iC = AvFILLp(	avICE );	if( iC==-1 ){	dBUG3ps_NOCUBE				return 0;	}
	long long int	Ub =	hi;

	SSize_t 		hit = 0;
	STRLEN		CS;
	SV		**	psviC0= AvARRAY(	avICE ),	**psviC,		*sviC;
	SV		**	ARGº= AvARRAY(	avArg ),				*svA=*( ARGº +a );

	ui08		Qic,		*cube,	*pq, *pq16;
	ui64		Aic, Bic, Xic, Xa, Zic, Eic, x;
	char		ic;
	for(	;	iC!=-1; --iC ){						sviC=*( psviC0+iC );		if(	sviC 	== NULL	){ dBUG_4A( cube_err[1], __FUNCTION__,		iC,			__FILE__, __LINE__ );		continue; }
																	if(	!SvOK( 	sviC	)	){ dBUG_6A( cube_err[2], __FUNCTION__, "svC",	iC, &*sviC,	__FILE__, __LINE__ );		continue; }
																	if(	!SvPOK( 	sviC	)	){ dBUG_6A( cube_err[3], __FUNCTION__, "svC",	iC, &*sviC,	__FILE__, __LINE__ );		continue; }
						cube=SvPVbyte(	sviC, CS );				if(	CS< 16			){ dBUG_5A( cube_err[4], __FUNCTION__,		iC,  CS,		__FILE__, __LINE__ );		continue; }
		pq16	=16	+	cube;
		ic		= zcOf(  	cube );										if(	ic==-1			){ dBUG_5A( cube_err[5], __FUNCTION__,		iC,  CS,		__FILE__, __LINE__ );		continue; }
		Eic		=*Edge(	cube );						pq=cube+CS;
		for(	; ic!=-1; --ic ){ _deICEr(	cube, CS,	cube[ ic ],		pq,	Aic, Bic, Qic );								/*	printf("hits: #%lld[%d]\n", iC, ic);					*/
				Zic =Eic -Bic;
			for(	Xic =Eic-1; Xic>=Zic; --Xic )	{	if( Xic&0x8000000000000000)	break;	//this routinely happens when ID#0 is set...
/* search	args */	while(	Xic !=SvIVX(	svA ) ){
					if(	Xic > SvIVX(	svA ) ){	lo =	a;	a=( lo+hi )>>1;	if(a==lo	){ hi=Ub;		goto _miss; }
					}else{					hi =	a;	a=( lo+hi )>>1;	if(a==hi	){ hi=Ub;		goto _miss; }
						}			svA = *(ARGº	+	a );
/* hit		*/		} ++	hit;											if( a==0 )				return hit;	// found last match 
				/* search window narrows */		hi=Ub=	a;
				/* next Xa in Xic..Eic?*/	svA = *( ARGº +	a-1 );			if( Zic > SvIVX(	svA ) )	break;		// no more matches in this ic
_miss:			/* reset search	*/			lo=0;	a=( lo+hi )>>1;	svA =	*( ARGº +	a );
				}													if(	pq< pq16			){ dBUG_5A( cube_err[6], __FUNCTION__,	iC,  CS,		__FILE__, __LINE__ );		goto _next_iC; }
			Eic =Zic -Aic;
			}								//						if(	Eic !=0			){  	printf("!	Eic!=0 (%lld)\n", Eic );		return hit; }
																	if(	pq !=pq16		){	printf("!	pq!=cube+16 (cube+%lld) function %s in %s line %d\n", pq-cube, __FUNCTION__, __FILE__, __LINE__ );
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
		if(	x > SvIVX( svA ) ){	lo=a;	a=( lo+hi )>>1; if(a==lo	){	lo=LB; hi=UB; a=( lo+hi )>>1;	svA =*( ARGº+a );	++miss; }	\
		}else{				hi=a;	a=( lo+hi )>>1; if(a==hi	){	lo=LB; hi=UB; a=( lo+hi )>>1;	svA =*( ARGº+a );	++miss; }	\
			}																			svA =*( ARGº+a );				\
/*hit*/	}											LB=a+1;	lo=LB; hi=UB; a=( lo+hi )>>1;	svA =*( ARGº+a );/*	goto ... ;	*/

	long long int	LB=0, 		UB = AvFILLp(	avArg )+1;								if( UB==0	){	dBUG3ps_NOARG					return 1;	}
	long long int	lo=LB,		hi=UB,
			iC,	zC = AvFILLp(	avICE ),					a =UB >>1;					if( zC==-1 ){	dBUG3ps_NOCUBE				return 0;	}

	SSize_t 		miss = 0;
	STRLEN		CS;
	SV		**	ICEº= AvARRAY(	avICE ),				*svC=*ICEº;				if(	svC==NULL){					dBUG3ps_svC(0);	return 0; }
	SV		**	ARGº= AvARRAY(	avArg ),				*svA=*ARGº;

	ui64			Ac, Bc, Ec, x;
	ui08		*	pq,		   *	cube = SvPVbyte(	svC,	CS),	Qc;

	char		ic,		zc =zcOf(	cube );			deICE0(			x,  Bc, Qc );			for(	Ec=x+Bc;  x< Ec;  ++x ){			FIND_X_OR_MISS( 0 );		}
	for(		ic=1; ic<=	zc;	++ic )	{			deICE( cube[ ic ],	Ac, Bc, Qc ); x=Ec+Ac;	for(	Ec=x+Bc;  x< Ec;  ++x ){			FIND_X_OR_MISS( 0 );		}
								} 												if(	Ec	!=*( (ui64*)	cube +1 )	){  	dBUG3ps_ic( iC );	return 0; }
																				if(	CS	!= pq 	-	cube	){	dBUG3ps_CS( iC );	return 0; }

	for(		iC=1;iC<=	zC;	++iC ){						svC=*( ICEº +iC );				if( svC==NULL){					dBUG3ps_svC( iC );	return 0; }
							cube = SvPVbyte(	svC, CS );
					zc =zcOf(	cube );			deICE0(			Ac, Bc, Qc ); x=Ec+Ac;	for(	Ec=x+Bc;  x< Ec;  ++x ){			FIND_X_OR_MISS( iC );		}
		for(	ic=1; ic<=	zc;	++ic )	{			deICE( cube[ ic ],	Ac, Bc, Qc ); x=Ec+Ac;	for(	Ec=x+Bc;  x< Ec;  ++x ){			FIND_X_OR_MISS( iC );		}
								} 												if(	Ec	!=*( (ui64*)	cube +1 )	){  	dBUG3ps_ic( iC );	return 0; }
																				if(	CS	!= pq 	-	cube	){	dBUG3ps_CS( iC );	return 0; }
		}
	return miss==0? 1: 0;	/* np. */
	}
bool _strikes(			/* avArgs */	){ //	cut matches from avArgs.		return true if all hit.			Searches args;	iterates ICEPack. 	best for small objects with many args.	
	#define	PULL_X_OR_CONTINUE( $iC, $pSv )	\
	while(	x !=SvIVX( svA ) ){	\
		if(	x > SvIVX( svA ) ){	lo=a;	a=( lo+hi )>>1; if(a==lo	){	lo=LB; hi=UB; a=( lo+hi )>>1;	svA =*( ARGº+a );	continue; }	\
		}else{				hi=a;	a=( lo+hi )>>1; if(a==hi	){	lo=LB; hi=UB; a=( lo+hi )>>1;	svA =*( ARGº+a );	continue; }	\
			}																		svA =*( ARGº+a );				\
/*hit*/	} SvREFCNT_dec( svA );	$pSv=	ARGº+a;	 		LB=a+1;	lo=LB; hi=UB; a=( lo+hi )>>1;	svA =*( ARGº+a );/*	goto ... ;	*/

	ui64			Ac, Bc, Ec, x;
	ui08			Qc,
			*	cube,
			*	pq;
	SSize_t 		hit;	//displacement
	STRLEN		CS;

	long long int	LB=0,	UB=	AvFILLp(	avArg )+1;										if( UB==0	){	dBUG3ps_NOARG					return 1;	}
	long long int	lo=LB,	hi=UB,
			iC,		zC =		AvFILLp(	avICE ),			a =UB >>1;						if( zC==-1 ){	dBUG3ps_NOCUBE				return 0;	}
	SV		**	src,
			**	dst,
			**	lim,
			**	ICEº= AvARRAY( avICE ),				*	svC = *ICEº;	   				if( svC==NULL){					dBUG3ps_svC(0);							return 0;		}
	SV		**	ARGº= AvARRAY( avArg ),				*	svA = *( ARGº +a );
								cube = SvPVbyte(	svC, CS);
	char		ic,		zc = zcOf(	cube );		deICE0(			x, Bc, Qc );				for(	Ec=x+Bc;  x< Ec;  ++x ){			PULL_X_OR_CONTINUE( 0, dst );	hit=1;iC=0;	goto	_next_x;	}
		for(	ic=1; ic<=	zc;	++ic )	{			deICE( cube[ ic ],	Ac, Bc, Qc );  x=Ec+Ac;		for(	Ec=x+Bc;  x< Ec;  ++x ){			PULL_X_OR_CONTINUE( 0, dst );	hit=1;iC=0;	goto	_next_x;	}
								} 													if(	Ec	!=*( (ui64*)	cube +1 )	){  	dBUG3ps_ic( 0 );							return 0;		}
																					if(	CS	!= pq 	-	cube	){	dBUG3ps_CS( 0 );							return 0;		}

	for(		iC=1;iC<=	zC;	++iC ){							svC = *(ICEº +iC );				if( svC==NULL){					dBUG3ps_svC( iC );							return 0;		}
								cube = SvPVbyte(	svC, CS );
			ic=0;	zc = zcOf(	cube );		deICE0(			Ac, Bc, Qc );  x=Ec+Ac;		for(	Ec=x+Bc;  x< Ec;  ++x ){			PULL_X_OR_CONTINUE( iC, dst );	hit=1;		goto	_next_x;	}
		for(	ic=1; ic<=	zc;	++ic )	{			deICE( cube[ ic ],	Ac, Bc, Qc );  x=Ec+Ac;		for(	Ec=x+Bc;  x< Ec;  ++x ){			PULL_X_OR_CONTINUE( iC, dst );	hit=1;		goto	_next_x;	}
								} 													if(	Ec	!=*( (ui64*)	cube +1 )	){  	dBUG3ps_ic( 0 );							return 0;		}
																					if(	CS	!= pq 	-	cube	){	dBUG3ps_CS( 0 );							return 0;		}
		}
	return 0;	/*	after iterating ICE object, a first matching argument was never found. */

	for(		;	iC<=	zC;	++iC ){							svC = *( ICEº +iC );				if( svC==NULL){					dBUG3ps_svC( iC );							return 0;		}
								cube = SvPVbyte(	svC, CS );	pq=cube+16;
					zc = zcOf(	cube );				
		for(	ic=0; ic<=	zc;	++ic )	{			deICE(cube[ ic ],	Ac, Bc, Qc );  x = Ec+Ac;		for(	Ec=x+Bc;  x< Ec;  ++x )	{		PULL_X_OR_CONTINUE( iC, lim );

																					/* array shift to collapse void */		if(hit< lim-dst)	{	src =dst +hit;
																																	do	{ *dst++ = *src++;} while( src< lim );
																																}	++hit;							_next_x:	}
								}													if(	Ec	!=*( (ui64*)	cube +1 )	){  	dBUG3ps_ic( 0 );							return 0;		}
																					if(	CS	!= pq 	-	cube	){	dBUG3ps_CS( 0 );							return 0;		}
		}
_end:
	lim= ARGº + AvFILLp(	avArg );
	src= ARGº +lo;
	while( src<=lim )	*dst++=*src++;
			AvFILLp( avArg ) -=hit;
	return	AvFILLp( avArg ) ==-1? 1: 0;
	}
