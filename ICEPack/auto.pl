use strict; use warnings;	++$|;

my $s=0;

	print("	starting cycle #0...\n");	
while(1){
	system('perl -Ilib -e "use ICEPack; use strict; use warnings; ICEPack::test_set_recursively( 15, 15, 1 );');  	++$s;
	print("	starting cycle #$s...\n");	
	}