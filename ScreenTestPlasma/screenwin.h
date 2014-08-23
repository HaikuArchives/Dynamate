#ifndef SCRNWIN
#define SCRNWIN

#include <WindowScreen.h>
#include <OS.h>
// Global
long  plasma(void *data);

class screenwin: public BWindowScreen
{
private:
	status_t	error;
	rgb_color	table[256];	//color

	uint8	*base;
	thread_id	plasma_thread;
	
virtual	void ScreenConnected(bool connected);

public:
	screenwin(const char *title, uint32 space, status_t *error,bool debugging);
};

#endif
