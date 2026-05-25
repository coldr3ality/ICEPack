extern AV	*	avOut,
			*	avDBUG,
			*	avICE;		extern long long int	iC, iCI, iCO, iCx, post_C, zC, zzC, post_zC, rel_iC, less_iC;  	//	iC is the index of the current cube.  zC is the array index of the ending cube.
extern AV	*	avICE_;		extern long long int	zCs;
extern AV	*	avArg;		extern long long int	a, za; 					//	a list of integer value[s] to operate on.
extern SV	**	src,
			**	dst,
			**	pSv0,
			*	svA;			/*	general purpose scratch SV								*/
extern ui08		svtype_cnt;
extern ui64		skip, hit, miss;	/*	the number of misses or collissions counted as a method processes arguments  		*/

extern char unsigned	u, v, w,	/*	matrix indeces		iterate		the modification range		in	matrix { A[], B[], E[], Q[] }	*/
/*	ix1,	ixX,	ixY,	*/	ixZ,		/*	matrix indeces		mark in		fragment boundaries		in	matrix { A[], B[], E[], Q[] }	*/
/*	iz1,	izX,	izY,	*/	izZ,		/*	matrix indeces		mark out		fragment boundaries		in	matrix { A[], B[], E[], Q[] }	*/
/*	^commented out because they do not need to be global.  Only the high fragment is ever seen outide of void _sv_commit().				*/

	ixM, izM,		 			/*	matrix indeces		mark in/out	the Modification range		in	matrix { A[], B[], E[], Q[] }	*/
	inM,	/*	izM+1		*/	/*	matrix index			high-bounds	the Modification range		in	matrix { A[], B[], E[], Q[] }	*/
	ixH;	/*	inM+n_del	*/	/*	matrix index			marks in		the High-passthrough range	in	matrix { A[], B[], E[], Q[] }	
								for inclusion-based methods, izM is always ixH -1.
								for exclusion-based methods, izM can be less than that, as cycla in-between are dropped.			*/

//char unsigned	q,	q0,	q1;		/*	q-field lengths			total		the q-data length			of any given cyclum			*/
char			ic, 				/*	cyclum index			iterates		the read position			in	char *	cube			*/
			icI,	icO,			/*	cyclum indeces		mark in/out	the Modification range		in	char *	cube			*/
			zc,	zcZ,			/*	cyclum index 			identifies		the zeta cyclum			of	char *	cube / cubeZ		*/
			tena_zc;			/*	cyclum index			identifies		the tentative zeta cyclum	of	char *	cube			*/

extern char *	opStat[];
extern enum	opStat{	null, ok, mod, new, del }
			RW[	256 ];			/* read/write status enumerator			*/

extern ui64	A[	256 ],	Ac,		/* relative coord.s	define	each negative cyclum phase		in	matrix { A[], B[], E[], Q[] }	*/
			B[	256 ],	Bc,		/* relative coord.s	define	each positive cyclum phase		in	matrix { A[], B[], E[], Q[] }	*/
			E[	256 ],	Ec,	E_;	/* "Epsilon" values	bound	each absolute cyclum range		in	matrix { A[], B[], E[], Q[] }	*/
extern ui08 	I[	256 ],			/* cycla indeces	align	pre op / post op keybytes		in	char *	cube			*/
			H[	256 ],			/* keybytes		encode	each cyclum's q-data geometry	in	char *	cube			*/
		*	Qp[	256 ],
			Q[	256 ],	Qc,		/* q-data lengths	define	each read increment			in	char *	cube			*/
			Qx[	256 ],			/* q-data lengths	define	each write increment			in	char *	cube			*/
			O[	256 ],			/* q-data offsets	mark	each read position				in	char *	cube			*/
			Ox[	256 ],			/* q-data offsets	mark	each write position				in	char *	cube			*/
		u,		v,		w,		/* matrix indeces	iterate	the modification vector			in	matrix { A[], B[], E[], Q[] }	*/
	ixM, izM;		 				/* matrix indeces	mark	the modification range			in	matrix { A[], B[], E[], Q[] }	*/
// array resequencing buffer matrix
extern SV	*	rSeq_SV[	256 ]; 	// temporary holding of SV* cubes pending insertion into AV* avICE
extern long long int	rSeq_iR[	256	], iR,	// source index of rSeq_SV 				(for each control point)
				rSeqIns[	256	],	// the number of trailing SVs to insert		(for each control point)
				rSeqCut[	256	],	// the number of leading SVs to remove 	(for each control point)
				rSeqSrc[	256	],	// source index						(for each control point)
				rSeqDst[	256	],	// destination index						(for each control point)
				rel_zC, 	dsc,  asc, zsc, juke, jmp,
				rack_iC;			// running control point iterator

extern char *		aString[8448];
extern STRLEN	cS, CS, CSZ;
extern ui08		*pk, *pq, *pqz,
				buf[	8 	+8	+8*16	+1	+15 ];	/*	buffers the output of ICE() and its variants
/*	CUBE STRUCT:	^	^	^		^	^ overflow padding (to survive an overshot "long long" cast)
					|	|	|		NULL byte
					|	|	up to 128 bytes of variable "q-data"
					|	"Epsilon" is the cube's search key.  It signifies the upper boundary of encoded keys within the cube.
					keybyte area stores up to (8) keybytes, which define variable "q-data" geometry for up to (8) inversion run cycla.
					*/

#define	ARG( $a )	SvIVX( svA=*(	AvARRAY(	avArg)+ $a	) )
#define	ARG0		SvIVX( svA=*	AvARRAY(	avArg)		)
