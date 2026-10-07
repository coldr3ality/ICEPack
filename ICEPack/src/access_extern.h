extern	bool	trace;
extern	void	_av_commit(),
			_sv_commit_1x(),
			_sv_commit_nx(),
			_print_mx(		unsigned char mx_max, short ix¹, short izΩ ),
			_print_mx_hex(	unsigned char mx_max, short ix¹, short izΩ ),
			printAvDBUG(),
			_init_mx(),
			deIce_vEI(), deIce_vKE(), deIce_vKI(), deIce_vKEI(), deIce_vKEI2(),
			reIce_uO(	ui16 u, ui16 v ),
			reIce_uOx(	ui16 u, ui16 v );

extern AV	*	avDBUG;	extern bool			run_iC;
extern AV	*	avICE;		extern long long int	iC,	iCI,		iCO, /*iCx, post_C, */zC, zzC, rel_iC;
extern AV	*	avArg;		extern long long int	a, za; 					//	a list of integer value[s] to operate on.
extern SV	**	Aº,
			**	src,
			**	dst,
			*	svA,					/*	general purpose scratch SV								*/
			*	svΩ,	 				/*	SV containing right-hand cube data	(upper fragment)		*/
			*	sv,					/*	SV containing pre-commit cube data	(original pre-op cube)	*/
			*	sv0,					/*	SV containing left-hand cube data		(lower fragment)		*/
			*	_sv_;				/*	const SV which points to const char* "nube"					*/
extern char	*	lightning,
				aString[],
				exit_code;
#if defined( DEBUG_ACCESS_L0 ) || defined (DEBUG_ACCESS_L1 ) || defined( DEBUG_ACCESS_L2X )
extern unsigned long long int		ƒloc;
#endif
extern STRLEN	cS, CS, CSΩ, oCS;

extern ui08		zube[16];
extern char		iqZ;
extern ui08	*	cube,				/*	unsigned char * cube data (of index iC )					*/
			*	cubeΩ,				/*	unsigned char * cube data (of index iC -1)					*/
			*	cube¹,
				nube[16],				/*	null cube / new cube									*/
				*pk,		*pq,		*pΩ,
			/*	*pkz,	*/		*pqz,
			/*	*pk_,	*/		*p_,	
			/*	*pkx,			*pqx,	*/
				q, q0, q1,		/*	q-field lengths, used generically	*/
				buf[];


extern ui64	hit, miss;


extern short unsigned 	u, v, w,					/*	matrix indeces		iterate		the modification range		in	matrix { A[], B[], E[], L[] }	*/
	ixº,	/*	ix¹,	ixⁿ,	ix²,	*/	ixΩ,				/*	matrix indeces		mark in		fragment boundaries		in	matrix { A[], B[], E[], L[] }	*/
		/*	iz¹,	izⁿ,	iz²,	*/	izΩ,				/*	matrix indeces		mark out		fragment boundaries		in	matrix { A[], B[], E[], L[] }	*/
/*			^localized to:	(void) _sv_commit_1x()
						(void) _sv_commit_nx()	*/

					ixM, izM,		 			/*	matrix indeces		mark in/out	the Modification range		in	matrix { A[], B[], E[], L[] }	*/
					inM,	/*	izM+1		*/	/*	matrix index			high-bounds	the Modification range		in	matrix { A[], B[], E[], L[] }	*/
					ixH;	/*	inM+n_del	*/	/*	matrix index			marks in		the High-passthrough range	in	matrix { A[], B[], E[], L[] }	
												for inclusion-based methods, izM is always ixH -1.
												for exclusion-based methods, izM can be less than that, as cycla in-between are dropped.			*/
extern char unsigned	q,	q0,	q1;		/*	q-field lengths			total		the q-data length			of any given cyclum			*/
extern char	ic, 				/*	cyclum index			iterates		the read position			in	char *	cube			*/
		/*	icI,*/ icO,			/*	cyclum indeces		mark in/out	the Modification range		in	char *	cube			*/
			zc,	zcΩ, zcC;		/*	cyclum index 			identifies		the zeta cyclum			of	char *	cube / cubeΩ		*/
extern short	oc, ocª, xc, xcª;	/*	cyclum index			identifies		the tentative zeta cyclum	of	char *	cube			*/

extern char *	opStat[];
extern enum	opStat{	null, del, ok, mod, new, epi }	/*doing something tricky with bit-2 to test for ok||mod at once.  */
											/* To add a 7th enumeration would interfere with that.		*/
			RW[	512 ];			/* read/write status enumerator			*/
extern ui64	A[	512 ],	Ac,		/* relative coord.s	which define	each negative cyclum phase	in	matrix { A[], B[], E[], L[] }	*/
			B[	512 ],	Bc,		/* relative coord.s	which define	each positive cyclum phase	in	matrix { A[], B[], E[], L[] }	*/
			E[	512 ],	Ec, E_;	/* "Edge" values	which bound	the absolute coordinates	in	matrix { A[], B[], E[], L[] }	*/
//			Zc[	512 ];			/* cube lengths, pre-re-fragmentation  	*/
extern ui08 	I[	512 ],			/* cycla indeces	which align	pre/post op keybytes		in	char *	cube			*/
			K[	512 ],			/* header codes	which encode	variable q-data layout		in	char *	cube			*/
			L[	512 ],	Lc;		/* q-data lengths	which define	each read increment		in	char *	cube			*/
extern ui16	O[	512 ],			/* q-data offsets	which mark	each read position			in	char *	cube			*/
			Oª[	512 ];			/* q-data offsets	which mark	each write position			in	char *	cube			*/

// array resequencing buffer matrix
extern SV	*	rSeq_SV[	512 ]; 	// temporary holding of SV* cubes pending insertion into AV* avICE
extern long long int	rSeq_iR[	512	], iR,	// source index of rSeq_SV 				(for each control point)
				rSeqIns[	512	],	// the number of trailing SVs to insert		(for each control point)
				rSeqCut[	512	],	// the number of leading SVs to remove 	(for each control point)
				rSeqSrc[	512	],	// source index						(for each control point)
				rSeqDst[	512	],	// destination index						(for each control point)
				rel_zC, 	dsc,  asc, /*zsc, juke, pmo,*/
				cut_iC,
				step_iC;			// running control point iterator

