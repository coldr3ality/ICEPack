use strict;
use warnings;
my @CAST=(	undef,	'ui08',	'ui16',	'ui32',		'ui32',	'ui64',		'ui64',	'ui64',	'ui64'	);	my @AND=(	undef, ";\t\t\t", ";\t\t\t", "& 0x00FFFFFF;  \t", ";\t\t\t", "& 0x000000FFFFFFFFFF;", "& 0x0000FFFFFFFFFFFF;", "& 0x00FFFFFFFFFFFFFF;", ";\t\t\t" );
my @OS=(	0,		0,		0,		-1,			0,		-3,			-2,		-1,		0		);
my @BS=(	"    \t",	"    \t",	"    \t",	">>8",		"    \t",	">>24 ",		">>16 ",	">>8 ",	"    \t"	);
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
						'_inc_p',			'',				'if( $s[A] >0 ){	printf $fh( "	\$pq +=%3d;	",			$s[A]	);	}'.
														'else{		printf $fh( "				",					);	}',
						'_init_p',			'',				'if( $s[A] >0 ){	printf $fh( "	\$pq =\$cube +%3d;	",	$s[A]+16	);	}'.
														'else{		printf $fh( "	\$pq =\$cube+16;		",			);	}',
#	|					|				|				|
#	|					|				|				|
						);
my	($anycast, $qs, $qs_, $b, $b2, $o, $o2, $c, $s, $s_, @casts, @c, @b, @o, @s, @q, @q_);
my $mtime = (stat($0))[9];
my $readable_date = scalar localtime($mtime);


for( my $ctv=0; $ctv< $#CASE_TERMINATOR; $ctv+=3 ){
# foreach my $overrunBytes(0..3){
  open(my $fh, '>',	"qHEXLEN$CASE_TERMINATOR[$ctv].h");
  printf $fh(
	"/*	This file was programmatically generated.\n\t	script:\t\t$0\n\t	last modified:\t$readable_date	*/\n\n".
	"#define	qHEXLEN%s( \$pq, \$s %s)	/*	get the combined width of [a, b] as printed in hex 	*/		\\\n",
		$CASE_TERMINATOR[$ctv		],	# variant's name suffix
		$CASE_TERMINATOR[$ctv	+1	],	# variant's add'l macro arguments
		);

###########	part 1 of 4:	A disabled;	B disabled	(neither)	###########
  print $fh("\\\n/*	part 1 of 4:	A disabled;	B disabled	(neither)	*/	\\\n",
#	"case 0x00:	/*  0, 0  */	\$s= 5;				$T$T	\t\t\\\n"
					);
			my $s=5;	$q[A]=1;
			$qs=0;
			$s[A]=0;
			$q[B]=$q_[B]=1;
	#		for( $q_[B]=1;		$q_[B]< 9; ++$q_[B] ){
				for( $q_[A]=2;	$q_[A]< 9; ++$q_[A] ){	#	q( A ): 1..8	q( B ): 0
					$qs_=0x00|	( ( $q_[B] -1) <<3)|	($q_[A]-1);	# lookahead
					$s_	=$q_[A]==$q_[B]? 5: 9;
  if( $s_==5||$s==5){	printf $fh(
	"case 0x%02X:	/* %2d, %-2d  */	\$s= %2d;\t	$T$T	\t\t\t",		$qs, $q[A], $q[B], 	$s	);
					eval( $CASE_TERMINATOR[ $ctv +2 ] );
					print $fh( "	break;	\\\n");
  }else{			 	printf $fh(
	"case 0x%02X:	/* %2d, %-2d  */	/* ... */		$T$T\t	\t\t\t\\\n",	$qs, $q[A], $q[B]		);
	}
					$s= $s_;
					$qs=$qs_;
					$q[A]=$q_[A];
					}

			for( $q_[B]=2;		$q_[B]< 9; ++$q_[B] ){
				for( $q_[A]=1;	$q_[A]< 9; ++$q_[A] ){	#	q( A ): 1..8	q( B ): 0
					$qs_=0x00|	( ( $q_[B] -1) <<3)|	($q_[A]-1);
					$s_	=$q_[A]==$q_[B]? 5: 9;
  if( $s_==5||$s==5){	printf $fh(
	"case 0x%02X:	/* %2d, %-2d  */	\$s= %2d;\t	$T$T	\t\t\t",		$qs, $q[A], $q[B], 	$s	);
					eval( $CASE_TERMINATOR[ $ctv +2 ] );
					print $fh( "	break;	\\\n");
  }else{			 	printf $fh(
	"case 0x%02X:	/* %2d, %-2d  */	/* ... */		$T$T\t	\t\t\t\\\n",	$qs, $q[A], $q[B]		);
	}
					$s= $s_;
					$qs=$qs_;
					$q[A]=$q_[A];
					$q[B]=$q_[B];
					}
				}
printf $fh(
	"case 0x%02X:	/* %2d, %-2d  */	\$s= %2d;\t	$T$T	\t\t\t",		$qs, $q[A], $q[B], 	$s	);
					eval( $CASE_TERMINATOR[ $ctv +2 ] );
					print $fh( "	break;	\\\n");

###########	part 2 of 4:	A enabled;	B disabled	(just A)	###########
  printf $fh("\\\n/*	part 2 of 4:	A enabled;	B disabled	(just A)	*/	\\\n"	);
			for( $q[B]=1;		$q[B]< 9; ++$q[B] ){
				for( $q[A]=1;	$q[A]< 9; ++$q[A] ){	#	q( A ): 1..8	q( B ): 0
					$qs=0x40|	( ( $q[B] -1) <<3)|	($q[A]-1);
					$s[A]=			$q[A];
					$o[A]=	$OS[	$q[A] ];
if( $OS[$q[A] ] ==0){
  printf $fh("case 0x%02X:	/* %2d, %-2d  */	\$s= 23-(__builtin_clzll( *( ($CAST[ $q[A]]*) \$pq		)"."%-5s) >>2);\t	$T	",										$qs, $q[A], 0,			$BS[$q[A] ]				);
}else{
  printf $fh("case 0x%02X:	/* %2d, %-2d  */	\$s= 23-(__builtin_clzll( *( ($CAST[ $q[A]]*) (\$pq %+d )\t)"."%-5s) >>2);\t	$T	",										$qs, $q[A], 0,	$o[A],	$BS[$q[A] ]				);
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
					$o[B]=	$OS[	$q[B] ];

if( $o[B ]==0){
  printf $fh("case 0x%02X:	/* %2d, %-2d  */		".								"	$T	\$s= 23	-	(__builtin_clzll( *( ($CAST[ $q[B]]*) \$pq		)".	"%-5s) >>2);	",	$qs, $q[B],	 			$q[A]-1,				$BS[$q[B] ]	);
}else{
  printf $fh("case 0x%02X:	/* %2d, %-2d  */		".								"	$T	\$s= 23	-	(__builtin_clzll( *( ($CAST[ $q[B]]*) (\$pq %+d )\t)".	"%-5s) >>2);	",	$qs, $q[B],	 			$q[A]-1,		$o[B],	$BS[$q[B] ]	);
	}
					eval( $CASE_TERMINATOR[ $ctv +2 ] );
					print $fh( "	break;	\\\n");
				}	}


###########	part 4 of 4:	A enabled;	B enabled	(both)	###########
  print $fh("\\\n/*	part 4 of 4:	A enabled;	B enabled	(both)	*/	\\\n"	);
			for( $q[B]=1;		$q[B]<9; ++$q[B] ){ 
				for( $q[A]=1;	$q[A]<9; ++$q[A] ){	#	q( A ): 1..8	q( B ): 1..8

							$s[B]=			$q[B];
					$s[A]=	$s[B]+	$q[A];
							$o[A]=	$OS[	$q[A] ];
					$o[B]=	$q[A]+	$OS[	$q[B] ];
					
					$qs=0xC0|	( ( $q[B] -1) <<3)|	($q[A]-1);
if(		$o[A ]==0){
  if(		$o[B ]==0){
    printf $fh("case 0x%02X:	/* %2d, %-2d  */	\$s= 39-(__builtin_clzll( *( ($CAST[ $q[A]]*) \$pq		)".	"%-5s) >>2)	-	(__builtin_clz( *( ($CAST[ $q[B]]*) \$pq		)".	"%-5s) >>2);	",	$qs, $q[A], $q[B],			$BS[$q[A] ],			$BS[$q[B] ]	);
  }else{
    printf $fh("case 0x%02X:	/* %2d, %-2d  */	\$s= 39-(__builtin_clzll( *( ($CAST[ $q[A]]*) \$pq		)".	"%-5s) >>2)	-	(__builtin_clz( *( ($CAST[ $q[B]]*) (\$pq %+d )\t)".	"%-5s) >>2);	",	$qs, $q[A], $q[B],			$BS[$q[A] ],	$o[B],	$BS[$q[B] ]	);
  }
}elsif(	$o[B ]==0){
    printf $fh("case 0x%02X:	/* %2d, %-2d  */	\$s= 39-(__builtin_clzll( *( ($CAST[ $q[A]]*) (\$pq %+d )\t)".	"%-5s) >>2)	-	(__builtin_clz( *( ($CAST[ $q[B]]*) \$pq		)".	"%-5s) >>2);	",	$qs, $q[A], $q[B],	$o[A],	$BS[$q[A] ],			$BS[$q[B] ]	);
}else{
    printf $fh("case 0x%02X:	/* %2d, %-2d  */	\$s= 39-(__builtin_clzll( *( ($CAST[ $q[A]]*) (\$pq %+d )\t)".	"%-5s) >>2)	-	(__builtin_clz( *( ($CAST[ $q[B]]*) (\$pq %+d )\t)".	"%-5s) >>2);	",	$qs, $q[A], $q[B],	$o[A],	$BS[$q[A] ],	$o[B],	$BS[$q[B] ]	);
	}
					eval( $CASE_TERMINATOR[ $ctv +2 ] );
					print $fh( "	break;	\\\n");
				}	}
  print $fh("\n");
  close( $fh);
}