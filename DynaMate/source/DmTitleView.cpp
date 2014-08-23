#ifndef HELLO_TITLEVIEW_H
#include "headers/DmTitleView.h"
#endif
#ifndef HELLO_WINDOW_H
#include "headers/DmWindow.h"
#endif

DmTitleView::DmTitleView(BRect rect, char *name,BBitmap *bitmappoint,uint16 totalmovespoint,uint16 stonesleftpoint, uint8 recordpoint):BView(rect, "OST"/*name*/, B_FOLLOW_ALL, B_WILL_DRAW)
{
	bitmap=bitmappoint;
	
	totalmoves=totalmovespoint;
	stonesleft=stonesleftpoint;
	record=recordpoint;
	
	SetViewColor(168,168,168,0);
	SetLowColor(168,168,168,0);

	SetFont(be_plain_font);
	SetFontSize(9);
	
	moves="Jonas";
	stones="loves";
	rec="britta";
	
	sprintf(moves,"%d",totalmoves);
	sprintf(stones,"%d",stonesleft);
	sprintf(rec,"%d",record);

}	   

void DmTitleView::Draw(BRect rect)
{
	if (rect.top<70) DrawBitmap(bitmap, BPoint(0,10));

	if (stonesleft!=65535){
		if (rect.top<102 & rect.bottom>92){
			if (!stonesleft){
				MovePenTo(BPoint(76, 102));
				DrawString("Completed in ");
				DrawString(moves);
				if (totalmoves==1)
					DrawString(" move.");
				else
					DrawString(" moves.");	
			}else{
				MovePenTo(BPoint(30, 102));
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
		}	

		if (rect.top<112 & rect.bottom>102)
			if (record<totalmoves){
				MovePenTo(BPoint(93, 112));
				DrawString("The record is ");
				DrawString(rec);
			}else{
				if (!stonesleft)
				if (record>totalmoves){
					MovePenTo(BPoint(65, 112));
					DrawString("A new record! The old was ");
					DrawString(rec);
				}else{
					MovePenTo(BPoint(80, 112));			
					DrawString("That is the old record");
				}
			}
	}











	if (rect.top<152 & rect.bottom>142){
		MovePenTo(BPoint(72, 152));
		DrawString("Drop a level here to play!");
	}

	if (rect.bottom>240){
		MovePenTo(BPoint(5, 250));
		DrawString("bedev@acc.umu.se");
		MovePenTo(BPoint(145, 250));
		DrawString("www.acc.umu.se/~bedev");
	}
}
