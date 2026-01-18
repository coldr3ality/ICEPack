# Inversion Cycle Encoding (ICE) v0.4.9 
package ICE;	 use strict; use warnings;	system('cls');  
use Data::Dumper;
use Inline 'C';	#		=> Config => ("BOOT", ";\n init();"); 
	init();
#	test_rack();
#	exit;
#	my $A1=[ 5, 6, 7, 12, 20, 22, 23, 24, 25, 29, 31, 34, 38, 40, 42, 46, 49, 52, 55, 58, 61, 64, 68, 70, 74, 76, 80, 82, 86, 88, 90, 94, 96, 100, 102, 106, 109, 113, 116, 120, 123, 127, 130, 134, 137, 140, 144, 147, 150, 153, 157, 160, 163, 168, 172, 178, 180, 184, 191, 195, 200, 205];	
#	my $A1=[ 0x5, 0x6,	0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 	0xFF, 0x100, 0x101,	0xFFE, 0xFFF,	0x1000,		0xFFFE, 0xFFFF, 0x10000,	0xFFFFFFE, 0xFFFFFFF, 0x10000000	];
#	my $A1=[ 5, 6, 7, 57, 111, 113, 151, 191, 222, 255, 257, 357, 457, 561, 717, 1111, 1113, 1211, 1212 ];
#	my $A1=[ 5, 6, 7, 57, 111, 113, 151, 191, 222, 255, 257, 357, 457, 561, 717, 1111, 1113, 1211, 1212, 1221, 1222, 2222, 4444, 8888, 12222, 14444, 16666	];
#	my $A1=[ 5, 6, 7, 57, 111, 113, 151, 191, 222, 255, 257, 357, 457, 561, 717, 1111, 1113, 1211, 1212, 1221, 1222, 2222, 4444, 8888, 12222,
#			14444, 16666, 212121, 212122, 313131, 313132, 313133, 414144,	101101101,	202202202,	303303303,
#			1111111100, 1111111101, 1111111102, , 1111111103, 1111111104, 1111111105, 1111111106, 1111111107, 1111111108, 1111111109,, 1111111110, 1111111111,
#			1113111130, 1113111131,	1211212110, 1211212111,	1211212112];
  
#	my $A1=[0, 1, 255, 256, 65535, 65536, 16777215, 16777216, 4294967295, 4294967296, 1099511627775, 1099511627776, 281474976710655, 281474976710656 ];
# 	my $A1=[0, 1, 255, 256, 65535, 65536, 16777215, 16777216, 4294967295, 4294967296, 1099511627775, 1099511627776, 281474976710655, 281474976710656, 72057594037927935, 72057594037927936 ];
 	my $A1=[0, 1, 100, 200, 255, 256, 60000, 65535, 65536, 70000, 80000, 900000, 1000000, 16000000, 16777215, 16777216, 200200200, 300300300, 400400400, 4294967295, 4294967296, 5005005005, 6006006006, 10010010010, 10999999999, 11000000000, 11111111111, 222222222222, 1099511627775, 1099511627776, 1099999999999, 1111111111111, 14001400140014, 281400000000000, 281474976710655, 281474976710656, 2814000028140000, 72057000000000000, 72057594037927935, 72057594037927936, 72057599999999999, 880088008800880088, 990099009900990099, 1152921212121212121, 1152921313131313131, 1152921504606846975, 1152921504606846976, 1234567890987654321, 1234567899999999999];
# 	my $A1=[0, 1, 255, 256, 65535, 65536, 16777215, 16777216, 4294967295, 4294967296, 1099511627775, 1099511627776, 281474976710655, 281474976710656, 72057594037927935, 72057594037927936, 18446744073709551615];
#	my $A1=[10, 20, 30, 40, 50, 60, 70, 80];
#	my $A1=[100, 200, 300, 400, 500, 600, 700, 800];

#	my $A1=[123, 234, 456, 567, 678, 789, 911, 1011];

#	my	$A1=[ 717, 1111, 1113, 1211, 1212, 1221, 1222, 2222, 4444, 8888, 12222, 14444, 16666, 18888, 20000, 22222, 24444, 28888, 30000, 31111, 33333	];
#		5	6		26	27	...						32		255..257				4094..4096				65534 .. 65536			268435454..268435456



#	while(	$_=<> ){	#	alloc() test
#					$x= $ICE->alloc();		print("\r #$x<--	\n",					 @{ $ICE->toText() } );
#					}
sub replay1{
	my $ICE= fromRvAV( [	1, 2, 12, 13, 21, 43, 57, 				undef, 
						112, 119, 143, 154, 				undef,
						162, 166, 179, 183, 195,				undef,
						197, 208, 211, 221, 222,				undef,
						234, 247, 249, 276, 289, 294, 311, 313,	undef,
						326,								undef,
						328,								undef	] );
	print( @{	$ICE->toText() } );
	my @keyBatch=( 14, 78, 88, 113, 121, 188, 255, 327 );
	print("\r	batch 0: -->", join(', ', @keyBatch), "<--\n\n");
					$ICE->set( \@keyBatch );
	print(		@{	$ICE->toText() } );
	exit;
	}
sub replay2{
	my	$ICE=fromRvAV( [
		1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 18, 21, 							undef,
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
		327,									undef	] );
	
	print( @{	$ICE->toText() } );
	my @keyBatch=( 29, 149, 186, 203, 238, 265, 302, 326);
	print("\r	batch 0: -->", join(', ', @keyBatch), "<--\n\n");
					$ICE->set( \@keyBatch );
	print(		@{	$ICE->toText() } );
	exit;
	}
#	replay2();
	
sub	divine{
	my $ICE=fromRvAV([ 212 ]);
	print( @{	$ICE->toText() } );
	exit;
	}
#	divine();
#	replay1();

sub test_set_prompt{
	my ($x, @A1, @D1);
#	my $ICE=fromRvAV( $A1 );
	my $ICE=fromRvAV( [1, 2, 12, 21, 112, 211, 221] );	#	bless( [], 'ICE' );
#	my $hv=$ICE->toHV();
#	my @keys= sort keys %$hv;
#	my $N=0;
#	foreach(@keys){	print("$N:	", unpack( "Q", $_), "\n");	++$N;	}
	
	print("\n\n\n", @{ $ICE->toText() }, "\n>");
	while(	$_=<> ){
		@D1=$_=~ /\d+/g;
		@A1= map{ int($_) } @D1;
		print("\nICE::set()==",	$ICE->set(	\@A1	),
			"\n\n\n\n\n",	@{	$ICE->toText(			) } , "\n>");
	}	}
#test_set_prompt();
test_set_loop_rand( 0, 333, 100 );
print( 'CAT'x1000);

sub test_set_loop_rand($$$){				# test &set and &unset by repeatedly filling, then emptying the namespace using random noise.
	my($min,$max,$iterations)=@_;
	my	($R,			$pbst,						$batch,	$hit, $miss, $r, $R_, $d, $ICE, $x, $i, $I, %chk,%chk_, @keyBatch, @keyBatchScreen, @keyBulk )=
		($max-$min,	bless(\pack('nnn',0,0,0),'PBAR'),	0		);
	$R_=$R>>1;
	my $nSamps=8;	#int(log($R))**2;
	
	print("\n_relay_race: noise test ICE::set and ICE::unset.\nNS: $min..$max @ $nSamps/pass \n");
#	$ICE=fromRvAV( [1, 2, 12, 21, 112, 211, 221] );	#	bless( [], 'ICE' );
#	print(		@{	$ICE->toText() } );

	TEST:foreach my $i(1..$iterations){
#		die("initial ICE block count is not 2 (".scalar(@$ICE).")") if 2!=@$ICE;
		%chk=();
		#inclusion test
		$ICE=fromRvAV( [1, 2, 12, 21, 112, 211, 221] );	#	bless( [], 'ICE' );
		print( @{	$ICE->toText() } );
		$r=0;
		while($r<$R){
			@keyBatch=();	++$batch;
			for( my $t=$nSamps;  $t >0;  --$t ){
				$x=$min+int(rand($R));
				if(	insortIV( \@keyBatch,	$x )	){	++$t;	}
			#	else	insortIV( \@keyBulk,	$x );
				}
			print("\r	batch $batch: -->", join(', ', @keyBatch), "<--\n\n");
			$r += $nSamps -	$ICE->set( \@keyBatch );

			print(		@{	$ICE->toText() } );
		#	$pbst->pbar($r/$R);
			@keyBatchScreen = @keyBatch;
			$hit = $ICE->screenKeys( \@keyBatchScreen );
			
			if( 0< ( $miss = scalar( @keyBatchScreen ) ) ){	print("\r$miss unknown entries: \n", join(', ', @keyBatchScreen ) );	exit; }

			if( $#$ICE==0 && length( $$ICE[0] )==18){		print("\n completed ($i) test[s]\n\n\n");	next TEST;	}
			}
	#	#exclusion test
	#	while($r>0){
	#		@arg=();
	#		for(my $t=$nSamps;$t>0;--$t){
	#			push(@arg,$x=$min+int(rand($R)));
	#			delete $chk{$x};
	#			}
	#		
	#		@arg=sort{ $a<=>$b } @arg;
	#		$r-=$nSamps	-$ICE->unset( \@arg );
#
#			$pbst->pbar($r/$R);
#			%chk_=%chk;
#			$map =$ICE->unmapHV( \%chk_ );
#			print("\n$i unknown entries.\n")		if 0<($i=scalar @$map);
#			print("\n$I missing entries.\n")		if 0<($I=scalar keys %chk_);
#			next TEST if $i || $I;
#			}
		
		}
	print("\r($iterations) PASSES\n\n");
	}
1;
__DATA__
__C__
#include	<stdio.h>
#include	"SwCASE.h"
#include	"qCAST.h"
#include	"hiCASTt0.h"
#include	"hiCASTt1.h"
#include	"hiCASTt2.h"
#include	"hiCASTt3.h"
#include	"hiCASTt0inc.h"
#include	"hiCASTt1inc.h"
#include	"hiCASTt2inc.h"
#include	"hiCASTt3inc.h"
#include	"ICE.h"
#include	"ICE.c"
void init(){	printf("\ninit()=====================================\n"); 
//	for( x=0; x<256; ++x ){	printf("\n%d:	%c\n", x, x);	}
	hvICE	= gv_stashpv("ICE", 0);
	avRack	= newAV();

	A[	255 ]=255;
	B[	255 ]=255;
	O[	255 ]=16;
	_O[	255 ]= 0;
	Q[	255 ]= 0;
	*( (ui64*) Hx )	= 0;
	respliceArc[	0 ]=0;
	respliceIns[	0 ]=0;
	respliceCut[	0 ]=0;
	respliceSrc[ 	0 ]=0;
	respliceDst[	0 ]=0;
//cube =SvPVbyte(	sv, 	CS );	Kx8=	*( (ui64*) cube );	zc = zIndexOf( Kx8);

/*	(6) distinct cases for racking:
		| Condition:												| Effect:
	#1.	| rel_c is neutral.											| Overwrite cycles mc0..mcZ in cube iC.  No change in cycle count.
	#2.	| rel_c is positive;	(2+) new cubes must be inserted to make space.	| Fragment cube iC, and distribute intermediate cubes in-between.
	#3.	| rel_c is positive;	(1) new cube must be inserted to make space.	| Fragment cube iC in a similar way as in the _alloc() function.
	#4.	| rel_c is negative;	Cycle count drops to zero, extinguishing cube iC.	| Delete cube iC.
	#5.	| rel_c is negative;	Cycle count decreases, but still non-zero.		| Right-shift trailing cycles & overwrite medial cycles if any.
	#6.	| rel_c is positive.	cube iC has enough vacant capacity.			| Left-shift trailing cycles, insert new & overwrite medials.

	*/
	}

/*	hindsight	lichtenstein	bartleby	  cubby	nymph	crew helm mission brink  disaster weld kudos
	wherewithall	alabaster	green tea	shelf
	coffee  baseball	unitarian	peace	feeling	icing	fruitcake	jingles  strike	here	heal caster oil	halibut curly hair		*/
/*	hold true the focus	light	sand ice sky  jewel	slate	food	newcomer	toluene  darkness clear locket list 
	*/
/*	stormcrow	hellbringer	rifleman	summoner	MADDOG	timberwolf		marauder	direwolf	jenner	kit fox
	fwe
	gargoyle		po diddy		hep cat	claptrap		rib bone		rabbleshnauzer	sneekypete	sup pup	jenzer	kaboodle

	hi		pancakes	fruitloops 	parfaits	eggies		rye toast			string cheese		heavy cream	butter	elderberries
	hola		waffles	turkey		souflette	<3			apple cinnamon	peach			shallots	butter oh
	blueberries	cantelope	pear	cupcakes			grits		turkey	hotsauce			onions	mustard	horseradish
	
	snausages	pineapple	juice		avocado	swiss cheese	beer	eggnog	beef jerky	bree	ghee	peanut butter
	flax		ghost pepper	pumpkin pie spice	matcha	moringa	himalayan	almonds <3	walnuts	pistache	pican
	quinoa	olive oil	black pepper		cumin	

	quartz	sapphire		ruby	diamond	 emerald pearl	obsidian	flint	granite	magnetite	jasper ice
	diamond	amethyst	indigo	anthrocite	chrysophrase	jade		aggot	mica	

	brave	ook	nook	zook	MOST_HOLY_GRAIL	CHIM_CHIMN_E	elle G choir	hi me cat	
	iOvnow	sorcear	planet bell47	coma84				joe

	creative	dork		cog	jerk	juice	oopz	dawg	craven	schnell	cat	dog	duck stuff  niche
	great jorb derf	vanilla	gdansk	GORSH	why do I hunger?
	push	zerk		na'an	goat milk		molasses		beans	cabbage	heirloom tomatoes
	do it k	very	good	man		tree			done	slice		pie		hmm	potatoes?
	chocolate	whip cream	sundae no	mayonaisse	fat	HODL	mincemeat	yams	pineapples
	do exist		perch		tears		madafaka souflette	snow
	doe			mustard		peppercorn	pecans	mango	pears	crab		macadamias	spinach cat

	zuke		cucu		spaghetti squash		mozarella	ricotta	parmessian	grey pupon	tiger sauce
	jamaica hellfire	pisqueya

	graft	instigate	craft	manage	summon	drink	traverse	straffe	grow	stew
	jello	pudding	tapioca	banana creme	chestnuts	brazil nuts	blue corn chips	salsa
	nein teimz [ten]
 
	so fat
	mustard? yeah
fe	how 'bout amaranth? cool
	teff spelt	kamut	
 	I am not hungry	not really.	no.  yeah I am always hungry, but not really.
	I will eat when my body needs to.
	I love the idea of food
c	I feel so coolbuf
	I know, I think I feel obsessed with eating
	cat catcat cat  cat  cat cat cat 	cat cat  cat cat cat cat  cat  catting
	cat  cat cat	cat  cat cat  cat cat cat  cat cat cat  cat cat catcat cat cat cat cat cat cat catcat  cat cat cat cat cat cat cat cat cat cat 
	cat cat  cat  	yellow cat	blue cat 
	danish		orance cat	oopcat boopcat can cat  cat cat cat  cat cat  cat	kate
	macaroons	figs pomegranates		caaaaaat
	cat 	car cat 	cat 	cat	cat	cat	cat	cat	cat	coolcat	cat	cat	cat cat	catfish	cattle	cats, the musical
	fecat cat cat 	cat	cat 	cat	cat 	cat	cat	coolcat		cat	cat	cat cat 	catbird	cat tail	acds 
wgcatcatcatccsdcds crwcsdcs fscdscdcdavdvre	wfe fccdesv
	ccdsccdescdecesscvewfwetcfcdscsdavcst cat cacaf cwcrwcrvw csd	cat		1	fce
	*/
#define SvINIT( $AV, $SV )		AvINIT1(		$AV );				\
						/*	SvREFCNT_inc(			$SV);	*/\
							*( AvARRAY(	$AV)	) =	$SV;

#define SvINS( $AV, $SV, $I )		AvINSERT1(	$AV,	$I );			\
						/*	SvREFCNT_inc(			$SV);	*/\
							*( AvARRAY(	$AV) +	$I )=	$SV;

SV*	toText(		SV*	rvICE	){
					avOut = newAV();
					rvOut = newRV_inc( (SV*) avOut );
	svtype			svt = SvTYPE( rvICE );
	STRLEN			L;


	if( ! SvROK( rvICE) ){	L =sprintf( aString, "\r!       ICE::toText( <%s> ): arg[0] is not a reference.\n\t",	svtype_names[ svt ] );
						av_push( avOut, newSVpvn( aString, L ) );	return rvOut; }
	avICE	= (AV*) SvRV(	rvICE	);	/*	dereference argument									*/
	svt= SvTYPE(avICE);				/*	check type of supposed perl object at dereferenced address	*/
	if( svt != SVt_PVAV ){	L =sprintf( aString, "\r!       ICE::toText( <%s> ): arg[0] is not an array ref.\n\t",	svtype_names[ svt ] );
						av_push( avOut, newSVpvn( aString, L ) );	return rvOut; }

	_toText();
 
	return rvOut;
	}
SV*	toHV(		SV*	rvICE	){

	svtype	rt0,		t0 = SvTYPE( rvICE );
	static const char	*	arg0_err	= "\r!       ICE::unmapHV( <%s> ): arg[1] is not an arrayref.\n\t";

	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg0_err,  svtype_names[		t0 ]	);  return &PL_sv_no; }
	avICE	= (AV*) SvRV(    	rvICE );	rt0 = SvTYPE( avICE );
	if( rt0 != SVt_PVAV ){				printf( arg0_err,  svtype_names_ref[	rt0 ]	);  return &PL_sv_no; }

	_toHV();
	rvOut = newRV_inc( (SV*) hvOut );
	return rvOut;
	}
SV*	upsortQ(		SV* rvArg,	SV*	svQx	){
	const char	*	arg0_err	= "\r!       ICE::upsortQ( <%s>, <%s> ): arg[0] is not an arrayref.\n\t",
				*	arg1_err	= "\r!       ICE::upsortQ( <%s>, <%s> ): arg[1] is not a packed quad.\n\t";
	svtype			t0 = SvTYPE( rvArg ),
					t1 = SvTYPE( svX	);
	if( t0 != SVt_RV || !SvROK(	rvArg	) ){	printf( arg0_err,  svtype_names[ t0 ],		svtype_names[ 0 ] );		return &PL_sv_no; }
	if( t1 != SVt_PV || !SvOK(	svQx	) ){	printf( arg1_err,  svtype_names[ t0 ],		svtype_names[ t1 ] );		return &PL_sv_no; }
	avArg	= (AV*) SvRV(    	rvArg );	t0 = SvTYPE( avArg );
	if( t0 != SVt_PVAV ){					printf( arg0_err,  svtype_names_ref[ t0 ],  	svtype_names[ t1 ] );		return &PL_sv_no; }

	SV			*	svQ,
				**	src,
				**	dst,
				**	sv0	= AvARRAY( avArg );
	ui08			*	pq;
	const ui08	*	pqx= SvPVbyte_nolen( svQx );
	const long long	x	= *( (ui64*) pqx );

	SSize_t			displacement;
	long long			lb	= 0,
					ub	= AvFILLp( avArg )+1,	i= ub >>1;		if( ub==0	){		svQ=newSVpvn( pqx, 8 );  SvINIT( avArg, svQ );	return &PL_sv_no;	}

						pq = SvPVbyte_nolen( svQ=	*( sv0 +i ) );
	while(	x !=	*( (ui64*)	pq )	){
		if(	x >	*( (ui64*)	pq )	){	lb=i;			i=( i +ub	)>>1;	if( i==lb	){ ++i;	svQ=newSVpvn( pqx, 8 );  SvINS( avArg, svQ, i ); 	return &PL_sv_no;  }
		}else{					ub=i;		i=( lb + i	)>>1;	if( i==ub	){		svQ=newSVpvn( pqx, 8 );  SvINS( avArg, svQ, i );	return &PL_sv_no;  }
			}			pq = SvPVbyte_nolen( svQ=	*( sv0 +i ) );
		}
	return &PL_sv_yes; 	// return true: index i  was redefined
	}
SV*	insortIV(		SV* rvArg,	SV*	svX	){
	const char	*	arg0_err	= "\r!       ICE::insortIV( <%s>, <%s> ): arg[0] is not an arrayref.\n\t",
				*	arg1_err	= "\r!       ICE::insortIV( <%s>, <%s> ): arg[1] is not a numeric scalar.	SvTYPE( svX )==%d; SVt_IV==%d\n\t";
	svtype			t0 = SvTYPE(	rvArg ),
					t1 = SvTYPE(	svX	);
	if(	t0 != SVt_RV		|| !SvROK(	rvArg	) ){	printf( arg0_err,  svtype_names[ t0 ],		svtype_names[ t1 ] );		return &PL_sv_no; }
	if( (	t1 != SVt_IV &&
		t1 != SVt_PVIV )	|| !SvOK(	svX		) ){	printf( arg1_err,  svtype_names[ t0 ],		svtype_names[ t1 ], SvTYPE( svX), SVt_IV );		return &PL_sv_no; }
	avArg = (AV*)	SvRV(	rvArg );
	t0 = SvTYPE(			avArg );
	if( t0 != SVt_PVAV ){						printf( arg0_err,  svtype_names_ref[ t0 ],  	svtype_names[ t1 ] );		return &PL_sv_no; }

	const long long	x	= SvIVX( svX );
	SSize_t			displacement;
	long long int		lb	= 0,
					ub	= AvFILLp( avArg )+1,	i= ub >>1;			if( ub==0	){		svX=newSViv( x );  SvINIT( avArg, svX );		return &PL_sv_no;	}

	SV				**	src,
					**	dst,
					**	svA0= AvARRAY( avArg ),
					*	svA	= *(svA0 +i );
	while(	x !=	SvIVX(	svA ) ){
		if(	x >	SvIVX(	svA ) ){		lb=i;			i=( i +ub	)>>1;	if( i==lb	){ ++i;	svX=newSViv( x );  SvINS( avArg, svX, i );	return &PL_sv_no;  }
		}else{						ub=i;		i=( lb + i	)>>1;	if( i==ub	){		svX=newSViv( x );  SvINS( avArg, svX, i );	return &PL_sv_no;  }
			}			svA	= *(svA0 +i );
		}
	return &PL_sv_yes; 	// return true: index x already exists
	}
SV*	screenKeys(	SV* rvICE, SV* rvArg ){
	SV*				svOut;
	svtype	rt0, rt1,	t0 = SvTYPE( rvICE ),
					t1 = SvTYPE( rvArg );
	const char	*	arg_err	= "\r!       ICE::screenKeys( <%s>, <%s> ): arg[%d] is not an arrayref.\n\t";

	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg_err,  svtype_names[		t0 ],  	svtype_names[	t1	], 0 );  return &PL_sv_no; }
	if( t1 != SVt_RV || !SvROK(	rvArg) ){	printf( arg_err,  svtype_names[		t0 ], 	svtype_names[	t1	], 0 );  return &PL_sv_no; }

	avICE	= (AV*) SvRV(    	rvICE );	rt0 = SvTYPE( avICE );
	avArg	= (AV*) SvRV(    	rvArg );	rt1 = SvTYPE( avArg );

	if( rt0 != SVt_PVAV ){				printf( arg_err,  svtype_names_ref[	rt0 ],  	svtype_names_ref[	rt1	], 1 );  return &PL_sv_no; }
	if( rt1 != SVt_PVAV ){				printf( arg_err,  svtype_names_ref[	rt0 ],  	svtype_names_ref[	rt1	], 1 );  return &PL_sv_no; }

	_screenKeys();
	svOut = newSViv( hit );
	return svOut;
	}
SV*	screenHV(	SV* rvICE, SV* rvArg ){
	SV*				svOut;
	svtype	rt0, rt1,	t0 = SvTYPE( rvICE ),
					t1 = SvTYPE( rvArg );
	static const char	*	arg0_err	= "\r!       ICE::screenHV( <%s>, <%s> ): arg[0] is not an arrayref.\n\t",
					*	arg1_err	= "\r!       ICE::screenHV( <%s>, <%s> ): arg[1] is not a hashref.\n\t";

	if( t0 != SVt_RV || !SvROK(	rvICE) ){	printf( arg0_err,  svtype_names[		t0 ],  	svtype_names[	t1	] );  return &PL_sv_no; }
	if( t1 != SVt_RV || !SvROK(	rvArg) ){	printf( arg1_err,  svtype_names[		t0 ], 	svtype_names[	t1	] );  return &PL_sv_no; }
	avICE	= (AV*) SvRV(    	rvICE );	rt0 = SvTYPE( avICE );
	hvArg	= (HV*) SvRV(    	rvArg );	rt1 = SvTYPE( hvArg );
	if( rt0 != SVt_PVAV ){				printf( arg0_err,  svtype_names_ref[	rt0 ],  	svtype_names_ref[	rt1	] );  return &PL_sv_no; }
	if( rt1 != SVt_PVHV ){				printf( arg1_err,  svtype_names_ref[	rt0 ],  	svtype_names_ref[	rt1	] );  return &PL_sv_no; }

	_screenHV();
	svOut = newSViv( N );
	return svOut;
	}
void test_unrack(){
	
	}
void test_rack(){

	char unsigned u, v, w,		/*	matrix indeces	which iterate		the source range			in	matrix { A[], B[], E[], Q[] }	*/
				__0x, __zx,	/*	matrix indeces	which mark		the range of cube iC (incl.)	in	matrix { A[], B[], E[], Q[] }	*/
				__mx0,		/*	matrix index		which marks-in	the source range			in	matrix { A[], B[], E[], Q[] }	*/
				__mxZ,		/* 	matrix index		which marks-out	the source range			in	matrix { A[], B[], E[], Q[] }	*/
				__pre_c,		/*	cyclum count		which tracks		the pre-op  dest. range		in	char *	cube				*/
				__post_c,		/*	cyclum count		which defines		the post-op dest. range		in	char *	cube				*/
				pre_q,		/*	q-data length sum	which tracks		the pre-op  dest. range		in	char *	cube				*/
		postQ0,	post_q;		/*	q-data length sum	which tracks		the post-op dest. range		in	char *	cube				
												and determines	the rebalance level			for the _rack() function			*/
	char			__mc0,__mcZ,	/*	cyclum indeces	which mark in/out	the destination range		in	char *	cube				*/
				__zc;		/*	cyclum index 		which bounds		the terminating cyclum		of	char *	cube / cube_		*/

	char unsigned	rem_c,		/*	cyclum count		which defines		the terminating fragment	in	char *	SvPVbyte( *( AvARRAY( avICE ) +iCZ), CS )	*/
				bal_c;		/*	cyclum count		which defines		the intermediate fragment[s]	in	char *	SvPVbyte( *( AvARRAY( avICE ) +iCX), CS )	*/
	ui64			G_bal,
				__Hx8,
				__Qx8,
			*	qob;
	//differential metrics will go negative
	char			__relQ,		/*	q-data offset		which compares	pre & post op q-data totals	in	matrix { A[], B[], E[], Q[] }	*/
				__rel_c;		/*	cyclum offset		which compares	pre & post op cyclum counts	in	matrix { A[], B[], E[], Q[] }	*/

	int		x,	__post_zc,
				__post_mcZ;

	char	unsigned	gmx,	__mxcZ,
				__Qx8a[8],
				__Qx8b[8];
	SV		*	__sv;
	STRLEN		__HL, __CS;


	for( icx=0;  icx<20 ;  ++icx ){	*( (ui64*) buf +icx )=0ULL;	}//zero the write buffer	

	avICE	= newAV();	AvINIT1( avICE );
	avOut	= newAV();
	rvOut	= newRV_inc( (SV*) avOut );

//	for( zc=-1;	zc<8; ++zc){
	for( __zc=0; 	__zc<8; ++__zc){
		__HL = __zc+1;
		
		for(					__mc0 	= 0;			__mc0<=7;	  ++	__mc0	){
			for(				__mcZ	= __mc0;		__mcZ<=7;	  ++	__mcZ	){	for(	gmx = 0; gmx<2;	++	gmx ){
					_ez	=1+	__mcZ +gmx;			__mx0=			__0x	=	__mc0				+	gmx;
								__pre_c = __mcZ -	__mc0;					
					for(			__post_c=0;  __post_c<= 15;  ++__post_c ){
														
						av_clear( avICE );	__sv = newSVpvz(	32		);
						
						SvCUR_set(		__sv,			16+__HL	);
						av_store(avICE,0,	__sv	);
						AvINSERT( avICE, 0, 1);
						*AvARRAY( avICE )=__sv;
						cube = SvPVbyte(	__sv, CS );

						qob = (ui64*) cube;
						switch( __HL){
/*					keybyte table							epsilon					variable q-data		*/
case 0: qob[ 0 ]=		0x0000000000000000;		qob[ 1 ]=		0;			qob[ 2 ]=		0x0000000000000000;		break;
case 1: qob[ 0 ]=		0x0000000000000048;		qob[ 1 ]=		11;			qob[ 2 ]=		0x000000000000000A;		break;
case 2: qob[ 0 ]=		0x0000000000004848;		qob[ 1 ]=		21;			qob[ 2 ]=		0x000000000000090A;		break;
case 3: qob[ 0 ]=		0x0000000000484848;		qob[ 1 ]=		31;			qob[ 2 ]=		0x000000000009090A;		break;
case 4: qob[ 0 ]=		0x0000000048484848;		qob[ 1 ]=		41;			qob[ 2 ]=		0x000000000909090A;		break;
case 5: qob[ 0 ]=		0x0000004848484848;		qob[ 1 ]=		51;			qob[ 2 ]=		0x000000090909090A;		break;
case 6: qob[ 0 ]=		0x0000484848484848;		qob[ 1 ]=		61;			qob[ 2 ]=		0x000009090909090A;		break;
case 7: qob[ 0 ]=		0x0048484848484848;		qob[ 1 ]=		71;			qob[ 2 ]=		0x000909090909090A;		break;
case 8: qob[ 0 ]=		0x4848484848484848;		qob[ 1 ]=		81;			qob[ 2 ]=		0x090909090909090A;
									}
						printf("\nHxExQ: 0x%016llXx%016llXx%015llX\n", qob[0], qob[1], qob[2] );

						_toText();
						_printAvOut();
						av_clear( avOut );

						__mxZ=	__post_c		+	__mx0;
						__rel_c =	__post_c -__pre_c;					_0x  	=	__0x;
								__post_zc	= __zc	+__rel_c;		_ez  	=1+	__post_zc			+	gmx;
								__post_mcZ	= __mcZ	+__rel_c;
						__mxcZ =__mcZ + gmx;

						Ev=10;	E[255]=0;	O[255]=16;Q[255]=0;
						u=0;

while(	u< gmx ){	F[u]=null;		O[u]=16;			Q[u]=		A[u]=	B[u]=	E[u]=0;			_O[u]=	_Q[u]= Hx[u]= 0;	++u;	 }
while(	u< __mx0 ){	F[u]=ok;		O[u]=16+u;		Q[u]=1;		A[u]=9;	B[u]=1;	E[u]=(10*(u+1) ) +1;	_O[u]=	_Q[u]= Hx[u]= 0;	++u;	 }
	v=	u +1;
	if(	u >__mxcZ ){	F[u]=new;	O[u]=17+__mxcZ;	Q[u]=0;	
	}else{			F[u]=mod;	O[u]=16+u;		Q[u]=1;	 }	A[u]=9;	B[u]=1;	E[u]=(10*(u+1) ) +1;	_O[u]=O[u];
														++	A[gmx];							ReICEuO(  u, v );	
while(	u< __mxZ ){
	if(	v >__mxcZ ){	F[v]=new;	O[v]=17+__mxcZ;	Q[v]=0;
	}else{			F[v]=mod;	O[v]=16+v; 		Q[v]=1;	 }	A[v]=9;	B[v]=1;	E[v]=(10*(v+1) ) +1;						u=v++;
																							ReICEuOx(  u, v );			}
																							O[v]=O[u]+1;
						_print_mx( 777); 
						__Hx8=*( (ui64*) cube );	//	*( (ui64*) __Qx8a) =0;	for( x=16; x<CS; ++x) __Qx8a[x-16]=cube[x];

						sv		= __sv;
						ic		= __mcZ;		zc		= __zc;
						mc0 	= __mc0;		mcZ	= __mcZ;			
						mx0	= __mx0;		mxZ	= __mxZ;		
						mxE	= __mxZ+1;	mcE 	= __mcZ+1;
						printf("\r_test_rack(): av_clear( avRack )...\n");
						av_clear( avRack );
						svC0=AvARRAY( avICE );

						printf("\r_test_rack(): _rack( 321 )...\n");
						_rack(321);			//	*( (ui64*) __Qx8b) =0;	for( x=16; x<CS; ++x) __Qx8b[x-16]=cube[x];
					//	_unrack();     

						printf("\r");
						_toText();
						_printAvOut();
						av_clear( avOut );
						printf("\nHx8, Qx8  (pre): 0x%016llX	 0x%016llX\nHx8, Qx8 (post): 0x%016llX	 0x%016llX\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n",
								__Hx8,			0ULL,		//	*( (ui64*) __Qx8a ),
								*( (ui64*) cube ),	0ULL	);	//	*( (ui64*) __Qx8b ) );



					/*	<SIMULATION>	grew  */
		   
					/*	</SIMULATION>	*/
		}	}	}	}	}
	}
void test_set(){

	}
SV* alloc(		SV*	rvICE	){
	avICE= (AV*) SvRV(	rvICE);
	if( ( t_xv=SvTYPE( avICE) ) !=SVt_PVAV){		printf("\r!	alloc(): argument 0 must be an arrayref\n", t_xv );	return &PL_sv_undef; }
	svX = _alloc()? newSVuv( x): &PL_sv_undef;
	return svX;
	}
SV* set(			SV* rvICE,	SV* rvArg ){
	avICE= (AV*) SvRV( rvICE);
	avArg= (AV*) SvRV( rvArg);
	_set();
	return newSViv( skip );
	}
SV* keys(		SV* rvICE	){
	ui08		sp[24];
	int			sL;
	avICE= (AV*) SvRV( rvICE);	zC = AvFILLp( avICE);
	avArg= newAV();
	Ex=0;
	ui64 i=0;
	for( iC=0; iC<=zC;  ++iC ){	sv = *( AvARRAY( avICE) +iC );
		cube = SvPVbyte(		sv,  CS );
		pq =cube +16;
		for(  Kx8= *( (ui64*) cube );  Kx8!=0;  Kx8>>=8 ){	Ki= Kx8;	deICE( Qx, Ax, Bx )
					x =Ex +Ax;
			for( Ex =	x +Bx;  x<Ex;  ++x){
				sL=sprintf( sp, "0x%llx", x);
				av_push( avArg, newSVpvn( sp, sL ) );
				}
			}
	//	sL=sprintf( sp, "|");
	//	av_push( avArg, newSVpvn( sp, sL ) );
		}
	rvArg =newRV_inc( (SV*) avArg);
	return rvArg;
	}
SV* ranges(		SV* rvICE	){
	avICE= (AV*) SvRV( rvICE);	zC = AvFILLp( avICE);
	avArg= newAV();
	Ex=0;
	for( iC=0; iC<=zC;  ++iC ){ sv= *( AvARRAY(	 avICE) +iC );
		cube = SvPVbyte(	sv,  CS );
		pq =cube +16;
		for(  Kx8= *( (ui64*) cube );   Kx8!=0;  Kx8>>=8 ){	Ki= Kx8;	deICE( Qx, Ax, Bx )
			av_push( avArg, newSViv( x=Ex +Ax	) );
			av_push( avArg, newSViv( Ex=x +Bx	) );
		}	}
	rvArg =newRV_inc( (SV*) avArg);
	return rvArg;
	}
SV* fromRvAV(	SV	* rvArg	){	printf("\r<fromRvAV()>\n");
	const char	*	arg0_err	= "\r!       ICE::fromRvAV( <%s> ): arg[0] is not an arrayref.\n\t";

	if(	SvTYPE(		rvArg ) !=		SVt_RV	||!	SvROK(	rvArg ) ){	printf( arg0_err,  svtype_names[		SvTYPE( avArg ) ] );		return &PL_sv_no; }
					avArg = (AV*)	SvRV(				rvArg );
	if(	SvTYPE(		avArg ) !=	SVt_PVAV ){					printf( arg0_err,  svtype_names_ref[	SvTYPE( avArg ) ] );	return &PL_sv_no; }
					avICE = newAV();
		za=  AvFILLp(	avArg);
	if(	za >=0 ){
		x =	SvIVX(  svX = *AvARRAY( avArg)  );
		*( (ui64*) 		buf )=0;	pk =buf;	pq =buf +16;		a=0; 	Ez=0;
		AvCUBE( avICE,	buf,		pk,		pq,		avArg,	a,	za,	Ez );
		}
			rvICE = newRV_inc( (SV*)	avICE );
	sv_bless(	rvICE,					hvICE );		printf("\r	</fromRvAV()>\n");
	return	rvICE;
	}