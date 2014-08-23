#include "DmWindow.h"
#include "DmWorld.h"

#include <stdio.h>

main()
{	
	HelloApplication *myApplication;

	myApplication = new HelloApplication();
	if (myApplication->InitCheck()==B_OK){
		myApplication->Run();
	}
	delete(myApplication);
	return(0);
}

status_t HelloApplication::InitCheck()
{
	return error;
}

HelloApplication::HelloApplication()
		  		  : BApplication("application/x-vnd.Jonas-DynaMate")
{
	BRect			aRect;

	// set up a rectangle and instantiate a new window
	aRect.Set(50,50,50+(16*16-1),50+(16*16-1));
	aWindow = new HelloWindow(aRect);

	if (B_OK == (error = aWindow->InitCheck()))	aWindow->Show();
}

void HelloApplication::RefsReceived(BMessage *message) 
{
	message->what=B_SIMPLE_DATA;
	
   	aWindow->PostMessage( message );
}