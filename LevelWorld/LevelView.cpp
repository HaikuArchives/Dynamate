/*
	
	LevelView.cpp
	
	Copyright 1995 Be Incorporated, All Rights Reserved.
	
*/

//#include <Directory.h>
#include <Entry.h>
#include <File.h>
#include <Messenger.h>
#include <Path.h>

#ifndef LEVELVIEW_H
#include "LevelView.h"
#endif

#include "../DynaMate/headers/pieces16.h"
#include "../DynaMate/headers/pieces24.h"

enum
{
	SAVE = 'save',
	LOAD = 'load',
	SAVE_AS = 'svas'
};

uint8  p[48]={
	S_GRAY,                 S_RED,          S_GREEN,                S_BLUE,
	S_BLACK,                S_YELLOW,       S_GLUE3,                S_GLUE5,
	S_PASS_VERT,            S_PASS_HORI,    S_TELEP_0,              S_TELEP_1,
	S_CYKLECOL,             S_CYKLEDIR_CW,  S_CYKLEDIR_CCW,         S_DEATH,

	M_GRAY,                 M_RED,          M_GREEN,                M_BLUE,
	M_BLACK,                M_YELLOW,       M_GLUE3,                M_GLUE5,
	M_PASS_VERT,            M_PASS_HORI,    M_TELEP_0,              M_TELEP_1,
	M_CYKLECOL,             M_CYKLEDIR_CW,  M_CYKLEDIR_CCW,         M_DEATH,

	S_GLUE0,                M_GLUE0,        S_EMPTY,                S_EMPTY,
	S_EMPTY,                S_EMPTY,        S_EMPTY,                S_EMPTY,
	S_EMPTY,                S_EMPTY,        S_EMPTY,                S_EMPTY,
	S_EMPTY,                S_EMPTY,        S_EMPTY,                S_EMPTY };


LevelView::LevelView(char *name)
	:
	BView(name, B_WILL_DRAW),
	entry(new BEntry("default",true)),
	gfx(NULL),
	piece(0),
	bitmap(new BBitmap(BRect(0,0,255,255),B_COLOR_8_BIT)),
	pbitmap(new BBitmap(BRect(0,0,255,47),B_COLOR_8_BIT)),
	size(16)
{
	buffer=(uint8 *)bitmap->Bits();
	pbuffer=(uint8 *)pbitmap->Bits();

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
	
	fOpenPanel = new BFilePanel(B_OPEN_PANEL, NULL, NULL, 0, false);
	fSavePanel = new BFilePanel(B_SAVE_PANEL, NULL, NULL, 0, false);
}


void LevelView::DrawAll()
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


uint8 *LevelView::const2point(uint8 piece)
{
#include "../DynaMate/headers/const2point.h"
}

		
void LevelView::load256(BEntry *entry, uint32 filesize, uint8 *buff)
{
	BFile	*file;

	file=new BFile(entry,(ulong) B_READ_ONLY);
	if (file->InitCheck()==B_NO_ERROR)
	{
		file->Read(buff, filesize);
		
		bitmap->SetBits(buff, sizeof(buff), 0, B_RGB32);
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


void LevelView::savelev(BEntry *entry)
{
	BFile	*file;
	file=new BFile(entry,(ulong) B_WRITE_ONLY+B_CREATE_FILE);
	if (file->InitCheck()==B_NO_ERROR)
	{
		file->Write(level, 256);
	}
	delete	file;
}


void LevelView::MouseDown(BPoint cursor)
{
	uint32	buttons=0;
	bool	checkMessageQueue;

	int oldx;
	int	oldy;

	int x1;
	int y1;

	int	x=(int)cursor.x/16;
	int	y=(int)cursor.y/16;

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
			} else if (y<19) {
				// We are over the palette, change the selected object type
				piece=p[(y-16)*16 +x];
				Draw(BRect(0,256,256,256+64));
			}
		}

		snooze(30 * 1000); 
		GetMouse(&cursor, &buttons,checkMessageQueue = true); 

		oldx=x;
		oldy=y;

		x=(int)cursor.x/16;
		y=(int)cursor.y/16;

	} while ( buttons ); 


}

void LevelView::update(int x,int y)
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

void LevelView::MessageReceived(BMessage *message)
{
	switch ( message->what )
	{
		case B_SIMPLE_DATA:
		case B_REFS_RECEIVED:
		{
			entry_ref ref;
			if( message->FindRef("refs", &ref) == B_OK )
			{
				if (entry) delete entry;
				entry=new BEntry(&ref,true);
				load256(entry,256,level);
				DrawAll();
				Draw(BRect(0,0,255,255));
			}
			
			break;
		}
		case SAVE:
		{
			savelev(entry);
			break;
		}
		case LOAD:
		{
			fOpenPanel->SetTarget(this);
			fOpenPanel->Show();
			break;
		}
		case SAVE_AS:
		{
			fSavePanel->SetTarget(this);
			fSavePanel->Show();
			break;
		}
		case B_SAVE_REQUESTED:
		{
			entry_ref dir;
			BString name;
			if (message->FindRef("directory", &dir) == B_OK &&
				message->FindString("name", &name) == B_OK)
			{
				BPath path(&dir);
				path.Append(name);
				BEntry my_entry(path.Path());
				savelev(&my_entry);
			}
		}
		default:
		{
			BView::MessageReceived(message);
			break;
		}
	}
}

void LevelView::Draw(BRect)
{
	// Draw the level
	DrawBitmap(bitmap,BPoint(0,0));

	// Draw the "toolbar" at the bottom
	DrawBitmap(pbitmap,BPoint(0,256));
}


LevelView::~LevelView()
{
	delete	bitmap;
	delete	pbitmap;
	
	delete fOpenPanel;
	delete fSavePanel;
}
