
	ICE encoding is efficient for inside-out UUID tables.  It has O(1) access time to lowest / highest / nearest existing / nonexisting keys.

	ICEPack is a Perl/XS implementation of ICE, providing hash-like access and wire-ready compression on hyperbolic time scales.

	ICEPack::REG implements a regressive exponent gradient, providing dynamic range enumeration over logarighmic time scales.

	So, to reiterate:
		> Trivial access to lowest / highest / nearest sparse index in O(1) time— an obvious strength for dynamic ID tables
		> Hash-like sparsity with array-like sorting effectively works like a range operator for key spaces
		> Basically redefines the Perl idiom "Everything Is A Number"

	ICE is a QWORD-sized compressed truth vector which uses an original variant of RLE encoding— Inversion Cycle RLE.
	IC-RLE compresses repeating values into run lengths  (like RLE), but stores no explicit values— only implicit boolean truth.
	Since RLE stores only the first occurrence of a repeating value, and boolean values can only be one of two, value is implicit—
	so essentially, IC-RLE representation is an explicit series of run length pairs which implicitly store alternating true-false values.

	To promote the integrity of the encoding across mutations, ICE compresses pairs of true-false run lengths in single entries,
	and mediates computational complexity to access and mutate these entries with opportunistic [de]fragmentation.
	Encoded data is stored as a series of semi-regular chunks (16 to 144 bytes in length) which are sorted into a searchable AV* array.
	
		> Computational complexity plots as a roughly hyperbolic asymptote given the worst case highly entropic data.
		> Batch processing affects significant improvement in mutation time complexity when leveraged by the application.
		> Variety of accessor methods enable manipulation by range, mask, sorted list and scalar arguments, as well as recombination.
		> In-memory data blocks are an easy packet payload to stream over TCP with no fragmentation and minimal layer-4 overhead.
	

	Any sparse array compression technique which omits nulls makes the obvious but unfortunate tradeoff of gaining space
	while sacrificing the implicit identity of each element by its index— often the single most characteristically useful property of arrays.
	This is where ICEPack::RELIC comes in— to implement efficient non-sparse sort order computation.

	For example: let's say you wish to implement a random number generator that is non-deterministic, yet also non-repeating,
	and you wish to use this to exzate Session IDs in a massively distributed cloud server application.  You would have your choice
	of entropy sources as usual, but instead of piping this directly into a Session ID generator, you use it to choose the "nth" free ID
	in an ICEPack::RELiC instance, which trivially guards against colissions; in order to make replication across a server farm more efficient,
	you can allow servers to preexzate large random sets of IDs, periodically throwing them back into the pool and drawing a new set.
	In this way, edge servers can still set service-wide Session ID assignments on an event-driven basis, with no core negotiation needed,
	but IDs are still guaranteed collission-free.  Not only does this free us to rate the appropriate namespace depth precisely, but it also
	frees us to implement Perfect Forward Secrecy— to renew the Session-ID upon each and every response.  

