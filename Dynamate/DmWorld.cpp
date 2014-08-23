/*
	
	HelloWorld.cpp
	
	Copyright 1995 Be Incorporated, All Rights Reserved.
	
*/

#ifndef HELLO_WINDOW_H
#include "DmWindow.h"
#endif

#ifndef HELLO_WORLD_H
#include "DmWorld.h"
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
		  		  : BApplication("application/x-vnd.Jonas-DynaMate")
{
	HelloWindow		*aWindow;
	BRect			aRect;

	// set up a rectangle and instantiate a new window
	aRect.Set(50,50,50+255,50+255);
	aWindow = new HelloWindow(aRect);


	// make window visible
	aWindow->Show();
}
