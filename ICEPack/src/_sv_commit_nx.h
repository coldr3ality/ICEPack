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
#if defined( DEBUG_SvCOMMIT_L0 ) || defined( DEBUG_SvCOMMIT_L1) || defined( DEBUG_SvCOMMIT_L1X )
extern	size_t	avdbuginx_dmarkcase;
extern	unsigned short 	subcase;
#endif

#ifdef DEBUG_SvCOMMIT_L1X	// process audit
	#define dBUG_NX1	/*	pre_q		= O[ inM	]	- O[ ixM ];		/* pre-op mod range q-len	*/	\
						/*	hp_c		=	zc		-	icO;			/* high passthrough cycla	*/	\
						/*	pre_xc		= I[	ixH-1 ]	-	I[	ixM	];	/* pre-op mod range cycla				(simplex ver., unaware of cube boundaries)	*/	\
						/*	rel_c		=	post_xc	-		pre_xc;	/* pre-to-post mod range size difference	(simplex... just here for learning purposes)	*/	\
						/*	postΩ_xc	=	izM		-		ocª;		/*	#5 passes but #13 doesn't (can't handle mutex wrapping) 		*/					\
						{cS =sprintf( aString, "\n_sv_commit_nx(%3d):	 locus : %3d.%d..%d.%-3d	 pre_xc: %3d	\10	 pre\xEA_xc: %3d	\10	 pre_q: %3d	\10	 pre\xEA_q: %3d	\10	oCS: %-3lld bytes\n",	\
													tcª,			 iCI, icI,	iC, icO,			 pre_xc,			preΩ_xc,				 pre_q,			 preΩ_q,				oCS				);	\
							cS+=sprintf( aString +cS,	"\t\x9Fsub NX1	 matrix: %5d..%-5d \10 \10	post_xc: %3d	\10	post\xEA_xc: %3d	\10	post_q: %3d	\10	post\xEA_q: %3d	\10	CS/\xEA: %3lld/%-3lld\n",	\
																 ixM, izM,				post_xc,			postΩ_xc,			post_q,			postΩ_q,				CS, CSΩ			);	\
							cS+=sprintf( aString +cS,		"			oc /xc : %5d/%-5d	\10	\10	  rel_c: %3d	\10	  rel\xEA_c: %3d	\10	 rel_q: %3d	\10	 rel\xEA_q: %3d	\n",						\
																oc,			xc,			  rel_c,			  relΩ_c,				 rel_q,			 relΩ_q								);	\
							cS+=sprintf( aString +cS,		"			oc\xA6/xc\xA6: %5d/%-5d	   hp_c: %3d	\10	  lp\xEA_q: %3d	\10	  hp_q: %3d						\n\n",	\
																ocª,			xcª,			   hp_c,			  lpΩ_q,				  hp_q								);	\
							cS+=sprintf( aString +cS,		"			zc\xEA: %3d\n",	zcΩ );	\
							AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase);	\
							}

	#define dBUG_NX2L	/*	hpΩ_c	=		xc		-	I[	ixΩ	];	*/	\
						{cS =sprintf( aString,"\n_sv_commit_nx(%3d):	 locus : %3d.%d..%d.%-3d	 pre_xc: %3d	\10	 hp\xEA_c: %3d	\10	\10	 CSI/CS: %3lld/%-3lld  bytes  \n",	\
													tcª,			 iCI, icI,	iC, icO,			pre_xc,			 hpΩ_c,					 CSI,		CS				);	\
							cS+=sprintf( aString +cS,	"\t\x9Fsub NX2L	 matrix: %5d..%-5d	\10	\10	post_xc: %3d			\10	\10	\10	\10	\10	CS\xA7/CS\xEA: %3d/%-3lld bytes\n", \
																 ixM, izM,				post_xc,									Oª[ ixΩ],	CSΩ	);	\
							cS+=sprintf( aString +cS,		"			oc /xc : %5d/%-5d	\10	\10	  rel_c: %3d	\10	rel\xEA_c: %3d	\10	\10	    oCS: %3d \n",	\
																oc,			xc,			  rel_c,			oc-I[ ixΩ ],				    oCS	);	\
							cS+=sprintf( aString +cS,		"			oc\xA6/xc\xA6: %5d/%-5d	  pre_q: %3d	\10	\n",		\
																ocª,			xcª,			  pre_q			);		\
							cS+=sprintf( aString +cS,					"						 post_q: %3d	\10	\n",		\
																						 post_q			);		\
							cS+=sprintf( aString +cS,					"						  rel_q: %3d	\10	rel\xEA_q: %3d	\n",		\
																						  rel_q,			relΩ_q			);		\
							cS+=sprintf( aString +cS,					"						  hp\xA7_q: %3d	hp\xEA_q: %3d	\n",		\
																						  hpº_q,			hpΩ_q			);		\
							AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase); \
							}


	#define dBUG_NX2H	/*	hpΩ_c	=		xc		-	I[	ixΩ	];	*/	\
						/*	preΩ_q	=	O[	inM	]	-	O[	ixM	];	*/	\
						{cS =sprintf( aString,"\n_sv_commit_nx(%3d):	 locus : %3d.%d..%d.%-3d	 pre_xc: %3d	\10	  pre_q: %3d	\10	\10	 CS: %-3d bytes	\10	oCS: %-3lld bytes	( alt CS\xEA: %-3lld )\n",	\
													tcª,			 iCI, icI,	iC, icO,			pre_xc,			  pre_q,				 CS,					oCS,			CSⁿ	);	\
							cS+=sprintf( aString +cS,	"\t\x9Fsub NX2H	 matrix: %5d..%-5d \10 \10	post_xc: %3d	\10	post_q: %3d	\10	\10	CS\xEA: %-3d bytes	CSI: %-3lld bytes\n\t",	\
																 ixM, izM,					post_xc,		post_q,				CSΩ,				CSI				);	\
							cS+=sprintf( aString +cS,						"					  rel_c: %3d	\10	 rel_q: %3d\n",		\
																						rel_c,			 rel_q	);			\
							cS+=sprintf( aString +cS,		"			oc /xc : %5d/%-5d	\10	\10	 rel\xEA_c: %3d	rel\xEA_q: %3d\n",		\
																oc,			xc,			 relΩ_c,			relΩ_q	);			\
							cS+=sprintf( aString +cS,		"			oc\xA6/xc\xA6: %5d/%-5d	  hp\xEA_c: %3d	 hp\xEA_q: %3d\n\n",	\
																ocª, 			 xcª,			  hpΩ_c,			 hpΩ_q			);	\
							AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase); \
							}
	#define dBUG_NX2M {	cS =sprintf( aString,"\n_sv_commit_nx(%3d):	 locus : %3d.%d..%d.%-3d	 pre\xEA_xc: %3d	 pre\xEA_q: %3d		\10	\10		 CS: %-3lld bytes	oCS: %-3lld bytes\n",	\
														tcª,		 iCI, icI,	iC, icO,			icO, 			preΩ_q,							 CS,				oCS	);				\
							cS+=sprintf( aString +cS, "\t\x9Fsub NX2M	 matrix: %5d..%-5d \10 \10 	post\xEA_xc: %3d	post\xEA_q: %3d	hp\xEA_c: %-3d	CSI: %-3d bytes\n",		\
																 ixM, izM,				postΩ_xc,		postΩ_q,			hpΩ_c,			Oª[ixΩ]				);	\
							cS+=sprintf( aString +cS,		"			oc /xc : %5d/%-5d	\10	\10	  rel\xEA_c: %3d	 rel\xEA_q: %3d	 hp_q: %3d	\10	CS\xEA: %-3lld bytes\n",			\
																oc,			 xc,			  relΩ_c,			 relΩ_q,			 hp_q,			CSΩ	);	\
							cS+=sprintf( aString +cS,		"			oc\xA6/xc\xA6: %5d/%-5d					\10	\10	\10	\10	hp\xEA_i: %3d	\n\n",			\
																ocª,			 xcª,											hpΩ_i					);	\
							AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase); \
							}
	#define dBUG_NX3	{cS =sprintf( aString,"\n_sv_commit_nx(%3d):	 locus : %3d.%d..%d.%-3d	 pre\xA7_xc: %3d	  pre1_xc: %3d \10 \10	  pre\xEA_xc: %3d \10 \10	CS: %-3lld bytes	oCS: %-3lld bytes\n",	\
													tcª,			 iCI, icI,	iC, icO,			 preº_xc,			  pre¹_xc,				  preΩ_xc,				CS,				oCS	);				\
						cS+=sprintf( aString +cS,	"\t\x9Fsub NX3-%c%c%c\t matrix: %5d..%-5d \10 \10	post\xA7_xc: %3d	 post1_xc: %3d \10 \10	 post\xEA_xc: %3d \10 \10	CSI/1/Z: %2lld/%2lld/%2lld bytes\n", \
		64+(	subcase&7), 64+( (subcase>>3)&7), 64+( (subcase>>9)&7), 		 ixM, izM,				postº_xc,			 post¹_xc,			 postΩ_xc,				CSI,	CS¹, CSΩ	);	\
							cS+=sprintf( aString +cS,		"			oc /xc : %5d/%-5d	\10	\10	  rel\xA7_c: %3d	   rel1_c: %3d \10 \10	   rel\xEA_c: %3d\n",		\
																oc,			 xc,			  zcº-zc,			   rel¹_c,				   relΩ_c		);			\
							cS+=sprintf( aString +cS,		"			oc\xA6/xc\xA6: %5d/%-5d	  pre\xA7_q: n/a	   pre1_q: n/a \10 \10	   pre\xEA_q: %3d\n",		\
																ocª,	 		 xcª,			  				  					   preΩ_q	);				\
							cS+=sprintf( aString +cS,					"	 zc: %3d	zc\xEA: %3d\t	 post\xA7_q: %3d	  post1_q: %3d \10 \10	  post\xEA_q: %3d\n",		\
																	 zc,		zcΩ,		 postº_q,			  post¹_q,			 	  postΩ_q	);			\
							cS+=sprintf( aString +cS,					"						  rel\xA7_q: n/a \10	   rel1_q: n/a \10 \10	   rel\xEA_q: %3d\n",		\
																															   relΩ_q	);				\
							cS+=sprintf( aString +cS,					"						\10		\10		    hp1_q: %3d \10 \10	    hp\xEA_q: %3d\n",		\
																										    hp¹_q,				    hpΩ_q	);				\
							cS+=sprintf( aString +cS,					"						\10		\10		    hp1_o: %3d	\n\n",							\
																										    hp¹_o		);								\
							cS+=sprintf( aString +cS,		"	ix\xA7/iz\xA7: %d/%d	ix1/iz1: %d/%d	ix\xEA/iz\xEA: %d/%d\n\n",	\
														ixº, izº, ix¹, iz¹, ixΩ, izΩ );	\
							\
							AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase); \
							}

	#define dBUG_DΩ_VERBOMETRY 	preΩ_q = O[ inM ] - O[ ixΩ ];
	#define dBUG_EΩ_VERBOMETRY 	preΩ_q = preΩ_c = postΩ_c = postΩ_q=0;	relΩ_c	=	zcΩ-zc;
	#define dBUG_NX4 { cS =sprintf( aString,"\n_sv_commit_nx(%3d):	  locus : %3d.%d..%d.%-3d	 pre\xA7_xc: %3d	\10	  pre1_xc: %3d	\10	  pre\xFD_xc: %3d \10	  pre\xEA_xc: %3d	\10	\10	CS: %-3lld bytes	oCS: %-3lld bytes\n",	\
													tcª,			 iCI, icI,	iC, icO,			preº_xc,			 	 pre¹_xc,				  pre²_xc,				  preΩ_xc,				CS,				oCS	);				\
						cS+=sprintf( aString +cS,	"\t\x9Fsub NX%3d-%c%c%c%c\t  matrix: %5d..%-5d	post\xA7_xc: %3d	\10	 post1_xc: %3d	\10	 post\xFD_xc: %3d \10	 post\xEA_xc: %3d	\10	\10	CSI/1/Y/Z: %2lld/%2lld/%2lld/%2lld bytes\n", \
						endo_c+4, 64+( subcase&7),	64+( (subcase>>3)&7),		\
							64+( (subcase>>6)&7),	64+( (subcase>>9)&7), ixM, izM,				postº_xc,				 post¹_xc,			 post²_xc,			 postΩ_xc,				CSI,	CS¹, CS², CSΩ	);	\
							cS+=sprintf( aString +cS,		"			iCI..iC\xA6: %5d..%-5d	\10	  rel\xA7_c: %3d	\10	   rel1_c: %3d	\10	\10	   rel\xFD_c: %3d \10	   rel\xEA_c: %3d	\n",		\
																iCI, iCª,					zcº-zc,				   rel¹_c,				   rel²_c,				   relΩ_c				);	\
							cS+=sprintf( aString +cS,		"			 oc /xc : %5d/%-5d	\10	\10	   lp\xA7_c: n/a	\10	    lp\xA7_c: %3d	\10	    lp\xFD_c: n/a	\10	    lp\xEA_c: n/a	\n",		\
																oc,			 xc,								    lp¹_c														);	\
							cS+=sprintf( aString +cS,		"			 oc\xA6/xc\xA6: %5d/%-5d	   hp\xA7_c: n/a	\10	    hp1_c: n/a	\10	\10	    hp\xFD_c: %3d \10	    hp\xEA_c: %3d	\n",		\
																 ocª,			xcª,													    hp²_c,				    hpΩ_c				);	\
							cS+=sprintf( aString +cS,		"			  zc/zc\xEA: %5d/%-5d	\10	  pre\xA7_q: n/a	\10	   pre1_q: n/a	\10	\10	   pre\xFD_q: n/a \10	   pre\xEA_q: %3d	\n",		\
																  zc,			zcΩ,			  				  											   preΩ_q				);	\
							cS+=sprintf( aString +cS,					"						 post\xA7_q: %3d \10	  post1_q: %3d	\10	  post\xFD_q: %3d \10	  post\xEA_q: %3d	\n",		\
																						 postº_q,				  post¹_q,				  post²_q,				  postΩ_q			);	\
							cS+=sprintf( aString +cS,					"						  rel\xA7_q: n/a	\10	   rel1_q: n/a	\10	\10	   rel\xFD_q: n/a \10 \10	   rel\xEA_q: %3d	\n",		\
																																					   relΩ_q				);	\
							cS+=sprintf( aString +cS,					"						   lp\xA7_q: n/a	\10	   lp1_q: %3d	\10	\10	    lp\xFD_q: n/a \10 \10	    lp\xEA_q: %3d	\n",		\
																											   lp¹_q,									    lpΩ_q				);	\
							cS+=sprintf( aString +cS,					"						   hp\xA7_q: n/a	\10	   hp1_q: n/a	\10	\10	    hp\xFD_q: %3d \10	    hp\xEA_q: %3d	\n",		\
																																    hp²_q,				    hpΩ_q				);	\
							AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase); \
							}
#else
	#ifdef	dBUG_SvCOMMIT_L1	
	#define dBUG_NX1 { cS =sprintf( aString, "\n_sv_commit_nx(%3d):	 locus : %3d.%d..%d.%-3d	\10	oCS: %-3lld bytes\n",	\
													tcª,			 iCI, icI,	iC, icO,			oCS				);	\
							cS+=sprintf( aString +cS,	"\t\x9Fsub NX1	 matrix: %5d..%-5d	\10	\10	CS/\xEA: %3lld/%-3lld\n",	\
																 ixM, izM,				CS, CSΩ			);	\
							cS+=sprintf( aString +cS,		"			oc /xc : %5d/%-5d	\10	\10	\n",					\
																oc,			xc			);		\
							cS+=sprintf( aString +cS,		"			oc\xA6/xc\xA6: %5d/%-5d	\n\n",	\
																ocª,			xcª			);		\
							AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase);					\
							}

	#define dBUG_NX2L { cS =sprintf( aString,"\n_sv_commit_nx(%3d):	 locus : %3d.%d..%d.%-3d	\10	 CSI/CS: %3lld/%-3lld  bytes  \n",	\
													tcª,			 iCI, icI,	iC, icO			 CSI,		CS				);	\
							cS+=sprintf( aString +cS,	"\t\x9Fsub NX2L	 matrix: %5d..%-5d	\10	\10	CS\xA7/CS\xEA: %3lld/%-3lld bytes\n", \
																 ixM, izM					Oª[ ixΩ],	CSΩ	);	\
							cS+=sprintf( aString +cS,		"			oc /xc : %5d/%-5d	\10	\10	    oCS: %3d \n",	\
																oc,			xc			   oCS	);	\
							cS+=sprintf( aString +cS,		"			oc\xA6/xc\xA6: %5d/%-5d	\n",		\
																ocª,			xcª			);		\
							AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase); \
							}


	#define dBUG_NX2H { cS =sprintf( aString,"\n_sv_commit_nx(%3d):	 locus : %3d.%d..%d.%-3d		 CS: %-3lld bytes	\10	oCS: %-3lld bytes	( alt CS\xEA: %-3lld )\n",	\
													tcª,			 iCI, icI,	iC, icO,			 CS,					oCS,			CSⁿ	);	\
							cS+=sprintf( aString +cS,	"\t\x9Fsub NX2H	 matrix: %5d..%-5d \10 \10	 CS\xEA: %-3lld bytes	CSI: %-3lld bytes\n\t",	\
																 ixM, izM,				CSΩ,				CSI				);	\
							cS+=sprintf( aString +cS,		"			oc /xc : %5d/%-5d	\10	\10	\n",		\
																oc,			xc			);		\
							cS+=sprintf( aString +cS,		"			oc\xA6/xc\xA6: %5d/%-5d	\n\n",	\
																ocª, 			 xcª			);		\
							AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase);					\
							}
	#define dBUG_NX2M { cS =sprintf( aString,"\n_sv_commit_nx(%3d):	 locus : %3d.%d..%d.%-3d	CS: %-3lld bytes	oCS: %-3lld bytes\n",	\
														tcª,		 iCI, icI,	iC, icO,			CS,				oCS	);				\
							cS+=sprintf( aString +cS, "\t\x9Fsub NX2M	 matrix: %5d..%-5d \10 \10 	\n",		\
																 ixM, izM					);		\
							cS+=sprintf( aString +cS,		"			oc /xc : %5d/%-5d	\10	\10	CS\xEA: %-3d bytes	\n",			\
																oc,			 xc,			CSΩ				);	\
							cS+=sprintf( aString +cS,		"			oc\xA6/xc\xA6: %5d/%-5d	\n\n",	\
																ocª,			 xcª			);		\
							AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase); 					\
							}
	#define dBUG_NX3 { cS =sprintf( aString,"\n_sv_commit_nx(%3d):	 locus : %3d.%d..%d.%-3d	CS: %-3lld bytes	oCS: %-3lld bytes\n",	\
													tcª,			 iCI, icI,	iC, icO,			CS,				oCS	);				\
						cS+=sprintf( aString +cS,	"\t\x9Fsub NX3-%c%c%c\t matrix: %5d..%-5d \10 \10	CSI/1/Z: %2lld/%2lld/%2lld bytes\n", \
		64+(	subcase&7), 64+( (subcase>>3)&7), 64+( (subcase>>9)&7), 		 ixM, izM,				CSI,	CS¹, CSΩ	);	\
							cS+=sprintf( aString +cS,		"			oc /xc : %5d/%-5d	\10	\10	\n",		\
																oc,			 xc			);		\
							cS+=sprintf( aString +cS,		"			oc\xA6/xc\xA6: %5d/%-5d	\n",		\
																ocª,	 		 xcª			);		\
							cS+=sprintf( aString +cS,		"	ix\xA7/iz\xA7: %d/%d	ix1/iz1: %d/%d	ix\xEA/iz\xEA: %d/%d\n\n",	\
														ixº, izº, ix¹, iz¹, ixΩ, izΩ );					\
							AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase); 					\
							}

	#define dBUG_DΩ_VERBOMETRY 	preΩ_q = O[ inM ] - O[ ixΩ ];
	#define dBUG_EΩ_VERBOMETRY 	preΩ_q = preΩ_c = postΩ_c = postΩ_q=0;	relΩ_c	=	zcΩ-zc;
	#define dBUG_NX4 {cS =sprintf( aString,"\n_sv_commit_nx(%3d):	  locus : %3d.%d..%d.%-3d	CS: %-3lld bytes	oCS: %-3lld bytes\n",	\
													tcª,			 iCI, icI,	iC, icO,			CS,				oCS	);				\
						cS+=sprintf( aString +cS,	"\t\x9Fsub NX%3d-%c%c%c%c\t  matrix: %5d..%-5d	CSI/1/Y/Z: %2lld/%2lld/%2lld/%2lld bytes\n", \
						endo_c+4, 64+( subcase&7),	64+( (subcase>>3)&7),		\
							64+( (subcase>>6)&7),	64+( (subcase>>9)&7), ixM, izM,				CSI,	CS¹, CS², CSΩ	);	\
							cS+=sprintf( aString +cS,		"			iCI..iC\xA6: %5d..%-5d	\10	\n",		\
																iCI, iCª,					);	\
							cS+=sprintf( aString +cS,		"			 oc /xc : %5d/%-5d	\10	\10	\n",		\
																oc,			 xc,			);	\
							cS+=sprintf( aString +cS,		"			 oc\xA6/xc\xA6: %5d/%-5d	\n",		\
																 ocª,			xcª			);	\
							cS+=sprintf( aString +cS,		"			  zc/zc\xEA: %5d/%-5d	\10	\n",		\
																  zc,			zcΩ		);	\
							AvDBUG_RESERVATION( aString, cS, avdbuginx_dmarkcase); \
							}

	#else
		#ifdef DEBUG_SvCOMMIT_L1F
			#define dBUG_NX1	cS=sprintf( aString, "N1 \r");		AvDBUG_PUSH( aString, cS );
			#define dBUG_NX2L	cS=sprintf( aString, "NL \r");	AvDBUG_PUSH( aString, cS );
			#define dBUG_NX2H	cS=sprintf( aString, "NH \r");	AvDBUG_PUSH( aString, cS );
			#define dBUG_NX2M	cS=sprintf( aString, "NM \r");	AvDBUG_PUSH( aString, cS );
			#define dBUG_NX3	cS=sprintf( aString, "N3 \r");		AvDBUG_PUSH( aString, cS );
			#define dBUG_NX4	cS=sprintf( aString, "N4 \r");		AvDBUG_PUSH( aString, cS );
		#else
			#define dBUG_NX1
			#define dBUG_NX2L
			#define dBUG_NX2H
			#define dBUG_NX2M
			#define dBUG_NX3
			#define dBUG_NX4
		#endif
		#define dBUG_DΩ_VERBOMETRY
		#define dBUG_EΩ_VERBOMETRY
	#endif
#endif
#ifdef DEBUG_SvCOMMIT_L3		//	paranoid integrity checks which are silent until there's a problem
	#define dBUG_NX3_XCª_SW						if( ixM >= iz¹){	printf( lightning );	printf("!	ixM; %d must be less-than iz1: %d.		invalid value for tc\xA6 (%d) within subcase NX3 of %s: %s line %d \n",		ixM,	iz¹,	tcª, __FUNCTION__, __FILE__, __LINE__ );	}	\
												if( izM <= ix¹){	printf( lightning );	printf("!	izM: %d must be greater-than ix1: %d.	invalid value for tc\xA6 (%d) within subcase NX3 of %s: %s line %d \n",	izM,	ix¹,	tcª, __FUNCTION__, __FILE__, __LINE__ );	}
#else
	#define dBUG_NX3_XCª_SW
#endif

#ifdef DEBUG_SvCOMMIT_L4
	#define	dBUG_MOD_Aº( ix$)	cS = sprintf( aString,	"\r<MOD_CUBE_I_AS_LPASS > iCI: %lld	CSI: O[ %s: %d ]: %d )	zcOf( cubeº ), zc\xA7: %d, %d	I[ %s: %d ]: %d\n",		\
																		iCI,			#ix$, ix$, O[ ix$ ],	zcOf( cubeº ), zcº,				#ix$, I[ ix$ ]		);	AvDBUG_PUSH( aString, cS );
	#define	dBUG_MOD_Aº_CLOSE	cS = sprintf( aString, "\r	</MOD_CUBE_I_AS_LPASS >\n\n\n");														AvDBUG_PUSH( aString, cS );
	#define	dBUG_MOD_Bº( ix$)	cS = sprintf( aString,	"\r<MOD_CUBE_I_AS_LPASSxMODS> iCI: %lld	ix\xA7/iz\xA7: %d/%d	CSI/\xA7: %d/%d	O\xA6[ ix$: %d ]: %d	O[ ix\xA7: %d ]: %d\n",			\
																				iCI,		ixº, izº,				CSI,	CSº,			ix$, 	 Oª[ ix$],			ixº,	O[ixº]	);		AvDBUG_PUSH( aString, cS );
	#define	dBUG_MOD_Bº_CLOSE	cS = sprintf( aString, "\r	</MOD_CUBE_I_AS_LPASSxMODS>\n\n\n");												AvDBUG_PUSH( aString, cS );	
	#define	dBUG_MOD_EΩ																				dBUG_EΩ_VERBOMETRY 	\
			cS=  	sprintf( aString,		"\r<MOD_CUBE_\xEA_AS_HIGHPASS>	iC: %lld\n", iC );					\
			cS+=	sprintf( aString+cS,	"	( CS\xEA: %d )	\10	= (	CS: %d )		\10	\10	+ ( rel\xEA_q: %+d )	\n",	\
										CSΩ,				CS,					relΩ_q				);	\
			cS+=	sprintf( aString+cS,	"	( hp\xEA_q: %d )	= (	CS: %d )-16		\10	- ( pre\xEA_q: %d);	 	\n",	\
										hpΩ_q,				CS,					preΩ_q				);	\
			cS+=	sprintf( aString+cS,	"	zc/zc\xEA: %d/%d	zcOf( cube ): %d	CS: %lld	SvCUR( sv ): %lld	SvCUR( *(Aº+iC) ): %lld	\n",\
										zc,	zcΩ,		zcOf( cube ),		CS, 		SvCUR( sv ), 		SvCUR( *(Aº+iC) )	);	\
			cS+=	sprintf( aString+cS,	"	( pre\xEA_q: %d )	= ( O[ ixH: %d]: %d )		- ( oCS: %d );			\n\n",\
										preΩ_q,				ixH, O[ ixH ],			oCS			);			\
			cS+=	sprintf( aString+cS,	"alt:	( rel\xEA_q: %d )	= ( O\xA6[ inM: %d]: %d )	- ( O[ ixH %d ]: %d );			\n\n",\
										Oª[inM]-O[ixH],		inM, Oª[ inM ],		ixH, O[ ixH ]	);			AvDBUG_PUSH( aString, cS );
	#define	dBUG_MOD_EΩ_CLOSE	cS=	sprintf( aString, "\r	</MOD_CUBE_\xEA_AS_HIGHPASS>\n\n\n");			AvDBUG_PUSH( aString, cS );
	#define	dBUG_MOD_DΩ																				dBUG_DΩ_VERBOMETRY	\
			if( oCS != O[ ocª ] ){	AvDBUG_PUSH( lightning, 156 );	\
							cS=sprintf( aString, "!	( oCS: %d ) != ( O[ oc\xA6: %d ]: %d )\n	Last time this was a problem, it was because of a hackish way of initializing EPIGEN by pre-incrementing oCS.  \n", oCS, ocª, O[ocª] );		AvDBUG_PUSH( aString, cS ); }	\
			cS=  	sprintf( aString,		"\r<MOD_CUBE_\xEA_AS_MODSxHPASS>	iC: %lld	oCS, O[ oc\xA6 ]: %d. %d\n", iC, oCS, O[ocª] );		\
			cS+=	sprintf( aString+cS,	"	( CS\xEA: %d )	\10	= ( CS: %d )			\10	+ ( rel\xEA_q: %+d )	\n",	\
										CSΩ,				CS,					relΩ_q				);	\
			cS+=	sprintf( aString+cS,	"	( hp\xEA_i: %d )	= ( I[ ix\xEA: %d]: %d )		- ( oc\xA6: %d );		\n",	\
										I[ ixΩ ]-ocª,			ixΩ,  I[ ixΩ ],			ocª					);	\
			cS+=	sprintf( aString+cS,	"alt:	( hp\xEA_i: %d )	= ( ix\xEA: %d )		\10	\10	- ( ixH: %d );		\n",	\
										ixΩ-ixH,				ixΩ,					ixH					);	\
										hpΩ_o	= oCS +CS 	- O[ ixH-1 ]	-16; 							\
			cS+=	sprintf( aString+cS,	"alt:	( hp\xEA_o: %d )	= ( oCS: %d )+( CS: %d )	\10	- ( O[ ixH-1: %d ]: %d ) -16;\n\n",	\
										hpΩ_o,				oCS, CS,				ixH-1, O[ ixH-1 ]		);	\
			cS+=	sprintf( aString+cS,	"	( hp\xEA_c: %d )	= ( zc: %d )			\10	- ( icO: %d );			\n",	\
										zc-icO,				zc,					icO					);	\
			cS+=	sprintf( aString+cS,	"alt:	( hp\xEA_c: %d )	= ( xc\xA6: %d )	+1		- ( ixH: %d );			\n",	\
										xcª+1-ixH,			xcª,					ixH					);	\
			cS+=	sprintf( aString+cS,	"alt:	( hp\xEA_c: %d )	= ( xc: %d )			\10	- ( I[ ixH: %d ]:%d );		\n",	\
										xc-I[ ixH ],				xc,					ixH, I[ ixH ]		);	\
			cS+=	sprintf( aString+cS,	"	( hp\xEA_q: %d )	= ( CS: %d )			\10	- ( pre\xEA_q: %d )	-16;	\n\n",	\
										hpΩ_q,				CS,					preΩ_q				);	\
			\
			\
			cS+=	sprintf( aString+cS,	"	( pre\xEA_q: %d )	= ( O[ ixH: %d ]: %d )	\10	- ( oCS: %d );			\n",	\
										preΩ_q,				ixH, O[ ixH-1 ],		oCS					);	\
			cS+=	sprintf( aString+cS,	"	( post\xEA_q: %d )	= ( O\xA6[ inM: %d ]: %d )	- ( O\xA6[ ix\xEA: %d ]: %d );	\n",	\
										postΩ_q,				inM,	Oª[ inM ],		ixΩ, Oª[ ixΩ ]			);	\
			\
			\
			cS+=	sprintf( aString+cS,	"	( pre\xEA_xc: %d )	= ( I[ ixH-1: %d ]: %d )	\10	- ( oc: %d );			\n",	\
										preΩ_xc,				ixH-1, I[ ixH-1 ],		oc					);	\
									char	preΩ_xc_=	I[	ixH-1 ]	- 	I[ ixΩ ];							\
			cS+=	sprintf( aString+cS,	"alt:	( pre\xEA_xc_: %d )	= ( I[ ixH-1: %d ]: %d )	\10	- ( I[ ix\xEA: %d ]: %d );	\n",	\
										preΩ_xc_,			ixH-1, I[ ixH-1 ],		ixΩ,	I[ ixΩ ]			);	\
			cS+=	sprintf( aString+cS,	"	( post\xEA_xc: %d )	= ( izM: %d )			\10	- ( ix\xEA: %d );		\n",	\
										postΩ_xc,			izM,					ixΩ					);	\
			cS+=	sprintf( aString+cS,	"	( rel\xEA_c: %d )	= ( post\xEA_xc: %d )		- ( pre\xEA_xc: %d );	\n\n",\
										relΩ_c,				postΩ_xc,		preΩ_xc				);		AvDBUG_PUSH( aString, cS );

	#define	dBUG_MOD_DΩ_CLOSE	cS= sprintf( aString, "\r	</MOD_CUBE_\xEA_AS_MODSxHPASS>\n\n\n");		AvDBUG_PUSH( aString, cS );
#else
	#define	dBUG_MOD_Aº( ix$ )
	#define	dBUG_MOD_Aº_CLOSE
	#define	dBUG_MOD_Bº( ix$ )
	#define	dBUG_MOD_Bº_CLOSE
	#ifdef	DEBUG_SvCOMMIT_L1
		/* compute unused metrics anyway for debug info */
		#define	dBUG_MOD_DΩ				dBUG_DΩ_VERBOMETRY
		#define	dBUG_MOD_EΩ				dBUG_EΩ_VERBOMETRY
	#else
		#define	dBUG_MOD_DΩ
		#define	dBUG_MOD_EΩ
	#endif
	#define	dBUG_MOD_DΩ_CLOSE
	#define	dBUG_MOD_EΩ_CLOSE
#endif


/*		MOD_CUBE_I_AS_LPASSxMODS		(NX2M, NX3c, NX4L-2)	*/
#define	MOD_CUBE_I_AS_LPASSxMODS( ix$ )	\
					CSº= 16+ Oª[	ix$ ] - O[ ixº ];															dBUG_MOD_Bº( ix$ )	\
			if(		CSº >CSI )	{	cubeº  =	SvGROW(	svI, CSº +1 );	\
											SvCUR_set(	svI, CSº );	cubeº[ CSº ]=0;					dBUG_SvCUR( svI, CSº );	\
			}else{					cubeº =	SvPVbyte_nolen( svI);		\
				if(	CSº != CSI )	{ 			SvCUR_set(	svI, CSº );	cubeº[ CSº ]=0;					dBUG_SvCUR( svI, CSº );	\
				}				}																	\
		/*	pº =cubeº +16 +O[ ixM ] -O[ ixº ];	*/	\
			pº =cubeº+ O[ ixM ];		\
										postº_xc	= izº - ixM;											\
						lpXen	=	icI |(	postº_xc<< 3 );												\
			switch(		lpXen	){	SwCASE_LPXOVER_01T( *( (ui64*) (K+ixº) ),								*( (ui64*) cubeº)  );  }					\
								/*	^lowpass crossover tee	^high inclusion src								^low passthrough / tee output	*/		\
					postº_q		=	Oª[	ix$	]	-	Oª[ 	ixM	];																			\
			if(		postº_q )	{		iCEPACK( pº,  	ixM, izº, ix$,		cubeº );								\
							}	/*	^re-pack modified q-data vectors ixM..izº to cubeº[ O[ ixM ]..O[ izº ] ] 	*/	\
																									dBUG_MOD_Bº_CLOSE




/*		MOD_CUBE_I_AS_LPASS			*/
#define	MOD_CUBE_I_AS_LPASS(  ix$ )																	dBUG_MOD_Aº( ix$ )	\
			if( ixº!=0 ){/*	cS= sprintf( aString, "\n:	MOD_CUBE_I_AS_LPASS( %d ): RACK offset reset detected; ix\xA7=%d;	I[ ix\xA7: %d]: %d	O[ ix\xA7: %d]: %d\n\n", ixº, ixº, I[ixº], ixº, O[ixº] ); AvDBUG_PUSH( aString, cS);*/	\
					CSº= 16+ O[	ix$ ] - O[ ixº ];	\
			}else	CSº=	O[	ix$ ];		\
				/*		switch(		ix$ ){	SwCASE_LOWPASS_0IS(	*( (ui64*)		cubeº 			) ) }	*/	\
				/*		switch(		zcº ){	SwCASE_LOWPASS_1IS(	*( (ui64*) (	cubeº +I[ ixº ]	)	) ) }	*/	\
						switch(		zcº ){	SwCASE_LOWPASS_1IS(	*( (ui64*) 	cubeº			) ) }		\
			if( CSI != CSº )	{																			dBUG_SvCUR( svI, CSº );	\
											SvCUR_set(	svI,	CSº );  cubeº[ CSº ]=0;						\
						}																			\
	/*		cS=sprintf( aString, "\n!	CSI: %d	( CS\xA7: %d ) =16 +( O[ ix$: %d]: %d } - ( O[ ix\xA7: %d ]: %d )\n\n",		\
								CSI,		CSº, 			ix$, O[ ix$ ],		ixº, O[ ixº ]	);	AvDBUG_PUSH( aString, cS );	*/	\
																									dBUG_MOD_Aº_CLOSE


/*		MOD_CUBE_Ω_AS_HIGHPASS		(NX3a/b/c, NX4)*/
#define	MOD_CUBE_Ω_AS_HIGHPASS(	)							svΩ  	= sv; 							\
			relΩ_q	=		oCS		-	O[	ixΩ	];				CSΩ	= CS	+ relΩ_q;					\
																hpΩ_q	=CSΩ	-16;						\
		/*	[iCZ ]:	IN-SITU HIGHPASS REFLOW															*/	dBUG_MOD_EΩ;	\
			if(			relΩ_q >0 )	{							SvCUR_set(	svΩ,	O[ ixM ]  	);		/*	prevent copying obsolete data	*/	\
									/*	expand	*/		cubeΩ =	SvGROW(	svΩ,	CSΩ+1);						\
									ReFLOW_DX(	cube,	cubeΩ,	relΩ_q, hpΩ_q,		CSΩ,	CS,			__LINE__ );	\
			}else if(		relΩ_q< 0 )	{/*	compact	*/		cubeΩ =	cube;		/*		^dstLim	^srcLim	*/			\
									ReFLOW_AC(	cube,	cubeΩ,	relΩ_q, hpΩ_q,		16,		CS - hpΩ_q,	__LINE__ );	\
			}else		{			/*	nuh	*/	cubeΩ =	cube;				/*		^dst0	^src0	*/			\
						}			cubeΩ[ CSΩ ]=0;														dBUG_SvCUR( svΩ, CSΩ );	\
														SvCUR_set(	svΩ,	CSΩ );					\
		/*	[iCZ ]: 	UNSHIFT KEYBYTE SECTION															*/	\
			if(		zcΩ< zc		){	bs =( zc-zcΩ )<< 3;		*( (ui64*) cubeΩ )>>= bs;	/*	cS=sprintf( aString, "\r	*( (ui64*) cube\xEA	) >>=%d\n	%016llX\n	%016llX\n\n", bs,	Kc, *( (ui64*) cubeΩ ) );	AvDBUG_PUSH( aString, cS );	*/	\
			}else if(	zcΩ!=zc		){	bs =( zcΩ-zc )<< 3;		*( (ui64*) cubeΩ )<<= bs;	/*	cS=sprintf( aString, "\r	*( (ui64*) cube\xEA	) <<=%d\n	%016llX\n	%016llX\n\n", bs,	Kc, *( (ui64*) cubeΩ ) );	AvDBUG_PUSH( aString, cS );	*/	\
								}																		dBUG_MOD_EΩ_CLOSE


/*		MOD_CUBE_Ω_AS_MODSxHPASS	(NX3a/c, NX4)*/
#define	MOD_CUBE_Ω_AS_MODSxHPASS( )							svΩ  	= sv;	CS=SvCUR( sv );				\
			hpΩ_c	= zc			-	icO;				/*	alt:		hpΩ_c	=		xcª+1	-		ixH;		*/	\
													/*	alt:		hpΩ_c	=		xc		-	I[	ixH	];	*/	\
			preΩ_xc	= oc	?	icO:	icO	-		icI;		/*	alt:		preΩ_xc	= 	I[	ixH-1 ]	- 		oc;		*/	\
			postΩ_xc = 		izM		-		ixΩ;					relΩ_c	=	postΩ_xc	-		preΩ_xc;		\
			preΩ_q	=	O[	ixH	]	-		oCS;	/*	<	for some reason, oCS  is off by (+1) in test #97.	*/		\
		/*	preΩ_q	=	O[	ixH	]	-	O[	ocª	];	*//*	<	but test #33 doesn't like the vector map version.			\
			2026-09-24:	The vector map term O[ ocª] is still unreliable, but oCS was fixed in latest tweak to the RACK macro.	\
						It has caused errors everywhere it was used, and I've totally replaced it with oCS now.				\
						I still haven't had a good think about the cause— is it architecture, or implementation?				\
		*/	\
																hpΩ_q	=		CS-16	-		preΩ_q;		\
			postΩ_q	=	Oª[	inM	]	-	Oª[	ixΩ	];				relΩ_q	=		postΩ_q	-		preΩ_q;		\
			CSΩ	= 16	+	postΩ_q	+		hpΩ_q;	/*			CSΩ	=		CS		+		relΩ_q;	*/	dBUG_MOD_DΩ	\
			\
		/*	[iCZ ]:	IN-SITU HIGHPASS REFLOW														*/	\
			if(			relΩ_q >0 )	{/*	expand	*/		cubeΩ =	SvGROW(	svΩ, CSΩ+1 );									\
									ReFLOW_DX(	cubeΩ,	cubeΩ,	relΩ_q, hpΩ_q,	CSΩ,		CS,			__LINE__ );		\
			}else if(		relΩ_q< 0 )	{/*	compact	*/		cubeΩ =	cube;		/*	^dstLim		^srcLim	*/					\
									ReFLOW_AC(	cubeΩ,	cubeΩ,	relΩ_q, hpΩ_q,	16+postΩ_q,	CS-hpΩ_q,	__LINE__ );		\
			}else		{			/*	shunt	*/		cubeΩ =	cube;		/*	^dst0		^src0	*/					\
						} cubeΩ[ CSΩ ]=0;		pΩ	 	=	cubeΩ+16;											dBUG_SvCUR( svΩ, CSΩ );	\
																SvCUR_set(	svΩ, CSΩ );									\
		/*	[iCI ]: 	SPLICE KEYBYTE SECTION														*/						\
			if( hpΩ_c ){	enXhp	=	postΩ_xc| ( hpΩ_c<< 3 );															/*	*Edge( cubeΩ ) = *Edge( cube ); 	*/	\
				if(	relΩ_c< 0)	{	bs = ( -relΩ_c )<< 3;	hipa = *( (ui64*) cube ) >>bs;	}	\
				else{				bs =   relΩ_c	<< 3;	hipa = *( (ui64*) cube )<< bs;	}	\
				switch(	enXhp	){	SwCASE_LPXOVER_10Y( hipa,				 	*( (ui64*)( K +ixΩ ) ),	*( (ui64*) cubeΩ )  )  	}			\
			}else{				/*	^lowpass crossover wye	 ^high passthrough, shifted	^low inclusion src		^wye output		*/	*Edge( cubeΩ ) = E[ izM ];		/*	Edge changed	*/	\
				switch(	postΩ_xc ){	SwCASE_LOWPASS_1I(							*( (ui64*)( K +ixΩ ) ),	*( (ui64*) cubeΩ )	)	}			\
				}				/*	^lowpass inline assignment						^definitive src			^low passthrough	*/	\
			if(			postΩ_q ){	iCEpACK(	pΩ,		ixΩ, izM, inM,		cubeΩ );												\
								}/*	^re-pack modified q-data vectors ixΩ..izM to cubeΩ[ 16..16+postΩ_q-1 ]	*/		dBUG_MOD_DΩ_CLOSE




