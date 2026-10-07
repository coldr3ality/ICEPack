/*	THE (3) LEVELS Of DEBUG:
	L1:	audit nominal activity
	L2:	audit nominal activity (more verbosely)
	L3:	silently check integrity, reporting only errors
	*/

/*	WARNING.  Most of these log new SV's to AV* avDBUG, causing memory runaway.
	It helps to use the version of "AvDBUG_PUSH" which just prints to screen, but it's much slower.
	*/
	#define	ReBAL_ENABLE				//		enables cube chaining during dwell loop and payload redistribution via _sv_commit_nx().
	#define	STDOUT_ENABLE				//		don't capture and hold debug info in (AV*) avDBUG, just dump it to screen

//	#define		DEBUG_SvCOMMIT_L0		//		MkIn & MkOut
//	#define		DEBUG_SvCOMMIT_L0X	//		xcª_OVERRUN_PROTECT message
	//	#define	DEBUG_SvCOMMIT_L1F	//		1X* and NX* ƒsub headers (utterly basic)
	//	#define	DEBUG_SvCOMMIT_L1		//		1X* and NX* ƒsub headers (basic)
//	#define		DEBUG_SvCOMMIT_L1X	//		1X* and NX* ƒsub headers

//	#define		DEBUG_SvCOMMIT_L2		//		PRIMOLOC, ANTELOC, INTERLOC, INTRaLOC, INTRaLOC1up, EPILOC markers
										//		bulk q-data operations (XLOAD, ICEPACK, ReFLOW) in terms of total ranges	(one line ea.)
	//	#define	DEBUG_SvCOMMIT_L2X	//		CoANTELOC, CoINTERLOC, ReINTERLOC, ReINTRaLOC
										//		bulk q-data operations (XLOAD, ICEPACK, ReFLOW) in terms of unit ranges	(multi-line)
	//	#define	DEBUG_SvCOMMIT_L2XX	//		bulk q-data operations (XLOAD, ICEPACK, ReFLOW) as atomic assignments	(many lines)
										//		simple Co***LOC ƒsub markers
//	#define		DEBUG_SvCOMMIT_L3		//		dBUGmx (_print_mx(...) )
	//	#define	DEBUG_SvCOMMIT_L4		//	?	audit SvCOMMIT bulk SV ops (NEW_CUBE_X_AS_MODSxHPASS etc.)
	//	#define	DEBUG_SvCOMMIT_L4	// mining for 1F4 triggers
//	#define		DEBUG_AvCOMMIT_L1		//		AvPOST, AvCUT _av_commit() schedule updates
	//	#define	DEBUG_AvCOMMIT_L2		//		explicit _av_commit() procedure
	//	#define	DEBUG_AvCOMMIT_L3		//	?
	//	#define	DEBUG_ACCESS_L0		//		multi-SV cube run Co****LOC case messages		?crashing?
//	#define		DEBUG_ACCESS_L1
	//!//	#define	DEBUG_ACCESS_L2		//	!	location and relocation events, any time cube focus changes
		/*	I believe _excludes() is crashing when AvDBUG_PRINT is set to log errors as SVs in global (SV*) avDBUG[],
			specifically when the cube_err[8] string is passed to sprintf, and I think it has to do with the value of *Edge( cubeΩ ).	*/

	//	#define	DEBUG_ACCESS_L2X		//		args
										//		[T]RACK
	//	#define	DEBUG_ACCESS_L2XX		//		co-location sub-functional control logic branch of each argument (ƒSUB)
	//	#define	DEBUG_ACCESS_L3		//		sanity checks and integrity validations for testing brave architectural changes
//		#define	DEBUG_ACCESS_L4		//		check all SvCUR_set() calls before & after
//	#define		DEBUG_TRUTH_L1
//	#define		DEBUG_TRUTH_L3
	//	#define	DEBUG_DeICE


#if	defined( DEBUG_SvCOMMIT_L0 )	||	defined( DEBUG_SvCOMMIT_L1)	||	defined( DEBUG_SvCOMMIT_L2) 	||	defined( DEBUG_SvCOMMIT_L3)	||	defined( DEBUG_SvCOMMIT_L4)	\
								||	defined( DEBUG_AvCOMMIT_L1)	||	defined( DEBUG_AvCOMMIT_L2)	||	defined( DEBUG_AvCOMMIT_L3)	\
								||	defined( DEBUG_ACCESS_L1)	||	defined( DEBUG_ACCESS_L2)	||	defined( DEBUG_ACCESS_L3)	||	defined( DEBUG_ACCESS_L4)	\
								||	defined( DEBUG_TRUTH_L1)		||	defined( DEBUG_TRUTH_L2)		||	defined( DEBUG_TRUTH_L3)
	#define		DEBUG
	#define		dBUGavCLR				av_clear( avDBUG );
	#ifdef		STDOUT_ENABLE
		#define	dBUG_0A( $str)						printf( $str);
		#define	dBUG_1A( $str, $1)						printf( $str, $1);
		#define	dBUG_2A( $str, $1, $2)					printf( $str, $1, $2);
		#define	dBUG_3A( $str, $1, $2, $3)				printf( $str, $1, $2, $3);
		#define	dBUG_4A( $str, $1, $2, $3, $4)			printf( $str, $1, $2, $3, $4 );
		#define	dBUG_5A( $str, $1, $2, $3, $4, $5)			printf( $str, $1, $2, $3, $4, $5);
		#define	dBUG_6A( $str, $1, $2, $3, $4, $5, $6)		printf( $str, $1, $2, $3, $4, $5, $6);
		#define	dBUG_7A( $str, $1, $2, $3, $4, $5, $6, $7)	printf( $str, $1, $2, $3, $4, $5, $6, $7);
		#define	AvDBUG_PUSH(			$str, $len	)	printf( $str );
		#define	AvDBUG_RESERVATION(	$str, $len, $i )	printf( $str );
	#else
		#define	dBUG_0A( $str)						{	cS=sprintf( $str);						av_push( avDBUG, newSVpvn( $str, cS) );	}
		#define	dBUG_1A( $str, $1)						{	cS=sprintf( $str, $1);					av_push( avDBUG, newSVpvn( $str, cS) );	}
		#define	dBUG_2A( $str, $1, $2)					{	cS=sprintf( $str, $1, $2);					av_push( avDBUG, newSVpvn( $str, cS) );	}
		#define	dBUG_3A( $str, $1, $2, $3)				{	cS=sprintf( $str, $1, $2, $3);				av_push( avDBUG, newSVpvn( $str, cS) );	}
		#define	dBUG_4A( $str, $1, $2, $3, $4)			{	cS=sprintf( $str, $1, $2, $3, $4 );			av_push( avDBUG, newSVpvn( $str, cS) );	}
		#define	dBUG_5A( $str, $1, $2, $3, $4, $5)			{	cS=sprintf( $str, $1, $2, $3, $4, $5);		av_push( avDBUG, newSVpvn( $str, cS) );	}
		#define	dBUG_6A( $str, $1, $2, $3, $4, $5, $6)		{	cS=sprintf( $str, $1, $2, $3, $4, $5, $6);		av_push( avDBUG, newSVpvn( $str, cS) );	}
		#define	dBUG_7A( $str, $1, $2, $3, $4, $5, $6, $7)	{	cS=sprintf( $str, $1, $2, $3, $4, $5, $6, $7);	av_push( avDBUG, newSVpvn( $str, cS) );	}
		#define	AvDBUG_PUSH(			$str, $len )	av_push( avDBUG, newSVpvn( $str, $len ) );
		#define	AvDBUG_RESERVATION(	$str, $len, $i )	SvREFCNT_inc( *( AvARRAY( avDBUG) +$i ) =newSVpvn( $str, $len ) );
	#endif
#else		/*	DEBUG DISABLED								*/
	#define		dBUG_0A( $str)
	#define		dBUG_1A( $str, $1)
	#define		dBUG_2A( $str, $1, $2)
	#define		dBUG_3A( $str, $1, $2, $3)
	#define		dBUG_4A( $str, $1, $2, $3, $4)
	#define		dBUG_5A( $str, $1, $2, $3, $4, $5)
	#define		dBUG_6A( $str, $1, $2, $3, $4, $5, $6)
	#define		dBUG_7A( $str, $1, $2, $3, $4, $5, $6, $7)
	#define		AvDBUG_PUSH(			$str, $len )	printf( $str );
	#define		AvDBUG_RESERVATION(	$str, $len, $i )	printf( $str );
	#define		dBUGavCLR			/*	av_clear( avDBUG );	*/
#endif

#ifdef DEBUG_ACCESS_L4			//	check integrity
	#define dBUG_SvCUR($SV, $CS )	if( $CS<16 || $CS >144){		printf(	"\n!	SvCUR_set( %s, !%s:%lld )	%s line %d\n", #$SV, #$CS, $CS,  __FILE__, __LINE__ );	exit_code=99; return;	}
	#define dBUG$xeqE( $x )  				if( $x< E[ u ] ){		cS=	sprintf( aString, "\r!	CoINTRaLOC( x: %d ): arg #%d is in descending order!\n", $x, a ); 	AvDBUG_PUSH( aString, cS ); }
#else
	#define dBUG_SvCUR($SV, $CS )
	#define dBUG$xeqE( $x )
#endif
