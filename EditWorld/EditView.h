/*
	
	HelloView.h
	
	Copyright 1995 Be Incorporated, All Rights Reserved.
	
*/

#ifndef HELLO_VIEW_H
#define HELLO_VIEW_H

#ifndef _VIEW_H
#include <View.h>
#endif

class HelloView : public BView {
private:
	int		colr;
	BBitmap	*bitmap;
	uint8	*buffer;
	void	load(char *name,uint8 *buff);
	void	save(uint8 *buff);	
public:
				HelloView(BRect frame, char *name); 
				~HelloView();
virtual void	Draw(BRect updateRect);
virtual void	MouseDown(BPoint); };

#endif