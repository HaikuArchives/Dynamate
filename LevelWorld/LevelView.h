/*
	
	HelloView.h
	
	Copyright 1995 Be Incorporated, All Rights Reserved.
	
*/

#ifndef HELLO_VIEW_H
#define HELLO_VIEW_H

	#ifndef _VIEW_H
	#include <View.h>
	#endif


#include "Const.h"  
#include "pieces.h"  

uint8	p[48]={	S_GRAY,			S_RED,			S_GREEN,		S_BLUE,
				S_BLACK,		S_YELLOW,		S_GLUE3,		S_GLUE5,
				S_PASS_VERT,	S_PASS_HORI,	S_TELEP_0,		S_TELEP_1,
				S_CYKLECOL,		S_CYKLEDIR_CW,	S_CYKLEDIR_CCW,	S_DEATH,
							
				M_GRAY,			M_RED,			M_GREEN,		M_BLUE,
				M_BLACK,		M_YELLOW,		M_GLUE3,		M_GLUE5,
				M_PASS_VERT,	M_PASS_HORI,	M_TELEP_0,		M_TELEP_1,
				M_CYKLECOL,		M_CYKLEDIR_CW,	M_CYKLEDIR_CCW,	M_DEATH,

				S_GLUE0,		M_GLUE0,		S_EMPTY,		S_EMPTY,
				S_EMPTY,		S_EMPTY,		S_EMPTY,		S_EMPTY,
				S_EMPTY,		S_EMPTY,		S_EMPTY,		S_EMPTY,
				S_EMPTY,		S_EMPTY,		S_EMPTY,		S_EMPTY	};
	
	class HelloView : public BView 
	{
	private:
		BEntry	*entry;
		uint8	*gfx;
		uint8	piece;			// Den piecen man ritar med.

		BBitmap	*bitmap;		// Bilden på skärmen.
		uint8	*buffer;
		
		BBitmap	*pbitmap;		// Bilden på skärmen.
		uint8	*pbuffer;
	
		uint8	level[256];		// Banan. (ej frukten)

		void	load256(BEntry *entry,uint32 filesize,uint8 *buff);
		void	savelev(BEntry *entry);
		uint8	*const2point(uint8 piece);
		void	update(int x,int y);		
		void	DrawAll();			
		void	MessageReceived(BMessage *message);

	public:
					HelloView(BRect frame, char *name); 
					~HelloView();
	virtual void	Draw(BRect updateRect);
	virtual void	MouseDown(BPoint); 
	};
#endif