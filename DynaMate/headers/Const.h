#ifndef dm_const_h
#define dm_const_h

enum{
/*
			[empty]
		(non-chg)
		|	|
		|	|	[glue]
		|	(content)
		|		[passv/h]
		|
	(mov-piece)
	|	|
	|	|	[tele]
	|	(chg)
	|		[cykle]
	|
(static/moveble)
	|
	|	(non-stone)
	|	|	[gray,death]
	|	|
	(non-moving)
		|
		(stone)
			|
			|	[bl,ylw]
			(real)
				[r,g,b]

*/
S_EMPTY			=	0x00,//00000 000;

S_GLUE0			=	0x10,//00010 000;
S_GLUE3			=	0x11,//00010 001;
S_GLUE5			=	0x12,//00010 010;

S_PASS_VERT		=	0x18,//%00011 000;
S_PASS_HORI		=	0x19,//%00011 001;

S_TELEP_0		=	0x20,//%0010 0000;
S_TELEP_1		=	0x21,//%0010 0001;

S_CYKLECOL		=	0x30,//%0011 0000;
S_CYKLEDIR_CW	=	0x31,//%0011 0001;
S_CYKLEDIR_CCW	=	0x32,//%0011 0010;

S_GRAY			=	0x50,//%0101 0000;
S_DEATH			=	0x51,//%0101 0001;

S_BLACK			=	0x70,//%01110 000;
S_YELLOW		=	0x71,//%01110 001;

S_RED			=	0x78,//%01111 000;
S_GREEN			=	0x79,//%01111 001;
S_BLUE			=	0x7a,//%01111 010;

M_GLUE0			=	0x90,//%10010 000;
M_GLUE3			=	0x91,//%10010 001;
M_GLUE5			=	0x92,//%10010 010;

M_PASS_VERT		=	0x98,//%10011 000;
M_PASS_HORI		=	0x99,//%10011 001;

M_TELEP_0		=	0xa0,//%1010 0000;
M_TELEP_1		=	0xa1,//%1010 0001;

M_CYKLECOL		=	0xb0,//%1011 0000;
M_CYKLEDIR_CW	=	0xb1,//%1011 0001;
M_CYKLEDIR_CCW	=	0xb2,//%1011 0010;

M_GRAY			=	0xd0,//%1101 0000;
M_DEATH			=	0xd1,//%1101 0001;

M_BLACK			=	0xf0,//%11110 000;
M_YELLOW		=	0xf1,//%11110 001;

M_RED			=	0xf8,//%11111 000;
M_GREEN			=	0xf9,//%11111 001;
M_BLUE			=	0xfa //%11111 010;

};

#endif // dm_const_h