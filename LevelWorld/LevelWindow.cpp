/*
	
	HelloWindow.cpp
	
	Copyright 1995 Be Incorporated, All Rights Reserved.
	
*/

#ifndef _APPLICATION_H
#include <Application.h>
#endif

#ifndef HELLO_WINDOW_H
#include "LevelWindow.h"
#endif

void set_palette_entry(long i,rgb_color c);

HelloWindow::HelloWindow(BRect frame)
				: BWindow(frame, "LevelWorld",  B_TITLED_WINDOW, B_NOT_ZOOMABLE+B_NOT_RESIZABLE)
{
}

bool HelloWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return(TRUE);
}
