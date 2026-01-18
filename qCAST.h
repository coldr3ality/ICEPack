
#define qCASTp1x( $p0, $p1)\
case 0x0:	/* 1	*/ 	*( (ui08*	) ( $p0		) )= *( (ui08	*	) ( $p1		) );	break;	\
case 0x1:	/* 2	*/ 	*( (ui16*	) ( $p0		) )= *( (ui16	*	) ( $p1		) );	break;	\
case 0x2:	/* 3	*/ 	*( (ui16*	) ( $p0		) )= *( (ui16	*	) ( $p1		) );			\
					*( (ui08*	) ( $p0 +2 	) )= *( (ui08	*	) ( $p1 +2 	) );	break;	\
case 0x3:	/* 4	*/ 	*( (ui32*	) ( $p0		) )= *( (ui32	*	) ( $p1		) );	break;	\
case 0x4:	/* 5	*/ 	*( (ui32*	) ( $p0		) )= *( (ui32	*	) ( $p1		) );			\
					*( (ui08*	) ( $p0 +4 	) )= *( (ui08	*	) ( $p1 +4 	) );	break;	\
case 0x5:	/* 6	*/ 	*( (ui32*	) ( $p0		) )= *( (ui32	*	) ( $p1		) );			\
					*( (ui16*	) ( $p0 +4 	) )= *( (ui16	*	) ( $p1 +4 	) );	break;	\
case 0x6:	/* 7	*/ 	*( (ui32*	) ( $p0		) )= *( (ui32	*	) ( $p1		) );			\
					*( (ui16*	) ( $p0 +4 	) )= *( (ui16	*	) ( $p1 +4 	) );			\
					*( (ui08*	) ( $p0 +6 	) )= *( (ui08	*	) ( $p1 +6 	) );	break;	\
case 0x7:	/* 8	*/ 	*( (ui64*	) ( $p0		) )= *( (ui64	*	) ( $p1		) );	break

#define CASTqp1x( $p0, $p1, $q)		switch( $q){	qCASTp1x( $p0, $p1):	}

#define qCASTa( $a, $pq)				/*	to assign (1) value with no overflow risk				*/		\
case 0x0:	/* 1		*/ 	*( (ui08*) ( $pq	) )= $a;										break;	\
case 0x1:	/* 2		*/ 	*( (ui16*) ( $pq	) )= $a;										break;	\
case 0x2:	/* 3		*/ 	*( (ui16*) ( $pq	) )= $a;										\
						*( (ui08*) ( $pq +2	) )= $a>>16;									break;	\
case 0x3:	/* 4		*/ 	*( (ui32*) ( $pq	) )= $a;										break;	\
case 0x4:	/* 5		*/ 	*( (ui32*) ( $pq	) )= $a;										\
						*( (ui08*) ( $pq +4 	) )= $a>>32;									break;	\
case 0x5:	/* 6		*/ 	*( (ui32*) ( $pq	) )= $a;										\
						*( (ui16*) ( $pq +4	) )= $a>>32;									break;	\
case 0x6:	/* 7		*/ 	*( (ui32*) ( $pq	) )= $a;										\
						*( (ui16*) ( $pq +4	) )= $a>>32;									\
						*( (ui08*) ( $pq +6	) )= $a>>48;									break;	\
case 0x7:	/* 8		*/ 	*( (ui64*) ( $pq	) )= $a;										break;


#define qCASTa1( $a, $pq)				/*	to assign (1) value with an overflow risk of 1 byte		*/		\
case 0x0:	/* 1		*/ 	*( (ui08*) ( $pq	) )= $a;										break;	\
case 0x1:	/* 2		*/ 	*( (ui16*) ( $pq	) )= $a;										break;	\
case 0x2:	/* 3		*/ 	*( (ui32*) ( $pq	) )= $a;										break;	\
case 0x3:	/* 4		*/ 	*( (ui32*) ( $pq	) )= $a;										break;	\
case 0x4:	/* 5		*/ 	*( (ui32*) ( $pq	) )= $a;										\
						*( (ui08*) ( $pq +4	) )= $a>>32;									break;	\
case 0x5:	/* 6		*/ 	*( (ui32*) ( $pq	) )= $a;										\
						*( (ui16*) ( $pq +4	) )= $a>>32;									break;	\
default:		/* 7		*/	\
			/* 8		*/ 	*( (ui64*) ( $pq	) )= $a;										break;


#define qCASTa2( $a, $pq)				/*	to assign (1) value with an overflow risk of 2 bytes	*/		\
case 0x0:	/* 1+2	*/ 	*( (ui08*) ( $pq	) )= $a;										break;	\
case 0x1:	/* 2+2	*/ 	*( (ui16*) ( $pq	) )= $a;										break;	\
case 0x2:	/* 3+2	*/ 	*( (ui32*) ( $pq	) )= $a;										break;	\
case 0x3:	/* 4+2	*/ 	*( (ui32*) ( $pq	) )= $a;										break;	\
case 0x4:	/* 5+2	*/ 	*( (ui32*) ( $pq	) )= $a;												\
						*( (ui08*) ( $pq +4	) )= $a>>32;									break;	\
default:		/* 6+2	*/	\
			/* 7+2	*/	\
			/* 8+2	*/	*( (ui64*) ( $pq	) )= $a;										break;


#define qCASTa3( $a, $pq)				/*	to assign (1) value with an overflow risk of 3 bytes	*/		\
case 0x0:	/* 1+n	*/ 	*( (ui08*) ( $pq	) )= $a;										break;	\
case 0x1:	/* 2+n	*/ 	*( (ui16*) ( $pq	) )= $a;										break;	\
case 0x2:	/* 3+n	*/ 	*( (ui32*) ( $pq	) )= $a;										break;	\
case 0x3:	/* 4+n	*/ 	*( (ui32*) ( $pq	) )= $a;										break;	\
default:		/* 5+n,	*/	\
			/* 6+n	*/	\
			/* 7+n	*/	\
			/* 8+n	*/ 	*( (ui64*) ( $pq	) )= $a;										break;


#define qCASTab( $b, $a, $pq )			/*	to assign (2) values with no overflow risk			*/		\
case 0x00:	/* 1x1	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +1 ) )= $b;      		break;	\
case 0x01:	/* 2x1	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +2 ) )= $b;      		break;	\
case 0x02:	/* 3x1	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +3 ) )= $b;      		break;	\
case 0x03:	/* 4x1	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +4 ) )= $b;      		break;	\
case 0x04:	/* 5x1	*/ 	*( (ui32*) ( $pq	) )= $a;      		\
						*( (ui08*) ( $pq +4 	) )= $a>>32;		*( (ui08*) ( $pq +5 ) )= $b;      		break;	\
case 0x05:	/* 6x1	*/ 	*( (ui32*) ( $pq	) )= $a;      		\
						*( (ui16*) ( $pq +4	) )= $a>>32;		*( (ui08*) ( $pq +6 ) )= $b;      		break;	\
case 0x06:	/* 7x1	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +7 ) )= $b;      		break;	\
case 0x07:	/* 8x1	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +8 ) )= $b;      		break;	\
case 0x08:	/* 1x2	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +1 ) )= $b;      		break;	\
case 0x09:	/* 2x2	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +2 ) )= $b;      		break;	\
case 0x0A:	/* 3x2	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +3 ) )= $b;      		break;	\
case 0x0B:	/* 4x2	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +4 ) )= $b;      		break;	\
case 0x0C:	/* 5x2	*/ 	*( (ui32*) ( $pq	) )= $a;      		\
						*( (ui08*) ( $pq +4	) )= $a>>32;		*( (ui16*) ( $pq +5 ) )= $b;      		break;	\
case 0x0D:	/* 6x2	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +6 ) )= $b;      		break;	\
case 0x0E:	/* 7x2	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +7 ) )= $b;      		break;	\
case 0x0F:	/* 8x2	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +8 ) )= $b;      		break;	\
case 0x10:	/* 1x3	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +1 ) )= $b;      		\
														*( (ui08*) ( $pq +3 ) )= $b>>16;	break;	\
case 0x11:	/* 2x3	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +2 ) )= $b;      		\
														*( (ui08*) ( $pq +4 ) )= $b>>16;	break;	\
case 0x12:	/* 3x3	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +3 ) )= $b;      		\
														*( (ui08*) ( $pq +5 ) )= $b>>16;	break;	\
case 0x13:	/* 4x3	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +4 ) )= $b;      		\
														*( (ui08*) ( $pq +6 ) )= $b>>16;	break;	\
case 0x14:	/* 5x3	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +5 ) )= $b;      		\
														*( (ui08*) ( $pq +7 ) )= $b>>16;	break;	\
case 0x15:	/* 6x3	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +6 ) )= $b;      		\
														*( (ui08*) ( $pq +8 ) )= $b>>16;	break;	\
case 0x16:	/* 7x3	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +7 ) )= $b;      		\
														*( (ui08*) ( $pq +9 ) )= $b>>16;	break;	\
case 0x17:	/* 8x3	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +8 ) )= $b;      		\
														*( (ui08*) ( $pq +10) )= $b>>16;	break;	\
case 0x18:	/* 1x4	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +1 ) )= $b;      		break;	\
case 0x19:	/* 2x4	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +2 ) )= $b;      		break;	\
case 0x1A:	/* 3x4	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +3 ) )= $b;      		break;	\
case 0x1B:	/* 4x4	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +4 ) )= $b;      		break;	\
case 0x1C:	/* 5x4	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +5 ) )= $b;      		break;	\
case 0x1D:	/* 6x4	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +6 ) )= $b;      		break;	\
case 0x1E:	/* 7x4	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +7 ) )= $b;      		break;	\
case 0x1F:	/* 8x4	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +8 ) )= $b;      		break;	\
case 0x20:	/* 1x5	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +1 ) )= $b;      		\
														*( (ui08*) ( $pq +5 ) )= $b>>32;	break;	\
case 0x21:	/* 2x5	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +2 ) )= $b;      		\
														*( (ui08*) ( $pq +6 ) )= $b>>32;	break;	\
case 0x22:	/* 3x5	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +3 ) )= $b;      		\
														*( (ui08*) ( $pq +7 ) )= $b>>32;	break;	\
case 0x23:	/* 4x5	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +4 ) )= $b;      		\
														*( (ui08*) ( $pq +8 ) )= $b>>32;	break;	\
case 0x24:	/* 5x5	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +5 ) )= $b;      		\
														*( (ui08*) ( $pq +9 ) )= $b>>32;	break;	\
case 0x25:	/* 6x5	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +6 ) )= $b;      		\
														*( (ui08*) ( $pq +10) )= $b>>32;	break;	\
case 0x26:	/* 7x5	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +7 ) )= $b;      		\
														*( (ui08*) ( $pq +11) )= $b>>32;	break;	\
case 0x27:	/* 8x5	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +8 ) )= $b;      		\
														*( (ui08*) ( $pq +12) )= $b>>32;	break;	\
case 0x28:	/* 1x6	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +1 ) )= $b;      		\
														*( (ui16*) ( $pq +5 ) )= $b>>32;	break;	\
case 0x29:	/* 2x6	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +2 ) )= $b;      		\
														*( (ui16*) ( $pq +6 ) )= $b>>32;	break;	\
case 0x2A:	/* 3x6	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +3 ) )= $b;      		\
														*( (ui16*) ( $pq +7 ) )= $b>>32;	break;	\
case 0x2B:	/* 4x6	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +4 ) )= $b;      		\
														*( (ui16*) ( $pq +8 ) )= $b>>32;	break;	\
case 0x2C:	/* 5x6	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +5 ) )= $b;      		\
														*( (ui16*) ( $pq +9 ) )= $b>>32;	break;	\
case 0x2D:	/* 6x6	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +6 ) )= $b;      		\
														*( (ui16*) ( $pq +10) )= $b>>32;	break;	\
case 0x2E:	/* 7x6	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +7 ) )= $b;      		\
														*( (ui16*) ( $pq +11) )= $b>>32;	break;	\
case 0x2F:	/* 8x6	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +8 ) )= $b;      		\
														*( (ui16*) ( $pq +12) )= $b>>32;	break;	\
case 0x30:	/* 1x7	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +1 ) )= $b;      		\
														*( (ui16*) ( $pq +5 ) )= $b>>32;	\
														*( (ui08*) ( $pq +7 ) )= $b>>48;	break;	\
case 0x31:	/* 2x7	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +2 ) )= $b;      		\
														*( (ui16*) ( $pq +6 ) )= $b>>32;	\
														*( (ui08*) ( $pq +8 ) )= $b>>48;	break;	\
case 0x32:	/* 3x7	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +3 ) )= $b;      		\
														*( (ui16*) ( $pq +7 ) )= $b>>32;	\
														*( (ui08*) ( $pq +9 ) )= $b>>48;	break;	\
case 0x33:	/* 4x7	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +4 ) )= $b;      		\
														*( (ui16*) ( $pq +8 ) )= $b>>32;	\
														*( (ui08*) ( $pq +10) )= $b>>48;	break;	\
case 0x34:	/* 5x7	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +5 ) )= $b;      		\
														*( (ui16*) ( $pq +9 ) )= $b>>32;	\
														*( (ui08*) ( $pq +11) )= $b>>48;	break;	\
case 0x35:	/* 6x7	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +6 ) )= $b;      		\
														*( (ui16*) ( $pq +10) )= $b>>32;	\
														*( (ui08*) ( $pq +12) )= $b>>48;	break;	\
case 0x36:	/* 7x7	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +7 ) )= $b;      		\
														*( (ui16*) ( $pq +11) )= $b>>32;	\
														*( (ui08*) ( $pq +13) )= $b>>48;	break;	\
case 0x37:	/* 8x7	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +8 ) )= $b;      		\
														*( (ui16*) ( $pq +12) )= $b>>32;	\
														*( (ui08*) ( $pq +14) )= $b>>48;	break;	\
case 0x38:	/* 1x8	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +1 ) )= $b;      		break;	\
case 0x39:	/* 2x8	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +2 ) )= $b;      		break;	\
case 0x3A:	/* 3x8	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +3 ) )= $b;      		break;	\
case 0x3B:	/* 4x8	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +4 ) )= $b;      		break;	\
case 0x3C:	/* 5x8	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +5 ) )= $b;      		break;	\
case 0x3D:	/* 6x8	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +6 ) )= $b;      		break;	\
case 0x3E:	/* 7x8	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +7 ) )= $b;      		break;	\
case 0x3F:	/* 8x8	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +8 ) )= $b;      		break;


#define qCASTab1( $b, $a, $pq )			/*	to assign (2) values with an overflow risk of 1 byte	*/		\
case 0x00:	/* 1x1	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +1 ) )= $b;      		break;	\
case 0x01:	/* 2x1	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +2 ) )= $b;      		break;	\
case 0x02:	/* 3x1	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +3 ) )= $b;      		break;	\
case 0x03:	/* 4x1	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +4 ) )= $b;      		break;	\
case 0x04:	/* 5x1	*/ 	*( (ui32*) ( $pq	) )= $a;      		\
						*( (ui08*) ( $pq +4	) )= $a>>32;		*( (ui08*) ( $pq +5 ) )= $b;      		break;	\
case 0x05:	/* 6x1	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +6 ) )= $b;      		break;	\
case 0x06:	/* 7x1	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +7 ) )= $b;      		break;	\
case 0x07:	/* 8x1	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +8 ) )= $b;      		break;	\
case 0x08:	/* 1x2	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +1 ) )= $b;      		break;	\
case 0x09:	/* 2x2	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +2 ) )= $b;      		break;	\
case 0x0A:	/* 3x2	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +3 ) )= $b;      		break;	\
case 0x0B:	/* 4x2	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +4 ) )= $b;      		break;	\
case 0x0C:	/* 5x2	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +5 ) )= $b;      		break;	\
case 0x0D:	/* 6x2	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +6 ) )= $b;      		break;	\
case 0x0E:	/* 7x2	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +7 ) )= $b;      		break;	\
case 0x0F:	/* 8x2	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +8 ) )= $b;      		break;	\
case 0x10:	/* 1x3	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +1 ) )= $b;      		break;	\
case 0x11:	/* 2x3	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +2 ) )= $b;      		break;	\
case 0x12:	/* 3x3	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +3 ) )= $b;      		break;	\
case 0x13:	/* 4x3	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +4 ) )= $b;      		break;	\
case 0x14:	/* 5x3	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +5 ) )= $b;      		break;	\
case 0x15:	/* 6x3	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +6 ) )= $b;      		break;	\
case 0x16:	/* 7x3	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +7 ) )= $b;      		break;	\
case 0x17:	/* 8x3	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +8 ) )= $b;      		break;	\
case 0x18:	/* 1x4	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +1 ) )= $b;      		break;	\
case 0x19:	/* 2x4	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +2 ) )= $b;      		break;	\
case 0x1A:	/* 3x4	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +3 ) )= $b;      		break;	\
case 0x1B:	/* 4x4	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +4 ) )= $b;      		break;	\
case 0x1C:	/* 5x4	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +5 ) )= $b;      		break;	\
case 0x1D:	/* 6x4	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +6 ) )= $b;      		break;	\
case 0x1E:	/* 7x4	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +7 ) )= $b;      		break;	\
case 0x1F:	/* 8x4	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +8 ) )= $b;      		break;	\
case 0x20:	/* 1x5	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +1 ) )= $b;      		\
														*( (ui08*) ( $pq +5 ) )= $b>>32;	break;	\
case 0x21:	/* 2x5	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +2 ) )= $b;      		\
														*( (ui08*) ( $pq +6 ) )= $b>>32;	break;	\
case 0x22:	/* 3x5	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +3 ) )= $b;      		\
														*( (ui08*) ( $pq +7 ) )= $b>>32;	break;	\
case 0x23:	/* 4x5	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +4 ) )= $b;      		\
														*( (ui08*) ( $pq +8 ) )= $b>>32;	break;	\
case 0x24:	/* 5x5	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +5 ) )= $b;      		\
														*( (ui08*) ( $pq +9 ) )= $b>>32;	break;	\
case 0x25:	/* 6x5	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +6 ) )= $b;      		\
														*( (ui08*) ( $pq +10) )= $b>>32;	break;	\
case 0x26:	/* 7x5	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +7 ) )= $b;      		\
														*( (ui08*) ( $pq +11) )= $b>>32;	break;	\
case 0x27:	/* 8x5	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +8 ) )= $b;      		\
														*( (ui08*) ( $pq +12) )= $b>>32;	break;	\
case 0x28:	/* 1x6	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +1 ) )= $b;      		\
														*( (ui16*) ( $pq +5 ) )= $b>>32;	break;	\
case 0x29:	/* 2x6	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +2 ) )= $b;      		\
														*( (ui16*) ( $pq +6 ) )= $b>>32;	break;	\
case 0x2A:	/* 3x6	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +3 ) )= $b;      		\
														*( (ui16*) ( $pq +7 ) )= $b>>32;	break;	\
case 0x2B:	/* 4x6	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +4 ) )= $b;      		\
														*( (ui16*) ( $pq +8 ) )= $b>>32;	break;	\
case 0x2C:	/* 5x6	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +5 ) )= $b;      		\
														*( (ui16*) ( $pq +9 ) )= $b>>32;	break;	\
case 0x2D:	/* 6x6	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +6 ) )= $b;      		\
														*( (ui16*) ( $pq +10) )= $b>>32;	break;	\
case 0x2E:	/* 7x6	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +7 ) )= $b;      		\
														*( (ui16*) ( $pq +11) )= $b>>32;	break;	\
case 0x2F:	/* 8x6	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +8 ) )= $b;      		\
														*( (ui16*) ( $pq +12) )= $b>>32;	break;	\
case 0x30:	/* 1x7	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +1 ) )= $b;      		break;	\
case 0x31:	/* 2x7	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +2 ) )= $b;      		break;	\
case 0x32:	/* 3x7	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +3 ) )= $b;      		break;	\
case 0x33:	/* 4x7	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +4 ) )= $b;      		break;	\
case 0x34:	/* 5x7	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +5 ) )= $b;      		break;	\
case 0x35:	/* 6x7	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +6 ) )= $b;      		break;	\
case 0x36:	/* 7x7	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +7 ) )= $b;      		break;	\
case 0x37:	/* 8x7	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +8 ) )= $b;      		break;	\
case 0x38:	/* 1x8	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +1 ) )= $b;      		break;	\
case 0x39:	/* 2x8	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +2 ) )= $b;      		break;	\
case 0x3A:	/* 3x8	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +3 ) )= $b;      		break;	\
case 0x3B:	/* 4x8	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +4 ) )= $b;      		break;	\
case 0x3C:	/* 5x8	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +5 ) )= $b;      		break;	\
case 0x3D:	/* 6x8	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +6 ) )= $b;      		break;	\
case 0x3E:	/* 7x8	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +7 ) )= $b;      		break;	\
case 0x3F:	/* 8x8	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +8 ) )= $b;      		break;


#define qCASTab2( $b, $a, $pq )			/*	to assign (2) values with an overflow risk of 2 bytes	*/		\
case 0x00:	/* 1x1	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +1 ) )= $b;      		break;	\
case 0x01:	/* 2x1	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +2 ) )= $b;      		break;	\
case 0x02:	/* 3x1	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +3 ) )= $b;      		break;	\
case 0x03:	/* 4x1	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +4 ) )= $b;      		break;	\
case 0x04:	/* 5x1	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +5 ) )= $b;      		break;	\
case 0x05:	/* 6x1	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +6 ) )= $b;      		break;	\
case 0x06:	/* 7x1	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +7 ) )= $b;      		break;	\
case 0x07:	/* 8x1	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +8 ) )= $b;      		break;	\
case 0x08:	/* 1x2	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +1 ) )= $b;      		break;	\
case 0x09:	/* 2x2	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +2 ) )= $b;      		break;	\
case 0x0A:	/* 3x2	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +3 ) )= $b;      		break;	\
case 0x0B:	/* 4x2	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +4 ) )= $b;      		break;	\
case 0x0C:	/* 5x2	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +5 ) )= $b;      		break;	\
case 0x0D:	/* 6x2	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +6 ) )= $b;      		break;	\
case 0x0E:	/* 7x2	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +7 ) )= $b;      		break;	\
case 0x0F:	/* 8x2	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +8 ) )= $b;      		break;	\
case 0x10:	/* 1x3	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +1 ) )= $b;      		break;	\
case 0x11:	/* 2x3	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +2 ) )= $b;      		break;	\
case 0x12:	/* 3x3	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +3 ) )= $b;      		break;	\
case 0x13:	/* 4x3	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +4 ) )= $b;      		break;	\
case 0x14:	/* 5x3	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +5 ) )= $b;      		break;	\
case 0x15:	/* 6x3	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +6 ) )= $b;      		break;	\
case 0x16:	/* 7x3	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +7 ) )= $b;      		break;	\
case 0x17:	/* 8x3	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +8 ) )= $b;      		break;	\
case 0x18:	/* 1x4	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +1 ) )= $b;      		break;	\
case 0x19:	/* 2x4	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +2 ) )= $b;      		break;	\
case 0x1A:	/* 3x4	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +3 ) )= $b;      		break;	\
case 0x1B:	/* 4x4	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +4 ) )= $b;      		break;	\
case 0x1C:	/* 5x4	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +5 ) )= $b;      		break;	\
case 0x1D:	/* 6x4	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +6 ) )= $b;      		break;	\
case 0x1E:	/* 7x4	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +7 ) )= $b;      		break;	\
case 0x1F:	/* 8x4	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +8 ) )= $b;      		break;	\
case 0x20:	/* 1x5	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +1 ) )= $b;      		\
														*( (ui08*) ( $pq +5 ) )= $b>>32;	break;	\
case 0x21:	/* 2x5	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +2 ) )= $b;      		\
														*( (ui08*) ( $pq +6 ) )= $b>>32;	break;	\
case 0x22:	/* 3x5	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +3 ) )= $b;      		\
														*( (ui08*) ( $pq +7 ) )= $b>>32;	break;	\
case 0x23:	/* 4x5	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +4 ) )= $b;      		\
														*( (ui08*) ( $pq +8 ) )= $b>>32;	break;	\
case 0x24:	/* 5x5	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +5 ) )= $b;      		\
														*( (ui08*) ( $pq +9 ) )= $b>>32;	break;	\
case 0x25:	/* 6x5	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +6 ) )= $b;      		\
														*( (ui08*) ( $pq +10) )= $b>>32;	break;	\
case 0x26:	/* 7x5	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +7 ) )= $b;      		\
														*( (ui08*) ( $pq +11) )= $b>>32;	break;	\
case 0x27:	/* 8x5	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +8 ) )= $b;      		\
														*( (ui08*) ( $pq +12) )= $b>>32;	break;	\
case 0x28:	/* 1x6	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +1 ) )= $b;      		break;	\
case 0x29:	/* 2x6	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +2 ) )= $b;      		break;	\
case 0x2A:	/* 3x6	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +3 ) )= $b;      		break;	\
case 0x2B:	/* 4x6	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +4 ) )= $b;      		break;	\
case 0x2C:	/* 5x6	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +5 ) )= $b;      		break;	\
case 0x2D:	/* 6x6	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +6 ) )= $b;      		break;	\
case 0x2E:	/* 7x6	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +7 ) )= $b;      		break;	\
case 0x2F:	/* 8x6	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +8 ) )= $b;      		break;	\
case 0x30:	/* 1x7	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +1 ) )= $b;      		break;	\
case 0x31:	/* 2x7	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +2 ) )= $b;      		break;	\
case 0x32:	/* 3x7	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +3 ) )= $b;      		break;	\
case 0x33:	/* 4x7	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +4 ) )= $b;      		break;	\
case 0x34:	/* 5x7	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +5 ) )= $b;      		break;	\
case 0x35:	/* 6x7	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +6 ) )= $b;      		break;	\
case 0x36:	/* 7x7	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +7 ) )= $b;      		break;	\
case 0x37:	/* 8x7	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +8 ) )= $b;      		break;	\
case 0x38:	/* 1x8	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +1 ) )= $b;      		break;	\
case 0x39:	/* 2x8	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +2 ) )= $b;      		break;	\
case 0x3A:	/* 3x8	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +3 ) )= $b;      		break;	\
case 0x3B:	/* 4x8	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +4 ) )= $b;      		break;	\
case 0x3C:	/* 5x8	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +5 ) )= $b;      		break;	\
case 0x3D:	/* 6x8	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +6 ) )= $b;      		break;	\
case 0x3E:	/* 7x8	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +7 ) )= $b;      		break;	\
case 0x3F:	/* 8x8	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +8 ) )= $b;      		break;


#define qCASTab3( $b, $a, $pq )			/*	to assign (2) values with an overflow risk of 3 bytes	*/		\
case 0x00:	/* 1x1	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +1 ) )= $b;      		break;	\
case 0x01:	/* 2x1	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +2 ) )= $b;      		break;	\
case 0x02:	/* 3x1	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +3 ) )= $b;      		break;	\
case 0x03:	/* 4x1	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +4 ) )= $b;      		break;	\
case 0x04:	/* 5x1	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +5 ) )= $b;      		break;	\
case 0x05:	/* 6x1	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +6 ) )= $b;      		break;	\
case 0x06:	/* 7x1	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +7 ) )= $b;      		break;	\
case 0x07:	/* 8x1	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui08*) ( $pq +8 ) )= $b;      		break;	\
case 0x08:	/* 1x2	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +1 ) )= $b;      		break;	\
case 0x09:	/* 2x2	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +2 ) )= $b;      		break;	\
case 0x0A:	/* 3x2	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +3 ) )= $b;      		break;	\
case 0x0B:	/* 4x2	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +4 ) )= $b;      		break;	\
case 0x0C:	/* 5x2	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +5 ) )= $b;      		break;	\
case 0x0D:	/* 6x2	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +6 ) )= $b;      		break;	\
case 0x0E:	/* 7x2	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +7 ) )= $b;      		break;	\
case 0x0F:	/* 8x2	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui16*) ( $pq +8 ) )= $b;      		break;	\
case 0x10:	/* 1x3	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +1 ) )= $b;      		break;	\
case 0x11:	/* 2x3	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +2 ) )= $b;      		break;	\
case 0x12:	/* 3x3	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +3 ) )= $b;      		break;	\
case 0x13:	/* 4x3	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +4 ) )= $b;      		break;	\
case 0x14:	/* 5x3	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +5 ) )= $b;      		break;	\
case 0x15:	/* 6x3	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +6 ) )= $b;      		break;	\
case 0x16:	/* 7x3	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +7 ) )= $b;      		break;	\
case 0x17:	/* 8x3	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +8 ) )= $b;      		break;	\
case 0x18:	/* 1x4	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +1 ) )= $b;      		break;	\
case 0x19:	/* 2x4	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +2 ) )= $b;      		break;	\
case 0x1A:	/* 3x4	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +3 ) )= $b;      		break;	\
case 0x1B:	/* 4x4	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +4 ) )= $b;      		break;	\
case 0x1C:	/* 5x4	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +5 ) )= $b;      		break;	\
case 0x1D:	/* 6x4	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +6 ) )= $b;      		break;	\
case 0x1E:	/* 7x4	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +7 ) )= $b;      		break;	\
case 0x1F:	/* 8x4	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui32*) ( $pq +8 ) )= $b;      		break;	\
case 0x20:	/* 1x5	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +1 ) )= $b;      		break;	\
case 0x21:	/* 2x5	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +2 ) )= $b;      		break;	\
case 0x22:	/* 3x5	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +3 ) )= $b;      		break;	\
case 0x23:	/* 4x5	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +4 ) )= $b;      		break;	\
case 0x24:	/* 5x5	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +5 ) )= $b;      		break;	\
case 0x25:	/* 6x5	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +6 ) )= $b;      		break;	\
case 0x26:	/* 7x5	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +7 ) )= $b;      		break;	\
case 0x27:	/* 8x5	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +8 ) )= $b;      		break;	\
case 0x28:	/* 1x6	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +1 ) )= $b;      		break;	\
case 0x29:	/* 2x6	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +2 ) )= $b;      		break;	\
case 0x2A:	/* 3x6	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +3 ) )= $b;      		break;	\
case 0x2B:	/* 4x6	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +4 ) )= $b;      		break;	\
case 0x2C:	/* 5x6	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +5 ) )= $b;      		break;	\
case 0x2D:	/* 6x6	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +6 ) )= $b;      		break;	\
case 0x2E:	/* 7x6	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +7 ) )= $b;      		break;	\
case 0x2F:	/* 8x6	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +8 ) )= $b;      		break;	\
case 0x30:	/* 1x7	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +1 ) )= $b;      		break;	\
case 0x31:	/* 2x7	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +2 ) )= $b;      		break;	\
case 0x32:	/* 3x7	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +3 ) )= $b;      		break;	\
case 0x33:	/* 4x7	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +4 ) )= $b;      		break;	\
case 0x34:	/* 5x7	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +5 ) )= $b;      		break;	\
case 0x35:	/* 6x7	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +6 ) )= $b;      		break;	\
case 0x36:	/* 7x7	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +7 ) )= $b;      		break;	\
case 0x37:	/* 8x7	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +8 ) )= $b;      		break;	\
case 0x38:	/* 1x8	*/ 	*( (ui08*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +1 ) )= $b;      		break;	\
case 0x39:	/* 2x8	*/ 	*( (ui16*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +2 ) )= $b;      		break;	\
case 0x3A:	/* 3x8	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +3 ) )= $b;      		break;	\
case 0x3B:	/* 4x8	*/ 	*( (ui32*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +4 ) )= $b;      		break;	\
case 0x3C:	/* 5x8	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +5 ) )= $b;      		break;	\
case 0x3D:	/* 6x8	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +6 ) )= $b;      		break;	\
case 0x3E:	/* 7x8	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +7 ) )= $b;      		break;	\
case 0x3F:	/* 8x8	*/ 	*( (ui64*) ( $pq	) )= $a;      		*( (ui64*) ( $pq +8 ) )= $b;      		break;

#define CASTq2i(	 	$I, $p, $q )		switch( $q){	case 0:	break;	\
												case 1:	$I=	 				*( (ui08* )	$p 		);			break;	\
												case 2:	$I=	  				*( (ui16* )	$p	 	);			break; 	\
												case 3:	$I=	 				*( (ui32* ) (	$p -1	) ) >>8;		break;	\
												case 4:	$I=	 				*( (ui32* )	$p		);			break;	\
												case 5:	$I=	 				*( (ui64* ) ( 	$p -3	) ) >>24;		break;	\
												case 6:	$I=	 				*( (ui64* ) (	$p -2	) ) >>16;		break;	\
												case 7:	$I=	  				*( (ui64* ) (	$p -1	) ) >>8;		break;	\
												case 8:	$I=	 				*( (ui64* ) 	$p		);			break;	}
#define CASTq2i_plus1inc( $I, $p, $q )		switch( $q){	case 0:	break;	\
												case 1:	$I+=	 	1+			*( (ui08* )	$p 		);			break;	\
												case 2:	$I+=	  	1+			*( (ui16* )	$p	 	);			break; 	\
												case 3:	$I+=	 	1+			*( (ui32* ) (	$p -1	) ) >>8;		break;	\
												case 4:	$I+=	 	1+			*( (ui32* )	$p		);			break;	\
												case 5:	$I+=	 	1+			*( (ui64* ) ( 	$p -3	) ) >>24;		break;	\
												case 6:	$I+=	 	1+			*( (ui64* ) (	$p -2	) ) >>16;		break;	\
												case 7:	$I+=	  	1+			*( (ui64* ) (	$p -1	) ) >>8;		break;	\
												case 8:	$I+=	 	1+			*( (ui64* ) 	$p		);			break;	}
#define CASTq2i_less1(	$I, $p, $q )		switch( $q){	case 0:	break;	\
												case 1:	$I=	 				*( (ui08* )	$p 		)		-1;	break;	\
												case 2:	$I=	  				*( (ui16* )	$p	 	)		-1;	break; 	\
												case 3:	$I=	 			(	*( (ui32* ) (	$p -1	) ) >>8	)-1;	break;	\
												case 4:	$I=	 				*( (ui32* )	$p		)		-1;	break;	\
												case 5:	$I=	 			(	*( (ui64* ) ( 	$p -3	) ) >>24	)-1;	break;	\
												case 6:	$I=	 			(	*( (ui64* ) (	$p -2	) ) >>16	)-1;	break;	\
												case 7:	$I=	  			(	*( (ui64* ) (	$p -1	) ) >>8	)-1;	break;	\
												case 8:	$I=	 				*( (ui64* ) 	$p		)		-1;	break;	}
#define CASTq2i_plus1(	$I, $p, $q )		switch( $q){	case 0:	break;	\
												case 1:	$I=	 	1+			*( (ui08* )	$p 		)		;	break;	\
												case 2:	$I=	  	1+			*( (ui16* )	$p	 	)		;	break; 	\
												case 3:	$I=	 	1+		(	*( (ui32* ) (	$p -1	) ) >>8	);	break;	\
												case 4:	$I=	 	1+			*( (ui32* )	$p		)		;	break;	\
												case 5:	$I=	 	1+		(	*( (ui64* ) ( 	$p -3	) ) >>24	);	break;	\
												case 6:	$I=	 	1+		(	*( (ui64* ) (	$p -2	) ) >>16	);	break;	\
												case 7:	$I=	  	1+		(	*( (ui64* ) (	$p -1	) ) >>8	);	break;	\
												case 8:	$I=	 	1+			*( (ui64* ) 	$p		)		;	break;	}
#define rCASTq2i(		$I, $p, $q )		switch( $q){	case 0:	break;	\
												case 1:	$I=	 				*( (ui08* ) (	$p -1	) );			break;	\
												case 2:	$I=	  				*( (ui16* ) (	$p -2 	) );			break; 	\
												case 3:	$I=	 				*( (ui32* ) (	$p -4	) ) >>8;		break;	\
												case 4:	$I=	 				*( (ui32* ) (	$p -4	) );			break;	\
												case 5:	$I=	 				*( (ui64* ) ( 	$p -8	) ) >>24;		break;	\
												case 6:	$I=	 				*( (ui64* ) (	$p -8	) ) >>16;		break;	\
												case 7:	$I=	  				*( (ui64* ) (	$p -8	) ) >>8;		break;	\
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
