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
#include	"_ICE.h"
#include "_AvMOD.h"

#define vOK		RW[ v ] = ok;
#define uMOD0	RW[ 0 ] = mod;
#define tMOD	RW[ t ] = mod;
#define uNUL		RW[ u ] = null;
#define uMOD	RW[ u ] = mod;
#define vMOD	RW[ v ] = mod;
#define uvMOD	RW[ u ] = \
				RW[ v ] = mod;
#define wMOD	RW[ w ] = mod;
#define wNEW	RW[ w ] = new;
#define wvRW	RW[ w ] = RW[ v ];
#define vNUL		RW[ v ] = null;
#define wNUL		RW[ w ] = null;
#define uNEW 	RW[ u ] = new;
#define vNEW 	RW[ v ] = new;
#define uMvM	RW[ u ] = mod;	\
				RW[ v ] = mod;

#define uMvN	RW[ u ] = mod;	\
				RW[ v ] = null;

#define INIT_MxRACK		run_iC=ixº=oc=ocª=0;	ixM=0xFF; /*<— how we know there's nothing to commit	*/
#define INIT_AvCOMMIT	rSeqCut[0]= rSeqIns[0]= rel_iC= step_iC= dsc=	0;	\
						rSeq_iR[0]= iR=							-1;

#ifdef DEBUG_ACCESS_L2X			//	audit nominal activity verbosely
	#define dBUGinit_mx			_init_mx();
	#define dBUGazMAX( $max )	cS=sprintf(aString, "\n!	%s: too many arguments (max %lld)	at %s line %d\n", __FUNCTION__, $max, __FILE__, __LINE__);					AvDBUG_PUSH( aString, cS );
	#define dBUG_ReICEz(	$v )													cS=sprintf(aString, "\nReICEzSvZ( %d ) line %d\n", $v, __LINE__);						AvDBUG_PUSH( aString, cS );\
								if( (ui08*) cubeΩ != (ui08*) SvPVbyte_nolen( svΩ ) ){	cS=sprintf(aString, "\nReICEzSvZ( %d ): cubeΩ [was] out of sync with svΩ!\n", $v );			AvDBUG_PUSH( aString, cS );\
																			cubeΩ= (ui08*) SvPVbyte_nolen( svΩ );	\
																			}
	#define dBUG_TRACK				cS=sprintf( aString, "\n>>	[TRACK]	ix\xA7: %d\n	oCS: %d\n	oc/oc\xA6: %d/%d\n	xc/xc\xA6: %d/%d\n	O[ oc\xA7]: %d	%s line %d\n\n", ixº, oCS, oc, ocª, xc, xcª, O[ocª], __FILE__, __LINE__ );	 AvDBUG_PUSH( aString, cS);
	#define dBUG_RACK				cS=sprintf( aString, "\n>>	[RACK]	\10	ix\xA7: %d\n	oCS: %d\n	oc/oc\xA6: %d/%d\n	xc/xc\xA6: %d/%d\n	O[ oc\xA7]: %d	%s line %d\n\n", ixº, oCS, oc, ocª, xc, xcª, O[ocª], __FILE__, __LINE__ );	 AvDBUG_PUSH( aString, cS);	
#else
	#define dBUGinit_mx
	#define dBUGazMAX( $max )
	#define dBUG_ReICEz(	$v )
	#define dBUG_TRACK
	#define dBUG_RACK
#endif

/*	MAIN VECTOR MAP OVERFLOW PROTECTION	*/
/*	Only needed when rebalancing is enabled.		*/
#ifdef			ReBAL_ENABLE
	#ifdef		DEBUG_SvCOMMIT_L0X
		#define	dBUG_OVERRUN_WARNING		\
				if( xcª >254) 					{ cS = sprintf( aString, "\n!	(xc\xA6: %d) >= 255:	overrun protection threshold[s] are too low!	%s line %d \n\n",	xcª,				__FILE__, __LINE__); AvDBUG_PUSH( aString, cS );	}
		#define	dBUG_OVERRUN_SOFT($LIM)	{ cS = sprintf( aString, "\n	(xc\xA6: %d) >= %d:	vmap soft-flushed	at argument %lld/%lld...	%s line %d\n",		xcª, $LIM, a, za,	__FILE__, __LINE__); AvDBUG_PUSH( aString, cS );	}
		#define	dBUG_OVERRUN_HARD($LIM)	{ cS = sprintf( aString, "\n	(xc\xA6: %d) >= %d:	vmap hard-flushed	at argument %lld/%lld...	%s line %d\n",		xcª, $LIM,  a, za,	__FILE__, __LINE__); AvDBUG_PUSH( aString, cS );	}
	#else
		#define	dBUG_OVERRUN_WARNING
		#define	dBUG_OVERRUN_SOFT
		#define	dBUG_OVERRUN_HARD
	#endif
	#define	xcª_SOFT_OVERRUN_PROTECTION	if( xcª >=	240	)	{	SvCOMMIT;	lo =iC; hi =nC; iC= ( lo+hi )>>1;				\
			dBUG_OVERRUN_WARNING;	\
		/*	dBUG_OVERRUN_SOFT(	240 );	*/		break;	}
	#define	xcª_HARD_OVERRUN_PROTECTION	if( xcª >=	224	)	{	SvCOMMIT;	if( dsc || rSeqIns[0] || rSeqCut[0] ) _av_commit();	\
			dBUG_OVERRUN_WARNING;	\
		/*	dBUG_OVERRUN_HARD(	224 );	*/				if( za != a ){	x = ARG( ++a );		goto	_start;		\
															}else{							return;				\
															}	}
#else
	#define	xcª_SOFT_OVERRUN_PROTECTION_VIA_SvCOMMIT
	#define	xcª_HARD_OVERRUN_PROTECTION_VIA_AvCOMMIT
#endif



#ifdef DEBUG_SvCOMMIT_L0
	#define dBUG_MkIn		cS=sprintf( aString, "\r^MkIn  		%s line: %d	ixM: %d \n", 						__FILE__, __LINE__, ixM );		AvDBUG_PUSH( aString, cS );
	#define dBUG_MkOut($N)	cS=sprintf( aString, "\r^MkOut(%d) 	%s line: %d	izM: %d	iCO: %lld	icO: %d\n", $N,	__FILE__, __LINE__, u, iCO, icO );	AvDBUG_PUSH( aString, cS );
#else
	#define dBUG_MkIn
	#define dBUG_MkOut($N)

#endif

#define MkIn			ixM	= u;										/*	iCI	= iC;	*/	dBUG_MkIn;
#define MkOut($N)	izM=u;	inM=v;	ixH=v; /*	icH=ic+1;	*/	icO = ic;		iCO	= iC;		dBUG_MkOut($N);
#define MkOutZ($N)	izM=u;	inM=v;	ixH=v; /*	icH=ic+1;	*/	icO = zc;		iCO 	= iC;		dBUG_MkOut($N);

#ifdef		DEBUG_ACCESS_L2
	#ifdef	DEBUG_ACCESS_L3
		#define	dBUG_LOCUS( $NAME)	cS=	sprintf( aString,		"\r<%-16s> in %s line %d:	cubes %3lld..%-3lld	*Edge( cube ): %-5llu ( 0x%llX) 	x: %5llu ( 0x%llX )			SvCUR( sv ): %lld	sv( %llx )\n\t",		\
															$NAME,	__FILE__, __LINE__,			iCI, iC,	*Edge( cube ),*Edge( cube ),		x,		x,				SvCUR( sv ),		&*sv		);	\
				if(	zc != zcOf( cube ) )	{cS+=sprintf( aString+cS,	"\r!	%s: zc (was) out of sync with (char*) cube.\n", $NAME);															AvDBUG_PUSH( aString, cS );	\
					zc =	zcOf( cube ); 	}
	#else
		#define	dBUG_LOCUS( $NAME)	cS =	sprintf( aString,		"\r<%-16s> in %s line %d:	cubes %3lld..%-3lld	*Edge( cube ): %-5llu ( 0x%llX) 	x: %5llu ( 0x%llX )			SvCUR( sv ): %lld	sv( %llx )\n\t",		\
															$NAME,	__FILE__, __LINE__,			iCI, iC,	*Edge( cube ),*Edge( cube ),		x,		x,				SvCUR( sv ),		&*sv		);	AvDBUG_PUSH( aString, cS );
	#endif
	#define		dBUG_LOCUS_CLOSE(	$NAME )	cS=sprintf( aString, "\n                     </%-16s>\n");
#else
	#ifdef		DEBUG_ACCESS_L3
		#define	dBUG_LOCUS( $NAME )	if( zc != zcOf(	cube ) )	{	\
												cS =	sprintf( aString, "\r!	%s: zc (was) out of sync with (char*) cube.\n", $NAME);						AvDBUG_PUSH( aString, cS );	\
												zc = zcOf(	cube );	}
	#else
		#define	dBUG_LOCUS(		$NAME )
	#endif
	#define		dBUG_LOCUS_CLOSE(	$NAME )

#endif
#ifdef DEBUG_ACCESS_L2X
	#define		dBUG_CoLOC( $NAME )			cS=sprintf( aString, "\r	<%-8s>	cubes %3lld..%-3lld	ic/zc: %d/%d		[u, v, xc\xA6: %d, %d, %d]	E[u]: %llX (%lld)	x: %llX (%lld)	%s line %d\n", 		\
																$NAME,	iCI,	iC,			ic, zc,			u, v, xcª,		E[ u ], E[u],		x, x, 		__FILE__, __LINE__ );								AvDBUG_PUSH( aString, cS );
	#define		dBUG_CoLOC_CLOSE(	$NAME )	cS=sprintf( aString, "\n                     </%-16s>	\x9Fsub: %lld	[u, v, xc\xA6: %d, %d, %d]	I[u]: %d	RW[u]: %s		\10	\10	\10	%s line %d\n\n", 		\
																$NAME,	ƒloc,			u, v, xcª,		I[ u ],	opStat[ RW[ u ] ],				__FILE__, __LINE__ );		AvDBUG_PUSH( aString, cS );
#else
	#define		dBUG_CoLOC( $NAME )
	#define		dBUG_CoLOC_CLOSE(	$NAME )
#endif

#define			dBUG_ReLOC(		$NAME )	dBUG_LOCUS(			$NAME )
#define			dBUG_ReLOC_CLOSE(	$NAME )	dBUG_LOCUS_CLOSE(	$NAME )

/*	xcª&=0xFFF8;
	do{	*( (ui64*) (RW	+xcª ) )=0;
		*( (ui64*) (Oª	+xcª ) )=0; xcª-=8;	I'd like to make MxINIT more efficient by zeroing RW[] on a long-long-int basis
*/
#ifdef		DEBUG
	#define	MxINIT	xc=-1;	/*ixº=0;	oc=ocª=0; */ while( xcª != -1 ){ Oª[ xcª ] =0;	RW[ xcª-- ]=null; }	if( ixM!=0xFF) printf("\r!	MxINIT called while SvCOMMIT pending!	%s line %d\n", __FILE__, __LINE__ );
#else						
	#define	MxINIT	xc=-1;	/*ixº=0;	oc=ocª=0; */ while( xcª != -1 ){ Oª[ xcª ] =0;	RW[ xcª-- ]=null; }	
#endif
							/*	^ We are going to keep "oc=ocª=0;" in step with "run_iC=0;".
								It's included in INIT_MxRACK at the head of every multi-scalar accessor,		
								and at the end of SvCOMMIT, which should keep them in lockstep with cube run starts and stops.
								The (oc) and (ocª) offsets are always zero until we locate a consecutive arg in a consecutive cube.
								They track the cumulative pre/post cycla offsets leading the currrent cube in an active cube run.
							*/
#define dBUG_CSo	if( oCS<16){	cS=sprintf( aString, lightning ); cS+=sprintf( aString+cS, "\n oCS< 16: %d at %s line %d\n\n", oCS, __FILE__, __LINE__ );	AvDBUG_PUSH( aString, cS); }


/*		LOCUS OPERANDI
		Latin macro names ending in "LOC" focus all operational variables on cube #iC and seek opscope [u, v] for argument x.

					In tandem (usually), these initialize an "interlocal" operation between two "cubes" (opaque data blocks):
	ANTELOC:		Initialize left-hand  vector [u]	at the  end  of	SvPVbyte( *( AvARRAY( avICE ) +iC  	)... )
	INTERLOC:		Initialize right-hand vector [v]	at the start of	SvPVbyte( *( AvARRAY( avICE ) +iC+1	)... )

	CoANTELOC,
	ReINTERLOC:		Conversely, these re-position and continue an already-initialized cube run to do the same for the next argument.

	INTRALOC		Initialize vectors [u, v] on the two adjacent cycla within a given cube which might need to be modified for arg (x).
	CoINTRALOC		Re-position vectors [u,v] likewise for the next argument, when it is also within the current cube.

	EPILOC			Focus on cube zC (the last cube) and position left-hand vector [u] at the end to append remaining args.
	CoEPILOC		Does the same thing, but continuing an already active cube run rather than initializing a new one.

	PRIMOLOC		Does the same thing as INTRALOC, but specifically for cube #0.

	ABLOC			locus of removal  / ablasion.
	TRALOC [unused]	threshold-crossing locus
	
	*/
#ifdef DEBUG_ACCESS_L2XX
	#ifdef DEBUG_ACCESS_L0
		#define dBUG_ƒSUB( $case )	ƒloc= $case;	 cS = sprintf( aString, "\r                      \x9FSUB: %d\n", $case );	AvDBUG_PUSH( aString, cS );
	#else
		#define dBUG_ƒSUB( $case )				 cS = sprintf( aString, "\r                      \x9FSUB: %d\n", $case );	AvDBUG_PUSH( aString, cS );
	#endif
	#define dBUG_RT0		cS = sprintf( aString, "\rVMAPiC: TRACK	\10	\10	\10	\10	%s line %d\n", __FILE__, __LINE__ );	AvDBUG_PUSH( aString, cS ); 
	#define dBUG_RT1		cS = sprintf( aString, "\rVMAPiC: MkIn+TRACK	%s line %d\n", __FILE__, __LINE__ );	AvDBUG_PUSH( aString, cS ); 
	#define dBUG_RT2		cS = sprintf( aString, "\rVMAPiC: RACK       	\10	%s line %d\n", __FILE__, __LINE__ );	AvDBUG_PUSH( aString, cS ); 

#else
	#ifdef DEBUG_ACCESS_L0
		#define dBUG_ƒSUB( $case )	ƒloc= $case;
	#else
		#define dBUG_ƒSUB( $case )
	#endif
	#define dBUG_RT0
	#define dBUG_RT1
	#define dBUG_RT2
#endif





/*	NOTE:  ABOUT SCOOCHING THE CUBE RUN MARK-IN INDEX ( iCI ) TO IGNORE SKIPPED ARGUMENTS
		· iCI..iCO mark the cube run modification range.
		· Namespace collissions are often handled simply by ignoring operands.
		· If no modifications are necessary to the leading cube in the run, we must mark-in over again at the next cube;
		  it's not optional.
		  —	this is because lowpass cannot span more than one cube, or we'ld have to add another axis to the vector map
			just to keep track of which lowpass cube each lowpass vector originates from.

	Precursor test #0 defines such a scenario.  However, in attempting to implement the iCI scootch simply by reassigning iCI,
	I remembered that there's more to it.

		·	oc and ocª are offsets used to translate the pre/post internal index space of each cube into the cumulative index space
			of the main writethrough buffer, vector map [K[], A[], B[], E[], I[], O[], Oª[], L[] ].
		·	They are reset to zero in alignment with internal cycle index 0 of the first cube in the run, anytime we enter a new run.
		·	Furthermore, so xc and xcª are initialized to zc upon cube run entry.
		·	The only difference between this and "goto _anteloc" is we don't have to call DeICE*, or set [u, v];

	In the future, we might integrate iCI, oc and ocª into a common struct to hint at their common procedural basis.
	Cube run mark-out iCO has no such functional reason to be included in that struct, and its inclusion might make the hint less obvious.
	However, it would seem to belong there semantically if the struct were perceived as representing the full context of the cube run.
	Perhaps separate structs for the start and end.
	What else would go with iCO?
		·	If the term "oc+icO" occurred more than once, we might give it a place to live there.
			As of 2026-09-06, this occurs nowhere, but I'll be on the lookout for new developments.

	12:56 PM
	I've assumed that ReINTERLOC can determine whether to scooch based on whether the mod range is marked in or not.
	However, CoANTELOC is the co-locutor, and its job is to position vector u on the last unit of cube Ω.

	If x==*Edge( cube ), we can't jump the gun.  It's too early to call cube iC unmodified in ReINTERLOC[¹].

	2026-09-07
	I'll call "the scootch" RACK, and conversely, I'll call cube run advancement DeWRAP.
	The word "rack" has been stuck in my brain since the early days of the Perl-based prototype for ICEPack ("IDEX"),
	but now I'm actually using it correctly: to "rack" the vector map in this sence is to discard the leading part up to the current position
	without executing any operations on it, similar to "racking" a gun to eject a chambered bullet.

	"DeWRAP" has no gun chamber analogy, but it is still apt.  As we interlocate the opscope throughout a continuous run of cubes,
	we must de-wrap each cube in line by re-aligning the offsets which translate cube-local index space to the common vector map space.

	These offsets are:

		oc:	[c]ycla [o]ffset 		Where (ic) originates at 0 for each cube, (oc) offsets that by total length of all leading cubes.
		ocª:	[c]ycla [o]ffset (active)	This is also cycla count for total cube run up to before current cube, but for post-op cycla count.
		xc:	[c]ycla e[x]tent		Same origin/basis as oc[ª], but it also counts the cycla within the current cube.
		xcª:	[c]ycla e[x]tent (active)	Same origin/basis, but for post-op cycla count. 
								—Caveat:	This count is obviously in flux for the current cube,
											but it is atomically updated in lockstep with (ic), on each discrete operation.

	So then, it has come to my attention that when we rack the vector map, oc and xc reset, but ocª and xcª do not.
	This ought to be obvious, but that is because oc and xc track the pre-operational offsets of the original cube data,
	while ocª and xcª (the "ª" is for "active") track the corresponding indeces in the vector map.
	So, unless we call MxINIT and wipe the buffer clean, pretending we just entered the operation loop,
	ocª and xcª will continue to accumulate the value of zc for each cube in the run, as normal.

	2026-10-01
	Stability of the essential rebalancing algorithm was achieved several days ago, verified yesterday.
	However, I am not yet ready to shift my focus away from the fragmentation/rebalancing layer;
	it is not yet fully functional, as the vector map is still completely unprotected from overflow,
	a crude workaround of limiting the max arguments to 40 is in place.

	Perhaps limiting argument number, though crude and simple, is the most efficient approach. 
	The net computational cost of each batch restart is only a binary search
				
	
	
	*/

#define	RUN_iC__RACK	run_iC=0;														\
						I[ v ]=0;	I[ u ]=	oc=	0;		xc  =  zc;				oCS =	16;	\
						iCI = iC;	ixº=	ocª=	xcª+	1;	xcª += zc +1;							dBUG_RACK

#define	RUN_iC__TRACK	run_iC=1; 	oc=	xc +	1;	xc  += zc	+1;	oCS += CSΩ -	16;			\
									ocª=	xcª+	1;	xcª += zc	+1;/* O[ v ] =oCS;	*/			dBUG_TRACK
//															^passes #97... but it's redundant here, 
//															because DeICE0_vKEI (which is called after RUN_iC) already sets this.
//															Better to set this in T│RACK, below:
#define	RUN_iC	\
		if(		ixM!=0xFF )	{							RUN_iC__TRACK;	O[ v ] =oCS;	dBUG_RT0	}	\
		else if(	RW[ u ] >ok )	{	MkIn;	ReICEuO( u, v );	RUN_iC__TRACK;	O[ v ] =oCS;	dBUG_RT1	}	\
		else					{							RUN_iC__RACK;	O[ v ] =16;	dBUG_RT2	}	


#define	ReINTERLOC¹																		dBUG_ReLOC( "ReINTERLOC1")	\
		zcΩ = zc;	cubeΩ =	cube;	svΩ=sv;			CSΩ=SvCUR(	svΩ	= *(		iC +Aº ) );	/* O[v]=CSΩ;*/	\
		ic=-1;			cube = cube¹;				CS = SvCUR(	sv	= *(++	iC +Aº ) );		\
		pq	=			cube +16;														\
		zc	=	zcOf(	cube	);			/*	run_iC=1;		*/							dBUG_ReLOC_CLOSE( "ReINTERLOC1")	\

#define	ReINTERLOC																		dBUG_ReLOC( "ReINTERLOC")	\
		zcΩ = zc;	cubeΩ =	cube;					CSΩ=SvCUR(	svΩ	= *(		iC +Aº ) );		/* O[v]=CSΩ;*/	\
		ic=-1;			cube = SvPVbyte(						sv	= *(++	iC +Aº ),	CS	);				\
		pq	=			cube +16;														\
		zc	=	zcOf(	cube	);														dBUG_ReLOC_CLOSE( "ReINTERLOC")	\


#define	PRIMOLOC		/*	Vectors [u, v] intralocate cube 0							*/	\
	/*	MxINIT;	*/	cubeΩ =	nube;						CS = SvCUR(	sv=*Aº );	oCS	=	16;					\
		zcΩ = -1;		iCI=iC=0;	CSΩ=16;		svΩ=NULL; 															dBUG_LOCUS("PRIMOLOC");


/*		ANTELOC( $zcΩ )	/*	Vector [u] locates the left cusp of cube iC and iC+1			*/
#define	ANTELOC( $zcΩ )	/*	Vector [u] locates the left cusp of cube iC and iC+1			*/	\
		MxINIT;				DeICEz_uKE_( $zcΩ );									oCS	=	16;					dBUG_LOCUS("ANTELOC");
		/*					^dependent on CS being up to date with SvCUR( cube )		*/

/*		INTERLOC( $0, $1)		Vectors [u, v] interlocate the cusp of cubes iC and iC+1		*/
#define	INTERLOC( $0, $1)	/*	Vectors [u, v] interlocate the cusp of cubes iC and iC+1		*/	\
	xcª= xc= zc = zcOf( cube );								CS = SvCUR(	sv );			oCS	=	16;					\
	run_iC=0;	ocª= oc= ixº= 0;	\
	u=$0; v=$1; K[$0] = cube[ 0];	DeICE0u(   	$0,	$1	);	E[ $0 ] =	*Edge( cubeΩ )	+A[$0] +B[$0];						\
	I[$0] =ic =0;				RW[ $0  ]= mod;										iCI	=	iC;					dBUG_LOCUS("INTERLOC");	\


/*		INTRaLOC			Vectors [u, v] intralocate cube iC							*/
#define	INTRaLOC		/*	Vectors [u, v] intralocate cube iC							*/	\
		zcΩ = zcOf(	cube );				svΩ = *( AvARRAY( avICE) +( iC -1 ) );			oCS	=	16;					\
					cubeΩ = SvPVbyte(	svΩ, CSΩ );															\
		zcΩ = zcOf(	cubeΩ );								CS = SvCUR(	sv );			iCI	=	iC;					dBUG_LOCUS("INTRaLOC");	\

/*		INTRaLOC1Up		Vectors [u, v] intralocate opscope of x as cycla (ic-1, ic) in cube iC+1						*/
#define	INTRaLOC1Up	/*	Vectors [u, v] intralocate opscope of x as cycla (ic-1, ic) in cube iC+1						*/	\
	if(	zC 	!= iC ){	cubeΩ =	cube;		svΩ			=				sv;			oCS	=	16;					\
		zcΩ = zcOf(	cubeΩ );	CSΩ=SvCUR(	svΩ );  cube	=	SvPVbyte(	sv =*( Aº +(	iCI=	++	iC ) ), CS	);			\
	}else{			cubeΩ = (ui08*) SvPVbyte_nolen( *( Aº+iC-1) );	CS = SvCUR(	sv =*( Aº +(	iCI=		zC ) )	);	goto	_epiloc;		\
		}																									dBUG_LOCUS("INTRaLOC1Up");

/*		INTRaLOC1Up_EX		Vectors [u, v] intralocate opscope of x as cycla (ic-1, ic) in cube iC+1  (exclusion op ver.)		*/
#define	INTRaLOC1Up_EX	/*	Vectors [u, v] intralocate opscope of x as cycla (ic-1, ic) in cube iC+1  (exclusion op ver.)		*/	\
	if(	zC != iC ){	cubeΩ =	cube;		svΩ			=				sv;			oCS	=	16;					\
		zcΩ = zcOf(	cubeΩ );	CSΩ=SvCUR(	svΩ );  cube	=	SvPVbyte(	sv =*( Aº +(	iCI=	++	iC ) ), CS	);	\
	}else{	miss+=1+za-a;								CS = SvCUR(	sv );			iCI=		zC;			goto	_exit_2;		\
		}																									dBUG_LOCUS("INTRaLOC1Up_EX");


/*		CoINTRaLOC_if_Eu_lt( $x )		Vectors [u, v] intralocate opscope of next x within current cube iC	( if E[ u ]< x )	*/
#define	CoINTRaLOC_if_Eu_lt( $x )	/*	Vectors [u, v] intralocate opscope of next x within current cube iC	( if E[ u ]< x )	*/	\
		/* mod range start	*/																					dBUG_CoLOC( "CoINTRaLOC")		\
		if( ixM == 0xFF){																						\
			if(		RW[ v ] >ok ){	MkIn;		ReICEuO(	u, v );										u=v++;	dBUG_ƒSUB( 1	);	\
				if(				$x >E[ u ] ){	ReICEuOx(	u, v ); 					deIce_vKEI();			u=v++;	\
					while(		$x >E[ u ] ){	Oª[ v ] =Oª[ u ] +L[ u ];					DeICE_vKEI( u, v );		u=v++; }	\
						}\
			}else if(	RW[ u ] >ok ){	MkIn;		ReICEuO(	u, v );	if( RW[ v ] == null )	deIce_vKEI();			u=v++;	dBUG_ƒSUB( 2	);	\
					while(		$x >E[ u ] ){	Oª[v]=Oª[u] +L[u];						DeICE_vKEI( u, v );		u=v++; }	\
		/* start cancels	*/\
			}else	{					/*	Oª[ v ] =Oª[ u ] +L[ u ];*/	if( RW[ v ] == null )	deIce_vKEI();			u=v++;	dBUG_ƒSUB( 3	);	\
					while(		$x >E[ u ] ){/*	Oª[ v ] =Oª[ u ] +L[ u ];*/					DeICE_vKEI( u, v );		u=v++; }	\
					}																						\
		/* mod range cont.	*/																					\
		}else if(		RW[ v ] >ok ){				ReICEuOx(	u, v );										u=v++;	dBUG_ƒSUB( 11 );	\
			if(					$x >E[ u ] ){	ReICEuOx(	u, v );					deIce_vKEI();			u=v++;	\
					while(		$x >E[ u ] ){	Oª[ v ] =Oª[ u ] +L[ u ];					DeICE_vKEI( u, v );		u=v++; }	\
					}\
		}else if(		RW[ u ] >ok ){				ReICEuOx(	u, v );	if( RW[ v ] == null )	deIce_vKEI();			u=v++;	dBUG_ƒSUB( 12 );	\
					while(		$x >E[ u ] ){	Oª[ v ] =Oª[ u ] +L[ u ];					DeICE_vKEI( u, v );		u=v++; }	\
		\
		}else		{						Oª[ v ] =Oª[ u ] +L[ u ];	if( RW[ v ] == null )	deIce_vKEI();			u=v++;	dBUG_ƒSUB( 13 );	\
					while(		$x >E[ u ] ){	Oª[ v ] =Oª[ u ] +L[ u ];					DeICE_vKEI( u, v );		u=v++; }	\
					}																						dBUG_CoLOC_CLOSE( "CoINTRaLOC")		\

/*		CoINTRaLOC($x)			Vectors [u, v] intralocate opscope of next x as cycla (ic-1, ic) in current cube (iC)		*/
#define	CoINTRaLOC($x)		/*	Vectors [u, v] intralocate opscope of next x as cycla (ic-1, ic) in current cube (iC)		*/		\
	if(							$x >E[ u ]	){	CoINTRaLOC_if_Eu_lt($x)	}

/*		CoANTELOC( $SYM_ID ) 	Vectors [u, v] interlocate opscope of next x, bridging cubes ( iC, iC+1 ).				*/
#define	CoANTELOC( $SYM_ID ) /*	Vectors [u, v] interlocate opscope of next x, bridging cubes ( iC, iC+1 ).				*/	dBUG_CoLOC("CoANTELOC");				\
	if(							ic< zc	){																	\
		if( ixM != 0xFF ){			/*	MkIn already on.	*/														\
			if(		RW[ v ] >ok )	{			ReICEuOx(	u, v );										u=v++;	\
				if(				ic< zc	){	ReICEuOx(	u, v );					deIce_vKEI();			u=v++;	\
					while(		ic< zc	){	Oª[ v ] =Oª[ u ] +L[ u ];					DeICE_vKEI(	u, v	);	u=v++; }	dBUG_ƒSUB(1);	\
					}						\
			}else if(	RW[ u ] >ok )	{			ReICEuOx(	u, v );	if( RW[ v ] == null )	deIce_vKEI();			u=v++;	\
				while(			ic< zc	){	Oª[ v ] =Oª[ u ] +L[ u ];					DeICE_vKEI(	u, v	);	u=v++; }	dBUG_ƒSUB(2);	\
											\
			}else/*	no mods	*/	{			Oª[ v ] =Oª[ u ] +L[ u ];	if( RW[ v ] == null )	deIce_vKEI();			u=v++;	\
				while(			ic< zc	){	Oª[ v ] =Oª[ u ] +L[ u ];					DeICE_vKEI(	u, v	);	u=v++; }	dBUG_ƒSUB(3);	\
								}			\
	/*	MkIn:	only if mods were made	*/		\
		}else{	\
			if(		RW[ v ] >ok )	{	MkIn;	ReICEuO(	u, v );										u=v++;	\
				if(				ic< zc	){	ReICEuOx(	u, v );					deIce_vKEI();			u=v++;	\
					while(		ic< zc	){	Oª[ v ] =Oª[ u ] +L[ u ];					DeICE_vKEI(	u, v	);	u=v++; }	dBUG_ƒSUB(11);	\
					}						\
			}else if(	RW[ u ] >ok )	{	MkIn;  	ReICEuO(	u, v );	if( RW[ v ] == null )	deIce_vKEI();			u=v++;	\
				while(			ic< zc	){	Oª[ v ] =Oª[ u ] +L[ u ];					DeICE_vKEI(	u, v	);	u=v++; }	dBUG_ƒSUB(12);	\
			\
			}else/*	no mods	*/	{								if( RW[ v ] == null )	deIce_vKEI();			u=v++;	\
				while(			ic< zc	){										DeICE_vKEI(	u, v	);	u=v++; }	dBUG_ƒSUB(13);	\
	/*	2026-10-02:	A whole branch was deleted here after being commented for many weeks of develeopment (refer to backups).	*/	\
			}						}		\
	}else						{			/*	case 23: absolutely nothing to do		*/							dBUG_ƒSUB(23);	\
								}			O [ v ] = O [ u ] +L[ u ];		/*	I[ v ] = I[ u ] +1;	*/					dBUG_CoLOC_CLOSE("CoANTELOC");


/*		CoEPILOC				Vectors [u, v] epilocate opscope of next x, crossing the End Of Object vmap boundary.	*/
#define	CoEPILOC( $SYM_ID )	/*	Vectors [u, v] epilocate opscope of next x, crossing the End Of Object vmap boundary.	*/	dBUG_LOCUS("CoEPILOC");	\
	if(							ic< zc	){	/*	re-encode the mod range up to end-of-cube (ic==zc).				*/	\
	/*	MkIn:	already on, continue run.	*/	\
		if( ixM != 0xFF ){																						\
			if(		RW[ v ] >ok )	{			ReICEuOx(	u, v );										u=v++;	dBUG_ƒSUB(10);	\
				if(				ic< zc	){	ReICEuOx(	u, v );					deIce_vKEI();			u=v++;	dBUG_ƒSUB(11);	\
					while(		ic< zc	){	Oª[ v ] =Oª[ u ] +L[ u ];					DeICE_vKEI(	u, v	);	u=v++; }	dBUG_ƒSUB(12);	\
					}						\
			}else if(	RW[ u ] >ok )	{			ReICEuOx(	u, v );	if( RW[ v ] == null )	deIce_vKEI();			u=v++;	dBUG_ƒSUB(20);	\
				while(			ic< zc	){	Oª[ v ] =Oª[ u ] +L[ u ];					DeICE_vKEI(	u, v	);	u=v++; }	\
											\
			}else				{			Oª[ v ] =Oª[ u ] +L[ u ];	if( RW[ v ] == null )	deIce_vKEI();			u=v++;	dBUG_ƒSUB(30);	\
				while(			ic< zc	){	Oª[ v ] =Oª[ u ] +L[ u ];					DeICE_vKEI(	u, v	);	u=v++; }	\
								}																			\
	/*	MkIn:	before mods; at end if none	*/	\
		}else{	\
			if(		RW[ v ] >ok )	{	MkIn;	ReICEuO(	u, v );										u=v++;	dBUG_ƒSUB(40);	\
				if(				ic< zc	){	ReICEuOx(	u, v );					deIce_vKEI();			u=v++;	\
					while(		ic< zc	){	Oª[ v ] =Oª[ u ] +L[ u ];					DeICE_vKEI(	u, v	);	u=v++; }	\
					}						Oª[ v ] =Oª[ u ] +L[ u ];												\
			\
			}else if(	RW[ u ] >ok )	{	MkIn;  	ReICEuO(	u, v );	if( RW[ v ] == null )	deIce_vKEI();			u=v++;	dBUG_ƒSUB(50);	\
				while(			ic< zc	){	Oª[ v ] =Oª[ u ] +L[ u ];					DeICE_vKEI(	u, v	);	u=v++; }	\
											Oª[ v ] =Oª[ u ] +L[ u ];												\
			\
			}else /*	no mods	*/	{								if( RW[ v ] == null )	deIce_vKEI();			u=v++;	\
				while(			ic< zc	){										DeICE_vKEI(	u, v	);	u=v++; }	\
									MkIn;	Oª[ u ] =O [ u ];													\
											Oª[ v ] =O [ u ] +L[ u ];												dBUG_ƒSUB(60);	\
			}					}																			\
		if(				u< xcª )	{			/*	if the mod range extends the cube, keep encoding 'til u==xcª.		*/	dBUG_ƒSUB(70);	\
			do	{							ReICEuOx(	u, v );	u=v++;														\
				} while(	u< xcª	);																			dBUG_ƒSUB(71);	\
								}			Oª[ v ] =Oª[ u ] +L[ u ];												\
	}else if(				u< xcª	){			/*	end-of-cube already; Mkin and encode extended mod range.		*/	\
	/*	MkIn:	already on, continue run.	*/	\
		if( ixM != 0xFF ){ do	{					ReICEuOx(	u, v );	u=v++;										\
						} while(	u< xcª	);																	dBUG_ƒSUB(13);	\
	/*	MkIn:	before mods if any exist	*/	\
		}else{ while( mod >RW[ u ] )	{								u=v++;	if( u == xcª ){	dBUG_ƒSUB(7);	goto	SYM( CoEPI_END, $SYM_ID );	}	\
								}	MkIn;	ReICEuO(	u, v );	u=v++;										\
			while(				u< xcª	){	ReICEuOx(	u, v );	u=v++;	}									dBUG_ƒSUB(8);	\
			}					\
	/*	MkIn:	on xcª, finally, if all else fails	*/	\
	}else if( ixM == 0xFF)			{	MkIn;	Oª[ u ] =O [ u ];													dBUG_ƒSUB(15);	\
											Oª[ v ] =O [ u ] +L[ u ];												\
	}else						{			Oª[ v ] =Oª[ u ] +L[ u ];												dBUG_ƒSUB(16);	\
								}			\
	SYM( CoEPI_END, $SYM_ID ):				O [ v ] =O [ u ] +L[ u ];				I[ v ] = I[ u ] +1;					dBUG_LOCUS_CLOSE("CoEPILOC");




/*		ReINTRaLOC			Vectors [u, v] intralocate opscope of next x as cycla (ic-1, ic) in following cube (++iC)			*/
#define	ReINTRaLOC		/*	Vectors [u, v] intralocate opscope of next x as cycla (ic-1, ic) in following cube (++iC)			*/	dBUG_LOCUS("ReINTRaLOC (not implemented)");
		//not implemented






#define EPIGEN( $u, $v )																						dBUG_LOCUS("EPIGEN");	\
	if( ixM==0xFF )			{ 	MkIn;			Oª[u] =O[u];				\
												Oª[v] =O[u] +L[u];			\
							printf( lightning );	printf( "\n!	CoEPILOC is supposed to MkIn for EPIGEN, always!!!\n\n");	\
							}	w = $v;							RW[ $u ]=epi;								\
	do	{ /*		E[]				I []		A []		O []		B []		RW []		*/							\
		if(		E[ $u ]<	x )	{ 	I[$v]=xc;							RW[ $v ]=epi;								\
		++	xcª;	E[ $v ] =	x+1;				A[ $v ]=x-E[ $u ];	B[ $v ]=1;			ReICEuOx( $u, $v ); $u=$v++;	\
		   if(	xcª >=224 )	{						O[ $v	]=oCS+CS-16;			ReICEuOx( $u, $v );		/*	dBUG_OVERRUN_HARD( 224);*/	\
																										dBUG_OVERRUN_WARNING;	\
						MkOutZ(0);				Oª[ $v+1	]=Oª[ $v ]+L[ $v ];									\
						if( run_iC && iCI!=iC ) _sv_commit_nx();  else _sv_commit_1x();								\
						if( dsc || rSeqIns[0] || rSeqCut[0] ) 	_av_commit();										\
						if( za!=a )	{		x =ARG( ++a );						ixM=0xFF;	goto	_start;	\
						} return;	}																		\
		\
		}else if(	E[ $u ]==	x )	{						  ++	B[ $u];											\
			++	E[ $u ];		}																			\
		if( za!=a )			x =ARG( ++a ); else	break; 															\
		} while( 1 );								O[ $v	]=oCS+CS-16;			ReICEuOx( $u, $v );			\
	MkOutZ(0);									Oª[ $v+1	]=Oª[ $v ]+L[ $v ];		\
/*	cS=sprintf( aString, "\nEPIGEN: O[ v: %d]: %d )=(oCS: %d)+(CS:%d)-16;\n\n", $v, O[$v], oCS, CS );	AvDBUG_PUSH(aString, cS);	*/	\
	if( run_iC && iCI!=iC ) _sv_commit_nx();  else _sv_commit_1x();		ixM=0xFF;		dBUG_LOCUS_CLOSE("EPIGEN");






#define EPILOG( $E0, $u, $v )			AvICExt( x, pq, pk, buf, E_, avArg, a, za );

#define EPILOC( $E0, $u, $v ) iCI= iC;	/*	E []			A []			B []		O/I []	*/							\
	MxINIT;	zc=-1;					E[0] =x+1;	A[0]=x-$E0;	B[0]=1;	I[0]=zc;		/* init coordinates of first ic	*/	\
	ixM=	$v=1; $u=0;

/*	"AvICExt" is a better and worse algorithm than "EPIGEN".	

	AvICExt is simpler; it just iterates and spits out cubes of length 7 with no control over the length of the final cube;
	however, it skips a lot of processing, and without doing in-depth benchmarking, the most obvious conclusion
	is that AvICExt is better with processor resources, and EPIGEN is better with memory.

	The functional difference with EPIGEN is that it utilizes the balanced fragmentation logic of SvCOMMIT, which
	splits the difference of the remaining cycla between the first and the last in the series, guaranteeing that
	the number of new cubes generated will provide optimal capacity to utilize their combined allocations efficiently.

	I honestly cannot rule out using them both in the same methods for different cases.

	Another functional advantage which EPIGEN has is that it integrates seamlessly with operational method logic,
	continuing the modification range where _set() family of accessors overruns the logical end of the object,
	and this point might be the deciding factor.

	I would love to see beautifully concise and and elegantly streamlined code, but I don't know if that's the top priority here.
	*/

	


/*		SvCOMMIT		Mark-out the modification range and call _sv_commit...() to re-balance the SV[s]				*/
#define	SvCOMMIT	/*	Mark-out the modification range and call _sv_commit...() to re-balance the SV[s]				*/	dBUG_LOCUS( "SvCOMMIT" );	\
	if( ixM == 0xFF ){	/* envelope not marked in yet 	*/											\
		if(		RW[ v ] >ok	)	{	MkIn;			ReICEuO( u, v );	u=v++; ReICEuOx( u, v );	MkOut(1);	if( run_iC && iCI< iC ) _sv_commit_nx();  else _sv_commit_1x();	ixM=0xFF;	\
		}else if(	RW[ u ] >ok	)	{	MkIn;			ReICEuO( u, v );							MkOut(2);	if( run_iC && iCI< iC ) _sv_commit_nx();  else _sv_commit_1x();	ixM=0xFF;	\
		}else		/* no mods */	{ /* shunt pointers	*/	cubeΩ= cube; CSΩ=CS; svΩ=sv; zcΩ= zc;		/* nothing to commit */		 								/*	ixM=0xFF; */	\
								}															\
	}else if(		RW[ v ] >ok	)	{					ReICEuOx( u, v );	u=v++; ReICEuOx( u, v );	MkOut(3);	if( run_iC && iCI< iC ) _sv_commit_nx();  else _sv_commit_1x();	ixM=0xFF;	\
	}else if(		RW[ u ] >ok	)	{					ReICEuOx( u, v );							MkOut(4);	if( run_iC && iCI< iC ) _sv_commit_nx();  else _sv_commit_1x();	ixM=0xFF;	\
	}else if(		RW[ u ] >null	)	{					Oª[ v ] =Oª[ u ] +L[ u ];						MkOut(5);	if( run_iC && iCI< iC ) _sv_commit_nx();  else _sv_commit_1x();	ixM=0xFF;	\
	}else						{					Oª[ v ] =Oª[ u ];							MkOut(6);	if( run_iC && iCI< iC ) _sv_commit_nx();  else _sv_commit_1x();	ixM=0xFF;	\
								}	\
/*	if( run_iC ){ */	oCS=16;		run_iC=ixº=oc=ocª=0;		\
/*			} */


/*		SvCOMMIT1x		Mark-out the modification range and call function to re-balance the SV[s]					*/
#define	SvCOMMIT1x	/*	Mark-out the modification range and call function to re-balance the SV[s]					*/	dBUG_LOCUS( "SvCOMMIT" );	\
	if( ixM == 0xFF ){	/* envelope not marked in yet 	*/											\
		if(		RW[ v ] >ok	)	{	MkIn;			ReICEuO( u, v );	u=v++; ReICEuOx( u, v );	MkOut(1);	_sv_commit_1x();	\
		}else if(	RW[ u ] >ok	)	{	MkIn;			ReICEuO( u, v );							MkOut(2);	_sv_commit_1x();	\
		}else		/* no mods */	{ /* shunt pointers	*/	cubeΩ= cube; CSΩ=CS; svΩ=sv; zcΩ= zc;		/* nothing to commit */		\
								}					\
	}else if(		RW[ v ] >ok	)	{					ReICEuOx( u, v );	u=v++; ReICEuOx( u, v );	MkOut(3);	_sv_commit_1x();	\
	}else if(		RW[ u ] >ok	)	{					ReICEuOx( u, v );							MkOut(4);	_sv_commit_1x();	\
	}else						{					Oª[ v ] =Oª[ u ] +L[ u ];						MkOut(5);	_sv_commit_1x();	\
								}



