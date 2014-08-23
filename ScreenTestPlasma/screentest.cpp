#include <Application.h>
#include <stdio.h>
#include "screenwin.h"

class screenapp: public BApplication
{
private:
	status_t	error;
public:
	screenapp();
};


screenapp::screenapp():BApplication("application/x-vnd.screentest")
{
	screenwin	*myscreen;
	printf("screen to be created\n");
	myscreen = new screenwin("PLASMA",B_8_BIT_640x480,&error,false);
	if ( error != B_OK ){
		printf("no screen\n");
		be_app->PostMessage(B_QUIT_REQUESTED);
	}else{
		printf("screen created\n");
	}
	myscreen->Show();
};

main()
{
	screenapp	*myapp;
	printf("app to be created\n");
	myapp = new screenapp(); 
	myapp->Run();
	delete (myapp);
	return(0);	
};
