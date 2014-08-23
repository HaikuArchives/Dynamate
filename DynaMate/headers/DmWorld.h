/*
	
	HelloWorld.h
	
	Copyright 1995 Be Incorporated, All Rights Reserved.

*/

#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

#ifndef _APPLICATION_H
#include <Application.h>
#endif

#include "DmGlobals.h"

class HelloApplication : public BApplication {
private:
	HelloWindow		*aWindow;
public:
				HelloApplication();
virtual void 	RefsReceived( BMessage *message );
};

#endif
