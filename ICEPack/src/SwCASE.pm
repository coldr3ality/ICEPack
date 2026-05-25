package SwCASE;	 use strict; use warnings;
use Inline 'C';# init();
system('cls');
#	_test_lowpass_0IS();
#	_test_lowpass_1I();
#	_test_lowpass_1IS();
#	_test_xover_0Y();
#	_test_xover_1Y();
#	_test_lpxover_00T();
#	_test_lpxover_01T();
#	_test_lpxover_10T();
#	_test_lpxover_01Y();
	_test_lpxover_10Y();
#	_test_lpxover_10Yabs();
#	_test_xxover_01T();
#	_test_xxover_01Y();
#	_test_xxover_01K();
#	_test_xxover_01W();
#	_test_xshelf_00T();
#	_test_xshelf_01T();
#	_test_xshelf_01IS();
#	_test_shelf_01IS();
1;
__DATA__
__C__

/*	welpy	z000	*/
/*   hey hey.   . . . . fe*/
#include	<stdio.h>
#include	"SwCASE.h"

long long			unsigned	int	A	= 0xAAAAAAAAAAAAAAAA,
							B	= 0xBBBBBBBBBBBBBBBB,
							C	= 0xCCCCCCCCCCCCCCCC,
							D	= 0xDDDDDDDDDDDDDDDD;


void _test_lowpass_0IS(){
	printf("_test_lowpass_0IS\n");
				unsigned	char	i,
							opCode;

	long long		unsigned	int	A,	head, tail;

	for(	i=0;    	i<=7;	++i ){								A	= 0xAAAAAAAAAAAAAAAA;
		switch(	i ){	SwCASE_LOWPASS_0IS(				A );	}
		printf("\rcase: 0x%02X	index: %-2d  %016llX\n", i, i,			A );
		}
	printf("\n");
	}
void _test_lowpass_1IS(){
	printf("_test_lowpass_1IS\n");
				unsigned	char	i,
							opCode;

	long long		unsigned	int	A,	head, tail;

	for(	i=0;    	i<=7;	++i ){								A	= 0xAAAAAAAAAAAAAAAA;
		switch(	i ){	SwCASE_LOWPASS_1IS(				A );	}
		printf("\rcase: 0x%02X	index: %-2d  %016llX\n", i, i,			A );
		}
	printf("\n");
	}
void _test_lowpass_1I(){
	printf("_test_lowpass_1I\n");
				unsigned	char	i,
							opCode;

	long long		unsigned	int	B;

	for(	i=0;    	i<=7;	++i ){
		switch(	i ){	SwCASE_LOWPASS_1I(				A,	B );	}
		printf("\rcase: 0x%02X	index: %-2d  %016llX\n", i, i,		B );
		}
	printf("\n");
	}

void _test_xover_0Y(){
	printf("_test_xover_0Y\n");
				unsigned	char	i,
							opCode;

	long long		unsigned	int	C,	head, tail;

	for(	i=0;    	i<=7;	++i ){
		switch(	i ){	SwCASE_XOVER_0Y(					A,	B,	C );	}
		printf("\rcase: 0x%02X	index: %-2d  %016llX\n", i, i,					C );
		}
	printf("\n");
	}
void _test_xover_1Y(){
	printf("_test_xover_1Y\n");
				unsigned	char	i,
							opCode;

	long long		unsigned	int	C,	head, tail;

	for(	i=0;    	i<=7;	++i ){
		switch(	i ){	SwCASE_XOVER_1Y(					A,	B,	C );	}
		printf("\rcase: 0x%02X	index: %-2d  %016llX\n", i, i,					C );
		}
	printf("\n");
	}
void _test_lpxover_00T(){
	printf("_test_lpxover_00T\n");
				unsigned	char	i,
							w,
							opCode;

	long long		unsigned	int	B,	head, body;

	for(		w=0;    	w<=7;	++w ){
		for(	i=0;    	i<=7;	++i ){
					opCode = i |( w<< 3 );							B	= 0xBBBBBBBBBBBBBBBB;
			switch(	opCode ){	SwCASE_LPXOVER_00T(		A,	B );	}
			printf("\rcase: 0x%02X	width x index: %2d x %-2d  %016llX\n", opCode, w, i,	B );
			}
		printf("\n");
		}
	printf("\n");
	}

void _test_lpxover_01T(){
	printf("_test_lpxover_01T\n");
				unsigned	char	i,
							w,
							opCode;

	long long		unsigned	int	B,	head, body;

	for(		w=0;    	w<=7;	++w ){
		for(	i=0;    	i<=7;	++i ){
					opCode = i |( w<< 3 );							B	= 0xBBBBBBBBBBBBBBBB;
			switch(	opCode ){	SwCASE_LPXOVER_01T(		A,	B );	}
			printf("\rcase: 0x%02X	width x index: %2d x %-2d  %016llX\n", opCode, w, i,	B );
			}
		printf("\n");
		}
	printf("\n");
	}
void _test_lpxover_10T(){
	printf("_test_lpxover_10T\n");
				unsigned	char	i,
							w,
							opCode;

	long long		unsigned	int	B,	head, body;

	for(		w=0;    	w<=7;	++w ){
		for(	i=0;    	i<=7;	++i ){
					opCode = i |( w<< 3 );							B	= 0xBBBBBBBBBBBBBBBB;
			switch(	opCode ){	SwCASE_LPXOVER_10T(		A,	B );	}
			printf("\rcase: 0x%02X	width x index: %2d x %-2d  %016llX\n", opCode, w, i,	B );
			}
		printf("\n");
		}
	printf("\n");
	}
void _test_lpxover_01Y(){
	printf("_test_lpxover_01Y\n");
				unsigned	char	i,
							w,
							opCode;

	long long		unsigned	int	C,	head, body;

	for(		w=0;    	w<=7;	++w ){
		for(	i=0;    	i<=7;	++i ){
					opCode = i |( w<< 3 );
			switch(	opCode ){	SwCASE_LPXOVER_01Y(		A,	B,	C );	}
			printf("\rcase: 0x%02X	width x index: %2d x %-2d  %016llX\n", opCode, w, i,	C );
			}
		printf("\n");
		}
	printf("\n");
	}
void _test_lpxover_10Y(){
	printf("_test_lpxover_10Y\n");
				unsigned	char	i,
							w,
							opCode;

	long long		unsigned	int	C,	head, body;

	for(		w=0;    	w<=7;	++w ){
		for(	i=0;    	i<=7;	++i ){
					opCode = i |( w<< 3 );
			switch(	opCode ){	SwCASE_LPXOVER_10Y(		A,	B,	C );	}
			printf("\rcase: 0x%02X	width x index: %2d x %-2d  %016llX\n", opCode, w, i,	C );
			}
		printf("\n");
		}
	printf("\n");
	}
void _test_lpxover_10Yabs(){
	printf("_test_lpxover_10Yabs\n");
				unsigned	char	i,
							w,
							opCode;

	long long		unsigned	int	C,	head, body;

	for(		w=0;    	w<=7;	++w ){
		for(	i=0;    	i<=7;	++i ){
					opCode = i |( w<< 3 );
			switch(	opCode ){	SwCASE_LPXOVER_10Yabs(		A,	B,	C );	}
			printf("\rcase: 0x%02X	width x index: %2d x %-2d  %016llX\n", opCode, w, i,	C );
			}
		printf("\n");
		}
	printf("\n");
	}
void _test_xxover_01T(){
	printf("_test_xxover_01T\n");
				unsigned	char	i,
							w,
							opCode;

	long long		unsigned	int	B,	body, tail;

	for(		w=0;    	w<=7;	++w ){
		for(	i=0;    	i<=7;	++i ){
					opCode = i |( w<< 3 );							B	= 0xBBBBBBBBBBBBBBBB;
			switch(	opCode ){	SwCASE_XXOVER_01T(		A,	B );	}
			printf("\rcase: 0x%02X	width x index: %2d x %-2d  %016llX\n", opCode, w, i,	B );
			}
		printf("\n");
		}
	printf("\n");
	}
void _test_xxover_01Y(){
	printf("_test_xxover_01Y\n");
				unsigned	char	i,
							w,
							opCode;

	long long		unsigned	int	C,	body, tail;

	for(		w=0;    	w<=7;	++w ){
		for(	i=0;    	i<=7;	++i ){
					opCode = i |( w<< 3 );
			switch(	opCode ){	SwCASE_XXOVER_01Y(		A,	B,	C );	}
			printf("\rcase: 0x%02X	width x index: %2d x %-2d  %016llX\n", opCode, w, i,	C );
			}
		printf("\n");
		}
	printf("\n");
	}
void _test_xxover_01K(){
	printf("_test_xxover_01K\n");
				unsigned	char	i,
							w,
							opCode;

	long long		unsigned	int	C,	head, body, tail;

	for(		w=0;    	w<=7;	++w ){
		for(	i=0;    	i<=7;	++i ){
					opCode = i |( w<< 3 );							C	= 0xCCCCCCCCCCCCCCCC;
			switch(	opCode ){	SwCASE_XXOVER_01K(		A,	B,	C );	}
			printf("\rcase: 0x%02X	width x index: %2d x %-2d  %016llX\n", opCode, w, i,	C );
			}
		printf("\n");
		}
	printf("\n");
	}
void _test_xxover_01W(){
	printf("_test_xxover_01W\n");
				unsigned	char	i,
							w,
							opCode;

	long long		unsigned	int		head, body, tail;

	for(		w=0;    	w<=7;	++w ){
		for(	i=0;    	i<=7;	++i ){
					opCode = i |( w<< 3 );
			switch(	opCode ){	SwCASE_XXOVER_01W(		A,	B,	C,	D);	}
			printf("\rcase: 0x%02X	width x index: %2d x %-2d  %016llX\n", opCode, w, i,	D );
			}
		printf("\n");
		}
	printf("\n");
	}
void _test_xshelf_00T(){
	printf("_test_xshelf_00T\n");
				unsigned	char	i,
							w,
							opCode;

	long long		unsigned	int	B,	head, tail;

	for(		w=0;    	w<=7;	++w ){
		for(	i=0;    	i<=7;	++i ){
					opCode = i |( w<< 3 );						B	= 0xBBBBBBBBBBBBBBBB;
			switch(	opCode ){	SwCASE_XSHELF_00T(		A,	B );	}
			printf("\rcase: 0x%02X	width x index: %2d x %-2d  %016llX\n", opCode, w, i,	B );
			}
		printf("\n");
		}
	printf("\n");
	}
void _test_xshelf_01T(){
	printf("_test_xshelf_01T\n");
				unsigned	char	i,
							w,
							opCode;

	long long		unsigned	int	B,	head, tail;

	for(		w=0;    	w<=7;	++w ){
		for(	i=0;    	i<=7;	++i ){
					opCode = i |( w<< 3 );							B	= 0xBBBBBBBBBBBBBBBB;
			switch(	opCode ){	SwCASE_XSHELF_01T(		A,	B );	}
			printf("\rcase: 0x%02X	width x index: %2d x %-2d  %016llX\n", opCode, w, i,	B );
			}
		printf("\n");
		}
	printf("\n");
	}
void _test_xshelf_01IS(){
	printf("_test_xshelf_01IS\n");
				unsigned	char	i,
							w,
							opCode;

	long long		unsigned	int	A,	head, tail;

	for(		w=0;    	w<=7;	++w ){
		for(	i=0;    	i<=7;	++i ){
					opCode = i |( w<< 3 );					A	= 0xAAAAAAAAAAAAAAAA;
			switch(	opCode ){	SwCASE_XSHELF_01IS(		A );	}
			printf("\rcase: 0x%02X	width x index: %2d x %-2d  %016llX\n", opCode, w, i,	A );
			}
		printf("\n");
		}
	printf("\n");
	}
void _test_shelf_01IS(){
	printf("_test_shelf_01IS\n");
				unsigned	char	i,
							w,
							opCode;

	long long		unsigned	int	A,	head, tail;

	for(		w=0;    	w<=7;	++w ){
		for(	i=0;    	i<=7;	++i ){
					opCode = i |( w<< 3 );					A	= 0xAAAAAAAAAAAAAAAA;
			switch(	opCode ){	SwCASE_SHELF_01IS(		A );	}
			printf("\rcase: 0x%02X	width x index: %2d x %-2d  %016llX\n", opCode, w, i,	A );
			}
		printf("\n");
		}
	printf("\n");
	}
