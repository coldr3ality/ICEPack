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
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "dBUG.h"
#include	"_av_commit.h"
//	void _av_commit() conducts a streamlined batch splice on AV* avICE by unwrapping the rSeq schedule as a sequence of mixed ascending/descending ranges.
void _av_commit(){	/* 	does batch splice on avICE, swapping new/old fragments. */
//	if( xcª -ixº <1 ){ printf( "\r	_av_commit() enter	%s %s line %d\n", __FUNCTION__, __FILE__, __LINE__ ); }
/*	word up: the algorithmic action of compaction and expansion is charicterized by "peristalsis"—
	a directed, sequential wave of movement where the order of units matters structurally,
	not just for performance.

	When you're moving overlapping regions of the same buffer, the direction of iteration isn't a choice; it's a necessity.
	Move forward during compaction, backward during expansion, or you corrupt unread source data.
	That iterative directionality is the operation's defining constraint, and it's what makes it fundamentally different
	from a simple copy or memcpy.

	*/
	long long int	asc, /*dsc, (global) */ zsc, xsc, juke, pmo, post_zC;

	
/*	TODO:	Reformulate zero-cross detection logic to occur earlier on the event-driven basis of the AvPOSTxxx macros,
			to eliminate (2) second-order nested loops in the critical path	*/
/*	NOTES:

	The "_av_commit()" function finalizes all deferred array splices without copying any shifted elements more than once.
	It is only called once to finalize all insertions and deletions made by _sv_commit_[n1]x(), which can run many times per accessor call.

	The parameters of all deferred splices are aggregated and temporarily stored in these (4) global arrays:
		> rSeqSrc 	—the absolute index number of the control index in the pre-operational array.
		> rSeqDst 	—the absolute index number of the control index in the post-operational array.
		> rSeqIns 	—the number of elements to be inserted at destination index.
		> rSeqCut 	—the number of elements to be removed at source index.

	These (4) arrays align to form the "resequencing schedule", a 4x256 matrix where iterators (asc) and (dsc) each select a 1x4 vector.
	The schedule contains the relative offsets, lengths, and count parameters necessary to do multiple concurrent splices.
	It is populated left-to-right, but it is processed as a descending series of ascending / descending runs, right-to-left overall.
	The running balance of elements in the pre-op vs post-op array can go positive or negative after any consecutive splice, so,	
	the main loop is actually two main loops which flip-flop at those junctures where the running balance changes signs, crossing zero.
	The specific comparison which yields this sign is: (source index post-cut) <=> (destination index pre-insert).
	This is due to the diference in ordinality of cuts and inserts which translates the control index from where it is when first registered;
	both are determined only after the cursor register "step_iC" has passed the reference index, yet to-be-cut elements are already there,
	whereas to-be-inserted elements are not— therefore the scheduled control index leads its cuts and trails its inserts.

	Prior to getting here, consecutive splice ops are aggregated into "batch steps" by common "control index".
	Each step defines a single shift-insert-cut iteration which affects one or many splice operations for a given control index.
	
	
	The loop starts by determining which direction to iterate in depending on whether the new length is greater than the old length.
	Actually, the direction of iteration will reverse every time the relative difference between source and destination index crosses zero.
	When flipping to "ascending mode", the (asc) iterator jumps its entire step run all at once, back tracking to (dsc-1) step-by-step;
	upon returning to (dsc-1), it jumps that amount again, flopping over to "descending mode" which picks up one element down
	from where "ascending mode" last began.  Descending mode simply iterates, while ascending mode "jukes".

	Overall though, the flip-flopping iteration pattern starts at the high end of the rSeq schedule and works leftwards to zero.
	The transitional boundary from descending to ascending shift requires special control logic (labeled "_edge").

	This text-based illustration helped me wrap my mind around the process:

dsc:		 0                    1     2               3            4        5            6    7    8    9
	---------|--------------------|-----|---------------|------------|--------|------------|----|----|----|
src:	.......xx|...............xxxxx|...xx|............xxx|....xxxxxxxx|.......x|...........x|xxxx|....|...x|..........$
		2-2                  3-5   8-2             3-3          1-8      2-1          6-1  8-4  1-0  0-1
		 0                   -2     4               4           -3       -2            3    7    8    7
dst:	.......|+‡...............|++‡...|+++++++‡............|++‡....|‡.......|+‡...........|+++++‡|+++++++‡....|‡...|..........$
	       0                 1      2                    3       4        5             6      7            8    9


	In ascending mode, the order of operations per step is:
		> cut deleted elements
		> shift intermediate elements
		> shift control index
		> insert new elements

	In descending mode, the order of operations per step (*with one caveat) is:
		> shift intermediate elements
		> insert new elements
		> shift control index
		> cut deleted elements

	* The first descending step after flopping from ascending mode does not shift the control index (special case labeled "_descx").
	Rather, that assignment is preempted by the first step of the preceding ascending run and prioritized to prevent potential clobbering.

	Inserts and cuts are scheduled by calls to AvPOST and AvCUT,
	but the shift parameter can only be computed in-between instantiations of steps.
	Obviously the final call is never followed by another, so to actually get things started here, the first thing we do is finalize the last step.

	*/
	/* finalize the last step		*/
			rSeq_iR[	dsc ]	=	iR;
			rSeqSrc[	dsc ]	=	step_iC;			rel_iC -=	rSeqCut[ dsc ];
			rSeqDst[	dsc ]	=	step_iC 		+	rel_iC;
							post_zC=zC		+	rel_iC +	rSeqIns[ dsc ];	if( post_zC< 0 ){	AvFILLp( avICE ) =-1;	return;	}

	/* unless the last step targets the last element, append a terminating null step to align with the pre-op and post-op array lengths */
	if(	step_iC< zC ){
++	dsc;		rSeqDst[	dsc ]	=	post_zC;
			rSeqSrc[	dsc ]	=	zC;
			rSeq_iR[	dsc ]	=	-1;
			rSeqIns[	dsc ]	=	0;
			rSeqCut[	dsc ]	=	0;
//	}else{	rSeqDst[	dsc ]	-=	rSeqCut[ dsc ];
//			rSeqCut[	dsc ]	=	0;
		}
	zsc=dsc;
	/* compute destination array size and return now if it's lt/eq zero, or extend if it's gt AvMAX  (AvFILLp is set last of all) */
	if( zC< post_zC ){	av_extend(	avICE,	post_zC+1 );	Aº=AvARRAY( avICE );	}

	#define $srcD 	rSeqSrc[	dsc ]
	#define $cutD		rSeqCut[	dsc ]
	#define $srcutD 	rSeqSrc[	dsc ] - rSeqCut[	dsc ]
	#define $dstD 	rSeqDst[	dsc ]
	#define $insD		rSeqIns[	dsc ]
	#define $dstinsD 	rSeqDst[	dsc ] - rSeqIns[	dsc ]

	#define $srcA		rSeqSrc[	asc ]
	#define $cutA		rSeqCut[	asc ]
	#define $srcutA	rSeqSrc[	asc ] - rSeqCut[	asc ]
	#define $dstA 	rSeqDst[	asc ]
	#define $insA		rSeqIns[	asc ]
	#define $dstinsA	rSeqDst[	asc ] - rSeqIns[	asc ]

	#define $srcX  	rSeqSrc[	xsc ]
	#define $srcutX	rSeqSrc[	xsc ] - rSeqCut[	xsc ]
	#define $dstX 	rSeqDst[	xsc ]
	#define $dstinsX	rSeqDst[	xsc ] - rSeqIns[	xsc ]
																						dBUG_AvCOMMIT_SCHED_PRE	
	/*	The first thing av_commit needs to do is determine whether to start in ascending or descending mode.
		However, as long as the pre- and post-commit source indeces for a given step are equal, this is ambiguous.
		In such cases, we can operate in either ascending  or descending mode, but when we reach a step with a difference,
		we need to be in the correct mode for that step already; the "juke" iterator will have already been determined.
		So, the very first thing we need to do is look ahead to where the tie breaks, and determine mode based on that step (xsc)
		rather than the initial step (dsc). 	*/
	for( xsc=asc=dsc;	xsc && $srcutX==$dstX; --xsc );

	if(				$srcutX> $dstX ){
		do	{	/*	ascending start */	if( dsc ) --dsc;	else	{	src=				dst=Aº;
														juke = asc+1;		asc=0;	dsc=-1;	dBUGiniA;	goto _asce;
													}
			} while(	$srcutD>=$dstD );						src= Aº+$srcD;	dst=Aº+$dstD;
														juke = asc -dsc;	asc=1+	dsc;		dBUGiniA;	goto _asce;

	}else	{	/*	descending start */						src = Aº +zC;	dst = Aº +post_zC;
//	}else	{	/*	descending start */						src= Aº+$srcZ;	dst=Aº+$dstZ;
			while(	$srcutA<=$dstA )	 if( asc ) --asc; else	{	juke = dsc+1;						dBUGiniD; 	goto _desc;
			}										}	juke = dsc-asc;					dBUGiniD;

	if( juke==0)	printf("\n?	2026-09-21 experiment: does it break anything?	in %s line %d\n", __FILE__, __LINE__);

	do		{	/*	as-needed reversal of normally-descending processing order	("juke" action)	*/
		if( juke )	/*	2026-09-21 in response to precursor #111 w/ ReBAL_ENABLE defined		*/
	_desc:	do	{											/*	descending expansion	*/	dBUGdscDIR;
				if( src != dst ) {	pmo = (src-Aº) -$srcD;											dBUG_PMv("_desc");
						if(0<	pmo ) do {	*	dst-- =	*	src--;/*	peristaltic move up		*/	dBUGpmvD; } while( -- pmo );
						else{				dst	-= pmo;	src= Aº+$srcD;					}
				}else	{					dst	=		src= Aº+$srcD;
						}
				if( dst -$insD != src )	{	  *(	dst-$insD)= *	src;	/*	the oft-erratic ctrl index	*/	dBUGlocD;	}
				while(	$insD--	)	{	  *	dst-- 	=	rSeq_SV[	rSeq_iR[ dsc ]--];			dBUGinsD;	}
				if(		$cutD	)	{					src -=$cutD +1;	$cutD=0;			}
				else									--	src;
										--	dst;
	--dsc;		} while( --juke >0 );	if( dsc< 0) break;

	_edge:	if( src != dst )	{	pmo = (src-Aº) -$srcD;			/*	finish to zero-crossing	*/	dBUG_PMv("_edge");
						if(0<	pmo ) do { 	*	dst--	= *	src--;							dBUGpmvE;	} while( -- pmo );
						}
			asc	= dsc;										/*	seek asc start index 	*/
			while(	$srcutD >= $dstD )	if( dsc ) --dsc;	else
				{	src=				dst=Aº;				juke = asc+1;		asc=0;	dsc=-1;	dBUGriniA;	goto _asce;
				}	src= Aº+$srcD;	dst=Aº+$dstD;		juke = asc -dsc;	asc=1+	dsc;		dBUGriniA;

	_asce:	do	{											/*	ascending compaction	*/	dBUGascDIR;
				if(	$cutA ){	pmo=( $srcA -$cutA )		-	(src -Aº);		$cutA=0;			}
				else			pmo= $srcA				-	(src -Aº);						dBUG_PMv("_asce");
					
				if(0<	pmo ) if ( src!=dst )	{ do	{ *	dst++	= *	src++;/*	peristaltic move down  	*/	dBUGpmvA; } while( -- pmo );
						}else  		{		dst += pmo;									}

				if(	dst-Aº != $srcA )	{	  *	dst		= *(	Aº +$srcA );						dBUGlocA;	}
										++	dst;			src = Aº +$srcA +1;
				while( $insA )			{	  *	dst++	=	rSeq_SV[	rSeq_iR[ asc ] - --$insA ];		dBUGinsA;	}

	++asc;		} while( --juke >0 ); 	if( dsc< 0) break;

			src = dst	= Aº +$dstD;	/* cursor re-jumps past start (-1) of now-complete asc run	*/
			asc = dsc;
			while(	$srcutA <= $dstA ) if( asc ) --asc; 	else	{	juke = dsc;						dBUGriniD;	goto _descx;
													}	juke = dsc-asc-1;					dBUGriniD;	//

	_descx:			pmo = (src-Aº) -$srcD;					/*	transversal to _desc		*/	dBUGdscDIR;	dBUG_PMv("_descx");
				if(0<	pmo )					dst -= pmo;
			//		^ pmo can go negative here, failing unset() crash precursor #7
				while(	$insD--	)	{	  *	dst-- 	=	rSeq_SV[	rSeq_iR[ dsc ]--];			dBUGinsD;	}
														/*	the erratic control index		*/
			/*! ! ! 	In _descx, we complete the "juke" by re-jumping to where _asce started,		*/
			/*		in order to resume _desc.											*/
			/*		While this is like _desc in that it does process one step of the splice schedule,	*/
			/*		there is nothing to shift because _edge already took care of that.			*/
			/*		This means there is no "peristaltic move down" or "erratic control index" line.	*/
			/*		Furthermore, while all (3) blocks evaluate the breaking point for the main loop,	*/
			/*		the main loop logically breaks a litte earlier here:							*/
			if(	dsc==0 ) break;			--	dst;
				if(		$cutD	)	{					src =Aº +($srcutD) -1;	$cutD=0; }
				else										src =Aº +$srcD -1;

	--dsc;	} while( 1 ); /*main loop */														dBUG_AvCOMMIT_SCHED_POST
	dsc=asc=juke=0;

	if( AvFILLp( avICE ) != post_zC ) AvFILLp( avICE ) = post_zC;
	for(; zsc>=0; --zsc ){
		rSeq_iR[	zsc ]=-1;
		rSeqIns[	zsc ]=0;
		rSeqCut[	zsc ]=0;
		rSeqSrc[ 	zsc ]=0;
		rSeqDst[	zsc ]=0;
		rSeq_SV[	zsc ]=NULL;
		}
//	if( xcª -ixº <1 ){ printf( "\r	_av_commit() exit	%s %s line %d\n", __FUNCTION__, __FILE__, __LINE__ ); }
	}

/*	dogsddddddcdddddddd	*/