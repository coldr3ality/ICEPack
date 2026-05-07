use strict;
use warnings;
use Inline 'C';	#		=> Config => ("BOOT", ";\n _init();"); 
_init();
1;
__DATA__
__C__
/*
0-8:	0-8
9/2:		5, 4
10/2:	5, 5
11/2:	6, 5
12/2:	6, 6
13/2:	7, 6
14/3:	5, 5, 4
15/3:	5. 5, 5
16/3:	6, 5, 5
17/3:	6, 6, 5
18/3:	6, 6, 6
19/3:	7, 6, 6
20/3:	7, 7, 6
21/3:	7, 7, 7
22/4:	6, 6, 5, 5
23/4:	6, 6, 6, 5
24/4:	6, 6, 6, 6
25/4:	7, 6, 6, 6
26/4:	7, 7, 6, 6
27/4:	7, 7, 7, 6
28/4:	7, 7, 7, 7
29/5:	6, 6,	7,	5, 5
30/5:	6, 6,	7,	6, 5
31/5:	6, 6,	7,	6, 6
32/5:	7, 6,	7,	6, 6
33/5:	7, 7,	7,	6, 6
34/5:	7, 7,	7,	7, 6
35/5:	7, 7,	7,	7, 7
36/6:	6, 6,	7, 7,	5, 5
*/

void _init(  ){		double max_tena_zc=32;
	static char *	subCaseCodes[]={
	/*	0	*/	"L_LMH_H",		//			"0-L   	1-LxMxH 	2-H   ",
	/*		*/	"xLMMH_Hx",		//impossible	"0-LxM	1-LxMxH		2-H   ",		//impossible
	/*	1	*/	"L_LMH ",			//			"0-L		1-LxM		2-H  ",
	/*		*/	"xLMLMHx",		//impossible	"0-LxM	1-LxM		2-H	",		//impossible
	/*	2	*/	"LMH_H ",		//			"0-L		1-MxH   		2-H	",
	/*	3	*/	"LMMH_H",		//			"0-LxM	1-MxH		2-H	",
	/*	4	*/	"LMH  ",			//			"0-L		1-M			2-H	",
	/*	5	*/	"LMMH ",		//			"0-LxM	1-M			2-H	",
	/*		*/	"xL_LMHMHx",	//impossible	"0-L   	1-LxMxH 	2-MxH   ",	//impossible
	/*		*/	"xLMLMHMHx",	//impossible	"0-LxM	1-LxMxH		2-MxH   ",	//impossible
	/*	6	*/	"L_LMMH",		//			"0-L		1-LxM		2-MxH  ",
	/*		*/	"xLMLMMHx",	//impossible	"0-LxM	1-LxM		2-MxH	",	//impossible
	/*		*/	"xLMHMHx",		//impossible	"0-L		1-MxH   		2-MxH	",	//impossible
	/*		*/	"xLMMHMHx",	//impossible	"0-LxM	1-MxH		2-MxH	",	//impossible
	/*	7	*/	"LMMH ",		//			"0-L		1-M			2-MxH	",
	/*	8	*/	"LMMMH"	};	//			"0-LxM	1-M			2-MxH	"	};

	printf("\n");
	char	tena_zc=0,	endo_C, endo_c,
		post_nc,		post_C, exo_c, zc0,	zc1, zcX, zcY, zcZ, zcN, nc0,	en0, en0, enX, enY, enZ, ex1, ixZ2,	
		div=6,		d,				total_ec, ix0, ixZ;
	int	min0=255, 	minZ=255,
		max0=0,   	maxZ=0;
	short	subCaseStats[16][2]={	{0xFFFF, 0},{0xFFFF, 0},{0xFFFF, 0},{0xFFFF, 0},{0xFFFF, 0},{0xFFFF, 0},{0xFFFF, 0},{0xFFFF, 0},
								{0xFFFF, 0},{0xFFFF, 0},{0xFFFF, 0},{0xFFFF, 0},{0xFFFF, 0},{0xFFFF, 0},{0xFFFF, 0},{0xFFFF, 0}
								};
	double	max_tena_zc_pct=( max_tena_zc +1 )/100,	total_d0=0,	total_dx=0, d0Pct, dxPct,
			max_ixZ=21;

	int	dist0	[]={0, 0, 0, 0, 0, 0, 0, 0},
		dist_	[]={0, 0, 0, 0, 0, 0, 0, 0};
	char subcase=0, _subcase=-1;

	for( tena_zc=21; tena_zc<=max_tena_zc; ++tena_zc ){		post_nc	= tena_zc  +1;
										endo_C = (	tena_zc /7 )-2;	if(endo_C< 0 )	printf("!	invalid tena_zc for rack case 1F4: %d\n", tena_zc );
								endo_c =	endo_C *7;
				exo_c = tena_zc -	endo_c -22;
		switch(	exo_c ){
			case 0:	/*	6, 6; 5, 5	*/	zc0=6;	zc1=6;	zcX=5;	zcZ=5;	en0=7;	en0=14;	enX=14+endo_c;	enZ=20+endo_c;	break;
			case 1:	/*	6, 6; 6, 5	*/	zc0=6;	zc1=6;	zcX=6;	zcZ=5;	en0=7;	en0=14;	enX=14+endo_c;	enZ=21+endo_c;	break;
			case 2:	/*	6, 6; 6, 6	*/	zc0=6;	zc1=6;	zcX=6;	zcZ=6;	en0=7;	en0=14;	enX=14+endo_c;	enZ=21+endo_c;	break;
			case 3:	/*	7, 6; 6, 6	*/	zc0=7;	zc1=6;	zcX=6;	zcZ=6;	en0=8;	en0=15;	enX=15+endo_c;	enZ=22+endo_c;	break;
			case 4:	/*	7, 7; 6, 6	*/	zc0=7;	zc1=7;	zcX=6;	zcZ=6;	en0=8;	en0=16;	enX=16+endo_c;	enZ=23+endo_c;	break;
			case 5:	/*	7, 7; 7, 6	*/	zc0=7;	zc1=7;	zcX=7;	zcZ=6;	en0=8;	en0=16;	enX=16+endo_c;	enZ=24+endo_c;	break;
			case 6:	/*	7, 7; 7, 7	*/	zc0=7;	zc1=7;	zcX=7;	zcZ=7;	en0=8;	en0=16;	enX=16+endo_c;	enZ=24+endo_c;	break;
			}
		enY=enX+1;	ex1=enZ+1;
		
		zcZ	=	exo_c >>1;		en0	=	exo_c	-zcZ;
		zc0	=	en0 -1;			enZ	=	tena_zc	-zcZ;	

		ix0	=	0;
		ixZ	=	4;
		for(		ix0=0;			ix0<= tena_zc-2;	++ix0 ){
			for(	ixZ =ix0 >2? ix0: 2;	ixZ<= tena_zc;	++ixZ ){
				subcase=0;
				if( ix0 >en0 )	{
	/* L_LxMxH_H	*/		if( ixZ< enZ )	{							/*			1:LxMxH				Z:H		*/	
							} else		{				subcase|=2;	/*			1: LxM						*/	
	/* L_LxM_H		*/					if( ixZ==enZ )	{				/*								Z: H		*/	}
	/* L_LxM_MxH	*/					else			{	subcase|=8;	/*								Z: MxH	*/	}
										}							/*	0: L									*/	
				} else		{
							if( ixZ< enZ )	{				subcase|=4;	/*			1: MxH				Z: H		*/	
							}else		{				subcase|=6;	/*			1: M						*/	
										if( ixZ==enZ )	{				/*								Z: H		*/	}
										else			{	subcase|=8;	/*								Z: MxH	*/	}	
										}
							if( ix0==en0 )	{							/*	0: L;									*/	}
							else			{				subcase|=1;	/*	0: LxM;								*/	}
							}
				if( ix0 < subCaseStats[subcase][0] ) subCaseStats[subcase][0]=ix0;
				if( ixZ < subCaseStats[subcase][1] ) subCaseStats[subcase][1]=ixZ;
			}	}
	//	zcZ	=	exo_c >>1;		zc0	=	exo_c	-zcZ;
	//	en0	=	zc0 +1;			enZ	=	tena_zc	-zcZ;	


		++dist0[ zc0 ];
		++dist_[ zcZ ];

		if(zc0	< min0	) min0	= zc0;	if( zc0	>max0	) max0	= zc0;
		if(zcZ	< minZ	) minZ	= zcZ;	if( zcZ	>maxZ	) maxZ	= zcZ;

		total_ec	= zc0+1+zc1+1+endo_c +zcX+1+zcZ +1;	
		printf(			"\r%c	tena_zc: %d		%2d+1 	+%2d+1	+(6+1)*%-2d	+%d+1	+%d+1		en0..enZ:	%d, %d		total: %d\n",
		total_ec==post_nc? 32: 33,	tena_zc,			zc0,		zc1,		endo_C,		zcX,		zcZ,						en0, enZ,	total_ec );

	/*	post_C	= endo_C +2;	*/		// +3 if absorbing preceding cube

	/*	The subcase of case 6 is determined by comparing
					the total cycla in the pre-op	cube run minus the pre-op displacement
			versus	the total cycla in the post-op	cube run not including the length of the final fragment.

		*/


		}
	printf("\nmin/max Cube[0]:	%d/%d\nmin/max Cube[iCZ]:	%d/%d\n\n", min0, max0, minZ, maxZ );
	for( d=0; d<8; ++d){		d0Pct =dist0[ d ] /max_tena_zc_pct;
									dxPct =dist_[ d ] /max_tena_zc_pct;	
		printf("\r	zc0==%d:	%0.2f%c		zcZ==%d:	%0.2f%c \n",
			d,			d0Pct, 37, d,	dxPct, 37);
		total_d0+=d0Pct;
		total_dx+=dxPct;
		}
	printf("\n	%0.2f%c	%0.2f%c\n\n", total_d0, 37, total_dx, 37 );
	}