/*
	
	HelloWorld.cpp
	
	Copyright 1995 Be Incorporated, All Rights Reserved.
	
*/

#ifndef HELLO_WINDOW_H
#include "headers/DmWindow.h"
#endif

#ifndef HELLO_WORLD_H
#include "headers/DmWorld.h"
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
		  		  : BApplication("application/x-vnd.Jonas-DnMt")
{
	BRect			aRect;

	// set up a rectangle and instantiate a new window
	aRect.Set(50,50,50+(16*SIZE-1),50+(16*SIZE-1));
	aWindow = new HelloWindow(aRect);


	// make window visible
	aWindow->Show();
}

void HelloApplication::RefsReceived(BMessage *message) 
{
	message->what=B_SIMPLE_DATA;
	
   	aWindow->PostMessage( message );
}