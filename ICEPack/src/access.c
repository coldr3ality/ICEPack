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
#include	"access.h"
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
		> gen_c_for__SwCASE_IC2AB_R2L.h.pl

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
		AV	*	avICE;		long long int	iC, iCI, iCO, iCx, post_C, zC, zzC, post_zC, rel_iC, less_iC;  	//	iC is the index of the current cube.  zC is the array index of the ending cube.
		AV	*	avICE_;		long long int	zCs=-1;
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
			*	sv,					/*	SV containing pre-commit cube data	(original pre-op cube)	*/
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
ui08 const	cube_i0[	16]={	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x08,		/* cyclum #0:	x==0			*/
							0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	1		};	/* Epsilon:	1				*/

/*			"nube" is used to initialize an empty cube, or as a global null value to set pointers to directly.			*/
ui08			nube[	16]={	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,		/* no content					*/
							0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00	};	/* Epsilon:	0				*/

/*			"cubE" is a global constant object used to failsafe RELiC accessors against potential overrun by iCE() and its variants.
			It contains a single null point at the max int, bounding the 64-bit namespace.					*/
ui08 const	cubE[	24]={	0xB8,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,		/* cyclum #7:	x==null			*/
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
char unsigned u, v, w,			/*	matrix indeces		iterate		the modification range		in	matrix { A[], B[], E[], Q[] }	*/
/*	ix1,	ixX,	ixY,	*/	ixZ,		/*	matrix indeces		mark in		fragment boundaries		in	matrix { A[], B[], E[], Q[] }	*/
/*	iz1,	izX,	izY,	*/	izZ,		/*	matrix indeces		mark out		fragment boundaries		in	matrix { A[], B[], E[], Q[] }	*/
/*	^commented out because they do not need to be global.  Only the high fragment is ever seen outide of void _sv_commit().				*/

	ixM, izM,		 			/*	matrix indeces		mark in/out	the Modification range		in	matrix { A[], B[], E[], Q[] }	*/
	inM,	/*	izM+1		*/	/*	matrix index			high-bounds	the Modification range		in	matrix { A[], B[], E[], Q[] }	*/
	ixH;	/*	inM+n_del	*/	/*	matrix index			marks in		the High-passthrough range	in	matrix { A[], B[], E[], Q[] }	
								for inclusion-based methods, izM is always ixH -1.
								for exclusion-based methods, izM can be less than that, as cycla in-between are dropped.			*/

char unsigned	q,	q0,	q1;		/*	q-field lengths			total		the q-data length			of any given cyclum			*/
char			ic, 				/*	cyclum index			iterates		the read position			in	char *	cube			*/
			icI,	icO,			/*	cyclum indeces		mark in/out	the Modification range		in	char *	cube			*/
		
			zc,	zcZ,			/*	cyclum index 			identifies		the zeta cyclum			of	char *	cube / cubeZ		*/
			tena_zc,			/*	cyclum index			identifies		the tentative zeta cyclum	of	char *	cube			*/
			vc,	vc_;			/*	cyclum count			defines		vacant capacity available	in	char *	cube / cubeZ		*/
AV			*avOut;
SV			*svOp;
svtype		svt;
long long int	displacement, d, D;

char *	opStat[]={"null", "ok", "mod", "new", "del"};
enum	opStat{	null, ok, mod, new, del }
/*		THE MATRIX					*/
		RW[	256 ];					/* read/write status enumerator			*/

ui64		A[	256 ],	Au,	Av,	Ac,		/* relative coord.s	which define	each negative cyclum phase	in	matrix { A[], B[], E[], Q[] }	*/
		B[	256 ],	Bu,	Bv,	Bc,		/* relative coord.s	which define	each positive cyclum phase	in	matrix { A[], B[], E[], Q[] }	*/
		E[	256 ],	Eu,	Ev,	Ec,	E_,	/* "Epsilon" values	which bound	the absolute coordinates	in	matrix { A[], B[], E[], Q[] }	*/
		ZC[	256 ];					/* cube lengths, pre-re-fragmentation  	*/
ui08 	I[	256 ],					/* cycla indeces	which align	pre/post op keybytes		in	char *	cube			*/
		H[	256 ],					/* header codes	which ixZ.	q-data field space			in	char *	cube			*/
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
				rel_zC, 	dsc,  asc, zsc, juke, jmp,
				rack_iC	=0;		// running control point iterator
#define INIT_SvCOMMIT	ixM=0xFF;								/*<— how we know there's nothing to commit	*/
#define INIT_AvCOMMIT	rSeqCut[0]= rSeqIns[0]=	juke= rel_iC= rack_iC= 	dsc	= 0;	\
						rSeq_iR[0]= iR=							asc	= -1;

#define	ARG( $a )	SvIVX( svA=*(	AvARRAY(	avArg)+ $a	) )
#define	ARG0		SvIVX( svA=*	AvARRAY(	avArg)		)

#define	zOf( 	$a)		7-( 	__builtin_clzll(			 $a		) >>3)
#define	zcOf(	$cube)	7-( 	__builtin_clzll( *( (ui64*)	$cube)	) >>3)
#define	ncOf(	$cube)	8-( 	__builtin_clzll( *( (ui64*)	$cube)	) >>3)

#ifdef DEBUG
	void _init_mx(){		printf(lightning); printf("\n_init_mx();\n");			/*	totally zero-out buffer matrix to improve clarity of debug info	*/
		ui08	x=255;	tena_zc=-1;

		u= v= w= izM =0;	ixM=0xFF;
		do{	RW[x]=0;
			A[x]=	B[x]=	E[x]=	0;
			H[x]=	Q[x]=	Qx[x]=
			I[x]=		O[x]=	Ox[x]=	0;
			} while( ++x != 255 );
		Qx[255]=0;
		}
#else
	void _init_mx( ){	printf("!	_init_mx() called w/o debugging implemented by preprocessor\n");		}
#endif

void _icepack_init(){	printf("—vUry cold\n\n");
#if	defined( DEBUG )
	avDBUG=newAV();
	printf("\n	Debug options are set.  From perl, call \"getAvDBUG()\" or \"printAvDBUG()\" to access audit data.\n", __FILE__);
#endif
#if defined(DEBUG_SvCOMMIT_L1)
	printf("\r	DEBUG_SvCOMMIT_L1 is defined in %s:	auditing nominal activity within _sv_commit()\n", __FILE__);
#endif
#if defined(DEBUG_SvCOMMIT_L2)
	printf("\r	DEBUG_SvCOMMIT_L2 is defined in %s:	auditing verbose activity within _sv_commit()\n", __FILE__);
#endif
#if defined(DEBUG_SvCOMMIT_L3)
	printf("\r	DEBUG_SvCOMMIT_L3 is defined in %s:	checking integrity within _sv_commit()\n", __FILE__);
#endif
#if defined(DEBUG_AvCOMMIT_L1)
	printf("\r	DEBUG_AvCOMMIT_L1 is defined in %s:	auditing nominal activity within _av_commit(), AvPOST, AvCUT, and AvCUT_B4\n", __FILE__);
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

void deIceV_KE(){	DeICEv_KE(	u, v );	}
void deIceV_KEI(){	DeICEv_KEI(	u, v );	}
#ifdef DEBUG_ACCESS_L2			//	audit nominal activity verbosely
	#define dBUGinit_mx			_init_mx();
	#define dBUG_ReICEzSvZ($v )										cS=sprintf(aString, "\nReICEzSvZ( %d )\n", $v ); AvDBUG_PUSH( aString, cS );\
								if( (ui08*) cubeZ != (ui08*) SvPVbyte_nolen( svZ ) ){	cS=sprintf(aString, "\nReICEzSvZ( %d ): cubeZ [was] out of sync with svZ!\n", $v ); AvDBUG_PUSH( aString, cS );\
																	cubeZ=SvPVbyte_nolen( svZ );	\
																}
#else
	#define dBUGinit_mx
	#define dBUG_ReICEzSvZ($v )
#endif
#ifdef DEBUG_ACCESS_L3			//	check integrity
	#define dBUG_SvCUR($CS, $VARNAME )			if( $CS<16){ printf("\n!	%s< 16 ( %d )	%s line %lld\n",$VARNAME, $CS,  __FILE__, __LINE__ );	exit(-1);	}
#else
	#define dBUG_SvCUR($CS, $VARNAME )
#endif

#define uMOD	RW[ u ] = mod
#define vMOD	RW[ v ] = mod
#define vNUL		RW[ v ] = null;
#define uNEW 	RW[ u ] = new
#define vNEW 	RW[ v ] = new
#define Epsilon(	$cube) ( (ui64*) $cube+1)

void	_set240(){
	#ifdef DEBUG_ACCESS_L1			//	audit nominal activity
		#define dBUGop0		cS=sprintf(aString, "\r=+|_	x( %llX )	=+|_ 	\n\t",	x	); AvDBUG_PUSH( aString, cS );
		#define dBUGop1 		cS=sprintf(aString, "\r!|+=	x( f%llX )	!|+= 	\n\t",	x	); AvDBUG_PUSH( aString, cS );
		#define dBUGop2		cS=sprintf(aString, "\r=|+=	x( %llX )	=|+= 	\n\t",	x	); AvDBUG_PUSH( aString, cS );
		#define dBUGop3		cS=sprintf(aString, "\r=+|$	x( %llX )	=+|$ 	\n\t",	x	); AvDBUG_PUSH( aString, cS );
		#define dBUGop4		cS=sprintf(aString, "\r=+_ 	x( %llX )	=+_  	\n\t",	x	); AvDBUG_PUSH( aString, cS );
		#define dBUGop5		cS=sprintf(aString, "\r=+= 	x( %llX )	=+=  	\n\t",	x	); AvDBUG_PUSH( aString, cS );
		#define dBUGop6		cS=sprintf(aString, "\r_+_	x( %llX )	_+_  	\n\t",	x	); AvDBUG_PUSH( aString, cS );
		#define dBUGop7		cS=sprintf(aString, "\r_+=	x( %llX )	_+=  	\n\t",	x	); AvDBUG_PUSH( aString, cS );
		#define dBUGop8		cS=sprintf(aString, "\r===	x( %llX )	===  	\n\t",	x	); AvDBUG_PUSH( aString, cS );
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
	#endif
	#if defined( DEBUG_ACCESS_L1 ) || defined( DEBUG_ACCESS_L2 ) || defined( $DEBUG_ACCESS_L3 )
		#define dBUGop9		cS=sprintf(aString, "\r=|==	x( %llX )	=|==  	\n\t",	x	); AvDBUG_PUSH( aString, cS );
	#else
		#define dBUGop9
	#endif

	SV ** pSv;			pSv0	= AvARRAY(	avICE );								dBUGavCLR	dBUGinit_mx
ui64	x = ARG0;		hit=a=0;	za	= AvFILLp(	avArg);				if( za ==-1){	/*	no args */		return;	}
					zzC=(	zC	= AvFILLp(	avICE )	)-1;			if( zC ==-1){		NEW(	0 );		return;	}
ui64							nC	= zC+1;	/*<— value to reset upper boundary (ub) to		*/
																if( za >=247 ){	printf("!	_set(): too many arguments (buffer rotation not yet implemented)\n");	return;	}
	INIT_SvCOMMIT;
	INIT_AvCOMMIT;

ui64	/*	shall we begin?	*/	lb=0, ub=nC;	cube = SvPVbyte_nolen(	*pSv0 );	// so, x is probably not in cube 0, but we handle it now to eliminate a special case within INTRALOC, which is a search entrance.
if( 	/*	x not in cube 0	*/	x >= *Epsilon(	cube)){							iC= ub>>1;
  do	{/*	search for iC of x	*/				cube = SvPVbyte_nolen(	sv =*(pSv0 +	iC ) );
	if(						x == *Epsilon(	cube) ){				zcZ = zcOf( cube );	
							cubeZ	=	cube;	CSZ = SvCUR(	svZ= sv );	_anteloc:	ANTELOC;				//_print_mx(tena_zc, ix1, izZ );
		if( iC< zC	){	sv=*( ++	iC	+pSv0 );	cube = SvPVbyte_nolen(	sv);			_interloc:	INTERLOC;										//_print_mx(tena_zc, ix1, izZ);
			/*						RW []	Q []		A []			B []				E []			O []			I []	*/
/*	=+|_	*/	do	{ if(		A[ 0 ] >1 ){		 	--	A[ 0 ];	   ++	B[ 255 ];												dBUGop0
							++	*Epsilon(	cubeZ);					if( za == a ){		ReICEzSvZ(255);	goto	_exit_1;		}
					}else if(	A[ 0 ]==1 ){				A[ 0 ]=A[255];	B[ 0 ]+=B[255]+1;													//_print_mx(tena_zc, ix1, izZ);
/*	!|+=		*/			if(	zcZ == 0 ){		 									AvCUT_B4( iC );						dBUGop1
/*	=|+=	*/			}else{	*Epsilon(	cubeZ) -=  	A[ 255 ]	+	B[ 255 ];
							cubeZ[zcZ--]=0;			SvCUR_set( svZ, O[ 255 ] );		cubeZ[O[255]]=0;						dBUGop2
							}																	goto	_next_a;
/*	=|==	*/		}else{ /* rogue null off-cycle is an artifact which the spec must allow */	dBUGop9 		goto	_next_a;   	}
	x = ARG( ++a );   	} while(	x == *Epsilon(	cubeZ ) );									ReICEzSvZ(255);	goto	_next_x;
		}else{	do	{		 ++	*Epsilon(	cubeZ );				  ++	B[ 255 ];												dBUGop3
/*	=+|$	*/													if( za == a ){		ReICEzSvZ(255);	goto	_exit_2; 	}
	x = ARG( ++a );	} while(	x == *Epsilon(	cubeZ ) );									ReICEzSvZ(255);
							E_=	*Epsilon(	cubeZ );													goto	_epiloc;
			}

	}else if(					x <	*Epsilon(	cube) ){	iC=(( ub	= iC )+lb	)>>1;  if( iC==ub ){	INTRALOC;		goto	_loca; 	}
	}else{				/*	x >	*Epsilon(	cube)*/	iC=(( lb	= iC )+ub	)>>1;  if( iC==lb  ){	INTRALOC1Up;			_loca:
		MxINIT; 			tena_zc=zc=zcOf(	cube );
		u=0; v=1;				DeICE0u_E(	0, 	1	);
		while( x >E[ u ] ){		DeICEv_EI(	u,	v	);	u =v++; }												I[ u ] =icI =ic;
/*	inclusion	*/
	_run: do{ if(				x !=E[u] ){
							d = E[u] -x -B[u];																						//_print_mx(tena_zc, ix1, izZ);
/*	_+_		*/	if(			d >1	){	vNEW;	Q[v]=0;	A[ v ] = d -1;	B[ v ] = B[ u ];		E[ v ] =E[ u ];/*O[v]=O[u]+Q[u];*/			dBUGop6
						++tena_zc;	uMOD;			A[ u ] -= d;	B[ u ] = 1;		E[ u ] =x +1;	O[v+1]=O[v];	I[ v ] = I[ u ];				//_print_mx(tena_zc, ix1, izZ);	
/*	_+=		*/	}else if(		d==1 ){	uMOD;		    --	A[ u ];	   ++	B[ u ];												dBUGop7
/*	===		*/	}else{	++hit;	/*	RW []	Q []		A []			B []				E []			O []			I []	*/		dBUGop8
					}
			}else{					uMOD;					if(	RW[ v ]== null ){	DeICEv_KEI( u, v );  }								//_print_mx(tena_zc, ix1, izZ);	
/*	=+_		*/	if(		A[ v ] >1 ){	vMOD;		    --	A[ v ];	   ++	B[ u ];		   ++	E[ u ];								dBUGop4
/*	=+=		*/	}else{	--tena_zc;  	vNUL;						B[ u ]+= A[v]+B[v];	E[ u ] =E[ v ];	O[v]+=Q[v];				dBUGop5//	printf("\nop5 (=+=): u, v, w= %d, %d, %d	I[u]=%d	I[v]=%d	I[w]=%d\n\n", u, v, v+1, I[u], I[v], I[v+1] );
				}	}

	_next_a:	if( za != a ){		x = ARG( ++a );
	_next_x:	    if(				x <	*Epsilon(	cube) ){	   								CoINTRaLOC;
			    }else{			/*	*	*	*	*	*	*	*	*	*	*	*	*/	SvCOMMIT;
				if(			iC< zzC){		cube = SvPVbyte_nolen(	sv = *( ++iC +pSv0 ) );
						if(	x >	*Epsilon(	cube) )		/* break run; resume search */					break;
				}else	if(	iC != zC){		cube = SvPVbyte_nolen(	sv = *( ++iC +pSv0 ) );
						if(	x >	*Epsilon(	cube) ){		/* past end (2 cubes up)		*/	E_=*Epsilon(	cube); goto	_epiloc;	}
				}else	{							/* past end (1 cube up)		*/	E_=*Epsilon(	cubeZ);		_epiloc:
							if( dsc || rSeqIns[0] || rSeqCut[0] ) 	_av_commit();			EPILOC( E_ );		return;
						}
				if(			x != *Epsilon(	cubeZ)){
						if(	x != *Epsilon(	cube )){	CS = SvCUR(	sv );				/*	ReINTRALOC;	*/	goto	_loca;	}
						else{	cubeZ =	cube;	CSZ=SvCUR(	svZ = sv ); zcZ = zcOf(	cube );			goto	_anteloc;	}
				}else	{														ANTELOC;		goto	_interloc;
			    }	}		}														else				goto	_exit_1;
/*	run */	} while( 1 );		lb =iC+1;	ub=nC;		iC= ( lb+ub )>>1;
	}	}	} while( 1 );		/* search	*/
    }else										{	CS=SvCUR( sv=*pSv0 );		iC=0;
/* special case to start in cube 0 eliminates a branch */	CSZ=16;	zcZ=0;	cubeZ = nube;						goto	_loca;
											}
	_exit_1:																		SvCOMMIT;
	_exit_2:				if( dsc || rSeqIns[0] || rSeqCut[0] ) 	_av_commit();
	}




#define zcNUL	RW[ zc ] = null
#define uDEL		RW[ u ] = del
#define UnREADv	if( RW[ v ] !=null ) --ic;
#define EXIT printf("\nexit line %lld\n", __LINE__ );

void	_unset(){
	#ifdef DEBUG_ACCESS_L1			//	audit nominal activity
		#define dBUGopA0	cS=sprintf(aString, "\r=|x=	x( %llX )	=|x=  	! ! ! A==0 ic#%d cube #%lld \n\t",	x, ic, iC	); AvDBUG_PUSH( aString, cS );
		#define dBUGopB0	cS=sprintf(aString, "\r=|x!	x( %llX )	=|x=  	! ! ! B==0 ic#%d cube #%lld \n\t",	x, ic, iC	); AvDBUG_PUSH( aString, cS );
		#define dBUGopB		cS=sprintf(aString, "\r=|__	x( %llX )	=|__  	\n\t",	x	); AvDBUG_PUSH( aString, cS );
		#define dBUGopC		cS=sprintf(aString, "\r=x= 	x( %llX )	=x=  	\n\t",	x	); AvDBUG_PUSH( aString, cS );
		#define dBUGopD 		cS=sprintf(aString, "\r=x_ 	x( %llX )	=x_  	\n\t",	x	); AvDBUG_PUSH( aString, cS );
		#define dBUGopE		cS=sprintf(aString, "\r_x= 	x( %llX )	_x=  	\n\t",	x	); AvDBUG_PUSH( aString, cS );
		#define dBUGopF		cS=sprintf(aString, "\r_x_ 	x( %llX )	_x_  	\n\t",	x	); AvDBUG_PUSH( aString, cS );
		#define dBUGopX		cS=sprintf(aString, "\r___	x( %llX )	___   	\n\t",	x	); AvDBUG_PUSH( aString, cS );
		#define dBUGopC2	cS=sprintf(aString, "\r=x=| 	x( %llX )	=x=| 	\n\t",	x	); AvDBUG_PUSH( aString, cS );
		#define dBUGopD2	cS=sprintf(aString, "\r=x|_ 	x( %llX )	=x|_ 	\n\t",	x	); AvDBUG_PUSH( aString, cS );
		#define dBUGopE2		cS=sprintf(aString, "\r_x=| 	x( %llX )	_x=| 	\n\t",	x	); AvDBUG_PUSH( aString, cS );
		#define dBUGopF2a	cS=sprintf(aString, "\r!x|_ 	x( %llX )	!x|_ 	\n\t",	x	); AvDBUG_PUSH( aString, cS );
		#define dBUGopF2b	cS=sprintf(aString, "\r_x|_ 	x( %llX )	_x|_ 	\n\t",	x	); AvDBUG_PUSH( aString, cS );
		#define dBUGopX2		cS=sprintf(aString, "\r__|_	x( %llX )	__|_ 	\n\t",	x	); AvDBUG_PUSH( aString, cS );
	#else
		#define dBUGopA0
		#define dBUGopB0
		#define dBUGopB
		#define dBUGopC 
		#define dBUGopD
		#define dBUGopE
		#define dBUGopF
		#define dBUGopX
		#define dBUGopC2
		#define dBUGopD2
		#define dBUGopE2
		#define dBUGopF2a
		#define dBUGopF2b
		#define dBUGopX2
	#endif
	#ifdef $DEBUG_ACCESS_L3
		#define dBUG_B0		cS=sprintf(aString, "! B==0 ic#%d cube #%lld %s line %lld  %s\n", ic, iC, __FILE__, __LINE__, __FUNCTION__ ); 	AvDBUG_PUSH( aString, cS );
	#else
		#define dBUG_B0
	#endif
	#if defined( DEBUG_ACCESS_L1 ) || defined( DEBUG_ACCESS_L2 ) || defined( $DEBUG_ACCESS_L3 )
		#define dBUGopA		cS=sprintf(aString, "\r|x=	x( %llX )	=|x=  	\n\t",	x	); 					AvDBUG_PUSH( aString, cS );
	#else
		#define dBUGopA
	#endif
ui64		Ac, Bc, Ec;
ui08 	Qc;

	SV ** pSv;			pSv0	= AvARRAY(	avICE );								dBUGavCLR	dBUGinit_mx
ui64	x = ARG0;		hit=a=0;	za	= AvFILLp(	avArg);				if( za ==-1){	/*	no args */		return;	}
					zzC=(	zC	= AvFILLp(	avICE )	)-1;			if( zC ==-1){		NEW(	0 );		return;	}
ui64							nC	= zC+1;	/*<— value to reset upper boundary (ub) to		*/
																if( za >=247 ){	printf("!	_set(): too many arguments (buffer rotation not yet implemented)\n");	return;	}
	INIT_SvCOMMIT;
	INIT_AvCOMMIT;

ui64	/*	shall we begin?	*/	lb=0, ub=nC;	cube = SvPVbyte_nolen(	*pSv0 );	// so, x is probably not in cube 0, but we handle it now to eliminate a special case within INTRALOC, which is a search entrance.
if( 	/*	x not in cube 0	*/	x >= *Epsilon(	cube)){							iC= ub>>1;
  do	{/*	search for iC of x	*/				cube = SvPVbyte_nolen(	sv =*(pSv0 +	iC ) );
	if(						x == *Epsilon(	cube) ){															_anteloc:
		if( iC< zC	){	sv=*( ++	iC	+pSv0 );	cube = SvPVbyte_nolen(	sv);
				MxINIT; 	tena_zc=zc=zcOf(	cube); 	DeICE0u_E(	0, 	1	);												dBUGopA0;
/*	|x=	*/		if(		A[0] == 0 ){
					if(	B[0] >1){		uMOD;			A[ 0 ] =1;	   --	B[ 0 ];			u=0; v=1;					I[ 0 ] =icI =0;
					}else{						DeICEv_K(	0, 1 );	A[1]+=B[0];	u=1; v=2;					I[ 1 ] =icI =1;	dBUGopB0;
						}
				//	}else if(	B[0]==1){				DeICEv1_KI(	0, 1 ); printf("\nDeICEv1\n");						I[ 1 ] =icI =1;
				//	}else{						dBUG_B0;										return;	}
/*	|__ 	*/		}else{	++miss;													dBUGopB;	}
		}else{			++miss;													dBUGopB;	}	goto	_next_a;
	}else if(					x <	*Epsilon(	cube) ){	iC=(( ub	= iC )+lb	)>>1;  if( iC==ub ){	INTRALOC;		goto	_loca; 	}
	}else{				/*	x >	*Epsilon(	cube)*/	iC=(( lb	= iC )+ub	)>>1;  if( iC==lb  ){	INTRALOC1Up_EX;			_loca:
		MxINIT; 			tena_zc=zc=zcOf(	cube );	DeICEzu(	255	);					Ec = *Epsilon( cube )-A[255] -B[255];
		if(					x< Ec ){				DeICE0u_E(	0, 	1	);	u=0; v=1;
			while( x >E[ u ] ){						DeICEv_E(	u,	v	);	u = v++; }						I[ u ] =icI =ic;
			do{	d =E[u] -x;
/*exclusion*/	    if( d >=1&&	B[ u ] >=d ){	uMOD;
				if(		B[ u ] >1 ){
					if(	B[ u ] !=d ){
/*	=x=		*/			if(	d!=1 ){			//	_print_mx( 12, ixM, izM );
								if(	RW[ v ] )	{w=v+1;	RW[ w ]=RW[v];	printf( lightning ); printf("\nunset: shunt v to w\n");
											Q[w]=Q[v]; A[w]=A[v];	B[w]=B[v];		E[ w ] = E[ v ];				I[w]=I[v];
											}												O[v+1]=O[v];
									vNEW;	Q[v]=Q[u]; A[ v ]=1;	B[ v ]=d-1;		E[ v ] = E[ u ];				I[ v ] = I[ u ];
						++tena_zc;			Q[u]=0;	/*	i +=	*/	B[ u ]-=d;			E[ u ]-= d;	/*Ox[ u ]=16;	I[ u ] = 0;*/	dBUGopC;
/*	=x_		*/			}else{								if(	RW[ v ]== null ){	DeICEv_KEI( u, v );  }	
									vMOD;		  ++	A[ v ];/*i+=*/--B[ u ];			--E[ u ];								dBUGopD;
							}
/*	_x=		*/		}else{						  ++	A[ u ];	   --	B[ u ];												dBUGopE;
						}
/*	_x_		*/	}else if( u<=--tena_zc){							if(	RW[ v ]== null ){//	DeICEvINC_KEI( u, v );	}else{
																				DeICEv_KEI( u, v );  }	
													A[u] += A[v]+1;
									vNUL;						B[ u ]=B[ v ];		E[ u ]=E[ v ];	O[v]+=Q[v];	I[ u ] = I[ v ];	dBUGopF;
					}														//	}
				else	{				uDEL;	Q[ u ]=0;											Ox[ u ]=16;
					}
/*	___	*/	    }else	{	++miss;	/*	RW []	Q []		A []			B []				E []			O []			I []	*/		dBUGopX;
					}
	_next_a:	    if( za != a ){		x = ARG( ++a );
	_next_x:		if(			x <	Ec ){				   								CoINTRaLOC;
				}else{															SvCOMMIT;	
				    if(			iC< zzC){		cube = SvPVbyte_nolen(	sv = *( ++iC +pSv0 ) );
						if(	x >	*Epsilon(	cube) )					/* break run; resume search */		break;
				    }else	if(	iC != zC){		cube = SvPVbyte_nolen(	sv = *( ++iC +pSv0 ) );
						if(	x >	*Epsilon(	cube) ){	CS=SvCUR( sv );	/* end (2 up) */miss+=1+( za-a );	EXIT	goto	_exit_1;	}
				    }else	if(	x <	*Epsilon(	cubeZ) ){													goto	_interloc;
				    }else	{						CS=SvCUR( sv );	/* end (1 up) */miss+=1+( za-a );	EXIT	goto	_exit_1;
						}
				    if(			x <	*Epsilon(	cubeZ) ){	CS = SvCUR(	sv );									goto	_interloc;	}
				    if(			x != *Epsilon(	cubeZ)){
						if(	x != *Epsilon(	cube )){	CS = SvCUR(	sv );				/*	ReINTRALOC;	*/	goto	_loca;	}
						else{	cubeZ =	cube;	CSZ=SvCUR(	svZ = sv ); zcZ = zcOf(	cube );			goto	_anteloc;	}
				    }else																			goto	_anteloc;
				}   }else{	EXIT				goto	_exit_1;	}
/*	run */	    } while( 1 );


		}else{	 cubeZ = cube; zcZ	= zcOf(	cubeZ );									CSZ = SvCUR(	svZ= sv );
										cube = SvPVbyte(	sv = *( ++iC +pSv0 ),		CS );					_interloc:
			MxINIT;		tena_zc=zc=zcOf(	cube );	DeICEzu(	zc	);					Ec = *Epsilon( cube )-A[zc] -B[zc];
/*	exclusion	(interlocated)	*/						DeICE0u_KE( 	0,	1	);/*	u=0;v=1;	*/						I[ 0 ] =icI =0;
			do{	d =*Epsilon( cubeZ )-x;
			    if( d >=1&&	B[255]>=	d ){	RW[0]=mod;
				if(		B[255] >1 ){
					if(	B[255] !=	d ){
/*	=x=| 	*/			if(	d != 1 ){  	ic=-1;			A[0]=1;		B[0] =	d-1;		E[0] = *Epsilon( cubeZ );					dBUGopC2;
						++tena_zc;	RW[1]=new;					B[255] -=	d;		*Epsilon( cubeZ )= d;
/*	=x|_ 	*/			}else	{				  ++	A[0];	   --	B[255];		   --	*Epsilon( cubeZ );						dBUGopD2;
								}	_print_mx(4, 0, 0);	u=0;v=1;		ReICEzSvZ(255);	goto	_next_a;
/*	_x=| 	*/		}else{			RW[255]=mod;  ++	A[255];	   --	B[255];		/*	only case which stays in this loop */		dBUGopE2;	}
				}else{								A[0]+=A[255]+	B[255];
/*	!x|_ 	*/		if(	zcZ == 0 ){		 			/*			^NULL?...o.O*/	AvCUT_B4( iC );						dBUGopF2a;
/*	_x|_ 	*/		}else{ cubeZ[zcZ--]=0; SvCUR_set( svZ, O[ 255 ] ); cubeZ[O[255]]=0;		*Epsilon(	cubeZ )-=A[255]+1;				dBUGopF2b;
						}												u=0;v=1;					goto	_next_a;
/*	__|_ 	*/ 	}	}
			    else	{	++miss;	/*	RW []	Q []		A []			B []				E []			O []			I []	*/		dBUGopX2;
					}
			    if( za != a )		x = ARG( ++a ); 		else{	if( RW[255] ){ReICEzSvZ(255); }			 	goto	_exit_2; 	}
			    } while(		x < *Epsilon(	cubeZ ) );			if( RW[255] ){ReICEzSvZ(255); }	u=0;v=1;		goto	_next_x;

			}				lb =iC+1;	ub=nC;		iC= ( lb+ub )>>1;
	}	}	} while( 1 );		/* search	*/
    }else										{	CS=SvCUR( sv=*pSv0 );		iC=0;
/* special case to start in cube 0 eliminates a branch */	CSZ=16;	zcZ=0;	cubeZ = nube;						goto	_loca;
											}
	_exit_1:																		SvCOMMIT;	
	_exit_2:				if( dsc || rSeqIns[0] || rSeqCut[0] ) 	_av_commit();
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
		pq=								cube +16;
						zc = zcOf(		cube );
		for(	ic=0;  ic<=	zc; ++ic ){	 deICE(	cube[ ic ], Qc, Ac, Bc );
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

	for(		iC=0; iC<= zC;  ++iC ){						sv = *( sviC0 +iC );
									cube = SvPVbyte(	sv,  CS );
		pq=							cube +16;
					zc = zcOf(		cube );
		for(	ic=0;  ic<=zc; ++ic ){	deICE(	cube[ ic ], Qc, Ac, Bc );
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

/*	dooooo	f*/