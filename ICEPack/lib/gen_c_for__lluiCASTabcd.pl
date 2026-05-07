use strict;
use warnings;
my @CAST=( 'ui08', 'ui16', 'ui32', 'ui64' );
my @ABCD=('$a', '$b', '$c', '$d');

my	($anycast, $qs, $b, $b2, $o, $o2, $c, @casts, @c, @b, @o, @s, @q);

sub fitcast($$){	my ( $cast, $space)= @_;
	foreach my $overcast(	1, 2, 4, 8,		3, 5, 6,		7){	return	$overcast if $overcast >=$cast and $overcast <=$space;	}
		#				^  ^  ^  ^		^  ^  ^		^
		#				1 cast		2 casts		3 casts
	die	#				
	}
open(my $fh, '>',	'lluiCASTabcd.c');
print $fh( 		'#define lluiCASTabcd( $d, $c, $b, $a, $pq )		/*	to assign (4) values with no overflow				*/		\\', "\n");
for( $q[3]=1; $q[3]<9; ++$q[3] ){
	for( $q[2]=1; $q[2]<9; ++$q[2] ){
		for( $q[1]=1; $q[1]<9; ++$q[1] ){
			for( $q[0]=1; $q[0]<9; ++$q[0] ){	$s[3]	=$q[3];
								$s[2]=	$s[3]	+$q[2];
						$s[1]=	$s[2]			+$q[1];
				$s[0]=	$s[1]					+$q[0];

				$qs= ( ( $q[3] -1) <<9)|	( ( $q[2] -1) <<6)|	( ( $q[1] -1) <<3)|	($q[0]-1);

				$anycast=0;
				$anycast |=	$casts[$_]= fitcast( $q[$_], $s[$_])	foreach 0..3;

				for( $c=3;	$c>=0;  --$c){
					if( $casts[ 0] &	($b=  (1<<$c ) ) ){
						print $fh( 	'case 0x', sprintf('%03X', $qs), ":	/* $q[0]x$q[1]x$q[2]x$q[3]	*/ ",
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
				$o=$q[0];			

				foreach my $i( 1..3){
					$o2=$o;
					for($c=3;	$c>=0;  --$c){
						if( $casts[ $i] &	($b=  (1<<$c ) ) ){
							print $fh( '	*( (',$CAST[ $c],	'*) ( $qp +', sprintf('%-2d', $o2), ') )= ',$ABCD[$i], ';	');
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
	}	}	}	}



close( $fh);