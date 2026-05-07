use strict;
use warnings;
my @CAST=( 'ui08', 'ui16', 'ui32', 'ui64' );
my @ABCD=('$a');

my	($anycast, $qs, $b, $b2, $o, $o2, $c, @casts, @c, @b, @o, @s, @q);

sub fitcast($$){	my ( $cast, $space)= @_;
	foreach my $overcast(	1, 2, 4, 8,		3, 5, 6,		7){	return	$overcast if $overcast >=$cast and $overcast <=$space;	}
		#				^  ^  ^  ^		^  ^  ^		^
		#				1 cast		2 casts		3 casts
	die	#				
	}
open(my $fh, '>',	'lluiCASTa.c');
print $fh( 		'#define lluiCASTa( $b, $a, $pq )			/*	to assign (2) values with an overflow risk of 1 byte	*/		\\', "\n");



			for( $q[0]=1; $q[0]<9; ++$q[0] ){


				$s[0]=	$q[0];

				$qs= ($q[0]-1);

				$anycast=0;
				$anycast |=	$casts[0]= fitcast( $q[0], $s[0]);

				for( $c=3;	$c>=0;  --$c){
					if( $casts[ 0] &	($b=  (1<<$c ) ) ){
						print $fh( 	'case 0x', sprintf('%01X', $qs), ":	/* $q[0]			*/ ",
									'	*( (',$CAST[ $c],	'*) ( $qp	) )= ', $ABCD[0], ';		');
						last;
					}	}
				$o2=$b;									$b2= ($b<<3);
				for( --$c;		$c>=0;  --$c){
					if( $casts[ 0] &	($b=  (1<<$c ) ) ){
							print $fh( "	\\\n						",
									'	*( (',$CAST[ $c],	'*) ( $qp +', sprintf('%-2d', $o2), ') )= ', $ABCD[0], '>>', $b2, ';	');
						$o2+=$b;							$b2+= ($b<<3);
					}	}

				print $fh( "	break;	\\\n");
				}



close( $fh);