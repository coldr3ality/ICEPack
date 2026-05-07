use strict; use warnings;	++$|;
my $s=0;
my $exit;

	print("	starting cycle #0...\n");	
while(1){
	my $exit=system('perl -Ilib -e "use ICEPack; ICEPack::test_set_recursively();"');  	++$s;
	exit if($exit==10);
	print("	starting cycle #$s...\n");	
	}