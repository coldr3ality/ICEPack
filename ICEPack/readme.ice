ICEPack v0.2.5

In this second release, the implementation has been aptly named "ICEPack".

In order to run the tests, build the project starting with Makefile.pl, then in the main directory:

perl -Ilib -e "use ICEPack;  ICEPack::test_precursors();  ICEPack::test_set_recursively(1);"

At its current functional level, ICEPack still has only one setter implemented (ICEPack::set) and although the core algorithm can now refragment data segments in all ways, there is still a limitation on number of arguments (240) which can be processed by set() at once because the main buffer still has no flush.  "Trivial" you may say— and you'd be right.  I just want to dwell on proper testing before I move on.


The fragmentation function "_rack1x()" has been a true investment.  Worthwhile and effective though time consuming to implement, its original specification was very simplistic in the Perl-based proof-of-concept.  This function is crucial for efficient mutation.  It is always in the critical path; it requires twelve branches to modify and re-fragment data segments (called "cubes") in every possible case given the objectives for efficiency.  It could have been simpler, and it could have been more complex; tradeoffs were made. 

The most complex cases have shown to be very improbable when randomly generating sample data.  While the simpler cases have been absolutely battered with hundreds of millions of tests by now, these complex cases have only hit a few times at the time of this writing (although I can say they have all passed).  At this point I am basically mining for rare sets of random sample data which trigger these cases and archiving them in the test script.  I still favor randomly generated test data over hand-crafted, as there is a very chaotic and dynamical aspect to the automated coordination of concurrent mutations.

Some of the process audits are absolutely wonderful— everything I'd dreamed.  Auditing the "av_commit()" function shows that it is properly handling a complex schedule.  This is essentially single-pass mutli-splice, and it is crucial to make this data structure performant.  An instance of ICEPack is just a Perl array populated with compressed data segments, and while minor mutations do not cause reallocation, the unavoidable O( length - n ) performance cost of fragmentation can only be mitigated with such streamlined batch processing.  As more arguments are overloaded into a single call, less reflow work is necessary.  The impact to high-scale computational complexity is enormous.

The finished base package, like its Perl proof of concept, will have all of the following accessor methods implemented:

	alloc()					[n/i]	Find the lowest available key, set it and return it	
	exists($x)				[n/i]	Check existence of key $x
	exist(@$args)				Check existence of keys in @$arg; cut hits from @$arg.
	set(@$args)				Include the keys in @$arg
	xset(@$args)			[n/i]	Include the keys in @$arg; cut hits from @$arg.
	set1($x)			[n/i]	Include key $x
	unset(@$args)			[n/i]	Exclude the keys in @$arg
	unset1($x)				[n/i]	Exclude key $x
	sweep($x, $y, $s)	[n/i]	Increase the vector captured by [x..y-1] by s;
								if none exists, create one at x+s-1.
	unsweep($x, $y, $s)	[n/i]	Decrease the vector captured by [x..y-1] by s.


Additionally, 2 out of 3 conversion methods are implemented:

	toText()				Convert the ICE object to human readable text table.
						Returns an arrayref of scalars.
	toPerl()				Convert the ICE object to monotype-formatted Perl array code.
						Returns an arrayref of scalars.
	toSerial()			[n/i]	Convert the ICE object to a packet stream of given MTU size.
						Returns an arrayref of scalars.


The extension built on top of this adds efficient dynamic enumeration provided by the following accessors:

	ord($x)		[n/i]	get the sort order of a given key, signed by existence
	uord($x)		[n/i]	get the sort order of a given key, don't care if it exists
	xord($x)		[n/i]	get the inverse sort order	of a nonexistent key
	xords(@$args)	[n/i]	get the inverse sort order[s]	of one or more nonexistent keys
	keyAt($i)		[n/i]	get the key 	at the given sort order
	keysAt(@$args)[n/i]	get the key[s]	at the given sort order[s]
	xkeyAt($x)		[n/i]	get the nonexistent key		at the given inverse sort order
	xkeysAt(@$args)[n/i]	get the nonexistent key[s]	at the given inverse sort order[s]

