use strict;
use warnings;
my @CAST=( 'ui08', 'ui16', 'ui32', 'ui64' );
my @ABCD=('$a', '$b');

my	($anycast, $qs, $b, $b2, $o, $o2, $c, @casts, @c, @b, @o, @s, @q);
my $mtime = (stat($0))[9];
my $readable_date = scalar localtime($mtime);
sub fitcast($$){	my ( $cast, $space)= @_;
	foreach my $overcast(	1, 2, 4, 8,		3, 5, 6,		7){	return	$overcast if $overcast >=$cast and $overcast <=$space;	}
		#				^  ^  ^  ^		^  ^  ^		^
		#				1 cast		2 casts		3 casts
	die	#				
	}
open(my $fh, '>',	'lluiCASThab.h');
  print $fh(
	"/*	This file was programmatically generated.\n\t	script:\t\t$0\n\t	last modified:\t$readable_date	*/\n\n",
	'#define lluiCASThab( $b, $a, $pq )				/*	to assign (2) values with no overflow				*/		\\', "\n");


		for( $q[1]=1; $q[1]<9; ++$q[1] ){
			for( $q[0]=1; $q[0]<9; ++$q[0] ){

						$s[1]=	$q[1];
				$s[0]=	$s[1]+	$q[0];

				$qs= ( ( $q[1] -1) <<3)|	($q[0]-1);

				$anycast=0;
				$anycast |=	$casts[$_]= fitcast( $q[$_], $s[$_])	foreach 0..1;

				for( $c=3;	$c>=0;  --$c){
					if( $casts[ 0] &	($b=  (1<<$c ) ) ){
						print $fh( 	'case 0x', sprintf('%02X', $qs), ":	/* $q[0]x$q[1]		*/ ",
									'	*( (',$CAST[ $c],	'*) ( $qp	) )= ', $ABCD[0], ';      	');
						last;
					}	}
				$o2=$b;									$b2= ($b<<3);
				for( --$c;		$c>=0;  --$c){
					if( $casts[ 0] &	($b=  (1<<$c ) ) ){
							print $fh( "	\\\n						",
									'	*( (',$CAST[ $c],	'*) ( $qp +', sprintf('%-2d', $o2), ') )= ', $ABCD[0], '>>', $b2, ';	');
						$o2+=$b;							$b2+= ($b<<3);
					}	}
				$o=$q[0];

				foreach my $i( 1){
					$o2=$o;
					for($c=3;	$c>=0;  --$c){
						if( $casts[ $i] &	($b=  (1<<$c ) ) ){
							print $fh( '	*( (',$CAST[ $c],	'*) ( $qp +', sprintf('%-2d', $o2), ') )= ',$ABCD[$i], ';      	');
							last;
						}	}

					$o2=$o+$b;							$b2= ($b<<3);
					for(--$c;	$c>=0;  --$c){
						if( $casts[ $i] &	($b=  (1<<$c ) ) ){
							print $fh( "	\\\n							",
									'							'x$i,
									'	*( (',$CAST[ $c],	'*) ( $qp +', sprintf('%-2d', $o2), ') )= ',$ABCD[$i], '>>', $b2, ';');
							$o2+=$b;						$b2+= ($b<<3);
						}	}
					$o+=$q[$i];
					}
				print $fh( "	break;	\\\n");
			}	}



close( $fh);