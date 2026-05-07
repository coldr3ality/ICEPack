#define	qCAST_t1incQ( $a, $b, $pq, $postQ)	/*	cast [a, b] to the high side of *pq	w/ (1) byte[s] of overrun tolerance	*/		\
\
/*	part 1 of 4:	A disabled;	B disabled	(neither)	*/	\
case 0x00:	/*  0, 0   */	\
case 0x01:	/*  0, 0   */	\
case 0x02:	/*  0, 0   */	\
case 0x03:	/*  0, 0   */	\
case 0x04:	/*  0, 0   */	\
case 0x05:	/*  0, 0   */	\
case 0x06:	/*  0, 0   */	\
case 0x07:	/*  0, 0   */	\
case 0x08:	/*  0, 0   */	\
case 0x09:	/*  0, 0   */	\
case 0x0A:	/*  0, 0   */	\
case 0x0B:	/*  0, 0   */	\
case 0x0C:	/*  0, 0   */	\
case 0x0D:	/*  0, 0   */	\
case 0x0E:	/*  0, 0   */	\
case 0x0F:	/*  0, 0   */	\
case 0x10:	/*  0, 0   */	\
case 0x11:	/*  0, 0   */	\
case 0x12:	/*  0, 0   */	\
case 0x13:	/*  0, 0   */	\
case 0x14:	/*  0, 0   */	\
case 0x15:	/*  0, 0   */	\
case 0x16:	/*  0, 0   */	\
case 0x17:	/*  0, 0   */	\
case 0x18:	/*  0, 0   */	\
case 0x19:	/*  0, 0   */	\
case 0x1A:	/*  0, 0   */	\
case 0x1B:	/*  0, 0   */	\
case 0x1C:	/*  0, 0   */	\
case 0x1D:	/*  0, 0   */	\
case 0x1E:	/*  0, 0   */	\
case 0x1F:	/*  0, 0   */	\
case 0x20:	/*  0, 0   */	\
case 0x21:	/*  0, 0   */	\
case 0x22:	/*  0, 0   */	\
case 0x23:	/*  0, 0   */	\
case 0x24:	/*  0, 0   */	\
case 0x25:	/*  0, 0   */	\
case 0x26:	/*  0, 0   */	\
case 0x27:	/*  0, 0   */	\
case 0x28:	/*  0, 0   */	\
case 0x29:	/*  0, 0   */	\
case 0x2A:	/*  0, 0   */	\
case 0x2B:	/*  0, 0   */	\
case 0x2C:	/*  0, 0   */	\
case 0x2D:	/*  0, 0   */	\
case 0x2E:	/*  0, 0   */	\
case 0x2F:	/*  0, 0   */	\
case 0x30:	/*  0, 0   */	\
case 0x31:	/*  0, 0   */	\
case 0x32:	/*  0, 0   */	\
case 0x33:	/*  0, 0   */	\
case 0x34:	/*  0, 0   */	\
case 0x35:	/*  0, 0   */	\
case 0x36:	/*  0, 0   */	\
case 0x37:	/*  0, 0   */	\
case 0x38:	/*  0, 0   */	\
case 0x39:	/*  0, 0   */	\
case 0x3A:	/*  0, 0   */	\
case 0x3B:	/*  0, 0   */	\
case 0x3C:	/*  0, 0   */	\
case 0x3D:	/*  0, 0   */	\
case 0x3E:	/*  0, 0   */	\
case 0x3F:	/*  0, 0   */																	break;	\
\
/*	part 2 of 4:	A enabled;	B disabled	(just A)	*/	\
case 0x40:	/*  1, 0   */	*( (ui08*) ( $pq	) )= $a;									$pq +=  1;	$postQ -=  1;	break;	\
case 0x41:	/*  2, 0   */	*( (ui16*) ( $pq	) )= $a;									$pq +=  2;	$postQ -=  2;	break;	\
case 0x42:	/*  3, 0   */	*( (ui32*) ( $pq	) )= $a;									$pq +=  3;	$postQ -=  3;	break;	\
case 0x43:	/*  4, 0   */	*( (ui32*) ( $pq	) )= $a;									$pq +=  4;	$postQ -=  4;	break;	\
case 0x44:	/*  5, 0   */	*( (ui32*) ( $pq	) )= $a;									\
						*( (ui08*) ( $pq +4 	) )= $a>>32;								$pq +=  5;	$postQ -=  5;	break;	\
case 0x45:	/*  6, 0   */	*( (ui32*) ( $pq	) )= $a;									\
						*( (ui16*) ( $pq +4 	) )= $a>>32;								$pq +=  6;	$postQ -=  6;	break;	\
case 0x46:	/*  7, 0   */	*( (ui64*) ( $pq	) )= $a;									$pq +=  7;	$postQ -=  7;	break;	\
case 0x47:	/*  8, 0   */	*( (ui64*) ( $pq	) )= $a;									$pq +=  8;	$postQ -=  8;	break;	\
case 0x48:	/*  1, 0   */	*( (ui08*) ( $pq	) )= $a;									$pq +=  1;	$postQ -=  1;	break;	\
case 0x49:	/*  2, 0   */	*( (ui16*) ( $pq	) )= $a;									$pq +=  2;	$postQ -=  2;	break;	\
case 0x4A:	/*  3, 0   */	*( (ui32*) ( $pq	) )= $a;									$pq +=  3;	$postQ -=  3;	break;	\
case 0x4B:	/*  4, 0   */	*( (ui32*) ( $pq	) )= $a;									$pq +=  4;	$postQ -=  4;	break;	\
case 0x4C:	/*  5, 0   */	*( (ui32*) ( $pq	) )= $a;									\
						*( (ui08*) ( $pq +4 	) )= $a>>32;								$pq +=  5;	$postQ -=  5;	break;	\
case 0x4D:	/*  6, 0   */	*( (ui32*) ( $pq	) )= $a;									\
						*( (ui16*) ( $pq +4 	) )= $a>>32;								$pq +=  6;	$postQ -=  6;	break;	\
case 0x4E:	/*  7, 0   */	*( (ui64*) ( $pq	) )= $a;									$pq +=  7;	$postQ -=  7;	break;	\
case 0x4F:	/*  8, 0   */	*( (ui64*) ( $pq	) )= $a;									$pq +=  8;	$postQ -=  8;	break;	\
case 0x50:	/*  1, 0   */	*( (ui08*) ( $pq	) )= $a;									$pq +=  1;	$postQ -=  1;	break;	\
case 0x51:	/*  2, 0   */	*( (ui16*) ( $pq	) )= $a;									$pq +=  2;	$postQ -=  2;	break;	\
case 0x52:	/*  3, 0   */	*( (ui32*) ( $pq	) )= $a;									$pq +=  3;	$postQ -=  3;	break;	\
case 0x53:	/*  4, 0   */	*( (ui32*) ( $pq	) )= $a;									$pq +=  4;	$postQ -=  4;	break;	\
case 0x54:	/*  5, 0   */	*( (ui32*) ( $pq	) )= $a;									\
						*( (ui08*) ( $pq +4 	) )= $a>>32;								$pq +=  5;	$postQ -=  5;	break;	\
case 0x55:	/*  6, 0   */	*( (ui32*) ( $pq	) )= $a;									\
						*( (ui16*) ( $pq +4 	) )= $a>>32;								$pq +=  6;	$postQ -=  6;	break;	\
case 0x56:	/*  7, 0   */	*( (ui64*) ( $pq	) )= $a;									$pq +=  7;	$postQ -=  7;	break;	\
case 0x57:	/*  8, 0   */	*( (ui64*) ( $pq	) )= $a;									$pq +=  8;	$postQ -=  8;	break;	\
case 0x58:	/*  1, 0   */	*( (ui08*) ( $pq	) )= $a;									$pq +=  1;	$postQ -=  1;	break;	\
case 0x59:	/*  2, 0   */	*( (ui16*) ( $pq	) )= $a;									$pq +=  2;	$postQ -=  2;	break;	\
case 0x5A:	/*  3, 0   */	*( (ui32*) ( $pq	) )= $a;									$pq +=  3;	$postQ -=  3;	break;	\
case 0x5B:	/*  4, 0   */	*( (ui32*) ( $pq	) )= $a;									$pq +=  4;	$postQ -=  4;	break;	\
case 0x5C:	/*  5, 0   */	*( (ui32*) ( $pq	) )= $a;									\
						*( (ui08*) ( $pq +4 	) )= $a>>32;								$pq +=  5;	$postQ -=  5;	break;	\
case 0x5D:	/*  6, 0   */	*( (ui32*) ( $pq	) )= $a;									\
						*( (ui16*) ( $pq +4 	) )= $a>>32;								$pq +=  6;	$postQ -=  6;	break;	\
case 0x5E:	/*  7, 0   */	*( (ui64*) ( $pq	) )= $a;									$pq +=  7;	$postQ -=  7;	break;	\
case 0x5F:	/*  8, 0   */	*( (ui64*) ( $pq	) )= $a;									$pq +=  8;	$postQ -=  8;	break;	\
case 0x60:	/*  1, 0   */	*( (ui08*) ( $pq	) )= $a;									$pq +=  1;	$postQ -=  1;	break;	\
case 0x61:	/*  2, 0   */	*( (ui16*) ( $pq	) )= $a;									$pq +=  2;	$postQ -=  2;	break;	\
case 0x62:	/*  3, 0   */	*( (ui32*) ( $pq	) )= $a;									$pq +=  3;	$postQ -=  3;	break;	\
case 0x63:	/*  4, 0   */	*( (ui32*) ( $pq	) )= $a;									$pq +=  4;	$postQ -=  4;	break;	\
case 0x64:	/*  5, 0   */	*( (ui32*) ( $pq	) )= $a;									\
						*( (ui08*) ( $pq +4 	) )= $a>>32;								$pq +=  5;	$postQ -=  5;	break;	\
case 0x65:	/*  6, 0   */	*( (ui32*) ( $pq	) )= $a;									\
						*( (ui16*) ( $pq +4 	) )= $a>>32;								$pq +=  6;	$postQ -=  6;	break;	\
case 0x66:	/*  7, 0   */	*( (ui64*) ( $pq	) )= $a;									$pq +=  7;	$postQ -=  7;	break;	\
case 0x67:	/*  8, 0   */	*( (ui64*) ( $pq	) )= $a;									$pq +=  8;	$postQ -=  8;	break;	\
case 0x68:	/*  1, 0   */	*( (ui08*) ( $pq	) )= $a;									$pq +=  1;	$postQ -=  1;	break;	\
case 0x69:	/*  2, 0   */	*( (ui16*) ( $pq	) )= $a;									$pq +=  2;	$postQ -=  2;	break;	\
case 0x6A:	/*  3, 0   */	*( (ui32*) ( $pq	) )= $a;									$pq +=  3;	$postQ -=  3;	break;	\
case 0x6B:	/*  4, 0   */	*( (ui32*) ( $pq	) )= $a;									$pq +=  4;	$postQ -=  4;	break;	\
case 0x6C:	/*  5, 0   */	*( (ui32*) ( $pq	) )= $a;									\
						*( (ui08*) ( $pq +4 	) )= $a>>32;								$pq +=  5;	$postQ -=  5;	break;	\
case 0x6D:	/*  6, 0   */	*( (ui32*) ( $pq	) )= $a;									\
						*( (ui16*) ( $pq +4 	) )= $a>>32;								$pq +=  6;	$postQ -=  6;	break;	\
case 0x6E:	/*  7, 0   */	*( (ui64*) ( $pq	) )= $a;									$pq +=  7;	$postQ -=  7;	break;	\
case 0x6F:	/*  8, 0   */	*( (ui64*) ( $pq	) )= $a;									$pq +=  8;	$postQ -=  8;	break;	\
case 0x70:	/*  1, 0   */	*( (ui08*) ( $pq	) )= $a;									$pq +=  1;	$postQ -=  1;	break;	\
case 0x71:	/*  2, 0   */	*( (ui16*) ( $pq	) )= $a;									$pq +=  2;	$postQ -=  2;	break;	\
case 0x72:	/*  3, 0   */	*( (ui32*) ( $pq	) )= $a;									$pq +=  3;	$postQ -=  3;	break;	\
case 0x73:	/*  4, 0   */	*( (ui32*) ( $pq	) )= $a;									$pq +=  4;	$postQ -=  4;	break;	\
case 0x74:	/*  5, 0   */	*( (ui32*) ( $pq	) )= $a;									\
						*( (ui08*) ( $pq +4 	) )= $a>>32;								$pq +=  5;	$postQ -=  5;	break;	\
case 0x75:	/*  6, 0   */	*( (ui32*) ( $pq	) )= $a;									\
						*( (ui16*) ( $pq +4 	) )= $a>>32;								$pq +=  6;	$postQ -=  6;	break;	\
case 0x76:	/*  7, 0   */	*( (ui64*) ( $pq	) )= $a;									$pq +=  7;	$postQ -=  7;	break;	\
case 0x77:	/*  8, 0   */	*( (ui64*) ( $pq	) )= $a;									$pq +=  8;	$postQ -=  8;	break;	\
case 0x78:	/*  1, 0   */	*( (ui08*) ( $pq	) )= $a;									$pq +=  1;	$postQ -=  1;	break;	\
case 0x79:	/*  2, 0   */	*( (ui16*) ( $pq	) )= $a;									$pq +=  2;	$postQ -=  2;	break;	\
case 0x7A:	/*  3, 0   */	*( (ui32*) ( $pq	) )= $a;									$pq +=  3;	$postQ -=  3;	break;	\
case 0x7B:	/*  4, 0   */	*( (ui32*) ( $pq	) )= $a;									$pq +=  4;	$postQ -=  4;	break;	\
case 0x7C:	/*  5, 0   */	*( (ui32*) ( $pq	) )= $a;									\
						*( (ui08*) ( $pq +4 	) )= $a>>32;								$pq +=  5;	$postQ -=  5;	break;	\
case 0x7D:	/*  6, 0   */	*( (ui32*) ( $pq	) )= $a;									\
						*( (ui16*) ( $pq +4 	) )= $a>>32;								$pq +=  6;	$postQ -=  6;	break;	\
case 0x7E:	/*  7, 0   */	*( (ui64*) ( $pq	) )= $a;									$pq +=  7;	$postQ -=  7;	break;	\
case 0x7F:	/*  8, 0   */	*( (ui64*) ( $pq	) )= $a;									$pq +=  8;	$postQ -=  8;	break;	\
\
/*	part 3 of 4:	A disabled;	B enabled	(just B)	*/	\
case 0x80:	/*  0, 1   */								\
case 0x81:	/*  0, 1   */								\
case 0x82:	/*  0, 1   */								\
case 0x83:	/*  0, 1   */								\
case 0x84:	/*  0, 1   */								\
case 0x85:	/*  0, 1   */								\
case 0x86:	/*  0, 1   */								\
case 0x87:	/*  0, 1   */								*( (ui08*) ( $pq	) )= $b;		$pq +=  1;	$postQ -=  1;	break;	\
case 0x88:	/*  0, 2   */								\
case 0x89:	/*  0, 2   */								\
case 0x8A:	/*  0, 2   */								\
case 0x8B:	/*  0, 2   */								\
case 0x8C:	/*  0, 2   */								\
case 0x8D:	/*  0, 2   */								\
case 0x8E:	/*  0, 2   */								\
case 0x8F:	/*  0, 2   */								*( (ui16*) ( $pq	) )= $b;		$pq +=  2;	$postQ -=  2;	break;	\
case 0x90:	/*  0, 3   */								\
case 0x91:	/*  0, 3   */								\
case 0x92:	/*  0, 3   */								\
case 0x93:	/*  0, 3   */								\
case 0x94:	/*  0, 3   */								\
case 0x95:	/*  0, 3   */								\
case 0x96:	/*  0, 3   */								\
case 0x97:	/*  0, 3   */								*( (ui32*) ( $pq	) )= $b;		$pq +=  3;	$postQ -=  3;	break;	\
case 0x98:	/*  0, 4   */								\
case 0x99:	/*  0, 4   */								\
case 0x9A:	/*  0, 4   */								\
case 0x9B:	/*  0, 4   */								\
case 0x9C:	/*  0, 4   */								\
case 0x9D:	/*  0, 4   */								\
case 0x9E:	/*  0, 4   */								\
case 0x9F:	/*  0, 4   */								*( (ui32*) ( $pq	) )= $b;		$pq +=  4;	$postQ -=  4;	break;	\
case 0xA0:	/*  0, 5   */								\
case 0xA1:	/*  0, 5   */								\
case 0xA2:	/*  0, 5   */								\
case 0xA3:	/*  0, 5   */								\
case 0xA4:	/*  0, 5   */								\
case 0xA5:	/*  0, 5   */								\
case 0xA6:	/*  0, 5   */								\
case 0xA7:	/*  0, 5   */								*( (ui32*) ( $pq	) )= $b;		\
													*( (ui08*) ( $pq +4 	) )= $b>>32;	$pq +=  5;	$postQ -=  5;	break;	\
case 0xA8:	/*  0, 6   */								\
case 0xA9:	/*  0, 6   */								\
case 0xAA:	/*  0, 6   */								\
case 0xAB:	/*  0, 6   */								\
case 0xAC:	/*  0, 6   */								\
case 0xAD:	/*  0, 6   */								\
case 0xAE:	/*  0, 6   */								\
case 0xAF:	/*  0, 6   */								*( (ui32*) ( $pq	) )= $b;		\
													*( (ui16*) ( $pq +4 	) )= $b>>32;	$pq +=  6;	$postQ -=  6;	break;	\
case 0xB0:	/*  0, 7   */								\
case 0xB1:	/*  0, 7   */								\
case 0xB2:	/*  0, 7   */								\
case 0xB3:	/*  0, 7   */								\
case 0xB4:	/*  0, 7   */								\
case 0xB5:	/*  0, 7   */								\
case 0xB6:	/*  0, 7   */								\
case 0xB7:	/*  0, 7   */								*( (ui64*) ( $pq	) )= $b;		$pq +=  7;	$postQ -=  7;	break;	\
case 0xB8:	/*  0, 8   */								\
case 0xB9:	/*  0, 8   */								\
case 0xBA:	/*  0, 8   */								\
case 0xBB:	/*  0, 8   */								\
case 0xBC:	/*  0, 8   */								\
case 0xBD:	/*  0, 8   */								\
case 0xBE:	/*  0, 8   */								\
case 0xBF:	/*  0, 8   */								*( (ui64*) ( $pq	) )= $b;		$pq +=  8;	$postQ -=  8;	break;	\
\
/*	part 4 of 4:	A enabled;	B enabled	(both)	*/	\
case 0xC0:	/*  1, 1   */	*( (ui08*) ( $pq	) )= $a;		*( (ui08*) ( $pq +1 	) )= $b;		$pq +=  2;	$postQ -=  2;	break;	\
case 0xC1:	/*  2, 1   */	*( (ui16*) ( $pq	) )= $a;		*( (ui08*) ( $pq +2 	) )= $b;		$pq +=  3;	$postQ -=  3;	break;	\
case 0xC2:	/*  3, 1   */	*( (ui32*) ( $pq	) )= $a;		*( (ui08*) ( $pq +3 	) )= $b;		$pq +=  4;	$postQ -=  4;	break;	\
case 0xC3:	/*  4, 1   */	*( (ui32*) ( $pq	) )= $a;		*( (ui08*) ( $pq +4 	) )= $b;		$pq +=  5;	$postQ -=  5;	break;	\
case 0xC4:	/*  5, 1   */	*( (ui32*) ( $pq	) )= $a;									\
						*( (ui08*) ( $pq +4 	) )= $a>>32;	*( (ui08*) ( $pq +5 	) )= $b;		$pq +=  6;	$postQ -=  6;	break;	\
case 0xC5:	/*  6, 1   */	*( (ui64*) ( $pq	) )= $a;		*( (ui08*) ( $pq +6 	) )= $b;		$pq +=  7;	$postQ -=  7;	break;	\
case 0xC6:	/*  7, 1   */	*( (ui64*) ( $pq	) )= $a;		*( (ui08*) ( $pq +7 	) )= $b;		$pq +=  8;	$postQ -=  8;	break;	\
case 0xC7:	/*  8, 1   */	*( (ui64*) ( $pq	) )= $a;		*( (ui08*) ( $pq +8 	) )= $b;		$pq +=  9;	$postQ -=  9;	break;	\
case 0xC8:	/*  1, 2   */	*( (ui08*) ( $pq	) )= $a;		*( (ui16*) ( $pq +1 	) )= $b;		$pq +=  3;	$postQ -=  3;	break;	\
case 0xC9:	/*  2, 2   */	*( (ui16*) ( $pq	) )= $a;		*( (ui16*) ( $pq +2 	) )= $b;		$pq +=  4;	$postQ -=  4;	break;	\
case 0xCA:	/*  3, 2   */	*( (ui32*) ( $pq	) )= $a;		*( (ui16*) ( $pq +3 	) )= $b;		$pq +=  5;	$postQ -=  5;	break;	\
case 0xCB:	/*  4, 2   */	*( (ui32*) ( $pq	) )= $a;		*( (ui16*) ( $pq +4 	) )= $b;		$pq +=  6;	$postQ -=  6;	break;	\
case 0xCC:	/*  5, 2   */	*( (ui64*) ( $pq	) )= $a;		*( (ui16*) ( $pq +5 	) )= $b;		$pq +=  7;	$postQ -=  7;	break;	\
case 0xCD:	/*  6, 2   */	*( (ui64*) ( $pq	) )= $a;		*( (ui16*) ( $pq +6 	) )= $b;		$pq +=  8;	$postQ -=  8;	break;	\
case 0xCE:	/*  7, 2   */	*( (ui64*) ( $pq	) )= $a;		*( (ui16*) ( $pq +7 	) )= $b;		$pq +=  9;	$postQ -=  9;	break;	\
case 0xCF:	/*  8, 2   */	*( (ui64*) ( $pq	) )= $a;		*( (ui16*) ( $pq +8 	) )= $b;		$pq += 10;	$postQ -= 10;	break;	\
case 0xD0:	/*  1, 3   */	*( (ui08*) ( $pq	) )= $a;		*( (ui32*) ( $pq +1 	) )= $b;		$pq +=  4;	$postQ -=  4;	break;	\
case 0xD1:	/*  2, 3   */	*( (ui16*) ( $pq	) )= $a;		*( (ui32*) ( $pq +2 	) )= $b;		$pq +=  5;	$postQ -=  5;	break;	\
case 0xD2:	/*  3, 3   */	*( (ui32*) ( $pq	) )= $a;		*( (ui32*) ( $pq +3 	) )= $b;		$pq +=  6;	$postQ -=  6;	break;	\
case 0xD3:	/*  4, 3   */	*( (ui32*) ( $pq	) )= $a;		*( (ui32*) ( $pq +4 	) )= $b;		$pq +=  7;	$postQ -=  7;	break;	\
case 0xD4:	/*  5, 3   */	*( (ui64*) ( $pq	) )= $a;		*( (ui32*) ( $pq +5 	) )= $b;		$pq +=  8;	$postQ -=  8;	break;	\
case 0xD5:	/*  6, 3   */	*( (ui64*) ( $pq	) )= $a;		*( (ui32*) ( $pq +6 	) )= $b;		$pq +=  9;	$postQ -=  9;	break;	\
case 0xD6:	/*  7, 3   */	*( (ui64*) ( $pq	) )= $a;		*( (ui32*) ( $pq +7 	) )= $b;		$pq += 10;	$postQ -= 10;	break;	\
case 0xD7:	/*  8, 3   */	*( (ui64*) ( $pq	) )= $a;		*( (ui32*) ( $pq +8 	) )= $b;		$pq += 11;	$postQ -= 11;	break;	\
case 0xD8:	/*  1, 4   */	*( (ui08*) ( $pq	) )= $a;		*( (ui32*) ( $pq +1 	) )= $b;		$pq +=  5;	$postQ -=  5;	break;	\
case 0xD9:	/*  2, 4   */	*( (ui16*) ( $pq	) )= $a;		*( (ui32*) ( $pq +2 	) )= $b;		$pq +=  6;	$postQ -=  6;	break;	\
case 0xDA:	/*  3, 4   */	*( (ui32*) ( $pq	) )= $a;		*( (ui32*) ( $pq +3 	) )= $b;		$pq +=  7;	$postQ -=  7;	break;	\
case 0xDB:	/*  4, 4   */	*( (ui32*) ( $pq	) )= $a;		*( (ui32*) ( $pq +4 	) )= $b;		$pq +=  8;	$postQ -=  8;	break;	\
case 0xDC:	/*  5, 4   */	*( (ui64*) ( $pq	) )= $a;		*( (ui32*) ( $pq +5 	) )= $b;		$pq +=  9;	$postQ -=  9;	break;	\
case 0xDD:	/*  6, 4   */	*( (ui64*) ( $pq	) )= $a;		*( (ui32*) ( $pq +6 	) )= $b;		$pq += 10;	$postQ -= 10;	break;	\
case 0xDE:	/*  7, 4   */	*( (ui64*) ( $pq	) )= $a;		*( (ui32*) ( $pq +7 	) )= $b;		$pq += 11;	$postQ -= 11;	break;	\
case 0xDF:	/*  8, 4   */	*( (ui64*) ( $pq	) )= $a;		*( (ui32*) ( $pq +8 	) )= $b;		$pq += 12;	$postQ -= 12;	break;	\
case 0xE0:	/*  1, 5   */	*( (ui08*) ( $pq	) )= $a;		*( (ui32*) ( $pq +1 	) )= $b;		\
													*( (ui08*) ( $pq +5 	) )= $b>>32;	$pq +=  6;	$postQ -=  6;	break;	\
case 0xE1:	/*  2, 5   */	*( (ui16*) ( $pq	) )= $a;		*( (ui32*) ( $pq +2 	) )= $b;		\
													*( (ui08*) ( $pq +6 	) )= $b>>32;	$pq +=  7;	$postQ -=  7;	break;	\
case 0xE2:	/*  3, 5   */	*( (ui32*) ( $pq	) )= $a;		*( (ui32*) ( $pq +3 	) )= $b;		\
													*( (ui08*) ( $pq +7 	) )= $b>>32;	$pq +=  8;	$postQ -=  8;	break;	\
case 0xE3:	/*  4, 5   */	*( (ui32*) ( $pq	) )= $a;		*( (ui32*) ( $pq +4 	) )= $b;		\
													*( (ui08*) ( $pq +8 	) )= $b>>32;	$pq +=  9;	$postQ -=  9;	break;	\
case 0xE4:	/*  5, 5   */	*( (ui64*) ( $pq	) )= $a;		*( (ui32*) ( $pq +5 	) )= $b;		\
													*( (ui08*) ( $pq +9 	) )= $b>>32;	$pq += 10;	$postQ -= 10;	break;	\
case 0xE5:	/*  6, 5   */	*( (ui64*) ( $pq	) )= $a;		*( (ui32*) ( $pq +6 	) )= $b;		\
													*( (ui08*) ( $pq +10	) )= $b>>32;	$pq += 11;	$postQ -= 11;	break;	\
case 0xE6:	/*  7, 5   */	*( (ui64*) ( $pq	) )= $a;		*( (ui32*) ( $pq +7 	) )= $b;		\
													*( (ui08*) ( $pq +11	) )= $b>>32;	$pq += 12;	$postQ -= 12;	break;	\
case 0xE7:	/*  8, 5   */	*( (ui64*) ( $pq	) )= $a;		*( (ui32*) ( $pq +8 	) )= $b;		\
													*( (ui08*) ( $pq +12	) )= $b>>32;	$pq += 13;	$postQ -= 13;	break;	\
case 0xE8:	/*  1, 6   */	*( (ui08*) ( $pq	) )= $a;		*( (ui32*) ( $pq +1 	) )= $b;		\
													*( (ui16*) ( $pq +5 	) )= $b>>32;	$pq +=  7;	$postQ -=  7;	break;	\
case 0xE9:	/*  2, 6   */	*( (ui16*) ( $pq	) )= $a;		*( (ui32*) ( $pq +2 	) )= $b;		\
													*( (ui16*) ( $pq +6 	) )= $b>>32;	$pq +=  8;	$postQ -=  8;	break;	\
case 0xEA:	/*  3, 6   */	*( (ui32*) ( $pq	) )= $a;		*( (ui32*) ( $pq +3 	) )= $b;		\
													*( (ui16*) ( $pq +7 	) )= $b>>32;	$pq +=  9;	$postQ -=  9;	break;	\
case 0xEB:	/*  4, 6   */	*( (ui32*) ( $pq	) )= $a;		*( (ui32*) ( $pq +4 	) )= $b;		\
													*( (ui16*) ( $pq +8 	) )= $b>>32;	$pq += 10;	$postQ -= 10;	break;	\
case 0xEC:	/*  5, 6   */	*( (ui64*) ( $pq	) )= $a;		*( (ui32*) ( $pq +5 	) )= $b;		\
													*( (ui16*) ( $pq +9 	) )= $b>>32;	$pq += 11;	$postQ -= 11;	break;	\
case 0xED:	/*  6, 6   */	*( (ui64*) ( $pq	) )= $a;		*( (ui32*) ( $pq +6 	) )= $b;		\
													*( (ui16*) ( $pq +10	) )= $b>>32;	$pq += 12;	$postQ -= 12;	break;	\
case 0xEE:	/*  7, 6   */	*( (ui64*) ( $pq	) )= $a;		*( (ui32*) ( $pq +7 	) )= $b;		\
													*( (ui16*) ( $pq +11	) )= $b>>32;	$pq += 13;	$postQ -= 13;	break;	\
case 0xEF:	/*  8, 6   */	*( (ui64*) ( $pq	) )= $a;		*( (ui32*) ( $pq +8 	) )= $b;		\
													*( (ui16*) ( $pq +12	) )= $b>>32;	$pq += 14;	$postQ -= 14;	break;	\
case 0xF0:	/*  1, 7   */	*( (ui08*) ( $pq	) )= $a;		*( (ui64*) ( $pq +1 	) )= $b;		$pq +=  8;	$postQ -=  8;	break;	\
case 0xF1:	/*  2, 7   */	*( (ui16*) ( $pq	) )= $a;		*( (ui64*) ( $pq +2 	) )= $b;		$pq +=  9;	$postQ -=  9;	break;	\
case 0xF2:	/*  3, 7   */	*( (ui32*) ( $pq	) )= $a;		*( (ui64*) ( $pq +3 	) )= $b;		$pq += 10;	$postQ -= 10;	break;	\
case 0xF3:	/*  4, 7   */	*( (ui32*) ( $pq	) )= $a;		*( (ui64*) ( $pq +4 	) )= $b;		$pq += 11;	$postQ -= 11;	break;	\
case 0xF4:	/*  5, 7   */	*( (ui64*) ( $pq	) )= $a;		*( (ui64*) ( $pq +5 	) )= $b;		$pq += 12;	$postQ -= 12;	break;	\
case 0xF5:	/*  6, 7   */	*( (ui64*) ( $pq	) )= $a;		*( (ui64*) ( $pq +6 	) )= $b;		$pq += 13;	$postQ -= 13;	break;	\
case 0xF6:	/*  7, 7   */	*( (ui64*) ( $pq	) )= $a;		*( (ui64*) ( $pq +7 	) )= $b;		$pq += 14;	$postQ -= 14;	break;	\
case 0xF7:	/*  8, 7   */	*( (ui64*) ( $pq	) )= $a;		*( (ui64*) ( $pq +8 	) )= $b;		$pq += 15;	$postQ -= 15;	break;	\
case 0xF8:	/*  1, 8   */	*( (ui08*) ( $pq	) )= $a;		*( (ui64*) ( $pq +1 	) )= $b;		$pq +=  9;	$postQ -=  9;	break;	\
case 0xF9:	/*  2, 8   */	*( (ui16*) ( $pq	) )= $a;		*( (ui64*) ( $pq +2 	) )= $b;		$pq += 10;	$postQ -= 10;	break;	\
case 0xFA:	/*  3, 8   */	*( (ui32*) ( $pq	) )= $a;		*( (ui64*) ( $pq +3 	) )= $b;		$pq += 11;	$postQ -= 11;	break;	\
case 0xFB:	/*  4, 8   */	*( (ui32*) ( $pq	) )= $a;		*( (ui64*) ( $pq +4 	) )= $b;		$pq += 12;	$postQ -= 12;	break;	\
case 0xFC:	/*  5, 8   */	*( (ui64*) ( $pq	) )= $a;		*( (ui64*) ( $pq +5 	) )= $b;		$pq += 13;	$postQ -= 13;	break;	\
case 0xFD:	/*  6, 8   */	*( (ui64*) ( $pq	) )= $a;		*( (ui64*) ( $pq +6 	) )= $b;		$pq += 14;	$postQ -= 14;	break;	\
case 0xFE:	/*  7, 8   */	*( (ui64*) ( $pq	) )= $a;		*( (ui64*) ( $pq +7 	) )= $b;		$pq += 15;	$postQ -= 15;	break;	\
case 0xFF:	/*  8, 8   */	*( (ui64*) ( $pq	) )= $a;		*( (ui64*) ( $pq +8 	) )= $b;		$pq += 16;	$postQ -= 16;	break;	\

