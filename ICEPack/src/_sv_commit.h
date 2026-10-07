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

	#include	"SwCASE_AB2IC_t0_inc.h"
//	#include	"SwCASE_AB2IC_t1_inc.h"
//	#include	"SwCASE_AB2IC_t2_inc.h"
	#include	"SwCASE_AB2IC_t3_inc.h"

#if defined( DEBUG_SvCOMMIT_L0 ) || defined( DEBUG_SvCOMMIT_L1) || defined( DEBUG_SvCOMMIT_L1X )
extern	size_t			avdbuginx_dmarkcase;
extern	unsigned short 	subcase;
#endif
#if defined( DEBUG_SvCOMMIT_L1 ) || defined( DEBUG_SvCOMMIT_L1X )
	#define dBUGnCª		ui64	iCª=iCI+nCª+3;
//	switch(	subcase << (   (cube#)  *8) &3 )
//		{
//		case 0:	cube is lowpass
//		case 1:	cube is lowpass + mods
//		case 2:	cube is mods + highpass
//		case 3:	cube is highpass
//		}
//									0.1	0.2	0.3	1.1	1.2	1.3	2.1		2.2	2.3	3.1		3.2		3.3
	#define dBUG_ABº		subcase|=( ixM< ix¹ )?	\
									1:	2;
	#define ƒSUBº_A		subcase|=	1;
	#define ƒSUBº_B		subcase|=		2;										
	#define ƒSUBº_C		subcase|=	1|	2;		
	#define ƒSUBº_D		subcase|=			4;	
	#define ƒSUBº_E		subcase|=	1|		4;
	#define ƒSUB¹_A		subcase|=				8;
	#define ƒSUB¹_B		subcase|=					0x10;									
	#define ƒSUB¹_C		subcase|=				8|	0x10;
	#define ƒSUB¹_D		subcase|=						0x20;
	#define ƒSUB¹_E		subcase|=				8|		0x20;
	#define ƒSUB²_A		subcase|=							0x40;
	#define ƒSUB²_B		subcase|=									0x80;
	#define ƒSUB²_C		subcase|=							0x40|	0x80;
	#define ƒSUB²_D		subcase|=									0x100;
	#define ƒSUB²_E		subcase|=							0x40|			0x100;
	#define ƒSUBΩ_A		subcase|=											0x200;
	#define ƒSUBΩ_B		subcase|=													0x400;
	#define ƒSUBΩ_C		subcase|=											0x200|	0x400;
	#define ƒSUBΩ_D		subcase|=															0x800;
	#define ƒSUBΩ_E		subcase|=											0x200|			0x800;
#else
	#define dBUGnCª
	#define ƒSUBº_A
	#define ƒSUBº_B
	#define ƒSUBº_C
	#define ƒSUBº_D
	#define ƒSUBº_E
	#define ƒSUB¹_A
	#define ƒSUB¹_B
	#define ƒSUB¹_C
	#define ƒSUB¹_D
	#define ƒSUB¹_E
	#define ƒSUB²_A
	#define ƒSUB²_B
	#define ƒSUB²_C
	#define ƒSUB²_D
	#define ƒSUB²_E
	#define ƒSUBΩ_A
	#define ƒSUBΩ_B
	#define ƒSUBΩ_C
	#define ƒSUBΩ_D
	#define ƒSUBΩ_E
#endif
#ifdef DEBUG_SvCOMMIT_L2
	/*		SvCOMMIT OP		glyph			bytes		dst		dst: 1st	dst: last		src		src: 1st	src: last			shift		*/
    #define	dBUG_XLOAD(	/*	X		*/		byte$,		dºcube,	dºq,		/*n/a*/		sºcube,	sÌ		/*n/a*/			/*n/a*/	)	o = dºq-dºcube;			\
			cS = sprintf( aString,	"\rX 	transfer (%3d) byte[s]:	%s[	\10	%3d..%-3d]	\10	=	%s[%3d..%-3d]	\10	\10	\10	\10	\10	\10	%s line %d\n",			\
												byte$,		#dºcube,	o,		o +byte$ -1,	#sºcube,	sÌ,		sÌ+byte$-1,		/*n/a*/	__FILE__,__LINE__);	AvDBUG_PUSH( aString, cS );
    #define	dBUG_ICEPACK(	/*	(251)			(q)	*/		dºcube,	dºq,		/*n/a*/		/**/ 	sÌ,		sÌz				/*n/a*/	)	o = dºq-dºcube;		q= Oª[ sÌz+1 ] - Oª[ sÌ ];	\
	if( sÌ<=sÌz){cS = sprintf( aString,	"\r%c	re-pack  (%3d) byte[s]:	%s[	\10	%3d..%-3d]	\10	=	vectors %3d..%-3d \n",						\
								251,				q,			#dºcube,  o,		 o+q-1,				sÌ, 		sÌz				/*n/a*/	);	AvDBUG_PUSH( aString, cS ); \
			}
    #define	dBUG_ReFLOW(		ascii$,			byte$,		ºcube,	dÌ0,		dÌz,			/**/		sÌ0,		sÌz,				rel$		)			\
			cS =sprintf( aString,	"\r%c	re-flow  (%3d) byte[s]:	%s[	\10	%3d..%-3d]	\10	=	%s[%3d..%-3d]	\10	\10	\10	\10	(%+3d) byte shift\n",	\
								ascii$,			byte$,		#ºcube,	dÌ0,		dÌz,			#ºcube,	sÌ0,		sÌz,				rel$		);	AvDBUG_PUSH( aString, cS);
																																										
    #define	dBUG_ReFLOW_A(	/*	(174),	*/		byte$,		ºcube, /*	ix,		ix+byte$-1, 	ºcube, 	iz,		iz+byte$-1*/		rel$		) 			\
			cS =sprintf( aString,	"\r%c	re-flow  (%3d) byte[s]:	%s[	\10	%3d..%-3d]	\10	=	%s[%3d..%-3d]	\10	\10	\10	\10	(%+3d) compaction\n",	\
								174,				byte$,		#ºcube,	ix,		ix+byte$-1,	#ºcube,	iz,		iz+byte$-1,		rel$		);	if( ix-iz != rel$ )  cS+=sprintf( aString+cS, "\r!!!	ERROR: src-dst offset (%+d) does not equal specified shift (%+d)!\n\n", ix-iz, rel$ );	\
																																	AvDBUG_PUSH( aString, cS);
    #define	dBUG_ReFLOW_D(	/*	(175),	*/		byte$,		ºcube, /*	ix-byte$,	ix-1,			ºcube,	iz-byte$,	iz-1		*/		rel$		)			\
			cS =sprintf( aString,	"\r%c	re-flow  (%3d) byte[s]:	%s[	\10	%3d..%-3d] 	\10	=	%s[%3d..%-3d]	\10	\10	\10	\10	(%+3d) expansion\n",	\
								175,				byte$,		#ºcube,	ix-byte$,	ix-1,			#ºcube,	iz-byte$,	iz-1,				rel$		);	if( ix-iz != rel$ )  cS+=sprintf( aString+cS, "\r!!!	ERROR: src-dst offset (%+d) does not equal specified shift (%+d)!\n\n", ix-iz, rel$ );	\
																																	AvDBUG_PUSH( aString, cS);
#else																																				
    #define	dBUG_XLOAD(	/*	X		*/		byte$,		dºcube,	dºq,		/*n/a*/		sºcube,	sÌ		/*n/a*/			/*n/a*/	)
    #define	dBUG_XLOADi(	/*	X		*/		byte$,		dºcube,	dºq,		/*n/a*/		sºcube,	sÌ,		sÌz				/*n/a*/	)
    #define	dBUG_ICEPACK(	/*	(251)	/*	/*	(q)	*/		dºcube,	dºq,		/*n/a*/		/**/ 	sÌ,		sÌz				/*n/a*/	)
    #define	dBUG_ReFLOW(		ascii$,			byte$,		ºcube,	dÌ0,		dÌz,			/**/		sÌ0,		sÌz,				rel$		)
    #define	dBUG_ReFLOW_A(	/*	(174),	*/		byte$,		ºcube, /*	ix,		ix+byte$-1, 	ºcube, 	iz,		iz+byte$-1*/		rel$		)
    #define	dBUG_ReFLOW_D(	/*	(175),	*/		byte$,		ºcube, /*	ix-byte$,	ix-1,			ºcube,	iz-byte$,	iz-1		*/		rel$		)
#endif																																				
																																				
#ifdef DEBUG_SvCOMMIT_L2X
	/*		SvCOMMIT OP		glyph			bytes		dst		dst: 1st	dst: last		src		src: 1st	src: last			shift		*/
    #define	dBUG_ICEPACK_i(	/*	(251)			(L[ sÌ ])	*/	dºcube,	dºq,		/*n/a*/		/**/		sÌ 		/*n/a*/			/*n/a*/	)	o = dºq -dºcube;		\
	if(L[sÌ]>0){ cS = sprintf( aString,	"\r%c	re-pack  (%3d) byte[s]:	%s[	\10	%3d..%-3d]	\10	=	vector  %3d\n",							\
								251,				L[ sÌ ],		#dºcube,	o,		o+L[ sÌ ]-1,	/**/		sÌ 		/*n/a*/			/*n/a*/	);	AvDBUG_PUSH( aString, cS ); \
			}																																				
    #define	dBUG_ReFLOW_i(		ascii$,			byte$,		ºcube,	dÌ,		/*n/a*/		/**/		sÌ,		/*n/a*/			rel$		)	\
			cS =sprintf( aString,	"\rrel$%c%d					%s[	\10	%3d..%-3d]	\10	=	%s[%3d..%-3d]\n",							\
								rel$, ascii$, byte$,				#ºcube,	dÌ,		dÌ+byte$-1,	#ºcube,	sÌ,		sÌ+byte$-1				);	AvDBUG_PUSH( aString, cS);	
#else																																				
	/*		SvCOMMIT OP		glyph			bytes		dst		dst: 1st	dst: last		src		src: 1st	src: last			shift		*/
    #define	dBUG_ICEPACK_i(	/*	(251)			(L[ sÌ ])	*/	dºcube,	dºq,		/*n/a*/		/**/		sÌ 		/*n/a*/			/*n/a*/	)
    #define	dBUG_ReFLOW_i(		ascii$,			byte$,		ºcube,	dÌ,		/*n/a*/		/**/		sÌ,		/*n/a*/			rel$		)
#endif




#ifdef DEBUG_SvCOMMIT_L2XX
	#define	dBUG_XL8	cS=sprintf( aString, "\rxload 8x: %02X%02X%02X%02X%02X%02X%02X%02X\n",	\
						*( (ui08*) (p_ +0 ) ),	*( (ui08*) (p_ +1 ) ),	*( (ui08*) (p_ +2 ) ),	*( (ui08*) (p_ +3 ) ),		\
						*( (ui08*) (p_ +4 ) ),	*( (ui08*) (p_ +5 ) ),	*( (ui08*) (p_ +6 ) ),	*( (ui08*) (p_ +7 ) )	);	AvDBUG_PUSH( aString, cS );
	#define	dBUG_XL4	cS=sprintf( aString, "\rxload 4x: %02X%02X%02X%02X\n",						\
						*( (ui08*) (p_ +0 ) ),	*( (ui08*) (p_ +1 ) ),	*( (ui08*) (p_ +2 ) ),	*( (ui08*) (p_ +3 ) )	);	AvDBUG_PUSH( aString, cS );
	#define	dBUG_XL2	cS=sprintf( aString, "\rxload 2x: %02X%02X\n",								\
						*( (ui08*) (p_ +0 ) ),	*( (ui08*) (p_ +1 ) )									);	AvDBUG_PUSH( aString, cS );
	#define	dBUG_XL1	cS=sprintf( aString, "\rxload 1x: %02X\n",									\
						*( (ui08*) (p_ +0 ) )													);	AvDBUG_PUSH( aString, cS );
#else
	#define	dBUG_XL8
	#define	dBUG_XL4
	#define	dBUG_XL2
	#define	dBUG_XL1
#endif

																									
#define	XLOAD( dºq, sÌ, byte$, sºcube, dºcube )							p_ = sºcube +sÌ;						dBUG_XLOAD( byte$, dºcube, dºq,	sºcube, sÌ	);	\
	while( byte$ >7 ){ *( (ui64*)	dºq ) = *( (ui64*)	p_ ); dBUG_XL8		dºq +=8;  	p_+=8;  		byte$-=8;	}	\
	while( byte$ >3 ){ *( (ui32*)	dºq ) = *( (ui32*)	p_ ); dBUG_XL4		dºq +=4;  	p_+=4;  		byte$-=4;	}	\
	while( byte$ >1 ){ *( (ui16*)	dºq ) = *( (ui16*)	p_ ); dBUG_XL2		dºq +=2;  	p_+=2;  		byte$-=2;	}	\
	while( byte$!=0 ){ *( (ui08*)	dºq ) = *( (ui08*)	p_ ); dBUG_XL1	++	dºq;   	++	p_;	--		byte$;		}

																									
#define	XLOADi( dºcube, sºcube,	dÌ, sÌ, lot$ )				p_ = sºcube +sÌ;									/*dBUG_XLOADi( byte$, sºcube, sÌ, sÌz,	dºcube, dºq	);*/	\
	while( lot$ >7 ){ *( (ui64*)	( dºcube+dÌ ) ) = *( (ui64*)	p_ ); dBUG_XL8	dÌ+=8;	p_+=8; 	  		lot$-=8;	}	\
	while( lot$ >3 ){ *( (ui32*)	( dºcube+dÌ ) ) = *( (ui32*)	p_ ); dBUG_XL4	dÌ+=4;	p_+=4;	  		lot$-=4;	}	\
	while( lot$ >1 ){ *( (ui16*)	( dºcube+dÌ ) ) = *( (ui16*)	p_ ); dBUG_XL2	dÌ+=2;	p_+=2;	  		lot$-=2;	}	\
	while( lot$!=0 ){ *( (ui08*)	( dºcube+dÌ ) ) = *( (ui08*)	p_ ); dBUG_XL1	dÌ+=1;	p_+=1;		--	lot$;		}	\

/*		ICEPACK		DISRUPT IVE: "++sÌ" and "--sÌz"!					/*	alters sÌ & sÌz			*/		
#define	ICEPACK( dºq,		sÌ,	sÌz, sÌn,	dºcube )														dBUG_ICEPACK(	dºcube, dºq,	sÌ, sÌz	);	\
		for(	;				sÌz	>	sÌ;--sÌz )	\
			if( Oª[ sÌn ] - Oª[	sÌz ]	>2	){		\
				do	{																			dBUG_ICEPACK_i(	dºcube, dºq,	sÌ		);	\
					switch(		K[	sÌ	] ){	SwCASE_AB2IC_t3_inc(	dºq,		A[ sÌ ],	B[ sÌ ],	dºq ); }	\
					} while(	sÌz > ++	sÌ );		/*			^overrun tolerance: 3				*/		\
				break;						\
				} do	{																			dBUG_ICEPACK_i(	dºcube, dºq,	sÌ		);	\
					switch(		K[	sÌ	] ){	SwCASE_AB2IC_t0_inc(	dºq,		A[ sÌ ],	B[ sÌ ],	dºq ); }	\
					} while(	sÌn > ++	sÌ );		/*			^overrun tolerance: 0				*/

/*		iCEPACK		lowercase "i" variant:    							/*	retain sÌ				*/
#define	iCEPACK( dºq,		sÌ,	sÌz, sÌn,	dºcube )	ix = sÌ;												dBUG_ICEPACK(  	dºcube, dºq,	ix, sÌz	);	\
		for(	;				sÌz	>	ix;	--sÌz )	\
			if( Oª[ sÌn ] - Oª[	sÌz ]	>2	){		\
				do	{																			dBUG_ICEPACK_i(	dºcube, dºq,	ix		);	\
					switch(		K[	ix	] ){	SwCASE_AB2IC_t3_inc(	dºq,		A[ ix ],	B[ ix ],	dºq ); }	\
					} while(	sÌz > ++	ix );		/*			^overrun tolerance: 3				*/		\
				break;						\
				} do	{																			dBUG_ICEPACK_i(	dºcube, dºq,	ix		);	\
					switch(		K[	ix	] ){	SwCASE_AB2IC_t0_inc(	dºq,		A[ ix ],	B[ ix ],	dºq ); }	\
					} while(	sÌn > ++	ix );		/*			^overrun tolerance: 0				*/

/*		ICEpACK		lowercase "p" variant:    						/*	retain sÌz				*/
#define	ICEpACK( dºq,    	sÌ,	sÌz, sÌn,	dºcube )	iz=sÌz;												dBUG_ICEPACK(  	dºcube, dºq,	sÌ, iz		);	\
		for(	;				iz	>	sÌ;--iz )	\
			if( Oª[ sÌn ] - Oª[	iz ]	>2	){		\
				do	{																			dBUG_ICEPACK_i(	dºcube, dºq,	sÌ		);	\
					switch(		K[	sÌ	] ){	SwCASE_AB2IC_t3_inc(	dºq,		A[ sÌ ],	B[ sÌ ],	dºq ); }	\
					} while(	iz > ++	sÌ );		/*			^overrun tolerance: 3				*/		\
				break;						\
				} do	{																			dBUG_ICEPACK_i(	dºcube, dºq,	sÌ		);	\
					switch(		K[	sÌ	] ){	SwCASE_AB2IC_t0_inc(	dºq,		A[ sÌ ],	B[ sÌ ],	dºq ); }	\
					} while(	sÌn > ++	sÌ );		/*			^overrun tolerance: 0				*/

/*		iCEpACK		lowercase "i" and"p" variant:    					/*	retain sÌ & sÌz			*/
#define	iCEpACK( dºq,    	sÌ,	sÌz, sÌn,	dºcube )	ix = sÌ;	iz=sÌz;										dBUG_ICEPACK(  	dºcube, dºq,	ix, iz		);	\
		for(	;				iz	>	ix;--iz )	\
			if( Oª[ sÌn ] - Oª[	iz ]	>2	){		\
				do	{																			dBUG_ICEPACK_i(	dºcube, dºq,	ix		);	\
					switch(		K[	ix	] ){	SwCASE_AB2IC_t3_inc(	dºq,		A[ ix ],	B[ ix ],	dºq ); }	\
					} while(	iz > ++	ix );		/*			^overrun tolerance: 3				*/		\
				break;						\
				} do	{																			dBUG_ICEPACK_i(	dºcube, dºq,	ix		);	\
					switch(		K[	ix	] ){	SwCASE_AB2IC_t0_inc(	dºq,		A[ ix ],	B[ ix ],	dºq ); }	\
					} while(	sÌn > ++	ix );		/*			^overrun tolerance: 0				*/



#define	dBUG_RF8($bs, ºcuBe, $r)	printf("\rre-flow *( cube+%-2d)	0x016llX \10 \10 \10 \10 \10 \10 \10	%2s( %d x8 )\n", iz, *( (ui64*) ( ºcuBe+iz ) ),	$bs,	$r	);
#define	dBUG_RF4($bs, ºcuBe, $r)	printf("\rre-flow *( cube+%-2d)	0x________%08lX \10 \10 \10 \10 \10	%2s( %d x8 )\n", iz, *( (ui32*) ( ºcuBe+iz ) ),	$bs,	$r	);
#define	dBUG_RF2($bs, ºcuBe, $r)	printf("\rre-flow *( cube+%-2d)	0x____________%04lX \10 \10 \10 \10	%2s( %d x8 )\n", iz, *( (ui16*) ( ºcuBe+iz ) ),	$bs,	$r	);
#define	dBUG_RF1($bs, ºcuBe, $r)	printf("\rre-flow *( cube+%-2d)	0x______________%02lX \10 \10 \10	%2s( %d x8 )\n", iz, *( (ui08*) ( ºcuBe+iz ) ),	$bs,	$r	);


#define ReFLOW_AC(	ºcuBe,	ºcuRe,	rel$, lot$,			dÌ0,		sÌ0,	$n )	 \
	if( lot$ ){										ix =	dÌ0;	iz =	sÌ0;		dBUG_ReFLOW_A(	lot$, ºcuRe, rel$ )	\
		if(	rel$ >-2 )	goto SYM( drop_1x, $n );			\
		if(	rel$ >-4 )	goto SYM( drop_2x, $n );			\
		if(	rel$ >-8 )	goto SYM( drop_4x, $n );			\
													\
		/*			drop_8x:	*/ if(	lot$ >7 ){	do{				*( (ui64*) ( ºcuRe+ix ) )=*( (ui64*) ( ºcuBe+iz ) );	ix+=8; iz+=8;	lot$-=8; } while( lot$ >7 );	\
								if(	lot$ >3 ){					*( (ui32*) ( ºcuRe+ix ) )=*( (ui32*) ( ºcuBe+iz ) );	ix+=4; iz+=4;	lot$-=4; }					\
								if(	lot$ >1 ){					*( (ui16*) ( ºcuRe+ix ) )=*( (ui16*) ( ºcuBe+iz ) );	ix+=2; iz+=2;	lot$-=2; }					\
								if(	lot$ >0 ){					*( (ui08*) ( ºcuRe+ix ) )=*( (ui08*) ( ºcuBe+iz ) );	ix+=1; iz+=1;	lot$-=1; }					\
		}else SYM(	drop_4x, $n ):	if(	lot$ >3 ){	do{				*( (ui32*) ( ºcuRe+ix ) )=*( (ui32*) ( ºcuBe+iz ) );	ix+=4; iz+=4;	lot$-=4; } while( lot$ >3 );	\
								if(	lot$ >1 ){					*( (ui16*) ( ºcuRe+ix ) )=*( (ui16*) ( ºcuBe+iz ) );	ix+=2; iz+=2;	lot$-=2; }					\
								if(	lot$ >0 ){					*( (ui08*) ( ºcuRe+ix ) )=*( (ui08*) ( ºcuBe+iz ) );	ix+=1; iz+=1;	lot$-=1; }					\
		}else SYM(	drop_2x, $n ):	if(	lot$ >1 ){	do{				*( (ui16*) ( ºcuRe+ix ) )=*( (ui16*) ( ºcuBe+iz ) );	ix+=2; iz+=2;	lot$-=2; } while( lot$ >1 );	\
								if(	lot$ >0 ){					*( (ui08*) ( ºcuRe+ix ) )=*( (ui08*) ( ºcuBe+iz ) );	ix+=1; iz+=1;	lot$-=1; }					\
		}else SYM(	drop_1x, $n ):				do{				*( (ui08*) ( ºcuRe+ix ) )=*( (ui08*) ( ºcuBe+iz ) );	ix+=1; iz+=1;	lot$-=1; } while( lot$ >0 );	\
		}
#define ReFLOW_DX(		ºcuBe, ºcuRe,	rel$, lot$,			dÌn,		sÌn,	$n )	\
	if( lot$ ){										ix =	dÌn;	iz =	sÌn;		dBUG_ReFLOW_D(	lot$, ºcuRe, rel$ )	\
		if(	rel$< 2 )	goto SYM( lift_1x, $n );				\
		if(	rel$< 4 )	goto SYM( lift_2x, $n );				\
		if(	rel$< 8 )	goto SYM( lift_4x, $n );				\
													\
		/*			lift_8x:	*/ if(	lot$ >7 ){	do{	ix-=8; iz-=8;	*( (ui64*) ( ºcuRe+ix ) )=*( (ui64*) ( ºcuBe+iz ) );				lot$-=8; } while( lot$ >7 );	\
								if(	lot$ &4 ){		ix-=4; iz-=4;	*( (ui32*) ( ºcuRe+ix ) )=*( (ui32*) ( ºcuBe+iz ) );				lot$-=4; }				\
								if(	lot$ &2 ){		ix-=2; iz-=2;	*( (ui16*) ( ºcuRe+ix ) )=*( (ui16*) ( ºcuBe+iz ) );				lot$-=2; }				\
								if(	lot$ &1 ){		ix-=1; iz-=1;	*( (ui08*) ( ºcuRe+ix ) )=*( (ui08*) ( ºcuBe+iz ) );				lot$-=1; }				\
		}else SYM(	lift_4x, $n ): if(		lot$ >3 ){	do{	ix-=4; iz-=4;	*( (ui32*) ( ºcuRe+ix ) )=*( (ui32*) ( ºcuBe+iz ) );				lot$-=4; } while( lot$ >3 );	\
								if(	lot$ &2 ){		ix-=2; iz-=2;	*( (ui16*) ( ºcuRe+ix ) )=*( (ui16*) ( ºcuBe+iz ) );				lot$-=2; }				\
								if(	lot$ &1 ){		ix-=1; iz-=1;	*( (ui08*) ( ºcuRe+ix ) )=*( (ui08*) ( ºcuBe+iz ) );				lot$-=1; }				\
		}else SYM(	lift_2x, $n ): if(		lot$ >1 ){	do{	ix-=2; iz-=2;	*( (ui16*) ( ºcuRe+ix ) )=*( (ui16*) ( ºcuBe+iz ) );				lot$-=2; } while( lot$ >1 );	\
								if(	lot$ &1 ){		ix-=1; iz-=1;	*( (ui08*) ( ºcuRe+ix ) )=*( (ui08*) ( ºcuBe+iz ) );				lot$-=1; }					\
		}else SYM(	lift_1x, $n ):				do{	ix-=1; iz-=1;	*( (ui08*) ( ºcuRe+ix ) )=*( (ui08*) ( ºcuBe+iz ) );				lot$-=1; } while( lot$ >0 );	\
		}
	/*							ºcuBe: the cube that be;	ºcuRe: that same cube, but re-assigned and possibly re-allocated		*/				\
#define _ReFLOW(		$svΩ,		ºcuBe, ºcuRe, 	rel$, byte$,	sÌ0,	dÌ0,	sÌn,	dÌn,						$n )					\
	if(		rel$ >0 ) 	{							SvCUR_set(	$svΩ,	O[ ixM ]  	);	/* prevent copying obsolete data	*/	\
	/* desc. expansion	*/					ºcuRe =	SvGROW(	$svΩ,	dÌn+1 );		/* $CSΩ= dÌn;					*/	\
					ReFLOW_DX(	ºcuBe,	ºcuRe,	rel$,	byte$,	dÌn,  	sÌn,						$n );					\
	}else if(	rel$< 0 )	{																							\
	/* asc. compaction	*/					ºcuRe = ºcuBe;															\
					ReFLOW_AC(	ºcuBe,	ºcuRe,	rel$, byte$,	dÌ0,	sÌ0,							$n );					\
	}else								ºcuRe = ºcuBe;															\
	/* bypass	*/														dBUG_SvCUR(	$svΩ, dÌn );				\
										ºcuRe[ dÌn ]=0;					SvCUR_set(		$svΩ, dÌn );
					
#define	ReFLOW(		$svΩ,		ºcuBe, ºcuRe, 	rel$, byte$,	sÌ0,	dÌ0,	sÌn,	dÌn	)		\
		_ReFLOW(	$svΩ,		ºcuBe, ºcuRe, 	rel$, byte$,	sÌ0,	dÌ0,	sÌn,	dÌn,	__LINE__	)




#ifdef DEBUG_SvCOMMIT_L3		//	paranoid integrity checks which are silent until there's a problem
	#define dBUGmx( $depth, $mkIn, $mkOut )		_print_mx( $depth, $mkIn, $mkOut );
	#define dBUGrackCALL($FRAG_LEV)					if( ixM		==	0xFF			){						printf("\n!	_sv_commit(%d):	nothing to commit\n",									$FRAG_LEV);	return;	}\
		STRLEN	CS_;									if( Aº    	!=	AvARRAY( avICE )	){ Aº=AvARRAY( avICE );	printf( "\r!	_sv_commit(%d): 	(SV**) \"Aº)\" was out of sync with *AvARRAY( avICE )!\n",	$FRAG_LEV);	}\
		SV*		sv_ 		= *(Aº +iC);					if( &*sv   	!=	&*sv_		){ sv= sv_;			printf( "\r!	_sv_commit(%d): 	(SV*) \"sv\" was out of sync with *( AvARRAY( avICE ) +iC )!\n",	$FRAG_LEV);	}\
		ui08*	cube_	= SvPVbyte( sv, CS_ );		 	if( cube		==	NULL		){ cube=cube_;		printf("\n!	_sv_commit(%d):	(unsigned char*) cube was NULL!\n",						$FRAG_LEV);	}\
												else	if( &*cube	!=	&*cube_		){ cube=cube_;		printf( "\r!	_sv_commit(%d): 	(char *) \"cube\" was out of sync with SvPVbyte( ... )! \n",		$FRAG_LEV);	}\
													if( CS    		!=	CS_			){ CS=CS_; 			printf( "\r!	_sv_commit(%d): 	(STRLEN) \"CS\" was out of sync with SvPVbyte( ... )!\n",		$FRAG_LEV);	}
#else
	#define dBUGmx( $depth, $mkIn, $mkOut )
	#define dBUGrackCALL($FRAG_LEV)
#endif
