/*
	
	HelloView.cpp
	
	Copyright 1995 Be Incorporated, All Rights Reserved.
	
*/

//#include <Directory.h>

#ifndef HELLO_VIEW_H
#include "LevelView.h"
#endif


HelloView::HelloView(BRect rect, char *name)
	   	   :BView(rect, name, B_FOLLOW_ALL, B_WILL_DRAW)
{

	piece=0;
	
	bitmap=new BBitmap(BRect(0,0,255,255),B_COLOR_8_BIT);
	buffer=(uint8 *)bitmap->Bits();

	pbitmap=new BBitmap(BRect(0,0,255,47),B_COLOR_8_BIT);
	pbuffer=(uint8 *)pbitmap->Bits();

	entry = new BEntry("default",true);
	
// Rita upp banan med grafik on the bitmap. 
	int x;
	int y;
	int x1;
	int y1;

	DrawAll();

// Rita upp de bitar man får välja mellan.
				
	for (y1=0;y1<3;y1++)
	{
		for (x1=0;x1<16;x1++)
		{
			gfx=const2point(p[y1*16+x1]);
			for (y=0;y<16;y++)
			{
				for (x=0;x<16;x++)
				{
					pbuffer[y1*16*256+x1*16+y*256+x]=gfx[y*16+x];
				}
			}
		}
	}

}


void HelloView::DrawAll()
{
	int x;
	int y;
	for (y=0;y<16;y++)
	{
		for (x=0;x<16;x++)
		{
			update(x,y);
		}
	}
}


uint8 *HelloView::const2point(uint8 piece)
{
#include "const2point.h"
}

		
void HelloView::load256(BEntry *entry, uint32 filesize, uint8 *buff)
{
	BFile	*file;

	file=new BFile(entry,(ulong) B_READ_ONLY);
	if (file->InitCheck()==B_NO_ERROR)
	{
		file->Read(buff, filesize);
	}
	else
	{
		// finns ej filen fyller vi minnet med 0:or
		int count;
		for (count=0;count<filesize;count++)
		{
			buff[count]=0;			
		}
	}

	delete	file;
}


void HelloView::savelev(BEntry *entry)
{
	BFile	*file;
	file=new BFile(entry,(ulong) B_WRITE_ONLY+B_CREATE_FILE);
	if (file->InitCheck()==B_NO_ERROR)
	{
		file->Write(level, 256);
	}
	delete	file;
}


void HelloView::MouseDown(BPoint cursor)
{
	uint32	buttons=0;
	bool	checkMessageQueue;

	int oldx;
	int	oldy;
	
	int x1;
	int y1;
	
	int	x=cursor.x/16;
	int	y=cursor.y/16;
		
	do 
	{  
		if (oldx!=x || oldy!=y)
		{
			if (y<16)
			{ 
				// man har flyttat sig, skall sätta en ny pixel
				level[y*16+x]=piece;
				gfx=const2point(piece);
				for (y1=0;y1<16;y1++)
				{
					for (x1=0;x1<16;x1++)
					{
						buffer[y*16*256+x*16+y1*256+x1]=gfx[y1*16+x1];
					}
				}
				Draw(BRect(0,0,255,255));
			}else{
				if (y<19){//	Man är över paletten (och har flyttat sig)
					piece=p[(y-16)*16 +x];
					Draw(BRect(0,256,256,256+64));
				}else{
					savelev(entry);
				}
			}	

		}
		
		snooze(30 * 1000); 
		GetMouse(&cursor, &buttons,checkMessageQueue = true); 

		oldx=x;
		oldy=y;

		x=cursor.x/16;
		y=cursor.y/16;

	} while ( buttons ); 


}

void HelloView::update(int x,int y)
{
	int x1;
	int y1;
	uint8	*gfx;	
	
	gfx=const2point(level[y*16+x]);
	
	for (y1=0;y1<16;y1++)
	{
		for (x1=0;x1<16;x1++)
		{
			buffer[y*16*256+x*16+y1*256+x1]=gfx[y1*16+x1];
		}
	}

}		

void HelloView::MessageReceived(BMessage *message)
{ 
	switch ( message->what )
	{			
		case	B_SIMPLE_DATA	:	{
									entry_ref ref;
									if( message->FindRef("refs", &ref) == B_OK )
										{
										if (entry) delete entry;
										entry=new BEntry(&ref,true);
										load256(entry,256,level);
										DrawAll();
										Draw(BRect(0,0,255,255));										
										}
									}
									break;
									
		default	:	inherited::MessageReceived(message);
								break;
	}
}
   
void HelloView::Draw(BRect)
{
	DrawBitmap(bitmap,BPoint(0,0));
	DrawBitmap(pbitmap,BPoint(0,256));
	MovePenTo(115,251+4*16);
	DrawString("SAVE");
}


HelloView::~HelloView()
{
	delete	bitmap;
	delete	pbitmap;
}
