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
use POSIX qw( log2 floor ceil );
our $VERSION=0.2.0;
use lib "blib/arch/auto/ICEPack";
require DynaLoader;
our @ISA = qw(DynaLoader);	bootstrap ICEPack;

use Exporter;
our @EXPORT=qw( test_set_recursively );	printf("\n\nbrrrrr\n");
use Time::HiRes qw(gettimeofday tv_interval);
my @avOut=();	my @precursors;	my @precursors_off;
my $msec0=gettimeofday; my $msec1=$msec0;
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
			printf(	"\rtesting strikes():	%6.2f%c completed (%d) test[s] w/ (%d) fail[s]  %11.2f/sec  ", $T/$nTx100,	37, $T, $fail, $perSec );
			$msec1=$msec2;
		}	}
	$perSec =$nTests /( gettimeofday-$msec0);
	printf(	"\rtesting strikes():	%6.2f%c completed (%d) test[s] w/ (%d) fail[s]  %11.2f/sec  \n", 100,	37, $T, $fail, $perSec );
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
			printf(	"\rtesting clears():	%6.2f%c completed (%d) test[s] w/ (%d) fail[s]  %11.2f/sec  ", $T/$nTx100,	37, $T, $fail, $perSec );
			$msec1=$msec2;
		}	}
	$perSec =$nTests /( gettimeofday-$msec0);
	printf(	"\rtesting clears():	%6.2f%c completed (%d) test[s] w/ (%d) fail[s]  %11.2f/sec  \n", 100,	37, $T, $fail, $perSec );
	}

sub test_precursors{							my $miss;	my @pre_args;	my @post_args;	my $ICE_B4;
	for( my $r=0; $r<$#precursors; $r+=2 ){
		my ($ranges, $args) =@precursors[$r..$r+1];
		@post_args=@$args;
		print("\rtesting crash precursor #", $r>>1, "... ");

		my	$ICE=av2ICE( $ranges );
			$ICE_B4=ICEPack::copy( $ICE );

	#	print( "\n\$ICE->set( [ ... ] );	");
	#	ICEPack::snapshot(	$ICE);
		ICEPack::set(		$ICE, $args );

		if(	$ICE->addsUp()					# addsUp() checks each cube's stored epsilon value against the sum of its cycla
		and	$ICE->clears( \@post_args ) ){		# clears()  only reads relevant cycla in relevant cubes, and does not check epsilon
	#			printAvDBUG();
											print("######	pass	######\n");
	#		print("\n\npre op:\n[\n");			print(	@{ ICEPack::toHex(		$ICE_B4	)	}, "\n],	[", join(",", map { sprintf("0x%X", $_) }	@$args		), "],\n\n");
	#		print("\n\n\n\n\n\n\n\n");
	#		print("\n[\n",								@{ ICEPack::toTextX(	$ICE_B4	)	},	"\n],	[", join(', ',						@$args		), "],\n\n");

	#		print("\n\npost op:\n[\n");			print(	@{ ICEPack::toHex(		$ICE	)	}, "\n],	[", join(",", map { sprintf("0x%X", $_) }	@post_args	), "],\n\n");
	#										print(	@{ ICEPack::toTextX(	$ICE	)	},	"\n],	[", join(', ',						@post_args	), "],\n\n");
		}else{								print("######	fail	######\n\n\n");
	#		printf("\naudit:\n\n");				printAvDBUG();	print("\n\n\n\n\n\n");
	#		print("\n\npre text:\n");				print(	@{ ICEPack::toTextX(	$ICE_B4	)	}, "\n\n");
#			print("\n\npre op:\n[\n");			print(	@{ ICEPack::toHex(	$ICE_B4	)	}, "\n],	[", join(",", map { sprintf("0x%X", $_) }	@$args	), "],\n\n");
#											print(	@{ ICEPack::toTextX(	$ICE_B4	)	}, "\n\n");
		#	print("\n[\n",								@{ $ICE->toHex()	},	"\n],	[", join(', ',						@$args	), "],\n\n");

#			print("\n\npost mortem:\n[\n");		print(	@{ ICEPack::toHex(	$ICE	)	}, "\n]\n\n");
#											print(	@{ ICEPack::toTextX(	$ICE	)	}, "\n\n");
	
#			print("\narg keys not found: [",		join(",", map { sprintf("0x%X", $_) } @post_args ), "]\n\n\n\n\n\n\n\n");

	}	}	}

sub test_prompt{
	my ($x, @A1, @D1);
#	my $ICE=av2ICE( $A1 );
	my $ICE=av2ICE( [	1..4, 111..112, 211, 222,240,260..280, 940, 1060,
					1080, 1099..1100, 1111..1113, 2100..2110, 2200..2222, 2300..2340, 2345..2460, 2598,
					2600..2650, 2660..2666, 2690, undef,
					2749, 2802, 2968, undef,
					2970, 3003..4004, 5005..6006, undef,
					7000, 7700..7777, 8000, 8800..8888, 9000] );	#	bless( [], 'ICEPack' );

#	my $hv=$ICE->toHash();
#	my @keys= sort keys %$hv;
#	my $N=0;
#	foreach(@keys){	print("$N:	", unpack( "Q", $_), "\n");	++$N;	}
	
	print("\n\n\n", @{ $ICE->toText() },	"]\n\n>");
	while(	$_=<> ){
		@D1=$_=~ /\d+/g;
		@A1= map{ int($_) } @D1;
		if(ord($_)==45){
			print("\nunset()==",	$ICE->unset(	\@A1	)	);
		}else{
			print("\nset()==",	$ICE->set(	\@A1	)	);
			}
		print(	"\n\n\n\n\n",	@{	$ICE->toText() } ,
		#		"\n\n", @{	$ICE->toHex() },
				"\n>");
				printAvDBUG();

		if(	not $ICE->addsUp()		){	print("\n!	doesn't add up\n");		}
		if(	not $ICE->clears( \@A1 ) ){		print("\n!	doesn't clear args: [",		join(",", @A1 ), "]\n\n\n");	}

	}	}

sub test_set($$$$$){		#\	Test ICEPack::set() by saturating the namespace range with random keys until it reaches totality.

	our	( $min, $max, $nTests, $nSamps,	$saturation				)=@_;

	our	( $window,	$Ct,			$Tsub,	$Tsub_,	$T,		$T_,	$T_stall,	$fpp,	$scale,	$scale100,	$nTx100,		$ok,	$batch,	$pass,	$fail,	$replay,					$maxZ,	$perSec, $msec2, $hit, $miss, $r, $R_, $d, $ICE, $ICE_B4, $x, $i, $I, %ICE, @ICE, @ICE_B4, @args, @args_B4, @args_extra, @args_XX, @keyBulk, @row)=
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
		#	printAvDBUG();
			if(	not $ICE->addsUp()			# addsUp() checks each cube's stored epsilon value against the sum of its cycla
		 	or	not $ICE->clears( \@args ) ){		# clears()  only reads relevant cycla in relevant cubes, and does not check epsilon
		#		){
				$ICE_B4=ICEPack::getSnapshot();	print("\n snapshot AV in Perl has $#$ICE_B4+1 elements\n");
				++$fail;							print("\n\ntest $T failed	 ", scalar localtime(), "\n");
				printf("\naudit:\n\n");				printAvDBUG();	print("\n\n\n\n\n\n");
				print("\n\npre text:\n");				print(	@{ ICEPack::toTextX(	$ICE_B4	)	}, "\n\n");
			#	print("\n\npre op:\n[\n");			print(	@{ ICEPack::toHex(		$ICE_B4	)	}, "\n],	[", join(",", map { sprintf("0x%X", $_) }	@args_B4	), "],\n\n");
				print("\n\npre op:\n[\n");			print(	@{ ICEPack::toHex(	$ICE_B4	)	},#	"\n],	[", join(",", map { sprintf("0x%X", $_) }	@args_B4	), "],\n\n");
																							"\n],	[", join(', ',						@args_B4	), "],\n\n");
			#	print("\n[\n",								@{ $ICE->toHex()	},					"\n],	[", join(', ',						@$args		), "],\n\n");

				print("\n\npost mortem:\n[\n");		print(	@{ ICEPack::toHex(	$ICE	)	}, "\n]\n\n");
												print(	@{ ICEPack::toTextX(	$ICE	)	}, "\n\n");
		
				print("\narg keys not found: [",		join(",", map { sprintf("0x%X", $_) } @args ), "]\n\n\n\n\n\n\n\n");

				exit(10);	
				next TEST;
				}
			$maxZ = $#$ICE if $#$ICE >$maxZ;

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
	}
my $LOG2X24=log2(0xFFFFFF);
sub test_set_recursively($$$){	my($start_bits, $end_bits, $saturation)=@_;	my $saturation_pct=$saturation*100;
	print("\n recursive test script started ", scalar localtime(), "\n\n");
	while( 1 ){							
######			Increasing the sample rate beyond the square root of the NS window 
		foreach my $bit_width($start_bits..$end_bits){	my	$W=1<<($bit_width-1);	my $rms=sqrt( $W*($W>>1) ); my $nSamps=$rms;	$nSamps=240 if $nSamps >240;
#		foreach my $bit_width(6..8){	my	$W=1<<$bit_width;	my $nSamps=240;
#		foreach my $bit_width(8..8){			my	$W=4<<$bit_width;	my $nTests=0x0FFF/$bit_width;
#		foreach my $bit_width(3..4){			my	$W=8<<$bit_width;	my $nTests=0x0FFF/$bit_width;


			my $nTests=int( (10000/$saturation )/$rms );	$nTests=1 if $nTests==0;
		#	printf("\nhit %d%c saturation of %d-bit namespace %3dx at sample rate %3d/call        \n",
		#			$saturation_pct, 37,  $bit_width, $nTests, $nSamps );

	## quiet for now
	##		printf("\n%d-bit NS (+/- %-3d) to %d%c saturation %3dx, sample rate: %d/call        \n",
	##				 $bit_width,	$W,	$saturation_pct, 37, $nTests,			$nSamps );
		#	printf("\n range: 0x%X (%d) x%d test iteration[s]\n", $_=$W<<1, $_, 1 );
			#\	Each range intermediates a cyclic boundary, so each key has a 50% chance of a +1 bytewise overflow/carry.
			#\	Starting with a namespace range of CB +/- $W and ($nTests) test[s], double the range and halve the tests.
			foreach my $base2Exp( 56, 48, 40, 32, 24, 16, 8 ){
				my $bytestep=1<<$base2Exp;

			#	printf("\n	NS 0x%-3llX +/- %-3d\n",$bytestep, $_=$W<<1);
				test_set( $bytestep -$W,	$bytestep +$W,	$nTests,	$nSamps, $saturation )	if( $bytestep >$W && 0xFFFFFFFFFFFFFFFF-$bytestep >$W );
	##			printf("\n");
				}
		}	}#			^NS lowbound		^NS highbound					^NS saturation factor to pass each test
	}
#	@precursors_off=(
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
	[	#proof that it is not possible to fragment a cube three ways while concentrating all endogenic cycla into the medial fragment
		#it shouldn't need proof, though.
		#Adding two more cubes implies that the number of additional cycla well exceeds what can fit in one cube.
		10,			20,			30,			40,			50,			60,			70,			80,
		100, 		200,			300,			400,			500,			600,			700,			800,
		1000,		2000,		3000,		4000,		5000,		6000,		7000,		8000
	],	[ 402, 404, 406, 408, 410, 412, 414	],
	[
	0xFFFFFFFFFFFFC0..0xFFFFFFFFFFFFE9, undef,
	0xFFFFFFFFFFFFEB..0x10000000000003F
	],      [0xFFFFFFFFFFFFC5,0xFFFFFFFFFFFFD4,0xFFFFFFFFFFFFD5,0xFFFFFFFFFFFFDE,0xFFFFFFFFFFFFE3,0xFFFFFFFFFFFFF4,0xFFFFFFFFFFFFF7,0xFFFFFFFFFFFFF8,0xFFFFFFFFFFFFFA,0x10000000000000D,0x10000000000001A,0x100000000000020,0x100000000000024,0x100000000000025,0x10000000000003C,0x10000000000003E],
	[
	0xFFFFC0..0xFFFFC2,	undef,
	0xFFFFC4..0x100003F,	undef,
	0x1000041..0x10000BC
	],      [0xFFFFC0,0xFFFFC5,0xFFFFCD,0xFFFFE0,0xFFFFE2,0xFFFFE8,0xFFFFEE,0xFFFFF4,0xFFFFF9,0xFFFFFB,0xFFFFFD,0x1000006,0x100000E,0x100000F,0x1000011,0x100001B,0x1000026,0x100002A,0x100002E,0x1000031,0x1000034],
	[
	0xFFFFFFFFFFC0..0x100000000002D,	undef,
	0x100000000002F..0x100000000003F
	],      [0xFFFFFFFFFFC1,0xFFFFFFFFFFC3,0xFFFFFFFFFFCB,0xFFFFFFFFFFD0,0xFFFFFFFFFFD8,0xFFFFFFFFFFDF,0xFFFFFFFFFFE1,0xFFFFFFFFFFE3,0xFFFFFFFFFFE5,0xFFFFFFFFFFE8,0xFFFFFFFFFFEB,0xFFFFFFFFFFED,0xFFFFFFFFFFEE,0xFFFFFFFFFFF0,0xFFFFFFFFFFF5,0xFFFFFFFFFFF8,0xFFFFFFFFFFFB,0x100000000000B,0x1000000000012,0x1000000000019,0x100000000002D],
	[
	0xFFFFC0..0x1000020,		undef,
	0x1000022..0x100003F,		undef,
	0x1000041..0x100005E
	],      [0xFFFFC7,0xFFFFC9,0xFFFFCB,0xFFFFCD,0xFFFFD2,0xFFFFDA,0xFFFFDE,0xFFFFE0,0xFFFFE3,0xFFFFEB,0xFFFFED,0xFFFFF0,0xFFFFF7,0xFFFFFA,0x100000C,0x100000D,0x100000F,0x100001D,0x100001F,0x1000021,0x1000023],
	[
	72057594037925895, 72057594037926007, 72057594037926053,                    72057594037926056, 72057594037926084, 72057594037926130, 72057594037926173, 72057594037926349,
	72057594037926377, 72057594037926478, 72057594037926503,                    72057594037926564, 72057594037926567, 72057594037926580, 72057594037926697, 72057594037926731,
	72057594037926772, 72057594037926789, 72057594037926843,                    72057594037926851, 72057594037926860, 72057594037927121, 72057594037927191, 72057594037927224,
	72057594037927333, 72057594037927383, 72057594037927412,                    72057594037927427, 72057594037927496, 72057594037927583, 72057594037927591, 72057594037927600,
	72057594037927715, 72057594037927784, 72057594037927791,                    72057594037927935, 72057594037927948, 72057594037928022, 72057594037928055, 72057594037928094,
	72057594037928103, 72057594037928180, 72057594037928186,                    72057594037928529, 72057594037928559, 72057594037928572, 72057594037928647, 72057594037928958,
	72057594037928967, 72057594037929013, 72057594037929071,                    72057594037929240, 72057594037929343, 72057594037929354, 72057594037929368, 72057594037929397..72057594037929398,
	72057594037929443, 72057594037929472, 72057594037929587..72057594037929588, 72057594037929601, 72057594037929616, 72057594037929732
	],      [72057594037925933, 72057594037926051, 72057594037926454, 72057594037926495, 72057594037926568, 72057594037926596, 72057594037926755, 72057594037926772, 72057594037926773, 72057594037926783, 72057594037926815, 72057594037926913, 72057594037926941, 72057594037927058, 72057594037927118, 72057594037927129, 72057594037927135, 72057594037927277, 72057594037927328, 72057594037927382, 72057594037927405, 72057594037927406, 72057594037927498, 72057594037927600, 72057594037927628, 72057594037927630, 72057594037927751, 72057594037927805, 72057594037928000, 72057594037928072, 72057594037928134, 72057594037928152, 72057594037928157, 72057594037928207, 72057594037928280, 72057594037928342, 72057594037928350, 72057594037928390, 72057594037928394, 72057594037928402, 72057594037928455, 72057594037928656, 72057594037928720, 72057594037928804, 72057594037928814, 72057594037928822, 72057594037928826, 72057594037928844, 72057594037928856, 72057594037928871, 72057594037928910, 72057594037928917, 72057594037928967, 72057594037929190, 72057594037929304, 72057594037929305, 72057594037929375, 72057594037929522, 72057594037929603, 72057594037929632, 72057594037929873, 72057594037929874, 72057594037929910, 72057594037929923],
	[
	281474976708634,                  281474976708640, 281474976708660, 281474976708829, 281474976708901, 281474976708910, 281474976708954, 281474976708965..281474976708966,
	281474976708971,                  281474976708998, 281474976709131, 281474976709165, 281474976709204, 281474976709248, 281474976709289, 281474976709409,
	281474976709515,                  281474976709595, 281474976709619, 281474976709659, 281474976709763, 281474976709777, 281474976709849, 281474976709930,
	281474976710026,                  281474976710138, 281474976710245, 281474976710564, 281474976710626, 281474976710637, 281474976710679, 281474976710695,
	281474976710865..281474976710866, 281474976711080, 281474976711202, 281474976711222, 281474976711248, 281474976711308, 281474976711322, 281474976711472,
	281474976711523,                  281474976711573, 281474976711619, 281474976711629, 281474976711643, 281474976711667, 281474976711670, 281474976711689,
	281474976711701,                  281474976711735, 281474976711781, 281474976711807, 281474976711900, 281474976712054, 281474976712057, 281474976712109,
	281474976712117,                  281474976712177, 281474976712217, 281474976712287, 281474976712491, 281474976712702
	],      [281474976708668, 281474976708755, 281474976708781, 281474976708809, 281474976708890, 281474976708916, 281474976709050, 281474976709066, 281474976709332, 281474976709352, 281474976709426, 281474976709599, 281474976709661, 281474976709910, 281474976709944, 281474976710000, 281474976710022, 281474976710045, 281474976710056, 281474976710127, 281474976710216, 281474976710231, 281474976710276, 281474976710283, 281474976710298, 281474976710325, 281474976710345, 281474976710379, 281474976710413, 281474976710433, 281474976710450, 281474976710476, 281474976710514, 281474976710520, 281474976710548, 281474976710567, 281474976710606, 281474976710640, 281474976710645, 281474976710672, 281474976710764, 281474976710876, 281474976710912, 281474976710935, 281474976711016, 281474976711215, 281474976711225, 281474976711246, 281474976711370, 281474976711390, 281474976711391, 281474976711454, 281474976711498, 281474976711642, 281474976711799, 281474976711874, 281474976711923, 281474976712134, 281474976712321, 281474976712362, 281474976712442, 281474976712454, 281474976712479, 281474976712663],
	[
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
	#	verify rare subcases of main case 1F4 within _sv_commit()
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
	#1F4-0A0202000201:
	[
	0xFFFFFFFFFFFEA3,  0xFFFFFFFFFFFEB1,  0xFFFFFFFFFFFF66,  0xFFFFFFFFFFFF89,                     0x100000000000006, 0x100000000000020, 0x100000000000024, 0x100000000000037,
	0x100000000000039, 0x10000000000006C, 0x10000000000006F, 0x100000000000074,                    0x1000000000000A0, 0x1000000000000B1, 0x1000000000000CD, 0x1000000000000EF,
	0x100000000000100, 0x10000000000011A, 0x10000000000011D, 0x100000000000151..0x100000000000152, 0x10000000000015C, 0x100000000000160, 0x10000000000017F, 0x1000000000001B3,
	0x1000000000001DF, 0x1000000000001EF, 0x1000000000001F8, 0x100000000000223,                    0x100000000000242, 0x100000000000281, 0x10000000000028F, 0x1000000000002A8,
	0x1000000000002EF, 0x1000000000002F1, 0x10000000000033A, 0x10000000000034C,                    0x10000000000037B, 0x10000000000038F, 0x1000000000003B8, 0x1000000000003EB,
	0x1000000000003EE, 0x1000000000003F5, 0x100000000000400, 0x100000000000412,                    0x10000000000041C
	], [ 0xFFFFFFFFFFFEED, 0xFFFFFFFFFFFEF9, 0xFFFFFFFFFFFF08, 0xFFFFFFFFFFFF22, 0xFFFFFFFFFFFF43, 0xFFFFFFFFFFFF44, 0xFFFFFFFFFFFF4D, 0xFFFFFFFFFFFF4F, 0xFFFFFFFFFFFF68, 0xFFFFFFFFFFFF9B, 0xFFFFFFFFFFFF9F, 0xFFFFFFFFFFFFAF, 0xFFFFFFFFFFFFD6, 0xFFFFFFFFFFFFD9, 0xFFFFFFFFFFFFE9, 0x10000000000000D, 0x100000000000033, 0x10000000000003A, 0x100000000000045, 0x10000000000004A, 0x100000000000054, 0x10000000000006F, 0x100000000000072, 0x1000000000000AE, 0x1000000000000BE, 0x1000000000000DB, 0x1000000000000F2, 0x100000000000138, 0x1000000000001AA, 0x1000000000001E6, 0x100000000000204, 0x100000000000221, 0x10000000000023D, 0x10000000000024B, 0x10000000000024E, 0x100000000000258, 0x100000000000259, 0x100000000000271, 0x100000000000297, 0x1000000000002AD, 0x1000000000002FB, 0x100000000000319, 0x10000000000032D, 0x10000000000033A, 0x100000000000342, 0x10000000000035B, ],
	#1F4-0A0702000201:
	[
	0xFFFFFFFFFFFE3B,  0xFFFFFFFFFFFED3,  0xFFFFFFFFFFFEF3,  0xFFFFFFFFFFFF00,                     0xFFFFFFFFFFFF03,                     0xFFFFFFFFFFFF14..0xFFFFFFFFFFFF15,  0xFFFFFFFFFFFF1E,                     0xFFFFFFFFFFFF26,
	0xFFFFFFFFFFFF2E,  0xFFFFFFFFFFFF31,  0xFFFFFFFFFFFF45,  0xFFFFFFFFFFFF47,                     0xFFFFFFFFFFFF58,                     0xFFFFFFFFFFFF6F,                    0xFFFFFFFFFFFF73,                     0xFFFFFFFFFFFF75,
	0xFFFFFFFFFFFF94,  0xFFFFFFFFFFFFE0,  0xFFFFFFFFFFFFEF,  0x10000000000000C..0x10000000000000D, 0x100000000000017..0x100000000000018, 0x10000000000005E,                   0x100000000000087,                    0x1000000000000F1,
	0x100000000000104, 0x100000000000114, 0x10000000000012B, 0x100000000000132,                    0x100000000000179,                    0x1000000000001C5,                   0x1000000000001C8..0x1000000000001C9, 0x1000000000001CC,
	0x1000000000001E3, 0x1000000000001E6, 0x1000000000001EC, 0x100000000000232,                    0x100000000000267,                    0x100000000000273,                   0x100000000000275,                    0x1000000000002AE,
	0x1000000000002B4, 0x100000000000326
	], [ 0xFFFFFFFFFFFED4, 0xFFFFFFFFFFFF0D, 0xFFFFFFFFFFFF1D, 0xFFFFFFFFFFFF3C, 0xFFFFFFFFFFFF59, 0xFFFFFFFFFFFF5C, 0xFFFFFFFFFFFF60, 0xFFFFFFFFFFFF64, 0xFFFFFFFFFFFF7E, 0xFFFFFFFFFFFFCA, 0xFFFFFFFFFFFFCD, 0xFFFFFFFFFFFFE7, 0xFFFFFFFFFFFFE9, 0x10000000000003C, 0x100000000000050, 0x100000000000054, 0x100000000000067, 0x100000000000070, 0x100000000000085, 0x100000000000099, 0x10000000000009C, 0x10000000000009D, 0x1000000000000AE, 0x1000000000000D4, 0x1000000000000EB, 0x100000000000101, 0x10000000000010C, 0x10000000000010F, 0x100000000000114, 0x100000000000126, 0x100000000000139, 0x10000000000017D, 0x10000000000018B, 0x1000000000001A3, 0x1000000000001AE, 0x1000000000001B8, 0x1000000000001F8, 0x1000000000001FF, 0x100000000000217, 0x10000000000021D, 0x100000000000225, 0x100000000000229, 0x100000000000267, 0x10000000000027E, 0x100000000000288, 0x1000000000002E1, ],
	#1F4-0A0702030201:
	[
	0xFFFFFFFFFFFE5E,                     0xFFFFFFFFFFFEB2,  0xFFFFFFFFFFFEE5,  0xFFFFFFFFFFFEF2,                     0xFFFFFFFFFFFF0B,  0xFFFFFFFFFFFF11,                     0xFFFFFFFFFFFF55,  0xFFFFFFFFFFFF69,
	0xFFFFFFFFFFFF6C,                     0xFFFFFFFFFFFF6F,  0xFFFFFFFFFFFF7C,  0xFFFFFFFFFFFF99,                     0xFFFFFFFFFFFFA4,  0xFFFFFFFFFFFFAC,                     0xFFFFFFFFFFFFB1,  0xFFFFFFFFFFFFB4,
	0xFFFFFFFFFFFFC1,                     0x100000000000003, 0x10000000000004C, 0x100000000000055..0x100000000000056, 0x1000000000000A0, 0x1000000000000D2..0x1000000000000D3, 0x1000000000000FC, 0x100000000000103,
	0x10000000000010C,                    0x100000000000119, 0x10000000000011E, 0x100000000000141,                    0x100000000000160, 0x100000000000164,                    0x100000000000197, 0x1000000000001C4,
	0x1000000000001D0,                    0x1000000000001E5, 0x1000000000001EC, 0x100000000000214,                    0x100000000000242, 0x100000000000244,                    0x10000000000024B, 0x10000000000026A,
	0x100000000000270..0x100000000000271, 0x100000000000278, 0x10000000000028C
	], [ 0xFFFFFFFFFFFE9F, 0xFFFFFFFFFFFEEF, 0xFFFFFFFFFFFEF7, 0xFFFFFFFFFFFF0B, 0xFFFFFFFFFFFF3B, 0xFFFFFFFFFFFF95, 0xFFFFFFFFFFFF9E, 0xFFFFFFFFFFFFB7, 0xFFFFFFFFFFFFDD, 0xFFFFFFFFFFFFE7, 0xFFFFFFFFFFFFF1, 0x100000000000001, 0x100000000000026, 0x10000000000002E, 0x100000000000041, 0x100000000000046, 0x100000000000069, 0x100000000000077, 0x100000000000087, 0x10000000000008C, 0x100000000000091, 0x10000000000009C, 0x1000000000000CD, 0x1000000000000CE, 0x1000000000000D7, 0x1000000000000DF, 0x1000000000000EE, 0x1000000000000F8, 0x100000000000101, 0x100000000000108, 0x100000000000133, 0x100000000000138, 0x100000000000197, 0x1000000000001A2, 0x1000000000001DA, 0x1000000000001DE, 0x1000000000001E0, 0x100000000000202, 0x100000000000219, 0x100000000000221, 0x10000000000022B, 0x10000000000023C, 0x10000000000024E, 0x10000000000024F, 0x100000000000277, 0x10000000000029E, ],
	#1F4-0B0703030201:
	[
	0xFFFFFFFFFE55,  0xFFFFFFFFFE99,  0xFFFFFFFFFEAF,  0xFFFFFFFFFEE5,  0xFFFFFFFFFEF2,                   0xFFFFFFFFFF03,  0xFFFFFFFFFF2F,  0xFFFFFFFFFF4B,
	0xFFFFFFFFFFC4,  0x1000000000022, 0x100000000002A, 0x100000000002F, 0x100000000003C,                  0x1000000000054, 0x1000000000059, 0x100000000006C,
	0x1000000000095, 0x100000000009A, 0x10000000000A4, 0x10000000000B8, 0x10000000000BA,                  0x10000000000DE, 0x1000000000116, 0x1000000000125,
	0x100000000012C, 0x1000000000133, 0x1000000000137, 0x1000000000151, 0x1000000000178..0x1000000000179, 0x1000000000180, 0x1000000000186, 0x100000000019E,
	0x10000000001A8, 0x10000000001C4, 0x10000000001D1, 0x10000000001F5, 0x1000000000204,                  0x1000000000225, 0x1000000000237, 0x100000000023E,
	0x1000000000253, 0x100000000025A, 0x100000000025D, 0x1000000000263, 0x100000000028A
	], [ 0xFFFFFFFFFE80, 0xFFFFFFFFFE9A, 0xFFFFFFFFFEB9, 0xFFFFFFFFFED2, 0xFFFFFFFFFEE2, 0xFFFFFFFFFF02, 0xFFFFFFFFFF19, 0xFFFFFFFFFF2A, 0xFFFFFFFFFF33, 0xFFFFFFFFFF52, 0xFFFFFFFFFF64, 0xFFFFFFFFFF66, 0xFFFFFFFFFF83, 0xFFFFFFFFFF86, 0xFFFFFFFFFF9A, 0xFFFFFFFFFFA2, 0xFFFFFFFFFFB1, 0xFFFFFFFFFFC1, 0xFFFFFFFFFFE0, 0xFFFFFFFFFFE7, 0xFFFFFFFFFFED, 0xFFFFFFFFFFF7, 0xFFFFFFFFFFFA, 0x1000000000013, 0x1000000000014, 0x1000000000075, 0x1000000000088, 0x100000000009F, 0x10000000000C1, 0x10000000000DE, 0x10000000000EF, 0x100000000012E, 0x1000000000130, 0x100000000014A, 0x100000000014E, 0x100000000015F, 0x1000000000167, 0x1000000000169, 0x10000000001C1, 0x10000000001F5, 0x10000000001FF, 0x100000000023E, 0x1000000000242, 0x100000000026A, 0x100000000027C, 0x100000000028E, ],
	#1F4-0B0707030201:
	[
	0xFFFFFFFFF4,                 0x1000000003A, 0x1000000006A, 0x1000000007D,                0x10000000086, 0x1000000008A, 0x1000000008D, 0x10000000098,
	0x1000000009D,                0x100000000BD, 0x10000000128, 0x1000000012D,                0x10000000131, 0x10000000136, 0x1000000013E, 0x1000000015B,
	0x10000000171..0x10000000173, 0x1000000018B, 0x10000000192, 0x100000001C2..0x100000001C3, 0x100000001DF, 0x10000000202, 0x10000000228, 0x10000000279,
	0x100000002A8,                0x100000002B2, 0x100000002D7, 0x100000002E1,                0x100000002F0, 0x10000000329, 0x10000000342, 0x10000000344,
	0x10000000373,                0x100000003B9, 0x100000003C5, 0x100000003E2,                0x10000000408, 0x1000000040B, 0x10000000416, 0x10000000447,
	0x100000004CE,                0x10000000532, 0x1000000053C
	], [ 0xFFFFFFFE7D, 0xFFFFFFFEC7, 0xFFFFFFFED0, 0xFFFFFFFF32, 0xFFFFFFFF33, 0xFFFFFFFF3A, 0xFFFFFFFF47, 0xFFFFFFFF48, 0xFFFFFFFF56, 0xFFFFFFFF69, 0xFFFFFFFF74, 0xFFFFFFFFA2, 0xFFFFFFFFA7, 0xFFFFFFFFC6, 0xFFFFFFFFD1, 0xFFFFFFFFD4, 0xFFFFFFFFDD, 0x1000000009C, 0x100000000AB, 0x100000000B3, 0x100000000B9, 0x100000000BC, 0x100000000CB, 0x100000000D1, 0x100000000D2, 0x100000000F7, 0x10000000103, 0x10000000115, 0x1000000013F, 0x10000000141, 0x10000000163, 0x10000000181, 0x10000000182, 0x10000000197, 0x100000001A9, 0x100000001B4, 0x100000001C3, 0x10000000200, 0x10000000216, 0x10000000227, 0x1000000023F, 0x1000000025C, 0x10000000266, 0x10000000289, 0x100000002E5, 0x100000002EA, ],
	#1F4-0F0707030201:
	[
	0xFFFFFE69,  0xFFFFFE6B,  0xFFFFFE84,               0xFFFFFEA1,  0xFFFFFEA8,               0xFFFFFEC7,  0xFFFFFECC,  0xFFFFFFB2,
	0xFFFFFFF4,  0xFFFFFFFC,  0x10000002C,              0x100000034, 0x10000003C,              0x10000004D, 0x100000069, 0x100000076,
	0x100000079, 0x10000007E, 0x1000000C7,              0x1000000D5, 0x1000000E6..0x1000000E7, 0x1000000F3, 0x100000102, 0x100000106,
	0x10000010A, 0x100000118, 0x100000129,              0x10000012E, 0x100000140,              0x100000175, 0x100000186, 0x10000018B,
	0x1000001A8, 0x1000001B5, 0x1000001D7,              0x1000001D9, 0x1000001F1,              0x1000001FF, 0x100000203, 0x100000206,
	0x100000219, 0x10000021E, 0x10000022A..0x10000022B, 0x1000002CC
	], [ 0xFFFFFED8, 0xFFFFFEED, 0xFFFFFEF7, 0xFFFFFF02, 0xFFFFFF0C, 0xFFFFFF13, 0xFFFFFF17, 0xFFFFFF36, 0xFFFFFF4A, 0xFFFFFF7A, 0xFFFFFF80, 0xFFFFFF87, 0xFFFFFFA5, 0xFFFFFFA8, 0xFFFFFFAD, 0xFFFFFFB0, 0xFFFFFFB5, 0xFFFFFFB8, 0xFFFFFFE9, 0xFFFFFFF1, 0x100000025, 0x10000004E, 0x100000054, 0x100000062, 0x100000082, 0x100000087, 0x10000009C, 0x1000000AB, 0x1000000B2, 0x1000000C6, 0x1000000DA, 0x1000000DE, 0x1000000E7, 0x1000000F5, 0x100000128, 0x10000014F, 0x100000169, 0x1000001A9, 0x1000001B2, 0x1000001C8, 0x1000001E5, 0x10000022D, 0x10000025B, 0x10000026E, 0x10000027B, 0x100000289, ],
	#1F4-0F0707030301:
	[
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
	[
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
	);
@precursors=(
[
0xFFFFFFFFF800,                  0xFFFFFFFFF803..0xFFFFFFFFF807, undef,
0xFFFFFFFFF809..0xFFFFFFFFF811,  0xFFFFFFFFF813,                    0xFFFFFFFFF815..0xFFFFFFFFF81C,    0xFFFFFFFFF81F,                    0xFFFFFFFFF821..0xFFFFFFFFF823, undef,
0xFFFFFFFFF825..0xFFFFFFFFF82F,  0xFFFFFFFFF831..0xFFFFFFFFF836, undef,
0xFFFFFFFFF838..0xFFFFFFFFF83E, undef,
0xFFFFFFFFF840..0xFFFFFFFFF849,  0xFFFFFFFFF84C..0xFFFFFFFFF84D,    0xFFFFFFFFF850..0xFFFFFFFFF851,    0xFFFFFFFFF856..0xFFFFFFFFF85B, undef,
0xFFFFFFFFF85D..0xFFFFFFFFF85F,  0xFFFFFFFFF861..0xFFFFFFFFF862,    0xFFFFFFFFF864,                    0xFFFFFFFFF868..0xFFFFFFFFF86B,    0xFFFFFFFFF86D..0xFFFFFFFFF874, undef,
0xFFFFFFFFF876..0xFFFFFFFFF879,  0xFFFFFFFFF87B..0xFFFFFFFFF880, undef,
0xFFFFFFFFF882..0xFFFFFFFFF884,  0xFFFFFFFFF886..0xFFFFFFFFF889,    0xFFFFFFFFF88C..0xFFFFFFFFF88D,    0xFFFFFFFFF88F,                    0xFFFFFFFFF894,                    0xFFFFFFFFF896..0xFFFFFFFFF898, undef,
0xFFFFFFFFF89A..0xFFFFFFFFF8A9, undef,
0xFFFFFFFFF8AB..0xFFFFFFFFF8B0,  0xFFFFFFFFF8B2,                    0xFFFFFFFFF8B4,                    0xFFFFFFFFF8B6..0xFFFFFFFFF8B8, undef,
0xFFFFFFFFF8BA,                  0xFFFFFFFFF8BD..0xFFFFFFFFF8BF,    0xFFFFFFFFF8C1,                    0xFFFFFFFFF8C3,                    0xFFFFFFFFF8C5, undef,
0xFFFFFFFFF8C7..0xFFFFFFFFF8CE,  0xFFFFFFFFF8D1..0xFFFFFFFFF8D5, undef,
0xFFFFFFFFF8D9..0xFFFFFFFFF8E5,  0xFFFFFFFFF8E7..0xFFFFFFFFF8E9,    0xFFFFFFFFF8EB,                    0xFFFFFFFFF8ED,                    0xFFFFFFFFF8EF,                    0xFFFFFFFFF8F2,                    0xFFFFFFFFF8F4..0xFFFFFFFFF8F5, undef,
0xFFFFFFFFF8F7,                  0xFFFFFFFFF8FA..0xFFFFFFFFF900,    0xFFFFFFFFF903, undef,
0xFFFFFFFFF905..0xFFFFFFFFF909,  0xFFFFFFFFF90B..0xFFFFFFFFF910,    0xFFFFFFFFF912..0xFFFFFFFFF913, undef,
0xFFFFFFFFF915..0xFFFFFFFFF918,  0xFFFFFFFFF91A..0xFFFFFFFFF91B,    0xFFFFFFFFF91D..0xFFFFFFFFF91E,    0xFFFFFFFFF920..0xFFFFFFFFF923,    0xFFFFFFFFF925,                    0xFFFFFFFFF927..0xFFFFFFFFF929, undef,
0xFFFFFFFFF92C..0xFFFFFFFFF93B,  0xFFFFFFFFF93D..0xFFFFFFFFF93F,    0xFFFFFFFFF941..0xFFFFFFFFF943, undef,
0xFFFFFFFFF945..0xFFFFFFFFF94A,  0xFFFFFFFFF94D,                    0xFFFFFFFFF951,                    0xFFFFFFFFF954..0xFFFFFFFFF955,    0xFFFFFFFFF957,                    0xFFFFFFFFF95A..0xFFFFFFFFF95C,    0xFFFFFFFFF95E, undef,
0xFFFFFFFFF960..0xFFFFFFFFF964,  0xFFFFFFFFF967,                    0xFFFFFFFFF969..0xFFFFFFFFF96A,    0xFFFFFFFFF96C, undef,
0xFFFFFFFFF96E..0xFFFFFFFFF973,  0xFFFFFFFFF975..0xFFFFFFFFF976,    0xFFFFFFFFF97A..0xFFFFFFFFF97B,    0xFFFFFFFFF97E..0xFFFFFFFFF987,    0xFFFFFFFFF98B..0xFFFFFFFFF98C,    0xFFFFFFFFF98F..0xFFFFFFFFF992, undef,
0xFFFFFFFFF994,                  0xFFFFFFFFF996,                    0xFFFFFFFFF998..0xFFFFFFFFF99B, undef,
0xFFFFFFFFF99D..0xFFFFFFFFF9A9,  0xFFFFFFFFF9AB..0xFFFFFFFFF9AC,    0xFFFFFFFFF9AE..0xFFFFFFFFF9AF, undef,
0xFFFFFFFFF9B1..0xFFFFFFFFF9B4,  0xFFFFFFFFF9B6..0xFFFFFFFFF9B8,    0xFFFFFFFFF9BA..0xFFFFFFFFF9BD, undef,
0xFFFFFFFFF9C0,                  0xFFFFFFFFF9C2..0xFFFFFFFFF9C3,    0xFFFFFFFFF9C5..0xFFFFFFFFF9C7,    0xFFFFFFFFF9C9,                    0xFFFFFFFFF9CB,                    0xFFFFFFFFF9CD..0xFFFFFFFFF9CF, undef,
0xFFFFFFFFF9D1..0xFFFFFFFFF9DD,  0xFFFFFFFFF9DF..0xFFFFFFFFF9E3,    0xFFFFFFFFF9E5,                    0xFFFFFFFFF9E7..0xFFFFFFFFF9E8,    0xFFFFFFFFF9EA..0xFFFFFFFFF9EC, undef,
0xFFFFFFFFF9EE..0xFFFFFFFFF9F3,  0xFFFFFFFFF9F5, undef,
0xFFFFFFFFF9F8,                  0xFFFFFFFFF9FA..0xFFFFFFFFF9FC,    0xFFFFFFFFF9FE,                    0xFFFFFFFFFA00..0xFFFFFFFFFA01, undef,
0xFFFFFFFFFA03..0xFFFFFFFFFA0C,  0xFFFFFFFFFA0E..0xFFFFFFFFFA13,    0xFFFFFFFFFA15..0xFFFFFFFFFA1A, undef,
0xFFFFFFFFFA1C..0xFFFFFFFFFA1F,  0xFFFFFFFFFA21..0xFFFFFFFFFA22,    0xFFFFFFFFFA24..0xFFFFFFFFFA27,    0xFFFFFFFFFA29,                    0xFFFFFFFFFA2B..0xFFFFFFFFFA2F,    0xFFFFFFFFFA32, undef,
0xFFFFFFFFFA34,                  0xFFFFFFFFFA37..0xFFFFFFFFFA3D, undef,
0xFFFFFFFFFA3F..0xFFFFFFFFFA41,  0xFFFFFFFFFA43..0xFFFFFFFFFA46,    0xFFFFFFFFFA4A,                    0xFFFFFFFFFA4C..0xFFFFFFFFFA4E, undef,
0xFFFFFFFFFA50..0xFFFFFFFFFA57,  0xFFFFFFFFFA5A,                    0xFFFFFFFFFA5C..0xFFFFFFFFFA5D,    0xFFFFFFFFFA5F..0xFFFFFFFFFA60, undef,
0xFFFFFFFFFA63..0xFFFFFFFFFA66,  0xFFFFFFFFFA68..0xFFFFFFFFFA73,    0xFFFFFFFFFA75,                    0xFFFFFFFFFA77..0xFFFFFFFFFA78,    0xFFFFFFFFFA7A..0xFFFFFFFFFA7E, undef,
0xFFFFFFFFFA80..0xFFFFFFFFFA83,  0xFFFFFFFFFA86..0xFFFFFFFFFA8D,    0xFFFFFFFFFA8F..0xFFFFFFFFFA92,    0xFFFFFFFFFA94..0xFFFFFFFFFA98, undef,
0xFFFFFFFFFA9B,                  0xFFFFFFFFFA9D,                    0xFFFFFFFFFAA0,                    0xFFFFFFFFFAA2,                    0xFFFFFFFFFAA5..0xFFFFFFFFFAA8, undef,
0xFFFFFFFFFAAB..0xFFFFFFFFFAB2,  0xFFFFFFFFFAB4,                    0xFFFFFFFFFAB6..0xFFFFFFFFFABF,    0xFFFFFFFFFAC3..0xFFFFFFFFFAC4,    0xFFFFFFFFFAC6..0xFFFFFFFFFAC7,    0xFFFFFFFFFAC9..0xFFFFFFFFFACA,    0xFFFFFFFFFACC..0xFFFFFFFFFACD,    0xFFFFFFFFFACF, undef,
0xFFFFFFFFFAD1..0xFFFFFFFFFAD2,  0xFFFFFFFFFAD6..0xFFFFFFFFFAD8,    0xFFFFFFFFFADA..0xFFFFFFFFFADE,    0xFFFFFFFFFAE0, undef,
0xFFFFFFFFFAE2..0xFFFFFFFFFAE3,  0xFFFFFFFFFAE5..0xFFFFFFFFFAE9,    0xFFFFFFFFFAEB..0xFFFFFFFFFAEC, undef,
0xFFFFFFFFFAEF..0xFFFFFFFFFAF0,  0xFFFFFFFFFAF2..0xFFFFFFFFFAF4,    0xFFFFFFFFFAF6..0xFFFFFFFFFAF7,    0xFFFFFFFFFAF9..0xFFFFFFFFFB00,    0xFFFFFFFFFB02..0xFFFFFFFFFB06, undef,
0xFFFFFFFFFB08..0xFFFFFFFFFB09,  0xFFFFFFFFFB0C..0xFFFFFFFFFB17, undef,
0xFFFFFFFFFB19,                  0xFFFFFFFFFB1F..0xFFFFFFFFFB21,    0xFFFFFFFFFB24..0xFFFFFFFFFB27,    0xFFFFFFFFFB29..0xFFFFFFFFFB2C, undef,
0xFFFFFFFFFB2E..0xFFFFFFFFFB30,  0xFFFFFFFFFB32..0xFFFFFFFFFB35,    0xFFFFFFFFFB37..0xFFFFFFFFFB3A, undef,
0xFFFFFFFFFB3C..0xFFFFFFFFFB3E,  0xFFFFFFFFFB42..0xFFFFFFFFFB43,    0xFFFFFFFFFB45..0xFFFFFFFFFB47, undef,
0xFFFFFFFFFB49..0xFFFFFFFFFB4C,  0xFFFFFFFFFB4E..0xFFFFFFFFFB52,    0xFFFFFFFFFB54..0xFFFFFFFFFB57, undef,
0xFFFFFFFFFB59..0xFFFFFFFFFB5A,  0xFFFFFFFFFB5C..0xFFFFFFFFFB62,    0xFFFFFFFFFB65,                    0xFFFFFFFFFB67..0xFFFFFFFFFB68, undef,
0xFFFFFFFFFB6A,                  0xFFFFFFFFFB6C..0xFFFFFFFFFB6D,    0xFFFFFFFFFB6F..0xFFFFFFFFFB72,    0xFFFFFFFFFB74..0xFFFFFFFFFB75,    0xFFFFFFFFFB78..0xFFFFFFFFFB79, undef,
0xFFFFFFFFFB7B,                  0xFFFFFFFFFB7D..0xFFFFFFFFFB7E,    0xFFFFFFFFFB80,                    0xFFFFFFFFFB85, undef,
0xFFFFFFFFFB87..0xFFFFFFFFFB8E,  0xFFFFFFFFFB90..0xFFFFFFFFFB91,    0xFFFFFFFFFB93..0xFFFFFFFFFB95,    0xFFFFFFFFFB97, undef,
0xFFFFFFFFFB9A..0xFFFFFFFFFBA2,  0xFFFFFFFFFBA4, undef,
0xFFFFFFFFFBA6..0xFFFFFFFFFBAE,  0xFFFFFFFFFBB1..0xFFFFFFFFFBB2,    0xFFFFFFFFFBB4,                    0xFFFFFFFFFBB6,                    0xFFFFFFFFFBB8,                    0xFFFFFFFFFBBA..0xFFFFFFFFFBBB,    0xFFFFFFFFFBBE,                    0xFFFFFFFFFBC0..0xFFFFFFFFFBC2, undef,
0xFFFFFFFFFBC4..0xFFFFFFFFFBCD,  0xFFFFFFFFFBCF..0xFFFFFFFFFBD3,    0xFFFFFFFFFBD5..0xFFFFFFFFFBD6,    0xFFFFFFFFFBD8..0xFFFFFFFFFBDA, undef,
0xFFFFFFFFFBDD..0xFFFFFFFFFBDF,  0xFFFFFFFFFBE1..0xFFFFFFFFFBE2,    0xFFFFFFFFFBE4..0xFFFFFFFFFBE7,    0xFFFFFFFFFBE9..0xFFFFFFFFFBFB, undef,
0xFFFFFFFFFBFD..0xFFFFFFFFFC03,  0xFFFFFFFFFC06, undef,
0xFFFFFFFFFC08..0xFFFFFFFFFC0D,  0xFFFFFFFFFC0F..0xFFFFFFFFFC12,    0xFFFFFFFFFC15..0xFFFFFFFFFC16,    0xFFFFFFFFFC18..0xFFFFFFFFFC1A, undef,
0xFFFFFFFFFC1C..0xFFFFFFFFFC1D,  0xFFFFFFFFFC1F,                    0xFFFFFFFFFC21..0xFFFFFFFFFC22,    0xFFFFFFFFFC26..0xFFFFFFFFFC28,    0xFFFFFFFFFC2A,                    0xFFFFFFFFFC2C..0xFFFFFFFFFC2D, undef,
0xFFFFFFFFFC2F..0xFFFFFFFFFC34,  0xFFFFFFFFFC36..0xFFFFFFFFFC3A,    0xFFFFFFFFFC3C..0xFFFFFFFFFC3E,    0xFFFFFFFFFC40..0xFFFFFFFFFC41,    0xFFFFFFFFFC44,                    0xFFFFFFFFFC46..0xFFFFFFFFFC4A, undef,
0xFFFFFFFFFC4C..0xFFFFFFFFFC53,  0xFFFFFFFFFC55..0xFFFFFFFFFC56,    0xFFFFFFFFFC58,                    0xFFFFFFFFFC5A..0xFFFFFFFFFC5D, undef,
0xFFFFFFFFFC60..0xFFFFFFFFFC61,  0xFFFFFFFFFC63..0xFFFFFFFFFC64,    0xFFFFFFFFFC66..0xFFFFFFFFFC68,    0xFFFFFFFFFC6A..0xFFFFFFFFFC6C, undef,
0xFFFFFFFFFC6E..0xFFFFFFFFFC71,  0xFFFFFFFFFC73..0xFFFFFFFFFC74,    0xFFFFFFFFFC76..0xFFFFFFFFFC77,    0xFFFFFFFFFC79..0xFFFFFFFFFC7B,    0xFFFFFFFFFC7D, undef,
0xFFFFFFFFFC7F..0xFFFFFFFFFC8E,  0xFFFFFFFFFC90..0xFFFFFFFFFC93,    0xFFFFFFFFFC95..0xFFFFFFFFFC96, undef,
0xFFFFFFFFFC98..0xFFFFFFFFFC9A,  0xFFFFFFFFFCA0..0xFFFFFFFFFCA1,    0xFFFFFFFFFCA3..0xFFFFFFFFFCA6,    0xFFFFFFFFFCA8..0xFFFFFFFFFCAA,    0xFFFFFFFFFCAD..0xFFFFFFFFFCB0, undef,
0xFFFFFFFFFCB2..0xFFFFFFFFFCB8,  0xFFFFFFFFFCBA..0xFFFFFFFFFCBD, undef,
0xFFFFFFFFFCBF..0xFFFFFFFFFCC7,  0xFFFFFFFFFCCA..0xFFFFFFFFFCCB,    0xFFFFFFFFFCCD..0xFFFFFFFFFCD4, undef,
0xFFFFFFFFFCD6..0xFFFFFFFFFCDF,  0xFFFFFFFFFCE2..0xFFFFFFFFFCE3, undef,
0xFFFFFFFFFCE6..0xFFFFFFFFFCE8,  0xFFFFFFFFFCEA..0xFFFFFFFFFCEC,    0xFFFFFFFFFCEE..0xFFFFFFFFFCF1, undef,
0xFFFFFFFFFCF3..0xFFFFFFFFFCFC,  0xFFFFFFFFFCFE..0xFFFFFFFFFD02,    0xFFFFFFFFFD04..0xFFFFFFFFFD07, undef,
0xFFFFFFFFFD09,                  0xFFFFFFFFFD0B..0xFFFFFFFFFD0C,    0xFFFFFFFFFD0F,                    0xFFFFFFFFFD11..0xFFFFFFFFFD12,    0xFFFFFFFFFD14..0xFFFFFFFFFD1A,    0xFFFFFFFFFD1C..0xFFFFFFFFFD20, undef,
0xFFFFFFFFFD22..0xFFFFFFFFFD26,  0xFFFFFFFFFD29..0xFFFFFFFFFD2B,    0xFFFFFFFFFD2D..0xFFFFFFFFFD31, undef,
0xFFFFFFFFFD34..0xFFFFFFFFFD38,  0xFFFFFFFFFD3A, undef,
0xFFFFFFFFFD3C..0xFFFFFFFFFD40,  0xFFFFFFFFFD42..0xFFFFFFFFFD43,    0xFFFFFFFFFD45,                    0xFFFFFFFFFD47..0xFFFFFFFFFD4F,    0xFFFFFFFFFD51..0xFFFFFFFFFD56, undef,
0xFFFFFFFFFD59..0xFFFFFFFFFD5A,  0xFFFFFFFFFD5C..0xFFFFFFFFFD5D,    0xFFFFFFFFFD61..0xFFFFFFFFFD63,    0xFFFFFFFFFD65,                    0xFFFFFFFFFD67..0xFFFFFFFFFD68,    0xFFFFFFFFFD6A..0xFFFFFFFFFD6B,    0xFFFFFFFFFD6D..0xFFFFFFFFFD6E, undef,
0xFFFFFFFFFD70..0xFFFFFFFFFD72,  0xFFFFFFFFFD74..0xFFFFFFFFFD75,    0xFFFFFFFFFD77,                    0xFFFFFFFFFD79..0xFFFFFFFFFD7A,    0xFFFFFFFFFD7D..0xFFFFFFFFFD80, undef,
0xFFFFFFFFFD82..0xFFFFFFFFFD88,  0xFFFFFFFFFD8A, undef,
0xFFFFFFFFFD8C..0xFFFFFFFFFD8F,  0xFFFFFFFFFD91..0xFFFFFFFFFD96,    0xFFFFFFFFFD99..0xFFFFFFFFFD9A,    0xFFFFFFFFFD9C..0xFFFFFFFFFDA0,    0xFFFFFFFFFDA4..0xFFFFFFFFFDA6,    0xFFFFFFFFFDA8..0xFFFFFFFFFDAA, undef,
0xFFFFFFFFFDAD..0xFFFFFFFFFDB3, undef,
0xFFFFFFFFFDB5..0xFFFFFFFFFDBD,  0xFFFFFFFFFDC0..0xFFFFFFFFFDC1,    0xFFFFFFFFFDC4,                    0xFFFFFFFFFDC6..0xFFFFFFFFFDC8, undef,
0xFFFFFFFFFDCB,                  0xFFFFFFFFFDCD,                    0xFFFFFFFFFDD0..0xFFFFFFFFFDD3,    0xFFFFFFFFFDD5,                    0xFFFFFFFFFDD7..0xFFFFFFFFFDDD, undef,
0xFFFFFFFFFDDF,                  0xFFFFFFFFFDE1..0xFFFFFFFFFDE2,    0xFFFFFFFFFDE5,                    0xFFFFFFFFFDE7..0xFFFFFFFFFDF2,    0xFFFFFFFFFDF4..0xFFFFFFFFFDF7, undef,
0xFFFFFFFFFDF9..0xFFFFFFFFFDFA,  0xFFFFFFFFFDFC,                    0xFFFFFFFFFDFF,                    0xFFFFFFFFFE02..0xFFFFFFFFFE06, undef,
0xFFFFFFFFFE08..0xFFFFFFFFFE0B,  0xFFFFFFFFFE0D,                    0xFFFFFFFFFE0F..0xFFFFFFFFFE11,    0xFFFFFFFFFE13,                    0xFFFFFFFFFE15..0xFFFFFFFFFE16, undef,
0xFFFFFFFFFE18,                  0xFFFFFFFFFE1A..0xFFFFFFFFFE1F,    0xFFFFFFFFFE21..0xFFFFFFFFFE22,    0xFFFFFFFFFE24..0xFFFFFFFFFE25,    0xFFFFFFFFFE27, undef,
0xFFFFFFFFFE29..0xFFFFFFFFFE32, undef,
0xFFFFFFFFFE34..0xFFFFFFFFFE38,  0xFFFFFFFFFE3A..0xFFFFFFFFFE3E,    0xFFFFFFFFFE40,                    0xFFFFFFFFFE42..0xFFFFFFFFFE43, undef,
0xFFFFFFFFFE45,                  0xFFFFFFFFFE47..0xFFFFFFFFFE48,    0xFFFFFFFFFE4B..0xFFFFFFFFFE52,    0xFFFFFFFFFE54..0xFFFFFFFFFE56,    0xFFFFFFFFFE58..0xFFFFFFFFFE59, undef,
0xFFFFFFFFFE5D..0xFFFFFFFFFE5F,  0xFFFFFFFFFE61..0xFFFFFFFFFE64, undef,
0xFFFFFFFFFE66..0xFFFFFFFFFE6D,  0xFFFFFFFFFE6F..0xFFFFFFFFFE70,    0xFFFFFFFFFE75..0xFFFFFFFFFE76,    0xFFFFFFFFFE79..0xFFFFFFFFFE7A, undef,
0xFFFFFFFFFE7D..0xFFFFFFFFFE81,  0xFFFFFFFFFE83..0xFFFFFFFFFE85,    0xFFFFFFFFFE87,                    0xFFFFFFFFFE89..0xFFFFFFFFFE91, undef,
0xFFFFFFFFFE94..0xFFFFFFFFFE96,  0xFFFFFFFFFE98,                    0xFFFFFFFFFE9A..0xFFFFFFFFFE9C,    0xFFFFFFFFFE9E..0xFFFFFFFFFEAE, undef,
0xFFFFFFFFFEB0..0xFFFFFFFFFEB5,  0xFFFFFFFFFEB7..0xFFFFFFFFFEB8,    0xFFFFFFFFFEBC..0xFFFFFFFFFEBE, undef,
0xFFFFFFFFFEC0..0xFFFFFFFFFEC3,  0xFFFFFFFFFEC5..0xFFFFFFFFFEC6,    0xFFFFFFFFFEC9..0xFFFFFFFFFECC, undef,
0xFFFFFFFFFECE,                  0xFFFFFFFFFED1..0xFFFFFFFFFED3,    0xFFFFFFFFFED5..0xFFFFFFFFFED6,    0xFFFFFFFFFED8..0xFFFFFFFFFEDB,    0xFFFFFFFFFEDD, undef,
0xFFFFFFFFFEDF..0xFFFFFFFFFEE4,  0xFFFFFFFFFEE6,                    0xFFFFFFFFFEE9..0xFFFFFFFFFEF0,    0xFFFFFFFFFEF3..0xFFFFFFFFFEF5,    0xFFFFFFFFFEF7..0xFFFFFFFFFEF8,    0xFFFFFFFFFEFA..0xFFFFFFFFFEFB, undef,
0xFFFFFFFFFEFD..0xFFFFFFFFFF01,  0xFFFFFFFFFF03,                    0xFFFFFFFFFF05..0xFFFFFFFFFF07,    0xFFFFFFFFFF0A..0xFFFFFFFFFF0D, undef,
0xFFFFFFFFFF0F..0xFFFFFFFFFF11,  0xFFFFFFFFFF14..0xFFFFFFFFFF16,    0xFFFFFFFFFF18,                    0xFFFFFFFFFF1A..0xFFFFFFFFFF1B,    0xFFFFFFFFFF1D..0xFFFFFFFFFF20, undef,
0xFFFFFFFFFF22..0xFFFFFFFFFF27,  0xFFFFFFFFFF29..0xFFFFFFFFFF2E,    0xFFFFFFFFFF30..0xFFFFFFFFFF37, undef,
0xFFFFFFFFFF3A..0xFFFFFFFFFF3C,  0xFFFFFFFFFF3E..0xFFFFFFFFFF42,    0xFFFFFFFFFF44..0xFFFFFFFFFF4F, undef,
0xFFFFFFFFFF52..0xFFFFFFFFFF59, undef,
0xFFFFFFFFFF5B..0xFFFFFFFFFF67,  0xFFFFFFFFFF69,                    0xFFFFFFFFFF6B,                    0xFFFFFFFFFF6D..0xFFFFFFFFFF6E,    0xFFFFFFFFFF70..0xFFFFFFFFFF73,    0xFFFFFFFFFF75..0xFFFFFFFFFF78, undef,
0xFFFFFFFFFF7B,                  0xFFFFFFFFFF7F..0xFFFFFFFFFF81,    0xFFFFFFFFFF87..0xFFFFFFFFFF8B,    0xFFFFFFFFFF8D..0xFFFFFFFFFF94,    0xFFFFFFFFFF96..0xFFFFFFFFFF97, undef,
0xFFFFFFFFFF99,                  0xFFFFFFFFFF9B..0xFFFFFFFFFFA1,    0xFFFFFFFFFFA4,                    0xFFFFFFFFFFA6,                    0xFFFFFFFFFFA8..0xFFFFFFFFFFA9,    0xFFFFFFFFFFAB..0xFFFFFFFFFFAD, undef,
0xFFFFFFFFFFAF..0xFFFFFFFFFFBC, undef,
0xFFFFFFFFFFBE..0xFFFFFFFFFFCB,  0xFFFFFFFFFFCF..0xFFFFFFFFFFD3,    0xFFFFFFFFFFD5,                    0xFFFFFFFFFFD7..0xFFFFFFFFFFDA,    0xFFFFFFFFFFDD..0xFFFFFFFFFFDF,    0xFFFFFFFFFFE1, undef,
0xFFFFFFFFFFE4..0xFFFFFFFFFFE9,  0xFFFFFFFFFFEB..0xFFFFFFFFFFEC,    0xFFFFFFFFFFEE..0xFFFFFFFFFFF2,    0xFFFFFFFFFFF4..0xFFFFFFFFFFF8, undef,
0xFFFFFFFFFFFA,                  0xFFFFFFFFFFFC,                    0xFFFFFFFFFFFE..0x1000000000003, undef,
0x1000000000006..0x1000000000014,0x1000000000017..0x100000000001B,  0x100000000001D, undef,
0x1000000000020,                 0x1000000000022,                   0x1000000000025,                   0x1000000000027,                   0x1000000000029,                   0x100000000002B..0x100000000002D,  0x100000000002F, undef,
0x1000000000031..0x1000000000038, undef,
0x100000000003B..0x1000000000046,0x1000000000048..0x100000000004E, undef,
0x1000000000051,                 0x1000000000053..0x1000000000056,  0x1000000000058..0x100000000005A,  0x100000000005C..0x1000000000060, undef,
0x1000000000062..0x1000000000065,0x1000000000068..0x1000000000069,  0x100000000006C..0x100000000006F,  0x1000000000071..0x1000000000072,  0x1000000000074..0x100000000007D, undef,
0x100000000007F..0x1000000000082,0x1000000000084..0x1000000000085,  0x1000000000087..0x1000000000088,  0x100000000008B,                   0x100000000008D..0x1000000000093,  0x1000000000095..0x1000000000096, undef,
0x1000000000098..0x10000000000A0,0x10000000000A2..0x10000000000A7,  0x10000000000AA,                   0x10000000000AC..0x10000000000AE, undef,
0x10000000000B0..0x10000000000B6,0x10000000000B8..0x10000000000B9,  0x10000000000BC..0x10000000000CA, undef,
0x10000000000CD..0x10000000000D3,0x10000000000D7,                   0x10000000000D9..0x10000000000DB,  0x10000000000DD..0x10000000000E3, undef,
0x10000000000E5..0x10000000000EA,0x10000000000EC..0x10000000000F0,  0x10000000000F2..0x10000000000F8,  0x10000000000FA..0x10000000000FB, undef,
0x10000000000FE..0x1000000000100,0x1000000000102..0x1000000000104,  0x1000000000106,                   0x1000000000108..0x100000000010A, undef,
0x100000000010D..0x1000000000110,0x1000000000112..0x1000000000113,  0x1000000000116,                   0x1000000000119,                   0x100000000011C..0x1000000000120,  0x1000000000122..0x1000000000126, undef,
0x1000000000128..0x100000000012A,0x100000000012D..0x1000000000131, undef,
0x1000000000133..0x100000000013C,0x100000000013E..0x1000000000141,  0x1000000000143..0x1000000000146,  0x1000000000148..0x100000000014B, undef,
0x100000000014D..0x1000000000150,0x1000000000152..0x1000000000154, undef,
0x1000000000156..0x100000000015F,0x1000000000161..0x1000000000166,  0x1000000000168..0x1000000000169,  0x100000000016B..0x100000000016C, undef,
0x100000000016E..0x1000000000177,0x1000000000179..0x100000000017B, undef,
0x100000000017D..0x1000000000183,0x1000000000185..0x1000000000187,  0x100000000018A..0x100000000018D,  0x100000000018F..0x1000000000190, undef,
0x1000000000193..0x1000000000194,0x1000000000196,                   0x1000000000198..0x100000000019B, undef,
0x100000000019D..0x100000000019E,0x10000000001A0..0x10000000001A2,  0x10000000001A4..0x10000000001B3, undef,
0x10000000001B5..0x10000000001B6,0x10000000001BA,                   0x10000000001BC..0x10000000001BE,  0x10000000001C0,                   0x10000000001C2, undef,
0x10000000001C4..0x10000000001D0,0x10000000001D3..0x10000000001D8, undef,
0x10000000001DA..0x10000000001E1,0x10000000001E4..0x10000000001E5,  0x10000000001E8..0x10000000001EA,  0x10000000001ED..0x10000000001EE, undef,
0x10000000001F4,                 0x10000000001F7..0x10000000001FC,  0x10000000001FF,                   0x1000000000201,                   0x1000000000203,                   0x1000000000205..0x1000000000209,  0x100000000020B..0x100000000020D, undef,
0x100000000020F..0x1000000000214,0x1000000000216,                   0x1000000000218..0x1000000000219,  0x100000000021B..0x100000000021D,  0x100000000021F..0x1000000000223, undef,
0x1000000000225..0x1000000000227,0x100000000022B..0x100000000022E,  0x1000000000230,                   0x1000000000232..0x1000000000233, undef,
0x1000000000235..0x1000000000238,0x100000000023A..0x100000000023D,  0x100000000023F..0x1000000000241,  0x1000000000243..0x100000000024B, undef,
0x100000000024F..0x1000000000252,0x1000000000254,                   0x1000000000256..0x1000000000257,  0x1000000000259, undef,
0x100000000025F..0x1000000000262,0x1000000000264..0x100000000026C,  0x100000000026F..0x1000000000274, undef,
0x1000000000276,                 0x1000000000278..0x100000000027D,  0x100000000027F..0x1000000000280,  0x1000000000282..0x1000000000283,  0x1000000000285..0x1000000000289, undef,
0x100000000028B..0x1000000000293,0x1000000000295..0x100000000029B,  0x100000000029D..0x10000000002A0, undef,
0x10000000002A2..0x10000000002A4,0x10000000002A7..0x10000000002AD,  0x10000000002AF..0x10000000002B0, undef,
0x10000000002B2..0x10000000002BA,0x10000000002BD,                   0x10000000002BF,                   0x10000000002C3..0x10000000002D1, undef,
0x10000000002D4..0x10000000002D7,0x10000000002D9..0x10000000002DA, undef,
0x10000000002DC..0x10000000002E1,0x10000000002E3..0x10000000002EA,  0x10000000002ED,                   0x10000000002EF..0x10000000002F0, undef,
0x10000000002F3..0x10000000002F4,0x10000000002F6..0x10000000002FF, undef,
0x1000000000301..0x1000000000306,0x1000000000308..0x100000000030A,  0x100000000030D,                   0x1000000000314..0x1000000000318,  0x100000000031A, undef,
0x100000000031C..0x1000000000323,0x1000000000325..0x1000000000327,  0x100000000032A..0x100000000032B,  0x100000000032D..0x100000000032E,  0x1000000000330..0x1000000000331, undef,
0x1000000000334..0x1000000000336,0x1000000000339..0x100000000033D,  0x100000000033F..0x1000000000341, undef,
0x1000000000343..0x1000000000345,0x1000000000347..0x100000000034A, undef,
0x100000000034C..0x1000000000353,0x1000000000357,                   0x1000000000359..0x100000000035A,  0x100000000035C..0x100000000035F, undef,
0x1000000000361..0x1000000000363,0x1000000000365..0x1000000000367,  0x1000000000369,                   0x100000000036C..0x100000000036D,  0x100000000036F..0x1000000000373,  0x1000000000375..0x100000000037A, undef,
0x100000000037C..0x100000000037E, undef,
0x1000000000380..0x1000000000391,0x1000000000394..0x1000000000397,  0x1000000000399..0x100000000039A,  0x100000000039D..0x100000000039F,  0x10000000003A1, undef,
0x10000000003A4..0x10000000003B0,0x10000000003B2..0x10000000003B3,  0x10000000003B7,                   0x10000000003B9,                   0x10000000003BB,                   0x10000000003BD,                   0x10000000003BF, undef,
0x10000000003C1..0x10000000003C6,0x10000000003C8..0x10000000003D0, undef,
0x10000000003D3..0x10000000003D9,0x10000000003DB..0x10000000003DD,  0x10000000003DF..0x10000000003E0, undef,
0x10000000003E2..0x10000000003ED,0x10000000003EF..0x10000000003F2,  0x10000000003F4..0x10000000003F6,  0x10000000003FA..0x10000000003FC,  0x10000000003FE..0x10000000003FF, undef,
0x1000000000401,                 0x1000000000403,                   0x1000000000405..0x1000000000406,  0x1000000000409..0x100000000040F, undef,
0x1000000000411..0x1000000000412,0x1000000000414..0x1000000000415,  0x1000000000418..0x100000000041A,  0x100000000041C..0x100000000041D,  0x100000000041F..0x1000000000420,  0x1000000000423..0x1000000000426, undef,
0x1000000000428..0x100000000042A, undef,
0x100000000042D..0x1000000000438,0x100000000043D..0x100000000043F,  0x1000000000441..0x1000000000445,  0x1000000000448,                   0x100000000044A..0x100000000044C, undef,
0x100000000044E,                 0x1000000000450..0x1000000000454,  0x1000000000456..0x1000000000457,  0x100000000045A,                   0x100000000045D..0x100000000045E,  0x1000000000460..0x1000000000461, undef,
0x1000000000463,                 0x1000000000466,                   0x1000000000468..0x100000000046A,  0x100000000046C..0x100000000046D, undef,
0x1000000000470..0x1000000000472,0x1000000000474..0x100000000047A,  0x100000000047C..0x100000000047F,  0x1000000000482..0x1000000000484, undef,
0x1000000000486..0x100000000048C,0x100000000048E..0x1000000000494,  0x1000000000498..0x100000000049C,  0x100000000049F..0x10000000004A4,  0x10000000004A6..0x10000000004A7, undef,
0x10000000004A9..0x10000000004AA,0x10000000004AD, undef,
0x10000000004B1..0x10000000004BC,0x10000000004BF..0x10000000004C3,  0x10000000004C5..0x10000000004C8, undef,
0x10000000004CA,                 0x10000000004CC..0x10000000004CF,  0x10000000004D1..0x10000000004D2,  0x10000000004D5,                   0x10000000004D7..0x10000000004D9,  0x10000000004DB..0x10000000004DD, undef,
0x10000000004DF..0x10000000004E0,0x10000000004E2..0x10000000004E3,  0x10000000004E5,                   0x10000000004E7..0x10000000004E8, undef,
0x10000000004EA..0x10000000004F6,0x10000000004F8,                   0x10000000004FA..0x10000000004FD,  0x10000000004FF..0x1000000000500, undef,
0x1000000000502..0x1000000000507,0x1000000000509,                   0x100000000050B..0x100000000050C, undef,
0x100000000050F,                 0x1000000000511..0x1000000000516,  0x1000000000518..0x1000000000519,  0x100000000051C,                   0x100000000051E, undef,
0x1000000000521..0x1000000000524,0x1000000000526..0x1000000000528,  0x100000000052B..0x100000000052C,  0x100000000052E..0x100000000052F,  0x1000000000532..0x1000000000534, undef,
0x1000000000536..0x100000000053C,0x100000000053F,                   0x1000000000542,                   0x1000000000545..0x1000000000546,  0x1000000000548..0x100000000054A, undef,
0x100000000054C..0x1000000000555,0x1000000000557, undef,
0x100000000055A..0x1000000000569,0x100000000056B..0x100000000056E,  0x1000000000570..0x1000000000572,  0x1000000000575..0x1000000000576,  0x1000000000578..0x1000000000579,  0x100000000057B..0x100000000057E, undef,
0x1000000000580, undef,
0x1000000000582..0x1000000000596, undef,
0x1000000000598..0x100000000059D,0x10000000005A0,                   0x10000000005A2,                   0x10000000005A5..0x10000000005A8,  0x10000000005AA,                   0x10000000005AF,                   0x10000000005B1..0x10000000005B2,  0x10000000005B4..0x10000000005B5, undef,
0x10000000005B7,                 0x10000000005B9..0x10000000005BB,  0x10000000005BE..0x10000000005C4, undef,
0x10000000005C8..0x10000000005CB,0x10000000005CD..0x10000000005D1,  0x10000000005D3..0x10000000005D5,  0x10000000005D7,                   0x10000000005D9..0x10000000005DB, undef,
0x10000000005DD..0x10000000005E0,0x10000000005E2..0x10000000005E5,  0x10000000005E7..0x10000000005E8,  0x10000000005EA,                   0x10000000005EC..0x10000000005F1, undef,
0x10000000005F3..0x10000000005F4,0x10000000005F6,                   0x10000000005F8..0x1000000000600, undef,
0x1000000000602..0x1000000000605,0x1000000000607,                   0x1000000000609..0x100000000060C, undef,
0x100000000060E..0x1000000000612,0x1000000000616,                   0x1000000000618..0x100000000061A,  0x100000000061D,                   0x1000000000620..0x1000000000621,  0x1000000000623..0x1000000000628, undef,
0x100000000062B..0x100000000062C,0x100000000062E..0x100000000062F,  0x1000000000632..0x1000000000637,  0x1000000000639..0x100000000063B,  0x100000000063D,                   0x100000000063F,                   0x1000000000641..0x1000000000644, undef,
0x1000000000646..0x100000000064A,0x100000000064D..0x1000000000650,  0x1000000000652..0x1000000000654,  0x1000000000656..0x1000000000659, undef,
0x100000000065C..0x1000000000665,0x1000000000667,                   0x1000000000669,                   0x100000000066B..0x100000000066C, undef,
0x100000000066F,                 0x1000000000671..0x1000000000673,  0x1000000000675..0x1000000000679, undef,
#0x100000000067B..0x1000000000681,0x1000000000683,                   0x1000000000685..0x1000000000687,  0x1000000000689..0x100000000068D,  0x100000000068F..0x1000000000697, undef,
#0x1000000000699..0x10000000006A7,0x10000000006A9..0x10000000006AF,  0x10000000006B1,                   0x10000000006B4..0x10000000006B5, undef,
#0x10000000006B8,                 0x10000000006BA..0x10000000006BD,  0x10000000006C0..0x10000000006C4, undef,
#0x10000000006C6,                 0x10000000006C8,                   0x10000000006CA..0x10000000006CF,  0x10000000006D1..0x10000000006D6,  0x10000000006D8..0x10000000006DB, undef,
#0x10000000006DD..0x10000000006DE,0x10000000006E0..0x10000000006EB, undef,
#0x10000000006ED..0x10000000006F0,0x10000000006F2..0x10000000006F3,  0x10000000006F5..0x10000000006FC,  0x10000000006FE..0x1000000000700, undef,
#0x1000000000702..0x1000000000706,0x1000000000708..0x1000000000709,  0x100000000070C..0x1000000000713,  0x1000000000715..0x1000000000716,  0x1000000000718..0x100000000071C, undef,
#0x100000000071E..0x1000000000720,0x1000000000722..0x1000000000729,  0x100000000072B..0x100000000072F, undef,
#0x1000000000731..0x1000000000736,0x1000000000739,                   0x100000000073C..0x100000000073F,  0x1000000000741..0x1000000000742,  0x1000000000744..0x1000000000747, undef,
#0x1000000000749..0x100000000074B,0x100000000074F,                   0x1000000000753,                   0x1000000000755..0x1000000000756,  0x1000000000758..0x100000000075B, undef,
#0x100000000075D..0x1000000000761,0x1000000000764,                   0x1000000000767..0x100000000076A,  0x100000000076C..0x1000000000775, undef,
#0x1000000000777,                 0x1000000000779..0x100000000077A,  0x100000000077E..0x1000000000780,  0x1000000000782..0x1000000000788, undef,
#0x100000000078A..0x100000000079A,0x100000000079C..0x10000000007A6,  0x10000000007A9, undef,
#0x10000000007AB..0x10000000007B1,0x10000000007B3..0x10000000007B5,  0x10000000007B7..0x10000000007B9,  0x10000000007BB..0x10000000007BF, undef,
#0x10000000007C1,                 0x10000000007C3,                   0x10000000007C5..0x10000000007CA,  0x10000000007CC, undef,
#0x10000000007CF..0x10000000007D0,0x10000000007D2..0x10000000007D6,  0x10000000007D8..0x10000000007D9,  0x10000000007DB,                   0x10000000007DD, undef,
#0x10000000007E0..0x10000000007E3,0x10000000007E6,                   0x10000000007E8, undef,
#0x10000000007EA..0x10000000007EF,0x10000000007F1..0x10000000007F7, undef,
#0x10000000007F9,                 0x10000000007FD..0x10000000007FF,

],      [281474976708637, 281474976708648, 281474976708656, 281474976708660, 281474976708701, 281474976708720, 281474976708742, 281474976708745, 281474976708779, 281474976708780, 281474976708800, 281474976708842, 281474976708859, 
#281474976708862, 281474976708871, 281474976708874, 281474976708903, 281474976708941, 281474976708950, 281474976709017, 
#281474976709021, 281474976709025, 281474976709033, 281474976709037, 281474976709039, 281474976709053, 281474976709081, 
#281474976709102, 281474976709103, 281474976709105, 281474976709108, 281474976709155, 281474976709183, 281474976709201, 
#281474976709205, 281474976709258, 281474976709262, 281474976709263, 281474976709271, 281474976709285, 281474976709294, 
281474976709313, 281474976709324, 281474976709344, 281474976709365, 281474976709366, 281474976709398, 281474976709410, 
#281474976709416, 281474976709417, 281474976709493, 281474976709521, 281474976709522, 281474976709524, 281474976709526, 
#281474976709540, 281474976709560, 281474976709583, 281474976709585, 281474976709601, 281474976709607, 281474976709614, 
#281474976709643, 281474976709684, 281474976709692, 281474976709693, 281474976709704, 281474976709720, 281474976709744, 
#281474976709752, 281474976709754, 281474976709756, 281474976709788, 281474976709819, 281474976709866, 281474976709891, 
#281474976709911, 281474976709926, 281474976709970, 281474976710030, 281474976710059, 281474976710071, 281474976710095, 
#281474976710120, 281474976710163, 281474976710170, 281474976710200, 281474976710205, 281474976710210, 281474976710219, 
#281474976710236, 281474976710241, 281474976710246, 281474976710255, 281474976710256, 281474976710277, 281474976710280, 
#281474976710303, 281474976710311, 281474976710321, 281474976710348, 281474976710362, 281474976710384, 281474976710413, 
#281474976710417, 281474976710421, 281474976710435, 281474976710447, 281474976710448, 281474976710465, 281474976710468, 
#281474976710469, 281474976710474, 281474976710476, 281474976710482, 281474976710484, 281474976710504, 281474976710513, 
281474976710534, 281474976710544,
281474976710568, 281474976710585, 281474976710592, 281474976710612, 281474976710624, 281474976710645, 281474976710664,
281474976710670, 281474976710726, 281474976710753, 281474976710782, 281474976710811, 281474976710814, 281474976710834, 
281474976710858, 281474976710942, 281474976710944, 281474976710954, 281474976710965, 281474976710976, 281474976711027, 
281474976711029, 281474976711032, 281474976711074, 281474976711076, 281474976711077, 281474976711088, 281474976711107, 
281474976711185, 281474976711220, 281474976711245, 281474976711272, 281474976711276, 281474976711287, 281474976711300, 
281474976711309, 281474976711318, 281474976711322, 281474976711355, 281474976711368, 281474976711373, 281474976711398, 
281474976711409, 281474976711483, 281474976711485, 281474976711509, 281474976711549, 281474976711581, 281474976711612, 
281474976711621, 281474976711696, 281474976711715, 281474976711728, 281474976711735, 281474976711801, 281474976711872, 
281474976711873, 281474976711880, 281474976711889, 281474976711899, 281474976711912, 281474976711935, 281474976711939, 
281474976711956, 281474976712013, 281474976712045, 281474976712065, 281474976712082, 281474976712087, 281474976712104, 
281474976712109, 281474976712127, 281474976712135, 281474976712155, 281474976712165, 281474976712168, 281474976712172, 
#281474976712189, 281474976712220, 281474976712231, 281474976712234, 281474976712235, 281474976712251, 281474976712269, 
#281474976712281, 281474976712330, 281474976712338, 281474976712348, 281474976712349, 281474976712350, 281474976712380,
#281474976712388, 281474976712391, 281474976712402, 281474976712404, 281474976712434, 281474976712440, 281474976712447,
#281474976712451, 281474976712457, 281474976712474, 281474976712479, 281474976712488, 281474976712536, 281474976712542,
# 281474976712543, 281474976712546, 281474976712555, 281474976712556, 281474976712578, 281474976712579, 281474976712605,
# 281474976712610, 281474976712630, 281474976712634, 281474976712653, 281474976712683, 281474976712687, 281474976712692,
# 281474976712700
	],
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
ICEPack is an instantiable object class for a data structure I categorically define as a Compressed Truth Vector.  The inspirational concept I was trying to achieve when I set out to develop this data structure was something which combined the access modalities of hashes and arrays without the complexity or overhead of a database, meeting or exceeding a modern standard of computational efficiency.  Elements are addressable by sparse key as in hashes, or by ordered index as in arrays.  The architecture has three abstraction layers, starting with a custom binary encoding I call Inversion Cycle RLE, which is a minimized version of RLE for alternating boolean values.  The second abstraction layer is a fairly basic binary search implementation over a sorted array of these IC-RLE segments, and the third abstraction layer is a stratified/laminar regressive quantization of the second-layer data array, grading the namespace content down into increasingly quantized reductions, storing respective modulus values in the freed up allocation space for each combined unit key, which can be atomically updated by setters as the structure changes, and efficiently summed by getters to compute the sort order of sparse keys on demand.  I want to call it dynamic enumeration.

In a way, it allows for treating defined and undefined namespace as two dimensions of one regular series.  It enables an access modality similar to Perl's range operator (where you specify a series in terms of its starting and ending value), but now those values can be sparse keys, and they can select from either the defined or undefined sparse key namespace efficiently.  This makes mass shuffle practical.  Indeed, the intended application is mass distributed session ID randomization where collision is prevented through true namespace conservation (not merely leveraging astronomical odds) and without introducing a special need or requirement for a core network to maintain sync across edge servers.

I first developed a complete proof of concept in 2020 written in Perl.  Since then, I have taken on learning C and giving the specification and architecture the proper treatment to realize an enterprise grade implementation.


	OBJECTIVE
	To implement a session ID generator that is non-deterministic, non-repeating, and operates ad-hoc
	on all edge devices while maintaining one coherent mapping without a specialized core network.
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