use strict;
use warnings;
my @CAST=(	undef,	'ui08',	'ui16',	'ui32',		'ui32',	'ui64',		'ui64',	'ui64',	'ui64'	);	my @AND=(	undef, ";\t\t\t", ";\t\t\t", "& 0x00FFFFFF;  \t", ";\t\t\t", "& 0x000000FFFFFFFFFF;", "& 0x0000FFFFFFFFFFFF;", "& 0x00FFFFFFFFFFFFFF;", ";\t\t\t" );
my @OS=(	0,		0,		0,		-1,			0,		-3,			-2,		-1,		0		);
my @BS=(	";",		";",		";",		">>8;",	";",		">>24;",	">>16;",	">>8;",	";"		);
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
my @CASE_TERMINATOR=( 	'',				'',				'printf $fh( "	\$q =%2d;  ",							$s[A]	);',
						'_inc_p',			'',				'printf $fh( "	\$q =%2d;  ",							$s[A]	);'.
														'if( $s[A] >0 ){	printf $fh( "	\$pq1 =\$pq0 +%3d;	",	$s[A]	);	}'.
														'else{		printf $fh( "	\$pq1 =\$pq0;			",			);	}',
						'_init_p',			'',				'printf $fh( "	\$q =%2d;	",						$s[A]	);',
#	|					|				|				|
#	|					|				|				|
						);
my	($anycast, $qs, $b, $b2, $o, $o2, $c, @casts, @c, @b, @o, @s, @q);



for( my $ctv=0; $ctv< $#CASE_TERMINATOR; $ctv+=3 ){
# foreach my $overrunBytes(0..3){
  open(my $fh, '>',	"qREADrev$CASE_TERMINATOR[$ctv].h");
  printf $fh("#define	qREADrev%s( \$q, \$a, \$b, \$pq0, \$pq1, \$cube %s)	/*	expand [a, b] from the q-data at *pq		*/		\\\n",
		$CASE_TERMINATOR[$ctv		],	# variant's name suffix
		$CASE_TERMINATOR[$ctv	+1	],	# variant's add'l macro arguments
		);

###########	part 1 of 4:	A disabled;	B disabled	(neither)	###########
  print $fh("\\\n/*	part 1 of 4:	A disabled;	B disabled	(neither)	*/	\\\n"	);
			$s[A]=0;
			for( $q[B]=1;		$q[B]< 9; ++$q[B] ){
				for( $q[A]=1;	$q[A]< 9; ++$q[A] ){	#	q( A ): 1..8	q( B ): 0
					$qs=		( ( $q[B] -1) <<3)|	($q[A]-1);
  printf $fh("case 0x%02X:	/* %2d, %-2d  */	$ABCD[0]= %d;".								"	$T	$ABCD[1]= %d;$T",										$qs, 0, 0,				$q[A] -1,					$q[B] -1	);

					eval( $CASE_TERMINATOR[ $ctv +2 ] );
					print $fh( "	break;	\\\n");
				}	}

###########	part 2 of 4:	A enabled;	B disabled	(just A)	###########
  printf $fh("\\\n/*	part 2 of 4:	A enabled;	B disabled	(just A)	*/	\\\n"	);
			for( $q[B]=1;		$q[B]< 9; ++$q[B] ){
				for( $q[A]=1;	$q[A]< 9; ++$q[A] ){	#	q( A ): 1..8	q( B ): 0
					$qs=0x40|	( ( $q[B] -1) <<3)|	($q[A]-1);
					$s[A]=			$q[A];
					$o[A]=	$OS[	$q[A] ] -$s[A];
if(		$o[A] ==0){
  printf $fh("case 0x%02X:	/* %2d, %-2d  */	$ABCD[0]= *( ($CAST[ $q[A]]*) \$pq0		)".	"%-18s	\t	$ABCD[1]= %d;$T",										$qs, $q[A], 0,			$BS[$q[A] ],				$q[B] -1	);
}else{
  printf $fh("case 0x%02X:	/* %2d, %-2d  */	$ABCD[0]= *( ($CAST[ $q[A]]*) (\$pq0 %+d )\t)".	"%-18s	\t	$ABCD[1]= %d;$T",										$qs, $q[A], 0,	$o[A],	$BS[$q[A] ],				$q[B] -1	);
	}

					eval( $CASE_TERMINATOR[ $ctv +2 ] );
					print $fh( "	break;	\\\n");
				}	}


###########	part 3 of 4:	A disabled;	B enabled	(just B)	###########
  print $fh("\\\n/*	part 3 of 4:	A disabled;	B enabled	(just B)	*/	\\\n"	);
			for( $q[B]=1;		$q[B]<9; ++$q[B] ){ 
				for( $q[A]=1;	$q[A]<9; ++$q[A] ){	#	q( A ): 0		q( B ): 1..8
					  $qs=0x80|	( ( $q[B] -1) <<3)|	($q[A]-1);

					$s[A]=	$s[B]=	$q[B];
					$o[B]=	$OS[	$q[B] ] -$s[B];

if(		$o[B ]==0){
  printf $fh("case 0x%02X:	/* %2d, %-2d  */	$ABCD[0]= %d;".								"	$T	$ABCD[1]= *( ($CAST[ $q[B]]*) \$pq0		)".	"%-18s	",	$qs, 0, $q[B],	 			$q[A]-1,				$BS[$q[B] ]	);
}else{
  printf $fh("case 0x%02X:	/* %2d, %-2d  */	$ABCD[0]= %d;".								"	$T	$ABCD[1]= *( ($CAST[ $q[B]]*) (\$pq0 %+2d)\t)".	"%-18s	",	$qs, 0, $q[B],	 			$q[A]-1,		$o[B],	$BS[$q[B] ]	);
	}
					eval( $CASE_TERMINATOR[ $ctv +2 ] );
					print $fh( "	break;	\\\n");
				}	}


###########	part 4 of 4:	A enabled;	B enabled	(both)	###########
  print $fh("\\\n/*	part 4 of 4:	A enabled;	B enabled	(both)	*/	\\\n"	);
			for( $q[B]=1;		$q[B]<9; ++$q[B] ){ 
				for( $q[A]=1;	$q[A]<9; ++$q[A] ){	#	q( A ): 1..8	q( B ): 1..8

							$s[B]=			$q[B];
							$o[B]=	$OS[	$q[B] ] -$s[B];
					$s[A]=	$s[B]+	$q[A];
					$o[A]=	$OS[	$q[A] ] -$s[A];
					
					$qs=0xC0|	( ( $q[B] -1) <<3)|	($q[A]-1);
if(		$o[A ]==0){
  if(		$o[B ]==0){
    printf $fh("case 0x%02X:	/* %2d, %-2d  */	$ABCD[0]= *( ($CAST[ $q[A]]*) \$pq0		)".	"%-18s	\t	$ABCD[1]= *( ($CAST[ $q[B]]*) \$pq0		)".	"%-18s	",	$qs, $q[A], $q[B],			$BS[$q[A] ],			$BS[$q[B] ]	);
  }else{
    printf $fh("case 0x%02X:	/* %2d, %-2d  */	$ABCD[0]= *( ($CAST[ $q[A]]*) \$pq0		)".	"%-18s	\t	$ABCD[1]= *( ($CAST[ $q[B]]*) (\$pq0 %+2d)\t)".	"%-18s	",	$qs, $q[A], $q[B],			$BS[$q[A] ],	$o[B],	$BS[$q[B] ]	);
  }
}elsif(	$o[B ]==0){
    printf $fh("case 0x%02X:	/* %2d, %-2d  */	$ABCD[0]= *( ($CAST[ $q[A]]*) (\$pq0 %+2d)\t)".	"%-18s	\t	$ABCD[1]= *( ($CAST[ $q[B]]*) \$pq0		)".	"%-18s	",	$qs, $q[A], $q[B],	$o[A],	$BS[$q[A] ],			$BS[$q[B] ]	);
}else{
    printf $fh("case 0x%02X:	/* %2d, %-2d  */	$ABCD[0]= *( ($CAST[ $q[A]]*) (\$pq0 %+2d)\t)".	"%-18s	\t	$ABCD[1]= *( ($CAST[ $q[B]]*) (\$pq0 %+2d)\t)".	"%-18s	",	$qs, $q[A], $q[B],	$o[A],	$BS[$q[A] ],	$o[B],	$BS[$q[B] ]	);
	}
					eval( $CASE_TERMINATOR[ $ctv +2 ] );
					print $fh( "	break;	\\\n");
				}	}
  print $fh("\n");
  close( $fh);
}