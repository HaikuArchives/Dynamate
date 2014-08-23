/*
	
	HelloWorld.cpp
	
	Copyright 1995 Be Incorporated, All Rights Reserved.
	
*/

#ifndef HELLO_WINDOW_H
#include "EditWindow.h"
#endif
#ifndef HELLO_VIEW_H
#include "EditView.h"
#endif
#ifndef HELLO_WORLD_H
#include "EditWorld.h"
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
		  		  : BApplication('HLWD')
{
	HelloWindow		*aWindow;
	HelloView		*aView;
	BRect			aRect;

	// set up a rectangle and instantiate a new window
	aRect.Set(50,50,50+208,50+384);
	aWindow = new HelloWindow(aRect);
	
	// set up a rectangle and instantiate a new view
	// view rect should be same size as window rect but with left top at (0, 0)
	aRect.OffsetTo(B_ORIGIN);
	aView = new HelloView(aRect, "View");
	
	// add view to window
	aWindow->AddChild(aView);
	
	// make window visible
	aWindow->Show();
}
