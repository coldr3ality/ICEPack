#include	"_ICE.h"
extern char	* cube_err[],
			* svtype_err,
			* malloc_err,
			* usage_err[];

extern AV	*	avOut,
			*	avDBUG,
			*	avICE,
			*	avICE_;		extern long long int	zCs;
extern AV	*	avArg;		extern long long int	a, za; 					//	a list of integer value[s] to operate on.
extern char		aString[];
extern const char	*svtype_names[],
				*svtype_names_ref[];
extern ui08		svtype_cnt;

extern char *	opStat[];
extern enum	opStat{	null, del, ok, mod, new}

			RW[	512 ];			/* read/write status enumerator			*/

extern ui64	A[	512 ],	Ac,		/* relative coord.s	define		each negative cyclum phase		in	matrix { A[], B[], E[], L[] }	*/
			B[	512 ],	Bc,		/* relative coord.s	define		each positive cyclum phase		in	matrix { A[], B[], E[], L[] }	*/
			E[	512 ],	Ec;		/* "Edge" values	bound		each absolute cyclum range		in	matrix { A[], B[], E[], L[] }	*/
extern ui08 	I[	512 ],			/* cycla indeces	align		pre op / post op keybytes		in	char *	cube			*/
			K[	512 ],			/* keybytes		encode		each cyclum's q-data geometry	in	char *	cube			*/
		*	Qp[	512 ],
			L[	512 ],	Qc;		/* q-data lengths	which define	each read increment			in	char *	cube			*/
extern ui16	O[	512 ],			/* q-data offsets	mark		each read position				in	char *	cube			*/
			Oª[	512 ];			/* q-data offsets	mark		each write position				in	char *	cube			*/
extern char unsigned 	u, v, w,		/* matrix indeces	iterate		the modification range			in	matrix { A[], B[], E[], L[] }	*/
					ixM, izM;		/* matrix indeces	mark in/out	the Modification range			in	matrix { A[], B[], E[], L[] }	*/


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
			*	fmtLLX[	24	] ={
				NULL,	" %c%03llX ",					" %c%03llX ",				" %c%03llX  ",			" %c%03llX   ",		" %c%03llX   ",		" %c%03llX     ",		" %c%03llX      ",
						" %c%llX       ",				" %c%llX        ",			" %c%llX         ",		" %c%llX          ",		" %c%llX          ",		" %c%llX            ",		" %c%llX             ",
						" %c%llX              ",				" %c%llX               ",		" %c%llX                ",	" %c%llX                 ",	" %c%llX                 ",	" %c%llX                   ",	" %c%llX                    ",
						" %c%llX                     ",			" %c%llX                      "	},
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


#define WSPACE_UNSAFE($pr, $WS )	\
	while(	$WS >7 ){			*( (ui64*)(	$pr		) )=0x2020202020202020;	$pr += 8;	$WS-=8;	}	\
	switch(	$WS ){	case 0x0:												break;	\
					case 0x1:	*( (ui08*) (	$pr		) )=0x20;					break;	\
					case 0x2:	*( (ui16*) (	$pr		) )=0x2020;				break;	\
					case 0x3:	\
					case 0x4:	*( (ui32*) (	$pr		) )=0x20202020;			break;	\
					case 0x5:	\
					case 0x6:	\
					case 0x7:	*( (ui64*)(	$pr		) )=0x2020202020202020;			\
				}							$pr+=$WS;

#define WSPACE($pr, $WS )	\
	while(	$WS >7 ){			*( (ui64*)(	$pr		) )=0x2020202020202020;	$pr += 8;	$WS-=8;	}	\
	switch(	$WS ){	case 0x0:												break;	\
					case 0x1:	*( (ui08*) (	$pr		) )=0x20;					break;	\
					case 0x2:	*( (ui16*) (	$pr		) )=0x2020;				break;	\
					case 0x3:	*( (ui16*) (	$pr		) )=0x2020;						\
								*( (ui08*) (	$pr +2 	) )=0x20;					break;	\
					case 0x4:	*( (ui32*) (	$pr		) )=0x20202020;			break;	\
					case 0x5:	*( (ui32*) (	$pr		) )=0x20202020;					\
								*( (ui08*) (	$pr +4 	) )=0x20;					break;	\
					case 0x6:	*( (ui32*) (	$pr		) )=0x20202020;					\
								*( (ui16*) (	$pr +4 	) )=0x2020;				break;	\
					case 0x7:	*( (ui32*) (	$pr		) )=0x20202020;					\
								*( (ui16*) (	$pr +4 	) )=0x2020;						\
								*( (ui08*) (	$pr +6 	) )=0x20;							\
				}							$pr+=$WS;

