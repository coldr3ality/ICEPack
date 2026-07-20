OBJECTIVE
To engineer a non-repeating ID layer across edge devices without a core network.

There are entropy sources as usual, but instead of piping this directly into a Session ID generator,
we allocate "random nth" IDs in a Compressed Truth Vector, conserving namespace locally; then,
implement periodic redistribution of free namespace across all nodes to minimize loss of entropy.
Edge servers assign Session IDs unilaterally and on an event-driven basis, with no core negotiation.
ID/name collissions are prevented implicitly by the applied concept of "Dynamic Enumeration".
Not only does this intrinsic collision prevention free us to spec for raw computation complexity,
it also enables us to implement Perfect Forward Secrecy— i.e., perpetual ID renewal. 

OBJECT CLASS
ICEPack manipulates QWORD-sized truth vectors designed to be used as inside-out UUID tables.
These truth vectors provide a hash-like interface to a 64-bit namespace, 18 quintillion flag bits,
though the absolute minimum compression ratio of 3:1 is to be expected for highly entropic data.
This space is fragmented as a searchable array and compressed using a sort of run length encoding—
Inversion Cycle RLE, or just Inversion Cycle Encoding (ICE).

ENCODING
ICE encoding is a compressed bit-vector format, where access to nearest adjacent set/unset bit
scales in constant O(1) time, ideal for allocation within highly entropic inside-out UUID tables.
Like RLE, ICE compresses repeating values as run lengths, but it stores no values explicitly—
alternating true-false run lengths store boolean value implicitly, as an "even" or "odd" count.
Compression peaks with namespace density, storing tightly-packed run length pairs as single bytes.

ACCESS MODALITY
ICEPack implements a hash-like interface while ICEPack::E extends it with "dynamic enumeration".
Dynamic enumeration enables a novel access modality where keys can be selected using ranges,
from both the existent/allocated and nonexistent/free namespace.  This is powerful.

In both use cases, a full suite of accessor methods enable manipulation by range, mask, sorted list,
or object comparison, as well as basic scalar arguments.

TIME COMPLEXITY
When using just the base class (without dynamic enumeration), time and size scale hyperbolically.
When using the extended class, a small additional overlaying structure scales semi-logarithmically.

ICE CUBES
To promote the integrity of the encoding across mutations, ICE compresses pairs of true-false runs
and mediates computational complexity to access and mutate these entries with fragmentation.
Encoded data is balanced over a series of variable segments (16 to 144 bytes in length) which 
are sorted into a searchable AV* array.

DYNAMIC ENUMERATION
Any sparse array compression technique eliminates null data, which represents a critical tradeoff:
recover space at the cost of the implicit 1:1 relationship of index to ID.

The solution applied here is to regressively quantize indeces across a modulus counter gradient,
storing summative modulus values in the freed up allocation space for each quantized unit index, 
which are atomically updated by setters during mutation, and efficiently summed by getters 
to compute the sort order of sparse keys on demand.

So, to reiterate:
	> Trivial access to lowest / highest / nearest sparse index in O(1) time
	> Hash-like sparsity with array-like sorting effectively works like a range operator for keys
	> Basically redefines the Perl idiom "Everything Is A Number"
