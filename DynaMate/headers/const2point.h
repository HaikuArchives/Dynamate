	uint8 *pieces;
	if (size==24)
		pieces=(uint8 *)pieces24;
	else
		pieces=(uint8 *)pieces16;
	
	switch (piece)
	{
		case S_EMPTY		:return(pieces+(size*size)*0);
		case S_GLUE3		:return(pieces+(size*size)*1);
		case S_GLUE5		:return(pieces+(size*size)*2);
		case S_PASS_VERT	:return(pieces+(size*size)*3);
		case S_PASS_HORI	:return(pieces+(size*size)*4);
		case S_TELEP_0		:return(pieces+(size*size)*5);
		case S_TELEP_1		:return(pieces+(size*size)*6);
		case S_CYKLECOL		:return(pieces+(size*size)*7);
		case S_CYKLEDIR_CW	:return(pieces+(size*size)*8);
		case S_CYKLEDIR_CCW	:return(pieces+(size*size)*9);
		case S_GRAY			:return(pieces+(size*size)*10);
		case S_DEATH		:return(pieces+(size*size)*11);
		case S_BLACK		:return(pieces+(size*size)*12);
		case S_YELLOW		:return(pieces+(size*size)*13);
		case S_RED			:return(pieces+(size*size)*14);
		case S_GREEN		:return(pieces+(size*size)*15);
		case S_BLUE			:return(pieces+(size*size)*16);

		case M_GLUE3		:return(pieces+(size*size)*17);
		case M_GLUE5		:return(pieces+(size*size)*18);
		case M_PASS_VERT	:return(pieces+(size*size)*19);
		case M_PASS_HORI	:return(pieces+(size*size)*20);
		case M_TELEP_0		:return(pieces+(size*size)*21);
		case M_TELEP_1		:return(pieces+(size*size)*22);
		case M_CYKLECOL		:return(pieces+(size*size)*23);
		case M_CYKLEDIR_CW	:return(pieces+(size*size)*24);
		case M_CYKLEDIR_CCW	:return(pieces+(size*size)*25);
		case M_GRAY			:return(pieces+(size*size)*26);
		case M_DEATH		:return(pieces+(size*size)*27);
		case M_BLACK		:return(pieces+(size*size)*28);
		case M_YELLOW		:return(pieces+(size*size)*29);
		case M_RED			:return(pieces+(size*size)*30);
		case M_GREEN		:return(pieces+(size*size)*31);
		case M_BLUE			:return(pieces+(size*size)*32);
		
		case S_GLUE0		:return(pieces+(size*size)*33);
		case M_GLUE0		:return(pieces+(size*size)*34);
		
		default				:return(pieces);
	}
