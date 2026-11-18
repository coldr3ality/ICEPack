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



I have re-written this description so many times, I'm beginning to feel crazy.  I have recently had a conversation with Claude (4.5) which was very enlightening, though, and a [nearly] final rewrite is in order; while the architecture shares familiar concepts with radix trees, binary search trees and age-old bitmap compression techniques, Claude cannot identify a single data structure that combines these three to do what this does.

ICEPack is a Perl object class for a data structure I categorically define as a compressed bitvector integrated with an octal radix tree, which enables a rich access modality that is simultaneously array-like and hash-like, and it accepts batch arguments as parametric ranges as well as discrete, literal keys and indeces.

It can rank (or get keys by rank) in terms of both used or free namespace.  This, without the need to reflect or mirror two different data sets; it's all one structure, and it's efficient with both processing and RAM.


The working concept I was inspired to develop was an ID table which combines the access modalities of hashes and arrays without the complexity or overhead of a database, meeting or exceeding a modern standard of computational efficiency.  True random deterministic ID shuffling is shown, although the full randomness pipeline is crucial.

I first developed a complete proof of concept in 2020 written in Perl.  Since then, I have taken on learning C and giving the specification and architecture the proper treatment to realize an enterprise grade implementation.

In a way, this is a prime example of the old Perl addage that "everything is a number".  Indeed, that sums it up.
