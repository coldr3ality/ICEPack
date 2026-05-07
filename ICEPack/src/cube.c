/*	Copyright 2026 Peter Arlen Schmidt

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	    http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "dBUG.h"
#include	"cube.h"
//	camelCase				JavaScript, Java
//	snake_case				Python, Ruby, C/C++ standard libraries
//	SCREAMING_SNAKE_CASE	Constants in C, Java, JavaScript
//	kebab-case				URLs, some JavaScript frameworks
//	PascalCase				C#, Java (for class names)
//	flatcase					HTML elements and attributes

/*	THE (3) LEVELS Of DEBUG:
	L1:	audit nominal activity
	L2:	audit nominal activity (more verbosely)
	L3:	silently check integrity, reporting only errors
	*/


/*	ICEPack::RELiC—	Regressive Exponent Laminar Index Counter (RELiC) over Inversion Cycle Encoding (ICE)
	this jam is real																				*/

/*	ABSTRACT																				*/

/*	ICE encoding is efficient for inside-out UUID tables.  It has O(1) access time to lowest / highest / nearest existing / nonexisting keys.

	ICEPack structures a sorted array of searchable ICE chunks, enabling hash-like and array-like access over hyperbolic time scales.

	ICEPack::REG implements a regressive exponent gradient, providing dynamic range enumeration over a logarighmic time scale.

	So, to reiterate:
		> Trivial access to lowest / highest / nearest sparse index in O(1) time— an obvious strength for dynamic ID tables
		> Hash-like sparsity with array-like sorting effectively works like a sorted hash
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

	As a security enthusiast, I must bore you with words of caution, because even the best tools don't use themselves (properly... yet).
	TODO lol

	*/

/*	RELiC extends ICE to support direct enumeration— in both defined and undefined namespace.  This is potentially very powerful:

		> As a data structure, RELIC is the fullest realization yet of the "Perlish" notion that "everything is a number".
		> RELiC allows for an efficient and completely deterministic inside-out implementation of mass distributed non-repeating shuffle.
		> Additional overhead per ICE instance is reasonable: +20% memory footprint and similar rise in access complexity.
		
	A RELiC graph may be visualized as an outline of a staircase in 2D, where the X and Y axes are defined / undefined namespace.
	Similar to the PATH element in SVG, all coordinates are relative, so the origin of each point is the previous point.
	When we assert the staircase shape, then for every even point, X would equal 0, and for every odd point, Y would equal 0.
	Given the assertion, we can safely omit these zeros to save space, which would apparently reduce our 2D polyline data to 1D—
	this works because we can still distinguish the X and Y coordinates by looking at whether a particular line segment is even or odd.
	The total length of the staircase at any point along any tread is analogous to its sorted index in the defined domain, whereas
	the total height of the staircase at any point along any riser is analogous to its sorted index in the undefined domain.

	*/

/*	RELiC acts as the second dimension of ICE, encapsulating a stack of ICE arrays which get exponentially smaller in ascending order.
	A twos-compliment numeric base is chosen (such as 2^3), and the source ICE array is regressively quantized to form a second axis.

	As a standalone algorithm, RELiC expresses a potentially heavy expanded matrix structure which becomes surprisingly light over ICE.
	An inverse relationship exists between the minimal field widths of RELiC's regressive exponents and corresponding counter values,
	which allows them both to be serialized as singular points in a compressed a truth vector. eliminating a tree-like addressing scheme.
	

	Embedded in the freed-up bit depth of each layer are counter values which, when traced and summed, give non-sparse z-index.
	This strikes a balance between the evil of O(n) complexity at both extremes of pre/post computation in O( log(n) ) time.
	Since the required bit depth of each counter scales inversely to the regression level of each respective index for each layer,
	these two sets of values are able to be serialized and stored in the same locations, avoiding any additional address-related overhead.

	Given a saturated 64-bit namespace and an octal base exponent, this results in (21) layers, each 1/8th the size of the last.
	The final layer is quantized down to a single entry, which gives the logical length of the truth vector, as if decompressed.

	*/

/*	ARCHITECTURE

	ICE encodes a pair of unsigned quads in a variable width format that occupies from 1 to 17 bytes in length (q).

	When there is ample free space following the target field, we can write these values using simplex assignments,
	but when we get within (3) bytes of the field boundary, there is a risk of accidentally clobbering several bytes past the end in this way.
	Depending on q, we may have to break the operation up into (2) or (3) assignments, using right-bitshift and casts.

	The dichotomy of a RELiC object is a 2D AV* array of SV* "cubes", where:

	>	Each SV* "cube" is labeled by an "Epsilon" value which represents the upper limit for the range of sorted keys contained within.
	>	Each SV* "cube" can vary in length from (16..144) bytes, containing up to (8) flag inversion boundary pairs known as "cycla".
	>	Each "cyclum" can vary in length from (1..17) byte[s], using a single "keybyte" to define a pair of ULLs (A, B) as variable fields.
		>	If either A or B is less-than 8, its value is stored in the keybyte and its variable field is omitted;
		>	If both A and B are less-than 8, their values are both stored in the keybyte for maximum compression at full NS saturation.

	>	Cycla chain together to form a vector path which stores the exzations of the NS as alternating ranges of un/defined keys.

	That last point is arguably the most significant, because IC-RLE encoding used in this way exhibits hyperbolic time complexity—
	the nearest approach to the asymptote occurs at around 60% capacity, after which point time drops back down to the initial value.
	This behavior is due to parametric representation, where memory is consumed more by sparsity than logical content.
	ICE encoding is leveraged to maximize compression in the saturation state by compressing the smallest (A, B) pairs into a single byte.
	At this granular level, this is the most probable case when data is highly entropic and saturation reaches an equilibrium state.

	*/

/*	NOTES
	We have a library of switch statements to surgically cast specific byte lengths of data into tight spaces.
	It is not always necessary to use such precision— most of the time, there is ample space ahead, but in order to prevent overrun,
	casting must be handled intelligently in certain cases (particulary for variable-field-length: 5, within (3) bytes of the end).
	These switches write to variable-length fields in the fewest statements possible within the explicit overrun tolerance.
	They are generated by the following perl scripts:

		> gen_c_for__lluiCASTa.pl
		> gen_c_for__lluiCASTab.pl
		> gen_c_for__lluiCASTabc.pl		*unused
		> gen_c_for__lluiCASTabcd.pl		*uused
		> gen_c_for__lluiCASThab.pl
		> gen_c_for__qCAST_t[0123].h.pl	*the numbers 0, 1, 2, and 3 specify the overrun tolerance
		> gen_c_for__qREAD.h.pl
		> gen_c_for__qREADrev.h.pl

	E.g.:
	In order to copy an unsigned LLU into a field fit for the significant bytes only, it will require one of the following combinations of casts:
	
		> a single assignment cast as a char, short, long, or long long			(1, 2, 4, or 8 bytes)
		> two assignments cast as:	» (short) x;	(char) x>>16				(3 bytes)
								» (long) x;	(char) x>>32				(5 bytes)
								» (long) x;	(short) x>>32				(6 bytes)
		> three assignments cast as:	 (long) x;  	(short) x>>32;	(char) x>>48	(7 bytes)




	THREE PHASES OF NAMESPACE DEPLETION
	Expansion:	When the namespace is mostly free,	entropic inclusions tend to generate cycla,	complexifying the graph.
	Saturation: 	When the namespace is about 60/40,	entropic inclusions have no overt tendency;	complexity plateaus.
	Contraction: 	When the namespace is mostly used,	entropic inclusions tend to integrate cycla,	simplifying the graph.

	*/


#define	zcOf( $a)	7-( 	__builtin_clzll( $a)	>>3)
#define	ncOf( $a)	8-( 	__builtin_clzll( $a)	>>3)


#define	CUBE_(	$iC )   									SvPVbyte( *( AvARRAY( avICE) +$iC ), CSZ	)
#define	CUBE(	$iC )   									SvPVbyte( *( AvARRAY( avICE) +$iC ), CS	)
#define	CUBEvc(	$iC )(  		__builtin_clzll( *( (ui64*) (	cube =	SvPVbyte( *( AvARRAY( avICE) +$iC ), CS	) ) +1 ) )	>>3)


		HV	*	hvICE,
			*	hvArg,
			*	hvOut;
		AV	*	avOut,
			*	avDBUG;	long long int	zd;
		AV	*	avICE;		long long int	iC, iC0, iCZ, iCx, post_C, zC, zzC, post_zC, rel_iC, less_iC;  	//	iC is the index of the current cube.  zC is the array index of the ending cube.
		AV	*	avICE_;		long long int	zC_=-1;
		AV	*	avArg;		long long int	a, za; 					//	a list of integer value[s] to operate on.
		SV	*	rvOut,				/*	arrayref to AV* avOut									*/
			*	rvArg,				/*	arrayref to AV* avArg									*/
			*	rvICE,				/*	arrayref to AV* avICE									*/
			*	rvICE_;				/*	arrayref to AV* avICE_									*/

SV			**	src,
			**	dst,
			**	pSv0,
			
			*	svA,					/*	general purpose scratch SV								*/
			*	svLbf,				/*	lower cube fragment									*/
			*	svZ,	 				/*	SV containing right-hand cube data	(upper fragment)		*/
			*	sv,					/*	SV containing pre-rack cube data		(original pre-op cube)	*/
			*	sv0;					/*	SV containing left-hand cube data		(lower fragment)		*/
ui08			*	cube	=NULL,		/*	unsigned char * cube data (of index iC )					*/
			*	cubeZ	=NULL,		/*	unsigned char * cube data (of index iC -1)					*/
			*	qube;
char			*	lightning = "\n!! !  !   !    !     !      !       !        !         !          !           !            !             !              !               !                !\n",
				aString[8448],
			*	ps;
bool				L=0,
				R=1;
STRLEN			cS, CS, CSZ;
ui08				*pk,		*pq,
			/*	*pkz, */	*pqz,
				*pk_,	*pq_,	
			/*	*pkx, */	*pqx,
				buf[	8 	+8	+8*16	+1	+15 ];	/*	buffers the output of ICE() and its variants
/*	CUBE STRUCT:	^	^	^		^	^ overflow padding (to survive an overshot "long long" cast)
					|	|	|		NULL byte
					|	|	up to 128 bytes of variable "q-data"
					|	"Epsilon" is the cube's search key.  It signifies the upper boundary of encoded keys within the cube.
					keybyte area stores up to (8) keybytes, which define variable "q-data" geometry for up to (8) inversion run cycla.
					*/

/*	standard global constant cube initialization templates 	*/
/*			"cube_i0" is used to initialize a cube which should start with element #0 set.						*/
const ui08	cube_i0[	16]={	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x08,		/* cyclum #0:	x==0			*/
							0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	1		};	/* Epsilon:	1				*/

/*			"nube" is used to initialize an empty cube, or as a global null value to set pointers to directly.			*/
const ui08	nube[	16]={	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,		/* no content					*/
							0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00	};	/* Epsilon:	0				*/

/*			"cubE" is a global constant object used to failsafe RELiC accessors against potential overrun by iCE() and its variants.
			It contains a single null point at the max int, bounding the 64-bit namespace.					*/
const ui08	cubE[	24]={	0xB8,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,		/* cyclum #7:	x==null			*/
							0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,		/* Epsilon:	2^64-1 (max uint)	*/
							0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF	};	/* A: 		2^64-1 (max uint)	*/


ui64			i, ub, lb, n, N, o, s;		/*	global scratch variables used in private contexts									*/
ui64			x, y, z,				/*	common arguments														*/
			skip, hit, miss,			/*	the number of misses or collissions counted as a method processes arguments  		*/
			hu, bu, hm, lm; 	 	/*	high-unit, base-unit, high-mask, low-mask:
									used to quantize keys for each unitary digit of numeric base (BASEBITS).		 		*/
ui08			f,					/*	A-B encoding flags, just the first (2) bits of the keybyte isolated						*/
			ab,					/*	A-B encoding parameters, the last (6) bits of the keybyte isolated; a pair of octal values	*/
			lost_ic;				/*	a number of cycla consolidated into a single cyclum due to having null B-value			*/
ui64			Kx8, Kx8_, _Kx8,		/*	an actual array of (8) octets, but cast as an unsigned quad, simply to use bitwise ops	*/
			Qx7;

//in general, a variable preceded by an underscore is vigilantly kept up-to-date, so to represent a value in a post-op state.
//matrix indeces will not be negative
/*						____	object______________________	verb_________	subject_____________________	preposition______________________	*/
char unsigned u, v, w,			/*	matrix indeces			iterate		the modification range		in	matrix { A[], B[], E[], Q[] }	*/
	en_1,	enZ1,	ex_z,	/*	matrix indeces			mark in/out	endogenous fragment[s]	in	matrix { A[], B[], E[], Q[] }	*/
	ix0, ixZ,	ixN; 			/*	matrix indeces			mark in/out	the modification range		in	matrix { A[], B[], E[], Q[] }	*/
ui08			HiQ[]={0,0,0,0};	/*	q-data offsets delimit (4) levels of multi-stage casting as write loop grades precision up approaching end of fragment run	*/
char unsigned	q0,	q1,	q2,	q3,	/*	q-field lengths			total		the q-data length			of any given cyclum			*/
			q,	q_,	qx,		/*	q-data length			defines 		the read size  increment		in	char *	cube / cubeZ		*/
			oq,	oq_,	oqx,		/*	q-data offset			iterates		the read position			in	char *	cube / cubeZ / buf	*/

			oq0,	oqZ, oqN;	/*	q-data offsets 		mark in/out	the destination range		in	char *	cube			*/
char			ic, 				/*	cyclum index			iterates		the read position			in	char *	cube			*/
			ic0,	icZ,	icN,		/*	cyclum indeces		mark in/out	the destination range		in	char *	cube			*/
			icF,		
			zc,	zcZ,			/*	cyclum index 			identifies		the zeta cyclum			of	char *	cube / cubeZ		*/
			tena_zc,			/*	cyclum index			identifies		the tentative zeta cyclum	of	char *	cube			*/
			vc,	vc_;			/*	cyclum count			defines		vacant capacity available	in	char *	cube / cubeZ		*/
AV			*avOut;
SV			*svOp;
svtype		svt;
long long int	displacement, d, D;

char *	opStat[]={"null", "ok", "mod", "new" };
enum	opStat{	null, ok, mod, new }
/*		THE MATRIX					*/
		RW[	256 ];					/* read/write status enumerator			*/

ui64		A[	256 ],	Au,	Av,	Ac,		/* relative coord.s	which define	each negative cyclum phase	in	matrix { A[], B[], E[], Q[] }	*/
		B[	256 ],	Bu,	Bv,	Bc,		/* relative coord.s	which define	each positive cyclum phase	in	matrix { A[], B[], E[], Q[] }	*/
		E[	256 ],	Eu,	Ev,	Ec,	E_,	/* "Epsilon" values	which bound	the absolute coordinates	in	matrix { A[], B[], E[], Q[] }	*/
		ZC[	256 ];					/* cube lengths, pre-re-fragmentation  	*/
ui08 	I[	256 ],					/* cycla indeces	which align	pre/post op keybytes		in	char *	cube			*/
		H[	256 ],					/* header codes	which ex_z.	q-data field space			in	char *	cube			*/
	*	Qp[	256 ],
		Q[	256 ], 	Qu,	Qv,	Qc,		/* q-data lengths	which define	each read increment		in	char *	cube			*/
		Qx[	256 ],					/* q-data lengths	which define	each write increment		in	char *	cube			*/
		O[	256 ],					/* q-data offsets	which mark	each read position			in	char *	cube			*/
		Ox[	256 ];					/* q-data offsets	which mark	each write position			in	char *	cube			*/
	
// array resequencing buffer matrix
	SV		*	rSeq_SV[	256 ]; 	// temporary holding of SV* cubes pending insertion into AV* avICE
	long long int	rSeq_iR[	256	], iR,	// source index of rSeq_SV 				(for each control point)
				rSeqIns[	256	],	// the number of trailing SVs to insert		(for each control point)
				rSeqCut[	256	],	// the number of leading SVs to remove 	(for each control point)
				rSeqSrc[	256	],	// source index						(for each control point)
				rSeqDst[	256	],	// destination index						(for each control point)
				rel_zC, 	dsc,  asc, zsc, dial, jmp,
				rack_iC	=0;		// running control point iterator

#define	ARG( $a )	SvIVX( svA=*(	AvARRAY(	avArg)+ $a	) )
#define	ARG0		SvIVX( svA=*	AvARRAY(	avArg)		)

#define	zcOf( $a)	7-( 	__builtin_clzll( $a)	>>3)
#define	ncOf( $a)	8-( 	__builtin_clzll( $a)	>>3)

const char	*	fmtLLU[	24	] ={
				NULL,	" %c%-1llu ",	" %c%-2llu ",	" %c%-3llu ",	" %c%-4llu ",	" %c%-5llu ",	" %c%-6llu ",	" %c%-7llu ",
						" %c%-8llu ",	" %c%-9llu ",	" %c%-10llu ",	" %c%-11llu ",	" %c%-12llu ",	" %c%-13llu ",	" %c%-14llu ",
						" %c%-15llu ",	" %c%-16llu ",	" %c%-17llu ",	" %c%-18llu ",	" %c%-19llu ",	" %c%-20llu ",	" %c%-21llu ",
						" %c%-22llu ",	" %c%-23llu "	},
			*	fmt02X[	24	] ={
				NULL,	" %c%01X ",					" %c%02X ",				" %c%02X  ",			" %c%02X   ",			" %c%02X   ",			" %c%02X     ",		" %c%02X      ",
						" %c%02X       ",				" %c%02X        ",			" %c%02X         ",		" %c%02X          ",		" %c%02X          ",		" %c%02X            ",		" %c%02X             ",
						" %c%02X              ",			" %c%02X               ",		" %c%02X                ",	" %c%02X                 ",	" %c%02X                 ",	" %c%02X                   ",	" %c%02X                    ",
						" %c%02X                     ",		" %c%02X                      "	},
			*	fmtStr[	24	] ={
				NULL,	" %-1s ",		" %-2s ",		" %-3s ",		" %-4s ",		" %-5s ",		" %-6s ",		" %-7s ",
						" %-8s ",		" %-9s ",		" %-10s ",	" %-11s ",	" %-12s ",	" %-13s ",	" %-14s ",
						" %-15s ",	" %-16s ",	" %-17s ",	" %-18s ",	" %-19s ",	" %-20s ",	" %-21s ",
						" %-22s ",	" %-23s "	},
			*	fmtChr[	24	] ={
				NULL,	" %-1c ",		" %-2c ",		" %-3c ",		" %-4c ",		" %-5c ",		" %-6c ",		" %-7c ",
						" %-8c ",		" %-9c ",		" %-10c ",	" %-11c ",	" %-12c ",	" %-13c ",	" %-14c ",
						" %-15c ",	" %-16c ",	" %-17c ",	" %-18c ",	" %-19c ",	" %-20c ",	" %-21c ",
						" %-22c ",	" %-23c "	},
			*	fmtStrNl[	24	] ={
				" \r\n",	" \r\n%1s ",	" \r\n%2s ",	" \r\n%3s ",	" \r\n%4s ",	" \r\n%5s ",	" \r\n%6s ",	" \r\n%7s ",
						" \r\n%8s ",	" \r\n%9s ",	" \r\n%10s ",	" \r\n%11s ",	" \r\n%12s ",	" \r\n%13s ",	" \r\n%14s ",
						" \r\n%15s ",	" \r\n%16s ",	" \r\n%17s ",	" \r\n%18s ",	" \r\n%19s ",	" \r\n%20s ",	" \r\n%21s ",
						" \r\n%22s ",	" \r\n%23s "	};

void _icepack_init(){	printf("—vUry cold\n\n");
#if	defined( DEBUG )
	avDBUG=newAV();
	printf("\n	Debug options are set.  From perl, call \"getAvDBUG()\" or \"printAvDBUG()\" to access audit data.\n", __FILE__);
#endif
#if defined(DEBUG_RACK_L1)
	printf("\r	DEBUG_RACK_L1 is defined in %s:	auditing nominal activity within _rack1x()\n", __FILE__);
#endif
#if defined(DEBUG_RACK_L2)
	printf("\r	DEBUG_RACK_L2 is defined in %s:	auditing verbose activity within _rack1x()\n", __FILE__);
#endif
#if defined(DEBUG_RACK_L3)
	printf("\r	DEBUG_RACK_L3 is defined in %s:	checking integrity within _rack1x()\n", __FILE__);
#endif
#if defined(DEBUG_SET_L3)
	printf("\r	DEBUG_SET_L3 is defined in %s:	checking integrity within ICE::set(...)\n", __FILE__);
#endif
#if defined(DEBUG_ReSEQ_L1)
	printf("\r	DEBUG_ReSEQ_L1 is defined in %s:	auditing nominal activity within _av_commit(), AvPOST, AvCUT, and AvCUT_B4\n", __FILE__);
#endif
#if defined(DEBUG_ReSEQ_L2)
	printf("\r	DEBUG_ReSEQ_L2 is defined in %s:	auditing verbose activity within _av_commit() \n", __FILE__);
#endif
#if defined(DEBUG_ReSEQ_L3)
	printf("\r	DEBUG_ReSEQ_L3 is defined in %s:	checking integrity within _av_commit()\n", __FILE__);
#endif
#if defined(DEBUG_SET_L1)
	printf("\r	DEBUG_SET_L1 is defined in %s:	auditing nominal activity within _set8x() and _set9up()\n", __FILE__);
#endif
#if defined(DEBUG_SET_L2)
	printf("\r	DEBUG_SET_L2 is defined in %s:	auditing verbose activity within _set8x() and _set9up()\n", __FILE__);
#endif
#if defined(DEBUG_SET_L3)
	printf("\r	DEBUG_SET_L3 is defined in %s:	checking integrity within _set8x() and _set9up()\n", __FILE__);
#endif

	hvICE		= gv_stashpv(	"ICEPack",			0);
	avOut		= get_av(		"ICEPack::avOut",		GV_ADD);
	A[	255 ]=255;
	B[	255 ]=255;
	O[	255 ]=16;
	Ox[	255 ]= 0;
	Q[	255 ]= 0;
	*( (ui64*) H )	= 0;
	u=v=w=255;
	int x;
	for( x=0; x<128; ++x){
		RW[x]=null;
		rSeq_iR[	x ]=-1;
		rSeqIns[	x ]=0;
		rSeqCut[	x ]=0;
		rSeqSrc[ 	x ]=0;
		rSeqDst[	x ]=0;
		rSeq_SV[	x ]=NULL;
	}	}

#ifdef DEBUG
void	_print_mx( unsigned char mx_max){
	if( mx_max >32 ){	printf("\r!_print_mx( unsigned char mx_max ): mx_max cannot exceed 32 (it is %d).\n", mx_max ); return; }
	const char	*	label[ ]	= {"H:", "A:", "B:", "E-1:", "I:", "O:", "Ox:", "Q:", "Qx:",  "stat:", "range:"},
					labelC	= sizeof( label ) / sizeof( label[0] ),
				*	csUVW	="|uvw|",
				*	csUV	="|uv|",
				*	csUW	="|wu|",
				*	csVW	="|vw|",
				*	csU		="|u|",
				*	csV		="|v|",
				*	csW		="|w|";
	SV		*sv;
	ui08				x, c=1;
	char				r=0,
			*ptxt,	txt[	8960	]={13, 10},	// max ex_z for 32-vector display: 8,753
					lblCell	=	1,
					cell[	255	]={	};	// abs max cell size = 19 decade digits +2 sign characters = 21 bytes
	STRLEN		p,	pos[	255	],
				i,	rowLen, txtLen;

	for( r = labelC-1; r >=0; --r )	{	s = strlen( label[ r ] );
							if(	s > lblCell ) lblCell = s;	
							}					p = lblCell;

	for( x=255; x!=mx_max; ++x ){			pos	[ x ] = p;
		s =1 + (char) ceil( log10l( (long double)	H  	[ x ]		) );				cell[ c ]= s>5? s: 5; //min cell width 5 accounting for "stat" enumerator
		s =1 + (char) ceil( log10l( (long double)	A  	[ x ]		) );	if( s >cell[ c ] )	cell[ c ]=s;
		s =1 + (char) ceil( log10l( (long double)	B  	[ x ]		) );	if( s >cell[ c ] )	cell[ c ]=s;
		s =1 + (char) ceil( log10l( (long double)	E  	[ x ]-1	) );	if( s >cell[ c ] )	cell[ c ]=s;
		s =1 + (char) ceil( log10l( (long double)	I  	[ x ]		) );	if( s >cell[ c ] )	cell[ c ]=s;
		s =1 + (char) ceil( log10l( (long double)	O  	[ x ]		) );	if( s >cell[ c ] )	cell[ c ]=s;
		s =1 + (char) ceil( log10l( (long double)	Ox  	[ x ]		) );	if( s >cell[ c ] )	cell[ c ]=s;
		s =1 + (char) ceil( log10l( (long double)	Q  	[ x ]		) );	if( s >cell[ c ] )	cell[ c ]=s;
		s =1 + (char) ceil( log10l( (long double)	Qx  	[ x ]		) );	if( s >cell[ c ] )	cell[ c ]=s;
		p += cell[ c ]+2;	++c;
		}

	for( rowLen = p; x< 255; ++x )	pos[x] =p;	// positioning markers beyond mx_max puts them where they'll get overwritten
	txtLen = ( (	rowLen	+1	)	*	(	labelC	+2 )		+4	+labelC );
	//			^		^		^		^		^		^	^plus this... why?  I really don't know
	//			|		|		|		|		|		plus (4) add'l newlines at end of output
	//			|		|		|		|		... number of cursor rows )
	//			|		|		|		(number of matrix rows, plus...
	//			|		|		multipled by number of rows
	//			|		plus (1) newline per row
	//			length of each row
//	printf("\n calculated output: ( %d +1) * ( %d+2 ) +1 +%d = %llu\n", rowLen, labelC, labelC<<1, txtLen );
	if( txtLen >sizeof( txt ) ){
		printf("_print_mx(): (char *) txt exzation not big enough!  need %llu bytes, have %llu", txtLen, sizeof( txt ) );
		return;
		}
/* whitespace backdrop		*/	for( i=0; i< rowLen;  i+=8 )		*( (ui64*)( txt +i ) ) = 0x2020202020202020;
/*1: u,v,w 	*/
	if( u==v)	if(	u==w )	{	sprintf( txt +pos[u], csUVW  	);	*( txt+pos[u]+5 )=0x20;
				}else	{	sprintf( txt +pos[v], csUV 	);	*( txt+pos[v]+4 )=0x20;
							sprintf( txt +pos[w], csW  	);	*( txt+pos[w]+3 )=0x20;
						}	
	else if(		u==w )	{	sprintf( txt +pos[u], csUW 	);	*( txt+pos[u]+4 )=0x20;
							sprintf( txt +pos[v], csV  	);	*( txt+pos[v]+3 )=0x20;
	}else{					sprintf( txt +pos[u], csU  	);	*( txt+pos[u]+3 )=0x20;
			if(	v==w )	{	sprintf( txt +pos[v], csVW 	);	*( txt+pos[v]+4 )=0x20;
			}else		{	sprintf( txt +pos[v], csV  	);	*( txt+pos[v]+3 )=0x20;
							sprintf( txt +pos[w], csW  	);	*( txt+pos[w]+3 )=0x20;
		}				}																	txt[p++]=10;
/*2: numbers	*/
	ptxt=txt+p;			for( i=0; i< rowLen;  i+=8 )			*( (ui64*)( ptxt+i ) ) = 0x5F5F5F5F5F5F5F5F;
						for( x=255 ; x!=24; ++x ){ 			*(ptxt+pos[x]+sprintf( ptxt+pos[x], "#%llu", x ) )=0x5F;		}
	p+=rowLen;
/*3: H		*/						sprintf( txt +p, fmtStrNl[	lblCell ],    label[++r]		);	p+= lblCell+3;
	c=1;	for( x=255; x!=mx_max; ++x ){	sprintf( txt +p, fmt02X[	cell[ c ] ], 120,	H[	x ]		);	p+= cell[ c++ ]+2;	}
/*4: A		*/						sprintf( txt +p, fmtStrNl[	lblCell ],    label[++r]		);	p+= lblCell+3;
	c=1;	for( x=255; x!=mx_max; ++x ){	sprintf( txt +p, fmtLLU[	cell[ c ] ], 45, 	A[	x ]		);	p+= cell[ c++ ]+2;	}
/*5: B		*/						sprintf( txt +p, fmtStrNl[	lblCell ],    label[++r]		);	p+= lblCell+3;
	c=1;	for( x=255; x!=mx_max; ++x ){	sprintf( txt +p, fmtLLU[	cell[ c ] ], 43, 	B[	x ]		);	p+= cell[ c++ ]+2;	}
/*6: E-1		*/						sprintf( txt +p, fmtStrNl[	lblCell ],    label[++r]		);	p+= lblCell+3;
	c=1;	for( x=255; x!=mx_max; ++x ){	sprintf( txt +p, fmtLLU[	cell[ c ] ], 90, 	E[	x ]-1	);	p+= cell[ c++ ]+2;	}
/*7: I		*/						sprintf( txt +p, fmtStrNl[	lblCell ],    label[++r]		);	p+= lblCell+3;
	c=1;	for( x=255; x!=mx_max; ++x ){	sprintf( txt +p, fmtLLU[	cell[ c ] ], 35, 	I[	x ]		);	p+= cell[ c++ ]+2;	}
/*8: O		*/						sprintf( txt +p, fmtStrNl[	lblCell ],    label[++r]		);	p+= lblCell+3;
	c=1;	for( x=255; x!=mx_max; ++x ){	sprintf( txt +p, fmtLLU[	cell[ c ] ], 46, 	O[	x ]		);	p+= cell[ c++ ]+2;	}
/*9: Ox		*/						sprintf( txt +p, fmtStrNl[	lblCell ],    label[++r]		);	p+= lblCell+3;
	c=1;	for( x=255; x!=mx_max; ++x ){	sprintf( txt +p, fmtLLU[	cell[ c ] ], 44, 	Ox[	x ]		);	p+= cell[ c++ ]+2;	}
/*10: Q		*/						sprintf( txt +p, fmtStrNl[	lblCell ],    label[++r]		);	p+= lblCell+3;
	c=1;	for( x=255; x!=mx_max; ++x ){	sprintf( txt +p, fmtLLU[	cell[ c ] ], 196,	Q[	x ]		);	p+= cell[ c++ ]+2;	}
/*11: Qx		*/						sprintf( txt +p, fmtStrNl[	lblCell ],    label[++r]		);	p+= lblCell+3;
	c=1;	for( x=255; x!=mx_max; ++x ){	sprintf( txt +p, fmtLLU[	cell[ c ] ], 205,	Qx[	x ]		);	p+= cell[ c++ ]+2;	}
/*12: stat	*/						sprintf( txt +p, fmtStrNl[	lblCell ],    label[++r]		);	p+= lblCell+3;
	c=1;	for( x=255; x!=mx_max; ++x ){	sprintf( txt +p, fmtStr[	cell[ c ] ],	RW[x]&0xF8? "...": opStat[ RW[ x ] ] );	p+= cell[ c++ ]+2;	}
/*13: range	*/	ptxt=txt+p;		i=	sprintf( txt +p, fmtStrNl[	lblCell ],    label[++r]		);	//p+= lblCell+3;
/* whitespace backdrop		*/	for(	; i< rowLen;  i+=8 )			*( (ui64*)( ptxt +i ) ) = 0x2020202020202020;
	ptxt+=4;
										ptxt[ pos[ ix0	]	]=192;	//lower-right corner
										ptxt[ pos[ ixZ	]+2	]=217;	//lower-left corner
	if( en_1==enZ1 ){						ptxt[ pos[ en_1	]+1	]=186;	//double vertical bar
				if(	ix0==ixZ
				&&	ix0!=en_1 )			ptxt[ pos[ ix0		]+1	]=196;	//horizontal bar
	}else		{						ptxt[ pos[ en_1	]+1	]=195;	//left-side tee
										ptxt[ pos[ enZ1	]+1	]=180;	//right-side tee
				if(	ix0==ixZ
				&&	ix0!=en_1 && ix0 !=enZ1 )	ptxt[ pos[ ix0	]+1	]=196;	//horizontal bar
				}
	p+=rowLen;	*( (ui64*) (txt+p) )=0x000A0A0A0A0A0A0A;	p+=7;		//(7) newlines and (1) NUL
//	else	sprintf( ptxt,	"[not marked]\n\n"	);
//	printf("\nactual output:	%lld byte[s]\n\n", p );
	AvPUSHaSTRING(txt, p);
	}
void _init_mx(){					/*	totally zero-out buffer matrix to improve clarity of debug info	*/
	ui08	x=255;	tena_zc=-1;

	u= v= w= en_1 =ixZ =0;	ix0=0xFF;
	do{	RW[x]=0;
		A[x]=	B[x]=	E[x]=	0;
		H[x]=	Q[x]=	Qx[x]=
		I[x]=		O[x]=	Ox[x]=	0;
		} while( ++x != 255 );
	Qx[255]=0;
	}
#else
void _print_mx( unsigned char mx_max){	printf("!	_print_mx(...) called w/o debugging implemented by preprocessor\n");	}
void _init_mx( ){						printf("!	_init_mx() called w/o debugging implemented by preprocessor\n");		}
#endif

void deIceV_KE(){	DeICEv_KE(	u, v );	}
void deIceV_KEI(){	DeICEv_KEI(	u, v );	}


void _rackXx(){	printf("\r!	_rackXx() is not implemented!\n"); }
void _av_commit(){	/* 	does batch splice on avICE, swapping new/old fragments. */

/*	word up: the algorithmic action of compaction and expansion is charicterized by peristalsis—
	a directed, sequential wave of movement where the order of units matters structurally,
	not just for performance.

	When you're moving overlapping regions of the same buffer, the direction of iteration isn't a choice; it's a necessity.
	Move forward during compaction, backward during expansion, or you corrupt unread source data.
	That iterative directionality is the operation's defining constraint, and it's what makes it fundamentally different
	from a simple copy or memcpy.

	*/
	long long int	asc, zsc, dial, jmp;
	
	#ifdef DEBUG_ReSEQ_L2		//	verbose audit of nominal activity	
		long long int iRz;
		#define dBUGiniA		cS=sprintf( aString, "\n starting in ascending mode at step #%lld/%lld for %lld iterations\n\n",   	asc, zsc, dial);		AvPUSHaSTRING( aString, cS );
		#define dBUGiniD		cS=sprintf( aString, "\n starting in descending mode at step #%lld/%lld for %lld iterations\n\n", 	dsc, zsc, dial);		AvPUSHaSTRING( aString, cS );

		#define dBUGriniA		cS=sprintf( aString, "\n switching to ascending mode at step #%lld/%lld for %lld iterations\n\n",	asc, zsc, dial	);	AvPUSHaSTRING( aString, cS );
		#define dBUGriniD		cS=sprintf( aString, "\n switching to descending mode at step #%lld/%lld for %lld iterations\n\n",	dsc, zsc, dial	);	AvPUSHaSTRING( aString, cS );

		#define dBUGinsA  		if( $insA >1) printf("\n!	rSeq_ins[ asc ] >1: %d\n", $insA );	\
								cS=sprintf( aString, "\r+I+	avICE[ %4lld ]	= SV%-4lld			asc: %lld/%lld	dial: %lld	src/dst: %lld/%lld\n",				dst-pSv0-1, 	rSeq_iR[asc]-$insA, 	asc,	zsc, dial, src-pSv0, dst-pSv0 ); 	AvPUSHaSTRING( aString, cS );
		#define dBUGcutA  		cS=sprintf( aString, "\r-X-	avICE[ %4lld ]	= NULL				asc: %lld/%lld	dial: %lld	src/dst: %lld/%lld\n",				src-pSv0, 				  		asc,	zsc, dial, src-pSv0, dst-pSv0 );	AvPUSHaSTRING( aString, cS );
		#define dBUGjmpA  		cS=sprintf( aString, "\r%c%c_	avICE[ %4lld ]	=	avICE[ %4lld ];		asc: %lld/%lld	dial: %lld	src/dst: %lld/%lld\n",	174,174, 		dst-pSv0-1, 		src-pSv0-1,	  	asc,	zsc, dial, src-pSv0, dst-pSv0 );	AvPUSHaSTRING( aString, cS );
		#define dBUGlocA  		cS=sprintf( aString, "\r|%c%c	avICE[ %4lld ]	=	avICE[ %4lld ]; [T]	asc: %lld/%lld	dial: %lld	src/dst: %lld/%lld\n",	174,174,		dst-pSv0, 		$srcA,  			asc,	zsc, dial, src-pSv0, dst-pSv0 );	AvPUSHaSTRING( aString, cS );

		#define dBUGinsD  		if( $insD >1) printf("\n!	rSeq_ins[ dsc ] >1: %d\n", $insD );	\
								cS=sprintf( aString, "\r+I+	avICE[ %4d ]	= SV%-4d			dsc: %lld/%lld	dial: %lld	src/dst: %lld/%lld\n",			1+	dst-pSv0,	rSeq_iR[dsc]+1,	 	dsc,	zsc, dial, src-pSv0, dst-pSv0);  	AvPUSHaSTRING( aString, cS );
		#define dBUGcutD  		cS=sprintf( aString, "\r-X-	avICE[ %4d ]	= NULL				dsc: %lld/%lld	dial: %lld	src/dst: %lld/%lld\n",				src-pSv0,							dsc,	zsc, dial, src-pSv0, dst-pSv0);		AvPUSHaSTRING( aString, cS );
		#define dBUGjmpD  		cS=sprintf( aString, "\r_%c%c	avICE[ %4d ]	=	avICE[ %4d ];		dsc: %lld/%lld	dial: %lld	src/dst: %lld/%lld\n",	175,175,	1+	dst-pSv0,	1+	src-pSv0,  		dsc,	zsc, dial, src-pSv0, dst-pSv0);		AvPUSHaSTRING( aString, cS );
		#define dBUGlocD  		cS=sprintf( aString, "\r%c%c|	avICE[ %4d ]	=	avICE[ %4d ]; [T]	dsc: %lld/%lld	dial: %lld	src/dst: %lld/%lld\n",	175,175,		dst-pSv0, 		$srcD,  			dsc,	zsc, dial, src-pSv0, dst-pSv0);		AvPUSHaSTRING( aString, cS );
		#define dBUGlocDx		cS=sprintf( aString, "\r_%c|	avICE[ %4d ]	=	avICE[ %4d ]; [Tx]	dsc: %lld/%lld	\n", 							175,			$dstD, 			$srcD,			dsc,	zsc						);	AvPUSHaSTRING( aString, cS );
		#define dBUGjmpDxA		cS=sprintf( aString, "\r__%c	avICE[ %4d ]	=	avICE[ %4d ];		dsc: %lld/%lld	dial: %lld	src/dst: %lld/%lld\n",	175, 	1+	dst-pSv0,	1+	src-pSv0,  		dsc,	zsc, dial, src-pSv0, dst-pSv0);		AvPUSHaSTRING( aString, cS );

		#define dBUG_ReSEQ_SCHED_PRE\
			cS =sprintf( aString,     "\n	racking schedule (pre process):\n	#\t\t");														\
													for( iRz=0; iRz<=7; ++iRz )	cS+=sprintf( aString +cS, "#%-7lld", 			iRz ); 	\
			cS+=sprintf( aString +cS, "\n	rSeq_iR:\t"	);	for( iRz=0; iRz<=7; ++iRz )	cS+=sprintf( aString +cS, " %-7lld",	rSeq_iR[ 	iRz ]	);	\
			cS+=sprintf( aString +cS, "\n	rSeqIns:\t"	);	for( iRz=0; iRz<=7; ++iRz )	cS+=sprintf( aString +cS, " %-7lld",	rSeqIns[ 	iRz ]	);	\
			cS+=sprintf( aString +cS, "\n	rSeqCut:\t"	);	for( iRz=0; iRz<=7; ++iRz )	cS+=sprintf( aString +cS, " %-7lld",	rSeqCut[	iRz ]	);	\
			cS+=sprintf( aString +cS, "\n	rSeqSrc:\t"	);	for( iRz=0; iRz<=7; ++iRz )	cS+=sprintf( aString +cS, " %-7lld",	rSeqSrc[	iRz ]	);	\
			cS+=sprintf( aString +cS, "\n	rSeqDst:\t"	);	for( iRz=0; iRz<=7; ++iRz )	cS+=sprintf( aString +cS, " %-7lld",	rSeqDst[	iRz ]	);	\
			cS+=sprintf( aString +cS, "\n\n");				AvPUSHaSTRING( aString, cS );

		#define dBUG_ReSEQ_SCHED_POST	\
			cS =sprintf( aString,    	"\n	racking schedule (post process):\n	#\t\t");											\
													for( iRz=0; iRz<=7; ++iRz ) cS+=sprintf( aString +cS, "#%-7lld", 			iRz );	\
			cS+=sprintf( aString +cS, "\n	rSeq_iR:\t"	);	for( iRz=0; iRz<=7; ++iRz ) cS+=sprintf( aString +cS, " %-7lld",	rSeq_iR[ 	iRz ]	);	\
			cS+=sprintf( aString +cS, "\n	rSeqIns:\t"	);	for( iRz=0; iRz<=7; ++iRz ) cS+=sprintf( aString +cS, " %-7lld",	rSeqIns[ 	iRz ]	);	\
			cS+=sprintf( aString +cS, "\n	rSeqCut:\t"	);	for( iRz=0; iRz<=7; ++iRz ) cS+=sprintf( aString +cS, " %-7lld",	rSeqCut[	iRz ]	);	\
			cS+=sprintf( aString +cS, "\n	rSeqSrc:\t"	);	for( iRz=0; iRz<=7; ++iRz ) cS+=sprintf( aString +cS, " %-7lld",	rSeqSrc[	iRz ]	);	\
			cS+=sprintf( aString +cS, "\n	rSeqDst:\t"	);	for( iRz=0; iRz<=7; ++iRz ) cS+=sprintf( aString +cS, " %-7lld",	rSeqDst[	iRz ]	);	\
			cS+=sprintf( aString +cS, "\n\n");				AvPUSHaSTRING( aString, cS );
	#else
		#define dBUGiniA
		#define dBUGiniD
		#define dBUGriniA
		#define dBUGriniD

		#define dBUGinsA
		#define dBUGcutA
		#define dBUGjmpA
		#define dBUGlocA
		#define dBUGinsD
		#define dBUGcutD
		#define dBUGjmpD
		#define dBUGlocD
		#define dBUGlocDx
		#define dBUGjmpDxA
		#define dBUG_ReSEQ_SCHED_PRE
		#define dBUG_ReSEQ_SCHED_POST
	#endif
	#ifdef DEBUG_ReSEQ_L3		//	paranoid integrity checks which are silent until there's a problem
		#define dBUGdsc		if(dsc<0 || dsc>zsc)		cS=sprintf( aString,		"\n!	dsc is out of bounds 0..%lld (%lld)\n", zsc, dsc);		AvPUSHaSTRING( aString, cS );\
							if(src >dst )	{		cS=sprintf( aString,		"\n!	going in the wrong direction for ReSEQ_DESCEND	src( %lld ) > dst( %lld ), step #%d/%d;	rSeqCut[%lld]: %d	rSeqSrc[%lld]: %d	rSeqDst[%lld]: %d\n",	\
																													src - pSv0, dst -pSv0,	dsc, zsc,		dsc, rSeqCut[dsc],	dsc, rSeqSrc[dsc],	dsc, rSeqDst[dsc]	);	AvPUSHaSTRING( aString, cS );	\
										}
		#define dBUGasc		if(asc<0 || asc>zsc)		cS=sprintf( aString, 	"\n!	asc is out of bounds 0..%lld (%lld)\n", zsc, asc);		AvPUSHaSTRING( aString, cS );\
							if(src< dst )	{		cS=sprintf( aString, 	"\n!	going in the wrong direction for ReSEQ_ASCEND    	src( %lld ) < dst( %lld ), step #%d/%d;	rSeqCut[%lld]: %d	rSeqSrc[%lld]: %d	rSeqDst[%lld]: %d\n", 	\
																													src - pSv0, dst -pSv0,	asc, zsc,		asc, rSeqCut[asc],	asc, rSeqSrc[asc],	asc, rSeqDst[asc]	);	AvPUSHaSTRING( aString, cS );	\
										}
		if( zC!= AvFILLp( avICE ) ){	zC = AvFILLp( avICE );	cS=sprintf( aString, 	"\n!	zC( %llu ) was out-of-sync with AvFILLp( avICE )( %llu )\n", zC, AvFILLp( avICE ) );	AvPUSHaSTRING( aString, cS );			}
		if(dsc<0){										cS=sprintf( aString, 	"\n!	dsc( %llu )< 0\n", dsc );													AvPUSHaSTRING( aString, cS );	return;	}
	#else
		#define dBUGdsc
		#define dBUGasc
	#endif
	
/*	TODO:	Reformulate zero-cross detection logic to occur earlier on the event-driven basis of the AvPOSTxxx macros,
			to eliminate (2) second-order nested loops in the critical path	*/
/*	NOTES:

	The "_av_commit()" function finalizes all deferred array splices without copying any shifted elements more than once.
	It is only called once per call to any public accessor method, after all encoding and fragmentation has been completed.

	The parameters of all deferred splices are aggregated and temporarily stored in these (4) global arrays:
		> rSeqSrc 	—the absolute index number of the operand element in the pre-operational array.
		> rSeqDst 	—the absolute index number of the operand element in the post-operational array.
		> rSeqIns 	—the number of elements to be inserted at destination index.
		> rSeqCut 	—the number of elements to be removed at source index.

	These (4) arrays align to form a 4x256 matrix.  They share two common iterators, (asc) and (dsc), which each represent 1x4 vectors.
	The matrix contains the relative offsets, lengths, and count parameters necessary to do multiple concurrent splices.
	It is populated left-to-right, but it is processed as a descending series of ascending and/or descending runs, right-to-left overall.
	As the running balance of elements in the pre-op vs post-op array can go positive or negative after any consecutive splice,
	the main loop is actually two main loops which flip-flop at those indeces where the running balance changes signs.
	The specific comparison which yields this sign is: (source index minus cut count) <=> (destination index pre-insertion).
	This offset alignment is due to the incongruency of reference index between cuts and inserts when they are first registered;
	both are determined only after the accessor's cursor has passed the reference index, but to-be-cut elements are already there,
	whereas to-be-inserted elements are not— therefore any one reference index leads its cuts and trails its inserts.

	Prior to getting here, the population of the matrix is event-based; simplex "insert" and "cut" ops are aggregated into "steps".
	Each step outlines a triad of insert/cut/shift runs which represent a single splice operation.
	
	The loop starts by determining which direction to iterate in depending on whether the new length is greater than the old length.
	The direction of iteration will reverse after any step where the relative difference between source and destination index crosses zero.
	When flipping to "ascending mode", the (asc) iterator jumps its entire step run all at once, back tracking to (dsc-1) step-by-step;
	upon returning to (dsc-1), it jumps that amount again, flopping over to "descending mode" which picks up one element down
	from where "ascending mode" last began.  Ascending motion steps like an old rotary phone dial, while descending motion is normal.
	Overall though, the flip-flopping iteration pattern still starts at the high end and works leftwards to zero.


	This scratch matrix illustration helped me wrap my mind around the process:

dsc:		 0                    1     2               3            4        5            6    7    8    9
	---------|--------------------|-----|---------------|------------|--------|------------|----|----|----|
src:	.......xx|...............xxxxx|...xx|............xxx|....xxxxxxxx|.......x|...........x|xxxx|....|...x|..........$
		2-2                  3-5   8-2             3-3          1-8      2-1          6-1  8-4  1-0  0-1
		 0                   -2     4               4           -3       -2            3    7    8    7
dst:	.......|+‡...............|++‡...|+++++++‡............|++‡....|‡.......|+‡...........|+++++‡|+++++++‡....|‡...|..........$
	       0                 1      2                    3       4        5             6      7            8    9


	In ascending mode, the order of operations per step is:
		> cut deleted elements
		> shift intermediate elements
		> shift operand element
		> insert new elements

	In descending mode, the order of operations per step (*with one caveat) is:
		> shift intermediate elements
		> insert new elements
		> shift operand element
		> cut deleted elements

	* The first descending step after flopping from ascending mode does not shift the operand element (special case labeled "_descx").
	Rather, that assignment is preempted by the first step of the preceding ascending run and prioritized to prevent potential clobbering.

	Inserts and cuts are defined immediately upon call to AvPOST AvCUT and AvPOST_retro,
	but the shift parameter can only be computed in-between instantiations of steps.
	Obviously the final call is never followed by another, so to actually get things started here, the first thing we do is finalize the last step.

	*/
	/* finalize the last step		*/
			rSeq_iR[	dsc ]	=	iR;
			rSeqSrc[	dsc ]	=	rack_iC;			rel_iC -=	rSeqCut[ dsc ];
			rSeqDst[	dsc ]	=	rack_iC 		+	rel_iC;
							post_zC=zC		+	rel_iC +	rSeqIns[ dsc ];	if( post_zC< 0 ){	AvFILLp( avICE ) =-1;	return;	}

	/* unless the last step targets the last element, append a terminating null step to align with the pre-op and post-op array lengths */
	if(	rack_iC<	zC ){
++	dsc;		rSeqDst[	dsc ]	=	post_zC;
			rSeqSrc[	dsc ]	=	zC;
			rSeq_iR[	dsc ]	=	0;
			rSeqIns[	dsc ]	=	0;
			rSeqCut[	dsc ]	=	0;
			}
	zsc=dsc;
	/* compute destination array size and return now if it's lt/eq zero, or extend if it's gt AvMAX  (AvFILLp is set last of all) */
	if( zC< post_zC ){	av_extend(	avICE,	post_zC+1 );	pSv0=AvARRAY( avICE );	}

	#define $insD		rSeqIns[	dsc ]
	#define $cutD		rSeqCut[	dsc ]
	#define $srcD 	rSeqSrc[	dsc ]
	#define $srcutD 	rSeqSrc[	dsc ] - rSeqCut[	dsc ]
	#define $dstD 	rSeqDst[	dsc ]

	#define $insA		rSeqIns[	asc ]
	#define $cutA		rSeqCut[	asc ]
	#define $srcA		rSeqSrc[	asc ]
	#define $srcutA	rSeqSrc[	asc ] - rSeqCut[	asc ]
	#define $dstA 	rSeqDst[	asc ]
	asc=dsc;																				dBUG_ReSEQ_SCHED_PRE	
	if(				$srcutD>=$dstD){				
		do	{/*	ascending start	*/	if( dsc ) --dsc;	else	{	src=				dst=pSv0;
														dial = asc+1;		asc=0;	dsc=-1;	dBUGiniA;	goto _asce;
													}
			} while(	$srcutD>=$dstD );						src= pSv0+$srcD;	dst=pSv0+$dstD;
														dial = asc -dsc;	asc=1+	dsc;		dBUGiniA;	goto _asce;

	}else	{/*	descending start	*/						src = pSv0 +zC;	dst = pSv0 +post_zC;
			while(	$srcutA< $dstA )	 if( asc ) --asc; else	{	dial = dsc+1;						dBUGiniD;	goto _desc;
			}										}	dial = dsc-asc;						dBUGiniD;

	do		{											/*	transverse loop			*/			
	_desc:	do	{		jmp = (src-pSv0) -$srcD;				/*	descending expansion loop	*/	dBUGdsc;
					if(	jmp >0 )	if( src == dst )	dst-=jmp;	/*	descending expansion		*/
								else	do	{	*dst-- = *src--;								dBUGjmpD;	} while( -- jmp );
					while( $insD)			{	*dst-- = rSeq_SV[	rSeq_iR[ dsc ]--]; --$insD; 		dBUGinsD;	}
					if(	dst -pSv0 != $srcD)	{	*dst = *( pSv0 +$srcD);							dBUGlocD;	}
					if(	$cutD ){	src =pSv0 +$srcutD -1;	$cutD=0; }
					else			src =pSv0 +$srcD -1;

	--dsc; --dst;	} while( --dial );	if( dsc< 0) break;

			if( src != dst )	{		jmp = (src-pSv0) -$srcD;		/*	finish dsc to asc edge		*/
							if(	jmp >0 ) do {	*dst-- = *src--;								dBUGjmpDxA;} while( -- jmp );
						}

			asc	= dsc;									/*	seek start index of asc run	*/
			while(	$srcutD >= $dstD )	if( dsc ) --dsc;	else
				{	src=				dst=pSv0;			dial = asc+1;		asc=0;	dsc=-1;	dBUGriniA;	goto _asce;
				}	src= pSv0+$srcD;	dst=pSv0+$dstD;		dial = asc -dsc;	asc=1+	dsc;		dBUGriniA;

	_asce:	do	{										/*	ascending compaction loop	*/	dBUGasc;
					if(	$cutA ){	jmp=( $srcutA )	-(src -pSv0);	$cutA=0;	}
					else			jmp= $srcA		-(src -pSv0);

					if(	jmp >0 )	if( src == dst )	dst+=jmp;	/*	ascending compaction		*/
								else	do	{	*dst++ = *src++;								dBUGjmpA;	} while( -- jmp );
					if(	dst -pSv0 != $srcA ){	*dst = *( pSv0 +$srcA );							dBUGlocA;	}
					++	dst;		src = pSv0 +$srcA +1;
					while( $insA )			{	*dst++ = rSeq_SV[	rSeq_iR[ asc ] - --$insA ]; 		dBUGinsA;	}

	++asc;		} while( --dial ); 	if( dsc< 0) break;

			src = dst	= pSv0 +$dstD;	/* cursor L-jumps (-1) past start of now-complete asc run	*/
			asc = dsc;									/*	L-seek end index of dsc run	*/
			while(	$srcutA <= $dstA ) if( asc ) --asc; 	else	{	dial = dsc;						dBUGriniD;	goto _descx;
													}	dial = dsc-asc-1;					dBUGriniD;

	_descx:				jmp = (src-pSv0) -$srcD;			/*	transversal to _desc	*/			dBUGdsc;
					if(	jmp >0 )				dst -= jmp;
						while( $insD)		{	*dst-- = rSeq_SV[	rSeq_iR[ dsc ]--]; --$insD; 		dBUGinsD;	}
			/*		if(	dst -pSv0 != $srcD ){	*dst = *( pSv0 +$srcD);							dBUGlocD;	}	*/
			/*		^^	this omission is what differentiates the "_desc" and "_descx" blocks							*/
					if(	dsc==0 ) break;
					if(	$cutD ){	src =pSv0 +$srcutD -1;	$cutD=0; }
					else			src =pSv0 +$srcD -1;
	--dsc; --dst;

			} while( 1 ); /* flip-flop asc/dsc */													dBUG_ReSEQ_SCHED_POST
	dsc=asc=dial=0;

	if( AvFILLp( avICE ) != post_zC ) AvFILLp( avICE ) = post_zC;
	}
void	_set8x(){
	#ifdef DEBUG_SET_L1			//	audit nominal activity
		#define dBUGop0		cS=sprintf(aString, "\r=+|_	x( %5llu )	=+|_ 	iC/zC  %5llu/%-5llu	*((ui64*)cubeZ+1) == %llu \n\t",	x, iC, zC, *((ui64*)cubeZ+1)	); AvPUSHaSTRING( aString, cS );		//_print_mx(21);
		#define dBUGop1 		cS=sprintf(aString, "\r!|+=	x( %5llu )	!|+= 	iC/zC  %5llu/%-5llu	*((ui64*)cubeZ+1) == %llu \n\t",	x, iC, zC, *((ui64*)cubeZ+1)	); AvPUSHaSTRING( aString, cS );		//_print_mx(23);
		#define dBUGop2		cS=sprintf(aString, "\r=|+=	x( %5llu )	=|+= 	iC/zC  %5llu/%-5llu	*((ui64*)cubeZ+1) == %llu \n\t",	x, iC, zC, *((ui64*)cubeZ+1)	); AvPUSHaSTRING( aString, cS );		//_print_mx(24);
		#define dBUGop3		cS=sprintf(aString, "\r=+|$	x( %5llu )	=+|$ 	iC/zC  %5llu/%-5llu	*((ui64*)cubeZ+1) == %llu \n\t",	x, iC, zC, *((ui64*)cubeZ+1)	); AvPUSHaSTRING( aString, cS );		//_print_mx(11);
		#define dBUGop4		cS=sprintf(aString, "\r=+_ 	x( %5llu )	=+_  	iC/zC  %5llu/%-5llu	E[%d]( %llu )\n\t",				x, iC, zC, u, E[u]			); AvPUSHaSTRING( aString, cS );		//_print_mx(311);	
		#define dBUGop5		cS=sprintf(aString, "\r=+= 	x( %5llu )	=+=  	iC/zC  %5llu/%-5llu	E[%d]( %llu )\n\t",				x, iC, zC,  u, E[u]			); AvPUSHaSTRING( aString, cS );		//_print_mx(312);	
		#define dBUGop6		cS=sprintf(aString, "\r_+_	x( %5llu )	_+_  	iC/zC  %5llu/%-5llu	E[%d]( %llu )\n\t",				x, iC, zC,  u, E[u]			); AvPUSHaSTRING( aString, cS );
		#define dBUGop7		cS=sprintf(aString, "\r_+=	x( %5llu )	_+=  	iC/zC  %5llu/%-5llu	E[%d]( %llu )\n\t",				x, iC, zC,  u, E[u]			); AvPUSHaSTRING( aString, cS );		//_print_mx(302);	
		#define dBUGop8		cS=sprintf(aString, "\r===	x( %5llu )	===  	iC/zC  %5llu/%-5llu	E[%d]( %llu )\n\t",				x, iC, zC,  u, E[u]			); AvPUSHaSTRING( aString, cS );		//_print_mx(303);	
		#define dBUGinit_mx	_init_mx();
	#else
		#define dBUGop0
		#define dBUGop1 
		#define dBUGop2
		#define dBUGop3
		#define dBUGop4
		#define dBUGop5
		#define dBUGop6
		#define dBUGop7
		#define dBUGop8
		#define dBUGinit_mx
	#endif
	#ifdef DEBUG_SET_L2			//	audit nominal activity verbosely
		#define dBUG_ReICEzSV_($v )				cS=sprintf(aString, "\nReICEzSV_( %d )\n", $v ); AvPUSHaSTRING( aString, cS );
	#else
		#define dBUG_ReICEzSV_($v )
	#endif
	#ifdef DEBUG_SET_L3			//	check integrity
		#define dBUGnARF	cS=sprintf(aString, "\n	INTERLOC: null gap	(==|=) \n");	AvPUSHaSTRING( aString, cS );
		#define dBUG_SvCUR($CS, $VARNAME )			if( $CS<16){ printf("\n!	%s< 16 ( %d )	%s line %lld\n",$VARNAME, $CS,  __FILE__, __LINE__ );	exit(-1);	}
	#else
		#define dBUGnARF
		#define dBUG_SvCUR($CS, $VARNAME )
	#endif

	#define uMOD	RW[ u ] = mod
	#define vMOD	RW[ v ] = mod
	#define vNUL		RW[ v ] = null;
	#define uNEW 	RW[ u ] = new
	#define vNEW 	RW[ v ] = new

	SV ** pSv;			pSv0	= AvARRAY(	avICE );								dBUGavCLR	dBUGinit_mx
	skip=a=0;					za	= AvFILLp(	avArg);	if( za ==-1){				/*	no args */		return;	}
	x = ARG0;	/*post_zC=*/	zC	= AvFILLp(	avICE);	if( zC ==-1){					NEW(	0 );		return;	}
	#define	INIT_WRITE_ACCESS	\
	ix0=0xFF;							/*<— how we know there's nothing to rack	*/\
	rSeqCut[0]= rSeqIns[0]=			\
	dial= rel_iC= rack_iC= 	dsc	= 0;	\
	rSeq_iR[0]=		iR=	asc	= -1;
	INIT_WRITE_ACCESS;
	
/* search for iC of x		*/	lb =0;	ub =zC +1;	iC= ub>>1;
do	{									cube = SvPVbyte_nolen(	sv =*(pSv0+iC ) );
	if(						x == *( (ui64*)	cube +1) ){
							cubeZ	=	cube;	CSZ = SvCUR(	svZ= sv );		_anteloc:	ANTELOC;										//_print_mx(10);
		if( iC< zC	){						cube = SvPVbyte_nolen(	sv =*(pSv0+ ++iC) );	INTERLOC;										//_print_mx(20);
			/*						RW []	Q []		A []			B []				E []			O []			I []	*/
/*	=+|_	*/	do	{ if(		A[ 0 ] >1 ){		 	--	A[ 0 ];	   ++	B[ 255 ];												dBUGop0
							++	*( (ui64*)	cubeZ +1);				if( za == a ){		ReICEzSV_(255);	goto	_none_x;		}
					}else if(	A[ 0 ]==1 ){				A[ 0 ]=A[255];	B[ 0 ]+=B[255]+1;													//_print_mx(22);
/*	!|+=		*/			if(	zcZ == 0 ){		 									AvCUT_B4( iC );						dBUGop1
/*	=|+=	*/			}else{	*( (ui64*) cubeZ+1) -=  	A[ 255 ]	+	B[ 255 ];
			//				cubeZ[zcZ--]=0;			SvCUR_set( svZ, CSZ-Q[ 255 ] );	/*	cubeZ[O[255]]=0;	*/	
							cubeZ[zcZ--]=0;			SvCUR_set( svZ, O[ 255 ] );		cubeZ[O[255]]=0;				dBUGop2
							}																	goto	_next_a;
/*	==|=	*/		}else{ /* rogue null off-cycle is an artifact which the spec must allow */	dBUGnARF		goto	_next_a;   	}
	x = ARG( ++a );   	} while(	x == *( (ui64*)	cubeZ+1) );								ReICEzSV_(255);	goto	_next_x;
		}else{	do	{		 ++	*( (ui64*)	cubeZ+1);			  ++	B[ 255 ];												dBUGop3
/*	=+|$	*/													if( za == a ){		ReICEzSV_(255);	goto	_av_commit; 	}
	x = ARG( ++a );	} while(	x == *( (ui64*)	cubeZ+1) );								ReICEzSV_(255);
							E_=	*( (ui64*)	cubeZ +1);												goto	_extra_x;
			}

	}else if(					x <	*( (ui64*)	cube +1) ){ iC=(( ub	= iC )+lb	)>>1;  if( iC==ub ){	INTRALOC;		goto	_intra_op; 	}
	}else{				/*	x >	*( (ui64*)	cube +1)*/ iC=(( lb	= iC )+ub	)>>1;  if( iC==lb  ){	INTRALOC1Up;			_intra_op:
		do{	if(				x==E[u]){	uMOD;					if(	RW[ v ]== null ){	DeICEv_KEI( u, v );  }								//_print_mx(310);	
/*	=+_		*/	if(		A[ v ] >1 ){	vMOD;		    --	A[ v ];	   ++	B[ u ];		   ++	E[ u ];								dBUGop4
/*	=+=		*/	}else{	--tena_zc;  	vNUL;						B[ u ]+= A[v]+B[v];	E[ u ] =E[ v ];	O[v]+=Q[v];				dBUGop5//	printf("\nop5 (=+=): u, v, w= %d, %d, %d	I[u]=%d	I[v]=%d	I[w]=%d\n\n", u, v, v+1, I[u], I[v], I[v+1] );
					}	/*	!	!	!	!	!	!	!	!	!	!	!	!	!	!	!	!	!	!	!	^^^brand new	*/
			}else{			d = E[u] -x -B[u];																						//_print_mx(300);
/*	_+_		*/	if(			d >1	){	vNEW;	Q[v]=0;	A[ v ] = d -1;	B[ v ] = B[ u ];		E[ v ] =E[ u ];/*O[v]=O[u]+Q[u];*/			dBUGop6
						++tena_zc;	uMOD;			A[ u ] -= d;	B[ u ] = 1;		E[ u ] =x +1;	O[v+1]=O[v];	I[ v ] = I[ u ];				//_print_mx(301);	
/*	_+=		*/	}else if(		d==1 ){	uMOD;		    --	A[ u ];	   ++	B[ u ];												dBUGop7
/*	===		*/	}else{	++skip;	/*	RW []	Q []		A []			B []				E []			O []			I []	*/		dBUGop8
				}	}
	_next_a:														if( za == a )						goto	_none_x;
							x = ARG( ++a );
	_next_x:	if(				x <	*( (ui64*)	cube +1) ){   								CoINTRaLOC;
			}else{			/*			cubeZ= cube;	(RACK handles this	) */			RACK;
				if(			x == *( (ui64*)	cubeZ+1) )												goto	_anteloc;
				if( zC ==	iC ){	E_=	*( (ui64*) cubeZ+1);												goto	_extra_x; 	}
				sv=*( ++	iC	+pSv0 );		cube = SvPVbyte_nolen(	sv);
				if(			x <	*( (ui64*)	cube +1) ){ CS = SvCUR(	sv);					ReINTRALOC;		goto	_intra_op; 	}
				if(			x == *( (ui64*)	cube +1) ){ CSZ=SvCUR(	svZ= sv );			cubeZ=cube;		goto	_anteloc;		}
				if( zC ==	iC ){	E_=	*( (ui64*)	cube +1);						_extra_x:		EXTRALOC( E_ );	return;	}
				break;
			}	} while( 1 );	lb =iC+1;	ub=zC +1;	iC= ( lb+ub )>>1;
	}	}	} while( 1 );		/* search	*/
	_none_x:																		RACK;
	_av_commit:		if( dsc || rSeqIns[0] || rSeqCut[0] )	_av_commit();
	}

#ifdef ENABLE_EXPERIMENTAL
void	_toHash(){					hvOut = newHV();
	ui64			x, Ac, Bc, Ec=0,	i=0;
	char			ic, zc,
				key[ 8 ];
	ui08			Qc,	bs;
			*	cube,
			*	pq;
	SV		**	sviC0  =	AvARRAY(  	avICE ),
			**	src,
			*	sv;
	STRLEN		CS, s;

	long long int	iC, zC  =	AvFILLp(  	avICE );

	for(		iC=0; iC<= zC;  ++iC ){								sv = *( sviC0 +iC );
											cube = SvPVbyte(	sv,  CS );
		pq=									cube +16;
						zc = zcOf(	*( (ui64*)	cube ) );
		for(	ic=0;  ic<=	zc; ++ic ){		deICE(	cube[ ic ], Qc, Ac, Bc );
					x =Ec +Ac;
			for( Ec =	x +Bc;  x< Ec;  ++x ){	bs = 	__builtin_clzll( x)	&0xFFFFFFFFFFFFFF00;
				*( (ui64*) key )= x;	//<< bs;
		
			src = hv_store( hvOut,	key,    	8, &PL_sv_undef, 0 );
				printf("\r...	_toHash(): cube %lld.%lld	hv_store( hvOut, \"%lld\", %d, &PL_sv_undef, 0)  returns SV** addr %llX\n", iC, ic, *( (ui64*) key), s, &**src);	

		}	}	}

	}
void	_filterHV(){
//	hvArg is set already
	N=hv_iterinit( hvArg );
	ui64			Ac, Bc, Ec=0,	i=0;
	char			ic, zc,
				key[ 8 ];
	ui08			Qc,
			*	cube,
			*	pq;
	SV		**	sviC0  =	AvARRAY(  	avICE ),
			*	sv;
	STRLEN		CS, s;

	long long int	iC, zC  =	AvFILLp(  	avICE );
	printf("\r_filterHV(): avICE has %d+1 element[s]\n	hvArg has (%d) key[s]\n\n", zC, N);

	for(		iC=0; iC<= zC;  ++iC ){								sv = *( sviC0 +iC );
											cube = SvPVbyte(	sv,  CS );
		pq=									cube +16;
						zc = zcOf(	*( (ui64*)	cube ) );
		for(	ic=0;  ic<=	zc; ++ic ){		deICE(	cube[ ic ], Qc, Ac, Bc );
						*( (ui64*)  	key ) =Ec +Ac;
			for(	Ec	=	*( (ui64*)  	key ) +Bc;
						*( (ui64*)  	key )< Ec;
					++	*( (ui64*)  	key ) ){	//s =ncOf( *( (ui64*)  key ) );
				sv= hv_delete( hvArg,	key,		8, 0 );
				if( &*sv ) --N;

				printf("\r...	_filterHV(): cube %lld.%lld	hv_delete( hvArg, \"%lld\", %d, 0)  returns SV addr %llX	\n", iC, ic, *( (ui64*) key), s, &*sv );	
		}	}	}
	printf("\r...	_filterHV() %d key[s] remain\n", N );
	}


void _set9up(){
						pSv0	= AvARRAY(	avICE );								dBUGavCLR	dBUGinit_mx
	skip=a=0;					za	= AvFILLp(	avArg );		if( za ==-1){			/*	no args */		return;	}
	x = ARG0;		zzC=(	zC	= AvFILLp(	avICE )	)-1;	if( zC ==-1){				NEW(	0 );		return;	}

	INIT_WRITE_ACCESS;

/* search for iC of x		*/	lb =0;	ub =zC +1;	iC= ub>>1;
do	{									cube = SvPVbyte_nolen(	sv =*(pSv0+iC ) );
	if(						x == *( (ui64*)	cube +1) ){
							cubeZ	=	cube;	CSZ = SvCUR(	svZ= sv );			ANTELOC;										//_print_mx(10);
		if( iC< zC	){						cube = SvPVbyte_nolen(	sv =*(pSv0+ ++iC) );	INTERLOC;										//_print_mx(20);
			/*						RW []	Q []		A []			B []				E []			O []			I []	*/
/*	=+|_	*/	do	{ if(		A[ 0 ] >1 ){			   --	A[ 0 ];	   ++	B[ 255 ];												dBUGop0
							++	*( (ui64*) cubeZ +1);				if( za == a ){		ReICEzSV_(255);	goto	_none_x;		}
					}else if(	A[ 0 ]==1 ){				A[ 0 ]=A[255];	B[ 0 ]+=B[255]+1;													//_print_mx(22);
/*	!|+=		*/			if(	zcZ == 0 ){											AvCUT_B4( iC );												dBUGop1
/*	=|+=	*/			}else{	*( (ui64*)	cubeZ+1) -=	A[ 255 ]	+	B[ 255 ];
							cubeZ[zcZ--]=0;			SvCUR_set( svZ, O[ 255 ] );		cubeZ[O[255]]=0;						dBUGop2
							}																	goto	_next_a;
/*	==|=	*/		}else{ /* rogue null off-cycle is an artifact which the spec must allow */	dBUGnARF		goto	_next_a;  	}
	x = ARG( ++a );	} while(	x == *( (ui64*)	cubeZ+1) );								ReICEzSV_(255);	goto	_next_x;
		}else{	do	{		 ++	*( (ui64*)	cubeZ+1);			  ++	B[ 255 ];												dBUGop3
/*	=+|$	*/													if( za == a ){		ReICEzSV_(255);	goto	_av_commit; 	}
	x = ARG( ++a );	} while(	x == *( (ui64*)	cubeZ+1) );								ReICEzSV_(255);	goto	_more_x;
			}



	}else if(					x <	*( (ui64*)	cube +1) ){ iC=(( ub	= iC )+lb	)>>1;  if( iC==ub ){	INTRALOC;		goto	_intra_op; 	}
	}else{				/*	x >	*( (ui64*)	cube +1)*/ iC=(( lb	= iC )+ub	)>>1;  if( iC==lb  ){	INTRALOC1Up;			_intra_op:
			do{	if(			x==E[u]){	uMOD;					if(	RW[ v ]== null ){	DeICEv_KEI( u, v );  }								//_print_mx(310);	
/*	=+_		*/		if(		A[v] >1){	vMOD;		    --	A[ v ];	   ++	B[ u ];		   ++	E[ u ];								dBUGop4
/*	=+=		*/		}else{--tena_zc; 	vNUL;	Q[u]+=Q[v];			B[ u ]+= A[v]+B[v];	E[ u ] =E[ v ];	O[v]+=Q[v];	dBUGop5
						}			//		^ try it a bunch before you  f with it again
				}else{		d = E[u] -x -B[u];																						//_print_mx(300);
/*	_+_		*/		if(		d >1	){	vNEW;	Q[v]=0;	A[ v ] = d -1;	B[ v ]  = B[ u ];		E[ v ] =E[ u ];	O[v]=O[u]+Q[u];			dBUGop6
						++tena_zc;	uMOD;			A[ u ] -= d;	B[ u ] = 1;		E[ u ] =x +1;	O[v+1]=O[v];	I[ v ] = I[ u ];				//_print_mx(301);	
/*	_+=		*/		}else if(	d==1 ){	uMOD;		    --	A[ u ];	   ++	B[ u ];												dBUGop7
/*	===		*/		}else{++skip;	/*	RW []	Q []		A []			B []				E []			O []			I []	*/		dBUGop8
					}	}

	_next_a:		if( za != a )	x = ARG( ++a );										else				goto	_none_x;
	_next_x:		if(		iC< zzC)	{		qube = SvPVbyte_nolen(	sv0=*( 1 +iC +pSv0 ) );
					if(		x >	*( (ui64*)	qube +1	) )	{					printf("\n-----1\n");		RACK;			break;
					}else if(	x >=	*( (ui64*)	cube +1	) )	{					printf("\n-----2");		CoINTERLOC;
						zc=zcOf(	*( (ui64*)	qube	) ); ++iC; ic=0;	sv=sv0; CS=SvCUR( sv);
						if(	x ==	*( (ui64*)	qube +1	) )		{	cube=qube;	printf("a\n");			CoINTERLOC;		continue;
														}	cube=qube;	printf("b\n");
								}					}
				else if(		x >=	*( (ui64*)	cube +1	) )	{					printf("\n-----3");		CoINTERLOC;
					if(	iC< zC)	{		cube = SvPVbyte(		sv=*( ++iC +pSv0 ), CS );
						zc=zcOf(	*( (ui64*)	cube	) ); 	ic=0;
						if(	x ==	*( (ui64*)	cube +1	) )		{				printf("x\n");			CoINTERLOC;		goto	_more_x;
								}						}		/*	x< fall through to "	CoINTRaLOC " */
					else{												printf("X\n");					goto	_more_x;	}
					}													printf("CoINTRALOC\n");		CoINTRaLOC;
				} while( 1 );	lb =iC+1;	ub=zC +1;	iC= ( lb+ub )>>1;
	}	}	} while( 1 );	/* search	*/
	_more_x:			EPILOC;
	_none_x:			RACK;
	_av_commit:		if( dsc || rSeqIns[0] || rSeqCut[0] )	_av_commit();	return;
	}
#endif

/*	dooooo	f*/