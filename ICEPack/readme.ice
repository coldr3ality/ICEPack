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

