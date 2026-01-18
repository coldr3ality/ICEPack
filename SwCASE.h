

#define CASTq2i(	 	$I, $p, $q )		switch( $q){	case 0:	break;	\
												case 1:	$I=	 				*( (ui08* )	$p 		);			break;	\
												case 2:	$I=					*( (ui16* )	$p	 	);			break; 	\
												case 3:	$I=	 				*( (ui32* ) (	$p -1	) ) >>8;		break;	\
												case 4:	$I=	 				*( (ui32* )	$p		);			break;	\
												case 5:	$I=	 				*( (ui64* ) ( 	$p -3	) ) >>24;		break;	\
												case 6:	$I=	 				*( (ui64* ) (	$p -2	) ) >>16;		break;	\
												case 7:	$I=					*( (ui64* ) (	$p -1	) ) >>8;		break;	\
												case 8:	$I=	 				*( (ui64* ) 	$p		);			break;	}
#define CASTq2i_plus1inc( $I, $p, $q )		switch( $q){	case 0:	break;	\
												case 1:	$I+=	 	1+			*( (ui08* )	$p 		);			break;	\
												case 2:	$I+=		1+			*( (ui16* )	$p	 	);			break; 	\
												case 3:	$I+=	 	1+			*( (ui32* ) (	$p -1	) ) >>8;		break;	\
												case 4:	$I+=	 	1+			*( (ui32* )	$p		);			break;	\
												case 5:	$I+=	 	1+			*( (ui64* ) ( 	$p -3	) ) >>24;		break;	\
												case 6:	$I+=	 	1+			*( (ui64* ) (	$p -2	) ) >>16;		break;	\
												case 7:	$I+=		1+			*( (ui64* ) (	$p -1	) ) >>8;		break;	\
												case 8:	$I+=	 	1+			*( (ui64* ) 	$p		);			break;	}
#define CASTq2i_less1(	$I, $p, $q )		switch( $q){	case 0:	break;	\
												case 1:	$I=	 				*( (ui08* )	$p 		)		-1;       	break;	\
												case 2:	$I=					*( (ui16* )	$p	 	)		-1;       	break; 	\
												case 3:	$I=	 			(	*( (ui32* ) (	$p -1	) ) >>8	)-1;       	break;	\
												case 4:	$I=	 				*( (ui32* )	$p		)		-1;       	break;	\
												case 5:	$I=	 			(	*( (ui64* ) ( 	$p -3	) ) >>24	)-1;       	break;	\
												case 6:	$I=	 			(	*( (ui64* ) (	$p -2	) ) >>16	)-1;       	break;	\
												case 7:	$I=				(	*( (ui64* ) (	$p -1	) ) >>8	)-1;       	break;	\
												case 8:	$I=	 				*( (ui64* ) 	$p		)		-1;       	break;	}
#define CASTq2i_plus1(	$I, $p, $q )		switch( $q){	case 0:	break;	\
												case 1:	$I=	 	1+			*( (ui08* )	$p 		)		;       	break;	\
												case 2:	$I=		1+			*( (ui16* )	$p	 	)		;       	break; 	\
												case 3:	$I=	 	1+		(	*( (ui32* ) (	$p -1	) ) >>8	);       	break;	\
												case 4:	$I=	 	1+			*( (ui32* )	$p		)		;       	break;	\
												case 5:	$I=	 	1+		(	*( (ui64* ) ( 	$p -3	) ) >>24	);       	break;	\
												case 6:	$I=	 	1+		(	*( (ui64* ) (	$p -2	) ) >>16	);       	break;	\
												case 7:	$I=		1+		(	*( (ui64* ) (	$p -1	) ) >>8	);       	break;	\
												case 8:	$I=	 	1+			*( (ui64* ) 	$p		)		;       	break;	}
#define rCASTq2i(		$I, $p, $q )		switch( $q){	case 0:	break;	\
												case 1:	$I=	 				*( (ui08* ) (	$p -1	) );			break;	\
												case 2:	$I=					*( (ui16* ) (	$p -2 	) );			break; 	\
												case 3:	$I=	 				*( (ui32* ) (	$p -4	) ) >>8;		break;	\
												case 4:	$I=	 				*( (ui32* ) (	$p -4	) );			break;	\
												case 5:	$I=	 				*( (ui64* ) ( 	$p -8	) ) >>24;		break;	\
												case 6:	$I=	 				*( (ui64* ) (	$p -8	) ) >>16;		break;	\
												case 7:	$I=					*( (ui64* ) (	$p -8	) ) >>8;		break;	\
												case 8:	$I=	 				*( (ui64* ) (	$p -8	) );			break;	}

#define CASTq2p(		$p0, $p1, $q )		switch( $q){	case 0:	break;	\
												case 1:	*( (ui08* )	$p0 )=	*( (ui08* )	$p1 		);			break;	\
												case 2:	*( (ui16* )	$p0 )=	*( (ui16* )	$p1	 	);			break; 	\
												case 3:	*( (ui32* )	$p0 )=	*( (ui32* ) (	$p1 -1	) ) >>8;		break;	\
												case 4:	*( (ui32* )	$p0 )=	*( (ui32* )	$p1		);			break;	\
												case 5:	*( (ui64* )	$p0 )=	*( (ui64* ) ( 	$p1 -3	) ) >>24;		break;	\
												case 6:	*( (ui64* )	$p0 )=	*( (ui64* ) (	$p1 -2	) ) >>16;		break;	\
												case 7:	*( (ui64* )	$p0 )=	*( (ui64* ) (	$p1 -1	) ) >>8;		break;	\
												default:	*( (ui64* )	$p0 )=	*( (ui64* ) 	$p1		);			break;	}

#define SwCASE_LOWPASS_0IS(		$src 	)		/* "0IS" means 	switch case vector 0 starts at zero,
																and arg[0] is both the input and output variable, "In Situ".	*/	\
		case 0x00:												$src	 =0x0000000000000000; 					break;	\
		case 0x01:												$src &=0x00000000000000FF;					break;\
		case 0x02:												$src &=0x000000000000FFFF;					break;\
		case 0x03:												$src &=0x0000000000FFFFFF;					break;\
		case 0x04:												$src &=0x00000000FFFFFFFF;						break;\
		case 0x05:												$src &=0x000000FFFFFFFFFF;						break;\
		case 0x06:												$src &=0x0000FFFFFFFFFFFF;						break;\
		case 0x07:												$src &=0x00FFFFFFFFFFFFFF;							

#define SwCASE_LOWPASS_1IS(		$src )			/* "1IS" means 	switch case vector 0 starts at one,
																and arg[0] is both the input and output variable, "In Situ".	*/	\
		case 0x00:												$src &=0x00000000000000FF;					break;\
		case 0x01:												$src &=0x000000000000FFFF;					break;\
		case 0x02:												$src &=0x0000000000FFFFFF;					break;\
		case 0x03:												$src &=0x00000000FFFFFFFF;						break;\
		case 0x04:												$src &=0x000000FFFFFFFFFF;						break;\
		case 0x05:												$src &=0x0000FFFFFFFFFFFF;						break;\
		case 0x06:												$src &=0x00FFFFFFFFFFFFFF;						break;\
		case 0x07:																							

#define SwCASE_LOWPASS_0I( $src,	$dst )			/* "0I" means 	switch case vector 0 starts at zero,
																and arg[0] is both the input and output variable, "In Situ".	*/	\
		case 0x00:		$dst =										= 0x0000000000000000; 					break;	\
		case 0x01:		$dst =									$src & 0x00000000000000FF;					break;\
		case 0x02:		$dst =									$src & 0x000000000000FFFF;						break;\
		case 0x03:		$dst =									$src & 0x0000000000FFFFFF;			 			break;\
		case 0x04:		$dst =									$src & 0x00000000FFFFFFFF;						break;\
		case 0x05:		$dst =									$src & 0x000000FFFFFFFFFF;						break;\
		case 0x06:		$dst =									$src & 0x0000FFFFFFFFFFFF;						break;\
		case 0x07:		$dst =									$src & 0x00FFFFFFFFFFFFFF;							

#define SwCASE_LOWPASS_1I( $src,	$dst )			/* "1I" means 	switch case vector 0 starts at one,
																arg[0] is the input variable, and
																arg[1] is the output variable.							*/	\
		case 0x00:		$dst =									$src & 0x00000000000000FF;					break;\
		case 0x01:		$dst =									$src & 0x000000000000FFFF; 					break;\
		case 0x02:		$dst =									$src & 0x0000000000FFFFFF; 					break;\
		case 0x03:		$dst =									$src & 0x00000000FFFFFFFF;						break;\
		case 0x04:		$dst =									$src & 0x000000FFFFFFFFFF;						break;\
		case 0x05:		$dst =									$src & 0x0000FFFFFFFFFFFF;						break;\
		case 0x06:		$dst =									$src & 0x00FFFFFFFFFFFFFF;						break;\
		case 0x07:		$dst =									$src;										

#define SwCASE_XOVER_0T( $srcHi,	$src )			/* "0T" means	switch case vector 0 starts at zero,
																and arg[0] "Tees into" arg[1], which is also the output variable.	*/	\
		case 0x00:	$src = $srcHi;																					break;	\
		case 0x01:	tail	= $srcHi & 0xFFFFFFFFFFFFFF00;       	head =	$src	&0x00000000000000FF;		$src = head|tail;       	break;\
		case 0x02:	tail	= $srcHi & 0xFFFFFFFFFFFF0000;       	head =	$src	&0x000000000000FFFF;		$src = head|tail;       	break;\
		case 0x03:	tail	= $srcHi & 0xFFFFFFFFFF000000;       	head =	$src	&0x0000000000FFFFFF;		$src = head|tail;       	break;\
		case 0x04:	tail	= $srcHi & 0xFFFFFFFF00000000;       	head =	$src	&0x00000000FFFFFFFF;		$src = head|tail;       	break;\
		case 0x05:	tail	= $srcHi & 0xFFFFFF0000000000;       	head =	$src	&0x000000FFFFFFFFFF;		$src = head|tail;       	break;\
		case 0x06:	tail	= $srcHi & 0xFFFF000000000000;       	head =	$src	&0x0000FFFFFFFFFFFF;		$src = head|tail;       	break;\
		case 0x07:	tail	= $srcHi & 0xFF00000000000000;       	head =	$src	&0x00FFFFFFFFFFFFFF;		$src = head|tail; 		

#define SwCASE_XOVER_1T( $srcHi,	$src	)			/* "1T" means	switch case vector 0 starts at one,
																and arg[0] "Tees into" arg[1], which is also the output variable.	*/	\
		case 0x00:	tail	= $srcHi & 0xFFFFFFFFFFFFFF00;       	head =	$src	&0x00000000000000FF;		$src = head|tail;       	break;\
		case 0x01:	tail	= $srcHi & 0xFFFFFFFFFFFF0000;       	head =	$src	&0x000000000000FFFF;		$src = head|tail;       	break;\
		case 0x02:	tail	= $srcHi & 0xFFFFFFFFFF000000;       	head =	$src	&0x0000000000FFFFFF;		$src = head|tail;       	break;\
		case 0x03:	tail	= $srcHi & 0xFFFFFFFF00000000;       	head =	$src	&0x00000000FFFFFFFF;		$src = head|tail;       	break;\
		case 0x04:	tail	= $srcHi & 0xFFFFFF0000000000;       	head =	$src	&0x000000FFFFFFFFFF;		$src = head|tail;       	break;\
		case 0x05:	tail	= $srcHi & 0xFFFF000000000000;       	head =	$src	&0x0000FFFFFFFFFFFF;		$src = head|tail;       	break;\
		case 0x06:	tail	= $srcHi & 0xFF00000000000000;       	head =	$src	&0x00FFFFFFFFFFFFFF;		$src = head|tail;       	break;\
		case 0x07:																								break;\


#define SwCASE_XOVER_0Y( $srcHi,	$src, $out )		/* "0Y" means	switch case vector 0 starts at zero,
																and args[0..1] "Wye into" arg-2, which is the output variable.	*/	\
		case 0x00:	$out = $srcHi;																					break;	\
		case 0x01:	tail	= $srcHi & 0xFFFFFFFFFFFFFF00;       	head =	$src	&0x00000000000000FF;		$out = head|tail;       	break;\
		case 0x02:	tail	= $srcHi & 0xFFFFFFFFFFFF0000;       	head =	$src	&0x000000000000FFFF;		$out = head|tail;       	break;\
		case 0x03:	tail	= $srcHi & 0xFFFFFFFFFF000000;       	head =	$src	&0x0000000000FFFFFF;		$out = head|tail;       	break;\
		case 0x04:	tail	= $srcHi & 0xFFFFFFFF00000000;       	head =	$src	&0x00000000FFFFFFFF;		$out = head|tail;       	break;\
		case 0x05:	tail	= $srcHi & 0xFFFFFF0000000000;       	head =	$src	&0x000000FFFFFFFFFF;		$out = head|tail;       	break;\
		case 0x06:	tail	= $srcHi & 0xFFFF000000000000;       	head =	$src	&0x0000FFFFFFFFFFFF;		$out = head|tail;       	break;\
		case 0x07:	tail	= $srcHi & 0xFF00000000000000;       	head =	$src	&0x00FFFFFFFFFFFFFF;		$out = head|tail;  		break;\
		case 0x08:																			$out = $src;

#define SwCASE_XOVER_1Y( $srcHi,	$src, $out )		/* "1Y" means	switch case vector 0 starts at one,
																and args[0..1] "Wye into" arg[2], which is the output variable.	*/	\
		case 0x00:	tail	= $srcHi & 0xFFFFFFFFFFFFFF00;       	head =	$src	&0x00000000000000FF;		$out = head|tail;       	break;\
		case 0x01:	tail	= $srcHi & 0xFFFFFFFFFFFF0000;       	head =	$src	&0x000000000000FFFF;		$out = head|tail;       	break;\
		case 0x02:	tail	= $srcHi & 0xFFFFFFFFFF000000;       	head =	$src	&0x0000000000FFFFFF;		$out = head|tail;       	break;\
		case 0x03:	tail	= $srcHi & 0xFFFFFFFF00000000;       	head =	$src	&0x00000000FFFFFFFF;		$out = head|tail;       	break;\
		case 0x04:	tail	= $srcHi & 0xFFFFFF0000000000;       	head =	$src	&0x000000FFFFFFFFFF;		$out = head|tail;       	break;\
		case 0x05:	tail	= $srcHi & 0xFFFF000000000000;       	head =	$src	&0x0000FFFFFFFFFFFF;		$out = head|tail;       	break;\
		case 0x06:	tail	= $srcHi & 0xFF00000000000000;       	head =	$src	&0x00FFFFFFFFFFFFFF;		$out = head|tail;       	break;\
		case 0x07:										$out=	$src;											




#define SwCASE_LPXOVER_00T( $srcHi,	$src )		/* "00T" means	switch case vector 0 starts at zero,
																switch case vector 1 starts at zero as well,
																and arg[0] "Tees into" arg[1], which is also the output variable.	*/	\
/* 0x0 */	case 0x00:										$src =			0x0000000000000000;															break;\
/* 0x1 */	case 0x01:																			$src &=		0x00000000000000FF;							break;\
/* 0x2 */	case 0x02:																			$src &=		0x000000000000FFFF;							break;\
/* 0x3 */	case 0x03:																			$src &=		0x0000000000FFFFFF;							break;\
/* 0x4 */	case 0x04:																			$src &=		0x00000000FFFFFFFF;							break;\
/* 0x5 */	case 0x05:																			$src &=		0x000000FFFFFFFFFF;							break;\
/* 0x6 */	case 0x06:																			$src &=		0x0000FFFFFFFFFFFF;							break;\
/* 0x7 */	case 0x07:																			$src &=		0x00FFFFFFFFFFFFFF;							break;\
\
/* 1x0 */	case 0x08:										$src =	$srcHi &	0x00000000000000FF;															break;\
/* 1x1 */	case 0x09:										body =	$srcHi &	0x000000000000FF00;	head = $src &	0x00000000000000FF;		$src =head|	body;	break;\
/* 1x2 */	case 0x0A:										body =	$srcHi &	0x0000000000FF0000;	head = $src &	0x000000000000FFFF;		$src =head|	body;	break;\
/* 1x3 */	case 0x0B:										body =	$srcHi &	0x00000000FF000000;	head = $src &	0x0000000000FFFFFF;		$src =head|	body;	break;\
/* 1x4 */	case 0x0C:										body =	$srcHi &	0x000000FF00000000;	head = $src &	0x00000000FFFFFFFF;		$src =head|	body;	break;\
/* 1x5 */	case 0x0D:										body =	$srcHi &	0x0000FF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$src =head|	body;	break;\
/* 1x6 */	case 0x0E:										body =	$srcHi &	0x00FF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$src =head|	body;	break;\
/* 1x7 */	case 0x0F:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$src =head|	body;	break;\
\
/* 2x0 */	case 0x10:										$src =	$srcHi &	0x000000000000FFFF;															break;\
/* 2x1 */	case 0x11:										body =	$srcHi &	0x0000000000FFFF00;	head = $src &	0x00000000000000FF;		$src =head|	body;	break;\
/* 2x2 */	case 0x12:										body =	$srcHi &	0x00000000FFFF0000;	head = $src &	0x000000000000FFFF;		$src =head|	body;	break;\
/* 2x3 */	case 0x13:										body =	$srcHi &	0x000000FFFF000000;	head = $src &	0x0000000000FFFFFF;		$src =head|	body;	break;\
/* 2x4 */	case 0x14:										body =	$srcHi &	0x0000FFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$src =head|	body;	break;\
/* 2x5 */	case 0x15:										body =	$srcHi &	0x00FFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$src =head|	body;	break;\
/* 2x6 */	case 0x16:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$src =head|	body;	break;\
/* 2x7 */	case 0x17:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$src =head|	body;	break;\
\
/* 3x0 */	case 0x18:										$src =	$srcHi &	0x0000000000FFFFFF;															break;\
/* 3x1 */	case 0x19:										body =	$srcHi &	0x00000000FFFFFF00;	head = $src &	0x00000000000000FF;		$src =head|	body;	break;\
/* 3x2 */	case 0x1A:										body =	$srcHi &	0x000000FFFFFF0000;	head = $src &	0x000000000000FFFF;		$src =head|	body;	break;\
/* 3x3 */	case 0x1B:										body =	$srcHi &	0x0000FFFFFF000000;	head = $src &	0x0000000000FFFFFF;		$src =head|	body;	break;\
/* 3x4 */	case 0x1C:										body =	$srcHi &	0x00FFFFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$src =head|	body;	break;\
/* 3x5 */	case 0x1D:										body =	$srcHi &	0xFFFFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$src =head|	body;	break;\
/* 3x6 */	case 0x1E:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$src =head|	body;	break;\
/* 3x7 */	case 0x1F:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$src =head|	body;	break;\
\
/* 4x0 */	case 0x20:										$src =	$srcHi &	0x00000000FFFFFFFF;															break;\
/* 4x1 */	case 0x21:										body =	$srcHi &	0x000000FFFFFFFF00;	head = $src &	0x00000000000000FF;		$src =head|	body;	break;\
/* 4x2 */	case 0x22:										body =	$srcHi &	0x0000FFFFFFFF0000;	head = $src &	0x000000000000FFFF;		$src =head|	body;	break;\
/* 4x3 */	case 0x23:										body =	$srcHi &	0x00FFFFFFFF000000;	head = $src &	0x0000000000FFFFFF;		$src =head|	body;	break;\
/* 4x4 */	case 0x24:										body =	$srcHi &	0xFFFFFFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$src =head|	body;	break;\
/* 4x5 */	case 0x25:										body =	$srcHi &	0xFFFFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$src =head|	body;	break;\
/* 4x6 */	case 0x26:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$src =head|	body;	break;\
/* 4x7 */	case 0x27:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$src =head|	body;	break;\
\
/* 5x0 */	case 0x28:										$src =	$srcHi &	0x000000FFFFFFFFFF;															break;\
/* 5x1 */	case 0x29:										body =	$srcHi &	0x0000FFFFFFFFFF00;	head = $src &	0x00000000000000FF;		$src =head|	body;	break;\
/* 5x2 */	case 0x2A:										body =	$srcHi &	0x00FFFFFFFFFF0000;	head = $src &	0x000000000000FFFF;		$src =head|	body;	break;\
/* 5x3 */	case 0x2B:										body =	$srcHi &	0xFFFFFFFFFF000000;	head = $src &	0x0000000000FFFFFF;		$src =head|	body;	break;\
/* 5x4 */	case 0x2C:										body =	$srcHi &	0xFFFFFFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$src =head|	body;	break;\
/* 5x5 */	case 0x2D:										body =	$srcHi &	0xFFFFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$src =head|	body;	break;\
/* 5x6 */	case 0x2E:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$src =head|	body;	break;\
/* 5x7 */	case 0x2F:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$src =head|	body;	break;\
\
/* 6x0 */	case 0x30:										$src =	$srcHi &	0x0000FFFFFFFFFFFF;															break;\
/* 6x1 */	case 0x31:										body =	$srcHi &	0x00FFFFFFFFFFFF00;	head = $src &	0x00000000000000FF;		$src =head|	body;	break;\
/* 6x2 */	case 0x32:										body =	$srcHi &	0xFFFFFFFFFFFF0000;	head = $src &	0x000000000000FFFF;		$src =head|	body;	break;\
/* 6x3 */	case 0x33:										body =	$srcHi &	0xFFFFFFFFFF000000;	head = $src &	0x0000000000FFFFFF;		$src =head|	body;	break;\
/* 6x4 */	case 0x34:										body =	$srcHi &	0xFFFFFFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$src =head|	body;	break;\
/* 6x5 */	case 0x35:										body =	$srcHi &	0xFFFFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$src =head|	body;	break;\
/* 6x6 */	case 0x36:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$src =head|	body;	break;\
/* 6x7 */	case 0x37:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$src =head|	body;	break;\
\
/* 7x0 */	case 0x38:										$src =	$srcHi &	0x00FFFFFFFFFFFFFF;															break;\
/* 7x1 */	case 0x39:										body =	$srcHi &	0xFFFFFFFFFFFFFF00;	head = $src &	0x00000000000000FF;		$src =head|	body;	break;\
/* 7x2 */	case 0x3A:										body =	$srcHi &	0xFFFFFFFFFFFF0000;	head = $src &	0x000000000000FFFF;		$src =head|	body;	break;\
/* 7x3 */	case 0x3B:										body =	$srcHi &	0xFFFFFFFFFF000000;	head = $src &	0x0000000000FFFFFF;		$src =head|	body;	break;\
/* 7x4 */	case 0x3C:										body =	$srcHi &	0xFFFFFFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$src =head|	body;	break;\
/* 7x5 */	case 0x3D:										body =	$srcHi &	0xFFFFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$src =head|	body;	break;\
/* 7x6 */	case 0x3E:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$src =head|	body;	break;\
/* 7x7 */	case 0x3F:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$src =head|	body;	
/*					^ there is no tail						^ isolate high octets					^ isolate low octets						^ rejoin				*/

#define SwCASE_LPXOVER_01T( $srcHi,	$src )		/* "01T" means	switch case vector 0 starts at zero,
																switch case vector 1 starts at one,
																and arg[0] "Tees into" arg[1], which is also the output variable.	*/	\
/* 0x0 */	case 0x00:										$src =	$srcHi &	0x00000000000000FF;															break;\
/* 0x1 */	case 0x01:										body =	$srcHi &	0x000000000000FF00;	head = $src &	0x00000000000000FF;		$src =head|	body;	break;\
/* 0x2 */	case 0x02:										body =	$srcHi &	0x0000000000FF0000;	head = $src &	0x000000000000FFFF;		$src =head|	body;	break;\
/* 0x3 */	case 0x03:										body =	$srcHi &	0x00000000FF000000;	head = $src &	0x0000000000FFFFFF;		$src =head|	body;	break;\
/* 0x4 */	case 0x04:										body =	$srcHi &	0x000000FF00000000;	head = $src &	0x00000000FFFFFFFF;		$src =head|	body;	break;\
/* 0x5 */	case 0x05:										body =	$srcHi &	0x0000FF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$src =head|	body;	break;\
/* 0x6 */	case 0x06:										body =	$srcHi &	0x00FF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$src =head|	body;	break;\
/* 0x7 */	case 0x07:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$src =head|	body;	break;\
\
/* 1x0 */	case 0x08:										$src =	$srcHi &	0x000000000000FFFF;															break;\
/* 1x1 */	case 0x09:										body =	$srcHi &	0x0000000000FFFF00;	head = $src &	0x00000000000000FF;		$src =head|	body;	break;\
/* 1x2 */	case 0x0A:										body =	$srcHi &	0x00000000FFFF0000;	head = $src &	0x000000000000FFFF;		$src =head|	body;	break;\
/* 1x3 */	case 0x0B:										body =	$srcHi &	0x000000FFFF000000;	head = $src &	0x0000000000FFFFFF;		$src =head|	body;	break;\
/* 1x4 */	case 0x0C:										body =	$srcHi &	0x0000FFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$src =head|	body;	break;\
/* 1x5 */	case 0x0D:										body =	$srcHi &	0x00FFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$src =head|	body;	break;\
/* 1x6 */	case 0x0E:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$src =head|	body;	break;\
/* 1x7 */	case 0x0F:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$src =head|	body;	break;\
\
/* 2x0 */	case 0x10:										$src =	$srcHi &	0x0000000000FFFFFF;															break;\
/* 2x1 */	case 0x11:										body =	$srcHi &	0x00000000FFFFFF00;	head = $src &	0x00000000000000FF;		$src =head|	body;	break;\
/* 2x2 */	case 0x12:										body =	$srcHi &	0x000000FFFFFF0000;	head = $src &	0x000000000000FFFF;		$src =head|	body;	break;\
/* 2x3 */	case 0x13:										body =	$srcHi &	0x0000FFFFFF000000;	head = $src &	0x0000000000FFFFFF;		$src =head|	body;	break;\
/* 2x4 */	case 0x14:										body =	$srcHi &	0x00FFFFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$src =head|	body;	break;\
/* 2x5 */	case 0x15:										body =	$srcHi &	0xFFFFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$src =head|	body;	break;\
/* 2x6 */	case 0x16:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$src =head|	body;	break;\
/* 2x7 */	case 0x17:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$src =head|	body;	break;\
\
/* 3x0 */	case 0x18:										$src =	$srcHi &	0x00000000FFFFFFFF;															break;\
/* 3x1 */	case 0x19:										body =	$srcHi &	0x000000FFFFFFFF00;	head = $src &	0x00000000000000FF;		$src =head|	body;	break;\
/* 3x2 */	case 0x1A:										body =	$srcHi &	0x0000FFFFFFFF0000;	head = $src &	0x000000000000FFFF;		$src =head|	body;	break;\
/* 3x3 */	case 0x1B:										body =	$srcHi &	0x00FFFFFFFF000000;	head = $src &	0x0000000000FFFFFF;		$src =head|	body;	break;\
/* 3x4 */	case 0x1C:										body =	$srcHi &	0xFFFFFFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$src =head|	body;	break;\
/* 3x5 */	case 0x1D:										body =	$srcHi &	0xFFFFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$src =head|	body;	break;\
/* 3x6 */	case 0x1E:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$src =head|	body;	break;\
/* 3x7 */	case 0x1F:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$src =head|	body;	break;\
\
/* 4x0 */	case 0x20:										$src =	$srcHi &	0x000000FFFFFFFFFF;															break;\
/* 4x1 */	case 0x21:										body =	$srcHi &	0x0000FFFFFFFFFF00;	head = $src &	0x00000000000000FF;		$src =head|	body;	break;\
/* 4x2 */	case 0x22:										body =	$srcHi &	0x00FFFFFFFFFF0000;	head = $src &	0x000000000000FFFF;		$src =head|	body;	break;\
/* 4x3 */	case 0x23:										body =	$srcHi &	0xFFFFFFFFFF000000;	head = $src &	0x0000000000FFFFFF;		$src =head|	body;	break;\
/* 4x4 */	case 0x24:										body =	$srcHi &	0xFFFFFFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$src =head|	body;	break;\
/* 4x5 */	case 0x25:										body =	$srcHi &	0xFFFFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$src =head|	body;	break;\
/* 4x6 */	case 0x26:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$src =head|	body;	break;\
/* 4x7 */	case 0x27:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$src =head|	body;	break;\
\
/* 5x0 */	case 0x28:										$src =	$srcHi &	0x0000FFFFFFFFFFFF;															break;\
/* 5x1 */	case 0x29:										body =	$srcHi &	0x00FFFFFFFFFFFF00;	head = $src &	0x00000000000000FF;		$src =head|	body;	break;\
/* 5x2 */	case 0x2A:										body =	$srcHi &	0xFFFFFFFFFFFF0000;	head = $src &	0x000000000000FFFF;		$src =head|	body;	break;\
/* 5x3 */	case 0x2B:										body =	$srcHi &	0xFFFFFFFFFF000000;	head = $src &	0x0000000000FFFFFF;		$src =head|	body;	break;\
/* 5x4 */	case 0x2C:										body =	$srcHi &	0xFFFFFFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$src =head|	body;	break;\
/* 5x5 */	case 0x2D:										body =	$srcHi &	0xFFFFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$src =head|	body;	break;\
/* 5x6 */	case 0x2E:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$src =head|	body;	break;\
/* 5x7 */	case 0x2F:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$src =head|	body;	break;\
\
/* 6x0 */	case 0x30:										$src =	$srcHi &	0x00FFFFFFFFFFFFFF;															break;\
/* 6x1 */	case 0x31:										body =	$srcHi &	0xFFFFFFFFFFFFFF00;	head = $src &	0x00000000000000FF;		$src =head|	body;	break;\
/* 6x2 */	case 0x32:										body =	$srcHi &	0xFFFFFFFFFFFF0000;	head = $src &	0x000000000000FFFF;		$src =head|	body;	break;\
/* 6x3 */	case 0x33:										body =	$srcHi &	0xFFFFFFFFFF000000;	head = $src &	0x0000000000FFFFFF;		$src =head|	body;	break;\
/* 6x4 */	case 0x34:										body =	$srcHi &	0xFFFFFFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$src =head|	body;	break;\
/* 6x5 */	case 0x35:										body =	$srcHi &	0xFFFFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$src =head|	body;	break;\
/* 6x6 */	case 0x36:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$src =head|	body;	break;\
/* 6x7 */	case 0x37:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$src =head|	body;	break;\
\
/* 7x0 */	case 0x38:										$src = $srcHi;																					break;\
/* 7x1 */	case 0x39:										body =	$srcHi &	0xFFFFFFFFFFFFFF00;	head = $src &	0x00000000000000FF;		$src =head|	body;	break;\
/* 7x2 */	case 0x3A:										body =	$srcHi &	0xFFFFFFFFFFFF0000;	head = $src &	0x000000000000FFFF;		$src =head|	body;	break;\
/* 7x3 */	case 0x3B:										body =	$srcHi &	0xFFFFFFFFFF000000;	head = $src &	0x0000000000FFFFFF;		$src =head|	body;	break;\
/* 7x4 */	case 0x3C:										body =	$srcHi &	0xFFFFFFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$src =head|	body;	break;\
/* 7x5 */	case 0x3D:										body =	$srcHi &	0xFFFFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$src =head|	body;	break;\
/* 7x6 */	case 0x3E:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$src =head|	body;	break;\
/* 7x7 */	case 0x3F:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$src =head|	body;		
/*					^ there is no tail						^ isolate high octets					^ isolate low octets						^ rejoin				*/


#define SwCASE_LPXOVER_10T( $srcHi,	$src )		/* "10T" means	switch case vector 0 starts at one,
																switch case vector 1 starts at zero,
																and arg[0] "Tees into" arg[1], which is also the output variable.	*/	\
\
/* 0x0 */	case 0x00:																			$src &=		0x00000000000000FF;							break;\
/* 0x1 */	case 0x01:																			$src &=		0x000000000000FFFF;							break;\
/* 0x2 */	case 0x02:																			$src &=		0x0000000000FFFFFF;							break;\
/* 0x3 */	case 0x03:																			$src &=		0x00000000FFFFFFFF;							break;\
/* 0x4 */	case 0x04:																			$src &=		0x000000FFFFFFFFFF;							break;\
/* 0x5 */	case 0x05:																			$src &=		0x0000FFFFFFFFFFFF;							break;\
/* 0x6 */	case 0x06:																			$src &=		0x00FFFFFFFFFFFFFF;							break;\
/* 0x7 */	case 0x07:										/*				0x0000000000000000				0xFFFFFFFFFFFFFFFF			*/					break;\
\
/* 1x0 */	case 0x08:										body =	$srcHi &	0x000000000000FF00;	head = $src &	0x00000000000000FF;		$src =head|	body;	break;\
/* 1x1 */	case 0x09:										body =	$srcHi &	0x0000000000FF0000;	head = $src &	0x000000000000FFFF;		$src =head|	body;	break;\
/* 1x2 */	case 0x0A:										body =	$srcHi &	0x00000000FF000000;	head = $src &	0x0000000000FFFFFF;		$src =head|	body;	break;\
/* 1x3 */	case 0x0B:										body =	$srcHi &	0x000000FF00000000;	head = $src &	0x00000000FFFFFFFF;		$src =head|	body;	break;\
/* 1x4 */	case 0x0C:										body =	$srcHi &	0x0000FF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$src =head|	body;	break;\
/* 1x5 */	case 0x0D:										body =	$srcHi &	0x00FF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$src =head|	body;	break;\
/* 1x6 */	case 0x0E:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$src =head|	body;	break;\
/* 1x7 */	case 0x0F:										/*				0x0000000000000000				0xFFFFFFFFFFFFFFFF			*/					break;\
\
/* 2x0 */	case 0x10:										body =	$srcHi &	0x0000000000FFFF00;	head = $src &	0x00000000000000FF;		$src =head|	body;	break;\
/* 2x1 */	case 0x11:										body =	$srcHi &	0x00000000FFFF0000;	head = $src &	0x000000000000FFFF;		$src =head|	body;	break;\
/* 2x2 */	case 0x12:										body =	$srcHi &	0x000000FFFF000000;	head = $src &	0x0000000000FFFFFF;		$src =head|	body;	break;\
/* 2x3 */	case 0x13:										body =	$srcHi &	0x0000FFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$src =head|	body;	break;\
/* 2x4 */	case 0x14:										body =	$srcHi &	0x00FFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$src =head|	body;	break;\
/* 2x5 */	case 0x15:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$src =head|	body;	break;\
/* 2x6 */	case 0x16:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$src =head|	body;	break;\
/* 2x7 */	case 0x17:										/*				0x0000000000000000				0xFFFFFFFFFFFFFFFF			*/					break;\
\
/* 3x0 */	case 0x18:										body =	$srcHi &	0x00000000FFFFFF00;	head = $src &	0x00000000000000FF;		$src =head|	body;	break;\
/* 3x1 */	case 0x19:										body =	$srcHi &	0x000000FFFFFF0000;	head = $src &	0x000000000000FFFF;		$src =head|	body;	break;\
/* 3x2 */	case 0x1A:										body =	$srcHi &	0x0000FFFFFF000000;	head = $src &	0x0000000000FFFFFF;		$src =head|	body;	break;\
/* 3x3 */	case 0x1B:										body =	$srcHi &	0x00FFFFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$src =head|	body;	break;\
/* 3x4 */	case 0x1C:										body =	$srcHi &	0xFFFFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$src =head|	body;	break;\
/* 3x5 */	case 0x1D:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$src =head|	body;	break;\
/* 3x6 */	case 0x1E:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$src =head|	body;	break;\
/* 3x7 */	case 0x1F:										/*				0x0000000000000000				0xFFFFFFFFFFFFFFFF			*/					break;\
\
/* 4x0 */	case 0x20:										body =	$srcHi &	0x000000FFFFFFFF00;	head = $src &	0x00000000000000FF;		$src =head|	body;	break;\
/* 4x1 */	case 0x21:										body =	$srcHi &	0x0000FFFFFFFF0000;	head = $src &	0x000000000000FFFF;		$src =head|	body;	break;\
/* 4x2 */	case 0x22:										body =	$srcHi &	0x00FFFFFFFF000000;	head = $src &	0x0000000000FFFFFF;		$src =head|	body;	break;\
/* 4x3 */	case 0x23:										body =	$srcHi &	0xFFFFFFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$src =head|	body;	break;\
/* 4x4 */	case 0x24:										body =	$srcHi &	0xFFFFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$src =head|	body;	break;\
/* 4x5 */	case 0x25:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$src =head|	body;	break;\
/* 4x6 */	case 0x26:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$src =head|	body;	break;\
/* 4x7 */	case 0x27:										/*				0x0000000000000000				0xFFFFFFFFFFFFFFFF			*/					break;\
\
/* 5x0 */	case 0x28:										body =	$srcHi &	0x0000FFFFFFFFFF00;	head = $src &	0x00000000000000FF;		$src =head|	body;	break;\
/* 5x1 */	case 0x29:										body =	$srcHi &	0x00FFFFFFFFFF0000;	head = $src &	0x000000000000FFFF;		$src =head|	body;	break;\
/* 5x2 */	case 0x2A:										body =	$srcHi &	0xFFFFFFFFFF000000;	head = $src &	0x0000000000FFFFFF;		$src =head|	body;	break;\
/* 5x3 */	case 0x2B:										body =	$srcHi &	0xFFFFFFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$src =head|	body;	break;\
/* 5x4 */	case 0x2C:										body =	$srcHi &	0xFFFFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$src =head|	body;	break;\
/* 5x5 */	case 0x2D:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$src =head|	body;	break;\
/* 5x6 */	case 0x2E:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$src =head|	body;	break;\
/* 5x7 */	case 0x2F:										/*				0x0000000000000000				0xFFFFFFFFFFFFFFFF			*/					break;\
\
/* 6x0 */	case 0x30:										body =	$srcHi &	0x00FFFFFFFFFFFF00;	head = $src &	0x00000000000000FF;		$src =head|	body;	break;\
/* 6x1 */	case 0x31:										body =	$srcHi &	0xFFFFFFFFFFFF0000;	head = $src &	0x000000000000FFFF;		$src =head|	body;	break;\
/* 6x2 */	case 0x32:										body =	$srcHi &	0xFFFFFFFFFF000000;	head = $src &	0x0000000000FFFFFF;		$src =head|	body;	break;\
/* 6x3 */	case 0x33:										body =	$srcHi &	0xFFFFFFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$src =head|	body;	break;\
/* 6x4 */	case 0x34:										body =	$srcHi &	0xFFFFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$src =head|	body;	break;\
/* 6x5 */	case 0x35:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$src =head|	body;	break;\
/* 6x6 */	case 0x36:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$src =head|	body;	break;\
/* 6x7 */	case 0x37:										/*				0x0000000000000000				0xFFFFFFFFFFFFFFFF			*/					break;\
\
/* 7x0 */	case 0x38:										body =	$srcHi &	0xFFFFFFFFFFFFFF00;	head = $src &	0x00000000000000FF;		$src =head|	body;	break;\
/* 7x1 */	case 0x39:										body =	$srcHi &	0xFFFFFFFFFFFF0000;	head = $src &	0x000000000000FFFF;		$src =head|	body;	break;\
/* 7x2 */	case 0x3A:										body =	$srcHi &	0xFFFFFFFFFF000000;	head = $src &	0x0000000000FFFFFF;		$src =head|	body;	break;\
/* 7x3 */	case 0x3B:										body =	$srcHi &	0xFFFFFFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$src =head|	body;	break;\
/* 7x4 */	case 0x3C:										body =	$srcHi &	0xFFFFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$src =head|	body;	break;\
/* 7x5 */	case 0x3D:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$src =head|	body;	break;\
/* 7x6 */	case 0x3E:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$src =head|	body;	break;\
/* 7x7 */	case 0x3F:										/*				0x0000000000000000				0xFFFFFFFFFFFFFFFF			*/					
/*					^ there is no tail						^ isolate high octets					^ isolate low octets						^ rejoin				*/


#define SwCASE_LPXOVER_10Y( $srcHi, $src, $out )		/* "10Y" means	switch case vector 0 starts at one,
																switch case vector 1 starts at zero,
																and args[0..1] "Wye into" arg-2, which is the output variable.	*/	\
\
/* 0x0 */	case 0x00:																			$out = $src &	0x00000000000000FF;							break;\
/* 0x1 */	case 0x01:																			$out = $src &	0x000000000000FFFF;							break;\
/* 0x2 */	case 0x02:																			$out = $src &	0x0000000000FFFFFF;							break;\
/* 0x3 */	case 0x03:																			$out = $src &	0x00000000FFFFFFFF;							break;\
/* 0x4 */	case 0x04:																			$out = $src &	0x000000FFFFFFFFFF;							break;\
/* 0x5 */	case 0x05:																			$out = $src &	0x0000FFFFFFFFFFFF;							break;\
/* 0x6 */	case 0x06:																			$out = $src &	0x00FFFFFFFFFFFFFF;							break;\
/* 0x7 */	case 0x07:																			$out = $src;												break;\
\
/* 1x0 */	case 0x08:										body =	$srcHi &	0x000000000000FF00;	head = $src &	0x00000000000000FF;		$out =head|	body;	break;\
/* 1x1 */	case 0x09:										body =	$srcHi &	0x0000000000FF0000;	head = $src &	0x000000000000FFFF;		$out =head|	body;	break;\
/* 1x2 */	case 0x0A:										body =	$srcHi &	0x00000000FF000000;	head = $src &	0x0000000000FFFFFF;		$out =head|	body;	break;\
/* 1x3 */	case 0x0B:										body =	$srcHi &	0x000000FF00000000;	head = $src &	0x00000000FFFFFFFF;		$out =head|	body;	break;\
/* 1x4 */	case 0x0C:										body =	$srcHi &	0x0000FF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$out =head|	body;	break;\
/* 1x5 */	case 0x0D:										body =	$srcHi &	0x00FF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$out =head|	body;	break;\
/* 1x6 */	case 0x0E:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$out =head|	body;	break;\
/* 1x7 */	case 0x0F:																			$out = $src;												break;\
\
/* 2x0 */	case 0x10:										body =	$srcHi &	0x0000000000FFFF00;	head = $src &	0x00000000000000FF;		$out =head|	body;	break;\
/* 2x1 */	case 0x11:										body =	$srcHi &	0x00000000FFFF0000;	head = $src &	0x000000000000FFFF;		$out =head|	body;	break;\
/* 2x2 */	case 0x12:										body =	$srcHi &	0x000000FFFF000000;	head = $src &	0x0000000000FFFFFF;		$out =head|	body;	break;\
/* 2x3 */	case 0x13:										body =	$srcHi &	0x0000FFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$out =head|	body;	break;\
/* 2x4 */	case 0x14:										body =	$srcHi &	0x00FFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$out =head|	body;	break;\
/* 2x5 */	case 0x15:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$out =head|	body;	break;\
/* 2x6 */	case 0x16:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$out =head|	body;	break;\
/* 2x7 */	case 0x17:																			$out = $src;												break;\
\
/* 3x0 */	case 0x18:										body =	$srcHi &	0x00000000FFFFFF00;	head = $src &	0x00000000000000FF;		$out =head|	body;	break;\
/* 3x1 */	case 0x19:										body =	$srcHi &	0x000000FFFFFF0000;	head = $src &	0x000000000000FFFF;		$out =head|	body;	break;\
/* 3x2 */	case 0x1A:										body =	$srcHi &	0x0000FFFFFF000000;	head = $src &	0x0000000000FFFFFF;		$out =head|	body;	break;\
/* 3x3 */	case 0x1B:										body =	$srcHi &	0x00FFFFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$out =head|	body;	break;\
/* 3x4 */	case 0x1C:										body =	$srcHi &	0xFFFFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$out =head|	body;	break;\
/* 3x5 */	case 0x1D:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$out =head|	body;	break;\
/* 3x6 */	case 0x1E:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$out =head|	body;	break;\
/* 3x7 */	case 0x1F:																			$out = $src;												break;\
\
/* 4x0 */	case 0x20:										body =	$srcHi &	0x000000FFFFFFFF00;	head = $src &	0x00000000000000FF;		$out =head|	body;	break;\
/* 4x1 */	case 0x21:										body =	$srcHi &	0x0000FFFFFFFF0000;	head = $src &	0x000000000000FFFF;		$out =head|	body;	break;\
/* 4x2 */	case 0x22:										body =	$srcHi &	0x00FFFFFFFF000000;	head = $src &	0x0000000000FFFFFF;		$out =head|	body;	break;\
/* 4x3 */	case 0x23:										body =	$srcHi &	0xFFFFFFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$out =head|	body;	break;\
/* 4x4 */	case 0x24:										body =	$srcHi &	0xFFFFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$out =head|	body;	break;\
/* 4x5 */	case 0x25:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$out =head|	body;	break;\
/* 4x6 */	case 0x26:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$out =head|	body;	break;\
/* 4x7 */	case 0x27:																			$out = $src;												break;\
\
/* 5x0 */	case 0x28:										body =	$srcHi &	0x0000FFFFFFFFFF00;	head = $src &	0x00000000000000FF;		$out =head|	body;	break;\
/* 5x1 */	case 0x29:										body =	$srcHi &	0x00FFFFFFFFFF0000;	head = $src &	0x000000000000FFFF;		$out =head|	body;	break;\
/* 5x2 */	case 0x2A:										body =	$srcHi &	0xFFFFFFFFFF000000;	head = $src &	0x0000000000FFFFFF;		$out =head|	body;	break;\
/* 5x3 */	case 0x2B:										body =	$srcHi &	0xFFFFFFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$out =head|	body;	break;\
/* 5x4 */	case 0x2C:										body =	$srcHi &	0xFFFFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$out =head|	body;	break;\
/* 5x5 */	case 0x2D:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$out =head|	body;	break;\
/* 5x6 */	case 0x2E:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$out =head|	body;	break;\
/* 5x7 */	case 0x2F:																			$out = $src;												break;\
\
/* 6x0 */	case 0x30:										body =	$srcHi &	0x00FFFFFFFFFFFF00;	head = $src &	0x00000000000000FF;		$out =head|	body;	break;\
/* 6x1 */	case 0x31:										body =	$srcHi &	0xFFFFFFFFFFFF0000;	head = $src &	0x000000000000FFFF;		$out =head|	body;	break;\
/* 6x2 */	case 0x32:										body =	$srcHi &	0xFFFFFFFFFF000000;	head = $src &	0x0000000000FFFFFF;		$out =head|	body;	break;\
/* 6x3 */	case 0x33:										body =	$srcHi &	0xFFFFFFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$out =head|	body;	break;\
/* 6x4 */	case 0x34:										body =	$srcHi &	0xFFFFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$out =head|	body;	break;\
/* 6x5 */	case 0x35:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$out =head|	body;	break;\
/* 6x6 */	case 0x36:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$out =head|	body;	break;\
/* 6x7 */	case 0x37:																			$out = $src;												break;\
\
/* 7x0 */	case 0x38:										body =	$srcHi &	0xFFFFFFFFFFFFFF00;	head = $src &	0x00000000000000FF;		$out =head|	body;	break;\
/* 7x1 */	case 0x39:										body =	$srcHi &	0xFFFFFFFFFFFF0000;	head = $src &	0x000000000000FFFF;		$out =head|	body;	break;\
/* 7x2 */	case 0x3A:										body =	$srcHi &	0xFFFFFFFFFF000000;	head = $src &	0x0000000000FFFFFF;		$out =head|	body;	break;\
/* 7x3 */	case 0x3B:										body =	$srcHi &	0xFFFFFFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$out =head|	body;	break;\
/* 7x4 */	case 0x3C:										body =	$srcHi &	0xFFFFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$out =head|	body;	break;\
/* 7x5 */	case 0x3D:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$out =head|	body;	break;\
/* 7x6 */	case 0x3E:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$out =head|	body;	break;\
/* 7x7 */	case 0x3F:																			$out = $src;												
/*					^ there is no tail						^ isolate high octets					^ isolate low octets						^ rejoin				*/



#define SwCASE_LPXOVER_10Yabs( $srcHi, $src, $out )	/* "10Yabs" means	switch case vector 0 starts at one,
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
/* 0x7 */	case 0x07:																			$out = $src &	0x00000000000000FF;							break;\
\
/* 1x0 */	case 0x08:										body =	$srcHi &	0x000000000000FF00;	head = $src &	0x00000000000000FF;		$out =head|	body;	break;\
/* 1x1 */	case 0x09:	\
/* 1x2 */	case 0x0A:	\
/* 1x3 */	case 0x0B:	\
/* 1x4 */	case 0x0C:	\
/* 1x5 */	case 0x0D:	\
/* 1x6 */	case 0x0E:	\
/* 1x7 */	case 0x0F:																			$out =$src &	0x000000000000FFFF;							break;\
\
/* 2x0 */	case 0x10:										body =	$srcHi &	0x0000000000FFFF00;	head = $src &	0x00000000000000FF;		$out =head|	body;	break;\
/* 2x1 */	case 0x11:										body =	$srcHi &	0x0000000000FF0000;	head = $src &	0x000000000000FFFF;		$out =head|	body;	break;\
/* 2x2 */	case 0x12:	\
/* 2x3 */	case 0x13:	\
/* 2x4 */	case 0x14:	\
/* 2x5 */	case 0x15:	\
/* 2x6 */	case 0x16:	\
/* 2x7 */	case 0x17:																			$out = $src &	0x0000000000FFFFFF;							break;\
\
/* 3x0 */	case 0x18:										body =	$srcHi &	0x00000000FFFFFF00;	head = $src &	0x00000000000000FF;		$out =head|	body;	break;\
/* 3x1 */	case 0x19:										body =	$srcHi &	0x00000000FFFF0000;	head = $src &	0x000000000000FFFF;		$out =head|	body;	break;\
/* 3x2 */	case 0x1A:										body =	$srcHi &	0x00000000FF000000;	head = $src &	0x0000000000FFFFFF;		$out =head|	body;	break;\
/* 3x3 */	case 0x1B:	\
/* 3x4 */	case 0x1C:	\
/* 3x5 */	case 0x1D:	\
/* 3x6 */	case 0x1E:	\
/* 3x7 */	case 0x1F:																			$out = $src &	0x00000000FFFFFFFF;							break;\
\
/* 4x0 */	case 0x20:										body =	$srcHi &	0x000000FFFFFFFF00;	head = $src &	0x00000000000000FF;		$out =head|	body;	break;\
/* 4x1 */	case 0x21:										body =	$srcHi &	0x000000FFFFFF0000;	head = $src &	0x000000000000FFFF;		$out =head|	body;	break;\
/* 4x2 */	case 0x22:										body =	$srcHi &	0x000000FFFF000000;	head = $src &	0x0000000000FFFFFF;		$out =head|	body;	break;\
/* 4x3 */	case 0x23:										body =	$srcHi &	0x000000FF00000000;	head = $src &	0x00000000FFFFFFFF;		$out =head|	body;	break;\
/* 4x4 */	case 0x24:	\
/* 4x5 */	case 0x25:	\
/* 4x6 */	case 0x26:	\
/* 4x7 */	case 0x27:																			$out = $src &	0x000000FFFFFFFFFF;							break;\
\
/* 5x0 */	case 0x28:										body =	$srcHi &	0x0000FFFFFFFFFF00;	head = $src &	0x00000000000000FF;		$out =head|	body;	break;\
/* 5x1 */	case 0x29:										body =	$srcHi &	0x0000FFFFFFFF0000;	head = $src &	0x000000000000FFFF;		$out =head|	body;	break;\
/* 5x2 */	case 0x2A:										body =	$srcHi &	0x0000FFFFFF000000;	head = $src &	0x0000000000FFFFFF;		$out =head|	body;	break;\
/* 5x3 */	case 0x2B:										body =	$srcHi &	0x0000FFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$out =head|	body;	break;\
/* 5x4 */	case 0x2C:										body =	$srcHi &	0x0000FF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$out =head|	body;	break;\
/* 5x5 */	case 0x2D:	\
/* 5x6 */	case 0x2E:	\
/* 5x7 */	case 0x2F:																			$out = $src &	0x0000FFFFFFFFFFFF;							break;\
\
/* 6x0 */	case 0x30:										body =	$srcHi &	0x00FFFFFFFFFFFF00;	head = $src &	0x00000000000000FF;		$out =head|	body;	break;\
/* 6x1 */	case 0x31:										body =	$srcHi &	0x00FFFFFFFFFF0000;	head = $src &	0x000000000000FFFF;		$out =head|	body;	break;\
/* 6x2 */	case 0x32:										body =	$srcHi &	0x00FFFFFFFF000000;	head = $src &	0x0000000000FFFFFF;		$out =head|	body;	break;\
/* 6x3 */	case 0x33:										body =	$srcHi &	0x00FFFFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$out =head|	body;	break;\
/* 6x4 */	case 0x34:										body =	$srcHi &	0x00FFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$out =head|	body;	break;\
/* 6x5 */	case 0x35:										body =	$srcHi &	0x00FF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$out =head|	body;	break;\
/* 6x6 */	case 0x36:	\
/* 6x7 */	case 0x37:																			$out = $src &	0x00FFFFFFFFFFFFFF;							break;\
\
/* 7x0 */	case 0x38:										body =	$srcHi &	0xFFFFFFFFFFFFFF00;	head = $src &	0x00000000000000FF;		$out =head|	body;	break;\
/* 7x1 */	case 0x39:										body =	$srcHi &	0xFFFFFFFFFFFF0000;	head = $src &	0x000000000000FFFF;		$out =head|	body;	break;\
/* 7x2 */	case 0x3A:										body =	$srcHi &	0xFFFFFFFFFF000000;	head = $src &	0x0000000000FFFFFF;		$out =head|	body;	break;\
/* 7x3 */	case 0x3B:										body =	$srcHi &	0xFFFFFFFF00000000;	head = $src &	0x00000000FFFFFFFF;		$out =head|	body;	break;\
/* 7x4 */	case 0x3C:										body =	$srcHi &	0xFFFFFF0000000000;	head = $src &	0x000000FFFFFFFFFF;		$out =head|	body;	break;\
/* 7x5 */	case 0x3D:										body =	$srcHi &	0xFFFF000000000000;	head = $src &	0x0000FFFFFFFFFFFF;		$out =head|	body;	break;\
/* 7x6 */	case 0x3E:										body =	$srcHi &	0xFF00000000000000;	head = $src &	0x00FFFFFFFFFFFFFF;		$out =head|	body;	break;\
/* 7x7 */	case 0x3F:																			$out = $src;							
/*					^ there is no tail						^ isolate high octets					^ isolate low octets						^ rejoin				*/



#define SwCASE_XXOVER_01T( $srcExo,	$src )		/* "01T" means	switch case vector 0 starts at zero,
																switch case vector 1 starts at one,
																and arg[0] "Tees into" arg[1], which is also the output variable.	*/	\
/* 0x0 */	case 0x00:	body =	$srcExo & 0x00000000000000FF;		tail	= $src & 0xFFFFFFFFFFFFFF00;		$src = body|tail;	break;\
/* 0x1 */	case 0x01:	body =	$srcExo & 0x000000000000FF00;		tail	= $src & 0xFFFFFFFFFFFF00FF;		$src = body|tail;	break;\
/* 0x2 */	case 0x02:	body =	$srcExo & 0x0000000000FF0000;		tail	= $src & 0xFFFFFFFFFF00FFFF;		$src = body|tail;	break;\
/* 0x3 */	case 0x03:	body =	$srcExo & 0x00000000FF000000;		tail	= $src & 0xFFFFFFFF00FFFFFF;		$src = body|tail;	break;\
/* 0x4 */	case 0x04:	body =	$srcExo & 0x000000FF00000000;		tail	= $src & 0xFFFFFF00FFFFFFFF;		$src = body|tail;	break;\
/* 0x5 */	case 0x05:	body =	$srcExo & 0x0000FF0000000000;		tail	= $src & 0xFFFF00FFFFFFFFFF;		$src = body|tail;	break;\
/* 0x6 */	case 0x06:	body =	$srcExo & 0x00FF000000000000;		tail	= $src & 0xFF00FFFFFFFFFFFF;		$src = body|tail;	break;\
/* 0x7 */	case 0x07:	body =	$srcExo & 0xFF00000000000000;		tail	= $src & 0x00FFFFFFFFFFFFFF;		$src = body|tail;	break;\
\
/* 1x0 */	case 0x08:	body =	$srcExo & 0x000000000000FFFF;		tail	= $src & 0xFFFFFFFFFFFF0000;	$src = body|tail;	break;\
/* 1x1 */	case 0x09:	body =	$srcExo & 0x0000000000FFFF00;		tail	= $src & 0xFFFFFFFFFF0000FF;	$src = body|tail;	break;\
/* 1x2 */	case 0x0A:	body =	$srcExo & 0x00000000FFFF0000;		tail	= $src & 0xFFFFFFFF0000FFFF;	$src = body|tail;	break;\
/* 1x3 */	case 0x0B:	body =	$srcExo & 0x000000FFFF000000;		tail	= $src & 0xFFFFFF0000FFFFFF;	$src = body|tail;	break;\
/* 1x4 */	case 0x0C:	body =	$srcExo & 0x0000FFFF00000000;		tail	= $src & 0xFFFF0000FFFFFFFF;	$src = body|tail;	break;\
/* 1x5 */	case 0x0D:	body =	$srcExo & 0x00FFFF0000000000;		tail	= $src & 0xFF0000FFFFFFFFFF;	$src = body|tail;	break;\
/* 1x6 */	case 0x0E:	body =	$srcExo & 0xFFFF000000000000;		tail	= $src & 0x0000FFFFFFFFFFFF;	$src = body|tail;	break;\
/* 1x7 */	case 0x0F:	body =	$srcExo & 0xFF00000000000000;		tail	= $src & 0x00FFFFFFFFFFFFFF;		$src = body|tail;	break;\
\
/* 2x0 */	case 0x10:	body =	$srcExo & 0x0000000000FFFFFF;		tail	= $src & 0xFFFFFFFFFF000000;	$src = body|tail;	break;\
/* 2x1 */	case 0x11:	body =	$srcExo & 0x00000000FFFFFF00;		tail	= $src & 0xFFFFFFFF000000FF;	$src = body|tail;	break;\
/* 2x2 */	case 0x12:	body =	$srcExo & 0x000000FFFFFF0000;		tail	= $src & 0xFFFFFF000000FFFF;	$src = body|tail;	break;\
/* 2x3 */	case 0x13:	body =	$srcExo & 0x0000FFFFFF000000;		tail	= $src & 0xFFFF000000FFFFFF;	$src = body|tail;	break;\
/* 2x4 */	case 0x14:	body =	$srcExo & 0x00FFFFFF00000000;		tail	= $src & 0xFF000000FFFFFFFF;	$src = body|tail;	break;\
/* 2x5 */	case 0x15:	body =	$srcExo & 0xFFFFFF0000000000;		tail	= $src & 0x000000FFFFFFFFFF;	$src = body|tail;	break;\
/* 2x6 */	case 0x16:	body =	$srcExo & 0xFFFF000000000000;		tail	= $src & 0x0000FFFFFFFFFFFF;	$src = body|tail;	break;\
/* 2x7 */	case 0x17:	body =	$srcExo & 0xFF00000000000000;		tail	= $src & 0x00FFFFFFFFFFFFFF;		$src = body|tail;	break;\
\
/* 3x0 */	case 0x18:	body =	$srcExo & 0x00000000FFFFFFFF;		tail	= $src & 0xFFFFFFFF00000000;	$src = body|tail;	break;\
/* 3x1 */	case 0x19:	body =	$srcExo & 0x000000FFFFFFFF00;		tail	= $src & 0xFFFFFF00000000FF;	$src = body|tail;	break;\
/* 3x2 */	case 0x1A:	body =	$srcExo & 0x0000FFFFFFFF0000;		tail	= $src & 0xFFFF00000000FFFF;	$src = body|tail;	break;\
/* 3x3 */	case 0x1B:	body =	$srcExo & 0x00FFFFFFFF000000;		tail	= $src & 0xFF00000000FFFFFF;	$src = body|tail;	break;\
/* 3x4 */	case 0x1C:	body =	$srcExo & 0xFFFFFFFF00000000;		tail	= $src & 0x00000000FFFFFFFF;	$src = body|tail;	break;\
/* 3x5 */	case 0x1D:	body =	$srcExo & 0xFFFFFF0000000000;		tail	= $src & 0x000000FFFFFFFFFF;	$src = body|tail;	break;\
/* 3x6 */	case 0x1E:	body =	$srcExo & 0xFFFF000000000000;		tail	= $src & 0x0000FFFFFFFFFFFF;	$src = body|tail;	break;\
/* 3x7 */	case 0x1F:	body =	$srcExo & 0xFF00000000000000;		tail	= $src & 0x00FFFFFFFFFFFFFF;		$src = body|tail;	break;\
\
/* 4x0 */	case 0x20:	body =	$srcExo & 0x000000FFFFFFFFFF;		tail	= $src & 0xFFFFFF0000000000;	$src = body|tail;	break;\
/* 4x1 */	case 0x21:	body =	$srcExo & 0x0000FFFFFFFFFF00;		tail	= $src & 0xFFFF0000000000FF;	$src = body|tail;	break;\
/* 4x2 */	case 0x22:	body =	$srcExo & 0x00FFFFFFFFFF0000;		tail	= $src & 0xFF0000000000FFFF;	$src = body|tail;	break;\
/* 4x3 */	case 0x23:	body =	$srcExo & 0xFFFFFFFFFF000000;		tail	= $src & 0x0000000000FFFFFF;	$src = body|tail;	break;\
/* 4x4 */	case 0x24:	body =	$srcExo & 0xFFFFFFFF00000000;		tail	= $src & 0x00000000FFFFFFFF;	$src = body|tail;	break;\
/* 4x5 */	case 0x25:	body =	$srcExo & 0xFFFFFF0000000000;		tail	= $src & 0x000000FFFFFFFFFF;	$src = body|tail;	break;\
/* 4x6 */	case 0x26:	body =	$srcExo & 0xFFFF000000000000;		tail	= $src & 0x0000FFFFFFFFFFFF;	$src = body|tail;	break;\
/* 4x7 */	case 0x27:	body =	$srcExo & 0xFF00000000000000;		tail	= $src & 0x00FFFFFFFFFFFFFF;		$src = body|tail;	break;\
\
/* 5x0 */	case 0x28:	body =	$srcExo & 0x0000FFFFFFFFFFFF;		tail	= $src & 0xFFFF000000000000;	$src = body|tail;	break;\
/* 5x1 */	case 0x29:	body =	$srcExo & 0x00FFFFFFFFFFFF00;		tail	= $src & 0xFF000000000000FF;	$src = body|tail;	break;\
/* 5x2 */	case 0x2A:	body =	$srcExo & 0xFFFFFFFFFFFF0000;		tail	= $src & 0x000000000000FFFF;	$src = body|tail;	break;\
/* 5x3 */	case 0x2B:	body =	$srcExo & 0xFFFFFFFFFF000000;		tail	= $src & 0x0000000000FFFFFF;	$src = body|tail;	break;\
/* 5x4 */	case 0x2C:	body =	$srcExo & 0xFFFFFFFF00000000;		tail	= $src & 0x00000000FFFFFFFF;	$src = body|tail;	break;\
/* 5x5 */	case 0x2D:	body =	$srcExo & 0xFFFFFF0000000000;		tail	= $src & 0x000000FFFFFFFFFF;	$src = body|tail;	break;\
/* 5x6 */	case 0x2E:	body =	$srcExo & 0xFFFF000000000000;		tail	= $src & 0x0000FFFFFFFFFFFF;	$src = body|tail;	break;\
/* 5x7 */	case 0x2F:	body =	$srcExo & 0xFF00000000000000;		tail	= $src & 0x00FFFFFFFFFFFFFF;		$src = body|tail;	break;\
\
/* 6x0 */	case 0x30:	body =	$srcExo & 0x00FFFFFFFFFFFFFF;		tail	= $src & 0xFF00000000000000;	$src = body|tail;	break;\
/* 6x1 */	case 0x31:	body =	$srcExo & 0xFFFFFFFFFFFFFF00;		tail	= $src & 0x00000000000000FF;	$src = body|tail;	break;\
/* 6x2 */	case 0x32:	body =	$srcExo & 0xFFFFFFFFFFFF0000;		tail	= $src & 0x000000000000FFFF;	$src = body|tail;	break;\
/* 6x3 */	case 0x33:	body =	$srcExo & 0xFFFFFFFFFF000000;		tail	= $src & 0x0000000000FFFFFF;	$src = body|tail;	break;\
/* 6x4 */	case 0x34:	body =	$srcExo & 0xFFFFFFFF00000000;		tail	= $src & 0x00000000FFFFFFFF;	$src = body|tail;	break;\
/* 6x5 */	case 0x35:	body =	$srcExo & 0xFFFFFF0000000000;		tail	= $src & 0x000000FFFFFFFFFF;	$src = body|tail;	break;\
/* 6x6 */	case 0x36:	body =	$srcExo & 0xFFFF000000000000;		tail	= $src & 0x0000FFFFFFFFFFFF;	$src = body|tail;	break;\
/* 6x7 */	case 0x37:	body =	$srcExo & 0xFF00000000000000;		tail	= $src & 0x00FFFFFFFFFFFFFF;		$src = body|tail;	break;\
\
/* 7x0 */	case 0x38:	$src=$srcExo;																							break;\
/* 7x1 */	case 0x39:	body =	$srcExo & 0xFFFFFFFFFFFFFF00;		tail	= $src & 0x00000000000000FF;	$src = body|tail;	break;\
/* 7x2 */	case 0x3A:	body =	$srcExo & 0xFFFFFFFFFFFF0000;		tail	= $src & 0x000000000000FFFF;	$src = body|tail;	break;\
/* 7x3 */	case 0x3B:	body =	$srcExo & 0xFFFFFFFFFF000000;		tail	= $src & 0x0000000000FFFFFF;	$src = body|tail;	break;\
/* 7x4 */	case 0x3C:	body =	$srcExo & 0xFFFFFFFF00000000;		tail	= $src & 0x00000000FFFFFFFF;	$src = body|tail;	break;\
/* 7x5 */	case 0x3D:	body =	$srcExo & 0xFFFFFF0000000000;		tail	= $src & 0x000000FFFFFFFFFF;	$src = body|tail;	break;\
/* 7x6 */	case 0x3E:	body =	$srcExo & 0xFFFF000000000000;		tail	= $src & 0x0000FFFFFFFFFFFF;	$src = body|tail;	break;\
/* 7x7 */	case 0x3F:	body =	$srcExo & 0xFF00000000000000;		tail	= $src & 0x00FFFFFFFFFFFFFF;		$src = body|tail;			
/*					^ isolate external octets					^	isolate internal octets				^ rejoin		*/


#define SwCASE_XXOVER_01Y( $srcExo, $src, $out )		/* "01Y" means	switch case vector 0 starts at zero,
																switch case vector 1 starts at one,
																and args[0..1] "Wye into" arg-2, which is the output variable.	*/	\
/* 0x0 */	case 0x00:	tail	= $srcExo & 0xFFFFFFFFFFFFFF00;       	head =	$src & 0x00000000000000FF;       	$out = head|tail;       	break;\
/* 0x1 */	case 0x01:	tail	= $srcExo & 0xFFFFFFFFFFFF00FF;       	head =	$src & 0x000000000000FF00;       	$out = head|tail;       	break;\
/* 0x2 */	case 0x02:	tail	= $srcExo & 0xFFFFFFFFFF00FFFF;       	head =	$src & 0x0000000000FF0000;       	$out = head|tail;       	break;\
/* 0x3 */	case 0x03:	tail	= $srcExo & 0xFFFFFFFF00FFFFFF;       	head =	$src & 0x00000000FF000000;       	$out = head|tail;       	break;\
/* 0x4 */	case 0x04:	tail	= $srcExo & 0xFFFFFF00FFFFFFFF;       	head =	$src & 0x000000FF00000000;       	$out = head|tail;       	break;\
/* 0x5 */	case 0x05:	tail	= $srcExo & 0xFFFF00FFFFFFFFFF;       	head =	$src & 0x0000FF0000000000;       	$out = head|tail;       	break;\
/* 0x6 */	case 0x06:	tail	= $srcExo & 0xFF00FFFFFFFFFFFF;       	head =	$src & 0x00FF000000000000;       	$out = head|tail;       	break;\
/* 0x7 */	case 0x07:	tail	= $srcExo & 0x00FFFFFFFFFFFFFF;       	head =	$src & 0xFF00000000000000;       	$out = head|tail;       	break;\
\
/* 1x0 */	case 0x08:	tail	= $srcExo & 0xFFFFFFFFFFFF0000;       	head =	$src & 0x000000000000FFFF;       	$out = head|tail;       	break;\
/* 1x1 */	case 0x09:	tail	= $srcExo & 0xFFFFFFFFFF0000FF;       	head =	$src & 0x0000000000FFFF00;       	$out = head|tail;       	break;\
/* 1x2 */	case 0x0A:	tail	= $srcExo & 0xFFFFFFFF0000FFFF;       	head =	$src & 0x00000000FFFF0000;       	$out = head|tail;       	break;\
/* 1x3 */	case 0x0B:	tail	= $srcExo & 0xFFFFFF0000FFFFFF;       	head =	$src & 0x000000FFFF000000;       	$out = head|tail;       	break;\
/* 1x4 */	case 0x0C:	tail	= $srcExo & 0xFFFF0000FFFFFFFF;       	head =	$src & 0x0000FFFF00000000;       	$out = head|tail;       	break;\
/* 1x5 */	case 0x0D:	tail	= $srcExo & 0xFF0000FFFFFFFFFF;       	head =	$src & 0x00FFFF0000000000;       	$out = head|tail;       	break;\
/* 1x6 */	case 0x0E:	tail	= $srcExo & 0x0000FFFFFFFFFFFF;       	head =	$src & 0xFFFF000000000000;       	$out = head|tail;       	break;\
/* 1x7 */	case 0x0F:	tail	= $srcExo & 0x00FFFFFFFFFFFFFF;       	head =	$src & 0xFF00000000000000;       	$out = head|tail;       	break;\
\
/* 2x0 */	case 0x10:	tail	= $srcExo & 0xFFFFFFFFFF000000;       	head =	$src & 0x0000000000FFFFFF;       	$out = head|tail;       	break;\
/* 2x1 */	case 0x11:	tail	= $srcExo & 0xFFFFFFFF000000FF;       	head =	$src & 0x00000000FFFFFF00;       	$out = head|tail;       	break;\
/* 2x2 */	case 0x12:	tail	= $srcExo & 0xFFFFFF000000FFFF;       	head =	$src & 0x000000FFFFFF0000;       	$out = head|tail;       	break;\
/* 2x3 */	case 0x13:	tail	= $srcExo & 0xFFFF000000FFFFFF;       	head =	$src & 0x0000FFFFFF000000;       	$out = head|tail;       	break;\
/* 2x4 */	case 0x14:	tail	= $srcExo & 0xFF000000FFFFFFFF;       	head =	$src & 0x00FFFFFF00000000;       	$out = head|tail;       	break;\
/* 2x5 */	case 0x15:	tail	= $srcExo & 0x000000FFFFFFFFFF;       	head =	$src & 0xFFFFFF0000000000;       	$out = head|tail;       	break;\
/* 2x6 */	case 0x16:	tail	= $srcExo & 0x0000FFFFFFFFFFFF;       	head =	$src & 0xFFFF000000000000;       	$out = head|tail;       	break;\
/* 2x7 */	case 0x17:	tail	= $srcExo & 0x00FFFFFFFFFFFFFF;       	head =	$src & 0xFF00000000000000;       	$out = head|tail;       	break;\
\
/* 3x0 */	case 0x18:	tail	= $srcExo & 0xFFFFFFFF00000000;       	head =	$src & 0x00000000FFFFFFFF;       	$out = head|tail;       	break;\
/* 3x1 */	case 0x19:	tail	= $srcExo & 0xFFFFFF00000000FF;       	head =	$src & 0x000000FFFFFFFF00;       	$out = head|tail;       	break;\
/* 3x2 */	case 0x1A:	tail	= $srcExo & 0xFFFF00000000FFFF;       	head =	$src & 0x0000FFFFFFFF0000;       	$out = head|tail;       	break;\
/* 3x3 */	case 0x1B:	tail	= $srcExo & 0xFF00000000FFFFFF;       	head =	$src & 0x00FFFFFFFF000000;       	$out = head|tail;       	break;\
/* 3x4 */	case 0x1C:	tail	= $srcExo & 0x00000000FFFFFFFF;       	head =	$src & 0xFFFFFFFF00000000;       	$out = head|tail;       	break;\
/* 3x5 */	case 0x1D:	tail	= $srcExo & 0x000000FFFFFFFFFF;       	head =	$src & 0xFFFFFF0000000000;       	$out = head|tail;       	break;\
/* 3x6 */	case 0x1E:	tail	= $srcExo & 0x0000FFFFFFFFFFFF;       	head =	$src & 0xFFFF000000000000;       	$out = head|tail;       	break;\
/* 3x7 */	case 0x1F:	tail	= $srcExo & 0x00FFFFFFFFFFFFFF;       	head =	$src & 0xFF00000000000000;       	$out = head|tail;       	break;\
\
/* 4x0 */	case 0x20:	tail	= $srcExo & 0xFFFFFF0000000000;       	head =	$src & 0x000000FFFFFFFFFF;       	$out = head|tail;       	break;\
/* 4x1 */	case 0x21:	tail	= $srcExo & 0xFFFF0000000000FF;       	head =	$src & 0x0000FFFFFFFFFF00;       	$out = head|tail;       	break;\
/* 4x2 */	case 0x22:	tail	= $srcExo & 0xFF0000000000FFFF;       	head =	$src & 0x00FFFFFFFFFF0000;       	$out = head|tail;       	break;\
/* 4x3 */	case 0x23:	tail	= $srcExo & 0x0000000000FFFFFF;       	head =	$src & 0xFFFFFFFFFF000000;       	$out = head|tail;       	break;\
/* 4x4 */	case 0x24:	tail	= $srcExo & 0x00000000FFFFFFFF;       	head =	$src & 0xFFFFFFFF00000000;       	$out = head|tail;       	break;\
/* 4x5 */	case 0x25:	tail	= $srcExo & 0x000000FFFFFFFFFF;       	head =	$src & 0xFFFFFF0000000000;       	$out = head|tail;       	break;\
/* 4x6 */	case 0x26:	tail	= $srcExo & 0x0000FFFFFFFFFFFF;       	head =	$src & 0xFFFF000000000000;       	$out = head|tail;       	break;\
/* 4x7 */	case 0x27:	tail	= $srcExo & 0x00FFFFFFFFFFFFFF;       	head =	$src & 0xFF00000000000000;       	$out = head|tail;       	break;\
\
/* 5x0 */	case 0x28:	tail	= $srcExo & 0xFFFF000000000000;       	head =	$src & 0x0000FFFFFFFFFFFF;       	$out = head|tail;       	break;\
/* 5x1 */	case 0x29:	tail	= $srcExo & 0xFF000000000000FF;       	head =	$src & 0x00FFFFFFFFFFFF00;       	$out = head|tail;       	break;\
/* 5x2 */	case 0x2A:	tail	= $srcExo & 0x000000000000FFFF;       	head =	$src & 0xFFFFFFFFFFFF0000;       	$out = head|tail;       	break;\
/* 5x3 */	case 0x2B:	tail	= $srcExo & 0x0000000000FFFFFF;       	head =	$src & 0xFFFFFFFFFF000000;       	$out = head|tail;       	break;\
/* 5x4 */	case 0x2C:	tail	= $srcExo & 0x00000000FFFFFFFF;       	head =	$src & 0xFFFFFFFF00000000;       	$out = head|tail;       	break;\
/* 5x5 */	case 0x2D:	tail	= $srcExo & 0x000000FFFFFFFFFF;       	head =	$src & 0xFFFFFF0000000000;       	$out = head|tail;       	break;\
/* 5x6 */	case 0x2E:	tail	= $srcExo & 0x0000FFFFFFFFFFFF;       	head =	$src & 0xFFFF000000000000;       	$out = head|tail;       	break;\
/* 5x7 */	case 0x2F:	tail	= $srcExo & 0x00FFFFFFFFFFFFFF;       	head =	$src & 0xFF00000000000000;       	$out = head|tail;       	break;\
\
/* 6x0 */	case 0x30:	tail	= $srcExo & 0xFF00000000000000;      	head =	$src & 0x00FFFFFFFFFFFFFF;       	$out = head|tail;       	break;\
/* 6x1 */	case 0x31:	tail	= $srcExo & 0x00000000000000FF;      	head =	$src & 0xFFFFFFFFFFFFFF00;       	$out = head|tail;       	break;\
/* 6x2 */	case 0x32:	tail	= $srcExo & 0x000000000000FFFF;       	head =	$src & 0xFFFFFFFFFFFF0000;       	$out = head|tail;       	break;\
/* 6x3 */	case 0x33:	tail	= $srcExo & 0x0000000000FFFFFF;       	head =	$src & 0xFFFFFFFFFF000000;       	$out = head|tail;       	break;\
/* 6x4 */	case 0x34:	tail	= $srcExo & 0x00000000FFFFFFFF;       	head =	$src & 0xFFFFFFFF00000000;       	$out = head|tail;       	break;\
/* 6x5 */	case 0x35:	tail	= $srcExo & 0x000000FFFFFFFFFF;       	head =	$src & 0xFFFFFF0000000000;       	$out = head|tail;       	break;\
/* 6x6 */	case 0x36:	tail	= $srcExo & 0x0000FFFFFFFFFFFF;       	head =	$src & 0xFFFF000000000000;       	$out = head|tail;       	break;\
/* 6x7 */	case 0x37:	tail	= $srcExo & 0x00FFFFFFFFFFFFFF;       	head =	$src & 0xFF00000000000000;       	$out = head|tail;       	break;\
\
/* 7x0 */	case 0x38:																			$out = $src;					break;\
/* 7x1 */	case 0x39:	tail	= $srcExo & 0x00000000000000FF;      	head =	$src & 0xFFFFFFFFFFFFFF00;       	$out = head|tail;       	break;\
/* 7x2 */	case 0x3A:	tail	= $srcExo & 0x000000000000FFFF;       	head =	$src & 0xFFFFFFFFFFFF0000;       	$out = head|tail;       	break;\
/* 7x3 */	case 0x3B:	tail	= $srcExo & 0x0000000000FFFFFF;       	head =	$src & 0xFFFFFFFFFF000000;       	$out = head|tail;       	break;\
/* 7x4 */	case 0x3C:	tail	= $srcExo & 0x00000000FFFFFFFF;       	head =	$src & 0xFFFFFFFF00000000;       	$out = head|tail;       	break;\
/* 7x5 */	case 0x3D:	tail	= $srcExo & 0x000000FFFFFFFFFF;       	head =	$src & 0xFFFFFF0000000000;       	$out = head|tail;       	break;\
/* 7x6 */	case 0x3E:	tail	= $srcExo & 0x0000FFFFFFFFFFFF;       	head =	$src & 0xFFFF000000000000;       	$out = head|tail;       	break;\
/* 7x7 */	case 0x3F:	tail	= $srcExo & 0x00FFFFFFFFFFFFFF;       	head =	$src & 0xFF00000000000000;       	$out = head|tail;       		
/*					^ isolate external octets					^	isolate internal octets				^ rejoin		*/


#define SwCASE_XXOVER_01K( $srcHi, $src, $ioLo )		/* "01K" means	switch case vector 0 starts at zero,
																switch case vector 1 starts at one,
																and args[0..2] "double-tee" into arg-2, which is also the output variable.	*/	\
/* 0x0 */	case 0x00:	tail	= $srcHi & 0xFFFFFFFFFFFFFF00;		body = $src &	0x00000000000000FF;											$ioLo =		body|	tail; 	break;\
/* 0x1 */	case 0x01:	tail	= $srcHi & 0xFFFFFFFFFFFF0000;		body = $src &	0x000000000000FF00;	head = $ioLo &	0x00000000000000FF;		$ioLo =head|	body|	tail;	break;\
/* 0x2 */	case 0x02:	tail	= $srcHi & 0xFFFFFFFFFF000000;		body = $src &	0x0000000000FF0000;	head = $ioLo &	0x000000000000FFFF;		$ioLo =head|	body|	tail;	break;\
/* 0x3 */	case 0x03:	tail	= $srcHi & 0xFFFFFFFF00000000;		body = $src &	0x00000000FF000000;	head = $ioLo &	0x0000000000FFFFFF;		$ioLo =head|	body|	tail;	break;\
/* 0x4 */	case 0x04:	tail	= $srcHi & 0xFFFFFF0000000000;		body = $src &	0x000000FF00000000;	head = $ioLo &	0x00000000FFFFFFFF;		$ioLo =head|	body|	tail;	break;\
/* 0x5 */	case 0x05:	tail	= $srcHi & 0xFFFF000000000000;		body = $src &	0x0000FF0000000000;	head = $ioLo &	0x000000FFFFFFFFFF;		$ioLo =head|	body|	tail;	break;\
/* 0x6 */	case 0x06:	tail	= $srcHi & 0xFF00000000000000;		body = $src &	0x00FF000000000000;	head = $ioLo &	0x0000FFFFFFFFFFFF;		$ioLo =head|	body|	tail;	break;\
/* 0x7 */	case 0x07:										body = $src &	0xFF00000000000000;	head = $ioLo &	0x00FFFFFFFFFFFFFF;		$ioLo =head|	body;		break;\
\
/* 1x0 */	case 0x08:	tail	= $srcHi & 0xFFFFFFFFFFFF0000;		body = $src &	0x000000000000FFFF;											$ioLo =		body|	tail;	break;\
/* 1x1 */	case 0x09:	tail	= $srcHi & 0xFFFFFFFFFF000000;		body = $src &	0x0000000000FFFF00;	head = $ioLo &	0x00000000000000FF;		$ioLo =head|	body|	tail;	break;\
/* 1x2 */	case 0x0A:	tail	= $srcHi & 0xFFFFFFFF00000000;		body = $src &	0x00000000FFFF0000;	head = $ioLo &	0x000000000000FFFF;		$ioLo =head|	body|	tail;	break;\
/* 1x3 */	case 0x0B:	tail	= $srcHi & 0xFFFFFF0000000000;		body = $src &	0x000000FFFF000000;	head = $ioLo &	0x0000000000FFFFFF;		$ioLo =head|	body|	tail;	break;\
/* 1x4 */	case 0x0C:	tail	= $srcHi & 0xFFFF000000000000;		body = $src &	0x0000FFFF00000000;	head = $ioLo &	0x00000000FFFFFFFF;		$ioLo =head|	body|	tail;	break;\
/* 1x5 */	case 0x0D:	tail	= $srcHi & 0xFF00000000000000;		body = $src &	0x00FFFF0000000000;	head = $ioLo &	0x000000FFFFFFFFFF;		$ioLo =head|	body|	tail;	break;\
/* 1x6 */	case 0x0E:										body = $src &	0xFFFF000000000000;	head = $ioLo &	0x0000FFFFFFFFFFFF;		$ioLo =head|	body;		break;\
/* 1x7 */	case 0x0F:										body = $src &	0xFF00000000000000;	head = $ioLo &	0x00FFFFFFFFFFFFFF;		$ioLo =head|	body;		break;\
\
/* 2x0 */	case 0x10:	tail	= $srcHi & 0xFFFFFFFFFF000000;		body = $src &	0x0000000000FFFFFF;											$ioLo =		body|	tail; 	break;\
/* 2x1 */	case 0x11:	tail	= $srcHi & 0xFFFFFFFF00000000;		body = $src &	0x00000000FFFFFF00;	head = $ioLo &	0x00000000000000FF;		$ioLo =head|	body|	tail;	break;\
/* 2x2 */	case 0x12:	tail	= $srcHi & 0xFFFFFF0000000000;		body = $src &	0x000000FFFFFF0000;	head = $ioLo &	0x000000000000FFFF;		$ioLo =head|	body|	tail;	break;\
/* 2x3 */	case 0x13:	tail	= $srcHi & 0xFFFF000000000000;		body = $src &	0x0000FFFFFF000000;	head = $ioLo &	0x0000000000FFFFFF;		$ioLo =head|	body|	tail;	break;\
/* 2x4 */	case 0x14:	tail	= $srcHi & 0xFF00000000000000;		body = $src &	0x00FFFFFF00000000;	head = $ioLo &	0x00000000FFFFFFFF;		$ioLo =head|	body|	tail;	break;\
/* 2x5 */	case 0x15:										body = $src &	0xFFFFFF0000000000;	head = $ioLo &	0x000000FFFFFFFFFF;		$ioLo =head|	body;		break;\
/* 2x6 */	case 0x16:										body = $src &	0xFFFF000000000000;	head = $ioLo &	0x0000FFFFFFFFFFFF;		$ioLo =head|	body;		break;\
/* 2x7 */	case 0x17:										body = $src &	0xFF00000000000000;	head = $ioLo &	0x00FFFFFFFFFFFFFF;		$ioLo =head|	body;		break;\
\
/* 3x0 */	case 0x18:	tail	= $srcHi & 0xFFFFFFFF00000000;		body = $src &	0x00000000FFFFFFFF;											$ioLo =		body|	tail; 	break;\
/* 3x1 */	case 0x19:	tail	= $srcHi & 0xFFFFFF0000000000;		body = $src &	0x000000FFFFFFFF00;	head = $ioLo &	0x00000000000000FF;		$ioLo =head|	body|	tail;	break;\
/* 3x2 */	case 0x1A:	tail	= $srcHi & 0xFFFF000000000000;		body = $src &	0x0000FFFFFFFF0000;	head = $ioLo &	0x000000000000FFFF;		$ioLo =head|	body|	tail;	break;\
/* 3x3 */	case 0x1B:	tail	= $srcHi & 0xFF00000000000000;		body = $src &	0x00FFFFFFFF000000;	head = $ioLo &	0x0000000000FFFFFF;		$ioLo =head|	body|	tail;	break;\
/* 3x4 */	case 0x1C:										body = $src &	0xFFFFFFFF00000000;	head = $ioLo &	0x00000000FFFFFFFF;		$ioLo =head|	body;		break;\
/* 3x5 */	case 0x1D:										body = $src &	0xFFFFFF0000000000;	head = $ioLo &	0x000000FFFFFFFFFF;		$ioLo =head|	body;		break;\
/* 3x6 */	case 0x1E:										body = $src &	0xFFFF000000000000;	head = $ioLo &	0x0000FFFFFFFFFFFF;		$ioLo =head|	body;		break;\
/* 3x7 */	case 0x1F:										body = $src &	0xFF00000000000000;	head = $ioLo &	0x00FFFFFFFFFFFFFF;		$ioLo =head|	body;		break;\
\
/* 4x0 */	case 0x20:	tail	= $srcHi & 0xFFFFFF0000000000;		body = $src &	0x000000FFFFFFFFFF;											$ioLo =		body|	tail; 	break;\
/* 4x1 */	case 0x21:	tail	= $srcHi & 0xFFFF000000000000;		body = $src &	0x0000FFFFFFFFFF00;	head = $ioLo &	0x00000000000000FF;		$ioLo =head|	body|	tail;	break;\
/* 4x2 */	case 0x22:	tail	= $srcHi & 0xFF00000000000000;		body = $src &	0x00FFFFFFFFFF0000;	head = $ioLo &	0x000000000000FFFF;		$ioLo =head|	body|	tail;	break;\
/* 4x3 */	case 0x23:										body = $src &	0xFFFFFFFFFF000000;	head = $ioLo &	0x0000000000FFFFFF;		$ioLo =head|	body;		break;\
/* 4x4 */	case 0x24:										body = $src &	0xFFFFFFFF00000000;	head = $ioLo &	0x00000000FFFFFFFF;		$ioLo =head|	body;		break;\
/* 4x5 */	case 0x25:										body = $src &	0xFFFFFF0000000000;	head = $ioLo &	0x000000FFFFFFFFFF;		$ioLo =head|	body;		break;\
/* 4x6 */	case 0x26:										body = $src &	0xFFFF000000000000;	head = $ioLo &	0x0000FFFFFFFFFFFF;		$ioLo =head|	body;		break;\
/* 4x7 */	case 0x27:										body = $src &	0xFF00000000000000;	head = $ioLo &	0x00FFFFFFFFFFFFFF;		$ioLo =head|	body;		break;\
\
/* 5x0 */	case 0x28:	tail	= $srcHi & 0xFFFF000000000000;		body = $src &	0x0000FFFFFFFFFFFF;											$ioLo =		body|	tail; 	break;\
/* 5x1 */	case 0x29:	tail	= $srcHi & 0xFF00000000000000;		body = $src &	0x00FFFFFFFFFFFF00;	head = $ioLo &	0x00000000000000FF;		$ioLo =head|	body|	tail;	break;\
/* 5x2 */	case 0x2A:										body = $src &	0xFFFFFFFFFFFF0000;	head = $ioLo &	0x000000000000FFFF;		$ioLo =head|	body;		break;\
/* 5x3 */	case 0x2B:										body = $src &	0xFFFFFFFFFF000000;	head = $ioLo &	0x0000000000FFFFFF;		$ioLo =head|	body;		break;\
/* 5x4 */	case 0x2C:										body = $src &	0xFFFFFFFF00000000;	head = $ioLo &	0x00000000FFFFFFFF;		$ioLo =head|	body;		break;\
/* 5x5 */	case 0x2D:										body = $src &	0xFFFFFF0000000000;	head = $ioLo &	0x000000FFFFFFFFFF;		$ioLo =head|	body;		break;\
/* 5x6 */	case 0x2E:										body = $src &	0xFFFF000000000000;	head = $ioLo &	0x0000FFFFFFFFFFFF;		$ioLo =head|	body;		break;\
/* 5x7 */	case 0x2F:										body = $src &	0xFF00000000000000;	head = $ioLo &	0x00FFFFFFFFFFFFFF;		$ioLo =head|	body;		break;\
\
/* 6x0 */	case 0x30:	tail	= $srcHi & 0xFF00000000000000;		body = $src &	0x00FFFFFFFFFFFFFF;											$ioLo =		body|	tail; 	break;\
/* 6x1 */	case 0x31:										body = $src &	0xFFFFFFFFFFFFFF00;	head = $ioLo &	0x00000000000000FF;		$ioLo =head|	body;		break;\
/* 6x2 */	case 0x32:										body = $src &	0xFFFFFFFFFFFF0000;	head = $ioLo &	0x000000000000FFFF;		$ioLo =head|	body;		break;\
/* 6x3 */	case 0x33:										body = $src &	0xFFFFFFFFFF000000;	head = $ioLo &	0x0000000000FFFFFF;		$ioLo =head|	body;		break;\
/* 6x4 */	case 0x34:										body = $src &	0xFFFFFFFF00000000;	head = $ioLo &	0x00000000FFFFFFFF;		$ioLo =head|	body;		break;\
/* 6x5 */	case 0x35:										body = $src &	0xFFFFFF0000000000;	head = $ioLo &	0x000000FFFFFFFFFF;		$ioLo =head|	body;		break;\
/* 6x6 */	case 0x36:										body = $src &	0xFFFF000000000000;	head = $ioLo &	0x0000FFFFFFFFFFFF;		$ioLo =head|	body;		break;\
/* 6x7 */	case 0x37:										body = $src &	0xFF00000000000000;	head = $ioLo &	0x00FFFFFFFFFFFFFF;		$ioLo =head|	body;		break;\
\
/* 7x0 */	case 0x38:										$ioLo = $src;																						break;\
/* 7x1 */	case 0x39:										body = $src &	0xFFFFFFFFFFFFFF00;	head = $ioLo &	0x00000000000000FF;		$ioLo =head|	body;		break;\
/* 7x2 */	case 0x3A:										body = $src &	0xFFFFFFFFFFFF0000;	head = $ioLo &	0x000000000000FFFF;		$ioLo =head|	body;		break;\
/* 7x3 */	case 0x3B:										body = $src &	0xFFFFFFFFFF000000;	head = $ioLo &	0x0000000000FFFFFF;		$ioLo =head|	body;		break;\
/* 7x4 */	case 0x3C:										body = $src &	0xFFFFFFFF00000000;	head = $ioLo &	0x00000000FFFFFFFF;		$ioLo =head|	body;		break;\
/* 7x5 */	case 0x3D:										body = $src &	0xFFFFFF0000000000;	head = $ioLo &	0x000000FFFFFFFFFF;		$ioLo =head|	body;		break;\
/* 7x6 */	case 0x3E:										body = $src &	0xFFFF000000000000;	head = $ioLo &	0x0000FFFFFFFFFFFF;		$ioLo =head|	body;		break;\
/* 7x7 */	case 0x3F:										body = $src &	0xFF00000000000000;	head = $ioLo &	0x00FFFFFFFFFFFFFF;		$ioLo =head|	body;		
/*					^ isolate high octets					^ isolate intermediate octets			^ isolate low octets							^ rejoin			*/


#define SwCASE_XSHELF_00T( $srcHi,	$src )			/* "00T" means	switch case vector 0 starts at zero,
																switch case vector 1 starts at zero as well,
																and arg[0] "Tees into" arg[1], which is also the output variable.	*/	\
/* 0x0 */	case 0x00: $src	= $srcHi;																					break;	\
/* 0x1 */	case 0x01:	tail	= $srcHi & 0xFFFFFFFFFFFFFF00;       	head =	$src & 0x00000000000000FF;       	$src = head|tail;       	break;\
/* 0x2 */	case 0x02:	tail	= $srcHi & 0xFFFFFFFFFFFF0000;       	head =	$src & 0x000000000000FFFF;       	$src = head|tail;       	break;\
/* 0x3 */	case 0x03:	tail	= $srcHi & 0xFFFFFFFFFF000000;       	head =	$src & 0x0000000000FFFFFF;       	$src = head|tail;       	break;\
/* 0x4 */	case 0x04:	tail	= $srcHi & 0xFFFFFFFF00000000;       	head =	$src & 0x00000000FFFFFFFF;       	$src = head|tail;       	break;\
/* 0x5 */	case 0x05:	tail	= $srcHi & 0xFFFFFF0000000000;       	head =	$src & 0x000000FFFFFFFFFF;       	$src = head|tail;       	break;\
/* 0x6 */	case 0x06:	tail	= $srcHi & 0xFFFF000000000000;       	head =	$src & 0x0000FFFFFFFFFFFF;       	$src = head|tail;       	break;\
/* 0x7 */	case 0x07:	tail	= $srcHi & 0xFF00000000000000;       	head =	$src & 0x00FFFFFFFFFFFFFF;       	$src = head|tail;       	break;\
/* 1x0 */	case 0x08: $src	= $srcHi & 0xFFFFFFFFFFFFFF00;									break;	\
/* 1x1 */	case 0x09:	tail	= $srcHi & 0xFFFFFFFFFFFF0000;       	head =	$src & 0x00000000000000FF;       	$src = head|tail;       	break;\
/* 1x2 */	case 0x0A:	tail	= $srcHi & 0xFFFFFFFFFF000000;       	head =	$src & 0x000000000000FFFF;       	$src = head|tail;       	break;\
/* 1x3 */	case 0x0B:	tail	= $srcHi & 0xFFFFFFFF00000000;       	head =	$src & 0x0000000000FFFFFF;       	$src = head|tail;       	break;\
/* 1x4 */	case 0x0C:	tail	= $srcHi & 0xFFFFFF0000000000;       	head =	$src & 0x00000000FFFFFFFF;       	$src = head|tail;       	break;\
/* 1x5 */	case 0x0D:	tail	= $srcHi & 0xFFFF000000000000;       	head =	$src & 0x000000FFFFFFFFFF;       	$src = head|tail;       	break;\
/* 1x6 */	case 0x0E:	tail	= $srcHi & 0xFF00000000000000;       	head =	$src &0x0000FFFFFFFFFFFF;		$src = head|tail;       	break;\
/* 1x7 */	case 0x0F:												$src &=0x00FFFFFFFFFFFFFF;							break;\
/* 2x0 */	case 0x10: $src	= $srcHi & 0xFFFFFFFFFFFF0000;																break;	\
/* 2x1 */	case 0x11:	tail	= $srcHi & 0xFFFFFFFFFF000000;       	head =	$src & 0x00000000000000FF;       	$src = head|tail;       	break;\
/* 2x2 */	case 0x12:	tail	= $srcHi & 0xFFFFFFFF00000000;       	head =	$src & 0x000000000000FFFF;       	$src = head|tail;       	break;\
/* 2x3 */	case 0x13:	tail	= $srcHi & 0xFFFFFF0000000000;       	head =	$src & 0x0000000000FFFFFF;       	$src = head|tail;       	break;\
/* 2x4 */	case 0x14:	tail	= $srcHi & 0xFFFF000000000000;       	head =	$src & 0x00000000FFFFFFFF;       	$src = head|tail;       	break;\
/* 2x5 */	case 0x15:	tail	= $srcHi & 0xFF00000000000000;       	head =	$src & 0x000000FFFFFFFFFF;       	$src = head|tail;       	break;\
/* 2x6 */	case 0x16:												$src &=0x0000FFFFFFFFFFFF;							break;\
/* 2x7 */	case 0x17:												$src &=0x00FFFFFFFFFFFFFF;							break;\
/* 3x0 */	case 0x18: $src	= $srcHi & 0xFFFFFFFFFF000000;																break;	\
/* 3x1 */	case 0x19:	tail	= $srcHi & 0xFFFFFFFF00000000;       	head =	$src & 0x00000000000000FF;       	$src = head|tail;       	break;\
/* 3x2 */	case 0x1A:	tail	= $srcHi & 0xFFFFFF0000000000;       	head =	$src & 0x000000000000FFFF;       	$src = head|tail;       	break;\
/* 3x3 */	case 0x1B:	tail	= $srcHi & 0xFFFF000000000000;       	head =	$src & 0x0000000000FFFFFF;       	$src = head|tail;       	break;\
/* 3x4 */	case 0x1C:	tail	= $srcHi & 0xFF00000000000000;       	head =	$src & 0x00000000FFFFFFFF;       	$src = head|tail;       	break;\
/* 3x5 */	case 0x1D:												$src &=0x000000FFFFFFFFFF;							break;\
/* 3x6 */	case 0x1E:												$src &=0x0000FFFFFFFFFFFF;							break;\
/* 3x7 */	case 0x1F:												$src &=0x00FFFFFFFFFFFFFF;							break;\
/* 4x0 */	case 0x20: $src	= $srcHi & 0xFFFFFFFF00000000;																break;	\
/* 4x1 */	case 0x21:	tail	= $srcHi & 0xFFFFFF0000000000;       	head =	$src & 0x00000000000000FF;       	$src = head|tail;       	break;\
/* 4x2 */	case 0x22:	tail	= $srcHi & 0xFFFF000000000000;       	head =	$src & 0x000000000000FFFF;       	$src = head|tail;       	break;\
/* 4x3 */	case 0x23:	tail	= $srcHi & 0xFF00000000000000;       	head =	$src & 0x0000000000FFFFFF;       	$src = head|tail;       	break;\
/* 4x4 */	case 0x24:												$src &=0x00000000FFFFFFFF;							break;\
/* 4x5 */	case 0x25:												$src &=0x000000FFFFFFFFFF;							break;\
/* 4x6 */	case 0x26:												$src &=0x0000FFFFFFFFFFFF;							break;\
/* 4x7 */	case 0x27:												$src &=0x00FFFFFFFFFFFFFF;							break;\
/* 5x0 */	case 0x28: $src	= $srcHi & 0xFFFFFF0000000000;																break;	\
/* 5x1 */	case 0x29:	tail	= $srcHi & 0xFFFF000000000000;       	head =	$src & 0x00000000000000FF;       	$src = head|tail;       	break;\
/* 5x2 */	case 0x2A:	tail	= $srcHi & 0xFF00000000000000;       	head =	$src & 0x000000000000FFFF;       	$src = head|tail;       	break;\
/* 5x3 */	case 0x2B:												$src &=0x0000000000FFFFFF;						break;\
/* 5x4 */	case 0x2C:												$src &=0x00000000FFFFFFFF;							break;\
/* 5x5 */	case 0x2D:												$src &=0x000000FFFFFFFFFF;							break;\
/* 5x6 */	case 0x2E:												$src &=0x0000FFFFFFFFFFFF;							break;\
/* 5x7 */	case 0x2F:												$src &=0x00FFFFFFFFFFFFFF;							break;\
/* 6x0 */	case 0x30: $src	= $srcHi & 0xFFFF000000000000;																break;	\
/* 6x1 */	case 0x31:	tail	= $srcHi & 0xFF00000000000000;       	head =	$src & 0x00000000000000FF;       	$src = head|tail;       	break;\
/* 6x2 */	case 0x32:												$src &=0x000000000000FFFF;						break;\
/* 6x3 */	case 0x33:												$src &=0x0000000000FFFFFF;						break;\
/* 6x4 */	case 0x34:												$src &=0x00000000FFFFFFFF;							break;\
/* 6x5 */	case 0x35:												$src &=0x000000FFFFFFFFFF;							break;\
/* 6x6 */	case 0x36:												$src &=0x0000FFFFFFFFFFFF;							break;\
/* 6x7 */	case 0x37:												$src &=0x00FFFFFFFFFFFFFF;							break;\
/* 7x0 */	case 0x38: $src	= $srcHi & 0xFF00000000000000;																break;	\
/* 7x1 */	case 0x39:												$src &=0x00000000000000FF;						break;\
/* 7x2 */	case 0x3A:												$src &=0x000000000000FFFF;						break;\
/* 7x3 */	case 0x3B:												$src &=0x0000000000FFFFFF;						break;\
/* 7x4 */	case 0x3C:												$src &=0x00000000FFFFFFFF;							break;\
/* 7x5 */	case 0x3D:												$src &=0x000000FFFFFFFFFF;							break;\
/* 7x6 */	case 0x3E:												$src &=0x0000FFFFFFFFFFFF;							break;\
/* 7x7 */	case 0x3F:												$src &=0x00FFFFFFFFFFFFFF;							break;\
/* 8x0 */	case 0x40:	$src	= 0;																						break;\
/* 8x1 */	case 0x41:												$src &=0x00000000000000FF;						break;\
/* 8x2 */	case 0x42:												$src &=0x000000000000FFFF;						break;\
/* 8x3 */	case 0x43:												$src &=0x0000000000FFFFFF;						break;\
/* 8x4 */	case 0x44:												$src &=0x00000000FFFFFFFF;							break;\
/* 8x5 */	case 0x45:												$src &=0x000000FFFFFFFFFF;							break;\
/* 8x6 */	case 0x46:												$src &=0x0000FFFFFFFFFFFF;							break;\
/* 8x7 */	case 0x47:												$src &=0x00FFFFFFFFFFFFFF;
/*					^ isolate trailing octets displaced					^	isolate leading octets retained		^ rejoin		*/





/*	kSpliceOpcode = ic0 |( post_c<< 3);	*/
#define SwCASE_XSHELF_01T( $srcHi,	$src )			/* "01T" means	switch case vector 0 starts at zero,
																switch case vector 1 starts at one,
																and arg[0] "Tees into" arg[1], which is also the output variable.	*/	\
/* 0x0 */	case 0x00:	$src	= $srcHi & 0xFFFFFFFFFFFFFF00;															break;\
/* 0x1 */	case 0x01:	tail	= $srcHi & 0xFFFFFFFFFFFF0000;       	head =	$src & 0x00000000000000FF;    	$src = head|tail;      break;\
/* 0x2 */	case 0x02:	tail	= $srcHi & 0xFFFFFFFFFF000000;       	head =	$src & 0x000000000000FFFF;    	$src = head|tail;      break;\
/* 0x3 */	case 0x03:	tail	= $srcHi & 0xFFFFFFFF00000000;       	head =	$src & 0x0000000000FFFFFF;    	$src = head|tail;      break;\
/* 0x4 */	case 0x04:	tail	= $srcHi & 0xFFFFFF0000000000;       	head =	$src & 0x00000000FFFFFFFF;    	$src = head|tail;      break;\
/* 0x5*/	case 0x05:	tail	= $srcHi & 0xFFFF000000000000;       	head =	$src & 0x000000FFFFFFFFFF;    	$src = head|tail;      break;\
/* 0x6 */	case 0x06:	tail	= $srcHi & 0xFF00000000000000;       	head =	$src & 0x0000FFFFFFFFFFFF;    	$src = head|tail;      break;\
/* 0x7 */	case 0x07:												$src &= 0x00FFFFFFFFFFFFFF;    					break;\
\
/* 1x0 */	case 0x08:	$src	= $srcHi & 0xFFFFFFFFFFFF0000;     														break;\
/* 1x1 */	case 0x09:	tail	= $srcHi & 0xFFFFFFFFFF000000;       	head =	$src & 0x00000000000000FF;    	$src = head|tail;      break;\
/* 1x2 */	case 0x0A:	tail	= $srcHi & 0xFFFFFFFF00000000;       	head =	$src & 0x000000000000FFFF;    	$src = head|tail;      break;\
/* 1x3 */	case 0x0B:	tail	= $srcHi & 0xFFFFFF0000000000;       	head =	$src & 0x0000000000FFFFFF;    	$src = head|tail;      break;\
/* 1x4 */	case 0x0C:	tail	= $srcHi & 0xFFFF000000000000;       	head =	$src & 0x00000000FFFFFFFF;    	$src = head|tail;      break;\
/* 1x5 */	case 0x0D:	tail	= $srcHi & 0xFF00000000000000;       	head =	$src & 0x000000FFFFFFFFFF;    	$src = head|tail;      break;\
/* 1x6 */	case 0x0E:												$src &=0x0000FFFFFFFFFFFF;						break;\
/* 1x7 */	case 0x0F:												$src &=0x00FFFFFFFFFFFFFF;						break;\
\
/* 2x0 */	case 0x10:	$src	= $srcHi & 0xFFFFFFFFFF000000;															break;\
/* 2x1 */	case 0x11:	tail	= $srcHi & 0xFFFFFFFF00000000;       	head =	$src & 0x00000000000000FF;       	$src = head|tail;      break;\
/* 2x2 */	case 0x12:	tail	= $srcHi & 0xFFFFFF0000000000;       	head =	$src & 0x000000000000FFFF;    	$src = head|tail;      break;\
/* 2x3 */	case 0x13:	tail	= $srcHi & 0xFFFF000000000000;       	head =	$src & 0x0000000000FFFFFF;    	$src = head|tail;      break;\
/* 2x4 */	case 0x14:	tail	= $srcHi & 0xFF00000000000000;       	head =	$src & 0x00000000FFFFFFFF;    	$src = head|tail;      break;\
/* 2x5 */	case 0x15:												$src &=0x000000FFFFFFFFFF;						break;\
/* 2x6 */	case 0x16:												$src &=0x0000FFFFFFFFFFFF;						break;\
/* 2x7 */	case 0x17:												$src &=0x00FFFFFFFFFFFFFF;						break;\
\
/* 3x0 */	case 0x18:	$src	= $srcHi & 0xFFFFFFFF00000000;															break;\
/* 3x1 */	case 0x19:	tail	= $srcHi & 0xFFFFFF0000000000;       	head =	$src & 0x00000000000000FF;       	$src = head|tail;      break;\
/* 3x2 */	case 0x1A:	tail	= $srcHi & 0xFFFF000000000000;       	head =	$src & 0x000000000000FFFF;    	$src = head|tail;      break;\
/* 3x3 */	case 0x1B:	tail	= $srcHi & 0xFF00000000000000;       	head =	$src & 0x0000000000FFFFFF;    	$src = head|tail;      break;\
/* 3x4 */	case 0x1C:												$src &=0x00000000FFFFFFFF;						break;\
/* 3x5 */	case 0x1D:												$src &=0x000000FFFFFFFFFF;						break;\
/* 3x6 */	case 0x1E:												$src &=0x0000FFFFFFFFFFFF;						break;\
/* 3x7 */	case 0x1F:												$src &=0x00FFFFFFFFFFFFFF;						break;\
\
/* 4x0 */	case 0x20:	$src	= $srcHi & 0xFFFFFF0000000000;															break;\
/* 4x1 */	case 0x21:	tail	= $srcHi & 0xFFFF000000000000;       	head =	$src & 0x00000000000000FF;       	$src = head|tail;      break;\
/* 4x2 */	case 0x22:	tail	= $srcHi & 0xFF00000000000000;       	head =	$src & 0x000000000000FFFF;    	$src = head|tail;      break;\
/* 4x3 */	case 0x23:												$src &=0x0000000000FFFFFF;					break;\
/* 4x4 */	case 0x24:												$src &=0x00000000FFFFFFFF;						break;\
/* 4x5 */	case 0x25:												$src &=0x000000FFFFFFFFFF;						break;\
/* 4x6 */	case 0x26:												$src &=0x0000FFFFFFFFFFFF;						break;\
/* 4x7 */	case 0x27:												$src &=0x00FFFFFFFFFFFFFF;						break;\
\
/* 5x0 */	case 0x28:	$src	= $srcHi & 0xFFFF000000000000;															break;\
/* 5x1 */	case 0x29:	tail	= $srcHi & 0xFF00000000000000;       	head =	$src & 0x00000000000000FF;       	$src = head|tail;      break;\
/* 5x2 */	case 0x2A:												$src &=0x000000000000FFFF;					break;\
/* 5x3 */	case 0x2B:												$src &=0x0000000000FFFFFF;					break;\
/* 5x4 */	case 0x2C:												$src &=0x00000000FFFFFFFF;						break;\
/* 5x5 */	case 0x2D:												$src &=0x000000FFFFFFFFFF;						break;\
/* 5x6 */	case 0x2E:												$src &=0x0000FFFFFFFFFFFF;						break;\
/* 5x7 */	case 0x2F:												$src &=0x00FFFFFFFFFFFFFF;						break;\
\
/* 6x0 */	case 0x30:	$src	=$srcHi & 0xFF00000000000000;															break;\
/* 6x1 */	case 0x31:												$src &=0x00000000000000FF;					break;\
/* 6x2 */	case 0x32:												$src &=0x000000000000FFFF;					break;\
/* 6x3 */	case 0x33:												$src &=0x0000000000FFFFFF;					break;\
/* 6x4 */	case 0x34:												$src &=0x00000000FFFFFFFF;						break;\
/* 6x5 */	case 0x35:												$src &=0x000000FFFFFFFFFF;						break;\
/* 6x6 */	case 0x36:												$src &=0x0000FFFFFFFFFFFF;						break;\
/* 6x7 */	case 0x37:												$src &=0x00FFFFFFFFFFFFFF;						break;\
\
/* 7x0 */	case 0x38:	$src	=		0x0000000000000000;															break;\
/* 7x1 */	case 0x39:												$src &=0x00000000000000FF;					break;\
/* 7x2 */	case 0x3A:												$src &=0x000000000000FFFF;					break;\
/* 7x3 */	case 0x3B:												$src &=0x0000000000FFFFFF;					break;\
/* 7x4 */	case 0x3C:												$src &=0x00000000FFFFFFFF;						break;\
/* 7x5 */	case 0x3D:												$src &=0x000000FFFFFFFFFF;						break;\
/* 7x6 */	case 0x3E:												$src &=0x0000FFFFFFFFFFFF;						break;\
/* 7x7 */	case 0x3F:												$src &=0x00FFFFFFFFFFFFFF;						
/*					^ isolate trailing octets							^ isolate leading octets			^ rejoin		*/



#define SwCASE_XSHELF_01IS( $src )					/* "01IS" means	switch case vector 0 starts at zero,
																switch case vector 1 starts at one,
																and arg[0] is both the input and output variable, "In Situ".	*/	\
/* 0x0 */	case 0x00:	$src &= 0xFFFFFFFFFFFFFF00;       	break;\
/* 0x1 */	case 0x01:	$src &= 0xFFFFFFFFFFFF00FF;       	break;\
/* 0x2 */	case 0x02:	$src &= 0xFFFFFFFFFF00FFFF;       	break;\
/* 0x3 */	case 0x03:	$src &= 0xFFFFFFFF00FFFFFF;       	break;\
/* 0x4 */	case 0x04:	$src &= 0xFFFFFF00FFFFFFFF;       	break;\
/* 0x5 */	case 0x05:	$src &= 0xFFFF00FFFFFFFFFF;       	break;\
/* 0x6 */	case 0x06:	$src &= 0xFF00FFFFFFFFFFFF;       	break;\
/* 0x7 */	case 0x07:	$src &= 0x00FFFFFFFFFFFFFF;       	break;\
\
/* 1x0 */	case 0x08:	$src &= 0xFFFFFFFFFFFF0000;       	break;\
/* 1x1 */	case 0x09:	$src &= 0xFFFFFFFFFF0000FF;       	break;\
/* 1x2 */	case 0x0A:	$src &= 0xFFFFFFFF0000FFFF;       	break;\
/* 1x3 */	case 0x0B:	$src &= 0xFFFFFF0000FFFFFF;       	break;\
/* 1x4 */	case 0x0C:	$src &= 0xFFFF0000FFFFFFFF;       	break;\
/* 1x5 */	case 0x0D:	$src &= 0xFF0000FFFFFFFFFF;       	break;\
/* 1x6 */	case 0x0E:	$src &= 0x0000FFFFFFFFFFFF;       	break;\
/* 1x7 */	case 0x0F:	$src &= 0x00FFFFFFFFFFFFFF;       	break;\
\
/* 2x0 */	case 0x10:	$src &= 0xFFFFFFFFFF000000;       	break;\
/* 2x1 */	case 0x11:	$src &= 0xFFFFFFFF000000FF;       	break;\
/* 2x2 */	case 0x12:	$src &= 0xFFFFFF000000FFFF;       	break;\
/* 2x3 */	case 0x13:	$src &= 0xFFFF000000FFFFFF;       	break;\
/* 2x4 */	case 0x14:	$src &= 0xFF000000FFFFFFFF;       	break;\
/* 2x5 */	case 0x15:	$src &= 0x000000FFFFFFFFFF;       	break;\
/* 2x6 */	case 0x16:	$src &= 0x0000FFFFFFFFFFFF;       	break;\
/* 2x7 */	case 0x17:	$src &= 0x00FFFFFFFFFFFFFF;       	break;\
\
/* 3x0 */	case 0x18:	$src &= 0xFFFFFFFF00000000;       	break;\
/* 3x1 */	case 0x19:	$src &= 0xFFFFFF00000000FF;       	break;\
/* 3x2 */	case 0x1A:	$src &= 0xFFFF00000000FFFF;       	break;\
/* 3x3 */	case 0x1B:	$src &= 0xFF00000000FFFFFF;       	break;\
/* 3x4 */	case 0x1C:	$src &= 0x00000000FFFFFFFF;       	break;\
/* 3x5 */	case 0x1D:	$src &= 0x000000FFFFFFFFFF;       	break;\
/* 3x6 */	case 0x1E:	$src &= 0x0000FFFFFFFFFFFF;       	break;\
/* 3x7 */	case 0x1F:	$src &= 0x00FFFFFFFFFFFFFF;       	break;\
\
/* 4x0 */	case 0x20:	$src &= 0xFFFFFF0000000000;      	break;\
/* 4x1 */	case 0x21:	$src &= 0xFFFF0000000000FF;       	break;\
/* 4x2 */	case 0x22:	$src &= 0xFF0000000000FFFF;       	break;\
/* 4x3 */	case 0x23:	$src &= 0x0000000000FFFFFF;       	break;\
/* 4x4 */	case 0x24:	$src &= 0x00000000FFFFFFFF;       	break;\
/* 4x5 */	case 0x25:	$src &= 0x000000FFFFFFFFFF;       	break;\
/* 4x6 */	case 0x26:	$src &= 0x0000FFFFFFFFFFFF;       	break;\
/* 4x7 */	case 0x27:	$src &= 0x00FFFFFFFFFFFFFF;       	break;\
\
/* 5x0 */	case 0x28:	$src &= 0xFFFFFF0000000000;       	break;\
/* 5x1 */	case 0x29:	$src &= 0xFFFF0000000000FF;       	break;\
/* 5x2 */	case 0x2A:	$src &= 0xFF0000000000FFFF;       	break;\
/* 5x3 */	case 0x2B:	$src &= 0x0000000000FFFFFF;       	break;\
/* 5x4 */	case 0x2C:	$src &= 0x00000000FFFFFFFF;       	break;\
/* 5x5 */	case 0x2D:	$src &= 0x000000FFFFFFFFFF;       	break;\
/* 5x6 */	case 0x2E:	$src &= 0x0000FFFFFFFFFFFF;       	break;\
/* 5x7 */	case 0x2F:	$src &= 0x00FFFFFFFFFFFFFF;       	break;\
\
/* 6x0 */	case 0x30:	$src &= 0xFF00000000000000;       	break;\
/* 6x1 */	case 0x31:	$src &= 0x00000000000000FF;       	break;\
/* 6x2 */	case 0x32:	$src &= 0x000000000000FFFF;       	break;\
/* 6x3 */	case 0x33:	$src &= 0x0000000000FFFFFF;       	break;\
/* 6x4 */	case 0x34:	$src &= 0x00000000FFFFFFFF;       	break;\
/* 6x5 */	case 0x35:	$src &= 0x000000FFFFFFFFFF;       	break;\
/* 6x6 */	case 0x36:	$src &= 0x0000FFFFFFFFFFFF;       	break;\
/* 6x7 */	case 0x37:	$src &= 0x00FFFFFFFFFFFFFF;       	break;\
\
/* 7x0 */	case 0x38:	$src =	0x0000000000000000;       	break;\
/* 7x1 */	case 0x39:	$src &=	0x00000000000000FF;       	break;\
/* 7x2 */	case 0x3A:	$src &= 0x000000000000FFFF;       	break;\
/* 7x3 */	case 0x3B:	$src &= 0x0000000000FFFFFF;       	break;\
/* 7x4 */	case 0x3C:	$src &= 0x00000000FFFFFFFF;       	break;\
/* 7x5 */	case 0x3D:	$src &= 0x000000FFFFFFFFFF;       	break;\
/* 7x6 */	case 0x3E:	$src &= 0x0000FFFFFFFFFFFF;       	break;\
/* 7x7 */	case 0x3F:	$src &= 0x00FFFFFFFFFFFFFF;     	


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
