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
	#define Op5		cS=sprintf(aString, "\r=+= 	x[%lld]: %lld ( 0x%llX )	cube #%lld ic#%d	u=%d	=+=  	E[%d..%d]: %llX..%llX\n\t", a, x, x, iC, ic, u, u, v, E[u],E[v] );	AvDBUG_PUSH( aString, cS );
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
#else/* 		^ Abnormal encoding: null padding at non-origin.  Non-fatal.	*/
	#define	Op9
	#define	Op10
#endif


	