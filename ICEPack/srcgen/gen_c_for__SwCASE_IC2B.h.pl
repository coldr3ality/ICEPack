use strict;
use warnings;
my @CASTo=( 'ui08', 'ui16', 'ui32', 'ui64' );
my @CAST=(	undef,	'ui08',	'ui16',	'ui32',		'ui32',	'ui64',		'ui64',	'ui64',	'ui64'	);	my @AND=(	undef, ";\t\t\t", ";\t\t\t", "& 0x00FFFFFF;  \t", ";\t\t\t", "& 0x000000FFFFFFFFFF;", "& 0x0000FFFFFFFFFFFF;", "& 0x00FFFFFFFFFFFFFF;", ";\t\t\t" );
my @OS=(	0,		0,		0,		-1,			0,		-3,			-2,		-1,		0		);
my @BS=(	"       \t)-1;",	"       \t)-1;",	"       \t)-1;",	">>8  \t)-1;",	"       \t)-1;",	">>24 \t)-1;",	">>16 \t)-1;",	">>8   \t)-1;",	"       \t)-1;"		);
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
my @CASE_TERMINATOR=(	'',				'',				'',
						);




my	($anycast, $qs, $qs2,	$b, $b2, $o, $o2, $v,	$c, @casts, @c, @b, @o, @s, @q);
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
# foreach my $overrunBytes(0..3){
  open(my $fh, '>',	"SwCASE_IC2B$CASE_TERMINATOR[$ctv].h");
  printf $fh(
	"/*	This file was programmatically generated.\n\t	script:\t\t$0\n\t	last modified:\t$readable_date	*/\n\n".
	"#define	SwCASE_IC2B%s(		\$pq, \$a, \$b, \$q %s)	/*	expand [a, b] from the q-data at *pq		*/		\\\n",
		$CASE_TERMINATOR[$ctv		],	# variant's name suffix
		$CASE_TERMINATOR[$ctv	+1	],	# variant's add'l macro arguments
		);

###########	part 1 of 4:	A disabled;	B disabled	(neither)	###########
  print $fh("\\\n/*	part 1 of 4:	A disabled;	B disabled	(neither)	*/	\\\n"	);
			$s[A]=0;
			for( $q[B]=1;		$q[B]< 9; ++$q[B] ){
				for( $q[A]=1;	$q[A]< 9; ++$q[A] ){	#	q( A ): 1..8	q( B ): 0
					$qs=		( ( $q[B] -1) <<3)|	($q[A]-1);	$qs2= $q[B]>1	? ( ( $q[B] -2) <<3)|	($q[A]-1)
																	: 				($q[A]-1);
if( $q[B]<2){
  printf $fh("case 0x%02X:	/* %2d, %-2d    	\$H = 0x%02X;      \t$ABCD[1]= %d; */$T",									$qs, 0,	0,     	$qs2,			$q[B] -1	);
}else{
  printf $fh("case 0x%02X:	/* %2d, %-2d  */	\$H = 0x%02X; /*   \t$ABCD[1]= %d; */$T",									$qs, 0,	0,     	$qs2,			$q[B] -1	);
	}

					eval( $CASE_TERMINATOR[ $ctv +2 ] );
					print $fh( "	break;	\\\n");
				}	}

###########	part 2 of 4:	A enabled;	B disabled	(just A)	###########
  printf $fh("\\\n/*	part 2 of 4:	A enabled;	B disabled	(just A)	*/	\\\n"	);
			for( $q[B]=1;		$q[B]< 9; ++$q[B] ){
				for( $q[A]=1;	$q[A]< 9; ++$q[A] ){	#	q( A ): 1..8	q( B ): 0
					$qs=0x40|	( ( $q[B] -1) <<3)|	($q[A]-1);		$qs2= $q[B]>1	? 0x40|	( ( $q[B] -2) <<3)|	($q[A]-1)
																		: 0x40|					($q[A]-1);
					$s[A]=			$q[A];
					$o[A]=	$OS[	$q[A] ];
if( $q[B]<2){
  printf $fh("case 0x%02X:	/* %2d, %-2d    	\$H = 0x%02X;      \t$ABCD[1]= %d; */$T",									$qs, $q[A], 0,   	$qs2,			$q[B] -1	);
}else{
  printf $fh("case 0x%02X:	/* %2d, %-2d  */	\$H = 0x%02X; /*   \t$ABCD[1]= %d; */$T",									$qs, $q[A], 0,   	$qs2,			$q[B] -1	);
	}

					eval( $CASE_TERMINATOR[ $ctv +2 ] );
					print $fh( "	break;	\\\n");
				}	}


###########	part 3 of 4:	A disabled;	B enabled	(just B)	###########
  print $fh("\\\n/*	part 3 of 4:	A disabled;	B enabled	(just B)	*/	\\\n"	);
				$q[B]=1;
				for( $q[A]=1;	$q[A]<9; ++$q[A] ){	#	q( A ): 0		q( B ): 1..8
					  $qs=0x80|	( ( $q[B] -1) <<3)|	($q[A]-1);		$qs2= $q[B]>1	? 		( ( $q[B] -2) <<3)|	($q[A]-1)
																		: 		0x38|			($q[A]-1);
				#	$s[A]=	$s[B]=	$q[B];	$anycast=	$casts[0]= fitcast( $q[B], $s[B] +$overrunBytes );
					$s[A]=	$s[B]=	$q[B];	$anycast=	$casts[0]= fitcast( $q[B], $s[B]);
					$o[B]=	$OS[	$q[B] ];
if( $o[B ]==0){
  printf $fh("case 0x%02X:	/* %2d, %-2d  */  				    	$ABCD[1]=(	*( ($CAST[ $q[B]]*) \$pq		)".		"%-18s	\t\t\\\n",	$qs, 0,	$q[B],					$BS[$q[B] ]	);
}else{
  printf $fh("case 0x%02X:	/* %2d, %-2d  */  				    	$ABCD[1]=(	*( ($CAST[ $q[B]]*) (\$pq %+d )\t)".	"%-18s	\t\t\\\n",	$qs, 0,	$q[B],			$o[B],	$BS[$q[B] ]	);
	}
if( $q[B]<2){			for( $c=3;	$c>=0;  --$c){	if( $casts[ 0] &	($b=  (1<<$c ) ) ){
  printf $fh("\t\t\tif( $ABCD[1]==8)		\$H = 0x%02X;	else{".	"	*( ($CASTo[ $c]*) ( \$pq	".			") )= $ABCD[1];	",		$qs2);	last;
						}	}																											$o2=$b;	$b2= ($b<<3);

}else{				for( $c=3;	$c>=0;  --$c){	if( $casts[ 0] &	($b=  (1<<$c ) ) ){
  printf $fh("	\\\n$T			".							"	*( ($CASTo[ $c]*) ( \$pq	".			") )= $ABCD[1];	",		$qs2);	last;
						}	}																											$o2=$b;	$b2= ($b<<3);
	}
					for( --$c;		$c>=0;  --$c){	if( $casts[ 0] &	($b=  (1<<$c ) ) ){
  printf $fh("\t\t\t\t\\\n$T			".						"	*( ($CASTo[ $c]*) ( \$pq +%-2d	".	") )= $ABCD[1]>>%2d;",	$o2, $b2 );			$o2+=$b;	$b2+= ($b<<3);
						}	}
  printf $fh("}");
	
					eval( $CASE_TERMINATOR[ $ctv +2 ] );
					print $fh( "		break;	\\\n");
					}

			for( $q[B]=2;		$q[B]<9; ++$q[B] ){ 
				for( $q[A]=1;	$q[A]<9; ++$q[A] ){	#	q( A ): 0		q( B ): 1..8
					  $qs=0x80|	( ( $q[B] -1) <<3)|	($q[A]-1);

					$s[A]=	$s[B]=	$q[B];	$anycast=	$casts[0]= fitcast( $q[B], $s[B]);
					$o[B]=	$OS[	$q[B] ];
if( $o[B ]==0){
  printf $fh("case 0x%02X:	/* %2d, %-2d  */  				    	$ABCD[1]=(	*( ($CAST[ $q[B]]*) \$pq		)".		"%-18s	\t",	$qs, 0,	$q[B],					$BS[$q[B] ]	);
}else{
  printf $fh("case 0x%02X:	/* %2d, %-2d  */  				    	$ABCD[1]=(	*( ($CAST[ $q[B]]*) (\$pq %+d )\t)".	"%-18s	\t",	$qs, 0,	$q[B],			$o[B],	$BS[$q[B] ]	);
	}
					for( $c=3;	$c>=0;  --$c){	if( $casts[ 0] &	($b=  (1<<$c ) ) ){
  printf $fh("	\\\n$T			".							"	*( ($CASTo[ $c]*) ( \$pq	".			") )= $ABCD[1];	"		);	last;
						}	}																											$o2=$b;	$b2= ($b<<3);
					for( --$c;		$c>=0;  --$c){	if( $casts[ 0] &	($b=  (1<<$c ) ) ){
  printf $fh("\t\t\t\t\\\n$T			".						"	*( ($CASTo[ $c]*) ( \$pq +%-2d	".	") )= $ABCD[1]>>%2d;",	$o2, $b2 );			$o2+=$b;	$b2+= ($b<<3);
						}	}

					eval( $CASE_TERMINATOR[ $ctv +2 ] );
					print $fh( "		break;	\\\n");
				}	}


###########	part 4 of 4:	A enabled;	B enabled	(both)	###########
  print $fh("\\\n/*	part 4 of 4:	A enabled;	B enabled	(both)	*/	\\\n"	);
			for( $q[B]=1;		$q[B]<9; ++$q[B] ){ 
				for( $q[A]=1;	$q[A]<9; ++$q[A] ){	#	q( A ): 1..8	q( B ): 1..8

							$s[B]=			$q[B];	$anycast=0;
					$s[A]=	$s[B]+	$q[A];			$anycast |=	$casts[$_]= fitcast( $q[$_], $s[$_] )	foreach A..B;
							$o[A]=	$OS[	$q[A] ];
					$o[B]=	$q[A]+	$OS[	$q[B] ];

					
					$qs=0xC0|	( ( $q[B] -1) <<3)|	($q[A]-1);		$qs2= $q[B]>1	? 0xC0|	( ( $q[B] -2) <<3)|	($q[A]-1)
																		:  0xC0|					($q[A]-1);

if( $o[B ]==0){
  printf $fh("case 0x%02X:	/* %2d, %-2d  */  				    	$ABCD[1]=(	*( ($CAST[ $q[B]]*) \$pq		)".		"%-18s	\t",	$qs, $q[A], $q[B],					$BS[$q[B] ]	);
}else{
  printf $fh("case 0x%02X:	/* %2d, %-2d  */  				    	$ABCD[1]=(	*( ($CAST[ $q[B]]*) (\$pq %+d )\t)".	"%-18s	\t",	$qs, $q[A], $q[B],			$o[B],	$BS[$q[B] ]	);
	}
					for( $c=3;	$c>=0;  --$c){	if( $casts[ 0] &	($b=  (1<<$c ) ) ){
  printf $fh("	\\\n$T			".							"	*( ($CASTo[ $c]*) ( \$pq	".			") )= $ABCD[1];	"		);	last;
						}	}																											$o2=$b;	$b2= ($b<<3);
					for( --$c;		$c>=0;  --$c){	if( $casts[ 0] &	($b=  (1<<$c ) ) ){
  printf $fh("\t\t\t\t\\\n$T			".						"	*( ($CASTo[ $c]*) ( \$pq +%-2d	".	") )= $ABCD[1]>>%2d;",	$o2, $b2 );			$o2+=$b;	$b2+= ($b<<3);
						}	}

					eval( $CASE_TERMINATOR[ $ctv +2 ] );
					print $fh( "	break;	\\\n");
				}	}
  print $fh("\n");
  close( $fh);
}