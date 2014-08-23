	switch (piece)
	{
		case S_EMPTY		:return(pieces+256*0);
		case S_GLUE3		:return(pieces+256*1);
		case S_GLUE5		:return(pieces+256*2);
		case S_PASS_VERT	:return(pieces+256*3);
		case S_PASS_HORI	:return(pieces+256*4);
		case S_TELEP_0		:return(pieces+256*5);
		case S_TELEP_1		:return(pieces+256*6);
		case S_CYKLECOL		:return(pieces+256*7);
		case S_CYKLEDIR_CW	:return(pieces+256*8);
		case S_CYKLEDIR_CCW	:return(pieces+256*9);
		case S_GRAY			:return(pieces+256*10);
		case S_DEATH		:return(pieces+256*11);
		case S_BLACK		:return(pieces+256*12);
		case S_YELLOW		:return(pieces+256*13);
		case S_RED			:return(pieces+256*14);
		case S_GREEN		:return(pieces+256*15);
		case S_BLUE			:return(pieces+256*16);

		case M_GLUE3		:return(pieces+256*17);
		case M_GLUE5		:return(pieces+256*18);
		case M_PASS_VERT	:return(pieces+256*19);
		case M_PASS_HORI	:return(pieces+256*20);
		case M_TELEP_0		:return(pieces+256*21);
		case M_TELEP_1		:return(pieces+256*22);
		case M_CYKLECOL		:return(pieces+256*23);
		case M_CYKLEDIR_CW	:return(pieces+256*24);
		case M_CYKLEDIR_CCW	:return(pieces+256*25);
		case M_GRAY			:return(pieces+256*26);
		case M_DEATH		:return(pieces+256*27);
		case M_BLACK		:return(pieces+256*28);
		case M_YELLOW		:return(pieces+256*29);
		case M_RED			:return(pieces+256*30);
		case M_GREEN		:return(pieces+256*31);
		case M_BLUE			:return(pieces+256*32);
		
		case S_GLUE0		:return(pieces+256*33);
		case M_GLUE0		:return(pieces+256*34);
		
		default				:return(pieces);
	}
