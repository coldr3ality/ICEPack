/*	This file was programmatically generated.
		script:		gen_c_for__SwCASE_ICEqHEXL.h.pl
		last modified:	Fri May 15 18:44:12 2026	*/

#define	SwCASE_ICEqHEXL( $pq, $s )	/*	get the combined width of [a, b] as printed in hex 	*/		\
\
/*	part 1 of 4:	A disabled;	B disabled	(neither)	*/	\
case 0x00:	/*  1, 1   */	$s=  5;																					break;	\
case 0x01:	/*  2, 1   */	/* ... */																					\
case 0x02:	/*  3, 1   */	/* ... */																					\
case 0x03:	/*  4, 1   */	/* ... */																					\
case 0x04:	/*  5, 1   */	/* ... */																					\
case 0x05:	/*  6, 1   */	/* ... */																					\
case 0x06:	/*  7, 1   */	/* ... */																					\
case 0x07:	/*  8, 1   */	/* ... */																					\
case 0x08:	/*  1, 2   */	$s=  9;																					break;	\
case 0x09:	/*  2, 2   */	$s=  5;																					break;	\
case 0x0A:	/*  3, 2   */	/* ... */																					\
case 0x0B:	/*  4, 2   */	/* ... */																					\
case 0x0C:	/*  5, 2   */	/* ... */																					\
case 0x0D:	/*  6, 2   */	/* ... */																					\
case 0x0E:	/*  7, 2   */	/* ... */																					\
case 0x0F:	/*  8, 2   */	/* ... */																					\
case 0x10:	/*  1, 3   */	/* ... */																					\
case 0x11:	/*  2, 3   */	$s=  9;																					break;	\
case 0x12:	/*  3, 3   */	$s=  5;																					break;	\
case 0x13:	/*  4, 3   */	/* ... */																					\
case 0x14:	/*  5, 3   */	/* ... */																					\
case 0x15:	/*  6, 3   */	/* ... */																					\
case 0x16:	/*  7, 3   */	/* ... */																					\
case 0x17:	/*  8, 3   */	/* ... */																					\
case 0x18:	/*  1, 4   */	/* ... */																					\
case 0x19:	/*  2, 4   */	/* ... */																					\
case 0x1A:	/*  3, 4   */	$s=  9;																					break;	\
case 0x1B:	/*  4, 4   */	$s=  5;																					break;	\
case 0x1C:	/*  5, 4   */	/* ... */																					\
case 0x1D:	/*  6, 4   */	/* ... */																					\
case 0x1E:	/*  7, 4   */	/* ... */																					\
case 0x1F:	/*  8, 4   */	/* ... */																					\
case 0x20:	/*  1, 5   */	/* ... */																					\
case 0x21:	/*  2, 5   */	/* ... */																					\
case 0x22:	/*  3, 5   */	/* ... */																					\
case 0x23:	/*  4, 5   */	$s=  9;																					break;	\
case 0x24:	/*  5, 5   */	$s=  5;																					break;	\
case 0x25:	/*  6, 5   */	/* ... */																					\
case 0x26:	/*  7, 5   */	/* ... */																					\
case 0x27:	/*  8, 5   */	/* ... */																					\
case 0x28:	/*  1, 6   */	/* ... */																					\
case 0x29:	/*  2, 6   */	/* ... */																					\
case 0x2A:	/*  3, 6   */	/* ... */																					\
case 0x2B:	/*  4, 6   */	/* ... */																					\
case 0x2C:	/*  5, 6   */	$s=  9;																					break;	\
case 0x2D:	/*  6, 6   */	$s=  5;																					break;	\
case 0x2E:	/*  7, 6   */	/* ... */																					\
case 0x2F:	/*  8, 6   */	/* ... */																					\
case 0x30:	/*  1, 7   */	/* ... */																					\
case 0x31:	/*  2, 7   */	/* ... */																					\
case 0x32:	/*  3, 7   */	/* ... */																					\
case 0x33:	/*  4, 7   */	/* ... */																					\
case 0x34:	/*  5, 7   */	/* ... */																					\
case 0x35:	/*  6, 7   */	$s=  9;																					break;	\
case 0x36:	/*  7, 7   */	$s=  5;																					break;	\
case 0x37:	/*  8, 7   */	/* ... */																					\
case 0x38:	/*  1, 8   */	/* ... */																					\
case 0x39:	/*  2, 8   */	/* ... */																					\
case 0x3A:	/*  3, 8   */	/* ... */																					\
case 0x3B:	/*  4, 8   */	/* ... */																					\
case 0x3C:	/*  5, 8   */	/* ... */																					\
case 0x3D:	/*  6, 8   */	/* ... */																					\
case 0x3E:	/*  7, 8   */	$s=  9;																					break;	\
case 0x3F:	/*  8, 8   */	$s=  5;																					break;	\
\
/*	part 2 of 4:	A enabled;	B disabled	(just A)	*/	\
case 0x40:	/*  1, 0   */	$s= 23-(__builtin_clzll( *( (ui08*) $pq		)    	) >>2);											break;	\
case 0x41:	/*  2, 0   */	$s= 23-(__builtin_clzll( *( (ui16*) $pq		)    	) >>2);											break;	\
case 0x42:	/*  3, 0   */	$s= 23-(__builtin_clzll( *( (ui32*) ($pq -1 )	)>>8  ) >>2);											break;	\
case 0x43:	/*  4, 0   */	$s= 23-(__builtin_clzll( *( (ui32*) $pq		)    	) >>2);											break;	\
case 0x44:	/*  5, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) ($pq -3 )	)>>24 ) >>2);											break;	\
case 0x45:	/*  6, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) ($pq -2 )	)>>16 ) >>2);											break;	\
case 0x46:	/*  7, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) ($pq -1 )	)>>8  ) >>2);											break;	\
case 0x47:	/*  8, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) $pq		)    	) >>2);											break;	\
case 0x48:	/*  1, 0   */	$s= 23-(__builtin_clzll( *( (ui08*) $pq		)    	) >>2);											break;	\
case 0x49:	/*  2, 0   */	$s= 23-(__builtin_clzll( *( (ui16*) $pq		)    	) >>2);											break;	\
case 0x4A:	/*  3, 0   */	$s= 23-(__builtin_clzll( *( (ui32*) ($pq -1 )	)>>8  ) >>2);											break;	\
case 0x4B:	/*  4, 0   */	$s= 23-(__builtin_clzll( *( (ui32*) $pq		)    	) >>2);											break;	\
case 0x4C:	/*  5, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) ($pq -3 )	)>>24 ) >>2);											break;	\
case 0x4D:	/*  6, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) ($pq -2 )	)>>16 ) >>2);											break;	\
case 0x4E:	/*  7, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) ($pq -1 )	)>>8  ) >>2);											break;	\
case 0x4F:	/*  8, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) $pq		)    	) >>2);											break;	\
case 0x50:	/*  1, 0   */	$s= 23-(__builtin_clzll( *( (ui08*) $pq		)    	) >>2);											break;	\
case 0x51:	/*  2, 0   */	$s= 23-(__builtin_clzll( *( (ui16*) $pq		)    	) >>2);											break;	\
case 0x52:	/*  3, 0   */	$s= 23-(__builtin_clzll( *( (ui32*) ($pq -1 )	)>>8  ) >>2);											break;	\
case 0x53:	/*  4, 0   */	$s= 23-(__builtin_clzll( *( (ui32*) $pq		)    	) >>2);											break;	\
case 0x54:	/*  5, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) ($pq -3 )	)>>24 ) >>2);											break;	\
case 0x55:	/*  6, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) ($pq -2 )	)>>16 ) >>2);											break;	\
case 0x56:	/*  7, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) ($pq -1 )	)>>8  ) >>2);											break;	\
case 0x57:	/*  8, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) $pq		)    	) >>2);											break;	\
case 0x58:	/*  1, 0   */	$s= 23-(__builtin_clzll( *( (ui08*) $pq		)    	) >>2);											break;	\
case 0x59:	/*  2, 0   */	$s= 23-(__builtin_clzll( *( (ui16*) $pq		)    	) >>2);											break;	\
case 0x5A:	/*  3, 0   */	$s= 23-(__builtin_clzll( *( (ui32*) ($pq -1 )	)>>8  ) >>2);											break;	\
case 0x5B:	/*  4, 0   */	$s= 23-(__builtin_clzll( *( (ui32*) $pq		)    	) >>2);											break;	\
case 0x5C:	/*  5, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) ($pq -3 )	)>>24 ) >>2);											break;	\
case 0x5D:	/*  6, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) ($pq -2 )	)>>16 ) >>2);											break;	\
case 0x5E:	/*  7, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) ($pq -1 )	)>>8  ) >>2);											break;	\
case 0x5F:	/*  8, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) $pq		)    	) >>2);											break;	\
case 0x60:	/*  1, 0   */	$s= 23-(__builtin_clzll( *( (ui08*) $pq		)    	) >>2);											break;	\
case 0x61:	/*  2, 0   */	$s= 23-(__builtin_clzll( *( (ui16*) $pq		)    	) >>2);											break;	\
case 0x62:	/*  3, 0   */	$s= 23-(__builtin_clzll( *( (ui32*) ($pq -1 )	)>>8  ) >>2);											break;	\
case 0x63:	/*  4, 0   */	$s= 23-(__builtin_clzll( *( (ui32*) $pq		)    	) >>2);											break;	\
case 0x64:	/*  5, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) ($pq -3 )	)>>24 ) >>2);											break;	\
case 0x65:	/*  6, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) ($pq -2 )	)>>16 ) >>2);											break;	\
case 0x66:	/*  7, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) ($pq -1 )	)>>8  ) >>2);											break;	\
case 0x67:	/*  8, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) $pq		)    	) >>2);											break;	\
case 0x68:	/*  1, 0   */	$s= 23-(__builtin_clzll( *( (ui08*) $pq		)    	) >>2);											break;	\
case 0x69:	/*  2, 0   */	$s= 23-(__builtin_clzll( *( (ui16*) $pq		)    	) >>2);											break;	\
case 0x6A:	/*  3, 0   */	$s= 23-(__builtin_clzll( *( (ui32*) ($pq -1 )	)>>8  ) >>2);											break;	\
case 0x6B:	/*  4, 0   */	$s= 23-(__builtin_clzll( *( (ui32*) $pq		)    	) >>2);											break;	\
case 0x6C:	/*  5, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) ($pq -3 )	)>>24 ) >>2);											break;	\
case 0x6D:	/*  6, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) ($pq -2 )	)>>16 ) >>2);											break;	\
case 0x6E:	/*  7, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) ($pq -1 )	)>>8  ) >>2);											break;	\
case 0x6F:	/*  8, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) $pq		)    	) >>2);											break;	\
case 0x70:	/*  1, 0   */	$s= 23-(__builtin_clzll( *( (ui08*) $pq		)    	) >>2);											break;	\
case 0x71:	/*  2, 0   */	$s= 23-(__builtin_clzll( *( (ui16*) $pq		)    	) >>2);											break;	\
case 0x72:	/*  3, 0   */	$s= 23-(__builtin_clzll( *( (ui32*) ($pq -1 )	)>>8  ) >>2);											break;	\
case 0x73:	/*  4, 0   */	$s= 23-(__builtin_clzll( *( (ui32*) $pq		)    	) >>2);											break;	\
case 0x74:	/*  5, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) ($pq -3 )	)>>24 ) >>2);											break;	\
case 0x75:	/*  6, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) ($pq -2 )	)>>16 ) >>2);											break;	\
case 0x76:	/*  7, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) ($pq -1 )	)>>8  ) >>2);											break;	\
case 0x77:	/*  8, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) $pq		)    	) >>2);											break;	\
case 0x78:	/*  1, 0   */	$s= 23-(__builtin_clzll( *( (ui08*) $pq		)    	) >>2);											break;	\
case 0x79:	/*  2, 0   */	$s= 23-(__builtin_clzll( *( (ui16*) $pq		)    	) >>2);											break;	\
case 0x7A:	/*  3, 0   */	$s= 23-(__builtin_clzll( *( (ui32*) ($pq -1 )	)>>8  ) >>2);											break;	\
case 0x7B:	/*  4, 0   */	$s= 23-(__builtin_clzll( *( (ui32*) $pq		)    	) >>2);											break;	\
case 0x7C:	/*  5, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) ($pq -3 )	)>>24 ) >>2);											break;	\
case 0x7D:	/*  6, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) ($pq -2 )	)>>16 ) >>2);											break;	\
case 0x7E:	/*  7, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) ($pq -1 )	)>>8  ) >>2);											break;	\
case 0x7F:	/*  8, 0   */	$s= 23-(__builtin_clzll( *( (ui64*) $pq		)    	) >>2);											break;	\
\
/*	part 3 of 4:	A disabled;	B enabled	(just B)	*/	\
case 0x80:	/*  1, 0   */											$s= 23	-	(__builtin_clzll( *( (ui08*) $pq		)    	) >>2);		break;	\
case 0x81:	/*  1, 1   */											$s= 23	-	(__builtin_clzll( *( (ui08*) $pq		)    	) >>2);		break;	\
case 0x82:	/*  1, 2   */											$s= 23	-	(__builtin_clzll( *( (ui08*) $pq		)    	) >>2);		break;	\
case 0x83:	/*  1, 3   */											$s= 23	-	(__builtin_clzll( *( (ui08*) $pq		)    	) >>2);		break;	\
case 0x84:	/*  1, 4   */											$s= 23	-	(__builtin_clzll( *( (ui08*) $pq		)    	) >>2);		break;	\
case 0x85:	/*  1, 5   */											$s= 23	-	(__builtin_clzll( *( (ui08*) $pq		)    	) >>2);		break;	\
case 0x86:	/*  1, 6   */											$s= 23	-	(__builtin_clzll( *( (ui08*) $pq		)    	) >>2);		break;	\
case 0x87:	/*  1, 7   */											$s= 23	-	(__builtin_clzll( *( (ui08*) $pq		)    	) >>2);		break;	\
case 0x88:	/*  2, 0   */											$s= 23	-	(__builtin_clzll( *( (ui16*) $pq		)    	) >>2);		break;	\
case 0x89:	/*  2, 1   */											$s= 23	-	(__builtin_clzll( *( (ui16*) $pq		)    	) >>2);		break;	\
case 0x8A:	/*  2, 2   */											$s= 23	-	(__builtin_clzll( *( (ui16*) $pq		)    	) >>2);		break;	\
case 0x8B:	/*  2, 3   */											$s= 23	-	(__builtin_clzll( *( (ui16*) $pq		)    	) >>2);		break;	\
case 0x8C:	/*  2, 4   */											$s= 23	-	(__builtin_clzll( *( (ui16*) $pq		)    	) >>2);		break;	\
case 0x8D:	/*  2, 5   */											$s= 23	-	(__builtin_clzll( *( (ui16*) $pq		)    	) >>2);		break;	\
case 0x8E:	/*  2, 6   */											$s= 23	-	(__builtin_clzll( *( (ui16*) $pq		)    	) >>2);		break;	\
case 0x8F:	/*  2, 7   */											$s= 23	-	(__builtin_clzll( *( (ui16*) $pq		)    	) >>2);		break;	\
case 0x90:	/*  3, 0   */											$s= 23	-	(__builtin_clzll( *( (ui32*) ($pq -1 )	)>>8  ) >>2);		break;	\
case 0x91:	/*  3, 1   */											$s= 23	-	(__builtin_clzll( *( (ui32*) ($pq -1 )	)>>8  ) >>2);		break;	\
case 0x92:	/*  3, 2   */											$s= 23	-	(__builtin_clzll( *( (ui32*) ($pq -1 )	)>>8  ) >>2);		break;	\
case 0x93:	/*  3, 3   */											$s= 23	-	(__builtin_clzll( *( (ui32*) ($pq -1 )	)>>8  ) >>2);		break;	\
case 0x94:	/*  3, 4   */											$s= 23	-	(__builtin_clzll( *( (ui32*) ($pq -1 )	)>>8  ) >>2);		break;	\
case 0x95:	/*  3, 5   */											$s= 23	-	(__builtin_clzll( *( (ui32*) ($pq -1 )	)>>8  ) >>2);		break;	\
case 0x96:	/*  3, 6   */											$s= 23	-	(__builtin_clzll( *( (ui32*) ($pq -1 )	)>>8  ) >>2);		break;	\
case 0x97:	/*  3, 7   */											$s= 23	-	(__builtin_clzll( *( (ui32*) ($pq -1 )	)>>8  ) >>2);		break;	\
case 0x98:	/*  4, 0   */											$s= 23	-	(__builtin_clzll( *( (ui32*) $pq		)    	) >>2);		break;	\
case 0x99:	/*  4, 1   */											$s= 23	-	(__builtin_clzll( *( (ui32*) $pq		)    	) >>2);		break;	\
case 0x9A:	/*  4, 2   */											$s= 23	-	(__builtin_clzll( *( (ui32*) $pq		)    	) >>2);		break;	\
case 0x9B:	/*  4, 3   */											$s= 23	-	(__builtin_clzll( *( (ui32*) $pq		)    	) >>2);		break;	\
case 0x9C:	/*  4, 4   */											$s= 23	-	(__builtin_clzll( *( (ui32*) $pq		)    	) >>2);		break;	\
case 0x9D:	/*  4, 5   */											$s= 23	-	(__builtin_clzll( *( (ui32*) $pq		)    	) >>2);		break;	\
case 0x9E:	/*  4, 6   */											$s= 23	-	(__builtin_clzll( *( (ui32*) $pq		)    	) >>2);		break;	\
case 0x9F:	/*  4, 7   */											$s= 23	-	(__builtin_clzll( *( (ui32*) $pq		)    	) >>2);		break;	\
case 0xA0:	/*  5, 0   */											$s= 23	-	(__builtin_clzll( *( (ui64*) ($pq -3 )	)>>24 ) >>2);		break;	\
case 0xA1:	/*  5, 1   */											$s= 23	-	(__builtin_clzll( *( (ui64*) ($pq -3 )	)>>24 ) >>2);		break;	\
case 0xA2:	/*  5, 2   */											$s= 23	-	(__builtin_clzll( *( (ui64*) ($pq -3 )	)>>24 ) >>2);		break;	\
case 0xA3:	/*  5, 3   */											$s= 23	-	(__builtin_clzll( *( (ui64*) ($pq -3 )	)>>24 ) >>2);		break;	\
case 0xA4:	/*  5, 4   */											$s= 23	-	(__builtin_clzll( *( (ui64*) ($pq -3 )	)>>24 ) >>2);		break;	\
case 0xA5:	/*  5, 5   */											$s= 23	-	(__builtin_clzll( *( (ui64*) ($pq -3 )	)>>24 ) >>2);		break;	\
case 0xA6:	/*  5, 6   */											$s= 23	-	(__builtin_clzll( *( (ui64*) ($pq -3 )	)>>24 ) >>2);		break;	\
case 0xA7:	/*  5, 7   */											$s= 23	-	(__builtin_clzll( *( (ui64*) ($pq -3 )	)>>24 ) >>2);		break;	\
case 0xA8:	/*  6, 0   */											$s= 23	-	(__builtin_clzll( *( (ui64*) ($pq -2 )	)>>16 ) >>2);		break;	\
case 0xA9:	/*  6, 1   */											$s= 23	-	(__builtin_clzll( *( (ui64*) ($pq -2 )	)>>16 ) >>2);		break;	\
case 0xAA:	/*  6, 2   */											$s= 23	-	(__builtin_clzll( *( (ui64*) ($pq -2 )	)>>16 ) >>2);		break;	\
case 0xAB:	/*  6, 3   */											$s= 23	-	(__builtin_clzll( *( (ui64*) ($pq -2 )	)>>16 ) >>2);		break;	\
case 0xAC:	/*  6, 4   */											$s= 23	-	(__builtin_clzll( *( (ui64*) ($pq -2 )	)>>16 ) >>2);		break;	\
case 0xAD:	/*  6, 5   */											$s= 23	-	(__builtin_clzll( *( (ui64*) ($pq -2 )	)>>16 ) >>2);		break;	\
case 0xAE:	/*  6, 6   */											$s= 23	-	(__builtin_clzll( *( (ui64*) ($pq -2 )	)>>16 ) >>2);		break;	\
case 0xAF:	/*  6, 7   */											$s= 23	-	(__builtin_clzll( *( (ui64*) ($pq -2 )	)>>16 ) >>2);		break;	\
case 0xB0:	/*  7, 0   */											$s= 23	-	(__builtin_clzll( *( (ui64*) ($pq -1 )	)>>8  ) >>2);		break;	\
case 0xB1:	/*  7, 1   */											$s= 23	-	(__builtin_clzll( *( (ui64*) ($pq -1 )	)>>8  ) >>2);		break;	\
case 0xB2:	/*  7, 2   */											$s= 23	-	(__builtin_clzll( *( (ui64*) ($pq -1 )	)>>8  ) >>2);		break;	\
case 0xB3:	/*  7, 3   */											$s= 23	-	(__builtin_clzll( *( (ui64*) ($pq -1 )	)>>8  ) >>2);		break;	\
case 0xB4:	/*  7, 4   */											$s= 23	-	(__builtin_clzll( *( (ui64*) ($pq -1 )	)>>8  ) >>2);		break;	\
case 0xB5:	/*  7, 5   */											$s= 23	-	(__builtin_clzll( *( (ui64*) ($pq -1 )	)>>8  ) >>2);		break;	\
case 0xB6:	/*  7, 6   */											$s= 23	-	(__builtin_clzll( *( (ui64*) ($pq -1 )	)>>8  ) >>2);		break;	\
case 0xB7:	/*  7, 7   */											$s= 23	-	(__builtin_clzll( *( (ui64*) ($pq -1 )	)>>8  ) >>2);		break;	\
case 0xB8:	/*  8, 0   */											$s= 23	-	(__builtin_clzll( *( (ui64*) $pq		)    	) >>2);		break;	\
case 0xB9:	/*  8, 1   */											$s= 23	-	(__builtin_clzll( *( (ui64*) $pq		)    	) >>2);		break;	\
case 0xBA:	/*  8, 2   */											$s= 23	-	(__builtin_clzll( *( (ui64*) $pq		)    	) >>2);		break;	\
case 0xBB:	/*  8, 3   */											$s= 23	-	(__builtin_clzll( *( (ui64*) $pq		)    	) >>2);		break;	\
case 0xBC:	/*  8, 4   */											$s= 23	-	(__builtin_clzll( *( (ui64*) $pq		)    	) >>2);		break;	\
case 0xBD:	/*  8, 5   */											$s= 23	-	(__builtin_clzll( *( (ui64*) $pq		)    	) >>2);		break;	\
case 0xBE:	/*  8, 6   */											$s= 23	-	(__builtin_clzll( *( (ui64*) $pq		)    	) >>2);		break;	\
case 0xBF:	/*  8, 7   */											$s= 23	-	(__builtin_clzll( *( (ui64*) $pq		)    	) >>2);		break;	\
\
/*	part 4 of 4:	A enabled;	B enabled	(both)	*/	\
case 0xC0:	/*  1, 1   */	$s= 39-(__builtin_clzll( *( (ui08*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui08*) ($pq +1 )	)    	) >>2);		break;	\
case 0xC1:	/*  2, 1   */	$s= 39-(__builtin_clzll( *( (ui16*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui08*) ($pq +2 )	)    	) >>2);		break;	\
case 0xC2:	/*  3, 1   */	$s= 39-(__builtin_clzll( *( (ui32*) ($pq -1 )	)>>8  ) >>2)	-	(__builtin_clz( *( (ui08*) ($pq +3 )	)    	) >>2);		break;	\
case 0xC3:	/*  4, 1   */	$s= 39-(__builtin_clzll( *( (ui32*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui08*) ($pq +4 )	)    	) >>2);		break;	\
case 0xC4:	/*  5, 1   */	$s= 39-(__builtin_clzll( *( (ui64*) ($pq -3 )	)>>24 ) >>2)	-	(__builtin_clz( *( (ui08*) ($pq +5 )	)    	) >>2);		break;	\
case 0xC5:	/*  6, 1   */	$s= 39-(__builtin_clzll( *( (ui64*) ($pq -2 )	)>>16 ) >>2)	-	(__builtin_clz( *( (ui08*) ($pq +6 )	)    	) >>2);		break;	\
case 0xC6:	/*  7, 1   */	$s= 39-(__builtin_clzll( *( (ui64*) ($pq -1 )	)>>8  ) >>2)	-	(__builtin_clz( *( (ui08*) ($pq +7 )	)    	) >>2);		break;	\
case 0xC7:	/*  8, 1   */	$s= 39-(__builtin_clzll( *( (ui64*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui08*) ($pq +8 )	)    	) >>2);		break;	\
case 0xC8:	/*  1, 2   */	$s= 39-(__builtin_clzll( *( (ui08*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui16*) ($pq +1 )	)    	) >>2);		break;	\
case 0xC9:	/*  2, 2   */	$s= 39-(__builtin_clzll( *( (ui16*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui16*) ($pq +2 )	)    	) >>2);		break;	\
case 0xCA:	/*  3, 2   */	$s= 39-(__builtin_clzll( *( (ui32*) ($pq -1 )	)>>8  ) >>2)	-	(__builtin_clz( *( (ui16*) ($pq +3 )	)    	) >>2);		break;	\
case 0xCB:	/*  4, 2   */	$s= 39-(__builtin_clzll( *( (ui32*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui16*) ($pq +4 )	)    	) >>2);		break;	\
case 0xCC:	/*  5, 2   */	$s= 39-(__builtin_clzll( *( (ui64*) ($pq -3 )	)>>24 ) >>2)	-	(__builtin_clz( *( (ui16*) ($pq +5 )	)    	) >>2);		break;	\
case 0xCD:	/*  6, 2   */	$s= 39-(__builtin_clzll( *( (ui64*) ($pq -2 )	)>>16 ) >>2)	-	(__builtin_clz( *( (ui16*) ($pq +6 )	)    	) >>2);		break;	\
case 0xCE:	/*  7, 2   */	$s= 39-(__builtin_clzll( *( (ui64*) ($pq -1 )	)>>8  ) >>2)	-	(__builtin_clz( *( (ui16*) ($pq +7 )	)    	) >>2);		break;	\
case 0xCF:	/*  8, 2   */	$s= 39-(__builtin_clzll( *( (ui64*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui16*) ($pq +8 )	)    	) >>2);		break;	\
case 0xD0:	/*  1, 3   */	$s= 39-(__builtin_clzll( *( (ui08*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui32*) $pq		)>>8  ) >>2);		break;	\
case 0xD1:	/*  2, 3   */	$s= 39-(__builtin_clzll( *( (ui16*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui32*) ($pq +1 )	)>>8  ) >>2);		break;	\
case 0xD2:	/*  3, 3   */	$s= 39-(__builtin_clzll( *( (ui32*) ($pq -1 )	)>>8  ) >>2)	-	(__builtin_clz( *( (ui32*) ($pq +2 )	)>>8  ) >>2);		break;	\
case 0xD3:	/*  4, 3   */	$s= 39-(__builtin_clzll( *( (ui32*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui32*) ($pq +3 )	)>>8  ) >>2);		break;	\
case 0xD4:	/*  5, 3   */	$s= 39-(__builtin_clzll( *( (ui64*) ($pq -3 )	)>>24 ) >>2)	-	(__builtin_clz( *( (ui32*) ($pq +4 )	)>>8  ) >>2);		break;	\
case 0xD5:	/*  6, 3   */	$s= 39-(__builtin_clzll( *( (ui64*) ($pq -2 )	)>>16 ) >>2)	-	(__builtin_clz( *( (ui32*) ($pq +5 )	)>>8  ) >>2);		break;	\
case 0xD6:	/*  7, 3   */	$s= 39-(__builtin_clzll( *( (ui64*) ($pq -1 )	)>>8  ) >>2)	-	(__builtin_clz( *( (ui32*) ($pq +6 )	)>>8  ) >>2);		break;	\
case 0xD7:	/*  8, 3   */	$s= 39-(__builtin_clzll( *( (ui64*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui32*) ($pq +7 )	)>>8  ) >>2);		break;	\
case 0xD8:	/*  1, 4   */	$s= 39-(__builtin_clzll( *( (ui08*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui32*) ($pq +1 )	)    	) >>2);		break;	\
case 0xD9:	/*  2, 4   */	$s= 39-(__builtin_clzll( *( (ui16*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui32*) ($pq +2 )	)    	) >>2);		break;	\
case 0xDA:	/*  3, 4   */	$s= 39-(__builtin_clzll( *( (ui32*) ($pq -1 )	)>>8  ) >>2)	-	(__builtin_clz( *( (ui32*) ($pq +3 )	)    	) >>2);		break;	\
case 0xDB:	/*  4, 4   */	$s= 39-(__builtin_clzll( *( (ui32*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui32*) ($pq +4 )	)    	) >>2);		break;	\
case 0xDC:	/*  5, 4   */	$s= 39-(__builtin_clzll( *( (ui64*) ($pq -3 )	)>>24 ) >>2)	-	(__builtin_clz( *( (ui32*) ($pq +5 )	)    	) >>2);		break;	\
case 0xDD:	/*  6, 4   */	$s= 39-(__builtin_clzll( *( (ui64*) ($pq -2 )	)>>16 ) >>2)	-	(__builtin_clz( *( (ui32*) ($pq +6 )	)    	) >>2);		break;	\
case 0xDE:	/*  7, 4   */	$s= 39-(__builtin_clzll( *( (ui64*) ($pq -1 )	)>>8  ) >>2)	-	(__builtin_clz( *( (ui32*) ($pq +7 )	)    	) >>2);		break;	\
case 0xDF:	/*  8, 4   */	$s= 39-(__builtin_clzll( *( (ui64*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui32*) ($pq +8 )	)    	) >>2);		break;	\
case 0xE0:	/*  1, 5   */	$s= 39-(__builtin_clzll( *( (ui08*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui64*) ($pq -2 )	)>>24 ) >>2);		break;	\
case 0xE1:	/*  2, 5   */	$s= 39-(__builtin_clzll( *( (ui16*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui64*) ($pq -1 )	)>>24 ) >>2);		break;	\
case 0xE2:	/*  3, 5   */	$s= 39-(__builtin_clzll( *( (ui32*) ($pq -1 )	)>>8  ) >>2)	-	(__builtin_clz( *( (ui64*) $pq		)>>24 ) >>2);		break;	\
case 0xE3:	/*  4, 5   */	$s= 39-(__builtin_clzll( *( (ui32*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +1 )	)>>24 ) >>2);		break;	\
case 0xE4:	/*  5, 5   */	$s= 39-(__builtin_clzll( *( (ui64*) ($pq -3 )	)>>24 ) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +2 )	)>>24 ) >>2);		break;	\
case 0xE5:	/*  6, 5   */	$s= 39-(__builtin_clzll( *( (ui64*) ($pq -2 )	)>>16 ) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +3 )	)>>24 ) >>2);		break;	\
case 0xE6:	/*  7, 5   */	$s= 39-(__builtin_clzll( *( (ui64*) ($pq -1 )	)>>8  ) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +4 )	)>>24 ) >>2);		break;	\
case 0xE7:	/*  8, 5   */	$s= 39-(__builtin_clzll( *( (ui64*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +5 )	)>>24 ) >>2);		break;	\
case 0xE8:	/*  1, 6   */	$s= 39-(__builtin_clzll( *( (ui08*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui64*) ($pq -1 )	)>>16 ) >>2);		break;	\
case 0xE9:	/*  2, 6   */	$s= 39-(__builtin_clzll( *( (ui16*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui64*) $pq		)>>16 ) >>2);		break;	\
case 0xEA:	/*  3, 6   */	$s= 39-(__builtin_clzll( *( (ui32*) ($pq -1 )	)>>8  ) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +1 )	)>>16 ) >>2);		break;	\
case 0xEB:	/*  4, 6   */	$s= 39-(__builtin_clzll( *( (ui32*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +2 )	)>>16 ) >>2);		break;	\
case 0xEC:	/*  5, 6   */	$s= 39-(__builtin_clzll( *( (ui64*) ($pq -3 )	)>>24 ) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +3 )	)>>16 ) >>2);		break;	\
case 0xED:	/*  6, 6   */	$s= 39-(__builtin_clzll( *( (ui64*) ($pq -2 )	)>>16 ) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +4 )	)>>16 ) >>2);		break;	\
case 0xEE:	/*  7, 6   */	$s= 39-(__builtin_clzll( *( (ui64*) ($pq -1 )	)>>8  ) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +5 )	)>>16 ) >>2);		break;	\
case 0xEF:	/*  8, 6   */	$s= 39-(__builtin_clzll( *( (ui64*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +6 )	)>>16 ) >>2);		break;	\
case 0xF0:	/*  1, 7   */	$s= 39-(__builtin_clzll( *( (ui08*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui64*) $pq		)>>8  ) >>2);		break;	\
case 0xF1:	/*  2, 7   */	$s= 39-(__builtin_clzll( *( (ui16*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +1 )	)>>8  ) >>2);		break;	\
case 0xF2:	/*  3, 7   */	$s= 39-(__builtin_clzll( *( (ui32*) ($pq -1 )	)>>8  ) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +2 )	)>>8  ) >>2);		break;	\
case 0xF3:	/*  4, 7   */	$s= 39-(__builtin_clzll( *( (ui32*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +3 )	)>>8  ) >>2);		break;	\
case 0xF4:	/*  5, 7   */	$s= 39-(__builtin_clzll( *( (ui64*) ($pq -3 )	)>>24 ) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +4 )	)>>8  ) >>2);		break;	\
case 0xF5:	/*  6, 7   */	$s= 39-(__builtin_clzll( *( (ui64*) ($pq -2 )	)>>16 ) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +5 )	)>>8  ) >>2);		break;	\
case 0xF6:	/*  7, 7   */	$s= 39-(__builtin_clzll( *( (ui64*) ($pq -1 )	)>>8  ) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +6 )	)>>8  ) >>2);		break;	\
case 0xF7:	/*  8, 7   */	$s= 39-(__builtin_clzll( *( (ui64*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +7 )	)>>8  ) >>2);		break;	\
case 0xF8:	/*  1, 8   */	$s= 39-(__builtin_clzll( *( (ui08*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +1 )	)    	) >>2);		break;	\
case 0xF9:	/*  2, 8   */	$s= 39-(__builtin_clzll( *( (ui16*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +2 )	)    	) >>2);		break;	\
case 0xFA:	/*  3, 8   */	$s= 39-(__builtin_clzll( *( (ui32*) ($pq -1 )	)>>8  ) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +3 )	)    	) >>2);		break;	\
case 0xFB:	/*  4, 8   */	$s= 39-(__builtin_clzll( *( (ui32*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +4 )	)    	) >>2);		break;	\
case 0xFC:	/*  5, 8   */	$s= 39-(__builtin_clzll( *( (ui64*) ($pq -3 )	)>>24 ) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +5 )	)    	) >>2);		break;	\
case 0xFD:	/*  6, 8   */	$s= 39-(__builtin_clzll( *( (ui64*) ($pq -2 )	)>>16 ) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +6 )	)    	) >>2);		break;	\
case 0xFE:	/*  7, 8   */	$s= 39-(__builtin_clzll( *( (ui64*) ($pq -1 )	)>>8  ) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +7 )	)    	) >>2);		break;	\
case 0xFF:	/*  8, 8   */	$s= 39-(__builtin_clzll( *( (ui64*) $pq		)    	) >>2)	-	(__builtin_clz( *( (ui64*) ($pq +8 )	)    	) >>2);		break;	\

