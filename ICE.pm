# Inversion Cycle Encoding (ICE) v0.4.9 
package ICE;	 use strict; use warnings;	++$|;	#system('cls');  
use Data::Dumper;
use Inline 'C';	#		=> Config => ("BOOT", ";\n init();"); 
my @avOut=();
	init();
	my $max_isq=0;	
#	test_rack();
#	exit;
#	my $A1=[ 5, 6, 7, 12, 20, 22, 23, 24, 25, 29, 31, 34, 38, 40, 42, 46, 49, 52, 55, 58, 61, 64, 68, 70, 74, 76, 80, 82, 86, 88, 90, 94, 96, 100, 102, 106, 109, 113, 116, 120, 123, 127, 130, 134, 137, 140, 144, 147, 150, 153, 157, 160, 163, 168, 172, 178, 180, 184, 191, 195, 200, 205];	
#	my $A1=[ 0x5, 0x6,	0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 	0xFF, 0x100, 0x101,	0xFFE, 0xFFF,	0x1000,		0xFFFE, 0xFFFF, 0x10000,	0xFFFFFFE, 0xFFFFFFF, 0x10000000	];
#	my $A1=[ 5, 6, 7, 57, 111, 113, 151, 191, 222, 255, 257, 357, 457, 561, 717, 1111, 1113, 1211, 1212 ];
#	my $A1=[ 5, 6, 7, 57, 111, 113, 151, 191, 222, 255, 257, 357, 457, 561, 717, 1111, 1113, 1211, 1212, 1221, 1222, 2222, 4444, 8888, 12222, 14444, 16666	];
	my $A1=[ 5, 6, 7, 57, 111, 113, 151, 191, 222, 255, 257, 357, 457, 561, 717, 1111, 1113, 1211, 1212, 1221, 1222, 2222, 4444, 8888, 12222,
			14444, 16666, 212121, 212122, 313131, 313132, 313133, 414144,	101101101,	202202202,	303303303,
			1111111100, 1111111101, 1111111102, , 1111111103, 1111111104, 1111111105, 1111111106, 1111111107, 1111111108, 1111111109,, 1111111110, 1111111111,
			1113111130, 1113111131,	1211212110, 1211212111,	1211212112];
  
#	my $A1=[0, 1, 255, 256, 65535, 65536, 16777215, 16777216, 4294967295, 4294967296, 1099511627775, 1099511627776, 281474976710655, 281474976710656 ];
# 	my $A1=[0, 1, 255, 256, 65535, 65536, 16777215, 16777216, 4294967295, 4294967296, 1099511627775, 1099511627776, 281474976710655, 281474976710656, 72057594037927935, 72057594037927936 ];
# 	my $A1=[0, 1, 100, 200, 255, 256, 60000, 65535, 65536, 70000, 80000, 900000, 1000000, 16000000, 16777215, 16777216, 200200200, 300300300, 400400400, 4294967295, 4294967296, 5005005005, 6006006006, 10010010010, 10999999999, 11000000000, 11111111111, 222222222222, 1099511627775, 1099511627776, 1099999999999, 1111111111111, 14001400140014, 281400000000000, 281474976710655, 281474976710656, 2814000028140000, 72057000000000000, 72057594037927935, 72057594037927936, 72057599999999999, 880088008800880088, 990099009900990099, 1152921212121212121, 1152921313131313131, 1152921504606846975, 1152921504606846976, 1234567890987654321, 1234567899999999999];
# 	my $A1=[0, 1, 255, 256, 65535, 65536, 16777215, 16777216, 4294967295, 4294967296, 1099511627775, 1099511627776, 281474976710655, 281474976710656, 72057594037927935, 72057594037927936, 18446744073709551615];
#	my $A1=[10, 20, 30, 40, 50, 60, 70, 80];
#	my $A1=[100, 200, 300, 400, 500, 600, 700, 800];

#	my $A1=[123, 234, 456, 567, 678, 789, 911, 1011];

#	my	$A1=[ 717, 1111, 1113, 1211, 1212, 1221, 1222, 2222, 4444, 8888, 12222, 14444, 16666, 18888, 20000, 22222, 24444, 28888, 30000, 31111, 33333	];
#		5	6		26	27	...						32		255..257				4094..4096				65534 .. 65536			268435454..268435456



#	while(	$_=<> ){	#	alloc() test
#					$x= $ICE->alloc();		print("\r #$x<--	\n",					 @{ $ICE->toText() } );
#					}


sub testCase2{
	printf("\rtestCase 2:	");
	my $ICE=fromRvAV([
		102..200,									undef,
		202..400, 								undef,
		402..500,									undef,
		510, 520, 530, 540,		550, 560, 570, 580,		undef,
		590, 600, 610, 620,		630, 640, 650, 660,		undef,
		670, 680, 690, 700,		710, 720, 730, 740,		undef,
		902..1000,								undef,
		1002..2000,								undef,
		2002..3000,								undef,
		3002..4000										]);
	
	print(	@{	$ICE->toText() } );
	my @args=( 201, 401,	525, 565, 605, 645, 685,725 );	#print("\n	batch 0:	(", join(', ', @args), ")\n\n");
				$ICE->set( \@args );
	print(	@{	$ICE->toText() } );		
	my $hit =	$ICE->screenKeys( \@args );
	my $miss=0;		
	if( 0< ( $miss = scalar( @args ) ) ){	print("\r($miss) missing keys:	(", join(', ', @args ), ")	failed testCase2\n\n" );	exit; }
	}
	testCase2;


sub testCase1{
	printf("\rtestCase 1:	");
	my $ICE=fromRvAV([
		1..100,												undef,
		102..200,												undef,
		202..400, 404, 440, 444, 480, 840, 848..900,					undef,
		902, 904..1000,										undef,
		1002..4000, 4004, 4040, 4444, 4848, 4884..4888, 4999..5000,	undef,
		5002..7200,											undef,
		7202..8400,	8402..8404, 8408..8048, 8448..8888, 9009..9099, 10001..11011, 11111, 11211,		undef,
		90210, 																			undef,
		90212..100000	]);
	
#	print(	@{	$ICE->toText() } );
	my @args=( 101, 201, 401, 402, 403, 1001, 4050, 4850,7201,8406, 90211 );	#print("\n	batch 0:	(", join(', ', @args), ")\n\n");
				$ICE->set( \@args );
	print(	@{	$ICE->toText() } );		
	my $hit =	$ICE->screenKeys( \@args );
	my $miss=0;		
	if( 0< ( $miss = scalar( @args ) ) ){	print("\r($miss) missing keys:	(", join(', ', @args ), ")	failed testCase1\n\n" );	exit; }
	}
#	testCase1;
sub replay24{
	print("\rreplay24:\t");
	my $ICE=fromRvAV( [
		0,         2..8,      17..18,    20..21,    23..32,    35..36,						undef,
		39..42,    44..47,    49..50,    52,										undef,
		55..60,    65,        69..74,    76..78,										undef,
		80,        82..87,    92,												undef,
		94,        96,        98..104,   106..109,  111,       117..119,					undef,
		121,       125..127,  130,       132,       134,       137..139,					undef,
		142,       144..145,  148,       150..151,  155..157,							undef,
		161,       163..167,  171,       173..175,  177,       179..180,  183,				undef,
		185..186,  190,       192,       194..196,  198,       201..203,					undef,
		205,       209..213,  215,       219..220,  223..226,  228,       230..232,			undef,
		234..236,  239..240,  242,       245,       248..250,  253..254,					undef,
		256..260,  262..265,  267,       270..274,  276..277,  279..282,				undef,
		284..287,  291..293,  296..299,  301..306,  308..309,						undef,
		314,       316..324,  326..327,											undef,
		330,       333..335,  337..338,  340,       342,       346,       348..349,			undef,
		351..352,  354..356,  358,       360..364,									undef,
		367..369,  371..372,  374,       378,       380..385,							undef,
		387,       389..391,  393..394,  396..400,  402..403,						undef,
		405..408,  410..412,  418..419,  422..426,								undef,
		428..429,  431,       433,       436..440,  442,								undef,
		444..445,  447..448,  451,       454..455,  457..458,  461..462,  464..465,		undef,
		482..483,  485..487,  491..492,  495..496,								undef,
		500..502,															undef,
		506..510,															undef,	
		506..507,  509,													undef,
		511	] );
#	print("\n\n",	@{	$ICE->toPerl() } );
#	print("\n\n",	@{	$ICE->toText() } );
	my @args=(   97, 288, 355, 429, 437, 444, 503, 505 );
#	print("\n	batch 0:	(", join(', ', @args), ")\n\n");
				$ICE->set( \@args );
#	print("\n\n", 	@{	$ICE->toPerl() } );
#	print("\n\n",	@{	$ICE->toText() } );		
	if( $ICE->screenKeys(	\@args ) or $#args!=-1 ){	print("\r(", scalar( @args ), ") missing keys:	(", join(', ', @args ), ")	failed replay 24\n\n" );	exit; }
	else{	print("	pass\n");	}
	}
	replay24;
sub replay23{
	print("\rreplay23:\t");
	my $ICE=fromRvAV( [
		0..4,      6..7,      9..10,     16,        20..21,								undef,
		23..24,    27,        29..30,    33..34,    36,									undef,
		40,        43..44,    47..48,    50..52,    56,        58,        60..62,					undef,
		64,        67..72,    80..81,    87,        91,									undef,
		96,        98,        101,       106,       108..110,								undef,
		112..116,  118..119,  123,       126..127,  129..130,  132..133,  135..137,		undef,
		139..142,  146..147,  151..152,  155..157,								undef,
		159..160,  162,       164,       167,       173..174,  176..177,					undef,
		179,       181..185,  187..192,											undef,
		200..201,  204..205,  209,											undef,
		212..214,  216..217,  221,       223,										undef,
		225..230,  241..245,  248..249,  259..261,  263..265,						undef,
		268..269,  272,       278,       280,       282..283,  285..286,  288,       297..299,	undef,
		301..303,  308,       314,       316..320,  325,       331..333,  336,				undef,
		342,       344,       348,												undef,
		350..353,  358,       360,       362..365,  368,								undef,
		373..375,  377,       381..386,  388..389,									undef,
		403..405,  407,       412..414,  416,       419,								undef,
		421,       423..424,  426,       429..430,  432..433,  436,       438,				undef,
		442,       447,       449,       452..453,  455..456,  460..461,					undef,
		463..464,  466..468,  474..475,										undef,
		477..478,															undef,
		483..484,															undef,
		490..494,															undef,
		491,       495,       499..500,  503..504,									undef,
		507..508														] );
#	print("\n\n",	@{	$ICE->toPerl() } );
#	print("\n\n",	@{	$ICE->toText() } );
	my @args=(   98, 188, 189, 217, 358, 430, 485, 486 );
#	print("\n	batch 0:	(", join(', ', @args), ")\n\n");
				$ICE->set( \@args );
#	print("\n\n", 	@{	$ICE->toPerl() } );
#	print("\n\n",	@{	$ICE->toText() } );		
	if( $ICE->screenKeys(	\@args ) or $#args!=-1 ){	print("\r(", scalar( @args ), ") missing keys:	(", join(', ', @args ), ")	failed replay 23\n\n" );	exit; }
	else{	print("	pass\n");	}
	}
	replay23;
sub replay22{
	print("\rreplay22:\t");
	my $ICE=fromRvAV( [
		3,         9..11,     13..15,    17..19,    21,									undef,
		25,        28..29,    31..36,    39,        41..42,    44,        48,					undef,
		54,        56..57,    59,        62,        64,        69..70,    73,        75,				undef,
		77..79,    81..83,    87,        89..91,										undef,
		93,        95,        98..100,   104..105,  108,       110,       113..115,  118,			undef,
		121,       124..125,  130,       133..134,  139,       146,						undef,
		148..149,  151..154,  157,       159..160,  163..164,						undef,
		169,       171..172,  175..176,  182,       184,								undef,
		188,       198..201,  203,       205..207,									undef,
		209,																undef,
		211..217,  220..221,  227..229,  231..234,  238..241,  243,       247..249,		undef,
		253..256,  258..259,  261,       264..265,  269,       271,       273..277,  280..281,	undef,
		285..287,  289,       292..294,  296,       298,								undef,
		303..305,  310,       313,												undef,
		316..317,  322..326,  328,       330,       334,								undef,
		339..341,  343,       345..346,  348..350,  352,							undef,
		369..370,  374,       376..377,  380..382,									undef,
		384..386,  389..390,  399,       401,       404,       410..411,  413..419,			undef,
		422,       424..425,  427,       430..431,  433,								undef,
		436,       438,       440,       442,       445..446,								undef,
		465..466,  468..471,												undef,
		474,       477..478,  481..482,  484..485,  487,							undef,
		490,       494..495,  497,       501..502,									undef,
		506,       509														] );
#	print("\n\n",	@{	$ICE->toPerl() } );
#	print("\n\n",	@{	$ICE->toText() } );
	my @args=(  64, 139, 201, 210, 342, 374, 443, 479 );
#	print("\n	batch 0:	(", join(', ', @args), ")\n\n");
				$ICE->set( \@args );
#	print("\n\n", 	@{	$ICE->toPerl() } );
#	print("\n\n",	@{	$ICE->toText() } );		
	if( $ICE->screenKeys(	\@args ) or $#args!=-1 ){	print("\r(", scalar( @args ), ") missing keys:	(", join(', ', @args ), ")	failed replay 22\n\n" );	exit; }
	else{	print("	pass\n");	}
	}
	replay22;
sub replay13{
	print("\rreplay13:\t");
	my $ICE=fromRvAV([
		7,    34,   40,   55,   67,						undef,
		69,   95,   118,  136,  188,					undef,
		285,  288,  296,  309,  341,  346,  363,  369,		undef,
		385,  393,  403,  420,  424,					undef,
		450,										undef,
		470		] );
#	print("\n\n",	@{	$ICE->toPerl() } );
#	print("\n\n",	@{	$ICE->toText() } );
	my @args=(  7, 34, 55, 116, 218, 244, 288, 341 );
#	print("\n	batch 0:	(", join(', ', @args), ")\n\n");
				$ICE->set( \@args );
#	print("\n\n", 	@{	$ICE->toPerl() } );
#	print("\n\n",	@{	$ICE->toText() } );		
	my $hit =	$ICE->screenKeys( \@args );
	my $miss=0;		
	if( 0< ( $miss = scalar( @args ) ) ){	print("\r($miss) missing keys:	(", join(', ', @args ), ")	failed replay 13\n\n" );	exit; }
	else{	print("	pass\n");	}
	}
	replay13;
sub replay12{
	print("\rreplay12:\t");
	my $ICE=fromRvAV([
		1..15,     17..21,													undef,
		23..26,    28..31,    33,												undef,
		35..42,    44..49,    51..54,    56,										undef,
		58..68,    70..71,    73..78,											undef,
		80..81,    83..85,    87..92,											undef,
		94..105,															undef,
		107..110,  112,       114..121,											undef,
		123..127,  129..131,												undef,
		133..143,															undef,
		145..157,  159,       161..163,  165..169,									undef,
		171..172,  174..179,												undef,
		181..192,  195..199,												undef,
		201..209,  211..214,  216..217,  219..228,								undef,
		230..237,  239..241,  245..248,  250,       252..253,  256,  258..259,  261..262,	undef,
		267..275,  277,       279..281,  283..285,  287..289,						undef,
		291..293,															undef,
		295..315,  317,													undef,
		320..325,  327..332,  334..339,										undef,
		342..351,  353..361,												undef,
		363..376,  378..381,  383..393,										undef,
		396,																undef,
		398..412,  415..419,  421..425,										undef,
		427..428,  430..436,												undef,
		438..466,															undef,
		468..474,  476..480,												undef,
		482..496,  498,       500..501,  504..506,									undef,
		508..511	]);
#	print("\n\n",	@{	$ICE->toPerl() } );
#	print("\n\n",	@{	$ICE->toText() } );
	my @args=(  27, 95, 149, 243, 294, 358, 387, 397 );
#	print("\n	batch 0:	(", join(', ', @args), ")\n\n");
				$ICE->set( \@args );
#	print("\n\n", 	@{	$ICE->toPerl() } );
#	print("\n\n",	@{	$ICE->toText() } );		
	my $hit =	$ICE->screenKeys( \@args );
	my $miss=0;		
	if( 0< ( $miss = scalar( @args ) ) ){	print("\r($miss) missing keys:	(", join(', ', @args ), ")	failed replay 12\n\n" );	exit; }
	else{	print("	pass\n");	}
	}
	replay12;
sub replay11{
	print("\rreplay11:\t");
	my $ICE=fromRvAV([
		0..5,															undef,
		7..14,     17..18,    22,        24..25,    28,        32..33,    40,        43..46,		undef,
		48..51,    53..56,    63,        65..66,									undef,
		71..72,    75..77,    79..82,    86..87,    90,        92,        95,        99..102,	undef,
		105..106,  108,       110,       112..114,  119,							undef,
		122..123,  128..130,  133..138,									undef,
		140..142,  144,       148,       150..156,  159..160,  163..164,				undef,
		169,       171..174,  176,       178..179,  181..182,						undef,
		187,       190,       194..195,  199,       203..204,						undef,
		206..213,  216,       218..219,  222,       226..230,						undef,
		233,       235..237,  239,       245..246,  248,							undef,
		254..257,  259,       264,       266..268,								undef,
		270..273,  278,       280,       283,       286..290,  293..296,  300..301,		undef,
		305..306,  312..314,  317,       320,       323..325,  328,       330..331,		undef,
		334..335,  337,       340..341,  343..347,								undef,
		349,       356,       359,       361..362,  364..367,  370..371,				undef,
		375,       377..379,  384,       388..390,  392,       394,					undef,
		396,       398..400,  402,       405..406,								undef,
		410..415,  417,       420..421,  423,       427..428,  430..431,  434..437,		undef,
		440,       444..445,  447..448,  450..451,  453,						undef,
		456..459,  461,       463..464,										undef,
		469,       471..476,  479,											undef,
		484..491,  493..495,  497..498,  501,								undef,
		503..505,														undef,
		507..510		]);
	
#	print("\n\n",	@{	$ICE->toPerl() } );
#	print("\n\n",	@{	$ICE->toText() } );
	my @args=( 6, 20, 26, 43, 103, 216, 326, 466 );
#	print("\n	batch 0:	(", join(', ', @args), ")\n\n");
				$ICE->set( \@args );
#	print("\n\n", 	@{	$ICE->toPerl() } );
#	print("\n\n",	@{	$ICE->toText() } );		
	my $hit =	$ICE->screenKeys( \@args );
	my $miss=0;		
	if( 0< ( $miss = scalar( @args ) ) ){	print("\r($miss) missing keys:	(", join(', ', @args ), ")	failed replay 11\n\n" );	exit; }
	else{	print("	pass\n");	}
	}
	replay11;
sub replay10{
	print("\rreplay10:\t");
	my $ICE=fromRvAV([
		0..2,      4..6,      8,         10,        12..13,	undef,
		16,        18..20,    22,        24..26,	undef,
		28..34,    37,	undef,
		39..43,    45..48,    50..52,	undef,
		54..62,    65..69,	undef,
		71..79,    82..86,    89,        93,        95..96,    99..102,   104,	undef,
		106,       108,       110..113,  115,       117..123,	undef,
		126..128,  131..132,  134,       136,       139..149,	undef,
		152,       154,       157..159,  162..169,	undef,
		171..195,	undef,
		197..204,  206,       208..211,  214..215,	undef,
		218..221,  224,       226..231,	undef,
		233,       235..241,  244..245,  247..250,  252..253,	undef,
		256..257,  259..263,  265,       267,       269..271,  273..278,  281..282,  288,	undef,
		290..291,  293..299,  301..308,  310..313,	undef,
		315,       317..322,  324..329,  331..332,  334,       337..338,  340..341,	undef,
		343..346,  348,       351,       354..358,	undef,
		360..364,  366..368,  370..374,  376..377,	undef,
		379..386,  388,	undef,
		390..395,  397..401,  404,	undef,
		407,       409..412,  414..417,  419..420,  422..423,  425..426,  428,       430..431,	undef,
		433..435,  438..439,  441..444,  447..448,	undef,
		452,       454,       456,       461,       463,	undef,
		465,       467..468,  470..475,  477..482,	undef,
		485..487,  489..493,  495..498,  500..501,	undef,
		503..504,	undef,
		506..511	]);
	
#	print("\n\n",	@{	$ICE->toPerl() } );
#	print("\n\n",	@{	$ICE->toText() } );
	my @args=( 32, 62, 196, 285, 353, 366, 464, 470 );
#	print("\n	batch 0:	(", join(', ', @args), ")\n\n");
				$ICE->set( \@args );
#	print("\n\n", 	@{	$ICE->toPerl() } );
#	print("\n\n",	@{	$ICE->toText() } );		
	my $hit =	$ICE->screenKeys( \@args );
	my $miss=0;		
	if( 0< ( $miss = scalar( @args ) ) ){	print("\r($miss) missing keys:	(", join(', ', @args ), ")	failed replay 10\n\n" );	exit; }
	else{	print("	pass\n");	}
	}
	replay10;
sub replay9{
	print("\rreplay9:\t");
	my $ICE=fromRvAV([
		1..3,      12..13,    21,        25,        28..29,    32..34,    42..43,		undef,
		50,        52..54,    57,        59,        61,						undef,
		64,        66,        72,        76..77,    80,						undef,
		82,        86..87,    93..96,    98..100,   106,       112,				undef,
		117,       124,       127..128,  131,       135,       137,				undef,
		139,       141,       144..145,  150..151,						undef,
		153,       155,       157,       161..162,  171,					undef,
		178,       181,       184,       186,							undef,
		194,       198..199,  202,       205,       209,       211..212,  215,      220..223,	undef,
		225..226,  230..231,  237..239,  241,       253,       255,       257,			undef,
		261,       264..266,  269..270,  272..274,						undef,
		277..278,  282..284,  287,       290..291,						undef,
		294,       297..298,  306,       309,       312..313,  317,				undef,
		329,       332,       339..340,  347,       350,					undef,
		354,       358,       364,       367..368,  375,       377,       380,      389,	undef,
		391..394,										undef,
		396..397,  406,       411..412,  417,       421..422,  426,       428,      430..431,	undef,
		436..437,  440,										
		]);
	
#	print( 	@{	$ICE->toPerl() } );
#	print(	@{	$ICE->toText() } );
	my @args=( 2, 160, 161, 304, 360, 385, 395, 409 );
#	print("\n	batch 0:	(", join(', ', @args), ")\n\n");
				$ICE->set( \@args );
#	print( 	@{	$ICE->toPerl() } );
#	print(	@{	$ICE->toText() } );		
	my $hit =	$ICE->screenKeys( \@args );
	my $miss=0;		
	if( 0< ( $miss = scalar( @args ) ) ){	print("\r($miss) missing keys:	(", join(', ', @args ), ")	failed replay 9\n\n" );	exit; }
	else{	print("	pass\n");	}
	}
	replay9;
sub replay8{
	print("\rreplay8:\t");
	my $ICE=fromRvAV([
		1..3,      5,         7,         12..14,    17,   21..23,			undef,
		26,        28,        31,        39..41,    43,   53,        65,		undef,
		71,        80,        82,        87,        92,   98,        108,  112,		undef,
		123..126,  136,       141,       147,       153,				undef,
		155,       157,       161,       170,       172,  177,       192,  205..207,	undef,
		211,       216,       218,       220..222,					undef,
		223,       228,       232,       240..242,  245,  248,				undef,
		250,       253,       270..273,  275..278,					undef,
		282,       284..289,  291,       304,						undef,
		306..309,  311..313,  321,       326,       328,  332,       337,		undef,
		346,       358,       361..363,  365..367,  372,				undef,
		383,       386,       395,       401,						undef,
		405,       407,       413,       418,       427,  433..436,			undef,
		438,										
		440	]);
	
#	print( 	@{	$ICE->toPerl() } );
#	print(	@{	$ICE->toText() } );
	my @args=( 85, 87, 139, 143, 164, 199, 220, 439 );
				$ICE->set( \@args );
#	print(	@{	$ICE->toText() } );		print("\n	batch 0:	(", join(', ', @args), ")\n\n");
	my $hit =	$ICE->screenKeys( \@args );
	my $miss=0;		
	if( 0< ( $miss = scalar( @args ) ) ){	print("\r($miss) missing keys:	(", join(', ', @args ), ")	failed replay 8\n\n" );	exit; }
	else{	print("	pass\n");	}
	}
	replay8;
sub replay7{
	print("\rreplay7:\t");
	my $ICE=fromRvAV([
		0..16,				undef,
		18..39,				undef,
		41..69,71..74,			undef,
		76..84,86..110,		undef,
		112..121,				undef,
		123..133,				undef,
		135..162,				undef,
		164..194,				undef,
		196..203,				undef,
		205..263,				undef,
		265..275,				undef,
		278..310,				undef,
		312..323, 325..332			]);
#	print( 	@{	$ICE->toPerl() } );
#	print(	@{	$ICE->toText() } );
	my @args=( 13, 122, 181, 204, 243, 247, 264, 272 );
				$ICE->set( \@args );
#	print(	@{	$ICE->toText() } );		print("\n	batch 0:	(", join(', ', @args), ")\n\n");
	my $hit =	$ICE->screenKeys( \@args );
	my $miss=0;		
	if( 0< ( $miss = scalar( @args ) ) ){	print("\r($miss) missing keys:	(", join(', ', @args ), ")	failed replay 7\n\n" );	exit; }
	else{	print("	pass\n");	}
	}
	replay7;
sub replay6{
	print("\rreplay6:\t");
	my $ICE=fromRvAV([
		0..23,							undef,
		25..30,32..43,						undef,
		45..49,51..53,55..56,59..61,63,67,69..70,72..75,	undef,
		77..78,80,82..83,85,87,89,				undef,
		91..92,96..101,105,107..108,110,			undef,
		112..117,119..127,129,					undef,
		131,133..145,147..152,154..158,				undef,
		160..168,170..183,					undef,
		185..190,192..193,195..201,203..206,			undef,
		210..214,216..218,220..223,				undef,
		225..229,231..232,234..239,241..244,247,249..250,	undef,
		252..256,258..261,263..264,266..270,272,275..278,281,	undef,
		284..288,290..291,293..296,299..303,305..308,310,	undef,
		312,314,316..321,325..326,				undef,
		328..330,						undef,
		332								]);
#	print( 	@{	$ICE->toPerl() } );
#	print(	@{	$ICE->toText() } );
	my @args=( 24, 44, 65, 109, 196, 206, 230, 318 );
				$ICE->set( \@args );
#	print(	@{	$ICE->toText() } );		print("\n	batch 0:	(", join(', ', @args), ")\n\n");
	my $hit =	$ICE->screenKeys( \@args );
	my $miss=0;		
	if( 0< ( $miss = scalar( @args ) ) ){	print("\r($miss) missing keys:	(", join(', ', @args ), ")	failed replay 6\n\n" );	exit; }
	else{	print("	pass\n");	}
	}
	replay6;
sub replay5{
	print("\rreplay5:\t");
	my $ICE = fromRvAV( [
		1,2,11..12,17..19,21,29,31,39,			undef,
		42,55..56,58,61,63..65,76,80,			undef,
		88..90,102,104,112,117,				undef,
		119,123,125..126,128,134,			undef,
		149,151,159,163,166,				undef,
		188,202,206,208,211,221,222,			undef,
		228,234,246,247,251,252,261,270,274..275,	undef,
		278,286,289,293..295,297,			undef,
		303,						undef,
		305..306,309,321,323,				undef,
		330..331						] );
#	print( 	@{	$ICE->toPerl() } );
#	print(	@{	$ICE->toText() } );
	my @args=( 6, 24, 64, 75, 87, 243, 304, 326 );
				$ICE->set( \@args );
#	print(	@{	$ICE->toText() } );		print("\n	batch 0:	(", join(', ', @args), ")\n\n");
	my $hit =	$ICE->screenKeys( \@args );
	my $miss=0;		
	if( 0< ( $miss = scalar( @args ) ) ){	print("\r($miss) missing keys:	(", join(', ', @args ), ")	failed replay 5\n\n" );	exit; }
	else{	print("	pass\n");	}
	}
	replay5;
sub replay4{
	print("\rreplay4:\t");
	my $ICE=fromRvAV( [
		1..2,4..5,12,21,29,			undef,
		31,37,51,65,				undef,
		85,100,112,159,179,183,			undef,
		193,211,217,221,			undef,
		230,233,240,258,288,291,306,325	] );
#	print( 	@{	$ICE->toPerl() } );
#	print(	@{	$ICE->toText() } );
	my @args=( 97, 159, 175, 206, 255, 292, 331, 332 );
				$ICE->set( \@args );
#	print(	@{	$ICE->toText() } );		print("\n	batch 0:	(", join(', ', @args), ")\n\n");
	my $hit =	$ICE->screenKeys( \@args );
	my $miss=0;		
	if( 0< ( $miss = scalar( @args ) ) ){	print("\r($miss) missing keys:	(", join(', ', @args ), ")	failed replay 4\n\n" );	exit; }
	else{	print("	pass\n");	}
	}
	replay4;
sub replay3{
	print("\rreplay3:\t");
	my $ICE=fromRvAV([
		0..2,4,						undef,
		6..27,29,31..37,				undef,
		39..43,						undef,
		45..76,78..80,82..87,				undef,
		89..94,						undef,
		96..110,					undef,
		112..143,					undef,
		146..147,149,151..160,				undef,
		162,164,					undef,
		166..182,184..189,				undef,
		192..195,					undef,
		197..217,219..222,				undef,
		224..245,					undef,
		247..304,306..307,309..316,319,322..325,	undef,
		327..329,					undef,
		331..332,							] );
#	print( 	@{	$ICE->toPerl() } );
#	print(	@{	$ICE->toText() } );
	my @args=( 11, 59, 60, 151, 163, 173, 237, 330 );
				$ICE->set( \@args );
#	print(	@{	$ICE->toText() } );		print("\n	batch 0:	(", join(', ', @args), ")\n\n");
	my $hit =	$ICE->screenKeys( \@args );
	my $miss=0;		
	if( 0< ( $miss = scalar( @args ) ) ){	print("\r($miss) missing keys:	(", join(', ', @args ), ")	failed replay 3\n\n" );	exit; }
	else{	print("	pass\n");	}
	}
	replay3;
sub replay2{
	print("\rreplay2:\t");
	my	$ICE=fromRvAV( [
		1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 18, 21, 							undef,
		24, 27, 32, 34, 35, 36, 41, 							undef,
		43, 45, 48, 53, 57, 58,							undef, 
		60, 61, 63, 66, 69, 70, 						undef,
		74, 75, 80, 81, 85, 88, 93, 						undef,
		104, 106, 107, 109, 112, 117, 119, 120, 121,					undef, 
		125, 126, 128, 134, 135, 138, 139, 141, 142, 				undef,
		144, 145, 151, 152, 155, 159, 162, 163, 164, 165, 167, 				undef,
		169, 170, 172, 175, 177, 187, 						undef,
		190, 191, 192, 194, 197, 198, 199, 200, 201, 209, 211, 215, 216, 218, 220, 221, 		undef,	
		225, 229, 233, 236, 240, 244, 						undef,
		251, 252, 257, 258, 263, 268, 						undef,
		270, 272, 275, 276, 278, 287, 						undef,
		292, 295, 296, 299, 302, 305, 306, 310, 312, 				undef,
		316, 317, 								undef,
		320, 322, 323,								undef,
		325, 									undef,
		327,											] );
#	print( 	@{	$ICE->toPerl() } );
#	print(	@{	$ICE->toText() } );
	my @args=( 29, 149, 186, 203, 238, 265, 302, 326);
				$ICE->set( \@args );
#	print(	@{	$ICE->toText() } );		print("\n	batch 0:	(", join(', ', @args), ")\n\n");
	my $hit =	$ICE->screenKeys( \@args );
	my $miss=0;		
	if( 0< ( $miss = scalar( @args ) ) ){	print("\r($miss) missing keys:	(", join(', ', @args ), ")	failed replay 2\n\n" );	exit; }
	else{	print("	pass\n");	}
	}
	replay2;
sub replay1{
	print("\rreplay1:\t");
	my $ICE= fromRvAV( [	1, 2, 12, 13, 21, 43, 57, 				undef, 
						112, 119, 143, 154, 				undef,
						162, 166, 179, 183, 195,				undef,
						197, 208, 211, 221, 222,				undef,
						234, 247, 249, 276, 289, 294, 311, 313,	undef,
						326,								undef,
						328,										] );
#	print( 	@{	$ICE->toPerl() } );
#	print(	@{	$ICE->toText() } );
	my @args=( 14, 78, 88, 113, 121, 188, 255, 327 );
				$ICE->set( \@args );
#	print(	@{	$ICE->toPerl() } );		print("\n	batch 0:	(", join(', ', @args), ")\n\n");
	my $hit =	$ICE->screenKeys( \@args );
	my $miss=0;		
	if( 0< ( $miss = scalar( @args ) ) ){	print("\r($miss) missing keys:	(", join(', ', @args ), ")	failed replay 1\n\n" );	exit; }
	else{	print("	pass\n");	}
	}
	replay1;
printf("\n\n\n\n\n");












sub test_set_prompt{
	my ($x, @A1, @D1);
#	my $ICE=fromRvAV( $A1 );
	my $ICE=fromRvAV( [1, 2, 12, 21, 112, 211, 221] );	#	bless( [], 'ICE' );
#	my $hv=$ICE->toHV();
#	my @keys= sort keys %$hv;
#	my $N=0;
#	foreach(@keys){	print("$N:	", unpack( "Q", $_), "\n");	++$N;	}
	
	print("\n\n\n", @{ $ICE->toText() }, "\n>");
	while(	$_=<> ){
		@D1=$_=~ /\d+/g;
		@A1= map{ int($_) } @D1;
		print("\nICE::set()==",	$ICE->set(	\@A1	),
			"\n\n\n\n\n",	@{	$ICE->toText(			) } , "\n>");
	}	}
#test_set_prompt();
test_set_loop_rand( 0, 512, 10000000 );
print( 'CAT'x1000);

sub test_set_loop_rand($$$){				# test &set and &unset by repeatedly filling, then emptying the namespace using random noise.
	my($min,$max,$iterations)=@_;
	my	($R,			$pbst,						$batch,	$pass,	$fail,	$replay,					$hit, $miss, $r, $R_, $d, $ICE, $ICE_B4, $x, $i, $I, %arg, @ICE, @ICE_B4, @ICE_AF, @args, @argsMissed, @keyBulk )=
		($max-$min,	bless(\pack('nnn',0,0,0),'PBAR'),	0,		0,		0,		 ["nothing to see here\n"]	);
	$R_=$R>>1;
	my $nSamps=8;	#int(log($R))**2;
	$ICE=bless( [], 'ICE' );
	$ICE_B4=bless( \@ICE_B4, 'ICE');
	my $maxZ=0;

	$#ICE=-1;
	
	print("\n_relay_race: noise test ICE::set and ICE::unset.\nNS: $min..$max @ $nSamps/pass \n");
#\	$ICE=fromRvAV( [1, 2, 12, 21, 112, 211, 221] );	#	bless( [], 'ICE' );
#\	print(		@{	$ICE->toText() } );

	TEST:foreach my $i(1..$iterations){
		$r=$batch=0;
		$ICE=bless( [], 'ICE' );
	#	$#$ICE=33;
	#	$#$ICE=-1;
		while(1){	++$batch;
			@args=();
			for( my $t=$nSamps;  $t >0;  --$t ){
				$x=$min+int(rand($R));
				if(	insortIV( \@args,	$x )	){	++$t;	}
			#\	else	insortIV( \@keyBulk,	$x );
				}

		#	$replay=$ICE->toPerl();

			@ICE_B4=@$ICE;
			$ICE->set(		\@args );
							@argsMissed=@args;

			$maxZ=$#$ICE if $#$ICE > $maxZ;

			if( $ICE->screenKeys(	\@argsMissed ) or $#argsMissed!=-1 ){	++$fail;	$miss=scalar @argsMissed;
				print("\n\n");
				print(	"\n\ntest $i failed; replay:\n[\n",									@{	$ICE_B4->toPerl()	},	"]",
			#\	print(	"\n\ntest $i failed; replay:\n[\n",									@$replay,	"]",
			#\			"\n\n\n\n######## TEST $i.$batch PRE-OP ########\n",			@{	$ICE_B4->toText()	},
						"\n\n	set keys:		",								join(', ',	@args		),
						"\n\n	($miss) missing keys:	",						join(', ',	@argsMissed	),
						"\n\n",
						"\n\n\n\n######## TEST $i.$batch POST-OP ########\n"		);
				print(																@{	$ICE->toText()	}	);
				print(	"\n\n\n\n"												);
				exit;
				next TEST;
				}
			if( $ICE->inTotality() ){	++$pass;
		#\		if( defined $replay ){	print( "\n######## TEST $i COMPLETE ########\n", @{ $ICE->toPerl() }, "\n>", join(', ', @args), "\n\n\n");	}
				print("\r	completed ($i) test[s]; 	$pass/$fail pass/fail    maxZ: $maxZ	");
				next TEST;	}

		}	}

	print("\n($iterations) PASSES\n\n");
	}

1;
__DATA__
__C__
#include	<stdio.h>
#include	"SwCASE.h"
#include	"qCAST.h"
#include	"hiCASTt0.h"
#include	"hiCASTt1.h"
#include	"hiCASTt2.h"
#include	"hiCASTt3.h"
#include	"hiCASTt0inc.h"
#include	"hiCASTt1inc.h"
#include	"hiCASTt2inc.h"
#include	"hiCASTt3inc.h"
#include	"ICE.h"
#include	"ICE.c"

const char	*	commaspace[ 48 ]={
				",",						", ",						",  ",						",   ",						",    ",						",     ",						",      ",						",       ",
				",        ",					",         ",					",          ",					",           ",					",            ",					",             ",					",              ",					",               ",
				",                ",				",                 ",				",                  ",				",                   ",				",                    ",				",                     ",				",                      ",				",                       ",
				",                        ",			",                         ",			",                          ",			",                           ",			",                            ",			",                             ",			",                              ",			",                               ",
				",                                ",		",                                 ",		",                                  ",		",                                   ",		",                                    ",		",                                     ",		",                                      ",		",                                       ",
				",                                        ",	",                                         ",	",                                          ",	",                                           ",	",                                            ",	",                                             ",	",                                              ",	",                                               "
				},
			*	space[ 48 ]={
				",",						"  ",						"   ",						"    ",						"     ",						"      ",						"       ",						"        ",
				"         ",					"          ",					"           ",					"            ",					"             ",					"              ",					"               ",					"                ",
				"                 ",				"                  ",				"                   ",				"                    ",				"                     ",				",                     ",				"                       ",				"                        ",
				"                         ",			"                          ",			"                           ",			"                            ",			"                             ",			"                              ",			"                               ",			"                                ",
				"                                 ",		"                                  ",		"                                   ",		"                                    ",		"                                     ",		"                                      ",		"                                       ",		"                                        ",
				"                                         ",	"                                          ",	"                                           ",	"                                            ",	"                                             ",	"                                              ",	"                                               ",	"                                                "
				};


















#define DEBUG	//	catcatfscatcatc
void init(){	printf("\ninit()=====================================\n"); 
//	for( x=0; x<256; ++x ){	printf("\n%d:	%c\n", x, x);	}

	hvICE		= gv_stashpv(	"ICE",			0);
	avOut		= get_av(		"ICE::avOut",		GV_ADD);
	sv_max_isq	= get_sv(		"ICE::max_isq",	GV_ADD);	//
	A[	255 ]=255;
	B[	255 ]=255;
	O[	255 ]=16;
	_O[	255 ]= 0;
	Q[	255 ]= 0;
	*( (ui64*) Hx )	= 0;
	int x;	
	for( x=0; x<128; ++x){
		rSeq_iR[	x ]=-1;
		rSeqIns[	x ]=0;
		rSeqCut[	x ]=0;
		rSeqSrc[ 	x ]=0;
		rSeqDst[	x ]=0;
		rSeq_SV[	x ]=NULL;
		}
//cube =SvPVbyte(	sv, 	CS );	Kx8=	*( (ui64*) cube );	zc = zIndexOf( Kx8);

/*	(6) distinct cases for racking:
		| Condition:												| Effect:
	#1.	| rel_c is neutral.											| Overwrite cycles mc0..mcZ in cube iC.  No change in cycle count.
	#2.	| rel_c is positive;	(2+) new cubes must be inserted to make space.	| Fragment cube iC, and distribute intermediate cubes in-between.
	#3.	| rel_c is positive;	(1) new cube must be inserted to make space.	| Fragment cube iC in a similar way as in the _alloc() function.
	#4.	| rel_c is negative;	Cycle count drops to zero, extinguishing cube iC.	| Delete cube iC.
	#5.	| rel_c is negative;	Cycle count decreases, but still non-zero.		| Right-shift trailing cycles & overwrite medial cycles if any.
	#6.	| rel_c is positive.	cube iC has enough vacant capacity.			| Left-shift trailing cycles, insert new & overwrite medials.

	*/
	}

/*	hindsight	lichtenstein	bartleby	  cubby	nymph	crew helm mission brink  disaster weld kudos
	wherewithall	alabaster	green tea	shelf
	coffee  baseball	unitarian	peace	feeling	icing	fruitcake	jingles  strike	here	heal caster oil	halibut curly hair		*/
/*	hold true the focus	light	sand ice sky  jewel	slate	food	newcomer	toluene  darkness clear locket list 
	*/
/*	stRormcrow	hellbringer	rifleman	summoner	MADDOG	timberwolf		marauder	direwolf	jenner	kit fox
	fweq
	gargoyle		po diddy		hep cat	claptrap		rib bone		rabbleshnauzer	sneekypete	sup pup	jenzer	kaboodle

	hi		pancakes	fruitloops 	parfaits	eggies		rye toast			string cheese		heavy cream	butter	elderberries
	hola		waffles	turkey		souflette	<3			apple cinnamon	peach			shallots	butter oh
	blueberries	cantelope	pear	cupcakes			grits		turkey	hotsauce			onions	mustard	horseradish
	
	snausages	pineapple	juice		avocado	swiss cheese	beer	eggnog	beef jerky	bree	ghee	peanut butter
	flax		ghost pepper	pumpkin pie spice	matcha	moringa	himalayan	almonds <3	walnuts	pistache	pican
	quinoa	olive oil	black pepper		cumin	

	quartz	sapphire		ruby	diamond	 emerald pearl	obsidian	flint	granite	magnetite	jasper ice
	diamond	amethyst	indigo	anthrocite	chrysophrase	jade		aggot	mica	
d
	brave	ook	nook	zook	MOST_HOLY_GRAIL	CHIM_CHIMN_E	elle G choir	hi me cat	
	iOvnow	sorcear	planet bell47	coma84				joe

	creative	dork		cog	jerk	juice	oopz	dawg	craven	schnell	cat	dog	duck stuff  niche
	great jorb derf	vanilla	gdansk	GORSH	why do I hunger?
	push	zerk		na'an	goat milk		molasses		beans	cabbage	heirloom tomatoes
	do it k	very	good	man		tree			done	slice		pie		hmm	potatoes?
	chocolate	whip cream	sundae no	mayonaisse	fat	HODL	mincemeat	yams	pineapples
	do exist		perch		tears		madafaka souflette	snow
	doe			mustard		peppercorn	pecans	mango	pears	crab		macadamias	spinach cat

	zuke		cucu		spaghetti squash		mozarella	ricotta	parmessian cat	grey pupon	tiger sauce
	jamaica hellfire	pisqueya		acid rain xPs

	graft	instigate	craft	manage	summon	drink	traverse	straffe	grow	stew
	jello	pudding	tapioca	banana creme	chestnuts	brazil nuts	blue corn chips	salsa
	nein teimz [ten]
 
	so fat	:*	1f
	mustard? yeah
	how 'bout amaranth? cool		I shouldn't eat restrictively forever.  I couldn't handle a surprises
	teff spelt	kamut	
 	I am not hungry	not really.	no.  yeah I am always hungry, but not really.  g			2
	I will eat when my body needs to.qserf
	I love the idea of food
	I feel so coolbuf
	I know, I think I feel obsessed with eating
	cat catcat cat  cat  cat cat cat 	cat cat  cat cat cat cat  cat  catting
	cat  cat cat	cat  cat cat  cat cat cat  cat cat cat  cat cat catcat cat cat cat cat cat cat catcat  cat cat cat cat cat cat cat cat cat cat 
	cat cat  cat  	yellow cat	blue cat 
	danish		orance cat	oopcat boopcat can cat  cat cat cat  cat cat  cat	kate
	macaroons	figs pomegranates		caaaaaat
	cat 	car cat 	cat 	cat	cat	cat	cat	cat	caq  t	coolcat	cat	cat	cat cat	catfish	cattle	cats, the musical
	fecat cat cat 	cat	cat 	cat	cat 	cawwt	cat	coolcat		cat	cat	cat cat 	catbird	cat tail	acds 

	ccdwegcc   ec fscc c vf wgc   fgg11  sccdescsde44wgwg w3wxxx  f gs88sg3sfew wgrr  54wgwgfewwqgrwwgw  wf4242ffrwwswgfeqwrwcesscvew fsrwcrgvwefw csd	cat		1	fceacdccat  fsc
	cats cats catsq
	>			fweg qww12wrgvrwffc32fccw  ff   	ffffefegf		88111 1sse	2  2
exf
206, 22f
wqffqwsssfqqqffwqf99	(red balloons) f			8f_
eswffs
wwf fewfe   ewfffewfffefffff			9
wfsffwffwe fefefefe fef catcatfrfefefewfef fefe fefefeefe2t4
1337zqwwsefegfweedeeewfwwfefewfeewwsfewffefg grfe   fewfew fefewfefewfefefewfefew?????fe fefegr  fewfewfeww3ww4g4csfewgww2424         wvqssw fq      333 pub				ok
			gqgqw		9qf		7ss	q
	> catbuf										buff sus 	the hunger is real.
	> catbufs	svc
		svccat		w	catbus	catmaxx		
	ten times overeasy cat
f					wgrW fews ggwrhat	afasc	feqfqq fg fefwe fewf egw cs few		w00f wOOf e
	f					fecs w
sdfwffeffefffffffffffq3fqeqfsqf	agwreffeewrgefefefefefefgfwfsf
dfewegvsssgs svasv ghost cat		    dsf     sfrecewaef asvsfsfgvr davf		wwfaffle cat   	3cat	qwf

s bOpwe wfssewgfsegfqw2sfewwwfewefw fewfewewsfsv shat cat
qes	wachit nah	don't satww1wewqwqe
						don't bat				helicat	quail cat
			wge					don't get fat 	wredffsfffs
	vwq my artwg ok dwf	fgw	cat 		111            	wrgbsewswewefq qfeisfw  wf222fess gfeedfgs  f    sr ewfefeqeff ffffcgefffefffew gwrfefef few
	q	  q ejw	cra-zMAX			snygi	    f		wab cat fs  gweff    		cat 
	r
	i miss my woods.		gg d f f	bOmbshell cat
//ssgf	eff				satq catfgrqqqqr	wffef		spoof cat				ballast cat						cat clogger
f		p			wfsss				frozen custard
fa		hyucks				e			w			1	d									wfe fsffesffeq
		breathe now	yes.		 qqqf s f Fffeff fsfffffef	wq  3331


fewewfewfswesfewfwwqw
g
f
	*/

#define SvINIT( $AV, $SV )		AvINIT1(		$AV );				\
						/*	SvREFCNT_inc(			$SV);	*/\
							*( AvARRAY(	$AV)	) =	$SV;

#define SvINS( $AV, $SV, $I )		AvINSERT1(	$AV,	$I );			\
						/*	SvREFCNT_inc(			$SV);	*/\
							*( AvARRAY(	$AV) +	$I )=	$SV;
SV*	inTotality(	SV*	rvICE	){
	svtype			type;
	const char	*	usage_err= "\r!	ICE::inTotality( <%s> ):	arg[0] must be an <arrayref (ICE object) >.\n";
	unsigned char	*	cube,
				*pk, *pq,
					zc;
	STRLEN			CS;
	ui08				Qx;
	ui64				Ax, Bx;

	if( (type	= SvTYPE(	rvICE ) )	!= SVt_RV || ! SvROK(	rvICE ) )										{ printf( usage_err,  	svtype_names[		type ] );		return &PL_sv_no;	}
						avICE 	= (AV*)		SvRV(	rvICE );	/*	dereference argument	*/
	if( (type	= SvTYPE(	avICE )	!= SVt_PVAV ) )													{ printf( usage_err,  	svtype_names_ref[ 	type ] );		return &PL_sv_no; 	}

	SV*				C0=*AvARRAY( avICE );

	if( AvFILLp( avICE)==0 ){
		cube = SvPVbyte( C0, CS );
		zc=zIndexOf( *( (ui64*) cube ) );

		if( zc==0 ){
			_deICE0(		cube, CS,	cube[0], pq, Qx, Ax, Bx );	
			if( Ax==0)		return 	newSViv( Bx );
		}	}
	return &PL_sv_no;
	}

SV*	toText(		SV* rvICE	){
					avOut = newAV();
					rvOut = newRV_inc( (SV*) avOut );
	svtype			svt = SvTYPE( rvICE );
	STRLEN			L;


	if( ! SvROK( rvICE) ){	L =sprintf( aString, "\r!       ICE::toText( <%s> ): arg[0] is not a reference.\n\t",	svtype_names[ svt ] );
						av_push( avOut, newSVpvn( aString, L ) );	return rvOut; }
	avICE	= (AV*) SvRV(	rvICE	);	/*	dereference argument									*/
	svt= SvTYPE(avICE);				/*	check type of supposed perl object at dereferenced address	*/
	if( svt != SVt_PVAV ){	L =sprintf( aString, "\r!       ICE::toText( <%s> ): arg[0] is not an array ref.\n\t",	svtype_names[ svt ] );
						av_push( avOut, newSVpvn( aString, L ) );	return rvOut; }

	if( AvFILLp( avICE ) !=-1) _toText();
 
	return rvOut;
	}
SV*	toHV(		SV* rvICE	){

	svtype	rt0,		t0 = SvTYPE( rvICE );
	static const char	*	arg0_err	= "\r!       ICE::unmapHV( <%s> ): arg[1] is not an arrayref.\n\t";

	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg0_err,  svtype_names[		t0 ]	);  return &PL_sv_no; }
	avICE	= (AV*) SvRV(    	rvICE );	rt0 = SvTYPE( avICE );
	if( rt0 != SVt_PVAV ){				printf( arg0_err,  svtype_names_ref[	rt0 ]	);  return &PL_sv_no; }

	_toHV();
	rvOut = newRV_inc( (SV*) hvOut );
	return rvOut;
	}
SV*	upsortQ(		SV* rvArg,	SV* svQx	){
	const char	*	arg0_err	= "\r!       ICE::upsortQ( <%s>, <%s> ): arg[0] is not an arrayref.\n\t",
				*	arg1_err	= "\r!       ICE::upsortQ( <%s>, <%s> ): arg[1] is not a packed quad.\n\t";
	svtype			t0 = SvTYPE( rvArg ),
					t1 = SvTYPE( svX	);
	if( t0 != SVt_RV || !SvROK(	rvArg	) ){	printf( arg0_err,  svtype_names[ t0 ],		svtype_names[ 0 ] );		return &PL_sv_no; }
	if( t1 != SVt_PV || !SvOK(	svQx	) ){	printf( arg1_err,  svtype_names[ t0 ],		svtype_names[ t1 ] );		return &PL_sv_no; }
	avArg	= (AV*) SvRV(    	rvArg );	t0 = SvTYPE( avArg );
	if( t0 != SVt_PVAV ){					printf( arg0_err,  svtype_names_ref[ t0 ],  	svtype_names[ t1 ] );		return &PL_sv_no; }

	SV			*	svQ,
				**	src,
				**	dst,
				**	sv0	= AvARRAY( avArg );
	ui08			*	pq;
	const ui08	*	pqx= SvPVbyte_nolen( svQx );
	const long long	x	= *( (ui64*) pqx );

	SSize_t			displacement;
	long long			lb	= 0,
					ub	= AvFILLp( avArg )+1,	i= ub >>1;		if( ub==0	){		svQ=newSVpvn( pqx, 8 );  SvINIT( avArg, svQ );	return &PL_sv_no;	}

						pq = SvPVbyte_nolen( svQ=	*( sv0 +i ) );
	while(	x !=	*( (ui64*)	pq )	){
		if(	x >	*( (ui64*)	pq )	){	lb=i;			i=( i +ub	)>>1;	if( i==lb	){ ++i;	svQ=newSVpvn( pqx, 8 );  SvINS( avArg, svQ, i ); 	return &PL_sv_no;  }
		}else{					ub=i;		i=( lb + i	)>>1;	if( i==ub	){		svQ=newSVpvn( pqx, 8 );  SvINS( avArg, svQ, i );	return &PL_sv_no;  }
			}			pq = SvPVbyte_nolen( svQ=	*( sv0 +i ) );
		}
	return &PL_sv_yes; 	// return true: index i  was redefined
	}
SV*	insortIV(		SV* rvArg,	SV* svX		){
	const char	*	arg0_err	= "\r!       ICE::insortIV( <%s>, <%s> ): arg[0] is not an arrayref.\n\t",
				*	arg1_err	= "\r!       ICE::insortIV( <%s>, <%s> ): arg[1] is not a numeric scalar.	SvTYPE( svX )==%d; SVt_IV==%d\n\t";
	svtype			t0 = SvTYPE(	rvArg ),
					t1 = SvTYPE(	svX	);
	if(	t0 != SVt_RV		|| !SvROK(	rvArg	) ){	printf( arg0_err,  svtype_names[ t0 ],		svtype_names[ t1 ] );		return &PL_sv_no; }
	if( (	t1 != SVt_IV &&
		t1 != SVt_PVIV )	|| !SvOK(	svX		) ){	printf( arg1_err,  svtype_names[ t0 ],		svtype_names[ t1 ], SvTYPE( svX), SVt_IV );		return &PL_sv_no; }
	avArg = (AV*)	SvRV(	rvArg );
	t0 = SvTYPE(			avArg );
	if( t0 != SVt_PVAV ){						printf( arg0_err,  svtype_names_ref[ t0 ],  	svtype_names[ t1 ] );		return &PL_sv_no; }

	const long long	x	= SvIVX( svX );
	SSize_t			displacement;
	long long int		lb	= 0,
					ub	= AvFILLp( avArg )+1,	i= ub >>1;			if( ub==0	){		svX=newSViv( x );  SvINIT( avArg, svX );		return &PL_sv_no;	}

	SV				**	src,
					**	dst,
					**	svA0= AvARRAY( avArg ),
					*	svA	= *(svA0 +i );
	while(	x !=	SvIVX(	svA ) ){
		if(	x >	SvIVX(	svA ) ){		lb=i;			i=( i +ub	)>>1;	if( i==lb	){ ++i;	svX=newSViv( x );  SvINS( avArg, svX, i );	return &PL_sv_no;  }
		}else{						ub=i;		i=( lb + i	)>>1;	if( i==ub	){		svX=newSViv( x );  SvINS( avArg, svX, i );	return &PL_sv_no;  }
			}			svA	= *(svA0 +i );
		}
	return &PL_sv_yes; 	// return true: index x already exists
	}
SV*	screenKeys(	SV* rvICE,	SV* rvArg	){
//	SV*				svOut;
	bool	err;
	svtype	rt0, rt1,	t0 = SvTYPE( rvICE ),
					t1 = SvTYPE( rvArg );
	const char	*	arg_err	= "\r!       ICE::screenKeys( <%s>, <%s> ): arg[%d] is not an arrayref.\n\t";
	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg_err,  svtype_names[		t0 ],  	svtype_names[	t1	], 0 );  return &PL_sv_no; }
	if( t1 != SVt_RV || !SvROK(	rvArg) ){	printf( arg_err,  svtype_names[		t0 ], 	svtype_names[	t1	], 0 );  return &PL_sv_no; }

	avICE	= (AV*) SvRV(    	rvICE );	rt0 = SvTYPE( avICE );
	avArg	= (AV*) SvRV(    	rvArg );	rt1 = SvTYPE( avArg );

	if( rt0 != SVt_PVAV ){				printf( arg_err,  svtype_names_ref[	rt0 ],  	svtype_names_ref[	rt1	], 1 );  return &PL_sv_no; }
	if( rt1 != SVt_PVAV ){				printf( arg_err,  svtype_names_ref[	rt0 ],  	svtype_names_ref[	rt1	], 1 );  return &PL_sv_no; }

	err=_screenKeys();
	if( err ) printf("\nscreenKeys() return true\n");
	return err? &PL_sv_yes: &PL_sv_no;
	}
SV*	screenHV(	SV* rvICE,	SV* rvArg	){
	SV*				svOut;
	svtype	rt0, rt1,	t0 = SvTYPE( rvICE ),
					t1 = SvTYPE( rvArg );
	static const char	*	arg0_err	= "\r!       ICE::screenHV( <%s>, <%s> ): arg[0] is not an arrayref.\n\t",
					*	arg1_err	= "\r!       ICE::screenHV( <%s>, <%s> ): arg[1] is not a hashref.\n\t";

	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg0_err,  svtype_names[		t0 ],  	svtype_names[	t1	] );  return &PL_sv_no; }
	if( t1 != SVt_RV || !SvROK(	rvArg) ){	printf( arg1_err,  svtype_names[		t0 ], 	svtype_names[	t1	] );  return &PL_sv_no; }
	avICE	= (AV*) SvRV(    	rvICE );	rt0 = SvTYPE( avICE );
	hvArg	= (HV*) SvRV(    	rvArg );	rt1 = SvTYPE( hvArg );
	if( rt0 != SVt_PVAV ){				printf( arg0_err,  svtype_names_ref[	rt0 ],  	svtype_names_ref[	rt1	] );  return &PL_sv_no; }
	if( rt1 != SVt_PVHV ){				printf( arg1_err,  svtype_names_ref[	rt0 ],  	svtype_names_ref[	rt1	] );  return &PL_sv_no; }

	_screenHV();
	svOut = newSViv( N );
	return svOut;
	}
SV*	alloc(		SV* rvICE	){
	avICE= (AV*) SvRV(	rvICE);
	if( ( t_xv=SvTYPE( avICE) ) !=SVt_PVAV){		printf("\r!	alloc(): argument 0 must be an arrayref\n", t_xv );	return &PL_sv_undef; }
	svX = _alloc()? newSVuv( x): &PL_sv_undef;
	return svX;
	}
SV*	set(			SV* rvICE,	SV* rvArg	){

	svtype	rt0, rt1,	t0 = SvTYPE( rvICE ),
					t1 = SvTYPE( rvArg );
	const char	*	arg_err	= "\r!       ICE::set( <%s>, <%s> ): arg[%d] is not an arrayref.\n\t";

	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg_err,  svtype_names[		t0 ],  	svtype_names[	t1	], 0 );  return &PL_sv_no; }
	if( t1 != SVt_RV || !SvROK(	rvArg) ){	printf( arg_err,  svtype_names[		t0 ], 	svtype_names[	t1	], 0 );  return &PL_sv_no; }

	avICE	= (AV*) SvRV(    	rvICE );	rt0 = SvTYPE( avICE );
	avArg	= (AV*) SvRV(    	rvArg );	rt1 = SvTYPE( avArg );

	if( rt0 != SVt_PVAV ){				printf( arg_err,  svtype_names_ref[	rt0 ],  	svtype_names_ref[	rt1	], 1 );  return &PL_sv_no; }
	if( rt1 != SVt_PVAV ){				printf( arg_err,  svtype_names_ref[	rt0 ],  	svtype_names_ref[	rt1	], 1 );  return &PL_sv_no; }

//	printf("\n_set() >");
	_set();
//	printf("<\n");
	return &PL_sv_yes;
	}
SV*	keys(		SV* rvICE	){
	ui08		sp[24];
	int			sL;
	avICE= (AV*) SvRV( rvICE);	zC = AvFILLp( avICE);
	avArg= newAV();
	Ex=0;
	ui64 i=0;
	for( iC=0; iC<=zC;  ++iC ){	sv = *( AvARRAY( avICE) +iC );
		cube = SvPVbyte(		sv,  CS );
		pq =cube +16;
		for(  Kx8= *( (ui64*) cube );  Kx8!=0;  Kx8>>=8 ){	Ki= Kx8;	deICE( Qx, Ax, Bx )
					x =Ex +Ax;
			for( Ex =	x +Bx;  x<Ex;  ++x){
				sL=sprintf( sp, "0x%llx", x);
				av_push( avArg, newSVpvn( sp, sL ) );
				}
			}
	//	sL=sprintf( sp, "|");
	//	av_push( avArg, newSVpvn( sp, sL ) );
		}
	rvArg =newRV_inc( (SV*) avArg);
	return rvArg;
	}
SV*	ranges(		SV* rvICE	){
	avICE= (AV*) SvRV( rvICE);	zC = AvFILLp( avICE);
	avArg= newAV();
	Ex=0;
	for( iC=0; iC<=zC;  ++iC ){ sv= *( AvARRAY(	 avICE) +iC );
		cube = SvPVbyte(	sv,  CS );
		pq =cube +16;
		for(  Kx8= *( (ui64*) cube );   Kx8!=0;  Kx8>>=8 ){	Ki= Kx8;	deICE( Qx, Ax, Bx )
			av_push( avArg, newSViv( x=Ex +Ax	) );
			av_push( avArg, newSViv( Ex=x +Bx	) );
		}	}
	rvArg =newRV_inc( (SV*) avArg);
	return rvArg;
	}
SV*	toPerl(		SV* rvICE	){
	const char	*	usage_err	=	"#       ICE::toPerl( <%s> ): arg[0] must be an <arrayref (ICE object) >.\n",
				*	cube_err[]	={	"#       ICE::toPerl( <%s> ): array index #%lld is NULL.\n",										//1
									"#       ICE::toPerl( <%s> ): scalar at array index #%lld is not a string (no cube data).\n",				//2
									"#       ICE::toPerl( <%s> ): string at array index #%lld is less-than 16 bytes (cube size: %lld byte[s]).\n",	//3
									"#       ICE::toPerl( <%s> ): cube at array index #%lld contains no keybytes (cube size: %lld byte[s]) .\n",	//4							//1
									},
				*	malloc_err	=	"#       ICE::toPerl( <%s> ): could not allocate memory for \"%s\" array.\n";
	AV*				avICE;
	SV			**	pai0,
				**	paiC,
				*	svC;
	unsigned char			s,	sizeX[	8	],
							sizeZ[	8	],
				*	pr,		row[  	384	],		ic,
				*	cube,
				**	Mpk,
				**	Mpq,
				*	Mzc;
	unsigned	long long int	
				**	MX,
				**	MZ,				Ki,	Qx, Ax, Bx, Zx;
			long long int	iC,	eC;
	svtype			type;
	STRLEN			L, L2, CS;
	rvOut	= &PL_sv_undef;

	if( (type	= SvTYPE(	rvICE ) )	!= SVt_RV || ! SvROK(	rvICE ) )										{ printf( usage_err,  	svtype_names[		type ] );			goto _free; 	}
						avICE 	= (AV*)		SvRV(	rvICE );	/*	dereference argument	*/
	if( (type	= SvTYPE(	avICE )	!= SVt_PVAV ) )													{ printf( usage_err,  	svtype_names_ref[ 	type ] );			goto _free; 	}
	if( (eC	= AvFILLp(	avICE )+1)==0 )															{														goto _free; 	}
	pai0 	= AvARRAY(	avICE );
	avOut	= newAV_alloc_x( eC +1 );		*( (ui64*) sizeX )=0;	*( (ui64*) sizeZ )=0;
	rvOut	= newRV_inc( (SV*) avOut );

	Newx( Mzc,	eC,	ui08 	);								if( Mzc==NULL)	{ printf( malloc_err, "Mzc" );									goto _free; 	}
	Newx( Mpq,	eC,	ui08*	);								if( Mpq==NULL)	{ printf( malloc_err, "Mpq" );									goto _free0; }
	Newx( Mpk,	eC,	ui08*	);								if( Mpk==NULL)	{ printf( malloc_err, "Mpk" );									goto _free1; }
	Newx( MX,	eC,	ui64*	);								if( MX==NULL) 	{ printf( malloc_err, "MX" );									goto _free2; }
	Newx( MZ,	eC,	ui64*	);								if( MZ==NULL) 	{ printf( malloc_err, "MZ" );									goto _free3; }

																						if( &*pai0==NULL)	{ printf( cube_err[1], 	svtype_names_ref[ 	type ], 0 ); Zx=0;	goto _2nd_cube; }
																svC =*	pai0;			if( !SvPOK( svC ) )	{ printf( cube_err[2], 	svtype_names_ref[ 	type ], 0 ); Zx=0;	goto _2nd_cube; }
												cube = SvPVbyte(	svC, CS );				if( CS<16 )		{ printf( cube_err[3], 	svtype_names_ref[ 	type ], 0,  CS );	goto _2nd_cube; }
			Mzc[		0	]= zIndexOf(	*( (ui64*)	cube	) );								if( Mzc[ 0 ]==-1 )	{ printf( cube_err[4], 	svtype_names_ref[ 	type ], 0,  CS );	goto _2nd_cube; }
			Newx( MX[	0 ],	8,	ui64	);													if( MX[ 0 ]==NULL )	{ printf( malloc_err, "MX[0]" );  								goto _free4; }
			Newx( MZ[	0 ],	8,	ui64	);													if( MZ[ 0 ]==NULL ) { printf( malloc_err, "MZ[0]" );				Safefree( MX[ 0 ] ); 	goto _free4; }

			Mpk[ 0 ] =	cube;
			_deICE0(    	cube, CS,	*Mpk[ 0 ], Mpq[ 0 ], Qx,  	Ax,								Bx );
			MX[	0 ][ 0 ] =									Ax;					MZ[ 0 ][ 0 ]=	Bx +Ax;
						s =	2+(char) ceil( log10l( (long double)	MX[ 0 ][ 0 ]	) );	if( s >sizeX[ 0 ] )	sizeX[ 0 ]=s;
			if( Bx >1 ){	s =	2+(char) ceil( log10l( (long double)	MZ[ 0 ][ 0 ]-1	) );	if( s >sizeZ[ 0 ] )	sizeZ[ 0 ]=s;	}

	_2nd_cube:
	for(		iC=1;	iC< eC;		++	iC ){
			Zx= *( (ui64*)	cube +1	);										paiC	= pai0 +iC;	if( &*paiC==NULL)	{ printf( cube_err[1], 	svtype_names_ref[ 	type ], iC );		continue; }
																svC =*	paiC;			if( !SvPOK( svC ) )	{ printf( cube_err[2], 	svtype_names_ref[ 	type ], iC );		continue; }
												cube = SvPVbyte(	svC, CS );				if( CS<16 )		{ printf( cube_err[3], 	svtype_names_ref[ 	type ], iC, CS );	continue; }
			Mzc[		iC	]=zIndexOf(	*( (ui64*)	cube	) );								if( Mzc[ iC ]==-1 )	{ printf( cube_err[4], 	svtype_names_ref[ 	type ], iC, CS );	continue; }
			Newx( MX[	iC ],	8,	ui64 );													if( MX[ iC ]==NULL )	{ printf( malloc_err, "MX[..]" );	while( iC >0 )	{	Safefree( MX[ --iC ] );
																																					Safefree( MZ[ iC ] );
																																				}					 	goto _free4; }
			Newx( MZ[	iC ],	8,	ui64 );													if( MZ[ iC ]==NULL ) { printf( malloc_err, "MZ[..]" );	while( iC >0 )	{	Safefree( MX[ iC ] );
																																					Safefree( MZ[ --iC ] );
																																				}	Safefree( MX[ 0 ] ); 	goto _free4; }
			Mpk[ iC ]=	cube;
			_deICE0(    	cube, CS,	*Mpk[ iC ], Mpq[ iC ], Qx,  	Ax,								Bx );
			MX[	iC ][0] =									Ax+	Zx;				MZ[ iC ][ 0 ]=	Bx +MX[ iC ][ 0 ];
						s =	2+(char) ceil( log10l( (long double)	MX[ iC ][ 0 ]	) );	if( s >sizeX[ 0 ] )	sizeX[ 0 ]=s;
			if( Bx >1 ){	s =	2+(char) ceil( log10l( (long double)	MZ[ iC ][ 0 ]-1	) );	if( s >sizeZ[ 0 ] )	sizeZ[ 0 ]=s;	}

			}

			ic=1;
	do	{
		for(	iC=0;	iC< eC;		   	++	iC )
		if(	ic<=Mzc[	iC ] )	{ 	++	Mpk[	iC ];
			_deICE(	 cube, CS,  *	Mpk[	iC ], Mpq[ iC ], Qx,	Ax,								Bx );
			MX[ iC ][ ic ]=									Ax+	MZ[ iC ][ ic-1 ];	MZ[ iC ][ ic ]=	Bx +MX[ iC ][ ic ];
						s =	2+(char) ceil( log10l( (long double)	MX[ iC ][ ic ]	) );	if( s >sizeX[ ic ] )	sizeX[ ic ]=s;
			if( Bx >1 ){	s =	2+(char) ceil( log10l( (long double) 	MZ[ iC ][ ic ]-1	) );	if( s >sizeZ[ ic ] )	sizeZ[ ic ]=s;	}
		}	} while( ++ic< 8 );

	
	for(		iC=0;	iC< eC;		++	iC ){	pr = row;	
		for(	ic=0;	ic<=Mzc[ iC ];	++	ic ){		

			if( MX[ iC ][ ic ]+1 == MZ[ iC ][ ic ] ) 	pr	+=(	L=	sprintf( pr, "%lld",			MX[ iC ][ ic ]					) );
			else							pr	+=(	L=	sprintf( pr, "%lld..%lld",		MX[ iC ][ ic ],	MZ[ iC ][ ic ]-1		) );
										pr	+=		sprintf( pr, commaspace[	sizeX[ ic ] 	+sizeZ[ ic ]	-L ]	);
			}							pr	+=		sprintf( pr, "\n" );
			
		*pr=0;
		av_push( avOut, newSVpvn( row, pr-row ) );
		}
	_free5:	for( iC=0; iC< eC; ++iC ){	Safefree( MX[ iC ] );  Safefree( MZ[ iC ] );	}
	_free4:	Safefree( MZ ); 
	_free3:	Safefree( MX );
	_free2:	Safefree( Mpk );
	_free1:	Safefree( Mpq );
	_free0:	Safefree( Mzc );
	_free:	return rvOut;
	}
SV*	fromRvAV(	SV* rvArg	){	/*printf("\r<fromRvAV()>\n");*/
	const char	*	arg0_err	= "\r!       ICE::fromRvAV( <%s> ): arg[0] must be an arrayref <ICE object>.\n\t";

	if(	SvTYPE(		rvArg ) !=		SVt_RV	||!	SvROK(	rvArg ) ){	printf( arg0_err,  svtype_names[		SvTYPE( avArg ) ] );		return &PL_sv_no; }
					avArg = (AV*)	SvRV(				rvArg );
	if(	SvTYPE(		avArg ) !=	SVt_PVAV ){					printf( arg0_err,  svtype_names_ref[	SvTYPE( avArg ) ] );	return &PL_sv_no; }
					avICE = newAV_alloc_x( 1 );
	pSv0=AvARRAY(	avICE );
		za=  AvFILLp(	avArg);
	if(	za >=0 ){
		x =	SvIVX(  svX = *AvARRAY( avArg)  );
		*( (ui64*) 		buf		)=0;	
		*( (ui64*) 		buf+1	)=0;	pk =buf;	pq =buf +16;		a=0; 	Ez=0;
		AvCUBE( avICE,	buf,			pk,		pq,		avArg,	a,	za,	Ez );
		}
			rvICE = newRV_inc( (SV*)	avICE );
	sv_bless(	rvICE,					hvICE );
	return	rvICE;
	}
