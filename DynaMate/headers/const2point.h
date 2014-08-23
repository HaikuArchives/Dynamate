	uint8 *pieces;
	if (SIZE==24)
		pieces=(uint8 *)pieces24;
	else
		pieces=(uint8 *)pieces16;
	
	switch (piece)
	{
		case S_EMPTY		:return(pieces+(SIZE*SIZE)*0);
		case S_GLUE3		:return(pieces+(SIZE*SIZE)*1);
		case S_GLUE5		:return(pieces+(SIZE*SIZE)*2);
		case S_PASS_VERT	:return(pieces+(SIZE*SIZE)*3);
		case S_PASS_HORI	:return(pieces+(SIZE*SIZE)*4);
		case S_TELEP_0		:return(pieces+(SIZE*SIZE)*5);
		case S_TELEP_1		:return(pieces+(SIZE*SIZE)*6);
		case S_CYKLECOL		:return(pieces+(SIZE*SIZE)*7);
		case S_CYKLEDIR_CW	:return(pieces+(SIZE*SIZE)*8);
		case S_CYKLEDIR_CCW	:return(pieces+(SIZE*SIZE)*9);
		case S_GRAY			:return(pieces+(SIZE*SIZE)*10);
		case S_DEATH		:return(pieces+(SIZE*SIZE)*11);
		case S_BLACK		:return(pieces+(SIZE*SIZE)*12);
		case S_YELLOW		:return(pieces+(SIZE*SIZE)*13);
		case S_RED			:return(pieces+(SIZE*SIZE)*14);
		case S_GREEN		:return(pieces+(SIZE*SIZE)*15);
		case S_BLUE			:return(pieces+(SIZE*SIZE)*16);

		case M_GLUE3		:return(pieces+(SIZE*SIZE)*17);
		case M_GLUE5		:return(pieces+(SIZE*SIZE)*18);
		case M_PASS_VERT	:return(pieces+(SIZE*SIZE)*19);
		case M_PASS_HORI	:return(pieces+(SIZE*SIZE)*20);
		case M_TELEP_0		:return(pieces+(SIZE*SIZE)*21);
		case M_TELEP_1		:return(pieces+(SIZE*SIZE)*22);
		case M_CYKLECOL		:return(pieces+(SIZE*SIZE)*23);
		case M_CYKLEDIR_CW	:return(pieces+(SIZE*SIZE)*24);
		case M_CYKLEDIR_CCW	:return(pieces+(SIZE*SIZE)*25);
		case M_GRAY			:return(pieces+(SIZE*SIZE)*26);
		case M_DEATH		:return(pieces+(SIZE*SIZE)*27);
		case M_BLACK		:return(pieces+(SIZE*SIZE)*28);
		case M_YELLOW		:return(pieces+(SIZE*SIZE)*29);
		case M_RED			:return(pieces+(SIZE*SIZE)*30);
		case M_GREEN		:return(pieces+(SIZE*SIZE)*31);
		case M_BLUE			:return(pieces+(SIZE*SIZE)*32);
		
		case S_GLUE0		:return(pieces+(SIZE*SIZE)*33);
		case M_GLUE0		:return(pieces+(SIZE*SIZE)*34);
		
		default				:return(pieces);
	}
