/*
	
	HelloWindow.h
	
	Copyright 1995 Be Incorporated, All Rights Reserved.
	
*/

#ifndef HELLO_WINDOW_H
#define HELLO_WINDOW_H

#ifndef HELLO_VIEW_H
#include "DmView.h"
#endif

#ifndef HELLO_TITLEVIEW_H
#include "DmTitleView.h"
#endif

#include <Window.h>

class HelloWindow : public BWindow {
private:

HelloView	*gameView;
DmTitleView	*titleView;

uint16	totalmoves;
uint16	stonesleft;

BEntry	*entry;

BRect	frame;
BBitmap	*bitmap;
uint8	*level;		// Banan. (ej frukten)
		void 	save256(BEntry *entry,uint32 filesize, uint8 *buff);
		void	load256(BEntry *entry,uint32 filesize, uint8 *buff);
		void	LaunchGame();
		void	KillGame();
		void	LaunchTitle();
		void	KillTitle();
public:
				HelloWindow(BRect frame); 

virtual void	MessageReceived(BMessage *message);
virtual	bool	QuitRequested();
};

#endif
