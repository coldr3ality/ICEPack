OBJECTIVE
An object class with sparse keys like a hash, but sorted and indexed like an array, 
with compression that packs tighter the more filled its namespace gets— 
a data structure that can work within a tight memory footprint indefinitely, 
while atomically maintaining a constant state of balanced fragmentation, 
amenable to direct packet encapsulation.

While this is a completely original design, it bears certain similarities with previous work.

From a conversation with Claude Haiku 5.5 on Nov. 8th, 2026:

[Me]
... It is meant to be versatile, to serve at least two very specific (yet different) use cases in application code perfectly.
The funny thing is, to me, it solves a general problem I seemed to run up against many times in my 20+ years of coding: 
often I wish to have the combined access modality of arrays and hashes in some kind of hybrid primitive structure, 
especially for use cases where a database is far too much bulk.  
This structure is intended to strike a balance of memory and processing efficiency, with predictable costs 
that allow the application designer to know for sure that an instance can live perpetually within a defined memory footprint 
and not need to be offloaded to disk, even in the worst case scenario.

[Claude]
The gap you describe is real. Most languages give you either an ordered sequence or a keyed map, 
and an ordered keyed structure with rank queries is awkward to build from those parts. 
Your design gets both behaviors from one sorted, rank-indexed set, and its predictable cost 
is the property that matters most for an in-memory footprint.

Some established structures cover parts of the same ground, which may help you position it:

[Structure]						[Keyed lookup]						[Rank (index of a key)]		[Predictable worst case]			[Compact storage]
Hash table						Yes, O(1) average					No												Only with careful hashing			Moderate, with load-factor slack  
																																					and resizing	
B-tree / B+ tree			Yes, O(log n)							Only with subtree counts	Yes													  Good, with page overhead

Skip list (indexable)	Yes, O(log n) expected		Yes, with span counts			Expected, not guaranteed			Higher pointer overhead

Adaptive radix tree		Yes, O(key length)				Only with added counts		Yes, bounded by key width			Good for dense keys

Your structure				Yes, O(d log n)						Yes, O(n) worst 					Yes, bounded by digit count		Very compact, 
											with running totals				or O(log n)																							digit-level sharing
            
Your design is closest to an adaptive radix tree with subtree counts, but flattened into sorted arrays, 
so there are no pointers and the layout is contiguous. 
That contiguity is probably what makes the footprint predictable, 
since the worst case is set by the number of distinct prefixes at each level 
rather than by allocator behavior.
