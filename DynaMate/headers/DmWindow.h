#ifndef DM_WINDOW_H
#define DM_WINDOW_H

#include <Window.h>
#include "DmView.h"
#include "DmTitleView.h"
#include "DmGlobals.h"


class HelloWindow : public BWindow {
private:

SoundStuff *snd;

HelloView	*gameView;
DmTitleView	*titleView;

int	totalmoves;
int	stonesleft;

uint8 SIZE;
BFile	*file;

status_t error;

BRect	frame;
uint8	*level;		// Banan. (ej frukten)
		void 	saverec(uint8 *buff);
		void	load256(entry_ref *ref,uint32 filesize, uint8 *buff);
		void	LaunchGame();
		void	KillGame();
		void	LaunchTitle();
		void	KillTitle();

public:
				HelloWindow(BRect frame); 
				~HelloWindow();

		void	Zoom(BPoint punkt, float w, float h);
virtual	void	MessageReceived(BMessage *message);
virtual	bool	QuitRequested();
		status_t	InitCheck();
};

#endif
