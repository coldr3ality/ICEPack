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

#include	"_ICE.h"
#include	"_AvSEQ.h"
#include "access_extern.h"
#include "access.h"

#ifdef DEBUG_ACCESS_L2X			//	audit nominal activity
	#define Op0		cS=sprintf(aString, "\r=+|_	x[%lld]: %lld ( 0x%llX )	cube #%lld ic#%d 	u=%d	=+|_ 	\n\t", a, x, x, iC, ic, u );	AvDBUG_PUSH( aString, cS );
	#define Op1 		cS=sprintf(aString, "\r!|+=	x[%lld]: %lld ( 0x%llX )	cube #%lld ic#%d	u=%d	!|+= 	\n\t", a, x, x, iC, ic, u );	AvDBUG_PUSH( aString, cS );
	#define Op2		cS=sprintf(aString, "\r=|+=	x[%lld]: %lld ( 0x%llX )	cube #%lld ic#%d	u=%d	=|+= 	\n\t", a, x, x, iC, ic, u );	AvDBUG_PUSH( aString, cS );
	#define Op3		cS=sprintf(aString, "\r=+|$	x[%lld]: %lld ( 0x%llX )	cube #%lld ic#%d	u=%d	=+|$ 	\n\t", a, x, x, iC, ic, u );	AvDBUG_PUSH( aString, cS );
	#define Op4		cS=sprintf(aString, "\r=+_ 	x[%lld]: %lld ( 0x%llX )	cube #%lld ic#%d	u=%d	=+_  	\n\t", a, x, x, iC, ic, u );	AvDBUG_PUSH( aString, cS );
	#define Op5		cS=sprintf(aString, "\r=+= 	x[%lld]: %lld ( 0x%llX )	cube #%lld ic#%d	u=%d	=+=  	\n\t", a, x, x, iC, ic, u );	AvDBUG_PUSH( aString, cS );
	#define Op6		cS=sprintf(aString, "\r_+_	x[%lld]: %lld ( 0x%llX )	cube #%lld ic#%d	u=%d	_+_  	\n\t", a, x, x, iC, ic, u );	AvDBUG_PUSH( aString, cS );
	#define Op7		cS=sprintf(aString, "\r_+=	x[%lld]: %lld ( 0x%llX )	cube #%lld ic#%d	u=%d	_+=  	\n\t", a, x, x, iC, ic, u );	AvDBUG_PUSH( aString, cS );
	#define Op8		cS=sprintf(aString, "\r===	x[%lld]: %lld ( 0x%llX )	cube #%lld ic#%d	u=%d	===  	\n\t", a, x, x, iC, ic, u );	AvDBUG_PUSH( aString, cS );
#else
	#define Op0
	#define Op1 
	#define Op2
	#define Op3
	#define Op4
	#define Op5
	#define Op6
	#define Op7
	#define Op8
#endif
#if defined( DEBUG_ACCESS_L1 ) || defined( DEBUG_ACCESS_L2 ) || defined( DEBUG_ACCESS_L2X ) || defined( $DEBUG_ACCESS_L3 )
	#define	Op9 	cS=sprintf(aString, "\r=|==	x[%lld]: %lld ( 0x%llX )	=|==  	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
	#define	Op10	cS=sprintf(aString, "\r=!= 	x[%lld]: %lld ( 0x%llX )	=!=   	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
#else/* 		^ Abnormal encoding: null padding at non-origin.  Non-fatal and self-healing.	*/
	#define	Op9
	#define	Op10
#endif

//	#define	DEBUG_ALPHA
#ifdef		DEBUG_ALPHA
	#define RT	printf("\r	return at line %d\n\n\n", __LINE__ );
	#define GI	printf("\rgoto _inter	line %d\n", __LINE__ );
	#define GE	printf("\ngoto _epiloc	line %d\n", __LINE__ );
	#define GC	printf("\rgoto _co_epiloc	line %d\n", __LINE__ );
	#define GS	printf("\rgoto _search	line %d\n", __LINE__ );
	#define GL	printf("\rgoto _loca 	line %d\n", __LINE__ );
	#define GA	printf("\rgoto _ante	line %d\n", __LINE__ );
	#define AL	printf("\rgoto _anteloc	line %d\n", __LINE__ );
	#define GIa	printf("\rgoto _intra	line %d\n", __LINE__ );
	#define GV	printf("\rgoto _intra_v	line %d\n", __LINE__ );
	#define GX	printf("\rgoto _next_x	line %d\n", __LINE__ );
	#define GSv	printf("\ngoto _sv_commit	line %d\n", __LINE__ );
#else
	#define RT
	#define GI
	#define GE
	#define GC
	#define GS
	#define GL
	#define GA
	#define AL
	#define GIa
	#define GV
	#define GX
	#define GSv
#endif