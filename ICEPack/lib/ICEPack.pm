# Inversion Cycle Encoding (ICE) Pack v0.2.0
#	Copyright 2026 Peter Arlen Schmidt
#
#	Licensed under the Apache License, Version 2.0 (the "License");
#	you may not use this file except in compliance with the License.
#	You may obtain a copy of the License at
#
#	    http://www.apache.org/licenses/LICENSE-2.0
#
#	Unless required by applicable law or agreed to in writing, software
#	distributed under the License is distributed on an "AS IS" BASIS,
#	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#	See the License for the specific language governing permissions and
#	limitations under the License.
package ICEPack;	 use strict; use warnings;no warnings 'portable';	++$|;	#system('cls');  
our $VERSION=0.2.0;
use lib "blib/arch/auto/ICEPack";
require DynaLoader;
our @ISA = qw(DynaLoader);	bootstrap ICEPack;

use Exporter;
our @EXPORT=qw( test_set_recursively );	printf("\n\nbrrrrr\n");
use Time::HiRes qw(gettimeofday tv_interval);
my @avOut=();	my @precursors;	my @precursors_off;
sub test_strikes($){
	my ( $nTests)=@_;
	my	($T,	$nTx100,		$ok,	$fail,	$perSec, $msec0, $msec1, $msec2, $x, $ICE,  @ICE, @args, @args_B4, @args_extra, @args_XX )=
		(0,	$nTests*0.01,	0,	0,		);
	$msec0=$msec1=gettimeofday;

	TEST:foreach $T(1..$nTests){
		@args=();
		@args_extra=();
		for( my $t =11;  $t >0;  --$t ){	$x = int( rand( 1024 ) );	if(		insortIV( \@args,		$x )	){	++$t;}	}

		@args_B4=@args;
		$ICE=av2ICE( \@args );
		for( my $t =3;  $t >0;  --$t ){	$x = int( rand( 1024 ) );	if(		insortIV( \@args,		$x ) ){	++$t;}
													else{	insortIV( \@args_extra,	$x );	}			}
		@args_XX=@args;
		$ok=$ICE->strikes( \@args );
		if( join('', @args) ne join('', @args_extra ) ){	if(		$ok ){ printf("\n!	ICEPack::strikes() returned false positive!	\n");		}
		#	print(	"\r	keys set:	",		join(', ', map{ sprintf( "%llX", $_ ) }	@args_B4 )		);
		#	print(	"\r	keys checked:	",	join(', ', map{ sprintf( "%llX", $_ ) }	@args_XX )		);
		#	print(	"\r	keys extra:	",	join(', ', map{ sprintf( "%llX", $_ ) }	@args_extra )		);
		#	print(	"\r	keys not found: ",	join(', ', map{ sprintf( "%llX", $_ ) }	@args )			);
			print(	"\r	keys set:	",		join(', ', @args_B4 ),	"\n");
			print(	"\r	keys checked:	",	join(', ', @args_XX ),	"\n");
			print(	"\r	keys extra:	",	join(', ', @args_extra ),	"\n");
			print(	"\r	keys not found: ",	join(', ', @args ),		"\n");
			print(	"\n\n" );
			++$fail;
			}
		$msec2=gettimeofday;

		if($msec2-$msec1 >0.1){
			$perSec =$T /( $msec2-$msec0);
			printf(	"\rtesting strikes():	%6.2f%c completed (%d) fail[s]  %11.2f/sec  ", $T/$nTx100,	37, $fail, $perSec );
			$msec1=$msec2;
		}	}
	$perSec =$nTests /( gettimeofday-$msec0);
	printf(	"\rtesting strikes():	%6.2f%c completed (%d) fail[s]  %11.2f/sec  \n", 100,	37, $fail, $perSec );
	}
sub test_clears($){
	my ( $nTests)=@_;
	my	($T,	$nTx100,		$ok,	$fail,	$perSec, $msec0, $msec1, $msec2, $x, $ICE,  @ICE, @args, @args_B4, @args_extra, @args_XX )=
		(0,	$nTests*0.01,	0,	0,		);
	$msec0=$msec1=gettimeofday;

	TEST:foreach $T(1..$nTests){
		@args=();
		@args_extra=();
		for( my $t =11;  $t >0;  --$t ){	$x = int( rand( 1024 ) );	if(		insortIV( \@args,		$x )	){	++$t;}	}

		@args_B4=@args;
		$ICE=av2ICE( \@args );
		for( my $t =3;  $t >0;  --$t ){	$x = int( rand( 1024 ) );	if(		insortIV( \@args,		$x ) ){	++$t;}
													else{	insortIV( \@args_extra,	$x );	}			}
		@args_XX=@args;
		$ok=$ICE->clears( \@args );
		if( join('', @args) ne join('', @args_extra ) ){	if(		$ok ){ printf("\n!	ICEPack::clears() returned false positive!	\n");		}
		#	print(	"\r	keys set:	",		join(', ', map{ sprintf( "%llX", $_ ) }	@args_B4 )		);
		#	print(	"\r	keys checked:	",	join(', ', map{ sprintf( "%llX", $_ ) }	@args_XX )		);
		#	print(	"\r	keys extra:	",	join(', ', map{ sprintf( "%llX", $_ ) }	@args_extra )		);
		#	print(	"\r	keys not found: ",	join(', ', map{ sprintf( "%llX", $_ ) }	@args )			);
			print(	"\r	keys set:	",		join(', ', @args_B4 ),	"\n");
			print(	"\r	keys checked:	",	join(', ', @args_XX ),	"\n");
			print(	"\r	keys extra:	",	join(', ', @args_extra ),	"\n");
			print(	"\r	keys not found: ",	join(', ', @args ),		"\n");
			print(	"\n\n" );
			++$fail;
			}
		$msec2=gettimeofday;

		if($msec2-$msec1 >0.1){
			$perSec =$T /( $msec2-$msec0);
			printf(	"\rtesting clears():	%6.2f%c completed (%d) fail[s]  %11.2f/sec  ", $T/$nTx100,	37, $fail, $perSec );
			$msec1=$msec2;
		}	}
	$perSec =$nTests /( gettimeofday-$msec0);
	printf(	"\rtesting clears():	%6.2f%c completed (%d) fail[s]  %11.2f/sec  \n", 100,	37, $fail, $perSec );
	}

sub test_precursors{							my $miss;	my @pre_args;	my @post_args;	my $ICE_B4;
	for( my $r=0; $r<$#precursors; $r+=2 ){
		my ($ranges, $args) =@precursors[$r..$r+1];
		@post_args=@$args;
		print("\rtesting crash precursor #", $r>>1, "... ");

		my	$ICE=av2ICE( $ranges );
			$ICE_B4=ICEPack::copy( $ICE );

	#	print( "\n\$ICE->set( [ ... ] );	");
		ICEPack::set(		$ICE, $args );

		if(	$ICE->checks()				# checks() performs a checksum, verifying all cube Epsilon values
		and	$ICE->clears( $args ) ){			# clears()  only reads relevant cubes, and does not checksum them
	#			printAvDBUG();
											print("######	pass	######\n");
	#		print("\n\npost op:\n[\n");			print(@{ $ICE->toPerl() }, "\n]\n\n");
	#										print(@{ $ICE->toText() }, "\n\n");
		}else{								print("######	fail	######\n\n\n");
	#		printf("\naudit:\n\n");				printAvDBUG();	print("\n\n\n\n\n\n");
	#		print("\n\npre text:\n");				print(	@{ ICEPack::toText(	$ICE_B4	)	}, "\n\n");
			print("\n\npre op:\n[\n");			print(	@{ ICEPack::toPerl(		$ICE_B4	)	}, "\n],	[", join(",", map { sprintf("0x%X", $_) }	@$args	), "],\n\n");
		#	print("\n[\n",								@{ $ICE->toPerl()	},	"\n],	[", join(', ',						@$args	), "],\n\n");

			print("\n\npost mortem:\n[\n");		print(	@{ ICEPack::toPerl(		$ICE	)	}, "\n]\n\n");
											print(	@{ ICEPack::toText(	$ICE	)	}, "\n\n");
	
			print("\narg keys not found: [",		join(",", map { sprintf("0x%X", $_) } @post_args ), "]\n\n\n\n\n\n\n\n");

	}	}	}

sub test_prompt{
	my ($x, @A1, @D1);
#	my $ICE=av2ICE( $A1 );
	my $ICE=av2ICE( [1, 2, 111, 112, 211, 222,240,260, 280, 940] );	#	bless( [], 'ICEPack' );

#	my $hv=$ICE->toHash();
#	my @keys= sort keys %$hv;
#	my $N=0;
#	foreach(@keys){	print("$N:	", unpack( "Q", $_), "\n");	++$N;	}
	
	print("\n\n\n", @{ $ICE->toText() }, "\n[", @{ $ICE->toPerl() }, "]\n\n>");
	while(	$_=<> ){
		@D1=$_=~ /\d+/g;
		@A1= map{ int($_) } @D1;
		print("\nset()==",	$ICE->set(	\@A1	),
			"\n\n\n\n\n",	@{	$ICE->toText() } ,
	#		"\n\n", @{	$ICE->toPerl() },
			"\n>");
				printAvDBUG();
	}	}

sub test_set($$$){		#\	Test ICEPack::set() by saturating the namespace range with random keys until it reaches totality.
	my ( $min, $max, $nTests)=@_;
	my	($W,			$Ct,	$pbst,						$Tsub,	$Tsub_,	$T,	$T_,	$T_stall,	$fpp,	$scale,	$scale100,	$nTx100,		$ok,	$batch,	$pass,	$fail,	$replay,					$maxZ,	$perSec, $msec0, $msec1, $msec2, $hit, $miss, $r, $R_, $d, $ICE, $ICE_B4, $x, $i, $I, %ICE, @ICE, @ICE_B4, @args, @args_B4, @args_extra, @args_XX, @keyBulk )=
		($max -$min,	0,	bless(\pack('nnn',0,0,0),'PBAR'),	0,		0,		0,	-1,	0,		0,		1,		100,			$nTests*0.01,	0,	0,		0,		0,		 ["nothing to see here\n"],	0		);

	$ICE_B4=bless( \@ICE_B4, 'ICEPack');
	$msec0=$msec1=gettimeofday;
my	$format=sprintf("%c6.%df%cc completed (%cd) fail[s]  %c11.%df/sec  max \$#ICE: %cd  NS: 0x%X..%X\r", 37, $fpp, 37, 37, 37, $fpp, 37, $min, $max);

	TEST:foreach	$T (0..$nTests-1 ){
		$Tsub_	=$T_	=-1;	$T_stall =4;
		$Tsub			=$batch =0;	$fpp=0;	$scale100 =( $scale =10**++$fpp )*100;
		$ICE=bless( [], 'ICEPack' );	$Ct =0;
		#\%ICE=();

		while(1){	++$batch;
			@args=();
			for( my $t =21;  $t >0;  --$t ){
				$x = int( rand( $W ) ) +$min;
				if(	insortIV( \@args,	$x )	){	++$t;	}
				}
		#	print("\n args: ", join(', ', @args ), "\n");

			@args_B4=@args;
			ICEPack::backup($ICE);	

		#	print( "\nset( [ ", join(', ', @args ), "] );\n \$ICE=[", @{ $ICE_B4->toPerl }, "];\n\n\n\n\n");
			$Ct += $ICE->set( \@args );	
		#	printAvDBUG();
			if(	not $ICE->checks()				# checks() performs a checksum, verifying all cube Epsilon values
		 	or	not $ICE->clears( \@args ) ){		# clears()  only reads relevant cubes, and does not checksum them
		#		){
				$ICE_B4=ICEPack::retrieve();
				++$fail;							print("\n\ntest $T failed.\n");
				printf("\naudit:\n\n");				printAvDBUG();	print("\n\n\n\n\n\n");
				print("\n\npre text:\n");				print(	@{ ICEPack::toText(	$ICE_B4	)	}, "\n\n");
			#	print("\n\npre op:\n[\n");			print(	@{ ICEPack::toPerl(		$ICE_B4	)	}, "\n],	[", join(",", map { sprintf("0x%X", $_) }	@args_B4	), "],\n\n");
				print("\n\npre op:\n[\n");			print(	@{ ICEPack::toPerl(		$ICE_B4	)	}, "\n],	[", join(",", map { sprintf("0x%X", $_) }	@args_B4	), "],\n\n");
			#	print("\n[\n",								@{ $ICE->toPerl()	},	"\n],	[", join(', ',						@$args	), "],\n\n");

				print("\n\npost mortem:\n[\n");		print(	@{ ICEPack::toPerl(		$ICE	)	}, "\n]\n\n");
												print(	@{ ICEPack::toText(	$ICE	)	}, "\n\n");
		
				print("\narg keys not found: [",		join(",", map { sprintf("0x%X", $_) } @args ), "]\n\n\n\n\n\n\n\n");

				exit(10);
				next TEST;
				}
			$maxZ = $#$ICE if $#$ICE >$maxZ;


			if( ( $msec2=gettimeofday )-$msec1 >0.2){
				if(		$T==$T_ )	{		$Tsub =	int( $Ct*$scale100 /$W )/$scale100;
								if(		$Tsub ==	$Tsub_ ){	
									if(++	$T_stall==5 )		{	$T_stall=0;
															if( $fpp< 16){
																$scale100 =( $scale =10**++$fpp )*100;
																$format=sprintf("%c6.%df%cc completed (%cd) fail[s]  %c11.%df/sec  max \$#ICE: %cd  NS: 0x%X..%X\r", 37, $fpp, 37, 37, 37, $fpp, 37, $min, $max);
														}		}
								}else{	$Tsub_=$Tsub;	--$T_stall if $T_stall >0; }
				}else{	$T_ =$T;	}
				
				$perSec =( $T + $Tsub ) /( $msec2-$msec0);
				printf(	$format, ( $T + $Tsub ) /$nTx100,	37, $fail, $perSec, $maxZ );
				$msec1=$msec2;
				}

			if( $ICE->fills( $min, $W ) ){	++$pass;	next TEST;	}
		}	}
	$perSec =$nTests /( gettimeofday-$msec0);
	printf(					$format, 100,		37, $fail, $perSec, $maxZ );	printf("\n");
	}
sub test_set_recursively(){
	while( 1 ){
#		foreach my $bit_width(20..24){		my	$W=8<<$bit_width;	my $nTests=0xFFF/$bit_width;
		foreach my $bit_width(3..4){			my	$W=4<<$bit_width;	my $nTests=0x0FFF/$bit_width;
#		foreach my $bit_width(3..4){			my	$W=8<<$bit_width;	my $nTests=0x0FFF/$bit_width;
			printf("\n range: 0x%X (%d) x%d test iteration[s]\n", $_=$W<<1, $_, $nTests );
		#	printf("\n range: 0x%X (%d) x%d test iteration[s]\n", $_=$W<<1, $_, 1 );
			#\	Each range intermediates a cyclic boundary, so each key has a 50% chance of a +1 bytewise overflow/carry.
			#\	Starting with a namespace range of CB +/- $W and ($nTests) test[s], double the range and halve the tests.
			foreach my $base2Exp( 56, 48, 40, 32, 24, 16, 8 ){
				my $bytestep=1<<$base2Exp;
				test_set( $bytestep -$W,	$bytestep +$W,	$nTests )	if( $bytestep >$W && 0xFFFFFFFFFFFFFFFF-$bytestep >$W );
				}
		}	}
	}
#	@precursors_off=(
	@precursors=(
	[	196..197,  199..200,  204,       207,       209,       211..212,  214,  216..218,		undef,
		220..227,  230..246,												undef,
		248..253,															undef,
		255..271,															undef,
		273..288,  290..301,												undef,
		303..317,															undef,
		320..321,  323,       325..332,  334..336,  338..341,						undef,
		343..346,  348..349,												undef,
		352..363,  365..367,  369..370,  372..386,  388,       390..391				],      [202, 205, 254, 272, 297, 338, 358, 376],
	[	196,       198..200,  203..205,  208..210,  213..216,  218..220,  224..226,  228..232, undef,
		235..238,															undef,
		240..253,															undef,
		255,       257..261,  264..265,  267..269,  271,       273..275,  277..280,			undef,
		282..285,  288,       292..294,  296..298,  300..301,						undef,
		303..309,  311..319,												undef,
		321..326,  328..330,  332,											undef,
		334..336,  340..342,  344..350,  352..357,								undef,
		359..363,  365..366,  369..371,  373,       375,							undef,
		377..380,  382..384,  386..387,  389..391								],      [206, 222, 239, 254, 271, 321, 378, 383],
	[	196..197,  199,       201,       204..205,  207,       212..215,					undef,
		217..218,  220,       222..223,  225..227,  229,							undef,
		232..234,  236..241,  248..249,  251..253,  255,       257..258,				undef,
		270..271,  276..279,  282,       284,       288..290,							undef,
		293..294,  297,       300,       304..310,  312..316,  318,						undef,
		320,       322..324,  326,       328..334,  337..338,  342..347,					undef,
		351,       354..355,  357..360,  362,       366,       368..371,					undef,
		373..374,															undef,
		376,																undef,
		378..381,															undef,
		381..386,  390,													undef,
		387,																undef,
		390																],      [213, 217, 233, 238, 278, 377, 380, 381],
	[	196,       198,       200..201,  206..207,  210,								undef,
		218..219,  222..225,  233,       236..238,  240..241,  243..245,				undef,
		248,       251,       259..260,  270,       286,       288..289,  291,				undef,
		293,       295,       297,       300..301,  305,								undef,
		315..316,  318,       325,       331,       336..337,  340,						undef,
		358,       360,       362,       368..370,  379,								undef,
		382..383,															undef,
		386..389,															undef,
		388..393,															undef,
		389,																undef,
		391																],      [222, 268, 293, 295, 311, 347, 384, 386],
	[	197..198,  200..201,  203..204,  210..217,  220..221,  223..224,				undef,
		227..228,  231,       233..235,  239,											undef,
		241..246,  248..257,  259,												undef,
		262..263,  265..268,													undef,
		270..275,  280..283,  286,       289..291,										undef,
		293,       295,       297,       300,       302,       307,       310..315,  318,				undef,
		322..324,  326..327,  329..332,  334..335,									undef,
		337..340,  342..344,  348,       351,											undef,
		353..358,  361..363,  365..367,  369..371,  374..375,  377..378,					undef,
		381,																	undef,
		384..388,																undef,
		387..388,																undef,
		391																	],      [274, 290, 305, 338, 366, 378, 382, 386],
	[	196,       199,       202,       207,       210..212,								undef,
		222,       224..227,  231..232,  236..238,										undef,
		240..241,  244..245,  251,       253..254,  261,       263..264,						undef,
		271,       274..275,  278,       282..283,  289,									undef,
		291..294,  298,       303..304,  307,											undef,
		309,       312,       315..316,  320,       323..325,  327..328,						undef,
		334,																	undef,
		371..374,																undef,
		375,																	undef,
		382..385,  388..389,													undef,
		390																	],	[211, 304, 309, 312, 356, 366, 376, 382],
	[	196..198,  201..204,  207..208,  212,       215,       218..219,  222..224,			undef,
		227..229,  233,       236,       241..242,  245,			undef,
		250..252,  254..256,  258,       260..262,  266..267,  270,			undef,
		273,       275,       279,       282,       284..286,  290..292,  294..296,			undef,
		298..300,  303..305,  307..308,			undef,
		311..312,  319,       321..322,  324,       327,       329..330,  334,       336..337,			undef,
		342,       346,       348,       350..351,  353..354,			undef,
		357..360,			undef,
		386..387,			undef,
		388,			undef,
		391																	],	[197, 329, 337, 342, 383, 384, 385, 387],
	[	199..200,  202..203,  205,       207..208,									undef,
		210..213,  215,       218,       222,       224..226,						undef,
		232,       234..236,  238..239,  243..245,  248,       250..252,				undef,
		255..258,  260,       262..263,										undef,
		266..267,  271,       273..277,  279,       286..288,  290..291,  294,       297,	undef,
		301,       307,       309,       311,       313,								undef,
		315,       317,       319..320,  322,       324,       326,       328..329,  331,		undef,
		347..350,  353,       356..361,  363..366,  369,       372..375,				undef,
		377..378,														undef,
		380..385,														undef,
		384..385,														undef,
		390																],	[208, 215, 245, 275, 318, 342, 379, 383],
	[	199..200,  208..209,  212..213,  220,       223,       226..227,  229..232,			undef,
		234,       236..237,  239..240,  244..245,									undef,
		247..249,  252..259,												undef,
		261,       263,       265..266,  268,       271,								undef,
		274,       277..278,  283..284,  289..292,									undef,
		294,       296,       298,       300,       302..303,  306..307,  309,       314..316,		undef,
		318,       321..322,  326..327,  329..331,									undef,
		334..335,  338,       341..342,  347,       353,								undef,
		356,																undef,
		377,																undef,
		379..381,															undef,
		381..386,															undef,
		385,       387..390													],	[235, 236, 259, 290, 300, 353, 378, 380],
	[	196..198,  204,       206,       209,       211..212,							undef,
		217..218,  223..224,  227,       233..236,														undef,
		242,       246,       254..258,  262..264,														undef,
		268,       271..273,  275..277,  281,       283..284,  286,  290,														undef,
		292,       294,       297..299,  301,       303,       307,  310..311,														undef,
		317,       319,       324,       326..327,  329,														undef,
		333..337,  341..342,  344,       346..347,  350..351,														undef,
		358,       361,														undef,
		382..383,														undef,
		385..388,														undef,
		387..392,														undef,
		390															],	[273, 276, 341, 344, 364, 366, 384, 386],
	[	196,       198..201,  203..206,  209,       211..212,  214..215,					undef,
		217,       222,       225..227,  229,       231..233,														undef,
		238..240,  243,       246,       250,       255..256,  258..259,														undef,
		271,       273..274,														undef,
		276..284,  287,       291,       295,       297,       301,														undef,
		303..304,  307..309,  311,       313..315,  323..326,														undef,
		328,       330,       332..333,  335..338,														undef,
		341..343,  345..346,  349,       357..361,														undef,
		365..367,  369..373,														undef,
		375..376,														undef,
		378..383,														undef,
		382..383,															undef,
		385,       388														],	[209, 235, 264, 282, 292, 328, 377, 381],
	[	196,       198,       201,       205..206,  209..212,  215..216,  219..220,			undef,
		222..225,  227,       229..233,  235,										undef,
		237..238,  241..242,  246..247,  251,       255..257,  259,       261,       265,		undef,
		269,       271..275,  277,       280..281,									undef,
		283..284,  288,       290..295,  297..299,									undef,
		302..303,  305..309,  311,       313..316,									undef,
		318..322,  325..326,  328..329,  331,       334,							undef,
		338,       341,       343..347,  349,       353,       355..357,  359..361,			undef,
		376..382,															undef,
		384..386,															undef,
		388,																undef,
		391																],	[262, 303, 321, 331, 342, 366, 383, 387],
	[	198..199,  203,       205..206,  208..213,  215,       217..218,  220..227,			undef,
		230..231,  233..234,  237,       239..241,									undef,
		243..244,  246,       248..249,  254,       256..257,							undef,
		259,       262,       265..269,  272,       274..275,  278..279,  281..282,			undef,
		302..306,  308..313,  316,       318..321,  326..327,  329..330,  332,			undef,
		334..335,  337,       342..344,  346..348,  350..351,						undef,
		357..360,  362..367,  369..372,										undef,
		375,																undef,
		377..380,															undef,
		382..387,															undef,
		384..385,  387,													undef,
		390																],	[224, 260, 330, 336, 345, 362, 381, 383],
	[	196..206,															undef,
		208,       210..215,  217..218,  222,  224..227,							undef,
		229,       231,       234..235,  237,  244,       246,       248,					undef,
		250..253,  256..260,  262..263,										undef,
		265..269,  271..272,  274,       276,										undef,
		278..280,  282,       284,       286,  289..292,  294..296,  298,  300..301,		undef,
		303..304,  307..310,  312..314,  316,  318..319,							undef,
		322,       324,       329..331,  333,  335..336,								undef,
		349,       354..356,													undef,
		370..375,  377,													undef,
		379..384,															undef,
		387,       389														],	[199, 207, 318, 321, 324, 327, 335, 347],
	[	198,       201..202,  206,       211,       213,       215..217,					undef,
		219..220,  224..225,  227,       229..230,  237,							undef,
		239,       242,       244,       252,       254..255,								undef,
		258,       261..262,  264,       269..270,  272,								undef,
		274..275,  279,       281,       283..284,									undef,
		301..303,  305..307,  309,       311,       319,       323,						undef,
		325,       329..330,  333,       335,       342..345,  351,       354,				undef,
		358..362,  364,       367..368,  371..373,  375..376,						undef,
		379..380,															undef,
		383..387,															undef,
		385..386,															undef,
		388																],	[213, 242, 269, 283, 323, 381, 384, 385],
	[	196..199,  202,       204..209,											undef,
		213..219,  221,       223..224,  226,       228..231,							undef,
		235..237,  239..242,												undef,
		245..248,  252..253,  257..259,  263..264,								undef,
		266..268,  273..275,  277..278,										undef,
		280..281,  286,       289,       291,       295,       299,       301..306,  308,			undef,
		313..318,  321,       323..324,											undef,
		328,       330..332,  334,       338..339,  341,       343,						undef,
		345,       349..352,  354,       357..358,  360..362,  364..367,					undef,
		369,																undef,
		371..376,															undef,
		376,       378..379,  381,       383,       385,								undef,
		387..391															],	[204, 237, 242, 282, 287, 343, 370, 375],
	[	196..200,  204,       206,       208,       211,								undef,
		213,       215..216,  218..219,  221..222,  224,       226..227,  230,				undef,
		234..238,  241..242,  245,       247..248,  256..257,  264..265,				undef,
		274..275,  277..280,  283,       285,       287,								undef,
		291..293,  295..298,  301..303,  310,       312,							undef,
		314,       317..322,  324..327,  329,       332,								undef,
		346,       348,       350..352,  356..358,  361,								undef,
		366,       369..370,  372,       374,       376,								undef,
		379,																undef,
		382..384,															undef,
		384..388,  392..393,												undef,
		390																],	[211, 277, 316, 323, 328, 332, 380, 382],
	[	196,       200,       202..203,  207..212,  215,								undef,
		221..224,  226..227,  230,       232,										undef,
		234..240,  242,       245..246,  248,       251..252,							undef,
		254,       256,       258,												undef,
		260..267,  269..271,  275,       278,       280..281,  284,  287..289,  291..292,	undef,
		294..296,  298..299,  302,       305..307,									undef,
		309,       312..313,  316..318,  321..322,									undef,
		332..337,  340..342,  345..347,  349,       351,       354,  356,       358,			undef,
		360..361,  363,       365,       367..369,  371,       373,						undef,
		375..379,															undef,
		381..383,															undef,
		385..388,															undef,
		391																],	[234, 239, 256, 267, 328, 344, 380, 384],
	[	196..200,  202..206,  208..209,  211..213,								undef,
		215..219,  221,       224,       227,       236,       239..241,					undef,
		243..248,  250,       252,       254..255,  258..259,  262,       264..266,			undef,
		268..269,  274..275,  277..279,  282..284,								undef,
		287,       289..290,  293,       295,       299..300,							undef,
		302,       304,       309..310,  312,										undef,
		315..318,  320,       322..324,  326,										undef,
		328..330,  332,       335,       337..339,  341..343,							undef,
		345..349,  352..353,  355,       357,       359..361,							undef,
		364..368,															undef,
		381..387,															undef,
		382,       385,														undef,
		387																],	[206, 250, 282, 302, 353, 355, 379, 381],
	[	197..199,  203..204,  206,       209,       212..213,							undef,
		216,       218..219,  221,       224,       226..227,							undef,
		240..242,  247..248,  251,       254,										undef,
		256..257,  259,       261,       263,       265..273,  280..282,					undef,
		287..291,  293..298,  300..301,  306..307,								undef,
		310..312,  315,       318,												undef,
		320..323,  325..328,  331,       337..339,									undef,
		342..343,  345..347,  350,       352..356,									undef,
		358..362,															undef,
		364..366,															undef,
		368..369,  371,       373..374,  376..378,									undef,
		382..384,															undef,
		390																],	[220, 297, 307, 321, 363, 364, 367, 390],
	[	196..201,  203..205,												undef,
		207..217,  220..222,												undef,
		224..227,  229,       231..236,  238..241,									undef,
		244..245,  248,       250,       252..253,  255..257,  259,						undef,
		262,       264,       267,       270,       272,       274,       276..280,				undef,
		282..283,  285..289,  292..293,  297,       299..300,  302..304,  308..310,		undef,
		312..313,  320,       322,       325,       327,       329,       331..333,  335,			undef,
		337..341,  343,       345..346,  348..351,  353..354,  356..357,				undef,
		359..360,  363..365,  369..370,  373..374,  376,							undef,
		378..379,															undef,
		381..387,															undef,
		386..387,															undef,
		389,       391,														undef],	[239, 278, 292, 315, 332, 350, 380, 385],
	[	199,       201..203,  205,       207,       209..211,							undef,
		214,       219,       224..225,  229..230,  235,       239,  242..243,		undef,
		268,       273,       277..278,  282,       293,						undef,
		295,       297,       301..304,  312..313,							undef,
		315,       318,       325,       329,       335..336,						undef,
		338,       341..344,  353,       355,       363,						undef,
		366..367,													undef,
		370..374,													undef,
		373..379,													undef,
		374,														undef,
		382,       387..389,											undef,
		391														],	[222, 229, 240, 246, 282, 366, 368, 371],
	[	196,       204,       208,       213..215,  218..219,  221,       225,  229..230,		undef,
		233,       236..238,  242,       246..247,  253,       256..257,					undef,
		260,       263..264,  271..272,  274,       278..281,  283..284,					undef,
		286,       291,       293..295,  297,       302,								undef,
		310..312,  315,       317,       319..321,									undef,
		323,       326..327,  329,       331,       337,       345,						undef,
		348..349,  356..357,  360,       363,										undef,
		367..369,															undef,
		371..374,															undef,
		376..381,															undef,
		378..380,															undef,
		382,       385..386,													undef ],	[197, 199, 208, 279, 302, 368, 375, 377],
	[	196..197,  199..201,  203,       205,       211..212,  214,						undef,
		219..221,  223,       225..226,  232..235,  237,							undef,
		239,       243..244,  247..248,  250..252,  254,       256,       258..259,  261..262,	undef,
		264,       266..267,  269..271,  273,       275..279,  281,       288..291,			undef,
		295,       298,       300..301,  303,       305..309,  311..312,					undef,
		314,       318..320,  323,       325..326,  328,								undef,
		332,       334..337,  340..343,  345..348,  350..351,  355..356,				undef,
		372..373,															undef,
		375..378,															undef,
		380..387,															undef,
		389,																undef,
		391																	],	[225, 269, 303, 326, 334, 379, 387, 388],
	[	7,    34,   40,   55,   67,												undef,
		69,   95,   118,  136,  188,					undef,
		285,  288,  296,  309,  341,  346,  363,  369,		undef,
		385,  393,  403,  420,  424,					undef,
		450,										undef,
		470													],	[7, 34, 55, 116, 218, 244, 288, 341],
	[	1..15,     17..21,													undef,
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
		508..511																],	[27, 95, 149, 243, 294, 358, 387, 397],
	[	0..5,																undef,
		7..14,     17..18,    22,        24..25,    28,        32..33,    40,        43..46,			undef,
		48..51,    53..56,    63,        65..66,										undef,
		71..72,    75..77,    79..82,    86..87,    90,        92,        95,        99..102,		undef,
		105..106,  108,       110,       112..114,  119,								undef,
		122..123,  128..130,  133..138,										undef,
		140..142,  144,       148,       150..156,  159..160,  163..164,					undef,
		169,       171..174,  176,       178..179,  181..182,							undef,
		187,       190,       194..195,  199,       203..204,							undef,
		206..213,  216,       218..219,  222,       226..230,							undef,
		233,       235..237,  239,       245..246,  248,								undef,
		254..257,  259,       264,       266..268,									undef,
		270..273,  278,       280,       283,       286..290,  293..296,  300..301,			undef,
		305..306,  312..314,  317,       320,       323..325,  328,       330..331,			undef,
		334..335,  337,       340..341,  343..347,									undef,
		349,       356,       359,       361..362,  364..367,  370..371,					undef,
		375,       377..379,  384,       388..390,  392,       394,						undef,
		396,       398..400,  402,       405..406,									undef,
		410..415,  417,       420..421,  423,       427..428,  430..431,  434..437,			undef,
		440,       444..445,  447..448,  450..451,  453,							undef,
		456..459,  461,       463..464,											undef,
		469,       471..476,  479,												undef,
		484..491,  493..495,  497..498,  501,									undef,
		503..505,															undef,
		507..510																],	[6, 20, 26, 43, 103, 216, 326, 466],
	[	0..2,      4..6,      8,         10,        12..13,									undef,
		16,        18..20,    22,        24..26,										undef,
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
		506..511																],	[32, 62, 196, 285, 353, 366, 464, 470],
	[	1..3,      12..13,    21,        25,        28..29,    32..34,    42..43,					undef,
		50,        52..54,    57,        59,        61,								undef,
		64,        66,        72,        76..77,    80,								undef,
		82,        86..87,    93..96,    98..100,   106,       112,					undef,
		117,       124,       127..128,  131,       135,       137,					undef,
		139,       141,       144..145,  150..151,								undef,
		153,       155,       157,       161..162,  171,							undef,
		178,       181,       184,       186,									undef,
		194,       198..199,  202,       205,       209,       211..212,  215,      220..223,	undef,
		225..226,  230..231,  237..239,  241,       253,       255,       257,			undef,
		261,       264..266,  269..270,  272..274,								undef,
		277..278,  282..284,  287,       290..291,								undef,
		294,       297..298,  306,       309,       312..313,  317,					undef,
		329,       332,       339..340,  347,       350,							undef,
		354,       358,       364,       367..368,  375,       377,       380,      389,	undef,
		391..394,										undef,
		396..397,  406,       411..412,  417,       421..422,  426,       428,      430..431,	undef,
		436..437,  440															],	[2, 160, 161, 304, 360, 385, 395, 409],
	[	1..3,      5,         7,         12..14,    17,   21..23,								undef,
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
		440																	],	[85, 87, 139, 143, 164, 199, 220, 439],
	[	0..16,															undef,
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
		312..323, 325..332														],	[13, 122, 181, 204, 243, 247, 264, 272],
	[	0..23,															undef,
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
		332																	],	[24, 44, 65, 109, 196, 206, 230, 318],
	[	1,2,11..12,17..19,21,29,31,39,										undef,
		42,55..56,58,61,63..65,76,80,			undef,
		88..90,102,104,112,117,				undef,
		119,123,125..126,128,134,			undef,
		149,151,159,163,166,				undef,
		188,202,206,208,211,221,222,			undef,
		228,234,246,247,251,252,261,270,274..275,	undef,
		278,286,289,293..295,297,			undef,
		303,						undef,
		305..306,309,321,323,				undef,
		330..331																],	[6, 24, 64, 75, 87, 243, 304, 326],
	[	1..2,4..5,12,21,29,													undef,
		31,37,51,65,				undef,
		85,100,112,159,179,183,			undef,
		193,211,217,221,			undef,
		230,233,240,258,288,291,306,325											],	[97, 159, 175, 206, 255, 292, 331, 332],
	[	0..2,4,															undef,
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
		331..332,																],	[11, 59, 60, 151, 163, 173, 237, 330],
	[	1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 18, 21, 							undef,
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
		327,																	],	[29, 149, 186, 203, 238, 265, 302, 326],
	[	1, 2, 12, 13, 21, 43, 57, 												undef, 
		112, 119, 143, 154, 				undef,
		162, 166, 179, 183, 195,				undef,
		197, 208, 211, 221, 222,				undef,
		234, 247, 249, 276, 289, 294, 311, 313,	undef,
		326,								undef,
		328,																	],	[14, 78, 88, 113, 121, 188, 255, 327],
	[
	0xFFFFFFFFFFC6,  0xFFFFFFFFFFC9,  0xFFFFFFFFFFE2,  0xFFFFFFFFFFE6,  0xFFFFFFFFFFEE,  0xFFFFFFFFFFF5, 0x1000000000001, 0x1000000000010,	undef,
	0x1000000000017, 0x1000000000048, 0x1000000000053, 0x100000000005B, 0x1000000000064
	],      [0xFFFFFFFFFF83,0xFFFFFFFFFF87,0xFFFFFFFFFF8C,0xFFFFFFFFFF8F,0xFFFFFFFFFFA1,0xFFFFFFFFFFA7,0xFFFFFFFFFFA8,0xFFFFFFFFFFB3,0xFFFFFFFFFFB6,0xFFFFFFFFFFC2,0x1000000000038,0x1000000000046,0x1000000000057],
	[
	0xFFFFFFFFFFFFDB..0xFFFFFFFFFFFFDE,   0xFFFFFFFFFFFFE7..0xFFFFFFFFFFFFE8, 0x100000000000006, 0x10000000000000D, 0x100000000000018, 0x100000000000033, 0x100000000000035..0x100000000000036, 0x10000000000003C
	],      [0xFFFFFFFFFFFFCA,0xFFFFFFFFFFFFD0,0xFFFFFFFFFFFFD2,0xFFFFFFFFFFFFD3,0xFFFFFFFFFFFFE0,0xFFFFFFFFFFFFF9,0xFFFFFFFFFFFFFD,0x100000000000004,0x10000000000000D,0x10000000000000E,0x100000000000014,0x100000000000030,0x10000000000003A],
	[
	0xFFFFFFFFFFFFE2,  0xFFFFFFFFFFFFE6,  0x100000000000007, 0x10000000000000B, 0x10000000000000E, 0x100000000000012, 0x100000000000018, 0x10000000000001E,
	0x100000000000020, 0x100000000000024, 0x100000000000030, 0x100000000000032, 0x10000000000003A
	],      [0xFFFFFFFFFFFFC4,0xFFFFFFFFFFFFC8,0xFFFFFFFFFFFFCE,0xFFFFFFFFFFFFD0,0xFFFFFFFFFFFFE6,0xFFFFFFFFFFFFEB,0xFFFFFFFFFFFFED,0xFFFFFFFFFFFFF0,0xFFFFFFFFFFFFF5,0x100000000000005,0x100000000000027,0x100000000000032,0x100000000000033],
	[
	0xFFFFE3,  0xFFFFFE,             0x1000003, 0x1000005, 0x100000A, 0x100000D, 0x100000F, 0x1000016..0x1000017,
	0x100001F, 0x1000033..0x1000034, 0x100003E
	],      [0xFFFFC3,0xFFFFCA,0xFFFFCE,0xFFFFDD,0xFFFFE0,0xFFFFE5,0xFFFFE6,0xFFFFEE,0xFFFFF4,0xFFFFF5,0xFFFFF8,0x1000037,0x1000038],
	[
	0x81,  0x8C,  0x99,  0x9D,  0xA8,  0xB4, 0xBF, 0x140,	undef,
	0x14B, 0x152, 0x154, 0x16A, 0x16F
	],      [0xCC,0xE1,0xE4,0x107,0x109,0x10B,0x10D,0x11F,0x138,0x139,0x142,0x157,0x177],
	[
	0xFFFFA8,  0xFFFFD2,  0xFFFFD4,  0xFFFFE2,  0xFFFFE8,  0xFFFFEB,  0xFFFFF7..0xFFFFF8,  0xFFFFFE, undef,
	0x1000013, 0x1000023, 0x1000037, 0x100004D, 0x1000050, 0x100005D, 0x1000062
	],      [0xFFFF83,0xFFFF8B,0xFFFFA7,0xFFFFAC,0xFFFFB9,0xFFFFC8,0xFFFFD3,0x1000019,0x1000048,0x1000049,0x100004A,0x100004B,0x1000053,0x1000057,0x100005A,0x100007C],
	[
	0xFFFFFFFFFF80,                   0xFFFFFFFFFF91,                   0xFFFFFFFFFF97,                   0xFFFFFFFFFF9A,  0xFFFFFFFFFFA2..0xFFFFFFFFFFA3,  0xFFFFFFFFFFAF,  0xFFFFFFFFFFB1,	undef,
	0xFFFFFFFFFFB5..0xFFFFFFFFFFB9,   0xFFFFFFFFFFC7,                   0xFFFFFFFFFFC9,                   0xFFFFFFFFFFCC,  0xFFFFFFFFFFCE,                  0xFFFFFFFFFFD0,  0xFFFFFFFFFFE0..0xFFFFFFFFFFE1,  0xFFFFFFFFFFE3..0xFFFFFFFFFFE4,	undef,
	0xFFFFFFFFFFE6,                   0xFFFFFFFFFFED,                   0xFFFFFFFFFFF2,                   0xFFFFFFFFFFF4,  0xFFFFFFFFFFF9,	undef,
	0x1000000000002,                  0x1000000000004..0x1000000000005, 0x100000000000E..0x1000000000010, 0x1000000000012,	undef,
	0x1000000000016,                  0x1000000000018,                  0x100000000001C,                  0x1000000000022,	undef,
	0x1000000000027..0x100000000002A, 0x100000000002F,                  0x100000000003B,	undef,
	0x100000000003E,                  0x1000000000048,                  0x100000000004A,                  0x100000000004D, 0x100000000004F,                 0x1000000000051, 0x100000000005B,	undef,
	0x100000000005D,                  0x1000000000060..0x1000000000062, 0x1000000000065,                  0x100000000006A, 0x100000000006D,	undef,
	0x1000000000077
	],      [0xFFFFFFFFFF81,0xFFFFFFFFFF8D,0xFFFFFFFFFF99,0xFFFFFFFFFFAE,0xFFFFFFFFFFCF,0xFFFFFFFFFFD2,0xFFFFFFFFFFD9,0xFFFFFFFFFFDA,0xFFFFFFFFFFE6,0xFFFFFFFFFFEF,0xFFFFFFFFFFFA,0xFFFFFFFFFFFD,0x100000000000C,0x1000000000013,0x100000000006C,0x1000000000071],
	[
	0xFFFFFFFFFFFFB8,  0xFFFFFFFFFFFFD7,  0xFFFFFFFFFFFFDB,  0xFFFFFFFFFFFFE2,  0xFFFFFFFFFFFFE6,  0xFFFFFFFFFFFFE8,  0xFFFFFFFFFFFFF1,  0xFFFFFFFFFFFFF6,
	0xFFFFFFFFFFFFF8,  0x100000000000012, 0x100000000000019, 0x100000000000038, 0x10000000000003B, 0x100000000000043, 0x100000000000056, 0x100000000000061
	],      [0xFFFFFFFFFFFF92,0xFFFFFFFFFFFF9B,0xFFFFFFFFFFFFAE,0xFFFFFFFFFFFFBD,0xFFFFFFFFFFFFC2,0xFFFFFFFFFFFFD3,0xFFFFFFFFFFFFF7,0xFFFFFFFFFFFFFE,0x100000000000007,0x10000000000001A,0x10000000000001F,0x10000000000002D,0x10000000000003B,0x10000000000005F,0x10000000000006D,0x100000000000077],
	[	#this is the one that finally elucidated the need for the descending-to-ascending jmp remainder.
	0xFFFFFFFFFFFFC2..0xFFFFFFFFFFFFC3,	undef,
	0xFFFFFFFFFFFFC5..0xFFFFFFFFFFFFCD,	0xFFFFFFFFFFFFCF..0xFFFFFFFFFFFFD0,	0xFFFFFFFFFFFFD3,				0xFFFFFFFFFFFFD5,				0xFFFFFFFFFFFFD9,				0xFFFFFFFFFFFFDC,		undef,
	0xFFFFFFFFFFFFDE, 			0xFFFFFFFFFFFFE7..0xFFFFFFFFFFFFE9,	0xFFFFFFFFFFFFEB,				0xFFFFFFFFFFFFED,				0xFFFFFFFFFFFFF4,				0xFFFFFFFFFFFFFB,		0x100000000000000,    0x100000000000002..0x100000000000005,	undef,
	0x100000000000007,			0x10000000000000B,			0x100000000000012,			0x100000000000015,			undef,
	0x100000000000018,			0x10000000000001C,			0x10000000000001E,			0x100000000000023,			0x100000000000028..0x100000000000029,	undef,
	0x10000000000002C,			0x100000000000030,			0x100000000000033..0x100000000000038,	0x10000000000003B..0x10000000000003C
	],      [0xFFFFFFFFFFFFC4,0xFFFFFFFFFFFFD2,0xFFFFFFFFFFFFD4,0xFFFFFFFFFFFFDC,0xFFFFFFFFFFFFDD,0xFFFFFFFFFFFFE4,0xFFFFFFFFFFFFEF,0xFFFFFFFFFFFFF6,0xFFFFFFFFFFFFF9,0xFFFFFFFFFFFFFD,0x100000000000001,0x100000000000005,0x100000000000007,0x10000000000000D,0x100000000000025,0x100000000000030],
	[	#this is the same as the previous but with all the inert arguments removed.
	0xFFFFFFFFFFFFC2..0xFFFFFFFFFFFFC3,	undef,
	0xFFFFFFFFFFFFC5..0xFFFFFFFFFFFFCD,	0xFFFFFFFFFFFFCF..0xFFFFFFFFFFFFD0,	0xFFFFFFFFFFFFD3,				0xFFFFFFFFFFFFD5,				0xFFFFFFFFFFFFD9,				0xFFFFFFFFFFFFDC,		undef,
	0xFFFFFFFFFFFFDE, 			0xFFFFFFFFFFFFE7..0xFFFFFFFFFFFFE9,	0xFFFFFFFFFFFFEB,				0xFFFFFFFFFFFFED,				0xFFFFFFFFFFFFF4,				0xFFFFFFFFFFFFFB,		0x100000000000000,    0x100000000000002..0x100000000000005,	undef,
	0x100000000000007,			0x10000000000000B,			0x100000000000012,			0x100000000000015,			undef,
	0x100000000000018,			0x10000000000001C,			0x10000000000001E,			0x100000000000023,			0x100000000000028..0x100000000000029,	undef,
	0x10000000000002C,			0x100000000000030,			0x100000000000033..0x100000000000038,	0x10000000000003B..0x10000000000003C

	],      [0xFFFFFFFFFFFFC4,0xFFFFFFFFFFFFE4,0xFFFFFFFFFFFFEF,0xFFFFFFFFFFFFF6,0xFFFFFFFFFFFFFD],
	[
	0xC0..0xC1,   0xC3..0xC4,	undef,
	0xC6..0xCD,   0xD0,         0xD3..0xD4,   0xD7..0xD8,  0xDA..0xDB,  0xE1..0xE2,   0xEA,         0xED..0xEE,	undef,
	0xF1,         0xF5,         0xF7,         0xF9,        0xFD,        0x100..0x101,	undef,
	0x104,        0x10F..0x111, 0x113..0x114, 0x118,       0x11B,       0x11F,        0x123..0x125,	undef,
	0x127,        0x129,        0x12E..0x12F, 0x131,       0x136,       0x138,        0x13A,	undef,
	0x13C,	undef,
	0x13F..0x14C, 0x14E..0x15B
	],      [0xC2,0xC5,0xCB,0xDF,0xF1,0x103,0x10B,0x113,0x116,0x12A,0x12D,0x132,0x133,0x135,0x137,0x13C],
#	);@precursors=(
	[	10,			20,			30,			40,			50,			60,			70,			80,
		100, 		200,			300,			400,			500,			600,			700,			800,
		1000,		2000,		3000,		4000,		5000,		6000,		7000,		8000
	],	[ 402, 404, 406, 408, 410, 412, 414	]
	);@precursors=(
	[
	0xFFFFFFFFFFFFC0..0xFFFFFFFFFFFFE9, undef,
	0xFFFFFFFFFFFFEB..0x10000000000003F
	],      [0xFFFFFFFFFFFFC5,0xFFFFFFFFFFFFD4,0xFFFFFFFFFFFFD5,0xFFFFFFFFFFFFDE,0xFFFFFFFFFFFFE3,0xFFFFFFFFFFFFF4,0xFFFFFFFFFFFFF7,0xFFFFFFFFFFFFF8,0xFFFFFFFFFFFFFA,0x10000000000000D,0x10000000000001A,0x100000000000020,0x100000000000024,0x100000000000025,0x10000000000003C,0x10000000000003E],

		);
	test_precursors();
#	test_prompt();

#	test_strikes(1<<16);

#	test_clears(1<<16);


#	test_set( 0,	0xFFFFFFFFFFFFFFFF,	1 );	# 64-bit NS	crashes ;/
#	test_set( 0,	0x7FFFFFFFFFFFFFFF,	1 );	# 63-bit NS
#	test_set( 0,	0xFFFFFF,				1 );	# 24-bit NS



1;


=head1 ICEPack

ICEPack - Compressed truth vector in hyperbolic time

=head1 VERSION	0.2.0

=head1 DESCRIPTION

ICE encoding is efficient for inside-out UUID tables.  It has O(1) access time to lowest / highest / nearest existing / nonexisting keys.

ICE::Cube encodes keys in octal structures called "cubes".  Decoding is O(n), but can begin at either end, and "n" is less-than 9.

ICE::Pack structures a sorted array of searchable ICE cubes, enabling hash-like and array-like access over hyperbolic time scales.

ICE::PIKE structures a regressive exponential gradient of ICE::Pack, for Instant Key Enumeration over logarithmic time scales.

So, to reiterate:
	> ICE::Cube enables trivial access to lowest / highest / nearest sparse index in O(1) time— an obvious strength for dynamic ID tables
	> ICE::Pack enables hash-like sparsity with array-like sorting which effectively works like a sorted hash
	> ICE::PIKE redefines the Perl idiom "Everything Is A Number"

ICE is a QWORD-sized compressed truth vector which uses an original variant of RLE encoding— Inversion Cycle RLE.
IC-RLE compresses repeating values into run lengths  (like RLE), but stores no explicit values— only implicit boolean truth.
Since RLE stores only the first occurrence of a repeating value, and boolean values can only be one of two, value is implicit—
so essentially, IC-RLE representation is an explicit series of run length pairs which implicitly store alternating true-false values.

To promote the integrity of the encoding across mutations, ICE compresses pairs of true-false run lengths in single entries,
and mediates computational complexity to access and mutate these entries with opportunistic [de]fragmentation.
Encoded data is stored as a series of semi-regular chunks (16 to 144 bytes in length) which are sorted into a searchable AV* array.

	> Computational complexity plots as a roughly hyperbolic asymptote given the worst case highly entropic data.
	> Batch processing affects significant improvement in mutation time complexity when leveraged by the application.
	> Variety of accessor methods enable manipulation by range, mask, sorted list and scalar arguments, as well as recombination.
	> In-memory data blocks are an easy packet payload to stream over TCP with no fragmentation and minimal layer-4 overhead.


Any sparse array compression technique which omits nulls makes the obvious but unfortunate tradeoff of gaining space
while sacrificing the implicit identity of each element by its index— often the single most characteristically useful property of arrays.
This is where ICEPack::RELIC comes in— to implement efficient non-sparse sort order computation.

For example: let's say you wish to implement a random number generator that is non-deterministic, yet also non-repeating,
and you wish to use this to allocate Session IDs in a massively distributed cloud server application.  You would have your choice
of entropy sources as usual, but instead of piping this directly into a Session ID generator, you use it to choose the "nth" free ID
in an ICEPack::RELiC instance, which trivially guards against colissions; in order to make replication across a server farm more efficient,
you can allow servers to preallocate large random sets of IDs, periodically throwing them back into the pool and drawing a new set.
In this way, edge servers can still set service-wide Session ID assignments on an event-driven basis, with no core negotiation needed,
but IDs are still guaranteed collission-free.  Not only does this free us to rate the appropriate namespace depth precisely, but it also
frees us to implement Perfect Forward Secrecy— to renew the Session-ID upon each and every response.  


=cut  