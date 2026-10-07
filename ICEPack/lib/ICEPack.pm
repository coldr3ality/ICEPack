# Inversion Cycle Encoding (ICE) Pack v0.4,2
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
use POSIX qw( log2 floor ceil );
our $VERSION=0.4.2;
use lib "blib/arch/auto/ICEPack";
require DynaLoader;
use Data::Dumper;
our @ISA = qw(DynaLoader);	bootstrap ICEPack;

#system("chcp 437");	#set the Windows command console active code page
		#	#Code Page	Name	Best For
		#	437	OEM US (DOS)	Original IBM PC characters, box-drawing
		#	850	OEM Multilingual	Western European accented characters
		#	852	OEM Central European	Polish, Czech, Hungarian, etc.
		#	855	OEM Cyrillic	Russian, Bulgarian, Serbian, etc.
		#	857	OEM Turkish	Turkish with special characters
		#	860	OEM Portuguese	Portuguese
		#	861	OEM Icelandic	Icelandic
		#	862	OEM Hebrew	Hebrew
		#	863	OEM French Canadian	French Canadian
		#	866	OEM Russian	Russian/Cyrillic
		#	874	Thai	Thai characters
		#	1200	UTF-16 LE	Unicode (but see caveat below)
		#	1252	Windows Western European	English, French, German, etc.
		#	1250-1251, 1253-1258	Windows code pages	Various languages
		#	20127	ASCII	Plain ASCII only
#printf("\n	º ¹ ⁿ ² Ω		³ ª \n\n	%c %c %c %c %c		%c %c\n\n",
#		167, 185, 252, 253, 234, 179, 166 );
use Exporter;
our @EXPORT=qw( test_set_recursively );	#printf("\n\nbrrrrr\n");
use Time::HiRes qw(gettimeofday tv_interval);
my @avOut=();	my @precursors;	my @unset_precursors;
my $msec0=gettimeofday; my $msec1=$msec0;

sub test_hits($){
	my ( $nTests)=@_;
	my	($T,	$nTx100,		$hit,	$miss,	$fail,	$perSec, $msec0, $msec1, $msec2, $x, $ICE,  @ICE, @args1, @args2 )=
		(0,	$nTests*0.01,	0,	0,		0,		);
	$msec0=$msec1=gettimeofday;

	TEST:foreach $T(1..$nTests){
		@args1=();
		@args2=();
		for( my $t =11;  $t >0;  --$t ){	$x = int( rand( 1024 ) );	if(		insortIV( \@args2,		$x )	){	++$t;}
													else{	insortIV( \@args1,		$x );			}	}

		for( my $t =222;  $t >0;  --$t ){	$x = int( rand( 1024 ) );	if(		insortIV( \@args2,		$x ) ){	++$t;}	}

		$ICE=av2ICE( \@args2 );
		$hit=$ICE->has( \@args1 );
		if($hit!=11){	$miss=11-$hit;
			print(	"\r	($miss) keys not found\n");
			++$fail;
			}
		$msec2=gettimeofday;

		if($msec2-$msec1 >0.1){
			$perSec =$T /( $msec2-$msec0);
			printf(	"\rtesting hits():	%6.2f%c completed (%d) test[s] w/ (%d) fail[s]  %11.2f/sec  ", $T/$nTx100,	37, $T, $fail, $perSec );
			$msec1=$msec2;
		}	}
	$perSec =$nTests /( gettimeofday-$msec0);
	printf(	"\rtesting hits():	%6.2f%c completed (%d) test[s] w/ (%d) fail[s]  %11.2f/sec  \n", 100,	37, $T, $fail, $perSec );
	}
sub test_strikes($){
	my ( $nTests)=@_;
	my	($T,	$nTx100,		$ok,	$fail,	$perSec, $msec0, $msec1, $msec2, $x, $ICE,  @ICE, @args, @args_B4, @args_salt, @args_XX )=
		(0,	$nTests*0.01,	0,	0,		);
	$msec0=$msec1=gettimeofday;

	TEST:foreach $T(1..$nTests){
		@args=();
		@args_salt=();
		for( my $t =11;  $t >0;  --$t ){	$x = int( rand( 1024 ) );	if(		insortIV( \@args,		$x )	){	++$t;}	}

		@args_B4=@args;
		$ICE=av2ICE( \@args );
		for( my $t =3;  $t >0;  --$t ){	$x = int( rand( 1024 ) );	if(		insortIV( \@args,		$x ) ){	++$t;}
													else{	insortIV( \@args_salt,	$x );	}			}
		@args_XX=@args;
		$ok=$ICE->strikes( \@args );
		if( join('', @args) ne join('', @args_salt ) ){	if(		$ok ){ printf("\n!	ICEPack::strikes() returned false positive!	\n");		}
		#	print(	"\r	keys set:	",		join(', ', map{ sprintf( "%llX", $_ ) }	@args_B4 )		);
		#	print(	"\r	keys checked:	",	join(', ', map{ sprintf( "%llX", $_ ) }	@args_XX )		);
		#	print(	"\r	keys extra:	",	join(', ', map{ sprintf( "%llX", $_ ) }	@args_salt )		);
		#	print(	"\r	keys not found: ",	join(', ', map{ sprintf( "%llX", $_ ) }	@args )			);
			print(	"\r	keys set:	",		join(', ', @args_B4 ),	"\n");
			print(	"\r	keys checked:	",	join(', ', @args_XX ),	"\n");
			print(	"\r	keys extra:	",	join(', ', @args_salt ),	"\n");
			print(	"\r	keys not found: ",	join(', ', @args ),		"\n");
			print(	"\n\n" );
			++$fail;
			}
		$msec2=gettimeofday;

		if($msec2-$msec1 >0.1){
			$perSec =$T /( $msec2-$msec0);
			printf(	"\rtesting strikes():	%6.2f%c completed (%d) test[s] w/ (%d) fail[s]  %11.2f/sec  ", $T/$nTx100,	37, $T, $fail, $perSec );
			$msec1=$msec2;
		}	}
	$perSec =$nTests /( gettimeofday-$msec0);
	printf(	"\rtesting strikes():	%6.2f%c completed (%d) test[s] w/ (%d) fail[s]  %11.2f/sec  \n", 100,	37, $T, $fail, $perSec );
	}
sub test_3ps($){
	my ( $nTests)=@_;
	my	($T,	$nTx100,		$ok,	$fail,	$perSec, $msec0, $msec1, $msec2, $x, $ICE,  @ICE, @args, @nargs, @draw, @hits, @args_B4, @args_salt, @args_XX )=
		(0,	$nTests*0.01,	0,	0,		);
	$msec0=$msec1=gettimeofday;

	TEST:foreach $T(1..$nTests){
		@args=();
		@args_salt=();
		for( my $t =11;  $t >0;  --$t ){	$x = int( rand( 1024 ) );	if(		insortIV( \@args,		$x )	){	++$t;}	}

		@args_B4=@args;
		$ICE=av2ICE( \@args );
		for( my $t =3;  $t >0;  --$t ){	$x = int( rand( 1024 ) );	if(		insortIV( \@args,		$x ) ){	++$t;}
													else{	insortIV( \@args_salt,	$x );	}			}
		@args_XX=@args;
		$ok=$ICE->excludes( \@args );
		if( join('', @args) ne join('', @args_salt ) ){	if(		$ok ){ printf("\n!	ICEPack::excludes() returned false positive!	\n");		}
		#	print(	"\r	keys set:	",		join(', ', map{ sprintf( "%llX", $_ ) }	@args_B4 )		);
		#	print(	"\r	keys checked:	",	join(', ', map{ sprintf( "%llX", $_ ) }	@args_XX )		);
		#	print(	"\r	keys extra:	",	join(', ', map{ sprintf( "%llX", $_ ) }	@args_salt )		);
		#	print(	"\r	keys not found: ",	join(', ', map{ sprintf( "%llX", $_ ) }	@args )			);
			print(	"\r	keys set:	",		join(', ',						@args_B4 ),	"\n"	);
			print(	"\r	keys checked:	",	join(', ',						@args_XX ),	"\n"	);
			print(	"\r	keys of salt:	",	join(', ',						@args_salt ),"\n"	);
			print(	"\r	keys excluded:\t",	join(', ',						@args ),		"\n"	);
			print(	"\n\n" );
			++$fail;
			}
		$msec2=gettimeofday;

		if($msec2-$msec1 >0.1){
			$perSec =$T /( $msec2-$msec0);
			printf(	"\rtesting excludes():	%6.2f%c completed (%6d) test[s] w/ (%d) fail[s]  %11.2f/sec  ", $T/$nTx100,	37, $T, $fail, $perSec );
			$msec1=$msec2;
		}	}
	$perSec =$nTests /( gettimeofday-$msec0);
	printf(	"\rtesting excludes():	%6.2f%c completed (%6d) test[s] w/ (%d) fail[s]  %11.2f/sec  \n", 100,	37, $nTests, $fail, $perSec );

	TEST_INCLUDES:foreach $T(1..$nTests){
		@nargs=();
		@args_salt=();

		for( my $t =11;  $t >0;  --$t ){	$x = int( rand( 1024 ) );			if(	insortIV(	\@nargs,		$x )	){	++$t;}	}
		for( my $t =3;  $t >0;  --$t ){	$x =$nargs[ int( rand( @nargs ) )];	if(	insortIV(	\@args_salt,	$x ) ){	++$t;}	}
		@args=@args_salt;

		$ICE=av2ICE( \@nargs );

		for( my $t =8;  $t >0;  --$t ){	$x = int( rand( 1024 ) );			if(	inIV(		\@nargs,		$x )
															or	insortIV( 	\@args,		$x ) ){	++$t;}	}

		@args_XX=@args;
		$ok=$ICE->includes( \@args );
		if( join('', @args) ne join('', @args_salt ) ){	if(		$ok ){ printf("\n!	ICEPack::includes() returned false positive!	\n");		}
		#	print(	"\r	keys set:	",		join(', ', map{ sprintf( "%llX", $_ ) }	@args_B4 )		);
		#	print(	"\r	keys checked:	",	join(', ', map{ sprintf( "%llX", $_ ) }	@args_XX )		);
		#	print(	"\r	keys extra:	",	join(', ', map{ sprintf( "%llX", $_ ) }	@args_salt )		);
		#	print(	"\r	keys not found: ",	join(', ', map{ sprintf( "%llX", $_ ) }	@args )			);
			print(	"\r	keys set:	",		join(', ',						@nargs ),	"\n"	);
			print(	"\r	keys checked:	",	join(', ',						@args_XX ),	"\n"	);
			print(	"\r	keys of salt:	",	join(', ',						@args_salt ),"\n"	);
			print(	"\r	keys included:	",	join(', ',						@args ),		"\n"	);
			print(	"\n\n" );
			++$fail;
			}
		$msec2=gettimeofday;

		if($msec2-$msec1 >0.1){
			$perSec =$T /( $msec2-$msec0);
			printf(	"\rtesting includes():	%6.2f%c completed (%6d) test[s] w/ (%d) fail[s]  %11.2f/sec  ", $T/$nTx100,	37, $T, $fail, $perSec );
			$msec1=$msec2;
		}	}
	$perSec =$nTests /( gettimeofday-$msec0);
	printf(	"\rtesting includes():	%6.2f%c completed (%6d) test[s] w/ (%d) fail[s]  %11.2f/sec  \n", 100,	37, $nTests, $fail, $perSec );
	}
sub test_set_precursors{
	my	(@pre_args, @post_args,	$ICE, $ICE_B4, $first, $last);	my $pass=0;	my $fail=0;	my $audit;
	my $max=$#precursors>>1;	my $nTests=$max+1;
	if(	0<=		$#_ ){	$audit=1;
						if( $_[0] >$max || $_[0]< 0		){	$first=0;	print("\n!	invalid argument[s] to test_set_precursors()\n");
						}else{							$first=$_[0];	}
		if( 1<=	$#_ ){	if( $_[1] >$max || $_[0]< $first	){	$last=$first;	print("\n!	invalid argument[s] to test_set_precursors()\n");
						}else{							$last=$_[1];	}
		}else{			$audit=0;							$last=$max;
			}
	}else{				$audit=0;					$first=0;	$last=$max;	}
	my $nRun=1+$last-$first;
	print("\ntest_set_precursors(...): running $nRun of $nTests test[s].\n\n");
	my $R=$last<<1;
	for(	my $r=$first<<1;  $r<=$R;  $r+=2 ){
		my ($ranges, $args) =@precursors[$r..$r+1];
		@post_args=@$args;
		if( ref( $ranges ) ne 'ARRAY' or ref( $args ) ne 'ARRAY' ){	printf("\nskipping undefined set() crash precursor #%-3d... ",	$r>>1 );	next;
		}else{											printf("\nreplaying set() crash precursor #%-3d... ",			$r>>1 );	}

		my	$ICE=av2ICE( $ranges );

	#	print( "\n\$ICE->set( [ ", join(', ', @$args ), " ] );	\n");
		ICEPack::snapshot(	$ICE);
		ICEPack::set(		$ICE, $args );

		if(	not	$ICE->encompasses( \@post_args	)
		or	not	$ICE->addsUp()			# addsUp() checks each cube's stored epsilon value against the sum of its cycla
			or	exitCode()
			){						++$fail;	printf("\t\t\t\t######	fail #%-3d ######", $r>>1);
		#	next if not $audit;

			$ICE_B4=ICEPack::getSnapshot();					print("\n snapshot AV in Perl has $#$ICE_B4+1 elements\n");

			printAvDBUG();
			print("\n...\n");
			print(	"pre:",						@{ ICEPack::toTextX(	$ICE_B4	)	},
					"post:",						@{ ICEPack::toTextX(	$ICE	)	},	"\n\n",
					"#precursor: \n\n[ #", scalar @precursors >>1, "\n",
												@{ ICEPack::toHex(	$ICE_B4	)	},
					"], [	",			join(",", map { sprintf("%X", $_) }	@{	$args	}	), "],	#hex\n\n"	);

		#	$ICE->excludes( \@post_args );
		#	print(	"#missing keys:\n",
		#			"		[	",	join(",",							@post_args	), "],  #dec\n",
		#			"		[	",	join(",", map { sprintf("%X", $_) }		@post_args	), "],  #hex\n\n");
														printf("\n\n\n\t\t\t\t######	fail #%-3d ######\n\n\n", $r>>1);
			exit;
		}else{											printf("\t\t\t\t######	pass #%-3d ######", $r>>1);
#			print(				"post:",						@{ ICEPack::toTextX(	$ICE	)	}	);
	#		printf("\naudit:\n\n");	printAvDBUG();	print("\n\n\n\n\n\n");
				
	#		$ICE_B4=ICEPack::getSnapshot();		print("\n snapshot AV in Perl has $#$ICE_B4+1 elements\n");

	#		print(	"\n\n",
	#				"#precursor: \n\n[ #", scalar @precursors >>1, "\n",
	#											@{ ICEPack::toHex(	$ICE_B4	)	},
	#				"], [	",			join(",", map { sprintf("%X", $_) }	@{	$args	}	), "],	#hex\n\n"	);
	#		print("\n\n\n\n\n\n\n\n");
	#		print(										@{ ICEPack::toTextX(	$ICE_B4	)	},	"\n],	[", join(', ',						@$args		), "],\n\n");

	#		print("\n\npost op:\n");				print("\n[\n",	@{ ICEPack::toHex(	$ICE	)	}, "\n],	[", join(",", map { sprintf("0x%X", $_) }	@post_args	), "],\n\n");
	#										print(		@{ ICEPack::toText(	$ICE	)	},	"\n],	[", join(', ',						@post_args	), "],\n\n");
		}	}
	printf("\n\ntry/pass/fail: $nTests/$pass/$fail\n\n");
	}
sub test_unset_precursors{
	my	(@pre_args, @post_args,	$ICE, $ICE_B4, $first, $last);	my $pass=0;	my $fail=0;
	my $max=$#unset_precursors>>1;	my $nTests=$max+1;
	if(	0<=		$#_ ){	if( $_[0] >$max || $_[0]< 0		){	$first=0;		print("\n!	invalid argument[s] to test_set_precursors()\n");
						}else{							$first=$_[0];	}
		if( 1<=	$#_ ){	if( $_[1] >$max || $_[0]< $first	){	$last=$first;	print("\n!	invalid argument[s] to test_set_precursors()\n");
						}else{							$last=$_[1];	}
		}else{						$last=$max;
			}
	}else{					$first=0;	$last=$max;	}
	my $nRun=1+$last-$first;
	print("\ntest_unset_precursors(...): running $nRun of $nTests test[s].\n\n");
	my $R=$last<<1;
	for(	my $r=$first<<1;  $r<=$R;  $r+=2 ){
		my ($ranges, $args) =@unset_precursors[$r..$r+1];
		if( ref( $ranges ) ne 'ARRAY' or ref( $args ) ne 'ARRAY' ){	printf("\nskipping undefined unset() crash precursor #%-3d... ",	$r>>1 );	next;
		}else{											printf("\nreplaying unset() crash precursor #%-3d... ",			$r>>1 );	}
		@post_args=@$args;

		

		my	$ICE=av2ICE( $ranges );
			$ICE_B4=ICEPack::copy( $ICE );

		ICEPack::snapshot(	$ICE);
		ICEPack::unset(	$ICE, $args );

		if(	not	$ICE->hits( \@post_args )	
		and 		$ICE->addsUp() ){ ++$pass;	# addsUp() checks each cube's stored epsilon value against the sum of its cycla
	#			printAvDBUG();
	#			$ICE_B4=ICEPack::getSnapshot();	print("\n snapshot AV in Perl has $#$ICE_B4+1 elements\n");
											printf("\t\t\t\t######	pass #%-3d ######", $r>>1);
	#		print("\n\npre op:\n[\n");			print(	@{ ICEPack::toHex(	$ICE_B4	)	}, "\n],	[", join(",", map { sprintf("0x%X", $_) }	@$args		), "],\n\n");
	#		print("\n\n\n\n\n\n\n\n");
##			print("\n[\n",								@{ ICEPack::toTextX(	$ICE_B4	)	}, "\n],	[", join(",", map { sprintf("0x%X", $_) }	@post_args	), "],\n\n");

	#		print("\n\npost op:\n[\n");			print(	@{ ICEPack::toHex(	$ICE	)	}, "\n],	[", join(",", map { sprintf("0x%X", $_) }	@post_args	), "],\n\n");
##											print(	@{ ICEPack::toTextX(	$ICE	)	}, "\n],	[", join(",", map { sprintf("0x%X", $_) }	@post_args	), "],\n\n");
		}else{						++$fail;	print("\t\t\t\t######	fail #%-3d ######\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n", $r>>1);
			$ICE_B4=ICEPack::getSnapshot();		print("\n snapshot AV in Perl has $#$ICE_B4+1 elements\n");
			printf("\naudit:\n\n");				printAvDBUG();	print("\n\n\n\n\n\n");
	#		print("\n\npre text:\n");				print(	@{ ICEPack::toTextX(	$ICE_B4	)	}, "\n\n");
			print("\n\npre op:\n[\n");			print(	@{ ICEPack::toHex(	$ICE_B4	)	}, "\n],	[", join(",", map { sprintf("0x%X", $_) }	@$args	), "],\n\n");
											print(	@{ ICEPack::toTextX(	$ICE_B4	)	}, "\n\n");
		#	print("\n[\n",								@{ $ICE->toHex()	},	"\n],	[", join(', ',						@$args	), "],\n\n");

			print("\n\npost mortem:\n[\n");		print(	@{ ICEPack::toHex(	$ICE	)	}, "\n]\n\n");
											print(	@{ ICEPack::toTextX(	$ICE	)	}, "\n\n");
			exit;
#			print("\narg keys not found: [",		join(",", map { sprintf("0x%X", $_) } @post_args ), "]\n\n\n\n\n\n\n\n");

		}	}
	printf("\n\ntry/pass/fail: $nTests/$pass/$fail\n\n");
	}

sub test_prompt{
	my ($x, @A1, @D1);
#	my $ICE=av2ICE( $A1 );
	my $ICE=av2ICE(	[	#hand-crafted to target NX3
#	0					1					2					3					4					5					6					7					
	0		..7,			10		..15,			20		..27,			30		..36,			40		..47,			50		..58,			60		..67,			72		..75,	
	77		..99,			100		..111,		200		..222,		300		..333,		400		..414,		500		..555,		600		..666,		700		..777,
	900		..999,		1000	..1111,		1200	..1222,		1300	..1333,		1400	..1444,		1500	..1555,		1600	..1666,		1700	..1777,
	1900	..1999,		2000	,,2111,		2200	..2222,		2300	..2333,		2400	..2444,		2500	..2555,		2600	..2666,		2700	..2777,
	2900	..2999,		3000	..3111,		3200	..3222,		3300	..3333,		3400	..3444,		3500	..3555,		3600	..3666,		3700	..3777,
	3900	..3999,		4000	..4111,		4200	..4222,		4300	..4333,		4400	..4444,		4500	..4555,		4600	..4666,		4700	..4777,
#	99		..100,		110		..111,		120		..122,		130		..133,		140		..144,		150		..155,		160		..166,		170		..177,
#	100		..107,		110		..116,		120		..127,		130		..138,		140		..147,		150		..155,		160		..167,		170		..176,
##	180		..187,		210		..215,		220		..227,		230		..236,		240		..247,		250		..258,		260		..267,		270		..275,
##	300		..306,		310		..317,		320		..328,		330		..337,		340		..345,		350		..357

#	0		..8,			10		..18,			20		..28,			30		..38,			40		..48,			50		..58,			60		..68,			70		..78,	
#	90		..98,			100		..108,		200		..208,		300		..308,		400		..408,		500		..508,		600		..608,		700		..708,	
#	900		..908,		1000	..1008,		2000	..2008,		3000	..3008,		4000	..4008,		5000	..5008,		6000	..6008,		7000	..7008,	
#	9000	..9008,		10000	..10008,		20000	..20008,		30000	..30008,		40000	..40008,		50000	..50008,		60000	..60008,		70000	..70008,	
#	90000	..90008,		100000	..100008,		200000	..200008,		300000	..300008,		400000	..400008,		500000	..500008,		600000	..600008,		700000	..700008,	
#	900000	..900008,		1000000	..1000008,	2000000	..2000008,	3000000	..3000008,	4000000	..4000008,	5000000	..5000008,	6000000	..6000008,	7000000	..7000008,	
#	9000000	..9000008,	10000000..10000008,	20000000..20000008,	30000000..30000008,	40000000..40000008,	50000000..50000008,	60000000..60000008,	70000000..70000008
	] );	#	bless( [], 'ICEPack' );

#	my $hv=$ICE->toHash();
#	my @keys= sort keys %$hv;
#	my $N=0;
#	foreach(@keys){	print("$N:	", unpack( "Q", $_), "\n");	++$N;	}
	
	print("\n\n", @{ $ICE->toText() },	"]\n>");
	while(	$_=<> ){
		@D1=$_=~ /\d+/g;
		@A1= map{ int($_) } @D1;
		if(		ord($_)==45){
				print("\nunset(", join(', ', @A1 ), ")==",	$ICE->unset(	\@A1	)	);
		}elsif(	ord($_)==62){
				print("\nsweep(", join(', ', @A1 ), ")==",$ICE->sweep(	\@A1	)	);
		}else{
				print("\nset(", join(', ', @A1 ), ")==",	$ICE->set(	\@A1	)	);
			}

		print(	"\n\n",	@{	$ICE->toText() } ,
		#		"\n\n", @{	$ICE->toHex() },
				"\n>");

	#	printAvDBUG();

		if(	not $ICE->addsUp()		){	print("\n!	doesn't add up\n");		}
		if(	not $ICE->excludes( \@A1 )	){	print("\n!	doesn't clear args: [",		join(",", @A1 ), "]\n\n\n");	}

	}	}
sub test_set($$$$$){		#\	Test ICEPack::set() by saturating the namespace range with random keys until it reaches totality.

	our	( $min, $max, $nTests, $nSamps,	$saturation				)=@_;

	our	( $window,	$Ct,			$Tsub,	$Tsub_,	$T,		$T_,	$T_stall,	$fpp,	$scale,	$scale100,	$nTx100,		$ok,	$batch,	$pass,	$fail,	$replay,					$maxZ,	$perSec, $msec2, $hit, $miss, $r, $R_, $d, $ICE, $ICE_B4, $x, $i, $I, %ICE, @ICE, @ICE_B4, @args, @args_B4, @args_salt, @args_XX, @keyBulk, @row)=
		( $max -$min,	0,			0,		0,		$nTests,	-1,	0,		0,		1,		100,			$nTests*0.01,	0,	0,		0,		0,		 ["nothing to see here\n"],	0		);
	our	$saturationCt= int( $saturation*$window );
	our			$band			= 1;
	our			$bands			= 1;
	our			$bandwidth		= $window/$bands;
	our			$bandwidth_int	=int( $bandwidth );
	our			$bandwidth_heif	=int( $bandwidth_int>>1 );
	our			$band_offset;

	$ICE_B4=bless( \@ICE_B4, 'ICEPack');
	$msec0=$msec1=gettimeofday;
our	$format=sprintf("%c6.%df%cc completed (%c4d) test[s] w/ (%cd) fail[s]  %c11.%df/sec  max \$#ICE: %cd  NS: 0x%X..%X\r", 37, $fpp, 37, 37, 37, 37, $fpp, 37, $min, $max);
	sub progress(){
		if(		$T==$T_ )	{		$Tsub =	int( $Ct*$scale100 /$window )/$scale100;
						if(		$Tsub ==	$Tsub_ ){	
							if(++	$T_stall==5 )		{	$T_stall=0;
													if( $fpp< 16){
														$scale100 =( $scale =10**++$fpp )*100;
														$format=sprintf("%c6.%df%cc completed (%c4d) test[s] w/ (%cd) fail[s]  %c11.%df/sec  max \$#ICE: %cd  NS: 0x%X..%X\r", 37, $fpp, 37, 37, 37, 37, $fpp, 37, $min, $max);
												}		}
						}else{	$Tsub_=$Tsub;	--$T_stall if $T_stall >0; }
		}else{	$T_ =$T;	}
		
		$perSec =( $T + $Tsub ) /( $msec2-$msec0);
		printf(	$format, ( $T + $Tsub ) /$nTx100,	37, $T, $fail, $perSec, $maxZ );
		}
	TEST:foreach	$T (0..$nTests-1 ){

		$Tsub_	=$T_	=-1;	$T_stall =4;
		$Tsub			=$batch =0;	$fpp=0;	$scale100 =( $scale =10**++$fpp )*100;
		$ICE=bless( [], 'ICEPack' );	$Ct =0;

		$band			= 1;
		$bands			= 1;
		$bandwidth		= $window/$bands;
		$bandwidth_int	=int( $bandwidth );
		$bandwidth_heif	=int( $bandwidth_int>>1 );

		#\%ICE=();

		while(1){	++$batch;
			@args=();
			for( my $t =$nSamps; $t >0;  --$t ){
######			This concentrates what would be fairly entropic values for $x into distinct bands in fifth-intervals with the array length.
######			See ./scratch_perl/bands.pl for a visual demo.
######			This is intended to increase the probability of the extreme case of 5-way fragmentation under nominal entropy.
		#		$bands			= int($maxZ/5)+1;
		#		$bandwidth		= $window/$bands;
		#		$bandwidth_int	=int( $bandwidth );
		#		$bandwidth_heif	=int( $bandwidth_int>>1 );
		#		$band_offset=int( $bandwidth*rand( $bands ) );	# choose a band
		#		$x	= $band_offset						# geomean two random values in an RMS relationship with the band's zero-crossing
		#			+int( (		(rand( $bandwidth_int )-$bandwidth_heif)
		#					*	(rand( $bandwidth_int )-$bandwidth_heif)	)/$bandwidth_heif )
		#			+$bandwidth_heif
		#			+$min;

######			Alternatively, basic rand():
				$x = int( rand( $window ) ) +$min;
		
				if(	insortIV( \@args,	$x )	){	++$t;	}
				}


		#	print("\n args: ", join(', ', @args ), "\n");

			@args_B4=@args;

			ICEPack::snapshot($ICE);
		#	$ICE_B4=ICEPack::getSnapshot();	#getting the snapshot creates a new one, using memory
		#	if( $#ICE_B4!=$#ICE){	print("\n!	snapshot differs in length: $#ICE_B4+1  rather than $#ICE+1\n");	exit;}
		#	my $zC= $#ICE_B4< $#ICE? $#ICE_B4: $#ICE;
		#	for( my $iC=0; $iC<=$zC; ++$iC ){
		#		if( $$ICE_B4[ $iC ] ne $$ICE[ $iC ] ){	print("\n!	snapshot cube #$iC ne\n");	exit;}
		#		}
		
		
		#	print( "\nset( [ ", join(', ', @args ), "] );\n \$ICE=[", @{ $ICE_B4->toHex }, "];\n\n\n\n\n");
			$Ct += $ICE->set( \@args );	

			if( $#ICE<1 && $ICE->zRange(0)<1 ){
					#			print("	avICE[0]->zRange(0) = ", $ICE->zRange(0), "\n");

					#	printf("\naudit:\n\n");				printAvDBUG();	print("\n\n\n\n\n\n");
						}
			if(	#	0
				not	$ICE->encompasses( \@args	)	
			or	not	$ICE->addsUp()					# addsUp() checks each cube's stored epsilon value against the sum of its cycla
		#		exitCode()
				){
				printf("\naudit:\n\n");				printAvDBUG();	print("\n\n\n\n\n\n");
				$ICE->excludes( \@args );
				$ICE_B4=ICEPack::getSnapshot();	print("\n snapshot AV in Perl has $#$ICE_B4+1 elements\n");
				++$fail;							print("\n\ntest $T failed	 ", scalar localtime(), "\n");

		#		print("\n\npre text:\n");				print(	@{ ICEPack::toTextX(	$ICE_B4	)	}, "\n\n");
			#	print("\n\npre op:\n[\n");			print(	@{ ICEPack::toHex(		$ICE_B4	)	}, "\n],	[", join(",", map { sprintf("0x%X", $_) }	@args_B4	), "],\n\n");
				print("\n\npre op:\n[\n");			print(	@{ ICEPack::toHex(	$ICE_B4	)	},	"\n],	[", join(",", map { sprintf("0x%X", $_) }	@args_B4	), "],\n\n");
																						#	"\n],	[", join(', ',						@args_B4	), "],\n\n");
			#	print("\n[\n",								@{ $ICE->toHex()	},					"\n],	[", join(', ',						@$args		), "],\n\n");

		#		print("\n\npost mortem:\n[\n");		print(	@{ ICEPack::toHex(	$ICE	)	}, "\n]\n\n");
		#										print(	@{ ICEPack::toTextX(	$ICE	)	}, "\n\n");
		
				print("\narg keys not found: [",		join(",", map { sprintf("0x%X", $_) } @args ), "]\n\n\n\n\n\n\n\n");

				exit(10);	
				next TEST;
				}

			$maxZ = $#$ICE if $#$ICE >$maxZ;	clearAvDBUG();
		#	if( $ICE->fills( $min, $window ) ){			++$pass;	next TEST;	}
		#	The tricky thing with using ICEPack::fills() to determine test completion, is that if the object contains additional keys
		#	in addition to the range described by $min..$min+$window, it will not pass!
		#	For now, we're just going to do a simple count-based 

			if( (	$msec2=gettimeofday )-$msec1 >0.2 ){	progress();		$msec1=$msec2;
				if(	$Ct >=$saturationCt ){								++$pass; next TEST; } }
			elsif(	$Ct >=$saturationCt ){			#	progress();
																	++$pass; next TEST; }
		#	if( $msec2-$msec1 >0.1){
		#		$bands			= int($maxZ/5)+1;
		#		$bandwidth		= $window/$bands;
		#		$bandwidth_int	=int( $bandwidth );
		#		$bandwidth_heif	=int( $bandwidth_int>>1 );
		#		}
		}	}

#	$T=$nTests; #++$pass;
	$Tsub=0;
	progress();	#	printf("\n");
	exit if( exitCode());
	}
my $LOG2X24=log2(0xFFFFFF);
sub test_set_recursively($$$){	my($start_bits, $end_bits, $saturation)=@_;	my $saturation_pct=$saturation*100;
	print("\n recursive test script started ", scalar localtime(), "\n\n");
	while( 1 ){							
######			Increasing the sample rate beyond the square root of the NS window 
		foreach my $bit_width($start_bits..$end_bits){	my	$W=1<<($bit_width-1);	my $rms=sqrt( $W )<<2;
		my $nSamps=$rms;	#	$nSamps=0 if $nSamps >120;
#		foreach my $bit_width(6..8){	my	$W=1<<$bit_width;	my $nSamps=240;
#		foreach my $bit_width(8..8){			my	$W=4<<$bit_width;	my $nTests=0x0FFF/$bit_width;
#		foreach my $bit_width(3..4){			my	$W=8<<$bit_width;	my $nTests=0x0FFF/$bit_width;


			my $nTests=int( (100000/$saturation )/$rms );	$nTests=1 if $nTests==0;
		#	printf("\nhit %d%c saturation of %d-bit namespace %3dx at sample rate %3d/call        \n",
		#			$saturation_pct, 37,  $bit_width, $nTests, $nSamps );

	## quiet for now
			printf("\n%d-bit NS (+/- %-3d) to %d%c saturation %3dx, sample rate: %d/call        \n",
					 $bit_width,	$W,	$saturation_pct, 37, $nTests,			$nSamps );
		#	printf("\n range: 0x%X (%d) x%d test iteration[s]\n", $_=$W<<1, $_, 1 );
			#\	Each range intermediates a cyclic boundary, so each key has a 50% chance of a +1 bytewise overflow/carry.
			#\	Starting with a namespace range of CB +/- $W and ($nTests) test[s], double the range and halve the tests.
		#	foreach my $base2Exp( 56, 48, 40, 32, 24, 16, 8 ){
			foreach my $base2Exp( 8, 16, 24, 32, 40, 48, 56 ){
				my $bytestep=1<<$base2Exp;

			#	printf("\n	NS 0x%-3llX +/- %-3d\n",$bytestep, $_=$W<<1);
				test_set( $bytestep -$W,	$bytestep +$W,	$nTests,	$nSamps, $saturation )	if( $bytestep >$W && 0xFFFFFFFFFFFFFFFF-$bytestep >$W );
				printf("\n");
				}
		}	}#			^NS lowbound		^NS highbound					^NS saturation factor to pass each test
	}
sub relay_race{	my $NS =	@_>0?	int( $_[0] ):	0x1FFF;	my $NSx1000=$NS/10000;	if( $NS< 1 ){	printf("\n!	relay_race(...): arg #1 must be >0.\n");	return;	}
				my $nSet =	@_>1?	int( $_[1] ):	0xF0;							if( $nSet< 1 ){	printf("\n!	relay_race(...): arg #2 must be >0.\n");	return;	}
	my	($Ct,	$pct,	$_pct,	$fail,	$T, $perSec, $msec2, $hits,	@args, @args_B4, @ICE,	@ICE_B4 )=
		(0,		0,		0,		0		);
	my $ICE=bless( \@ICE, 'ICEPack');					my $args=	\@args;		my $ICE_B4=	\@ICE_B4;

	printf("\nrelay_race(): saturating, then depleting namespace 0x%X in sets of (%d) random key[s].\n\n", $NS, $nSet);
	$msec0=$msec1=gettimeofday;

	TEST: while( 1 ){	$T=0;
	#	@ICE=();
	#	print("\nset\n");
		while($Ct< $NS){	++$T;
			@args=();
			while($#args< $nSet ){ insortIV( $args, int( rand( $NS ) ) );	}
			@args_B4=@args;
			ICEPack::snapshot($ICE);
			$Ct +=	ICEPack::set( $ICE, $args );
			if(	not	$ICE->encompasses( \@args	)
			or	not	$ICE->addsUp()			# addsUp() checks each cube's stored epsilon value against the sum of its cycla
#			or	exitCode()
				){	$ICE->excludes( \@args );
				$ICE_B4=ICEPack::getSnapshot();		print("\n snapshot AV in Perl has $#$ICE_B4+1 elements\n");
				++$fail;							print("\n\ntest $T failed	 ", scalar localtime(), "\n");
				printf("\naudit:\n\n");				printAvDBUG();	print("\n\n\n\n\n\n");
#				print("\n\npre text:\n");				print(	@{ ICEPack::toText(	$ICE_B4	)	}, "\n\n");
#				print("\n\npre op:\n[\n");			print(	@{ ICEPack::toHex(	$ICE_B4	)	}, "\n],	[", join(",", map { sprintf("0x%X", $_) }	@args_B4	), "],\n\n");
	##			print("\n\npre op (set):\n[\n");		print(	@{ ICEPack::toHex(	$ICE_B4	)	},	"\n],	[", join(",", map { sprintf("0x%X", $_) }	@args_B4	), "],\n\n");
																						#	"\n],	[", join(', ',						@args_B4	), "],\n\n");

#				print("\n\npost mortem:\n[\n");	#	print(	@{ ICEPack::toHex(	$ICE	)	}, "\n]\n\n");
#												print(	@{ ICEPack::toText(	$ICE	)	}, "\n\n");
		
		#		print("\narg keys not found: [",		join(",", map { sprintf("0x%X", $_) } @args ), "]\n\n\n\n\n\n\n\n");
				print("\narg keys not found: [",		join(",", 						@args	), "]\n\n\n\n\n\n\n\n");

	#			exit(exitCode());
				exit(11);
				next TEST;
				}
			if( (	$msec2=gettimeofday )-$msec1 >0.05 ){	printf("\r++ %-2.2f%c    ", int( $Ct/$NSx1000 )/100,	37 );
				$msec1=$msec2;
				}
			}
		@args_B4=@args;		$T=0;
#		print("\nunset\n");
		while( $Ct >0 ){	++$T;
			@args=();
			while($#args< $nSet){ insortIV( $args, int( rand( $NS ) ) );	}
			@args_B4=@args;
			ICEPack::snapshot($ICE);				
			$Ct -=	ICEPack::unset(	$ICE, $args );
			if(		$ICE->contains( \@args )
			or	not	$ICE->addsUp()			# addsUp() checks each cube's stored epsilon value against the sum of its cycla
#				or	exitCode()
				){	$ICE->includes( \@args );
				print("\r!	", scalar( @args ), " of ", scalar( @args_B4 ), " flags were not unset:\n	",	join(",", map { sprintf("0x%X", $_) }	@args		),
			#									"\n			the original set of arguments: ",	join(', ',  map { sprintf("0x%X", $_) }	@args_B4	),
				"\n\n");

				$hits=$ICE->has( \@args_B4 );		#		print("\r	has(): $hits\n");
			#	$hits=$ICE->hits( \@args_B4 );
			#	print("\r	hits(): $hits\n");
			#	my @args_AFTr=@args_B4;
			#	$ICE->excludes(\@args_AFTr );
			#	print("\r	excludes(): 	", scalar( @args_AFTr ), " of ", scalar( @args_B4 ), " \n");
				

		#		$ICE_B4=ICEPack::getSnapshot();	print("\n snapshot AV in Perl has $#$ICE_B4+1 elements\n");
				printf("\naudit:\n\n");				printAvDBUG();	print("\n\n\n\n\n\n");
		#		print("\n\npre text:\n");				print(	@{ ICEPack::toText(	$ICE_B4	)	}, "\n\n");
		#		print("\n\npre op:\n[\n");			print(	@{ ICEPack::toHex(	$ICE_B4	)	}, "\n],	[", join(",", map { sprintf("0x%X", $_) }	@args_B4	), "],\n\n");
		##		print("\n\npre op (unset):\n[\n");		print(	@{ ICEPack::toHex(	$ICE_B4	)	},	"\n],	[", join(",", map { sprintf("0x%X", $_) }	@args_B4	), "],\n\n");
																						#	"\n],	[", join(', ',						@args_B4	), "],\n\n");

		#		print("\n\npost mortem:\n[\n");	#	print(	@{ ICEPack::toHex(	$ICE	)	}, "\n]\n\n");
		#										print(	@{ ICEPack::toText(	$ICE	)	}, "\n\n");
		
			#	print("\narg keys not found: [",		join(",", map { sprintf("0x%X", $_) } @args	), "]\n\n\n\n\n\n\n\n");
				print("\narg keys not found: [",		join(",", 						@args	), "]\n\n\n\n\n\n\n\n");

				exit(exitCode());
				}
			if( (	$msec2=gettimeofday )-$msec1 >0.05 ){	printf("\r-- %-2.2f%c    ", int( $Ct/$NSx1000 )/100,	37 );
				$msec1=$msec2;
				}
			if(	$#$ICE==-1)	{#	printf("\r-- %-2.2f%c    ", 100, 37 );
								last;
							}
			}
		}
	}


#my	@unset_precursors_off=(
 @unset_precursors=(
	[
	0x2,         0xA,         0xC,								undef,
	0x10..0x11,  0x16..0x18,  0x1A,  0x1C,  0x1E,				undef,
	0x25,        0x2B..0x2C,									undef,
	0x3A..0x3B,											undef,
	0x45,        0x47..0x48,  0x4E,								undef,
	0x5E,        0x62,										undef,
	0x6F,												undef,
	0x7E,        0x80,        0x82,  0x85,  0x88,  0x8A,  0x8D..0x92,	undef,
	0x9C,        0x9E..0x9F,  0xA4,							undef,
	0xBA,        0xC1,        0xC4,								undef,
	0xC8,        0xCA,        0xCD,  0xD5,  0xDA,					undef,
	0xE0,        0xE3,        0xEA,  0xF0,							undef,
	0xFB,												undef,
	0x120,       0x125,										undef,
	0x136,       0x13C,										
	],      [12, 22, 24, 25, 30, 36, 37, 44, 45, 54, 60, 83, 96, 106, 124, 137, 152, 170, 173, 175, 188, 210, 222, 228, 238, 243, 246, 259, 277, 279, 283, 288, 290],
	[
	0x1..0x7,    0x9..0x1A,   0x1C..0x26,  0x2A..0x42,  0x44..0x49,    0x4C..0x4E,					undef,
	0x50..0x5A,  0x5C..0x5F,  0x61..0x63,  0x65..0x66,  0x68..0x6A,    0x6C..0x8C,				undef,
	0x8E..0xA0,  0xA2..0xA4,  0xA6..0xB3,  0xB5..0xBE,  0xC0..0xCE,    0xD0..0xD2,    0xD4..0xD8,	undef,
	0xDA..0xDD,  0xDF..0xF3,  0xF5..0xFE,  0x100..0x106,0x109..0x110,							undef,
	0x112..0x115,0x117..0x11D,0x11F..0x124,0x126..0x134,0x136..0x13B,
	],      [4, 16, 18, 20, 33, 43, 44, 52, 65, 69, 74, 122, 124, 133, 148, 169, 172, 178, 181, 197, 209, 216, 221, 222, 226, 235, 238, 242, 267, 276, 283, 303, 306],
	[
	0x0,         0x2,         0x4..0x8,    0xA..0xC,    0xE..0x11,     0x13,          0x15..0x1E,    0x21..0x22,	undef,
	0x24..0x25,  0x27,        0x2B..0x2C,  0x2E..0x2F,											undef,
	0x31..0x36,  0x38..0x3A,  0x3C,        0x3F..0x41,  0x44..0x45,								undef,
	0x48,        0x4A..0x4F,  0x51,        0x53..0x54,  0x57,          0x59..0x5F,						undef,
	0x62..0x6F,  0x71..0x76,  0x78..0x7B,  0x7D..0x85,  0x87,									undef,
	0x89..0x98,  0x9A..0xA0,  0xA2..0xA3,  0xA5..0xBC,  0xBE..0xC7,							undef,
	0xC9..0xD2,  0xD4..0xD5,  0xD7..0xDA,  0xDC,        0xDE,									undef,
	0xE0..0xE1,  0xE3..0xE4,  0xE6..0xEC,  0xEE..0xF4,  0xF6,          0xF8..0xFB,					undef,
	0xFD..0x108, 0x10A..0x10C,0x10E..0x116,0x11A..0x11D,0x11F..0x122,						undef,
	0x124..0x126,0x128..0x129,0x12B,       0x12D..0x131,0x133..0x134,  0x136..0x13A,			undef,
	0x13B,

	],      [29, 36, 40, 60, 62, 69, 77, 82, 85, 107, 112, 114, 116, 133, 134, 161, 172, 177, 191, 194, 196, 199, 227, 231, 236, 238, 248, 258, 269, 275, 296, 309, 310],
	[
	0x0,		undef,
	0x3B,		undef,
	0x7C,		undef,
	0x8A,		undef,
	0xC8, 0xCB, 0xD9,		undef,
	0xE1,

	],      [0x0,0x7,0x18,0x1C,0x1E,0x23,0x26,0x2B,0x3F,0x50,0x52,0x5F,0x60,0x62,0x65,0x66,0x6B,0x7A,0x94,0xA0,0xAB,0xC7,0xDC,0xE4,0xE9,0xEE,0xF1,0xFE,0x10C,0x111,0x122,0x12F,0x13B],
	[
	0x0..0x1,    0x3,         0x5..0x8,    0xA..0xB,														undef,
	0xF,         0x11,        0x13,        0x16..0x17,  0x19..0x1E,    0x20,										undef,
	0x24..0x25,  0x28..0x2C,  0x30,        0x34,														undef,
	0x37,        0x3C..0x3F,  0x42..0x46,  0x49..0x4A,													undef,
	0x4C..0x4E,  0x51..0x52,  0x55..0x56,  0x58,        0x5B,											undef,
	0x61..0x62,  0x67..0x68,  0x6A,        0x6E..0x6F,													undef,
	0x71,        0x74..0x75,  0x80..0x84,  0x86,        0x88,          0x8B..0x8C,								undef,
	0x90,        0x94..0x95,  0x98..0x9A,  0x9D,        0xA3..0xA4,    0xA6,          0xAA..0xAB,    0xAD..0xB0,		undef,
	0xB3,        0xB7,        0xB9,        0xBE..0xBF,  0xC2..0xC4,											undef,
	0xC7,        0xC9,        0xCB,        0xD3..0xD4,													undef,
	0xD6,        0xDA,        0xDC,        0xE4..0xE6,  0xE9..0xEB,    0xED,									undef,
	0xEF..0xF0,  0xF6..0xF7,																		undef,
	0xFE,        0x101,       0x103..0x104,0x107,       0x10A,												undef,
	0x10F..0x111,0x113,       0x115,       0x11A,       0x11C,         0x11E,         0x120,         0x123,				undef,
	0x126..0x128,0x12D,       0x130..0x131,0x135..0x137,

	],      [0xB,0x10,0x12,0x16,0x28,0x32,0x35,0x5A,0x60,0x71,0x83,0x87,0x8B,0x91,0x9E,0xA6,0xAC,0xB5,0xB9,0xBF,0xC6,0xCE,0xD2,0xD6,0xDA,0xE2,0xE6,0xF7,0xFA,0x101,0x10B,0x11A,0x131],
	[
	0x6,		undef,
	0x25,		undef,
	0x36,		undef,
	0x65,		undef,
	0x7E,		undef,
	0x8E,		undef,
	0xB7,		undef,
	0xDD, 0xE4,		undef,
	0xED,		undef,
	0x101,

	],      [0x0,0x6,0x7,0x10,0x17,0x21,0x29,0x35,0x40,0x46,0x4D,0x59,0x5D,0x61,0x66,0x71,0x73,0x76,0x84,0x8C,0x90,0xA7,0xB2,0xB6,0xB7,0xC6,0xD7,0x10C,0x119,0x127,0x134,0x136,0x138],
	[
	0x1,         0x5,         0x7..0xC,															undef,
	0x13,        0x15..0x16,  0x18..0x1C,  0x1E..0x22,  0x27..0x28,    0x2C,          0x2E..0x31,				undef,
	0x37,        0x39,        0x3C,        0x3E,        0x40,          0x43,          0x46..0x47,    0x49..0x4C,			undef,
	0x50..0x54,  0x56,        0x58..0x59,  0x5B..0x5C,												undef,
	0x5E,        0x60,        0x62,        0x64,        0x66,												undef,
	0x68..0x6F,  0x71,        0x76..0x79,  0x7D..0x7E,												undef,
	0x81,        0x83,        0x85..0x8A,  0x8C,													undef,
	0x8E..0x94,  0x98..0x99,  0x9B,        0x9F,        0xA1..0xA4,									undef,
	0xAA,        0xAD,        0xAF..0xB0,  0xB2..0xB4,  0xB9..0xBA,									undef,
	0xBC,        0xBE..0xC1,																	undef,
	0xC3..0xC5,  0xC7,        0xC9,        0xCB,        0xCE..0xD3,    0xD5..0xD6,    0xD9..0xDA,    0xDE,		undef,
	0xE0..0xE3,  0xE5..0xE9,  0xEE,        0xF1,        0xF3..0xF4,    0xF6..0xF7,    0xF9,          0xFB,			undef,
	0xFE..0x100, 0x102..0x103,0x105,       0x109..0x10B,0x10E,         0x111..0x112,  0x114,         0x117,	undef,
	0x11A,       0x11C..0x11D,0x11F..0x120,0x122,       0x124,         0x126..0x127,						undef,
	0x12A..0x12D,0x12F..0x132,0x135,														undef,
	0x13B,

	],      [0x1,0xA,0x11,0x1B,0x29,0x4A,0x4D,0x60,0x6D,0x6F,0x78,0x7B,0x7E,0x9C,0xA2,0xAD,0xB6,0xB7,0xBB,0xBD,0xBF,0xC3,0xCB,0xD0,0xD2,0xE8,0xF6,0x111,0x113,0x118,0x121,0x122,0x134],
	[#7
	0x1,         0x3..0x4,    0x6..0x7,    0xA..0xF,    0x12..0x13,  0x17..0x1A,  0x1C..0x1D,  0x1F,	undef,
	0x22,        0x25,        0x27..0x28,  0x2A..0x2D,  0x30..0x31,  0x33..0x34,  0x36..0x37,		undef,
	0x3A..0x3B,  0x3D..0x3E,  0x44,        0x46,											undef,
	0x49,        0x4B..0x4E,  0x51,        0x53..0x54,  0x56..0x57,  0x59,						undef,
	0x5B,        0x5D,        0x5F,        0x61..0x62,  0x64,        0x66..0x67,						undef,
	0x6A..0x6C,  0x6E,        0x70..0x71,  0x73,        0x75,        0x77,							undef,
	0x79..0x7B,  0x7D,        0x7F..0x80,  0x82,        0x84,        0x86..0x87,  0x89..0x8A,			undef,
	0x8D,        0x90,        0x92..0x93,  0x98..0x99,										undef,
	0x9B..0x9F,  0xA1,        0xA4,        0xA6..0xA9,										undef,
	0xAB..0xAC,  0xAE..0xAF,  0xB3..0xB4,  0xB6..0xB8,  0xBA..0xBB,  0xBD,        0xBF,		undef,
	0xC1,        0xC5..0xC8,  0xCB,        0xCD..0xD0,  0xD2,        0xD4,        0xD6..0xDA,		undef,
	0xDC..0xDE,  0xE0..0xE2,  0xE5..0xE6,  0xE9..0xEA,  0xEC..0xEF,  0xF4,        0xF6..0xF7,		undef,
	0xF9,																		undef,	#original
	0xFA,																		undef,	# original
#	0xFB,																		undef,	# fixed
	0xFE,

	],      [0x6,0xB,0xE,0x13,0x16,0x1D,0x29,0x48,0x50,0x54,0x5A,0x6B,0x79,0x7B,0x85,0x98,0x9A,0x9D,0xA7,0xAD,0xB7,0xBA,0xBC,0xBD,0xDB,0xDF,0xE0,0xE2,0xE7,0xE9,0xEB,0xFA,0xFE],
	[#8
	0x0,         0x2..0x15,   0x17..0x1C,  0x1E..0x1F,  0x21..0x27,  0x29,        0x2B..0x35,					undef,
	0x38..0x44,  0x46,        0x48..0x49,  0x4B..0x4F,  0x51..0x57,  0x59..0x5C,  0x5E..0x63,					undef,
	0x65..0x70,																				undef,
	0x73,        0x75..0x78,  0x7B..0x82,  0x85..0x8D,													undef,
	0x8F..0x92,  0x94..0x99,  0x9B..0x9F,  0xA1..0xA4,  0xA6..0xA8,  0xAB..0xB4,							undef,
	0xB6..0xBA,  0xBC..0xC0,  0xC3..0xCA,  0xCC..0xD4,  0xD6..0xD7,  0xD9..0xEA,  0xEC..0xF5,  0xF7..0xFD,	undef,
	0xFF,

	],      [0x2,0x8,0xD,0x10,0x15,0x18,0x2A,0x2B,0x2F,0x4D,0x4F,0x53,0x5B,0x6D,0x79,0x7A,0x94,0xAC,0xB0,0xB5,0xB9,0xC0,0xC9,0xCA,0xCD,0xD3,0xDF,0xE0,0xE4,0xEF,0xF1,0xFD,0xFE],
	[#9	This is a tricky one because the last cube is a single cyclum with a rogue null void.  Technically, it is malformed, but not corrupt.
#	"Rogue null void" (RNV) is where two vectors are separated by a null gap (void), which is better expressed as one unbroken vector.
#	Diagnostics shows that if I allow ULL pmo to go negative in the "_desc" block of void _av_commit(), it'll actually handle this fine.
#	However, that enables a much worse failure mode where _av_commit() corrupts the entire structure and overrun the array allocatiuon.
#	I'm drawing a blank now on which precursors were prone to triggering that, but we have them here somewhere.
#	I think the least evil is to arrest RNVs at the accessor op level and keep _av_commit() telemetry validation tight.
#	0x0..0x7,    0x9..0xD,    0x10..0x11,													undef,
#	0x13..0x16,  0x18,        0x1A..0x1B,  0x1D..0x22,  0x24..0x28,								undef,
#	0x2A..0x2C,  0x2E,        0x30..0x33,  0x35,        0x37..0x3A,  0x3C..0x3E,  0x40,        0x42..0x43,	undef,
#	0x45..0x49,  0x4B,        0x4D..0x4E,  0x50,        0x53..0x55,								undef,
#	0x57..0x58,  0x5A..0x5D,  0x5F,        0x61..0x62,  0x64,									undef,
	0x66,        0x68..0x6E,  0x70..0x71,  0x73..0x79,  0x7B..0x7E,  0x80..0x83,					undef,
#	0x87,        0x89,        0x8B,        0x8D..0x90,												undef,
#	0x92..0x9B,  0x9D..0xA0,  0xA3..0xA6,  0xA8..0xAA,  0xAC..0xAE,							undef,
#	0xB2,        0xB4..0xB6,  0xB8,        0xBA..0xBC,  0xBF..0xC2,  0xC4,        0xC7..0xCA,			undef,
#	0xCC..0xCD,  0xCF..0xD4,  0xD6..0xDE,  0xE0..0xE4,  0xE6..0xEC,							undef,
	0xF3..0xF4,  0xF6..0xF8,  0xFB..0xFD,													undef,
#	0xFE,	#original
	0xFF,	#fixed RNV

#orig ],	[0x6,0xB,0xD,0xF,0x16,0x1A,0x1C,0x21,0x24,0x2D,0x2E,0x2F,0x3B,0x47,0x53,0x5D,0x6A,0x70,0x74,0x76,0x79,0x82,0x9A,0xA9,0xAA,0xBC,0xCC,0xD3,0xD7,0xDA,0xDF,0xF5,0xFE],
	],	[0x6A,0x70,0x74,0x76,0x79,0x82,	0xF5,0xFF],
	[#10	I[u]=I[v] was commented out of operation F	(a.k.a."_x_").  In theory, I[] values should never be altered once initialized.
	0x1..0x4,    0x6..0x9,      0xB,           0xD..0xE,      0x12..0x13,												undef,
	0x15..0x16,  0x18,          0x1D,          0x20..0x21,    0x24..0x26,												undef,
	0x29..0x2E,  0x30..0x33,    0x35..0x37,    0x39..0x3A,														undef,
	0x3C..0x3E,  0x40,          0x44..0x46,    0x48..0x49,    0x4B..0x4E,											undef,
	0x53..0x55,  0x57..0x58,    0x5A,          0x5C,          0x5E..0x60,    0x63..0x64,									undef,
	0x67..0x69,  0x6C,          0x6E..0x6F,    0x71..0x72,    0x75..0x7A,											undef,
	0x7D..0x80,  0x84..0x8C,																			undef,
	0x8F,        0x91,          0x93..0x95,    0x97..0x9A,    0x9D..0x9E,												undef,
	0xA0..0xA2,  0xA7,          0xA9..0xB0,    0xB2..0xB4,    0xB6,          0xB8..0xB9,								undef,
	0xBB,        0xBD..0xC0,    0xC4..0xC6,    0xC8..0xCA,    0xCC..0xCD,											undef,
	0xCF..0xD1,  0xD5,          0xD7..0xD8,    0xDB,															undef,
	0xE0..0xE1,  0xE3..0xE7,    0xEB..0xEF,    0xF1..0xF3,														undef,
	0xF5,        0xF7,          0xF9,          0xFB..0xFC,    0xFE..0x100,												undef,
	0x103..0x107,0x10A..0x10C,  0x10F..0x112,  0x115..0x116,												undef,
	0x118..0x119,0x11B,         0x11E..0x120,																undef,
	0x123,       0x125..0x128,  0x12A..0x12C,																undef,
	0x12E..0x131,0x136,         0x13A..0x13C,  0x13E..0x141,													undef,
	0x145..0x14B,0x14F,         0x151..0x152,  0x154..0x15A,  0x15C..0x15D,  0x15F,								undef,
	0x161..0x162,																						undef,
	0x166..0x16B,0x170..0x173,  0x175..0x177,															undef,
	0x17A..0x17D,0x17F..0x180,  0x183..0x184,  0x186,														undef,
	0x189..0x18E,0x191,         0x194..0x197,  0x19A..0x19C,  0x19F,         0x1A1..0x1A2,							undef,
	0x1A5..0x1A9,0x1AB,         0x1AE..0x1B1,  0x1B3..0x1B4,  0x1B9..0x1BC,									undef,
	0x1BF..0x1C0,0x1C2,         0x1C4..0x1C8,  0x1CA,         0x1CE..0x1D2,										undef,
	0x1D4..0x1D6,0x1D9..0x1DB,  0x1DD..0x1E0,  0x1E2,         0x1E5..0x1E6,  0x1E8..0x1E9,  0x1EC..0x1ED,			undef,
	0x1EF,       0x1F1..0x1F2,  0x1F4..0x1F7,  0x1F9,         0x1FB,												undef,
	0x1FD..0x202,0x204..0x206,  0x209..0x20A,  0x20C..0x20E,  0x210..0x211,									undef,
	0x213,       0x216..0x21C,  0x21E..0x222,  0x225,         0x227..0x228,  0x22A..0x22D,  0x22F..0x232,				undef,
	0x234..0x235,0x239,         0x23B..0x23C,  0x23E..0x23F,  0x241..0x244,  0x246,         0x248,						undef,
	0x24A,       0x24C,																					undef,
	0x24E..0x25B,0x25E,         0x261..0x262,																undef,
	0x265..0x270,																						undef,
	0x272..0x278,0x27A,         0x27C..0x27E,  0x280..0x288,  0x28A..0x28B,										undef,
	0x28D..0x28E,0x290..0x294,  0x297..0x29C,  0x2A0,         0x2A2..0x2A4,  0x2A6..0x2A7,						undef,
	0x2AB..0x2AE,0x2B1..0x2B3,  0x2B5..0x2B7,  0x2BA,         0x2BD,         0x2BF..0x2C0,							undef,
	0x2C2..0x2C4,0x2CB,         0x2CE..0x2D1,  0x2D4,														undef,
	0x2D7..0x2D8,0x2DB,         0x2DD..0x2E1,  0x2E3..0x2E4,  0x2E6,         0x2E8..0x2EB,  0x2ED..0x2F1,  0x2F4..0x2F6,	undef,
	0x2F8..0x2F9,0x2FB,
	0x2FD,

	],      [0x5,0xE,0x15,0x1E,0x2C,0x3A,0x5D,0x60,0x73,0x7A,0xB3,0xB4,0xC0,0x13E,0x161,0x17C,0x186,0x1A1,0x1AB,0x1E8,0x1FE,0x20D,0x21D,0x223,0x253,0x254,0x261,0x297,0x2C0,0x2E6,0x2E9,0x2EF,0x2FC],

	);

my @precursorzs=(
#	[	# overflows the main buffer, for which rotation still is not implemented 2026/05/10
	[
	0xDDE7,           0xE327,  0xF276,  0xF6F1,  0xFA5E,           0xFCC8,  0xFD43,  0xFF6E,
	0x1013D,          0x101A2, 0x103A3, 0x10586, 0x1062D,          0x106CA, 0x10752, 0x1084C,
	0x10897,          0x10940, 0x109D2, 0x10AFA, 0x10B03,          0x10C0B, 0x10CA3, 0x10D31,
	0x10F00,          0x1102A, 0x1110E, 0x1111F, 0x11235,          0x11336, 0x11354, 0x11495,
	0x11513,          0x11556, 0x1159E, 0x115EA, 0x11623,          0x11825, 0x118CB, 0x119D4,
	0x11A2C,          0x11A60, 0x11B12, 0x11C91, 0x11CB2,          0x11D0D, 0x11DB5, 0x11E16,
	0x11E9C,          0x11FD5, 0x12060, 0x1208B, 0x120C4..0x120C5, 0x1214E, 0x121CE, 0x1220E,
	0x12223,          0x12324, 0x1233B, 0x123C3, 0x12415,          0x12450, 0x12632, 0x1265A,
	0x126B5,          0x12713, 0x12895, 0x129B7, 0x129F0,          0x12A61, 0x12AEA, 0x12B8A,
	0x12BDB,          0x12C02, 0x12C1C, 0x12C2F, 0x12E30,          0x12E7A, 0x12EC9, 0x12F03,
	0x12F07,          0x12F3C, 0x12F51, 0x12FEE, 0x1311C,          0x13156, 0x1318D, 0x131C5,
	0x13335,          0x1333F, 0x133A3, 0x133FB, 0x1341A,          0x1343C, 0x13445, 0x1346C,
	0x1348C,          0x134FA, 0x134FF, 0x1359C, 0x135E2,          0x136C1, 0x13788, 0x137DA,
	0x137DE,          0x1386D, 0x13915, 0x1392D, 0x139D6,          0x13A23, 0x13A8A, 0x13CB9,
	0x13D4A,          0x13DF5, 0x13E27, 0x13EFB, 0x13FE3,          0x14045, 0x1404B, 0x14125,
	0x141AE,          0x14367, 0x14396, 0x143B8, 0x143CC,          0x1442A, 0x144EC, 0x14511,
	0x1451B,          0x145E5, 0x145F3, 0x146F5, 0x14719,          0x14739, 0x14757, 0x14819,
	0x148B4,          0x148E4, 0x1497F, 0x149BA, 0x14A8C,          0x14B5B, 0x14C99, 0x14CC9,
	0x14DA0,          0x14DCE, 0x14DD5, 0x14E04, 0x14E39,          0x14E88, 0x14F05, 0x14FB5,
	0x15003,          0x1512A, 0x15149, 0x151BC, 0x151D7,          0x1520D, 0x15231, 0x15287,
	0x152C4,          0x153F4, 0x1548E, 0x1560A, 0x15611,          0x15640, 0x15696, 0x156F8,
	0x15745,          0x1581A, 0x158E1, 0x15908, 0x15B60,          0x15B7D, 0x15CE7, 0x15D91,
	0x15F19,          0x16032, 0x1603B, 0x160EE, 0x16106,          0x1618C, 0x161AB, 0x161D2,
	0x16282,          0x162E4, 0x1636B, 0x164CB, 0x1658E,          0x16596, 0x16598, 0x1659E,
	0x16697..0x16698, 0x1673B, 0x16786, 0x1688E, 0x16895,          0x16947, 0x16956, 0x169E1,
	0x16AFC,          0x16C67, 0x16C72, 0x16CE4, 0x16D1A,          0x16D70, 0x16E54, 0x17153,
	0x171B3,          0x17220, 0x17240, 0x17305, 0x173B0,          0x17517, 0x176D3, 0x1772C,
	0x1776E,          0x177D4, 0x17838, 0x17874, 0x178B3,          0x17951, 0x17A05, 0x17C58,
	0x17D27,          0x17DA5, 0x17FE9, 0x1800E, 0x18046,          0x1811E, 0x181A3, 0x182E6,
	0x182E9,          0x183C4, 0x183D2, 0x1843C, 0x18492,          0x1856A, 0x1857D, 0x18620,
	0x18725,          0x18925, 0x18ACE, 0x18D2E, 0x18F17,          0x18FBA, 0x1981D, 0x1A014,
	0x1A09D,          0x1A2B9, 0x1A3F4, 0x1AC9C
	],      [50730, 50794, 50982, 51690, 51778, 51825, 51859, 51932, 52227, 52241, 52312, 52417, 52535, 52704, 52775, 52984, 52988, 52997, 53071, 53207, 53340, 53345, 53392, 53836, 53855, 54035, 54060, 54113, 54244, 54319, 54566, 54717, 55074, 55092, 55430, 55479, 55590, 55639, 55745, 55775, 55914, 55996, 56052, 56130, 56388, 56493, 56557, 56575, 56611, 56663, 56697, 56700, 56835, 56873, 57177, 57228, 57352, 57479, 57505, 57545, 57594, 57672, 57690, 57727, 57845, 57883, 57994, 58368, 58393, 58405, 58542, 58601, 58655, 58728, 59412, 59720, 59908, 60012, 60073, 60354, 60438, 60613, 60685, 60741, 60931, 61037, 61118, 61376, 61416, 61731, 61732, 61746, 61784, 61937, 61939, 62099, 62370, 62392, 62517, 62661, 62687, 62743, 62744, 62799, 62813, 62852, 63017, 63135, 63197, 63257, 63343, 63375, 63459, 63784, 64036, 64161, 64178, 64343, 64344, 64475, 64957, 65153, 65253, 65322, 65352, 65380, 65697, 65834, 65839, 65869, 65972, 66304, 66535, 66755, 67012, 67048, 67196, 67222, 67324, 67415, 67455, 67536, 67625, 67752, 67927, 67937, 68057, 68296, 68472, 68539, 68988, 69026, 69116, 69157, 69175, 69831, 69914, 70268, 70436, 70637, 70835, 70933, 71111, 71164, 71208, 71493, 71822, 71962, 72543, 72592, 72598, 72714, 72781, 73335, 73525, 73778, 73948, 74135, 74241, 74445, 74547, 74567, 74595, 74601, 74824, 74995, 74998, 75382, 75505, 75524, 75663, 75853, 75895, 76436, 76632, 76836, 77027, 77185, 77283, 77675, 77697, 77826, 77908, 77970, 78033, 78268, 78432, 78588, 78629, 78672, 78703, 78875, 79304, 79432, 79441, 79509, 79604, 79630, 79679, 79957, 80048, 80105, 80202, 80238, 80523, 80605, 80779, 80841, 81075, 81103, 81159, 81315, 81317, 81611, 81717, 81724, 81812, 81830, 81985, 82016, 82063, 82461, 82498, 82512, 82546, 82583, 82642, 82761, 83537, 83726, 84038, 84140, 84615, 84680],
	);
	@precursors=(
	[	196..197,  199..200,  204,       207,       209,       211..212,  214,  216..218,		undef,		#0	2026-09-06: failing after imlementing iCI, oc, ocª reset on ixM==0xFF in ReINTERLOC
		220..227,  230..246,												undef,
		248..253,															undef,
		255..271,															undef,
		273..288,  290..301,												undef,
		303..317,															undef,
		320..321,  323,       325..332,  334..336,  338..341,						undef,
		343..346,  348..349,												undef,
		352..363,  365..367,  369..370,  372..386,  388,       390..391				],      [202, 205, 254, 272, 297, 338, 358, 376],
	[	196,       198..200,  203..205,  208..210,  213..216,  218..220,  224..226,  228..232, undef,		#1
		235..238,															undef,
		240..253,															undef,
		255,       257..261,  264..265,  267..269,  271,       273..275,  277..280,			undef,
		282..285,  288,       292..294,  296..298,  300..301,						undef,
		303..309,  311..319,												undef,
		321..326,  328..330,  332,											undef,
		334..336,  340..342,  344..350,  352..357,								undef,
		359..363,  365..366,  369..371,  373,       375,							undef,
		377..380,  382..384,  386..387,  389..391								],      [206, 222, 239, 254, 271, 321, 378, 383],
	[	196..197,  199,       201,       204..205,  207,       212..215,					undef,		#2
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
	[	196,       198,       200..201,  206..207,  210,								undef,		#3
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
	[	197..198,  200..201,  203..204,  210..217,  220..221,  223..224,				undef,		#4
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
	[	196,       199,       202,       207,       210..212,								undef,		#5	Test 5 has two null pads. wtf
		222,       224..227,  231..232,  236..238,										undef,
		240..241,  244..245,  251,       253..254,  261,       263..264,						undef,
		271,       274..275,  278,       282..283,  289,									undef,
		291..294,  298,       303..304,  307,											undef,
		309,       312,       315..316,  320,       323..325,  327..328,						undef,
		334,																	undef,
		371..374,																undef,
		375,																	undef,	
		382..385,  388..389,													undef,
		390																	],	[#	211, 304, 309, 312, #all collissions, then the cube run ends anyway
																					356, 366, 376, 382],
	[	196..198,  201..204,  207..208,  212,       215,       218..219,  222..224,			undef,		#6
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
	[	199..200,  202..203,  205,       207..208,									undef,		#7
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
	[	199..200,  208..209,  212..213,  220,       223,       226..227,  229..232,			undef,		#8
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
	[	196..198,  204,       206,       209,       211..212,							undef,		#9
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
	[	196,       198..201,  203..206,  209,       211..212,  214..215,					undef,		#10
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
	[	196,       198,       201,       205..206,  209..212,  215..216,  219..220,			undef,		#11
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
	[	198..199,  203,       205..206,  208..213,  215,       217..218,  220..227,			undef,		#12
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
	[	196..206,															undef,		#13
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
	[	198,       201..202,  206,       211,       213,       215..217,					undef,		#14
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
	[	196..199,  202,       204..209,											undef,		#15
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
	[	196..200,  204,       206,       208,       211,								undef,		#16
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
	[	196,       200,       202..203,  207..212,  215,								undef,		#17	2026-09-06: failing after imlementing iCI, oc, ocª reset on ixM==0xFF in ReINTERLOC
		221..224,  226..227,  230,       232,										undef,		#	hits 1X2L
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
	[	196..200,  202..206,  208..209,  211..213,								undef,		#18
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
	[	197..199,  203..204,  206,       209,       212..213,							undef,		#19	2026-09-06: failing after imlementing iCI, oc, ocª reset on ixM==0xFF in ReINTERLOC
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
	[	196..201,  203..205,												undef,		#20
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
	[	199,       201..203,  205,       207,       209..211,							undef,		#21
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
	[	196,       204,       208,       213..215,  218..219,  221,       225,  229..230,		undef,		#22
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
	[	196..197,  199..201,  203,       205,       211..212,  214,						undef,		#23
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
	[	7,    34,   40,   55,   67,												undef,		#24
		69,   95,   118,  136,  188,					undef,
		285,  288,  296,  309,  341,  346,  363,  369,		undef,
		385,  393,  403,  420,  424,					undef,
		450,										undef,
		470													],	[7, 34, 55, 116, 218, 244, 288, 341],
	[	1..15,     17..21,													undef,		#25
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
	[	0..5,																undef,		#26
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
	[	0..2,      4..6,      8,         10,        12..13,									undef,		#27
#		16,        18..20,    22,        24..26,										undef,
#		28..34,    37,	undef,
#		39..43,    45..48,    50..52,	undef,
#		54..62,    65..69,	undef,
#		71..79,    82..86,    89,        93,        95..96,    99..102,   104,	undef,
#		106,       108,       110..113,  115,       117..123,	undef,
#		126..128,  131..132,  134,       136,       139..149,	undef,
#		152,       154,       157..159,  162..169,	undef,
#		171..195,	undef,
#		197..204,  206,       208..211,  214..215,	undef,
#		218..221,  224,       226..231,	undef,
#		233,       235..241,  244..245,  247..250,  252..253,	undef,
#		256..257,  259..263,  265,       267,       269..271,  273..278,  281..282,  288,	undef,
#		290..291,  293..299,  301..308,  310..313,	undef,
		315,       317..322,  324..329,  331..332,  334,       337..338,  340..341,	undef,
		343..346,  348,       351,       354..358,	undef,
		360..364,  366..368,  370..374,  376..377,	undef,
#		379..386,  388,	undef,
#		390..395,  397..401,  404,	undef,
#		407,       409..412,  414..417,  419..420,  422..423,  425..426,  428,       430..431,	undef,
#		433..435,  438..439,  441..444,  447..448,	undef,
#		452,       454,       456,       461,       463,	undef,
#		465,       467..468,  470..475,  477..482,	undef,
#		485..487,  489..493,  495..498,  500..501,	undef,
#		503..504,	undef,
#		506..511
			],	[#	32, 62, 196, 285,
					353, 366,
			#	464, 470
			],
	[	1..3,      12..13,    21,        25,        28..29,    32..34,    42..43,					undef,		#28
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
	[	1..3,      5,         7,         12..14,    17,   21..23,								undef,		#29
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
	[	0..16,															undef,		#30
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
	[	0..23,															undef,		#31
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
	[	1,2,11..12,17..19,21,29,31,39,										undef,		#32	EPIGEN: 1 key
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
	[	1..2,4..5,12,21,29,													undef,		#33
		31,37,51,65,				undef,
		85,100,112,159,179,183,			undef,
		193,211,217,221,			undef,
		230,233,240,258,288,291,306,325											],	[97, 159, 175, 206, 255, 292, 331, 332],
	[	0..2,4,															undef,		#34
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
	[	1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 18, 21, 							undef,		#35
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
	[	1, 2, 12, 13, 21, 43, 57, 												undef, 		#36
		112, 119, 143, 154, 				undef,
		162, 166, 179, 183, 195,				undef,
		197, 208, 211, 221, 222,				undef,
		234, 247, 249, 276, 289, 294, 311, 313,	undef,
		326,								undef,
		328,																	],	[14, 78, 88, 113, 121, 188, 255, 327],
	[	#37
	0xFFFFFFFFFFC6,  0xFFFFFFFFFFC9,  0xFFFFFFFFFFE2,  0xFFFFFFFFFFE6,  0xFFFFFFFFFFEE,  0xFFFFFFFFFFF5, 0x1000000000001, 0x1000000000010,	undef,
	0x1000000000017, 0x1000000000048, 0x1000000000053, 0x100000000005B, 0x1000000000064
	],      [0xFFFFFFFFFF83,0xFFFFFFFFFF87,0xFFFFFFFFFF8C,0xFFFFFFFFFF8F,0xFFFFFFFFFFA1,0xFFFFFFFFFFA7,0xFFFFFFFFFFA8,0xFFFFFFFFFFB3,0xFFFFFFFFFFB6,0xFFFFFFFFFFC2,0x1000000000038,0x1000000000046,0x1000000000057],
	[	#38
	0xFFFFFFFFFFFFDB..0xFFFFFFFFFFFFDE,   0xFFFFFFFFFFFFE7..0xFFFFFFFFFFFFE8, 0x100000000000006, 0x10000000000000D, 0x100000000000018, 0x100000000000033, 0x100000000000035..0x100000000000036, 0x10000000000003C
	],      [0xFFFFFFFFFFFFCA,0xFFFFFFFFFFFFD0,0xFFFFFFFFFFFFD2,0xFFFFFFFFFFFFD3,0xFFFFFFFFFFFFE0,0xFFFFFFFFFFFFF9,0xFFFFFFFFFFFFFD,0x100000000000004,0x10000000000000D,0x10000000000000E,0x100000000000014,0x100000000000030,0x10000000000003A],
	[	#39
	0xFFFFFFFFFFFFE2,  0xFFFFFFFFFFFFE6,  0x100000000000007, 0x10000000000000B, 0x10000000000000E, 0x100000000000012, 0x100000000000018, 0x10000000000001E,
	0x100000000000020, 0x100000000000024, 0x100000000000030, 0x100000000000032, 0x10000000000003A
	],      [0xFFFFFFFFFFFFC4,0xFFFFFFFFFFFFC8,0xFFFFFFFFFFFFCE,0xFFFFFFFFFFFFD0,0xFFFFFFFFFFFFE6,0xFFFFFFFFFFFFEB,0xFFFFFFFFFFFFED,0xFFFFFFFFFFFFF0,0xFFFFFFFFFFFFF5,0x100000000000005,0x100000000000027,0x100000000000032,0x100000000000033],
	[	#40
	0xFFFFE3,  0xFFFFFE,             0x1000003, 0x1000005, 0x100000A, 0x100000D, 0x100000F, 0x1000016..0x1000017,
	0x100001F, 0x1000033..0x1000034, 0x100003E
	],      [0xFFFFC3,0xFFFFCA,0xFFFFCE,0xFFFFDD,0xFFFFE0,0xFFFFE5,0xFFFFE6,0xFFFFEE,0xFFFFF4,0xFFFFF5,0xFFFFF8,0x1000037,0x1000038],
	[	#41	EPIGEN: 1 key
	0x81,  0x8C,  0x99,  0x9D,  0xA8,  0xB4, 0xBF, 0x140,	undef,
	0x14B, 0x152, 0x154, 0x16A, 0x16F
	],      [0xCC,0xE1,0xE4,0x107,0x109,0x10B,0x10D,0x11F,0x138,0x139,0x142,0x157,0x177],
	[	#42	EPIGEN: 1 key
	0xFFFFA8,  0xFFFFD2,  0xFFFFD4,  0xFFFFE2,  0xFFFFE8,  0xFFFFEB,  0xFFFFF7..0xFFFFF8,  0xFFFFFE, undef,
	0x1000013, 0x1000023, 0x1000037, 0x100004D, 0x1000050, 0x100005D, 0x1000062
	],      [0xFFFF83,0xFFFF8B,0xFFFFA7,0xFFFFAC,0xFFFFB9,0xFFFFC8,0xFFFFD3,0x1000019,0x1000048,0x1000049,0x100004A,0x100004B,0x1000053,0x1000057,0x100005A,0x100007C],
	[	#43
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
	[	#44	EPIGEN: 2 keys
	0xFFFFFFFFFFFFB8,  0xFFFFFFFFFFFFD7,  0xFFFFFFFFFFFFDB,  0xFFFFFFFFFFFFE2,  0xFFFFFFFFFFFFE6,  0xFFFFFFFFFFFFE8,  0xFFFFFFFFFFFFF1,  0xFFFFFFFFFFFFF6,
	0xFFFFFFFFFFFFF8,  0x100000000000012, 0x100000000000019, 0x100000000000038, 0x10000000000003B, 0x100000000000043, 0x100000000000056, 0x100000000000061
	],      [0xFFFFFFFFFFFF92,0xFFFFFFFFFFFF9B,0xFFFFFFFFFFFFAE,0xFFFFFFFFFFFFBD,0xFFFFFFFFFFFFC2,0xFFFFFFFFFFFFD3,0xFFFFFFFFFFFFF7,0xFFFFFFFFFFFFFE,0x100000000000007,0x10000000000001A,0x10000000000001F,0x10000000000002D,0x10000000000003B,0x10000000000005F,0x10000000000006D,0x100000000000077],
	[	#45		this is the one that finally elucidated the need for the descending-to-ascending pmo remainder.
	0xFFFFFFFFFFFFC2..0xFFFFFFFFFFFFC3,	undef,
	0xFFFFFFFFFFFFC5..0xFFFFFFFFFFFFCD,	0xFFFFFFFFFFFFCF..0xFFFFFFFFFFFFD0,	0xFFFFFFFFFFFFD3,				0xFFFFFFFFFFFFD5,				0xFFFFFFFFFFFFD9,				0xFFFFFFFFFFFFDC,		undef,
	0xFFFFFFFFFFFFDE, 			0xFFFFFFFFFFFFE7..0xFFFFFFFFFFFFE9,	0xFFFFFFFFFFFFEB,				0xFFFFFFFFFFFFED,				0xFFFFFFFFFFFFF4,				0xFFFFFFFFFFFFFB,		0x100000000000000,    0x100000000000002..0x100000000000005,	undef,
	0x100000000000007,			0x10000000000000B,			0x100000000000012,			0x100000000000015,			undef,
	0x100000000000018,			0x10000000000001C,			0x10000000000001E,			0x100000000000023,			0x100000000000028..0x100000000000029,	undef,
	0x10000000000002C,			0x100000000000030,			0x100000000000033..0x100000000000038,	0x10000000000003B..0x10000000000003C
	],      [0xFFFFFFFFFFFFC4,0xFFFFFFFFFFFFD2,0xFFFFFFFFFFFFD4,0xFFFFFFFFFFFFDC,0xFFFFFFFFFFFFDD,0xFFFFFFFFFFFFE4,0xFFFFFFFFFFFFEF,0xFFFFFFFFFFFFF6,0xFFFFFFFFFFFFF9,0xFFFFFFFFFFFFFD,0x100000000000001,0x100000000000005,0x100000000000007,0x10000000000000D,0x100000000000025,0x100000000000030],
	[	#46		this is the same as the previous but with all the inert arguments removed.
	0xFFFFFFFFFFFFC2..0xFFFFFFFFFFFFC3,	undef,
	0xFFFFFFFFFFFFC5..0xFFFFFFFFFFFFCD,	0xFFFFFFFFFFFFCF..0xFFFFFFFFFFFFD0,	0xFFFFFFFFFFFFD3,				0xFFFFFFFFFFFFD5,				0xFFFFFFFFFFFFD9,				0xFFFFFFFFFFFFDC,		undef,
	0xFFFFFFFFFFFFDE, 			0xFFFFFFFFFFFFE7..0xFFFFFFFFFFFFE9,	0xFFFFFFFFFFFFEB,				0xFFFFFFFFFFFFED,				0xFFFFFFFFFFFFF4,				0xFFFFFFFFFFFFFB,		0x100000000000000,    0x100000000000002..0x100000000000005,	undef,
	0x100000000000007,			0x10000000000000B,			0x100000000000012,			0x100000000000015,			undef,
	0x100000000000018,			0x10000000000001C,			0x10000000000001E,			0x100000000000023,			0x100000000000028..0x100000000000029,	undef,
	0x10000000000002C,			0x100000000000030,			0x100000000000033..0x100000000000038,	0x10000000000003B..0x10000000000003C

	],      [0xFFFFFFFFFFFFC4,0xFFFFFFFFFFFFE4,0xFFFFFFFFFFFFEF,0xFFFFFFFFFFFFF6,0xFFFFFFFFFFFFFD],
	[	#47
	0xC0..0xC1,   0xC3..0xC4,	undef,
	0xC6..0xCD,   0xD0,         0xD3..0xD4,   0xD7..0xD8,  0xDA..0xDB,  0xE1..0xE2,   0xEA,         0xED..0xEE,	undef,
	0xF1,         0xF5,         0xF7,         0xF9,        0xFD,        0x100..0x101,	undef,
	0x104,        0x10F..0x111, 0x113..0x114, 0x118,       0x11B,       0x11F,        0x123..0x125,	undef,
	0x127,        0x129,        0x12E..0x12F, 0x131,       0x136,       0x138,        0x13A,	undef,
	0x13C,	undef,
	0x13F..0x14C, 0x14E..0x15B
	],      [0xC2,0xC5,0xCB,0xDF,0xF1,0x103,0x10B,0x113,0x116,0x12A,0x12D,0x132,0x133,0x135,0x137,0x13C],
	[	#48		proof that it is not possible to fragment a cube three ways while concentrating all endogenic cycla into the medial fragment
		#it shouldn't need proof, though.
		#Adding two more cubes implies that the number of additional cycla well exceeds what can fit in one cube.
		10,			20,			30,			40,			50,			60,			70,			80,
		100, 		200,			300,			400,			500,			600,			700,			800,
		1000,		2000,		3000,		4000,		5000,		6000,		7000,		8000
	],	[ 402, 404, 406, 408, 410, 412, 414	],
	[	#49
	0xFFFFFFFFFFFFC0..0xFFFFFFFFFFFFE9, undef,
	0xFFFFFFFFFFFFEB..0x10000000000003F
	],      [0xFFFFFFFFFFFFC5,0xFFFFFFFFFFFFD4,0xFFFFFFFFFFFFD5,0xFFFFFFFFFFFFDE,0xFFFFFFFFFFFFE3,0xFFFFFFFFFFFFF4,0xFFFFFFFFFFFFF7,0xFFFFFFFFFFFFF8,0xFFFFFFFFFFFFFA,0x10000000000000D,0x10000000000001A,0x100000000000020,0x100000000000024,0x100000000000025,0x10000000000003C,0x10000000000003E],
	[	#50
	0xFFFFC0..0xFFFFC2,	undef,
	0xFFFFC4..0x100003F,	undef,
	0x1000041..0x10000BC
	],      [0xFFFFC0,0xFFFFC5,0xFFFFCD,0xFFFFE0,0xFFFFE2,0xFFFFE8,0xFFFFEE,0xFFFFF4,0xFFFFF9,0xFFFFFB,0xFFFFFD,0x1000006,0x100000E,0x100000F,0x1000011,0x100001B,0x1000026,0x100002A,0x100002E,0x1000031,0x1000034],
	[	#51
	0xFFFFFFFFFFC0..0x100000000002D,	undef,
	0x100000000002F..0x100000000003F
	],      [0xFFFFFFFFFFC1,0xFFFFFFFFFFC3,0xFFFFFFFFFFCB,0xFFFFFFFFFFD0,0xFFFFFFFFFFD8,0xFFFFFFFFFFDF,0xFFFFFFFFFFE1,0xFFFFFFFFFFE3,0xFFFFFFFFFFE5,0xFFFFFFFFFFE8,0xFFFFFFFFFFEB,0xFFFFFFFFFFED,0xFFFFFFFFFFEE,0xFFFFFFFFFFF0,0xFFFFFFFFFFF5,0xFFFFFFFFFFF8,0xFFFFFFFFFFFB,0x100000000000B,0x1000000000012,0x1000000000019,0x100000000002D],
	[	#52
	0xFFFFC0..0x1000020,		undef,
	0x1000022..0x100003F,		undef,
	0x1000041..0x100005E
	],      [0xFFFFC7,0xFFFFC9,0xFFFFCB,0xFFFFCD,0xFFFFD2,0xFFFFDA,0xFFFFDE,0xFFFFE0,0xFFFFE3,0xFFFFEB,0xFFFFED,0xFFFFF0,0xFFFFF7,0xFFFFFA,0x100000C,0x100000D,0x100000F,0x100001D,0x100001F,0x1000021,0x1000023],
	[	#53	EPIGEN: 3 keys
	72057594037925895, 72057594037926007, 72057594037926053,                    72057594037926056, 72057594037926084, 72057594037926130, 72057594037926173, 72057594037926349,
	72057594037926377, 72057594037926478, 72057594037926503,                    72057594037926564, 72057594037926567, 72057594037926580, 72057594037926697, 72057594037926731,
	72057594037926772, 72057594037926789, 72057594037926843,                    72057594037926851, 72057594037926860, 72057594037927121, 72057594037927191, 72057594037927224,
	72057594037927333, 72057594037927383, 72057594037927412,                    72057594037927427, 72057594037927496, 72057594037927583, 72057594037927591, 72057594037927600,
	72057594037927715, 72057594037927784, 72057594037927791,                    72057594037927935, 72057594037927948, 72057594037928022, 72057594037928055, 72057594037928094,
	72057594037928103, 72057594037928180, 72057594037928186,                    72057594037928529, 72057594037928559, 72057594037928572, 72057594037928647, 72057594037928958,
	72057594037928967, 72057594037929013, 72057594037929071,                    72057594037929240, 72057594037929343, 72057594037929354, 72057594037929368, 72057594037929397..72057594037929398,
	72057594037929443, 72057594037929472, 72057594037929587..72057594037929588, 72057594037929601, 72057594037929616, 72057594037929732
	],      [72057594037925933, 72057594037926051, 72057594037926454, 72057594037926495, 72057594037926568, 72057594037926596, 72057594037926755, 72057594037926772, 72057594037926773, 72057594037926783, 72057594037926815, 72057594037926913, 72057594037926941, 72057594037927058, 72057594037927118, 72057594037927129, 72057594037927135, 72057594037927277, 72057594037927328, 72057594037927382, 72057594037927405, 72057594037927406, 72057594037927498, 72057594037927600, 72057594037927628, 72057594037927630, 72057594037927751, 72057594037927805, 72057594037928000, 72057594037928072, 72057594037928134, 72057594037928152, 72057594037928157, 72057594037928207, 72057594037928280, 72057594037928342, 72057594037928350, 72057594037928390, 72057594037928394, 72057594037928402, 72057594037928455, 72057594037928656, 72057594037928720, 72057594037928804, 72057594037928814, 72057594037928822, 72057594037928826, 72057594037928844, 72057594037928856, 72057594037928871, 72057594037928910, 72057594037928917, 72057594037928967, 72057594037929190, 72057594037929304, 72057594037929305, 72057594037929375, 72057594037929522, 72057594037929603, 72057594037929632, 72057594037929873, 72057594037929874, 72057594037929910, 72057594037929923],
	[	#54	EPIGEN: 1 key
	281474976708634,                  281474976708640, 281474976708660, 281474976708829, 281474976708901, 281474976708910, 281474976708954, 281474976708965..281474976708966,
	281474976708971,                  281474976708998, 281474976709131, 281474976709165, 281474976709204, 281474976709248, 281474976709289, 281474976709409,
	281474976709515,                  281474976709595, 281474976709619, 281474976709659, 281474976709763, 281474976709777, 281474976709849, 281474976709930,
	281474976710026,                  281474976710138, 281474976710245, 281474976710564, 281474976710626, 281474976710637, 281474976710679, 281474976710695,
	281474976710865..281474976710866, 281474976711080, 281474976711202, 281474976711222, 281474976711248, 281474976711308, 281474976711322, 281474976711472,
	281474976711523,                  281474976711573, 281474976711619, 281474976711629, 281474976711643, 281474976711667, 281474976711670, 281474976711689,
	281474976711701,                  281474976711735, 281474976711781, 281474976711807, 281474976711900, 281474976712054, 281474976712057, 281474976712109,
	281474976712117,                  281474976712177, 281474976712217, 281474976712287, 281474976712491, 281474976712702
	],      [281474976708668, 281474976708755, 281474976708781, 281474976708809, 281474976708890, 281474976708916, 281474976709050, 281474976709066, 281474976709332, 281474976709352, 281474976709426, 281474976709599, 281474976709661, 281474976709910, 281474976709944, 281474976710000, 281474976710022, 281474976710045, 281474976710056, 281474976710127, 281474976710216, 281474976710231, 281474976710276, 281474976710283, 281474976710298, 281474976710325, 281474976710345, 281474976710379, 281474976710413, 281474976710433, 281474976710450, 281474976710476, 281474976710514, 281474976710520, 281474976710548, 281474976710567, 281474976710606, 281474976710640, 281474976710645, 281474976710672, 281474976710764, 281474976710876, 281474976710912, 281474976710935, 281474976711016, 281474976711215, 281474976711225, 281474976711246, 281474976711370, 281474976711390, 281474976711391, 281474976711454, 281474976711498, 281474976711642, 281474976711799, 281474976711874, 281474976711923, 281474976712134, 281474976712321, 281474976712362, 281474976712442, 281474976712454, 281474976712479, 281474976712663],
	[	#55
	1099511625754, 1099511625804, 1099511625866, 1099511625938, 1099511625953, 1099511625964, 1099511626039, 1099511626046,
	1099511626144, 1099511626320, 1099511626358, 1099511626480, 1099511626523, 1099511626535, 1099511626568, 1099511626573,
	1099511626615, 1099511626757, 1099511626804, 1099511626828, 1099511626843, 1099511626922, 1099511626926, 1099511626946,
	1099511626957, 1099511626993, 1099511627003, 1099511627041, 1099511627163, 1099511627186, 1099511627209, 1099511627259,
	1099511627724, 1099511627983, 1099511628090, 1099511628240, 1099511628525, 1099511628558, 1099511628690, 1099511628740,
	1099511628783, 1099511628803, 1099511628825, 1099511628854, 1099511628911, 1099511628926, 1099511629009, 1099511629037,
	1099511629074, 1099511629082, 1099511629144, 1099511629162, 1099511629247, 1099511629388, 1099511629401, 1099511629425,
	1099511629440, 1099511629445, 1099511629529, 1099511629547, 1099511629558, 1099511629650, 1099511629706, 1099511629763
	],      [1099511625822, 1099511625858, 1099511625894, 1099511626017, 1099511626089, 1099511626156, 1099511626213, 1099511626293, 1099511626375, 1099511626391, 1099511626483, 1099511626513, 1099511626536, 1099511626746, 1099511626849, 1099511626892, 1099511626932, 1099511626948, 1099511627012, 1099511627217, 1099511627233, 1099511627257, 1099511627451, 1099511627496, 1099511627508, 1099511627540, 1099511627546, 1099511627576, 1099511627585, 1099511627666, 1099511627742, 1099511627766, 1099511627773, 1099511627806, 1099511627953, 1099511628018, 1099511628038, 1099511628054, 1099511628104, 1099511628133, 1099511628242, 1099511628244, 1099511628431, 1099511628485, 1099511628501, 1099511628545, 1099511628608, 1099511628625, 1099511628670, 1099511628728, 1099511628874, 1099511629017, 1099511629164, 1099511629183, 1099511629226, 1099511629231, 1099511629374, 1099511629392, 1099511629395, 1099511629412, 1099511629437, 1099511629627, 1099511629632, 1099511629801],
#	);@precursors=(#
	#	verify rare subcases of main case 1X4 within _sv_commit()
	#	each precursor here is commented with a hex code.  The first 3 digits are the subcase, and the last 10 are the trace.
	#	SUBCASE
	#	bit 1:	cube Y has highpass
	#	bit 2:	cube Z has mods
	#	bit 3:	cube 1 has lowpass
	#	bit 4:	cube 0 has mods
	#
	#	LAYOUT[0]							LAYOUT[3]
	#	bit 1:	cube 0 has post_q bytes			bit 1:	cube Y keybyte highpass shifted
	#										bit 2:	cube Y has post_q bytes
	#	LAYOUT[1]							bit 3:	cube Y has hp_q bytes
	#	bit 1:	cube 1 has lp_q bytes			bit 4:	cube Y has post_q bytes (2)
	#	bit 2:	cube 1 has post_q bytes			
	#	bit 3:	cube 1 has post_q bytes (2)		LAYOUT[4]
	#										bit 1:	cube Z has highpass keybytes
	#	LAYOUT[2]							bit 2:	cube Z has post_q bytes
	#	bit 1:	there is at least one cube X		bit 3:	cube Z has hp_q bytes
	#	bit 2:	cube X has post_q bytes			bit 4:	cube Z has hp_q bytes (2)
	#
	#1X4-0A0202000201:
	[	#56
	0xFFFFFFFFFFFEA3,  0xFFFFFFFFFFFEB1,  0xFFFFFFFFFFFF66,  0xFFFFFFFFFFFF89,                     0x100000000000006, 0x100000000000020, 0x100000000000024, 0x100000000000037,
	0x100000000000039, 0x10000000000006C, 0x10000000000006F, 0x100000000000074,                    0x1000000000000A0, 0x1000000000000B1, 0x1000000000000CD, 0x1000000000000EF,
	0x100000000000100, 0x10000000000011A, 0x10000000000011D, 0x100000000000151..0x100000000000152, 0x10000000000015C, 0x100000000000160, 0x10000000000017F, 0x1000000000001B3,
	0x1000000000001DF, 0x1000000000001EF, 0x1000000000001F8, 0x100000000000223,                    0x100000000000242, 0x100000000000281, 0x10000000000028F, 0x1000000000002A8,
	0x1000000000002EF, 0x1000000000002F1, 0x10000000000033A, 0x10000000000034C,                    0x10000000000037B, 0x10000000000038F, 0x1000000000003B8, 0x1000000000003EB,
	0x1000000000003EE, 0x1000000000003F5, 0x100000000000400, 0x100000000000412,                    0x10000000000041C
	], [ 0xFFFFFFFFFFFEED, 0xFFFFFFFFFFFEF9, 0xFFFFFFFFFFFF08, 0xFFFFFFFFFFFF22, 0xFFFFFFFFFFFF43, 0xFFFFFFFFFFFF44, 0xFFFFFFFFFFFF4D, 0xFFFFFFFFFFFF4F, 0xFFFFFFFFFFFF68, 0xFFFFFFFFFFFF9B, 0xFFFFFFFFFFFF9F, 0xFFFFFFFFFFFFAF, 0xFFFFFFFFFFFFD6, 0xFFFFFFFFFFFFD9, 0xFFFFFFFFFFFFE9, 0x10000000000000D, 0x100000000000033, 0x10000000000003A, 0x100000000000045, 0x10000000000004A, 0x100000000000054, 0x10000000000006F, 0x100000000000072, 0x1000000000000AE, 0x1000000000000BE, 0x1000000000000DB, 0x1000000000000F2, 0x100000000000138, 0x1000000000001AA, 0x1000000000001E6, 0x100000000000204, 0x100000000000221, 0x10000000000023D, 0x10000000000024B, 0x10000000000024E, 0x100000000000258, 0x100000000000259, 0x100000000000271, 0x100000000000297, 0x1000000000002AD, 0x1000000000002FB, 0x100000000000319, 0x10000000000032D, 0x10000000000033A, 0x100000000000342, 0x10000000000035B, ],
	#1X4-0A0702000201:
	[	#57
	0xFFFFFFFFFFFE3B,  0xFFFFFFFFFFFED3,  0xFFFFFFFFFFFEF3,  0xFFFFFFFFFFFF00,                     0xFFFFFFFFFFFF03,                     0xFFFFFFFFFFFF14..0xFFFFFFFFFFFF15,  0xFFFFFFFFFFFF1E,                     0xFFFFFFFFFFFF26,
	0xFFFFFFFFFFFF2E,  0xFFFFFFFFFFFF31,  0xFFFFFFFFFFFF45,  0xFFFFFFFFFFFF47,                     0xFFFFFFFFFFFF58,                     0xFFFFFFFFFFFF6F,                    0xFFFFFFFFFFFF73,                     0xFFFFFFFFFFFF75,
	0xFFFFFFFFFFFF94,  0xFFFFFFFFFFFFE0,  0xFFFFFFFFFFFFEF,  0x10000000000000C..0x10000000000000D, 0x100000000000017..0x100000000000018, 0x10000000000005E,                   0x100000000000087,                    0x1000000000000F1,
	0x100000000000104, 0x100000000000114, 0x10000000000012B, 0x100000000000132,                    0x100000000000179,                    0x1000000000001C5,                   0x1000000000001C8..0x1000000000001C9, 0x1000000000001CC,
	0x1000000000001E3, 0x1000000000001E6, 0x1000000000001EC, 0x100000000000232,                    0x100000000000267,                    0x100000000000273,                   0x100000000000275,                    0x1000000000002AE,
	0x1000000000002B4, 0x100000000000326
	], [ 0xFFFFFFFFFFFED4, 0xFFFFFFFFFFFF0D, 0xFFFFFFFFFFFF1D, 0xFFFFFFFFFFFF3C, 0xFFFFFFFFFFFF59, 0xFFFFFFFFFFFF5C, 0xFFFFFFFFFFFF60, 0xFFFFFFFFFFFF64, 0xFFFFFFFFFFFF7E, 0xFFFFFFFFFFFFCA, 0xFFFFFFFFFFFFCD, 0xFFFFFFFFFFFFE7, 0xFFFFFFFFFFFFE9, 0x10000000000003C, 0x100000000000050, 0x100000000000054, 0x100000000000067, 0x100000000000070, 0x100000000000085, 0x100000000000099, 0x10000000000009C, 0x10000000000009D, 0x1000000000000AE, 0x1000000000000D4, 0x1000000000000EB, 0x100000000000101, 0x10000000000010C, 0x10000000000010F, 0x100000000000114, 0x100000000000126, 0x100000000000139, 0x10000000000017D, 0x10000000000018B, 0x1000000000001A3, 0x1000000000001AE, 0x1000000000001B8, 0x1000000000001F8, 0x1000000000001FF, 0x100000000000217, 0x10000000000021D, 0x100000000000225, 0x100000000000229, 0x100000000000267, 0x10000000000027E, 0x100000000000288, 0x1000000000002E1, ],
	#1X4-0A0702030201:
	[	#58	EPIGEN: 1 key
	0xFFFFFFFFFFFE5E,                     0xFFFFFFFFFFFEB2,  0xFFFFFFFFFFFEE5,  0xFFFFFFFFFFFEF2,                     0xFFFFFFFFFFFF0B,  0xFFFFFFFFFFFF11,                     0xFFFFFFFFFFFF55,  0xFFFFFFFFFFFF69,
	0xFFFFFFFFFFFF6C,                     0xFFFFFFFFFFFF6F,  0xFFFFFFFFFFFF7C,  0xFFFFFFFFFFFF99,                     0xFFFFFFFFFFFFA4,  0xFFFFFFFFFFFFAC,                     0xFFFFFFFFFFFFB1,  0xFFFFFFFFFFFFB4,
	0xFFFFFFFFFFFFC1,                     0x100000000000003, 0x10000000000004C, 0x100000000000055..0x100000000000056, 0x1000000000000A0, 0x1000000000000D2..0x1000000000000D3, 0x1000000000000FC, 0x100000000000103,
	0x10000000000010C,                    0x100000000000119, 0x10000000000011E, 0x100000000000141,                    0x100000000000160, 0x100000000000164,                    0x100000000000197, 0x1000000000001C4,
	0x1000000000001D0,                    0x1000000000001E5, 0x1000000000001EC, 0x100000000000214,                    0x100000000000242, 0x100000000000244,                    0x10000000000024B, 0x10000000000026A,
	0x100000000000270..0x100000000000271, 0x100000000000278, 0x10000000000028C
	], [ 0xFFFFFFFFFFFE9F, 0xFFFFFFFFFFFEEF, 0xFFFFFFFFFFFEF7, 0xFFFFFFFFFFFF0B, 0xFFFFFFFFFFFF3B, 0xFFFFFFFFFFFF95, 0xFFFFFFFFFFFF9E, 0xFFFFFFFFFFFFB7, 0xFFFFFFFFFFFFDD, 0xFFFFFFFFFFFFE7, 0xFFFFFFFFFFFFF1, 0x100000000000001, 0x100000000000026, 0x10000000000002E, 0x100000000000041, 0x100000000000046, 0x100000000000069, 0x100000000000077, 0x100000000000087, 0x10000000000008C, 0x100000000000091, 0x10000000000009C, 0x1000000000000CD, 0x1000000000000CE, 0x1000000000000D7, 0x1000000000000DF, 0x1000000000000EE, 0x1000000000000F8, 0x100000000000101, 0x100000000000108, 0x100000000000133, 0x100000000000138, 0x100000000000197, 0x1000000000001A2, 0x1000000000001DA, 0x1000000000001DE, 0x1000000000001E0, 0x100000000000202, 0x100000000000219, 0x100000000000221, 0x10000000000022B, 0x10000000000023C, 0x10000000000024E, 0x10000000000024F, 0x100000000000277, 0x10000000000029E, ],
	#1X4-0B0703030201:
	[	#59	EPIGEN: 1 key
	0xFFFFFFFFFE55,  0xFFFFFFFFFE99,  0xFFFFFFFFFEAF,  0xFFFFFFFFFEE5,  0xFFFFFFFFFEF2,                   0xFFFFFFFFFF03,  0xFFFFFFFFFF2F,  0xFFFFFFFFFF4B,
	0xFFFFFFFFFFC4,  0x1000000000022, 0x100000000002A, 0x100000000002F, 0x100000000003C,                  0x1000000000054, 0x1000000000059, 0x100000000006C,
	0x1000000000095, 0x100000000009A, 0x10000000000A4, 0x10000000000B8, 0x10000000000BA,                  0x10000000000DE, 0x1000000000116, 0x1000000000125,
	0x100000000012C, 0x1000000000133, 0x1000000000137, 0x1000000000151, 0x1000000000178..0x1000000000179, 0x1000000000180, 0x1000000000186, 0x100000000019E,
	0x10000000001A8, 0x10000000001C4, 0x10000000001D1, 0x10000000001F5, 0x1000000000204,                  0x1000000000225, 0x1000000000237, 0x100000000023E,
	0x1000000000253, 0x100000000025A, 0x100000000025D, 0x1000000000263, 0x100000000028A
	], [ 0xFFFFFFFFFE80, 0xFFFFFFFFFE9A, 0xFFFFFFFFFEB9, 0xFFFFFFFFFED2, 0xFFFFFFFFFEE2, 0xFFFFFFFFFF02, 0xFFFFFFFFFF19, 0xFFFFFFFFFF2A, 0xFFFFFFFFFF33, 0xFFFFFFFFFF52, 0xFFFFFFFFFF64, 0xFFFFFFFFFF66, 0xFFFFFFFFFF83, 0xFFFFFFFFFF86, 0xFFFFFFFFFF9A, 0xFFFFFFFFFFA2, 0xFFFFFFFFFFB1, 0xFFFFFFFFFFC1, 0xFFFFFFFFFFE0, 0xFFFFFFFFFFE7, 0xFFFFFFFFFFED, 0xFFFFFFFFFFF7, 0xFFFFFFFFFFFA, 0x1000000000013, 0x1000000000014, 0x1000000000075, 0x1000000000088, 0x100000000009F, 0x10000000000C1, 0x10000000000DE, 0x10000000000EF, 0x100000000012E, 0x1000000000130, 0x100000000014A, 0x100000000014E, 0x100000000015F, 0x1000000000167, 0x1000000000169, 0x10000000001C1, 0x10000000001F5, 0x10000000001FF, 0x100000000023E, 0x1000000000242, 0x100000000026A, 0x100000000027C, 0x100000000028E, ],
	#1X4-0B0707030201:
	[	#60
	0xFFFFFFFFF4,                 0x1000000003A, 0x1000000006A, 0x1000000007D,                0x10000000086, 0x1000000008A, 0x1000000008D, 0x10000000098,
	0x1000000009D,                0x100000000BD, 0x10000000128, 0x1000000012D,                0x10000000131, 0x10000000136, 0x1000000013E, 0x1000000015B,
#	0x10000000171..0x10000000173, 0x1000000018B, 0x10000000192, 0x100000001C2..0x100000001C3, 0x100000001DF, 0x10000000202, 0x10000000228, 0x10000000279,
#	0x100000002A8,                0x100000002B2, 0x100000002D7, 0x100000002E1,                0x100000002F0, 0x10000000329, 0x10000000342, 0x10000000344,
#	0x10000000373,                0x100000003B9, 0x100000003C5, 0x100000003E2,                0x10000000408, 0x1000000040B, 0x10000000416, 0x10000000447,
#	0x100000004CE,                0x10000000532, 0x1000000053C
	], [
	0xFFFFFFFE7D, 0xFFFFFFFEC7, 0xFFFFFFFED0, 0xFFFFFFFF32, 0xFFFFFFFF33, 0xFFFFFFFF3A, 0xFFFFFFFF47, 0xFFFFFFFF48, 
	0xFFFFFFFF56, 0xFFFFFFFF69, 0xFFFFFFFF74, 0xFFFFFFFFA2, 0xFFFFFFFFA7, 0xFFFFFFFFC6, 0xFFFFFFFFD1, 0xFFFFFFFFD4, 
#	0xFFFFFFFFDD, 0x1000000009C, 0x100000000AB, 0x100000000B3, 0x100000000B9, 0x100000000BC, 0x100000000CB, 
#	0x100000000D1, 0x100000000D2, 0x100000000F7, 0x10000000103, 0x10000000115, 0x1000000013F, 0x10000000141, 
#	0x10000000163, 0x10000000181, 0x10000000182, 0x10000000197, 0x100000001A9, 0x100000001B4, 0x100000001C3, 
#	0x10000000200, 0x10000000216, 0x10000000227, 0x1000000023F, 0x1000000025C, 0x10000000266, 0x10000000289, 
#	0x100000002E5, 0x100000002EA
	],
	#1X4-0F0707030201:
	[	#61
	0xFFFFFE69,  0xFFFFFE6B,  0xFFFFFE84,               0xFFFFFEA1,  0xFFFFFEA8,               0xFFFFFEC7,  0xFFFFFECC,  0xFFFFFFB2,
	0xFFFFFFF4,  0xFFFFFFFC,  0x10000002C,              0x100000034, 0x10000003C,              0x10000004D, 0x100000069, 0x100000076,
	0x100000079, 0x10000007E, 0x1000000C7,              0x1000000D5, 0x1000000E6..0x1000000E7, 0x1000000F3, 0x100000102, 0x100000106,
	0x10000010A, 0x100000118, 0x100000129,              0x10000012E, 0x100000140,              0x100000175, 0x100000186, 0x10000018B,
	0x1000001A8, 0x1000001B5, 0x1000001D7,              0x1000001D9, 0x1000001F1,              0x1000001FF, 0x100000203, 0x100000206,
	0x100000219, 0x10000021E, 0x10000022A..0x10000022B, 0x1000002CC
	], [ 0xFFFFFED8, 0xFFFFFEED, 0xFFFFFEF7, 0xFFFFFF02, 0xFFFFFF0C, 0xFFFFFF13, 0xFFFFFF17, 0xFFFFFF36, 0xFFFFFF4A, 0xFFFFFF7A, 0xFFFFFF80, 0xFFFFFF87, 0xFFFFFFA5, 0xFFFFFFA8, 0xFFFFFFAD, 0xFFFFFFB0, 0xFFFFFFB5, 0xFFFFFFB8, 0xFFFFFFE9, 0xFFFFFFF1, 0x100000025, 0x10000004E, 0x100000054, 0x100000062, 0x100000082, 0x100000087, 0x10000009C, 0x1000000AB, 0x1000000B2, 0x1000000C6, 0x1000000DA, 0x1000000DE, 0x1000000E7, 0x1000000F5, 0x100000128, 0x10000014F, 0x100000169, 0x1000001A9, 0x1000001B2, 0x1000001C8, 0x1000001E5, 0x10000022D, 0x10000025B, 0x10000026E, 0x10000027B, 0x100000289, ],
	#1X4-0F0707030301:
	[	#62
	0xFFFFFFFFFFFEA7,  0xFFFFFFFFFFFEA9,                    0xFFFFFFFFFFFEB5,  0xFFFFFFFFFFFEEC,  0xFFFFFFFFFFFEF5,  0xFFFFFFFFFFFF04,                     0xFFFFFFFFFFFF09,  0xFFFFFFFFFFFF47,
	0xFFFFFFFFFFFF50,  0xFFFFFFFFFFFF67..0xFFFFFFFFFFFF68,  0xFFFFFFFFFFFF6F,  0xFFFFFFFFFFFF87,  0xFFFFFFFFFFFF92,  0xFFFFFFFFFFFF95,                     0xFFFFFFFFFFFFB3,  0xFFFFFFFFFFFFBB,
	0xFFFFFFFFFFFFC1,  0xFFFFFFFFFFFFC3,                    0xFFFFFFFFFFFFC8,  0xFFFFFFFFFFFFD8,  0xFFFFFFFFFFFFE5,  0x100000000000013,                    0x100000000000019, 0x10000000000001F,
	0x10000000000004A, 0x10000000000005E,                   0x10000000000008B, 0x1000000000000AD, 0x1000000000000D3, 0x1000000000000D5,                    0x1000000000000DD, 0x1000000000000E1,
	0x1000000000000E4, 0x100000000000119,                   0x10000000000011E, 0x100000000000122, 0x10000000000012D, 0x10000000000012F..0x100000000000130, 0x100000000000144, 0x10000000000023F,
	0x100000000000251, 0x100000000000277,                   0x100000000000291, 0x1000000000002AC
	], [ 0xFFFFFFFFFFFE5F, 0xFFFFFFFFFFFEDA, 0xFFFFFFFFFFFEF7, 0xFFFFFFFFFFFF06, 0xFFFFFFFFFFFF0C, 0xFFFFFFFFFFFF12, 0xFFFFFFFFFFFF1C, 0xFFFFFFFFFFFF2A, 0xFFFFFFFFFFFF42, 0xFFFFFFFFFFFF63, 0xFFFFFFFFFFFF73, 0xFFFFFFFFFFFF82, 0xFFFFFFFFFFFF95, 0xFFFFFFFFFFFF98, 0xFFFFFFFFFFFFB4, 0xFFFFFFFFFFFFCD, 0xFFFFFFFFFFFFDB, 0xFFFFFFFFFFFFE1, 0xFFFFFFFFFFFFEF, 0xFFFFFFFFFFFFFB, 0xFFFFFFFFFFFFFF, 0x10000000000001E, 0x100000000000063, 0x10000000000006E, 0x10000000000008A, 0x100000000000095, 0x1000000000000AB, 0x1000000000000C0, 0x100000000000164, 0x100000000000176, 0x100000000000186, 0x10000000000018E, 0x10000000000019A, 0x1000000000001AD, 0x1000000000001B3, 0x1000000000001B7, 0x1000000000001C7, 0x1000000000001E4, 0x1000000000001E9, 0x1000000000001F1, 0x1000000000001F6, 0x100000000000217, 0x100000000000226, 0x100000000000249, 0x10000000000026C, 0x100000000000290, ],
#	);
#	@precursors=(
	# holy shit!  I can't believe I'm still finding bugs like this!  How did this never hit?  "The law of averages is a fallacy", and so I know
	# my current test script parameters must bias the probabilities just right in order to hit this far-out exception twice in 10 minutes
	# 
	# The bug was in the _asce block.  I noticed in the audit that an insert was being made to the spot vacated by the control index move,
	# but in the wrong order: the control index move is really an optional finishing iteration of the peristaltic shift loop, which
	# obviously needs to do its work before any insertions are made, in order to clear space for them.
	# Maybe the reason this hadn't caused a problem yet is that rel_q had never pivoted from positive to negative on the control index.
	# Say that requires an insertion of more than one element swinging rel_q from positive to negative, skipping over zero-crossing,
	# and that is what made it so unlikely— because typically, the "asce" loop would take over before rel_q goes negative.
	# I think I would need to watch step-by-step replays in order to understand all these edge cases in clear, obvious detail—
	# but while the question of why it never hit may still puzzle me, the fact that those lines were swapped is perfectly obvious.
	# See backups of av_commit() before/after 2026/05/23 to see the change that was made.
	# 
	[	#63	EPIGEN: 11 keys
	# Again, holy shit!  I have no confidence in brute force anymore.
	# well, it was so obvious, which puts things in perspective.  There are areas of the code which simply haven't grown up
	# past rudimentary status.  This was yet another bug in void _av_commit().  Right at the top, when it initializes the main loop,
	# it decides which mode to start in (ascending or descending) based on the difference in pre / post length.
	# But what if the length is the same?
	# Previously, it just assumed same length could be treated like regular descending mode, but on second thought,
	# it's ambiguous.  We have to skip initial steps until the tie breaks.
#	0xFFFFFFFE00..0xFFFFFFFE01,  0xFFFFFFFE03,                0xFFFFFFFE05..0xFFFFFFFE06,    0xFFFFFFFE08,	undef,
	0xFFFFFFFE0A..0xFFFFFFFE11,  0xFFFFFFFE13..0xFFFFFFFE14,  0xFFFFFFFE17,                  0xFFFFFFFE1A..0xFFFFFFFE20,    0xFFFFFFFE22,                  0xFFFFFFFE26,                  0xFFFFFFFE29..0xFFFFFFFE2B,	undef,
	0xFFFFFFFE2E,                0xFFFFFFFE31..0xFFFFFFFE32,  0xFFFFFFFE39..0xFFFFFFFE3B,    0xFFFFFFFE3D,	undef,
	0xFFFFFFFE41,                0xFFFFFFFE44..0xFFFFFFFE45,  0xFFFFFFFE49..0xFFFFFFFE4A,    0xFFFFFFFE4C..0xFFFFFFFE4D,    0xFFFFFFFE4F..0xFFFFFFFE50,	undef,
	0xFFFFFFFE52..0xFFFFFFFE54,  0xFFFFFFFE56,                0xFFFFFFFE59,                  0xFFFFFFFE5B..0xFFFFFFFE5D,    0xFFFFFFFE5F..0xFFFFFFFE62,	undef,
#	0xFFFFFFFE65..0xFFFFFFFE68,  0xFFFFFFFE6C..0xFFFFFFFE6D,  0xFFFFFFFE6F,                  0xFFFFFFFE73..0xFFFFFFFE74,    0xFFFFFFFE76,	undef,
#	0xFFFFFFFE7C,                0xFFFFFFFE7F,                0xFFFFFFFE81,                  0xFFFFFFFE85..0xFFFFFFFE8C,	undef,
	0xFFFFFFFE8E..0xFFFFFFFE91,  0xFFFFFFFE93,                0xFFFFFFFE95..0xFFFFFFFE96,    0xFFFFFFFE98..0xFFFFFFFE99,    0xFFFFFFFE9C..0xFFFFFFFE9F,	undef,
#	0xFFFFFFFEA3,                0xFFFFFFFEA6,                0xFFFFFFFEA8..0xFFFFFFFEA9,    0xFFFFFFFEAD,                  0xFFFFFFFEB0..0xFFFFFFFEB1,	undef,
#	0xFFFFFFFEB3..0xFFFFFFFEB5,  0xFFFFFFFEB8..0xFFFFFFFEB9,  0xFFFFFFFEBB..0xFFFFFFFEBE,    0xFFFFFFFEC0..0xFFFFFFFEC1,	undef,
	0xFFFFFFFEC3..0xFFFFFFFEC8,  0xFFFFFFFECB..0xFFFFFFFECC,  0xFFFFFFFECE..0xFFFFFFFED2,    0xFFFFFFFED4..0xFFFFFFFED5,	undef,
#	0xFFFFFFFED7,                0xFFFFFFFED9,                0xFFFFFFFEDB,                  0xFFFFFFFEE2..0xFFFFFFFEE3,    0xFFFFFFFEE6..0xFFFFFFFEE9,	undef,
	0xFFFFFFFEEB,                0xFFFFFFFEED..0xFFFFFFFEF2,  0xFFFFFFFEF4..0xFFFFFFFEF6,    0xFFFFFFFEF8,                  0xFFFFFFFEFA..0xFFFFFFFEFB,	undef,
#	0xFFFFFFFEFD,                0xFFFFFFFF00,                0xFFFFFFFF03..0xFFFFFFFF05,    0xFFFFFFFF09,                  0xFFFFFFFF0B..0xFFFFFFFF0C,	undef,
	0xFFFFFFFF0E..0xFFFFFFFF13,  0xFFFFFFFF15..0xFFFFFFFF16,  0xFFFFFFFF19..0xFFFFFFFF1D,    0xFFFFFFFF1F,	undef,
	0xFFFFFFFF25..0xFFFFFFFF26,  0xFFFFFFFF28..0xFFFFFFFF29,  0xFFFFFFFF2E,                  0xFFFFFFFF30..0xFFFFFFFF31,	undef,
	0xFFFFFFFF33..0xFFFFFFFF36,  0xFFFFFFFF38,                0xFFFFFFFF3A,                  0xFFFFFFFF41,                  0xFFFFFFFF44,                  0xFFFFFFFF48,                  0xFFFFFFFF4A..0xFFFFFFFF4B,	undef,
	0xFFFFFFFF4E..0xFFFFFFFF50,  0xFFFFFFFF53..0xFFFFFFFF63,	undef,
	0xFFFFFFFF65,                0xFFFFFFFF69..0xFFFFFFFF6B,  0xFFFFFFFF6D..0xFFFFFFFF6E,    0xFFFFFFFF70..0xFFFFFFFF71,    0xFFFFFFFF73,                  0xFFFFFFFF77..0xFFFFFFFF79,    0xFFFFFFFF7D..0xFFFFFFFF7E,    0xFFFFFFFF81,	undef,
	0xFFFFFFFF83,                0xFFFFFFFF86..0xFFFFFFFF89,  0xFFFFFFFF8C..0xFFFFFFFF8D,    0xFFFFFFFF93..0xFFFFFFFF94,    0xFFFFFFFF98,                  0xFFFFFFFF9B..0xFFFFFFFF9C,	undef,
	0xFFFFFFFF9E..0xFFFFFFFFA1,  0xFFFFFFFFA7,                0xFFFFFFFFAA,                  0xFFFFFFFFAD..0xFFFFFFFFAE,    0xFFFFFFFFB0,                  0xFFFFFFFFB2,                  0xFFFFFFFFB5..0xFFFFFFFFB7,	undef,
	0xFFFFFFFFBA,                0xFFFFFFFFBD,                0xFFFFFFFFC1..0xFFFFFFFFC5,    0xFFFFFFFFC9..0xFFFFFFFFCA,    0xFFFFFFFFD0..0xFFFFFFFFD1,	undef,
	0xFFFFFFFFD4..0xFFFFFFFFD5,  0xFFFFFFFFD9..0xFFFFFFFFDA,  0xFFFFFFFFDE,                  0xFFFFFFFFE0,                  0xFFFFFFFFE2..0xFFFFFFFFE3,    0xFFFFFFFFE5,                  0xFFFFFFFFE8,	undef,
#	0xFFFFFFFFED,                0xFFFFFFFFEF,                0xFFFFFFFFF1,                  0xFFFFFFFFF6..0xFFFFFFFFF9,    0xFFFFFFFFFC..0x10000000000,   0x10000000004..0x10000000005,  0x10000000007,	undef,
#	0x1000000000A,               0x1000000000C..0x10000000010,0x10000000012,                 0x10000000015..0x10000000019,  0x1000000001B..0x1000000001C,  0x10000000021..0x10000000026,	undef,
	0x10000000028,               0x1000000002A..0x10000000030,0x10000000033,                 0x10000000035,	undef,
	0x10000000037,               0x10000000039,               0x1000000003B..0x1000000003C,  0x1000000003F,	undef,
	0x10000000045..0x1000000004C,0x1000000004E..0x1000000004F,0x10000000051..0x10000000057,	undef,
	0x1000000005B..0x10000000063,0x10000000066,               0x10000000068,                 0x1000000006C,	undef,
#	0x1000000006E,               0x10000000070,               0x10000000072..0x10000000073,  0x10000000075..0x10000000078,	undef,
#	0x1000000007A,               0x1000000007D,               0x1000000007F,                 0x10000000081..0x10000000084,  0x10000000086..0x10000000088,	undef,
#	0x1000000008A..0x10000000091,0x10000000093..0x10000000096,0x10000000098,                 0x1000000009A..0x1000000009F,  0x100000000A1..0x100000000A3,  0x100000000A6,	undef,
#	0x100000000AA,               0x100000000AC,               0x100000000AE..0x100000000AF,  0x100000000B1,	undef,
#	0x100000000B6..0x100000000BA,0x100000000BE..0x100000000BF,0x100000000C2,                 0x100000000C5,                 0x100000000C7..0x100000000C8,  0x100000000CA,	undef,
#	0x100000000CD..0x100000000D6,0x100000000D8..0x100000000DA,0x100000000DC..0x100000000DE,  0x100000000E2,                 0x100000000E4..0x100000000E5,  0x100000000E7,	undef,
#	0x100000000EA..0x100000000EB,0x100000000ED,               0x100000000F0..0x100000000F1,  0x100000000F6..0x100000000F7,  0x100000000F9,                 0x100000000FC..0x100000000FE,	undef,
#	0x10000000102..0x10000000103,0x10000000106,               0x10000000108..0x10000000109,  0x1000000010B,                 0x10000000110,                 0x10000000113..0x10000000116,	undef,
#	0x1000000011B..0x1000000011D,0x1000000011F,               0x10000000123..0x10000000124,  0x10000000126,                 0x10000000129,                 0x1000000012B,                 0x1000000012F,                 0x10000000132,	undef,
#	0x10000000135..0x10000000137,0x1000000013A,               0x1000000013C,                 0x10000000140,                 0x10000000143,	undef,
#	0x10000000145..0x10000000147,0x1000000014B,               0x1000000014D..0x1000000014E,  0x10000000150,                 0x10000000155..0x10000000156,	undef,
#	0x1000000015B,               0x1000000015F,               0x10000000161,                 0x10000000168..0x10000000169,  0x1000000016D..0x1000000016E,  0x10000000172,                 0x10000000174,	undef,
#	0x10000000176,               0x1000000017B..0x1000000017C,0x1000000017F,                 0x10000000182,                 0x10000000185..0x10000000186,  0x10000000189..0x1000000018A,  0x1000000018D..0x10000000190,	undef,
#	0x10000000192..0x10000000193,0x10000000196,               0x10000000198..0x1000000019C,  0x1000000019E..0x100000001A5,  0x100000001A7,	undef,
	0x100000001AB..0x100000001AD,0x100000001AF..0x100000001B0,0x100000001B2,                 0x100000001B6,                 0x100000001B9..0x100000001BB,  0x100000001BF..0x100000001C1,	undef,

	],      [1099511627270, 1099511627271, 1099511627279, 1099511627280, 1099511627283, 1099511627288, 1099511627291, 1099511627292, 1099511627295, 1099511627297, 1099511627300, 1099511627304, 1099511627307, 1099511627310, 1099511627312, 1099511627317, 1099511627319, 1099511627327, 1099511627330, 1099511627332, 1099511627333, 1099511627338, 1099511627340, 1099511627346, 1099511627347, 1099511627356, 1099511627361, 1099511627368, 1099511627370, 1099511627384, 1099511627385, 1099511627390, 1099511627396, 1099511627404, 1099511627405, 1099511627409, 1099511627410, 1099511627413, 1099511627414, 1099511627415, 1099511627418, 1099511627419, 1099511627423, 1099511627432, 1099511627433, 1099511627437, 1099511627451, 1099511627454, 1099511627459, 1099511627464, 1099511627465, 1099511627468, 1099511627471, 1099511627472, 1099511627475, 1099511627477, 1099511627481, 1099511627484, 1099511627490, 1099511627497, 1099511627500, 1099511627502, 1099511627504, 1099511627505, 1099511627506, 1099511627510, 1099511627514, 1099511627520, 1099511627523, 1099511627541, 1099511627542, 1099511627553, 1099511627555, 1099511627560, 1099511627561, 1099511627563, 1099511627566, 1099511627588, 1099511627593, 1099511627594, 1099511627599, 1099511627601, 1099511627602, 1099511627620, 1099511627625, 1099511627630, 1099511627635, 1099511627637, 1099511627642, 1099511627650, 1099511627654, 1099511627657, 1099511627659, 1099511627663, 1099511627664, 1099511627667, 1099511627671, 1099511627676, 1099511627680, 1099511627682, 1099511627687, 1099511627689, 1099511627694, 1099511627702, 1099511627708, 1099511627712, 1099511627716, 1099511627722, 1099511627730, 1099511627737, 1099511627739, 1099511627743, 1099511627746, 1099511627747, 1099511627750, 1099511627752, 1099511627755, 1099511627759, 1099511627770, 1099511627775, 1099511627778, 1099511627780, 1099511627781, 1099511627785, 1099511627786, 1099511627787, 1099511627797, 1099511627804, 1099511627811, 1099511627821, 1099511627823, 1099511627828, 1099511627830, 1099511627838, 1099511627853, 1099511627856,
	 1099511627857, 1099511627860, 1099511627861, 1099511627864, 1099511627865, 1099511627866, 1099511627869, 1099511627870, 1099511627874, 1099511627882, 1099511627887, 1099511627891, 1099511627905, 1099511627906, 1099511627910, 1099511627919, 1099511627921, 1099511627925, 1099511627935, 1099511627937, 1099511627942, 1099511627946, 1099511627950, 1099511627959, 1099511627964, 1099511627965, 1099511627972, 1099511627987, 1099511627988, 1099511627990, 1099511627995, 1099511628002, 1099511628005, 1099511628007, 1099511628009, 1099511628013, 1099511628015, 1099511628018, 1099511628019, 1099511628020, 1099511628022, 1099511628023, 1099511628024, 1099511628036, 1099511628041, 1099511628046, 1099511628051, 1099511628059, 1099511628061, 1099511628065, 1099511628077, 1099511628081, 1099511628089, 1099511628091, 1099511628095, 1099511628099, 1099511628104, 1099511628105, 1099511628109, 1099511628114, 1099511628116, 1099511628117, 1099511628118, 1099511628119, 1099511628125, 1099511628130, 1099511628131, 1099511628132, 1099511628133, 1099511628143, 1099511628155, 1099511628159, 1099511628160, 1099511628161, 1099511628163, 1099511628168, 1099511628191, 1099511628196, 1099511628200, 1099511628202, 1099511628204, 1099511628209, 1099511628210, 1099511628212, 1099511628215, 1099511628217, 1099511628218, 1099511628222, 1099511628226, 1099511628230, 1099511628231, 1099511628232, 1099511628236, 1099511628244, 1099511628247, 1099511628249, 1099511628251, 1099511628254, 1099511628255, 1099511628257, 1099511628265, 1099511628273, 1099511628281, 1099511628282],

	####	);@precursors=(
	[	#64
	0x10000000002B2..0x10000000002BA,0x10000000002BD,                   0x10000000002BF,                   0x10000000002C3..0x10000000002D1, undef,
	0x10000000002D4..0x10000000002D7,0x10000000002D9..0x10000000002DA, undef,
	0x10000000002DC..0x10000000002E1,0x10000000002E3..0x10000000002EA,  0x10000000002ED,                   0x10000000002EF..0x10000000002F0, undef,
	0x10000000002F3..0x10000000002F4,0x10000000002F6..0x10000000002FF, undef,
	0x1000000000301..0x1000000000306,0x1000000000308..0x100000000030A,  0x100000000030D,                   0x1000000000314..0x1000000000318,  0x100000000031A, undef,
	0x100000000031C..0x1000000000323,0x1000000000325..0x1000000000327,  0x100000000032A..0x100000000032B,  0x100000000032D..0x100000000032E,  0x1000000000330..0x1000000000331, undef,
	0x1000000000334..0x1000000000336,0x1000000000339..0x100000000033D,  0x100000000033F..0x1000000000341, undef,

	],      [
	281474976711309, 281474976711318, 281474976711322, 281474976711355, 281474976711368, 281474976711373, 281474976711398, 
	281474976711409, 281474976711483, 
		],
	[	#65: minimized version of #64 from 2026-09-11 when debugging ReBAL mode.  First time getting this far.  Woohoo!!
	0x100000000028B..0x1000000000293,  0x1000000000295..0x100000000029B,  0x100000000029D..0x10000000002A0,
	0x10000000002A2..0x10000000002A4,  0x10000000002A7..0x10000000002AD,  0x10000000002AF..0x10000000002B0,
	0x10000000002B2..0x10000000002BA,  0x10000000002BD,                   0x10000000002BF,                   0x10000000002C3..0x10000000002D1,
	0x10000000002D4..0x10000000002D7,  0x10000000002D9..0x10000000002DA,
	0x10000000002DC..0x10000000002E1,  0x10000000002E3..0x10000000002EA,  0x10000000002ED,                   0x10000000002EF..0x10000000002F0,
	0x10000000002F3..0x10000000002F4,  0x10000000002F6..0x10000000002FF,
	0x1000000000301..0x1000000000306,  0x1000000000308..0x100000000030A,  0x100000000030D,                   0x1000000000314..0x1000000000318,  0x100000000031A,
	0x100000000031C..0x1000000000323,  0x1000000000325..0x1000000000327,  0x100000000032A..0x100000000032B,  0x100000000032D..0x100000000032E,  0x1000000000330..0x1000000000331,
	0x1000000000334..0x1000000000336,  0x1000000000339..0x100000000033D,  0x100000000033F..0x1000000000341,
	], [    0x100000000028D,0x1000000000296,0x100000000029A,0x10000000002BB,0x10000000002C8,0x10000000002CD,0x10000000002E6,0x10000000002F1,0x100000000033B], #hex

	[	#66	EPIGEN: 2 keys
	0x6,         0xB,         0xE..0xF,    0x13..0x14,    0x1F,          0x21,          0x2D,			undef,
	0x30,        0x35,        0x3B,        0x41,          0x48,          0x4C,          0x4E,  0x5B..0x5C,	undef,
	0x5E,        0x68,        0x6A,        0x6F..0x70,										undef,
	0x74,        0x77,        0x7B,        0x84,          0x86,          0x8F,						undef,
	0x91..0x92,  0x95..0x96,  0x9D..0x9E,  0xA0,          0xA3,							undef,
	0xA5..0xA6,  0xAB,        0xAD,        0xB0,          0xB3..0xB4,    0xBB,          0xC8,  0xCE,	undef,
	0xD2,        0xD4,        0xD7,        0xD9,          0xDD,								undef,
	0xE0,        0xE5,        0xEB,        0xED,          0xF3,          0xF6,          0xF9,				undef,
	0xFC..0xFD,  0x100,       0x10A,       0x10C,         0x10E,							undef,
	0x112,       0x115,       0x11A,       0x126,         0x12F,								undef,
	0x133,       0x13A,       0x141,       0x148,         0x14A,         0x14C,					undef,
	0x14F..0x151,0x156,       0x163,       0x165,         0x16B,							undef,
	0x16D,       0x176,       0x17B..0x17C,0x181..0x182,  0x18E,						undef,
	0x190,       0x196..0x197,0x19A,       0x1A2,         0x1A5,         0x1A9..0x1AA,			undef,
	0x1B0..0x1B1,0x1C0,       0x1C2,       0x1C5,         0x1CE,         0x1D2,         0x1D4,		undef,
	0x1D6..0x1D9,0x1DB,       0x1DD,       0x1E2,         0x1EA,

	],      [0x42,0x6C,0x7E,0x7F,0x93,0xAA,0xB9,0xEB,0x10D,0x112,0x127,0x12B,0x12E,0x140,0x15F,0x182,0x185,0x18F,0x1A8,0x1AF,0x1BB,0x1D1,0x1DC,0x1F2,0x1F8],
	[	#67	EPIGEN: 1 key
	0x2,         0x5..0x6,    0xA,         0x10,          0x12,          0x14,          0x17,          0x1B,								undef,
	0x1D,        0x1F..0x21,  0x23,        0x27,          0x29,          0x2B,          0x2F,          0x32..0x33,							undef,
	0x39..0x3B,  0x40..0x43,  0x47,        0x49,          0x4B..0x4E,    0x50,          0x52,          0x54,							undef,
	0x59,        0x5B..0x62,  0x65,        0x69,          0x6C,          0x6E..0x71,    0x79,          0x7C..0x7D,		undef,
	0x7F,        0x81,        0x83,        0x87,          0x89,          0x8B,          0x8D..0x8F,    0x91,				undef,
	0x93..0x94,  0x96..0x97,  0x9D,        0x9F..0xA2,    0xA7,          0xA9,          0xAB..0xAD,    0xB1,		undef,
	0xB4..0xB5,  0xB8,        0xBA..0xBB,  0xBE,          0xC3..0xC4,    0xC7,          0xC9,          0xCD,		undef,
	0xCF,        0xD1..0xD3,  0xD8..0xDA,  0xDD..0xDE,    0xE3..0xE4,    0xE7,          0xE9,          0xEB,		undef,
	0xEE..0xF0,  0xF8,        0xFB..0xFC,  0xFE,          0x101,         0x103..0x104,  0x109,         0x10D,						undef,
	0x110..0x111,0x113,       0x116..0x117,0x119..0x11A,  0x11C,         0x11E..0x121,  0x124,         0x128..0x129,			undef,
	0x12B..0x12C,0x132,       0x134,       0x136,         0x139,         0x13B..0x141,  0x144..0x145,  0x148..0x14B,				undef,
	0x14D,       0x14F,       0x151..0x152,0x154,         0x156,         0x15B,         0x15D,         0x160,						undef,
	0x162..0x168,0x16A,       0x16C,       0x170,         0x177,         0x179..0x17B,  0x17D..0x17E,  0x180,					undef,
	0x183..0x184,0x187,       0x18D,       0x191..0x192,  0x195..0x197,  0x19A..0x19B,  0x19E..0x19F,  0x1A1,				undef,
	0x1A9,       0x1AB..0x1B0,0x1B2,       0x1B4,         0x1B6..0x1B8,  0x1BC,         0x1C2..0x1C4,  0x1C6,					undef,
	0x1CC..0x1CD,0x1CF,       0x1D1..0x1D3,0x1D7,         0x1DA..0x1DD,  0x1E1..0x1E2,  0x1E4..0x1E5,  0x1E7..0x1EA,		undef,
	0x1EC..0x1EF,0x1F1..0x1F5,0x1F7..0x1FA,0x1FC,
	],      [0x0,0x2,0x5,0x6,0xD,0xF,0x11,0x13,0x15,0x17,0x18,0x19,0x1B,0x1D,0x20,0x22,0x23,0x26,0x28,0x29,0x2B,0x31,0x32,0x34,0x36,0x37,0x39,0x3B,0x3C,0x3D,0x3F,0x41,0x43,0x45,0x46,0x47,0x4B,0x4D,0x4F,0x50,0x51,0x52,0x56,0x5B,0x5C,0x5E,0x60,0x61,0x62,0x63,0x68,0x69,0x6A,0x6B,0x6E,0x6F,0x71,0x72,0x75,0x78,0x7A,0x7B,0x7C,0x7D,0x7E,0x81,0x84,0x86,0x87,0x88,0x89,0x8A,0x8C,0x8F,0x91,0x93,0x94,0x95,0x96,0x97,0x99,0x9A,0x9B,0x9F,0xA2,0xA3,0xA5,0xA8,0xAA,0xAB,0xB1,0xB3,0xB4,0xB8,0xB9,0xBA,0xBB,0xBC,0xC5,0xC6,0xC7,0xC8,0xCA,0xCE,0xCF,0xD1,0xD2,0xD8,0xD9,0xDC,0xE0,0xE1,0xE2,0xE4,0xE8,0xE9,0xEC,0xEE,0xF3,0xF5,0xF7,0xFB,0xFC,0xFD,0xFF,0x102,0x103,0x104,0x108,0x109,0x10B,0x10D,0x10F,0x110,0x117,0x118,0x119,0x11A,0x11C,0x11D,0x11E,0x11F,0x120,0x121,0x122,0x127,0x128,0x129,0x12B,0x12E,0x12F,0x130,0x132,0x133,0x135,0x13A,0x13B,0x145,0x146,0x147,0x149,0x14C,0x14D,0x151,0x154,0x156,0x159,0x15A,0x15C,0x15D,0x15E,0x15F,0x160,0x161,0x166,0x16A,0x16C,0x16D,0x16E,0x172,0x173,0x176,0x178,0x179,0x17A,0x17B,0x17C,0x17F,0x180,0x181,0x182,0x183,0x185,0x186,0x187,0x188,0x189,0x18B,0x18D,0x18E,0x190,0x191,0x19A,0x19B,0x19E,0x19F,0x1A1,0x1A3,0x1A5,0x1A7,0x1A8,0x1AD,0x1B3,0x1B4,0x1BB,0x1C3,0x1C4,0x1C6,0x1C7,0x1C8,0x1CD,0x1D3,0x1D4,0x1D5,0x1D6,0x1D7,0x1D8,0x1DA,0x1DC,0x1E2,0x1E3,0x1E9,0x1EB,0x1EE,0x1EF,0x1F4,0x1F6,0x1F7,0x1FA,0x1FB,0x1FE],
	[	#68	EPIGEN: 0 keys (must have incremented B[ u ])
	0x0..0x2,    0x4..0xF,      0x11..0x1A,													undef,
	0x1C..0x21,  0x23..0x25,    0x27..0x29,    0x2B..0x2D,									undef,
	0x2F..0x3C,  0x3E,          0x40..0x4B,													undef,
	0x4D..0x54,  0x56..0x57,    0x59..0x5B,    0x5E..0x6E,										undef,
	0x71..0x7C,  0x7E..0x92,															undef,
	0x94..0x95,  0x97..0xA0,    0xA2,          0xA4..0xAA,										undef,
	0xAC..0xB8,																		undef,
	0xBB..0xCD,  0xD0..0xD8,    0xDB,          0xDD..0xE1,									undef,
	0xE3..0xE7,  0xE9..0xEC,    0xEE..0xEF,    0xF1..0xF7,    0xF9..0xFD,							undef,
	0x101..0x103,0x106..0x10F,  0x111..0x113,  0x115..0x11A,								undef,
	0x11C..0x120,0x123..0x12B,  0x12D..0x138,											undef,
	0x13A..0x146,0x148..0x14B,  0x14E..0x152,											undef,
	0x154..0x159,0x15B,         0x15D..0x15F,  0x162,         0x164..0x17D,						undef,
	0x180..0x184,0x186..0x18D,  0x18F,         0x191..0x194,  0x196,         0x198..0x19C,			undef,
	0x19E..0x1A7,0x1A9,         0x1AB..0x1B6,  0x1B8..0x1C0,									undef,
	0x1C2..0x1C3,0x1C5..0x1D0,  0x1D2..0x1DC,  0x1DF..0x1E0,								undef,
	0x1E2..0x1F2,0x1F4..0x1F8,  0x1FA,         0x1FC..0x1FD,
	],      [0x3,0x4,0x8,0x9,0xA,0xB,0xC,0xD,0x10,0x11,0x13,0x14,0x15,0x16,0x19,0x1E,0x1F,0x20,0x22,0x25,0x27,0x28,0x29,0x2B,0x2C,0x2F,0x30,0x31,0x33,0x34,0x35,0x3A,0x3C,0x3F,0x45,0x46,0x4A,0x4B,0x50,0x53,0x54,0x57,0x58,0x5A,0x5B,0x5D,0x5F,0x60,0x62,0x64,0x65,0x66,0x6C,0x6E,0x6F,0x71,0x72,0x75,0x77,0x78,0x79,0x7A,0x7D,0x7E,0x7F,0x80,0x86,0x87,0x89,0x8C,0x8D,0x8F,0x91,0x97,0x98,0x99,0x9E,0x9F,0xA1,0xA2,0xA5,0xA7,0xAA,0xAB,0xAF,0xB0,0xB6,0xB9,0xBB,0xBC,0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xCB,0xCC,0xCF,0xD1,0xD2,0xD3,0xD5,0xD6,0xDC,0xDD,0xDF,0xE2,0xE4,0xE5,0xE6,0xE9,0xED,0xF0,0xF3,0xF5,0xF6,0xFC,0xFE,0x100,0x102,0x105,0x108,0x110,0x112,0x114,0x118,0x119,0x11B,0x11F,0x123,0x124,0x125,0x126,0x129,0x12B,0x12F,0x132,0x133,0x136,0x137,0x138,0x139,0x13E,0x140,0x142,0x144,0x147,0x149,0x14B,0x14D,0x14E,0x151,0x154,0x156,0x157,0x159,0x15A,0x15D,0x15E,0x160,0x163,0x165,0x166,0x167,0x169,0x16A,0x16B,0x170,0x173,0x174,0x177,0x178,0x17A,0x17B,0x17C,0x17D,0x17E,0x17F,0x180,0x186,0x187,0x189,0x18A,0x18C,0x18E,0x190,0x191,0x195,0x196,0x197,0x19A,0x19B,0x19C,0x19E,0x1A2,0x1A5,0x1A6,0x1A7,0x1AA,0x1AB,0x1B1,0x1B6,0x1B7,0x1B9,0x1BC,0x1C0,0x1C1,0x1C2,0x1C3,0x1C4,0x1C5,0x1C6,0x1C7,0x1CA,0x1CB,0x1CD,0x1D0,0x1D6,0x1D7,0x1D8,0x1D9,0x1DA,0x1DB,0x1DF,0x1E4,0x1E5,0x1E7,0x1E8,0x1E9,0x1EB,0x1EC,0x1ED,0x1EF,0x1F0,0x1F6,0x1F8,0x1FC,0x1FE],
	[	#69	EPIGEN: 1 key
	0x4,         0x7..0x9,    0xB,         0xE..0x10,   0x12,          0x14..0x15,    0x17..0x19,    0x1B..0x1C,
	0x20,        0x23,        0x25,        0x27..0x28,  0x2A,          0x2D..0x2E,    0x32..0x37,    0x3B..0x3C,
	0x3F..0x40,  0x42..0x43,  0x47,        0x49,        0x4F,          0x53,          0x55..0x59,    0x5F..0x60,
	0x69,        0x6B..0x6D,  0x6F..0x70,  0x72,        0x75,          0x78,          0x7B..0x7D,    0x7F..0x80,
	0x82,        0x84..0x85,  0x88,        0x8B..0x95,  0x98..0x99,    0x9D..0x9E,    0xA0,          0xA3..0xA4,
	0xA7..0xAA,  0xAE..0xAF,  0xB2,        0xB5..0xB7,  0xC0,          0xC3..0xC5,    0xC7,          0xCB,
	0xD1..0xD2,  0xD4,        0xD6..0xD7,  0xDB,        0xDD,          0xDF..0xE0,    0xE4,          0xE6..0xE8,
	0xF2,        0xF7,        0xF9,        0xFC,        0xFF..0x101,   0x106..0x107,  0x109,         0x10B..0x10C,
	0x111,       0x115,       0x117,       0x119..0x11B,0x11F,         0x121,         0x125..0x126,  0x128..0x129,
	0x12B..0x12C,0x12F,       0x131,       0x137,       0x139..0x13A,  0x13D..0x13E,  0x141..0x142,  0x146..0x14A,
	0x14C..0x14F,0x151,       0x154..0x157,0x159..0x15B,0x15D,         0x15F..0x160,  0x164..0x166,  0x169..0x16A,
	0x16C..0x16E,0x170,       0x172,       0x174..0x175,0x178..0x17C,  0x180..0x184,  0x189..0x18C,  0x18E..0x18F,
	0x191..0x192,0x195,       0x19C,       0x1A1..0x1A2,0x1A6,         0x1AB..0x1AC,  0x1AF..0x1B0,  0x1B2,
	0x1B4..0x1B5,0x1B8..0x1BB,0x1BD,       0x1BF,       0x1C1..0x1C4,  0x1C7,         0x1CF,         0x1D2..0x1D3,
	0x1D7..0x1D8,0x1DA,       0x1DC,       0x1E0..0x1E2,0x1E5..0x1E6,  0x1EA,         0x1EE,         0x1F1..0x1F3,
	0x1F5,       0x1F8..0x1F9,0x1FB,

	],      [0x0,0x1,0x2,0x6,0x7,0x8,0xA,0xB,0xC,0xD,0xF,0x10,0x13,0x18,0x19,0x1A,0x1E,0x22,0x23,0x2B,0x2E,0x2F,0x33,0x35,0x36,0x37,0x38,0x3A,0x3B,0x3D,0x3F,0x42,0x44,0x46,0x49,0x4C,0x4E,0x4F,0x50,0x51,0x53,0x54,0x55,0x56,0x58,0x5C,0x60,0x61,0x62,0x63,0x64,0x65,0x67,0x68,0x6A,0x6D,0x6F,0x7A,0x7C,0x7D,0x7F,0x80,0x82,0x86,0x87,0x89,0x8A,0x8B,0x8C,0x8E,0x8F,0x90,0x91,0x94,0x96,0x97,0x98,0x9A,0x9E,0xA0,0xA1,0xA2,0xA3,0xA4,0xA7,0xA9,0xAA,0xAD,0xAE,0xAF,0xB5,0xB8,0xBB,0xBE,0xBF,0xC0,0xC2,0xC4,0xC9,0xCC,0xCD,0xD1,0xD2,0xD3,0xD9,0xDA,0xDC,0xDE,0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE9,0xEA,0xEC,0xED,0xEE,0xEF,0xF5,0xF7,0xF8,0xFA,0xFB,0xFF,0x100,0x102,0x104,0x105,0x106,0x107,0x10B,0x10D,0x111,0x117,0x11A,0x11F,0x123,0x124,0x127,0x12B,0x12C,0x12F,0x130,0x131,0x132,0x134,0x135,0x137,0x13A,0x13E,0x140,0x142,0x144,0x145,0x14B,0x14E,0x150,0x152,0x153,0x157,0x158,0x15B,0x15C,0x15E,0x15F,0x160,0x161,0x162,0x163,0x164,0x165,0x166,0x16B,0x16C,0x16D,0x171,0x173,0x176,0x178,0x17B,0x17E,0x17F,0x180,0x181,0x182,0x183,0x184,0x185,0x186,0x187,0x188,0x189,0x18B,0x193,0x19C,0x1A0,0x1A2,0x1A8,0x1AE,0x1AF,0x1B0,0x1B2,0x1B6,0x1B7,0x1B9,0x1C2,0x1C4,0x1C5,0x1C6,0x1C8,0x1CB,0x1CD,0x1CF,0x1D0,0x1D2,0x1D3,0x1D5,0x1D6,0x1D9,0x1DA,0x1DC,0x1DE,0x1E0,0x1E4,0x1E5,0x1E6,0x1E8,0x1EA,0x1EB,0x1EF,0x1F0,0x1F2,0x1F3,0x1F8,0x1F9,0x1FD,0x1FE],
	[	#70	EPIGEN: 1 key
	0x1..0x3,    0x5..0x6,    0x8..0xB,    0xD..0xF,      0x12,          0x14,          0x17,          0x19,						undef,
	0x1D,        0x22,        0x27..0x28,  0x2B..0x2D,    0x30,          0x33,          0x35,          0x37..0x38,					undef,
	0x3A..0x3C,  0x3E,        0x45..0x47,  0x49,          0x4B,          0x4D,          0x4F..0x50,    0x52..0x53,				undef,
	0x57..0x58,  0x5A,        0x5D,        0x5F,          0x62,          0x64..0x66,    0x68..0x69,    0x6C..0x6D,				undef,
	0x70..0x71,  0x77..0x78,  0x7D..0x7E,  0x82,          0x84,          0x87..0x89,    0x8B,          0x8E,					undef,
	0x90,        0x92..0x94,  0x97,        0x9A,          0x9E,          0xA0,          0xA2,          0xA7..0xA8,					undef,
	0xAA..0xAD,  0xAF,        0xB3..0xB4,  0xB8,          0xBA..0xBB,    0xBE..0xC2,    0xC6,          0xC8,					undef,
	0xCB..0xCD,  0xCF..0xD0,  0xD5..0xD7,  0xD9,          0xDC,          0xE2..0xE3,    0xE5,          0xE8,					undef,
	0xED..0xF0,  0xF2..0xF4,  0xF7,        0xFA,          0xFD..0xFE,    0x100,         0x105,         0x107..0x108,				undef,
	0x10C..0x10F,0x115..0x116,0x118,       0x11E,         0x120..0x123,  0x126,         0x129,         0x12B..0x12E,			undef,
	0x130..0x132,0x134..0x135,0x137,       0x13B,         0x13D..0x13E,  0x140,         0x143,         0x145,				undef,
	0x147,       0x14B,       0x14E..0x150,0x155..0x158,  0x15B..0x15C,  0x15E,         0x162,         0x165..0x168,			undef,
	0x16A..0x16B,0x16F..0x173,0x175,       0x17B..0x17E,  0x182,         0x185..0x187,  0x18E,         0x191,				undef,
	0x193,       0x195,       0x197..0x19C,0x1A0..0x1A1,  0x1A6..0x1A7,  0x1AA..0x1AC,  0x1B0,         0x1B2,			undef,
	0x1B6,       0x1B8,       0x1BA,       0x1BC..0x1BD,  0x1C0..0x1C2,  0x1C5..0x1C8,  0x1CA..0x1CC,  0x1D1..0x1D5,	undef,				undef,
	0x1D8..0x1D9,0x1DB,       0x1DF..0x1E0,0x1E2,         0x1E6,         0x1E8..0x1E9,  0x1ED..0x1EE,  0x1F0,
	0x1F4,       0x1F8,

	],      [0x4,0xD,0xF,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x1B,0x1F,0x20,0x21,0x25,0x26,0x27,0x28,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x31,0x32,0x33,0x34,0x38,0x3B,0x3D,0x40,0x45,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x51,0x52,0x56,0x58,0x59,0x67,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x70,0x72,0x73,0x74,0x75,0x76,0x77,0x7D,0x80,0x81,0x82,0x84,0x85,0x86,0x8C,0x8D,0x90,0x93,0x95,0x97,0x9D,0xA0,0xA3,0xA4,0xA5,0xA7,0xA9,0xAD,0xAE,0xAF,0xB0,0xB2,0xB3,0xB5,0xB6,0xB8,0xB9,0xBC,0xBE,0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xCA,0xCC,0xCD,0xCE,0xD1,0xD2,0xD3,0xD4,0xD8,0xD9,0xDD,0xDE,0xE0,0xE1,0xE4,0xE8,0xE9,0xEB,0xEC,0xEE,0xEF,0xF1,0xF3,0xF6,0xF7,0xF9,0xFB,0xFC,0xFE,0x100,0x103,0x104,0x106,0x109,0x10C,0x10E,0x10F,0x112,0x114,0x115,0x116,0x117,0x119,0x11C,0x11D,0x122,0x126,0x12C,0x12D,0x12F,0x130,0x131,0x132,0x134,0x135,0x139,0x141,0x144,0x147,0x14A,0x14C,0x14D,0x14E,0x14F,0x151,0x155,0x157,0x15A,0x160,0x162,0x165,0x169,0x16B,0x16C,0x16D,0x16E,0x16F,0x172,0x173,0x174,0x176,0x177,0x178,0x17B,0x17E,0x17F,0x183,0x185,0x187,0x189,0x18A,0x18D,0x190,0x194,0x195,0x198,0x19B,0x19D,0x19E,0x1A4,0x1A8,0x1AA,0x1AB,0x1AC,0x1AE,0x1B0,0x1B2,0x1B5,0x1B8,0x1B9,0x1BE,0x1C0,0x1C3,0x1C4,0x1C9,0x1CA,0x1CC,0x1D0,0x1D1,0x1D2,0x1D3,0x1D8,0x1D9,0x1DD,0x1DE,0x1E0,0x1E1,0x1E2,0x1E4,0x1E5,0x1E7,0x1EA,0x1EB,0x1F0,0x1F1,0x1F3,0x1F5,0x1FA,0x1FB,0x1FC,0x1FD,0x1FE],

	[	#71	EPIGEN: 1 key
	0x1,         0x3,         0xE,         0x12,													undef,
	0x1A,        0x1C,        0x1E,        0x20,          0x24,          0x26,          0x2C..0x2F,				undef,
	0x32,        0x34,        0x37,        0x43,          0x45..0x46,    0x52..0x53,    0x57,          0x5D,		undef,
	0x64..0x65,  0x68,        0x6C,        0x71..0x72,    0x7A..0x7B,    0x84,          0x8A,				undef,
	0x8F,        0x91,        0x95,        0x9F,          0xA1,          0xA6..0xA7,    0xAD,          0xB5,			undef,
	0xBB,        0xC5,        0xCA,        0xCE,          0xD3..0xD4,    0xDC,							undef,
	0xE3,        0xEA,        0xF4..0xF6,  0xFC,          0xFF,										undef,
	0x102,       0x104..0x106,0x111,       0x113,         0x11A..0x11C,  0x11F..0x120,				undef,
	0x123..0x124,0x126,       0x12A,       0x12C,												undef,
	0x130,       0x139,       0x141,       0x156,         0x158,										undef,
	0x161,       0x169,       0x170..0x171,0x176,         0x181,         0x184..0x186,  0x18B,         0x18F,	undef,
	0x191,       0x193,       0x19A..0x19B,0x1B2..0x1B3,  0x1BD,								undef,
	0x1C0,       0x1CD,       0x1D1,       0x1D5,         0x1D9..0x1DA,								undef,
	0x1DC..0x1DE,0x1E2..0x1E4,0x1E6..0x1E7,0x1E9,         0x1EF,         0x1F6,         0x1F9,
	],      [0x0,0x13,0x46,0x74,0xB2,0xB7,0xBD,0xD0,0xEF,0x103,0x109,0x10A,0x12F,0x142,0x145,0x165,0x16A,0x17D,0x18F,0x195,0x1A7,0x1B9,0x1DA,0x1E4,0x1FC],
	[	#72	EPIGEN: 1 key
	0x1,         0xD,         0x11,        0x2C,          0x31,          0x37,									undef,
	0x48,        0x4B..0x4C,  0x56,        0x5D,          0x61,											undef,
	0x71,        0x75,        0x7C,        0x7F,          0x89,												undef,
	0x8B,        0x8F..0x90,  0x99,        0x9B,          0xA0,          0xA6..0xA8,							undef,
	0xAE..0xAF,  0xB2,        0xB4,        0xB6,          0xB9,          0xBE,								undef,
	0xC1,        0xC6,        0xCD..0xCE,  0xD8,          0xE3,          0xE6,          0xF4,          0xF6,				undef,
	0xF8,        0x103..0x104,0x108..0x109,0x10C,         0x116,										undef,
	0x11D,       0x123,       0x125..0x126,0x12A,         0x12F,         0x135,         0x13E..0x13F,				undef,
	0x147,       0x149..0x14A,0x14C,       0x14F..0x151,											undef,
	0x157,       0x15F,       0x162,       0x165,         0x169..0x16A,									undef,
	0x16D,       0x171..0x172,0x176,       0x178,													undef,
	0x17D..0x17E,0x182,       0x18E,       0x19F,         0x1BB,										undef,
	0x1BD,       0x1BF,       0x1C9,       0x1CC,													undef,
	0x1D0..0x1D1,0x1D6,       0x1D8,       0x1DB,         0x1DF,         0x1E5,         0x1E7..0x1E9,  0x1F6,
	],      [0x17,0x38,0x56,0x57,0x61,0x6B,0x6E,0x77,0x9B,0xA9,0xB1,0xBC,0xBF,0xD2,0x10C,0x118,0x12F,0x148,0x15A,0x186,0x1A5,0x1A7,0x1BC,0x1DB,0x1FE],
	[	#73	EPIGEN: 1 key
	0x1,         0x5,         0xF..0x10,   0x13,        0x1F,          0x21,          0x23..0x24,    0x26,							undef,
	0x28..0x29,  0x2F..0x30,  0x38,        0x3A,        0x3D,          0x41..0x45,    0x4F,          0x57,						undef,
	0x5D,        0x5F..0x60,  0x6B,        0x6E,        0x71,          0x75..0x76,    0x7A..0x7B,    0x7E,						undef,
	0x81..0x83,  0x86,        0x88,        0x8B,        0x90,          0x94..0x95,    0x98..0x99,    0x9D,						undef,
	0xA3,        0xA7,        0xAA,        0xAE,        0xB3,          0xB6,          0xB8,          0xBF,							undef,
	0xC3,        0xC6,        0xCB..0xCC,  0xD0..0xD1,  0xD8..0xD9,    0xE2,          0xE5,          0xE8,						undef,
	0xEE..0xEF,  0xF9,        0xFF,        0x106,       0x10A..0x10B,  0x116..0x117,  0x126..0x127,  0x12E..0x12F,			undef,
	0x138,       0x13E..0x13F,0x142..0x143,0x146,       0x14A,         0x14F,         0x15A..0x15B,  0x15D,					undef,
	0x161..0x162,0x169,       0x170,       0x174..0x175,0x17C..0x17D,  0x17F,         0x185,         0x18C,					undef,
	0x190..0x192,0x194..0x195,0x199..0x19A,0x19F..0x1A0,0x1A2,         0x1A6,         0x1AE,         0x1B3..0x1B6,		undef,
	0x1BC..0x1BD,0x1BF,       0x1C4,       0x1C8..0x1C9,0x1CC,         0x1D1..0x1D5,  0x1D7,         0x1DB,				undef,
	0x1DF,       0x1E1,       0x1E5,       0x1E9..0x1EA,0x1ED,         0x1F3,         0x1F7,         0x1FA,						undef,
	0x1FC,
	],      [0x2,0x7,0x8,0xB,0xC,0x11,0x15,0x1D,0x27,0x28,0x31,0x39,0x40,0x42,0x44,0x4D,0x50,0x52,0x58,0x5A,0x5C,0x5E,0x5F,0x60,0x62,0x63,0x65,0x67,0x6A,0x6C,0x73,0x76,0x77,0x78,0x79,0x7C,0x7E,0x86,0x8C,0x90,0x9E,0xA9,0xAA,0xAD,0xAF,0xB5,0xB8,0xBC,0xBF,0xC1,0xC2,0xC4,0xC7,0xC8,0xCB,0xCF,0xD3,0xD9,0xDF,0xE5,0xE9,0xEC,0xF0,0xF3,0xF8,0xFA,0xFB,0xFF,0x100,0x101,0x102,0x103,0x104,0x107,0x108,0x10A,0x10B,0x10D,0x110,0x112,0x114,0x115,0x116,0x119,0x11C,0x122,0x125,0x127,0x12F,0x13D,0x141,0x149,0x14A,0x14D,0x14E,0x152,0x153,0x158,0x159,0x15B,0x15D,0x15E,0x15F,0x161,0x168,0x16A,0x16D,0x16E,0x176,0x17D,0x17F,0x180,0x185,0x186,0x187,0x18D,0x18F,0x192,0x198,0x199,0x1A3,0x1AC,0x1AE,0x1BA,0x1C0,0x1C6,0x1C8,0x1D1,0x1D4,0x1D7,0x1DF,0x1E0,0x1E3,0x1E4,0x1F2,0x1F3,0x1F6,0x1F7,0x1F9,0x1FA,0x1FE],
	[	#74	EPIGEN: 1 key					targets the iC==zC INTERLOC1UP case of _set()
	0x0..0x2,    0x4..0x8,    0xA,           0xC,           0xF..0x10,								undef,
	0x12..0x13,  0x15,        0x17..0x1B,												undef,
	0x1E..0x25,  0x29..0x34,  0x36..0x37,												undef,
	0x39..0x3D,  0x3F..0x42,  0x44..0x45,    0x47..0x48,									undef,
	0x4A,        0x4C..0x4D,  0x4F..0x53,												undef,
	0x55..0x5A,  0x5C,        0x5F..0x62,    0x64,											undef,
	0x66..0x6A,  0x6C,        0x6E..0x6F,    0x71,          0x73..0x75,    0x77..0x7A,    0x7C..0x80,	undef,
	0x84..0x87,  0x89..0x8B,  0x8E,          0x90..0x93,    0x95,								undef,
	0x97..0x9C,  0x9E..0x9F,  0xA1,          0xA3..0xA6,    0xA8..0xA9,    0xAB..0xAD,			undef,
	0xAF..0xB1,  0xB3..0xB5,  0xB8,          0xBA..0xC5,									undef,
	0xC7..0xCF,  0xD1..0xD8,														undef,
	0xDA..0xDB,  0xDD,        0xDF..0xE2,    0xE5,          0xE7..0xEB,							undef,
	0xED..0xEE,  0xF2..0xF3,  0xF5..0xF6,    0xF9,          0xFB..0xFF,    0x101..0x10A,			undef,
	0x10C,       0x10E,       0x110,         0x112..0x115,									undef,
	0x117..0x11A,0x11C,       0x11E,													undef,
	0x120..0x125,0x127,       0x129..0x12B,  0x12D..0x130,  0x133,         0x135,				undef,
	0x13B,       0x13D..0x13F,0x143..0x14D,  0x14F..0x152,  0x155..0x157,					undef,
	0x15B..0x15D,0x15F,       0x161..0x162,  0x164..0x165,  0x167..0x168,  0x16B..0x16F,		undef,
	0x171..0x179,0x17C,       0x17E..0x181,  0x184..0x186,								undef,
	0x188..0x191,0x195..0x197,0x19A..0x19E,											undef,
	0x1A0..0x1A1,0x1A3..0x1A4,0x1A7..0x1AA,  0x1AC..0x1B3,  0x1B6..0x1BC,				undef,
	0x1BE..0x1BF,0x1C1..0x1C3,0x1C6..0x1C7,  0x1CA..0x1D0,							undef,
	0x1D2..0x1D7,0x1D9,       0x1DC..0x1DD,  0x1DF..0x1E0,  0x1E2..0x1E5,					undef,
	0x1E7,       0x1E9,       0x1EB..0x1ED,  0x1EF..0x1F5,									undef,
	0x1F8,																		undef,
	0x1FB,
	],      [0x9,0xF,0x11,0x14,0x16,0x17,0x1D,0x1E,0x1F,0x21,0x25,0x26,0x29,0x2C,0x2D,0x3A,0x40,0x46,0x49,0x50,0x51,0x52,0x53,0x54,0x57,0x58,0x5B,0x5D,0x5E,0x5F,0x61,0x68,0x6B,0x6C,0x6D,0x6E,0x70,0x71,0x72,0x76,0x79,0x7B,0x7E,0x7F,0x80,0x85,0x88,0x8E,0x9E,0xA5,0xA7,0xA8,0xA9,0xAA,0xAC,0xB0,0xB3,0xBB,0xC6,0xC7,0xC8,0xCB,0xCF,0xD1,0xD3,0xD8,0xD9,0xDE,0xE0,0xE6,0xF2,0xF4,0xF5,0xFA,0xFE,0xFF,0x106,0x107,0x10D,0x10F,0x111,0x116,0x11C,0x122,0x132,0x137,0x138,0x13D,0x13F,0x143,0x144,0x14A,0x14B,0x14D,0x14F,0x152,0x15A,0x15C,0x162,0x165,0x16A,0x171,0x172,0x173,0x176,0x17F,0x18E,0x191,0x194,0x199,0x19A,0x19B,0x19C,0x19D,0x19E,0x1A2,0x1A6,0x1AB,0x1AC,0x1B2,0x1B7,0x1BF,0x1C0,0x1C1,0x1C3,0x1C4,0x1C6,0x1C9,0x1CC,0x1CF,0x1D0,0x1D1,0x1D4,0x1D7,0x1DC,0x1E0,0x1E5,0x1E9,0x1EA,0x1F2,0x1FE],
	[	#75	EPIGEN: 1 key
	0x1..0x3,    0x7..0x8,      0xA,																undef,
	0xC,         0xF,           0x11,          0x13..0x15,    0x17..0x18,    0x1A..0x1B,    0x1E,						undef,
	0x21..0x26,  0x28..0x2D,    0x2F..0x34,    0x37..0x3A,												undef,
	0x3C..0x41,  0x43..0x46,    0x48,          0x4B..0x4D,    0x4F..0x50,    0x52..0x54,						undef,
	0x56,        0x5A..0x5B,    0x5D..0x60,    0x62,          0x65..0x6D,										undef,
	0x70..0x7D,  0x7F..0x80,    0x82,																undef,
	0x85..0x86,  0x88..0x8A,    0x8C..0x92,														undef,
	0x94..0x9B,  0x9D..0xA0,    0xA2,																undef,
	0xA5..0xAA,  0xAC..0xB4,    0xB6,          0xB8,													undef,
	0xBA..0xBC,  0xBE,          0xC1..0xC2,    0xC4,          0xC6..0xCF,    0xD1..0xD5,    0xD7,  0xDA..0xDB,		undef,
	0xDD..0xDE,  0xE1..0xE2,    0xE4,          0xE7..0xE8,    0xEA..0xED,									undef,
	0xEF,        0xF1..0xF3,    0xF6..0xFA,    0xFC..0xFD,    0x100,         0x103..0x106,						undef,
	0x108..0x10A,0x10C..0x112,  0x114,															undef,
	0x116..0x117,0x11B..0x11F,  0x121..0x123,														undef,
	0x125..0x12C,0x12E..0x12F,  0x131..0x132,  0x134,												undef,
	0x137,       0x139..0x13A,  0x13C..0x13E,  0x140..0x142,											undef,
	0x144..0x146,0x149,         0x14B,         0x14D..0x151,  0x153..0x156,  0x159,							undef,
	0x15B..0x161,0x163..0x168,  0x16A..0x172,  0x174..0x17E,  0x180,         0x182,						undef,
	0x184..0x188,0x18A..0x18C,  0x18E..0x193,  0x195,												undef,
	0x197..0x198,0x19A..0x19D,  0x19F,         0x1A1,         0x1A3..0x1A7,  0x1A9,							undef,
	0x1AB..0x1AE,0x1B0,         0x1B2..0x1B3,														undef,
	0x1B5..0x1BF,0x1C6..0x1CB,																undef,
	0x1CD..0x1D1,0x1D4,         0x1D7..0x1DC,														undef,
	0x1DE,       0x1E0,         0x1E3,         0x1E5..0x1E6,												undef,
	0x1E8..0x1E9,0x1EB..0x1EC,  0x1EE..0x1F0,  0x1F2..0x1F3,  0x1F5..0x1F7,							undef,
	0x1F9,       0x1FB,
	],      [0x3,0x6,0xC,0xD,0xF,0x10,0x11,0x16,0x1A,0x1F,0x21,0x25,0x27,0x28,0x2C,0x2D,0x2E,0x2F,0x30,0x32,0x35,0x36,0x37,0x38,0x40,0x41,0x42,0x46,0x47,0x4A,0x4B,0x4E,0x53,0x55,0x57,0x58,0x59,0x5C,0x62,0x63,0x65,0x69,0x6C,0x6F,0x70,0x72,0x75,0x77,0x7E,0x81,0x82,0x86,0x87,0x8A,0x8B,0x8C,0x91,0x9A,0x9E,0x9F,0xA9,0xAA,0xAB,0xAE,0xAF,0xB3,0xB5,0xB8,0xBE,0xC0,0xC1,0xC6,0xC8,0xCA,0xCF,0xD1,0xD6,0xD9,0xDB,0xDE,0xE0,0xE6,0xED,0xFC,0x105,0x107,0x108,0x10D,0x112,0x114,0x118,0x123,0x128,0x12E,0x12F,0x130,0x131,0x133,0x135,0x139,0x13E,0x13F,0x140,0x142,0x144,0x146,0x153,0x15C,0x15E,0x15F,0x169,0x16B,0x17F,0x181,0x183,0x190,0x192,0x193,0x197,0x19D,0x1A1,0x1A8,0x1AA,0x1AE,0x1B8,0x1B9,0x1BB,0x1BD,0x1C0,0x1CE,0x1CF,0x1D5,0x1D7,0x1D8,0x1D9,0x1DD,0x1DF,0x1E9,0x1EB,0x1F4,0x1FD],
	[	#76	EPIGEN: 1 key
	0x3,         0x5,         0xB,         0xE,         0x10,          0x1B..0x1C,    0x23,          0x28..0x29,					undef,
	0x2E,        0x35,        0x39,        0x42,        0x44,          0x48,          0x50,          0x52,							undef,
	0x56..0x57,  0x5B,        0x69..0x6A,  0x72..0x73,  0x77,          0x7A..0x7B,    0x7D..0x7E,    0x80,				undef,
	0x83..0x84,  0x8B,        0x8D,        0x92,        0x96,          0xA6,          0xA8,          0xAE,						undef,
	0xB4,        0xB6,        0xB9,        0xBB,        0xC1,          0xC4,          0xC6,          0xC8,						undef,
	0xD1,        0xD4,        0xDA,        0xDC,        0xE3,          0xEC,          0xF4,          0xF7..0xF8,					undef,
	0xFA,        0x101,       0x103..0x104,0x10C,       0x10E,         0x110,         0x112,         0x117..0x118,			undef,
	0x11A,       0x11D,       0x121,       0x123,       0x125,         0x12B..0x12C,  0x138,         0x13A..0x13B,			undef,
	0x13F,       0x143,       0x148..0x149,0x14F..0x150,0x153,         0x158..0x15A,  0x15D,         0x163,				undef,
	0x165..0x167,0x16B,       0x16D..0x16F,0x172..0x173,0x177,         0x17B,         0x187,         0x18B,			undef,
	0x18F,       0x198..0x19B,0x1A4,       0x1A6,       0x1A9..0x1AA,  0x1AC..0x1AD,  0x1AF,         0x1B3..0x1B4,		undef,
	0x1B6,       0x1B8,       0x1BB,       0x1BD..0x1BE,0x1C8,         0x1CA,         0x1CD..0x1CF,  0x1D6..0x1D7,		undef,
	0x1DC,       0x1E1,       0x1E6,       0x1EA..0x1ED,0x1F1,         0x1F3,         0x1F5..0x1F6,  0x1F8,				undef,
	0x1FA,
	],      [0x2,0x3,0xB,0xD,0xE,0x10,0x11,0x12,0x19,0x1C,0x26,0x27,0x29,0x40,0x41,0x43,0x44,0x45,0x46,0x4A,0x4D,0x50,0x51,0x53,0x54,0x56,0x58,0x5B,0x5C,0x5D,0x6A,0x6D,0x6F,0x70,0x71,0x74,0x75,0x7D,0x7F,0x84,0x85,0x88,0x8A,0x91,0x95,0x96,0x9D,0x9F,0xA1,0xA7,0xAA,0xAE,0xB1,0xB5,0xB8,0xB9,0xBB,0xBE,0xC0,0xC3,0xC9,0xCA,0xD1,0xD3,0xD8,0xE3,0xE6,0xE7,0xED,0xF4,0xF7,0xFA,0xFC,0x102,0x107,0x10A,0x10E,0x117,0x119,0x11A,0x11B,0x125,0x126,0x128,0x130,0x131,0x134,0x13D,0x141,0x142,0x143,0x144,0x145,0x154,0x155,0x158,0x159,0x16A,0x16F,0x170,0x171,0x172,0x174,0x176,0x179,0x183,0x186,0x189,0x18A,0x18C,0x18E,0x193,0x194,0x195,0x19B,0x1A4,0x1AF,0x1B2,0x1B6,0x1BE,0x1C1,0x1C4,0x1C5,0x1C8,0x1C9,0x1CA,0x1CB,0x1CD,0x1CE,0x1D0,0x1DC,0x1DD,0x1E4,0x1EB,0x1EC,0x1F3,0x1F4,0x1F5,0x1F6,0x1FD,0x1FE],
	[	#77	EPIGEN: 1 key					targets the iC==zC INTERLOC case of _set()
	0x0..0x1,    0x5,         0x7..0xB,    0xE,         0x11..0x19,    0x1B,          0x1E,          0x21,						undef,
	0x25..0x27,  0x2B..0x2E,  0x31,        0x35,        0x3D..0x3F,    0x41..0x42,    0x44,          0x49,					undef,
	0x4B..0x4D,  0x4F,        0x52,        0x54,        0x56..0x58,    0x61,          0x64..0x67,    0x69..0x6A,				undef,
	0x6D..0x6F,  0x71,        0x74,        0x77..0x78,  0x7E..0x82,    0x87..0x8B,    0x8E..0x8F,    0x91..0x93,			undef,
	0x95,        0x99..0x9C,  0x9E,        0xA0..0xA1,  0xA3..0xA4,    0xA6,          0xA8,          0xAC..0xAE,			undef,
	0xB0,        0xB2..0xB3,  0xB6,        0xB9,        0xBC..0xBD,    0xC0..0xC3,    0xC5..0xC6,    0xC8..0xCA,			undef,
	0xCC..0xCD,  0xCF,        0xD2,        0xD4,        0xD7..0xDA,    0xDC,          0xE1..0xE3,    0xE8..0xE9,			undef,
	0xEE..0xF0,  0xF2..0xF5,  0xF8..0xFE,  0x101,       0x105,         0x107,         0x10B,         0x10E..0x10F,			undef,
	0x111..0x112,0x115,       0x118..0x11A,0x11D..0x11E,0x122,         0x125..0x12A,  0x12C..0x12E,  0x130,		undef,
	0x135,       0x139,       0x13C..0x13D,0x141,       0x143..0x144,  0x147,         0x14A,         0x14D,				undef,
	0x153,       0x15A,       0x15C..0x15F,0x161,       0x164..0x165,  0x169,         0x16B..0x16C,  0x16F,				undef,
	0x174..0x176,0x178..0x17A,0x180,       0x182..0x184,0x186,         0x188,         0x18B..0x18C,  0x18E,			undef,
	0x191..0x194,0x197,       0x19B,       0x1A3,       0x1A5..0x1A6,  0x1AA..0x1AE,  0x1B3,         0x1B5..0x1B6,		undef,
	0x1BA,       0x1BD,       0x1BF,       0x1C4..0x1C6,0x1C8,         0x1CA..0x1CF,  0x1D5,         0x1DA,				undef,
	0x1DF,       0x1E2,       0x1E4,       0x1E7,       0x1EA..0x1EB,  0x1ED,         0x1EF,         0x1F3..0x1F4,			undef,
	0x1F7,

	],      [0x0,0x1,0x4,0x7,0x8,0x9,0xA,0xC,0xD,0x12,0x14,0x15,0x16,0x17,0x19,0x1A,0x1B,0x21,0x23,0x26,0x29,0x2A,0x2B,0x2D,0x2E,0x31,0x33,0x37,0x39,0x3A,0x3B,0x3F,0x43,0x44,0x46,0x47,0x4B,0x4D,0x4F,0x52,0x53,0x55,0x58,0x5A,0x5B,0x5C,0x5F,0x64,0x69,0x6A,0x6F,0x70,0x71,0x73,0x79,0x7A,0x82,0x84,0x86,0x87,0x8A,0x8B,0x8C,0x8E,0x91,0x94,0x96,0x99,0x9A,0x9B,0x9D,0x9E,0x9F,0xA1,0xA3,0xA6,0xA7,0xA8,0xAB,0xAC,0xB0,0xB2,0xB4,0xB7,0xB9,0xBA,0xBB,0xBC,0xC0,0xC2,0xC3,0xC5,0xC6,0xC7,0xC8,0xC9,0xCC,0xCD,0xD2,0xD5,0xD7,0xD9,0xDB,0xE0,0xE6,0xE7,0xE8,0xEC,0xEE,0xEF,0xF0,0xF4,0xF5,0xF8,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,0x100,0x102,0x104,0x106,0x109,0x10A,0x10B,0x10F,0x112,0x115,0x116,0x117,0x119,0x11A,0x11C,0x11D,0x11E,0x120,0x121,0x122,0x123,0x127,0x128,0x129,0x12C,0x12E,0x12F,0x130,0x132,0x138,0x13D,0x141,0x142,0x144,0x145,0x146,0x148,0x14A,0x14E,0x14F,0x150,0x152,0x153,0x154,0x155,0x156,0x15A,0x15B,0x15C,0x15D,0x15E,0x162,0x163,0x164,0x166,0x16B,0x171,0x173,0x174,0x175,0x176,0x179,0x17A,0x17B,0x17D,0x17F,0x181,0x182,0x185,0x188,0x189,0x18A,0x18B,0x18C,0x18D,0x18E,0x196,0x198,0x199,0x19A,0x19D,0x1A1,0x1A4,0x1A6,0x1A7,0x1AC,0x1AE,0x1B0,0x1B4,0x1B7,0x1B9,0x1BC,0x1BD,0x1C0,0x1C2,0x1C4,0x1C6,0x1C8,0x1CB,0x1CE,0x1CF,0x1D0,0x1D3,0x1D4,0x1D7,0x1D9,0x1DA,0x1DB,0x1DC,0x1DF,0x1E0,0x1E6,0x1E7,0x1EA,0x1EF,0x1F2,0x1F3,0x1F8,0x1FB,0x1FD,0x1FE],
#	);@precursors=(
	[	#78/ 0:	NX1						hand-crafted, targets  _sv_commit_nx case NX1
	1..4, 111..112, 211, 222,240,260..280, 940, 1060,
	1080, 1099..1100, 1111..1113, 2100..2110, 2200..2222, 2300..2340, 2345..2460, 2598,
	2600..2650, 2660..2666, 2668, 2690, 2749, 2802, undef,
	2804..2824, 2826, undef,
	2828, 2968, undef,
	2970, 3003..4004, 5005..6006, undef,
	7000, 7700..7777, 8000, 8800..8888, 9000
	], [ 2755, 2825 ],
	[	#79/ 1:	NX2L					lhand-crafted to trigger _sv_commit_nx case NX2L
#	2026-09-03
#	For teh past 3 days, I went around and around in circles diagnosing MOD_CUBE_Z_AS_MODSxHPASS,
#	rewriting CoINTERLOC and CoEPILOC twice,
#	injecting gratuitous debug messages in all DeICE* macros,
#	all because I forgot that ReINTERLOC[¹] does not call SvPVbyte.
#	Variant created.
#
#	NOTES: on MOD_CUBE_Z_AS_MODSxHPASS
#	After all this deliberation, it occurs to me that the correct vector to take the top index of pre_q / pre_xc is (ixH-1). 
#	ixM, izM, inM and ixH all track the modification range in the vector map.
#	ixM..izM is the range itself; inM is always izM+1, the high boundary.
#	ixH is nuanced: this is the starting vector for the highpass region, and even though highpass always follows mods,
#	it is possible that one or more ending vectors of the mod range get deleted or integrated post-op, causing izM and inM to decrease.
#	So, the only safe pre-op measurement for the final index of the mod range is ixH-1.

	1..4, 111..112, 211, 222,240,260..280, 940, 1060,
	1080, 1099..1100, 1111..1113, 2100..2110, 2200..2222, 2300..2340, 2345..2460, 2598,
	2600..2650, 2660..2666, 2668, 2690, 2749, 2802, undef,
	2804..2824, 2826, undef,
	2828, 2968, undef,
	2970, 3003..4004, 5005..6006, 6060, 6066, 6600, 6606, 6666, undef,
	7000, 7700..7777, 8000, 8800..8888, 9000
	], [2829, 2969],
	[	#80/ 2:	NX2H					hand-crafted, targets  _sv_commit_nx case NX2H
	1..4, 111..112, 211, 222,240,260..280, 940, 1060,
	1080, 1099..1100, 1111..1113, 2100..2110, 2200..2222, 2300..2340, 2345..2460, 2598,
	2600..2650, 2660..2666, 2668, 2690, 2749, 2802, 2804..2824, 2826,
	2828, 2968, undef,
	2970, 3003..4004, 5005..6006, undef,
	7000, 7700..7777, 8000, 8800..8888, 9000
	], [ 2755, 2827 ],
	[	#81/ 3:	NX2M					hand-crafted, targets _sv_commit_nx case NX2M where cube run is >2 (3 in this case)
	1..4, 111..112, 211, 222,240,260..280, 940, 1060,
	1080, 1099..1100, 1111..1113, 2100..2110, 2200..2222, 2300..2340, 2345..2460, 2598,
	2600..2650, 2660..2666, 2668, 2690, 2749, 2802, undef,
	2804..2824, 2826, undef,
	2828, 2968, undef,
	2970, 3003..4004, 5005..6006, undef,
	7000, 7700..7777, 8000, 8800..8888, 9000
	], [ 2755, 2777, 2780, 2790, 2800, 2825, 2827, 2882 ],	#2755 2777 2780 2790 2800 2825 2827 2882
	[	#82/ 4:	NX3-@					crafted to hit NX3c
	0		..7,			10		..15,			20		..27,			30		..36,			40		..47,			50		..58,			60		..67,			72		..75,	
	100		..107,		110		..116,		120		..127,		130		..138,		140		..147,		150		..155,		160		..167,		170		..176,
	180		..187,		210		..215,		220		..227,		230		..236,		240		..247,		250		..258,		260		..267,		270		..275,
	300		..306,		310		..317,		320		..328,		330		..337,		340		..345,		350		..357
	], [ 59, 118 ],
	[	#83/ 5:	NX3-B					crafted to hit NX3c w/ a merge operation where u and v cointerlocate cubes 0 & 1 and rel_c is non-zero
		# This was an interesting one!  I had to add a special conditional modifier for ocª after the CoINTRaLOC macro:
		#
		# 	if( x==E[ u ] &&A[v]==1 )	ocª=xc; else ocª=xcª+1;
		#
		# It's the same test as set()'s merge operation, but here, the co-intralocation condition is implicitly true.
		# I'm still thinking about whether this is really the best arrangement for branch prediction, however.
		#
#	0		..7,			10		..15,			20		..27,			30		..36,			40		..47,			50		..58,			60		..67,			72		..75,	
#	77		..99,			100		..111,		200		..222,		300		..333,		400		..414,		500		..555,		600		..666,		700		..777,
#	900		..999,		1000	..1111,		1200	..1222,		1300	..1333,		1400	..1444,		1500	..1555,		1600	..1666,		1700	..1777,
#	1900	..1999,		2000	,,2111,		2200	..2222,		2300	..2333,		2400	..2444,		2500	..2555,		2600	..2666,		2700	..2777,
#	2900	..2999,		3000	..3111,		3200	..3222,		3300	..3333,		3400	..3444,		3500	..3555,		3600	..3666,		3700	..3777,
#	3900	..3999,		4000	..4111,		4200	..4222,		4300	..4333,		4400	..4444,		4500	..4555,		4600	..4666,		4700	..4777,
	0x0..0x7,      0xA..0xF,      0x14..0x1B,    0x1E..0x24,    0x28..0x2F,    0x32..0x3A,    0x3C..0x43,     0x48..0x4B,
	0x4D..0x6F,    0xC8..0xDE,    0x12C..0x14D,  0x190..0x19E,  0x1F4..0x22B,  0x258..0x29A,  0x2BC..0x309,   0x384..0x457,
	0x4B0..0x4C6,  0x514..0x535,  0x578..0x5A4,  0x5DC..0x613,  0x640..0x682,  0x6A4..0x6F1,  0x76C..0x7D0,   0x83F,
	0x898..0x8AE,  0x8FC..0x91D,  0x960..0x98C,  0x9C4..0x9FB,  0xA28..0xA6A,  0xA8C..0xAD9,  0xB54..0xC27,   0xC80..0xC96,
	0xCE4..0xD05,  0xD48..0xD74,  0xDAC..0xDE3,  0xE10..0xE52,  0xE74..0xEC1,  0xF3C..0x100F, 0x1068..0x107E, 0x10CC..0x10ED,
	0x1130..0x115C,0x1194..0x11CB,0x11F8..0x123A,0x125C..0x12A9,
	], [18, 28, 38, 76 ],
	[	#84/ 6:	NX3-@					crafted to hit NX3c w/ cubeΩ as mods & hipass
	0		..7,			10		..15,			20		..27,			30		..36,			40		..47,			50		..58,			60		..67,			72		..75,	
	90		..99,			100		..111,		200		..222,		300		..333,		400		..444,		500		..555,		600		..666,		700		..777,
	900		..999,		1000	..1111,		1200	..1222,		1300	..1333,		1400	..1444,		1500	..1555,		1600	..1666,		1700	..1777,
	1900	..1999,		2000	,,2111,		2200	..2222,		2300	..2333,		2400	..2444,		2500	..2555,		2600	..2666,		2700	..2777,
	2900	..2999,		3000	..3111,		3200	..3222,		3300	..3333,		3400	..3444,		3500	..3555,		3600	..3666,		3700	..3777,
	3900	..3999,		4000	..4111,		4200	..4222,		4300	..4333,		4400	..4444,		4500	..4555,		4600	..4666,		4700	..4777,

	], [38, 233],
	[	#85/ 7:	NX4-CC
#	0		..7,			10		..15,			20		..27,			30		..36,			40		..47,			50		..58,			60		..67,			72		..75,	
#	77		..99,			100		..111,		200		..222,		300		..333,		400		..414,		500		..555,		600		..666,		700		..777,
#	900		..999,		1000	..1111,		1200	..1222,		1300	..1333,		1400	..1444,		1500	..1555,		1600	..1666,		1700	..1777,
#	1900	..1999,		2000	,,2111,		2200	..2222,		2300	..2333,		2400	..2444,		2500	..2555,		2600	..2666,		2700	..2777,
#	2900	..2999,		3000	..3111,		3200	..3222,		3300	..3333,		3400	..3444,		3500	..3555,		3600	..3666,		3700	..3777,
#	3900	..3999,		4000	..4111,		4200	..4222,		4300	..4333,		4400	..4444,		4500	..4555,		4600	..4666,		4700	..4777,
	0x0..0x7,      0xA..0xF,      0x14..0x1B,    0x1E..0x24,    0x28..0x2F,    0x32..0x3A,    0x3C..0x43,     0x48..0x4B,
	0x4D..0x6F,    0xC8..0xDE,    0x12C..0x14D,  0x190..0x19E,  0x1F4..0x22B,  0x258..0x29A,  0x2BC..0x30A,   0x386..0x4A2,
	0x4B0..0x4C6,  0x514..0x535,  0x578..0x5A4,  0x5DC..0x613,  0x640..0x682,  0x6A4..0x6F1,  0x76C..0x7D0,   0x83F,
	0x898..0x8AE,  0x8FC..0x91D,  0x960..0x98C,  0x9C4..0x9FB,  0xA28..0xA6A,  0xA8C..0xAD9,  0xB54..0xC27,   0xC80..0xC96,
	0xCE4..0xD05,  0xD48..0xD74,  0xDAC..0xDE3,  0xE10..0xE52,  0xE74..0xEC1,  0xF3C..0x100F, 0x1068..0x107E, 0x10CC..0x10ED,
	0x1130..0x115C,0x1194..0x11CB,0x11F8..0x123A,0x125C..0x12A9,
	], [ 69, 76, 114, 116, 118, 120, 122, 124, 444 ],
	[	#86/ 8:	NX4-CB					fixed a bug I introduced yesterday with computing ocª 
	0		..7,			10		..15,			20		..27,			30		..36,			40		..47,			50		..58,			60		..67,			72		..75,	
	77		..99,			100		..111,		200		..222,		300		..333,		400		..414,		500		..555,		600		..666,		700		..777,
	900		..999,		1000	..1111,		1200	..1222,		1300	..1333,		1400	..1444,		1500	..1555,		1600	..1666,		1700	..1777,
	1900	..1999,		2000	,,2111,		2200	..2222,		2300	..2333,		2400	..2444,		2500	..2555,		2600	..2666,		2700	..2777,
	2900	..2999,		3000	..3111,		3200	..3222,		3300	..3333,		3400	..3444,		3500	..3555,		3600	..3666,		3700	..3777,
	3900	..3999,		4000	..4111,		4200	..4222,		4300	..4333,		4400	..4444,		4500	..4555,		4600	..4666,		4700	..4777,
	], [ 38, 69, 71, 113, 115, 120, 130, 140, 150, 333, 678, 800, 888, 1122, 1144 ],
	[	#87/ 9:	NX4-CC					no bug, just wanted to target it
	0		..7,			10		..15,			20		..27,			30		..36,			40		..47,			50		..58,			60		..67,			72		..75,	
	77		..99,			100		..111,		200		..222,		300		..333,		400		..414,		500		..555,		600		..666,		700		..777,
	900		..999,		1000	..1111,		1200	..1222,		1300	..1333,		1400	..1444,		1500	..1555,		1600	..1666,		1700	..1777,
	1900	..1999,		2000	,,2111,		2200	..2222,		2300	..2333,		2400	..2444,		2500	..2555,		2600	..2666,		2700	..2777,
	2900	..2999,		3000	..3111,		3200	..3222,		3300	..3333,		3400	..3444,		3500	..3555,		3600	..3666,		3700	..3777,
	3900	..3999,		4000	..4111,		4200	..4222,		4300	..4333,		4400	..4444,		4500	..4555,		4600	..4666,		4700	..4777,
	], [ 140, 150, 152, 154, 156, 158, 345, 357, 678, 789, 800, 888, 1122, 1144 ],
	[	#88/10:	NX4-CC 	EPIGEN: 2 keys	"cube #18 STRLEN error.     ( computed: 19  stored: 100  )"
#	0xFFFFFFFFFFF801, 0xFFFFFFFFFFF816, 0xFFFFFFFFFFF883, 0xFFFFFFFFFFF8BE,  0xFFFFFFFFFFF8DA,                      0xFFFFFFFFFFF94B,									undef,
#	0xFFFFFFFFFFF959, 0xFFFFFFFFFFF967, 0xFFFFFFFFFFF988, 0xFFFFFFFFFFF997,  0xFFFFFFFFFFF9A6,                      0xFFFFFFFFFFF9AD,									undef,
#	0xFFFFFFFFFFF9CA, 0xFFFFFFFFFFF9DA, 0xFFFFFFFFFFF9F3, 0xFFFFFFFFFFFA12,  0xFFFFFFFFFFFA45,                      0xFFFFFFFFFFFA49,  0xFFFFFFFFFFFA4E,					undef,
#	0xFFFFFFFFFFFA71, 0xFFFFFFFFFFFAAF, 0xFFFFFFFFFFFAC5, 0xFFFFFFFFFFFAF9,  0xFFFFFFFFFFFB23,                      0xFFFFFFFFFFFB31,  0xFFFFFFFFFFFB49,					undef,
#	0xFFFFFFFFFFFB93, 0xFFFFFFFFFFFC13, 0xFFFFFFFFFFFC2C, 0xFFFFFFFFFFFC58,  0xFFFFFFFFFFFC76,                      0xFFFFFFFFFFFC92,  0xFFFFFFFFFFFCA7,					undef,
#	0xFFFFFFFFFFFD7D, 0xFFFFFFFFFFFD94, 0xFFFFFFFFFFFDA2, 0xFFFFFFFFFFFDC9,  0xFFFFFFFFFFFE39,                      0xFFFFFFFFFFFE48,  0xFFFFFFFFFFFEAB,					undef,
#	0xFFFFFFFFFFFEB9, 0xFFFFFFFFFFFEC9, 0xFFFFFFFFFFFEE2, 0xFFFFFFFFFFFF71,  0xFFFFFFFFFFFF95,                      0xFFFFFFFFFFFF9B,  0xFFFFFFFFFFFFCC,					undef,
#	0xFFFFFFFFFFFFD4, 0xFFFFFFFFFFFFEA, 0x100000000000025,0x100000000000051, 0x100000000000074,                     0x10000000000008D, 0x1000000000000B2,		undef,
#	0x100000000000111,0x100000000000150,0x100000000000167,0x1000000000001FA, 0x100000000000216,                     0x100000000000244, 0x100000000000274,	undef,
#	0x100000000000286,0x1000000000002BF,0x1000000000002F5,0x100000000000316, 0x10000000000032A,                     0x10000000000039A, 0x1000000000003E1,	undef,
	0x1000000000003F1,0x1000000000003F4,0x1000000000004ED,0x1000000000004F8, 0x100000000000506..0x100000000000507,								undef,
	0x100000000000552,0x10000000000057B,0x100000000000598,0x1000000000005D2, 0x100000000000609,												undef,
	0x100000000000684,0x100000000000689,0x1000000000006A6,0x1000000000006E8,																	undef,
	0x1000000000006FB,0x100000000000721,0x10000000000075A,0x1000000000007D5, 0x1000000000007E1
	],      [
	#	0xFFFFFFFFFFF82C,0xFFFFFFFFFFF8E9,0xFFFFFFFFFFF8F5,0xFFFFFFFFFFF907,0xFFFFFFFFFFF920,0xFFFFFFFFFFF97D,0xFFFFFFFFFFFA40,0xFFFFFFFFFFFAED,0xFFFFFFFFFFFB5E,0xFFFFFFFFFFFC3E,0xFFFFFFFFFFFCA2,0xFFFFFFFFFFFCAF,0xFFFFFFFFFFFD00,0xFFFFFFFFFFFDC2,0xFFFFFFFFFFFE4A,0xFFFFFFFFFFFE53,0xFFFFFFFFFFFE6A,0xFFFFFFFFFFFEAD,0xFFFFFFFFFFFED4,0xFFFFFFFFFFFF9F,0x10000000000000D,0x1000000000000CC,0x100000000000112,0x100000000000116,0x100000000000191,0x100000000000208,0x100000000000213,0x1000000000002F1,
		0x1000000000004E6,0x1000000000004EC,0x100000000000574,0x100000000000597,0x1000000000005AC,0x1000000000005E4,0x1000000000005EC,0x1000000000005F6,0x10000000000060F,0x100000000000638,0x10000000000063D,0x1000000000006AC,0x10000000000074E,0x100000000000757,0x1000000000007E4,0x1000000000007F4],
	[	#89/11:	
#	0xFFFFFFFFFFF807,                    0xFFFFFFFFFFF818,                    0xFFFFFFFFFFF81D, 0xFFFFFFFFFFF827,  0xFFFFFFFFFFF83B,  0xFFFFFFFFFFF841,                      0xFFFFFFFFFFF86B,		undef,
#	0xFFFFFFFFFFF872,                    0xFFFFFFFFFFF89C,                    0xFFFFFFFFFFF8CB, 0xFFFFFFFFFFF8DB,  0xFFFFFFFFFFF8E7,  0xFFFFFFFFFFF8EE,                      0xFFFFFFFFFFF936,		undef,
#	0xFFFFFFFFFFF93C..0xFFFFFFFFFFF93D,  0xFFFFFFFFFFF94C,                    0xFFFFFFFFFFF965, 0xFFFFFFFFFFF972,  0xFFFFFFFFFFF9AC,  0xFFFFFFFFFFF9FC,                      0xFFFFFFFFFFFA20,		undef,
#	0xFFFFFFFFFFFA91,                    0xFFFFFFFFFFFAA9,                    0xFFFFFFFFFFFAD1, 0xFFFFFFFFFFFAEB,  0xFFFFFFFFFFFB23,  0xFFFFFFFFFFFB3D,                      0xFFFFFFFFFFFB60,		undef,
#	0xFFFFFFFFFFFB6B,                    0xFFFFFFFFFFFB78,                    0xFFFFFFFFFFFB94, 0xFFFFFFFFFFFBC5,  0xFFFFFFFFFFFBCE,  0xFFFFFFFFFFFBDB,		undef,
#	0xFFFFFFFFFFFBF0,                    0xFFFFFFFFFFFC09,                    0xFFFFFFFFFFFC5B, 0xFFFFFFFFFFFC7E,  0xFFFFFFFFFFFCA5,  0xFFFFFFFFFFFCA9,		undef,
#	0xFFFFFFFFFFFCE8,                    0xFFFFFFFFFFFD54..0xFFFFFFFFFFFD55,  0xFFFFFFFFFFFD6C, 0xFFFFFFFFFFFD7E,  0xFFFFFFFFFFFD83,  0xFFFFFFFFFFFDA0,                      0xFFFFFFFFFFFDA3,		undef,
#	0xFFFFFFFFFFFDAA,                    0xFFFFFFFFFFFDBC,                    0xFFFFFFFFFFFDD2, 0xFFFFFFFFFFFE07,  0xFFFFFFFFFFFE10,  0xFFFFFFFFFFFE46,                      0xFFFFFFFFFFFEA3,		undef,
#	0xFFFFFFFFFFFEB6,                    0xFFFFFFFFFFFEC8,                    0xFFFFFFFFFFFEE8, 0xFFFFFFFFFFFF09,  0xFFFFFFFFFFFF1C,  0xFFFFFFFFFFFF20,		undef,
	0xFFFFFFFFFFFF62,                    0xFFFFFFFFFFFF6F,                    0xFFFFFFFFFFFF82, 0xFFFFFFFFFFFFCC,  0xFFFFFFFFFFFFD3,  0xFFFFFFFFFFFFE7,		undef,
	0x100000000000002,                   0x10000000000005C,                   0x1000000000000AE,0x1000000000000C7, 0x1000000000000ED, 0x1000000000000F5,                     0x100000000000111,		undef,
	0x100000000000115,                   0x10000000000013B,                   0x100000000000190,0x1000000000001CC, 0x1000000000001FA, 0x100000000000203,                     0x100000000000222,		undef,
	0x100000000000227,                   0x100000000000247,                   0x100000000000289,0x1000000000002A4, 0x1000000000002B4, 0x10000000000030A,                     0x10000000000031B,		undef,
	0x100000000000351,                   0x10000000000038D,                   0x1000000000003D2,0x1000000000003DB, 0x1000000000003F6, 0x100000000000404,                     0x100000000000450,		undef,
	0x100000000000480,                   0x100000000000484,                   0x10000000000048D,0x100000000000496, 0x1000000000004C7, 0x1000000000004D5,                     0x1000000000004E1,		undef,
	0x1000000000004ED,                   0x10000000000050E,                   0x10000000000052E,0x100000000000570, 0x10000000000057A, 0x1000000000005AB..0x1000000000005AC,  0x1000000000005C1,		undef,
	0x100000000000609,                   0x100000000000651..0x100000000000652,0x100000000000657,0x100000000000677, 0x100000000000688, 0x100000000000690,                     0x10000000000069F,		undef,
	0x1000000000006C9,                   0x1000000000006CE,                   0x1000000000006E4,0x100000000000728, 0x100000000000749,		undef,
	0x10000000000075D,                   0x100000000000789,                   0x1000000000007AF,0x1000000000007C8, 0x1000000000007D7

	],      [#0xFFFFFFFFFFF84C,0xFFFFFFFFFFF899,0xFFFFFFFFFFF8C4,0xFFFFFFFFFFF9A0,0xFFFFFFFFFFF9CB,0xFFFFFFFFFFFB53,0xFFFFFFFFFFFB7D,0xFFFFFFFFFFFB8A,0xFFFFFFFFFFFBBD,0xFFFFFFFFFFFC0B,0xFFFFFFFFFFFCB4,0xFFFFFFFFFFFCBD,0xFFFFFFFFFFFCC9,0xFFFFFFFFFFFD48,0xFFFFFFFFFFFD83,0xFFFFFFFFFFFD84,0xFFFFFFFFFFFDD6,0xFFFFFFFFFFFE2E,0xFFFFFFFFFFFE95,0xFFFFFFFFFFFE98,
		0xFFFFFFFFFFFF69,0xFFFFFFFFFFFFAD,0x10000000000009B,0x10000000000009D,0x1000000000000AE,0x1000000000000CD,0x100000000000174,0x100000000000196,0x1000000000001FA,0x10000000000023E,0x10000000000031C,0x100000000000325,0x1000000000004C8,0x10000000000051B,0x10000000000052B,0x100000000000581,0x100000000000589,0x100000000000590,0x10000000000062E,0x100000000000667,0x100000000000699,0x10000000000073F,0x100000000000765,0x10000000000076B],
	[	#90/12:	1X2M	EPIGEN: 1 key
	0xFFFFFFFFFFF80D, 0xFFFFFFFFFFF81E, 0xFFFFFFFFFFF8A7, 0xFFFFFFFFFFF8DF,  0xFFFFFFFFFFF8FF,  0xFFFFFFFFFFF913,  0xFFFFFFFFFFF93B,  0xFFFFFFFFFFF972,
	0xFFFFFFFFFFF978, 0xFFFFFFFFFFFAF8, 0xFFFFFFFFFFFB01, 0xFFFFFFFFFFFB0F,  0xFFFFFFFFFFFB23,  0xFFFFFFFFFFFBAE,  0xFFFFFFFFFFFC21,  0xFFFFFFFFFFFC35,
	0xFFFFFFFFFFFC53, 0xFFFFFFFFFFFC7F, 0xFFFFFFFFFFFD78, 0xFFFFFFFFFFFDC4,  0xFFFFFFFFFFFE75,  
#	0xFFFFFFFFFFFE9F,  0xFFFFFFFFFFFED7,  0xFFFFFFFFFFFF3D,
#	0xFFFFFFFFFFFFAE, 0xFFFFFFFFFFFFFB, 0x100000000000044,0x100000000000072, 0x10000000000016C, 0x1000000000001B1, 0x100000000000292, 0x1000000000002EE,
#	0x100000000000340,0x100000000000403,0x100000000000424,0x10000000000047F, 0x1000000000004D1, 0x10000000000056A, 0x100000000000590, 0x100000000000616,
#	0x100000000000637,0x1000000000007AF,0x1000000000007DB,0x1000000000007EC,

	],      [	0xFFFFFFFFFFF973,0xFFFFFFFFFFF9E6,
			0xFFFFFFFFFFFA1A,0xFFFFFFFFFFFA4E,0xFFFFFFFFFFFA60,0xFFFFFFFFFFFAA7,0xFFFFFFFFFFFAB7,0xFFFFFFFFFFFAEC,0xFFFFFFFFFFFB6A,0xFFFFFFFFFFFB7E,0xFFFFFFFFFFFBBF,0xFFFFFFFFFFFC18,
			0xFFFFFFFFFFFC7A,0xFFFFFFFFFFFCDB,0xFFFFFFFFFFFCEC,0xFFFFFFFFFFFD31,0xFFFFFFFFFFFD8D,0xFFFFFFFFFFFDFA,0xFFFFFFFFFFFE00,
		#	0xFFFFFFFFFFFE7B,0xFFFFFFFFFFFEAE,0xFFFFFFFFFFFEBD,0xFFFFFFFFFFFEF4,
		#	0xFFFFFFFFFFFF5A,0xFFFFFFFFFFFF6B,0x100000000000022,0x1000000000000B0,0x1000000000000CB,0x10000000000010F,
		#	0x100000000000180,0x1000000000001D0,0x10000000000026A,0x100000000000361,0x10000000000039C,0x1000000000003D8,0x1000000000003DB,0x100000000000428,0x1000000000004FE,0x100000000000544,0x10000000000057B,0x100000000000589,0x10000000000068F,0x1000000000006BC,0x1000000000006BD
			],
	[	#91	
	0xFFFFFFFFFFF816,                    0xFFFFFFFFFFF81E,                    0xFFFFFFFFFFF82A,                    0xFFFFFFFFFFF83C,	undef,
	0xFFFFFFFFFFF85E,                    0xFFFFFFFFFFF88A,                    0xFFFFFFFFFFF890,                    0xFFFFFFFFFFF8B2,  0xFFFFFFFFFFF8B5,	undef,
	0xFFFFFFFFFFF8C6,                    0xFFFFFFFFFFF8D4,
#      0xFFFFFFFFFFF915,                    0xFFFFFFFFFFF919,  0xFFFFFFFFFFF91B,                      0xFFFFFFFFFFF936,                      0xFFFFFFFFFFF960,	undef,
#	0xFFFFFFFFFFF967,                    0xFFFFFFFFFFF969,                    0xFFFFFFFFFFF979,                    0xFFFFFFFFFFF987,  0xFFFFFFFFFFF9AB,                      0xFFFFFFFFFFF9BA,	undef,
#	0xFFFFFFFFFFF9F3,                    0xFFFFFFFFFFF9F8,                    0xFFFFFFFFFFF9FE,                    0xFFFFFFFFFFFA05,  0xFFFFFFFFFFFA1B,                      0xFFFFFFFFFFFA38,	undef,
#	0xFFFFFFFFFFFA46,                    0xFFFFFFFFFFFA55,                    0xFFFFFFFFFFFA87,                    0xFFFFFFFFFFFA98,  0xFFFFFFFFFFFAA1,                      0xFFFFFFFFFFFAB5,                      0xFFFFFFFFFFFACC,	undef,
#	0xFFFFFFFFFFFAD9,                    0xFFFFFFFFFFFAFA,                    0xFFFFFFFFFFFB0E,                    0xFFFFFFFFFFFB2B,  0xFFFFFFFFFFFB30,                      0xFFFFFFFFFFFB32,                      0xFFFFFFFFFFFB53,	undef,
#	0xFFFFFFFFFFFB72..0xFFFFFFFFFFFB73,  0xFFFFFFFFFFFB7B,                    0xFFFFFFFFFFFB80,                    0xFFFFFFFFFFFBAC,  0xFFFFFFFFFFFBB0,                      0xFFFFFFFFFFFBB5,	undef,
#	0xFFFFFFFFFFFBC4,                    0xFFFFFFFFFFFBD2,                    0xFFFFFFFFFFFBD9,                    0xFFFFFFFFFFFC38,  0xFFFFFFFFFFFC43,	undef,
#	0xFFFFFFFFFFFC4A,                    0xFFFFFFFFFFFC4D,                    0xFFFFFFFFFFFC7C,                    0xFFFFFFFFFFFC85,  0xFFFFFFFFFFFC8F..0xFFFFFFFFFFFC90,    0xFFFFFFFFFFFC96,                      0xFFFFFFFFFFFCBF,	undef,
#	0xFFFFFFFFFFFCC3,                    0xFFFFFFFFFFFCCA,                    0xFFFFFFFFFFFCDF,                    0xFFFFFFFFFFFCF9,  0xFFFFFFFFFFFD12,                      0xFFFFFFFFFFFD22,                      0xFFFFFFFFFFFD3A,  0xFFFFFFFFFFFD5A,	undef,
#	0xFFFFFFFFFFFD65,                    0xFFFFFFFFFFFD72,                    0xFFFFFFFFFFFD9B,                    0xFFFFFFFFFFFDA2,  0xFFFFFFFFFFFDA4,                      0xFFFFFFFFFFFDB3,                      0xFFFFFFFFFFFDCF,	undef,
#	0xFFFFFFFFFFFDD5,                    0xFFFFFFFFFFFE0A,                    0xFFFFFFFFFFFE0D..0xFFFFFFFFFFFE0E,  0xFFFFFFFFFFFE21,  0xFFFFFFFFFFFE2E,                      0xFFFFFFFFFFFE30,                      0xFFFFFFFFFFFE41,	undef,
#	0xFFFFFFFFFFFE6B,                    0xFFFFFFFFFFFE8A,                    0xFFFFFFFFFFFE92,                    0xFFFFFFFFFFFEA4,  0xFFFFFFFFFFFEDC..0xFFFFFFFFFFFEDD,    0xFFFFFFFFFFFF0C..0xFFFFFFFFFFFF0E,    0xFFFFFFFFFFFF1B,	undef,
#	0xFFFFFFFFFFFF2E,                    0xFFFFFFFFFFFF93,                    0xFFFFFFFFFFFFA0,                    0xFFFFFFFFFFFFA4,  0xFFFFFFFFFFFFC8,                      0xFFFFFFFFFFFFCE,                      0xFFFFFFFFFFFFEA,	undef,
#	0xFFFFFFFFFFFFEC,                    0xFFFFFFFFFFFFF4,                    0x100000000000020,                   0x100000000000026, 0x100000000000028,                     0x100000000000033,                     0x10000000000003C,	undef,
#	0x10000000000003F,                   0x100000000000048,                   0x10000000000004B,                   0x100000000000061, 0x100000000000071,                     0x10000000000007E,                     0x1000000000000A6,	undef,
#	0x1000000000000B4,                   0x1000000000000BB,                   0x1000000000000C2,                   0x1000000000000CA, 0x10000000000011A,                     0x100000000000125,	undef,
#	0x10000000000012F,                   0x100000000000158,                   0x10000000000015E,                   0x100000000000161, 0x100000000000187,                     0x10000000000018F..0x100000000000190,	undef,
#	0x100000000000196,                   0x10000000000019E,                   0x1000000000001A2,                   0x1000000000001A5, 0x1000000000001A9..0x1000000000001AA,  0x1000000000001B5..0x1000000000001B6,	undef,
#	0x1000000000001BA,                   0x1000000000001FD,                   0x1000000000001FF,                   0x100000000000212, 0x10000000000021D,                     0x100000000000246,	undef,
#	0x10000000000025F,                   0x100000000000274,                   0x10000000000027E,                   0x100000000000284, 0x10000000000029E,	undef,
#	0x1000000000002AA,                   0x1000000000002CC,                   0x1000000000002E0,                   0x1000000000002E5, 0x1000000000002E8,                     0x1000000000002F0,	undef,
#	0x10000000000032C,                   0x10000000000032E,                   0x100000000000333,                   0x100000000000345, 0x10000000000034D,                     0x100000000000353..0x100000000000354,  0x100000000000357, 0x100000000000385,	undef,
#	0x1000000000003C9,                   0x1000000000003D2,                   0x1000000000003DA,                   0x1000000000003DF, 0x1000000000003FD,                     0x100000000000420,	undef,
#	0x100000000000427,                   0x100000000000429,                   0x10000000000042C,                   0x10000000000042F, 0x100000000000450,                     0x10000000000045A,                     0x100000000000473,	undef,
#	0x100000000000485,                   0x1000000000004B1,                   0x1000000000004D5,                   0x10000000000051A, 0x10000000000053F,                     0x10000000000058B,	undef,
#	0x100000000000592,                   0x1000000000005D5,                   0x1000000000005D9,                   0x1000000000005E0, 0x100000000000613,                     0x100000000000619,	undef,
#	0x10000000000061E,                   0x10000000000063C,                   0x100000000000644,                   0x100000000000663, 0x10000000000068E,                     0x1000000000006AB,                     0x1000000000006F9,	undef,
#	0x100000000000705,                   0x100000000000722,                   0x10000000000072A,                   0x10000000000072D, 0x10000000000073D,                     0x10000000000074B,                     0x10000000000075C,	undef,
#	0x100000000000771,                   0x100000000000782..0x100000000000784,0x100000000000789,                   0x1000000000007A5, 0x1000000000007AA,                     0x1000000000007BC,	undef,
#	0x1000000000007BE,                   0x1000000000007C9,                   0x1000000000007DA,                   0x1000000000007DE, 0x1000000000007E4,                     0x1000000000007FF,

	],      [0xFFFFFFFFFFF83C,0xFFFFFFFFFFF847,0xFFFFFFFFFFF84D,0xFFFFFFFFFFF852,0xFFFFFFFFFFF8B1,0xFFFFFFFFFFF8F2,
#		0xFFFFFFFFFFF909,0xFFFFFFFFFFF952,0xFFFFFFFFFFF953,0xFFFFFFFFFFF960,0xFFFFFFFFFFF9A5,0xFFFFFFFFFFFA59,0xFFFFFFFFFFFAA5,0xFFFFFFFFFFFAAF,0xFFFFFFFFFFFAD0,0xFFFFFFFFFFFBE6,0xFFFFFFFFFFFBF6,0xFFFFFFFFFFFC7D,0xFFFFFFFFFFFCCA,0xFFFFFFFFFFFCCC,0xFFFFFFFFFFFD2B,0xFFFFFFFFFFFEC0,0xFFFFFFFFFFFEFC,0xFFFFFFFFFFFF43,0xFFFFFFFFFFFF85,
	#	0xFFFFFFFFFFFFF1,
	#	0x10000000000005F,0x100000000000087,0x1000000000000FB,0x100000000000119,0x10000000000012E,0x1000000000001DF,0x10000000000023D,0x100000000000285,0x1000000000002F8,0x1000000000003BD,0x1000000000004F3,0x10000000000053F,0x100000000000550,0x100000000000602,0x1000000000006A5,0x100000000000750,0x100000000000760,0x1000000000007BC
		],
	[	#92
	0xFFFFFFFFFFF817,                    0xFFFFFFFFFFF81C, 0xFFFFFFFFFFF851,  0xFFFFFFFFFFF878,	undef,
	0xFFFFFFFFFFF87B,                    0xFFFFFFFFFFF8B0, 0xFFFFFFFFFFF8E4,  0xFFFFFFFFFFF8EC,  0xFFFFFFFFFFF91F,	undef,
	0xFFFFFFFFFFF92E,                    0xFFFFFFFFFFF949, 0xFFFFFFFFFFF9A2,  0xFFFFFFFFFFF9F0,  0xFFFFFFFFFFFA29,  0xFFFFFFFFFFFA2B,	undef,
	0xFFFFFFFFFFFA3D,                    0xFFFFFFFFFFFA54, 0xFFFFFFFFFFFA5F,  0xFFFFFFFFFFFA6E,  0xFFFFFFFFFFFA86,  0xFFFFFFFFFFFA92,  0xFFFFFFFFFFFACF,  0xFFFFFFFFFFFB32,	undef,
	0xFFFFFFFFFFFB48,                    0xFFFFFFFFFFFB81, 0xFFFFFFFFFFFB97,  0xFFFFFFFFFFFBAD,  0xFFFFFFFFFFFBD4,  0xFFFFFFFFFFFC09,  0xFFFFFFFFFFFC14,	undef,
	0xFFFFFFFFFFFCBE,                    0xFFFFFFFFFFFCDA, 0xFFFFFFFFFFFCE3,  0xFFFFFFFFFFFD3A,  0xFFFFFFFFFFFDA0,  0xFFFFFFFFFFFDA4,  0xFFFFFFFFFFFDB4,  0xFFFFFFFFFFFE2F,	undef,
	0xFFFFFFFFFFFE59,                    0xFFFFFFFFFFFE7A, 0xFFFFFFFFFFFEA9,  0xFFFFFFFFFFFEBB,  0xFFFFFFFFFFFEC0,  0xFFFFFFFFFFFED9,  0xFFFFFFFFFFFF41,	undef,
	0xFFFFFFFFFFFF49,                    0xFFFFFFFFFFFF4C, 0xFFFFFFFFFFFF6D,  0xFFFFFFFFFFFFA3,  0xFFFFFFFFFFFFD5,  0xFFFFFFFFFFFFE0,	undef,
	0x100000000000000,                   0x100000000000057,0x10000000000008E, 0x1000000000000B8, 0x1000000000000CD, 0x1000000000000D2,	undef,
	0x1000000000000E1..0x1000000000000E2,0x1000000000000EB,0x100000000000124, 0x10000000000012A, 0x100000000000151, 0x100000000000158, 0x100000000000179,	undef,
	0x10000000000018D,                   0x100000000000197,0x1000000000001FE, 0x100000000000203, 0x10000000000022B, 0x10000000000023D, 0x100000000000257, 0x10000000000025D,	undef,
	0x100000000000278,                   0x100000000000297,0x100000000000324, 0x100000000000358, 0x100000000000360, 0x1000000000003AE,	undef,
	0x1000000000003E5,                   0x1000000000003E8,0x1000000000003EA, 0x1000000000003F7, 0x1000000000003FB, 0x10000000000041F,	undef,
	0x100000000000436,                   0x100000000000444,0x100000000000542, 0x100000000000594, 0x1000000000005DF, 0x1000000000005F7,	undef,
	0x10000000000060E,                   0x100000000000629,0x10000000000065D, 0x10000000000066B, 0x100000000000671, 0x1000000000006A6,	undef,
	0x1000000000006A9,                   0x1000000000006CE,0x1000000000006D5, 0x1000000000006FD, 0x100000000000711,	undef,
	0x10000000000072A,                   0x100000000000736,0x1000000000007C8, 0x1000000000007E7, 0x1000000000007FB,

	],      [0xFFFFFFFFFFF925,0xFFFFFFFFFFFBB4,0xFFFFFFFFFFFBE3,0xFFFFFFFFFFFE2E,0xFFFFFFFFFFFE74,0xFFFFFFFFFFFEC4,0xFFFFFFFFFFFFE4,0x10000000000017A,0x1000000000004F4,0x100000000000539,0x10000000000062A,0x1000000000007B0],
	[	#93		introduced during CoEPILOC overhaul, I have to suspect, though it took a long time to brute force, so 
		#		it could have been hiding somewhere for days.
		#		2026-08-31
		#		Spent all day on this.  In 1X3-B¹, I found that when pre¹_xc is 0, rel¹_c and subsequently hp¹_i would be 1 too high.
		#		I noticed in the _print_mx() output that we had (5) new cycla prepended to the high input cube, and they all had I[]==0.
		#		It then occurred to me that a prepended cyclum would logically have a pre-index of -1, so I tried making I[] signed.
		#		This caused problems everywhere.  Signing I[] also halves the effective size of the buffer.
		#		I noticed that hp¹_i would often be negative, which was dangerous considering it was used as a pointer index.
		#		I changed that to a bitwise shift, which I copied from NX3.  While I was there, I decided to copy the interesting line:
		#		pre¹_xc	=	I[	inM	]	-		oc -1;
		#		..which I had commented on earlier, since vector inM is not within the modification range.
		#		Still, this is the only thing that worked.
		#		One very important detail about the conditions of precursor #92 is that the last operation to act on vector ixM
		#		is a union (=+=).  The question becomes, what ought to happen with I[ v ] in a union with I[ u ]?
		#		Clearly I had been on this train of thought before (probably when I wrote NX3), because I had commented out
		#		an experimental line that didn't exist in the backups one month ago, when I started my current attempt
		#		to implement Co/ReINTERLOC.  I tried I[u]=I[v], and that broke precursor #41 (the only one which hit 1X3-B¹). 
		#		I found that 	if( ic==yc ) I[u]=I[v] 	didn't break anything, but I also found that it fired extremely often, and
		#		while the conditional kept it from breaking, it still didn't fix anything.
		#		So, I will have to figure out why the curious pre¹_xc statement, shifting the pre-op mod range up 1, doesn't break.
		#		—not so far, anyway.  I'll be testing.
		#		2026-09-09
		#		Several days ago it clicked; the correct assignment for pre¹_xc is:
		#		pre¹_xc	=	I[	ixH-1 ]	-		oc;
		#		We must use (ixH-1) to identify the highpass boundary rather than (izM) in all "pre-" calculations;
		#		for "post-", (izM) is correct.

	0xFFFFFF6E,              0xFFFFFF77,              0xFFFFFF87,              0xFFFFFF96,              0xFFFFFF9C,                0xFFFFFFAC..0xFFFFFFAD,    0xFFFFFFC8,  0xFFFFFFCB,			undef,
	0x100000033,             0x100000035,             0x100000047,             0x100000057,             0x100000060,               0x100000064,               0x100000085, 0x10000008C,			undef,
	0x100000093,             0x1000000C1,             0x1000000CB,             0x1000000E7,             0x1000000FB,               0x100000133,               0x100000160, 0x100000162,			undef,
	0x100000170,             0x10000017D,             0x1000001D2,             0x1000001DD,             0x1000001E1,               0x1000001FA,               0x10000021D, 0x10000022B,			undef,
	],      [
		0xFFFFFFCB,0xFFFFFFD4,0xFFFFFFD8,0xFFFFFFE8,0xFFFFFFEA,0xFFFFFFEE,0xFFFFFFF6,0xFFFFFFFB,0xFFFFFFFE,0x100000021,
		0x10000002B,0x100000034,0x1000000BA,0x1000000DB,0x100000107,0x100000127,0x10000012C,0x100000140,
		0x100000152,0x10000016A,0x100000179,0x10000017F,0x100000185,0x10000018B,0x10000019F,0x1000001AA,

		],
#	);	@precursors=(
	[	#94/0	MILESTONE: the first brute force precursor generated with ReBAL enabled!
	0xFFFFFFFFFFF80F, 0xFFFFFFFFFFF870, 0xFFFFFFFFFFF880, 0xFFFFFFFFFFF899,  0xFFFFFFFFFFF8C4,                      0xFFFFFFFFFFF8CB,  0xFFFFFFFFFFF8CF,
	0xFFFFFFFFFFF8E7, 0xFFFFFFFFFFF901, 0xFFFFFFFFFFF921, 0xFFFFFFFFFFF92E,  0xFFFFFFFFFFF955,                      0xFFFFFFFFFFF967,  0xFFFFFFFFFFF982,
	0xFFFFFFFFFFF9C9, 0xFFFFFFFFFFF9D4, 0xFFFFFFFFFFF9E3, 0xFFFFFFFFFFF9F0,  0xFFFFFFFFFFFA0A,                      0xFFFFFFFFFFFA10,  0xFFFFFFFFFFFA54,
	0xFFFFFFFFFFFA7A, 0xFFFFFFFFFFFA93, 0xFFFFFFFFFFFAA1, 0xFFFFFFFFFFFAC7,  0xFFFFFFFFFFFAEA,                      0xFFFFFFFFFFFB06,  0xFFFFFFFFFFFB0E,
	0xFFFFFFFFFFFB13, 0xFFFFFFFFFFFB15, 0xFFFFFFFFFFFB37, 0xFFFFFFFFFFFB47,  0xFFFFFFFFFFFB4C,                      0xFFFFFFFFFFFB67,  0xFFFFFFFFFFFB73,
	0xFFFFFFFFFFFB7E, 0xFFFFFFFFFFFC32, 0xFFFFFFFFFFFC3E, 0xFFFFFFFFFFFC72,  0xFFFFFFFFFFFC8F,                      0xFFFFFFFFFFFCAC,  0xFFFFFFFFFFFCB5,
	0xFFFFFFFFFFFCBC, 0xFFFFFFFFFFFCCD, 0xFFFFFFFFFFFCE5, 0xFFFFFFFFFFFCF5,  0xFFFFFFFFFFFD1C,                      0xFFFFFFFFFFFD59,  0xFFFFFFFFFFFDAC,
	0xFFFFFFFFFFFDBB, 0xFFFFFFFFFFFDF2, 0xFFFFFFFFFFFE22, 0xFFFFFFFFFFFE28,  0xFFFFFFFFFFFE2B,                      0xFFFFFFFFFFFE6E,  0xFFFFFFFFFFFE80,
	0xFFFFFFFFFFFE8B, 0xFFFFFFFFFFFEBB, 0xFFFFFFFFFFFECD, 0xFFFFFFFFFFFF15,  0xFFFFFFFFFFFF1A,                      0xFFFFFFFFFFFF38,  0xFFFFFFFFFFFF3A,
	0xFFFFFFFFFFFF54, 0xFFFFFFFFFFFFDA, 0x100000000000006,0x10000000000001D, 0x10000000000002A,                     0x100000000000059, 0x100000000000076,
	0x1000000000000A4,0x1000000000000AD,0x1000000000000D9,0x100000000000104, 0x100000000000151,                     0x100000000000158, 0x10000000000020F,
	0x100000000000223,0x10000000000024A,0x10000000000024D,0x100000000000251, 0x100000000000290,                     0x100000000000299, 0x1000000000002C1,
	0x1000000000002D5,0x1000000000002D8,0x1000000000002DC,0x1000000000002E0, 0x10000000000037C,                     0x100000000000382, 0x100000000000390,
	0x1000000000003B1,0x1000000000003F1,0x100000000000409,0x100000000000462, 0x10000000000046D,                     0x100000000000495, 0x1000000000004AE,
	0x1000000000004D7,0x1000000000004E7,0x1000000000004F4,0x100000000000509, 0x10000000000050D,                     0x100000000000521, 0x100000000000586,
	0x100000000000590,0x1000000000005CB,0x100000000000624,0x10000000000062C, 0x100000000000690..0x100000000000691,  0x10000000000069A, 0x1000000000006AA,
	0x1000000000006B6,0x1000000000006C4,0x1000000000006E0,0x1000000000006E3, 0x1000000000006EF,                     0x1000000000006FD, 0x100000000000748,
	0x10000000000075B,0x100000000000765,0x10000000000079A,0x1000000000007B1, 0x1000000000007D4,                     0x1000000000007F2, 0x1000000000007FD,
	],      [0xFFFFFFFFFFF807,0xFFFFFFFFFFF83A,0xFFFFFFFFFFF87D,0xFFFFFFFFFFF887,0xFFFFFFFFFFF8C0,0xFFFFFFFFFFF9A7,0xFFFFFFFFFFF9EB,0xFFFFFFFFFFFAA0,0xFFFFFFFFFFFAF6,0xFFFFFFFFFFFB1C,0xFFFFFFFFFFFB37,0xFFFFFFFFFFFB55,0xFFFFFFFFFFFB98,0xFFFFFFFFFFFBF5,0xFFFFFFFFFFFC22,0xFFFFFFFFFFFC7E,0xFFFFFFFFFFFD01,0xFFFFFFFFFFFD0F,0xFFFFFFFFFFFE07,0xFFFFFFFFFFFE61,0xFFFFFFFFFFFF24,0xFFFFFFFFFFFF77,0xFFFFFFFFFFFF8F,0x100000000000035,0x100000000000074,0x100000000000076,0x1000000000000CA,0x10000000000011D,0x100000000000178,0x1000000000001CB,0x1000000000001E7,0x100000000000201,0x100000000000211,0x100000000000297,0x1000000000002D8,0x100000000000330,0x10000000000037F,0x1000000000003A7,0x1000000000003B0,0x1000000000003C9,0x1000000000003E2,0x100000000000429,0x10000000000042C,0x1000000000004CE,0x1000000000004D3,0x1000000000004E3,0x100000000000509,0x100000000000557,0x100000000000558,0x10000000000059A,0x1000000000005BB,0x1000000000005CA,0x1000000000005CB,0x10000000000060A,0x100000000000625,0x100000000000634,0x10000000000063E,0x100000000000643,0x100000000000683,0x100000000000695,0x1000000000006B6,0x100000000000748,0x100000000000767,0x100000000000794],
	[	#95/1: a mish mash of sorts
	0		..7,			10		..15,			20		..27,			30		..36,			40		..47,			50		..58,			60		..67,			72		..75,	
	77		..99,			100		..111,		200		..222,		300		..333,		400		..414,		500		..555,		600		..666,		700		..777,
	900		..999,		1000	..1111,		1200	..1222,		1300	..1333,		1400	..1444,		1500	..1555,		1600	..1666,		1700	..1777,
	1900	..1999,		2000	,,2111,		2200	..2222,		2300	..2333,		2400	..2444,		2500	..2555,		2600	..2666,		2700	..2777,
	2900	..2999,		3000	..3111,		3200	..3222,		3300	..3333,		3400	..3444,		3500	..3555,		3600	..3666,		3700	..3777,
	3900	..3999,		4000	..4111,		4200	..4222,		4300	..4333,		4400	..4444,		4500	..4555,		4600	..4666,		4700	..4777,
	], [234, 345, 456, 567, 789, 910, 1020, 2030, 3040, 4050, 5060 ],
	[	#96/2
	0xFFFFFFFFFFF805, 0xFFFFFFFFFFF811,                    0xFFFFFFFFFFF833, 0xFFFFFFFFFFF83B,  0xFFFFFFFFFFF842,                      0xFFFFFFFFFFF875,														undef,
	0xFFFFFFFFFFF89D, 0xFFFFFFFFFFF8D0,                    0xFFFFFFFFFFF8DA, 0xFFFFFFFFFFF8EF,  0xFFFFFFFFFFF8F6,                      0xFFFFFFFFFFF90F,													undef,
	0xFFFFFFFFFFF914, 0xFFFFFFFFFFF91F,                    0xFFFFFFFFFFF935, 0xFFFFFFFFFFF940,  0xFFFFFFFFFFF94D,                      0xFFFFFFFFFFF959,  0xFFFFFFFFFFF95D,										undef,
	0xFFFFFFFFFFF983, 0xFFFFFFFFFFF986,                    0xFFFFFFFFFFF9C9, 0xFFFFFFFFFFF9F7,  0xFFFFFFFFFFF9FF,                      0xFFFFFFFFFFFA80,  0xFFFFFFFFFFFAB3,										undef,
	0xFFFFFFFFFFFABC, 0xFFFFFFFFFFFAC1,                    0xFFFFFFFFFFFAC7, 0xFFFFFFFFFFFAD1,  0xFFFFFFFFFFFAD6,                      0xFFFFFFFFFFFAE8,  0xFFFFFFFFFFFAF1,									undef,
	0xFFFFFFFFFFFB07, 0xFFFFFFFFFFFB3C,                    0xFFFFFFFFFFFB67, 0xFFFFFFFFFFFB6E,  0xFFFFFFFFFFFB7A,                      0xFFFFFFFFFFFB97,  0xFFFFFFFFFFFBA0,									undef,
	0xFFFFFFFFFFFC22, 0xFFFFFFFFFFFCC6..0xFFFFFFFFFFFCC7,  0xFFFFFFFFFFFCE8, 0xFFFFFFFFFFFD48,  0xFFFFFFFFFFFD51,                      0xFFFFFFFFFFFD74,  0xFFFFFFFFFFFD83,								undef,
	0xFFFFFFFFFFFE00, 0xFFFFFFFFFFFE26,                    0xFFFFFFFFFFFE3C, 0xFFFFFFFFFFFE58,  0xFFFFFFFFFFFE5D,                      0xFFFFFFFFFFFE7D,  0xFFFFFFFFFFFE87,										undef,
	0xFFFFFFFFFFFEB7, 0xFFFFFFFFFFFEC7,                    0xFFFFFFFFFFFEE6, 0xFFFFFFFFFFFF07,  0xFFFFFFFFFFFF56,                      0xFFFFFFFFFFFF8A,  0xFFFFFFFFFFFF91,										undef,
	0xFFFFFFFFFFFFC9, 0xFFFFFFFFFFFFE9,                    0x100000000000000,0x100000000000006, 0x10000000000000C..0x10000000000000D,  0x100000000000033, 0x10000000000003E,				undef,
	0x10000000000007A,0x100000000000081,                   0x10000000000008F,0x1000000000000BA, 0x100000000000103..0x100000000000104,  0x100000000000169, 0x1000000000001A1,			undef,
	0x100000000000204,0x100000000000229,                   0x10000000000022C,0x100000000000240, 0x100000000000283,                     0x10000000000028A, 0x10000000000029A,					undef,
	0x10000000000029D,0x1000000000002A7,                   0x1000000000002AB,0x1000000000002C8, 0x1000000000002F8,                     0x100000000000331, 0x10000000000035A,					undef,
	0x10000000000036B,0x10000000000037C,                   0x100000000000396,0x1000000000003AA, 0x1000000000003B5..0x1000000000003B6,  0x100000000000404, 0x10000000000040F,			undef,
	0x10000000000043A,0x100000000000470,                   0x100000000000496,0x1000000000004C5, 0x1000000000004DC,                     0x1000000000004FF, 0x100000000000508,					undef,
	0x100000000000512,0x100000000000562,                   0x1000000000005B9,0x1000000000005BF, 0x1000000000005C2,                     0x1000000000005F6, 0x100000000000601,					undef,
	0x10000000000060F,0x10000000000061C,                   0x100000000000627,0x10000000000062C, 0x100000000000642,                     0x100000000000684,										undef,
	0x1000000000006F9,0x100000000000739,                   0x10000000000075B,0x10000000000077C, 0x10000000000077E,                     0x10000000000079F,

	],      [0xFFFFFFFFFFF850,0xFFFFFFFFFFF880,0xFFFFFFFFFFF8C4,0xFFFFFFFFFFF8D8,0xFFFFFFFFFFF8E5,0xFFFFFFFFFFF8EC,0xFFFFFFFFFFF8F2,0xFFFFFFFFFFF900,0xFFFFFFFFFFF97E,0xFFFFFFFFFFF996,0xFFFFFFFFFFF9EE,0xFFFFFFFFFFFA55,0xFFFFFFFFFFFAAD,0xFFFFFFFFFFFB8F,0xFFFFFFFFFFFBBA,0xFFFFFFFFFFFBD4,0xFFFFFFFFFFFC9B,0xFFFFFFFFFFFCD5,0xFFFFFFFFFFFCDA,0xFFFFFFFFFFFCDE,0xFFFFFFFFFFFD07,0xFFFFFFFFFFFD3A,0xFFFFFFFFFFFD5B,0xFFFFFFFFFFFDDD,0xFFFFFFFFFFFDE6,0xFFFFFFFFFFFE1D,0xFFFFFFFFFFFF35,0xFFFFFFFFFFFF49,0xFFFFFFFFFFFFAD,0xFFFFFFFFFFFFCB,0x1000000000000A4,0x1000000000000AE,0x1000000000000C4,0x10000000000017A,0x100000000000200,0x100000000000212,0x10000000000027F,0x100000000000288,0x1000000000002F3,0x1000000000002FD,0x10000000000030B,0x100000000000350,0x100000000000393,0x1000000000003E4,0x100000000000410,0x100000000000427,0x100000000000443,0x100000000000454,0x100000000000469,0x10000000000046C,0x10000000000047B,0x1000000000004BC,0x10000000000053F,0x1000000000005BB,0x1000000000005D5,0x1000000000005F9,0x1000000000006A0,0x1000000000006D0,0x1000000000006D1,0x1000000000006D9,0x10000000000071F,0x10000000000076D,0x1000000000007C8,0x1000000000007EA],
	[	#97/3 
	0xFFFFFFFFFFF84E,                    0xFFFFFFFFFFF855, 0xFFFFFFFFFFF878, 0xFFFFFFFFFFF8B2,  0xFFFFFFFFFFF8D2,  0xFFFFFFFFFFF8ED,  0xFFFFFFFFFFF965,  0xFFFFFFFFFFF9B0,
	0xFFFFFFFFFFF9BC,                    0xFFFFFFFFFFF9D6, 0xFFFFFFFFFFF9FC, 0xFFFFFFFFFFFA16,  0xFFFFFFFFFFFA3D,  0xFFFFFFFFFFFA6A,  0xFFFFFFFFFFFA6C,  0xFFFFFFFFFFFA6E,
	0xFFFFFFFFFFFAA2,                    0xFFFFFFFFFFFAA5, 0xFFFFFFFFFFFB1D, 0xFFFFFFFFFFFC05,  0xFFFFFFFFFFFC56,  0xFFFFFFFFFFFC5F,  0xFFFFFFFFFFFCDA,  0xFFFFFFFFFFFCE4,
	0xFFFFFFFFFFFCF3,                    0xFFFFFFFFFFFD81, 0xFFFFFFFFFFFD91, 0xFFFFFFFFFFFD99,  0xFFFFFFFFFFFDE6,  0xFFFFFFFFFFFDFD,  0xFFFFFFFFFFFE84,  0xFFFFFFFFFFFEA8,
	0xFFFFFFFFFFFEC6..0xFFFFFFFFFFFEC7,  0xFFFFFFFFFFFED1, 0xFFFFFFFFFFFF2F, 0xFFFFFFFFFFFFB0,  0xFFFFFFFFFFFFCD,  0xFFFFFFFFFFFFDF,  0x100000000000019, 0x10000000000005E,
	0x10000000000006D,                   0x100000000000073,0x100000000000120,0x1000000000001A7, 0x1000000000001C8, 0x10000000000020D, 0x1000000000002A9, 0x1000000000002C6,
	0x1000000000002FA,                   0x100000000000347,0x100000000000366,0x100000000000427, 0x100000000000431, 0x1000000000004BA, 0x100000000000521, 0x10000000000059E,
	0x1000000000005B5,                   0x10000000000064B,0x100000000000655,0x1000000000006FC, 0x1000000000007A7, 0x1000000000007BA, 0x1000000000007D8,

	],      [0xFFFFFFFFFFF800,0xFFFFFFFFFFF816,0xFFFFFFFFFFF8C0,0xFFFFFFFFFFF8CF,0xFFFFFFFFFFF926,0xFFFFFFFFFFF99D,0xFFFFFFFFFFF9B1,0xFFFFFFFFFFFA85,0xFFFFFFFFFFFB0E,0xFFFFFFFFFFFB5A,0xFFFFFFFFFFFB87,0xFFFFFFFFFFFBAC,0xFFFFFFFFFFFBEB,0xFFFFFFFFFFFC55,0xFFFFFFFFFFFC84,0xFFFFFFFFFFFC99,0xFFFFFFFFFFFCA8,0xFFFFFFFFFFFCB9,0xFFFFFFFFFFFCBA,0xFFFFFFFFFFFD68,0xFFFFFFFFFFFD70,0xFFFFFFFFFFFD96,0xFFFFFFFFFFFE11,0xFFFFFFFFFFFE5E,0xFFFFFFFFFFFE61,0xFFFFFFFFFFFE99,0xFFFFFFFFFFFE9C,0xFFFFFFFFFFFEA9,0xFFFFFFFFFFFEAF,0xFFFFFFFFFFFEB9,0xFFFFFFFFFFFEE0,0xFFFFFFFFFFFEEE,0xFFFFFFFFFFFF0F,0xFFFFFFFFFFFF1E,0xFFFFFFFFFFFFA6,0xFFFFFFFFFFFFC5,0xFFFFFFFFFFFFEB,0x10000000000003D,0x10000000000008E,0x1000000000000CD,0x10000000000014D,0x100000000000197,0x10000000000019E,0x100000000000202,0x100000000000205,0x100000000000207,0x100000000000286,0x1000000000002A6,0x1000000000002C4,0x1000000000002C6,0x1000000000002D9,0x100000000000309,0x100000000000457,0x1000000000004D9,0x1000000000005A5,0x1000000000005E7,0x100000000000621,0x100000000000634,0x100000000000659,0x1000000000006A3,0x1000000000006FD,0x100000000000722,0x100000000000731,0x100000000000780],
	[	#98:	"cube #7 checksum error".  Last keybyte was corrupt.	Cause was in NX4-BCDE, pre²_xc was set to ( I[ izM ] -oc -1 ), but the "-1" was extraneous.
	0xFC13,				0xFC50,				0xFC53,				0xFC5B,				0xFC71,			0xFC79,									undef,
	0xFC82,				0xFC87,				0xFCA4,				0xFCAA..0xFCAB,		0xFCCE..0xFCCF,	0xFCE5,									undef,
	0xFCEA,				0xFCEE,				0xFCF0..0xFCF1,		0xFCF7,				0xFCFC,			0xFD05,				0xFD0A,				undef,
	0xFD0F,				0xFD17,				0xFD25,				0xFD35,				0xFD38,			0xFD3E,				0xFD42,				undef,
	0xFD4A,				0xFD4C,				0xFD5E,				0xFD60,				0xFD62,			0xFD6D,				0xFD73..0xFD74,		undef,
	0xFD7E,				0xFD93,				0xFD96,				0xFDA0..0xFDA1,		0xFDA8,			0xFDAF,				0xFDBB,				undef,
	0xFDEE,				0xFDF0,				0xFDF2,				0xFDF8,				0xFDFE,			0xFE02,				0xFE0B,				undef,
	0xFE0F,				0xFE2A,				0xFE2F,				0xFE37,				0xFE3D,			0xFE44,				0xFE4E,				undef,
	0xFE5C,				0xFE6A..0xFE6B,		0xFE89,				0xFE8B,				0xFE96,			0xFE9A,				0xFEA0,				undef,
	0xFEB2..0xFEB3,		0xFECE,				0xFEE7,				0xFEEF,				0xFF03,			0xFF1D,				0xFF20,				undef,
#	0xFF33,				0xFF3E,				0xFF46..0xFF47,		0xFF58,				0xFF63,			0xFF66,				0xFF69,				undef,
#	0xFF7F,				0xFF99,				0xFF9D,				0xFFA4..0xFFA5,		0xFFBB,			0xFFBD,				0xFFC2,				undef,
#	0xFFE3,				0xFFE5,				0x10004,				0x10006,				0x1000D,		0x1002D,			0x10030,				undef,
#	0x10032,				0x10038,				0x10051,				0x1005A,			0x1005C,		0x1005F,				0x10068..0x10069,		undef,
#	0x1006D,			0x10077,				0x100AA,			0x100CB..0x100CD,	0x100DE,		0x100E3,				0x10101,				undef,
#	0x10116,				0x1012E,				0x10137,				0x10145,				0x10156..0x10157,	0x10167,				0x10174,				undef,
#	0x1017A..0x1017B,	0x1018D,			0x101A2..0x101A3,	0x101A9,			0x101CA,		0x101CC,			0x101D1,			undef,
#	0x101DB,			0x101E0,				0x101E6,				0x101F1,				0x101FF,			0x1020C..0x1020D,	0x10211,				undef,
#	0x1021A,			0x1021D..0x1021E,	0x10225,				0x10227,				0x1022B,		0x10235,				0x10248,				undef,
#	0x10251..0x10252,		0x10266,				0x10271,				0x1028B,			0x10292,			0x10297,				0x1029F,				undef,
#	0x102AA,			0x102AE,			0x102B8,			0x102BF,				0x102CD,		0x102DB,			0x102F7,				undef,
#	0x102FC,				0x102FE,				0x1030A..0x1030B,	0x10310..0x10311,		0x1032D,		0x10330,				0x10336,				undef,
#	0x10346,				0x1035D,			0x1038F,				0x10397..0x10398,		0x1039D,												undef,
#	0x103C8,			0x103E0,				0x103E2,				0x103F5,				0x103FF
	],	[
		0xFC00,0xFC21,0xFC27,0xFC2B,0xFC4C,0xFC81,0xFCA9,0xFCCA,0xFCDA,0xFCDC,0xFCF8,0xFD36,
		0xFD67,0xFD7D,0xFD80,0xFD96,0xFDC1,0xFEA8,0xFEAE,0xFEFE,
	#	0xFF0B,0xFF24,0xFF2B,0xFF60,0xFF7F,0xFF86,0xFF92,0xFFC3,0xFFE4,0xFFEF,0x1003D,0x10045,
	#	0x10056,0x1005E,0x100A5,0x100B0,0x10121,0x1013D,0x10142,0x1015A,0x1015F,0x10163,
	#	0x10178,0x101AB,0x101D4,0x101DF,0x101E9,0x101F0,0x101F8,0x10218,0x1027A,0x102C0,
	#	0x102EC,0x10337,0x10349,0x1034A,0x1035A,0x10381,0x103A6,0x103B9,0x103CC,0x103D7,0x103DB,0x103F8
		],
	[	#99:	"keys not found: [0xF95F,0xF963,0xF97B]"	In MOD_CUBE_0_AS_LPASSxMODS, SwCASE input from K vector did not use ixº as its starting index.
	0xF80A,			0xF823,		0xF841,			0xF851,			0xF854,			0xF85A,							undef,
	0xF889,			0xF88D,		0xF8B8,			0xF8C5,			0xF8F4,			0xF8FE,							undef,
	0xF921,			0xF925,		0xF92F,			0xF93F,			0xF943..0xF945,	0xF94B,				0xF95D, 		undef,
	0xF967,			0xF96F,		0xF980,			0xF9DE,			0xFA09,			0xFA0C,				0xFA0F, 		undef,
#	0xFA1A,			0xFA40,		0xFA53,			0xFA59,			0xFA5B,			0xFA63,				0xFA8B, 		undef,
#	0xFAA4,			0xFABE,		0xFAE6,			0xFAF8,			0xFAFE,			0xFB17,				0xFB1D, 		undef,
#	0xFB58,			0xFB5A,		0xFB69..0xFB6A,	0xFB88,			0xFB93,			0xFB95,				0xFBAA, 		undef,
#	0xFBCD,			0xFBE9,		0xFC23,			0xFC2D,			0xFC34,			0xFC45,				0xFC54, 		undef,
#	0xFC5A,			0xFC72,		0xFC94,			0xFCD9,			0xFCF7,			0xFD03,				0xFD0D, 		undef,
#	0xFD25,			0xFD6A,		0xFD73..0xFD74,	0xFD9C,			0xFDCC,			0xFDD5,				0xFDEC, 		undef,
#	0xFDF5,			0xFDFA,		0xFE00,			0xFE44..0xFE45,	0xFE50,			0xFE8C,				0xFEAF, 		undef,
#	0xFEB5,			0xFEC9,		0xFECD,			0xFEE1,			0xFEFA,			0xFF1E,				0xFF26, 		undef,
#	0xFF29,			0xFF3C,		0xFF5E,			0xFF63,			0xFF7B,			0xFF89,				0xFF8D, 		undef,
#	0xFF92,			0xFFAE,		0xFFB8,			0xFFCD,			0x10008,			0x10033,				0x1003D,	undef,
#	0x10043,			0x100AE,	0x100BA,		0x100CB,		0x1010B,		0x10119,				0x10122,		undef,
#	0x1012C,		0x10138,		0x10153,			0x10155,			0x1015C,		0x10167..0x10168,		0x10179,		undef,
#	0x10186,			0x10189,		0x1018D,		0x101AC,		0x101B3,		0x101FE,				0x10212,		undef,
#	0x10219,			0x10223,		0x10228,			0x1022B,		0x10255,			0x102A9,			0x102C5,	undef,
#	0x102DD,		0x102E6,		0x102F0,			0x102F3,			0x102F8,			0x1031D,			0x10359,		undef,
#	0x1036C,		0x10391,		0x1039E,			0x103B3,		0x103B6,		0x103BC,			0x1040D,	undef,
#	0x10414,			0x1041B,	0x1043E,			0x10455,			0x10462,			0x10467,				0x10484,		undef,
#	0x1049F,			0x104B7,	0x104BE,		0x104C7,		0x104C9,		0x104CF,				0x104E7,		undef,
#	0x10516,			0x10528,		0x10542,			0x10573,			0x10578,			0x10589,				0x105AF,		undef,
#	0x105B4,		0x105B6,	0x105C3,		0x105EE,			0x1060C,		0x1063B,			0x10651,		undef,
#	0x1065F..0x10660,	0x10663,		0x1067D,		0x1068E,			0x106B8,		0x106E1,				0x1070E,		undef,
#	0x10714,			0x10720,		0x1072B,		0x10731,			0x1073B,										undef,
#	0x10744,			0x10746,		0x10755,			0x107C0,		0x107FF

	], [	0xF92F,0xF93F,0xF95F,0xF963,0xF97B,0xF98B,0xF9E2,0xFA8D,
#		0xFB3C,0xFB42,0xFBD6,0xFC8B,0xFCCC,0xFD8D,
#		0xFDDA,0xFE08,0xFE39,0xFE8F,0xFEB0,0xFEBF,0xFEDE,0xFEFD,0xFF1F,0xFF33,0xFF4D,0xFF51,0xFF69,0x1009C,
#		0x100A7,0x100EB,0x10112,0x1012D,0x10147,0x10221,0x1025A,0x1026A,0x1029A,0x102AA,0x10343,0x1037A,
#		0x10386,0x103E8,0x10429,0x1042A,0x1048C,0x10536,0x1059D,0x105AB,0x10601,0x1060A,0x1060B,0x1066B,
#		0x10695,0x106B1,0x106E4,0x106EA,0x10716,0x10718,0x10738,0x1079B,0x107BB,0x107EE,0x107F6,0x107FC
		],
[#	Congratulations on your 100th fatal error, ICEPack!
#	0				1				2				3				4				5					6				7
	0xF80A..0xF80B,	0xF81F,			0xF823,			0xF826,			0xF836,			0xF838,								undef,
	0xF845,			0xF850,			0xF85C,			0xF879,			0xF880,			0xF88A,								undef,
	0xF8D3,			0xF8EC,			0xF915,			0xF924,			0xF93F,			0xF961,				0xF963,			undef,
#	0xF973..0xF974,	0xF97D,			0xF9A4,			0xF9AE,			0xF9B7..0xF9B8,	0xF9C0,				0xF9CF,			undef,
#	0xF9D2,			0xF9EB,			0xFA34,			0xFA37,			0xFA42,			0xFA47,								undef,
#	0xFA69,			0xFA6F,			0xFA7F,			0xFA9D,			0xFAA5,												undef,
#	0xFAAA,			0xFAB1,			0xFAC1,			0xFACE,			0xFAD1,												undef,
#	0xFAE1,			0xFB02,			0xFB43,			0xFB47,			0xFB4A,			0xFB4D..0xFB4E,		0xFB6D,			undef,
#	0xFB74,			0xFB7B,			0xFB83,			0xFB8F,			0xFBC3,			0xFBDF,								undef,
#	0xFBE3,			0xFBE8,			0xFBEC,			0xFC02,			0xFC16,			0xFC18..0xFC19,		0xFC26,			undef,
#	0xFC3A..0xFC3B,	0xFC3F,			0xFC47,			0xFC4B,			0xFC50..0xFC51,	0xFC56,				0xFC5D,			undef,
#	0xFC71,			0xFC89,			0xFCBC,			0xFCBE,			0xFCC9,			0xFCD7,				0xFCE1,			undef,
#	0xFCEE,			0xFCF6,			0xFCFC,			0xFCFF,			0xFD2C,			0xFD4F,				0xFD53,			undef,
#	0xFD69,			0xFD7D..0xFD7E,	0xFD8B..0xFD8C,	0xFD99,			0xFDA3,			0xFDAA,				0xFDB4..0xFDB5,	undef,
#	0xFDC1,			0xFDCB,			0xFDCE,			0xFDDA,			0xFDEB,			0xFDED,				0xFDF5,			undef,
#	0xFE0A,			0xFE24,			0xFE54,			0xFE5A,			0xFE71,			0xFE84,								undef,
#	0xFE92..0xFE93,	0xFEC2,			0xFEC5,			0xFECE,			0xFED5,			0xFEFF,								undef,
#	0xFF2E,			0xFF32,			0xFF37,			0xFF3E,			0xFF41,			0xFF5E,				0xFF68,			undef,
#	0xFF7E,			0xFF8F,			0xFF92,			0xFF99,			0xFFA2,			0xFFA5,				0xFFA9..0xFFAA,	undef,
#	0xFFD5,			0xFFD8,			0xFFDF,			0xFFEB,			0xFFEF,			0xFFFB,				0x10001,			undef,
#	0x1000A,		0x1002E,			0x10032,			0x10038..0x10039,	0x1004F,			0x10051,				0x10064,			undef,
#	0x10066,			0x1006E,			0x10071,			0x10084,			0x10088,			0x1008A,			0x10097,			undef,
#	0x100A5,		0x100A8..0x100AA, 0x100AD,		0x100BA,		0x100C0,		0x100D5,			0x100E1,			undef,
#	0x10104,			0x10114,			0x10116,			0x10123..0x10124,	0x10133,			0x1013C,			0x10141,			undef,
#	0x10143,			0x10147,			0x1015D,		0x1016E,			0x10173,			0x10175,				0x10179,			undef,
#	0x1018B..0x1018C, 0x101A3,		0x101A7,		0x101D3,		0x101D6,		0x101E6,				0x101E9,			undef,
#	0x10202,			0x10229,			0x10236,			0x1023A,		0x1023D,		0x10243,								undef,
#	0x10245,			0x10251,			0x10264,			0x1028C..0x1028D, 0x10291,		0x1029F,				0x102A7,		undef,
#	0x102B2,		0x102B7..0x102B8, 0x102C9,		0x102D3,		0x102E6,			0x102EA,							undef,
#	0x102F3,			0x102F7,			0x10302,			0x10324,			0x10335,			0x1034C,							undef,
#	0x10352,			0x10365,			0x10385,			0x103A5,		0x103B0,		0x103BE,			0x103C1,		undef,
#	0x103C8,		0x103DD..0x103DE, 0x103EA,		0x10404,			0x1040E,			0x10413,				0x10419,			undef,
#	0x1041D,		0x10427,			0x10435,			0x10437,			0x10439,			0x1043B,			0x10443,			undef,
#	0x10475,			0x10480..0x10481,	0x10485,			0x1049E,			0x104A4,		0x104B2,			0x104C9,		undef,
#	0x104CF,			0x104D6,		0x104E9,			0x104F3,			0x104F8,			0x10502,				0x10505,			undef,
#	0x10514,			0x10516,			0x10534,			0x10547,			0x10556,			0x1057C,			0x1058A,		undef,
#	0x10593,			0x10596..0x10598,	0x105A5,		0x105BB,		0x105BD,		0x105D6,			0x105DC,		undef,
#	0x105F1,			0x10609,			0x10613,			0x10624,			0x1062F,			0x10631,				0x10636..0x10637,	undef,
#	0x10643,			0x10645,			0x10650,			0x1065B,		0x10666,			0x1067A..0x1067B,	0x1068A,		undef,
#	0x106A0,		0x106B9,		0x106BD,		0x106C0,		0x106C2,		0x106C9,			0x106D2,		undef,
#	0x106DD,		0x106EE,			0x106F4,			0x1070A,		0x1071A,		0x10721,				0x10725,			undef,
#	0x10731,			0x10734,			0x10745,			0x1074D,		0x10753,			0x10758,								undef,
#	0x107B1,		0x107B4,		0x107BE,		0x107C7,		0x107D2,		0x107E9,

	],	[
		0xF81E,0xF84A,
	#	0xF971,0xF98B,0xF997,0xF9F2,0xFA16,0xFA3D,0xFA5B,0xFA7D,0xFA8D,0xFAB4,0xFB2D,0xFB92,0xFB9C,
	#	0xFB9E,0xFC18,0xFC42,0xFC94,0xFCDE,0xFD10,0xFD73,0xFD86,0xFD8B,0xFDD7,0xFDF4,0xFE7C,0xFF14,0xFF44,0xFF6B,
	#	0xFFC0,0x10030,0x10075,0x1008A,0x100A3,0x100C6,0x100E3,0x1015B,0x1019B,0x101A2,0x101AE,0x101C2,0x101E9,
	#	0x102B0,0x102F5,0x1032A,0x10391,0x10392,0x103A5,0x103B7,0x1041A,0x10466,0x1048C,0x104CD,0x10586,0x1058E,
	#	0x105CD,0x105E0,0x1061E,0x10750,0x107AC,0x107C9,0x107DA,0x107E5
		],

	[	#101  a bit more chewed up than usual!	In NX3-ABD. low passthrough src was *( (ui64*) cube+ (I[ix¹]-oc) ) instead of *( (ui64*) cubeº+I[ ix¹ ] ).
#	0			1			2			3			4			5			6			7
#	0xF802,			0xF81E,			0xF821,			0xF82F,			0xF847,			0xF84C,						undef,	
#	0xF857,			0xF859,			0xF871,			0xF879..0xF87A,		0xF880..0xF882,		0xF887..0xF888,					undef,
#	0xF898,			0xF89F,			0xF8A3,			0xF8AB,												undef,
#	0xF8BB,			0xF8BD,			0xF8C7,			0xF8CC,			0xF8D4,									undef,
#	0xF8D8..0xF8D9,		0xF8DC,			0xF8E3,			0xF8E6,			0xF8E8,			0xF8F6,			0xF900,			undef,
#	0xF90D..0xF90E,		0xF911,			0xF916..0xF917,		0xF92F,			0xF935,			0xF939,			0xF93D,			undef,
#	0xF93F,			0xF952,			0xF967,			0xF96E,			0xF97A..0xF97B,								undef,
#	0xF97E,			0xF983,			0xF99D,			0xF9A5,												undef,
#	0xF9AD,			0xF9B2,			0xF9B6,			0xF9C6,			0xF9C8,									undef,
#	0xF9CD,			0xF9CF..0xF9D0,		0xF9D5,			0xF9DA,			0xF9F6,			0xFA08,			0xFA11,			undef,
#	0xFA14,			0xFA18,			0xFA1F,			0xFA25,			0xFA34,									undef,
#	0xFA37,			0xFA3C..0xFA3D,		0xFA49,			0xFA53,			0xFA57..0xFA58,								undef,
#	0xFA5D,			0xFA63,			0xFA6D,			0xFA73..0xFA75,		0xFA7B,			0xFA87..0xFA88,		0xFA98,			undef,
#	0xFA9C,			0xFAB5,			0xFAB8,			0xFAC8,			0xFACC,			0xFAD0,						undef,
#	0xFADD,			0xFAE1..0xFAE2,		0xFAE4,			0xFAE7,			0xFAFB..0xFAFC,		0xFB07,						undef,
#	0xFB0D,			0xFB11..0xFB12,		0xFB16,			0xFB1D,			0xFB21,									undef,
#	0xFB36,			0xFB39,			0xFB55..0xFB56,		0xFB58,			0xFB5E,			0xFB68,			0xFB73..0xFB74,		undef,
#	0xFB83,			0xFB91,			0xFB98,			0xFBA2,			0xFBA6,			0xFBAB,			0xFBAD,			undef,
#	0xFBB5,			0xFBB8..0xFBB9,		0xFBC7,			0xFBCA,			0xFBD0,			0xFBD2,			0xFBDB,			0xFBE5,
#	0xFBF4,			0xFBFC..0xFBFD,		0xFBFF,			0xFC01,			0xFC03,			0xFC07,						undef,
#	0xFC0B,			0xFC11,			0xFC27..0xFC28,		0xFC2C,			0xFC2E,			0xFC31,						undef,
#	0xFC3B,			0xFC3F..0xFC40,		0xFC61,			0xFC70,			0xFC73,			0xFC7A,			0xFC8E,			0xFC9D,
#	0xFCD5,			0xFCD9..0xFCDA,		0xFCE2,			0xFCE4,												undef,
#	0xFCEB,			0xFCF9,			0xFD0E,			0xFD2D..0xFD2E,		0xFD36,			0xFD3A,			0xFD41,			undef,
#	0xFD45,			0xFD47,			0xFD51,			0xFD65,			0xFD67,			0xFD6E,			0xFD70,			undef,
#	0xFD73,			0xFD77..0xFD78,		0xFD89,			0xFD8F..0xFD90,		0xFD94,			0xFDA9..0xFDAA,					undef,
#	0xFDBE,			0xFDC1,			0xFDC3,			0xFDC9,			0xFDCF,			0xFDDD,			0xFDF6,			undef,
#	0xFDF9,			0xFDFC,			0xFE04,			0xFE0E,			0xFE19,									undef,
#	0xFE20,			0xFE24,			0xFE2B,			0xFE2D,			0xFE2F..0xFE30,								undef,
#	0xFE3F,			0xFE43,			0xFE4B,			0xFE73,			0xFE89,			0xFE99,						undef,
#	0xFEA6,			0xFEAF..0xFEB0,		0xFEC8,			0xFECA,			0xFEDA,			0xFEDD..0xFEDE,					undef,
#	0xFEEA,			0xFEF8,			0xFEFB,			0xFEFD,			0xFF05,									undef,
#	0xFF07,			0xFF15,			0xFF1F..0xFF20,		0xFF26,			0xFF30,									undef,
#	0xFF4D,			0xFF4F,			0xFF65,			0xFF6A,			0xFF79,			0xFF7F,						undef,
#	0xFF97,			0xFF9B,			0xFFA3,			0xFFAC..0xFFAD,		0xFFB9,			0xFFCE,						undef,
#	0xFFE9,			0xFFEF,			0x10002,		0x10014,		0x10016..0x10017,	0x10019,					undef,
#	0x10022,		0x10026,		0x10063,		0x1006D,		0x10072,		0x10084,					undef,
#	0x10093..0x10095,	0x10098,		0x1009B,		0x1009F,		0x100A1,		0x100A3,		0x100A9,		undef,
#	0x100AD,		0x100C1,		0x100D3,		0x100D6,		0x100D9,		0x100E3,		0x100EE,		0x100F3,
#	0x100F5,		0x10106,		0x10109,		0x10110..0x10111,	0x1011D,		0x10126,					undef,
#	0x10133,		0x1013F,		0x10143,		0x1014D,		0x10151,		0x10156,					undef,
#	0x1015C..0x1015D,	0x1015F,		0x10169,		0x1016F,		0x10176,		0x10193,		0x10199,		undef,
#	0x1019B,		0x101A3,		0x101AB,		0x101B3,		0x101B5,		0x101B8..0x101B9,				undef,
#	0x101C7,		0x101CA,		0x101DD,		0x101E2,		0x101E4,		0x101E8..0x101E9,	0x101F3,		undef,
#	0x101FB,		0x101FE,		0x10213..0x10215,	0x10219,		0x1021D..0x1021E,	0x10222,					undef,
#	0x10224,		0x10228,		0x1022B,		0x1022D..0x1022F,	0x10233,		0x10248..0x10249,	0x10256,		undef,
#	0x1025F,		0x1026F,		0x10274,		0x10281,		0x10287,		0x10298..0x10299,				undef,
#	0x102A9,		0x102C5..0x102C6,	0x102C8..0x102C9,	0x102CC,		0x102CF,		0x102D4..0x102D5,				undef,
#	0x102DC..0x102DE,	0x102E8,		0x102F7,		0x102F9,		0x10300,		0x1030A,					undef,
#	0x10313,		0x10319,		0x10320,		0x10322,		0x10325,		0x1032D,		0x10339..0x1033A,	undef,
#	0x1033D,		0x10343,		0x1034A,		0x10350,		0x10357,		0x1035A,					undef,
#	0x10378,		0x1037B,		0x10389,		0x1038F,		0x10393..0x10394,	0x1039B,		0x1039D,		undef,
#	0x1039F..0x103A0,	0x103AE,		0x103B7,		0x103BA,		0x103BC,		0x103C8,		0x103CB,		undef,
#	0x103D0,		0x103D2,		0x103E2,		0x103F1..0x103F2,	0x10400..0x10403,	0x10405,		0x10408,		undef,
#	0x10414,		0x10416,		0x1041A,		0x1042B,		0x1042E,		0x10432,		0x10435,		undef,
#	0x1043A,		0x10444,		0x1044A,		0x1044E,											undef,
#	0x10452,		0x1045B,		0x1045D,		0x10467,		0x1046F,								undef,
#	0x1047C,		0x1048C,		0x10499,		0x104A6,		0x104A8,		0x104AB,					undef,
#	0x104B2,		0x104B4,		0x104B8..0x104B9,	0x104CE,		0x104D2..0x104D3,	0x104E9,					undef,
#	0x104EF,		0x104F1..0x104F2,	0x104FA,		0x10505,		0x10508,		0x1051E..0x1051F,	0x1053A,		undef,
	0x1053C,		0x10543,		0x1054D,		0x10552,		0x10554,		0x10559,					undef,
	0x1055E,		0x10561,		0x10563,		0x10565..0x10566,	0x10573,		0x1057C,		0x10583,		0x10593,
	0x10598,		0x105AD,		0x105B0,		0x105BC,		0x105CC,		0x105D8,		0x105E6..0x105E7,	undef,
	0x105EC..0x105ED,	0x105FB,		0x10606,		0x10610,		0x10615,		0x10619,		0x10627,		undef,
#	0x1062E..0x1062F,	0x10633..0x10634,	0x10642,		0x10653,		0x10659,		0x10660,		0x10663,		undef,
#	0x10667,		0x10669,		0x1066D,		0x10671,		0x1067D,		0x1067F,		0x1068B..0x1068C,	undef,
#	0x1068F,		0x1069B,		0x106A2,		0x106BA,		0x106C4,		0x106C6,		0x106C8,		undef,
#	0x106D0,		0x106D2..0x106D3,	0x106DD,		0x106E3,		0x106E5..0x106E6,	0x106EA,					undef,
#	0x106EC,		0x106EE,		0x106F7,		0x10711,		0x10715,		0x1071B,		0x10722,		0x10725,
#	0x10734,		0x1073A,		0x1073E..0x1073F,	0x1074D,		0x10758,		0x10769,		0x10771,		undef,
#	0x10773,		0x10777,		0x10779,		0x1077B,		0x10787,		0x10794,		0x1079A..0x1079B,	undef,
#	0x107A1,		0x107A5,		0x107AE,		0x107B6,		0x107BA,		0x107C3..0x107C5,	0x107C7,		0x107D4..0x107D5,
#	0x107DF..0x107E0,	0x107E6,		0x107EB,		0x107F6,		0x107FE,
	],	[
	#	0xF812,0xF817,0xF88F,0xF8E3,0xF8F0,0xF94A,0xF975,0xF978,0xF97C,0xF97E,0xF981,0xF990,0xFA05,0xFA2C,0xFA54,0xFA72,
	#	0xFAEE,0xFB58,0xFB95,0xFBA4,0xFC66,0xFC78,0xFDCE,0xFE08,0xFE4F,0xFE6C,0xFE91,0xFE96,0xFEB2,0xFF51,0xFFE2,0xFFF0,
	#	0x10003,0x10005,0x10019,0x10091,0x100A2,0x100A6,0x100BC,0x100EC,0x10105,0x1014F,0x10161,0x101BE,0x101CD,
	#	0x1025F,0x102BB,0x10326,0x1035F,0x10382,0x1039E,0x1042B,0x1048D,
	#	0x104C0,
				0x1058A,0x105D6,	#0x10697,
	#	0x106A8,0x106CA,0x106DF,0x10735,
	#	0x1073A,0x10751,0x107B7
		],
	[	#102: in _next_x block of _set(),  "oCS+= CS-16;" before "goto _co_epiloc;"  was complete bs, apparently
#	0xF806, 0xF808,          0xF82F,          0xF832,            0xF83D,  0xF860,						undef,
#	0xF86E, 0xF88B,          0xF8AD,          0xF8AF,            0xF8BE,  0xF8D9,						undef,
#	0xF8E0, 0xF8F7..0xF8F8,  0xF8FC,          0xF904,            0xF90B,  0xF910,            0xF913,						undef,
#	0xF946, 0xF94E,          0xF95B,          0xF96B,            0xF97C,  0xF9C4,            0xF9C6..0xF9C7,						undef,
#	0xF9E4, 0xF9E8,          0xFA06,          0xFA37,            0xFA3A,  0xFA4B,						undef,
#	0xFA68, 0xFA8E,          0xFAA4,          0xFAAB,            0xFAAE,						undef,
#	0xFABE, 0xFACA,          0xFAD1,          0xFADC,            0xFAE2,  0xFAF6,            0xFB00,						undef,
#	0xFB04, 0xFB0E,          0xFB1A,          0xFB2A,            0xFB64,  0xFB6D,            0xFB8D,						undef,
#	0xFB94, 0xFB99..0xFB9A,  0xFBBD,          0xFBC0,            0xFBDA,  0xFBE2,            0xFC00,						undef,
#	0xFC04, 0xFC18,          0xFC1D,          0xFC20,            0xFC54,  0xFC5F,            0xFC66,						undef,
#	0xFC6B, 0xFC71,          0xFC73,          0xFC75,            0xFC81,  0xFC83,            0xFCA5,						undef,
#	0xFCCB, 0xFCCE,          0xFCE5,          0xFD07,            0xFD1F,  0xFD23,            0xFD37,						undef,
#	0xFD3F, 0xFD46,          0xFD4B..0xFD4C,  0xFD51,            0xFD55,  0xFD59,            0xFD85,						undef,
#	0xFDA7, 0xFDA9,          0xFDAB,          0xFDAD,            0xFDC1,  0xFDC6,            0xFDF1,						undef,
#	0xFDF3, 0xFDF5,          0xFDF9,          0xFE21,            0xFE28,  0xFE2B,            0xFE3E,						undef,
#	0xFE44, 0xFE46,          0xFE4A,          0xFE63..0xFE64,    0xFE69,  0xFE6D,            0xFE70,						undef,
#	0xFE75, 0xFE85,          0xFE88,          0xFE94,            0xFEE1,  0xFF34,            0xFF4F,						undef,
#	0xFF71, 0xFF8D,          0xFF95,          0xFFA5,            0xFFC9,  0xFFCB,            0xFFCD,						undef,
#	0xFFE9, 0xFFF9,          0xFFFE,          0x10001,           0x1000F, 0x10017,           0x10021,						undef,
#	0x10035,0x10039,         0x10041,         0x1004D,           0x10064, 0x1006F..0x10070,						undef,
#	0x10073,0x100A1,         0x100A7,         0x100AB,           0x100CD, 0x100F4,           0x10100,						undef,
#	0x10110,0x10141,         0x1014C,         0x1017B,           0x1017F, 0x10185..0x10186,						undef,
#	0x101AD,0x101C7,         0x101E2,         0x101F4,           0x1020F, 0x10221,						undef,
#	0x10278,0x1027C,         0x1027F,         0x1028C,           0x1029E, 0x102B1,           0x102BE,						undef,
#	0x102C2,0x102D0,         0x102D4,         0x102E6,           0x102F4, 0x102F7,           0x10305,						undef,
	0x10331,0x10359,         0x1035E,         0x1036E,           0x10395,						undef,
	0x10398,0x103A6,         0x103B2,         0x103BB,           0x103EB,						undef,
	0x103F1,0x103F6,         0x10402,         0x10406,           0x10411, 0x10420,           0x1042B,						undef,
	0x10437,0x10439,         0x10441,         0x10457,           0x10466, 0x1046A,						undef,
	0x1047F,0x10488,         0x104A6,         0x104C3,           0x104E5, 0x104F2,						undef,
	0x1051A,0x10521,         0x10529,         0x1052D,           0x10537, 0x10550,           0x1055D,						undef,
	0x10565,0x10598,         0x105A5,         0x105A9,           0x105AC, 0x105B2,           0x105EA,						undef,
	0x105FC,0x10625,         0x10627,         0x10646,           0x1064C, 0x10654,           0x10665,						undef,
	0x10671,0x1067D,         0x106A3,         0x106AD,           0x106B0, 0x106E7,           0x106FA,						undef,
	0x10701,0x10705,         0x10720..0x10721,0x1072E,           0x10730, 0x1073C,           0x1074C,						undef,
	0x10758,0x1075E,         0x10764,         0x1079A,           0x1079D,						undef,
	0x107AB,0x107C0,         0x107CE,         0x107E0..0x107E1,  0x107EC,

	],      [
#		0xF824,0xF91B,0xF93C,0xF96E,0xF976,0xF985,0xF99C,0xFA6A,0xFA6F,0xFB9A,0xFBC8,0xFBFB,0xFC1D,0xFC67,
#		0xFC85,0xFC8B,0xFC9C,0xFCC7,0xFCCB,0xFCF4,0xFCFC,0xFD64,0xFDEF,0xFE16,0xFE66,0xFEBA,0xFF21,0xFF89,
#		0xFFE4,0xFFF9,0x10010,0x10016,0x10045,0x1006D,0x1009B,0x1009F,0x100C5,0x10127,0x10133,0x1015F,0x101AC,
#		0x101B4,0x101BF,0x101F2,0x101F6,0x10240,0x103F8,0x10435,0x10446,0x10467,0x1047C,0x10494,0x104A9,0x104AA,
		0x104D6,0x104ED,0x10541,0x10568,0x1056F,0x105AC,0x106CB,0x106EF,0x107C2,0x107FD],
	[	# 103: in ƒsub NX4-xxDx, pre¹_xc metric originated at I[ izM ] instead of I[ ixH ]-1.
#	0xF800,          0xF80C,          0xF819,          0xF81B,            0xF81D,            0xF826,            0xF82A,						undef,
#	0xF834,          0xF839,          0xF842,          0xF845,            0xF848,            0xF851..0xF854,    0xF866,            0xF874..0xF875,						undef,
#	0xF880,          0xF887,          0xF88A,          0xF88C,            0xF891,            0xF893,            0xF89B,						undef,
#	0xF89D,          0xF8A6,          0xF8B2,          0xF8DC,						undef,
#	0xF8E3,          0xF8F0,          0xF8FA,          0xF8FF..0xF900,    0xF90E,						undef,
#	0xF914..0xF915,  0xF921,          0xF92B..0xF92C,  0xF939,            0xF93B,            0xF940,            0xF943,						undef,
#	0xF952,          0xF954..0xF955,  0xF96C,          0xF985,            0xF9A6,            0xF9C1,						undef,
#	0xF9D5,          0xF9D8,          0xF9E1,          0xF9F3..0xF9F4,    0xFA00..0xFA01,						undef,
#	0xFA04,          0xFA0C..0xFA0D,  0xFA10,          0xFA1C,            0xFA24,						undef,
#	0xFA32,          0xFA39,          0xFA3D..0xFA3E,  0xFA42..0xFA43,    0xFA51,            0xFA59,            0xFA5C,						undef,
#	0xFA70,          0xFA74,          0xFA82,          0xFA92,            0xFA98,            0xFA9D,						undef,
#	0xFAA0,          0xFAA2,          0xFAA8,          0xFAB0..0xFAB2,    0xFAB7,            0xFABB..0xFABC,						undef,
#	0xFAC1,          0xFAD0,          0xFAD2..0xFAD3,  0xFADF,            0xFAE9,            0xFAF2..0xFAF3,						undef,
#	0xFAF8,          0xFB1B,          0xFB30,          0xFB3C,            0xFB3F,            0xFB41,						undef,
#	0xFB4A,          0xFB56,          0xFB62,          0xFB68,            0xFB6F,            0xFB78,						undef,
#	0xFB8A,          0xFB8C,          0xFB8F,          0xFBB9,            0xFBBF,            0xFBC2,            0xFBC5,						undef,
#	0xFBD5,          0xFBD8,          0xFBE9,          0xFBEC,            0xFC14,            0xFC1A,						undef,
#	0xFC22,          0xFC24..0xFC26,  0xFC2D,          0xFC3F,            0xFC42,            0xFC4F,						undef,
#	0xFC55,          0xFC59,          0xFC68,          0xFC83..0xFC84,    0xFC8C..0xFC8D,    0xFC90,						undef,
#	0xFC9B,          0xFCA1,          0xFCAA,          0xFCBF,            0xFD00,            0xFD09,						undef,
#	0xFD17,          0xFD22..0xFD23,  0xFD48..0xFD49,  0xFD55,            0xFD5A,            0xFD8D,            0xFD90,						undef,
#	0xFD95,          0xFD98,          0xFD9A,          0xFDA2,            0xFDA4,            0xFDB7,            0xFDBA,						undef,
#	0xFDBF,          0xFDDD,          0xFDE5,          0xFDE8,            0xFDEF,            0xFE17..0xFE18,    0xFE2D..0xFE2E,						undef,
#	0xFE44,          0xFE4B,          0xFE4E,          0xFE50,            0xFE59..0xFE5A,    0xFE63,						undef,
#	0xFE68,          0xFE76,          0xFE7E,          0xFE83,            0xFE87,            0xFE96,						undef,
#	0xFE98,          0xFE9D,          0xFEAE,          0xFEB7,            0xFEC1,            0xFEC7,						undef,
#	0xFECC..0xFECD,  0xFEE2,          0xFEED,          0xFEF3,            0xFF07,            0xFF0F,            0xFF12,            0xFF21,						undef,
#	0xFF2A,          0xFF39,          0xFF69..0xFF6A,  0xFF6C..0xFF6D,    0xFF76,            0xFF7A,            0xFF8B,						undef,
#	0xFF92,          0xFF95,          0xFF9E,          0xFFA7,            0xFFA9,            0xFFAC,						undef,
#	0xFFD3,          0xFFD7,          0xFFDF,          0xFFE2,            0xFFE4,            0xFFEB,						undef,
#	0xFFED,          0xFFF7,          0x10004,         0x10007,           0x1001D,           0x1001F,           0x10021,						undef,
#	0x10023,         0x10027,         0x1002B,         0x10039,           0x10044,           0x1004F,						undef,
#	0x10051,         0x10060..0x10062,0x1006A,         0x1006D,           0x10072,           0x10078,						undef,
#	0x1007B,         0x1008E..0x1008F,0x100A1,         0x100A9,           0x100AF,           0x100B4,						undef,
#	0x100BD,         0x100C4,         0x100CB,         0x100CD..0x100CE,  0x100F7..0x100F9,  0x10101..0x10102,  0x1011A..0x1011B,						undef,
#	0x10121..0x10122,0x1013E..0x1013F,0x10142,         0x1014F,           0x10157,           0x10159,						undef,
#	0x10161,         0x10163,         0x10166,         0x10169,           0x1017A..0x1017B,  0x1017E,						undef,
#	0x1018F,         0x10194,         0x10197,         0x1019C,           0x101A8,           0x101AE,           0x101B0,						undef,
#	0x101B4..0x101B5,0x101BE..0x101BF,0x101C2,         0x101C6,           0x101EA,           0x101F8,           0x101FB,						undef,
#	0x10209,         0x1020E,         0x10215,         0x1021A..0x1021B,  0x10220,           0x10222,						undef,
#	0x1022D,         0x10239,         0x10244,         0x10246,           0x1024B,           0x1024D,           0x10254,						undef,
#	0x1025E,         0x10261,         0x10272,         0x1027A,           0x1027F,           0x10291,           0x102A8,						undef,
#	0x102AE,         0x102B2,         0x102B4,         0x102B7..0x102B9,  0x102C6,           0x102CB,						undef,
#	0x102CE,         0x102D5,         0x102EA,         0x102F0,           0x102F4..0x102F5,  0x102F8..0x102F9,						undef,
#	0x102FC,         0x10300..0x10301,0x10306,         0x1030A,           0x10315,           0x1031C,           0x10326,						undef,
#	0x1032A,         0x10335,         0x10351,         0x10362,           0x1036E,           0x10371,           0x10378,						undef,
#	0x1037C,         0x1037F,         0x10390,         0x103A4..0x103A6,  0x103CB,           0x103E0,						undef,
#	0x103E5,         0x103F4,         0x103FB,         0x103FF,           0x10410,           0x10414,						undef,
#	0x10417..0x10418,0x1041B..0x1041C,0x1041E,         0x1042D,           0x1043F..0x10440,  0x10446,						undef,
#	0x10448..0x1044A,0x1044D,         0x1044F,         0x10464,           0x10470,           0x10472,           0x1047D,           0x10485,						undef,
#	0x1048D,         0x1049D..0x1049E,0x104A3,         0x104A5..0x104A6,  0x104A8,           0x104AC,						undef,
#	0x104BE,         0x104CB,         0x104CE,         0x104D4,           0x104D6,           0x104DA..0x104DB,  0x104DE,						undef,
#	0x104E7,         0x104E9..0x104EA,0x104F3,         0x104F9,           0x1050E,           0x10513,						undef,
#	0x1051C,         0x10526,         0x10529,         0x10530..0x10531,  0x1053A,           0x10548,						undef,
	0x10552..0x10553,0x10560,         0x1056F,         0x10574,           0x10578,           0x1057D,						undef,
	0x1058D,         0x10592,         0x10596,         0x105AD..0x105AF,  0x105B7,           0x105B9,						undef,
	0x105C5,         0x105D2,         0x105E2,         0x105E9,           0x105F0,           0x105FB,						undef,
	0x10603,         0x10607,         0x10617,         0x10636,           0x10638,           0x1063E,						undef,
	0x10640,         0x10654,         0x1065A,         0x1065D,           0x10660,           0x1066A,           0x10677..0x10678,						undef,
	0x1068E,         0x10690,         0x10693,         0x1069A..0x1069B,  0x106A5,           0x106C1,           0x106CC,						undef,
	0x106CE,         0x106D2,         0x106DB,         0x106E9,           0x106F1,           0x106F6,           0x10704,						undef,
#	0x1070A,         0x10717,         0x1071B,         0x1071D,           0x10729,           0x1072C,           0x1072E..0x1072F,						undef,
#	0x10732,         0x1073D,         0x1073F,         0x10744..0x10745,  0x10761,           0x10767,           0x10773,						undef,
#	0x1077D,         0x10785..0x10786,0x10790..0x10792,0x10794,           0x1079D,           0x107A1..0x107A3,						undef,
#	0x107AE,         0x107B6..0x107B7,0x107C8,         0x107DD,           0x107DF,           0x107FF,

	],      [
#	0xF817,0xF851,0xF933,0xF9B6,0xF9CC,0xFA5C,0xFAC6,0xFB1D,0xFB58,0xFB87,0xFBF7,0xFC15,0xFC69,0xFCCB,0xFD5F,
#	0xFD76,0xFD95,0xFDC9,0xFDD5,0xFE21,0xFE3C,0xFE89,0xFEAB,0xFEB1,0xFF00,0xFF5A,0xFFEB,0x10037,0x1004A,0x10071,
#	0x1007F,0x10086,0x10130,0x101A7,0x101D0,0x101DC,0x101ED,0x1020D,0x1022F,0x10270,0x102D9,0x10318,0x10325,0x1035A,
#	0x1036D,0x103A0,0x103BC,0x103D0,0x10426,0x104A4,0x104B9,
	0x1055C,0x1059F,0x10608,0x10643,0x10687,0x1069A,0x106B3, 0x106CD,
#	0x10756,0x10757,0x10768,0x107F5,0x107FE
	],
	[	#104	ƒsub NX3-ABD	"#missing keys...  [ FDA4 ]"	XLOAD was pulling lowpass q from (cube) instead of (cubeº)
	0xFD67..0xFD68,	0xFD6C,		0xFD81,		0xFD86,		0xFD8E,		0xFD94,		0xFD9E,		0xFDA9..0xFDAB,			undef,
	0xFDAE,		0xFDB0,		0xFDB6,		0xFDBB,		0xFDBD,		0xFDC0,				undef,
	0xFDC8,		0xFDE2,		0xFDE9,		0xFDED,		0xFDF7..0xFDF9,	0xFE01,				undef,
	],	[0xFDA1,0xFDA4,0xFDA5,	0xFDC0	],
	[	#105:	In NX2L, ixº is consumed by ICEPACK macro.  "*Edge( cubeº ) = E[ ixº]; " had to come before that, but after ReFLOW.
		#		I also deleted "-oCS" term from "XLOAD p¹, O[ ix¹ ]-oCS, lp¹_q, cube, cube¹ );", and I posit that
		#
		#			> lowpass metrics should never require a running offset like (oCS) if the cube run is properly trimmed.
		#
	0x101CD,         0x101DB,         0x101E1,         0x101E3,           0x101E7,										undef,
	0x101ED,         0x101F0,         0x101F2,         0x101F9,           0x101FC..0x101FD,  0x10203..0x10204,  0x10209,           0x10211,			undef,
	],	[0x101D6, 0x101EC	],
	[	#106:	"arg	keys	not	found:	[0xFB1C,0xFB3C]"	It was preventable.  I already ran into issues not using (cubeº) instead of (cube) in "multi-scalar" NX* handlers.
	0xFAFA,		0xFAFD,		0xFAFF,		0xFB08,		0xFB0E..0xFB0F,	0xFB15,		0xFB1D..0xFB1E,			undef,
	0xFB26,		0xFB36,		0xFB3D,		0xFB43..0xFB45,									undef,
	0xFB54,		0xFB5C,		0xFB62,		0xFB68,		0xFB73..0xFB74,							undef,
	0xFB78,		0xFB8E,		0xFB94,		0xFB96,		0xFB9A,		0xFB9E..0xFB9F,					undef,
	], [	0xFB1C,0xFB3C ],
	[	#107	in NX3-AB*, the conditional for whether to invoke MOD_CUBE_Ω_AS_HIGHPASS or MOD_CUBE_Ω_AS_MODSxHPASS
		#		was { if( izM==iz¹ ) }, assuming izM could not be less-than iz¹. 
		#		I changed it to" if( izM< ixΩ ) " as it was and is already everywhere else these macros branch.

	0x1041C,	0x10422, 		0x1042D,	0x10437, 	0x1043D,	0x10444, 	0x10454, 	0x1045C,
	0x10463, 	0x10468, 		0x10479, 	0x1047F, 	0x10481, 	0x1048C,	0x1048F,		undef,
	],	[0x1045A,0x1045F	],
	[	#108:	"cube #1 checksum error."	ƒsub NX2L				TODO: Revisit!!!
#	changed 			hpI_q	=	O[ 	ixΩ	]	-	O[ 	ixH	];
#	to				hpI_q	=	O[ 	ixΩ	]	-		oCS;
#
#	While having a look around at NX2L, it came to my attention that I'm pretty sure it isn't conserving highpass in low cube,
#	just re-encoding the highpass region, and this works because that will be loaded in the vector map,
#	and it might even tend to be more efficient, but the fact is, it seems to be an accident, because we still have a ReFLOW block
#	for the low cube that probably will never execute as it is.
#
	0x10254,	0x1025C,	0x10266,0x10269,	0x10271,				undef,
	0x10298,	0x102A7,	0x102A9,0x102CD,	0x102DD,	0x102EA,	0x102F7, undef,
	],	[	0x10253,0x10298	],
	[	#109:	"cube #1 checksum error"	ƒsub NX2H
	0x102ED,         0x102F0,         0x102F2,         0x102F4,           0x102F6,           0x102F8,           0x102FE..0x10300,  undef,
	0x10302..0x10306,0x1030B,         0x1030D,         0x10311,           0x10313,           0x10317..0x10318,  undef,

	], 	[0x102F2,0x10301,0x10311],
	[	#110:	"cube #2 checksum error"	ƒsub NX1:	changed calculation of relΩ_q from/to:
#	from:
#			relΩ_q		=	Oª[	inM	]	-	O[	ixH-ocª	];	/* erroneous nonsense	*/
#	to:
#			relΩ_q = rel_q	+	Oª[	ocª	]	-		16;			/* relative different in pre-to-post q, plus redistribution	*/
#
#	I barely remember writing the first line.  I'd been trying to find relΩ_q as a single difference between two points on the vector map.
#	With fresh eyes, that idea of subtracting two vmap indeces makes absolutely no sense.  It was pure shit shot that hit.
#	The change in q for cube Ω only, in ƒsub NX1 where many fragments collapse into the ending one, is a combination of:
#
#		> the change in overal encoded data length post-op, as well as
#		>  the adoption of consolidated data from preceding cubes.
#
#	These measurements have different frames of reference, as the former is a change in overall data length, and	
#	the latter is simply the movement of a reference point (vector ocª) within that data.
#
#	In NX2M, I wrote this more explicitly using (3) lines, without a dependence on rel_q which is not needed there:
#
#			preΩ_q	=	O[	ixH	]	-	O[	ocª	];
#			postΩ_q	=	Oª[	inM	]	-	Oª[	ixΩ	];
#			relΩ_q	=	postΩ_q	-		preΩ_q;
#	
#	And in NX2L, the reflow of highpass in cube omega is simpler, as there is no modified data in that range.
#
#			relΩ_q	=	O[ 	ixΩ	]	-		oCS;	/* relative difference in NX2L cube-omega is due to rebalancing only	*/

	0xFDEA,		0xFDED,		0xFDF1,		0xFDF5,		0xFDFC..0xFDFE,	undef,
	0xFE01,		0xFE04,		0xFE08,		0xFE0A,		0xFE0C..0xFE0D,	0xFE12,		undef,
	0xFE1F..0xFE21,	0xFE27..0xFE29,	0xFE2B,		0xFE31,		0xFE33..0xFE34,	undef,
	0xFE37,		0xFE3A,		0xFE3D,		0xFE45,		0xFE4F..0xFE50,	undef,

	],	[	0xFDED,0xFE2A,0xFE32,0xFE3B	],
	[	#111:	the juke is nuke:  a rare _av_commit() error!	Here's what I learned:
#	When SV rebalancing is enabled, cube runs are enabled; _sv_commit_nx() is activated, which will utilize AvCUT2() defined in _AvSEQ.h.
#	AvCUT2 is a variant of AvCUT which can schedule multiple cubes for deletion at once.
#	The subsequent activation of AvCUT2() via ReBAL_ENABLE is the only imaginable effector of what I observed in _av_commit().
#	Precursor #111 causes (juke) to equal zero after the _asce{} block finishes.  This is effectively a null descending/expansion cycle,
#	if not for the intermediate _descx{} block, which is explained in the comments there.
#	Theoretically, there is nothing wrong with _descx{} being the only descending iteration, but curiously, it has never occurred
#	in all these millions of tests with ReBAL_ENABLE deactivated.
#
#	I found it very interesting to compare the pre-op resequencing schedules between two versions of this test:
#	the original as it is below, versus itself with just one change: the last argument commented out.
#	By commenting the final argument, the null juke condition was untriggered.
#	The main difference is the final _sv_commit_nx() subcase is NX3 instead of NX4, the cube run length also being 3 instead of 4.
#	Here we see that (1) less SV is created, and (1) less SV is destroyed, for the same net src/dst difference in step #3, but crucially,
#	it triggers (src-cut) to drop below (dst), which is the threshold of reversing from ascending/compaction to descending/expansion.
#
#	unmodified original:
#						commit schedule (pre process):
#							#               #0      #1      #2      #3      #4
#							rSeq_iR:         -1      -1      1       1       -1
#							rSeqIns:         0       0       2       0       0
#							rSeqCut:         0       1       0       2       0
#							rSeqSrc:         0       2       14      17      18
#							rSeqDst:         0       1       13      16      17
#	w/ last arg commented:
#						commit schedule (pre process):
#							#               #0      #1      #2      #3      #4
#							rSeq_iR:         -1      -1      0       0       -1
#							rSeqIns:         0       0       1       0       0
#							rSeqCut:         0       1       0       1       0
#							rSeqSrc:         0       2       14      16      18
#							rSeqDst:         0       1       13      15      17
#
#	I tried in vain to experimentally adjust this threshold so all 111 tests would still pass (far from it),
#	so eventually I thought to myself, "well, what if that part is actually working?" and I looked elsewhere.
#	Turns out, it seems to work fine when we make sure that if juke==0, only the initial descending iteration (_descx{}) can run.
#	Imagine that!  No, that's perfectly obvious, I just found it very surprising that this has never happened with AvCUT2() deactivated.
#	Unfortunately I have to stop here for now, because before I continue, I must disable ReBAL_ENABLE and run tests for a few hours
#	to make sure I haven't destabilized anything.
#
#	To be continued...
#
	0xFFA6..0xFFA8,	0xFFAB..0xFFAD,	0xFFB0,		0xFFB3,		0xFFB5..0xFFB7,	undef,
	0xFFBA,		0xFFBC..0xFFBD,	0xFFBF,		0xFFC1,		0xFFC6,		undef,
	0xFFCA,		0xFFCD,		0xFFCF..0xFFD0,	0xFFD2,		0xFFD5..0xFFD6,	undef,
	0xFFDA..0xFFDB,	0xFFDE,		0xFFE0,		0xFFE4..0xFFE5,	0xFFE7,		0xFFEA..0xFFEB,	0xFFF2..0xFFF3,	undef,
	0xFFF5,		0xFFFA..0xFFFB,	0xFFFD..0xFFFE,	0x10003..0x10005,	0x10008,		0x1000A,		0x1000C,		undef,
	0x1000E..0x10016,0x10018,		0x1001C..0x1001F,0x10023,		0x10025..0x10029,	0x1002B,		0x1002D..0x10038,	undef,
	0x1003A..0x1003B,0x1003E..0x1003F,0x10041..0x10042,0x10044,		0x10047,		0x10049..0x1004A,	0x1004F..0x10052,	undef,
	0x10054..0x10055,0x10057..0x1005D,0x1005F..0x10060,0x10062,		0x10067..0x1006A,	0x1006C,		undef,
	0x1006E..0x10072,0x10074..0x10075,0x10077..0x1007A,0x1007C,		0x1007F,		0x10081,		undef,
	0x10083..0x10086,0x10088..0x1008A,0x1008D,		0x1008F,		0x10092..0x10095,	undef,
	0x10097..0x1009B,0x1009E,		0x100A0..0x100A4,0x100A7,		0x100A9,		0x100AE,		undef,
	0x100B0,		0x100B3..0x100B8,0x100BA..0x100BB,0x100BD..0x100BE,	0x100C0,		0x100C2,		undef,
	0x100C5..0x100C9,0x100CC,		0x100CE,		0x100D1,		0x100D4,		0x100D6..0x100D7,	undef,
	0x100D9..0x100DB,0x100DD,		0x100E0..0x100E1,0x100E3,		0x100E5,		0x100E8,		undef,
	0x100EA..0x100EE,0x100F0..0x100F4,0x100F6..0x100FA,0x100FC,		0x100FE..0x10100,	0x10102,		undef,
	0x10106..0x10108,0x1010A,		0x1010E..0x1010F,0x10112..0x10114,	0x10117,		0x10119..0x1011B,	undef,
	0x1011F,		0x10121..0x10127,0x10129..0x1012B,0x1012D..0x10132,	0x10134..0x10139,	0x1013D,		0x1013F,		undef,
	0x10142..0x10144,0x10146..0x10147,0x1014C..0x10156,0x10158,		0x1015A,		0x1015C..0x1015E,	undef,
	0x10161..0x10162,0x10164,		0x10168..0x10169,0x1016B,		0x1016D..0x1016F,	0x10171,		0x10173,		undef,
	],	[
		0xFFB4,
		0xFFB8,0xFFC3,0xFFC7,0xFFCA,	0x10015,0x10038,0x10047,0x1006B,	0x100FA,0x10103,0x10123,0x1012A,
		0x1014F,
		],

	[	#112	"cube #1 checksum error"	ƒsub NX2L	changed preΩ_q calc from/to:
#			preΩ_q	=	O[	ixH	]	-	O[	ocª	];
#			preΩ_q	=	O[	ixH	]	-		oCS;
	0xFD43..0xFD44,	0xFD46,		0xFD48..0xFD4B,	0xFD4F,		0xFD52..0xFD57,	0xFD59..0xFD5C,	undef,
	0xFD5E..0xFD69,	0xFD6B..0xFD73,	0xFD76..0xFD79,	0xFD7C..0xFD82,	0xFD84..0xFD86,	0xFD89..0xFD90,	0xFD92,		undef,
	],	[
		0xFD45,0xFD46,0xFD5D,0xFD5E,
		0xFD80,
		],
	[	#113	"cube #1 checksum error"	ƒsub NX1	changed relΩ_q calc from/to:
#		relΩ_q=rel_q	+	Oª[	ocª	]	-		16;			/* relative difference in pre-to-post q for cube Ω		*/
#		relΩ_q=rel_q	+		oCS 	-		16;			/* relative difference in pre-to-post q for cube Ω		*/
	0xF852..0xF856,	0xF858..0xF85B,	0xF85E..0xF86B,	0xF86D..0xF86F,	0xF872,		0xF874..0xF877,	0xF879,		undef,
	0xF87B..0xF882,	0xF884..0xF88D,	0xF88F,																	undef,
	0xF891..0xF893,	0xF895..0xF896,	0xF899..0xF8A0,	0xF8A3..0xF8AD
	],	[	0xF883,	0xF899	],
	[	#114	"cube #2 checksum error"	ƒsub NX2L	added a crossload block from high cube to low cube, introducing hpº_q...
#			The nuance: while it is not possible for the modification range not to extend into the last cube of the pre-op cube run,
#			the new boundary of last cube of the post-op cube run (cube omega) can start anywhere before or after the mod range.
#			This means that while the pre-op highpass is always contained within the last cube of the pre-op cube run (*cube),
#			and while all or most of that highpass will remain in cube omega,
#			some of that highpass may need to be crossloaded to post-op cubeº—
#				depending on whether the q-data offset at the new cube-omega vector index ( O[ ixΩ ] )
#				is higher than the old q-data offset ( oCS ).
	0xFFFFF88D..0xFFFFF896,	0xFFFFF898..0xFFFFF89B,	0xFFFFF89D..0xFFFFF89F,	0xFFFFF8A3,		0xFFFFF8A6..0xFFFFF8AC,	undef,
	0xFFFFF8AE..0xFFFFF8B6,	0xFFFFF8B8..0xFFFFF8BD,	0xFFFFF8BF..0xFFFFF8C3,	0xFFFFF8C5..0xFFFFF8C6,	undef,
	0xFFFFF8C9,		0xFFFFF8CB,		0xFFFFF8CD..0xFFFFF8CF,	0xFFFFF8D1..0xFFFFF8D4,	0xFFFFF8D7..0xFFFFF8DB,	undef,
	0xFFFFF8DD..0xFFFFF8E3,	0xFFFFF8E5..0xFFFFF8F1,	0xFFFFF8F4,		0xFFFFF8F6..0xFFFFF8FA,	0xFFFFF8FC..0xFFFFF8FE,	0xFFFFF900..0xFFFFF903,	0xFFFFF905..0xFFFFF915,	0xFFFFF917..0xFFFFF91B,
	], [	0xFFFFF8AC,0xFFFFF8CC,0xFFFFF8DF ],
	[	#115:	"cube #3 checksum error"	ƒsub NX4-BCDE	changed hp²_o calc from/to
#;		hp²_o	=16+O[	ixH	]	-	O[	ocª	];		//	this should be notorious by now!
#;		hp²_o	=16+O[	ixH	]	-		oCS;		//	I searched for all occurrences of regex \bO\[\s*ocª
#;	


	0x1053C..0x1053F,0x10541..0x1054A,0x1054C..0x10551,	0x10554,		0x10556,		0x10558..0x1055A,	undef,
	0x1055D..0x10561,0x10563..0x1056F,0x10571,		0x10573..0x10574,	0x1057A..0x1057F,	0x10582..0x1058B,	undef,
	0x1058D,		0x10590,		0x10592..0x1059A,	0x1059D..0x1059F,	0x105A1,		undef,
	0x105A3..0x105A5,0x105A8..0x105AD,0x105AF,		0x105B1..0x105B3,	0x105B5..0x105B7,	undef,
	0x105B9,		0x105BB..0x105BD,0x105BF..0x105C1,	0x105C3..0x105CB,	0x105CF..0x105DB,	undef,
	0x105DD..0x105E5,0x105E7..0x105F1,0x105F3..0x105F8,	0x105FA..0x10600,	0x10602..0x10609,	0x1060B..0x1060E,	0x10610..0x10615,	0x10617..0x1061B,
	],	[ 0x10540,0x1058C,0x1059C,0x105AD,0x105DC	],
	[	#116:	"cube #1 checksum error"	ƒsub NX2H		FALSE FIX— see #117	changed ReFLOW_AC args from/to:	 
#	ReFLOW_AC(	cube,	cubeΩ,	relΩ_q, hpΩ_q, 16+Oª[ ixH]-Oª[ixΩ],	16+O[ ixH]-oCS,	__LINE__ );
#	ReFLOW_AC(	cube,	cubeΩ,	relΩ_q, hpΩ_q, 16+Oª[ ixH]-oCS,		16+O[ ixH]-oCS,	__LINE__ );
	0x102F4,			0x102F7,		0x102FA,			0x102FD,	0x10303,		0x10311..0x10313,	0x10318,		0x1031F,
	0x10323..0x10326,	0x1032B,	0x10335..0x10337,	0x10342,
	],	[ 0x1031E,0x1032E ],

	[	#117:	"cube #1 checksum error"	ƒsub NX2H		recurrence of #116  	changed ReFLOW_AC args from/to:
#	ReFLOW_AC(	cube,	cubeΩ,	relΩ_q, hpΩ_q, 16+Oª[ ixH]-oCS,		16+O[ ixH]-oCS,	__LINE__ );
#	ReFLOW_AC(	cube,	cubeΩ,	relΩ_q, hpΩ_q, 16+Oª[ ixH]-O[ixΩ],	16+O[ ixH]-oCS,	__LINE__ );	//#116 "before":
#	ReFLOW_AC(	cube,	cubeΩ,	relΩ_q, hpΩ_q, 16+Oª[ ixH]-Oª[ixΩ],	16+O[ ixH]-oCS,	__LINE__ );
#
#	...after thinking about it, the relative origin of post-op q-offset of vector ixH has to be post-op start of cube-omega.
#	The real reason #116 failed was because Oª[ ixΩ ] was not populated, but I realized I am abot to use the pre-op value
#	because in ƒsub NX2H, the whole point is the mod range is contained within cube-omega; it cannot start before ixΩ.
	0xFFFD47,		0xFFFD49,		0xFFFD4F,		0xFFFD56,		0xFFFD5E,		0xFFFD60,		0xFFFD6A,		undef,
	0xFFFD73,		0xFFFD77,		0xFFFD7A,		0xFFFD84,		undef,
	0xFFFD87,		0xFFFD8A..0xFFFD8B,	0xFFFD8D,		0xFFFD8F,		0xFFFD9B,		undef,
	0xFFFDAC,		0xFFFDAE,		0xFFFDB6,		0xFFFDBA..0xFFFDBB,	0xFFFDC3,		0xFFFDCA,		undef,
	],	[0xFFFD66,0xFFFD71],
	[	#118:	"cube #1 checksum error"	ƒsub 1x3-xxx		I'd forgotten to update the fragment boundary calcs...
		#												...when I implemented ixº and RACK.
	0xFFF826,	0xFFF847,		0xFFF84D,	0xFFF86B,	0xFFF880,	0xFFF8AB,	0xFFF8B8,	undef,
	0xFFF8C3,	0xFFF921,		0xFFF958,	0xFFF962,	0xFFF9C8,	0xFFF9F1,	0xFFFA11,	undef,

	],	[0xFFF84D,0xFFF8C7,0xFFF900,0xFFF90F,0xFFF935,0xFFF972,0xFFF976,0xFFF9B2,0xFFF9F5],
	[	#119:	"cube #2 checksum error"	ƒsub NX1		differentiated relΩ_q calc for when  inM<= ocª
#	before:
#				relΩ_q=rel_q	+		oCS 	-		16;
#	after:
#				preΩ_q = inM>ocª?	O[	inM	]	-		oCS:	0;
#				postΩ_q		=	Oª[	inM	]	-	O[	ixº	];
#				relΩ_q		=		postΩ_q	-		preΩ_q;
#
	0xFFFFFFFFFFFECC..0xFFFFFFFFFFFECF,	0xFFFFFFFFFFFED1..0xFFFFFFFFFFFEDC,	0xFFFFFFFFFFFEDE..0xFFFFFFFFFFFEE0,	0xFFFFFFFFFFFEE2,			0xFFFFFFFFFFFEE4..0xFFFFFFFFFFFEEF,	0xFFFFFFFFFFFEF1..0xFFFFFFFFFFFEFA,	0xFFFFFFFFFFFEFC..0xFFFFFFFFFFFEFF,	0xFFFFFFFFFFFF02..0xFFFFFFFFFFFF03,
	0xFFFFFFFFFFFF06,			0xFFFFFFFFFFFF08..0xFFFFFFFFFFFF09,	0xFFFFFFFFFFFF0B,			0xFFFFFFFFFFFF0E..0xFFFFFFFFFFFF13,	0xFFFFFFFFFFFF15..0xFFFFFFFFFFFF17,	undef,
	0xFFFFFFFFFFFF1A..0xFFFFFFFFFFFF20,	0xFFFFFFFFFFFF22..0xFFFFFFFFFFFF23,	0xFFFFFFFFFFFF25..0xFFFFFFFFFFFF26,	0xFFFFFFFFFFFF28..0xFFFFFFFFFFFF31,	undef,
	0xFFFFFFFFFFFF33..0xFFFFFFFFFFFF42,	0xFFFFFFFFFFFF44..0xFFFFFFFFFFFF54,	0xFFFFFFFFFFFF56..0xFFFFFFFFFFFF5D,	0xFFFFFFFFFFFF5F..0xFFFFFFFFFFFF63,	0xFFFFFFFFFFFF65..0xFFFFFFFFFFFF67,	0xFFFFFFFFFFFF69..0xFFFFFFFFFFFF6D,	undef,
	],	[ 0xFFFFFFFFFFFEFD,0xFFFFFFFFFFFF1E,0xFFFFFFFFFFFF32,0xFFFFFFFFFFFF43 ],	#hex
	[	#120	"cube #1 checksum error"		NX2L		looks very similar to #119...
#		
#
#
	0xFFFFFFFFFFFBE9,			0xFFFFFFFFFFFBEB..0xFFFFFFFFFFFBED,	0xFFFFFFFFFFFBEF,	0xFFFFFFFFFFFBF1,			0xFFFFFFFFFFFBF3,			undef,
	0xFFFFFFFFFFFBF9,			0xFFFFFFFFFFFBFB,			0xFFFFFFFFFFFC00,	0xFFFFFFFFFFFC04,			0xFFFFFFFFFFFC07,			undef,
	0xFFFFFFFFFFFC10..0xFFFFFFFFFFFC11,	0xFFFFFFFFFFFC1B,			0xFFFFFFFFFFFC1E,	0xFFFFFFFFFFFC21..0xFFFFFFFFFFFC28,	0xFFFFFFFFFFFC2B..0xFFFFFFFFFFFC2F,	0xFFFFFFFFFFFC31,	0xFFFFFFFFFFFC34..0xFFFFFFFFFFFC36,	0xFFFFFFFFFFFC3A..0xFFFFFFFFFFFC3B,
	],	[	0xFFFFFFFFFFFBFA,0xFFFFFFFFFFFC0F],	#hex
	[	#121
	0xFFFFFFFFFF6E..0xFFFFFFFFFF7D,			0xFFFFFFFFFF7F..0xFFFFFFFFFF81,			0xFFFFFFFFFF83..0xFFFFFFFFFF97,			0xFFFFFFFFFF99..0xFFFFFFFFFFA1,			0xFFFFFFFFFFA3..0xFFFFFFFFFFA5,			0xFFFFFFFFFFA7,						0xFFFFFFFFFFA9..0xFFFFFFFFFFB0,			0xFFFFFFFFFFB2..0xFFFFFFFFFFBF,
	0xFFFFFFFFFFC1..0xFFFFFFFFFFC7,			0xFFFFFFFFFFC9..0xFFFFFFFFFFD5,			0xFFFFFFFFFFD9..0xFFFFFFFFFFE3,			0xFFFFFFFFFFE5..0xFFFFFFFFFFF3,			0xFFFFFFFFFFF5..0xFFFFFFFFFFF6,			0xFFFFFFFFFFF8..0x100000000000E,		undef,
	0x1000000000010..0x1000000000017,		0x1000000000019..0x100000000002E,		0x1000000000030..0x1000000000041,		0x1000000000043..0x1000000000060,		0x1000000000062..0x1000000000069,		0x100000000006B,					undef,
	0x100000000006D..0x100000000007E,	0x1000000000080..0x1000000000081,		0x1000000000083..0x1000000000091,		0x1000000000093..0x10000000000BD,	0x10000000000BF..0x10000000000C3,	0x10000000000C5..0x10000000000C8,	0x10000000000CA,					undef,
	0x10000000000CC..0x10000000000DA,	0x10000000000DC..0x10000000000DD,	0x10000000000DF,					0x10000000000E1..0x10000000000FA,		0x10000000000FC..0x1000000000103,		undef,
	0x1000000000105..0x1000000000106,		0x1000000000108..0x1000000000119,		0x100000000011B..0x100000000011D,	0x100000000011F..0x1000000000125,		0x1000000000127..0x1000000000144,		undef,
	0x1000000000146,						0x1000000000148..0x100000000014C,	0x100000000014E..0x1000000000151,		0x1000000000153..0x1000000000156,		0x1000000000158..0x100000000015F,		undef,
	0x1000000000161..0x100000000016C,	0x100000000016E..0x1000000000182,		0x1000000000184..0x1000000000187,		0x1000000000189..0x1000000000193,		0x1000000000195..0x10000000001A4,	0x10000000001A6..0x10000000001AE,	undef,
	0x10000000001B0..0x10000000001B6,	0x10000000001B8..0x10000000001C8,	0x10000000001CA..0x10000000001CC,	0x10000000001CE..0x10000000001DC,	0x10000000001DF..0x10000000001EA,	0x10000000001EC..0x10000000001F3,		undef,
	0x10000000001F5,						0x10000000001F7..0x1000000000207,		0x1000000000209..0x100000000020C,	0x100000000020E..0x100000000020F,		0x1000000000211..0x1000000000212,		0x1000000000214..0x100000000021A,	undef,
	0x100000000021C..0x100000000022F,		0x1000000000231..0x1000000000233,		0x1000000000235..0x1000000000250,		0x1000000000252..0x1000000000270,		0x1000000000272..0x100000000027D,	0x100000000027F..0x1000000000281,		0x1000000000283..0x1000000000284,		undef,
	0x1000000000286..0x1000000000295,		0x1000000000297..0x100000000029B,	0x100000000029D..0x100000000029E,	0x10000000002A0,					0x10000000002A2..0x10000000002AB,	0x10000000002AD..0x10000000002B6,	undef,
	0x10000000002B8..0x10000000002BC,	0x10000000002BE..0x10000000002C8,	0x10000000002CA..0x10000000002D4,	0x10000000002D6..0x10000000002D7,	0x10000000002D9..0x10000000002DA,	0x10000000002DC..0x10000000002DD,	undef,
	0x10000000002DF..0x10000000002E5,	0x10000000002E7..0x10000000002F5,		0x10000000002F7..0x10000000002F9,		0x10000000002FB..0x100000000030D,	0x100000000030F..0x1000000000321,		undef,
	0x1000000000323,						0x1000000000325..0x1000000000328,		0x100000000032A..0x1000000000355,	0x1000000000357..0x100000000036F,		0x1000000000371..0x1000000000373,		0x1000000000375..0x100000000038C,	undef,
	0x100000000038E..0x1000000000396,		0x1000000000398..0x10000000003AD,	0x10000000003AF..0x10000000003B4,	0x10000000003B6..0x10000000003BF,	undef,
	0x10000000003C1..0x10000000003D0,	0x10000000003D2..0x10000000003E6,	0x10000000003E8..0x10000000003EE,		0x10000000003F0..0x10000000003FC,		undef,
	0x10000000003FE..0x1000000000414,		0x1000000000416..0x1000000000418,		0x100000000041A..0x1000000000421,	0x1000000000423..0x1000000000424,		undef,
	0x1000000000426..0x100000000042A,	0x100000000042C..0x1000000000446,	0x1000000000448..0x100000000044D,	0x100000000044F..0x1000000000453,		undef,
	0x1000000000455..0x1000000000458,		0x100000000045A..0x1000000000465,	0x1000000000468..0x1000000000475,		0x1000000000477..0x10000000004A0,	0x10000000004A2..0x10000000004A5,	0x10000000004A8..0x10000000004A9,	0x10000000004AB..0x10000000004B0,	undef,
	0x10000000004B2..0x10000000004B4,	0x10000000004B6..0x10000000004C2,	0x10000000004C4..0x10000000004C6,	0x10000000004C8..0x10000000004CB,	0x10000000004CD..0x10000000004DA,	0x10000000004DC..0x10000000004DD,	0x10000000004DF..0x10000000004E0,	undef,
	0x10000000004E2..0x10000000004F3,		0x10000000004F6..0x10000000004F9,		0x10000000004FB..0x1000000000502,		0x1000000000504,						0x1000000000506..0x100000000050B,	undef,
	0x100000000050D..0x100000000050F,	0x1000000000512..0x100000000051E,		0x1000000000520..0x1000000000532,		0x1000000000534..0x100000000053C,	0x100000000053E..0x1000000000547,		0x1000000000549..0x1000000000557,		undef,
	0x1000000000559..0x100000000056B,	0x100000000056D,					0x100000000056F..0x1000000000571,		0x1000000000573..0x100000000057F,		0x1000000000581..0x1000000000583,		undef,
	0x1000000000585..0x100000000058B,	0x100000000058D..0x1000000000599,	0x100000000059B..0x10000000005A0,	0x10000000005A5..0x10000000005BD,	0x10000000005BF..0x10000000005CC,	0x10000000005CE..0x10000000005D1,	0x10000000005D3..0x10000000005DE,	undef,
	0x10000000005E0..0x10000000005E8,		0x10000000005EA..0x10000000005F8,		0x10000000005FA,						0x10000000005FC..0x1000000000602,		0x1000000000605..0x100000000060E,		0x1000000000610..0x100000000061A,	0x100000000061C,					undef,
	0x100000000061E..0x1000000000639,		0x100000000063C..0x100000000063D,	0x100000000063F..0x100000000064C,		0x100000000064E..0x1000000000656,		0x1000000000658..0x100000000065E,		undef,
	0x1000000000660..0x1000000000662,		0x1000000000664..0x1000000000667,		0x100000000066A..0x100000000066C,	0x100000000066E..0x1000000000679,		0x100000000067B..0x1000000000681,	0x1000000000683..0x100000000068A,	undef,
	0x100000000068C..0x1000000000694,	undef,
	0x1000000000696..0x10000000006A2,	0x10000000006A4..0x10000000006B2,	0x10000000006B4..0x10000000006B6,	0x10000000006B8..0x10000000006C2,	0x10000000006C4..0x10000000006DD,	0x10000000006DF..0x10000000006E7,	0x10000000006E9..0x1000000000707,		undef,
	0x1000000000709..0x1000000000711,		0x1000000000713..0x1000000000717,		0x1000000000719..0x100000000071C,	0x100000000071E..0x1000000000721,		0x1000000000723..0x1000000000726,		0x1000000000728..0x100000000073F,		undef,
	],	[
		0x1000000000224,0x10000000002C7,0x10000000002CE,0x1000000000348,0x100000000039D,0x10000000003B2,0x10000000003D0,0x1000000000411,0x100000000042E,0x1000000000449,0x100000000047E,0x1000000000543,0x1000000000579,0x100000000057B,0x100000000058E,0x1000000000675,0x1000000000695,0x10000000006A3,
		],
	[	#122	fuckin' crazy... cube run of 1..37 from only 64 randomly-generated arguments, and it definitely overflows the vector map.
		#	_sv_commit_nx(258):	locus :	1.0..30.6		preº_xc:	0		pre1_xc:	0		pre²_xc:	0	preΩ_xc:	6	CS: 18	bytes	oCS: 139 bytes
		#		ƒsub NX235-BCCD	matrix:	0..258		postº_xc:	6		post1_xc: 0		post²_xc:	0	postΩ_xc:6	CSI/1/Y/Z: 22/21/19/18 bytes
		#				iCI..iCª:	1..37	relº_c: 0		rel1_c:	0		rel²_c:	0		relΩ_c:	0
		#				 oc /xc :	196/202	lpº_c: n/a		lpº_c:	-102	lp²_c:	n/a		lpΩ_c:	n/a
		#				 ocª/xcª:	251/258	hpº_c: n/a	hp1_c:	n/a		hp²_c:	-45		hpΩ_c:	0
		#				zc/zcΩ:	6/6		 preº_q: n/a	pre1_q:	n/a		pre²_q:	n/a		preΩ_q:	2
		#								 postº_q: 136	post1_q:	5		post²_q:	5		postΩ_q:	2
		#								relº_q: n/a	rel1_q:	n/a		rel²_q:	n/a		relΩ_q:	0
		#								lpº_q: n/a		lp1_q:	0		lp²_q:	n/a		lpΩ_q:	0
		#								hpº_q: n/a	hp1_q:	n/a		hp²_q:	7		hpΩ_q:	0
		#
	0xF9C3,          0xF9DD,          0xF9E6,          0xFA01,            0xFA1D..0xFA1E,    0xFA22,            0xFA2E,  undef,
	0xFA37,          0xFA42,          0xFA4A,          0xFA57..0xFA58,    0xFA7D,            0xFA98,            0xFACB,  undef,
	0xFAD6,          0xFAEF,          0xFAFD,          0xFB01,            0xFB05,            0xFB2B,            0xFB2D,  undef,
	0xFB2F,          0xFB53,          0xFB73,          0xFB85,            0xFB8C,            0xFBA2,            0xFBBB,  undef,
	0xFBC1,          0xFBD3,          0xFBDC,          0xFC2A,            0xFC31,            0xFC3C,            0xFC53,  undef,
	0xFC5B,          0xFC68,          0xFC6F,          0xFCB1,            0xFCC7,            0xFCD1,            undef,
	0xFCF1,          0xFCFB,          0xFCFD,          0xFD04,            0xFD0B,            0xFD15,            0xFD1F,  undef,
	0xFD2D,          0xFD59,          0xFD60,          0xFD67,            0xFDBB,            0xFDC1,            undef,
	0xFDE5,          0xFDEA,          0xFDF4,          0xFDFC,            0xFE02,            0xFE09..0xFE0A,    0xFE29,  undef,
	0xFE30..0xFE31,  0xFE46,          0xFE48,          0xFE52,            0xFE56,            0xFE59,            0xFE84,  undef,
	0xFE9B..0xFE9C,  0xFEA0,          0xFEA5,          0xFED4,            0xFEE1,            0xFEE3,            0xFF00,  undef,
	0xFF0C,          0xFF39,          0xFF52,          0xFF5F,            0xFF63,            0xFF77,            0xFF79,  undef,
	0xFF7E,          0xFF90,          0xFF92,          0xFF96,            0xFFA1,            0xFFCC,            0xFFE7,  undef,
	0xFFEE,          0xFFF5,          0x1000C,         0x10016,           0x10029,           0x10037,           0x10040, undef,
	0x1004E,         0x10065,         0x10069,         0x10089,           0x100A5,           0x100C4,           0x100E6, undef,
	0x100F0,         0x100F4,         0x100F7..0x100F8,0x10109,           0x1011C,           0x1012B,           0x10134, undef,
	0x10138,         0x1013B..0x1013C,0x10161,         0x10177,           0x10187,           0x1018F,           0x10197, undef,
	0x101A8,         0x101C3,         0x101D6,         0x101D8,           0x101F0,           0x101F7,           undef,
	0x10219,         0x10226,         0x1023A,         0x1023D,           0x10250,           0x10259..0x1025A,  0x10268, undef,
	0x10275,         0x102C0..0x102C1,0x102C7,         0x102CD,           0x102DB,           0x102E1,           undef,
	0x10311,         0x1031C,         0x10323,         0x1032B..0x1032C,  0x10331,           0x10361,           undef,
	0x10367,         0x1036F,         0x1037C,         0x1039A,           0x10400,           0x1041E,           0x10442, undef,
	0x10467,         0x1046D,         0x1048F,         0x10495,           0x104D8..0x104D9,  0x104DB,           0x104E3, undef,
	0x104E7,         0x104ED,         0x104F9,         0x10511,           0x1051C,           0x10524,           0x10526, undef,
	0x10539,         0x10552,         0x10564,         0x1057A,           0x1057E,           0x1058D,           undef,
	0x105AD,         0x105BA,         0x105E4,         0x105E6,           0x1060E,           0x10618,           undef,
	0x10623,         0x1062C,         0x10639..0x1063A,0x1063C,           0x10656,           0x1066C,           0x10686, undef,
	0x10688,         0x106A4,         0x106B0,         0x106B9,           0x106DF,           0x106E1,           0x106EE, undef,
	0x10714,         0x10717,         0x10719,         0x1073A,           0x1073D,           0x10744,           0x1074A, undef,
	0x10755..0x10756,0x10758,         0x10776..0x10777,0x1077D,           0x10798,           0x1079C,           0x107B8, undef,
	0x107BA,         0x107C0,         0x107DF,         0x107E3..0x107E4,  0x107E6,           0x107F6,           0x107FD, undef,

	],      [0xFA31,0xFB12,	0xFB59,0xFB5C,	0xFBEE,0xFCAF,	0xFCD9,0xFD20,
		0xFD54,0xFD78,	0xFD84,0xFD9C,	0xFDA2,0xFDDA,	0xFE78,0xFE7E,
		0xFE9E,0xFEF6,	0xFF03,0xFF16,	0xFF5B,0xFF6B,	0xFF6C,0xFFA6,
		0x10023,0x1003B,	0x10051,0x100AD,	0x10127,0x1015F,	0x10166,0x1017B,
		0x10196,0x101AF,	0x101E4,0x1023D,	0x10287,0x10292,	0x102D0,0x10319,
		0x10378,0x10385,	0x103FB,0x10413,	0x1042B,0x104AF,	0x104E5,0x10543,
		0x105BB,0x10611,	0x10617,0x1061D,	0x10627,0x10637,	0x1064D,0x106D2,
		0x106E6,0x1071D,	0x10723,0x1075A,	0x10790,0x107FB	],
	[	#123	main buffer overrun protection implemented since #122.  Works great with up to 14-bit NS; 15-bit errs.
	#			program was crashing with "Out of memory in perl:util:safesysmalloc".
	#			It took two days to track it down to the newSVpvz() calls in NXN-xxCx, xCxx, and xxAxx.
	#			A sanity check I implemented very early on would have caught it, if it had been arranged to execute first.  lol, damn.
	#			Turns out, CS* is negative because Oª[ ixΩ ]< Oª[ ix² ]; in fact, Oª[ ixΩ ] is going very low, like 2.. way less than 16.
	#			I anticipate this will be another long investigation.
	#	2026-10-07 (the next morning)
	#			This was very straightforward, actually.  (unsigned char *) O[256] and (unsigned char *) Oª[ 256 ] are overflowing.
	#			Of course they are!  (char) is very under-sized for mapping multiple cubes!
	#			It would work fine with ReBAL_ENABLE turned off, but even a short run of cubes could easily exceed that.
	#			The reason we didn't see problems with NS < 15-bits is the increased NS also increased avg. encoded data length.
	#			How much memory is this buffer going to require to bump these up to (unsigned short *) O[ 256 ]?
	#			16mb each??  Oh dear.  What else can I do?  Create a variant with 8-bit carry and write an efficient qualifier for it.
	#
	#	There is one very fortunate caveat about the incrementation of the proposed 9th-bit-up carry field:
	#	It always starts at 0 and increments by 1, when it increments, because 144< 256.
	#	As long as the basic template for the cube maxes out at less than 256, this assertion holds.
	#	Keep this important note in mind if ever such an architectural change would be in order.
	#
	#	This fortuitous constraint could allow for a very memory efficient run-length storage, where
	#	instead of storing the high bytes directly, we store the vmap indeces at which these successive incrementations occur.
	#
	#	/* In ReICEuO, after this:	*/	Oª[ $v ] = O[ $u ] +( L[ $u ]=1 +q );
	#	/*	—add the following:	*/	if( ( 256-L )< O[ $u ] )	Oflow[ ofc++ ] = $u;	/* count the overflow */
	#
	#	But then, it only works as neatly if we can do our O[]-based calculations also in successive order of value.
	#	In NX1, I know that the last two cubes are created first, then the first two, then the intermediates / engodenous.
	#	This was to avoid having to buffer the value of *Edge( cubeº ), but that is not necessary in NXN.
	#	So I just changed it around in NXN, and it works!  Passes all the precursor tests, and it seems stable, but let's make sure...
	#	I'll leave it running tests while I'm away getting coffee.
	#	While I'm at it, I'll also trivially call out O[] and Oª[] as (unsigned short *) to confirm the diagnosis for precursor #123...
	#	Well, that's strange.  It seems to be working but the RAM consumption hasn't shot up past 64mb, like I thought...
	#	It's using 15mb versus previous 12mb, though that could be accounted for by actual 15-bit NS operation (it works).
	#	Is there magic in the standard C library to conserve the unused portion of my crazy (unsigned short *) O[ 256 ] arrays?
	#	Oh.  I checked my math.  There is no magic and no need to worry about the allocation size of the vmap.
	#	(unsigned short *) O[ 512 ] only requires 1kb.  duh...............! haha!

0xC000..0xC069,    0xC06B..0xC06E,    0xC070,            0xC072..0xC08C,    0xC08E..0xC09E,    0xC0A0..0xC0C7,    undef,
0xC0C9..0xC17B,    0xC17D..0xC1AC,    0xC1AE..0xC238,    0xC23A..0xC275,    0xC277..0xC33C,    0xC33E..0xC3E0,    undef,
0xC3E2..0xC3FE,    0xC400..0xC428,    0xC42A..0xC4D5,    0xC4D7..0xC4F2,    0xC4F4..0xC586,    0xC588..0xC673,    undef,
0xC675..0xC6E4,    0xC6E6..0xC7B7,    0xC7B9..0xC7E0,    0xC7E2..0xC863,    0xC865..0xC866,    0xC868..0xC8A1,    undef,
0xC8A3..0xC944,    0xC946..0xCA42,    0xCA44..0xCAAA,    0xCAAC..0xCAD8,    0xCADA..0xCB32,    0xCB34..0xCB74,    0xCB76..0xCC39,    undef,
0xCC3B..0xCC87,    0xCC89..0xCDBA,    0xCDBC..0xCE4A,    0xCE4C..0xCFE5,    0xCFE7..0xCFFB,    0xCFFD..0xD0C5,    0xD0C7..0xD162,    undef,
0xD164..0xD17E,    0xD180..0xD1E7,    0xD1E9..0xD200,    0xD202..0xD2FF,    0xD301..0xD34E,    0xD350..0xD37A,    0xD37C..0xD450,    undef,
0xD452..0xD459,    0xD45B..0xD47C,    0xD47E..0xD483,    0xD485..0xD4B2,    0xD4B4..0xD50F,    0xD511..0xD590,    0xD592..0xD64B,    undef,
0xD64D..0xD64F,    0xD651..0xD729,    0xD72B..0xD7FE,    0xD800..0xD82E,    0xD830..0xD838,    0xD83A..0xD89D,    0xD89F..0xD8E9,    undef,
0xD8EB..0xD90C,    0xD90E..0xD91B,    0xD91D..0xD961,    0xD963..0xD9B4,    0xD9B6..0xD9DA,    0xD9DC..0xDA44,    0xDA46..0xDB84,    undef,
0xDB86..0xDC5E,    0xDC60..0xDC7E,    0xDC80..0xDC92,    0xDC94..0xDCF1,    0xDCF3..0xDD1E,    0xDD20..0xDE0D,    0xDE0F..0xDE56,    undef,
0xDE58..0xDF2D,    0xDF2F..0xDF38,    0xDF3A..0xDF4C,    0xDF4E..0xE018,    0xE01A..0xE0A6,    0xE0A8..0xE0AD,    0xE0AF..0xE0EA,    undef,
0xE0EC..0xE0F4,    0xE0F6..0xE151,    0xE153..0xE167,    0xE169..0xE20A,    0xE20C..0xE26B,    0xE26D..0xE2BE,    0xE2C0..0xE320,    undef,
0xE322..0xE33B,    0xE33D..0xE395,    0xE397..0xE461,    0xE463..0xE473,    0xE475..0xE499,    0xE49B..0xE4A9,    0xE4AB..0xE528,    undef,
0xE52A..0xE558,    0xE55A..0xE57B,    0xE57D..0xE5EF,    0xE5F1..0xE617,    0xE619..0xE681,    0xE683..0xE788,    0xE78A..0xE827,    undef,
0xE829..0xE89B,    0xE89D..0xE8EB,    0xE8ED..0xE916,    0xE918..0xE93E,    0xE940..0xE95B,    0xE95D..0xE96C,    0xE96E..0xE9B1,    undef,
0xE9B3..0xEA24,    0xEA26..0xEAA4,    0xEAA6..0xEAAE,    0xEAB0..0xEAB4,    0xEAB6..0xEAD4,    0xEAD6..0xEC4A,    0xEC4C..0xEC75,    undef,
0xEC77..0xEC93,    0xEC95..0xECF6,    0xECF8..0xECFA,    0xECFC..0xED45,    0xED47..0xED80,    0xED82..0xED86,    0xED88..0xEE48,    undef,
0xEE4A..0xEE4F,    0xEE51..0xEEEA,    0xEEEC..0xEF76,    0xEF78..0xEFFF,    0xF001..0xF016,    0xF018..0xF138,    0xF13A..0xF152,    undef,
0xF154..0xF170,    0xF172..0xF17D,    0xF17F..0xF190,    0xF192..0xF1F8,    0xF1FA..0xF219,    0xF21B..0xF29B,    0xF29D..0xF2DF,    undef,
0xF2E1..0xF2FD,    0xF2FF..0xF30C,    0xF30E..0xF34E,    0xF350..0xF386,    0xF388..0xF3B4,    0xF3B6..0xF4EE,    0xF4F0..0xF5AB,    undef,
0xF5AD..0xF6B4,    0xF6B6..0xF6E2,    0xF6E4..0xF7E3,    0xF7E5..0xF825,    0xF827..0xF83E,    0xF840..0xF875,    0xF877..0xF879,    undef,
0xF87B..0xF89B,    0xF89D..0xF948,    0xF94A..0xFA7A,    0xFA7C..0xFAFE,    0xFB00..0xFB33,    0xFB35..0xFBAC,    0xFBAE..0xFBD9,    undef,
0xFBDB..0xFC0E,    0xFC10..0xFCED,    0xFCEF..0xFCF6,    0xFCF8..0xFD3F,    0xFD41..0xFD5A,    0xFD5C..0xFD67,    0xFD69..0xFD9C,    undef,
0xFD9E..0xFE9D,    0xFE9F,            0xFEA1..0xFF38,    0xFF3A..0xFF70,    0xFF72..0x1000F,   0x10011..0x10065,  0x10067..0x100BB,  undef,
0x100BD..0x10117,  0x10119..0x1011F,  0x10121..0x1017E,  0x10180..0x101EF,  0x101F1..0x10244,  0x10246..0x102AE,  0x102B0..0x102BD,  undef,
0x102BF..0x10314,  0x10316..0x1036F,  0x10371..0x103A6,  0x103A8..0x10401,  0x10403..0x10466,  0x10468..0x104FA,  0x104FC..0x10594,  undef,
0x10596..0x105A5,  0x105A7..0x1064B,  0x1064D..0x1069F,  0x106A1..0x106C8,  0x106CA..0x10748,  0x1074A..0x10777,  0x10779..0x107AE,  undef,
0x107B0..0x107FB,  0x107FD..0x108B2,  0x108B4..0x1098E,  0x10990..0x109B2,  0x109B4..0x10A36,  0x10A38..0x10A9F,  0x10AA1..0x10AD7,  undef,
0x10AD9..0x10B3B,  0x10B3D..0x10B5C,  0x10B5E..0x10C68,  0x10C6A..0x10CE7,  0x10CE9..0x10D16,  0x10D18..0x10D35,  0x10D37..0x10D59,  undef,
0x10D5B..0x10DB1,  0x10DB3..0x10F0B,  0x10F0D..0x10FCF,  0x10FD1..0x10FE4,  0x10FE6..0x110D9,  0x110DB..0x11109,  0x1110C..0x11156,  undef,
0x11158..0x112BA,  0x112BC..0x112EB,  0x112ED..0x1132C,  0x1132E..0x113A3,  0x113A5..0x114BF,  0x114C1..0x1161F,  0x11621..0x116E0,  undef,
0x116E2..0x1175B,  0x1175D..0x11762,  0x11764..0x117AB,  0x117AD..0x117AE,  0x117B0..0x117B7,  0x117B9..0x11850,  0x11852..0x11977,  undef,
0x11979..0x11991,  0x11993..0x119A8,  0x119AA..0x119DF,  0x119E1..0x11A44,  0x11A46..0x11AD7,  0x11AD9..0x11AE6,  0x11AE9..0x11B78,  undef,
0x11B7A..0x11BFB,  0x11BFD..0x11C2B,  0x11C2D..0x11C46,  0x11C48..0x11C60,  0x11C62..0x11D26,  0x11D28..0x11D38,  0x11D3A..0x11D5B,  undef,
0x11D5D..0x11D7D,  0x11D7F..0x11E05,  0x11E07..0x11E3A,  0x11E3C..0x11E93,  0x11E95..0x11EC8,  0x11ECA..0x11ECD,  0x11ECF..0x11EFA,  undef,
0x11EFC..0x11F01,  0x11F03..0x11F1F,  0x11F21..0x11F2C,  0x11F2E..0x11F3E,  0x11F40..0x11F5A,  0x11F5C..0x11F6D,  undef,
0x11F6F..0x11F7C,  0x11F7E..0x11F88,  0x11F8A..0x11F90,  0x11F92..0x11F9F,  0x11FA1..0x11FCB,  0x11FCD..0x11FD0,  0x11FD2..0x120A0,  undef,
0x120A2..0x12182,  0x12184..0x121B8,  0x121BA..0x1231A,  0x1231C..0x12364,  0x12366..0x12369,  0x1236B..0x123AA,  0x123AC..0x123AF,  undef,
0x123B1..0x123E7,  0x123E9..0x124B7,  0x124B9..0x124F0,  0x124F2..0x12645,  0x12647..0x12675,  0x12677..0x126D6,  0x126D8..0x12823,  undef,
0x12825..0x1283E,  0x12840..0x12851,  0x12853..0x1287E,  0x12880..0x128B3,  0x128B5..0x12904,  0x12906..0x12939,  0x1293B..0x129DD,  undef,
0x129DF..0x12AAE,  0x12AB0..0x12AC3,  0x12AC5..0x12B28,  0x12B2A..0x12B2E,  0x12B30..0x12B36,  0x12B38..0x12B8B,  0x12B8D..0x12BB5,  undef,
0x12BB7..0x12CAD,  0x12CAF..0x12CB5,  0x12CB7..0x12D47,  0x12D49..0x12D50,  0x12D52..0x12E02,  0x12E04..0x12E8E,  0x12E90..0x12EA8,  undef,
0x12EAA..0x12EEB,  0x12EED..0x1305E,  0x13060..0x130E3,  0x130E5..0x13181,  0x13183..0x13244,  0x13246..0x13297,  0x13299..0x132AF,  undef,
0x132B2..0x132C3,  0x132C5..0x132C9,  0x132CB..0x1343B,  0x1343D..0x13469,  0x1346B..0x1347F,  0x13481..0x13524,  undef,
0x13526..0x13552,  0x13554..0x13589,  0x1358B..0x135E7,  0x135E9..0x1360C,  0x1360E..0x1366B,  0x1366D..0x13697,  undef,
0x13699..0x136C2,  0x136C4..0x137FC,  0x137FE..0x13812,  0x13814..0x13820,  0x13822..0x13898,  0x1389A..0x138CA,  0x138CC..0x139DA,  undef,
0x139DC..0x139F8,  0x139FA..0x139FF,  0x13A01..0x13A16,  0x13A18..0x13AA4,  0x13AA6..0x13ABA,  0x13ABC..0x13B20,  0x13B22..0x13B51,  undef,
0x13B53..0x13B56,  0x13B58..0x13B9C,  0x13B9E..0x13BFB,  0x13BFD..0x13C60,  0x13C62..0x13C8C,  0x13C8E..0x13E6E,  undef,
0x13E70..0x13E73,  0x13E75..0x13EED,  0x13EEF..0x13F44,  0x13F46..0x13F6A,  0x13F6C..0x13FFF,  undef,

],      [0xC008,0xC071,0xC0A5,0xC0AD,0xC1DE,0xC20D,0xC21D,0xC228,0xC274,0xC290,0xC293,0xC2F8,0xC308,0xC32B,0xC330,0xC336,0xC3CF,0xC407,0xC443,0xC453,0xC486,0xC529,0xC65F,0xC684,0xC6A3,0xC6A6,0xC6D8,0xC706,0xC70A,0xC70D,0xC78E,0xC807,0xC81A,0xC880,0xC8AA,0xC8FB,0xC917,0xC97B,0xC99A,0xC9BF,0xC9D1,0xCA24,0xCA2D,0xCA7C,0xCB9E,0xCC84,0xCC8A,0xCC97,0xCD0E,0xCD27,0xCD34,0xCD37,0xCDE3,0xCDE5,0xCE3D,0xCE4A,0xCE82,0xCEFA,0xCFA6,0xCFC9,0xD001,0xD081,0xD097,0xD0A0,0xD0A2,0xD0B9,0xD153,0xD19F,0xD1E6,0xD33D,0xD358,0xD35C,0xD367,0xD3BD,0xD3D0,0xD466,0xD4D2,0xD4E1,0xD527,0xD528,0xD54E,0xD5BE,0xD5CD,0xD5F6,0xD653,0xD70D,0xD71C,0xD72B,0xD77F,0xD7A3,0xD7A9,0xD7BD,0xD7D0,0xD82B,0xD82F,0xD87F,0xD8C6,0xD8D7,0xD9C1,0xD9FA,0xDA24,0xDA25,0xDAAF,0xDB47,0xDB4C,0xDBB9,0xDC03,0xDC9D,0xDD38,0xDD3C,0xDD44,0xDD52,0xDD67,0xDDAB,0xDDBB,0xDDF4,0xDE05,0xDE1B,0xDF04,0xDFCF,0xDFDA,0xE046,0xE06D,0xE089,0xE0B3,0xE10A,0xE1F2,0xE20B,0xE284,0xE2AF,0xE36F,0xE3C0,0xE3C1,0xE409,0xE42B,0xE46E,0xE4C6,0xE590,0xE5B9,0xE60B,0xE61C,0xE69A,0xE6BD,0xE71D,0xE752,
0xE753,0xE781,0xE7CC,0xE80E,0xE813,0xE854,0xE8D0,0xE93C,0xE95E,0xE9CD,0xEA58,0xEC06,0xEC70,0xEC7C,0xECE1,0xECF3,0xED0E,0xED4B,0xED69,0xEDBC,0xEE37,0xEE3C,0xEE75,0xEEA2,0xEF2A,0xEF69,0xEFA4,0xEFA5,0xF051,0xF072,0xF09A,0xF0A4,0xF0A6,0xF0B2,0xF0D1,0xF0F1,0xF0F2,0xF0FD,0xF102,0xF12F,0xF166,0xF18E,0xF1A4,0xF1B1,0xF1BB,0xF286,0xF294,0xF29C,0xF2F3,0xF2F6,0xF30D,0xF36E,0xF3F7,0xF411,0xF42E,0xF540,0xF57F,0xF5A3,0xF5DB,0xF66D,0xF67B,0xF69A,0xF72E,0xF7A4,0xF7B6,0xF81D,0xF87B,0xF8A6,0xF8B2,0xF943,0xF983,0xF9D8,0xFA62,0xFAC6,0xFAE0,0xFB34,0xFB8B,0xFBF6,0xFBFE,0xFC0F,0xFC49,0xFC6F,0xFC7E,0xFC7F,0xFD1D,0xFD28,0xFD45,0xFD60,0xFDB1,0xFE29,0xFE83,0xFEC0,0xFEE1,0xFF28,0xFF83,0xFFE1,0x1001A,0x10028,0x10046,0x1004E,0x10055,0x100CD,0x10106,0x10137,0x10146,0x1014C,0x101AE,0x10279,0x102BA,0x102C4,0x10349,0x10364,0x103AF,0x10407,0x10412,0x10457,0x1048B,0x104A8,0x105AE,0x105C5,0x105CB,0x105FA,0x10700,0x10717,0x107BA,0x107C9,0x10817,0x10843,0x1086C,0x10886,0x108F9,0x10902,0x1092E,0x109D6,0x10A11,0x10B1D,0x10B4F,0x10B6B,0x10BFA,0x10C63,
0x10D2F,0x10D78,0x10DA1,0x10DA4,0x10DBA,0x10DC7,0x10E59,0x10EAA,0x10EDA,0x10F54,0x10F62,0x10F65,0x10F73,0x10FCC,0x10FE5,0x1104C,0x11081,0x11088,0x1109E,0x110FD,0x11164,0x111CB,0x111D9,0x11222,0x1126C,0x11296,0x1133B,0x1134B,0x11369,0x113FB,0x11417,0x1142B,0x114A3,0x114DA,0x11579,0x11596,0x115F5,0x115F6,0x11677,0x1167F,0x11700,0x1172B,0x1172E,0x11772,0x11775,0x1177D,0x1177F,0x117F4,0x11825,0x11843,0x118E1,0x118F2,0x11953,0x1196A,0x11983,0x11990,0x11A2A,0x11A90,0x11AC3,0x11ACE,0x11B25,0x11B31,0x11B5F,0x11BA7,0x11BB4,0x11C27,0x11C4A,0x11C9C,0x11CA8,0x11CDB,0x11CF1,0x11D1A,0x11D1D,0x11D3D,0x11D85,0x11DBF,0x11DEC,0x11E07,0x11E26,0x11E41,0x11E62,0x11EFD,0x11F77,0x11FD2,0x11FDF,0x11FED,0x11FF0,0x12004,0x12016,0x1202E,0x1203E,0x120AB,0x12131,0x12188,0x121D0,0x12210,0x12222,0x12261,0x1228D,0x1229E,0x122F9,0x1231A,0x1234D,0x1235E,0x12363,0x12386,0x12390,0x123AC,0x123B8,0x1243E,0x12487,0x124B0,0x12539,0x12542,0x1258A,0x125BB,0x125DB,0x1265D,0x12666,0x1267A,0x12695,0x1270C,0x1274D,0x12762,0x127A4,0x127B0,0x1281A,0x1285C,
0x12974,0x129AF,0x129EA,0x129EB,0x12A2D,0x12A7F,0x12AB6,0x12ADD,0x12AEA,0x12B03,0x12B15,0x12B56,0x12B9E,0x12BDA,0x12BE7,0x12C13,0x12C26,0x12CC8,0x12D37,0x12D48,0x12DB0,0x12DD6,0x12DDA,0x12DE7,0x12DFF,0x12E45,0x12F8C,0x12FCB,0x13017,0x13091,0x1309B,0x130AE,0x130E8,0x130F5,0x130FB,0x13156,0x13227,0x1336B,0x13373,0x133A0,0x133F0,0x133F7,0x13460,0x13465,0x1347C,0x134D7,0x13530,0x135BC,0x1363E,0x1366B,0x13676,0x136D5,0x1370A,0x13718,0x1374A,0x1375F,0x13771,0x13774,0x137E9,0x13821,0x1382A,0x13870,0x1394A,0x1396A,0x13974,0x13984,0x13991,0x1399F,0x139D5,0x13A23,0x13A4A,0x13A4F,0x13A7F,0x13AA7,0x13AF1,0x13B00,0x13B31,0x13B3B,0x13B45,0x13B96,0x13B9D,0x13C65,0x13CA4,0x13CE9,0x13CF9,0x13D15,0x13D16,0x13D23,0x13D78,0x13D98,0x13DB9,0x13E1A,0x13E3A,0x13EB6,0x13ED1,0x13F74,0x13FB9,0x13FC2,0x13FFA],

		);

#		test_set_precursors();

#		test_unset_precursors();

#	test_prompt();

#	test_strikes(1<<16);

#	test_3ps_excludes(1<<16);


#	test_set( 0,	0xFFFFFFFFFFFFFFFF,	1 );	# 64-bit NS	crashes ;/
#	test_set( 0,	0x7FFFFFFFFFFFFFFF,	1 );	# 63-bit NS
#	test_set( 0,	0xFFFFFF,				1 );	# 24-bit NS


1;


=head1 ICEPack

ICEPack - Compressed Fenwick Octree in O( √( log(n) * log( nmax-n ) ) +O( log( n) )

=head1 VERSION	0.2.0

=head1 DESCRIPTION
ICEPack is an instantiable object class for a data structure I categorically define as a Compressed Truth Vector.  The inspirational concept I was trying to achieve when I set out to develop this data structure was something which combined the access modalities of hashes and arrays without the complexity or overhead of a database, meeting or exceeding a modern standard of computational efficiency.  Elements are addressable by sparse key as in hashes, or by ordered index as in arrays.  The architecture has three abstraction layers, starting with a custom binary encoding I call Inversion Cycle RLE, which is a minimized version of RLE for alternating boolean values.  The second abstraction layer is a fairly basic binary search implementation over a sorted array of these IC-RLE segments, and the third abstraction layer is a stratified/laminar regressive quantization of the second-layer data array, grading the namespace content down into increasingly quantized reductions, storing respective modulus values in the freed up allocation space for each combined unit key, which can be atomically updated by setters as the structure changes, and efficiently summed by getters to compute the sort order of sparse keys on demand.  I want to call it dynamic enumeration.

In a way, it allows for treating defined and undefined namespace as two dimensions of one regular series.  It enables an access modality similar to Perl's range operator (where you specify a series in terms of its starting and ending value), but now those values can be sparse keys, and they can select from either the defined or undefined sparse key namespace efficiently.  This makes mass shuffle practical.  Indeed, the intended application is mass distributed session ID randomization where collision is prevented through true namespace conservation (not merely leveraging astronomical odds) and without introducing a special need or requirement for a core network to maintain sync across edge servers.

I first developed a complete proof of concept in 2020 written in Perl.  Since then, I have taken on learning C and giving the specification and architecture the proper treatment to realize an enterprise grade implementation.


	OBJECTIVE
	To implement one regular namespace over many ad-hoc nodes with non-deterministic allocation.

	There are entropy sources as usual, but instead of piping this directly into a Session ID generator,
	use it to select the "nth" free ID in an ICEPack instance, conserving namespace locally; then,
	implement periodic redistribution of available namespace service-wide, without degrading entropy,
	randomly drawing large sets of nth IDs for each edge server and periodically throwing them back 
	into the pool and drawing a new set.
	In this way, edge servers can unilaterally assign system-wide Session IDs on an event-driven basis,
	with no core negotiation needed, with guaranteed ID collission protection.  Not only does this free us
	to rate the appropriate namespace depth precisely, it also frees us to implement Forward Secrecy—
	i.e., perpetual renewal of active Session-IDs. 

	OBJECT CLASS
	ICEPack manipulates QWORD-sized truth vectors designed to be used as inside-out UUID tables.
	These truth vectors provide a hash-like interface to a 64-bit namespace, 18 quintillion flag bits,
	though the absolute minimum compression ratio of 3:1 is to be expected for highly entropic data.
	This space is fragmented as a searchable array and compressed using a sort of run length encoding—
	Inversion Cycle RLE, or just Inversion Cycle Encoding (ICE).

	ENCODING
	ICE encoding is a compressed bitvector format, where access to nearest adjacent set/unset bit
	scales in constant O(1) time, ideal for allocation within highly entropic inside-out UUID tables.
	Like RLE, ICE compresses repeating values as run lengths, but it stores no values explicitly—
	alternating true-false run lengths implicitly store value as evenness/oddness, or "half-cycle phase".
	Compression peaks with namespace density, storing tightly-packed run length pairs as single bytes.

	ACCESS MODALITY
	ICEPack implements a hash-like interface while ICEPack::E extends it with "dynamic enumeration".
	Dynamic enumeration enables a novel access modality where keys can be selected using ranges,
	from both the existent/allocated and nonexistent/free namespace.  This is powerful.

	In both use cases, a full suite of accessor methods enable manipulation by range, mask, sorted list,
	or object comparison, as well as basic scalar arguments.

	TIME COMPLEXITY
	When using just the base class (without dynamic enumeration), time and size scale hyperbolically.
	When using the extended class, a small additional overlaying structure scales semi-logarithmically.

	ICE CUBES
	To promote the integrity of the encoding across mutations, ICE compresses pairs of true-false runs
	and mediates computational complexity to access and mutate these entries with fragmentation.
	Encoded data is balanced over a series of variable segments (16 to 144 bytes in length) which 
	are sorted into a searchable AV* array.
	
	DYNAMIC ENUMERATION
	Any sparse array compression technique which omits nulls makes the obvious unfortunate tradeoff
	of recovering space while sacrificing the implicit identity of the element index— 
	the most characteristic property of arrays.

	The solution applied here is to regressively quantize the truth vector as a modulus gradient,
	storing summative modulus values in the freed up allocation space for each quantized unit key, 
	which are atomically updated by setters during mutation, and efficiently summed by getters 
	to compute the sort order of sparse keys on demand.

	So, to reiterate:
		> Trivial access to lowest / highest / nearest sparse index in O(1) time
		> Hash-like sparsity with array-like sorting effectively works like a range operator for keys
		> Basically redefines the Perl idiom "Everything Is A Number"

=cut  