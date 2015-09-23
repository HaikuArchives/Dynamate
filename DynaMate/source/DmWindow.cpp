#include <stdio.h>

#include <StorageKit.h>
#include <stdlib.h>
#include <string.h>
#include <AppKit.h>
#include "DmWindow.h"

#include <stdio.h>
void set_palette_entry(long i,rgb_color c);

HelloWindow::HelloWindow(BRect theframe)
				: BWindow(theframe, "DynaMate",  B_TITLED_WINDOW, B_NOT_RESIZABLE)
{
/// /// /// /// SOUND /// /// /// /// LÄGG TILL FELKOLLAR !!
	error=0;
	snd = new SoundStuff;

	app_info ai;	
	if (be_app->GetAppInfo(&ai)){ error = B_ERROR; fputs("DynaMate: Error getting AppInfo.\n",stderr); return;}

	entry_ref mref, sref, eref;
	BEntry *ment, *sent, *eent;
	
	BDirectory dir;
	BEntry *exeEnt;
	
	exeEnt = new BEntry(&(ai.ref));
	if (exeEnt->InitCheck())	{ error = B_ERROR; fputs("DynaMate: Error converting ref to Entry.\n",stderr); return;}
	if (exeEnt->GetParent(&dir)){ error = B_ERROR; fputs("DynaMate: Error getting parent.\n",stderr); return;}
	
	ment = new BEntry(&dir, "sfx/move");
	if (ment->InitCheck())		{ error = B_ERROR; fputs("DynaMate: Problems with file 'sfx/move'.\n",stderr); return;}

	sent = new BEntry(&dir, "sfx/stop");
	if (sent->InitCheck())		{ error = B_ERROR; fputs("DynaMate: Problems with file 'sfx/stop'.\n",stderr); return;}

	eent = new BEntry(&dir, "sfx/explosion");
	if (eent->InitCheck())		{ error = B_ERROR; fputs("DynaMate: Problems with file 'sfx/explosion'.\n",stderr); return;}

	if (ment->GetRef(&mref))	{ error = B_ERROR; fputs("DynaMate: Error converting ref to Entry.(mref)\n",stderr); return;}
	if (sent->GetRef(&sref))	{ error = B_ERROR; fputs("DynaMate: Error converting ref to Entry.(sref)\n",stderr); return;}
	if (eent->GetRef(&eref))	{ error = B_ERROR; fputs("DynaMate: Error converting ref to Entry.(eref)\n",stderr); return;}

	delete ment;
	delete sent;
	delete eent;
	delete exeEnt;

	snd->moveblip = new BSound(&mref,true);
	snd->stopblip = new BSound(&sref,true);
	snd->explblip = new BSound(&eref,true);

	if (snd->moveblip->InitCheck()) { error = B_ERROR; fputs("DynaMate: Problems with file 'sfx/move'.\n",stderr); return;}
	if (snd->stopblip->InitCheck()) { error = B_ERROR; fputs("DynaMate: Problems with file 'sfx/stop'.\n",stderr); return;}
	if (snd->explblip->InitCheck()) { error = B_ERROR; fputs("DynaMate: Problems with file 'sfx/explosion'.\n",stderr); return;}

/// /// /// /// /// /// /// /// ///

	frame=theframe;
	totalmoves=0;
	stonesleft=65535;
	SIZE=16;
	file = NULL;		
// reservera banan
	level=(uint8 *)malloc(256+1);		// 256==en piece 1==rekordet
	
// Starta en view	
	frame.OffsetTo(B_ORIGIN);

	gameView = NULL;
	titleView = NULL;
	LaunchTitle();
}

HelloWindow::~HelloWindow()
{
	KillGame(); 
	KillTitle(); 

	delete snd;
}


void HelloWindow::LaunchTitle()
{
	if (!gameView){
		titleView = new DmTitleView(BRect(0,0,16*SIZE-1,16*SIZE-1), totalmoves,stonesleft,level[256]);
		AddChild((BView*)titleView);
	}
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
	if (!titleView){
	gameView = new HelloView(BRect(0,0,16*SIZE-1,16*SIZE-1), "Game",level,this, totalmoves,snd);
	AddChild((BView*)gameView);
	}
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

void HelloWindow::saverec(uint8 *buff)
{
	{
//		printf("saverec: %d\n",buff[256]);
		file->WriteAt(256,(void *) (buff+256), 1);
		delete file; file=NULL;
	}
}


void HelloWindow::load256(entry_ref *ref, uint32 filesize, uint8 *buff)
{
	if (file) delete file;
	file=new BFile(ref,B_READ_WRITE);
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
	totalmoves=0;
}

void HelloWindow::MessageReceived(BMessage *message)
{ 
	char filename[512];
	//printf("recieved:%d\n",message);
	switch ( message->what )
	{			
		case	B_SIMPLE_DATA	:	{
									entry_ref ref;
									if( message->FindRef("refs", &ref) == B_OK )
										{
										strcpy (filename,"DynaMate - ");
										strcpy ((char *)filename+11,ref.name);
										SetTitle(filename);

										level[256]=255;
										load256(&ref,257,level);
										KillGame();
										KillTitle();
										LaunchGame();
										gameView->totalmoves=0; // added 981018
										}
									}
									break;
		case	LEVELCOMPLETE	:	{
									KillGame();
									uint16 temp=level[256]; //gamla rekordet
									if (totalmoves<level[256]){
										level[256]=totalmoves;
										saverec(level);
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
 								
		default	:	BWindow::MessageReceived(message);
								break;
	}
}
   
void HelloWindow::Zoom(BPoint punkt, float w, float h)
{
	if (SIZE==24){
		SIZE=16;
		ResizeTo(255,255);
	}else{
		ResizeTo(24*16-1,24*16-1);
		SIZE=24;
	}	

	if (gameView){
		KillGame();
		LaunchGame();		
	}else{
		KillTitle();
		LaunchTitle();
	}
}

bool HelloWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return(TRUE);
}

status_t HelloWindow::InitCheck()
{
	return error;
};

