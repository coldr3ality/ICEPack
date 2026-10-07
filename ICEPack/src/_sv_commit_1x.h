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
#ifdef DEBUG_SvCOMMIT_L1X
	#define dBUG_1X1	{cS =sprintf( aString, "\n_sv_commit_1x(%3d):	locus : %3lld.%d..%lld.%-3d	 pre_c: %3d+1	\10	\10	 pre_q: %3d	 CS: %-3lld bytes\n",	\
												xcª,			iCI, icI,		iC, icO,		pre_xc,				 pre_q,		 CS );				\
						cS+=sprintf( aString +cS,	"\t\x9Fsub 1X1	matrix: %5d..%-5d	\10	\10	post_c: %3d+1	\10	post_q: %3d	oCS: %-3lld bytes	O[inM]: %-3d\n",	\
															ixM, izM,					post_xc,				post_q,		oCS,			O[inM]		);	\
						cS+=sprintf( aString +cS,		"			oc /xc : %5d/%-5d	\10	\10	 rel_c: %3d	\10	\10	 rel_q: %3d	\n",		\
															oc,		xc,				 rel_c,				 rel_q		);		\
						cS+=sprintf( aString +cS,		"			oc\xA6/xc\xA6: %5d/%-5d	  hp_c: %3d	\10	\10	  hp_q: %3d	\n\n",	\
															ocª,		xcª,				  hp_c,				  hp_q 		);		\
						AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase);	\
						}
	#define dBUG_1X2L {cS =sprintf( aString,"\n_sv_commit_1x(%3d):	 locus : %3lld.%d..%lld.%-3d	 pre_c: %3d	\10	\10	 pre_q: %3d	    CS: %-3lld bytes\n",	\
												xcª,			 iCI, icI,		iC, icO,		 pre_c,				 pre_q,		    CS );				\
						cS+=sprintf( aString +cS,	"\t\x9Fsub 1X2L	 matrix: %5d..%-5d	\10	\10	post_c: %3d	\10	\10	post_q: %3d	   CS\xA7: %-3d bytes ( O\xA6[ ix\xEA ] )\n",		\
															 ixM, izM,				post_c,				post_q,		   Oª[ixΩ]						);	\
						cS+=sprintf( aString +cS,		"			oc /xc : %5d/%-5d	\10	\10	 rel_c: %3d	\10	\10	 rel_q: %3d	   CS\xEA: %-3lld bytes ( CS +16 -	( O\xA6[ ix\xEA ]: %d ) )\n",	\
															oc,		xc,				 rel_c,				 rel_q,		   CSΩ,					Oª[ ixΩ ]			);	\
						cS+=sprintf( aString +cS,		"			oc\xA6/xc\xA6: %5d/%-5d		\10	\10	\10	\10	  hp_q: %3d\n",		\
															ocª,		xcª,									  hp_q		);	\
						AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase); \
						}
	#define dBUG_1X2H {cS =sprintf( aString,"\n_sv_commit_1x(%3d):	 locus : %3lld.%d..%lld.%-3d	 pre_c: %3d	\10	\10	 pre_q: %3d	 CS: %-3lld bytes\n",	\
												xcª,			 iCI, icI,		iC, icO,		pre_c,				pre_q,		 CS	);				\
						cS+=sprintf( aString +cS,	"\t\x9Fsub 1X2H	 matrix: %5d..%-5d	\10	\10	post_c: %3d	\10	\10	post_q: %3d	CS\xA7: %-3lld bytes ( O\xA6[ ix\xEA ]: %d )\n",	\
															 ixM, izM,				post_c,				post_q,		O[ixΩ],		Oª[ ixΩ ]		);	\
						cS+=sprintf( aString +cS,		"			oc /xc : %5d/%-5d			rel_c: %3d	\10	\10	 rel_q: %3d	CS\xEA:	%-3lld bytes ( CS	+rel_q( %d ) +16	-O[ix1]( %d ) )	\n",	\
															oc,		xc,				rel_c,				rel_q,		CSΩ,						rel_q,			O[ixΩ]		);	\
						cS+=sprintf( aString +cS,		"			oc\xA6/xc\xA6: %5d/%-5d	rel\xEA_c: %3d	\n",	\
															ocª,		xcª,				relΩ_c			);	\
						cS+=sprintf( aString +cS,		"			\10	\10	\10	\10	\10		 lp\xEA_c: %3d	\10	 hp\xEA_q: %3d	\n",	\
																					 lpΩ_c,				 hpΩ_q			);	\
						AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase);			\
						}
	#define dBUG_1X2M {cS =sprintf( aString,"\n_sv_commit_1x(%3d):	 locus : %3lld.%d..%lld.%-3d	  zc-icI: %3d	\10	\10	 pre\xEA_c: %3d	  pre_q: %3d	\10	 CS: %-3lld bytes\n",	\
												xcª,			 iCI, icI,		iC, icO,		  zc-icI,				 preΩ_c,			  pre_q,			 CS				);	\
						cS+=sprintf( aString +cS,	"\t\x9Fsub 1X2M	 matrix: %5d..%-5d	\10	\10	post\xA7_xc: %3d	\10	post\xEA_c: %3d	post\xEA_q: %3d	CS\xA7 (O\xA6[ix1]): %-3d bytes\n",	\
															 ixM, izM,				postº_xc,				postΩ_c,			postΩ_q,				Oª[ixΩ]			);	\
						cS+=sprintf( aString +cS,		"			oc /xc : %5d/%-5d	\10	\10	   rel_c: %3d	\10	\10	   hp_c: %3d	\10	  hp\xEA_q: %3d	CS\xEA: %-3lld bytes\n",	\
															oc,		xc,				   rel_c,				   hp_c,			  hpΩ_q,			CSΩ				);	\
						cS+=sprintf( aString +cS,		"			oc\xA6/xc\xA6: %5d/%-5d	\n",	\
															ocª,		xcª				);	\
						cS+=sprintf( aString +cS,		"			ix\xA7/iz\xA7: %5d/%-5d	\n",	\
															ixº,		izº				);	\
						AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase); \
						}
	#define dBUG_1X3	{	/*	preº_q	= pre¹_q	= preΩ_q	= 0;		\
							relº_q	= rel¹_q	= relΩ_q	= 0;	*/	\
					cS =sprintf( aString,"\n_sv_commit_1x(%3d):	locus : %3lld.%d..%lld.%-3d	%3d.%d..%d.%-3d	\10	%3d.%d..%d.%-3d	%3d.%d..%d.%-3d	\n",		\
												xcª,			iCI, icI,		iC, icO,		0,0,		0,0,			0,0,		0,0,		0,0,		0,0			);	\
					cS+=sprintf( aString +cS,	"\t\x9Fsub 1X3-%c%c%c\tmatrix: %5d..%-5d \10 \10	%5d..%-5d	\10	\10	%5d..%-5d	\10	%5d..%-5d		\n",		\
						64+(	subcase&7),		64+( (subcase>>3)&7),	\
						64+( (subcase>>9)&7), 					ixM, izM,					0, 	/*izº*/ ix¹-1,		ix¹,		iz¹,		ixΩ, 	izΩ				);	\
						cS+=sprintf( aString +cS,		"			oc /xc : %5d/%-5d		\10	  pre\xA7_c: %3d	\10	  pre1_xc: %3d	 pre\xEA_c: %3d	CS: %-3lld bytes  CS1: %-3lld bytes  CS\xEA: %-3lld bytes\n",	\
															oc,		xc,				  preº_c,		  		  pre¹_xc,			 preΩ_c,			CS,				CS¹,			CSΩ				);	\
						cS+=sprintf( aString +cS,		"			oc\xA6/xc\xA6: %5d/%-5d	 post\xA7_c: %3d	\10	 post1_xc: %3d 	post\xEA_c: %3d	\n",		\
															ocª,		xcª,			/*	relº_c,	*/			   rel¹_c,			 relΩ_c				);	\
						cS+=sprintf( aString +cS,					"						  pre\xA7_q: n/a	\10	   pre1_q: %3d 	 pre\xEA_q: n/a	\n",		\
																				/*	preº_q,	*/			   pre¹_q		/*	 preΩ_q	*/			);	\
						cS+=sprintf( aString +cS,					"ix\xA7/iz\xA7:			 post\xA7_q: n/a	\10	  post1_q: %3d 	post\xEA_q: n/a	\n",		\
															ixº,		izº,				 postº_q,				  post¹_q,			postΩ_q				);	\
						cS+=sprintf( aString +cS,					"						  rel\xA7_q: n/a	\10	   rel1_q: %3d  \10	 rel\xEA_q: n/a	\n",		\
																				/*	relº_q,	*/			   rel¹_q		/*	 relΩ_q	*/			);	\
						cS+=sprintf( aString +cS,					"						   hp\xA7_q: n/a	\10	    hp1_q: %3d  \10	  hp\xEA_q: n/a	\n",		\
																				/*	   hpº_q,	*/			    hp¹_q		/*	  hpΩ_q	*/			);	\
						cS+=sprintf( aString +cS,					"						   hp\xA7_i: n/a	\10	    hp1_i: %3d  \10	  hp\xEA_i: n/a	\n\n",	\
																				/*	   hpº_i,	*/			    hp¹_i		/*	  hpΩ_i	*/			);	\
						AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase); 	\
						}
	#define dBUG_1X4	{ cS =sprintf( aString,"\n_sv_commit_1x(%3d):	locus : %3lld.%d..%lld.%-3d	  pre\xA7_c: %3d	\10	  pre1_c: %3d	\10	  pre\xFD_c: %3d	  pre\xEA_c: %3d	CS: %-3lld bytes  CS1: %-3lld bytes  CS\xB2: %-3lld bytes  CS\xEA: %-3lld bytes\n",				\
												xcª,			iCI, icI,		iC, icO,		  preº_c,				pre¹_c,			  pre²_c,			  preΩ_c,		CS,			CS¹,			CS²,			CSΩ				);			\
						cS+=sprintf( aString +cS,		"	 		matrix: %5d..%-5d \10 \10	 post\xA7_c: %3d	\10	 post1_c: %3d	\10	 post\xFD_c: %3d	 post\xEA_c: %3d \n",			\
															ixM, izM,					  postº_c,				post¹_c,			 post²_c,			 postΩ_c				);	\
						cS+=sprintf( aString +cS,		"			oc /xc : %5d/%-5d			\n",	\
															oc,		xc				);	\
						cS+=sprintf( aString +cS,		"			oc\xA6/xc\xA6: %5d/%-5d	\n",	\
															ocª,		xcª				);	\
						\
						cS+=sprintf( aString +cS,	"\t\x9Fsub 1X%d-%c%c%c%c	\10				 post\xA7_q: %3d	\10	 post1_q: %3d	\10	  post\xFD_q: %3d	 post\xEA_q: %3d\n\n",	\
						endo_c+4, 64+( subcase&7),	64+( (subcase>>3)&7),		\
						64+( (subcase>>6)&7),		64+( (subcase>>9)&7),					 postº_q,				post¹_q,			  post²_q,			  postΩ_q			);	\
						AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase); \
						}
#else
	#ifdef DEBUG_SvCOMMIT_L1
	#define dBUG_1X1	{ cS =sprintf( aString, "\n_sv_commit_1x(%3d):	locus : %3lld.%d..%lld.%-3d	 CS: %-3lld bytes\n",	\
												xcª,			iCI, icI,		iC, icO,		 CS );				\
						cS+=sprintf( aString +cS,	"\t\x9Fsub 1X1	matrix: %5d..%-5d	\10	\10	oCS: %-3d bytes	O[inM]: %-3d\n",	\
															ixM, izM,					oCS,			O[inM]		);	\
						cS+=sprintf( aString +cS,		"			oc /xc : %5d/%-5d	\10	\10	\n",		\
															oc,		xc					);	\
						cS+=sprintf( aString +cS,		"			oc\xA6/xc\xA6: %5d/%-5d	\n\n",	\
															ocª,		xcª					);	\
						AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase);					\
						}

	#define dBUG_1X2L { cS =sprintf( aString,"\n_sv_commit_1x(%3d):	 locus : %3lld.%d..%lld.%-3d	    CS: %-3lld bytes		\n",	\
												xcª,			 iCI, icI,		iC, icO,		    CS );					\
						cS+=sprintf( aString +cS,	"\t\x9Fsub 1X2L	 matrix: %5d..%-5d	\10	\10	   CS\xA7: %-3d bytes	\n",	\
															 ixM, izM,				   Oª[ixΩ]				);	\
						cS+=sprintf( aString +cS,		"			oc /xc : %5d/%-5d	\10	\10	   CS\xEA: %-3d bytes	\n",	\
															oc,		xc,				   CSΩ				);	\
						cS+=sprintf( aString +cS,		"			oc\xA6/xc\xA6: %5d/%-5d	\n\n",		\
															ocª,		xcª					);	\
						AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase); \
						}


	#define dBUG_1X2H { cS =sprintf( aString,"\n_sv_commit_1x(%3d):	 locus : %3lld.%d..%lld.%-3d	 CS: %-3lld bytes\n",	\
												xcª,			 iCI, icI,		iC, icO,		 CS	);				\
						cS+=sprintf( aString +cS,	"\t\x9Fsub 1X2H	 matrix: %5d..%-5d	\10	\10	CS\xA7: %-3lld bytes ( O\xA6[ ix1 ]: %d )\n",	\
															 ixM, izM,				O[ixΩ],		Oª[ ixΩ ]		);	\
						cS+=sprintf( aString +cS,		"			oc /xc : %5d/%-5d			CS\xEA:	%-3d bytes ( CS	+rel_q( %d ) +16	-O[ix1]( %d ) )	\n",	\
															oc,		xc,				CSΩ,						rel_q,			O[ixΩ]		);	\
						cS+=sprintf( aString +cS,		"			oc\xA6/xc\xA6: %5d/%-5d	\n",	\
															ocª,		xcª				);	\
						AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase);			\
						}
	#define dBUG_1X2M { cS =sprintf( aString,"\n_sv_commit_1x(%3d):	 locus : %3lld.%d..%lld.%-3d	   CS: %-3lld bytes\n",	\
												xcª,			 iCI, icI,		iC, icO,		   CS				);	\
						cS+=sprintf( aString +cS,	"\t\x9Fsub 1X2M	 matrix: %5d..%-5d	\10	\10	CS\xA7 (O\xA6[ix1]): %-3d bytes\n",	\
															 ixM, izM,				Oª[ixΩ]			);	\
						cS+=sprintf( aString +cS,		"			oc /xc : %5d/%-5d	\10	\10	CS\xEA: %-3d bytes\n",	\
															oc,		xc,				CSΩ				);	\
						cS+=sprintf( aString +cS,		"			oc\xA6/xc\xA6: %5d/%-5d	\n",	\
															ocª,		xcª				);	\
						cS+=sprintf( aString +cS,		"			ix\xA7/iz\xA7: %5d/%-5d	\n",	\
															ixº,		izº				);	\
						AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase); \
						}

	#define dBUG_1X3	{ cS =sprintf( aString,"\n_sv_commit_1x(%3d):	locus : %3lld.%d..%lld.%-3d	\n",		\
												xcª,			iCI, icI,		iC, icO		);		\
					cS+=sprintf( aString +cS,	"\t\x9Fsub 1X3-%c%c%c\tmatrix: %5d..%-5d \10 \10	\n",		\
						64+(	subcase&7),		64+( (subcase>>3)&7),								\
						64+( (subcase>>9)&7), 					ixM, izM					);		\
						cS+=sprintf( aString +cS,		"			oc /xc : %5d/%-5d		\10	CS: %-3lld bytes  CS1: %-3lld bytes  CS\xEA: %-3lld bytes\n",		\
															oc,		xc,				CS,				CS¹,			CSΩ				);	\
						cS+=sprintf( aString +cS,		"			oc\xA6/xc\xA6: %5d/%-5d	\n",		\
															ocª,		xcª				);		\
						cS+=sprintf( aString +cS,					"ix\xA7/iz\xA7: %5d/%-5d	\n",		\
															ixº,		izº				);		\
						AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase); 					\
						}
	#define dBUG_1X4	{ cS =sprintf( aString,"\n_sv_commit_1x(%3d):	locus : %3lld.%d..%lld.%-3d	CS: %-3lld bytes  CS1: %-3lld bytes  CS\xB2: %-3lld bytes  CS\xEA: %-3lld bytes\n",				\
												xcª,			iCI, icI,		iC, icO,		CS,			CS¹,			CS²,			CSΩ				);			\
						cS+=sprintf( aString +cS,		"	 		matrix: %5d..%-5d \10 \10	\n",		\
															ixM, izM					);		\
						cS+=sprintf( aString +cS,		"			oc /xc : %5d/%-5d			\n",		\
															oc,		xc				);		\
						cS+=sprintf( aString +cS,		"			oc\xA6/xc\xA6: %5d/%-5d	\n",		\
															ocª,		xcª				);		\
						cS+=sprintf( aString +cS,	"\t\x9Fsub 1X%d-%c%c%c%c	\10				\n\n",	\
						endo_c+4, 64+( subcase&7),	64+( (subcase>>3)&7),							\
						64+( (subcase>>6)&7),		64+( (subcase>>9)&7)					);		\
						AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase); 					\
						}
	#else
		#ifdef DEBUG_SvCOMMIT_L1F
			#define dBUG_1X1		cS=sprintf( aString, "11 \r");		AvDBUG_PUSH( aString, cS );
			#define dBUG_1X2L	cS=sprintf( aString, "1L \r");		AvDBUG_PUSH( aString, cS );
			#define dBUG_1X2H	cS=sprintf( aString, "1H \r");	AvDBUG_PUSH( aString, cS );
			#define dBUG_1X2M	cS=sprintf( aString, "1M \r");	AvDBUG_PUSH( aString, cS );
			#define dBUG_1X3		cS=sprintf( aString, "13 \r");		AvDBUG_PUSH( aString, cS );
			#define dBUG_1X4		cS=sprintf( aString, "14 \r");		AvDBUG_PUSH( aString, cS );
		#else
			#define dBUG_1X1
			#define dBUG_1X2L
			#define dBUG_1X2H
			#define dBUG_1X2M
			#define dBUG_1X3
			#define dBUG_1X4
		#endif
	#endif
#endif

#ifdef DEBUG_SvCOMMIT_L2
	#define dBUG_MOD_Eº			cS=sprintf( aString, "\r<MOD_CUBE_0_AS_LPASS>\n");				AvDBUG_PUSH( aString, cS );
	#define dBUG_MOD_Eº_CLOSE	cS=sprintf( aString, "\r	</MOD_CUBE_0_AS_LPASS>\n");				AvDBUG_PUSH( aString, cS );
	#define dBUG_MOD_Aº			cS=sprintf( aString, "\r<MOD_CUBE_0_AS_LPASSxMODS>\n");			AvDBUG_PUSH( aString, cS );
	#define dBUG_MOD_Aº_CLOSE	cS=sprintf( aString, "\r	</MOD_CUBE_0_AS_LPASSxMODS>\n");		AvDBUG_PUSH( aString, cS );
//			cS+=	sprintf( aString+cS,	"	( CS\xEA: %d )	\10	= (	CS: %d )		\10	\10	+ ( rel\xEA_q: ! )		\n",	\
										CSΩ,				CS				/*,	relΩ_q	*/			);	\

	#define dBUG_NEW_EΩ			cS =  sprintf( aString, "\r<NEW_CUBE_\xEA_AS_HIGHPASS> iC: %lld\n", iC );				AvDBUG_PUSH( aString, cS );
//			cS+=	sprintf( aString+cS,	"	( hp\xEA_q: %d )	= (	CS: %d )-16		\10	- ( pre\xEA_q: !);	 	\n",	\
										hpΩ_q,				CS				/*,	preΩ_q	*/			);	\
			cS+=	sprintf( aString+cS,	"	zc/zc\xEA: %d/%d	zcOf( cube ): %d	CS: %lld	SvCUR( sv ): %lld	SvCUR( *(Aº+iC) ): %lld	\n",\
										zc,	zcΩ,		zcOf( cube ),		CS, 		SvCUR( sv ), 		SvCUR( *(Aº+iC) )	);	\
			cS+=	sprintf( aString+cS,	"	( pre\xEA_q: ! )	= ( O[ ixH: %d]: %d )		- ( oCS: %d );			\n\n",\
									/*	preΩ_q,		*/		ixH, O[ ixH ],			oCS			);			\
			cS+=	sprintf( aString+cS,	"alt:	( rel\xEA_q: %d )	= ( O\xA6[ inM: %d]: %d )	- ( O[ ixH %d ]: %d );			\n\n",\
										Oª[inM]-O[ixH],		inM, Oª[ inM ],		ixH, O[ ixH ]	);			AvDBUG_PUSH( aString, cS );

	#define dBUG_NEW_EΩ_CLOSE	cS = sprintf( aString, "\r	</NEW_CUBE_\xEA_AS_HIGHPASS>\n");				AvDBUG_PUSH( aString, cS );
//			cS+=	sprintf( aString+cS,	"	( CS\xEA: %d )	\10	= ( CS: %d )			\10	+ ( rel\xEA_q: ! )		\n",	\
										CSΩ,				CS				/*,	relΩ_q	*/			);	\
			cS+=	sprintf( aString+cS,	"	( hp\xEA_i: %d )	= ( I[ ix\xEA: %d]: %d )		- ( oc\xA6: %d );		\n",	\
										I[ ixΩ ]-ocª,			ixΩ,  I[ ixΩ ],			ocª					);	\
			cS+=	sprintf( aString+cS,	"alt:	( hp\xEA_i: %d )	= ( ix\xEA: %d )		\10	\10	- ( ixH: %d );		\n",	\
										ixΩ-ixH,				ixΩ,					ixH					);	\
									/*	hpΩ_o	= oCS +CS 	- O[ ixH-1 ]	-16; 	*/						\
			cS+=	sprintf( aString+cS,	"alt:	( hp\xEA_o: ! )	= ( oCS: %d )+( CS: %d )	\10	- ( O[ ixH-1: %d ]: %d ) -16;\n\n",	\
									/*	hpΩ_o,		*/		oCS, CS,				ixH-1, O[ ixH-1 ]		);	\
			cS+=	sprintf( aString+cS,	"	( hp\xEA_c: %d )	= ( zc: %d )			\10	- ( icO: %d );			\n",	\
										zc-icO,				zc,					icO					);	\
			cS+=	sprintf( aString+cS,	"alt:	( hp\xEA_c: %d )	= ( xc\xA6: %d )	+1		- ( ixH: %d );			\n",	\
										xcª+1-ixH,			xcª,					ixH					);	\
			cS+=	sprintf( aString+cS,	"alt:	( hp\xEA_c: %d )	= ( xc: %d )			\10	- ( I[ ixH: %d ]:%d );		\n",	\
										xc-I[ ixH ],				xc,					ixH, I[ ixH ]		);	\

	#define dBUG_NEW_DΩ	cS = sprintf( aString, "\r<NEW_CUBE_\xEA_AS_MODSxHPASS> iC: %lld	\n", iC );			\
			if( oCS != O[ ocª ] )	{	cS+=sprintf( aString+cS, lightning );	\
								cS += sprintf( aString+cS, "!	( oCS: %d ) != ( O[ oc\xA6: %d ]: %d )\n	Last time this was a problem, it was because of a hackish way of initializing EPIGEN by pre-incrementing oCS.  \n", oCS, ocª, O[ocª] );	\
							}	\
			cS+=	sprintf( aString+cS,	"alt:	( hp\xEA_q: %d )	= ( CS: %d )			\10	- ( O[ ixH:%d]: %d )	-16;	\n\n",	\
										hpΩ_q,				CS,					ixH, O[ ixH ]			);	\
			cS+=	sprintf( aString+cS,	"	( hp\xEA_q: %d )	= ( CS: %d )			\10	- ( pre\xEA_q: %d )	-16;	\n\n",	\
										hpΩ_q,				CS,					preΩ_q				);	\
			\
			cS+=	sprintf( aString+cS,	"	( post\xEA_q: %d )	= ( O\xA6[ inM: %d ]: %d )	- ( O\xA6[ ix\xEA: %d ]: %d );	\n",	\
										postΩ_q,				inM,	Oª[ inM ],		ixΩ, Oª[ ixΩ ]			);	\
			cS+=	sprintf( aString+cS,	"	( pre\xEA_xc: %d )				\n",	\
										preΩ_xc						);	\
		AvDBUG_PUSH( aString, cS );
	//								char	preΩ_xc_=	I[	ixH-1 ]	- 	I[ ixΩ ];							\
			cS+=	sprintf( aString+cS,	"alt:	( pre\xEA_xc_: %d )	= ( I[ ixH-1: %d ]: %d )	\10	- ( I[ ix\xEA: %d ]: %d );	\n",	\
										preΩ_xc_,			ixH-1, I[ ixH-1 ],		ixΩ,	I[ ixΩ ]			);	\
			cS+=	sprintf( aString+cS,	"	( post\xEA_xc: %d )	= ( izM: %d )			\10	- ( ix\xEA: %d );		\n",	\
										postΩ_xc,			izM,					ixΩ					);	\
			cS+=	sprintf( aString+cS,	"	( rel\xEA_c: %d )	= ( post\xEA_xc: %d )		- ( pre\xEA_xc: %d );	\n\n",\
										relΩ_c,				postΩ_xc,			preΩ_xc				);		AvDBUG_PUSH( aString, cS );

	#define dBUG_NEW_DΩ_CLOSE	cS = sprintf( aString, "\r	</NEW_CUBE_\xEA_AS_MODSxHPASS>\n");			AvDBUG_PUSH( aString, cS );
#else
	#define dBUG_MOD_Eº
	#define dBUG_MOD_Eº_CLOSE
	#define dBUG_MOD_Aº
	#define dBUG_MOD_Aº_CLOSE
	#define dBUG_NEW_EΩ
	#define dBUG_NEW_EΩ_CLOSE
	#define dBUG_NEW_DΩ
	#define dBUG_NEW_DΩ_CLOSE
#endif

#ifdef DEBUG_SvCOMMIT_L3		//	paranoid integrity checks which are silent until there's a problem
	#define dBUG_1X3_XCª_SW						if( ixM >= iz¹){	printf( lightning );	printf("!	ixM( %d ) must be less-than iz¹( %d ).  invalid value for xcª (%d) within subcase 1X3 of %s: %s line %d \n",		ixM,	iz¹,	xcª, __FUNCTION__, __FILE__, __LINE__ );	}	\
												if( izM <= ix¹){	printf( lightning );	printf("!	izM( %d ) must be greater-than ix¹( %d ).  invalid value for xcª (%d) within subcase 1X3 of %s: %s line %d \n",	izM,	ix¹,	xcª, __FUNCTION__, __FILE__, __LINE__ );	}
#else
	#define dBUG_1X3_XCª_SW
#endif

// the following(4) macros are fragment-generating code blocks shared within _sv_commit() by main cases 1X2H, 1X2M, 1X3 and 1X4.

/*		NEW_CUBE_Ω_AS_MODSxHPASS()		*/
#define	NEW_CUBE_Ω_AS_MODSxHPASS()							/*	hpΩ_q=CS-O[ ixH ];	*/			\
			preΩ_q	=	O[	ixH	]	-		oCS;	/* oCS is a ticking timebomb 2026-09-13 precursor #97 */	\
		/*	preΩ_q	=	O[	ixH	]	-	O[	ocª	];	*/				hpΩ_q	=		CS-16	-		preΩ_q;		\
			postΩ_q	=	Oª[	inM ]	-	Oª[	ixΩ	];		CSΩ=16+	hpΩ_q + postΩ_q;					\
			pΩ=( cubeΩ	= SvPVbyte_nolen(	svΩ = newSVpvz(	CSΩ |0x6 ) ) )+16;	SvCUR_set( svΩ, CSΩ );			dBUG_SvCUR( svΩ, CSΩ );	\
			postΩ_xc	= 		izM		-		ixΩ;			cubeΩ[	CSΩ ]=0;							\
			relΩ_c		=	postΩ_xc	-		icO;			\
			hpΩ_c		=		zc		-		icO;													dBUG_NEW_DΩ	\
			\
			if( hpΩ_c ){	enXhp	=	postΩ_xc| ( hpΩ_c<< 3 );											*Edge( cubeΩ ) = *Edge( cube ); 	/* Edge of [iC] is conserved */	\
				if(	relΩ_c< 0){		bs = ( -relΩ_c ) << 3;	hipa = *( (ui64*) cube ) >>bs;	}	\
				else{				bs =   relΩ_c	<< 3;	hipa = *( (ui64*) cube )<< bs;	}	\
				switch(	enXhp	){	SwCASE_LPXOVER_10Y( hipa,					*( (ui64*)( K +ixΩ ) ),	*( (ui64*) cubeΩ )  )  	}			\
			}else{				/*	^lowpass crossover wye	 ^high passthrough, shifted	^low inclusion src		^wye output		*/	*Edge( cubeΩ ) = E[ izM ];		/* Edge changed			*/	\
				switch(	postΩ_xc ){	SwCASE_LOWPASS_1I(							*( (ui64*)( K +ixΩ ) ),	*( (ui64*) cubeΩ )	)	}			\
				}				/*	^lowpass inline assignment						^definitive src			^trimmed output	*/	\
			if(		postΩ_q	)	{	iCEpACK( pΩ,	ixΩ, izM, inM,			cubeΩ );												\
								}/*	^re-pack modified q-data vectors ixΩ..izM to cubeΩ[ 16..16+postΩ_q-1 ]	*/									\
			if(		hpΩ_q	)	{	XLOAD(	pΩ,	O[ ixH ],		hpΩ_q,	cube,	cubeΩ );				\
								}/*	^crossload (hpΩ_q) high-pass bytes from *(cube+O[ ixH ] ) to *pΩ		*/	dBUG_NEW_DΩ_CLOSE

/*		NEW_CUBE_Ω_AS_HIGHPASS()		*/
#define	NEW_CUBE_Ω_AS_HIGHPASS()									hpΩ_q=CS-O[ ixΩ ];				\
														CSΩ=16+	hpΩ_q;							dBUG_NEW_EΩ	\
			pΩ=( cubeΩ	= SvPVbyte_nolen(	svΩ = newSVpvz(	CSΩ |0x6 ) ) )+16;	SvCUR_set( svΩ, CSΩ );			dBUG_SvCUR( svΩ, CSΩ );	\
												cubeΩ[	CSΩ ]=0;										*Edge( cubeΩ ) = *Edge( cube );	/* set Edge() of high cube	(there is a displacement, so Edge() of pre-op cube is conserved)	*/\
			switch(	zcΩ		){		SwCASE_LOWPASS_1I(	*( (ui64*)( cube +I[	ixΩ ] ) ),						*( (ui64*)	cubeΩ )	);	 }	\
								/*	^inline lowpass		^high passthrough src							^lowpass output	*/		\
			if(		hpΩ_q )	{		XLOAD(	pΩ,	O[ ixΩ ],	hpΩ_q,		cube,	cubeΩ );				\
							}	/*	^crossload (hpΩ_q) high-pass bytes from *(cube+O[ ixΩ ] ) to *pΩ		*/	dBUG_NEW_EΩ_CLOSE


/*		MOD_CUBE_0_AS_LPASS(		ix$ )	*/
#define	MOD_CUBE_0_AS_LPASS( 		ix$ )	/*	if( ixM >izº ){	*/											dBUG_MOD_Eº	\
				switch(		zcº ){	SwCASE_LOWPASS_1IS(	*( (ui64*) cubeº )	)		}					\
				if( CS != O[	ix$ ] ){			SvCUR_set(	sv,	O[	ix$ ] );	cubeº[	O[	ix$ ] ]=0;			dBUG_SvCUR( sv,  O[ ix$] );	}	\
																									dBUG_MOD_Eº
/*		MOD_CUBE_0_AS_LPASSxMODS()	*/
#define	MOD_CUBE_0_AS_LPASSxMODS( ix$ )																dBUG_MOD_Aº	\
				if( CS <  Oª[	ix$ ] ){ cubeº  =	SvGROW(	sv,	Oª[	ix$ ] +1 );								\
											SvCUR_set(	sv,	Oª[	ix$ ] );	cubeº[	Oª[	ix$ ] ]=0;			dBUG_SvCUR( sv, Oª[	ix$ ] );	}	\
			else	if( CS != Oª[	ix$ ] ){			SvCUR_set(	sv,	Oª[	ix$ ] );	cubeº[	Oª[	ix$ ] ]=0;			dBUG_SvCUR( sv, Oª[	ix$ ] );	}	\
																									\
			pº =cubeº +O[	ixM	];			postº_xc	= izº - ixM;											\
						lpXen	=	icI 	|(	postº_xc<< 3 );											\
			switch(		lpXen	){	SwCASE_LPXOVER_01T( *( (ui64*) (K+ixº) ),								*( (ui64*) cubeº)  );  }							\
								/*	^lowpass crossover tee	^high inclusion src								^low passthrough / tee output	*/				\
					postº_q		=	Oª[	ix$	]	-	Oª[ 	ixM	];										\
			if(		postº_q )	{		iCEPACK( pº, 	ixM, izº, ix$,			cubeº ); 							\
							}	/*	^re-pack modified q-data vectors ixM..izº to cubeº[ O[ ixM ]..O[ izº ] ] 	*/	dBUG_MOD_Aº_CLOSE
