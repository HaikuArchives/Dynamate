/*
	
	HelloWindow.cpp
	
	Copyright 1995 Be Incorporated, All Rights Reserved.
	
*/

#ifndef HELLO_APPLICATION_H
#include <Application.h>
#endif

#ifndef HELLO_WINDOW_H
#include "DmWindow.h"
#endif

void set_palette_entry(long i,rgb_color c);

HelloWindow::HelloWindow(BRect theframe)
				: BWindow(theframe, "DynaMate",  B_TITLED_WINDOW, B_NOT_RESIZABLE)
{
	frame=theframe;
	totalmoves=0;
	stonesleft=65535;
		
	bitmap=new BBitmap(BRect(0,0,255,59),B_COLOR_8_BIT);
	bitmap->SetBits(title, 256*60, 0, B_COLOR_8_BIT);
/*	BEntry *entry = new BEntry("gfx/title.raw",true);
	load256(entry,60*256,(uint8 *)bitmap->Bits());
	delete entry;
	
uint8 *gfx=(uint8 *)bitmap->Bits();

int x1;
int x2;
for (x1=0;x1<60*16;x1++){
	for(x2=0;x2<16;x2++)
	printf("%d,",gfx[x1*16+x2]);
	
	printf("\n");
	};
*/


// reservera banan
	level=(uint8 *)malloc(256+1);		// 256==en piece 1==rekordet
	entry=NULL;
	
	
// Starta en view	
	frame.OffsetTo(B_ORIGIN);

	LaunchTitle();
}




void HelloWindow::LaunchTitle()
{
	titleView = new DmTitleView(frame, "View",bitmap,totalmoves,stonesleft,level[256]);
	AddChild((BView*)titleView);
}

void HelloWindow::KillTitle()
{
	if (titleView){
		RemoveChild(titleView);
		delete titleView;
		titleView=NULL;
	}
}

void HelloWindow::LaunchGame()
{
	gameView = new HelloView(BRect(0,0,16*SIZE-1,16*SIZE-1), "View",level,this);
	AddChild((BView*)gameView);
}

void HelloWindow::KillGame()
{
	if (gameView){
		totalmoves=gameView->totalmoves;
		stonesleft=gameView->stonesleft;
		RemoveChild(gameView);
		delete gameView;
		gameView=NULL;
	}
}

void HelloWindow::save256(BEntry *entry, uint32 filesize, uint8 *buff)
{
	BFile	*file;
	file=new BFile(entry,(ulong) B_WRITE_ONLY+B_CREATE_FILE);
	if (file->InitCheck()==B_NO_ERROR)
	{
		file->Write(buff, filesize);
	}
	delete	file;
}

void HelloWindow::load256(BEntry *entry, uint32 filesize, uint8 *buff)
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
			buff[count]=255;			
		}
	}

	delete	file;
}

void HelloWindow::MessageReceived(BMessage *message)
{ 
	char *filename="this string is supposed to be very long";
	//printf("recieved:%d\n",message);
	switch ( message->what )
	{			
		case	B_SIMPLE_DATA	:	{
									entry_ref ref;
									if( message->FindRef("refs", &ref) == B_OK )
										{	
										if (entry) delete entry;
										strcpy (filename,"DynaMate - ");
										strcpy ((char *)filename+11,ref.name);
										SetTitle(filename);

										entry=new BEntry(&ref,true);
										level[256]=255;
										load256(entry,257,level);
										KillGame();
										KillTitle();
										LaunchGame();
										}
									}
									break;
		case	LEVELCOMPLETE	:	{
									KillGame();
									uint16 temp=level[256]; //gamla rekordet
									if (totalmoves<level[256]){
										level[256]=totalmoves;
										load256(entry,256,(uint8 *)level);
										save256(entry,257,(uint8 *)level);
										level[256]=temp;
										}
									LaunchTitle();	
									}
									break;
								
		case	LEVELABANDONED	:	{
									KillGame();
									LaunchTitle();
									}
									break;
									
		default	:	inherited::MessageReceived(message);
								break;
	}
}
   
void HelloWindow::Zoom(BPoint punkt, float w, float h)
{
	KillGame();

	if (SIZE==24){
		SIZE=16;
		ResizeTo(255,255);
	}else{
		ResizeTo(24*16-1,24*16-1);
		SIZE=24;
	}
	
	LaunchGame();		
}

bool HelloWindow::QuitRequested()
{
	KillGame(); 
	KillTitle(); 
	delete entry;
	be_app->PostMessage(B_QUIT_REQUESTED);
	return(TRUE);
}
