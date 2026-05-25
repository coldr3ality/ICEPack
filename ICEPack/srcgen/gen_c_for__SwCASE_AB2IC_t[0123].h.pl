use strict;
use warnings;
my @CAST=( 'ui08', 'ui16', 'ui32', 'ui64' );
my @ABCD=('$a', '$b');
my	$T="\t\t\t\t\t\t\t";
use constant	A=>0;
use constant	B=>1;
use constant	C=>2;
use constant	D=>3;
#	|					|				|				|
#	|Let's generate 		|Variant suffix 	|Add'l args		|Perl code to be eval'ed— to generate add'l C code
#	|several variants		|shown in name	|to function-like	|at the end of each switch-case, 
#	|at once.				|of macro & file:	|macro:			|immediately preceding "break":
my @CASE_TERMINATOR=( 	'',				'',				'',
						'_inc',			', $i',			'printf $fh( "	\$i +=%3d;",					$s[A]		);',
						'_inc_dec',		', $i, $o',			'printf $fh( "	\$i +=%3d;	\$o -=%3d;",		$s[A], $s[A]	);',
#	|					|				|				|
#	|					|				|				|
						);
my	($anycast, $qs, $b, $b2, $o, $o2, $c, @casts, @c, @b, @o, @s, @q);
my $mtime = (stat($0))[9];
my $readable_date = scalar localtime($mtime);

sub fitcast($$){	my ( $cast, $space)= @_;
#						0 0 0 0		1  3  2              1
	foreach my $overcast(	1, 2, 4, 8,		3, 5, 6,		7){	return	$overcast if $overcast >=$cast and $overcast <=$space;	}
		#				^  ^  ^  ^		^  ^  ^		^
		#				1 cast		2 casts		3 casts
	die	#				
	}


for( my $ctv=0; $ctv< $#CASE_TERMINATOR; $ctv+=3 ){
 foreach my $overrunBytes(0..3){
  open(my $fh, '>',	"SwCASE_AB2IC_t$overrunBytes$CASE_TERMINATOR[$ctv].h");
  printf $fh(
	"/*	This file was programmatically generated.\n\t	script:\t\t$0\n\t	last modified:\t$readable_date	*/\n\n".
		"#define	SwCASE_AB2IC_t$overrunBytes%s( \$a, \$b, \$pq%s)	/*	cast [a, b] to the high side of *pq	w/ ($overrunBytes) byte[s] of overrun tolerance	*/		\\\n",
		$CASE_TERMINATOR[$ctv		],	# variant's name suffix
		$CASE_TERMINATOR[$ctv	+1	],	# variant's add'l macro arguments
		);

###########	part 1 of 4:	A disabled;	B disabled	(neither)	###########
  print $fh("\\\n/*	part 1 of 4:	A disabled;	B disabled	(neither)	*/	\\\n"	);

  printf $fh("case 0x%02X:	/*  0, 0   */	\\\n", $_)  			foreach( 0..	0x3E );
  print $fh('case 0x3F:'.	"	/*  0, 0   */$T$T			break;	\\\n");


###########	part 2 of 4:	A enabled;	B disabled	(just A)	###########
  printf $fh("\\\n/*	part 2 of 4:	A enabled;	B disabled	(just A)	*/	\\\n"	);
			for( $q[B]=1;		$q[B]< 9; ++$q[B] ){
				for( $q[A]=1;	$q[A]< 9; ++$q[A] ){	#	q( A ): 1..8	q( B ): 0
					$qs=0x40|	( ( $q[B] -1) <<3)|	($q[A]-1);
					$s[A]=			$q[A];	$anycast=	$casts[0]= fitcast( $q[A], $s[A] +$overrunBytes );

					for( $c=3;	$c>=0;  --$c){	if( $casts[ 0] &	($b=  (1<<$c ) ) ){
  printf $fh("case 0x%02X:	/* %2d, %-2d  */	*( ($CAST[ $c]*) ( \$pq	".		") )= $ABCD[0];	$T",		$qs, $q[A],	0	);	last;
						}	}																		$o2=$b;	$b2= ($b<<3);
					for( --$c;		$c>=0;  --$c){	if( $casts[ 0] &	($b=  (1<<$c ) ) ){
  printf $fh(	"	\\\n						*( ($CAST[ $c]*) ( \$pq +%-2d	".	") )= $ABCD[0]>>%2d;$T",	$o2, $b2	);		$o2+=$b;	$b2+= ($b<<3);
						}	}
					eval( $CASE_TERMINATOR[ $ctv +2 ] );
					print $fh( "	break;	\\\n");
				}	}


###########	part 3 of 4:	A disabled;	B enabled	(just B)	###########
  print $fh("\\\n/*	part 3 of 4:	A disabled;	B enabled	(just B)	*/	\\\n"	);
			for( $q[B]=1;		$q[B]<9; ++$q[B] ){ 
				for( $q[A]=1;	$q[A]<8; ++$q[A] ){	#	q( A ): 0		q( B ): 1..8
					  $qs=0x80|	( ( $q[B] -1) <<3)|	($q[A]-1);
  printf $fh("case 0x%02X:	/* %2d, %-2d  */	$T\\\n",												$qs, 0,	$q[B]	);
					} $qs=0x80|	( ( $q[B] -1) <<3)|	0x07;

					$s[A]=	$s[B]=	$q[B];	$anycast=	$casts[0]= fitcast( $q[B], $s[B] +$overrunBytes );

 
					for( $c=3;	$c>=0;  --$c){	if( $casts[ 0] &	($b=  (1<<$c ) ) ){
  printf $fh("case 0x%02X:	/* %2d, %-2d  */$T".		"	*( ($CAST[ $c]*) ( \$pq	".		") )= $ABCD[1];	",	$qs, 0, $q[B]	);	last;
						}	}																											$o2=$b;	$b2= ($b<<3);
					for( --$c;		$c>=0;  --$c){	if( $casts[ 0] &	($b=  (1<<$c ) ) ){
  printf $fh("	\\\n					$T".  			"	*( ($CAST[ $c]*) ( \$pq +%-2d	".	") )= $ABCD[1]>>%2d;",	$o2, $b2 );		$o2+=$b;	$b2+= ($b<<3);
						}	}
					eval( $CASE_TERMINATOR[ $ctv +2 ] );
					print $fh( "	break;	\\\n");
					}


###########	part 4 of 4:	A enabled;	B enabled	(both)	###########
  print $fh("\\\n/*	part 4 of 4:	A enabled;	B enabled	(both)	*/	\\\n"	);
			for( $q[B]=1;		$q[B]<9; ++$q[B] ){ 
				for( $q[A]=1;	$q[A]<9; ++$q[A] ){	#	q( A ): 1..8	q( B ): 1..8
					$qs=0xC0|	( ( $q[B] -1) <<3)|	($q[A]-1);

							$s[B]=	$q[B];	$anycast=0;
					$s[A]=	$s[B]+	$q[A];	$anycast |=	$casts[$_]= fitcast( $q[$_], $s[$_] +$overrunBytes )	foreach A..B;
					
					

					for( $c=3;	$c>=0;  --$c){	if( $casts[ 0] & ($b=  (1<<$c ) ) ){
  printf $fh("case 0x%02X:	/* %2d, %-2d  */	*( ($CAST[ $c]*) ( \$pq	".		") )= $ABCD[0];	",	$qs, $q[A], $q[B] );		last;
						}	}																		$o2=$b;	$b2= ($b<<3);
					for( --$c;		$c>=0;  --$c){	if( $casts[ 0] & ($b=  (1<<$c ) ) ){
  printf $fh(	"$T	\\\n						*( ($CAST[ $c]*) ( \$pq +%-2d	".	") )= $ABCD[0]>>%2d;",	$o2, $b2 );			$o2+=$b; $b2+= ($b<<3);
						}	}
					$o=$q[A];

					foreach my $i( 1){
						$o2=$o;
						for($c=3;	$c>=0;  --$c){	if( $casts[ $i] & ($b=  (1<<$c ) ) ){
  printf $fh(										"	*( ($CAST[ $c]*) ( \$pq +%-2d	".	") )= $ABCD[$i];	",	$o2	);	last;
							}	}																	$o2=$o+$b;	$b2= ($b<<3);
						for(--$c;	$c>=0;  --$c){	if( $casts[ $i] & ($b=  (1<<$c ) ) ){
  printf $fh("	\\\n					$T".  			"	*( ($CAST[ $c]*) ( \$pq +%-2d	".	") )= $ABCD[$i]>>%2d;",	$o2, $b2 );		$o2+=$b;		$b2+= ($b<<3);
							}	}
						$o+=$q[$i];
						}
					eval( $CASE_TERMINATOR[ $ctv +2 ] );
					print $fh( "	break;	\\\n");
				}	}
  print $fh("\n");
  close( $fh);
} }