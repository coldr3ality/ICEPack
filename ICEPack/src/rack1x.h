#define	cui8	const	unsigned	char	
#define	ui08			unsigned	char	
#define	ui16			unsigned	short 
#define	ui32		long	unsigned	int 
#define	si64	long long			int 
#define	ui64	long long	unsigned	int 
#define	ui64	long long	unsigned	int 

	#include	"dBUG.h"
	#include	"SwCASE.h"	
	#include	"_AvSEQ.h"	/*	function-like macros for array "resequencing"	*/	
ui08				ixZmax=0, ixZmin=32, ix0max=0, ix0min=32;
ui08	range[24][2]=	{	{255,0},{255,0},{255,0},{255,0},	{255,0},{255,0},{255,0},{255,0},
					{255,0},{255,0},{255,0},{255,0},	{255,0},{255,0},{255,0},{255,0},
					{255,0},{255,0},{255,0},{255,0},	{255,0},{255,0},{255,0},{255,0}
				};

extern AV	*	avDBUG;	extern long long int	zd;
extern AV	*	avICE;		extern long long int	iC, iC0, iCZ, iCx, post_C, zC, zzC, post_zC, rel_iC, less_iC;  	//	iC is the index of the current cube.  zC is the array index of the ending cube.

extern ui64		displacement;
extern SV	**	src,
			**	dst,
			**	pSv0,
			*	svZ,	 				/*	SV containing right-hand cube data	(upper fragment)		*/
			*	sv,					/*	SV containing pre-rack cube data		(original pre-op cube)	*/
			*	sv0;					/*	SV containing left-hand cube data		(lower fragment)		*/
extern STRLEN	cS, CS, CSZ;
extern ui08	*	cube,				/*	unsigned char * cube data (of index iC )					*/
			*	cubeZ,				/*	unsigned char * cube data (of index iC -1)					*/
				*pk,		*pq,
			/*	*pkz, */	*pqz,
				*pk_,	*pq_,	
			/*	*pkx, */	*pqx,
				q, q0, q1,		/*	q-field lengths, used generically	*/
				buf[],
		u,		v,		w,		/*	matrix indeces			iterate		the modification range		in	matrix { A[], B[], E[], Q[] }	*/

		ix0,  	ixZ,  	ixN; 	/*	matrix indeces			mark in/out	the modification range		in	matrix { A[], B[], E[], Q[] }	*/
extern char	*	lightning;
extern char		aString[],
				ic, 				/*	cyclum index			iterates		the read position			in	char *	cube			*/
				ic0,	icZ,	icN,		/*	cyclum indeces		mark in/out	the destination range		in	char *	cube				*/
				zc,	zcZ,			/*	cyclum index 			identifies		the zeta cyclum			of	char *	cube / cubeZ		*/
				tena_zc;			/*	cyclum index			identifies		the tentative zeta cyclum	of	char *	cube			*/
			
extern void		deIceV_KEI(),
				_print_mx( unsigned char mx_max),
				_init_mx();

extern ui64		x, y, z,				/*	common method arguments													*/
				Ac, Bc, Ec, E_,
				skip, hit, miss;			/*	the number of misses or collissions counted as a method processes arguments  		*/

//extern char *	opStat[];

extern enum	opStat{	null, ok, mod, new }
			RW[	256 ];			/* read/write status enumerator			*/

extern ui64	A[	256 ],	Ac,		/* relative coord.s	which define	each negative cyclum phase	in	matrix { A[], B[], E[], Q[] }	*/
			B[	256 ],	Bc,		/* relative coord.s	which define	each positive cyclum phase	in	matrix { A[], B[], E[], Q[] }	*/
			E[	256 ],	Ec,		/* "Epsilon" values	which bound	the absolute coordinates	in	matrix { A[], B[], E[], Q[] }	*/
			ZC[	256 ];			/* cube lengths, pre-re-fragmentation  	*/
extern ui08 	I[	256 ],			/* cycla indeces	which align	pre/post op keybytes		in	char *	cube			*/
			H[	256 ],			/* header codes	which ex_z.	q-data field space			in	char *	cube			*/
		*	Qp[	256 ],
			Q[	256 ],	Qc,		/* q-data lengths	which define	each read increment		in	char *	cube			*/
			Qx[	256 ],			/* q-data lengths	which define	each write increment		in	char *	cube			*/
			O[	256 ],			/* q-data offsets	which mark	each read position			in	char *	cube			*/
			Ox[	256 ];			/* q-data offsets	which mark	each write position			in	char *	cube			*/

#define	XLOAD( $pdst, $osrc, $bytes,$dBUG_MACRO )			pq_ =cube +$osrc;							$dBUG_MACRO;	\
	while( $bytes >7 ){ *( (ui64*)	$pdst ) = *( (ui64*)	pq_ );		$pdst +=8;  	pq_+=8;  	$bytes-=8;	}	\
	while( $bytes >3 ){ *( (ui32*)	$pdst ) = *( (ui32*)	pq_ );		$pdst +=4;  	pq_+=4;  	$bytes-=4;	}	\
	while( $bytes >1 ){ *( (ui16*)	$pdst ) = *( (ui16*)	pq_ );		$pdst +=2;  	pq_+=2;  	$bytes-=2;	}	\
	while( $bytes!=0 ){ *( (ui08*)	$pdst ) = *( (ui08*)	pq_ );	++	$pdst;	++	pq_;	--	$bytes;		}

#define ICEPACK( $pq, $I, $Z, $N, $dBUG_MACRO, $dBUG_MACRO_i )										$dBUG_MACRO(	$I );	\
		for(	;				$Z	>	$I;--$Z )	\
			if( Ox[ $N ] - Ox[	$Z ] >2 ){			\
				do	{	switch(	H[	$I	] ){	qCAST_t3inc(	A[ $I ],	B[ $I ],	$pq  ); }					$dBUG_MACRO_i(	$I );	\
					}	while(	++	$I< $Z );	\
				break;							\
				}								\
		do			{	switch(	H[	$I	] ){	qCAST_t0inc(	A[ $I ],	B[ $I ],	$pq	); }					$dBUG_MACRO_i(	$I );	\
					}	while(	++	$I< $N );

#define iCEPACK( $pq, $I, $Z, $N, $dBUG_MACRO, $dBUG_MACRO_i )										$dBUG_MACRO(	$I );	\
		for(	ix=$I;			$Z	>	ix;--$Z )	\
			if( Ox[ $N ] - Ox[	$Z ] >2 ){			\
				do	{	switch(	H[	ix	] ){	qCAST_t3inc(	A[ ix ],  	B[ ix ],	$pq  ); }					$dBUG_MACRO_i(	ix );	\
					}	while(	++	ix< $Z );	\
				break;							\
				}								\
		do			{	switch(	H[	ix	] ){	qCAST_t0inc(	A[ ix ],  	B[ ix ],	$pq	); }					$dBUG_MACRO_i(	ix );	\
					}	while(	++	ix< $N );

#define ICEpACK( $pq, $I, $Z, $N, $dBUG_MACRO, $dBUG_MACRO_i )										$dBUG_MACRO(	$I );	\
		for(	iz=$Z;			iz	>	$I;--iz )	\
			if( Ox[ $N ] - Ox[	iz ] >2 ){			\
				do	{	switch(	H[	$I	] ){	qCAST_t3inc(	A[ $I ],	B[ $I ],	$pq  ); }					$dBUG_MACRO_i(	$I );	\
					}	while(	++	$I< iz );	\
				break;							\
				}								\
		do			{	switch(	H[	$I	] ){	qCAST_t0inc(	A[ $I ],	B[ $I ],	$pq	); }					$dBUG_MACRO_i(	$I );	\
					}	while(	++	$I< $N );

#define iCEpACK( $pq, $I, $Z, $N, $dBUG_MACRO, $dBUG_MACRO_i )										$dBUG_MACRO(	$I );	\
							iz=$Z;			\
		for(	ix=$I;			iz	>	ix;--iz )	\
			if( Ox[ $N ] - Ox[	iz ] >2 ){			\
				do	{	switch(	H[	ix	] ){	qCAST_t3inc(	A[ ix ],  	B[ ix ],	$pq  ); }					$dBUG_MACRO_i(	ix );	\
					}	while(	++	ix< iz );	\
				break;							\
				}								\
		do			{	switch(	H[	ix	] ){	qCAST_t0inc(	A[ ix ],  	B[ ix ],	$pq	); }					$dBUG_MACRO_i(	ix );	\
					}	while(	++	ix< $N );

#if	defined( DEBUG_RACK_L0) || defined (DEBUG_RACK_L1 )

	#define dBUG_1F3_SUBc0L										pre0_c =post0_c =0;
	#define dBUG_1F3_SUBc0LM	subcase|=1;						pre0_c =post0_c =post0_xc +1;
	#define dBUG_1F3_SUBc1LMH			
	#define dBUG_1F3_SUBc1LM	subcase|=2;
	#define dBUG_1F3_SUBc1MH	subcase|=4;
	#define dBUG_1F3_SUBc1M		subcase|=6;
	#define dBUG_1F3_SUBcZMH	subcase|=8;
	size_t	avdbuginx_dmarkcase;
	char 	subcase=0;
	static char *	subCaseCodes[]={
	/*	0	*/	"LLMHH",		//			"0-L   	1-LxMxH 	2-H   ",
	/*		*/	"xLMMHHx",		//impossible	"0-LxM	1-LxMxH		2-H   ",		//impossible
	/*	1	*/	"LLMH ",			//			"0-L		1-LxM		2-H  ",
	/*		*/	"xLMLMHx",		//impossible	"0-LxM	1-LxM		2-H	",		//impossible
	/*	2	*/	"LMHH ",		//			"0-L		1-MxH   		2-H	",
	/*	3	*/	"LMMHH",		//			"0-LxM	1-MxH		2-H	",
	/*	4	*/	"LMH  ",			//			"0-L		1-M			2-H	",
	/*	5	*/	"LMMH ",		//			"0-LxM	1-M			2-H	",
	/*		*/	"xLLMHMHx",	//impossible	"0-L   	1-LxMxH 	2-MxH   ",	//impossible
	/*		*/	"xLMLMHMHx",	//impossible	"0-LxM	1-LxMxH		2-MxH   ",	//impossible
	/*	6	*/	"LLMMH",		//			"0-L		1-LxM		2-MxH  ",
	/*		*/	"xLMLMMHx",	//impossible	"0-LxM	1-LxM		2-MxH	",	//impossible
	/*		*/	"xLMHMHx",		//impossible	"0-L		1-MxH   		2-MxH	",	//impossible
	/*		*/	"xLMMHMHx",	//impossible	"0-LxM	1-MxH		2-MxH	",	//impossible
	/*	7	*/	"LMMH ",		//			"0-L		1-M			2-MxH	",
	/*	8	*/	"LMMMH"	};	//			"0-LxM	1-M			2-MxH	"	};
#else
		#define dBUG_1F3_SUBcZMH
		#define dBUG_1F3_SUBc0LM
		#define dBUG_1F3_SUBc1LMH
		#define dBUG_1F3_SUBc1LM
		#define dBUG_1F3_SUBc1MH
		#define dBUG_1F3_SUBc1M
#endif

#ifdef DEBUG_RACK_L1	// process audit (brief)
		#define dBUG_1F1		cS =sprintf( aString, "\n_rack(	):	cube%3d: %3d..%-3d	 pre_c: %3d	 pre_q: %3d	    CS: %-3d bytes",	\
														iC,		ic0, icZ,		pre_c,		pre_q,		CS );				\
							\
							cS+=sprintf( aString +cS,	"\n  1F1      	matrix : %3d..%-3d	post_c: %3d	post_q: %3d	O[ixN]: %-3d\n\t\t\t\t	 rel_c: %3d   	 rel_q: %3d\n\t\t\t\t	  hp_c: %3d   	  hp_q: %3d\n\n\t",	\
																ix0, ixZ,		post_c,		post_q,		O[ixN],				rel_c,		rel_q,				hp_c,		hp_q );			AvPUSHaSTRING( aString, cS);

		#define dBUG_1F2L	cS =sprintf( aString,"\n_rack(	):	cube%3d: %3d..%-3d	 pre_c: %3d	 pre_q: %3d	    CS: %-3d bytes",	\
														iC,		ic0, icZ,		pre_c,		pre_q,		CS );				\
							\
							cS+=sprintf( aString +cS,	"\n  1F2L     	matrix : %3d..%-3d	post_c: %3d	post_q: %3d	   CS0: %-3d bytes (		Ox[ en_1 ]( %d ) )\n\t\t\t\t	 rel_c: %3d   	 rel_q: %3d	   CSZ: %-2d bytes ( CS +16 -	Ox[ en_1 ]( %d ) )\n\t\t\t\t\t\t\t	 hp_q: %3d\n	mods: L\n\n\t",	\
																ix0, ixZ,		post_c,		post_q,		Ox[en_1],				Ox[ en_1 ],				rel_c,		rel_q,		CSZ,					Ox[ en_1 ],					hp_q );						AvPUSHaSTRING( aString, cS);

		#define dBUG_1F2H	cS =sprintf( aString,"\n_rack(	):	cube%3d: %3d..%-3d	 pre_c: %3d	 pre_q: %3d	    CS: %-3d bytes",	\
														iC,		ic0, icZ,		pre_c,		pre_q,		CS	);				\
							\
							cS+=sprintf( aString +cS,	"\n  1F2H     	matrix : %3d..%-3d	post_c: %3d	post_q: %3d	   CS0: %-3d bytes (			Ox[ en_1 ]( %d ) )\n\t\t\t\t	 rel_c: %3d   	 rel_q: %3d	   CSZ:	%-2d bytes ( CS	+rel_q( %d ) +16	-O[en_1]( %d ) )\n\t\t\t\t\t\t\t	hpZ_q: %3d\n\n\n\t",	\
																ix0, ixZ,		post_c,		post_q,		O[en_1],						Ox[ en_1 ],				rel_c,		rel_q,		CSZ,					rel_q,			O[en_1],						hpZ_q );				AvPUSHaSTRING( aString, cS);

		#define dBUG_1F2S	cS =sprintf( aString,"\n_rack(	):	cube%3d: %3d..%-3d	  preZ_c: %3d	  pre_q: %3d			CS: %-3d bytes",	\
														iC,		ic0, icZ,		preZ_c,		pre_q,				CS	);				\
							\
							cS+=sprintf( aString +cS,	"\n  1F2S     	matrix : %3d..%-3d	post0_xc: %3d	postZ_c: %3d	postZ_q: %3d    CS0: %-3d bytes (				O[en_1]( %d ) )",			\
																ix0, ixZ,		post0_xc,		postZ_c,		postZ_q,		Ox[en_1],					O[en_1]	);				\
							\
							cS+=sprintf( aString +cS,				"\n\t\t\t\t	   rel_c: %3d	   hp_c: %3d	  hpZ_q: %3d	CSZ: %-3d bytes (16 +postZ_q( %d )	+hpZ_q( %d )	)\n\n\t",	\
																			rel_c,		hp_c,		hpZ_q,		CSZ,				postZ_q,		hpZ_q			);				AvPUSHaSTRING( aString, cS);

		#define dBUG_1F3		cS =sprintf( aString,"\n_rack(	):	cube%3d: %3d..%-3d	  pre0_c: %3d	  pre1_c: %3d	  preZ_c: %3d	CS: %-3d bytes  CS1: %-3d bytes  CSZ: %-3d bytes",				\
														iC,		ic0, icZ,		pre0_c,		pre1_c,		preZ_c,		CS,			CS1,				CSZ				);			\
							\
							cS+=sprintf( aString +cS,	"\n  1F3-%-5s	matrix : %3d..%-3d	 post0_c: %3d	 post1_c: %3d	 postZ_c: %3d",			\
									subCaseCodes[subcase],		ix0, ixZ,		post0_c,		post1_c,		postZ_c				);	\
							\
							cS+=sprintf( aString +cS,					"\n\t\t\t\t	 post0_q: %3d	 post1_q: %3d	 postZ_q: %3d\n\n\t",	\
																			post0_q,		post1_q,		postZ_q				);	\
							*( AvARRAY( avDBUG) +avdbuginx_dmarkcase) =newSVpvn( aString, cS );
		#define dBUG_1F4
	#else
		#define dBUG_1F1
		#define dBUG_1F2L
		#define dBUG_1F2H
		#define dBUG_1F2S
		#define dBUG_1F3
		#define dBUG_1F4
	#endif
	#ifdef DEBUG_RACK_L2		// process audit (verbose)		bytes	shift		src		src index			src out-dex	dst			dst index			dst out-dex			op symbol	msg
		#define								dBUG_XLOAD(	$bytes,			$cubeS,	i$src,			o$src,		$cubeD,		i$dst,			o$dst							)			cS =sprintf( aString,	"\rmv	copy (%3d) byte[s] of passthrough data:\n	%s[%3d..%-3d] = %s[%3d..%-3d]\n",			\
																																																							$bytes,						$cubeD, i$dst, o$dst,	$cubeS, i$src, o$src );	AvPUSHaSTRING( aString, cS);
		#define								dBUG_hiCAST(	$bytes,					ix$src,			ox$src,		$cubeD,		i$dst,			o$dst							)			cS =sprintf( aString,	"\r%c	re-pack (%3d) byte[s] for vector[s] %3d..%-3d    	to %s[%3d..%-3d] \n",					\
																																																			251,				$bytes,						ix$src, ox$src,			$cubeD, i$dst, o$dst );	AvPUSHaSTRING( aString, cS);
		#define								dBUG_hiCAST_i(	$bytes,					ix$src,			hex$src,		$cubeD,		i$dst,			o$dst							) if( $bytes ){	cS =sprintf( aString,	"\r%c	re-pack (%3d) byte[s] for vector %2d ( keybyte 0x%02X)  	to %s[%3d..%-3d]\n",			\
																																																			251,				$bytes,						ix$src, hex$src,		$cubeD, i$dst, o$dst );	AvPUSHaSTRING( aString, cS);	}
		#define								dBUG_bSHIFT(	$bytes, $rel,				i$src,			o$src,		$cube,		i$dst,			o$dst,				$ascii_char 	)			cS =sprintf( aString,	"\r%c	shift (%3d) byte[s] by %+3d:	%s[%3d..%-3d] = %s[%3d..%-3d]\n",						\
																																																			$ascii_char,		$bytes,	$rel,		$cube, i$dst, o$dst,	$cube, i$src, o$src );				AvPUSHaSTRING( aString, cS);
	//	#define								dBUG_bSHIFT_i(					$cubeS,	i$,							$cube,		o$,									$ascii_char 	)			cS =sprintf( aString,	"\r%c\t\t\t	%s[ %d ]	= %s[ %d ];\n", $ascii_char, $cube, i$, $cube, o$ );							AvPUSHaSTRING( aString, cS);
	//														bytes	shift		src		src index			src out-dex	dst			dst index			dst out-dex			op symbol
		#define dBUG_hiCAST_1F1_post( $i)		dBUG_hiCAST(	post_q,					$i,				ixZ,			"cubeZ",    	Ox[	$i	],		Ox[	ixN ]-1			)
		#define dBUG_hiCAST_1F1_post_i( $i)		dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cubeZ",    	pqZ-cubeZ-Q[ $i ],	pqZ-cubeZ-1			)
		#define dBUG_hiCAST_1F2L_post( $i)		dBUG_hiCAST(	post_q,					$i,				zc0,			"cube0",    	Ox[	$i	],		Ox[	en_1 ]-1			)
		#define dBUG_hiCAST_1F2L_post_i($i)		dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cube0",    	pq0-cube0-Q[ $i ],	pq0-cube0-1			)
		#define dBUG_hiCAST_1F2H_post( $i)		dBUG_hiCAST(	post_q,					$i,				ixZ,			"cubeZ",    	16 +lpZ_q,		15 +lpZ_q +post_q		)		
		#define dBUG_hiCAST_1F2H_post_i($i)		dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cubeZ",    	pqZ-cubeZ-Q[ $i ],	pqZ-cubeZ-1			)
		#define dBUG_hiCAST_1F2S_post0( $i )		dBUG_hiCAST(	post0_q,					$i,				zc0,			"cube0",    	Ox[	$i	],		Ox[	en_1 ]-1			)
		#define dBUG_hiCAST_1F2S_post0_i($i)		dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cube0",    	pq0-cube0-Q[ $i ],	pq0-cube0-1			)
		#define dBUG_hiCAST_1F2S_postZ( $i )		dBUG_hiCAST(	postZ_q,					$i,				ixZ,			"cubeZ",    	16,				15	+postZ_q			)
		#define dBUG_hiCAST_1F2S_postZ_i($i)		dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cubeZ",    	pqZ-cubeZ-Q[ $i ],	pqZ-cubeZ-1			)

		#define dBUG_hiCAST_1F3_post0( $i )  		dBUG_hiCAST(	post0_q,					$i,				zc0,			"cube0",    	Ox[	$i	],		Ox[	en_1 ]-1			)
		#define dBUG_hiCAST_1F3_post0_i($i)		dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cube0",    	pq0-cube0-Q[ $i ],	pq0-cube0-1			)
		#define dBUG_hiCAST_1F4_post0( $i )		dBUG_hiCAST_1F3_post0( $i )
		#define dBUG_hiCAST_1F4_post0_i($i)		dBUG_hiCAST_1F3_post0_i($i)

		#define dBUG_hiCAST_1F3LM_post1($i)  	lp1_q	=	O[	ix0 ]	-	O[	en_1 ];\
											dBUG_hiCAST(	post1_q,					$i,				ixZ,			"cube1",    	16 +lp1_q,		15 +lp1_q +post1_q		)	
		#define dBUG_hiCAST_1F3LM_post1_i($i)	dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cube1",    	pq1-cube1-Q[ $i ],	pq1-cube1-1			)
		#define dBUG_hiCAST_1F3MH_post1($i)  	dBUG_hiCAST(	post1_q,					$i,				ixZ,			"cube1",    	16,				15 +post1_q			)
		#define dBUG_hiCAST_1F3MH_post1_i($i)	dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cube1",    	pq1-cube1-Q[ $i ],	pq1-cube1-1			)
		#define dBUG_hiCAST_1F3M_post1($i)  	dBUG_hiCAST(	post1_q,					$i,				ixZ,			"cube1",    	16,				15 +post1_q			)
		#define dBUG_hiCAST_1F3M_post1_i($i)	dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cube1",    	pq1-cube1-Q[ $i ],	pq1-cube1-1			)

		#define dBUG_hiCAST_1F3_postZ( $i )  		dBUG_hiCAST(	postZ_q,					$i,				ixZ,			"cubeZ",    	16,				15 +postZ_q			)
		#define dBUG_hiCAST_1F3_postZ_i( $i )		dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cubeZ",    	pqZ-cubeZ-Q[ $i ],	pqZ-cubeZ-1			)

		#define dBUG_hiCAST_1F4LM_post1($i)	dBUG_hiCAST_1F3LM_post1($i)
		#define dBUG_hiCAST_1F4LM_post1_i($i)	dBUG_hiCAST_1F3LM_post1_i($i)
//		#define dBUG_hiCAST_1F4MH_post1($i)	dBUG_hiCAST_1F3MH_post1($i)
//		#define dBUG_hiCAST_1F4MH_post1_i($i)	dBUG_hiCAST_1F3MH_post1_i($i)
		#define dBUG_hiCAST_1F4M_post1($i)		dBUG_hiCAST_1F3M_post1_i($i)
		#define dBUG_hiCAST_1F4M_post1_i($i)	dBUG_hiCAST_1F3M_post1_i($i)

		#define dBUG_hiCAST_1F4M_postY($i)  	dBUG_hiCAST(	postY_q,					$i,				ixZ,			"cubeY",    	16,				15 +postY_q			)
		#define dBUG_hiCAST_1F4M_postY_i($i)	dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cubeY",    	pqY-cubeY-Q[ $i ],	pqY-cubeY-1			)
		#define dBUG_hiCAST_1F4MH_postY($i)  	dBUG_hiCAST(	postY_q,					$i,				ixZ,			"cubeY",    	16,				15 +postY_q			)
		#define dBUG_hiCAST_1F4MH_postY_i($i)	dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cubeY",    	pqY-cubeY-Q[ $i ],	pqY-cubeY-1			)

		#define dBUG_hiCAST_1F4_postZ( $i )		dBUG_hiCAST_1F3_postZ( $i )
		#define dBUG_hiCAST_1F4_postZ_i( $i )		dBUG_hiCAST_1F3_postZ_i( $i )

		#define dBUG_bSHIFT_1F1_UP			dBUG_bSHIFT(	hp_q,	rel_q,			O[	ixN	],		CS -1,		"cube",    	Ox[	ixN ],		CSZ	-1,				175	);
		#define dBUG_bSHIFT_1F1_DN			dBUG_bSHIFT(	hp_q,	rel_q,			O[	ixN	],		CS -1,		"cube",    	Ox[	ixN ],		CSZ	-1,				174	);
		#define dBUG_bSHIFT_1F2L_UP			dBUG_bSHIFT(	hp0_q,	rel_q,			O[	ixN	],		O[ en_1	] -1,	"cube0",    	Ox[	ixN ],		Ox[	en_1 ] -1,		175	);
		#define dBUG_bSHIFT_1F2L_DN			dBUG_bSHIFT(	hp0_q,	rel_q,			O[	ixN	],		O[ en_1	] -1,	"cube0",    	Ox[	ixN ],		Ox[	en_1 ] -1,		174	);
		#define dBUG_XLOAD_1F2H_lp1			dBUG_XLOAD(	lp1_q,			"cube",	O[	en_1 ],		O[ ix0	] -1,	"cubeZ",    	16,				15 +lp1_q			)
		#define dBUG_XLOAD_1F2H_hpZ			dBUG_XLOAD(	hp1_q,			"cube",	O[	ixN	],		CS- 1,		"cubeZ",    	16 +lp1_q +post_q,	CSZ	-1				)
		#define dBUG_XLOAD_1F2S_hpZ			dBUG_XLOAD(	hpZ_q,			"cube",	O[	ixN	],		CS -1,		"cubeZ",    	16 +postZ_q,		CSZ	-1				)
		#define dBUG_XLOAD_1F2L_tota1		dBUG_XLOAD(	tota1_q,			"cube",	O[	en_1 ],	 	CS -1,		"cubeZ",    	16,				CSZ -1				)

		#define dBUG_XLOAD_1F3_lp1			dBUG_XLOAD(	lp1_q,			"cube",	O[	en_1 ],		O[ ix0	] -1,	"cube1",    	16,				15 +lp1_q			)
		#define dBUG_XLOAD_1F3MH_hp1		dBUG_XLOAD(	hp1_q,			"cube",	O[	ixN	],		O[ ex_z	] -1,	"cube1",   	16 +post1_q,		CS1-1				)
		#define dBUG_XLOAD_1F3MH_hpZ  		dBUG_XLOAD(	hpZ_q,			"cube",	O[	ex_z ],		CS -1,		"cubeZ",    	16,				CSZ-1				)
		#define dBUG_XLOAD_1F3M_hpZ  		dBUG_XLOAD(	hpZ_q,			"cube",	O[	ixN	],		CS -1,		"cubeZ",    	16 +postZ_q,		CSZ-1				)

		#define dBUG_XLOAD_1F4MH_hpY  		dBUG_XLOAD(	hpY_q,			"cube",	O[	ex_z ],		CS -1,		"cubeY",    	16,				CSY-1				)
		#define dBUG_XLOAD_1F4_lp1			dBUG_XLOAD_1F3_lp1
		#define dBUG_XLOAD_1F4MH_hp1		dBUG_XLOAD_1F3MH_hp1
		#define dBUG_XLOAD_1F4MH_hpZ		dBUG_XLOAD_1F3MH_hpZ
		#define dBUG_XLOAD_1F4M_hpZ			dBUG_XLOAD_1F3M_hpZ
	#else
		#define dBUG_hiCAST_1F1_post($i)
		#define dBUG_hiCAST_1F1_post_i($i)
		#define dBUG_hiCAST_1F2L_post($i)
		#define dBUG_hiCAST_1F2L_post_i($i)
		#define dBUG_hiCAST_1F2H_post($i)
		#define dBUG_hiCAST_1F2H_post_i($i)
		#define dBUG_hiCAST_1F2S_post0($i)
		#define dBUG_hiCAST_1F2S_post0_i($i)
		#define dBUG_hiCAST_1F2S_postZ($i)
		#define dBUG_hiCAST_1F2S_postZ_i($i)
		#define dBUG_hiCAST_1F3_post0($i)
		#define dBUG_hiCAST_1F3_post0_i($i)
		#define dBUG_hiCAST_1F4_post0($i)
		#define dBUG_hiCAST_1F4_post0_i($i)
		#define dBUG_hiCAST_1F3LMH_post1($i)
		#define dBUG_hiCAST_1F3LMH_post1_i($i)
		#define dBUG_hiCAST_1F3LM_post1($i)
		#define dBUG_hiCAST_1F3LM_post1_i($i)
		#define dBUG_hiCAST_1F3MH_post1($i)
		#define dBUG_hiCAST_1F3MH_post1_i($i)
		#define dBUG_hiCAST_1F3M_post1($i)
		#define dBUG_hiCAST_1F3M_post1_i($i)
		#define dBUG_hiCAST_1F3_postZ( $i )
		#define dBUG_hiCAST_1F3_postZ_i( $i )
		#define dBUG_hiCAST_1F4LM_post1($i)
		#define dBUG_hiCAST_1F4LM_post1_i($i)
		#define dBUG_hiCAST_1F4M_post1($i)
		#define dBUG_hiCAST_1F4M_post1_i($i)
		#define dBUG_hiCAST_1F4M_postY($i)
		#define dBUG_hiCAST_1F4M_postY_i($i)
		#define dBUG_hiCAST_1F4MH_postY($i)
		#define dBUG_hiCAST_1F4MH_postY_i($i)
		#define dBUG_hiCAST_1F4_postZ( $i )
		#define dBUG_hiCAST_1F4_postZ_i( $i )
		#define dBUG_bSHIFT_1F1_UP
		#define dBUG_bSHIFT_1F1_DN
		#define dBUG_bSHIFT_1F2L_UP
		#define dBUG_bSHIFT_1F2L_DN
		#define dBUG_XLOAD_1F2H_lp1
		#define dBUG_XLOAD_1F2H_hpZ
		#define dBUG_XLOAD_1F2S_hpZ
		#define dBUG_XLOAD_1F2L_tota1
		#define dBUG_XLOAD_1F3_lp1
		#define dBUG_XLOAD_1F3LMH_hp1
		#define dBUG_XLOAD_1F3MH_hp1
		#define dBUG_XLOAD_1F3MH_hpZ
		#define dBUG_XLOAD_1F3M_hpZ
		#define dBUG_XLOAD_1F4_lp1
		#define dBUG_XLOAD_1F4MH_hp1
		#define dBUG_XLOAD_1F4MH_hpZ
		#define dBUG_XLOAD_1F4MH_hpY
		#define dBUG_XLOAD_1F4M_hpZ
	#endif
	#ifdef DEBUG_RACK_L3		//	paranoid integrity checks which are silent until there's a problem
		#define dBUG_1F3_TENA_ZC							if( ix0 >= enZ1){	printf( lightning );	printf("!	ix0( %d ) must be less-than enZ1( %d ).  invalid value for tena_zc: %d\n",		ix0, enZ1, tena_zc );	}	\
														if( ixZ <= en_1){	printf( lightning );	printf("!	ixZ( %d ) must be greater-than en_1( %d ).  invalid value for tena_zc: %d\n",	ixZ, en_1, tena_zc );	}

		#define dBUGmxB4( $X )	_print_mx( $X );	
		#define dBUGmxEO( $X )	_print_mx( $X  );	_init_mx();
													//	if( rel_q		!=	post_q -pre_q		){ printf( "\r!	_rack1x(): 	( rel_q = Ox[ ixN ] - O[ ixN ]	)==%d should be equal to:\n			( rel_q = post_q -pre_q	)==%d\n\n",	\
																												rel_q,						post_q -pre_q );	}
		#define dBUG_SvCUR($CS, $VARNAME)				if( $CS<16){ printf("\n!	%s< 16 ( %d )	%s line %lld \n",			__FILE__, __LINE__, $VARNAME, $CS );	exit(-1);	}
		#define dBUGrackCALL($FRAG_LEV)					if( ix0		==	0xFF			){						printf("\n!	_rack1x%d():	nothing to rack\n",										$FRAG_LEV);	goto _end;	}\
			STRLEN	CS_check;							if( pSv0    	!=	AvARRAY( avICE )	){ pSv0=AvARRAY( avICE );	printf( "\r!	_rack1x%d(): 	(SV**) \"pSv0)\" was out of sync with *AvARRAY( avICE )!\n",	$FRAG_LEV);	}\
			SV*		sv_check 	= *(pSv0 +iC);				if( &*sv   	!=	&*sv_check		){ sv=sv_check;			printf( "\r!	_rack1x%d(): 	(SV*) \"sv\" was out of sync with *( AvARRAY( avICE ) +iC )!\n",	$FRAG_LEV);	}\
			ui08*	cube_check	= SvPVbyte( sv, CS_check );	if( cube		==	NULL			){ cube=cube_check;		printf("\n!	_rack1x%d():	(unsigned char*) cube was NULL!\n",						$FRAG_LEV);	}\
													else	if( &*cube	!=	&*cube_check		){ cube=cube_check;		printf( "\r!	_rack1x%d(): 	(char *) \"cube\" was out of sync with SvPVbyte( ... )! \n",		$FRAG_LEV);	}\
														if( CS    		!=	CS_check			){ CS=CS_check;			printf( "\r!	_rack1x%d(): 	(STRLEN) \"CS\" was out of sync with SvPVbyte( ... )!\n",		$FRAG_LEV);	}\
			char		zc_check= zcOf(  *( (ui64*)	cube) );		if( zc_check	!=	zc				){ zc= zc_check;			printf( "\r!	_rack1x%d(): 	(char) \"zc\" was out of sync with zcOf( ... )!\n",				$FRAG_LEV);	}
	#else
		#define dBUG_1F3_TENA_ZC
		#define dBUGmxB4( $X )
		#define dBUGmxEO( $X )
		#define dBUG_SvCUR($CS, $VARNAME )
		#define dBUGrackCALL($FRAG_LEV)
	#endif
