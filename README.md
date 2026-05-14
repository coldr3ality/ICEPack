Copyright 2026 Peter Arlen Schmidt

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

ICEPack is an instantiable object class for a data structure I categorically define as a Compressed Truth Vector.  The inspirational concept I was trying to achieve when I set out to develop this data structure was something which combined the access modalities of hashes and arrays without the complexity or overhead of a database, meeting or exceeding a modern standard of computational efficiency.  Elements are addressable by sparse key as in hashes, or by ordered index as in arrays.  The architecture has three abstraction layers, starting with a custom binary encoding I call Inversion Cycle RLE, which is a minimized version of RLE for alternating boolean values.  The second abstraction layer is a fairly basic binary search implementation over a sorted array of these IC-RLE segments, and the third abstraction layer is a stratified/laminar regressive quantization of the second-layer data array, grading the namespace content down into increasingly quantized reductions, storing respective modulus values in the freed up allocation space for each combined unit key, which can be atomically updated by setters as the structure changes, and efficiently summed by getters to compute the sort order of sparse keys on demand.  I want to call it dynamic enumeration.

In a way, it allows for treating defined and undefined namespace as two dimensions of one regular series.  It enables an access modality similar to Perl's range operator (where you specify a series in terms of its starting and ending value), but now those values can be sparse keys, and they can select from either the defined or undefined sparse key namespace efficiently.  This makes mass shuffle practical.  Indeed, the intended application is mass distributed session ID randomization where collision is prevented through true namespace conservation (not merely leveraging astronomical odds) and without introducing a special need or requirement for a core network to maintain sync across edge servers.

I first developed a complete proof of concept in 2020 written in Perl.  Since then, I have taken on learning C and giving the specification and architecture the proper treatment to realize an enterprise grade implementation.

In my estimation, the current status of development is a well-earned v0.2.5, where I have the first abstraction layer very well optimized, and the low level code of the second abstraction layer fully implemented and tested.  Only one of three public setters within the second abstraction layer is implemented, and the third abstraction layer is still entirely not implemented.


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

	As a security enthusiast, I must bore you with words of caution.

	While this data structure is designed to be directly amenable to wire synchronization across edge servers, this concept is not widely used.
	
