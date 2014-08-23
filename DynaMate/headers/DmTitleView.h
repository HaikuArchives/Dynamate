#ifndef HELLO_TITLE_H
#define HELLO_TITLE_H

class DmTitleView: public BView
{
private:
	BBitmap	*bitmap;
	int stonesleft;
	int totalmoves;
	uint8 record;
	
	char	*stones;
	char	*moves;
	char	*rec;
public:
	DmTitleView(BRect frame, char *name,BBitmap *bitmappoint,uint16 totalmovespoint,uint16 stonesleftpoint, uint8 recordpoint);  

virtual void Draw(BRect rect);
};

#endif