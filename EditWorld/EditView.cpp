/*
	
	HelloView.cpp
	
	Copyright 1995 Be Incorporated, All Rights Reserved.
	
*/

#include <Directory.h>

#ifndef HELLO_VIEW_H
#include "EditView.h"
#endif

const pixize=12;

HelloView::HelloView(BRect rect, char *name)
	   	   : BView(rect, name, B_FOLLOW_ALL, B_WILL_DRAW)
{

	bitmap=new BBitmap(BRect(0,0,15,15),B_COLOR_8_BIT);
	buffer=(uint8 *)bitmap->Bits();
	load("projs/DynaMate/gfx/def.raw",buffer);

}

void HelloView::load(char *name,uint8 *buff)
{
	BEntry	*entry;
	BFile	*file;

	entry=new BEntry(name,true);
	file=new BFile(entry,(ulong) B_READ_ONLY);
	if (file->InitCheck()==B_NO_ERROR)
	{
		file->Read(buff, 256);
	}
	else
	{
		int count;
		for (count=0;count<256;count++)
		{
			buffer[count]=0;
		}
	}
	
	delete	file;
	delete	entry;
}

void HelloView::save(uint8 *buff)
{
	BEntry	*entry;
	BFile	*file;

	entry=new BEntry("projs/DynaMate/gfx/def.raw",true);
	file=new BFile(entry,(ulong) B_WRITE_ONLY+B_CREATE_FILE);
	if (file->InitCheck()==B_NO_ERROR)
	{
		file->Write(buff, 256);
	}

	delete	file;
	delete	entry;
}

void HelloView::MouseDown(BPoint cursor)
{
	uint32	buttons=0;
	bool	checkMessageQueue;

	int oldx;
	int	oldy;
	
	int	x=cursor.x/pixize;
	int	y=cursor.y/pixize;
		
	do 
	{  
		if (oldx!=x || oldy!=y)
		{
			if (x<16)
			{
				if (y<16)
				{ 
					// man har flyttat sig, skall sätta en ny pixel
					buffer[y*16+x]=colr;	
					Draw(BRect(x*pixize,y*pixize,(x+1)*pixize-1,(y+1)*pixize-1));
				}
				else
				{
					//	Man är över paletten (och har flyttat sig)
					colr=((y-16)*16 +x);
					Draw(BRect(0,16*pixize,16*pixize-1,32*pixize-1));
				}
			}
			else
			{
				if (y==0)
				{
					save(buffer);
				}
			}	
		}

		
		snooze(30 * 1000); 
		GetMouse(&cursor, &buttons,checkMessageQueue = true); 

		oldx=x;
		oldy=y;

		x=cursor.x/pixize;
		y=cursor.y/pixize;

	} while ( buttons ); 


}

void HelloView::Draw(BRect nisse)
{
	DrawBitmap(bitmap,BPoint(16*pixize,0));

	int y;
	int x;
	
	if ((nisse.right-nisse.left!=pixize-1) || (nisse.bottom-nisse.top!=pixize-1))
	{
		//	Draw magnified bitmap...
		for (y=0;y<16;y++)
			{
			for (x=0;x<16;x++)
			{		
				SetHighColor(system_colors()->color_list[buffer[y*16+x]]);
				FillRect(BRect(x*pixize,y*pixize,x*pixize+pixize-1,y*pixize+pixize-1),B_SOLID_HIGH);
			}
		}
		
		//	Draw palette (a bit lame...)
		if (nisse.bottom>16*pixize)
		{
			
			for (y=0;y<16;y++)
			{
				for (x=0;x<16;x++)
				{		
					SetHighColor(system_colors()->color_list[y*16+x]);
					
					FillRect(BRect(x*pixize,y*pixize+pixize*16,x*pixize+pixize-1,y*pixize+pixize-1+pixize*16),B_SOLID_HIGH);
					if (colr==(y*16+x))
					{
						SetLowColor(255,255,255);
						StrokeLine(BPoint(x*pixize,y*pixize+pixize*16),BPoint(x*pixize+pixize-1,y*pixize+pixize*17-1),B_SOLID_LOW);
						SetLowColor(0,0,0);
						StrokeLine(BPoint(x*pixize,y*pixize+pixize*17-1),BPoint(x*pixize+pixize-1,y*pixize+pixize*16),B_SOLID_LOW);
					}
				}
			}
		}
	}
	else
	{
		// rita bara rätt pixel.
		x=nisse.right/pixize;
		y=nisse.bottom/pixize;
		
		SetHighColor(system_colors()->color_list[buffer[y*16+x]]);
		FillRect(BRect(x*pixize,y*pixize,(x+1)*pixize-1,(y+1)*pixize-1),B_SOLID_HIGH);
	}
}


HelloView::~HelloView()
{
	delete	bitmap;
}
