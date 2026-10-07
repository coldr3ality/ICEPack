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
#include	"_AvSEQ.h"
#include	"access_extern.h"

#ifdef DEBUG_AvCOMMIT_L2		//	verbose audit of nominal activity	
	long long int isc;
	#define dBUGiniA		{		cS=sprintf( aString, "\n starting in ascending mode at step #%lld/%lld for %lld iterations\n\n",   	asc, zsc, juke);		AvDBUG_PUSH( aString, cS );	}
	#define dBUGiniD		{		cS=sprintf( aString, "\n starting in descending mode at step #%lld/%lld for %lld iterations\n\n", 	dsc, zsc, juke);		AvDBUG_PUSH( aString, cS );	}
	#define dBUGriniA		{		cS=sprintf( aString, "\n switching to ascending mode at step #%lld/%lld for %lld iterations\n\n",	asc, zsc, juke	);	AvDBUG_PUSH( aString, cS );	}
	#define dBUGriniD		{		cS=sprintf( aString, "\n switching to descending mode at step #%lld/%lld for %lld iterations	line %d\n\n",	dsc, zsc, juke, __LINE__	);	AvDBUG_PUSH( aString, cS );	}

																																																								
	#define dBUGinsA  	{		cS=sprintf( aString, "\r+I+	avICE[ %4lld ]	= SV%-4lld			asc: %lld/%lld	juke: %lld	src/dst: %lld/%lld\n",				dst-Aº-1,		rSeq_iR[asc]-$insA, asc,	zsc, juke, src-Aº, dst-Aº	); 	AvDBUG_PUSH( aString, cS );	}
	#define dBUGcutA  	{		cS=sprintf( aString, "\r-X-	avICE[ %4lld ]	= NULL				asc: %lld/%lld	juke: %lld	src/dst: %lld/%lld\n",				src-Aº, 				 	 	asc,	zsc, juke, src-Aº, dst-Aº	); 	AvDBUG_PUSH( aString, cS );	}
	#define dBUGpmvA  	{/*<<_*/	cS=sprintf( aString, "\r%c%c_	avICE[ %4lld ]	=	avICE[ %4lld ];		asc: %lld/%lld	juke: %lld	src/dst: %lld/%lld\n",	174,174, 		dst-Aº-1, 	src-Aº-1,	 	 	asc,	zsc, juke, src-Aº, dst-Aº	); 	AvDBUG_PUSH( aString, cS );	}
	#define dBUGlocA  	{		cS=sprintf( aString, "\r|%c%c	avICE[ %4lld ]	=	avICE[ %4lld ]; [T]	asc: %lld/%lld	juke: %lld	src/dst: %lld/%lld\n",	174,174,		dst-Aº, 		$srcA,  			asc,	zsc, juke, src-Aº, dst-Aº	); 	AvDBUG_PUSH( aString, cS );	}
																																																								
	#define dBUGinsD  	{		cS=sprintf( aString, "\r+I+	avICE[ %4d ]	= SV%-4d			dsc: %lld/%lld	juke: %lld	src/dst: %lld/%lld\n",			1+	dst-Aº,		rSeq_iR[dsc]+1,	dsc,	zsc, juke, src-Aº, dst-Aº	);   	AvDBUG_PUSH( aString, cS );	}
	#define dBUGcutD  	{		cS=sprintf( aString, "\r-X-	avICE[ %4d ]	= NULL				dsc: %lld/%lld	juke: %lld	src/dst: %lld/%lld\n",				src-Aº,						dsc,	zsc, juke, src-Aº, dst-Aº	); 	AvDBUG_PUSH( aString, cS );	}
	#define dBUGpmvD  	{/*_>>*/	cS=sprintf( aString, "\r_%c%c	avICE[ %4d ]	=	avICE[ %4d ];		dsc: %lld/%lld	juke: %lld	src/dst: %lld/%lld\n",	175,175,	1+	dst-Aº,		1+src-Aº,  		dsc,	zsc, juke, src-Aº, dst-Aº	); 	AvDBUG_PUSH( aString, cS );	}
	#define dBUGlocD  	{		cS=sprintf( aString, "\r%c%c|	avICE[ %4d ]	=	avICE[ %4d ]; [T]	dsc: %lld/%lld	juke: %lld	src/dst: %lld/%lld\n",	175,175,		dst-Aº-$insD,	$srcD,  			dsc,	zsc, juke, src-Aº, dst-Aº	); 	AvDBUG_PUSH( aString, cS );	}
																																																								
	#define dBUGlocDx	{		cS=sprintf( aString, "\r_%c|	avICE[ %4d ]	=	avICE[ %4d ]; [Tx]	dsc: %lld/%lld	\n", 							175,			$dstD, 		$srcD,			dsc,	zsc					);	AvDBUG_PUSH( aString, cS );	}
	#define dBUGpmvE	{		cS=sprintf( aString, "\r__%c	avICE[ %4d ]	=	avICE[ %4d ];		dsc: %lld/%lld	juke: %lld	src/dst: %lld/%lld\n",	175, 	1+	dst-Aº,	1+	src-Aº, 	 		dsc,	zsc, juke, src-Aº, dst-Aº	); 	AvDBUG_PUSH( aString, cS );	}
																																																									#define dBUG_AvCOMMIT_SCHED_PRE	char dString[8448];	\
	{	cS =sprintf( dString,	"\ncommit schedule (pre process):\n	#\t\t");													\
												for( isc=0; isc<=zsc; ++isc )	cS+=sprintf( dString +cS, "#%-7lld", 		isc ); 	\
		cS+=sprintf( dString +cS, "\n	rSeq_iR:\t"	);	for( isc=0; isc<=zsc; ++isc )	cS+=sprintf( dString +cS, " %-7lld",	rSeq_iR[ 	isc ]	);	\
		cS+=sprintf( dString +cS, "\n	rSeqIns:\t"	);	for( isc=0; isc<=zsc; ++isc )	cS+=sprintf( dString +cS, " %-7lld",	rSeqIns[ 	isc ]	);	\
		cS+=sprintf( dString +cS, "\n	rSeqCut:\t"	);	for( isc=0; isc<=zsc; ++isc )	cS+=sprintf( dString +cS, " %-7lld",	rSeqCut[	isc ]	);	\
		cS+=sprintf( dString +cS, "\n	rSeqSrc:\t"	);	for( isc=0; isc<=zsc; ++isc )	cS+=sprintf( dString +cS, " %-7lld",	rSeqSrc[	isc ]	);	\
		cS+=sprintf( dString +cS, "\n	rSeqDst:\t"	);	for( isc=0; isc<=zsc; ++isc )	cS+=sprintf( dString +cS, " %-7lld",	rSeqDst[	isc ]	);	\
		cS+=sprintf( dString +cS, "\n\n");				AvDBUG_PUSH( dString, cS );	\
	}
	#define dBUG_AvCOMMIT_SCHED_POST	\
	{	cS =sprintf( aString,    	"\ncommit schedule (post process):\n	#\t\t");													\
												for( isc=0; isc<=zsc; ++isc ) cS+=sprintf( aString +cS, "#%-7lld", 			isc );	\
		cS+=sprintf( aString +cS, "\n	rSeq_iR:\t"	);	for( isc=0; isc<=zsc; ++isc ) cS+=sprintf( aString +cS, " %-7lld",	rSeq_iR[ 	isc ]	);	\
		cS+=sprintf( aString +cS, "\n	rSeqIns:\t"	);	for( isc=0; isc<=zsc; ++isc ) cS+=sprintf( aString +cS, " %-7lld",	rSeqIns[ 	isc ]	);	\
		cS+=sprintf( aString +cS, "\n	rSeqCut:\t"	);	for( isc=0; isc<=zsc; ++isc ) cS+=sprintf( aString +cS, " %-7lld",	rSeqCut[	isc ]	);	\
		cS+=sprintf( aString +cS, "\n	rSeqSrc:\t"	);	for( isc=0; isc<=zsc; ++isc ) cS+=sprintf( aString +cS, " %-7lld",	rSeqSrc[	isc ]	);	\
		cS+=sprintf( aString +cS, "\n	rSeqDst:\t"	);	for( isc=0; isc<=zsc; ++isc ) cS+=sprintf( aString +cS, " %-7lld",	rSeqDst[	isc ]	);	\
		cS+=sprintf( aString +cS, "\n\n");				AvDBUG_PUSH( aString, cS );	\
	}
#else
	#define dBUGiniA
	#define dBUGiniD
	#define dBUGriniA
	#define dBUGriniD

	#define dBUGinsA
	#define dBUGcutA
	#define dBUGpmvA
	#define dBUGlocA
	#define dBUGinsD
	#define dBUGcutD
	#define dBUGpmvD
	#define dBUGlocD
	#define dBUGlocDx
	#define dBUGpmvE
	#define dBUG_AvCOMMIT_SCHED_PRE
	#define dBUG_AvCOMMIT_SCHED_POST
#endif
#ifdef DEBUG_AvCOMMIT_L3		//	paranoid integrity checks which are silent until there's a problem
	#define dBUGdscDIR	if(dsc<0 || dsc>zsc)	{	cS=sprintf( aString,		"\n!	dsc is out of bounds 0..%lld (%lld)\n", zsc, dsc);		AvDBUG_PUSH( aString, cS );	\
											break;	\
										}			\
						if(src >dst )		{	cS=sprintf( aString,		"\n!	going in the wrong direction in \"_desc\" block pf function %s, file %s line %d	src( %lld ) > dst( %lld ), step #%d/%d;	rSeqCut[%lld]: %d	rSeqSrc[%lld]: %d	rSeqDst[%lld]: %d\n",	\
																									__FUNCTION__, __FILE__, __LINE__,	src - Aº, dst -Aº,	dsc, zsc,		dsc, rSeqCut[dsc],	dsc, rSeqSrc[dsc],	dsc, rSeqDst[dsc]		);	AvDBUG_PUSH( aString, cS );		\
										/*	if( -pmo< src-Aº )	exit_code=1;	*/	\
											break;	\
										}
	#define dBUG_PMv( $LBL)  if( pmo< 0 )		{	cS=sprintf( aString,		"\n!	\"pmo\" is negative ( %lld ) in \"%s\" block of function %s, file %s line %d \n",				\
																					pmo,		$LBL,	__FUNCTION__, __FILE__, __LINE__		);	AvDBUG_PUSH( aString, cS );	\
										/*	if( -pmo< src-Aº ){ exit_code=1; } */		\
										}
	#define dBUGascDIR	if(asc<0 || asc>zsc)	{	cS=sprintf( aString, 	"\n!	asc is out of bounds 0..%lld (%lld)\n", zsc, asc);	AvDBUG_PUSH( aString, cS );	\
											break;	\
										}			\
						if(src< dst )		{	cS=sprintf( aString, 	"\n!	going in the wrong direction in \"_asce\" block of function %s, file %s line %d    	src( %lld ) < dst( %lld ), step #%d/%d;	rSeqCut[%lld]: %d	rSeqSrc[%lld]: %d	rSeqDst[%lld]: %d\n", 	\
																									__FUNCTION__, __FILE__, __LINE__,	src - Aº, dst -Aº,	asc, zsc,		asc, rSeqCut[asc],	asc, rSeqSrc[asc],	asc, rSeqDst[asc]		);	AvDBUG_PUSH( aString, cS );	\
										/*	if( -pmo< src-Aº )	exit_code=1;	*/	\
											break;	\
										}
//	if( zC!= AvFILLp( avICE ) ){zzC=( zC = AvFILLp( avICE ) )-1;	cS=sprintf( aString, 	"\n!	zC( %llu ) was out-of-sync with AvFILLp( avICE )( %llu )\n", zC, AvFILLp( avICE ) );	AvDBUG_PUSH( aString, cS );			}
//	if(dsc<0){											cS=sprintf( aString, 	"\n!	dsc( %llu )< 0\n", dsc );													AvDBUG_PUSH( aString, cS );	return;	}
#else
	#define dBUG_PMv( $LBL)
	#define dBUGdscDIR
	#define dBUGascDIR
#endif
