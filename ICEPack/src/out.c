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
//	#include "SwCASE_IC_HEXL_inc.h"
	#include "SwCASE_IC2XE_R2L_dec.h"
	#include "SwCASE_IC2XE_inc.h"

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
				edge, wipe, r0,	r1,	vecS, cellS, rowLen, oddLineLen, evnLineLen,  avSizeDigs,
				Kc, Qc, ic=0, zc;
	ui64			Ac, Bc, Xc, Ec,	EC,		EzC,									avSize;
	long double	log;
				log = log10l( (long double)	nC );
	nCS	= ceil(	log );

	//find the decimal-represented string length of (what should be) the largest number in the whole structure: epsilon of [iCO]
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
			&& SvPOK(	sviC ) )	avSize += SvCUR( sviC );
			}
					log = log10l( (long double)	avSize );
	avSizeDigs=ceil(	log );

/*	format the format strings to set the cell and line number sizes		if you change these, make sure the row allocations are good */
	sprintf( fsHeadID,		"(%c%dllu)  ",					37, nCS			);	// top-left	cell at col [0-1] 	row [0-1]
	sprintf( fsLineID,		"[%c-%dllu] ",					37, nCS			);	// leftmost	cell at col [0+ic]	row [0+iC*2]

	sprintf( fsMeta,		"[< %c%dllu %c%dllub ]\n", 	37, vecS, 37, avSizeDigs	);

	sprintf( fsOdd_L0,		"%cc%cc%c-%dllu", 	 37,	37,	37, vecS		);	// odd-row	cell format used when either A or B is 0
	sprintf( fsOdd_L1,		"  %c-%dllu", 	 				37, vecS		);	// odd-row	cell format used when B<= 1
	sprintf( fsOdd_LX,		"  %c-%dllu",  					37, vecS		);	// odd-row	cell format used when B >1
	sprintf( fsEvn_LX,		"..%c-%dllu",  					37, vecS		);	/* even-row	cell format used when B >1 (exclusively as the even-row cells are blank unless run length expresses a range		*/

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
		zc= zcOf( cube );
		
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
void _toTextX(){
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
				edge, wipe, r0,	r1,	vecS, cellS, rowLen, oddLineLen, evnLineLen,  avSizeDigs,
				Kc, Qc, ic=0, zc;
	ui64			Ac, Bc, Xc, Ec,	EC,		EzC,									avSize;
	long double	log;
				log = log10l( (long double)	nC );
	nCS	= ceil(	log );

	//find the decimal-represented string length of (what should be) the largest number in the whole structure: epsilon of [zC]
	if(		NULL==	sviC
	||		!SvOK(	sviC )
	||		SvTYPE(	sviC )!=3 )				{	EzC=0; vecS=18; cellS=20;	avSize=0;
	}else{	cube = SvPVbyte( sviC, CS);
		if(	cube==NULL )						{	EzC=0; vecS=18; cellS=20;	avSize=0;
		}else								{	EzC=*( (ui64*) cube +1 );	avSize=CS;
		//				log = log10l( (long double)	EzC );	/* "Epsilon" of cube zC (minus one) will be the largest number encoded	*/
		//	vecS=ceil(	log );				cellS =vecS +2;

			vecS=18-(__builtin_clzll( EzC ) >>2);	cellS =vecS +2;
		}	}
	//sum total byte length of all SV* allocations in AV* avICE
	for( iC=zC; iC >=0; --iC ){	sviC = *( pSv0 +iC );
		if( NULL !=	sviC
		&& SvPOK(	sviC ) )	avSize += SvCUR( sviC );
		}
					log = log10l( (long double)	avSize );
	avSizeDigs=1+ceil(	log );

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
		zc= zcOf( cube );
		
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

unsigned char		**	Mpk,
				**	Mpq;
char				*	Mzc, MZ=-1;

SV* toHex(		SV*	rvICE		){
	AV			*	avICE,
				*	avOut;
	SV			*	rvOut,
				**	pSv0,
				**	pSviC,
				*	SvC;
	unsigned char	WS,	s,
						cell[	8	]={5,5,5,5,5,5,5,5},
				*	pr,	row[  384	], ic;
	ui64			Xc,	Ec;
	long long int	iC,	zC, nC;
	STRLEN			L, CS, rowL;
#ifdef DEBUG
	STRLEN		cS;
#endif
	avOut	= newAV_alloc_x( nC +1 );
	rvOut	= newRV_inc( (SV*) avOut );
	svtype			type= SvTYPE(	rvICE );					if(	type >= svtype_cnt )				{ dBUG_4A( svtype_err,	__FUNCTION__, (ui08) type, __FILE__, __LINE__ );	type=0;	}
															if(	type != SVt_RV || ! SvROK(	rvICE ) )	{ dBUG_2A( usage_err[0], __FUNCTION__, type < svtype_cnt? svtype_names[		type ]: "UNKNOWN"  );			return rvOut;	}
					avICE=(AV*) SvRV(	rvICE );
					type = SvTYPE(	avICE );					if(	type != SVt_PVAV )					{ dBUG_2A( usage_err[0], __FUNCTION__, type < svtype_cnt? svtype_names_ref[ 	type ]: "UNKNOWN" );			return rvOut; 	}
	nC=( zC= AvFILLp(	avICE ) ) +1;								if(	nC==0 )							return rvOut;

	if( MZ< nC ){
		if( MZ==-1 ){	Newx(	Mzc, nC,	char );	Newx(	Mpq, nC, ui08* );	Newx(	Mpk, nC, ui08* );
		}else	{	Renew(	Mzc, nC,	char );	Renew(	Mpq, nC, ui08* );	Renew(	Mpk, nC, ui08* );
				}
		if( Mzc==NULL|| Mpq==NULL||Mpk==NULL)	{ printf( malloc_err, __FUNCTION__, __FILE__, __LINE__ );	return rvOut;	}
		MZ=nC;
		}
	pSv0	= AvARRAY(	avICE );								if( pSv0==NULL)	{ dBUG_4A( cube_err[0], __FUNCTION__,							0, 			__FILE__, __LINE__ );				return rvOut; }
									SvC	=*	pSv0;			if(SvC==NULL)		{ dBUG_4A( cube_err[1], __FUNCTION__,							0, 			__FILE__, __LINE__ );	Mzc[0]=-1;	goto _continue; }
					type = SvTYPE(	SvC );					if(!SvOK( SvC ) )	{ dBUG_6A( cube_err[2], __FUNCTION__, svtype_names_ref[ 	type ],	0, &*SvC,	__FILE__, __LINE__ );	Mzc[0]=-1;	goto _continue; }
															if(!SvPOK( SvC ) )	{ dBUG_6A( cube_err[3], __FUNCTION__, svtype_names_ref[ 	type ],	0, &*SvC,	__FILE__, __LINE__ );	Mzc[0]=-1;	goto _continue; }
	Mpk[	0 ] = SvPVbyte( 			SvC, CS );				if(CS<16 )		{ dBUG_5A( cube_err[4], __FUNCTION__,							0, CS,		__FILE__, __LINE__ );	Mzc[0]=-1;	goto _continue; }
	Mzc[	0 ] = zcOf( Mpk[0] );								if(Mzc[ 0 ]==-1 )	{ dBUG_5A( cube_err[5], __FUNCTION__,							0, CS,		__FILE__, __LINE__ );	}
	Mpq[	0 ] = Mpk[ 0 ]+16;									/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*/	_continue:


	for(	iC=zC;	iC>0;	--iC ){		SvC	=*(	pSv0 +iC );		if(SvC==NULL)		{ dBUG_4A( cube_err[1], __FUNCTION__,							iC,			__FILE__, __LINE__ );	Mzc[iC]=-1;		continue; }
					type = SvTYPE(	SvC );					if(!SvOK( SvC ) )	{ dBUG_6A( cube_err[2], __FUNCTION__, svtype_names_ref[ 	type ],	iC, &*SvC,	__FILE__, __LINE__ );	Mzc[iC]=-1;		continue; }
															if(!SvPOK( SvC ) )	{ dBUG_6A( cube_err[3], __FUNCTION__, svtype_names_ref[ 	type ],	iC, &*SvC,	__FILE__, __LINE__ );	Mzc[iC]=-1;		continue; }
		Mpk[ iC] = SvPVbyte(			SvC, CS );				if(CS<16 )		{ dBUG_5A( cube_err[4], __FUNCTION__,							iC, CS,		__FILE__, __LINE__ );	Mzc[iC]=-1;		continue; }
		Mzc[ iC]= zcOf( Mpk[ iC ] );								if(Mzc[ 0 ]==-1 )	{ dBUG_5A( cube_err[5], __FUNCTION__,							iC, CS,		__FILE__, __LINE__ );	Mzc[iC]=-1;		continue; }
		Mpq[ iC]= Mpk[ iC ]+16;
		}
	Xc=Ec=0;
	for(		ic=0;	ic< 8; ++ic ){
		for(	iC=0;	iC <= zC;	++iC ){	if( ic<= Mzc[ iC ])			{	switch( Mpk[ iC ][ ic ] ){ SwCASE_IC2XE_inc(	Mpq[ iC ], Xc, Ec, Mpq[ iC ] );	}
/*hex*/		s = (Xc+1==Ec)?	20-	(__builtin_clzll( Xc ) >>2)
						:	41-(	(__builtin_clzll( Xc ) >>2)+(__builtin_clzll( Ec-1 ) >>2) );
/*dec*/	//	s = (Xc+1==Ec)?	2 +(char) ceil( log10l( (long double)	Xc	) )
		//					4 +(char) ceil( log10l( (long double)	Xc	) ) +(char) ceil( log10l( (long double)	Ec-1	) );
			if( s >cell[ ic ] )	cell[ ic ] = s;	
		}	}												}

	Xc=Ec=0;
	for(		iC=0;	iC <= zC;  ++iC){		pr = row;
		if(	Mzc[ iC ] ==-1 ){				L=	sprintf(	pr, "# cube #%llu error\n", iC );		av_push( avOut, newSVpvn(  row, L ) );
		}else{
	//		Ec = *( (ui64*) Mpk[ iC ] );
			Mpq[ iC ]	= Mpk[ iC ] +16;	for( ic=0; ic<= Mzc[ iC ]; ++ic )	{	switch( Mpk[ iC ][ ic ] ){ SwCASE_IC2XE_inc(	Mpq[ iC ], Xc, Ec, Mpq[ iC ] );	}

				if(	Xc+1 == Ec )	pr +=(	L=	sprintf(	pr,	"0x%llX,",		Xc		) );
				else				pr +=(	L=	sprintf(	pr,	"0x%llX..0x%llX,",	Xc,	Ec-1	) );

									WS = cell[ ic ] -L;
				WSPACE_UNSAFE(	pr,	WS );
				}
		//	Ec = *( (ui64*) Mpk[ iC ] );
								*pr++ = 10;		
			av_push( avOut, newSVpvn( row, pr-row ) );
		}	}
	return	rvOut;
	}

void _printHex(	AV*	avICE		){
	SV			**	pSv0,
				**	pSviC,
				*	SvC;
	unsigned char	WS,	s,
						cell[	8	]={5,5,5,5,5,5,5,5},
				*	pr,	row[  384	], ic;
	ui64			Xc,	Ec;
	long long int	iC,	zC, nC;
	STRLEN			L, CS, rowL;
#ifdef DEBUG
	STRLEN		cS;
#endif

	svtype		type = SvTYPE(	avICE );						if(	type != SVt_PVAV )					{ printf( usage_err[0], __FUNCTION__, type < svtype_cnt? svtype_names_ref[ 	type ]: "UNKNOWN" );			return; 	}
	nC=( zC= AvFILLp(	avICE ) ) +1;								if(	nC==0 )							return;

	if( MZ==-1 ){	Newx(	Mzc, nC,	char );	Newx(	Mpq, nC, ui08* );	Newx(	Mpk, nC, ui08* );
	}else	{	Renew(	Mzc, nC,	char );	Renew(	Mpq, nC, ui08* );	Renew(	Mpk, nC, ui08* );
			}
	if( Mzc==NULL|| Mpq==NULL||Mpk==NULL)	{ printf( malloc_err, __FUNCTION__, __FILE__, __LINE__ );	return;	}


	pSv0	= AvARRAY(	avICE );								if( pSv0==NULL)	{ dBUG_4A( cube_err[0], __FUNCTION__,							0, 			__FILE__, __LINE__ );				return; }
									SvC	=*	pSv0;			if(SvC==NULL)		{ dBUG_4A( cube_err[1], __FUNCTION__,							0, 			__FILE__, __LINE__ );	Mzc[0]=-1;	goto _continue; }
				type = SvTYPE(		SvC );					if(!SvOK( SvC ) )	{ dBUG_6A( cube_err[2], __FUNCTION__, svtype_names_ref[ 	type ],	0, &*SvC,	__FILE__, __LINE__ );	Mzc[0]=-1;	goto _continue; }
															if(!SvPOK( SvC ) )	{ dBUG_6A( cube_err[3], __FUNCTION__, svtype_names_ref[ 	type ],	0, &*SvC,	__FILE__, __LINE__ );	Mzc[0]=-1;	goto _continue; }
	Mpk[	0 ] = SvPVbyte( 			SvC, CS );				if(CS<16 )		{ dBUG_5A( cube_err[4], __FUNCTION__,							0, CS,		__FILE__, __LINE__ );	Mzc[0]=-1;	goto _continue; }
	Mzc[	0 ] = zcOf( Mpk[0] );								if(Mzc[ 0 ]==-1 )	{ dBUG_5A( cube_err[5], __FUNCTION__,							0, CS,		__FILE__, __LINE__ );	}
	Mpq[	0 ] = Mpk[ 0 ]+16;									/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*/	_continue:


	for(	iC=zC;	iC>0;	--iC ){		SvC	=*(	pSv0 +iC );		if(SvC==NULL)		{ dBUG_4A( cube_err[1], __FUNCTION__,							iC,			__FILE__, __LINE__ );	Mzc[iC]=-1;		continue; }
				type = SvTYPE(		SvC );					if(!SvOK( SvC ) )	{ dBUG_6A( cube_err[2], __FUNCTION__, svtype_names_ref[ 	type ],	iC, &*SvC,	__FILE__, __LINE__ );	Mzc[iC]=-1;		continue; }
															if(!SvPOK( SvC ) )	{ dBUG_6A( cube_err[3], __FUNCTION__, svtype_names_ref[ 	type ],	iC, &*SvC,	__FILE__, __LINE__ );	Mzc[iC]=-1;		continue; }
		Mpk[ iC] = SvPVbyte(		SvC, CS );					if(CS<16 )		{ dBUG_5A( cube_err[4], __FUNCTION__,							iC, CS,		__FILE__, __LINE__ );	Mzc[iC]=-1;		continue; }
		Mzc[ iC]= zcOf( Mpk[ iC ] );								if(Mzc[ 0 ]==-1 )	{ dBUG_5A( cube_err[5], __FUNCTION__,							iC, CS,		__FILE__, __LINE__ );	Mzc[iC]=-1;		continue; }
		Mpq[ iC]= Mpk[ iC ]+16;
		}
	Xc=Ec=0;
	for(		ic=0;	ic< 8; ++ic ){
		for(	iC=0;	iC <= zC;	++iC ){	if( ic<= Mzc[ iC ])			{	switch( Mpk[ iC ][ ic ] ){ SwCASE_IC2XE_inc(	Mpq[ iC ], Xc, Ec, Mpq[ iC ] );	}
/*hex*/		s = (Xc+1==Ec)?	20-	(__builtin_clzll( Xc ) >>2)
						:	41-(	(__builtin_clzll( Xc ) >>2)+(__builtin_clzll( Ec-1 ) >>2) );
/*dec*/	//	s = (Xc+1==Ec)?	2 +(char) ceil( log10l( (long double)	Xc	) )
		//					4 +(char) ceil( log10l( (long double)	Xc	) ) +(char) ceil( log10l( (long double)	Ec-1	) );
			if( s >cell[ ic ] )	cell[ ic ] = s;	
		}	}												}

	Xc=Ec=0;
	for(		iC=0;	iC <= zC;  ++iC){		pr = row;
		if(	Mzc[ iC ] ==-1 ){				L=	sprintf(	pr, "# cube #%llu error\n", iC );		av_push( avOut, newSVpvn(  row, L ) );
		}else{
	//		Ec = *( (ui64*) Mpk[ iC ] );
			Mpq[ iC ]	= Mpk[ iC ] +16;	for( ic=0; ic<= Mzc[ iC ]; ++ic )	{	switch( Mpk[ iC ][ ic ] ){ SwCASE_IC2XE_inc(	Mpq[ iC ], Xc, Ec, Mpq[ iC ] );	}

				if(	Xc+1 == Ec )	pr +=(	L=	sprintf(	pr,	"0x%llX,",		Xc		) );
				else				pr +=(	L=	sprintf(	pr,	"0x%llX..0x%llX,",	Xc,	Ec-1	) );

									WS = cell[ ic ] -L;
				WSPACE_UNSAFE(	pr,	WS );
				}
		//	Ec = *( (ui64*) Mpk[ iC ] );
								*pr++ = 10;		*pr=0;
			printf( row );
	}	}	}


#ifdef DEBUG
void	_print_mx( unsigned char mx_max, short ix1, short izZ ){
	if( mx_max >32 ){	printf("\r!_print_mx( unsigned char mx_max ): mx_max cannot exceed 32 (it is %d).\n", mx_max ); return; }
	const char	*	label[ ]	= {"H:", "A:", "B:", "E-1:", "I:", "O:", "Ox:", "Q:", "Qx:",  "stat:", " rack:"},
					labelC	= sizeof( label ) / sizeof( label[0] ),
				*	csUVW	="|uvw|",
				*	csUV	="|uv|",
				*	csUW	="|wu|",
				*	csVW	="|vw|",
				*	csU		="|u|",
				*	csV		="|v|",
				*	csW		="|w|";
	SV		*sv;
	ui08				x, c=1;
	char				r=0,
			*ptxt,	txt[	8960	]={13, 10},	// max ixZ for 32-vector display: 8,753
					lblCell	=	1,
					cell[	256	]={	};	// abs max cell size = 19 decade digits +2 sign characters = 21 bytes
	STRLEN	s,	p,	pos[	256	],
				i,	rowLen, txtLen;

	for( r = labelC-1; r >=0; --r )	{	s = strlen( label[ r ] );
							if(	s > lblCell ) lblCell = s;	
							}					p = lblCell;

	for( x=255; x!=mx_max; ++x ){			pos	[ x ] = p;
		s =1 + (char) ceil( log10l( (long double)	H  	[ x ]		) );				cell[ c ]= s>5? s: 5; //min cell width 5 accounting for "stat" enumerator
		s =1 + (char) ceil( log10l( (long double)	A  	[ x ]		) );	if( s >cell[ c ] )	cell[ c ]=s;
		s =1 + (char) ceil( log10l( (long double)	B  	[ x ]		) );	if( s >cell[ c ] )	cell[ c ]=s;
		s =1 + (char) ceil( log10l( (long double)	E  	[ x ]-1	) );	if( s >cell[ c ] )	cell[ c ]=s;
		s =1 + (char) ceil( log10l( (long double)	I  	[ x ]		) );	if( s >cell[ c ] )	cell[ c ]=s;
		s =1 + (char) ceil( log10l( (long double)	O  	[ x ]		) );	if( s >cell[ c ] )	cell[ c ]=s;
		s =1 + (char) ceil( log10l( (long double)	Ox  	[ x ]		) );	if( s >cell[ c ] )	cell[ c ]=s;
		s =1 + (char) ceil( log10l( (long double)	Q  	[ x ]		) );	if( s >cell[ c ] )	cell[ c ]=s;
		s =1 + (char) ceil( log10l( (long double)	Qx  	[ x ]		) );	if( s >cell[ c ] )	cell[ c ]=s;
		p += cell[ c ]+2;	++c;
		}

	for( rowLen = p; x< 255; ++x )	pos[x] =p;	// positioning markers beyond mx_max puts them where they'll get overwritten
	txtLen = ( (	rowLen	+1	)	*	(	labelC	+2 )		+4	+labelC );
	//			^		^		^		^		^		^	^plus this... why?  I really don't know
	//			|		|		|		|		|		plus (4) add'l newlines at end of output
	//			|		|		|		|		... number of cursor rows )
	//			|		|		|		(number of matrix rows, plus...
	//			|		|		multipled by number of rows
	//			|		plus (1) newline per row
	//			length of each row
//	printf("\n calculated output: ( %d +1) * ( %d+2 ) +1 +%d = %llu\n", rowLen, labelC, labelC<<1, txtLen );
	if( txtLen >sizeof( txt ) ){
		printf("_print_mx(): (char *) txt allocation under-sized!  need %llu bytes, have %llu", txtLen, sizeof( txt ) );
		return;
		}
/* whitespace backdrop		*/	for( i=0; i< rowLen;  i+=8 )		*( (ui64*)( txt +i ) ) = 0x2020202020202020;
/*1: u,v,w 	*/
	if( u==v)	if(	u==w )	{	sprintf( txt +pos[u], csUVW  	);	*( txt+pos[u]+5 )=0x20;
				}else	{	sprintf( txt +pos[v], csUV 	);	*( txt+pos[v]+4 )=0x20;
							sprintf( txt +pos[w], csW  	);	*( txt+pos[w]+3 )=0x20;
						}	
	else if(		u==w )	{	sprintf( txt +pos[u], csUW 	);	*( txt+pos[u]+4 )=0x20;
							sprintf( txt +pos[v], csV  	);	*( txt+pos[v]+3 )=0x20;
	}else{					sprintf( txt +pos[u], csU  	);	*( txt+pos[u]+3 )=0x20;
			if(	v==w )	{	sprintf( txt +pos[v], csVW 	);	*( txt+pos[v]+4 )=0x20;
			}else		{	sprintf( txt +pos[v], csV  	);	*( txt+pos[v]+3 )=0x20;
							sprintf( txt +pos[w], csW  	);	*( txt+pos[w]+3 )=0x20;
		}				}																	txt[p++]=10;
/*2: numbers	*/
	ptxt=txt+p;			for( i=0; i< rowLen;  i+=8 )			*( (ui64*)( ptxt+i ) ) = 0x5F5F5F5F5F5F5F5F;
						for( x=255 ; x!=24; ++x ){ 			*(ptxt+pos[x]+sprintf( ptxt+pos[x], "#%llu", x ) )=0x5F;		}
	p+=rowLen;
/*3: H		*/						sprintf( txt +p, fmtStrNl[	lblCell ],    label[++r]		);	p+= lblCell+3;
	c=1;	for( x=255; x!=mx_max; ++x ){	sprintf( txt +p, fmt02X[	cell[ c ] ], 120,	H[	x ]		);	p+= cell[ c++ ]+2;	}
/*4: A		*/						sprintf( txt +p, fmtStrNl[	lblCell ],    label[++r]		);	p+= lblCell+3;
	c=1;	for( x=255; x!=mx_max; ++x ){	sprintf( txt +p, fmtLLU[	cell[ c ] ], 45, 	A[	x ]		);	p+= cell[ c++ ]+2;	}
/*5: B		*/						sprintf( txt +p, fmtStrNl[	lblCell ],    label[++r]		);	p+= lblCell+3;
	c=1;	for( x=255; x!=mx_max; ++x ){	sprintf( txt +p, fmtLLU[	cell[ c ] ], 43, 	B[	x ]		);	p+= cell[ c++ ]+2;	}
/*6: E-1		*/						sprintf( txt +p, fmtStrNl[	lblCell ],    label[++r]		);	p+= lblCell+3;
	c=1;	for( x=255; x!=mx_max; ++x ){	sprintf( txt +p, fmtLLU[	cell[ c ] ], 90, 	E[	x ]-1	);	p+= cell[ c++ ]+2;	}
/*7: I		*/						sprintf( txt +p, fmtStrNl[	lblCell ],    label[++r]		);	p+= lblCell+3;
	c=1;	for( x=255; x!=mx_max; ++x ){	sprintf( txt +p, fmtLLU[	cell[ c ] ], 35, 	I[	x ]		);	p+= cell[ c++ ]+2;	}
/*8: O		*/						sprintf( txt +p, fmtStrNl[	lblCell ],    label[++r]		);	p+= lblCell+3;
	c=1;	for( x=255; x!=mx_max; ++x ){	sprintf( txt +p, fmtLLU[	cell[ c ] ], 46, 	O[	x ]		);	p+= cell[ c++ ]+2;	}
/*9: Ox		*/						sprintf( txt +p, fmtStrNl[	lblCell ],    label[++r]		);	p+= lblCell+3;
	c=1;	for( x=255; x!=mx_max; ++x ){	sprintf( txt +p, fmtLLU[	cell[ c ] ], 44, 	Ox[	x ]		);	p+= cell[ c++ ]+2;	}
/*10: Q		*/						sprintf( txt +p, fmtStrNl[	lblCell ],    label[++r]		);	p+= lblCell+3;
	c=1;	for( x=255; x!=mx_max; ++x ){	sprintf( txt +p, fmtLLU[	cell[ c ] ], 196,	Q[	x ]		);	p+= cell[ c++ ]+2;	}
/*11: Qx		*/						sprintf( txt +p, fmtStrNl[	lblCell ],    label[++r]		);	p+= lblCell+3;
	c=1;	for( x=255; x!=mx_max; ++x ){	sprintf( txt +p, fmtLLU[	cell[ c ] ], 205,	Qx[	x ]		);	p+= cell[ c++ ]+2;	}
/*12: stat	*/						sprintf( txt +p, fmtStrNl[	lblCell ],    label[++r]		);	p+= lblCell+3;
	c=1;	for( x=255; x!=mx_max; ++x ){	sprintf( txt +p, fmtStr[	cell[ c ] ],	RW[x]&0xF8? "...": opStat[ RW[ x ] ] );	p+= cell[ c++ ]+2;	}
/*13: range	*/	ptxt=txt+p;		i=	sprintf( txt +p, fmtStrNl[	lblCell ],    label[++r]		);	//p+= lblCell+3;
/* whitespace backdrop		*/	for(	; i< rowLen;  i+=8 )			*( (ui64*)( ptxt +i ) ) = 0x2020202020202020;
	ptxt+=4;
	if( ixM >=	0 &&( ixM<	mx_max || ixM ==	255	) )	ptxt[ pos[ ixM	]	]=123;	//	right curly-bracket:		start of mod range
	if( izM >=	0 && ( izM<	mx_max || izM ==	255	) )	ptxt[ pos[ izM	]+3	]=125;	//	left curly-bracket:		end of mod range
	if( ix1 >=	0 && ( ix1<	mx_max || ix1 ==	255	) )	ptxt[ pos[ ix1	]+1	]=91;	//	left square bracket:	start of fragment range
	if( izZ >=	0 && ( izZ<	mx_max || izZ ==	255	) )	ptxt[ pos[ izZ	]+2	]=93;	//	right square bracket:	end of fragment range

	p+=rowLen;	*( (ui64*) (txt+p) )=0x000A0A0A0A0A0A0A;	p+=7;		//(7) newlines and (1) NUL
//	else	sprintf( ptxt,	"[not marked]\n\n"	);
//	printf("\nactual output:	%lld byte[s]\n\n", p );
	AvDBUG_PUSH(txt, p);
	}

#else
void _print_mx( unsigned char mx_max, short ix1, short izZ ){	printf("!	_print_mx(...) called w/o debugging implemented by preprocessor\n");	}
#endif

