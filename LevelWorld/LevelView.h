/*
	
	LevelView.h
	
	Copyright 1995 Be Incorporated, All Rights Reserved.
	
*/

#ifndef HELLO_VIEW_H
#define HELLO_VIEW_H

	#ifndef _VIEW_H
	#include <View.h>
	#endif

#include "../DynaMate/headers/DmView.h"

	class LevelView : public BView 
	{
	private:
		BEntry	*entry;
		uint8	*gfx;
		uint8	piece;			// Den piecen man ritar med.

		BBitmap	*bitmap;		// Bilden på skärmen.
		uint8	*buffer;
		
		BBitmap	*pbitmap;		// Bilden på skärmen.
		uint8	*pbuffer;
	
		uint8	size;
		uint8	level[256];		// Banan. (ej frukten)

		void	load256(BEntry *entry,uint32 filesize,uint8 *buff);
		void	savelev(BEntry *entry);
		uint8	*const2point(uint8 piece);
		void	update(int x,int y);		
		void	DrawAll();			
		void	MessageReceived(BMessage *message);

	public:
					LevelView(BRect frame, char *name); 
					~LevelView();
	virtual void	Draw(BRect updateRect);
	virtual void	MouseDown(BPoint); 
	};
#endif
