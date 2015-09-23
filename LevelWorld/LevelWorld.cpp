/*
	
	HelloWorld.cpp
	
	Copyright 1995 Be Incorporated, All Rights Reserved.
	
*/

#ifndef HELLO_WINDOW_H
#include "LevelWindow.h"
#endif
#ifndef HELLO_VIEW_H
#include "LevelView.h"
#endif
#ifndef HELLO_WORLD_H
#include "LevelWorld.h"
#endif

main()
{	
	HelloApplication *myApplication;

	myApplication = new HelloApplication();
	myApplication->Run();
	
	delete(myApplication);
	return(0);
}

HelloApplication::HelloApplication()
		  		  : BApplication("application/x-vnd.Jonas-DynaMateLevEd")
{
	HelloWindow		*aWindow;
	LevelView		*aView;
	BRect			aRect;

	// set up a rectangle and instantiate a new window
	aRect.Set(50,50,50+255,50+255+64);
	aWindow = new HelloWindow(aRect);
	
	// set up a rectangle and instantiate a new view
	// view rect should be same size as window rect but with left top at (0, 0)
	aRect.OffsetTo(B_ORIGIN);
	aView = new LevelView(aRect, "View");
	
	// add view to window
	aWindow->AddChild(aView);
	
	// make window visible
	aWindow->Show();
}
