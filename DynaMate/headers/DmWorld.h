#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

#ifndef _APPLICATION_H
#include <Application.h>
#endif

class HelloApplication : public BApplication {
private:
	status_t error;
	HelloWindow		*aWindow;
public:
	status_t	InitCheck();
				HelloApplication();
virtual void 	RefsReceived( BMessage *message );
};

#endif
