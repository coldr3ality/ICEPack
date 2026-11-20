/*	Copyright 2026 Peter Arlen Schmidt
g
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
#include	"access.h"	
int	à=10,	ª=9;
int	ß=7;
int	ê=0, È=1, Ê=2;
int	Ì=8;
int 	Ú=3, Ü=4,	º=5,	µ=6,	Þ=0xDEC27;

bool trace=0;
extern	void	_av_commit(),
			_sv_commit_1x(),
			_sv_commit_nx(),
			printAvDBUG(),
			_print_mx( unsigned char mx_max, short ix¹, short izΩ );


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

/*	OBJECTIVE
	To implement a session ID generator that is non-deterministic, non-repeating, and operates ad-hoc
	on all edge devices while maintaining one coherent mapping without a specialized core network.
	There are entropy sources as usual, but instead of piping this directly into a Session ID generator,
	use it to select the "nth" free ID in an ICEPack instance, conserving namespace locally; then,
	implement periodic redistribution of available namespace service-wide, without degrading entropy,
	randomly drawing large sets of nth IDs for each edge server and periodically throwing them back 
	into the pool and drawing a new set.
	In this way, edge servers can unilaterally assign system-wide Session IDs on an event-driven basis,
	with no core negotiation needed, with guaranteed ID collission protection.  Not only does this free us
	to rate the appropriate namespace depth precisely, it also frees us to implement Forward Secrecy—
	i.e., perpetual renewal of active Session-IDs. 

	OBJECT CLASS
	ICEPack manipulates QWORD-sized truth vectors designed to be used as inside-out UUID tables.
	These truth vectors provide a hash-like interface to a 64-bit namespace, 18 quintillion flag bits,
	though the absolute minimum compression ratio of 3:1 is to be expected for highly entropic data.
	This space is fragmented as a searchable array and compressed using a sort of run length encoding—
	Inversion Cycle RLE, or just Inversion Cycle Encoding (ICE).

	ENCODING
	ICE encoding is a compressed bitvector format, where access to nearest adjacent set/unset bit
	scales in constant O(1) time, ideal for allocation within highly entropic inside-out UUID tables.
	Like RLE, ICE compresses repeating values as run lengths, but it stores no values explicitly—
	alternating true-false run lengths implicitly store value as evenness/oddness, or "half-cycle phase".
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
	Any sparse array compression technique which omits nulls makes the obvious unfortunate tradeoff
	of recovering space while sacrificing the implicit identity of the element index— 
	the most characteristic property of arrays.

	The solution applied here is to regressively quantize the truth vector as a modulus gradient,
	storing summative modulus values in the freed up allocation space for each quantized unit key, 
	which are atomically updated by setters during mutation, and efficiently summed by getters 
	to compute the sort order of sparse keys on demand.

	So, to reiterate:
		> Trivial access to lowest / highest / nearest sparse index in O(1) time
		> Hash-like sparsity with array-like sorting effectively works like a range operator for keys
		> Basically redefines the Perl idiom "Everything Is A Number"

	*/

/*	ARCHITECTURE

	ICE encodes a pair of unsigned quads in a variable width format that occupies from 1 to 17 bytes in length (q).

	When there is ample free space following the target field, we can write these values using simplex assignments,
	but when we get within (3) bytes of the field boundary, there is a risk of accidentally clobbering several bytes past the end in this way.
	Depending on q, we may have to break the operation up into (2) or (3) assignments, using right-bitshift and casts.

	The dichotomy of a RELiC object is a 2D AV* array of SV* "cubes", where:

	>	Each SV* "cube" is labeled by an "Edge" value which represents the upper limit for the range of sorted keys contained within.
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
	We have a library of switch statements to cast exact byte lengths of data into confined spaces.
	It is not always necessary to use such precision— most of the time, there is ample space ahead, but in order to prevent overrun,
	casting must be handled intelligently in certain cases (particulary for variable-field-length: 5, within (3) bytes of the high boundary).
	These switches write to variable-length fields in the fewest statements possible given the allowable tolerance / boundary clearance.
	They are generated by the perl scripts in the "srcgen" directory, namely:

		> gen_c_for__lluiCASTa.pl
		> gen_c_for__lluiCASTab.pl
		> gen_c_for__lluiCASTabc.pl		*unused
		> gen_c_for__lluiCASTabcd.pl		*unused
		> gen_c_for__lluiCASThab.pl
		> gen_c_for__SwCASE_AB2IC_t[0123].h.pl	*the numbers 0, 1, 2, and 3 are tolerance ratings for allowable bytes of overrun.
		> gen_c_for__SwCASE_IC2AB.h.pl
		> gen_c_for__SwCASE_IC2ABQ_R2L.h.pl

	E.g.:
	In order to copy an unsigned LLU into a field fit for the significant bytes only, it will require one of the following combinations of casts:
	
		> a single assignment cast as a char, short, long, or long long			(1, 2, 4, or 8 bytes)
		> two assignments cast as:	(short) x;	(char) x>>16;				(3 bytes)
								(long) x;	(char) x>>32;				(5 bytes)
								(long) x;	(short) x>>32;				(6 bytes)
		> three assignments cast as:	(long) x;	(short) x>>32;	(char) x>>48;	(7 bytes)


	THREE PHASES OF NAMESPACE DEPLETION
	Expansion:	while the namespace is mostly free,	entropic inclusions tend to fragment cycla,	complexifying the graph.
	Saturation: 	while the namespace is about 60/40,	entropic inclusions hold static pressure;		complexity plateaus.
	Compaction: 	while the namespace is mostly used,	entropic inclusions tend to consolidate cycla,	simplifying the graph.

	*/


		HV	*	hvICE,
			*	hvArg,
			*	hvOut;
		AV	*	avOut,
			*	avDBUG;	long long int	zd;
		AV	*	avRdx;		bool			bal_iC;
		AV	*	avICE;		long long int	iC, iCI, iCO, iCx, post_C, zC, zzC, nC, rel_iC, less_iC;  	//	iC is the index of the current cube.  zC is the array index of the ending cube.
		AV	*	avICE_;		long long int	zCs=-1;
		AV	*	avArg;		long long int	a, za; 					//	a list of integer value[s] to operate on.
		SV	*	rvOut,				/*	arrayref to AV* avOut									*/
			*	rvArg,				/*	arrayref to AV* avArg									*/
			*	rvICE,				/*	arrayref to AV* avICE									*/
			*	rvICE_;				/*	arrayref to AV* avICE_									*/

SV			**	src,
			**	dst,
			**	Aº,
			
			*	svA,					/*	general purpose scratch SV								*/
			*	svLbf,				/*	lower cube fragment									*/
			*	svΩ,	 				/*	SV containing right-hand cube data	(upper fragment)		*/
			*	sv,					/*	SV containing pre-commit cube data	(original pre-op cube)	*/
			*	sv0;					/*	SV containing left-hand cube data		(lower fragment)		*/
ui08			*	cube	=NULL,		/*	unsigned char * cube data (of index iC )					*/
			*	cubeΩ	=NULL,		/*	unsigned char * cube data (of index iC -1)					*/
			*	cube¹;
char			*	lightning = "\n!! !  !   !    !     !      !       !        !         !          !           !            !             !              !               !                !\n",
				aString[8448],
				exit_code=0,
			*	ps;

STRLEN			cS, CS, CSΩ, oCS;
char	iqZ;
ui08				*pk,			*pq,		*pΩ,
			/*	*pkz,		*pqz,	*/
			/*	*pk_,	*/	*p_,	
			/*	*pkx,		*pqx,	*/
				buf[	8 	+8	+8*16	+1	+15 ];	/*	buffers the output of ICE() and its variants
/*	CUBE STRUCT:	^	^	^		^	^ overflow padding (to survive an overshot "long long" cast)
					|	|	|		NULL byte
					|	|	up to 128 bytes of variable "q-data"
					|	"Edge" is the cube's search key.  It signifies the upper boundary of encoded keys within the cube.
					keybyte area stores up to (8) keybytes, which define variable "q-data" geometry for up to (8) inversion run cycla.
					*/

/*	standard global constant cube initialization templates 	*/
/*			"cube_i0" is used to initialize a cube which should start with element #0 set.						*/
ui08 const	cube_i0[	16]={	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x08,		/* cyclum #0:	x==0			*/
							0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	1		};	/* Edge:		1				*/

/*			"nube" is used to initialize an empty cube, or as a global null value to set pointers to directly.			*/
ui08			nube[	16]={	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,		/* no content					*/
							0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00	};	/* Edge:		0				*/

ui08			zube[	16]={	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,		/* no content					*/
							0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00	};	/* Edge:		0				*/
SV			_sv_;

/*			"cubE" is a global constant object used to failsafe RELiC accessors against potential overrun by iCE() and its variants.
			It contains a single null point at the max int, bounding the 64-bit namespace.					*/
ui08 const	cubE[	24]={	0xB8,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,		/* cyclum #7:	x==null			*/
							0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,		/* Edge:		2^64-1 (max uint)	*/
							0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF	};	/* A: 		2^64-1 (max uint)	*/


ui64			i, hi, lo, n, N, o, s;		/*	global scratch variables used in private contexts									*/
ui64			x, y, z,				/*	common arguments														*/
			skip, hit, miss, max,	/*	the number of misses or collissions counted as a method processes arguments  		*/
			hu, bu, hm, lm; 	 	/*	high-unit, base-unit, high-mask, low-mask:
									used to quantize keys for each unitary digit of numeric base (BASEBITS).		 		*/

//in general, a variable preceded by an underscore is vigilantly kept up-to-date, so to represent a value in a post-op state.
//matrix indeces will not be negative
/*						____	object______________________	verb_________	subject_____________________	preposition______________________	*/
short		oc,	xc,
			ocª,	xcª;			/*		mark		the [active: ª] indeces		of	char *	cube			*/
short 		 u, v, w,			/*	matrix indeces		iterate		the modification range		in	matrix { A[], B[], E[], L[] }	*/

	ixº,	/*	ix¹, ixⁿ, ix², */	ixΩ,		/*	matrix indeces		mark in		fragment boundaries		in	matrix { A[], B[], E[], L[] }	*/
	izº,	/*	iz¹, izⁿ, iz², */	izΩ,		/*	matrix indeces		mark out		fragment boundaries		in	matrix { A[], B[], E[], L[] }	*/
/*			^localized to:	(void) _sv_commit_1x()
						(void) _sv_commit_nx()	*/

	ixM, izM,		 			/*	matrix indeces		mark in/out	the Modification range		in	matrix { A[], B[], E[], L[] }	*/
	inM,	/*	izM+1		*/	/*	matrix index			high-bounds	the Modification range		in	matrix { A[], B[], E[], L[] }	*/
	ixH;	/*	inM+n_del	*/	/*	matrix index			marks in		the High-passthrough range	in	matrix { A[], B[], E[], L[] }	
								for inclusion-based methods, izM is always ixH -1.
								for exclusion-based methods, izM can be less than that, as cycla in-between are dropped.			*/

char unsigned	q,	q0,	q1;		/*	q-field lengths			total		the q-data length			of any given cyclum			*/
char			ic, 				/*	cyclum index			iterates		the read position			in	char *	cube			*/
		/*	icI, 	localized in _sv_commit_1x() and _sv_commit_nx()	*/
			icO,				/*	cycla index			marks out	the modification range		in	char *	cube			*/
			zc,	zcΩ, zcC;		/*	cycla indeces 			mark		the ending indeces			of	char *	cube / cubeΩ		*/

AV			*avOut;
SV			*svOp;
svtype		svt;
long long int	displacement, d, D;

char *	opStat[]=	{"null",	"del",	"ok",	"mod",	"new",	"epi"	};
enum	opStat	{null,	del,		ok,		mod,	new,	epi		}
/*		THE MATRIX				*/
		RW[	512 ];				/* read/write status enumerator			*/

ui64		A[	512 ],	Ac,			/* relative coord.s	which define	each negative cyclum phase	in	matrix { A[], B[], E[], L[] }	*/
		B[	512 ],	Bc,			/* relative coord.s	which define	each positive cyclum phase	in	matrix { A[], B[], E[], L[] }	*/
		E[	512 ],	Ec,	E_;		/* "Edge" values	which bound	the absolute coordinates	in	matrix { A[], B[], E[], L[] }	*/
//		Zc[	512 ];				/* cube lengths, pre-re-fragmentation  	*/
ui08 	I[	512 ],				/* cycla indeces	which align	pre/post op keybytes		in	char *	cube			*/
		K[	512 ],				/* header codes	which encode	variable q-data layout		in	char *	cube			*/
		L[	512 ], 	Lc;			/* q-data lengths	which define	each read increment		in	char *	cube			*/
ui16		O[	512 ],				/* q-data offsets	which mark	each read position			in	char *	cube			*/
		Oª[	512 ];				/* q-data offsets	which mark	each write position			in	char *	cube			*/

struct arg	{	char					stat;
				unsigned short		fwd_vc,	rev_vc,
									gt,		lt,		next;
				unsigned long long int	x;
			}	X[	0xFFFF ];				/* global arguments sorting buffer: 786,432 bytes	*/
int		Xmin = -1,
		Xmax = -1;

/*	Failed experiment: a linked-list based argument sorting construct (a linked list cannot be searched)
	[deleted 2026-11-19, see prior backups]	*/
	
/*	Shared context with AvPOST(...), AvCUT1B4(...) & AvCUT_B4(...) defined in AvSEQ.h,  and _av_commit() defined in _av_commit.c:	*/

	SV		*	rSeq_SV[	512 ]; 	//	temporary holding of SvPVbyte(...) char* "cubes" awaiting batch splice-insertion to AV* avICE
	long long int	rSeq_iR[	512	], iR,	//	source index of rSeq_SV 		after the destination index	(for each step [asc|dsc] )
				rSeqIns[	512	],	//	number of trailing SVs to insert	after the destination index	('')
				rSeqCut[	512	],	//	number of leading SVs to remove before the destination index	('')
				rSeqSrc[	512	],	//	source index						
				rSeqDst[	512	],	//	destination index				
						dsc,		//	step iterators, ascending/descending
				rel_iC,			/*	relative difference in active cube index since control index of current step was initialized
									—This is especially used by AvPOST(...); AvCUT1B4[2](...) to compute running dest. indeces.	*/
				cut_iC,
				step_iC =	0;		//	running destination index counter
				/*,	local to (void) _av_commit():
						asc,		//	step iterator, ascending
						zsc,		//	ending step
						juke,	//	step run length of reactive iteration reversal from descending to ascending order
						pmo	/*	[p]eristaltic [mo]ve run length (formerly jmp for "jump", which was an oversimplified )
									—"peristaltic move" refers to reflow / compaction or expansion of subsequent indeces.	*/

void __init_mx(){
	++xcª;
	}

void _init_mx(){		/*	totally zero-out buffer matrix to improve clarity of debug info	*/
	short	x=xcª;//	ixº=oc=ocª=0; xc= xcª=-1;
//	u= v= w= izM =0;	ixM=0xFF;
	do{	RW[x]=0;
		A[	x ]=	B[	x]=	E[x]=	0;
		K[	x ]=	L[	x]=	I[x]=		0;
		O[	x ]=	Oª[	x]=	0;
		} while( --x != -1 );
	}
void _icepack_init(){	/*	printf("—vUry cold\n\n");	*/
#if	defined( DEBUG )
	avDBUG=newAV();
	printf("\n	Debug options are set.  From perl, call \"getAvDBUG()\" or \"printAvDBUG()\" to access audit data.\n", __FILE__);
#endif
#if defined(DEBUG_SvCOMMIT_L1)
	printf("\r	DEBUG_SvCOMMIT_L1 is defined in %s:	auditing nominal activity within _sv_commit_1x and _sv_commit_nx()\n", __FILE__);
#endif
#if defined(DEBUG_SvCOMMIT_L2)
	printf("\r	DEBUG_SvCOMMIT_L2 is defined in %s:	auditing verbose activity within _sv_commit_1x and _sv_commit_nx()\n", __FILE__);
#endif
#if defined(DEBUG_SvCOMMIT_L3)
	printf("\r	DEBUG_SvCOMMIT_L3 is defined in %s:	checking integrity within _sv_commit_1x and _sv_commit_nx()\n", __FILE__);
#endif
#if defined(DEBUG_AvCOMMIT_L1)
	printf("\r	DEBUG_AvCOMMIT_L1 is defined in %s:	auditing nominal activity within _av_commit(), AvPOST and AvCUT1B4\n", __FILE__);
#endif
#if defined(DEBUG_AvCOMMIT_L2)
	printf("\r	DEBUG_AvCOMMIT_L2 is defined in %s:	auditing verbose activity within _av_commit() \n", __FILE__);
#endif
#if defined(DEBUG_AvCOMMIT_L3)
	printf("\r	DEBUG_AvCOMMIT_L3 is defined in %s:	checking integrity within _av_commit()\n", __FILE__);
#endif
#if defined(DEBUG_ACCESS_L1)
	printf("\r	DEBUG_ACCESS_L1 is defined in %s:	auditing nominal activity within accessor methods.\n", __FILE__);
#endif
#if defined(DEBUG_ACCESS_L2)
	printf("\r	DEBUG_ACCESS_L2 is defined in %s:	auditing verbose activity within accessor methods.\n", __FILE__);
#endif
#if defined(DEBUG_ACCESS_L3)
	printf("\r	DEBUG_ACCESS_L3 is defined in %s:	checking integrity within accessor methods.\n", __FILE__);
#endif
	hvICE		= gv_stashpv(	"ICEPack",			0);
	avOut		= get_av(		"ICEPack::avOut",		GV_ADD);
	A[	256 ]=255;
	B[	256 ]=255;
	O[	256 ]=16;
	Oª[	256 ]= 0;
	L[	256 ]= 0;

	u=v=w=255;
	int x;
	for( x=0; x<64; ++x){
		*( (ui64*) K		+x )= 0;
		*( (ui64*) RW		+x )=null;
		*( (ui64*) rSeq_iR	+x )=-1;
		*( (ui64*) rSeqIns	+x )=0;
		*( (ui64*) rSeqCut	+x )=0;
		*( (ui64*) rSeqSrc 	+x )=0;
		*( (ui64*) rSeqDst	+x )=0;
		}
	for( x=0; x<512; ++x){
		rSeq_SV[ x ]=NULL;
	}	}

void deIce_vEI(){	DeICE_vEI(	u, v );	}
void deIce_vKE(){	DeICE_vKE(	u, v );	}
//void deIce_vKI(){	DeICE_vKI(	u, v );	}
void deIce_vKEI(){	DeICE_vKEI(	u, v );	}
void reIce_uO(	ui16 u, ui16 v)	{	ReICEuO(	u, v );	}
void reIce_uOx(	ui16 u, ui16 v)	{	ReICEuOx(	u, v );	}


#ifdef EXPERIMENTAL_ENABLE
//	soundcloud.com/byproduct/asteroiddance_final
//	music.youtube.com/playlist?list=PLW-SI8dXPY9PCKS_Fr7yJ0bdak0S5RwOR

void	_toHash(){					hvOut = newHV();
	ui64			x, Ac, Bc, Ec=0,	i=0;
	char			ic, zc,
				key[ 8 ];
	ui08			Lc,	bs;
			*	cube,
			*	pq;
	SV		**	sviC0  =	AvARRAY(  	avICE ),
			**	src,
			*	sv;
	STRLEN		CS, s;

	long long int	iC, zC  =	AvFILLp(  	avICE );

	for(		iC=0; iC<= zC;  ++iC ){									sv = *( sviC0 +iC );
										cube = SvPVbyte(	sv,  CS );
		pq=								cube +16;
						zc = zcOf(		cube );
		for(	ic=0;  ic<=	zc; ++ic ){	 deICE(	cube[ ic ], Ac, Bc, Lc );
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
	ui08			Lc,
			*	cube,
			*	pq;
	SV		**	sviC0  =	AvARRAY(  	avICE ),
			*	sv;
	STRLEN		CS, s;

	long long int	iC, zC  =	AvFILLp(  	avICE );
	printf("\r_filterHV(): avICE has %d+1 element[s]\n	hvArg has (%d) key[s]\n\n", zC, N);

	for(		iC=0; iC<= zC;  ++iC ){								sv = *( sviC0 +iC );
										cube = SvPVbyte(	sv,  CS );
		pq=								cube +16;
						zc = zcOf(		cube );
		for(	ic=0;  ic<=	zc; ++ic ){	deICE(	cube[ ic ], Ac, Bc, Lc );
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


#endif

/*
I am writing a Perl/XS module in C called ICEPack.  I have a series of macros with a very carefully curated naming convention inspired by Latin, and occasionally I must come up with another thoughtful variant name for a specific edge case.  Currently, there are (10) of these macros, but before I name them and attempt to describe the nuances of what they each do differently, I must provide some context about the program architecture.

These macros are called within my methods as an abstraction of the underlying encoding/fragmentation/re-balancing layer.  Each of these macros is suffixed as "LOC" (for the latin root word LOCUS) as they each locate a given argument (value of x) and position the decode cursor within the relevant fragment (or "cube") relative to the previous argument in the arguments list (which has already been decoded, operated on, and buffered, pending re-encoding of the entire batch at once, after all arguments in any one cube run have been buffered).  These macros help make the methods' source code easier to read, as there is much to do with navigating the compressed data fragments which doesn't need to be reviewed there.  Not only does the "LOC" suffix characterize them as a related set of procedures, but the use of Latin distinguishes them strongly from any other set of macros.  I chose to use Latin because it allows me to describe combinations of unique spatial relationships both within the logical namespace of these data points and the allocation space of the fragments which contain them, concisely, as compound nouns.

To give you an idea of what these macros handle, each setter supports batch arguments, and in order to implement re-balancing of the structure, it is necessary to vector map the continuous run of decoded coordinates of any straight run of cubes (for any straight run of arguments spanning them) in order to re-distribute them optimally across a new run of cubes and re-encode them all at once.  As such, these macros also manage the mark-in and mark-out of continuous cube runs, for which there is a run-intializing as well as a run-continuing category.  To further differentiate them, each operation needs to modify two adjacent encode units at once (addressed as vectors [u, v] in the main buffer) which are usually both in the same cube, but are often bridging two adjacent cubes; as such, there is an intra-local as well as an inter-local category.  What's more, if the data points run past the end of the object, that's referred to as the epi-local context.

Here are their names, as well as brief descriptions of what they do:

ANTELOC and INTERLOC are the only two which handle vectors [u, v] separately.  They handle the "inter-local" context where vector u focuses on the last encode unit of the left- ("ante-") cube, and vector v focuses on the first encode unit of the right- ("dextra-") cube.  If, upon entering the ANTELOC context, we encounter the end of the object, we simply do not call INTERLOC, and instead proceed to EPILOC.

CoANTELOC and ReINTERLOC do the same thing, except in continuing a run instead of initializing one.

INTRALOC and CoINTRALOC initialize / continue a cube run in the intra-local context (both located within one cube).

INTRALOC1up is a minor variant of INTRALOC to handle the same locus, for when the search loop breaks one cube too low.

EPILOC and CoEPILOC initialize / continue buffering to the end of the last cube in the object, preparing to append remaining args.

The newest addition is PRIMOLOC, which is a special case for marking-in a cube run starting at the 0th cube.

*/	