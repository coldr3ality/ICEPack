
#define SwCASE_LOWPASS_0IS(		lo$IS 	)	/* "0IS" means 	switch case vector 0 starts at zero,
															and arg[0] is both the input and output variable, "In Situ".	*/	\
		case 0x00:											lo$IS  =	0x0000000000000000;						break;\
		case 0x01:											lo$IS &=	0x00000000000000FF;						break;\
		case 0x02:											lo$IS &=	0x000000000000FFFF;						break;\
		case 0x03:											lo$IS &=	0x0000000000FFFFFF;						break;\
		case 0x04:											lo$IS &=	0x00000000FFFFFFFF;						break;\
		case 0x05:											lo$IS &=	0x000000FFFFFFFFFF;						break;\
		case 0x06:											lo$IS &=	0x0000FFFFFFFFFFFF;						break;\
		case 0x07:											lo$IS &=	0x00FFFFFFFFFFFFFF;							

#define SwCASE_LOWPASS_1IS(		lo$IS )		/* "1IS" means 	switch case vector 0 starts at one,
															and arg[0] is both the input and output variable, "In Situ".	*/	\
		case 0x00:											lo$IS &=	0x00000000000000FF;						break;\
		case 0x01:											lo$IS &=	0x000000000000FFFF;						break;\
		case 0x02:											lo$IS &=	0x0000000000FFFFFF;						break;\
		case 0x03:											lo$IS &=	0x00000000FFFFFFFF;						break;\
		case 0x04:											lo$IS &=	0x000000FFFFFFFFFF;						break;\
		case 0x05:											lo$IS &=	0x0000FFFFFFFFFFFF;						break;\
		case 0x06:											lo$IS &=	0x00FFFFFFFFFFFFFF;						break;\
		case 0x07:																							

#define SwCASE_LOWPASS_0I( lo$,	$dst )		/* "0I" means 	switch case vector 0 starts at zero,
															arg[0] is the input variable, and
															arg[1] is the output variable (Inline).					*/	\
		case 0x00:		$dst =										= 0x0000000000000000; 					break;\
		case 0x01:		$dst =									lo$  & 0x00000000000000FF;						break;\
		case 0x02:		$dst =									lo$  & 0x000000000000FFFF;						break;\
		case 0x03:		$dst =									lo$  & 0x0000000000FFFFFF;			 			break;\
		case 0x04:		$dst =									lo$  & 0x00000000FFFFFFFF;						break;\
		case 0x05:		$dst =									lo$  & 0x000000FFFFFFFFFF;						break;\
		case 0x06:		$dst =									lo$  & 0x0000FFFFFFFFFFFF;						break;\
		case 0x07:		$dst =									lo$  & 0x00FFFFFFFFFFFFFF;							

#define SwCASE_LOWPASS_1I( lo$,	$dst )		/* "1I" means 	switch case vector 0 starts at one,
															arg[0] is the input variable, and
															arg[1] is the output variable (Inline).					*/	\
		case 0x00:		$dst =									lo$  & 0x00000000000000FF;						break;\
		case 0x01:		$dst =									lo$  & 0x000000000000FFFF;						break;\
		case 0x02:		$dst =									lo$  & 0x0000000000FFFFFF;						break;\
		case 0x03:		$dst =									lo$  & 0x00000000FFFFFFFF;						break;\
		case 0x04:		$dst =									lo$  & 0x000000FFFFFFFFFF;						break;\
		case 0x05:		$dst =									lo$  & 0x0000FFFFFFFFFFFF;						break;\
		case 0x06:		$dst =									lo$  & 0x00FFFFFFFFFFFFFF;						break;\
		case 0x07:		$dst =									lo$;										

#define SwCASE_XOVER_0T( hi$,	lo$T )			/* "0T" means	switch case vector 0 starts at zero,
															and arg[0] "Tees into" arg[1], which is also the output variable.	*/	\
		case 0x00:	lo$T = hi$;																					break;\
		case 0x01:	tail =	hi$  & 0xFFFFFFFFFFFFFF00;     	head =	lo$T	&0x00000000000000FF;		lo$T = head|tail;     	break;\
		case 0x02:	tail =	hi$  & 0xFFFFFFFFFFFF0000;     	head =	lo$T	&0x000000000000FFFF;		lo$T = head|tail;     	break;\
		case 0x03:	tail =	hi$  & 0xFFFFFFFFFF000000;     	head =	lo$T	&0x0000000000FFFFFF;		lo$T = head|tail;     	break;\
		case 0x04:	tail =	hi$  & 0xFFFFFFFF00000000;     	head =	lo$T	&0x00000000FFFFFFFF;		lo$T = head|tail;     	break;\
		case 0x05:	tail =	hi$  & 0xFFFFFF0000000000;     	head =	lo$T	&0x000000FFFFFFFFFF;		lo$T = head|tail;     	break;\
		case 0x06:	tail =	hi$  & 0xFFFF000000000000;     	head =	lo$T	&0x0000FFFFFFFFFFFF;		lo$T = head|tail;     	break;\
		case 0x07:	tail =	hi$  & 0xFF00000000000000;     	head =	lo$T	&0x00FFFFFFFFFFFFFF;		lo$T = head|tail; 		

#define SwCASE_XOVER_1T( hi$,	lo$T	)			/* "1T" means	switch case vector 0 starts at one,
																and arg[0] "Tees into" arg[1], which is also the output variable.	*/	\
		case 0x00:	tail =	hi$  & 0xFFFFFFFFFFFFFF00;     	head =	lo$T	&0x00000000000000FF;		lo$T = head|tail;     	break;\
		case 0x01:	tail =	hi$  & 0xFFFFFFFFFFFF0000;     	head =	lo$T	&0x000000000000FFFF;		lo$T = head|tail;     	break;\
		case 0x02:	tail =	hi$  & 0xFFFFFFFFFF000000;     	head =	lo$T	&0x0000000000FFFFFF;		lo$T = head|tail;     	break;\
		case 0x03:	tail =	hi$  & 0xFFFFFFFF00000000;     	head =	lo$T	&0x00000000FFFFFFFF;		lo$T = head|tail;     	break;\
		case 0x04:	tail =	hi$  & 0xFFFFFF0000000000;     	head =	lo$T	&0x000000FFFFFFFFFF;		lo$T = head|tail;     	break;\
		case 0x05:	tail =	hi$  & 0xFFFF000000000000;     	head =	lo$T	&0x0000FFFFFFFFFFFF;		lo$T = head|tail;     	break;\
		case 0x06:	tail =	hi$  & 0xFF00000000000000;     	head =	lo$T	&0x00FFFFFFFFFFFFFF;		lo$T = head|tail;     	break;\
		case 0x07:																								break;\


#define SwCASE_XOVER_0Y( hi$,	lo$, out$Y )		/* "0Y" means	switch case vector 0 starts at zero,
																and args[0..1] "Wye into" arg-2, which is the output variable.	*/	\
		case 0x00:	out$Y = hi$;																					break;\
		case 0x01:	tail =	hi$  & 0xFFFFFFFFFFFFFF00;     	head =	lo$	&0x00000000000000FF;		out$Y = head|tail;     	break;\
		case 0x02:	tail =	hi$  & 0xFFFFFFFFFFFF0000;     	head =	lo$	&0x000000000000FFFF;		out$Y = head|tail;     	break;\
		case 0x03:	tail =	hi$  & 0xFFFFFFFFFF000000;     	head =	lo$	&0x0000000000FFFFFF;		out$Y = head|tail;     	break;\
		case 0x04:	tail =	hi$  & 0xFFFFFFFF00000000;     	head =	lo$	&0x00000000FFFFFFFF;		out$Y = head|tail;     	break;\
		case 0x05:	tail =	hi$  & 0xFFFFFF0000000000;     	head =	lo$	&0x000000FFFFFFFFFF;		out$Y = head|tail;     	break;\
		case 0x06:	tail =	hi$  & 0xFFFF000000000000;     	head =	lo$	&0x0000FFFFFFFFFFFF;		out$Y = head|tail;     	break;\
		case 0x07:	tail =	hi$  & 0xFF00000000000000;     	head =	lo$	&0x00FFFFFFFFFFFFFF;		out$Y = head|tail;  		break;\
		case 0x08:																			out$Y = lo$;

#define SwCASE_XOVER_1Y( hi$,	lo$, out$Y )		/* "1Y" means	switch case vector 0 starts at one,
																and args[0..1] "Wye into" arg[2], which is the output variable.	*/	\
		case 0x00:	tail =	hi$  & 0xFFFFFFFFFFFFFF00;     	head =	lo$	&0x00000000000000FF;		out$Y = head|tail;     	break;\
		case 0x01:	tail =	hi$  & 0xFFFFFFFFFFFF0000;     	head =	lo$	&0x000000000000FFFF;		out$Y = head|tail;     	break;\
		case 0x02:	tail =	hi$  & 0xFFFFFFFFFF000000;     	head =	lo$	&0x0000000000FFFFFF;		out$Y = head|tail;     	break;\
		case 0x03:	tail =	hi$  & 0xFFFFFFFF00000000;     	head =	lo$	&0x00000000FFFFFFFF;		out$Y = head|tail;     	break;\
		case 0x04:	tail =	hi$  & 0xFFFFFF0000000000;     	head =	lo$	&0x000000FFFFFFFFFF;		out$Y = head|tail;     	break;\
		case 0x05:	tail =	hi$  & 0xFFFF000000000000;     	head =	lo$	&0x0000FFFFFFFFFFFF;		out$Y = head|tail;     	break;\
		case 0x06:	tail =	hi$  & 0xFF00000000000000;     	head =	lo$	&0x00FFFFFFFFFFFFFF;		out$Y = head|tail;     	break;\
		case 0x07:										out$Y=	lo$;											




#define SwCASE_LPXOVER_00T( endo$,	lo$ )		/* "00T" means	switch case vector 0 starts at zero,
															switch case vector 1 starts at zero as well,
															and arg[0] "Tees into" arg[1], which is also the output variable.	*/	\
/* 0x0 */	case 0x00:										lo$ =			0x0000000000000000;															break;\
/* 0x1 */	case 0x01:																			lo$ &=		0x00000000000000FF;							break;\
/* 0x2 */	case 0x02:																			lo$ &=		0x000000000000FFFF;							break;\
/* 0x3 */	case 0x03:																			lo$ &=		0x0000000000FFFFFF;							break;\
/* 0x4 */	case 0x04:																			lo$ &=		0x00000000FFFFFFFF;							break;\
/* 0x5 */	case 0x05:																			lo$ &=		0x000000FFFFFFFFFF;							break;\
/* 0x6 */	case 0x06:																			lo$ &=		0x0000FFFFFFFFFFFF;							break;\
/* 0x7 */	case 0x07:																			lo$ &=		0x00FFFFFFFFFFFFFF;							break;\
\
/* 1x0 */	case 0x08:										lo$ =	endo$ &	0x00000000000000FF;															break;\
/* 1x1 */	case 0x09:										body =	endo$ &	0x000000000000FF00;	head = lo$ &	0x00000000000000FF;		lo$ =head|	body;	break;\
/* 1x2 */	case 0x0A:										body =	endo$ &	0x0000000000FF0000;	head = lo$ &	0x000000000000FFFF;		lo$ =head|	body;	break;\
/* 1x3 */	case 0x0B:										body =	endo$ &	0x00000000FF000000;	head = lo$ &	0x0000000000FFFFFF;		lo$ =head|	body;	break;\
/* 1x4 */	case 0x0C:										body =	endo$ &	0x000000FF00000000;	head = lo$ &	0x00000000FFFFFFFF;		lo$ =head|	body;	break;\
/* 1x5 */	case 0x0D:										body =	endo$ &	0x0000FF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		lo$ =head|	body;	break;\
/* 1x6 */	case 0x0E:										body =	endo$ &	0x00FF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 1x7 */	case 0x0F:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		lo$ =head|	body;	break;\
\
/* 2x0 */	case 0x10:										lo$ =	endo$ &	0x000000000000FFFF;															break;\
/* 2x1 */	case 0x11:										body =	endo$ &	0x0000000000FFFF00;	head = lo$ &	0x00000000000000FF;		lo$ =head|	body;	break;\
/* 2x2 */	case 0x12:										body =	endo$ &	0x00000000FFFF0000;	head = lo$ &	0x000000000000FFFF;		lo$ =head|	body;	break;\
/* 2x3 */	case 0x13:										body =	endo$ &	0x000000FFFF000000;	head = lo$ &	0x0000000000FFFFFF;		lo$ =head|	body;	break;\
/* 2x4 */	case 0x14:										body =	endo$ &	0x0000FFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		lo$ =head|	body;	break;\
/* 2x5 */	case 0x15:										body =	endo$ &	0x00FFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		lo$ =head|	body;	break;\
/* 2x6 */	case 0x16:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 2x7 */	case 0x17:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		lo$ =head|	body;	break;\
\
/* 3x0 */	case 0x18:										lo$ =	endo$ &	0x0000000000FFFFFF;															break;\
/* 3x1 */	case 0x19:										body =	endo$ &	0x00000000FFFFFF00;	head = lo$ &	0x00000000000000FF;		lo$ =head|	body;	break;\
/* 3x2 */	case 0x1A:										body =	endo$ &	0x000000FFFFFF0000;	head = lo$ &	0x000000000000FFFF;		lo$ =head|	body;	break;\
/* 3x3 */	case 0x1B:										body =	endo$ &	0x0000FFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		lo$ =head|	body;	break;\
/* 3x4 */	case 0x1C:										body =	endo$ &	0x00FFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		lo$ =head|	body;	break;\
/* 3x5 */	case 0x1D:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		lo$ =head|	body;	break;\
/* 3x6 */	case 0x1E:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 3x7 */	case 0x1F:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		lo$ =head|	body;	break;\
\
/* 4x0 */	case 0x20:										lo$ =	endo$ &	0x00000000FFFFFFFF;															break;\
/* 4x1 */	case 0x21:										body =	endo$ &	0x000000FFFFFFFF00;	head = lo$ &	0x00000000000000FF;		lo$ =head|	body;	break;\
/* 4x2 */	case 0x22:										body =	endo$ &	0x0000FFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		lo$ =head|	body;	break;\
/* 4x3 */	case 0x23:										body =	endo$ &	0x00FFFFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		lo$ =head|	body;	break;\
/* 4x4 */	case 0x24:										body =	endo$ &	0xFFFFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		lo$ =head|	body;	break;\
/* 4x5 */	case 0x25:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		lo$ =head|	body;	break;\
/* 4x6 */	case 0x26:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 4x7 */	case 0x27:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		lo$ =head|	body;	break;\
\
/* 5x0 */	case 0x28:										lo$ =	endo$ &	0x000000FFFFFFFFFF;															break;\
/* 5x1 */	case 0x29:										body =	endo$ &	0x0000FFFFFFFFFF00;	head = lo$ &	0x00000000000000FF;		lo$ =head|	body;	break;\
/* 5x2 */	case 0x2A:										body =	endo$ &	0x00FFFFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		lo$ =head|	body;	break;\
/* 5x3 */	case 0x2B:										body =	endo$ &	0xFFFFFFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		lo$ =head|	body;	break;\
/* 5x4 */	case 0x2C:										body =	endo$ &	0xFFFFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		lo$ =head|	body;	break;\
/* 5x5 */	case 0x2D:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		lo$ =head|	body;	break;\
/* 5x6 */	case 0x2E:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 5x7 */	case 0x2F:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		lo$ =head|	body;	break;\
\
/* 6x0 */	case 0x30:										lo$ =	endo$ &	0x0000FFFFFFFFFFFF;															break;\
/* 6x1 */	case 0x31:										body =	endo$ &	0x00FFFFFFFFFFFF00;	head = lo$ &	0x00000000000000FF;		lo$ =head|	body;	break;\
/* 6x2 */	case 0x32:										body =	endo$ &	0xFFFFFFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		lo$ =head|	body;	break;\
/* 6x3 */	case 0x33:										body =	endo$ &	0xFFFFFFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		lo$ =head|	body;	break;\
/* 6x4 */	case 0x34:										body =	endo$ &	0xFFFFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		lo$ =head|	body;	break;\
/* 6x5 */	case 0x35:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		lo$ =head|	body;	break;\
/* 6x6 */	case 0x36:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 6x7 */	case 0x37:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		lo$ =head|	body;	break;\
\
/* 7x0 */	case 0x38:										lo$ =	endo$ &	0x00FFFFFFFFFFFFFF;															break;\
/* 7x1 */	case 0x39:										body =	endo$ &	0xFFFFFFFFFFFFFF00;	head = lo$ &	0x00000000000000FF;		lo$ =head|	body;	break;\
/* 7x2 */	case 0x3A:										body =	endo$ &	0xFFFFFFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		lo$ =head|	body;	break;\
/* 7x3 */	case 0x3B:										body =	endo$ &	0xFFFFFFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		lo$ =head|	body;	break;\
/* 7x4 */	case 0x3C:										body =	endo$ &	0xFFFFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		lo$ =head|	body;	break;\
/* 7x5 */	case 0x3D:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		lo$ =head|	body;	break;\
/* 7x6 */	case 0x3E:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 7x7 */	case 0x3F:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		lo$ =head|	body;	
/*					^ there is no tail						^ isolate high octets					^ isolate low octets						^ rejoin				*/

#define SwCASE_LPXOVER_01T( endo$,	lo$ )		/* "01T" means	switch case vector 0 starts at zero,
																switch case vector 1 starts at one,
																and arg[0] "Tees into" arg[1], which is also the output variable.	*/	\
/* 0x0 */	case 0x00:										lo$ =	endo$ &	0x00000000000000FF;															break;\
/* 0x1 */	case 0x01:										body =	endo$ &	0x000000000000FF00;	head = lo$ &	0x00000000000000FF;		lo$ =head|	body;	break;\
/* 0x2 */	case 0x02:										body =	endo$ &	0x0000000000FF0000;	head = lo$ &	0x000000000000FFFF;		lo$ =head|	body;	break;\
/* 0x3 */	case 0x03:										body =	endo$ &	0x00000000FF000000;	head = lo$ &	0x0000000000FFFFFF;		lo$ =head|	body;	break;\
/* 0x4 */	case 0x04:										body =	endo$ &	0x000000FF00000000;	head = lo$ &	0x00000000FFFFFFFF;		lo$ =head|	body;	break;\
/* 0x5 */	case 0x05:										body =	endo$ &	0x0000FF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		lo$ =head|	body;	break;\
/* 0x6 */	case 0x06:										body =	endo$ &	0x00FF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 0x7 */	case 0x07:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		lo$ =head|	body;	break;\
\
/* 1x0 */	case 0x08:										lo$ =	endo$ &	0x000000000000FFFF;															break;\
/* 1x1 */	case 0x09:										body =	endo$ &	0x0000000000FFFF00;	head = lo$ &	0x00000000000000FF;		lo$ =head|	body;	break;\
/* 1x2 */	case 0x0A:										body =	endo$ &	0x00000000FFFF0000;	head = lo$ &	0x000000000000FFFF;		lo$ =head|	body;	break;\
/* 1x3 */	case 0x0B:										body =	endo$ &	0x000000FFFF000000;	head = lo$ &	0x0000000000FFFFFF;		lo$ =head|	body;	break;\
/* 1x4 */	case 0x0C:										body =	endo$ &	0x0000FFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		lo$ =head|	body;	break;\
/* 1x5 */	case 0x0D:										body =	endo$ &	0x00FFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		lo$ =head|	body;	break;\
/* 1x6 */	case 0x0E:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 1x7 */	case 0x0F:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		lo$ =head|	body;	break;\
\
/* 2x0 */	case 0x10:										lo$ =	endo$ &	0x0000000000FFFFFF;															break;\
/* 2x1 */	case 0x11:										body =	endo$ &	0x00000000FFFFFF00;	head = lo$ &	0x00000000000000FF;		lo$ =head|	body;	break;\
/* 2x2 */	case 0x12:										body =	endo$ &	0x000000FFFFFF0000;	head = lo$ &	0x000000000000FFFF;		lo$ =head|	body;	break;\
/* 2x3 */	case 0x13:										body =	endo$ &	0x0000FFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		lo$ =head|	body;	break;\
/* 2x4 */	case 0x14:										body =	endo$ &	0x00FFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		lo$ =head|	body;	break;\
/* 2x5 */	case 0x15:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		lo$ =head|	body;	break;\
/* 2x6 */	case 0x16:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 2x7 */	case 0x17:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		lo$ =head|	body;	break;\
\
/* 3x0 */	case 0x18:										lo$ =	endo$ &	0x00000000FFFFFFFF;															break;\
/* 3x1 */	case 0x19:										body =	endo$ &	0x000000FFFFFFFF00;	head = lo$ &	0x00000000000000FF;		lo$ =head|	body;	break;\
/* 3x2 */	case 0x1A:										body =	endo$ &	0x0000FFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		lo$ =head|	body;	break;\
/* 3x3 */	case 0x1B:										body =	endo$ &	0x00FFFFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		lo$ =head|	body;	break;\
/* 3x4 */	case 0x1C:										body =	endo$ &	0xFFFFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		lo$ =head|	body;	break;\
/* 3x5 */	case 0x1D:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		lo$ =head|	body;	break;\
/* 3x6 */	case 0x1E:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 3x7 */	case 0x1F:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		lo$ =head|	body;	break;\
\
/* 4x0 */	case 0x20:										lo$ =	endo$ &	0x000000FFFFFFFFFF;															break;\
/* 4x1 */	case 0x21:										body =	endo$ &	0x0000FFFFFFFFFF00;	head = lo$ &	0x00000000000000FF;		lo$ =head|	body;	break;\
/* 4x2 */	case 0x22:										body =	endo$ &	0x00FFFFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		lo$ =head|	body;	break;\
/* 4x3 */	case 0x23:										body =	endo$ &	0xFFFFFFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		lo$ =head|	body;	break;\
/* 4x4 */	case 0x24:										body =	endo$ &	0xFFFFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		lo$ =head|	body;	break;\
/* 4x5 */	case 0x25:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		lo$ =head|	body;	break;\
/* 4x6 */	case 0x26:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 4x7 */	case 0x27:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		lo$ =head|	body;	break;\
\
/* 5x0 */	case 0x28:										lo$ =	endo$ &	0x0000FFFFFFFFFFFF;															break;\
/* 5x1 */	case 0x29:										body =	endo$ &	0x00FFFFFFFFFFFF00;	head = lo$ &	0x00000000000000FF;		lo$ =head|	body;	break;\
/* 5x2 */	case 0x2A:										body =	endo$ &	0xFFFFFFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		lo$ =head|	body;	break;\
/* 5x3 */	case 0x2B:										body =	endo$ &	0xFFFFFFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		lo$ =head|	body;	break;\
/* 5x4 */	case 0x2C:										body =	endo$ &	0xFFFFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		lo$ =head|	body;	break;\
/* 5x5 */	case 0x2D:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		lo$ =head|	body;	break;\
/* 5x6 */	case 0x2E:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 5x7 */	case 0x2F:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		lo$ =head|	body;	break;\
\
/* 6x0 */	case 0x30:										lo$ =	endo$ &	0x00FFFFFFFFFFFFFF;															break;\
/* 6x1 */	case 0x31:										body =	endo$ &	0xFFFFFFFFFFFFFF00;	head = lo$ &	0x00000000000000FF;		lo$ =head|	body;	break;\
/* 6x2 */	case 0x32:										body =	endo$ &	0xFFFFFFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		lo$ =head|	body;	break;\
/* 6x3 */	case 0x33:										body =	endo$ &	0xFFFFFFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		lo$ =head|	body;	break;\
/* 6x4 */	case 0x34:										body =	endo$ &	0xFFFFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		lo$ =head|	body;	break;\
/* 6x5 */	case 0x35:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		lo$ =head|	body;	break;\
/* 6x6 */	case 0x36:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 6x7 */	case 0x37:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		lo$ =head|	body;	break;\
\
/* 7x0 */	case 0x38:										lo$ = endo$;																					break;\
/* 7x1 */	case 0x39:										body =	endo$ &	0xFFFFFFFFFFFFFF00;	head = lo$ &	0x00000000000000FF;		lo$ =head|	body;	break;\
/* 7x2 */	case 0x3A:										body =	endo$ &	0xFFFFFFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		lo$ =head|	body;	break;\
/* 7x3 */	case 0x3B:										body =	endo$ &	0xFFFFFFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		lo$ =head|	body;	break;\
/* 7x4 */	case 0x3C:										body =	endo$ &	0xFFFFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		lo$ =head|	body;	break;\
/* 7x5 */	case 0x3D:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		lo$ =head|	body;	break;\
/* 7x6 */	case 0x3E:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 7x7 */	case 0x3F:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		lo$ =head|	body;		
/*					^ there is no tail						^ isolate high octets					^ isolate low octets						^ rejoin				*/


#define SwCASE_LPXOVER_10T( endo$,	lo$ )		/* "10T" means	switch case vector 0 starts at one,
																switch case vector 1 starts at zero,
																and arg[0] "Tees into" arg[1], which is also the output variable.	*/	\
\
/* 0x0 */	case 0x00:																			lo$ &=		0x00000000000000FF;							break;\
/* 0x1 */	case 0x01:																			lo$ &=		0x000000000000FFFF;							break;\
/* 0x2 */	case 0x02:																			lo$ &=		0x0000000000FFFFFF;							break;\
/* 0x3 */	case 0x03:																			lo$ &=		0x00000000FFFFFFFF;							break;\
/* 0x4 */	case 0x04:																			lo$ &=		0x000000FFFFFFFFFF;							break;\
/* 0x5 */	case 0x05:																			lo$ &=		0x0000FFFFFFFFFFFF;							break;\
/* 0x6 */	case 0x06:																			lo$ &=		0x00FFFFFFFFFFFFFF;							break;\
/* 0x7 */	case 0x07:										/*				0x0000000000000000				0xFFFFFFFFFFFFFFFF			*/					break;\
\
/* 1x0 */	case 0x08:										body =	endo$ &	0x000000000000FF00;	head = lo$ &	0x00000000000000FF;		lo$ =head|	body;	break;\
/* 1x1 */	case 0x09:										body =	endo$ &	0x0000000000FF0000;	head = lo$ &	0x000000000000FFFF;		lo$ =head|	body;	break;\
/* 1x2 */	case 0x0A:										body =	endo$ &	0x00000000FF000000;	head = lo$ &	0x0000000000FFFFFF;		lo$ =head|	body;	break;\
/* 1x3 */	case 0x0B:										body =	endo$ &	0x000000FF00000000;	head = lo$ &	0x00000000FFFFFFFF;		lo$ =head|	body;	break;\
/* 1x4 */	case 0x0C:										body =	endo$ &	0x0000FF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		lo$ =head|	body;	break;\
/* 1x5 */	case 0x0D:										body =	endo$ &	0x00FF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 1x6 */	case 0x0E:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 1x7 */	case 0x0F:										/*				0x0000000000000000				0xFFFFFFFFFFFFFFFF			*/					break;\
\
/* 2x0 */	case 0x10:										body =	endo$ &	0x0000000000FFFF00;	head = lo$ &	0x00000000000000FF;		lo$ =head|	body;	break;\
/* 2x1 */	case 0x11:										body =	endo$ &	0x00000000FFFF0000;	head = lo$ &	0x000000000000FFFF;		lo$ =head|	body;	break;\
/* 2x2 */	case 0x12:										body =	endo$ &	0x000000FFFF000000;	head = lo$ &	0x0000000000FFFFFF;		lo$ =head|	body;	break;\
/* 2x3 */	case 0x13:										body =	endo$ &	0x0000FFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		lo$ =head|	body;	break;\
/* 2x4 */	case 0x14:										body =	endo$ &	0x00FFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		lo$ =head|	body;	break;\
/* 2x5 */	case 0x15:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 2x6 */	case 0x16:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 2x7 */	case 0x17:										/*				0x0000000000000000				0xFFFFFFFFFFFFFFFF			*/					break;\
\
/* 3x0 */	case 0x18:										body =	endo$ &	0x00000000FFFFFF00;	head = lo$ &	0x00000000000000FF;		lo$ =head|	body;	break;\
/* 3x1 */	case 0x19:										body =	endo$ &	0x000000FFFFFF0000;	head = lo$ &	0x000000000000FFFF;		lo$ =head|	body;	break;\
/* 3x2 */	case 0x1A:										body =	endo$ &	0x0000FFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		lo$ =head|	body;	break;\
/* 3x3 */	case 0x1B:										body =	endo$ &	0x00FFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		lo$ =head|	body;	break;\
/* 3x4 */	case 0x1C:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		lo$ =head|	body;	break;\
/* 3x5 */	case 0x1D:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 3x6 */	case 0x1E:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 3x7 */	case 0x1F:										/*				0x0000000000000000				0xFFFFFFFFFFFFFFFF			*/					break;\
\
/* 4x0 */	case 0x20:										body =	endo$ &	0x000000FFFFFFFF00;	head = lo$ &	0x00000000000000FF;		lo$ =head|	body;	break;\
/* 4x1 */	case 0x21:										body =	endo$ &	0x0000FFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		lo$ =head|	body;	break;\
/* 4x2 */	case 0x22:										body =	endo$ &	0x00FFFFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		lo$ =head|	body;	break;\
/* 4x3 */	case 0x23:										body =	endo$ &	0xFFFFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		lo$ =head|	body;	break;\
/* 4x4 */	case 0x24:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		lo$ =head|	body;	break;\
/* 4x5 */	case 0x25:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 4x6 */	case 0x26:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 4x7 */	case 0x27:										/*				0x0000000000000000				0xFFFFFFFFFFFFFFFF			*/					break;\
\
/* 5x0 */	case 0x28:										body =	endo$ &	0x0000FFFFFFFFFF00;	head = lo$ &	0x00000000000000FF;		lo$ =head|	body;	break;\
/* 5x1 */	case 0x29:										body =	endo$ &	0x00FFFFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		lo$ =head|	body;	break;\
/* 5x2 */	case 0x2A:										body =	endo$ &	0xFFFFFFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		lo$ =head|	body;	break;\
/* 5x3 */	case 0x2B:										body =	endo$ &	0xFFFFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		lo$ =head|	body;	break;\
/* 5x4 */	case 0x2C:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		lo$ =head|	body;	break;\
/* 5x5 */	case 0x2D:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 5x6 */	case 0x2E:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 5x7 */	case 0x2F:										/*				0x0000000000000000				0xFFFFFFFFFFFFFFFF			*/					break;\
\
/* 6x0 */	case 0x30:										body =	endo$ &	0x00FFFFFFFFFFFF00;	head = lo$ &	0x00000000000000FF;		lo$ =head|	body;	break;\
/* 6x1 */	case 0x31:										body =	endo$ &	0xFFFFFFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		lo$ =head|	body;	break;\
/* 6x2 */	case 0x32:										body =	endo$ &	0xFFFFFFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		lo$ =head|	body;	break;\
/* 6x3 */	case 0x33:										body =	endo$ &	0xFFFFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		lo$ =head|	body;	break;\
/* 6x4 */	case 0x34:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		lo$ =head|	body;	break;\
/* 6x5 */	case 0x35:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 6x6 */	case 0x36:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 6x7 */	case 0x37:										/*				0x0000000000000000				0xFFFFFFFFFFFFFFFF			*/					break;\
\
/* 7x0 */	case 0x38:										body =	endo$ &	0xFFFFFFFFFFFFFF00;	head = lo$ &	0x00000000000000FF;		lo$ =head|	body;	break;\
/* 7x1 */	case 0x39:										body =	endo$ &	0xFFFFFFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		lo$ =head|	body;	break;\
/* 7x2 */	case 0x3A:										body =	endo$ &	0xFFFFFFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		lo$ =head|	body;	break;\
/* 7x3 */	case 0x3B:										body =	endo$ &	0xFFFFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		lo$ =head|	body;	break;\
/* 7x4 */	case 0x3C:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		lo$ =head|	body;	break;\
/* 7x5 */	case 0x3D:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 7x6 */	case 0x3E:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		lo$ =head|	body;	break;\
/* 7x7 */	case 0x3F:										/*				0x0000000000000000				0xFFFFFFFFFFFFFFFF			*/					
/*					^ there is no tail						^ isolate high octets					^ isolate low octets						^ rejoin				*/

#define SwCASE_LPXOVER_01Y( endo$, lo$, out$Y )		/* "01Y" means	switch case vector 0 starts at zero,
																switch case vector 1 starts at one,
																and args[0..1] "Wye into" arg-2, which is the output variable.	*/	\
/* 0x0 */	case 0x00:										out$Y =	endo$ &	0x00000000000000FF;															break;\
/* 0x1 */	case 0x01:										body =	endo$ &	0x000000000000FF00;	head = lo$ &	0x00000000000000FF;		out$Y =head|	body;	break;\
/* 0x2 */	case 0x02:										body =	endo$ &	0x0000000000FF0000;	head = lo$ &	0x000000000000FFFF;		out$Y =head|	body;	break;\
/* 0x3 */	case 0x03:										body =	endo$ &	0x00000000FF000000;	head = lo$ &	0x0000000000FFFFFF;		out$Y =head|	body;	break;\
/* 0x4 */	case 0x04:										body =	endo$ &	0x000000FF00000000;	head = lo$ &	0x00000000FFFFFFFF;		out$Y =head|	body;	break;\
/* 0x5 */	case 0x05:										body =	endo$ &	0x0000FF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		out$Y =head|	body;	break;\
/* 0x6 */	case 0x06:										body =	endo$ &	0x00FF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 0x7 */	case 0x07:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		out$Y =head|	body;	break;\
\
/* 1x0 */	case 0x08:										out$Y =	endo$ &	0x000000000000FFFF;															break;\
/* 1x1 */	case 0x09:										body =	endo$ &	0x0000000000FFFF00;	head = lo$ &	0x00000000000000FF;		out$Y =head|	body;	break;\
/* 1x2 */	case 0x0A:										body =	endo$ &	0x00000000FFFF0000;	head = lo$ &	0x000000000000FFFF;		out$Y =head|	body;	break;\
/* 1x3 */	case 0x0B:										body =	endo$ &	0x000000FFFF000000;	head = lo$ &	0x0000000000FFFFFF;		out$Y =head|	body;	break;\
/* 1x4 */	case 0x0C:										body =	endo$ &	0x0000FFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		out$Y =head|	body;	break;\
/* 1x5 */	case 0x0D:										body =	endo$ &	0x00FFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		out$Y =head|	body;	break;\
/* 1x6 */	case 0x0E:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 1x7 */	case 0x0F:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		out$Y =head|	body;	break;\
\
/* 2x0 */	case 0x10:										out$Y =	endo$ &	0x0000000000FFFFFF;															break;\
/* 2x1 */	case 0x11:										body =	endo$ &	0x00000000FFFFFF00;	head = lo$ &	0x00000000000000FF;		out$Y =head|	body;	break;\
/* 2x2 */	case 0x12:										body =	endo$ &	0x000000FFFFFF0000;	head = lo$ &	0x000000000000FFFF;		out$Y =head|	body;	break;\
/* 2x3 */	case 0x13:										body =	endo$ &	0x0000FFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		out$Y =head|	body;	break;\
/* 2x4 */	case 0x14:										body =	endo$ &	0x00FFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		out$Y =head|	body;	break;\
/* 2x5 */	case 0x15:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		out$Y =head|	body;	break;\
/* 2x6 */	case 0x16:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 2x7 */	case 0x17:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		out$Y =head|	body;	break;\
\
/* 3x0 */	case 0x18:										out$Y =	endo$ &	0x00000000FFFFFFFF;															break;\
/* 3x1 */	case 0x19:										body =	endo$ &	0x000000FFFFFFFF00;	head = lo$ &	0x00000000000000FF;		out$Y =head|	body;	break;\
/* 3x2 */	case 0x1A:										body =	endo$ &	0x0000FFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		out$Y =head|	body;	break;\
/* 3x3 */	case 0x1B:										body =	endo$ &	0x00FFFFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		out$Y =head|	body;	break;\
/* 3x4 */	case 0x1C:										body =	endo$ &	0xFFFFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		out$Y =head|	body;	break;\
/* 3x5 */	case 0x1D:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		out$Y =head|	body;	break;\
/* 3x6 */	case 0x1E:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 3x7 */	case 0x1F:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		out$Y =head|	body;	break;\
\
/* 4x0 */	case 0x20:										out$Y =	endo$ &	0x000000FFFFFFFFFF;															break;\
/* 4x1 */	case 0x21:										body =	endo$ &	0x0000FFFFFFFFFF00;	head = lo$ &	0x00000000000000FF;		out$Y =head|	body;	break;\
/* 4x2 */	case 0x22:										body =	endo$ &	0x00FFFFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		out$Y =head|	body;	break;\
/* 4x3 */	case 0x23:										body =	endo$ &	0xFFFFFFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		out$Y =head|	body;	break;\
/* 4x4 */	case 0x24:										body =	endo$ &	0xFFFFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		out$Y =head|	body;	break;\
/* 4x5 */	case 0x25:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		out$Y =head|	body;	break;\
/* 4x6 */	case 0x26:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 4x7 */	case 0x27:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		out$Y =head|	body;	break;\
\
/* 5x0 */	case 0x28:										out$Y =	endo$ &	0x0000FFFFFFFFFFFF;															break;\
/* 5x1 */	case 0x29:										body =	endo$ &	0x00FFFFFFFFFFFF00;	head = lo$ &	0x00000000000000FF;		out$Y =head|	body;	break;\
/* 5x2 */	case 0x2A:										body =	endo$ &	0xFFFFFFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		out$Y =head|	body;	break;\
/* 5x3 */	case 0x2B:										body =	endo$ &	0xFFFFFFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		out$Y =head|	body;	break;\
/* 5x4 */	case 0x2C:										body =	endo$ &	0xFFFFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		out$Y =head|	body;	break;\
/* 5x5 */	case 0x2D:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		out$Y =head|	body;	break;\
/* 5x6 */	case 0x2E:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 5x7 */	case 0x2F:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		out$Y =head|	body;	break;\
\
/* 6x0 */	case 0x30:										out$Y =	endo$ &	0x00FFFFFFFFFFFFFF;															break;\
/* 6x1 */	case 0x31:										body =	endo$ &	0xFFFFFFFFFFFFFF00;	head = lo$ &	0x00000000000000FF;		out$Y =head|	body;	break;\
/* 6x2 */	case 0x32:										body =	endo$ &	0xFFFFFFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		out$Y =head|	body;	break;\
/* 6x3 */	case 0x33:										body =	endo$ &	0xFFFFFFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		out$Y =head|	body;	break;\
/* 6x4 */	case 0x34:										body =	endo$ &	0xFFFFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		out$Y =head|	body;	break;\
/* 6x5 */	case 0x35:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		out$Y =head|	body;	break;\
/* 6x6 */	case 0x36:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 6x7 */	case 0x37:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		out$Y =head|	body;	break;\
\
/* 7x0 */	case 0x38:										out$Y = endo$;																					break;\
/* 7x1 */	case 0x39:										body =	endo$ &	0xFFFFFFFFFFFFFF00;	head = lo$ &	0x00000000000000FF;		out$Y =head|	body;	break;\
/* 7x2 */	case 0x3A:										body =	endo$ &	0xFFFFFFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		out$Y =head|	body;	break;\
/* 7x3 */	case 0x3B:										body =	endo$ &	0xFFFFFFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		out$Y =head|	body;	break;\
/* 7x4 */	case 0x3C:										body =	endo$ &	0xFFFFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		out$Y =head|	body;	break;\
/* 7x5 */	case 0x3D:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		out$Y =head|	body;	break;\
/* 7x6 */	case 0x3E:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 7x7 */	case 0x3F:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		out$Y =head|	body;		
/*					^ there is no tail						^ isolate high octets					^ isolate low octets						^ rejoin				*/


#define SwCASE_LPXOVER_10Y( endo$, lo$, out$Y )		/* "10Y" means	switch case vector 0 starts at one,
																switch case vector 1 starts at zero,
																and args[0..1] "Wye into" arg-2, which is the output variable.	*/	\
\
/* 0x0 */	case 0x00:																			out$Y = lo$ &	0x00000000000000FF;							break;\
/* 0x1 */	case 0x01:																			out$Y = lo$ &	0x000000000000FFFF;							break;\
/* 0x2 */	case 0x02:																			out$Y = lo$ &	0x0000000000FFFFFF;							break;\
/* 0x3 */	case 0x03:																			out$Y = lo$ &	0x00000000FFFFFFFF;							break;\
/* 0x4 */	case 0x04:																			out$Y = lo$ &	0x000000FFFFFFFFFF;							break;\
/* 0x5 */	case 0x05:																			out$Y = lo$ &	0x0000FFFFFFFFFFFF;							break;\
/* 0x6 */	case 0x06:																			out$Y = lo$ &	0x00FFFFFFFFFFFFFF;							break;\
/* 0x7 */	case 0x07:																			out$Y = lo$;												break;\
\
/* 1x0 */	case 0x08:										body =	endo$ &	0x000000000000FF00;	head = lo$ &	0x00000000000000FF;		out$Y =head|	body;	break;\
/* 1x1 */	case 0x09:										body =	endo$ &	0x0000000000FF0000;	head = lo$ &	0x000000000000FFFF;		out$Y =head|	body;	break;\
/* 1x2 */	case 0x0A:										body =	endo$ &	0x00000000FF000000;	head = lo$ &	0x0000000000FFFFFF;		out$Y =head|	body;	break;\
/* 1x3 */	case 0x0B:										body =	endo$ &	0x000000FF00000000;	head = lo$ &	0x00000000FFFFFFFF;		out$Y =head|	body;	break;\
/* 1x4 */	case 0x0C:										body =	endo$ &	0x0000FF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		out$Y =head|	body;	break;\
/* 1x5 */	case 0x0D:										body =	endo$ &	0x00FF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 1x6 */	case 0x0E:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 1x7 */	case 0x0F:																			out$Y = lo$;												break;\
\
/* 2x0 */	case 0x10:										body =	endo$ &	0x0000000000FFFF00;	head = lo$ &	0x00000000000000FF;		out$Y =head|	body;	break;\
/* 2x1 */	case 0x11:										body =	endo$ &	0x00000000FFFF0000;	head = lo$ &	0x000000000000FFFF;		out$Y =head|	body;	break;\
/* 2x2 */	case 0x12:										body =	endo$ &	0x000000FFFF000000;	head = lo$ &	0x0000000000FFFFFF;		out$Y =head|	body;	break;\
/* 2x3 */	case 0x13:										body =	endo$ &	0x0000FFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		out$Y =head|	body;	break;\
/* 2x4 */	case 0x14:										body =	endo$ &	0x00FFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		out$Y =head|	body;	break;\
/* 2x5 */	case 0x15:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 2x6 */	case 0x16:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 2x7 */	case 0x17:																			out$Y = lo$;												break;\
\
/* 3x0 */	case 0x18:										body =	endo$ &	0x00000000FFFFFF00;	head = lo$ &	0x00000000000000FF;		out$Y =head|	body;	break;\
/* 3x1 */	case 0x19:										body =	endo$ &	0x000000FFFFFF0000;	head = lo$ &	0x000000000000FFFF;		out$Y =head|	body;	break;\
/* 3x2 */	case 0x1A:										body =	endo$ &	0x0000FFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		out$Y =head|	body;	break;\
/* 3x3 */	case 0x1B:										body =	endo$ &	0x00FFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		out$Y =head|	body;	break;\
/* 3x4 */	case 0x1C:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		out$Y =head|	body;	break;\
/* 3x5 */	case 0x1D:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 3x6 */	case 0x1E:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 3x7 */	case 0x1F:																			out$Y = lo$;												break;\
\
/* 4x0 */	case 0x20:										body =	endo$ &	0x000000FFFFFFFF00;	head = lo$ &	0x00000000000000FF;		out$Y =head|	body;	break;\
/* 4x1 */	case 0x21:										body =	endo$ &	0x0000FFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		out$Y =head|	body;	break;\
/* 4x2 */	case 0x22:										body =	endo$ &	0x00FFFFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		out$Y =head|	body;	break;\
/* 4x3 */	case 0x23:										body =	endo$ &	0xFFFFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		out$Y =head|	body;	break;\
/* 4x4 */	case 0x24:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		out$Y =head|	body;	break;\
/* 4x5 */	case 0x25:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 4x6 */	case 0x26:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 4x7 */	case 0x27:																			out$Y = lo$;												break;\
\
/* 5x0 */	case 0x28:										body =	endo$ &	0x0000FFFFFFFFFF00;	head = lo$ &	0x00000000000000FF;		out$Y =head|	body;	break;\
/* 5x1 */	case 0x29:										body =	endo$ &	0x00FFFFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		out$Y =head|	body;	break;\
/* 5x2 */	case 0x2A:										body =	endo$ &	0xFFFFFFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		out$Y =head|	body;	break;\
/* 5x3 */	case 0x2B:										body =	endo$ &	0xFFFFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		out$Y =head|	body;	break;\
/* 5x4 */	case 0x2C:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		out$Y =head|	body;	break;\
/* 5x5 */	case 0x2D:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 5x6 */	case 0x2E:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 5x7 */	case 0x2F:																			out$Y = lo$;												break;\
\
/* 6x0 */	case 0x30:										body =	endo$ &	0x00FFFFFFFFFFFF00;	head = lo$ &	0x00000000000000FF;		out$Y =head|	body;	break;\
/* 6x1 */	case 0x31:										body =	endo$ &	0xFFFFFFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		out$Y =head|	body;	break;\
/* 6x2 */	case 0x32:										body =	endo$ &	0xFFFFFFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		out$Y =head|	body;	break;\
/* 6x3 */	case 0x33:										body =	endo$ &	0xFFFFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		out$Y =head|	body;	break;\
/* 6x4 */	case 0x34:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		out$Y =head|	body;	break;\
/* 6x5 */	case 0x35:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 6x6 */	case 0x36:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 6x7 */	case 0x37:																			out$Y = lo$;												break;\
\
/* 7x0 */	case 0x38:										body =	endo$ &	0xFFFFFFFFFFFFFF00;	head = lo$ &	0x00000000000000FF;		out$Y =head|	body;	break;\
/* 7x1 */	case 0x39:										body =	endo$ &	0xFFFFFFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		out$Y =head|	body;	break;\
/* 7x2 */	case 0x3A:										body =	endo$ &	0xFFFFFFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		out$Y =head|	body;	break;\
/* 7x3 */	case 0x3B:										body =	endo$ &	0xFFFFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		out$Y =head|	body;	break;\
/* 7x4 */	case 0x3C:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		out$Y =head|	body;	break;\
/* 7x5 */	case 0x3D:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 7x6 */	case 0x3E:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 7x7 */	case 0x3F:																			out$Y = lo$;												
/*					^ there is no tail						^ isolate high octets					^ isolate low octets						^ rejoin				*/



#define SwCASE_LPXOVER_10Yabs( endo$, lo$, out$Y )	/* "10Yabs" means	switch case vector 0 starts at one,
																	switch case vector 1 starts at zero minus vector 0,
																	and args[0..1] "Wye into" arg-2, which is the output variable.	*/	\
\
/* 0x0 */	case 0x00:	\
/* 0x1 */	case 0x01:	\
/* 0x2 */	case 0x02:	\
/* 0x3 */	case 0x03:	\
/* 0x4 */	case 0x04:	\
/* 0x5 */	case 0x05:	\
/* 0x6 */	case 0x06:	\
/* 0x7 */	case 0x07:																			out$Y = lo$ &	0x00000000000000FF;							break;\
\
/* 1x0 */	case 0x08:										body =	endo$ &	0x000000000000FF00;	head = lo$ &	0x00000000000000FF;		out$Y =head|	body;	break;\
/* 1x1 */	case 0x09:	\
/* 1x2 */	case 0x0A:	\
/* 1x3 */	case 0x0B:	\
/* 1x4 */	case 0x0C:	\
/* 1x5 */	case 0x0D:	\
/* 1x6 */	case 0x0E:	\
/* 1x7 */	case 0x0F:																			out$Y =lo$ &	0x000000000000FFFF;							break;\
\
/* 2x0 */	case 0x10:										body =	endo$ &	0x0000000000FFFF00;	head = lo$ &	0x00000000000000FF;		out$Y =head|	body;	break;\
/* 2x1 */	case 0x11:										body =	endo$ &	0x0000000000FF0000;	head = lo$ &	0x000000000000FFFF;		out$Y =head|	body;	break;\
/* 2x2 */	case 0x12:	\
/* 2x3 */	case 0x13:	\
/* 2x4 */	case 0x14:	\
/* 2x5 */	case 0x15:	\
/* 2x6 */	case 0x16:	\
/* 2x7 */	case 0x17:																			out$Y = lo$ &	0x0000000000FFFFFF;							break;\
\
/* 3x0 */	case 0x18:										body =	endo$ &	0x00000000FFFFFF00;	head = lo$ &	0x00000000000000FF;		out$Y =head|	body;	break;\
/* 3x1 */	case 0x19:										body =	endo$ &	0x00000000FFFF0000;	head = lo$ &	0x000000000000FFFF;		out$Y =head|	body;	break;\
/* 3x2 */	case 0x1A:										body =	endo$ &	0x00000000FF000000;	head = lo$ &	0x0000000000FFFFFF;		out$Y =head|	body;	break;\
/* 3x3 */	case 0x1B:	\
/* 3x4 */	case 0x1C:	\
/* 3x5 */	case 0x1D:	\
/* 3x6 */	case 0x1E:	\
/* 3x7 */	case 0x1F:																			out$Y = lo$ &	0x00000000FFFFFFFF;							break;\
\
/* 4x0 */	case 0x20:										body =	endo$ &	0x000000FFFFFFFF00;	head = lo$ &	0x00000000000000FF;		out$Y =head|	body;	break;\
/* 4x1 */	case 0x21:										body =	endo$ &	0x000000FFFFFF0000;	head = lo$ &	0x000000000000FFFF;		out$Y =head|	body;	break;\
/* 4x2 */	case 0x22:										body =	endo$ &	0x000000FFFF000000;	head = lo$ &	0x0000000000FFFFFF;		out$Y =head|	body;	break;\
/* 4x3 */	case 0x23:										body =	endo$ &	0x000000FF00000000;	head = lo$ &	0x00000000FFFFFFFF;		out$Y =head|	body;	break;\
/* 4x4 */	case 0x24:	\
/* 4x5 */	case 0x25:	\
/* 4x6 */	case 0x26:	\
/* 4x7 */	case 0x27:																			out$Y = lo$ &	0x000000FFFFFFFFFF;							break;\
\
/* 5x0 */	case 0x28:										body =	endo$ &	0x0000FFFFFFFFFF00;	head = lo$ &	0x00000000000000FF;		out$Y =head|	body;	break;\
/* 5x1 */	case 0x29:										body =	endo$ &	0x0000FFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		out$Y =head|	body;	break;\
/* 5x2 */	case 0x2A:										body =	endo$ &	0x0000FFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		out$Y =head|	body;	break;\
/* 5x3 */	case 0x2B:										body =	endo$ &	0x0000FFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		out$Y =head|	body;	break;\
/* 5x4 */	case 0x2C:										body =	endo$ &	0x0000FF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		out$Y =head|	body;	break;\
/* 5x5 */	case 0x2D:	\
/* 5x6 */	case 0x2E:	\
/* 5x7 */	case 0x2F:																			out$Y = lo$ &	0x0000FFFFFFFFFFFF;							break;\
\
/* 6x0 */	case 0x30:										body =	endo$ &	0x00FFFFFFFFFFFF00;	head = lo$ &	0x00000000000000FF;		out$Y =head|	body;	break;\
/* 6x1 */	case 0x31:										body =	endo$ &	0x00FFFFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		out$Y =head|	body;	break;\
/* 6x2 */	case 0x32:										body =	endo$ &	0x00FFFFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		out$Y =head|	body;	break;\
/* 6x3 */	case 0x33:										body =	endo$ &	0x00FFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		out$Y =head|	body;	break;\
/* 6x4 */	case 0x34:										body =	endo$ &	0x00FFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		out$Y =head|	body;	break;\
/* 6x5 */	case 0x35:										body =	endo$ &	0x00FF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 6x6 */	case 0x36:	\
/* 6x7 */	case 0x37:																			out$Y = lo$ &	0x00FFFFFFFFFFFFFF;							break;\
\
/* 7x0 */	case 0x38:										body =	endo$ &	0xFFFFFFFFFFFFFF00;	head = lo$ &	0x00000000000000FF;		out$Y =head|	body;	break;\
/* 7x1 */	case 0x39:										body =	endo$ &	0xFFFFFFFFFFFF0000;	head = lo$ &	0x000000000000FFFF;		out$Y =head|	body;	break;\
/* 7x2 */	case 0x3A:										body =	endo$ &	0xFFFFFFFFFF000000;	head = lo$ &	0x0000000000FFFFFF;		out$Y =head|	body;	break;\
/* 7x3 */	case 0x3B:										body =	endo$ &	0xFFFFFFFF00000000;	head = lo$ &	0x00000000FFFFFFFF;		out$Y =head|	body;	break;\
/* 7x4 */	case 0x3C:										body =	endo$ &	0xFFFFFF0000000000;	head = lo$ &	0x000000FFFFFFFFFF;		out$Y =head|	body;	break;\
/* 7x5 */	case 0x3D:										body =	endo$ &	0xFFFF000000000000;	head = lo$ &	0x0000FFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 7x6 */	case 0x3E:										body =	endo$ &	0xFF00000000000000;	head = lo$ &	0x00FFFFFFFFFFFFFF;		out$Y =head|	body;	break;\
/* 7x7 */	case 0x3F:																			out$Y = lo$;							
/*					^ there is no tail						^ isolate high octets					^ isolate low octets						^ rejoin				*/



#define SwCASE_XXOVER_01T( endo$,	lo$ )				/* "01T" means	switch case vector 0 starts at zero,
																switch case vector 1 starts at one,
																and arg[0] "Tees into" arg[1], which is also the output variable.	*/	\
/* 0x0 */	case 0x00:	body =	endo$ & 0x00000000000000FF;    	tail =	lo$  & 0xFFFFFFFFFFFFFF00;      	lo$ =  body|tail;	break;\
/* 0x1 */	case 0x01:	body =	endo$ & 0x000000000000FF00;    	tail =	lo$  & 0xFFFFFFFFFFFF00FF;      	lo$ =  body|tail;	break;\
/* 0x2 */	case 0x02:	body =	endo$ & 0x0000000000FF0000;    	tail =	lo$  & 0xFFFFFFFFFF00FFFF;      	lo$ =  body|tail;	break;\
/* 0x3 */	case 0x03:	body =	endo$ & 0x00000000FF000000;    	tail =	lo$  & 0xFFFFFFFF00FFFFFF;      	lo$ =  body|tail;	break;\
/* 0x4 */	case 0x04:	body =	endo$ & 0x000000FF00000000;    	tail =	lo$  & 0xFFFFFF00FFFFFFFF;      	lo$ =  body|tail;	break;\
/* 0x5 */	case 0x05:	body =	endo$ & 0x0000FF0000000000;    	tail =	lo$  & 0xFFFF00FFFFFFFFFF;      	lo$ =  body|tail;	break;\
/* 0x6 */	case 0x06:	body =	endo$ & 0x00FF000000000000;    	tail =	lo$  & 0xFF00FFFFFFFFFFFF;      	lo$ =  body|tail;	break;\
/* 0x7 */	case 0x07:	body =	endo$ & 0xFF00000000000000;    	tail =	lo$  & 0x00FFFFFFFFFFFFFF;      	lo$ =  body|tail;	break;\
\
/* 1x0 */	case 0x08:	body =	endo$ & 0x000000000000FFFF;    	tail =	lo$  & 0xFFFFFFFFFFFF0000;      	lo$ =  body|tail;	break;\
/* 1x1 */	case 0x09:	body =	endo$ & 0x0000000000FFFF00;    	tail =	lo$  & 0xFFFFFFFFFF0000FF;      	lo$ =  body|tail;	break;\
/* 1x2 */	case 0x0A:	body =	endo$ & 0x00000000FFFF0000;    	tail =	lo$  & 0xFFFFFFFF0000FFFF;      	lo$ =  body|tail;	break;\
/* 1x3 */	case 0x0B:	body =	endo$ & 0x000000FFFF000000;    	tail =	lo$  & 0xFFFFFF0000FFFFFF;      	lo$ =  body|tail;	break;\
/* 1x4 */	case 0x0C:	body =	endo$ & 0x0000FFFF00000000;    	tail =	lo$  & 0xFFFF0000FFFFFFFF;      	lo$ =  body|tail;	break;\
/* 1x5 */	case 0x0D:	body =	endo$ & 0x00FFFF0000000000;    	tail =	lo$  & 0xFF0000FFFFFFFFFF;      	lo$ =  body|tail;	break;\
/* 1x6 */	case 0x0E:	body =	endo$ & 0xFFFF000000000000;    	tail =	lo$  & 0x0000FFFFFFFFFFFF;      	lo$ =  body|tail;	break;\
/* 1x7 */	case 0x0F:	body =	endo$ & 0xFF00000000000000;    	tail =	lo$  & 0x00FFFFFFFFFFFFFF;      	lo$ =  body|tail;	break;\
\
/* 2x0 */	case 0x10:	body =	endo$ & 0x0000000000FFFFFF;    	tail =	lo$  & 0xFFFFFFFFFF000000;      	lo$ =  body|tail;	break;\
/* 2x1 */	case 0x11:	body =	endo$ & 0x00000000FFFFFF00;    	tail =	lo$  & 0xFFFFFFFF000000FF;      	lo$ =  body|tail;	break;\
/* 2x2 */	case 0x12:	body =	endo$ & 0x000000FFFFFF0000;    	tail =	lo$  & 0xFFFFFF000000FFFF;      	lo$ =  body|tail;	break;\
/* 2x3 */	case 0x13:	body =	endo$ & 0x0000FFFFFF000000;    	tail =	lo$  & 0xFFFF000000FFFFFF;      	lo$ =  body|tail;	break;\
/* 2x4 */	case 0x14:	body =	endo$ & 0x00FFFFFF00000000;    	tail =	lo$  & 0xFF000000FFFFFFFF;      	lo$ =  body|tail;	break;\
/* 2x5 */	case 0x15:	body =	endo$ & 0xFFFFFF0000000000;    	tail =	lo$  & 0x000000FFFFFFFFFF;      	lo$ =  body|tail;	break;\
/* 2x6 */	case 0x16:	body =	endo$ & 0xFFFF000000000000;    	tail =	lo$  & 0x0000FFFFFFFFFFFF;      	lo$ =  body|tail;	break;\
/* 2x7 */	case 0x17:	body =	endo$ & 0xFF00000000000000;    	tail =	lo$  & 0x00FFFFFFFFFFFFFF;      	lo$ =  body|tail;	break;\
\
/* 3x0 */	case 0x18:	body =	endo$ & 0x00000000FFFFFFFF;    	tail =	lo$  & 0xFFFFFFFF00000000;      	lo$ =  body|tail;	break;\
/* 3x1 */	case 0x19:	body =	endo$ & 0x000000FFFFFFFF00;    	tail =	lo$  & 0xFFFFFF00000000FF;      	lo$ =  body|tail;	break;\
/* 3x2 */	case 0x1A:	body =	endo$ & 0x0000FFFFFFFF0000;    	tail =	lo$  & 0xFFFF00000000FFFF;      	lo$ =  body|tail;	break;\
/* 3x3 */	case 0x1B:	body =	endo$ & 0x00FFFFFFFF000000;    	tail =	lo$  & 0xFF00000000FFFFFF;      	lo$ =  body|tail;	break;\
/* 3x4 */	case 0x1C:	body =	endo$ & 0xFFFFFFFF00000000;    	tail =	lo$  & 0x00000000FFFFFFFF;      	lo$ =  body|tail;	break;\
/* 3x5 */	case 0x1D:	body =	endo$ & 0xFFFFFF0000000000;    	tail =	lo$  & 0x000000FFFFFFFFFF;      	lo$ =  body|tail;	break;\
/* 3x6 */	case 0x1E:	body =	endo$ & 0xFFFF000000000000;    	tail =	lo$  & 0x0000FFFFFFFFFFFF;      	lo$ =  body|tail;	break;\
/* 3x7 */	case 0x1F:	body =	endo$ & 0xFF00000000000000;    	tail =	lo$  & 0x00FFFFFFFFFFFFFF;      	lo$ =  body|tail;	break;\
\
/* 4x0 */	case 0x20:	body =	endo$ & 0x000000FFFFFFFFFF;    	tail =	lo$  & 0xFFFFFF0000000000;      	lo$ =  body|tail;	break;\
/* 4x1 */	case 0x21:	body =	endo$ & 0x0000FFFFFFFFFF00;    	tail =	lo$  & 0xFFFF0000000000FF;      	lo$ =  body|tail;	break;\
/* 4x2 */	case 0x22:	body =	endo$ & 0x00FFFFFFFFFF0000;    	tail =	lo$  & 0xFF0000000000FFFF;      	lo$ =  body|tail;	break;\
/* 4x3 */	case 0x23:	body =	endo$ & 0xFFFFFFFFFF000000;    	tail =	lo$  & 0x0000000000FFFFFF;      	lo$ =  body|tail;	break;\
/* 4x4 */	case 0x24:	body =	endo$ & 0xFFFFFFFF00000000;    	tail =	lo$  & 0x00000000FFFFFFFF;      	lo$ =  body|tail;	break;\
/* 4x5 */	case 0x25:	body =	endo$ & 0xFFFFFF0000000000;    	tail =	lo$  & 0x000000FFFFFFFFFF;      	lo$ =  body|tail;	break;\
/* 4x6 */	case 0x26:	body =	endo$ & 0xFFFF000000000000;    	tail =	lo$  & 0x0000FFFFFFFFFFFF;      	lo$ =  body|tail;	break;\
/* 4x7 */	case 0x27:	body =	endo$ & 0xFF00000000000000;    	tail =	lo$  & 0x00FFFFFFFFFFFFFF;      	lo$ =  body|tail;	break;\
\
/* 5x0 */	case 0x28:	body =	endo$ & 0x0000FFFFFFFFFFFF;    	tail =	lo$  & 0xFFFF000000000000;      	lo$ =  body|tail;	break;\
/* 5x1 */	case 0x29:	body =	endo$ & 0x00FFFFFFFFFFFF00;    	tail =	lo$  & 0xFF000000000000FF;      	lo$ =  body|tail;	break;\
/* 5x2 */	case 0x2A:	body =	endo$ & 0xFFFFFFFFFFFF0000;    	tail =	lo$  & 0x000000000000FFFF;      	lo$ =  body|tail;	break;\
/* 5x3 */	case 0x2B:	body =	endo$ & 0xFFFFFFFFFF000000;    	tail =	lo$  & 0x0000000000FFFFFF;      	lo$ =  body|tail;	break;\
/* 5x4 */	case 0x2C:	body =	endo$ & 0xFFFFFFFF00000000;    	tail =	lo$  & 0x00000000FFFFFFFF;      	lo$ =  body|tail;	break;\
/* 5x5 */	case 0x2D:	body =	endo$ & 0xFFFFFF0000000000;    	tail =	lo$  & 0x000000FFFFFFFFFF;      	lo$ =  body|tail;	break;\
/* 5x6 */	case 0x2E:	body =	endo$ & 0xFFFF000000000000;    	tail =	lo$  & 0x0000FFFFFFFFFFFF;      	lo$ =  body|tail;	break;\
/* 5x7 */	case 0x2F:	body =	endo$ & 0xFF00000000000000;    	tail =	lo$  & 0x00FFFFFFFFFFFFFF;      	lo$ =  body|tail;	break;\
\
/* 6x0 */	case 0x30:	body =	endo$ & 0x00FFFFFFFFFFFFFF;    	tail =	lo$  & 0xFF00000000000000;      	lo$ =  body|tail;	break;\
/* 6x1 */	case 0x31:	body =	endo$ & 0xFFFFFFFFFFFFFF00;    	tail =	lo$  & 0x00000000000000FF;      	lo$ =  body|tail;	break;\
/* 6x2 */	case 0x32:	body =	endo$ & 0xFFFFFFFFFFFF0000;    	tail =	lo$  & 0x000000000000FFFF;      	lo$ =  body|tail;	break;\
/* 6x3 */	case 0x33:	body =	endo$ & 0xFFFFFFFFFF000000;    	tail =	lo$  & 0x0000000000FFFFFF;      	lo$ =  body|tail;	break;\
/* 6x4 */	case 0x34:	body =	endo$ & 0xFFFFFFFF00000000;    	tail =	lo$  & 0x00000000FFFFFFFF;      	lo$ =  body|tail;	break;\
/* 6x5 */	case 0x35:	body =	endo$ & 0xFFFFFF0000000000;    	tail =	lo$  & 0x000000FFFFFFFFFF;      	lo$ =  body|tail;	break;\
/* 6x6 */	case 0x36:	body =	endo$ & 0xFFFF000000000000;    	tail =	lo$  & 0x0000FFFFFFFFFFFF;      	lo$ =  body|tail;	break;\
/* 6x7 */	case 0x37:	body =	endo$ & 0xFF00000000000000;    	tail =	lo$  & 0x00FFFFFFFFFFFFFF;      	lo$ =  body|tail;	break;\
\
/* 7x0 */	case 0x38:	lo$	=	endo$;																							break;\
/* 7x1 */	case 0x39:	body =	endo$ & 0xFFFFFFFFFFFFFF00;    	tail =	lo$  & 0x00000000000000FF;      	lo$ =  body|tail;	break;\
/* 7x2 */	case 0x3A:	body =	endo$ & 0xFFFFFFFFFFFF0000;    	tail =	lo$  & 0x000000000000FFFF;      	lo$ =  body|tail;	break;\
/* 7x3 */	case 0x3B:	body =	endo$ & 0xFFFFFFFFFF000000;    	tail =	lo$  & 0x0000000000FFFFFF;      	lo$ =  body|tail;	break;\
/* 7x4 */	case 0x3C:	body =	endo$ & 0xFFFFFFFF00000000;    	tail =	lo$  & 0x00000000FFFFFFFF;      	lo$ =  body|tail;	break;\
/* 7x5 */	case 0x3D:	body =	endo$ & 0xFFFFFF0000000000;    	tail =	lo$  & 0x000000FFFFFFFFFF;      	lo$ =  body|tail;	break;\
/* 7x6 */	case 0x3E:	body =	endo$ & 0xFFFF000000000000;    	tail =	lo$  & 0x0000FFFFFFFFFFFF;      	lo$ =  body|tail;	break;\
/* 7x7 */	case 0x3F:	body =	endo$ & 0xFF00000000000000;    	tail =	lo$  & 0x00FFFFFFFFFFFFFF;      	lo$ =  body|tail;			
/*					^ isolate external octets					^	isolate internal octets				^ rejoin		*/


#define SwCASE_XXOVER_01Y( endo$, exo$, out$Y )		/* "01Y" means	switch case vector 0 starts at zero,
																switch case vector 1 starts at one,
																and args[0..1] "Wye into" arg-2, which is the output variable.	*/	\
/* 0x0 */	case 0x00:	tail =	exo$ & 0xFFFFFFFFFFFFFF00;     	body =	endo$  & 0x00000000000000FF;  	out$Y = body|tail;     	break;\
/* 0x1 */	case 0x01:	tail =	exo$ & 0xFFFFFFFFFFFF00FF;     	body =	endo$  & 0x000000000000FF00;  	out$Y = body|tail;     	break;\
/* 0x2 */	case 0x02:	tail =	exo$ & 0xFFFFFFFFFF00FFFF;     	body =	endo$  & 0x0000000000FF0000;  	out$Y = body|tail;     	break;\
/* 0x3 */	case 0x03:	tail =	exo$ & 0xFFFFFFFF00FFFFFF;     	body =	endo$  & 0x00000000FF000000;  	out$Y = body|tail;     	break;\
/* 0x4 */	case 0x04:	tail =	exo$ & 0xFFFFFF00FFFFFFFF;     	body =	endo$  & 0x000000FF00000000;  	out$Y = body|tail;     	break;\
/* 0x5 */	case 0x05:	tail =	exo$ & 0xFFFF00FFFFFFFFFF;     	body =	endo$  & 0x0000FF0000000000;  	out$Y = body|tail;     	break;\
/* 0x6 */	case 0x06:	tail =	exo$ & 0xFF00FFFFFFFFFFFF;     	body =	endo$  & 0x00FF000000000000;  	out$Y = body|tail;     	break;\
/* 0x7 */	case 0x07:	tail =	exo$ & 0x00FFFFFFFFFFFFFF;     	body =	endo$  & 0xFF00000000000000;  	out$Y = body|tail;     	break;\
\
/* 1x0 */	case 0x08:	tail =	exo$ & 0xFFFFFFFFFFFF0000;     	body =	endo$  & 0x000000000000FFFF;  	out$Y = body|tail;     	break;\
/* 1x1 */	case 0x09:	tail =	exo$ & 0xFFFFFFFFFF0000FF;     	body =	endo$  & 0x0000000000FFFF00;  	out$Y = body|tail;     	break;\
/* 1x2 */	case 0x0A:	tail =	exo$ & 0xFFFFFFFF0000FFFF;     	body =	endo$  & 0x00000000FFFF0000;  	out$Y = body|tail;     	break;\
/* 1x3 */	case 0x0B:	tail =	exo$ & 0xFFFFFF0000FFFFFF;     	body =	endo$  & 0x000000FFFF000000;  	out$Y = body|tail;     	break;\
/* 1x4 */	case 0x0C:	tail =	exo$ & 0xFFFF0000FFFFFFFF;     	body =	endo$  & 0x0000FFFF00000000;  	out$Y = body|tail;     	break;\
/* 1x5 */	case 0x0D:	tail =	exo$ & 0xFF0000FFFFFFFFFF;     	body =	endo$  & 0x00FFFF0000000000;  	out$Y = body|tail;     	break;\
/* 1x6 */	case 0x0E:	tail =	exo$ & 0x0000FFFFFFFFFFFF;     	body =	endo$  & 0xFFFF000000000000;  	out$Y = body|tail;     	break;\
/* 1x7 */	case 0x0F:	tail =	exo$ & 0x00FFFFFFFFFFFFFF;     	body =	endo$  & 0xFF00000000000000;  	out$Y = body|tail;     	break;\
\
/* 2x0 */	case 0x10:	tail =	exo$ & 0xFFFFFFFFFF000000;     	body =	endo$  & 0x0000000000FFFFFF;  	out$Y = body|tail;     	break;\
/* 2x1 */	case 0x11:	tail =	exo$ & 0xFFFFFFFF000000FF;     	body =	endo$  & 0x00000000FFFFFF00;  	out$Y = body|tail;     	break;\
/* 2x2 */	case 0x12:	tail =	exo$ & 0xFFFFFF000000FFFF;     	body =	endo$  & 0x000000FFFFFF0000;  	out$Y = body|tail;     	break;\
/* 2x3 */	case 0x13:	tail =	exo$ & 0xFFFF000000FFFFFF;     	body =	endo$  & 0x0000FFFFFF000000;  	out$Y = body|tail;     	break;\
/* 2x4 */	case 0x14:	tail =	exo$ & 0xFF000000FFFFFFFF;     	body =	endo$  & 0x00FFFFFF00000000;  	out$Y = body|tail;     	break;\
/* 2x5 */	case 0x15:	tail =	exo$ & 0x000000FFFFFFFFFF;     	body =	endo$  & 0xFFFFFF0000000000;  	out$Y = body|tail;     	break;\
/* 2x6 */	case 0x16:	tail =	exo$ & 0x0000FFFFFFFFFFFF;     	body =	endo$  & 0xFFFF000000000000;  	out$Y = body|tail;     	break;\
/* 2x7 */	case 0x17:	tail =	exo$ & 0x00FFFFFFFFFFFFFF;     	body =	endo$  & 0xFF00000000000000;  	out$Y = body|tail;     	break;\
\
/* 3x0 */	case 0x18:	tail =	exo$ & 0xFFFFFFFF00000000;     	body =	endo$  & 0x00000000FFFFFFFF;  	out$Y = body|tail;     	break;\
/* 3x1 */	case 0x19:	tail =	exo$ & 0xFFFFFF00000000FF;     	body =	endo$  & 0x000000FFFFFFFF00;  	out$Y = body|tail;     	break;\
/* 3x2 */	case 0x1A:	tail =	exo$ & 0xFFFF00000000FFFF;     	body =	endo$  & 0x0000FFFFFFFF0000;  	out$Y = body|tail;     	break;\
/* 3x3 */	case 0x1B:	tail =	exo$ & 0xFF00000000FFFFFF;     	body =	endo$  & 0x00FFFFFFFF000000;  	out$Y = body|tail;     	break;\
/* 3x4 */	case 0x1C:	tail =	exo$ & 0x00000000FFFFFFFF;     	body =	endo$  & 0xFFFFFFFF00000000;  	out$Y = body|tail;     	break;\
/* 3x5 */	case 0x1D:	tail =	exo$ & 0x000000FFFFFFFFFF;     	body =	endo$  & 0xFFFFFF0000000000;  	out$Y = body|tail;     	break;\
/* 3x6 */	case 0x1E:	tail =	exo$ & 0x0000FFFFFFFFFFFF;     	body =	endo$  & 0xFFFF000000000000;  	out$Y = body|tail;     	break;\
/* 3x7 */	case 0x1F:	tail =	exo$ & 0x00FFFFFFFFFFFFFF;     	body =	endo$  & 0xFF00000000000000;  	out$Y = body|tail;     	break;\
\
/* 4x0 */	case 0x20:	tail =	exo$ & 0xFFFFFF0000000000;     	body =	endo$  & 0x000000FFFFFFFFFF;  	out$Y = body|tail;     	break;\
/* 4x1 */	case 0x21:	tail =	exo$ & 0xFFFF0000000000FF;     	body =	endo$  & 0x0000FFFFFFFFFF00;  	out$Y = body|tail;     	break;\
/* 4x2 */	case 0x22:	tail =	exo$ & 0xFF0000000000FFFF;     	body =	endo$  & 0x00FFFFFFFFFF0000;  	out$Y = body|tail;     	break;\
/* 4x3 */	case 0x23:	tail =	exo$ & 0x0000000000FFFFFF;     	body =	endo$  & 0xFFFFFFFFFF000000;  	out$Y = body|tail;     	break;\
/* 4x4 */	case 0x24:	tail =	exo$ & 0x00000000FFFFFFFF;     	body =	endo$  & 0xFFFFFFFF00000000;  	out$Y = body|tail;     	break;\
/* 4x5 */	case 0x25:	tail =	exo$ & 0x000000FFFFFFFFFF;     	body =	endo$  & 0xFFFFFF0000000000;  	out$Y = body|tail;     	break;\
/* 4x6 */	case 0x26:	tail =	exo$ & 0x0000FFFFFFFFFFFF;     	body =	endo$  & 0xFFFF000000000000;  	out$Y = body|tail;     	break;\
/* 4x7 */	case 0x27:	tail =	exo$ & 0x00FFFFFFFFFFFFFF;     	body =	endo$  & 0xFF00000000000000;  	out$Y = body|tail;     	break;\
\
/* 5x0 */	case 0x28:	tail =	exo$ & 0xFFFF000000000000;     	body =	endo$  & 0x0000FFFFFFFFFFFF;  	out$Y = body|tail;     	break;\
/* 5x1 */	case 0x29:	tail =	exo$ & 0xFF000000000000FF;     	body =	endo$  & 0x00FFFFFFFFFFFF00;  	out$Y = body|tail;     	break;\
/* 5x2 */	case 0x2A:	tail =	exo$ & 0x000000000000FFFF;     	body =	endo$  & 0xFFFFFFFFFFFF0000;  	out$Y = body|tail;     	break;\
/* 5x3 */	case 0x2B:	tail =	exo$ & 0x0000000000FFFFFF;     	body =	endo$  & 0xFFFFFFFFFF000000;  	out$Y = body|tail;     	break;\
/* 5x4 */	case 0x2C:	tail =	exo$ & 0x00000000FFFFFFFF;     	body =	endo$  & 0xFFFFFFFF00000000;  	out$Y = body|tail;     	break;\
/* 5x5 */	case 0x2D:	tail =	exo$ & 0x000000FFFFFFFFFF;     	body =	endo$  & 0xFFFFFF0000000000;  	out$Y = body|tail;     	break;\
/* 5x6 */	case 0x2E:	tail =	exo$ & 0x0000FFFFFFFFFFFF;     	body =	endo$  & 0xFFFF000000000000;  	out$Y = body|tail;     	break;\
/* 5x7 */	case 0x2F:	tail =	exo$ & 0x00FFFFFFFFFFFFFF;     	body =	endo$  & 0xFF00000000000000;  	out$Y = body|tail;     	break;\
\
/* 6x0 */	case 0x30:	tail =	exo$ & 0xFF00000000000000;     	body =	endo$  & 0x00FFFFFFFFFFFFFF;  	out$Y = body|tail;     	break;\
/* 6x1 */	case 0x31:	tail =	exo$ & 0x00000000000000FF;     	body =	endo$  & 0xFFFFFFFFFFFFFF00;  	out$Y = body|tail;     	break;\
/* 6x2 */	case 0x32:	tail =	exo$ & 0x000000000000FFFF;     	body =	endo$  & 0xFFFFFFFFFFFF0000;  	out$Y = body|tail;     	break;\
/* 6x3 */	case 0x33:	tail =	exo$ & 0x0000000000FFFFFF;     	body =	endo$  & 0xFFFFFFFFFF000000;  	out$Y = body|tail;     	break;\
/* 6x4 */	case 0x34:	tail =	exo$ & 0x00000000FFFFFFFF;     	body =	endo$  & 0xFFFFFFFF00000000;  	out$Y = body|tail;     	break;\
/* 6x5 */	case 0x35:	tail =	exo$ & 0x000000FFFFFFFFFF;     	body =	endo$  & 0xFFFFFF0000000000;  	out$Y = body|tail;     	break;\
/* 6x6 */	case 0x36:	tail =	exo$ & 0x0000FFFFFFFFFFFF;     	body =	endo$  & 0xFFFF000000000000;  	out$Y = body|tail;     	break;\
/* 6x7 */	case 0x37:	tail =	exo$ & 0x00FFFFFFFFFFFFFF;     	body =	endo$  & 0xFF00000000000000;  	out$Y = body|tail;     	break;\
\
/* 7x0 */	case 0x38:																			out$Y = endo$;		break;\
/* 7x1 */	case 0x39:	tail =	exo$ & 0x00000000000000FF;     	body =	endo$  & 0xFFFFFFFFFFFFFF00;  	out$Y = body|tail;     	break;\
/* 7x2 */	case 0x3A:	tail =	exo$ & 0x000000000000FFFF;     	body =	endo$  & 0xFFFFFFFFFFFF0000;  	out$Y = body|tail;     	break;\
/* 7x3 */	case 0x3B:	tail =	exo$ & 0x0000000000FFFFFF;     	body =	endo$  & 0xFFFFFFFFFF000000;  	out$Y = body|tail;     	break;\
/* 7x4 */	case 0x3C:	tail =	exo$ & 0x00000000FFFFFFFF;     	body =	endo$  & 0xFFFFFFFF00000000;  	out$Y = body|tail;     	break;\
/* 7x5 */	case 0x3D:	tail =	exo$ & 0x000000FFFFFFFFFF;     	body =	endo$  & 0xFFFFFF0000000000;  	out$Y = body|tail;     	break;\
/* 7x6 */	case 0x3E:	tail =	exo$ & 0x0000FFFFFFFFFFFF;     	body =	endo$  & 0xFFFF000000000000;  	out$Y = body|tail;     	break;\
/* 7x7 */	case 0x3F:	tail =	exo$ & 0x00FFFFFFFFFFFFFF;     	body =	endo$  & 0xFF00000000000000;  	out$Y = body|tail;     		
/*					^ isolate external octets					^ isolate internal octets					^ rejoin				*/


#define SwCASE_XXOVER_01K( hi$, endo$, out$K )		/* "01K" means	switch case vector 0 starts at zero,
																switch case vector 1 starts at one,
																and args[0..2] "double-tee" into arg-2, which is also the output variable.	*/	\
/* 0x0 */	case 0x00:	tail =	hi$  & 0xFFFFFFFFFFFFFF00;		body = endo$ & 0x00000000000000FF;										out$K =		body|	tail; 	break;\
/* 0x1 */	case 0x01:	tail =	hi$  & 0xFFFFFFFFFFFF0000;		body = endo$ & 0x000000000000FF00;	head = out$K & 0x00000000000000FF;		out$K =head|	body|	tail;	break;\
/* 0x2 */	case 0x02:	tail =	hi$  & 0xFFFFFFFFFF000000;		body = endo$ & 0x0000000000FF0000;	head = out$K & 0x000000000000FFFF;		out$K =head|	body|	tail;	break;\
/* 0x3 */	case 0x03:	tail =	hi$  & 0xFFFFFFFF00000000;		body = endo$ & 0x00000000FF000000;	head = out$K & 0x0000000000FFFFFF;		out$K =head|	body|	tail;	break;\
/* 0x4 */	case 0x04:	tail =	hi$  & 0xFFFFFF0000000000;		body = endo$ & 0x000000FF00000000;	head = out$K & 0x00000000FFFFFFFF;		out$K =head|	body|	tail;	break;\
/* 0x5 */	case 0x05:	tail =	hi$  & 0xFFFF000000000000;		body = endo$ & 0x0000FF0000000000;	head = out$K & 0x000000FFFFFFFFFF;		out$K =head|	body|	tail;	break;\
/* 0x6 */	case 0x06:	tail =	hi$  & 0xFF00000000000000;		body = endo$ & 0x00FF000000000000;	head = out$K & 0x0000FFFFFFFFFFFF;		out$K =head|	body|	tail;	break;\
/* 0x7 */	case 0x07:										body = endo$ & 0xFF00000000000000;	head = out$K & 0x00FFFFFFFFFFFFFF;		out$K =head|	body;		break;\
\
/* 1x0 */	case 0x08:	tail =	hi$  & 0xFFFFFFFFFFFF0000;		body = endo$ & 0x000000000000FFFF;										out$K =		body|	tail;	break;\
/* 1x1 */	case 0x09:	tail =	hi$  & 0xFFFFFFFFFF000000;		body = endo$ & 0x0000000000FFFF00;	head = out$K & 0x00000000000000FF;		out$K =head|	body|	tail;	break;\
/* 1x2 */	case 0x0A:	tail =	hi$  & 0xFFFFFFFF00000000;		body = endo$ & 0x00000000FFFF0000;	head = out$K & 0x000000000000FFFF;		out$K =head|	body|	tail;	break;\
/* 1x3 */	case 0x0B:	tail =	hi$  & 0xFFFFFF0000000000;		body = endo$ & 0x000000FFFF000000;	head = out$K & 0x0000000000FFFFFF;		out$K =head|	body|	tail;	break;\
/* 1x4 */	case 0x0C:	tail =	hi$  & 0xFFFF000000000000;		body = endo$ & 0x0000FFFF00000000;	head = out$K & 0x00000000FFFFFFFF;		out$K =head|	body|	tail;	break;\
/* 1x5 */	case 0x0D:	tail =	hi$  & 0xFF00000000000000;		body = endo$ & 0x00FFFF0000000000;	head = out$K & 0x000000FFFFFFFFFF;		out$K =head|	body|	tail;	break;\
/* 1x6 */	case 0x0E:										body = endo$ & 0xFFFF000000000000;	head = out$K & 0x0000FFFFFFFFFFFF;		out$K =head|	body;		break;\
/* 1x7 */	case 0x0F:										body = endo$ & 0xFF00000000000000;	head = out$K & 0x00FFFFFFFFFFFFFF;		out$K =head|	body;		break;\
\
/* 2x0 */	case 0x10:	tail =	hi$  & 0xFFFFFFFFFF000000;		body = endo$ & 0x0000000000FFFFFF;										out$K =		body|	tail; 	break;\
/* 2x1 */	case 0x11:	tail =	hi$  & 0xFFFFFFFF00000000;		body = endo$ & 0x00000000FFFFFF00;	head = out$K & 0x00000000000000FF;		out$K =head|	body|	tail;	break;\
/* 2x2 */	case 0x12:	tail =	hi$  & 0xFFFFFF0000000000;		body = endo$ & 0x000000FFFFFF0000;	head = out$K & 0x000000000000FFFF;		out$K =head|	body|	tail;	break;\
/* 2x3 */	case 0x13:	tail =	hi$  & 0xFFFF000000000000;		body = endo$ & 0x0000FFFFFF000000;	head = out$K & 0x0000000000FFFFFF;		out$K =head|	body|	tail;	break;\
/* 2x4 */	case 0x14:	tail =	hi$  & 0xFF00000000000000;		body = endo$ & 0x00FFFFFF00000000;	head = out$K & 0x00000000FFFFFFFF;		out$K =head|	body|	tail;	break;\
/* 2x5 */	case 0x15:										body = endo$ & 0xFFFFFF0000000000;	head = out$K & 0x000000FFFFFFFFFF;		out$K =head|	body;		break;\
/* 2x6 */	case 0x16:										body = endo$ & 0xFFFF000000000000;	head = out$K & 0x0000FFFFFFFFFFFF;		out$K =head|	body;		break;\
/* 2x7 */	case 0x17:										body = endo$ & 0xFF00000000000000;	head = out$K & 0x00FFFFFFFFFFFFFF;		out$K =head|	body;		break;\
\
/* 3x0 */	case 0x18:	tail =	hi$  & 0xFFFFFFFF00000000;		body = endo$ & 0x00000000FFFFFFFF;										out$K =		body|	tail; 	break;\
/* 3x1 */	case 0x19:	tail =	hi$  & 0xFFFFFF0000000000;		body = endo$ & 0x000000FFFFFFFF00;	head = out$K & 0x00000000000000FF;		out$K =head|	body|	tail;	break;\
/* 3x2 */	case 0x1A:	tail =	hi$  & 0xFFFF000000000000;		body = endo$ & 0x0000FFFFFFFF0000;	head = out$K & 0x000000000000FFFF;		out$K =head|	body|	tail;	break;\
/* 3x3 */	case 0x1B:	tail =	hi$  & 0xFF00000000000000;		body = endo$ & 0x00FFFFFFFF000000;	head = out$K & 0x0000000000FFFFFF;		out$K =head|	body|	tail;	break;\
/* 3x4 */	case 0x1C:										body = endo$ & 0xFFFFFFFF00000000;	head = out$K & 0x00000000FFFFFFFF;		out$K =head|	body;		break;\
/* 3x5 */	case 0x1D:										body = endo$ & 0xFFFFFF0000000000;	head = out$K & 0x000000FFFFFFFFFF;		out$K =head|	body;		break;\
/* 3x6 */	case 0x1E:										body = endo$ & 0xFFFF000000000000;	head = out$K & 0x0000FFFFFFFFFFFF;		out$K =head|	body;		break;\
/* 3x7 */	case 0x1F:										body = endo$ & 0xFF00000000000000;	head = out$K & 0x00FFFFFFFFFFFFFF;		out$K =head|	body;		break;\
\
/* 4x0 */	case 0x20:	tail =	hi$  & 0xFFFFFF0000000000;		body = endo$ & 0x000000FFFFFFFFFF;										out$K =		body|	tail; 	break;\
/* 4x1 */	case 0x21:	tail =	hi$  & 0xFFFF000000000000;		body = endo$ & 0x0000FFFFFFFFFF00;	head = out$K & 0x00000000000000FF;		out$K =head|	body|	tail;	break;\
/* 4x2 */	case 0x22:	tail =	hi$  & 0xFF00000000000000;		body = endo$ & 0x00FFFFFFFFFF0000;	head = out$K & 0x000000000000FFFF;		out$K =head|	body|	tail;	break;\
/* 4x3 */	case 0x23:										body = endo$ & 0xFFFFFFFFFF000000;	head = out$K & 0x0000000000FFFFFF;		out$K =head|	body;		break;\
/* 4x4 */	case 0x24:										body = endo$ & 0xFFFFFFFF00000000;	head = out$K & 0x00000000FFFFFFFF;		out$K =head|	body;		break;\
/* 4x5 */	case 0x25:										body = endo$ & 0xFFFFFF0000000000;	head = out$K & 0x000000FFFFFFFFFF;		out$K =head|	body;		break;\
/* 4x6 */	case 0x26:										body = endo$ & 0xFFFF000000000000;	head = out$K & 0x0000FFFFFFFFFFFF;		out$K =head|	body;		break;\
/* 4x7 */	case 0x27:										body = endo$ & 0xFF00000000000000;	head = out$K & 0x00FFFFFFFFFFFFFF;		out$K =head|	body;		break;\
\
/* 5x0 */	case 0x28:	tail =	hi$  & 0xFFFF000000000000;		body = endo$ & 0x0000FFFFFFFFFFFF;										out$K =		body|	tail; 	break;\
/* 5x1 */	case 0x29:	tail =	hi$  & 0xFF00000000000000;		body = endo$ & 0x00FFFFFFFFFFFF00;	head = out$K & 0x00000000000000FF;		out$K =head|	body|	tail;	break;\
/* 5x2 */	case 0x2A:										body = endo$ & 0xFFFFFFFFFFFF0000;	head = out$K & 0x000000000000FFFF;		out$K =head|	body;		break;\
/* 5x3 */	case 0x2B:										body = endo$ & 0xFFFFFFFFFF000000;	head = out$K & 0x0000000000FFFFFF;		out$K =head|	body;		break;\
/* 5x4 */	case 0x2C:										body = endo$ & 0xFFFFFFFF00000000;	head = out$K & 0x00000000FFFFFFFF;		out$K =head|	body;		break;\
/* 5x5 */	case 0x2D:										body = endo$ & 0xFFFFFF0000000000;	head = out$K & 0x000000FFFFFFFFFF;		out$K =head|	body;		break;\
/* 5x6 */	case 0x2E:										body = endo$ & 0xFFFF000000000000;	head = out$K & 0x0000FFFFFFFFFFFF;		out$K =head|	body;		break;\
/* 5x7 */	case 0x2F:										body = endo$ & 0xFF00000000000000;	head = out$K & 0x00FFFFFFFFFFFFFF;		out$K =head|	body;		break;\
\
/* 6x0 */	case 0x30:	tail =	hi$  & 0xFF00000000000000;		body = endo$ & 0x00FFFFFFFFFFFFFF;										out$K =		body|	tail; 	break;\
/* 6x1 */	case 0x31:										body = endo$ & 0xFFFFFFFFFFFFFF00;	head = out$K & 0x00000000000000FF;		out$K =head|	body;		break;\
/* 6x2 */	case 0x32:										body = endo$ & 0xFFFFFFFFFFFF0000;	head = out$K & 0x000000000000FFFF;		out$K =head|	body;		break;\
/* 6x3 */	case 0x33:										body = endo$ & 0xFFFFFFFFFF000000;	head = out$K & 0x0000000000FFFFFF;		out$K =head|	body;		break;\
/* 6x4 */	case 0x34:										body = endo$ & 0xFFFFFFFF00000000;	head = out$K & 0x00000000FFFFFFFF;		out$K =head|	body;		break;\
/* 6x5 */	case 0x35:										body = endo$ & 0xFFFFFF0000000000;	head = out$K & 0x000000FFFFFFFFFF;		out$K =head|	body;		break;\
/* 6x6 */	case 0x36:										body = endo$ & 0xFFFF000000000000;	head = out$K & 0x0000FFFFFFFFFFFF;		out$K =head|	body;		break;\
/* 6x7 */	case 0x37:										body = endo$ & 0xFF00000000000000;	head = out$K & 0x00FFFFFFFFFFFFFF;		out$K =head|	body;		break;\
\
/* 7x0 */	case 0x38:										out$K = endo$;																				break;\
/* 7x1 */	case 0x39:										body = endo$ & 0xFFFFFFFFFFFFFF00;	head = out$K & 0x00000000000000FF;		out$K =head|	body;		break;\
/* 7x2 */	case 0x3A:										body = endo$ & 0xFFFFFFFFFFFF0000;	head = out$K & 0x000000000000FFFF;		out$K =head|	body;		break;\
/* 7x3 */	case 0x3B:										body = endo$ & 0xFFFFFFFFFF000000;	head = out$K & 0x0000000000FFFFFF;		out$K =head|	body;		break;\
/* 7x4 */	case 0x3C:										body = endo$ & 0xFFFFFFFF00000000;	head = out$K & 0x00000000FFFFFFFF;		out$K =head|	body;		break;\
/* 7x5 */	case 0x3D:										body = endo$ & 0xFFFFFF0000000000;	head = out$K & 0x000000FFFFFFFFFF;		out$K =head|	body;		break;\
/* 7x6 */	case 0x3E:										body = endo$ & 0xFFFF000000000000;	head = out$K & 0x0000FFFFFFFFFFFF;		out$K =head|	body;		break;\
/* 7x7 */	case 0x3F:										body = endo$ & 0xFF00000000000000;	head = out$K & 0x00FFFFFFFFFFFFFF;		out$K =head|	body;		
/*					^ isolate high octets					^ isolate intermediate octets			^ isolate low octets						^ rejoin					*/


#define SwCASE_XXOVER_01W( hi$, endo$, lo$, out$W )	/* "01W" means	switch case vector 0 starts at zero,
																switch case vector 1 starts at one,
																and args[0..2] "double-wye" into arg-3, which is the output variable.	*/	\
/* 0x0 */	case 0x00:	tail =	hi$  & 0xFFFFFFFFFFFFFF00;		body = endo$ & 0x00000000000000FF;										out$W =		body|	tail; 	break;\
/* 0x1 */	case 0x01:	tail =	hi$  & 0xFFFFFFFFFFFF0000;		body = endo$ & 0x000000000000FF00;	head = lo$ & 0x00000000000000FF;    		out$W =head|	body|	tail;	break;\
/* 0x2 */	case 0x02:	tail =	hi$  & 0xFFFFFFFFFF000000;		body = endo$ & 0x0000000000FF0000;	head = lo$ & 0x000000000000FFFF;    		out$W =head|	body|	tail;	break;\
/* 0x3 */	case 0x03:	tail =	hi$  & 0xFFFFFFFF00000000;		body = endo$ & 0x00000000FF000000;	head = lo$ & 0x0000000000FFFFFF;    		out$W =head|	body|	tail;	break;\
/* 0x4 */	case 0x04:	tail =	hi$  & 0xFFFFFF0000000000;		body = endo$ & 0x000000FF00000000;	head = lo$ & 0x00000000FFFFFFFF;    		out$W =head|	body|	tail;	break;\
/* 0x5 */	case 0x05:	tail =	hi$  & 0xFFFF000000000000;		body = endo$ & 0x0000FF0000000000;	head = lo$ & 0x000000FFFFFFFFFF;    		out$W =head|	body|	tail;	break;\
/* 0x6 */	case 0x06:	tail =	hi$  & 0xFF00000000000000;		body = endo$ & 0x00FF000000000000;	head = lo$ & 0x0000FFFFFFFFFFFF;    		out$W =head|	body|	tail;	break;\
/* 0x7 */	case 0x07:										body = endo$ & 0xFF00000000000000;	head = lo$ & 0x00FFFFFFFFFFFFFF;    		out$W =head|	body;		break;\
\
/* 1x0 */	case 0x08:	tail =	hi$  & 0xFFFFFFFFFFFF0000;		body = endo$ & 0x000000000000FFFF;										out$W =		body|	tail;	break;\
/* 1x1 */	case 0x09:	tail =	hi$  & 0xFFFFFFFFFF000000;		body = endo$ & 0x0000000000FFFF00;	head = lo$ & 0x00000000000000FF;    		out$W =head|	body|	tail;	break;\
/* 1x2 */	case 0x0A:	tail =	hi$  & 0xFFFFFFFF00000000;		body = endo$ & 0x00000000FFFF0000;	head = lo$ & 0x000000000000FFFF;    		out$W =head|	body|	tail;	break;\
/* 1x3 */	case 0x0B:	tail =	hi$  & 0xFFFFFF0000000000;		body = endo$ & 0x000000FFFF000000;	head = lo$ & 0x0000000000FFFFFF;    		out$W =head|	body|	tail;	break;\
/* 1x4 */	case 0x0C:	tail =	hi$  & 0xFFFF000000000000;		body = endo$ & 0x0000FFFF00000000;	head = lo$ & 0x00000000FFFFFFFF;    		out$W =head|	body|	tail;	break;\
/* 1x5 */	case 0x0D:	tail =	hi$  & 0xFF00000000000000;		body = endo$ & 0x00FFFF0000000000;	head = lo$ & 0x000000FFFFFFFFFF;    		out$W =head|	body|	tail;	break;\
/* 1x6 */	case 0x0E:										body = endo$ & 0xFFFF000000000000;	head = lo$ & 0x0000FFFFFFFFFFFF;    		out$W =head|	body;		break;\
/* 1x7 */	case 0x0F:										body = endo$ & 0xFF00000000000000;	head = lo$ & 0x00FFFFFFFFFFFFFF;    		out$W =head|	body;		break;\
\
/* 2x0 */	case 0x10:	tail =	hi$  & 0xFFFFFFFFFF000000;		body = endo$ & 0x0000000000FFFFFF;										out$W =		body|	tail; 	break;\
/* 2x1 */	case 0x11:	tail =	hi$  & 0xFFFFFFFF00000000;		body = endo$ & 0x00000000FFFFFF00;	head = lo$ & 0x00000000000000FF;    		out$W =head|	body|	tail;	break;\
/* 2x2 */	case 0x12:	tail =	hi$  & 0xFFFFFF0000000000;		body = endo$ & 0x000000FFFFFF0000;	head = lo$ & 0x000000000000FFFF;    		out$W =head|	body|	tail;	break;\
/* 2x3 */	case 0x13:	tail =	hi$  & 0xFFFF000000000000;		body = endo$ & 0x0000FFFFFF000000;	head = lo$ & 0x0000000000FFFFFF;    		out$W =head|	body|	tail;	break;\
/* 2x4 */	case 0x14:	tail =	hi$  & 0xFF00000000000000;		body = endo$ & 0x00FFFFFF00000000;	head = lo$ & 0x00000000FFFFFFFF;    		out$W =head|	body|	tail;	break;\
/* 2x5 */	case 0x15:										body = endo$ & 0xFFFFFF0000000000;	head = lo$ & 0x000000FFFFFFFFFF;    		out$W =head|	body;		break;\
/* 2x6 */	case 0x16:										body = endo$ & 0xFFFF000000000000;	head = lo$ & 0x0000FFFFFFFFFFFF;    		out$W =head|	body;		break;\
/* 2x7 */	case 0x17:										body = endo$ & 0xFF00000000000000;	head = lo$ & 0x00FFFFFFFFFFFFFF;    		out$W =head|	body;		break;\
\
/* 3x0 */	case 0x18:	tail =	hi$  & 0xFFFFFFFF00000000;		body = endo$ & 0x00000000FFFFFFFF;										out$W =		body|	tail; 	break;\
/* 3x1 */	case 0x19:	tail =	hi$  & 0xFFFFFF0000000000;		body = endo$ & 0x000000FFFFFFFF00;	head = lo$ & 0x00000000000000FF;    		out$W =head|	body|	tail;	break;\
/* 3x2 */	case 0x1A:	tail =	hi$  & 0xFFFF000000000000;		body = endo$ & 0x0000FFFFFFFF0000;	head = lo$ & 0x000000000000FFFF;    		out$W =head|	body|	tail;	break;\
/* 3x3 */	case 0x1B:	tail =	hi$  & 0xFF00000000000000;		body = endo$ & 0x00FFFFFFFF000000;	head = lo$ & 0x0000000000FFFFFF;    		out$W =head|	body|	tail;	break;\
/* 3x4 */	case 0x1C:										body = endo$ & 0xFFFFFFFF00000000;	head = lo$ & 0x00000000FFFFFFFF;    		out$W =head|	body;		break;\
/* 3x5 */	case 0x1D:										body = endo$ & 0xFFFFFF0000000000;	head = lo$ & 0x000000FFFFFFFFFF;    		out$W =head|	body;		break;\
/* 3x6 */	case 0x1E:										body = endo$ & 0xFFFF000000000000;	head = lo$ & 0x0000FFFFFFFFFFFF;    		out$W =head|	body;		break;\
/* 3x7 */	case 0x1F:										body = endo$ & 0xFF00000000000000;	head = lo$ & 0x00FFFFFFFFFFFFFF;    		out$W =head|	body;		break;\
\
/* 4x0 */	case 0x20:	tail =	hi$  & 0xFFFFFF0000000000;		body = endo$ & 0x000000FFFFFFFFFF;										out$W =		body|	tail; 	break;\
/* 4x1 */	case 0x21:	tail =	hi$  & 0xFFFF000000000000;		body = endo$ & 0x0000FFFFFFFFFF00;	head = lo$ & 0x00000000000000FF;    		out$W =head|	body|	tail;	break;\
/* 4x2 */	case 0x22:	tail =	hi$  & 0xFF00000000000000;		body = endo$ & 0x00FFFFFFFFFF0000;	head = lo$ & 0x000000000000FFFF;    		out$W =head|	body|	tail;	break;\
/* 4x3 */	case 0x23:										body = endo$ & 0xFFFFFFFFFF000000;	head = lo$ & 0x0000000000FFFFFF;    		out$W =head|	body;		break;\
/* 4x4 */	case 0x24:										body = endo$ & 0xFFFFFFFF00000000;	head = lo$ & 0x00000000FFFFFFFF;    		out$W =head|	body;		break;\
/* 4x5 */	case 0x25:										body = endo$ & 0xFFFFFF0000000000;	head = lo$ & 0x000000FFFFFFFFFF;    		out$W =head|	body;		break;\
/* 4x6 */	case 0x26:										body = endo$ & 0xFFFF000000000000;	head = lo$ & 0x0000FFFFFFFFFFFF;    		out$W =head|	body;		break;\
/* 4x7 */	case 0x27:										body = endo$ & 0xFF00000000000000;	head = lo$ & 0x00FFFFFFFFFFFFFF;    		out$W =head|	body;		break;\
\
/* 5x0 */	case 0x28:	tail =	hi$  & 0xFFFF000000000000;		body = endo$ & 0x0000FFFFFFFFFFFF;										out$W =		body|	tail; 	break;\
/* 5x1 */	case 0x29:	tail =	hi$  & 0xFF00000000000000;		body = endo$ & 0x00FFFFFFFFFFFF00;	head = lo$ & 0x00000000000000FF;    		out$W =head|	body|	tail;	break;\
/* 5x2 */	case 0x2A:										body = endo$ & 0xFFFFFFFFFFFF0000;	head = lo$ & 0x000000000000FFFF;    		out$W =head|	body;		break;\
/* 5x3 */	case 0x2B:										body = endo$ & 0xFFFFFFFFFF000000;	head = lo$ & 0x0000000000FFFFFF;    		out$W =head|	body;		break;\
/* 5x4 */	case 0x2C:										body = endo$ & 0xFFFFFFFF00000000;	head = lo$ & 0x00000000FFFFFFFF;    		out$W =head|	body;		break;\
/* 5x5 */	case 0x2D:										body = endo$ & 0xFFFFFF0000000000;	head = lo$ & 0x000000FFFFFFFFFF;    		out$W =head|	body;		break;\
/* 5x6 */	case 0x2E:										body = endo$ & 0xFFFF000000000000;	head = lo$ & 0x0000FFFFFFFFFFFF;    		out$W =head|	body;		break;\
/* 5x7 */	case 0x2F:										body = endo$ & 0xFF00000000000000;	head = lo$ & 0x00FFFFFFFFFFFFFF;    		out$W =head|	body;		break;\
\
/* 6x0 */	case 0x30:	tail =	hi$  & 0xFF00000000000000;		body = endo$ & 0x00FFFFFFFFFFFFFF;										out$W =		body|	tail; 	break;\
/* 6x1 */	case 0x31:										body = endo$ & 0xFFFFFFFFFFFFFF00;	head = lo$ & 0x00000000000000FF;    		out$W =head|	body;		break;\
/* 6x2 */	case 0x32:										body = endo$ & 0xFFFFFFFFFFFF0000;	head = lo$ & 0x000000000000FFFF;    		out$W =head|	body;		break;\
/* 6x3 */	case 0x33:										body = endo$ & 0xFFFFFFFFFF000000;	head = lo$ & 0x0000000000FFFFFF;    		out$W =head|	body;		break;\
/* 6x4 */	case 0x34:										body = endo$ & 0xFFFFFFFF00000000;	head = lo$ & 0x00000000FFFFFFFF;    		out$W =head|	body;		break;\
/* 6x5 */	case 0x35:										body = endo$ & 0xFFFFFF0000000000;	head = lo$ & 0x000000FFFFFFFFFF;    		out$W =head|	body;		break;\
/* 6x6 */	case 0x36:										body = endo$ & 0xFFFF000000000000;	head = lo$ & 0x0000FFFFFFFFFFFF;    		out$W =head|	body;		break;\
/* 6x7 */	case 0x37:										body = endo$ & 0xFF00000000000000;	head = lo$ & 0x00FFFFFFFFFFFFFF;    		out$W =head|	body;		break;\
\
/* 7x0 */	case 0x38:										out$W = endo$;																				break;\
/* 7x1 */	case 0x39:										body = endo$ & 0xFFFFFFFFFFFFFF00;	head = lo$ & 0x00000000000000FF;    		out$W =head|	body;		break;\
/* 7x2 */	case 0x3A:										body = endo$ & 0xFFFFFFFFFFFF0000;	head = lo$ & 0x000000000000FFFF;    		out$W =head|	body;		break;\
/* 7x3 */	case 0x3B:										body = endo$ & 0xFFFFFFFFFF000000;	head = lo$ & 0x0000000000FFFFFF;    		out$W =head|	body;		break;\
/* 7x4 */	case 0x3C:										body = endo$ & 0xFFFFFFFF00000000;	head = lo$ & 0x00000000FFFFFFFF;    		out$W =head|	body;		break;\
/* 7x5 */	case 0x3D:										body = endo$ & 0xFFFFFF0000000000;	head = lo$ & 0x000000FFFFFFFFFF;    		out$W =head|	body;		break;\
/* 7x6 */	case 0x3E:										body = endo$ & 0xFFFF000000000000;	head = lo$ & 0x0000FFFFFFFFFFFF;    		out$W =head|	body;		break;\
/* 7x7 */	case 0x3F:										body = endo$ & 0xFF00000000000000;	head = lo$ & 0x00FFFFFFFFFFFFFF;    		out$W =head|	body;		
/*					^ isolate high octets					^ isolate intermediate octets			^ isolate low octets						^ rejoin					*/


#define SwCASE_XSHELF_00T( hi$,	lo$T )			/* "00T" means	switch case vector 0 starts at zero,
																switch case vector 1 starts at zero as well,
																and arg[0] "Tees into" arg[1], which is also the output variable.	*/	\
/* 0x0 */	case 0x00:	lo$T =	hi$;																				break;\
/* 0x1 */	case 0x01:	tail =	hi$  & 0xFFFFFFFFFFFFFF00;     	head =	lo$T  & 0x00000000000000FF;     	lo$T = head|tail;     	break;\
/* 0x2 */	case 0x02:	tail =	hi$  & 0xFFFFFFFFFFFF0000;     	head =	lo$T  & 0x000000000000FFFF;     	lo$T = head|tail;     	break;\
/* 0x3 */	case 0x03:	tail =	hi$  & 0xFFFFFFFFFF000000;     	head =	lo$T  & 0x0000000000FFFFFF;     	lo$T = head|tail;     	break;\
/* 0x4 */	case 0x04:	tail =	hi$  & 0xFFFFFFFF00000000;     	head =	lo$T  & 0x00000000FFFFFFFF;     	lo$T = head|tail;     	break;\
/* 0x5 */	case 0x05:	tail =	hi$  & 0xFFFFFF0000000000;     	head =	lo$T  & 0x000000FFFFFFFFFF;     	lo$T = head|tail;     	break;\
/* 0x6 */	case 0x06:	tail =	hi$  & 0xFFFF000000000000;     	head =	lo$T  & 0x0000FFFFFFFFFFFF;     	lo$T = head|tail;     	break;\
/* 0x7 */	case 0x07:	tail =	hi$  & 0xFF00000000000000;     	head =	lo$T  & 0x00FFFFFFFFFFFFFF;     	lo$T = head|tail;     	break;\
/* 1x0 */	case 0x08:	lo$T =	hi$  & 0xFFFFFFFFFFFFFF00;															break;\
/* 1x1 */	case 0x09:	tail =	hi$  & 0xFFFFFFFFFFFF0000;     	head =	lo$T  & 0x00000000000000FF;     	lo$T = head|tail;     	break;\
/* 1x2 */	case 0x0A:	tail =	hi$  & 0xFFFFFFFFFF000000;     	head =	lo$T  & 0x000000000000FFFF;     	lo$T = head|tail;     	break;\
/* 1x3 */	case 0x0B:	tail =	hi$  & 0xFFFFFFFF00000000;     	head =	lo$T  & 0x0000000000FFFFFF;     	lo$T = head|tail;     	break;\
/* 1x4 */	case 0x0C:	tail =	hi$  & 0xFFFFFF0000000000;     	head =	lo$T  & 0x00000000FFFFFFFF;     	lo$T = head|tail;     	break;\
/* 1x5 */	case 0x0D:	tail =	hi$  & 0xFFFF000000000000;     	head =	lo$T  & 0x000000FFFFFFFFFF;     	lo$T = head|tail;     	break;\
/* 1x6 */	case 0x0E:	tail =	hi$  & 0xFF00000000000000;     	head =	lo$T  & 0x0000FFFFFFFFFFFF;		lo$T = head|tail;     	break;\
/* 1x7 */	case 0x0F:												lo$T &=0x00FFFFFFFFFFFFFF;						break;\
/* 2x0 */	case 0x10:	lo$T =	hi$  & 0xFFFFFFFFFFFF0000;															break;\
/* 2x1 */	case 0x11:	tail =	hi$  & 0xFFFFFFFFFF000000;     	head =	lo$T  & 0x00000000000000FF;     	lo$T = head|tail;     	break;\
/* 2x2 */	case 0x12:	tail =	hi$  & 0xFFFFFFFF00000000;     	head =	lo$T  & 0x000000000000FFFF;     	lo$T = head|tail;     	break;\
/* 2x3 */	case 0x13:	tail =	hi$  & 0xFFFFFF0000000000;     	head =	lo$T  & 0x0000000000FFFFFF;     	lo$T = head|tail;     	break;\
/* 2x4 */	case 0x14:	tail =	hi$  & 0xFFFF000000000000;     	head =	lo$T  & 0x00000000FFFFFFFF;     	lo$T = head|tail;     	break;\
/* 2x5 */	case 0x15:	tail =	hi$  & 0xFF00000000000000;     	head =	lo$T  & 0x000000FFFFFFFFFF;     	lo$T = head|tail;     	break;\
/* 2x6 */	case 0x16:												lo$T &=0x0000FFFFFFFFFFFF;						break;\
/* 2x7 */	case 0x17:												lo$T &=0x00FFFFFFFFFFFFFF;						break;\
/* 3x0 */	case 0x18:	lo$T =	hi$  & 0xFFFFFFFFFF000000;															break;\
/* 3x1 */	case 0x19:	tail =	hi$  & 0xFFFFFFFF00000000;     	head =	lo$T  & 0x00000000000000FF;     	lo$T = head|tail;     	break;\
/* 3x2 */	case 0x1A:	tail =	hi$  & 0xFFFFFF0000000000;     	head =	lo$T  & 0x000000000000FFFF;     	lo$T = head|tail;     	break;\
/* 3x3 */	case 0x1B:	tail =	hi$  & 0xFFFF000000000000;     	head =	lo$T  & 0x0000000000FFFFFF;     	lo$T = head|tail;     	break;\
/* 3x4 */	case 0x1C:	tail =	hi$  & 0xFF00000000000000;     	head =	lo$T  & 0x00000000FFFFFFFF;     	lo$T = head|tail;     	break;\
/* 3x5 */	case 0x1D:												lo$T &=0x000000FFFFFFFFFF;						break;\
/* 3x6 */	case 0x1E:												lo$T &=0x0000FFFFFFFFFFFF;						break;\
/* 3x7 */	case 0x1F:												lo$T &=0x00FFFFFFFFFFFFFF;						break;\
/* 4x0 */	case 0x20:	lo$T =	hi$  & 0xFFFFFFFF00000000;															break;\
/* 4x1 */	case 0x21:	tail =	hi$  & 0xFFFFFF0000000000;     	head =	lo$T  & 0x00000000000000FF;     	lo$T = head|tail;     	break;\
/* 4x2 */	case 0x22:	tail =	hi$  & 0xFFFF000000000000;     	head =	lo$T  & 0x000000000000FFFF;     	lo$T = head|tail;     	break;\
/* 4x3 */	case 0x23:	tail =	hi$  & 0xFF00000000000000;     	head =	lo$T  & 0x0000000000FFFFFF;     	lo$T = head|tail;     	break;\
/* 4x4 */	case 0x24:												lo$T &=0x00000000FFFFFFFF;						break;\
/* 4x5 */	case 0x25:												lo$T &=0x000000FFFFFFFFFF;						break;\
/* 4x6 */	case 0x26:												lo$T &=0x0000FFFFFFFFFFFF;						break;\
/* 4x7 */	case 0x27:												lo$T &=0x00FFFFFFFFFFFFFF;						break;\
/* 5x0 */	case 0x28:	lo$T =	hi$  & 0xFFFFFF0000000000;															break;\
/* 5x1 */	case 0x29:	tail =	hi$  & 0xFFFF000000000000;     	head =	lo$T  & 0x00000000000000FF;     	lo$T = head|tail;     	break;\
/* 5x2 */	case 0x2A:	tail =	hi$  & 0xFF00000000000000;     	head =	lo$T  & 0x000000000000FFFF;     	lo$T = head|tail;     	break;\
/* 5x3 */	case 0x2B:												lo$T &=0x0000000000FFFFFF;						break;\
/* 5x4 */	case 0x2C:												lo$T &=0x00000000FFFFFFFF;						break;\
/* 5x5 */	case 0x2D:												lo$T &=0x000000FFFFFFFFFF;						break;\
/* 5x6 */	case 0x2E:												lo$T &=0x0000FFFFFFFFFFFF;						break;\
/* 5x7 */	case 0x2F:												lo$T &=0x00FFFFFFFFFFFFFF;						break;\
/* 6x0 */	case 0x30:	lo$T =	hi$  & 0xFFFF000000000000;															break;\
/* 6x1 */	case 0x31:	tail =	hi$  & 0xFF00000000000000;     	head =	lo$T  & 0x00000000000000FF;     	lo$T = head|tail;     	break;\
/* 6x2 */	case 0x32:												lo$T &=0x000000000000FFFF;					break;\
/* 6x3 */	case 0x33:												lo$T &=0x0000000000FFFFFF;						break;\
/* 6x4 */	case 0x34:												lo$T &=0x00000000FFFFFFFF;						break;\
/* 6x5 */	case 0x35:												lo$T &=0x000000FFFFFFFFFF;						break;\
/* 6x6 */	case 0x36:												lo$T &=0x0000FFFFFFFFFFFF;						break;\
/* 6x7 */	case 0x37:												lo$T &=0x00FFFFFFFFFFFFFF;						break;\
/* 7x0 */	case 0x38:	lo$T =	hi$  & 0xFF00000000000000;															break;\
/* 7x1 */	case 0x39:												lo$T &=0x00000000000000FF;					break;\
/* 7x2 */	case 0x3A:												lo$T &=0x000000000000FFFF;					break;\
/* 7x3 */	case 0x3B:												lo$T &=0x0000000000FFFFFF;						break;\
/* 7x4 */	case 0x3C:												lo$T &=0x00000000FFFFFFFF;						break;\
/* 7x5 */	case 0x3D:												lo$T &=0x000000FFFFFFFFFF;						break;\
/* 7x6 */	case 0x3E:												lo$T &=0x0000FFFFFFFFFFFF;						break;\
/* 7x7 */	case 0x3F:												lo$T &=0x00FFFFFFFFFFFFFF;						break;\
/* 8x0 */	case 0x40:	lo$T =	0;																				break;\
/* 8x1 */	case 0x41:												lo$T &=0x00000000000000FF;					break;\
/* 8x2 */	case 0x42:												lo$T &=0x000000000000FFFF;					break;\
/* 8x3 */	case 0x43:												lo$T &=0x0000000000FFFFFF;						break;\
/* 8x4 */	case 0x44:												lo$T &=0x00000000FFFFFFFF;						break;\
/* 8x5 */	case 0x45:												lo$T &=0x000000FFFFFFFFFF;						break;\
/* 8x6 */	case 0x46:												lo$T &=0x0000FFFFFFFFFFFF;						break;\
/* 8x7 */	case 0x47:												lo$T &=0x00FFFFFFFFFFFFFF;
/*					^ isolate trailing octets displaced				^	isolate leading octets retained		^ rejoin		*/





/*	kSpliceOpcode = ic0 |( post_c<< 3);	*/
#define SwCASE_XSHELF_01T( hi$,	lo$T )			/* "01T" means	switch case vector 0 starts at zero,
																switch case vector 1 starts at one,
																and arg[0] "Tees into" arg[1], which is also the output variable.	*/	\
/* 0x0 */	case 0x00:	lo$T =	hi$  & 0xFFFFFFFFFFFFFF00;															break;\
/* 0x1 */	case 0x01:	tail =	hi$  & 0xFFFFFFFFFFFF0000;     	head =	lo$T  & 0x00000000000000FF;     	lo$T = head|tail;     	break;\
/* 0x2 */	case 0x02:	tail =	hi$  & 0xFFFFFFFFFF000000;     	head =	lo$T  & 0x000000000000FFFF;     	lo$T = head|tail;     	break;\
/* 0x3 */	case 0x03:	tail =	hi$  & 0xFFFFFFFF00000000;     	head =	lo$T  & 0x0000000000FFFFFF;     	lo$T = head|tail;     	break;\
/* 0x4 */	case 0x04:	tail =	hi$  & 0xFFFFFF0000000000;     	head =	lo$T  & 0x00000000FFFFFFFF;     	lo$T = head|tail;     	break;\
/* 0x5*/	case 0x05:	tail =	hi$  & 0xFFFF000000000000;     	head =	lo$T  & 0x000000FFFFFFFFFF;     	lo$T = head|tail;     	break;\
/* 0x6 */	case 0x06:	tail =	hi$  & 0xFF00000000000000;     	head =	lo$T  & 0x0000FFFFFFFFFFFF;     	lo$T = head|tail;     	break;\
/* 0x7 */	case 0x07:												lo$T &=0x00FFFFFFFFFFFFFF;     					break;\
\
/* 1x0 */	case 0x08:	lo$T =	hi$  & 0xFFFFFFFFFFFF0000;     														break;\
/* 1x1 */	case 0x09:	tail =	hi$  & 0xFFFFFFFFFF000000;     	head =	lo$T  & 0x00000000000000FF;     	lo$T = head|tail;     	break;\
/* 1x2 */	case 0x0A:	tail =	hi$  & 0xFFFFFFFF00000000;     	head =	lo$T  & 0x000000000000FFFF;     	lo$T = head|tail;     	break;\
/* 1x3 */	case 0x0B:	tail =	hi$  & 0xFFFFFF0000000000;     	head =	lo$T  & 0x0000000000FFFFFF;     	lo$T = head|tail;     	break;\
/* 1x4 */	case 0x0C:	tail =	hi$  & 0xFFFF000000000000;     	head =	lo$T  & 0x00000000FFFFFFFF;     	lo$T = head|tail;     	break;\
/* 1x5 */	case 0x0D:	tail =	hi$  & 0xFF00000000000000;     	head =	lo$T  & 0x000000FFFFFFFFFF;     	lo$T = head|tail;     	break;\
/* 1x6 */	case 0x0E:												lo$T &=0x0000FFFFFFFFFFFF;						break;\
/* 1x7 */	case 0x0F:												lo$T &=0x00FFFFFFFFFFFFFF;						break;\
\
/* 2x0 */	case 0x10:	lo$T =	hi$  & 0xFFFFFFFFFF000000;															break;\
/* 2x1 */	case 0x11:	tail =	hi$  & 0xFFFFFFFF00000000;     	head =	lo$T  & 0x00000000000000FF;     	lo$T = head|tail;     	break;\
/* 2x2 */	case 0x12:	tail =	hi$  & 0xFFFFFF0000000000;     	head =	lo$T  & 0x000000000000FFFF;     	lo$T = head|tail;     	break;\
/* 2x3 */	case 0x13:	tail =	hi$  & 0xFFFF000000000000;     	head =	lo$T  & 0x0000000000FFFFFF;     	lo$T = head|tail;     	break;\
/* 2x4 */	case 0x14:	tail =	hi$  & 0xFF00000000000000;     	head =	lo$T  & 0x00000000FFFFFFFF;     	lo$T = head|tail;     	break;\
/* 2x5 */	case 0x15:												lo$T &=0x000000FFFFFFFFFF;						break;\
/* 2x6 */	case 0x16:												lo$T &=0x0000FFFFFFFFFFFF;						break;\
/* 2x7 */	case 0x17:												lo$T &=0x00FFFFFFFFFFFFFF;						break;\
\
/* 3x0 */	case 0x18:	lo$T =	hi$  & 0xFFFFFFFF00000000;															break;\
/* 3x1 */	case 0x19:	tail =	hi$  & 0xFFFFFF0000000000;     	head =	lo$T  & 0x00000000000000FF;     	lo$T = head|tail;     	break;\
/* 3x2 */	case 0x1A:	tail =	hi$  & 0xFFFF000000000000;     	head =	lo$T  & 0x000000000000FFFF;     	lo$T = head|tail;     	break;\
/* 3x3 */	case 0x1B:	tail =	hi$  & 0xFF00000000000000;     	head =	lo$T  & 0x0000000000FFFFFF;     	lo$T = head|tail;     	break;\
/* 3x4 */	case 0x1C:												lo$T &=0x00000000FFFFFFFF;						break;\
/* 3x5 */	case 0x1D:												lo$T &=0x000000FFFFFFFFFF;						break;\
/* 3x6 */	case 0x1E:												lo$T &=0x0000FFFFFFFFFFFF;						break;\
/* 3x7 */	case 0x1F:												lo$T &=0x00FFFFFFFFFFFFFF;						break;\
\
/* 4x0 */	case 0x20:	lo$T =	hi$  & 0xFFFFFF0000000000;															break;\
/* 4x1 */	case 0x21:	tail =	hi$  & 0xFFFF000000000000;     	head =	lo$T  & 0x00000000000000FF;     	lo$T = head|tail;     	break;\
/* 4x2 */	case 0x22:	tail =	hi$  & 0xFF00000000000000;     	head =	lo$T  & 0x000000000000FFFF;     	lo$T = head|tail;     	break;\
/* 4x3 */	case 0x23:												lo$T &=0x0000000000FFFFFF;						break;\
/* 4x4 */	case 0x24:												lo$T &=0x00000000FFFFFFFF;						break;\
/* 4x5 */	case 0x25:												lo$T &=0x000000FFFFFFFFFF;						break;\
/* 4x6 */	case 0x26:												lo$T &=0x0000FFFFFFFFFFFF;						break;\
/* 4x7 */	case 0x27:												lo$T &=0x00FFFFFFFFFFFFFF;						break;\
\
/* 5x0 */	case 0x28:	lo$T =	hi$  & 0xFFFF000000000000;															break;\
/* 5x1 */	case 0x29:	tail =	hi$  & 0xFF00000000000000;     	head =	lo$T  & 0x00000000000000FF;     	lo$T = head|tail;     	break;\
/* 5x2 */	case 0x2A:												lo$T &=0x000000000000FFFF;					break;\
/* 5x3 */	case 0x2B:												lo$T &=0x0000000000FFFFFF;						break;\
/* 5x4 */	case 0x2C:												lo$T &=0x00000000FFFFFFFF;						break;\
/* 5x5 */	case 0x2D:												lo$T &=0x000000FFFFFFFFFF;						break;\
/* 5x6 */	case 0x2E:												lo$T &=0x0000FFFFFFFFFFFF;						break;\
/* 5x7 */	case 0x2F:												lo$T &=0x00FFFFFFFFFFFFFF;						break;\
\
/* 6x0 */	case 0x30:	lo$T =	hi$  &  0xFF00000000000000;														break;\
/* 6x1 */	case 0x31:												lo$T &=0x00000000000000FF;					break;\
/* 6x2 */	case 0x32:												lo$T &=0x000000000000FFFF;					break;\
/* 6x3 */	case 0x33:												lo$T &=0x0000000000FFFFFF;						break;\
/* 6x4 */	case 0x34:												lo$T &=0x00000000FFFFFFFF;						break;\
/* 6x5 */	case 0x35:												lo$T &=0x000000FFFFFFFFFF;						break;\
/* 6x6 */	case 0x36:												lo$T &=0x0000FFFFFFFFFFFF;						break;\
/* 6x7 */	case 0x37:												lo$T &=0x00FFFFFFFFFFFFFF;						break;\
\
/* 7x0 */	case 0x38:	lo$T	=		0x0000000000000000;															break;\
/* 7x1 */	case 0x39:												lo$T &=0x00000000000000FF;					break;\
/* 7x2 */	case 0x3A:												lo$T &=0x000000000000FFFF;					break;\
/* 7x3 */	case 0x3B:												lo$T &=0x0000000000FFFFFF;						break;\
/* 7x4 */	case 0x3C:												lo$T &=0x00000000FFFFFFFF;						break;\
/* 7x5 */	case 0x3D:												lo$T &=0x000000FFFFFFFFFF;						break;\
/* 7x6 */	case 0x3E:												lo$T &=0x0000FFFFFFFFFFFF;						break;\
/* 7x7 */	case 0x3F:												lo$T &=0x00FFFFFFFFFFFFFF;						
/*					^ isolate trailing octets						^ isolate leading octets			^ rejoin		*/



#define SwCASE_XSHELF_01IS( exo$ )					/* "01IS" means	switch case vector 0 starts at zero,
																switch case vector 1 starts at one,
																and arg[0] is both the input and output variable, "In Situ".	*/	\
/* 0x0 */	case 0x00:	exo$ &=	0xFFFFFFFFFFFFFF00;  	break;\
/* 0x1 */	case 0x01:	exo$ &=	0xFFFFFFFFFFFF00FF;  	break;\
/* 0x2 */	case 0x02:	exo$ &=	0xFFFFFFFFFF00FFFF;  	break;\
/* 0x3 */	case 0x03:	exo$ &=	0xFFFFFFFF00FFFFFF;  	break;\
/* 0x4 */	case 0x04:	exo$ &=	0xFFFFFF00FFFFFFFF;  	break;\
/* 0x5 */	case 0x05:	exo$ &=	0xFFFF00FFFFFFFFFF;  	break;\
/* 0x6 */	case 0x06:	exo$ &=	0xFF00FFFFFFFFFFFF;  	break;\
/* 0x7 */	case 0x07:	exo$ &=	0x00FFFFFFFFFFFFFF;  	break;\
\
/* 1x0 */	case 0x08:	exo$ &=	0xFFFFFFFFFFFF0000;  	break;\
/* 1x1 */	case 0x09:	exo$ &=	0xFFFFFFFFFF0000FF;  	break;\
/* 1x2 */	case 0x0A:	exo$ &=	0xFFFFFFFF0000FFFF;  	break;\
/* 1x3 */	case 0x0B:	exo$ &=	0xFFFFFF0000FFFFFF;  	break;\
/* 1x4 */	case 0x0C:	exo$ &=	0xFFFF0000FFFFFFFF;  	break;\
/* 1x5 */	case 0x0D:	exo$ &=	0xFF0000FFFFFFFFFF;  	break;\
/* 1x6 */	case 0x0E:	exo$ &=	0x0000FFFFFFFFFFFF;  	break;\
/* 1x7 */	case 0x0F:	exo$ &=	0x00FFFFFFFFFFFFFF;  	break;\
\
/* 2x0 */	case 0x10:	exo$ &=	0xFFFFFFFFFF000000;  	break;\
/* 2x1 */	case 0x11:	exo$ &=	0xFFFFFFFF000000FF;  	break;\
/* 2x2 */	case 0x12:	exo$ &=	0xFFFFFF000000FFFF;  	break;\
/* 2x3 */	case 0x13:	exo$ &=	0xFFFF000000FFFFFF;  	break;\
/* 2x4 */	case 0x14:	exo$ &=	0xFF000000FFFFFFFF;  	break;\
/* 2x5 */	case 0x15:	exo$ &=	0x000000FFFFFFFFFF;  	break;\
/* 2x6 */	case 0x16:	exo$ &=	0x0000FFFFFFFFFFFF;  	break;\
/* 2x7 */	case 0x17:	exo$ &=	0x00FFFFFFFFFFFFFF;  	break;\
\
/* 3x0 */	case 0x18:	exo$ &=	0xFFFFFFFF00000000;  	break;\
/* 3x1 */	case 0x19:	exo$ &=	0xFFFFFF00000000FF;  	break;\
/* 3x2 */	case 0x1A:	exo$ &=	0xFFFF00000000FFFF;  	break;\
/* 3x3 */	case 0x1B:	exo$ &=	0xFF00000000FFFFFF;  	break;\
/* 3x4 */	case 0x1C:	exo$ &=	0x00000000FFFFFFFF;  	break;\
/* 3x5 */	case 0x1D:	exo$ &=	0x000000FFFFFFFFFF;  	break;\
/* 3x6 */	case 0x1E:	exo$ &=	0x0000FFFFFFFFFFFF;  	break;\
/* 3x7 */	case 0x1F:	exo$ &=	0x00FFFFFFFFFFFFFF;  	break;\
\
/* 4x0 */	case 0x20:	exo$ &=	0xFFFFFF0000000000;  	break;\
/* 4x1 */	case 0x21:	exo$ &=	0xFFFF0000000000FF;  	break;\
/* 4x2 */	case 0x22:	exo$ &=	0xFF0000000000FFFF;  	break;\
/* 4x3 */	case 0x23:	exo$ &=	0x0000000000FFFFFF;  	break;\
/* 4x4 */	case 0x24:	exo$ &=	0x00000000FFFFFFFF;  	break;\
/* 4x5 */	case 0x25:	exo$ &=	0x000000FFFFFFFFFF;  	break;\
/* 4x6 */	case 0x26:	exo$ &=	0x0000FFFFFFFFFFFF;  	break;\
/* 4x7 */	case 0x27:	exo$ &=	0x00FFFFFFFFFFFFFF;  	break;\
\
/* 5x0 */	case 0x28:	exo$ &=	0xFFFFFF0000000000;  	break;\
/* 5x1 */	case 0x29:	exo$ &=	0xFFFF0000000000FF;  	break;\
/* 5x2 */	case 0x2A:	exo$ &=	0xFF0000000000FFFF;  	break;\
/* 5x3 */	case 0x2B:	exo$ &=	0x0000000000FFFFFF;  	break;\
/* 5x4 */	case 0x2C:	exo$ &=	0x00000000FFFFFFFF;  	break;\
/* 5x5 */	case 0x2D:	exo$ &=	0x000000FFFFFFFFFF;  	break;\
/* 5x6 */	case 0x2E:	exo$ &=	0x0000FFFFFFFFFFFF;  	break;\
/* 5x7 */	case 0x2F:	exo$ &=	0x00FFFFFFFFFFFFFF;  	break;\
\
/* 6x0 */	case 0x30:	exo$ &=	0xFF00000000000000;  	break;\
/* 6x1 */	case 0x31:	exo$ &=	0x00000000000000FF;  	break;\
/* 6x2 */	case 0x32:	exo$ &=	0x000000000000FFFF;  	break;\
/* 6x3 */	case 0x33:	exo$ &=	0x0000000000FFFFFF;  	break;\
/* 6x4 */	case 0x34:	exo$ &=	0x00000000FFFFFFFF;  	break;\
/* 6x5 */	case 0x35:	exo$ &=	0x000000FFFFFFFFFF;  	break;\
/* 6x6 */	case 0x36:	exo$ &=	0x0000FFFFFFFFFFFF;  	break;\
/* 6x7 */	case 0x37:	exo$ &=	0x00FFFFFFFFFFFFFF;  	break;\
\
/* 7x0 */	case 0x38:	exo$ =	0x0000000000000000;  	break;\
/* 7x1 */	case 0x39:	exo$ &=	0x00000000000000FF;  	break;\
/* 7x2 */	case 0x3A:	exo$ &=	0x000000000000FFFF;  	break;\
/* 7x3 */	case 0x3B:	exo$ &=	0x0000000000FFFFFF;  	break;\
/* 7x4 */	case 0x3C:	exo$ &=	0x00000000FFFFFFFF;  	break;\
/* 7x5 */	case 0x3D:	exo$ &=	0x000000FFFFFFFFFF;  	break;\
/* 7x6 */	case 0x3E:	exo$ &=	0x0000FFFFFFFFFFFF;  	break;\
/* 7x7 */	case 0x3F:	exo$ &=	0x00FFFFFFFFFFFFFF;     	


#define SwCASE_SHELF_01IS( endo$IS )					/* "01IS" means	switch case vector 0 starts at zero,
																	switch case vector 1 starts at one,
																	and arg[0] is both the input and output variable, "In Situ".	*/	\
/* FxF */	case 0x00:	endo$IS &=	0x00000000000000FF;  	break;\
/* Fx1 */	case 0x01:	endo$IS &=	0x000000000000FF00;  	break;\
/* Fx2 */	case 0x02:	endo$IS &=	0x0000000000FF0000;  	break;\
/* Fx3 */	case 0x03:	endo$IS &=	0x00000000FF000000;  	break;\
/* Fx4 */	case 0x04:	endo$IS &=	0x000000FF00000000;  	break;\
/* Fx5 */	case 0x05:	endo$IS &=	0x0000FF0000000000;  	break;\
/* Fx6 */	case 0x06:	endo$IS &=	0x00FF000000000000;  	break;\
/* Fx7 */	case 0x07:	endo$IS &=	0xFF00000000000000;  	break;\
\
/* 1xF */	case 0x08:	endo$IS &=	0x000000000000FFFF;  	break;\
/* 1x1 */	case 0x09:	endo$IS &=	0x0000000000FFFF00;  	break;\
/* 1x2 */	case 0x0A:	endo$IS &=	0x00000000FFFF0000;  	break;\
/* 1x3 */	case 0x0B:	endo$IS &=	0x000000FFFF000000;  	break;\
/* 1x4 */	case 0x0C:	endo$IS &=	0x0000FFFF00000000;  	break;\
/* 1x5 */	case 0x0D:	endo$IS &=	0x00FFFF0000000000;  	break;\
/* 1x6 */	case 0x0E:	endo$IS &=	0xFFFF000000000000;  	break;\
/* 1x7 */	case 0x0F:	endo$IS &=	0xFF00000000000000;  	break;\
\
/* 2xF */	case 0x10:	endo$IS &=	0x0000000000FFFFFF;  	break;\
/* 2x1 */	case 0x11:	endo$IS &=	0x00000000FFFFFF00;  	break;\
/* 2x2 */	case 0x12:	endo$IS &=	0x000000FFFFFF0000;  	break;\
/* 2x3 */	case 0x13:	endo$IS &=	0x0000FFFFFF000000;  	break;\
/* 2x4 */	case 0x14:	endo$IS &=	0x00FFFFFF00000000;  	break;\
/* 2x5 */	case 0x15:	endo$IS &=	0xFFFFFF0000000000;  	break;\
/* 2x6 */	case 0x16:	endo$IS &=	0xFFFF000000000000;  	break;\
/* 2x7 */	case 0x17:	endo$IS &=	0xFF00000000000000;  	break;\
\
/* 3xF */	case 0x18:	endo$IS &=	0x00000000FFFFFFFF;  	break;\
/* 3x1 */	case 0x19:	endo$IS &=	0x000000FFFFFFFF00;  	break;\
/* 3x2 */	case 0x1A:	endo$IS &=	0x0000FFFFFFFF0000;  	break;\
/* 3x3 */	case 0x1B:	endo$IS &=	0x00FFFFFFFF000000;  	break;\
/* 3x4 */	case 0x1C:	endo$IS &=	0xFFFFFFFF00000000;  	break;\
/* 3x5 */	case 0x1D:	endo$IS &=	0xFFFFFF0000000000;  	break;\
/* 3x6 */	case 0x1E:	endo$IS &=	0xFFFF000000000000;  	break;\
/* 3x7 */	case 0x1F:	endo$IS &=	0xFF00000000000000;  	break;\
\
/* 4xF */	case 0x20:	endo$IS &=	0x000000FFFFFFFFFF;  	break;\
/* 4x1 */	case 0x21:	endo$IS &=	0x0000FFFFFFFFFF00;  	break;\
/* 4x2 */	case 0x22:	endo$IS &=	0x00FFFFFFFFFF0000;  	break;\
/* 4x3 */	case 0x23:	endo$IS &=	0xFFFFFFFFFF000000;  	break;\
/* 4x4 */	case 0x24:	endo$IS &=	0xFFFFFFFF00000000;  	break;\
/* 4x5 */	case 0x25:	endo$IS &=	0xFFFFFF0000000000;  	break;\
/* 4x6 */	case 0x26:	endo$IS &=	0xFFFF000000000000;  	break;\
/* 4x7 */	case 0x27:	endo$IS &=	0xFF00000000000000;  	break;\
\
/* 5xF */	case 0x28:	endo$IS &=	0x000000FFFFFFFFFF;  	break;\
/* 5x1 */	case 0x29:	endo$IS &=	0x0000FFFFFFFFFF00;  	break;\
/* 5x2 */	case 0x2A:	endo$IS &=	0x00FFFFFFFFFF0000;  	break;\
/* 5x3 */	case 0x2B:	endo$IS &=	0xFFFFFFFFFF000000;  	break;\
/* 5x4 */	case 0x2C:	endo$IS &=	0xFFFFFFFF00000000;  	break;\
/* 5x5 */	case 0x2D:	endo$IS &=	0xFFFFFF0000000000;  	break;\
/* 5x6 */	case 0x2E:	endo$IS &=	0xFFFF000000000000;  	break;\
/* 5x7 */	case 0x2F:	endo$IS &=	0xFF00000000000000;  	break;\
\
/* 6xF */	case 0x30:	endo$IS &=	0x00FFFFFFFFFFFFFF;  	break;\
/* 6x1 */	case 0x31:	endo$IS &=	0xFFFFFFFFFFFFFF00;  	break;\
/* 6x2 */	case 0x32:	endo$IS &=	0xFFFFFFFFFFFF0000;  	break;\
/* 6x3 */	case 0x33:	endo$IS &=	0xFFFFFFFFFF000000;  	break;\
/* 6x4 */	case 0x34:	endo$IS &=	0xFFFFFFFF00000000;  	break;\
/* 6x5 */	case 0x35:	endo$IS &=	0xFFFFFF0000000000;  	break;\
/* 6x6 */	case 0x36:	endo$IS &=	0xFFFF000000000000;  	break;\
/* 6x7 */	case 0x37:	endo$IS &=	0xFF00000000000000;  	break;\
\
/* 7xF */	case 0x38:									break;\
/* 7x1 */	case 0x39:	endo$IS &=	0xFFFFFFFFFFFFFF00;    	break;\
/* 7x2 */	case 0x3A:	endo$IS &=	0xFFFFFFFFFFFF0000;  	break;\
/* 7x3 */	case 0x3B:	endo$IS &=	0xFFFFFFFFFF000000;  	break;\
/* 7x4 */	case 0x3C:	endo$IS &=	0xFFFFFFFF00000000;  	break;\
/* 7x5 */	case 0x3D:	endo$IS &=	0xFFFFFF0000000000;  	break;\
/* 7x6 */	case 0x3E:	endo$IS &=	0xFFFF000000000000;  	break;\
/* 7x7 */	case 0x3F:	endo$IS &=	0xFF00000000000000;  	


#define LLUI_BYTESUB_MORE(	$LLUI, $i, $shift_bytes, $mask_bytes )\
							bs = $shift_b<< 3;	/* Convert ( i ) bytes to ( bs ) bits.						*/	\
	Kx8_ = *( (ui64*) $LLUI )<<	bs;				/* Left-shift a copy of $LLUI by (bs) bits.				*/	\
			kSpliceOpcode =	bs|$i;			/* Serialize the given parameters to generate the opcode.	*/	\
	switch(	kSpliceOpcode ){ LLUI_BYTECUT_SwCASES( Kx8_, *( (ui64*) $LLUI) );	}

#define LLUI_BYTESUB_LESS		$LLUI, $i, $shift_bytes, $mask_bytes )\
							bs = $shift_b<< 3;	/* Convert ( i ) bytes to ( bs ) bits.						*/	\
	Kx8_ = *( (ui64*) $LLUI )>>	bs;				/* Right-shift a copy of $LLUI by (bs) bits.				*/	\
			kSpliceOpcode =	bs|$i;			/* Serialize the given parameters to generate the opcode.	*/	\
	switch(	kSpliceOpcode ){ LLUI_BYTECUT_SwCASES( Kx8_, *( (ui64*) $LLUI) );	}
