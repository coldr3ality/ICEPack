use ExtUtils::MakeMaker;
use File::Glob ':bsd_glob';

my @c_src			= bsd_glob('src/*.c');
my @o_src			= @c_src;
my @o_src			= map { s/\.c$/\$(OBJ_EXT)/; $_ } @o_src;
my @o_src_padded	= map { sprintf("%-32s", $_ ) } @o_src;
my @c_src_padded	= map { sprintf("%-32s", $_ ) } @c_src;

print("\n\n\"*.c\" files in  ./src:\n\t", join("\n\t", @c_src ), "\n\n\n");
print("\n\n\"*.o\" files out ./src:\n\t", join("\n\t", @o_src ), "\n\n\n");

WriteMakefile(
	'NAME'				=> 'ICEPack',
	'LICENSE'			=> "Apache-2.0",
	'AUTHOR'			=> 'Peter Schmidt',
	'VERSION_FROM'  	=> 'lib/ICEPack.pm',
	'ABSTRACT_FROM' 	=> 'lib/ICEPack.pm',

#	'TYPEMAPS' => ['C:\\Perl64S\\perl\\lib\\ExtUtils\\typemap'],
	'LIBS'				=> ['-lm'],              # Link with math library
#	'INC'				=> '-iquote"lib/"',
	'INC'				=> '-I. -I./src',
	'PREREQ_PM'			=>{	'ExtUtils::MakeMaker'	=> '7.12',
							'Time::HiRes'			=> 0			},
	'XS'					=>{ 'ICEPack.xs'	=> 'ICEPack.c'	},
#	'clean'				=>{ 'FILES'		=> 'ICEPack.c'	},
	'OBJECT'				=> '$(O_FILES) ' . join(' ',  @o_src),
	'LIBS'				=> ['-lm'],              # Link with math library

#	'TYPEMAPS' => ['C:\\Perl64S\\perl\\lib\\ExtUtils\\typemap'],

#	'CCFLAGS'			=> "$Config::Config{ccflags}",
	'OPTIMIZE'			=> '-O1',
#	'XSMULTI'			=> 1,
	);

sub MY::postamble {
	my @rules;	$#rules=$#c_src;
	for( my $f=0; $f<= $#c_src; ++$f ){
		my $src=$c_src[ $f ];
		my $obj=$o_src[ $f ];

		$rules[$f]="\n$o_src[$f]: $c_src[$f]\n	\$(CC) -c $c_src_padded[$f] -o $o_src_padded[$f] \$(OPTIMIZE) \$(INC) -I\$(PERL_INC) -I\$(PERL_INCDEP) $Config::Config{ccflags}\n\n"
		}
	return join( '', @rules );
	}

# Remove the Makefile dependency. Causes problems on a few systems.
#sub MY::makefile { '' }