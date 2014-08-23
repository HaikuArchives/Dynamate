#ifndef HELLO_TITLE_H
#define HELLO_TITLE_H

#include <Bitmap.h>
#include <InterfaceKit.h>
#include <Rect.h>

class DmTitleView: public BView
{
private:
	BBitmap	*bitmap;
	int stonesleft;
	int totalmoves;
	uint8 record;
	
	uint8	size;

	char	stones[12];
	char	moves[12];
	char	rec[12];
public:
	DmTitleView(BRect frame, uint16 totalmovespoint,uint16 stonesleftpoint, uint8 recordpoint);  

	void MouseDown(BPoint cursor);
	void Draw(BRect rect);
};

#endif