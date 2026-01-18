#define DEBUG
/*	ICE::RELiC—	Regressive Exponent Laminar Index Counter (RELiC) over Inversion Cycle Encoding (ICE)
	this jam is real																				*/

/*	ABSTRACT																				*/

/*	Standalone ICE encoding works well as a representation for ID allocations, because it guarantees instant O(1) access
	to the lowest / highest / nearest [non-]free sparse index.

	When structured in a sorted array as searchable chunks, it enables hash-like and array-like access, exhibiting hyperbolic complexity.

		> Trivial access to lowest / highest / nearest sparse index in O(1) time— an obvious strength for dynamic ID tables
		> Hash-like sparsity with array-like sorting effectively works like a sorted hash
		> Indeces maintain order (as in vectors/arrays) but without direct correlation between fixed and sorted index (like hashes)

	ICE is a QWORD-sized compressed truth vector which uses an original variant of RLE encoding— Inversion Cycle RLE.
	IC-RLE compresses repeating values into run lengths  (like RLE), but stores no explicit values— only implicit boolean truth.
	Since RLE stores only the first occurrence of a repeating value, and boolean values can only be one of two, value is actually implied,
	and IC-RLE representation is nothing more than a series of run length pairs which implicitly store alternating true-false value.

	To promote the integrity of the encoding across mutations, ICE compresses pairs of true-false run lengths in single entries,
	and mediates computational complexity to access and mutate these entries with opportunistic [de]fragmentation.
	Encoded data is stored as a series of semi-regular chunks (16 to 144 bytes in length) which are sorted into a searchable AV* array.
	
		> Computational complexity plots as a roughly hyperbolic asymptote given the worst case highly entropic data.
		> Batch processing affects significant improvement in mutation time complexity when leveraged by the application.
		> Variety of accessor methods enable manipulation by range, mask, sorted list and scalar arguments, as well as recombination.
		> In-memory data blocks are an easy packet payload to stream over TCP with no fragmentation and minimal layer-4 overhead.
	

	Any compression technique which removes the voids from a sparse array comes with the obvious but unfortunate tradeoff
	of losing the intrinsic correlation between index and sort order, which is often what makes arrays useful in the first place.
	This is where ICE::RELiC comes in— to implement efficient non-sparse sort order computation.

	For example: let's say you wish to implement a random number generator that is non-deterministic, yet also non-repeating,
	and you wish to use this to allocate Session IDs in a massively distributed cloud server application.  You would have your choice
	of entropy sources as usual, but instead of piping this directly into a Session ID generator, you use it to choose the "nth" free ID
	in an ICE::RELiC instance, which trivially guards against colissions; in order to make replication across a server farm more efficient,
	you can allow servers to preallocate large random sets of IDs, periodically throwing them back into the pool and drawing a new set.
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

	>	Cycla chain together to form a vector path which stores the allocations of the NS as alternating ranges of un/defined keys.

	That last point is arguably the most significant, because IC-RLE encoding used in this way exhibits hyperbolic time complexity—
	the nearest approach to the asymptote occurs at around 60% capacity, after which point time drops back down to the initial value.
	This behavior is due to parametric representation, where memory is consumed more by sparsity than logical content.
	ICE encoding is leveraged to maximize compression in the saturation state by compressing the smallest (A, B) pairs into a single byte.
	At this granular level, this is the most probable case when data is highly entropic and saturation reaches an equilibrium state.

	*/

/*	NOTES
	We have precomputed all relevant combinations of assignments in the form of switch statements.
	These switch statements write the values in few instructions without overflowing the field width (plus the allowable "overflow risk").
	They are generated by the following perl scripts:
		> gen_c_for_qCASTa.pl
		> gen_c_for_qCASTab.pl
		> gen_c_for_qCASTab1.pl
		> gen_c_for_qCASTab2.pl
		> gen_c_for_qCASTab3.pl

	The following generators may be obsolete or not useful:
		> gen_c_for_qCASTabc.pl
		> gen_c_for_qCASTabcd.pl

	These CAST_CASE macros safely and efficiently inject variable-width integers into active working byte arrays without clobbering data.
	In order to copy an unsigned quad into a field fit for the significant bytes only, it will require one of the following combinations of casts:
	
		> a single assignment cast as a char, short, long, or quad				(1, 2, 4, or 8 bytes)
		> two assignments cast as:	» (short) x;	(char) x>>16				(3 bytes)
								» (long) x;	(char) x>>32				(5 bytes)
								» (long) x;	(short) x>>32				(6 bytes)
		> three assignments cast as:	 (long) x;  	(short) x>>32;	(char) x>>48	(7 bytes)

	These variants are each optimized to leverage a specific length of allowable overrun (up to (3) bytes can make a difference).
	They are further differentiated to write values either (1) or (2) integers at a time.
	They are defined as:
		> qCASTa	to assign (1) value with no overflow risk				(minor variant qCASTp1x takes pointer, not int )
		> qCASTa1	to assign (1) value with an overflow risk of 1 byte		(no generator exists - it was derived from qCASTa)
		> qCASTa2	to assign (1) value with an overflow risk of 2 bytes	(no generator exists - it was derived from qCASTa)
		> qCASTa3	to assign (1) value with an overflow risk of 3 bytes	(no generator exists - it was derived from qCASTa)
		> qCASTab	to assign (2) values with no overflow risk
		> qCASTab1	to assign (2) values with an overflow risk of 1 byte
		> qCASTab2	to assign (2) values with an overflow risk of 2 bytes
		> qCASTab3	to assign (2) values with an overflow risk of 3 bytes


	THREE PHASES OF NAMESPACE DEPLETION
	Expansion:	When the namespace is mostly free,	entropic inclusions tend to generate cycla,	complexifying the graph.
	Saturation: 	When the namespace is about 60/40,	entropic inclusions have no overt tendency;	complexity plateaus.
	Contraction: 	When the namespace is mostly used,	entropic inclusions tend to integrate cycla,	simplifying the graph.

	*/

#define	i64	long long			int
#define	ui64	long long	unsigned	int
#define	ui64	long long	unsigned	int

#define	ui32		long	unsigned	int
#define	ui16			unsigned	short 
#define	ui08			unsigned	char	
#define	cui8	const	unsigned	char	

#define	zIndexOf( $a)		7-( 	__builtin_clzll( $a)	>>3)
#define	SizeOf( $a)		8-( 	__builtin_clzll( $a)	>>3)


#define	CUBE_(	$iC )   									SvPVbyte( *( AvARRAY( avICE) +$iC ), CS_	)
#define	CUBE(	$iC )   									SvPVbyte( *( AvARRAY( avICE) +$iC ), CS	)
#define	CUBEvc(	$iC )(  		__builtin_clzll( *( (ui64*) (	cube =	SvPVbyte( *( AvARRAY( avICE) +$iC ), CS	) ) +1 ) )	>>3)

char	*	lightning = "\n!! !  !   !    !     !      !       !        !         !          !           !            !             !              !               !                !\n",
		aString[256];

svtype			t_xv;
HV			*	hvICE,
			*	hvArg,
			*	hvOut;
AV			*	avOut,
			*	avICE;	long long int	iC, post_iC, zC, post_zC, rel_iC, iCs, iCd, less_iC;  	//	iC is the index of the current cube.  zC is the array index of the ending cube.
AV			*	avArg;	long long int	a, za; 					//	a list of integer value[s] to operate on.
AV			*	avRack; 	long long int	rZ, rE;					//	contains a series of SV* cubes pending insertion into AV* avICE

SV			**	src,
			**	dst,
			**	psv,
			**	svC0,
			*	rvOut,				/*	arrayref to AV* avOut								*/
			*	rvArg,				/*	arrayref to AV* avArg								*/
			*	rvICE,				/*	arrayref to AV* avICE								*/
			*	svX,					/*	general purpose scratch SV							*/
			*	svLbf,				/*	lower cube fragment								*/
			*	sv_,					/*	SV containing left-hand cube data						*/
			*	sv,					/*	SV containing right-hand cube data					*/
			*	_sv;					/*	SV containing pre-rack cube data						*/
ui08			*	cube	=NULL,		/*	unsigned char * cube data (of index iC )				*/
			*	cube_	=NULL,		/*	unsigned char * cube data (of index iC -1)				*/
			*	_cube	=NULL,		/*	unsigned char * cube data (detached from avICE)		*/
			*	hob[2]	={NULL, NULL};
bool				L=0,
				R=1;
	
STRLEN			CS,	CS_, _CS;
ui08				buf[	8 	+8	+8*16	+1	+15 ];	/*	buffers the output of ICE() and its variants
/*	CUBE STRUCT:	^	^	^		^	^ overflow padding (to survive an overshot "long long" cast)
					|	|	|		NULL byte
					|	|	up to 128 bytes of q-data
					|	"Epsilon" equals the ending value of each cube +1, which serves as an upper boundary for binary search
					keybyte section which stores up to (8) keybytes
					*/
ui64	*	pKx	= (ui64*) buf;
ui64	*	pEx	= (ui64*) buf +1;

ui08		**pps,	**ppd,
		*pk,		*pq,
		*pkz,	*pqz,
		*pk_,	*pq_,	*_pk,	*_pq,
		*pku,	*pqu,	
		*pkv,	*pqv,	
		*pk0,	*pq0,	
		*pkx,	*pqx;

/*	standard global constant cube initialization templates 	*/
/*			"cube0" is used to initialize a cube which should start with element #0 set.						*/
const ui08	cube0[	16]={	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x08,		/* cyclum #0:	x==0			*/
							0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	1		};	/* Epsilon:	1				*/

/*			"nube" is used to initialize an empty cube, or as a null value to set pointers to directly.			*/
const ui08	nube[	16]={	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,		/* no content					*/
							0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00	};	/* Epsilon:	0				*/

/*			"cubE" is a global constant object used to failsafe RELiC accessors against potential overrun by iCE() and its variants.
			It contains a single null point at the max int, bounding the 64-bit namespace.					*/
const ui08	cubE[	24]={	0xB8,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,		/* cyclum #7:	x==null			*/
							0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,		/* Epsilon:	2^64-1 (max uint)	*/
							0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF	};	/* A: 		2^64-1 (max uint)	*/
static const char* svtype_names[] = {		"SVt_NULL",		"SVt_IV",		"SVt_NV",		"SVt_RV",		"SVt_PV",	"SVt_PVIV",		"SVt_PVNV",		"SVt_PVMG",		"SVt_INVLIST",		"SVt_REGEXP",		"SVt_PVGV",		"SVt_PVLV",		"SVt_PVAV",		"SVt_PVHV",		"SVt_PVCV",		"SVt_PVFM",		"SVt_PVIO",		"SVt_PVBM",		"SVt_PVGV",		"SVt_PVLV",		"SVt_PVAV",		"SVt_PVHV",		"SVt_PVCV",		"SVt_PVFM",		"SVt_PVIO",		"SVt_PVBM",		"SVt_PVGV",		"SVt_PVLV",		"SVt_PVAV",		"SVt_PVHV",		"SVt_PVCV",		"SVt_PVFM",		"SVt_PVIO",		"SVt_PVBM",		"SVt_PVGV",		"SVt_PVLV",		"SVt_PVAV",		"SVt_PVHV",		"SVt_PVCV",		"SVt_PVFM",		"SVt_PVIO",		"SVt_PVBM",		"SVt_PVGV",		"SVt_PVLV",		"SVt_PVAV",		"SVt_PVHV",		"SVt_PVCV",		"SVt_PVFM",		"SVt_PVIO",		"SVt_PVBM",		"SVt_PVGV",		"SVt_PVLV",		"SVt_PVAV",		"SVt_PVHV",		"SVt_PVCV",		"SVt_PVFM",		"SVt_PVIO",		"SVt_PVBM",		"SVt_PVGV",		"SVt_PVLV",		"SVt_PVAV",		"SVt_PVHV",		"SVt_PVCV",		"SVt_PVFM",		"SVt_PVIO",		"SVt_PVBM",		"SVt_PVGV",		"SVt_PVLV",		"SVt_PVAV",		"SVt_PVHV",		"SVt_PVCV",		"SVt_PVFM",		"SVt_PVIO",		"SVt_PVBM",		"SVt_PVGV",		"SVt_PVLV",		"SVt_PVAV",		"SVt_PVHV",		"SVt_PVCV",		"SVt_PVFM",		"SVt_PVIO",		"SVt_PVBM",		"SVt_PVGV",		"SVt_PVLV",		"SVt_PVAV",		"SVt_PVHV",		"SVt_PVCV",		"SVt_PVFM",		"SVt_PVIO",		"SVt_PVBM",		"SVt_PVGV",		"SVt_PVLV",		"SVt_PVAV",		"SVt_PVHV",		"SVt_PVCV",		"SVt_PVFM"		};
static const char* svtype_names_ref[] = {	"ref: SVt_NULL",	"ref: SVt_IV",	"ref: SVt_NV",	"ref: SVt_RV", 	"ref: SVt_PV",	"ref: SVt_PVIV",	"ref: SVt_PVNV",	"ref: SVt_PVMG",	"ref: SVt_INVLIST", 	"ref: SVt_REGEXP",	"ref: SVt_PVGV",	"ref: SVt_PVLV",	"ref: SVt_PVAV",	"ref: SVt_PVHV",	"ref: SVt_PVCV",	"ref: SVt_PVFM",	"ref: SVt_PVIO",	"ref: SVt_PVBM",	"ref: SVt_PVGV",	"ref: SVt_PVLV",	"ref: SVt_PVAV",	"ref: SVt_PVHV",	"ref: SVt_PVCV",	"ref: SVt_PVFM",	"ref: SVt_PVIO",	"ref: SVt_PVBM",	"ref: SVt_PVGV",	"ref: SVt_PVLV",	"ref: SVt_PVAV",	"ref: SVt_PVHV",	"ref: SVt_PVCV",	"ref: SVt_PVFM",	"ref: SVt_PVIO",	"ref: SVt_PVBM",	"ref: SVt_PVGV",	"ref: SVt_PVLV",	"ref: SVt_PVAV",	"ref: SVt_PVHV",	"ref: SVt_PVCV",	"ref: SVt_PVFM",	"ref: SVt_PVIO",	"ref: SVt_PVBM",	"ref: SVt_PVGV",	"ref: SVt_PVLV",	"ref: SVt_PVAV",	"ref: SVt_PVHV",	"ref: SVt_PVCV",	"ref: SVt_PVFM",	"ref: SVt_PVIO",	"ref: SVt_PVBM",	"ref: SVt_PVGV",	"ref: SVt_PVLV",	"ref: SVt_PVAV",	"ref: SVt_PVHV",	"ref: SVt_PVCV",	"ref: SVt_PVFM",	"ref: SVt_PVIO",	"ref: SVt_PVBM",	"ref: SVt_PVGV",	"ref: SVt_PVLV",	"ref: SVt_PVAV",	"ref: SVt_PVHV",	"ref: SVt_PVCV",	"ref: SVt_PVFM",	"ref: SVt_PVIO",	"ref: SVt_PVBM",	"ref: SVt_PVGV",	"ref: SVt_PVLV",	"ref: SVt_PVAV",	"ref: SVt_PVHV",	"ref: SVt_PVCV",	"ref: SVt_PVFM",	"ref: SVt_PVIO",	"ref: SVt_PVBM",	"ref: SVt_PVGV",	"ref: SVt_PVLV",	"ref: SVt_PVAV",	"ref: SVt_PVHV",	"ref: SVt_PVCV",	"ref: SVt_PVFM",	"ref: SVt_PVIO",	"ref: SVt_PVBM",	"ref: SVt_PVGV",	"ref: SVt_PVLV",	"ref: SVt_PVAV",	"ref: SVt_PVHV",	"ref: SVt_PVCV",	"ref: SVt_PVFM",	"ref: SVt_PVIO",	"ref: SVt_PVBM",	"ref: SVt_PVGV",	"ref: SVt_PVLV",	"ref: SVt_PVAV",	"ref: SVt_PVHV",	"ref: SVt_PVCV",	"ref: SVt_PVFM"	};


ui64			i, ub, lb, n, N, o, s;		/*	global scratch variables used in private contexts									*/
SV			*svX, *svY, *svZ;		/*	perl scalars which contain common arguments									*/
ui64			x, y, z,				/*	common arguments														*/
			skip, hit, miss,			/*	the number of misses or collissions counted as a method processes arguments  		*/
			hu, bu, hm, lm; 	 	/*	high-unit, base-unit, high-mask, low-mask:
									used to quantize keys for each unitary digit of numeric base (BASEBITS).		 		*/
ui08			Ki,					/*	the keybyte of the current cyclum												*/
			f,					/*	A-B encoding flags, just the first (2) bits of the keybyte isolated						*/
			ab,					/*	A-B encoding parameters, the last (6) bits of the keybyte isolated; a pair of octal values	*/
			lost_ic;				/*	a number of cycla consolidated into a single cyclum due to having null B-value			*/
ui64			Kx8, Kx8_, _Kx8;		/*	an actual array of (8) octets, but cast as an unsigned quad, simply to use bitwise ops	*/

//in general, a variable preceded by an underscore is updated in realtime, so to represent a value in a post-op state.
//matrix indeces will not be negative
/*						____	object______________________	verb_________	subject_____________________	preposition______________________	*/
char unsigned u, v, w,		/*	matrix indeces			iterate		the source range			in	matrix { A[], B[], E[], Q[] }	*/
			_0x, _ez,		/*	matrix indeces			mark		the range of cube iC (incl.)	in	matrix { A[], B[], E[], Q[] }	*/
			mx0,		/*	matrix index				marks-in		the [first] source range		in	matrix { A[], B[], E[], Q[] }	*/
			mxF,		/*	matrix index				marks-in		the second source range	in	matrix { A[], B[], E[], Q[] }	*/
			mxZ, mxE,	/* 	matrix index				marks-out	the source range			in	matrix { A[], B[], E[], Q[] }	*/
		//	pre_xc,		/*	cycla count	(zero-based )	tracks		the pre-op mod. range		in	char *	cube				*/
			post_xc,		/*	cycla count	(zero-based )	defines		the post-op mod. range		in	char *	cube				*/
			pre_c,		/*	cycla count				tracks		the pre-op mod. range		in	char *	cube				*/
			post_c,		/*	cycla count				defines		the post-op mod. range		in	char *	cube				*/
	pre_c0,	pre_c1,
	pre0_c,	pre1_c,
	post0_xc,	post1_xc,
	post0_c,	post1_c,
			dis_c,
			dis_q,		/*	q-data length				defines		the q-data displacement 	in	char *	cube				*/
			pre_q,		/*	q-data length sum			totals		the pre-op  mod. cycla		in	char *	cube				*/
			post_q,		/*	q-data length sum			totals		the post-op mod. cycla		in	char *	cube				*/
	post0_q,		post1_q,	/*	q-data length sums		do the same,	but when fragmenting		into	char *	cube & cube_			*/
	post0_qS,	post1_qS,
	cube0_q,		cube1_q,
			sign;
char unsigned
			q0,	q1,	q2,		/*	q-field lengths			total		the q-data length			of any given cyclum			*/
			q,	q_,	qx,		/*	q-data length			defines 		the read size  increment		in	char *	cube / cube_		*/
			oq,	oq_,	oqx,		/*	q-data offset			iterates		the read position			in	char *	cube / cube_ / buf	*/
			oq0,	oqZ, oqZ_;	/*	q-data offsets 		mark in/out	the destination range		in	char *	cube				*/
char			ic,	ic_,	icx,		/*	tip indeces			iterate		the read position			in	char *	cube / cube_ / buf	*/
			mc0, mcZ,		/*	cyclum indeces		mark in/out	the destination range		in	char *	cube				*/
			mcF, mcE,		
			zc,	zc_,	_zc, 		/*	cyclum index 			bounds		the terminating cyclum		of	char *	cube / cube_		*/
			post_zc,	post_ec,
			vc,	vc_;			/*	cyclum count			defines		vacant capacity available	in	char *	cube / cube_		*/
char unsigned	rem_c,			/*	cyclum count			balances		the terminating fragment	in	char *	SvPVbyte( *( AvARRAY( avICE ) +iCZ), CS )	*/
			bal_c;			/*	cyclum count			balances		the intermediate fragment[s]	in	char *	SvPVbyte( *( AvARRAY( avICE ) +iCX), CS )	*/
ui64			bal_C;
//differential metrics will go negative
char			rel_q,rel_qq,	/*	q-data offset		which compares	pre & post op q-data totals	in	matrix { A[], B[], E[], Q[] }	*/
			rel_c, rel1_c,	/*	cyclum offset		which compares	pre & post op cyclum counts	in	matrix { A[], B[], E[], Q[] }	*/
			dis_i,	dis1_i,
					lead1_c,
			lead0_q,	lead1_q,
			dis0_q,	dis1_q;

AV			*avOut;
SV			*svOp;
svtype		svt;
long long int	displacement, d, D;

char *	opStat[5]={"null", "ok", "mod", "new", "over"};
enum	opStat{	null, ok, mod, new, over }
/*		2D			1D			*/
		F[	256 ],	Fu,	Fv;		/* status enumerator			*/
ui64		E[	256 ],	Eu,	Ev,	Ez,	/* "Epsilon" values	which bound	the absolute coordinates	in	matrix { A[], B[], E[], Q[] }	*/
		X[	256 ],	Ax,	Bx,	Ex,	/* absolute coord.s	which define	decoded application data	in	matrix { A[], B[], E[], Q[] }	*/
							E_,
		A[	256 ],	Au,	Av,		/* relative coord.s	which define	each negative cyclum phase	in	matrix { A[], B[], E[], Q[] }	*/
		B[	256 ],	Bu,	Bv;		/* relative coord.s	which define	each positive cyclum phase	in	matrix { A[], B[], E[], Q[] }	*/
ui08 	Hx[	256 ],				/* header codes	which alloc.	q-data field space			in	char *	cube			*/
		I[	256 ],				/* cycla indeces	which align	pre-op byte positions		in	char *	cube			*/
								/*				with			post-op matrix indeces		in	matrix { A[], B[], E[], Q[] }	*/
		Q[	256 ],	Qx, Qu,	Qv,		/* q-data lengths	which define	each read increment		in	char *	cube			*/
		_Q[	256 ],				/* q-data lengths	which define	each write increment		in	char *	cube			*/
		O[	256 ],				/* q-data offsets	which mark	each read position			in	char *	cube			*/
		_O[	256 ];				/* q-data offsets	which mark	each write position			in	char *	cube			*/
ui64		G[	256 ];				/* "cube" indeces	which relate	cube->matrix mapping		for debugging purposes only.		*/
char		cmpZ	=0;
long long int		rel_zC,	eji, _eji, alt,
				rack_iC	=0,		
				respliceAlt[	256	],
				respliceSrc[	256	],
				respliceDst[	256	],
				respliceIns[	256	],
				respliceCut[	256	];

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

SV*	av_del( SV* rvICE,	SV* svI,	SV* svN){	if( !SvROK( rvICE) ){	printf("\r!	ICE::av_del(): arg[0] is not an arrayref\n\t");	return &PL_sv_undef; }
	AV	*	av	= (AV*) SvRV(		rvICE	);
	svtype	t_xv	= SvTYPE( 	av		);	if( t_xv!=SVt_PVAV){	printf("\r!	ICE::av_del(): arg[0] is not an arrayref\n\t");	return &PL_sv_undef; }
										if( AvFILLp( av)==-1){	printf("\r!	ICE::av_del(): array is empty\n\t");			return &PL_sv_undef; }
	i64	i	= SvIVX( svI	),
		n	= SvIVX( svN	),
		ni;

	if( i	< 0 ){	n +=i;	i=0;	}
	ni = AvFILLp( av) -i -n;
	if( ni	< 0 ) 	n +=ni;
	if( n	< 1 )				return &PL_sv_no;
	AvDELETE( av, i, n);		return &PL_sv_yes;
	}

#define	ReICEuOx(		$u, $v)				if( O[$u]==0 ) printf("\n!	ReICEuOx( %d, %d ): mx step u does not seem to have been read-in (O[%d]==0)\n\n", $u, $v, $u ); \
	if( A[$u]< 8){	if( B[$u]< 8 ){	Hx[$u] =	/*	0x00 |*/	(				B[$u]    << 3 ) |				A[$u];		_O[$v] = _O[$u];	_Q[$u]=0;			}	\
				else		{	Hx[$u] =  	0x80 |( (	q=zIndexOf(		B[$u] ) )<< 3 ) |				A[$u];		_O[$v] = _O[$u] +(	_Q[$u]=1 +q		);	}	\
	}else{		if( B[$u]< 8 ){	Hx[$u] =  	0x40 |(					B[$u]    << 3 ) | ( q=zIndexOf( 	A[$u] ) );		_O[$v] = _O[$u] +(	_Q[$u]=1 +q		);	}	\
				else		{	Hx[$u] =  	0xC0 |( (	q1=zIndexOf(		B[$u] ) )<< 3 ) | ( q0=zIndexOf(	A[$u] ) );		_O[$v] = _O[$u] +(	_Q[$u]=2 +q0 +q1	);	}	\
		}

#define	ReICEuO(		$u, $v)																			_O[$u] = O[$u];	\
	if( A[$u]< 8){	if( B[$u]< 8 ){	Hx[$u] =	/*	0x00 |*/	(				B[$u]    << 3 ) |				A[$u];		_O[$v] = O[$u];	_Q[$u]=0;			}	\
				else		{	Hx[$u] =  	0x80 |( (	q=zIndexOf(		B[$u] ) )<< 3 ) |				A[$u];		_O[$v] = O[$u] +(	_Q[$u]=1 +q		);	}	\
	}else{		if( B[$u]< 8 ){	Hx[$u] =  	0x40 |(					B[$u]    << 3 ) | ( q=zIndexOf( 	A[$u] ) );		_O[$v] = O[$u] +(	_Q[$u]=1 +q		);	}	\
				else		{	Hx[$u] =  	0xC0 |( (	q1=zIndexOf(		B[$u] ) )<< 3 ) | ( q0=zIndexOf(	A[$u] ) );		_O[$v] = O[$u] +(	_Q[$u]=2 +q0 +q1	);	}	\
		}

#define	ReICEu(			$u )			\
	if( A[$u]< 8){	if( B[$u]< 8 ){	Hx[$u] =	/*	0x00 |*/	(				B[$u]    << 3 ) |				A[$u];						_Q[$u]=0;			}	\
				else		{	Hx[$u] =  	0x80 |( (	q=zIndexOf(		B[$u] ) )<< 3 ) |				A[$u];						_Q[$u]=1 +q;			}	\
	}else{		if( B[$u]< 8 ){	Hx[$u] =  	0x40 |(					B[$u]    << 3 ) | ( q=zIndexOf( 	A[$u] ) );						_Q[$u]=1 +q;			}	\
				else		{	Hx[$u] =  	0xC0 |( (	q1=zIndexOf(		B[$u] ) )<< 3 ) | ( q0=zIndexOf(	A[$u] ) );						_Q[$u]=2 +q0 +q1;		}	\
		}


#define	ReICE(	$v, $pk, $pq )		\
	if( A[$v]< 8){	if( B[$v]< 8 ){	*$pk   =	/*	0x00 |*/	(				B[$v]    << 3 ) |				A[$v];													_Q[$v]=0;		}	\
				else		{	*$pk   =		0x80 |( (	q=zIndexOf(		B[$v] ) )<< 3 ) |				A[$v];		switch( q ){ qCASTa(	B[$v],			$pq ); }	_Q[$v]=1 +q;		}	\
	}else{		if( B[$v]< 8 ){	*$pk   =	  	0x40 |(					B[$v]    << 3 ) | ( q=zIndexOf( 	A[$v] ) );		switch( q ){ qCASTa(			A[$v],	$pq ); }	_Q[$v]=1 +q;		}	\
				else		{	*$pk   =	  	0xC0 |(	q=( (	q1=zIndexOf(	B[$v] ) )<< 3 ) | ( q0=zIndexOf(	A[$v] ) ) );	switch( q ){ qCASTab(	B[$v],	A[$v], 	$pq ); }	_Q[$v]=2 +q0 +q1;	}	\
		}

#define	ReICEzSV_(			$v, $call )																											pqz=cube_ +CS_  -	Q[$v];				\
	if( A[$v]< 8){	if( B[$v]< 8 ){	cube_[zc_]=/*	0x00 |*/	(				B[$v]    << 3 ) |				A[$v];															Q[$v]=0;			}	\
				else		{	cube_[zc_]=	0x80 |( (	q=zIndexOf(		B[$v] ) )<< 3 ) |				A[$v];		switch( q ){ qCASTa(	B[$v],			pqz ); }			Q[$v]=1 +q;		}	\
	}else{		if( B[$v]< 8 ){	cube_[zc_]=  	0x40 |(					B[$v]    << 3 ) | ( q=zIndexOf( 	A[$v] ) );		switch( q ){ qCASTa(			A[$v],	pqz ); }			Q[$v]=1 +q;		}	\
				else		{	cube_[zc_]=  	0xC0 |(	q=( (	q1=zIndexOf(	B[$v] ) )<< 3 ) | ( q0=zIndexOf(	A[$v] ) ) );	switch( q ){ qCASTab(	B[$v],	A[$v], 	pqz ); }			Q[$v]=2 +q0 +q1;	}	\
		}			CS_=O[ $v ]+Q[ $v];	if( CS_<16){ printf("\n_set( ): CS_( %lld ) <16	catch #10-%d\n",CS_, $call );	exit(11+$call);	}	\
	SvCUR_set( sv_,	CS_ );


#define	ReICEzSV(			$v, $call )																											pqz=cube +CS  -	Q[$v];				\
	if( A[$v]< 8){	if( B[$v]< 8 ){	cube[zc]=/*	0x00 |*/	(				B[$v]    << 3 ) |				A[$v];															Q[$v]=0;			}	\
				else		{	cube[zc]=  	0x80 |( (	q=zIndexOf(		B[$v] ) )<< 3 ) |				A[$v];		switch( q ){ qCASTa(	B[$v],			pqz ); }			Q[$v]=1 +q;		}	\
	}else{		if( B[$v]< 8 ){	cube[zc]=  	0x40 |(					B[$v]    << 3 ) | ( q=zIndexOf( 	A[$v] ) );		switch( q ){ qCASTa(			A[$v],	pqz ); }			Q[$v]=1 +q;		}	\
				else		{	cube[zc]=  	0xC0 |(	q=( (	q1=zIndexOf(	B[$v] ) )<< 3 ) | ( q0=zIndexOf(	A[$v] ) ) );	switch( q ){ qCASTab(	B[$v],	A[$v], 	pqz ); }			Q[$v]=2 +q0 +q1;	}	\
		}			CS=O[ $v ]+Q[ $v];		if( CS<16){ printf("\nset( ): CS( %lld ) <16	catch #10-%d\n",CS, $call );	exit(11+$call);	}	\
	SvCUR_set( sv,	CS );


#define	reICE( $a, $b, $pk, $pq)			\
	if( $a< 8){	if( $b< 8	){	*$pk++	= /*	0x00 |*/	(				$b    << 3 ) |				$a;															}	\
				else		{	*$pk++	=  	0x80 |( (	q=zIndexOf(		$b ) )<< 3 ) |				$a;		switch( q ){ qCASTa(	$b,		$pq ); }	$pq +=1 +q;		}	\
	}else{		if( $b< 8	){	*$pk++	=  	0x40 |(					$b    << 3 ) | ( q=zIndexOf( 	$a ) );	switch( q ){ qCASTa(		$a,	$pq ); }	$pq +=1 +q;		}	\
				else		{	*$pk++	=  	0xC0 |(	q=( (	q1=zIndexOf(	$b ) )<< 3 ) | ( q0=zIndexOf(	$a ) ) );	switch( q ){ qCASTab(	$b,	$a,	$pq ); }	$pq +=2 +q0 +q1;	}	\
		}
#define	reICEx( $a, $b, $pk, $pq)			\
	if( $a< 8){	if( $b< 8	){	*$pk	= /*	0x00 |*/	(				$b    << 3 ) |				$a;															}	\
				else		{	*$pk	=  	0x80 |( (	q=zIndexOf(		$b ) )<< 3 ) |				$a;		switch( q ){ qCASTa(	$b,		$pq ); }					}	\
	}else{		if( $b< 8	){	*$pk	=  	0x40 |(					$b    << 3 ) | ( q=zIndexOf( 	$a ) );	switch( q ){ qCASTa(		$a,	$pq ); }					}	\
				else		{	*$pk	=  	0xC0 |(	q=( (	q1=zIndexOf(	$b ) )<< 3 ) | ( q0=zIndexOf(	$a ) ) );	switch( q ){ qCASTab(	$b,	$a,	$pq ); }					}	\
		}
#define	reICE0(  $a, $b, $pk, $pq) $pq =$pk +16;							\
	if( $a< 8){	if( $b< 8	){	*$pk	= /*	0x00 |*/	(				$b    << 3 ) |				$a;															}	\
				else		{	*$pk	=  	0x80 |( (	q=zIndexOf(		$b ) )<< 3 ) |				$a;		switch( q ){ qCASTa(	$b,		$pq ); }	$pq +=1 +q;		}	\
	}else{		if( $b< 8	){	*$pk	=  	0x40 |(					$b    << 3 ) | ( q=zIndexOf( 	$a ) );	switch( q ){ qCASTa(		$a,	$pq ); }	$pq +=1 +q;		}	\
				else		{	*$pk	=  	0xC0 |(	q=( (	q1=zIndexOf(	$b ) )<< 3 ) | ( q0=zIndexOf(	$a ) ) );	switch( q ){ qCASTab(	$b,	$a,	$pq ); }	$pq +=2 +q0 +q1;	}	\
		}

#define _Q( $u )	B[$u]< 8	? A[$u]< 8	?	0	\
									:	8	-(__builtin_clzll( A[$u] ) >>3 )	\
						: A[$u]< 8	?	8	-(__builtin_clzll( B[$u] ) >>3 )	\
									:	16	-(__builtin_clzll( A[$u] ) >>3 )	-(__builtin_clzll( B[$u] ) >>3 )
void _printAvOut(){
	int x, zO		= AvFILLp(	avOut	);
	STRLEN OL;
	char * pStr;

	for(x=0; x<= zO; ++x){
		pStr= SvPVX( sv= *(AvARRAY( avOut) +x) );
		printf( pStr );
		}
	}

#define __ToTEXT_ROW_ALLOC	224
void _toText(){
	av_push(		avOut,	newSVpvn(	"\n\n", 2 ) );
	STRLEN		pvS, CS, nCS, lenLnHd, lenSigHd, lenEOR1;
	char			row0[__ToTEXT_ROW_ALLOC ],
				row1[__ToTEXT_ROW_ALLOC ],
				oCell,
			*	pCell0,
			*	pCell1,
				fCellSpc[	32 ],
				fLnHd[	16 ],
				fSigHd[	32 ],
				fLnNum[	16 ],
				fCell0B0[	32 ],
				fCell0B1[	32 ],
				fCell0BX[	32 ],
				fCell1BX[	32 ],
				fSigLn[		32 ],
			*	pq;
	long long int	x,  iC=0,		zC = AvFILLp(		avICE ),	nC =zC +1;
	SV		**	svC0 =			AvARRAY(	avICE ),
			*	sviC=*( svC0	+zC );

	ui08		*	cube,
				edge, r0,	r1,	vecS, cellS, rowSize, avSize=3,
				Kc, Qc, ic=0, zc;
	ui64			Ac, Bc, Xc, Ec,	EC,		EzC;
	long double	log;
				log = log10l( (long double)	nC );
	nCS	= ceil(	log );

	if(	NULL	==	sviC	|| !SvOK( sviC ) ){	EzC=0; vecS=12; cellS=14;
	}else if( 3 != SvTYPE( sviC ) ){				EzC=0; vecS=12; cellS=14;
	}else{		cube = SvPVbyte( sviC, CS);
		if( cube==NULL){					EzC=0; vecS=12; cellS=14;
		}else{							EzC=*( (ui64*) cube +1 ) -1;
				log = log10l( (long double)	EzC );	/* "Epsilon" of cube zC (minus one) will be the largest number encoded	*/
		vecS=ceil( log );	cellS =vecS +2;
	}	}
	

/*	format the format strings to set the cell and line number sizes		if you change these, make sure the row allocations are good */
	sprintf( fLnHd,		"(%c%dllu) ",					37, nCS			);
	sprintf( fLnNum,	"[%c-%dllu] ",					37, nCS			);

	sprintf( fSigHd,	"[ %c%dlluEmax %c%dllub ]\n", 	37, vecS, 37, avSize	);
	sprintf( fSigLn,		"[ %c%dlluEmax %c%dllub ]\n",	37, vecS, 37, avSize	);

	sprintf( fCell0B0,	"%cc%cc%c-%dllu", 	 37,	37,	37, vecS		);
	sprintf( fCell0B1,	"  %c-%dllu", 	 				37, vecS		);
	sprintf( fCell0BX,	"  %c-%dllu",  					37, vecS		);
	sprintf( fCell1BX,	"..%c-%dllu",  					37, vecS		);

	lenLnHd	= sprintf( row0,			fLnHd,	nC			);
	rowSize	= lenLnHd +( cellS *8 ) +1;	/*	+1:	the "fLnNum" template used in regular rows is one space longer than	
											the "fLnHd" template used in the header	*/
	lenSigHd	= sprintf( row0 +rowSize,	fSigHd,	EzC, avSize	);
	if( rowSize +lenSigHd >__ToTEXT_ROW_ALLOC ){	printf("\n!	_toText(): row allocation is too low!  Increase at least to %d bytes!\n\n", rowSize +lenSigHd );
											return;	}

	edge = lenLnHd;	while( edge< rowSize	){	*( (ui64 *)(	row0	+edge )	) = 0x5F5F5F5F5F5F5F5F;	edge += 8;	}
	edge = lenLnHd;	while( ic< 8){							row0[	edge	] = 35;
														row0[	edge+1	] = 48 +ic++;				edge += cellS;	}

	edge = 0;			 while( edge< cellS		){	*( (ui64 *)(	fCellSpc	+edge )	) = 0x2020202020202020;
											*( (ui64 *)(	row1	+edge )	) = 0x2020202020202020;	edge += 8;	}
	fCellSpc[ cellS ] =0;

	pvS = sprintf( row0 +rowSize, fSigHd, EzC, 123 );
	av_push( avOut, newSVpvn( row0, rowSize +lenSigHd ) );

	lenEOR1 = sprintf( row1 +rowSize, "  \n\n" );

	Ec=0;
	for( iC=0; iC <= zC;  ++iC){
		sviC = *( svC0 +iC );		if(NULL	==	sviC		){ pvS =sprintf( aString, "\r[%llu]: NULL\n",				iC); av_push( avOut, newSVpvn( aString, pvS ) );	continue;	}
								if( !SvOK( sviC )		){ pvS =sprintf( aString, "\r[%llu]: ! SvOK\n",				iC); av_push( avOut, newSVpvn( aString, pvS ) );	continue;	}
								if( SvTYPE( sviC )!=3	){ pvS =sprintf( aString, "\r[%llu]: SVTYPE != SVt_RV\n",	iC); av_push( avOut, newSVpvn( aString, pvS ) );	continue;	}
		cube=SvPVbyte( sviC,  CS );	if( cube==NULL		){ pvS =sprintf( aString, "\r[%llu]: SvPVbyte(...)==NULL\n",	iC); av_push( avOut, newSVpvn( aString, pvS ) );	continue;	}
		pq	= cube +16;
		zc= zIndexOf( *( (ui64*) cube ) );
		
		sprintf( row0,			fLnNum,	iC	);
		sprintf( row0 +rowSize,	fSigLn,		*( (ui64*) cube +1 ), CS	);

		pCell0 =row0 +lenLnHd;
		pCell1 =row1 +lenLnHd;

		for( ic=0; ic <=zc;  ++ic ){	Kc = cube[ ic ];	_deICE( cube, CS, Kc, pq, Qc, Ac, Bc);	Ec =( Xc= Ac +Ec ) +Bc;
			if(				Bc<2	){
				if(	Ac==0||	Bc==0	)	sprintf( pCell0, fCell0B0, Ac? 32: 65, Bc? 32: 66, Xc	);
				else						sprintf( pCell0, fCell0B1, Xc	);	sprintf( pCell1, fCellSpc		);
			}else{
				if(	Ac==0 )				sprintf( pCell0, fCell0B0, Ac? 32: 65, Bc? 32: 66, Xc	);
				else						sprintf( pCell0, fCell0BX, Xc	);	sprintf( pCell1, fCell1BX,	Ec-1	); 
				}
			pCell0 +=cellS;
			pCell1 +=cellS;
			}
		while( ic++< 8 ){	sprintf( pCell0, fCellSpc );		sprintf( pCell1, fCellSpc );
			pCell0 +=cellS;
			pCell1 +=cellS;
			}

		Ec =*( (ui64*) cube+1);

		av_push(		avOut,	newSVpvn(	row0, rowSize +lenSigHd	) );
		av_push(		avOut,	newSVpvn(	row1, rowSize +lenEOR1	) );
		}

	av_push(			avOut,	newSVpvn(	"\n\n", 2 ) );
	}
void	_toHV(){					hvOut = newHV();
	ui64			x, Ax, Bx, Ex=0,	i=0;
	char			ic, zc,
				key[ 8 ];
	ui08			Qx,	Ki, bs;
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
						zc= zIndexOf( *( (ui64*)	cube ) );
		for(	ic=0;  ic<=	zc; ++ic ){		Ki	=	cube[ ic ];	 deICE( Qx, Ax, Bx );
					x =Ex +Ax;
			for( Ex =	x +Bx;  x< Ex;  ++x ){	bs = 	__builtin_clzll( x)	&0xFFFFFFFFFFFFFF00;
				*( (ui64*) key )= x;	//<< bs;
		
			src = hv_store( hvOut,	key,    	8, &PL_sv_undef, 0 );
				printf("\r...	_toHV(): cube %lld.%lld	hv_store( hvOut, \"%lld\", %d, &PL_sv_undef, 0)  returns SV** addr %llX\n", iC, ic, *( (ui64*) key), s, &**src);	

		}	}	}

	}
void	_screenKeys(){
//	hvArg is set already
	miss =0;	// "hit" and "dis" would always have the same value— no need for "hit"
	ui64			Ax, Bx, Ex, x;
	ui08			Qx,	Ki,
			*	cube,
			*	pq;
	SSize_t		hit;	//displacement
	STRLEN		CS;
	SV		**	src,
			**	dst,
			**	lim,
			**	svC0 = AvARRAY( avICE ),	*svC,
			**	svA0= AvARRAY( avArg ),	*svA;
	long long	int	lb = 0, 	V,	ea = AvFILLp(	avArg )+1,	I,
				ub=ea,	iC,	zC = AvFILLp(	avICE ),		i =	ub	 >>1;		if( ea==0	||zC==-1 ){	printf("\n_screenKeys: something's empty ub: %llu, zC: %llu\n", ub, zC);
																							return;	}
																		svA = *( dst= svA0 +i );

												cube = SvPVbyte(	*svC0, CS);
	char					ic,	zc = zIndexOf( *( (ui64*)	cube ) );	Ki = cube[0];	deICE0( Qx, x, Bx );  ic=0;
			for(	Ex=x  +Bx;	x< Ex;  ++x ){												
				while(		x !=SvIVX(	svA ) ){
					if(		x > SvIVX(	svA ) ){	lb	= i;	i =( i +ub	)>>1;	if( i==lb	)					goto _retry_x0_L0;
					}else{						ub	= i;	i =( lb + i	)>>1;	if( i==ub	)					goto _retry_x0_L0;
						}												svA = *(	dst= svA0 +i );
/* hit */				}			hit=1;	iC=0;	I = i++;	SvREFCNT_dec(	svA );  *	dst= &PL_sv_undef;	goto _next_x;
_retry_x0_L0:					++	miss;	ub=ea;	lb =0;	i =	ub	 >>1;	svA = *(	dst= svA0 +i );
				}

//	printf("\r_screenKeys(): loop 1\n");
	/* none of the keys in the first cyclum were hits.  Enter a loop to search the rest of the first cube for the first hit. */
		for(	ic = 1;		ic<=	zc;	++ic ){					Ki = cube[ ic ];	deICE( Qx, Ax, Bx );  x = Ex+Ax;
			for(	Ex=x  +Bx;	x< Ex;  ++x ){												
				while(		x !=	SvIVX(	svA ) ){
					if(		x > SvIVX(	svA ) ){	lb	= i;	i =( i +ub	)>>1;	if( i==lb	)					goto _retry_x0_L1;
					}else{						ub	= i;	i =( lb + i	)>>1;	if( i==ub	)					goto _retry_x0_L1;
						}												svA = *(	dst= svA0 +i );
/* hit */				}			hit=1;	iC=0;	I = i++;	SvREFCNT_dec(	svA ); *	dst=&PL_sv_undef;    	goto _next_x;		//	printf("\r..  	x( %-6llu ): found at index #%lld\n", x, i );
_retry_x0_L1:					++	miss;	ub=ea;	lb = 0;	i =	ub	 >>1;	svA = *(	dst= svA0 +i );
			}	}	if(*( (ui64*)	cube +1 ) != Ex ){											printf(	"\r!	cube #0 broken: computed( %llu ) vs. stored( %llu ) Epsilon values do not match!\n",			Ex, *( (ui64*) cube +1 ) );	goto _end; }
					if( pq-cube!=CS){														printf(	"\r!	cube #0 broken: computed( %llu ) vs. stored( %llu ) CS values do not match!\n",			pq-cube, CS );				goto _end; }
		
//	printf("\r_screenKeys(): loop 2\n");
	/* none of the keys in the first cube were hits.  Enter a loop to search the entire ICE array for the first hit. */
	for(		iC=1;		iC<=	zC;	++iC ){			cube = SvPVbyte(	*( svC0 +iC ), CS );
							zc = zIndexOf( *( (ui64*)	cube ) );	Ki = cube[0];	deICE0( Qx, Ax, Bx );  x = Ex+Ax;	  ic=0;
			for(	Ex=x  +Bx;	x< Ex;  ++x ){												
				while(		x !=SvIVX(	svA ) ){
					if(		x > SvIVX(	svA ) ){	lb	= i;	i =( i +ub	)>>1;	if( i==lb	)					goto _retry_x0_L2;
					}else{						ub	= i;	i =( lb + i	)>>1;	if( i==ub	)					goto _retry_x0_L2;
						}												svA = *(	dst= svA0 +i );
/* hit */				}			hit=1;			I = i++;	SvREFCNT_dec(	svA ); *	dst=&PL_sv_undef;    	goto _next_x;		//	printf("\r...  	x( %-6llu ): found at index #%lld\n", x, i );
_retry_x0_L2:					++	miss;	ub=ea;	lb =0;	i =	ub	 >>1;	svA = *(	dst= svA0 +i );
				}

//	printf("\r_screenKeys(): loop 3\n");
		for(	ic = 1;		ic<=	zc;	++ic ){					Ki = cube[ ic ];	deICE( Qx, Ax, Bx );  x = Ex+Ax;
			for(	Ex=x  +Bx;	x< Ex;  ++x ){												
				while(		x !=SvIVX(	svA ) ){
					if(		x > SvIVX(	svA ) ){	lb	= i;	i =( i +ub	)>>1;	if( i==lb	)					goto _retry_x0_L3;
					}else{						ub	= i;	i =( lb + i	)>>1;	if( i==ub	)					goto _retry_x0_L3;
						}												svA = *(	dst= svA0 +i );
/* hit */				}			hit=1;			I = i++;	SvREFCNT_dec(	svA ); *	dst=&PL_sv_undef;		goto _next_x;		//	printf("\r....  	x( %-6llu ): found at index #%lld\n", x, i );
_retry_x0_L3:					++	miss;	ub=ea;	lb =0;	i =	ub	 >>1;	svA = *(	dst= svA0 +i );
			}	}	if( *( (ui64*)	cube +1 ) != Ex ){											printf("\r!!	cube #%lld broken: computed( %llu ) vs. stored( %llu ) Epsilon values do not match!\n",	iC, Ex,	*( (ui64*) cube +1 ) );	goto _end; }
					if( pq-cube!=CS){														printf("\r!!	cube #%lld broken: computed( %llu ) vs. stored( %llu ) CS values do not match!\n",		iC, pq-cube, CS );				goto _end; }
		}
//	printf("\r_screenKeys(): nothing found\n");
	return;

	for(			;		iC<=	zC;	++iC ){			cube = SvPVbyte(	*( svC0 +iC ), CS );
							zc = zIndexOf( *( (ui64*)	cube ) );				pk=cube;	pq=cube+16;
		for(	ic = 0;		ic<=	zc;	++ic ){					Ki = cube[ ic ];	deICE( Qx, Ax, Bx );  x = Ex+Ax;
			for(	Ex=x  +Bx;	x< Ex;  ++x ){												
				while(		x !=SvIVX(	svA ) ){
					if(		x > SvIVX(	svA ) ){	lb	= i;	i=( i +ub	)>>1;	if( i==lb	)					goto _next_x;
					}else{						ub	= i;	i=( lb + i	)>>1;	if( i==ub	)					goto _next_x;
						}												svA = *(	lim= svA0 +i );
/* hit */				} V =    		lim - dst - hit;				SvREFCNT_dec(	svA ); *	lim=&PL_sv_undef;						// printf("\r.....  	x( %-6llu ): found at index #%lld\n", x, i );
/* collapse void */	if(	   V >0 )	{	src = dst + hit;		I = i;	do{	*dst++ = *src++; } while( src<	lim );
							} ++	hit;				++i;

_next_x:			if( i == ea){ AvFILLp( avArg ) -=hit; return; }
										ub=ea;	lb	= i ;	i =( lb+ub	)>>1;	svA = *(	lim= svA0 +i );
			}	}	if( *( (ui64*)	cube +1 ) != Ex ){											printf("\r!!!	cube #%lld broken: computed( %llu ) vs. stored( %llu ) Epsilon values do not match!\n",	iC,	Ex, *( (ui64*) cube +1 ) );	goto _end; }
					if( pq-cube!=CS){														printf("\r!!!	cube #%lld broken: computed( %llu ) vs. stored( %llu ) CS values do not match!\n",		iC, pq-cube, CS );				goto _end; }
		}
_end:
	lim= svA0 +ea;
	src= svA0 +lb;
	while( src< lim )	*dst++=*src++;
	AvFILLp( avArg ) -=hit;
	}
void	_screenHV(){
//	hvArg is set already
	N=hv_iterinit( hvArg );
	ui64			Ax, Bx, Ex=0,	i=0;
	char			ic, zc,
				key[ 8 ];
	ui08			Qx,	Ki,
			*	cube,
			*	pq;
	SV		**	sviC0  =	AvARRAY(  	avICE ),
			*	sv;
	STRLEN		CS, s;

	long long int	iC, zC  =	AvFILLp(  	avICE );
	printf("\r_screenHV(): avICE has %d+1 element[s]\n	hvArg has (%d) key[s]\n\n", zC, N);

	for(		iC=0; iC<= zC;  ++iC ){								sv = *( sviC0 +iC );
											cube = SvPVbyte(	sv,  CS );
		pq=									cube +16;
						zc= zIndexOf( *( (ui64*)	cube ) );
		for(	ic=0;  ic<=	zc; ++ic ){		Ki	=	cube[ ic ];	 deICE( Qx, Ax, Bx );
						*( (ui64*)  	key ) =Ex +Ax;
			for(	Ex	=	*( (ui64*)  	key ) +Bx;
						*( (ui64*)  	key )< Ex;
					++	*( (ui64*)  	key ) ){	//s =SizeOf( *( (ui64*)  key ) );
				sv= hv_delete( hvArg,	key,		8, 0 );
				if( &*sv ) --N;

				printf("\r...	_screenHV(): cube %lld.%lld	hv_delete( hvArg, \"%lld\", %d, 0)  returns SV addr %llX	\n", iC, ic, *( (ui64*) key), s, &*sv );	
		}	}	}
	printf("\r...	_screenHV() %d key[s] remain\n", N );
	}
void	_print_mx( unsigned short caller ){
	printf("\n_print_mx(	caller==%-4d )\n", caller, u, v, w);
	long long int		col[		14	],
					rowSize;
	STRLEN			xsl;
	SV*				xsv;
	ui64				e1, c, C, i, s;
	ui08				x=255, y, z;
	char				h=1, r=0,
					txt[		24 *14 *13 ]={13, 10},	//4368
				*	ptxt,
					size[		18	]={2},
					pos[		18	]={4};
/*	for( e1=0; e1< 4068; ++e1 )	txt[e1]=175;	*/	txt[4068]=0;

	const char	*	label[	13	] = {"", ">:", "Hx:", "A:", "B:", "E-1:", "I:", "O:", "_O:", "Q:", "_Q:", "stat:", "range:"},
				*	csUVW	="|uvw|",
				*	csUV	="|uv|",
				*	csUW	="|uw|",
				*	csU		="|u|",
				*	csV		="|v|",
				*	csW		="|w|";
	char			* csSPC	=" ",
				* stip0	=" . . . . . . . . . . . .",
				* stip1	=". . . . . . . . . . . . ",
				ugh[25];

	while( r< 13 ){	xsl = strlen( label[ r ] );								if( xsl >size[ 0 ] ) size[ 0 ]=xsl;		++r;	};
	r=0; c=1;
	while( x!=16 ){	s =1 + (char) ceil( log10l( (long double) Hx  	[ x ]		) );				size[ h ]= s>5? s: 5;
				s =1 + (char) ceil( log10l( (long double) A  	[ x ]		) );	if( s >size[ h ] )	size[ h ]=s;
				s =1 + (char) ceil( log10l( (long double) B  	[ x ]		) );	if( s >size[ h ] )	size[ h ]=s;
				s =1 + (char) ceil( log10l( (long double) E  	[ x ]-1	) );	if( s >size[ h ] )	size[ h ]=s;
				s =1 + (char) ceil( log10l( (long double) I  	[ x ]		) );	if( s >size[ h ] )	size[ h ]=s;
				s =1 + (char) ceil( log10l( (long double) O  	[ x ]		) );	if( s >size[ h ] )	size[ h ]=s;
				s =1 + (char) ceil( log10l( (long double) _O  	[ x ]		) );	if( s >size[ h ] )	size[ h ]=s;
				s =1 + (char) ceil( log10l( (long double) Q  	[ x ]		) );	if( s >size[ h ] )	size[ h ]=s;
				s =1 + (char) ceil( log10l( (long double) _Q  	[ x ]		) );	if( s >size[ h ] )	size[ h ]=s;
				c += size[ h ]+2;
				pos[ h ] =c;
				++h; ++x; }

/*	Alt+0175: ¯	*/		
	c=0;			
/*1:	col #	*/								sprintf( txt +c, fmtStrNl[	size[ 0 ] ],    	label[r++]		);	c+= size[ 0 ]+3;
				x=255;	for( h=1; h<18;  ++h ){	sprintf( txt +c, fmtLLU[	size[ h ] ],    	35,	x++		);	c+= size[ h ]+2;  	}

/*2: u|v|w cursors	*/
	rowSize = c;								sprintf( txt +c, fmtStrNl[	size[ 0 ] ],    	label[r++]		);	c+= size[ 0 ]+3;

				x=255;
	if( u==v)	if(	u==w){	for( h=1; h<18;  ++h ){	sprintf( txt +c, fmtStr[ size[ h ] ],	x==u? csUVW:	csSPC );	c+= size[ h ]+2;  ++x;	}
			}else{		for( h=1; h<18;  ++h ){	sprintf( txt +c, fmtStr[ size[ h ] ],	x==u? csUV:
																		x==w? csW:	csSPC );	c+= size[ h ]+2;  ++x;	}
				}
	else 	if(	u==w){	for( h=1; h<18;  ++h ){	sprintf( txt +c, fmtStr[ size[ h ] ],	x==u? csUW:
																		x==v? csV: 	csSPC );	c+= size[ h ]+2;  ++x;	}

			}else{		for( h=1; h<18;  ++h ){	sprintf( txt +c, fmtStr[ size[ h ] ],	x==u? csU:
																		x==v? csV:
																		x==w? csW:	csSPC );	c+= size[ h ]+2;  ++x;	}
				}
/*3: Hx		*/								sprintf( txt +c, fmtStrNl[	size[ 0 ] ],    label[r++]		);	c+= size[ 0 ]+3;
				x=255;	for( h=1; h<18;  ++h ){	sprintf( txt +c, fmt02X[	size[ h ] ], 120,	Hx[	x++ ]	);	c+= size[ h ]+2;	}
/*4: A		*/								sprintf( txt +c, fmtStrNl[	size[ 0 ] ],    label[r++]		);	c+= size[ 0 ]+3;
				x=255;	for( h=1; h<18;  ++h ){	sprintf( txt +c, fmtLLU[	size[ h ] ], 45, 	A[	x++ ]	);	c+= size[ h ]+2;	}
/*5: B		*/								sprintf( txt +c, fmtStrNl[	size[ 0 ] ],    label[r++]		);	c+= size[ 0 ]+3;
				x=255;	for( h=1; h<18;  ++h ){	sprintf( txt +c, fmtLLU[	size[ h ] ], 43, 	B[	x++ ]	);	c+= size[ h ]+2;	}
/*6: E-1		*/								sprintf( txt +c, fmtStrNl[	size[ 0 ] ],    label[r++]		);	c+= size[ 0 ]+3;
				x=255;	for( h=1; h<18;  ++h ){	sprintf( txt +c, fmtLLU[	size[ h ] ], 90, 	E[	x++ ]-1	);	c+= size[ h ]+2;	}
/*7: I		*/								sprintf( txt +c, fmtStrNl[	size[ 0 ] ],    label[r++]		);	c+= size[ 0 ]+3;
				x=255;	for( h=1; h<18;  ++h ){	sprintf( txt +c, fmtLLU[	size[ h ] ], 35, 	I[	x++ ]	);	c+= size[ h ]+2;	}
/*8: O		*/								sprintf( txt +c, fmtStrNl[	size[ 0 ] ],    label[r++]		);	c+= size[ 0 ]+3;
				x=255;	for( h=1; h<18;  ++h ){	sprintf( txt +c, fmtLLU[	size[ h ] ], 46, 	O[	x++ ]	);	c+= size[ h ]+2;	}
/*9: _O		*/								sprintf( txt +c, fmtStrNl[	size[ 0 ] ],    label[r++]		);	c+= size[ 0 ]+3;
				x=255;	for( h=1; h<18;  ++h ){	sprintf( txt +c, fmtLLU[	size[ h ] ], 44, 	_O[	x++ ]	);	c+= size[ h ]+2;	}
/*10: Q		*/								sprintf( txt +c, fmtStrNl[	size[ 0 ] ],    label[r++]		);	c+= size[ 0 ]+3;
				x=255;	for( h=1; h<18;  ++h ){	sprintf( txt +c, fmtLLU[	size[ h ] ], 196,	Q[	x++ ]	);	c+= size[ h ]+2;	}
/*11: _Q		*/								sprintf( txt +c, fmtStrNl[	size[ 0 ] ],    label[r++]		);	c+= size[ 0 ]+3;
				x=255;	for( h=1; h<18;  ++h ){	sprintf( txt +c, fmtLLU[	size[ h ] ], 205,	_Q[	x++ ]	);	c+= size[ h ]+2;	}
/*12: stat	*/								sprintf( txt +c, fmtStrNl[	size[ 0 ] ],    label[r++]		);	c+= size[ 0 ]+3;
				x=255;	for( h=1; h<18;  ++h ){	sprintf( txt +c, fmtStr[	size[ h ] ],	opStat[ F[ x++ ] ]	);	c+= size[ h ]+2;	}
/*13: range	*/								sprintf( txt +c, fmtStrNl[	size[ 0 ] ],    label[r++]		);	c+= size[ 0 ]+3;
	ptxt =txt +c;
	for( i=0;  i< rowSize;  i+=8 )	*( (ui64*)( ptxt +i ) ) = 0x2020202020202020;
						x =mx0 +1;	y =mxF +1;	z =mxZ +1;	//ptxt[ pos[ y ] ]=197;

	if(		mx0==mxZ)	if(	mx0==mxF ){			ptxt[ pos[ x ]		]=192;
												ptxt[ pos[ x ] +1	]=197;
												ptxt[ pos[ x ] +2	]=217;

						}else{					ptxt[ pos[ x ]		]=192;
												ptxt[ pos[ x ] +1	]=196;
												ptxt[ pos[ x ] +2	]=217;
												ptxt[ pos[ z ] +1	]=179;
							}
	else if(	mx0<mxZ)	if(		mx0==mxF	){	ptxt[ pos[ x ]		]=192;
												ptxt[ pos[ x ] +1	]=197;
												ptxt[ pos[ z ] +1	]=217;

						}else if(	mxZ==mxF	){	ptxt[ pos[ x ] +1	]=192;
												ptxt[ pos[ z ] +1	]=197;
												ptxt[ pos[ z ] +2	]=217;
						}else if(	mxF>mxZ
							||	mxF<mx0	){	ptxt[ pos[ x ] +1	]=192;
												ptxt[ pos[ y ] +1	]=179;
												ptxt[ pos[ z ] +1	]=217;

						}else{					ptxt[ pos[ x ] +1	]=192;
												ptxt[ pos[ y ] +1	]=197;
												ptxt[ pos[ z ] +1	]=217;
							}
						
	else		sprintf( txt +c, fmtStr[	size[ h ] ],	"[none]"	);

	if( c>4368){	printf( lightning );	printf("\n_print_mx(): (char *) txt allocation not big enough!  used %d bytes\n\n", c);	printf( lightning ); }
	printf( txt );
	printf( "\n\n\t");
	}
void _init_mx(){
	ui08	x=255;	post_zc=-1;

	u= v= w= mxF =mxZ =0;	mx0=0xFF;
	do{	F[x]=0;
		A[x]=	B[x]=	E[x]=	X[x]=	0;
		Hx[x]=	Q[x]=	_Q[x]=
		I[x]=		O[x]=	_O[x]=			0;
		} while( ++x != 255 );
/*	if(	O[ 255 ] !=16 ){	printf( lightning );
						printf("\n!	_init_mx(): O[ 255 ] was clobbered!\n");
						O[255]=16;	}
	if(	_O[ 255 ] !=0 ){	printf( lightning );
						printf("\n!	_init_mx(): _O[ 255 ] was clobbered!\n");
						_O[255]=0;	}
	*/
	_Q[255]=0;
	*( (ui64*) Hx	)	=
	*( (ui64*) Hx+1	)=0;

	}
void _init_mx_(){
	f =mx0=mxF=0xFF;
	do{	F[f]=0; E[f]=0;	} while( ++f != 15 );
	*( (ui64*) Hx	)	=
	*( (ui64*) Hx+1	)=0;

	}



void iCE( ui64 a,   ui64 b ){
		if( a <8){	if( b <8){	buf[ ++icx] =/*	0x00 |*/	(				b	<< 3 ) |				a;															}
				else{	buf[ ++icx] =	0x80 |( (	q=zIndexOf(		b ) )	<< 3 ) |				a;		switch( q ){ qCASTa(	b,		pqx ); }	pqx +=1 +q;		}
		}else{	if( b <8){	buf[ ++icx] =	0x40 |(					b	<< 3 ) | (	q=zIndexOf(	a ) ); 	switch( q ){ qCASTa(		a,	pqx ); }	pqx +=1 +q;		}
				else	{	buf[ ++icx] =	0xC0 |( ( q1=zIndexOf(		b ) )	<< 3 ) | (	q0=zIndexOf(	a ) ); 	switch( q ){ qCASTab(	b,	a,	pqx ); }	pqx +=2 +q0 +q1;	}
	}		}
void iCEp( ui64 a,   ui64 b ){		/* The "p" stands for "pointer", but this only differentiates the keybyte assignment; q-data assignment always uses a pointer.	*/
		if( a <8){	if( b <8){	*pk++	=/*	0x00 |*/	(				b	<< 3 ) |				a;															}
				else{	*pk++	=	0x80 |( (	q=zIndexOf(		b ) )	<< 3 ) |				a;		switch( q ){ qCASTa(	b,		pqx ); }	pqx +=1 +q;		}
		}else{	if( b <8){	*pk++	=	0x40 |(					b	<< 3 ) | (	q=zIndexOf(	a ) );		switch( q ){ qCASTa(		a,	pqx ); }	pqx +=1 +q;		}
				else	{	*pk++	=	0xC0 |(	q=( ( q1=zIndexOf(	b ) )	<< 3 ) | (	q0=zIndexOf(	a ) ) );	switch( q ){ qCASTab(	b,	a,	pqx ); }	pqx +=2 +q0 +q1;	}
	}		}

char vstepr0_mx(){	/*	Returns 1 if it steps past the end of the last cube; past the end of the entire ICE array.	*/
	printf("\rvstepr0_mx()\n\t");
																	lost_ic= 0;
	if( ic==zc ){
			do	{	if(	zC	==	iC ){	mxOVERSTEP( v );											return 1;
					}else{ RACK_SvCUT( iC ); ++iC;
						cube=CUBE( iC );	zc= zIndexOf(  *( (ui64*)	cube) );
						}		} while(	zc == -1);
			DeICE0v_KE(	u, v );
	}else{	DeICEv_KE(	u, v);
		}
	while( A[ v ] ==0){				B[u]+=B[v];  E[u]+=B[v];					++lost_ic;	if(ic!=0) printf("\r!vstepr0_mx(): strange monopole detected, cyclum %d, cube %d.\n\t", ic, iC );
		if( ic==zc ){
			do	{	if(	zC	==	iC ){	mxOVERSTEP( v );											return 1;
					}else{ RACK_SvCUT( iC ); ++iC;
						cube=CUBE( iC );	zc= zIndexOf(  *( (ui64*)	cube) );	lost_ic= 0;

						}		} while(	zc == -1);
			DeICE0v_KE(	u, v );
		}else{DeICEv_KE(	u, v );
		}	}																				return 0;
	}	
char vstepr0(){	/*	Returns 1 if it steps past the end of the last cube; past the end of the entire ICE array.	*/
																	lost_ic= 0;
	if( ic==zc ){
			do	{	if(	zC	==	iC ){	OVERSTEP( Qv, Av, Bv, Ev, Fv);								return 1;
					}else{ RACK_SvCUT( iC );	++iC;
						cube=CUBE( iC );	zc= zIndexOf(  *( (ui64*)	cube) );	Kx8=*( (ui64*) cube );
						}		} while(	zc == -1);

								deICE0ke(	Qv, Av, Bv, Ev );
	}else	Ki= cube[ ++ic ];		deICEe(		Qv, Av, Bv, Ev );

	while( Av ==0){				Bu+=Bv;  Eu+=Bv;						++lost_ic;	if(ic!=0) printf("\r!vstepr0(): strange monopole detected, cyclum %d, cube %d.\n\t", ic, iC );
		if( ic==zc ){
			do	{	if(	zC	==	iC ){	OVERSTEP( Qv, Av, Bv, Ev, Fv);								return 1;
					}else{ RACK_SvCUT( iC );	++iC;							lost_ic= 0;
						cube=CUBE( iC );	zc= zIndexOf(  *( (ui64*)	cube) );	Kx8=*( (ui64*) cube );
						}		} while(	zc == -1);

								deICE0ke(	Qv, Av, Bv, Ev );
		}else Ki= cube[ ++ic ];		deICEe(		Qv, Av, Bv, Ev );
		}																					return 0;
	}
short caseTest=0;
bool _alloc(){					zC = AvFILLp(	avICE );
	if( zC==-1){  AvINIT1(	avICE );	
			*AvARRAY(	avICE )=		newSVpvn(	cube0, 16 );										x=0;		caseTest|=256;	printf("	^+$		caseTest==%d\n\t", caseTest);	return 1;/* initialized */	
			}
	iC=0;	cube=SvPVbyte(	*(	svC0 = AvARRAY( avICE ) ),	CS );	Kx8 = *( (ui64*) cube );	zc = zIndexOf( Kx8);
	if( zc==-1 ){ sv_insert(			*svC0, 0, CS,		cube0, 16);										x=0;		caseTest|=512;	printf("	^+$!		caseTest==%d\n\t", caseTest);	return 1;/* initialized */
			}
					pqx	= buf +16;
	ic=0; 			pq	= cube+16;	Eu =0;
	Ki =Kx8;	deICEe(	Qu, Au, Bu,	Eu );	/* Ki will only take the 1st byte of Kx8  */
	rel_iC=0;							Ev=Eu;

/*	Case 1:	There are more than (1) free IDs in cyclum U.
			In order to take the first one, we have to append a new cyclum, shifting cyclum U forward to become cyclum V.
			The cube may already be at capacity with (8) cycla, so this may necessitate fragmenting the cube.					^+_-		*/
	if(			Au>1){ 		*( (ui64*) buf)= Kx8<<8;													x=0;		caseTest|=1;		printf("	^+_-		caseTest==%d\n\t", caseTest);
			//				reICEi0(	0,  	  	1,	buf, icx, pq );
			//				reICEi(	Au-1,	Bu,	buf, icx, pq );	if(		zc==0)	*pEx=Eu;
			//													else if(	zc==7)	goto _frag__alloc;
					icx =-1;	iCE(	0,    	1		);
							iCE(	Au-1, Bu		);			if(		zc==0)	*pEx=Eu;
														else if(	zc==7)	goto _frag__alloc;
	}else{ pk =cube; /* iCEp() iterator */
/*	Case 2:	There is exactly (1) free ID in cyclum U.																	^+-		*/
		if(		Au==1 ){		iCEp(	0,    	Bu+1	);		if(		zc==0)	*( (ui64*) cube +1) =Eu;		x=0;		caseTest|=2;		printf("	^+-		caseTest==%d\n\t", caseTest);
/*	Case 3:	There are no free IDs in cyclum U, and there is only (1) cyclum in the only cube in avICE
			(disregarding any and all monopole cycla which follow it, which are invalid and will be annihilated ).					-+$		*/
		}else if( vstepr0() ){		if( Eu==0xFFFFFFFFFFFFFFFF)		return 0;
							iCEp(	0,    	Bu+1	);	 					*( (ui64*) cube +1) =Eu +1;	x=Eu;	caseTest|=4;		printf("	-+$		caseTest==%d\n\t", caseTest);
		/*	^ vstepr0 returns true when it runs past the end of avICE	*/							
		}else if( rel_iC ==0){
/*	Case 4:	There is exactly (1) free ID in cyclum [1], which gets taken, merging cycla U and [1].								-+-		*/
			if(	Av==1){		*( (ui64*) cube) >>=8;																			printf("	-+-		caseTest==%d\n\t", caseTest);
							iCEp(	0,		Bu+1 +Bv );  	if(		zc==0)	*( (ui64*) cube +1) =Ev;		x=Eu;	caseTest|=8;	
/*	Case 5:	There are more than (1) free IDs in cyclum [1].															-+_		*/
			}else{			iCEp(	0,		Bu+1	);  											x=Eu;	caseTest|=16;		printf("	-+_		caseTest==%d\n\t", caseTest);
							iCEp(	Av-1,	Bv		);	if(		zc==1)	*( (ui64*) cube +1) =Ev;
				}
		}else{ zc -= lost_ic; /* correct the number of valid cycla for any monopole cycla annihilated by vstepr0().	*/
/*	Case 4x:	There is exactly (1) free ID in cyclum V, but 
			(Steps [1..lost_ic] are absorbed by cyclum U. )  															-+|-		*/
			if(	Av==1){		if(		lost_ic >0 )	*( (ui64*) cube) >>= lost_ic >>3;											printf("	-+|-		caseTest==%d\n\t", caseTest);
							iCEp(	0,		Bu+1 +Bv );	if(		zc==0)	*( (ui64*) cube +1) =Ev;		x=Eu;	caseTest|=32;	
/*	Case 5x:	There are more than (1) free IDs in cyclum V,
			but cycla U and V bridge two cubes, and vstepr0 may have advanced cyclum offset ic by more than 1.  [1..7]			-+|_ 	*/
			}else if( zc<7){		if(		lost_ic==0)	*( (ui64*) cube) <<=8;
							else if(	lost_ic >1)	*( (ui64*) cube) >>=( (lost_ic -1) >>3);					x=Eu;	caseTest|=64;		printf("	-+|_		caseTest==%d\n\t", caseTest);
							iCEp(	0,		Bu+1	);											if(x!=Eu)	printf("\n\n\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n\n\n\n");
							iCEp(	Av-1,	Bv		);	if(		zc==0)	*( (ui64*) cube +1) =Ev;
/*	Case 5y:	There are more than (1) free IDs in cyclum V,
			but cycla U and V bridge two cubes, and vstepr0 may have advanced cyclum offset ic by more than 1.  [1..7],
			AND, the additional prepended cyclum we have to insert won't fit in cube iC +rel_iC.								-+|_ (frag) 	*/
			}else{			if(		lost_ic ==0)	*( (ui64*) buf)= Kx8<< 8;
							else if(	lost_ic >1)	*( (ui64*) buf)= Kx8>>( (lost_ic -1) >>3);					x=Eu;	caseTest|=128;	printf("	-+|_ (frag)	caseTest==%d\n\t", caseTest);
					icx =-1;	iCE(		0,	Bu+1	);
							iCE(		Av-1,	Bv		);						goto _frag__alloc;
		}	}	}

/*	Finalization for cases 2..5, 4x & 5x		*/
	if(		rel_iC<0){		AvDELETE(	avICE, 0, -rel_iC	);  }
	else if(	rel_iC>0){		AvINSERT(	avICE, 0,  rel_iC	);  }


						oq=pq -cube -16;	oqx =pqx -buf -16;
	sv_insert( *svC0, 16,	oq, 	buf+16,		oqx  );		/* prepend the additional q data at offet +16	*/
	return 1;
/*	Finalization for case 1 & case 5y		*/
	_frag__alloc:  FRAG_LoC_8p1;
	return 1;
	}


#define	ARG( $a )	SvIVX( svX=*(	AvARRAY(	avArg) +$a	) )
#define	ARG0		SvIVX( svX=*	AvARRAY(	avArg)		)


void deIceV_KE(){	DeICEv_KE(	u, v );	}
void deIceV_KEI(){	DeICEv_KEI(	u, v );	}

void _rack( unsigned short caller ){	//	"rack"		is the post-operational process of rendering changes to the elements of avICE.
	ui64		head, body, tail, top, mid;
	ui08		m, bs, hxbs, mc0xZ, mc1xZ;
/*	Going in, we expect (SV*) sv  to equal *( AvARRAY( iC ) ), and (char*) cube to equal SvPVbyte( sv... ).
	In the 'operating' state,	(SV*) sv,  	(char*) cube,   	(int) iC, 	and (uchar) zc 	represent "this" 'pre-operational' cube.
	The underscored aliases	(SV*) sv_, 	(char*) cube_,  	(int) iC_,	and (uchar) zc_	represent the cube preceding that one.

	However, upon return, this cube changes state to 'post-operational',thus then it is shunted down to the trailing-underscore analogs.
	It is not determined here whether this post-operational cube will precede the next to be operated on, but it may.

	The INTERLOC operations use both sets, since they bridge the logical namespace gap between two cubes, operating on both at once.
	However, those operations do not require racking or extrication, since those mutations are simple and direct in-situ assignments.

	*/

	if(mx0==0xFF ){	printf("\n!_rack(	caller==%-4d ): nothing to rack\n", caller);	goto _end__rack;		}
	if(cube==NULL){	printf("\n!_rack(	caller==%-4d ): *cube is NULL\n", caller);	goto _end__rack;		}

												if(	svC0	!=	AvARRAY( avICE )	){	printf( lightning );	printf(  "\n!	_rack(	caller==%-4d ): 	(SV**) \"svC)\" is off!\n");	svC0=AvARRAY( avICE );	}
	STRLEN	CS_chk;
	SV*		svChk=*(svC0 +iC);						if(	&*sv	!=	&*svChk			){	printf(  lightning );	printf(  "\n!	_rack(	caller==%-4d ): 	(SV*) \"sv\" is off!\n");		sv=svChk;				}
	ui08*	cubeChk=SvPVbyte( svChk, CS_chk );		if(	&*cube	!=	&*cubeChk		){	printf(  lightning );	printf(  "\n!	_rack(	caller==%-4d ): 	(char *) \"cube\" is off! \n");	cube=cubeChk;			}
												if(	CS		!=	CS_chk			){	printf(  lightning );	printf(  "\n!	_rack(	caller==%-4d ): 	(STRLEN) \"CS\" is off!\n");	CS=CS_chk;				}
	char		zcChk= zIndexOf(  *( (ui64*)	cube) );		if(	zcChk	!=	zc				){	printf( lightning );	printf( "\n!	_rack(	caller==%-4d ): 	(char) \"zc\" is off!\n");		zc= zcChk;				}
	char		ec0, ec1, ec=zc+1;

	if(	O[ mx0 ] != _O[ mx0 ] ){	printf( lightning ); printf("\n!!!	O[ mx0 ( %d ) ] ( %lld )   != _O[ mx0 ]( %lld )!!!\n\n", mx0, O[mx0], _O[mx0] );
							printf( lightning );	}
	pre_q		= O[   mcE ]	-O[   mc0 ];
//	pre_q		= O[   mcZ ]+Q[mcZ]  -O[   mc0 ];
	post_q		= _O[ mxE ]	-_O[ mx0 ];
	rel_q		= _O[ mxE ]	-O[	mxE ];
	rel_qq		= post_q		-pre_q;
	post_iC		= post_zc >>3;

	printf("\r_rack( %-4d ):	Determine fragmentation level (post_iC: %d )...\n", caller, post_iC);
//	_print_mx( caller );
//	switch( post_iC ){
	if(			post_zc< 0	){	/* Cycla count drops to zero, extinguishing cube iC.						*/	printf("\r	Cycla count drops to zero, extinguishing cube iC.	[NOT IMPLEMENTED]\n\t");

	/*	mark element iC for deletion		*/
		RACK_SvCUT( iC );

		//get entire length of  cube # iC and  add it to the negative phase of cyclum 0 in cube iC +1	Ki=cube[ 0];
		_cube= SvPVbyte(	_sv	= *( svC0 + iC -1	), _CS  );
		cube_ = SvPVbyte(	sv_	= *( svC0 + ++iC	),  CS_ );
		E_ = *( (ui64*) cube +1 ) -*( (ui64*)_cube +1 );
		printf("	The total namespace inside cube %d is (was) %lld\n", E_ );
		
		deICE0_( Qv, Av, Bv);			Av += E_;
		*( (ui64*) buf )=0;
		reICEx( Av, Bv, cube_, buf );
		sv_insert( sv_, 16, Qv, buf, q );
		
		if( q!=Qv ){	rel_q=q-Qv;	CS_ += rel_q;	}


		}
	else if(		post_zc<= 7	){	/* Cycla count is still within nominal capacity for cube iC.  					*/
		zc_			=		post_zc;
		post_xc		=		mxZ			-mx0;	/*			post_xc is zero-based—	it is used as a bitvector.	*/
		post_c		=		mxE			-mx0;	/*			post_c is one-based—	it is used in arithmetic.	*/
		pre_c		=		mcE				-mc0;
		rel_c		=		post_c			-pre_c;
		dis_q		=		CS		-O[		mxE	];
		dis_c		=		ec				-mcE;
#ifdef DEBUG
		printf("\n_rack(	caller==%-4d ):	cube%-3d: %3d..%-3d	 pre_c: %3d	 pre_q: %3d	    CS: %3d\n\t\t	matrix : %3d..%-3d	post_c: %3d	post_q: %3d	O[mxE]:	%3d\n\t\t\t\t\t	 rel_c: %3d   	 rel_q: %3d\n\t\t\t\t\t	 dis_c: %3d	rel_qq: %3d\n\t\t\t\t\t\t\t	 dis_q: %3d\n\n\t",
						caller,			iC,		mc0, mcZ,	pre_c,		pre_q,		CS,				mx0, mxZ,		post_c,		post_q,		O[mxE],					rel_c,		rel_q,				dis_c,		rel_qq,					dis_q );
#endif
	//	printf("\n	cube:	0x%016llX\n	Hx:	0x%016llX\n", *( (ui64*) cube ), *( (ui64*) Hx ) );
		
/*#####	SV RESIZE & PARASTALTIC DISPLACEMENT  / Q-DATA SHIFT	*/

		if(		rel_q >0	){	CS_= CS +rel_q;			cube_ =	SvGROW(	sv_= *(svC0 +iC ),	CS_+1	);
			if(	dis_q >0 ){//	printf("\r%c	shift (%d) byte[s] by %-3d  	cube[%d..%d] = cube[%d..%d]\n",
						//	175,			dis_q,		rel_q,		_O[	mxE ],	CS_	-1,
						//										O[	mxE ],	CS	-1	);
					for(  i = CS-1;		i >=O[mxE];	-- i )	{		cube_[ i +rel_q	]	= cube[ i ];
					}								}		cube_[CS_]		= 0;
															SvCUR_set(	sv_,	CS_  	);		if( CS_<16){ printf("\n_rack( %d ): CS_( %lld ) <16	catch #2\n", caller, CS_ );	exit(2);	}

		}else if(	rel_q <0	){	CS_= CS +rel_q;			cube_ =	cube;		sv_= *(svC0 +iC );
			if(	dis_q >0 ){//	printf("\r%c	shift (%d) byte[s] by %-3d  	cube[%d..%d] = cube[%d..%d]\n",
						//	174,			dis_q,		rel_q,		_O[	mxE ],	CS_	-1,
						//										O[	mxE ],	CS	-1	);
					for(  i = O[mxE];	i < CS;		++i )	{		cube_[ i +rel_q	]	= cube[ i ];
					}								}		cube_[CS_]		= 0;
															SvCUR_set(	sv_,	CS_  	);		if( CS_<16){ printf("\n_rack( %d ): CS_( %lld ) <16	catch #3\n", caller, CS_ );	exit(3);	}

		}else{				CS_= CS;					cube_ =	cube;		sv_= *(svC0 +iC );
			}

	//	printf("\n	cube_:	0x%016llX\n	Hx:	0x%016llX\n", *( (ui64*) cube_ ), *( (ui64*) Hx ) );
/*#####	SPLICE KEYBYTE SECTION	*/
		/*	crossover modified cycla (as uquad* Hx ) with unaltered leading / trailing in-situ    	*/
						mc0xZ = mc0 |(	post_xc<< 3 );
		if(		rel_c == 0 ){		/* Cycla count unchanged;	trailing cycla stay.			*/
			switch(		mc0xZ ){	SwCASE_XXOVER_01T(						*( (ui64*) Hx ),	*( (ui64*) cube_ )	)	}
		}else{					/* Cycla count has changed;	trailing cycla shift.			*/
			if(	rel_c >0){			bs =   rel_c	<< 3;	top = *( (ui64*) cube )	<<	bs;	}
			else{				bs = ( -rel_c )	<< 3;	top = *( (ui64*) cube )	>>	bs;	}
			switch(		mc0xZ ){	SwCASE_XXOVER_01K(	top,					*( (ui64*) Hx ),	*( (ui64*) cube_ )	) 	}
			}

	//	printf("\n	cube_:	0x%016llX\n	Hx:	0x%016llX\n", *( (ui64*) cube_ ), *( (ui64*) Hx ) );
		/*	re-encode modified cycla from matrix[ mx0..mxE ] to upper fragment char * cube_[ 16..16 +post_q -1 ]	*/
		if( post_q ){	m=mx0;	pq_  = cube_ +O[ mx0 ];	
				//	printf("\r%c	re-cast (%d) byte[s] q-data for keybyte[s]	Hx[ %2d..%2d ]	to cube_[ %d..%d ] \n",
				//		251,				post_q,						mx0, mxZ,		O[mx0], _O[mxE]-1 );
			do	{ //	printf("\r%c	re-cast (%d) byte[s] q-data for keybyte	Hx[ %2d ]( 0x%02X )	to cube_[ %d..%d]\n",
				//		251,				_Q[m],						m,	Hx[ m ],		pq_-cube_, pq_ +_Q[m] -cube_ -1);
				switch( Hx[ m ] ){  hiCASTt0inc(	A[m], B[m], pq_ )	}
				} while( ++m< mxE );
			}
	//	printf("\n	cube_:	0x%016llX\n	Hx:	0x%016llX\n", *( (ui64*) cube_ ), *( (ui64*) Hx ) );
		}

	else if( 		post_zc<= 15	){	/* Cycla count exceeds the capacity of cube iC, splitting it in two.  		*/
/*______	 post_ec:_____	0..post_zc:________	ec0:_____	0.._zc:____________	ec1:_____	0..zc_:___________
		(16)			0..15				(8)		0..7,				(8)		0..7
		(15)			0..14				(8)		0..7,				(7)		0..6
		(14)			0..13				(7)		0..6,				(7)		0..6
		(13)			0..12				(7)		0..6,				(6)		0..5
		(12)			0..11				(6)		0..5,				(6)		0..5
		(11)			0..10				(6)		0..5,				(5)		0..4
		(10)			0..9					(5)		0..4,				(5)		0..4
		(9)			0..8					(5)		0..4,				(4)		0..3			*/
		post_ec	= post_zc  +1;
		_zc		= post_zc	>>1;				ec0	=_zc +1;
		zc_		= post_zc		-ec0;		ec1	=zc_ +1;
		mxF		= post_ec	-ec1;

	/*	read ahead to the fragment boundary if the mx cursor hasn't made it there	*/
		if(			u< mxF ){	/*	_O[v]=_O[u]+_Q[u]; 	*/	if( F[ v ] == null )	deIceV_KEI();
			while(	v< mxF ){ u=v++;	_O[v]=_O[u]+Q[u];							DeICEv_KEI( u, v );	
			}	}

	/*	retain char * pointer and char * length of pre-op cube iC for final step later	*/
		_cube	= cube;
		_sv		= *(svC0 +iC );
	//	preCS	= CS;	//we're going to leave CS alone after all

			
/*#############		MOD' CYCLA SEQUESTERED TO LEFT FRAGMENT				#############	*/
/*######	|	|								|								|		######	*/
/*######	|-1	|0	1	2	3	4	5	6	7	|8	9	10	11	12	13	14	15	|		######	*/
/*######	|null	|_—	_—	_—	_—	_+	_+	_+	_+	|_—	_—	_—	_—	_—	_—	_—	_—	|		######	*/
/*######	|^	|				^. . . .Hx	 . . . .$	|								|		######	*/

		if(		mxZ< mxF ){	_CS =	_O[		mxF   ];	/*	printf("\r######	Lower fragment envelops the mod range.\n");	*/
			post_xc	=		mxZ			-mx0;	/*			post_xc is zero-based—	it is used as a bitvector.	*/
			post_c	=		mxE			-mx0;	/*			post_c is one-based—	it is used in arithmetic.	*/
			pre_c	=		mcE				-mc0;
			rel_c	=		post_c			-pre_c;
			cube1_q	=		CS		-O[  	mxF  	];
		//	dis0_q	=		_CS -1	-_O[  	mxE ];		see "2026-01-08 debug LSeq dis0_q A.txt" and 2026-01-08 debug LSeq dis0_q B.txt"
			dis0_q	=		_CS		-_O[  	mxE  	];


/*######	UPPER FRAGMENT [1]:	SV SETUP	*/
		/*	create new cube to serve as the higher fragment	*/
			CS_		= 16 +cube1_q;		
			sv_		= newSVpvz( 0x6 |	CS_	);		// round sv_ allocation up to the nearest quad, +0 / -1
			SvCUR_set(			sv_,	CS_	);
			cube_  	= SvPVbyte(	sv_,	CS_	); 
			cube_[ CS_ ] = 0;
			*( (ui64*) cube_+1 ) =		*( (ui64*) cube+1 );	/* set Epsilon of upper fragment (it carries the original)	*/
			*( (ui64*) _cube+1 ) =		E[ mxF -1	];	/* set Epsilon of lower fragment while we're at it			*/
#ifdef DEBUG
			printf("\n_rack(	caller==%-4d ):	cube%-3d: %3d..%-3d	 pre_c: %3d	 pre_q: %3d	    CS: %-2d bytes\n\t\t	matrix : %3d..%-3d	post_c: %3d	post_q: %3d	   _CS: %-2d bytes (		_O[ mxF ]( %d ) )\n\t\t\t\t\t	 rel_c: %3d   	 rel_q: %3d	   CS_: %-2d bytes ( CS +16 -	_O[ mxF ]( %d )\n\t\t\t\t\t\t\t	 dis_q: %3d\n	mods: L\n\n\t",
							caller,			iC,		mc0, mcZ,	pre_c,		pre_q,		   CS,					mx0, mxZ,		post_c,		post_q,	_CS,						_O[ mxF ],				rel_c,		rel_q,		CS_,						_O[ mxF ],				dis_q );
			if( CS_<16){ printf("\n_rack( %d ): CS_( %lld ) <16	catch #4\n", caller, CS_ );	exit(4);	}
#endif

		/*	rack the new cube for now— all array splice operations are deferred until once-and-for-all call to _resplice()	*/
			RACK_SvINS( iC, sv_ );

/*######	UPPER FRAGMENT [1]:	SPLICE KEYBYTE SECTION		(L-Seq)									*/
		/*	copy the top part of the original cube to the upper fragment, at the pre-offset which corresponds to mxF.	*/
													*( (ui64*) cube_ ) =		*( (ui64*)(  cube+I[ mxF ]) );
			switch(	zc_ ){		SwCASE_LOWPASS_1IS(	*( (ui64*) cube_ )	);			}

/*			LOWER FRAGMENT [0]:	SPLICE KEYBYTE SECTION		(L-Seq)									*/
		/*	crossover modified cycla (as uquad* Hx ) with unaltered leading / trailing in-situ    	*/
							mc0xZ = mc0 |(	post_xc<< 3 );
			if(		rel_c == 0 ){		/* Cycla count unchanged;	trailing cycla stay.			*/
				switch(		mc0xZ ){	SwCASE_XXOVER_01T(						*( (ui64*) Hx ),	*( (ui64*) _cube )	)	}
			}else{					/* Cycla count has changed;	trailing cycla shift.			*/
				if(	rel_c >0){			bs =   rel_c	<< 3;	top = *( (ui64*) _cube )	<<	bs;	}
				else{				bs = ( -rel_c )	<< 3;	top = *( (ui64*) _cube )	>>	bs;	}
				switch(		mc0xZ ){	SwCASE_XXOVER_01K(	top,					*( (ui64*) Hx ),	*( (ui64*) _cube )	) 	}
				}

/*			LOWER FRAGMENT [0]		*/
		/*	trim everything off the lower fragment that went to the upper fragment.		*/
			switch( _zc ){			SwCASE_LOWPASS_1IS(	*( (ui64*) _cube )	);			}

/*######	UPPER FRAGMENT [1]:	SPLICE Q-DATA SECTION	(L-Seq)										*/
		/*	bulk move (cube1_q) bytes of trailing unaltered q-data to upper fragment								*/
			if( cube1_q ){		/*	dest: 					cube_[	16		..	CS_-1	] =				*/
							/*	src:						cube[	O[ mxF ]	..	CS-1	]				*/
			//	printf("\rmv	bulk move ( %d ) bytes of leading data:\n	cube_[%d..%d] = cube[%d..%d]\n",	cube1_q,
			//													16,			CS_-1,
			//													O[ mxF ],		CS-1	);	sign= O[ mxF ] >16? 243: 240;
				pqx 	= cube	+O[ mxF ];
				pq_	= cube_	+16;
				while( cube1_q >7 ){	*( (ui64*) pq_ ) = *( (ui64*) pqx );		pq_ +=8;	pqx+=8;	cube1_q-=8;	}
				while( cube1_q >3 ){	*( (ui32*) pq_ ) = *( (ui32*) pqx );		pq_ +=4;	pqx+=4;	cube1_q-=4;	}
				while( cube1_q >1 ){	*( (ui16*) pq_ ) = *( (ui16*) pqx );		pq_ +=2;	pqx+=2;	cube1_q-=2;	}
				while( cube1_q >0 ){	*( (ui08*) pq_ ) = *( (ui08*) pqx );	++	pq_;	++	pqx;	--	cube1_q;		}
				}

/*######	LOWER FRAGMENT [0]:	SV RESIZE & PARASTALTIC DISPLACEMENT  / Q-DATA SHIFT					*/

			if(		rel_q >0 )	{							 	_cube =	SvGROW(	_sv, _CS +1	);
				if(	dis0_q >0 ){															//	printf("\r%c	shift (%d) byte[s] by %-3d  	_cube[%d..%d]	= cube[%d..%d]\n",
																						//	175,			dis0_q,		rel_q,		_O[	mxE ],	_O[	mxF ] -1,
																						//										O[	mxE ],	O[	mxF ] -1	);
						for( i = O[ mxF ] -1;		i >=O[ mxE ];	-- i )	{	_cube[ i +rel_q	] =	_cube[ i ];	//	printf("\r%c\t\t\t	_cube[ %d +%d ]	= cube[ %d ];\n", 175, i, rel_q, i );
						}									}
			}else if(	rel_q< 0 )	{
				if(	dis0_q >0 ){															//	printf("\r%c	shift (%d) byte[s] by %-3d  	_cube[%d..%d]	= cube[%d..%d]\n",
																						//	174,			dis0_q,		rel_q,		_O[	mxE ],	_O[	mxF ] -1,
																						//										O[	mxE ],	O[	mxF ] -1	);
						for( i = O[ mxE ];		i <O[ mxF ];	++i )	{	_cube[ i +rel_q	] =	_cube[ i ];	//	printf("\r%c\t\t\t	_cube[ %d +%d ]	= cube[ %d ];\n", 174, i, rel_q, i );
				}		}									}	_cube[ _CS ]		= 0;
																SvCUR_set(		_sv,	_CS  	);			if( _CS<16){ printf("\n_rack( %d ): _CS( %lld ) <16	catch #6\n", caller, _CS );	exit(6);	}
				



		/*	re-encode modified cycla from op matrix[ mx0..mxF-1 ] to lower fragment char * _cube					*/
			if( post_q ){	m=mx0;		_pq = _cube +O[ mx0 ]; 
					//	printf("\r%c	re-cast q-data for keybyte[s] Hx[ %2d..%2d ]	to _cube[ %d..%d ] \n",
					//		251,								mx0, mxF-1,		O[mx0], _O[mxF]-1 );
				do	{//	printf("\r%c	re-cast q-data for keybyte Hx[ %2d ]( 0x%02X )	to _cube[ %d..%d]\n",
					//		251,								m,	Hx[ m ],		_pq-_cube, _pq +_Q[m] -_cube -1);
					switch( Hx[ m ] ){  hiCASTt0inc(	A[m], B[m], _pq )	}
					} while( ++m< mxF );
			}	}

/*#############		MOD' CYCLA SEQUESTERED TO RIGHT FRAGMENT				#############	*/
/*######	|	|						||		|								|		######	*/
/*######	|-1	|0	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	|		######	*/
/*######	|null	|_—	_—	_—	_—	_—	_—	|_—	_+	_+	_+	_+	_+	_—				|		######	*/
/*######	|^	|						|	^. . . . . . . . . . . . . . .$		||			|		######	*/
/*######		|					^_zc |	^mc0					||			|		######	*/
/*######		|						|0	1	2	3	4	5	6	||			|		######	*/

		else if(	mx0 >= mxF ){	_CS = O[ mxF ];	/*	printf("\r######	Upper fragment envelops the mod range.\n"); */
		// 	Cap'n Obvious Asserts:  In this case, mx0 >= mxF ( mod range start is gt/eq frag1 start).
			post_xc	=		mxZ			-mx0;	/*			post_xc is zero-based—	it is used as a bitvector.	*/
			post_c	=		mxE			-mx0;	/*			post_c is one-based—	it is used in arithmetic.	*/
			pre_c	=		mcE				-mc0;
			rel_c	=		post_c			-pre_c;
			rel1_c	=		rel_c	-I[		mxF		];

			cube0_q	=	O[ 	mxF ]			-16;		// only used once
			lead1_c	=		mx0			-mxF;
			lead1_q	=	O[	mx0 ]	-O[		mxF ];
		//	dis1_q	=		CS		-O[		mxZ ];
			dis1_q	=		CS		-O[		mxE	];
			dis1_i	=	I[	mxF	]	-		rel_c;


/*######	UPPER FRAGMENT [1]:	SV SETUP	*/
		/*	create new cube to serve as the higher fragment	*/
			CS_		= CS +rel_q   	-cube0_q;		// length of upper frag will be original length +rel_q less cube0_q
			sv_		= newSVpvz( 0x6 |	CS_	);		// round sv_ allocation up to the nearest quad, +0 / -1
			SvCUR_set(			sv_,	CS_	);
			cube_  	= SvPVbyte(	sv_,	CS_	); 
			cube_[ CS_ ] = 0;
#ifdef DEBUG
			printf("\n_rack(	caller==%-4d ):	cube%-3d: %3d..%-3d	 pre_c: %3d	 pre_q: %3d	    CS: %-2d bytes\n\t\t	matrix : %3d..%-3d	post_c: %3d	post_q: %3d	   _CS:	%-2d bytes (			O[ mxF ]( %d ) )\n\t\t\t\t\t	 rel_c: %3d   	 rel_q: %3d	   CS_:	%-2d bytes ( CS	+rel_q( %d ) +16	-O[ mxF ]( %d ) )\n\t\t\t\t\t\t\t	dis1_q: %3d\n	mods: R\n\n\t",
							caller,			iC,		mc0, mcZ,	pre_c,		pre_q,		CS,						mx0, mxZ,		post_c,		post_q,		_CS,							_O[ mxF ],				rel_c,		rel_q,		CS_,						rel_q,			O[ mxF ],						dis1_q );
			if( CS_<16){ printf("\n_rack( %d ): CS_( %lld ) <16	catch #7\n", caller, CS_ );	exit(7);	}
#endif
		/*	rack the new cube for now— all array splice operations are deferred until once-and-for-all call to _resplice()	*/
		//	++iC;
			RACK_SvINS( iC, sv_ );

/*######	UPPER FRAGMENT [1]:	SPLICE KEYBYTE SECTION	(R-Seq)			*/
		/*	prime the upper fragment's keybyte section for splicing with the upper split from the original.					*/
			*( (ui64*) cube_ )		=	*( (ui64*)( cube+I[ mxF ] ) );	/*	only the lead is kept over the next step.		*/

		/*	crossover high part of modified cycla (from Hx) with displacement (from char * _cube) to yield upper fragment	*/
						mc1xZ = lead1_c| ( post_xc<< 3 );
			if(		zc == mcZ	){																	*( (ui64*) cube_+1 ) = E[ mxZ ];			/* set Epsilon of upper fragment	( there is no displacement, so mxZ is the new ending cyclum)	*/
				switch(	mc1xZ ){	SwCASE_LPXOVER_01T(								*( (ui64*)( Hx +mxF ) ),	*( (ui64*) cube_ )  )  }
				//				^crossover wye									^body src			^head src / wye output

			}else if(	rel1_c==0	){																	*( (ui64*) cube_+1 )	= *( (ui64*) cube +1 );	/* set Epsilon of upper fragment	(there is a displacement, so Epsilon of pre-op cube is conserved)	*/
				switch(	mc1xZ ){	SwCASE_XXOVER_01T(								*( (ui64*)( Hx +mxF ) ),	*( (ui64*) cube_ )  )  }
			}else{																					*( (ui64*) cube_+1 )	= *( (ui64*) cube +1 );	/* set Epsilon of upper fragment	(there is a displacement, so Epsilon of pre-op cube is conserved)	*/		
				if(	rel1_c >0){		bs =   rel1_c	<< 3;	top = *( (ui64*) cube )	<<	bs;	}
				else{				bs = ( -rel1_c )	<< 3;	top = *( (ui64*) cube )	>>	bs;	}
				switch(	mc1xZ ){	SwCASE_XXOVER_01K(		top,						*( (ui64*)( Hx +mxF ) ),	*( (ui64*) cube_ )  )  }
				}

/*			LOWER FRAGMENT [0]		*/
			*( (ui64*) _cube+1 )	=			E[ mxF -1	];	/*	set Epsilon of lower fragment,  only now that 
															we've had a chance to conserve the old value
															in the upper fragment					*/
		/*	trim the lower fragment																	*/
			switch(		_zc	){	SwCASE_LOWPASS_1IS(		*( (ui64*) _cube )	)		}	

/*######	UPPER FRAGMENT [1]:	SPLICE Q-DATA SECTION 	(R-Seq)									*/
		/*	bulk move (lead1_q) bytes of leading unaltered q-data to upper fragment							*/
			pq_  = cube_ +16;
			if( lead1_q ){		/*	dest: 					cube_[	16		..	16+lead1_q	] =		*/
							/*	src:						cube[	O[ mxF ]	..	O[ mx0 ]		]		*/
			//	printf("\rmv	bulk move ( %d ) bytes of leading data:\n	cube_[%d..%d] = cube[%d..%d]\n",
			//						lead1_q,						16,					15+lead1_q,	
			//													O[ mxF ],				O[ mx0 ]-1	);	sign= O[ mxF ] >16? 243: 240;
				pqx = cube+O[ mxF ];
				while( lead1_q >7 ){	*( (ui64*) pq_ ) = *( (ui64*) pqx );		pq_ +=8;	pqx+=8;	lead1_q-=8;	}
				while( lead1_q >3 ){	*( (ui32*) pq_ ) = *( (ui32*) pqx );		pq_ +=4;	pqx+=4;	lead1_q-=4;	}
				while( lead1_q >1 ){	*( (ui16*) pq_ ) = *( (ui16*) pqx );		pq_ +=2;	pqx+=2;	lead1_q-=2;	}
				while( lead1_q >0 ){	*( (ui08*) pq_ ) = *( (ui08*) pqx );	++	pq_;	++	pqx;	--	lead1_q;		}
				}

		/*	re-encode modified cycla from matrix[ mx0..mxE ] to upper fragment char * cube_[ 16..16 +post_q -1 ]	*/
			if( post_q ){	m=mx0;
				q1= pq_ -cube_;
				pq_ =cube_ +q1;
				//		printf("\r%c	re-cast q-data for keybyte[s] Hx[ %2d..%2d ]	to cube_[ %d..%d ] \n",
				//			251,								mx0, mxZ,		q1,	15 +_O[ mxE] -O[ mxF ] );
				do	{//	printf("\r%c	re-cast q-data for keybyte Hx[ %2d ]( 0x%02X )	to cube_[ %d..%d ]\n",
					//		251,								m,	Hx[ m ],		pq_-cube_, pq_ +_Q[m] -cube_ -1);
					switch( Hx[ m ] ){  hiCASTt0inc(	A[m], B[m], pq_ )	}
					} while( ++m< mxE );
				}

		/*	bulk move (dis1_q) bytes of trailing unaltered q-data to upper fragment							*/
			if( dis1_q ){		/*	dest: 					cube_[	_O[ mxE] -post0_qS ..	CS_	-1 ] =	*/
							/*	src:						cube[	O[ mxE ],		 ..	CS	-1 ];		*/
			//	printf("\rmv	bulk move (%d) byte[s] of trailing data:\n	cube_[%d..%d] = cube[%d..%d]\n",
			//						dis1_q,						_O[	mxE] -cube0_q,	CS_	-1,
			//													O[	mxE ],			CS	-1 );		sign= post0_qS? 243: 240;
				pqx= cube +O[ mxE ];
				while( dis1_q >7 ){	*( (ui64*) pq_ ) = *( (ui64*) pqx );		pq_ +=8;	pqx+=8;	dis1_q-=8;	}
				while( dis1_q >3 ){	*( (ui32*) pq_ ) = *( (ui32*) pqx );		pq_ +=4;	pqx+=4;	dis1_q-=4;	}
				while( dis1_q >1 ){	*( (ui16*) pq_ ) = *( (ui16*) pqx );		pq_ +=2;	pqx+=2;	dis1_q-=2;	}
				while( dis1_q >0 ){	*( (ui08*) pq_ ) = *( (ui08*) pqx );	++	pq_;	++	pqx;	--	dis1_q;		}
				}

/*			LOWER FRAGMENT [0]: Resize						(R-Seq)								*/
			if(			CS !=	_CS	){//	printf("\r	resize char * _cube from (%d) byte[s] to (%d) byte[s]\n", CS, _CS );
				SvCUR_set(	_sv,	_CS	);			if( _CS<16){ printf("\n_rack( %d ): _CS( %lld ) <16	catch #8\n", caller, _CS );	exit(8);	}
				_cube[			_CS	]=0;
			}	}

/*#############		MOD' CYCLA DIVIDED ACROSS BOTH FRAGMENTS				#############	*/
/*######	|	|								|								|		######	*/
/*######	|-1	|0	1	2	3	4	5	6	7	8	|9	10	11	12	13	14	15	|		######	*/
/*######	|null	|_—	_—	_—	_—	_+	_+	_+	_+	|_+	_+	_+	_+	_*	_*	_—	_—	|		######	*/
/*######	|^	|				^. . . .	 . . . .	| . . . .	. . . .		. . . .	$			|		######	*/
		else	{					_CS  = _O[ mxF ];	/*	printf("\r######	Each fragment envelops part of the mod range.\n");	*/

		//	pre0_c	=	 I[	mxF ]	 		-mc0;	/*	not used?	*/
			pre1_c	= 		mcE		-I[		mxF		];
			post0_xc	= 		mxF -1			-mx0;
			post1_c	= 		mxE			-mxF;
			post1_xc	= 		mxZ			-mxF;
			rel1_c	= 		post1_c			-pre1_c;
			dis_c	=		ec				-mcE;

			post0_q	=	_O[	mxF ]	-_O[ 	mx0 	];		// this doesn't include any leading or trailing q, so it doesn't end in "S"
			post1_q	=	_O[	mxE ]	-_O[ 	mxF 	];		// this doesn't include any leading or trailing q, so it doesn't end in "S"
		//	pre1_q	=	O[	mxE ]	-O[		mxF 	];
			dis1_q	=		CS		-O[		mxE	];
			dis1_i	=	I[	mxF ] 			-rel1_c;			/* this offset shifts the pre-op trailing displacement to the post-op 2nd frag */

/*######	UPPER FRAGMENT [1]:	SV SETUP
		/*	create new cube to serve as the higher fragment	*/
			CS_		= 16 +post1_q +dis1_q;			// length of upper frag will be upper part of post-mod-q plus displacement
			sv_		= newSVpvz( 0x6 |	CS_	);		// round sv_ allocation up to the nearest quad, +0 / -1
			SvCUR_set(			sv_,	CS_	);
			cube_  	= SvPVbyte(	sv_,	CS_	); 
			cube_[ CS_ ] = 0;

#ifdef DEBUG
			printf("\n_rack(	caller==%-4d ):	cube%-3d: %3d..%-3d			 pre1_c: %3d	  pre_q: %3d	 CS: %-2d bytes\n\t\t	matrix : %3d..%-3d	post0_xc: %3d	post1_c: %3d	post1_q: %3d    _CS: %-2d bytes (				O[ mxF ]( %d ) )\n\t\t\t\t\t	   rel_c: %3d	  dis_c: %3d	 dis1_q: %3d    CS_: %-2d bytes (16 +post1_q( %d )	+dis1_q( %d )	)\n	mods: LR\n\n\t",		
							caller,			iC,		mc0, mcZ,			pre1_c,		pre_q,		CS,					mx0, mxZ,		post0_xc,		post1_c,		post1_q,		_CS,							O[ mxF ],					rel_c,		dis_c,		dis1_q,		CS_,					post1_q,		dis1_q				);
			if( CS_<16){ printf("\n_rack( %d ): CS_( %lld ) <16	catch #9\n", caller, CS_ );	exit(9);	}
#endif
		/*	rack the new cube for now— all array splice operations are deferred 'til once-and-for-all call to _resplice()	*/
		//	++iC;
			RACK_SvINS( iC, sv_ );

/*######	UPPER FRAGMENT [1]:	SPLICE KEYBYTE SECTION	(RL-Split)			*/
		/*	crossover high part of modified cycla (as uquad mid) with displacement (as char * _cube) to yield upper fragment	*/
			if(		dis_c == 0 ){	/*						*( (ui64*) cube_ ) =			*( (ui64*)( Hx+mxF ) );*/	*( (ui64*) cube_+1 ) = E[ mxZ ];			/* set Epsilon of upper fragment	( there is no displacement, so mxZ is the new ending cyclum)	*/	
				switch( post1_xc ){	SwCASE_LOWPASS_1I(								*( (ui64*)( Hx +mxF ) ),	*( (ui64*) cube_ )	)		}	
		//						^this shouldn't be necessary as long as we clear Hx between rackings
			}else{		mc1xZ = post1_xc| ( dis_c<< 3 );													*( (ui64*) cube_+1 )	= *( (ui64*) cube +1 );	/* set Epsilon of upper fragment	(there is a displacement, so Epsilon of pre-op cube is conserved)	*/
				switch(	mc1xZ ){	SwCASE_LPXOVER_10Y(	*( (ui64*)( cube+dis1_i ) ),  	*( (ui64*)( Hx +mxF ) ),	*( (ui64*) cube_ )  )  }
		//						^crossover wye			^tail src					^body src			^head src / wye output
				}

/*			LOWER FRAGMENT [0]		*/
			*( (ui64*) _cube+1 )	=			E[ mxF -1	];	/*	set Epsilon of lower fragment,  only now that 
															we've had a chance to conserve the old value
															in the upper fragment					*/
		/*	crossover low part of modified cycla (from Hx ) with unaltered cycla in-situ						*/
						mc0xZ = mc0 |( post0_xc<< 3 );
			switch(		mc0xZ ){	SwCASE_LPXOVER_01T( 	*( (ui64*) Hx ),								*( (ui64*) _cube)  );  }
		//						^low-pass crossover tee		^tail src										^head src / output


/*######	UPPER FRAGMENT [1]:	SPLICE Q-DATA SECTION 	(RL-Split)			*/
		/*	re-encode modified cycla from op matrix[ mxF..mxE ] to upper fragment char * cube_[ 16.._O[ mxE ] ]	*/
			if( post1_q ){
				pq_  = cube_ +16;  m=mxF;
				//		printf("\r%c	re-cast q-data for keybyte[s] Hx[ %2d..%2d ]	to cube_[ 16..%d ] \n",
				//			251,								mxF, mxZ,		15+post1_q);
				do	{//	printf("\r%c	re-cast q-data for keybyte Hx[ %2d ]( 0x%02X )	to cube_[ %d..%d ]\n",
					//		251,								m,	Hx[ m ],		pq_-cube_, pq_ +_Q[m] -cube_ -1);
					switch( Hx[ m ] ){  hiCASTt0inc(	A[m], B[m], pq_  )	}
					} while( ++m< mxE );
				}

		/*	bulk move (dis1_q) bytes of trailing / displaced unaltered q-data to upper fragment					*/
			if( dis1_q ){		/*	dest: 					cube_[	16 +post1_q	..	CS_	-1 ] =		*/
							/*	src:						_cube[	O[ mxE ]		..	CS	-1 ];			*/
		//		printf("\rmv	bulk move ( %d ) bytes of trailing data:\n	cube_[%d..%d] = cube[%d..%d]\n",	dis1_q,
		//														16 +post1_q,		CS_	-1,
		//														O[ mxE ],		CS	-1	); 		sign= post1_q? 243: 240;
				pq_= cube_ +16 +post1_q;
				pqx= cube +O[ mxE ];
				while( dis1_q >7 ){	*( (ui64*) pq_ ) = *( (ui64*) pqx );		pq_ +=8;	pqx+=8;	dis1_q-=8;	}
				while( dis1_q >3 ){	*( (ui32*) pq_ ) = *( (ui32*) pqx );		pq_ +=4;	pqx+=4;	dis1_q-=4;	}
				while( dis1_q >1 ){	*( (ui16*) pq_ ) = *( (ui16*) pqx );		pq_ +=2;	pqx+=2;	dis1_q-=2;	}
				while( dis1_q >0 ){	*( (ui08*) pq_ ) = *( (ui08*) pqx );	++	pq_;	++	pqx;	--	dis1_q;		}
				}

/*			LOWER FRAGMENT [0]: Resize					(RL-Split)								*/
		/*	re-size frag 0 now to make sure it has space for new cycla									*/
			if(		CS !=	_CS	){//	printf("\r	resize char * _cube from (%d) byte[s] to (%d) byte[s]\n", CS, _CS );
				if(	CS <	_CS )	_cube =	SvGROW(	_sv,	_CS +1 );
				_cube[		_CS ] = 0;			SvCUR_set(	_sv,	_CS	);		if( _CS<16){ printf("\n_rack( %d ): _CS( %lld ) <16	catch #0\n", caller, _CS );	exit(0);	}
				}

		/*	re-encode modified cycla from op matrix[ mx0..mxF-1 ] to lower fragment char * _cube			*/
			if( post0_q ){
				_pq  = _cube +O[ mx0 ];	 m=mx0;
					//	printf("\r%c	re-cast q-data for keybyte[s] Hx[ %2d..%2d ]	to _cube[ %d..%d ] \n",
					//		251,								mx0, mxF-1,		O[ mx0 ], _O[ mxF ]-1 );
				do	{//	printf("\r%c	re-cast q-data for keybyte Hx[ %2d ]( 0x%02X )	to _cube[ %d..%d]\n",
					//		251,								m,	Hx[ m ],		_pq-_cube, _pq +_Q[m] -_cube -1);
					switch( Hx[ m ] ){  hiCASTt0inc(	A[m], B[m], _pq  )	}
					} while( ++m< mxF );
		}	}	}
	else					{	/* Cycla count exceeds the capacity of cube iC, creating an array of new cubes.	[NOT IMPLEMENTED]*/	printf("\r	Cycla count exceeds the capacity of cube iC, creating an array of new cubes.	[not implemented]\n\t");

		bal_c	= ec +rel_c;
		bal_C	= (bal_c >>3)	+1;
		if(	bal_C >1 ){
			bal_c	= bal_c /	bal_C;
			rem_c	= bal_c %	bal_C;
			}
		}

//	_print_mx( caller );
_end__rack:
	O[mxZ]=_O[mxZ];
	O[mxE]=_O[mxZ] +( Q[mxZ] = _Q[mxZ] );
	mx0=0xFF;
	*( (ui64*) Hx )=0;
//	printf("\n	</RACK>\n");
	}
void _resplice( ui08 caller ){		//	"resplice"	is the post-operational process of rendering changes to the avICE array itself.
	printf("\n_resplice( caller==%d ):	eji=%lld	_eji=%lld	alt=%lld\n", caller, eji, _eji, alt );
	if( zC!= AvFILLp( avICE ) ){	printf( lightning );
							printf("\n!	zC( %llu ) != AvFILLp( avICE )( %llu )\n", zC, AvFILLp( avICE ) );
							zC = AvFILLp( avICE );
							}
	
	/* rel. AvFILLp:	*/				rel_iC += respliceIns[ eji ] - respliceCut[ eji ];
	/* new AvFILLp:	*/	post_zC =zC +	rel_iC;								if(	post_zC< 0 ){ AvFILLp( avICE ) =-1;	return ;	}
	if(					post_zC >=AvMAX(	avICE ) ){			av_extend( avICE,		post_zC );	printf("\n	avICE extended to (%d)\n", post_zC );	}

/*	"Re-splice" streamlines any number of deferred array splice operations into one, using a bistable loop with 2nd order dynamics.
	Inputs are the (5) global arrays:
		> respliceSrc	—the absolute index number of the operand element in the pre-operational array.
		> respliceDst	—the absolute index number of the operand element in the post-operational array.
		> respliceIns	—the number of elements to be inserted at destination index.
		> respliceCut	—the number of elements to be removed at source index.
		> respliceAlt	—not a part of the main vector.  Uses a separate iterator, "alt".  Governs ascending / descending alternation.

	The first (4) arrays share a common iterator"eji", and they align as one matrix, such that "eji" represents a vector, crossing the (4).
	The fifth array is the main array of the outer loop below.  It subdivides the step matrix into ascending / descending ranges,
	directing sequential numbers of iterations for the two nested inner loops as they swap over to each other within the main loop.

	Prior to getting here, the population of the resplice matrix is event-based; the only two events are "insert" and "cut".
	Events which occur at the same index increment the counter of a single "eji" step, and are thus aggregated; additionally,
	"cut" events which occur on consecutive elements are also aggregated in a single "eji" step, since "cut" implies "next".
	
	The loop starts by determining which end to start on / direction to iterate in depending on whether the new length is greater.
	The direction of iteration reverses each time the relative difference between source and destination index crosses zero.
	When swapping to "ascending" mode, the total ascending span is incremented all at once initially, decrementing step-by-step;
	upon returning to the alternation index (minus one), it jumps forward by that length again, proceeding in the initial direcion.

	Whether in ascending or descending mode, the order of array operations per step is "cut; jump; insert; continue".
	inserts and cuts are self-explanatory, while the dynamics of jumps are determined by direction and non-zero relative pre-post offset.
	Basically, a jump initializes cut & insert positions, shifting intermediate elements peristaltically for non-zero relative pre-post offset.
	For all but the highest-index step, these jump intervals are already stored in the (int) respliceDst[] array before we get here.
	Obviously the final event is not followed by another one, so the very first thing we do is compute "dst" for the highest-index step.
	*/

#define	__ReSPLICE_DESC(		$isrc, $idst, $cut, $ins )							printf("\n	<__ReSPLICE_DESC	eji=%lld>\n", eji );	\
				jmp =	dst -svC0 -$idst;									\
	src = svC0 + $isrc +jmp;	\
	if( $cut )	{									psv = svC0 +$isrc;			\
			dst-=$cut;	do	{	SvREFCNT_dec(  *	--psv);					\
											*	psv = &PL_sv_undef;		printf("\r		x%d  	avICE[ %-2d ]    		= &PL_sv_undef;			cut: %d\n",	eji, psv-svC0,			$cut );	\
							} while( -- $cut );								\
			}															\
	if(	$isrc == $idst ){			src-=jmp;		dst-=jmp;						\
	}else	if( jmp >0 )	do	{											printf("\r		%c%d  	avICE[ %-2d]    		= avICE[ %-2d];			jmp: %d\n",	\
																					175, eji,	dst -svC0,			src -svC0,  				jmp );		\
							*dst-- = *src--;								\
							} while( -- jmp );								\
	if( $ins )	{								psv = svR0 +r;  r -= $ins;			\
						do	{											printf("\r		*%d  	avICE[ %-2d ]    		= avRack[ %d ];			ins: %d\n",	\
																					eji,		dst-svC0,			psv-svR0,				$ins  );		\
							*dst-- = *psv;	   *	psv-- = &PL_sv_undef;			\
							} while( -- $ins );								\
			}\
																		printf("\n\t	</__ReSPLICE_DESC>\n");	\



#define	__ReSPLICE_ASC(	$isrc, $idst, $cut, $ins  )								\
			dst	=	svC0 +$idst;											\
			src	=	svC0 +$isrc;	jmp	= ( 1-respliceCut[ eji+1] ) +respliceDst[ eji+1 ]	- $idst;			\
																		printf("\n	<__ReSPLICE_ASC	eji=%lld	jmp=%lld	rel=%lld >\n", eji, jmp, rel );	\
	if( $cut )	{									psv = src-1;				\
						do	{	SvREFCNT_dec(  *	psv);					\
											*	psv-- = &PL_sv_undef;		printf("\r		x%d  	avICE[ %-2d ]    		= &PL_sv_undef;			cut: %d\n",		eji, psv+1-svC0,			$cut );	\
							} while( -- $cut );								\
			}															\
	if( $ins )	{								psv = svR0 +r;  r -= $ins;			\
						do	{											printf("\r		*%d  	avICE[ %-2d ]    		= avRack[ %d ];			ins: %d\n",	\
																					eji,		dst-svC0,			psv-svR0,				$ins  );		\
							*dst-- = *psv;	   *	psv-- = &PL_sv_undef;			\
							} while( -- $ins );								\
			dst	=	svC0 +$idst;											\
			}															\
	if(	$isrc == $idst ){		src+=jmp;	dst+=jmp;						\
	}else	if( jmp >0 )	do	{											printf("\r		%c%d  	avICE[ %-2d]    		= avICE[ %-2d];			jmp: %d\n",	\
																					175, eji,	dst -svC0,			src -svC0,  				jmp );		\
							*dst++ = *src++;								\
							} while( -- jmp );								printf("\n\t	</__ReSPLICE_ASC>\n");




#define	__ReSPLICE_ASC_(	$isrc, $idst, $cut, $ins  )								\
		dst	=	svC0 +$idst;												\
		src	=	svC0 +$isrc;		jmp	= ( 1-respliceCut[ eji+1] ) +respliceDst[ eji+1 ]	- $idst;			\
																		printf("\n	<__ReSPLICE_ASC	eji=%lld	jmp=%lld	rel=%lld >\n", eji, jmp, rel );	\
	if( $cut )	{									psv = src-1;				\
						do	{	SvREFCNT_dec(  *	psv);					\
											*	psv-- = &PL_sv_undef;		printf("\r		x%d  	avICE[ %-2d ]    		= &PL_sv_undef;			cut: %d\n",		eji, psv+1-svC0,			$cut );	\
							} while( -- $cut );								\
			}															\
	if(	$isrc == $idst ){		src+=jmp;	dst+=jmp;						\
	}else	if( jmp >0 )	do	{											printf("\r		%c%d  	avICE[ %-2d]    		= avICE[ %-2d];			jmp: %d\n",	\
																					175, eji,	dst -svC0,			src -svC0,  				jmp );		\
							*dst++ = *src++;								\
							} while( -- jmp );								\
	if( $ins )	{								psv = svR0 +r;  r -= $ins;			\
						do	{											printf("\r		*%d  	avICE[ %-2d ]    		= avRack[ %d ];			ins: %d\n",	\
																					eji,		dst-svC0,			psv-svR0,				$ins  );		\
							*dst-- = *psv;	   *	psv-- = &PL_sv_undef;			\
							} while( -- $ins );								\
			}															printf("\n\t	</__ReSPLICE_ASC>\n");


	printf("\n before finalizing respliceAlt, rel_iC=%lld	cmpZ==%d	alt=%d\n\n", rel_iC, cmpZ, alt );

	if(		rel_iC< 0 ){	if(	cmpZ >0 ){ 	respliceAlt[ alt++	] = eji -_eji;	respliceAlt[ alt ]=1; 	}
						else{			respliceAlt[ alt		] = eji -_eji;					}	cmpZ =-1;
	}else if(	rel_iC >0 ){	if( 	cmpZ< 0 ){ 	respliceAlt[ alt++	] = eji -_eji;	respliceAlt[ alt ]=1; 	}
						else{			respliceAlt[ alt		] = eji -_eji;					}	cmpZ = 1;
	}else{								respliceAlt[ alt		] = eji -_eji;					}


	printf("\n	finalizing step %d:	respliceAlt[ alt( %d ) ] = eji( %d ) - _eji( %d ); %lld\n\n", alt, eji, _eji );
	/* finalize last resplice step		*/
	respliceSrc[	eji ]	=	rack_iC;
	respliceDst[	eji ]	=	rack_iC 	+ 	rel_iC;
//	if(		cmpZ==1 ){		if(		rel_iC< 0	){	cmpZ=0;				respliceAlt[	alt++	] = eji -_eji;  _eji = eji;  }
//	}else if(	cmpZ==0		&&		rel_iC >0	){	cmpZ=1;				respliceAlt[	alt++	] = eji -_eji;  _eji = eji;  }

//	if( rack_iC!=zC){
		respliceSrc[	eji +1	] =	zC;
		respliceDst[	eji +1	] =	post_zC;
//		}

	int	z, rel, dis, jmp, si, di, r	= AvFILLp(	avRack	);
	SV **			svR0	= AvARRAY(	avRack	);
					svC0	= AvARRAY(	avICE	);
	printf("\r<ReSPLICE>\n	zC:		%lld\n	post_zC:	%lld\n", zC, post_zC );

	printf("\n	racking schedule (pre process):\n	#		");
							for( z=0; z<=7; ++z ){ printf("#%-7d", 			z );	}
	printf("\n	respliceAlt\t"	);	for( z=0; z<=7; ++z ){ printf(" %-7d",	respliceAlt[	z ] );	}
	printf("\n	respliceCut:\t"	);	for( z=0; z<=7; ++z ){ printf(" %-7d",	respliceCut[	z ] );	}
	printf("\n	respliceIns:\t"	);	for( z=0; z<=7; ++z ){ printf(" %-7d",	respliceIns[ 	z ] );	}
	printf("\n	respliceSrc:\t"	);	for( z=0; z<=7; ++z ){ printf(" %-7d",	respliceSrc[	z ] );	}
	printf("\n	respliceDst:\t"	);	for( z=0; z<=7; ++z ){ printf(" %-7d",	respliceDst[	z ] );	}
	printf("\n\n");


	if( cmpZ< 0 ){
		_eji = ( eji -=		respliceAlt[	alt ]-1 ) -1;
		goto asc;
		}

	src	= svC0 +zC;
	dst	= svC0 +post_zC;
	do	{
	dsc:	printf("\r	resplice entering descending mode at index #%d.\n", eji );
		do		{	printf("\n	dsc:	%lld	< %lld	respliceAlt[ alt( %d ) ]: %lld\n",	respliceSrc[ eji	],	respliceDst[ eji	],	alt,	respliceAlt[	alt ] ); if(	respliceSrc[ eji ] > respliceDst[ eji ]) printf("\n!	wrong direction ( %lld > %lld)\n", respliceSrc[eji], respliceDst[ eji ] );
											__ReSPLICE_DESC(				respliceSrc[ eji	],	respliceDst[ eji	],		respliceCut[	eji ],		respliceIns[	eji ] );	
		--eji;		} while( --	respliceAlt[	alt ] >0 );	if( alt == 0 ) break;
		_eji = ( eji -=		respliceAlt[ --	alt ] ) -1;

	asc:	src	=	svC0 +respliceSrc[ eji  ];	/*	rel	=	respliceDst[ eji+1	] - respliceSrc[ eji+1	];
		dst	=	src +rel;						jmp	= 1+	respliceSrc[ eji+1	] - respliceSrc[ eji	];*/
		printf("\r	resplice entering ascending mode at index #%d.	returning to descending  mode at index #%d.\n", eji, _eji);

		do		{	printf("\n	asc:	%lld	> %lld	respliceAlt[ alt( %d ) ]: %lld\n",	respliceSrc[ eji	],	respliceDst[ eji	],	alt,	respliceAlt[	alt ] ); if(	respliceSrc[ eji ] < respliceDst[ eji ]) printf("\n!	wrong direction ( %lld < %lld)\n", respliceSrc[eji], respliceDst[ eji ] );
											__ReSPLICE_ASC(				respliceSrc[ eji	],	respliceDst[ eji	],		respliceCut[	eji ],		respliceIns[	eji ] );	
		++eji;	} while( --	respliceAlt[	alt ] >0 );

		eji =		_eji;
		} while( --	alt >=0 );
	printf("	loop end;	eji=%lld	_eji=%lld	alt=%lld\n\n", eji, _eji, alt);
	eji=_eji=alt=0;


	if( AvFILLp( avICE ) != post_zC ){	AvFILLp(	avICE ) = post_zC;	printf("\r	AvFILLp( avICE ) = %lld;\n", post_zC );	}
				
	printf("\n	racking schedule (post process):\n	#		");
							for( z=0; z<=7; ++z ){ printf("#%-7d", 			z );	}
	printf("\n	respliceAlt\t"	);	for( z=0; z<=7; ++z ){ printf(" %-7d",	respliceAlt[	z ] );	respliceAlt[ z ]=0; }
	printf("\n	respliceCut:\t"	);	for( z=0; z<=7; ++z ){ printf(" %-7d",	respliceCut[	z ] );	respliceCut[	z ]=0; }
	printf("\n	respliceIns:\t"	);	for( z=0; z<=7; ++z ){ printf(" %-7d",	respliceIns[ 	z ] );	respliceIns[ 	z ]=0; }
	printf("\n	respliceSrc:\t"	);	for( z=0; z<=7; ++z ){ printf(" %-7d",	respliceSrc[	z ] );	respliceSrc[	z ]=0; }
	printf("\n	respliceDst:\t"	);	for( z=0; z<=7; ++z ){ printf(" %-7d",	respliceDst[	z ] );	respliceDst[	z ]=0; }

	printf("\n	</ReSPLICE>\n\n\n\n\n");
	}

bool	_set(){
#define uOK   	F[ u ] = ok
#define uMOD	F[ u ] = mod
#define vMOD	F[ v ] = mod
#define vNUL		F[ v ] = null;
#define uNEW 	F[ u ] = new
#define vNEW 	F[ v ] = new
#define uNUL 	F[ u ] = null;
	skip=a=0;					za = AvFILLp(	avArg);	if( za ==-1)			/*	no args */				return 0;
	x=ARG0;		post_zC=		zC = AvFILLp(	avICE);	if( zC ==-1){				ENDOcp(	0 );				return 0; }
	mx0=0xFF;						/*<— how we know there's nothing to rack	*/
	rel_iC = rack_iC = alt =	eji =0;		/*<— how we know there's nothing to resplice	*/
						_eji=-1;
	av_clear( avRack ); cmpZ=0;
	t_xv	= SvTYPE( 	avICE	);		if( t_xv!=SVt_PVAV 		){ printf("\r!_set():	(AV*) avICE is not a valid perl array\n\t"	);	return 0; }
	svC0 = AvARRAY(	avICE );			if( *svC0==&PL_sv_undef	){ printf("\r!_set():	*AvARRAY( avICE) is undef\n\t"			);	return 0; }
									if( *svC0==&PL_sv_no		){ printf("\r!_set():	*AvARRAY( avICE) is false\n\t"			);	return 0; }
									if( *svC0==NULL			){ printf("\r!_set():	*AvARRAY( avICE) is NULL\n\t"			);	return 0; }

/* search for iC of x			*/						lb = 0;			/* search window of first search starts at cube 0 */																				//_print_mx(1);
												iC= ( ub	= zC +1	)>>1;
do{										cube = SvPVbyte(		sv =*(svC0+iC ),	CS );
	if(						x == *( (ui64*)	cube +1) ){ cube_=cube;	sv_=sv;	CS_	=	CS;							_endoloc:
																				ENDOLOC;																									//_print_mx(10);
		if( iC< zC ){ 						cube = SvPVbyte(		sv =*(svC0+ ++iC),	CS);	INTERLOC;																									//_print_mx(20);
/*	=+|_	*/	do{	if(		A[ 0 ] >1 ){	/* =+|_	*/ --	A[ 0 ];	   ++	B[ 255 ];		++	*( (ui64*) cube_ +1);							printf("\r=+|_\t\t\t\t\t\tx( %5llu )	=+|_ 	iC( %5llu )	*((ui64*)cube_+1) == %llu \n\t", x, iC, *((ui64*)cube_+1) );		//_print_mx(21);
						if(	za == a++ ){				ReICEzSV_( 255,3 );							goto	_exit;		}
					}else if(	A[ 0 ]==1 ){				A[ 0 ]=A[255];	B[ 0 ]+=B[255]+1;																												//_print_mx(22);
/*	!|+=		*/			if(	zc_ == 0 ){ 	/* !|+=	*/ 	RACK_SvReCUT( iC );														printf("\r!|+=\t\t\t\t\t\tx( %5llu )	!|+= 	iC( %5llu )	*((ui64*)cube_+1) == %llu \n\t", x, iC, *((ui64*)cube_+1) );		//_print_mx(23);
/*	=|+=	*/			}else{			/* =|+=	*/	d=A[255]+B[255];				*( (ui64*) cube_+1) -=(  A[255] +B[255] );
																														
							cube_[zc_--]=0;			SvCUR_set( sv_, O[ 255 ] );													printf("\r=|+=\t\t\t\t\t\tx( %5llu )	=|+= 	iC( %5llu )	*((ui64*)cube_+1) == %llu \n\t", x, iC, *((ui64*)cube_+1) );		//_print_mx(24);
						}if(	za == a++ ){															goto	_exit;		}
	x=ARG(a);																					goto	_next_x;
/*	==|=	*/		}else{		printf( lightning ); printf("\n	INTERLOC: null gap	(==|=) \n");				goto	_next_x;
						}
	x=ARG(a);		} while(	x == *((ui64*)	cube_+1) );	ReICEzSV_( 255,4 );							goto	_next_x;
		}else{	do	{					/*	=+|$  */			  ++	B[ 255 ];		++	*((ui64*)cube_+1);								printf("\r=+|$\t\t\t\t\t\tx( %5llu )	=+|$ 	iC( %5llu )	*((ui64*)cube_+1) == %llu \n\t", x, iC, *((ui64*)cube_+1) );		//_print_mx(11);
/*	=+|$	*/			if(	za == a++ ){				ReICEzSV_( 255,1 );							goto	_resplice; 	}
	x=ARG(a);		} while(	x == *((ui64*)	cube_+1) );	ReICEzSV_( 255,2 ); 	ENDOcp(	*((ui64*)cube_+1));	return 0;
			}

	}else if(					x <	*( (ui64*)	cube +1) ){ iC=(( ub	= iC )+lb	)>>1;  if( iC==ub ){	INTRALOC;		goto	_intra_op; 	}
	}else{				/*	x >	*( (ui64*)	cube +1)*/ iC=(( lb	= iC )+ub	)>>1;  if( iC==lb  ){	INTRALOC1Up;			_intra_op:
		do{	//	if( a>1) _print_mx(100);
			if(				x==E[u]){	uMOD;
				if(		F[ v ]== null ){	DeICEv_KEI( u, v );  }																																		//_print_mx(310);	
/*	=+_		*/	if(		A[ v ] >1 ){	vMOD;		    --	A[ v ];	   ++	B[ u ];		   ++	E[ u ];									//	printf("\r=+_ \t\t\t\t\t\tx( %5llu )	=+_  	E[%d]( %llu )\n\t", x, u, E[u] );		//_print_mx(311);	
/*	=+=		*/	}else{//_print_mx(10101);
						--post_zc;	vNUL;	Q[u]+=Q[v];			B[ u ]+= A[v]+B[v];	E[ u ] =E[ v ];	O[v]+=Q[v];					//	printf("\r\t\t\t\t\t\t\t\t\t\tx( %llu )	=+=  	E[%d]( %llu )\n\t", x, u, E[u] );		//_print_mx(312);	
					//_print_mx(20202);	//		^ try it a bunch before you  f with it again
					}
			}else{			d = E[u] -x -B[u];																																					//_print_mx(300);
/*	_+_		*/	if(			d >1	){	vNEW;	Q[v]=0;	A[ v ] = d -1;	B[ v ]  = B[ u ];		E[ v ] =E[ u ];	O[v]=O[u]+Q[u];	O[v+1]=O[v];	//	printf("\r_+_ \t\t\t\t\t\tx( %5llu )	_+_  	E[%d]( %llu )\n\t", x, u, E[u] );
						++post_zc;	uMOD;			A[ u ] -= d;	B[ u ] = 1;		E[ u ] =x +1;	I[ v ] = I[ u ];																						//_print_mx(301);	
/*	_+=		*/	}else if(		d==1 ){	uMOD;		    --	A[ u ];	   ++	B[ u ];													//	printf("\r_+= \t\t\t\t\t\tx( %5llu )	_+=  	E[%d]( %llu )\n\t", x, u, E[u] );		//_print_mx(302);	
/*	===		*/	}else{		++skip;																						//	printf("\r=== \t\t\t\t\t\tx( %5llu )	===  	E[%d]( %llu )\n\t", x, u, E[u] );		//_print_mx(303);	
				}	}	/*			F []		Q []		A []			B []				E []					*/
			if(				za ==	a++ ){														goto	_exit; 		}
	x=ARG(a);																							_next_x:
			if(				x<	*( (ui64*)	cube +1) ){    								CoINTRALOC;
			}else{					/*	cube_= cube;	(EXTRICATE effects this		) */	EXTRICATE;	
				if(			x == *( (ui64*)	cube_ +1) ){/*	(keep sv_, CS_ values too	) */					goto	_endoloc;
				}else if(		iC == zC	){									ENDOcp(	*((ui64*) cube_+1));	return 0;
				}else{								cube = SvPVbyte(	sv = *( svC0 + ++iC),	CS );
					if(		x<	*( (ui64*)	cube +1) ){   								ReINTRALOC;		goto	_intra_op;
					}else if(	x == *( (ui64*)	cube +1) ){	cube_=cube;		sv_=sv;		CS_	=	CS;		goto	_endoloc;
					}else if(	iC == zC	){									ENDOcp(	*( (ui64*) cube+1));	return 0;
					}else{	break;
			}	}	}	}	while(1);	/* dwell on iC	*/
							lb =iC+1;	ub=zC +1;	iC= ( lb+ub )>>1;					printf("\r........SEARCH %d < %d < %d\n", lb, iC, ub );
	}	}	} while( 1 );	/* search	*/
	_exit:																		EXTRICATE;	
	_resplice:		if( eji || respliceIns[0] || respliceCut[0] )	_resplice(1);	
	return 0;
	}






