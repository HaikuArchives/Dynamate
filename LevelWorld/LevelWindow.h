/*
	
	HelloWindow.h
	
	Copyright 1995 Be Incorporated, All Rights Reserved.
	
*/

#ifndef LEVELWINDOW_H
#define LEVELWINDOW_H

#ifndef _WINDOW_H
#include <Window.h>
#endif

class LevelWindow : public BWindow {

public:
				LevelWindow(BRect frame); 
virtual	bool	QuitRequested();
};

#endif
