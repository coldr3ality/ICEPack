ICEPack v0.2.0

This initial release is meant to demarcate a major milestone of first stable functionality.  I am releasing it with the intent to commit the project to the public domain.  It features just one primary accessor "set" in just the base package.  It may be novel, maybe not, but Claude couldn't tell, so I'm calling this data structure a Compressed Truth Vector; the encoding, ICE.  This implementation has no official name yet.  The Perl prototype is called "IDEX" (which is not released).

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

