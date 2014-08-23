#include "DmTitleView.h"
#include <Bitmap.h>
#include <Application.h>
#include <Rect.h>
#include <stdio.h>
#include <Alert.h>
#include "title.h"

DmTitleView::DmTitleView(BRect rect, uint16 totalmovespoint,uint16 stonesleftpoint, uint8 recordpoint):BView(rect, "OST"/*name*/, B_FOLLOW_ALL, B_WILL_DRAW)
{
puts("bozze");
//	titelkillen
	bitmap=new BBitmap(BRect(0,0,63,62),B_COLOR_8_BIT);
	bitmap->SetBits(title, 64*63, 0, B_COLOR_8_BIT);
	
	size=(uint8)((rect.right - rect.left + 1) /16);
	totalmoves=totalmovespoint;
	stonesleft=stonesleftpoint;
	record=recordpoint;
	
	SetViewColor(255,255,255,0);
	SetLowColor(255,255,255,0);

	SetFont(be_plain_font);
	SetFontSize(9);
	
	sprintf(moves,"%d",totalmoves);
	sprintf(stones,"%d",stonesleft);
	sprintf(rec,"%d",record);

}	   

void DmTitleView::Draw(BRect rect)
{
puts("Bosse");
	/*if (rect.top<70)*/ DrawBitmap(bitmap, BPoint(size*8-32,size*8-32));
	if (stonesleft!=65535){
//		if (rect.top<102 & rect.bottom>92){
			if (!stonesleft){
				MovePenTo(BPoint(size*8-51, size*4));
				DrawString("Completed in ");
				DrawString(moves);
				if (totalmoves==1)
					DrawString(" move.");
				else
					DrawString(" moves.");	
			}else{
				MovePenTo(BPoint(size*8-97, size*4));
				DrawString("Abandoned after ");
				DrawString(moves);
				if (totalmoves==1)
					DrawString(" move, with ");
				else
					DrawString(" moves, with ");
							
				DrawString(stones);
				if (stonesleft==1)
					DrawString(" stone left.");
				else
					DrawString(" stones left.");
			}
//		}	

		if (rect.top<112 & rect.bottom>102)
			if (record<totalmoves){
				MovePenTo(BPoint(size*8-34,  size*4+12));
				DrawString("The record is ");
				DrawString(rec);
			}else{
				if (!stonesleft)
				if (record>totalmoves){
					MovePenTo(BPoint(size*8-62,  size*4+12));
					DrawString("A new record! The old was ");
					DrawString(rec);
				}else{
					MovePenTo(BPoint(size*8-50,  size*4+12));			
					DrawString("That is the old record.");
				}
			}
	}
}

//	! M O U S E D O W N !
void DmTitleView::MouseDown(BPoint cursor)
{
	BAlert *myAlert = new BAlert("About", "Dynamate R4 (c)1999 Jonas Norberg\n\nTo play Dynamate drop a level on the main window, on the application or doubleclick a level.","Quit","Ok",NULL, B_WIDTH_AS_USUAL, B_OFFSET_SPACING, B_IDEA_ALERT);
	if (0 == myAlert->Go()) be_app->PostMessage(B_QUIT_REQUESTED);

}