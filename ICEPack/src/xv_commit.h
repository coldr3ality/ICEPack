#define	cui8	const	unsigned	char	
#define	ui08			unsigned	char	
#define	ui16			unsigned	short 
#define	ui32		long	unsigned	int 
#define	si64	long long			int 
#define	ui64	long long	unsigned	int 
#define	ui64	long long	unsigned	int 
#define Epsilon(	$cube) ( 	(ui64*) $cube+1)

	#include	"dBUG.h"
	#include	"SwCASE.h"	
	#include	"_AvSEQ.h"	/*	function-like macros for array "resequencing"	*/	

#define INIT_SvCOMMIT	ixM=0xFF;								/*<— how we know there's nothing to commit	*/
#define INIT_AvCOMMIT	rSeqCut[0]= rSeqIns[0]=	juke= rel_iC= rack_iC= 	dsc	= 0;	\
						rSeq_iR[0]= iR=							asc	= -1;

extern AV	*	avDBUG;	extern long long int	zd;
extern AV	*	avICE;		extern long long int	iC, iCI, iCO, iCx, post_C, zC, zzC, post_zC, rel_iC, less_iC;  	//	iC is the index of the current cube.  zC is the array index of the ending cube.
extern AV	*	avICE_,
			*	avOut,
			*	avArg;		extern long long int	a, za; 					//	a list of integer value[s] to operate on.
extern ui64		displacement;
extern SV	**	src,
			**	dst,
			**	pSv0,
			*	svZ,	 				/*	SV containing right-hand cube data	(upper fragment)		*/
			*	sv,					/*	SV containing pre-commit cube data	(original pre-op cube)	*/
			*	sv0;					/*	SV containing left-hand cube data		(lower fragment)		*/
extern STRLEN	cS, CS, CSZ;
extern ui08	*	cube,				/*	unsigned char * cube data (of index iC )					*/
			*	cubeZ,				/*	unsigned char * cube data (of index iC -1)					*/
				nube[16],				/*	null cube / new cube									*/
				*pk,		*pq,
			/*	*pkz, */	*pqz,
				*pk_,	*pq_,	
			/*	*pkx, */	*pqx,
				q, q0, q1,		/*	q-field lengths, used generically	*/
				buf[],
		u,		v,		w,		/*	matrix indeces		iterate		the modification range				in	matrix { A[], B[], E[], Q[] }	*/
		ixM, izM, inM,  	ixH; 	/*	matrix indeces		define		the Modification & Highpass ranges	in	matrix { A[], B[], E[], Q[] }	*/
extern char	*	lightning;
extern char		aString[],
				exit_code,
				ic, 				/*	cyclum index			iterates		the read position					in	char *	cube			*/
				icI,	icO,	icN,		/*	cyclum indeces		mark in/out	the destination range				in	char *	cube				*/
				zc,	zcZ;			/*	cyclum index 			identifies		the zeta cyclum					of	char *	cube / cubeZ		*/
extern short		tena_zc;			/*	cyclum index			identifies		the tentative zeta cyclum			of	char *	cube			*/
extern void		deIceV_KEI(),
				_print_mx( unsigned char mx_max, short ix1, short izZ ),
				_init_mx();
extern SV*		retrieve();
extern void		_printHex();

extern ui64		x, y, z,				/*	common method arguments													*/
				Ac, Bc, Ec, E_,
				skip, hit, miss;			/*	the number of misses or collissions counted as a method processes arguments  		*/


	#ifdef DEBUG_SvCOMMIT_L4
		#define dBUG_SUBc1F4x1	subcase1F4|=1;
		#define dBUG_SUBc1F4x2	subcase1F4|=2;
		#define dBUG_SUBc1F4x4	subcase1F4|=4;
		#define dBUG_SUBc1F4x8	subcase1F4|=8;
		#define dBUG_TRACE0x1 trace[0]|=1;
		#define dBUG_TRACE1x1 trace[1]|=1;
		#define dBUG_TRACE1x2 trace[1]|=2;
		#define dBUG_TRACE1x4 trace[1]|=4;
		#define dBUG_TRACE2x1 trace[2]|=1;
		#define dBUG_TRACE2x2 trace[2]|=2;
		#define dBUG_TRACE3x1 trace[3]|=1;
		#define dBUG_TRACE3x2 trace[3]|=2;
		#define dBUG_TRACE3x4 trace[3]|=4;
		#define dBUG_TRACE3x8 trace[3]|=8;
		#define dBUG_TRACE4x1 trace[4]|=1;
		#define dBUG_TRACE4x2 trace[4]|=2;
		#define dBUG_TRACE4x4 trace[4]|=4;
		#define dBUG_TRACE4x8 trace[4]|=8;
		#define dBUG_TRACE_1F4	if(	*( (ui64*) trace_) !=	*( (ui64*) trace ) ||	subcase1F4_ !=	subcase1F4 )	{	printf("\n#1F4-%02lX%010llX:\n[\n", subcase1F4, *( (ui64*) trace ) );	\
									*( (ui64*) trace_) =	*( (ui64*) trace );	subcase1F4_ =	subcase1F4;	\
									_printHex(avICE_);												\
									printf("\n], [ ");												\
									for(	temp_a=0; temp_a<=za; ++temp_a ){							\
										temp_x=SvIVX( *( AvARRAY( avArg )+temp_a ) );	printf("0x%llX, ", temp_x );	\
									} printf("],\n\n"); }
	#else
		#define dBUG_SUBc1F4x1
		#define dBUG_SUBc1F4x2
		#define dBUG_SUBc1F4x4
		#define dBUG_SUBc1F4x8
		#define dBUG_TRACE0x1
		#define dBUG_TRACE1x1
		#define dBUG_TRACE1x2
		#define dBUG_TRACE1x4
		#define dBUG_TRACE2x1
		#define dBUG_TRACE2x2
		#define dBUG_TRACE3x1
		#define dBUG_TRACE3x2
		#define dBUG_TRACE3x4
		#define dBUG_TRACE3x8
		#define dBUG_TRACE4x1
		#define dBUG_TRACE4x2
		#define dBUG_TRACE4x4
		#define dBUG_TRACE4x8
		#define dBUG_TRACE_1F4
	#endif
/*
subcase
	bit 1:	cube Y has highpass
	bit 2:	cube Z has mods
	bit 3:	cube 1 has lowpass
	bit 4:	cube 0 has mods

trace[0]
	bit 1:	cube 0 has post_q bytes

trace[0]
	bit 1:	cube 1 has lp_q bytes
	bit 2:	cube 2 has post_q bytes

trace[0]
	bit 1:	there is at least one cube X
	bit 2:	cube X has post_q bytes

trace[0]
	bit 1:	cube Y keybyte highpass shifted
	bit 2:	cube Y has post_q bytes
	bit 3:	cube Y has hp_q bytes

trace[0]
	bit 1:	cube Z has highpass keybytes
	bit 2:	cube Z has post_q bytes
	bit 3:	cube Z has hp_q bytes

	*/

//extern char *	opStat[];

extern enum	opStat{	null, del, ok, mod, new}
			RW[	256 ];			/* read/write status enumerator			*/

extern ui64	A[	256 ],	Ac,		/* relative coord.s	which define	each negative cyclum phase	in	matrix { A[], B[], E[], Q[] }	*/
			B[	256 ],	Bc,		/* relative coord.s	which define	each positive cyclum phase	in	matrix { A[], B[], E[], Q[] }	*/
			E[	256 ],	Ec,		/* "Epsilon" values	which bound	the absolute coordinates	in	matrix { A[], B[], E[], Q[] }	*/
			ZC[	256 ];			/* cube lengths, pre-re-fragmentation  	*/
extern ui08 	I[	256 ],			/* cycla indeces	which align	pre/post op keybytes		in	char *	cube			*/
			H[	256 ],			/* keybyte codes	which layout	q-data field space			in	char *	cube			*/
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
				do	{	switch(	H[	$I	] ){	SwCASE_AB2IC_t3_inc(	A[ $I ],	B[ $I ],	$pq, $pq ); }		$dBUG_MACRO_i(	$I );	\
					}	while(	++	$I< $Z );	\
				break;							\
				}								\
		do			{	switch(	H[	$I	] ){	SwCASE_AB2IC_t0_inc(	A[ $I ],	B[ $I ],	$pq, $pq ); }		$dBUG_MACRO_i(	$I );	\
					}	while(	++	$I< $N );

#define iCEPACK( $pq, $I, $Z, $N, $dBUG_MACRO, $dBUG_MACRO_i )										$dBUG_MACRO(	$I );	\
		for(	ix=$I;			$Z	>	ix;--$Z )	\
			if( Ox[ $N ] - Ox[	$Z ] >2 ){			\
				do	{	switch(	H[	ix	] ){	SwCASE_AB2IC_t3_inc(	A[ ix ],  	B[ ix ],	$pq, $pq ); }		$dBUG_MACRO_i(	ix );	\
					}	while(	++	ix< $Z );	\
				break;							\
				}								\
		do			{	switch(	H[	ix	] ){	SwCASE_AB2IC_t0_inc(	A[ ix ],  	B[ ix ],	$pq, $pq ); }		$dBUG_MACRO_i(	ix );	\
					}	while(	++	ix< $N );

#define ICEpACK( $pq, $I, $Z, $N, $dBUG_MACRO, $dBUG_MACRO_i )										$dBUG_MACRO(	$I );	\
		for(	iz=$Z;			iz	>	$I;--iz )	\
			if( Ox[ $N ] - Ox[	iz ] >2 ){			\
				do	{	switch(	H[	$I	] ){	SwCASE_AB2IC_t3_inc(	A[ $I ],	B[ $I ],	$pq, $pq ); }		$dBUG_MACRO_i(	$I );	\
					}	while(	++	$I< iz );	\
				break;							\
				}								\
		do			{	switch(	H[	$I	] ){	SwCASE_AB2IC_t0_inc(	A[ $I ],	B[ $I ],	$pq, $pq ); }		$dBUG_MACRO_i(	$I );	\
					}	while(	++	$I< $N );

#define iCEpACK( $pq, $I, $Z, $N, $dBUG_MACRO, $dBUG_MACRO_i )										$dBUG_MACRO(	$I );	\
							iz=$Z;			\
		for(	ix=$I;			iz	>	ix;--iz )	\
			if( Ox[ $N ] - Ox[	iz ] >2 ){			\
				do	{	switch(	H[	ix	] ){	SwCASE_AB2IC_t3_inc(	A[ ix ],  	B[ ix ],	$pq, $pq  ); }		$dBUG_MACRO_i(	ix );	\
					}	while(	++	ix< iz );	\
				break;							\
				}								\
		do			{	switch(	H[	ix	] ){	SwCASE_AB2IC_t0_inc(	A[ ix ],  	B[ ix ],	$pq, $pq	); }		$dBUG_MACRO_i(	ix );	\
					}	while(	++	ix< $N );

#if	defined( DEBUG_SvCOMMIT_L0) || defined (DEBUG_SvCOMMIT_L1 )

	#define dBUG_1F3_SUBc0L										pre0_c =post0_c =0;
	#define dBUG_1F3_SUBc0LM	subcase|=1;						pre0_c =post0_c =post0_xc +1;
	#define dBUG_1F3_SUBc1LMH			
	#define dBUG_1F3_SUBc1LM	subcase|=2;
	#define dBUG_1F3_SUBc1MH	subcase|=4;
	#define dBUG_1F3_SUBc1M		subcase|=6;
	#define dBUG_1F3_SUBcZMH	subcase|=8;
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

#ifdef DEBUG_SvCOMMIT_L1	// process audit (brief)
		#define dBUG_1F1		{cS =sprintf( aString, "\n_sv_commit(%3d):	cube%3d: %3d..%-3d	 pre_c: %3d+1	 pre_q: %3d	    CS: %-3d bytes",	\
													tena_zc,		iC,		icI, icO,		pre_xc,		pre_q,		CS );				\
							\
							cS+=sprintf( aString +cS,	"\n\t  1F1		matrix : %3d..%-3d	post_c: %3d+1	post_q: %3d	O[inM]: %-3d\n\t\t\t\t\t	 rel_c: %3d   	 rel_q: %3d\n\t\t\t\t\t	  hp_c: %3d   	  hp_q: %3d\n\n\t",	\
																ixM, izM,			post_xc,			post_q,		O[inM],				rel_c,		rel_q,				hp_c,		hp_q );			\
							AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase); \
							}
		#define dBUG_1F2L	{cS =sprintf( aString,"\n_sv_commit(%3d):	cube%3d: %3d..%-3d	 pre_c: %3d	 pre_q: %3d	    CS: %-3d bytes",	\
													tena_zc,		iC,		icI, icO,		pre_c,		pre_q,		CS );				\
							\
							cS+=sprintf( aString +cS,	"\n\t  1F2L		matrix : %3d..%-3d	post_c: %3d	post_q: %3d	   CS0: %-3d bytes (		Ox[ ix1 ]( %d ) )\n\t\t\t\t\t	 rel_c: %3d   	 rel_q: %3d	   CSZ: %-2d bytes ( CS +16 -	Ox[ ix1 ]( %d ) )\n\t\t\t\t\t\t\t	 hp_q: %3d\n\n\t",	\
																ixM, izM,		post_c,		post_q,		Ox[ix1],				Ox[ ix1 ],				rel_c,		rel_q,		CSZ,					Ox[ ix1 ],					hp_q );							\
							AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase); \
							}
		#define dBUG_1F2H	{cS =sprintf( aString,"\n_sv_commit(%3d):	cube%3d: %3d..%-3d	 pre_c: %3d	 pre_q: %3d	    CS: %-3d bytes",	\
													tena_zc,		iC,		icI, icO,		pre_c,		pre_q,		CS	);				\
							\
							cS+=sprintf( aString +cS,	"\n\t  1F2H		matrix : %3d..%-3d	post_c: %3d	post_q: %3d	   CS0: %-3d bytes (			Ox[ ix1 ]( %d ) )\n\t\t\t\t\t	 rel_c: %3d   	 rel_q: %3d	   CSZ:	%-2d bytes ( CS	+rel_q( %d ) +16	-O[ix1]( %d ) )\n\t\t\t\t\t\t\t	 hpZ_q: %3d\n\n\n\t",	\
																ixM, izM,		post_c,		post_q,		O[ix1],						Ox[ ix1 ],				rel_c,		rel_q,		CSZ,					rel_q,			O[ix1],					hpZ_q );			\
							AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase); \
							}
		#define dBUG_1F2S	{cS =sprintf( aString,"\n_sv_commit(%3d):	cube%3d: %3d..%-3d	  preZ_c: %3d	  pre_q: %3d			CS: %-3d bytes",	\
													tena_zc,		iC,		icI, icO,		preZ_c,		pre_q,				CS	);				\
							\
							cS+=sprintf( aString +cS,	"\n\t  1F2S		matrix : %3d..%-3d	post0_xc: %3d	postZ_c: %3d	postZ_q: %3d    CS0: %-3d bytes (				O[ix1]( %d ) )",			\
																ixM, izM,		post0_xc,		postZ_c,		postZ_q,		Ox[ix1],					O[ix1]	);				\
							\
							cS+=sprintf( aString +cS,				"\n\t\t\t\t\t	   rel_c: %3d	   hp_c: %3d	  hpZ_q: %3d	CSZ: %-3d bytes (16 +postZ_q( %d )	+hpZ_q( %d )	)\n\n\t",	\
																		rel_c,		hp_c,		hpZ_q,		CSZ,				postZ_q,		hpZ_q			);\
							AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase); \
							}
		#define dBUG_1F3		{cS =sprintf( aString,"\n_sv_commit(%3d):	cube%3d: %3d..%-3d	  pre0_c: %3d	  pre1_c: %3d	  preZ_c: %3d	CS: %-3d bytes  CS1: %-3d bytes  CSZ: %-3d bytes",				\
													tena_zc,		iC,		icI, icO,		pre0_c,		pre1_c,		preZ_c,		CS,			CS1,				CSZ				);			\
							\
							cS+=sprintf( aString +cS,	"\n\t  1F3-%-5s	matrix : %3d..%-3d	 post0_c: %3d	 post1_c: %3d	 postZ_c: %3d",			\
									subCaseCodes[subcase],		ixM, izM,		post0_c,		post1_c,		postZ_c				);	\
							\
							cS+=sprintf( aString +cS,					"\n\t\t\t\t\t	 post0_q: %3d	 post1_q: %3d	 postZ_q: %3d\n\n\t",	\
																			post0_q,		post1_q,		postZ_q				);	\
							AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase); \
							}
		#define dBUG_1F4		{cS =sprintf( aString,"\n_sv_commit(%3d):	cube%3d: %3d..%-3d	  pre0_c: %3d	  pre1_c: %3d	  preY_c: %3d	  preZ_c: %3d	CS: %-3d bytes  CS1: %-3d bytes  CSY: %-3d bytes  CSZ: %-3d bytes",				\
													tena_zc,		iC,		icI, icO,		pre0_c,		pre1_c,		preY_c,		preZ_c,		CS,			CS1,			CSY,			CSZ				);			\
							\
							cS+=sprintf( aString +cS,		"\n\t 		matrix : %3d..%-3d	 post0_c: %3d	 post1_c: %3d	 postY_c: %3d	 postZ_c: %3d",			\
																ixM, izM,		post0_c,		post1_c,		postY_c,		postZ_c				);	\
							\
							cS+=sprintf( aString +cS,	"\n\t	1F4-%8llX-%16llX	 post0_q: %3d	 post1_q: %3d	 postY_q: %3d	 postZ_q: %3d\n\n\t",		\
										subcase1F4, *( (ui64*) trace ),	post0_q,		post1_q,		postY_q,		postZ_q				);	\
							AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase); \
							}
	#else
		#define dBUG_1F1
		#define dBUG_1F2L
		#define dBUG_1F2H
		#define dBUG_1F2S
		#define dBUG_1F3
		#define dBUG_1F4
	#endif
	#ifdef DEBUG_SvCOMMIT_L2		// process audit (verbose)		bytes	shift		src		src index			src out-dex	dst			dst index			dst out-dex			op symbol	msg
		#define								dBUG_XLOAD(	$bytes,			$cubeS,	i$src,			o$src,		$cubeD,		i$dst,			o$dst							)			cS =sprintf( aString,	"\rmv	copy (%3d) byte[s] of passthrough data:\n	%s[%3d..%-3d] = %s[%3d..%-3d]\n",			\
																																																							$bytes,						$cubeD, i$dst, o$dst,	$cubeS, i$src, o$src );	AvDBUG_PUSH( aString, cS);
		#define								dBUG_hiCAST(	$bytes,					ix$src,			ox$src,		$cubeD,		i$dst,			o$dst							)			cS =sprintf( aString,	"\r%c	re-pack (%3d) byte[s] for vector[s] %3d..%-3d    	to %s[%3d..%-3d] \n",					\
																																																			251,				$bytes,						ix$src, ox$src,			$cubeD, i$dst, o$dst );	AvDBUG_PUSH( aString, cS);
		#define								dBUG_hiCAST_i(	$bytes,					ix$src,			hex$src,		$cubeD,		i$dst,			o$dst							) if( $bytes ){	cS =sprintf( aString,	"\r%c	re-pack (%3d) byte[s] for vector %2d ( keybyte 0x%02X)  	to %s[%3d..%-3d]\n",			\
																																																			251,				$bytes,						ix$src, hex$src,		$cubeD, i$dst, o$dst );	AvDBUG_PUSH( aString, cS);	}
		#define								dBUG_bSHIFT(	$bytes, $rel,				i$src,			o$src,		$cube,		i$dst,			o$dst,				$ascii_char 	)			cS =sprintf( aString,	"\r%c	shift (%3d) byte[s] by %+3d:	%s[%3d..%-3d] = %s[%3d..%-3d]\n",						\
																																																			$ascii_char,		$bytes,	$rel,		$cube, i$dst, o$dst,	$cube, i$src, o$src );				AvDBUG_PUSH( aString, cS);
	//	#define								dBUG_bSHIFT_i(					$cubeS,	i$,							$cube,		o$,									$ascii_char 	)			cS =sprintf( aString,	"\r%c\t\t\t	%s[ %d ]	= %s[ %d ];\n", $ascii_char, $cube, i$, $cube, o$ );							AvDBUG_PUSH( aString, cS);
	//														bytes	shift		src		src index			src out-dex	dst			dst index			dst out-dex			op symbol
		#define dBUG_hiCAST_1F1_post( $i)		dBUG_hiCAST(	post_q,					$i,				izM,			"cubeZ",    	Ox[	$i	],		Ox[	inM ]-1			)
		#define dBUG_hiCAST_1F1_post_i( $i)		dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cubeZ",    	pqZ-cubeZ-Q[ $i ],	pqZ-cubeZ-1			)
		#define dBUG_hiCAST_1F2L_post( $i)		dBUG_hiCAST(	post_q,					$i,				zc0,			"cube0",    	Ox[	$i	],		Ox[	ix1 ]-1			)
		#define dBUG_hiCAST_1F2L_post_i($i)		dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cube0",    	pq0-cube0-Q[ $i ],	pq0-cube0-1			)
		#define dBUG_hiCAST_1F2H_post( $i)		dBUG_hiCAST(	post_q,					$i,				izM,			"cubeZ",    	16 +lpZ_q,		15 +lpZ_q +post_q		)		
		#define dBUG_hiCAST_1F2H_post_i($i)		dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cubeZ",    	pqZ-cubeZ-Q[ $i ],	pqZ-cubeZ-1			)
		#define dBUG_hiCAST_1F2S_post0( $i )		dBUG_hiCAST(	post0_q,					$i,				zc0,			"cube0",    	Ox[	$i	],		Ox[	$i ]+post0_q-1		)
		#define dBUG_hiCAST_1F2S_post0_i($i)		dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cube0",    	pq0-cube0-Q[ $i ],	pq0-cube0-1			)
		#define dBUG_hiCAST_1F2S_postZ( $i )		dBUG_hiCAST(	postZ_q,					$i,				izM,			"cubeZ",    	16,				15	+postZ_q			)
		#define dBUG_hiCAST_1F2S_postZ_i($i)		dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cubeZ",    	pqZ-cubeZ-Q[ $i ],	pqZ-cubeZ-1			)

		#define dBUG_hiCAST_1F3_post0( $i )  		dBUG_hiCAST(	post0_q,					$i,				zc0,			"cube0",    	Ox[	$i	],		Ox[	ix1 ]-1			)
		#define dBUG_hiCAST_1F3_post0_i($i)		dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cube0",    	pq0-cube0-Q[ $i ],	pq0-cube0-1			)
		#define dBUG_hiCAST_1F4_post0( $i )		dBUG_hiCAST_1F3_post0( $i )
		#define dBUG_hiCAST_1F4_post0_i($i)		dBUG_hiCAST_1F3_post0_i($i)

		#define dBUG_hiCAST_1F3LM_post1($i)  	lp1_q	=	O[	ixM ]	-	O[	ix1 ];\
											dBUG_hiCAST(	post1_q,					$i,				izM,			"cube1",    	16 +lp1_q,		15 +lp1_q +post1_q		)	
		#define dBUG_hiCAST_1F3LM_post1_i($i)	dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cube1",    	pq1-cube1-Q[ $i ],	pq1-cube1-1			)
		#define dBUG_hiCAST_1F3MH_post1($i)  	dBUG_hiCAST(	post1_q,					$i,				izM,			"cube1",    	16,				15 +post1_q			)
		#define dBUG_hiCAST_1F3MH_post1_i($i)	dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cube1",    	pq1-cube1-Q[ $i ],	pq1-cube1-1			)
		#define dBUG_hiCAST_1F3M_post1($i)  	dBUG_hiCAST(	post1_q,					$i,				izM,			"cube1",    	16,				15 +post1_q			)
		#define dBUG_hiCAST_1F3M_post1_i($i)	dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cube1",    	pq1-cube1-Q[ $i ],	pq1-cube1-1			)

		#define dBUG_hiCAST_1F3_postZ( $i )  		dBUG_hiCAST(	postZ_q,					$i,				izM,			"cubeZ",    	16,				15 +postZ_q			)
		#define dBUG_hiCAST_1F3_postZ_i( $i )		dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cubeZ",    	pqZ-cubeZ-Q[ $i ],	pqZ-cubeZ-1			)

		#define dBUG_hiCAST_1F4LM_post1($i)	dBUG_hiCAST_1F3LM_post1($i)
		#define dBUG_hiCAST_1F4LM_post1_i($i)	dBUG_hiCAST_1F3LM_post1_i($i)
		#define dBUG_hiCAST_1F4M_post1($i)		dBUG_hiCAST(	post1_q,					$i,				iz1,			"cube1",    	16,				15 +post1_q			)
		#define dBUG_hiCAST_1F4M_post1_i($i)	dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cube1",    	pq1-cube1-Q[ $i ],	pq1-cube1-1			)

		#define dBUG_hiCAST_1F4_postX($i)  		dBUG_hiCAST(	postX_q,					$i,				izX,			"cubeX",    	16,				15 +postX_q			)
		#define dBUG_hiCAST_1F4_postX_i($i)		dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cubeX",    	pqX-cubeX-Q[ $i ],	pqX-cubeX-1			)

		#define dBUG_hiCAST_1F4M_postY($i)  	dBUG_hiCAST(	postY_q,					$i,				izY,			"cubeY",    	16,				15 +postY_q			)
		#define dBUG_hiCAST_1F4M_postY_i($i)	dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cubeY",    	pqY-cubeY-Q[ $i ],	pqY-cubeY-1			)
		#define dBUG_hiCAST_1F4MH_postY($i)  	dBUG_hiCAST(	postY_q,					$i,				izM,			"cubeY",    	16,				15 +postY_q			)
		#define dBUG_hiCAST_1F4MH_postY_i($i)	dBUG_hiCAST_i(	Q[$i],					$i,				H[ $i ],		"cubeY",    	pqY-cubeY-Q[ $i ],	pqY-cubeY-1			)

		#define dBUG_hiCAST_1F4_postZ( $i )		dBUG_hiCAST_1F3_postZ( $i )
		#define dBUG_hiCAST_1F4_postZ_i( $i )		dBUG_hiCAST_1F3_postZ_i( $i )

		#define dBUG_bSHIFT_1F1_UP			dBUG_bSHIFT(	hp_q,	rel_q,			O[	ixH	],		CS -1,		"cube",    	Ox[	ixH ],		CSZ	-1,				175	);
		#define dBUG_bSHIFT_1F1_DN			dBUG_bSHIFT(	hp_q,	rel_q,			O[	ixH	],		CS -1,		"cube",    	Ox[	ixH ],		CSZ	-1,				174	);
		#define dBUG_bSHIFT_1F2L_UP			dBUG_bSHIFT(	hp0_q,	rel_q,			O[	ixH	],		O[ ix1	] -1,	"cube0",    	Ox[	ixH ],		Ox[	ix1 ] -1,		175	);
		#define dBUG_bSHIFT_1F2L_DN			dBUG_bSHIFT(	hp0_q,	rel_q,			O[	ixH	],		O[ ix1	] -1,	"cube0",    	Ox[	ixH ],		Ox[	ix1 ] -1,		174	);
		#define dBUG_XLOAD_1F2H_lp1			dBUG_XLOAD(	lp1_q,			"cube",	O[	ix1 ],		O[ ixM	] -1,	"cubeZ",    	16,				15 +lp1_q			)
		#define dBUG_XLOAD_1F2H_hpZ			dBUG_XLOAD(	hpZ_q,			"cube",	O[	ixH	],		CS- 1,		"cubeZ",    	16 +lp1_q +post_q,	CSZ	-1				)
		#define dBUG_XLOAD_1F2S_hpZ			dBUG_XLOAD(	hpZ_q,			"cube",	O[	ixH	],		CS -1,		"cubeZ",    	16 +postZ_q,		CSZ	-1				)
		#define dBUG_XLOAD_1F2L_tota1		dBUG_XLOAD(	tota1_q,			"cube",	O[	ix1 ],	 	CS -1,		"cubeZ",    	16,				CSZ -1				)

		#define dBUG_XLOAD_1F3_lp1			dBUG_XLOAD(	lp1_q,			"cube",	O[	ix1 ],		O[ ixM	] -1,	"cube1",    	16,				15 +lp1_q			)
		#define dBUG_XLOAD_1F3MH_hp1		dBUG_XLOAD(	hp1_q,			"cube",	O[	ixH	],		O[ ixZ	] -1,	"cube1",   	16 +post1_q,		CS1-1				)
		#define dBUG_XLOAD_1F3MH_hpZ  		dBUG_XLOAD(	hpZ_q,			"cube",	O[	ixZ ],		CS -1,		"cubeZ",    	16,				CSZ-1				)
		#define dBUG_XLOAD_1F3M_hpZ  		dBUG_XLOAD(	hpZ_q,			"cube",	O[	ixH	],		CS -1,		"cubeZ",    	16 +postZ_q,		CSZ-1				)

		#define dBUG_XLOAD_1F4MH_hpY  		dBUG_XLOAD(	hpY_q,			"cube",	O[	ixZ ],		CS -1,		"cubeY",    	16,				CSY-1				)
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
		#define dBUG_hiCAST_1F4_postX( $i )
		#define dBUG_hiCAST_1F4_postX_i( $i )
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
	#ifdef DEBUG_SvCOMMIT_L3		//	paranoid integrity checks which are silent until there's a problem
		#define dBUG_1F3_TENA_ZC							if( ixM >= iz1){	printf( lightning );	printf("!	ixM( %d ) must be less-than iz1( %d ).  invalid value for tena_zc (%d) within subcase 1F3 of %s: %s line %lld \n",		ixM,	iz1,	tena_zc, __FUNCTION__, __FILE__, __LINE__ );	}	\
														if( izM <= ix1){	printf( lightning );	printf("!	izM( %d ) must be greater-than ix1( %d ).  invalid value for tena_zc (%d) within subcase 1F3 of %s: %s line %lld \n",	izM,	ix1,	tena_zc, __FUNCTION__, __FILE__, __LINE__ );	}	\

		#define dBUGmxB4( $X )	_print_mx( $X,	ix1, izZ );	
		#define dBUGmxEO( $X )	_print_mx( $X,	ix1, izZ );/*	_init_mx(); NO */
													//	if( rel_q		!=	post_q -pre_q		){ printf( "\r!	_sv_commit(): 	( rel_q = Ox[ inM ] - O[ inM ]	)==%d should be equal to:\n			( rel_q = post_q -pre_q	)==%d\n\n",	\
																												rel_q,						post_q -pre_q );	}
		#define dBUG_SvCUR($CS, $VARNAME)				if( $CS<16){ printf("\n!	%s< 16 ( %d )	%s line %lld \n",			$VARNAME, $CS, __FILE__, __LINE__ );	exit(-1);	}
		#define dBUGrackCALL($FRAG_LEV)					if( ixM		==	0xFF			){						printf("\n!	_sv_commit(%d):	nothing to commit\n",									$FRAG_LEV);	goto _end;	}\
			STRLEN	CS_check;							if( pSv0    	!=	AvARRAY( avICE )	){ pSv0=AvARRAY( avICE );	printf( "\r!	_sv_commit(%d): 	(SV**) \"pSv0)\" was out of sync with *AvARRAY( avICE )!\n",	$FRAG_LEV);	}\
			SV*		sv_check 	= *(pSv0 +iC);				if( &*sv   	!=	&*sv_check		){ sv=sv_check;			printf( "\r!	_sv_commit(%d): 	(SV*) \"sv\" was out of sync with *( AvARRAY( avICE ) +iC )!\n",	$FRAG_LEV);	}\
			ui08*	cube_check	= SvPVbyte( sv, CS_check );	if( cube		==	NULL			){ cube=cube_check;		printf("\n!	_sv_commit(%d):	(unsigned char*) cube was NULL!\n",						$FRAG_LEV);	}\
													else	if( &*cube	!=	&*cube_check		){ cube=cube_check;		printf( "\r!	_sv_commit(%d): 	(char *) \"cube\" was out of sync with SvPVbyte( ... )! \n",		$FRAG_LEV);	}\
														if( CS    		!=	CS_check			){ CS=CS_check;			printf( "\r!	_sv_commit(%d): 	(STRLEN) \"CS\" was out of sync with SvPVbyte( ... )!\n",		$FRAG_LEV);	}\
			char		zc_check= zcOf( cube);					if( zc_check	!=	zc				){ zc= zc_check;			printf( "\r!	_sv_commit(%d): 	(char) \"zc\" was out of sync with zcOf( ... )!\n",				$FRAG_LEV);	}
	#else
		#define dBUG_1F3_TENA_ZC
		#define dBUGmxB4( $X )
		#define dBUGmxEO( $X )
		#define dBUG_SvCUR($CS, $VARNAME )
		#define dBUGrackCALL($FRAG_LEV)
	#endif
// the following(4) macros are fragment-generating code blocks shared within _sv_commit() by main cases 1F2S, 1F3 and 1F4.

/*######	CREATE:	HIGH CUBE [iC+1] 	######		(CASE 1F3)		######							*/
		/*	[iC+Z]:	HIGH CUBE		SUBCASE 1: 	HIGHPASS				*/
#define NEW_CUBE_Z_AS_HIGHPASS(		$dBUG_XLOAD)				hpZ_q=CS-O[ ixZ ];					\
														CSZ=16+	hpZ_q;								\
			pqZ=( cubeZ	= SvPVbyte_nolen(	svZ = newSVpvz(	CSZ |0x6 ) ) )+16;	SvCUR_set( svZ, CSZ );			dBUG_SvCUR(	CSZ,	"CSZ"	);	\
																									*( (ui64*) cubeZ+1 ) = *( (ui64*) cube +1 );	/* set Epsilon of high cube	(there is a displacement, so Epsilon of pre-op cube is conserved)	*/\
			switch(	zcZ		){		SwCASE_LOWPASS_1I(	*( (ui64*)( cube +I[	ixZ ] ) ),						*( (ui64*) cubeZ )	);	 }			\
								/*	^inline lowpass		^high passthrough src							^lowpass output	*/				\
			if(		hpZ_q )	{		XLOAD(	pqZ,	O[ ixZ ],	hpZ_q,									$dBUG_XLOAD );					dBUG_TRACE4x4;	\
							}	/*	^crossload (hpZ_q) high-pass bytes from *(cube+O[ ixZ ] ) to *pqZ		*/


		/*	[iC+Z]:	HIGH CUBE		SUBCASE 2: 	MODS x HIGHPASS		*/
#define NEW_CUBE_Z_AS_MODSxHPASS(	$dBUG_hiCAST, $dBUG_hiCAST_i,			$dBUG_XLOAD	)	\
																hpZ_q=CS-O[ ixH ];						\
			postZ_q	=	Ox[	inM ]	-	Ox[	ixZ ];		CSZ=16+	hpZ_q + postZ_q;						\
			pqZ=( cubeZ	= SvPVbyte_nolen(	svZ = newSVpvz(	CSZ |0x6 ) ) )+16;	SvCUR_set( svZ, CSZ );			dBUG_SvCUR(	CSZ,	"CSZ"	);	\
			postZ_xc	= 		izM		-		ixZ;			\
			preZ_xc	= 		icO		-	I[	ixZ ];		\
			relZ_c	= 		postZ_xc	-		preZ_xc;		\
		/*	hpZ_i	=	I[	ixZ ] 	-		relZ_c;	*/	\
			hpZ_c	=		zc		-		icO;			\
			\
			if( hpZ_c ){	enXhp	=	postZ_xc| ( hpZ_c<< 3 );					hpZ_i = I[ ixZ ] -relZ_c;								*( (ui64*) cubeZ+1 ) = *( (ui64*) cube +1 );	/* Epsilon of [iC] is conserved */	\
				switch(	enXhp	){	SwCASE_LPXOVER_10Y( *( (ui64*)( cube +	hpZ_i ) ), 	*( (ui64*)( H +ixZ ) ),	*( (ui64*) cubeZ )  )  	}			dBUG_TRACE4x1		\
			}else{				/*	^lowpass crossover wye	 ^high passthrough, shifted	^low inclusion src		^wye output		*/	*( (ui64*) cubeZ+1 ) = E[ izM ];			/* Epsilon changed			*/	\
				switch(	postZ_xc ){	SwCASE_LOWPASS_1I(							*( (ui64*)( H +ixZ ) ),	*( (ui64*) cubeZ )	)	}			\
				}				/*	^lowpass inline assignment						^definitive src			^low passthrough	*/	\
			if(		postZ_q )	{		iCEpACK( pqZ,	ixZ, izM, inM,										$dBUG_hiCAST, $dBUG_hiCAST_i );	dBUG_TRACE4x2;	\
							}	/*	^re-pack modified q-data vectors ixZ..izM to cubeZ[ 16..16+postZ_q-1 ]	*/									\
			if(		hpZ_q )	{		XLOAD(	pqZ,	O[ ixH ],		hpZ_q,								$dBUG_XLOAD );					dBUG_TRACE4x4;	\
							}	/*	^crossload (hpZ_q) high-pass bytes from *(cube+O[ ixH ] ) to *pqZ		*/


/*######	UPDATE:	LOW CUBE [iC+0] 	######		(CASE 1F3)		######							*/
		/*	[iC+0]:	LOW CUBE		SUBCASE 1: 	LOWPASS				*/
#define MOD_CUBE_0_AS_LPASS( 		ix$ )	/*	if( ixM >zc0 ){	*/\
				switch(		zc0 ){	SwCASE_LOWPASS_1IS(	*( (ui64*) cube0 )	)		}					\
				if( CS != O[	ix$ ] ){			SvCUR_set(	sv,	O[	ix$ ] );	cube0[	O[	ix$ ] ]=0;			dBUG_SvCUR(	O[	ix$], sprintf( "O[%s]", #ix$) );	}\
		/*	} */


		/*	[iC+0]:	LOW CUBE		SUBCASE 2: 	LOWPASS x MODS			*/
#define MOD_CUBE_0_AS_LPASSxMODS( ix$,		$dBUG_hiCAST, $dBUG_hiCAST_i	)	\
				if( CS <  Ox[	ix$ ] ){ cube0  =	SvGROW(	sv,	Ox[	ix$ ] +1 );							\
											SvCUR_set(	sv,	Ox[	ix$ ] );	cube0[	Ox[	ix$ ] ]=0;			dBUG_SvCUR(	Ox[	ix$ ], sprintf( "O[%s]", #ix$)	);	}	\
			else	if( CS != Ox[	ix$ ] ){			SvCUR_set(	sv,	Ox[	ix$ ] );	cube0[	Ox[	ix$ ] ]=0;			dBUG_SvCUR(	Ox[	ix$ ], sprintf( "O[%s]", #ix$)	);	}	\
			\
			pq0 =cube0 +O[	ixM	];			post0_xc	= zc0 - ixM;										\
						lpXen	=	icI |(	post0_xc<< 3 );											\
			switch(		lpXen	){	SwCASE_LPXOVER_01T( *( (ui64*) H ),									*( (ui64*) cube0)  );  }							\
								/*	^lowpass crossover tee	^high inclusion src								^low passthrough / tee output	*/				\
					post0_q		=	Ox[	ix$	]	-	Ox[ 	ixM	];																					\
			if(		post0_q )	{		iCEPACK( pq0, 	ixM, zc0, ix$,										$dBUG_hiCAST, $dBUG_hiCAST_i );	dBUG_TRACE0x1;	\
							}	/*	^re-pack modified q-data vectors ixM..zc0 to cube0[ O[ ixM ]..O[ zc0 ] ]	*/
