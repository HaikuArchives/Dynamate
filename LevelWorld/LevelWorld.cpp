/*
	
	HelloWorld.cpp
	
	Copyright 1995 Be Incorporated, All Rights Reserved.
	
*/

#ifndef LEVELWINDOW_H
#include "LevelWindow.h"
#endif
#ifndef LEVELVIEW_H
#include "LevelView.h"
#endif
#ifndef LEVELWORLD_H
#include "LevelWorld.h"
#endif

main()
{	
	LevelApplication *myApplication;

	myApplication = new LevelApplication();
	myApplication->Run();
	
	delete(myApplication);
	return(0);
}

LevelApplication::LevelApplication()
	: BApplication("application/x-vnd.Jonas-DynaMateLevEd")
{
	LevelWindow		*aWindow;
	LevelView		*aView;
	BRect			aRect;

	// set up a rectangle and instantiate a new window
	aRect.Set(50,50,50+255,50+255+64);
	aWindow = new LevelWindow(aRect);
	
	// set up a rectangle and instantiate a new view
	// view rect should be same size as window rect but with left top at (0, 0)
	aRect.OffsetTo(B_ORIGIN);
	
	// make window visible
	aWindow->Show();
}
