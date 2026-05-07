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
#include "out.h"
#define __ToTEXT_ROW_ALLOC	224

void _toText(){
	av_push(		avOut,	newSVpvn(	"\n\n", 2 ) );
	STRLEN		pvS, CS, nCS, lenRowID, metaLen, EOLLen;
	char			ptrOddRow[__ToTEXT_ROW_ALLOC ],
				ptrEvnRow[__ToTEXT_ROW_ALLOC ],
				oCell,
				fsBlankRow[	32 ],
				fsHeadID[	16 ],
				fsLineID[  	16 ],
				fsOdd_L0[	32 ],
				fsOdd_L1[	32 ],
				fsOdd_LX[	32 ],
				fsEvn_LX[	32 ],
				fsMeta[		32 ],
			*	pq,
			*	po,
			*	pe;
	long long int	x,		  iC,	zC = AvFILLp(		avICE ),	nC =zC +1;
	SV		**	pSv0 =			AvARRAY(	avICE ),
			*	sviC=*( pSv0	+zC );

	ui08		*	cube,	pos,
				edge, wipe, r0,	r1,	vecS, cellS, rowLen, oddLineLen, evnLineLen, avSize, avSizeDigs,
				Kc, Qc, ic=0, zc;
	ui64			Ac, Bc, Xc, Ec,	EC,		EzC;
	long double	log;
				log = log10l( (long double)	nC );
	nCS	= ceil(	log );

	//find the decimal-represented string length of (what should be) the largest number in the whole structure: epsilon of [iCZ]
	if(		NULL==	sviC
	||		!SvOK(	sviC )
	||		SvTYPE(	sviC )!=3 )				{	EzC=0; vecS=12; cellS=14;	avSize=0;
	}else{	cube = SvPVbyte( sviC, CS);
		if(	cube==NULL )						{	EzC=0; vecS=12; cellS=14;	avSize=0;
		}else								{	EzC=*( (ui64*) cube +1 );	avSize=CS;
						log = log10l( (long double)	EzC );	/* "Epsilon" of cube zC (minus one) will be the largest number encoded	*/
			vecS=ceil(	log );	cellS =vecS +2;
		}	}
	//sum total byte length of all SV* allocations in AV* avICE
	for( iC=zC; iC >=0; --iC ){	sviC = *( pSv0 +iC );
		if( NULL !=	sviC
		&& SvOK(	sviC )
		&& SvTYPE(	sviC )==3
		&& SvPVbyte(	sviC,  CS )!=NULL ) avSize += CS;
		}
					log = log10l( (long double)	avSize );
	avSizeDigs=ceil(	log );

/*	format the format strings to set the cell and line number sizes		if you change these, make sure the row allocations are good */
	sprintf( fsHeadID,		"(%c%dllu)  ",					37, nCS			);	// top-left	cell at col [0-1] 	row [0-1]
	sprintf( fsLineID,		"[%c-%dllu] ",					37, nCS			);	// leftmost	cell at col [0+ic]	row [0+iC*2]

	sprintf( fsMeta,		"[< %c%dllX %c%dllub ]\n", 	37, vecS, 37, avSizeDigs	);

	sprintf( fsOdd_L0,		"%cc%cc%c-%dllX", 	 37,	37,	37, vecS		);	// odd-row	cell format used when either A or B is 0
	sprintf( fsOdd_L1,		"  %c-%dllX", 	 				37, vecS		);	// odd-row	cell format used when B<= 1
	sprintf( fsOdd_LX,		"  %c-%dllX",  					37, vecS		);	// odd-row	cell format used when B >1
	sprintf( fsEvn_LX,		"..%c-%dllX",  					37, vecS		);	/* even-row	cell format used when B >1 (exclusively as the even-row cells are blank unless run length expresses a range		*/

							lenRowID = sprintf( ptrOddRow,	fsHeadID,	nC			);
					rowLen =	lenRowID +( cellS *8 ) +2;// +1;	/*	+1:	the "fsLineID" template used in regular rows is one space longer than the "fsHeadID" template used in the header	*/
			pos =	rowLen &0x07;
	switch(	pos ){	case 0x0:												break;
					case 0x1:	*( (ui08*) (	ptrOddRow		) )=0x5F;
								*( (ui08*) (	ptrEvnRow		) )=0x20;
								*( (ui08*) (	fsBlankRow		) )=0x20;			break;
					case 0x2:	*( (ui16*) (	ptrOddRow		) )=0x5F5F;
								*( (ui16*) (	ptrEvnRow		) )=0x2020;
								*( (ui16*) (	fsBlankRow		) )=0x2020;		break;
					case 0x3:	*( (ui16*) (	ptrOddRow		) )=0x5F5F;
								*( (ui16*) (	ptrEvnRow		) )=0x2020;
								*( (ui16*) (	fsBlankRow		) )=0x2020;
								*( (ui08*) (	ptrOddRow +2 	) )=0x5F;
								*( (ui08*) (	ptrEvnRow +2 	) )=0x20;
								*( (ui08*) (	fsBlankRow +2 	) )=0x20;			break;
					case 0x4:	*( (ui32*) (	ptrOddRow		) )=0x5F5F5F5F;
								*( (ui32*) (	ptrEvnRow		) )=0x20202020;
								*( (ui32*) (	fsBlankRow		) )=0x20202020;	break;
					case 0x5:	*( (ui32*) (	ptrOddRow		) )=0x5F5F5F5F;
								*( (ui32*) (	ptrEvnRow		) )=0x20202020;
								*( (ui32*) (	fsBlankRow		) )=0x20202020;	
								*( (ui08*) (	ptrOddRow +4 	) )=0x5F;
								*( (ui08*) (	ptrEvnRow +4 	) )=0x20;
								*( (ui08*) (	fsBlankRow +4 	) )=0x20;			break;
					case 0x6:	*( (ui32*) (	ptrOddRow		) )=0x5F5F5F5F;
								*( (ui32*) (	ptrEvnRow		) )=0x20202020;
								*( (ui32*) (	fsBlankRow		) )=0x20202020;
								*( (ui16*) (	ptrOddRow +4 	) )=0x5F5F;
								*( (ui16*) (	ptrEvnRow +4 	) )=0x2020;
								*( (ui16*) (	fsBlankRow +4 	) )=0x2020;		break;
					case 0x7:	*( (ui32*) (	ptrOddRow		) )=0x5F5F5F5F;
								*( (ui32*) (	ptrEvnRow		) )=0x20202020;
								*( (ui32*) (	fsBlankRow		) )=0x20202020;
								*( (ui16*) (	ptrOddRow +4 	) )=0x5F5F;
								*( (ui16*) (	ptrEvnRow +4 	) )=0x2020;
								*( (ui16*) (	fsBlankRow +4 	) )=0x2020;		
								*( (ui08*) (	ptrOddRow +6 	) )=0x5F;
								*( (ui08*) (	ptrEvnRow +6 	) )=0x20;
								*( (ui08*) (	fsBlankRow +6 	) )=0x20;			break;
						}
	for( ; pos< rowLen;	pos +=8 )	{	*( (ui64*)(	ptrOddRow +pos	) )=0x5F5F5F5F5F5F5F5F;
								*( (ui64*)(	ptrEvnRow +pos	) )=0x2020202020202020;
								*( (ui64*)(	fsBlankRow +pos	) )=0x2020202020202020;
								}			fsBlankRow[ cellS ] =0;

	for( pos= lenRowID;	ic< 8; ++ic )	{	ptrOddRow[ pos+1	] = 35;
										ptrOddRow[ pos+2	] = 48 +ic;	pos += cellS;
									}

	metaLen	= sprintf( ptrOddRow	+rowLen,	fsMeta, EzC, avSize );	oddLineLen	=rowLen +metaLen;	ptrOddRow[oddLineLen]=0;
	EOLLen	= sprintf( ptrEvnRow	+rowLen, "  \n\n" );				evnLineLen	=rowLen +EOLLen;		ptrEvnRow[evnLineLen]=0;
	

	if(	oddLineLen >__ToTEXT_ROW_ALLOC ){	printf("\n!	_toText(): row length allocation is too low!  Increase at least to %d bytes!\n\n", rowLen +metaLen );
											return;	}

	av_push( avOut, newSVpvn( ptrOddRow, oddLineLen ) );

	Ec=0;
	for( iC=0; iC <= zC;  ++iC){
		sviC = *( pSv0 +iC );		if(NULL	==	sviC		){ pvS =sprintf( aString, "\r[%llu]: NULL\n",				iC); av_push( avOut, newSVpvn( aString, pvS ) );	continue;	}
								if( !SvOK( sviC )		){ pvS =sprintf( aString, "\r[%llu]: ! SvOK\n",				iC); av_push( avOut, newSVpvn( aString, pvS ) );	continue;	}
								if( !SvPOK( sviC )		){ pvS =sprintf( aString, "\r[%llu]: ! SvPOK\n",			iC); av_push( avOut, newSVpvn( aString, pvS ) );	continue;	}
								if( SvTYPE( sviC )!=3	){ pvS =sprintf( aString, "\r[%llu]: SVTYPE != SVt_RV\n",	iC); av_push( avOut, newSVpvn( aString, pvS ) );	continue;	}
		cube=SvPVbyte( sviC,  CS );	if( cube==NULL		){ pvS =sprintf( aString, "\r[%llu]: SvPVbyte(...)==NULL\n",	iC); av_push( avOut, newSVpvn( aString, pvS ) );	continue;	}
		pq	= cube +16;
		zc= zcOf( *( (ui64*) cube ) );
		
		sprintf( ptrOddRow,		fsLineID,	iC	);

		po = ptrOddRow	+lenRowID;
		pe = ptrEvnRow	+lenRowID;


		for( ic=0; ic <=zc;  ++ic ){				_deICE( cube, CS, cube[ ic ], pq, Qc, Ac, Bc);	Ec =( Xc= Ac +Ec ) +Bc;
			if(				Bc<2	){
				if(	Ac==0||	Bc==0	)	sprintf( po, fsOdd_L0, Ac? 95: 33, Bc? 95: 33, Xc	);
				else						sprintf( po, fsOdd_L1, Xc	);	sprintf( pe, fsBlankRow		);
			}else{
				if(	Ac==0 )				sprintf( po, fsOdd_L0, Ac? 95: 33, Bc? 95: 33, Xc	);
				else						sprintf( po, fsOdd_LX, Xc	);	sprintf( pe, fsEvn_LX,	Ec-1	); 
				}
			po +=cellS;
			pe +=cellS;
			}
		while( ic++< 8 ){	sprintf( po, fsBlankRow );		sprintf( pe, fsBlankRow );
			po +=cellS;
			pe +=cellS;
			}
		sprintf( ptrOddRow +rowLen,	fsMeta,		*( (ui64*) cube +1 ), CS	);

		Ec =*( (ui64*) cube+1);

		av_push(		avOut,	newSVpvn(	ptrOddRow,	oddLineLen	) );
		av_push(		avOut,	newSVpvn(	ptrEvnRow,	evnLineLen	) );
		}

	av_push(			avOut,	newSVpvn(	"\n\n", 2 ) );
	}
/*
void _toBase96(){

	ui08		*	data,
			*	cube;
	SV		**	pSvC0	= AvARRAY(	avICE	);
	size_t		iC,	zC	= AvFILLp(	avICE	);
	unsigned char	ic,	zc	= zcOf(		*pSvC0	);
	ui64		q=0;
	STRLEN	i0, i1=1;
	for( iC=0;  iC<=zC;  ++iC ) 	q+= SvCUR(		*( pSvC0 +iC ) );	if( q==0 ) return;
	SV		*	svQ = newSVpvz( q );
	ui08		*	pq1 = SvPVbyte_nolen( svQ )+16;
	ui16		c, r, n=0;

	while( zC-- >=0 ){

		cube =	SvPVbyte(	*(	pSvC0 +iC	), i0 );
		while( --i0 >15 ){	c =	cube[ i0		] /96;	data[ i1 ] = n= cube[ i0 ] %96;
					if(	c )	data[ i1+1	] =c;

				pq0 = cube +16;
				
				*pq1 = *( (ui64*
			
/*	01230000

	00004560
	00000007 ..	8A

	00123000
	00000123

	12300000
	00012300
	00000012
	30000000

	ui08		*	cube	= SvPVbyte(	*pSvC0,	CS );
	


	}*/