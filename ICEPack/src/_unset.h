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
	#define OpA0	cS=sprintf(aString, "\r=|x=	x[%lld]: %lld ( 0x%llX )	=|x=  	! ! ! A==0 ic#%d cube #%lld \n\t",	a, x, x, ic, iC	); AvDBUG_PUSH( aString, cS );
	#define OpB0	cS=sprintf(aString, "\r=|x!	x[%lld]: %lld ( 0x%llX )	=|x=  	! ! ! B==0 ic#%d cube #%lld \n\t",	a, x, x, ic, iC	); AvDBUG_PUSH( aString, cS );
	#define OpA		cS=sprintf(aString, "\r=x|_ 	x[%lld]: %lld ( 0x%llX )	=x|_   	\n\t", a, x, x );  AvDBUG_PUSH( aString, cS );
	#define OpAz		cS=sprintf(aString, "\r=x|$ 	x[%lld]: %lld ( 0x%llX )	=x|$  	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
	#define OpB		cS=sprintf(aString, "\r_x|_ 	x[%lld]: %lld ( 0x%llX )	_x|_   	\n\t", a, x, x );  AvDBUG_PUSH( aString, cS );
	#define OpBz		cS=sprintf(aString, "\r_x|$ 	x[%lld]: %lld ( 0x%llX )	_x|$  	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
	#define OpZ		cS=sprintf(aString, "\r|x|_ 	x[%lld]: %lld ( 0x%llX )	|x|_   	\n\t", a, x, x );  AvDBUG_PUSH( aString, cS );
	#define OpZz		cS=sprintf(aString, "\r|x|$ 	x[%lld]: %lld ( 0x%llX )	|x|$  	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
	#define OpC		cS=sprintf(aString, "\r=x= 	x[%lld]: %lld ( 0x%llX )	=x=  	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
	#define OpD 		cS=sprintf(aString, "\r=x_ 	x[%lld]: %lld ( 0x%llX )	=x_  	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
	#define OpE		cS=sprintf(aString, "\r_x= 	x[%lld]: %lld ( 0x%llX )	_x=  	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
	#define OpF		cS=sprintf(aString, "\r_x_ 	x[%lld]: %lld ( 0x%llX )	_x_  	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
	#define OpX		cS=sprintf(aString, "\r___	x[%lld]: %lld ( 0x%llX )	___   	\n\t", a, x, x );	 AvDBUG_PUSH( aString, cS );
#else
	#define OpA0
	#define OpB0
	#define OpA
	#define OpAz
	#define OpB
	#define OpBz
	#define OpZ
	#define OpZz
	#define OpC 
	#define OpD
	#define OpE
	#define OpF
	#define OpX
#endif
