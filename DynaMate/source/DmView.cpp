/*
	
	HelloView.cpp
	
	Copyright 1995 Be Incorporated, All Rights Reserved.
	
*/

//#include <Directory.h>


#ifndef HELLO_VIEW_H
#include "headers/DmView.h"
#endif
#ifndef HELLO_WINDOW_H
#include "headers/DmWindow.h"
#endif



HelloView::HelloView(BRect rect, char *name, uint8 *levelpoint, HelloWindow *windowpoint)
	   	   :BView(rect, name, B_FOLLOW_ALL, B_WILL_DRAW)
{
	
// Allokera minne
	bitmap=new BBitmap(BRect(0,0,(16*SIZE-1),(16*SIZE-1)),B_COLOR_8_BIT);
	buffer=(uint8 *)bitmap->Bits();

// Nollställ
	totalmoves=0;
	stonesleft=0;
	gluesleft=0;
	
	window=windowpoint;
	level=levelpoint;

// (räkna stones)
	int x;
	int y;
	for (y=0;y<16;y++)
	{
		for (x=0;x<16;x++)
		{
			if ((level[y*16+x]& S_BLACK)==S_BLACK)
				stonesleft++;
		}
	}
	

// Rita upp banan med grafik on the bitmap. 
	
	for (y=0;y<16;y++)
	{
		for (x=0;x<16;x++)
		{
			update(x,y);
		}
	}
}

uint8 *HelloView::const2point(uint8 piece)
{
#include "const2point.h"
}
		
void HelloView::get_next(pstruct *piece)
{
	int x;
	int y;

	int sx=piece->x;
	int sy=piece->y;
	int st=piece->type;
				
	piece->x=piece->x+piece->dirx;
	piece->y=piece->y+piece->diry;
	
	// koll om utanför
	if (piece->x>=0 & piece->x<16 & piece->y>=0 & 	piece->y<16 )
		piece->type=level[piece->y*16+piece->x];
	else
		piece->type=S_DEATH;

	if (totalmoves>250)	piece->type=S_DEATH;

		
	// tester här, and 127 för att s eller m spelar ingen roll.	

	switch (piece->type & 127)
	{
		case	S_EMPTY		:	piece->state=dmOK; 
								break;

		case	S_PASS_HORI	:	if (sy!=piece->y){
									piece->state=dmSTOPPED;
								} break;

		case	S_PASS_VERT	:	if (sx!=piece->x){
									piece->state=dmSTOPPED;
								} break;
								
		case	S_CYKLECOL	:	if ((st & 0xf8 )== 0xf8)//rätt grupp?
								{
									st++;
									if (st >0xf8+2){st=0xf8;}
								} break;

		case	S_RED		:	if ((st == M_BLACK)||(st==M_BLUE)) {		//endast svart och blå
									piece->state=dmEXPL;
								}else{
									piece->state=dmSTOPPED;
								}break;
		case	S_GREEN		:	if ((st == M_BLACK)||(st==M_RED)) {		//endast svart och röd
									piece->state=dmEXPL;
								}else{
									piece->state=dmSTOPPED;
								}break;

		case	S_BLUE		:	if ((st == M_BLACK)||(st==M_GREEN)) {		//endast svart och grön
									piece->state=dmEXPL;
								}else{
									piece->state=dmSTOPPED;
								}break;

		case	S_BLACK		:	if (st == M_BLACK) {		//endast svart
									piece->state=dmEXPL;
								}else{
									piece->state=dmSTOPPED;
								}break;

		case	S_YELLOW	:	if (((st & 0xf0 )== 0xf0)&& st!=M_YELLOW){// alla stenar utom gul
									piece->state=dmEXPL;
								}else{
									piece->state=dmSTOPPED;
								}break;

		case	S_CYKLEDIR_CW	:	switch (piece->dirx)
								{
									case 1	:	{piece->dirx=0;		piece->diry=1;}	break;
									case -1	:	{piece->dirx=0;		piece->diry=-1;}		break;
									default	:	
										switch (piece->diry)
										{
											case 1	:	{piece->dirx=-1;		piece->diry=0;}	break;
											default	:	{piece->dirx=1;	piece->diry=0;}		break;
										}
								}
								break;

		case	S_CYKLEDIR_CCW	:	switch (piece->dirx)
								{
									case 1	:	{piece->dirx=0;		piece->diry=-1;}	break;
									case -1	:	{piece->dirx=0;		piece->diry=1;}		break;
									default	:	
										switch (piece->diry)
										{
											case 1	:	{piece->dirx=1;		piece->diry=0;}	break;
											default	:	{piece->dirx=-1;	piece->diry=0;}		break;
										}
								}
								break;
																
		case	S_TELEP_0	:	if ((st & 127)!=S_TELEP_0){
									for (y=0;y<16;y++){
										for (x=0;x<16;x++){
											if (((level[y*16+x] & 127)==S_TELEP_0) && ( (x!=piece->x) || (y!=piece->y) )){
												piece->x=x;
												piece->y=y;
												x=16;	//fult sätt att hoppa ut ur loopen
												y=16;
											}
										}
									}
								}
								break;
								
		case	S_TELEP_1	:	if ((st & 127)!=S_TELEP_1){
									for (y=0;y<16;y++){
										for (x=0;x<16;x++){
											if (((level[y*16+x] & 127)==S_TELEP_1) && ((x!=piece->x) || (y!=piece->y))){
												piece->x=x;
												piece->y=y;
												x=16;	//fult sätt att hoppa ut ur loopen
												y=16;
											}
										}
									}
								}
								break;

		case	S_DEATH		:	piece->state=dmDEATH;
								break;
									
		case	S_GLUE0		:	gluesleft=1;
								explode(piece->x,piece->y,false);
								break;

		case	S_GLUE3		:	gluesleft=3+1;
								explode(piece->x,piece->y,false);
								break;

		case	S_GLUE5		:	gluesleft=5+1;
								explode(piece->x,piece->y,false);
								break;
								
		default 			:	piece->state=dmSTOPPED; 
 	}
 	piece->type=st;
}
		
//	GO!     x,y,dirx,diry SKA vara ifyllda.
		
void HelloView::go(pstruct piece) 
{
	totalmoves++;
	//printf("%x%x%x\n",piece.x,piece.y,(piece.dirx+1)+((piece.diry+1)<<2));
		
	piece.state=dmSEARCHING;
	piece.type=level[piece.y*16+piece.x];
	
	pstruct old;
	while (piece.state!=dmSTOPPED && piece.state!=dmEXPL)
	{
		old=piece;
		do{
			piece.state=dmSEARCHING;
			get_next(&piece);
		}while (piece.state==dmSEARCHING);

		switch (piece.state)
		{
			case dmOK	:	level[old.y*16+old.x]=piece.type;
							move(old.x,old.y, piece.x, piece.y);
							if (gluesleft)
							{
								gluesleft--;
								piece.state=dmSTOPPED;
							}
							break;
							
			case dmDEATH:	window->PostMessage(LEVELABANDONED);
							piece.state=dmSTOPPED;
							break;

			case dmEXPL	:	explode(old.x,old.y,true);
							explode(piece.x, piece.y,true);

							while (piece.state==dmEXPL)
							{
								old=piece;
								do{
									piece.state=dmSEARCHING;
									get_next(&piece);
								}while (piece.state==dmSEARCHING);
						
							if 	(piece.state==dmEXPL)
								{
								explode(piece.x,piece.y,true);
								}
							}
							piece.state=dmSTOPPED;

							if (!stonesleft){
								window->PostMessage(LEVELCOMPLETE);
								}
							break;
		}
	}	
}

void HelloView::explode(int x, int y, bool stone)
{
	level[y*16+x]=S_EMPTY;
	if (stone) stonesleft--;
	update(x,y);
	Draw(BRect(x*SIZE,y*SIZE,(x+1)*SIZE-1,(y+1)*SIZE-1));
}		

void HelloView::update(int x,int y)
{
	int x1;
	int y1;
	uint8	*gfx;	
	
	gfx=const2point(level[y*16+x]);
	
	for (y1=0;y1<SIZE;y1++)
	{
		for (x1=0;x1<SIZE;x1++)
		{
			buffer[y*16*(SIZE*SIZE)+x*SIZE+y1*(16*SIZE)+x1]=gfx[y1*SIZE+x1];
		}
	}

}		

void HelloView::move(int x,int y,int x1,int y1)
{
	level[y1*16+x1]=level[y*16+x];	
	level[y*16+x]=S_EMPTY;
	update(x,y);
	update(x1,y1);
	snooze(30 * 1000);
	Draw(BRect(x*SIZE,y*SIZE,(x+1)*SIZE-1,(y+1)*SIZE-1) | BRect(x1*SIZE,y1*SIZE,(x1+1)*SIZE-1,(y1+1)*SIZE-1));
}



//	! M O U S E D O W N !
void HelloView::MouseDown(BPoint cursor)
{
	uint32	buttons=0;
	bool	checkMessageQueue;

	pstruct piece;
	
	int oldx;
	int	oldy;
	
	int	x=cursor.x/SIZE;
	int	y=cursor.y/SIZE;
		
	do 
	{  
		oldx=x;
		oldy=y;

		x=cursor.x/SIZE;
		y=cursor.y/SIZE;
		
		if (oldx!=x || oldy!=y)
		{	
			piece.x=oldx;	piece.y=oldy;

// Set direction
			if (x>oldx)
			{ piece.dirx=1; piece.diry=0;}
			if (x<oldx)
			{ piece.dirx=-1; piece.diry=0;}
			if (y>oldy)
			{ piece.dirx=0; piece.diry=1;}
			if (y<oldy)
			{ piece.dirx=0; piece.diry=-1;}
			
			if (level[piece.y*16+piece.x] & 128) go(piece);
		}
		
		snooze(30 * 1000); 
		GetMouse(&cursor, &buttons,checkMessageQueue = true); 

	} while ( buttons && (oldx==x) && (oldy==y)); 
}


void HelloView::Draw(BRect rect)
{
	DrawBitmap(bitmap,rect,rect);
}

HelloView::~HelloView()
{
	delete	bitmap;
}
