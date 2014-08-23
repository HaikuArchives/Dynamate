/*
	
	HelloView.h
	
	Copyright 1995 Be Incorporated, All Rights Reserved.
	
*/

#ifndef HELLO_VIEW_H
#define HELLO_VIEW_H

class HelloWindow;

#include <View.h>
#include "Const.h"
#include "pieces.h"
#include "title.h"

enum {	dmSTOPPED,
		dmOK,
		dmSEARCHING,
		dmEXPL,
		dmDEATH
		};

const uint32 LEVELCOMPLETE 	=	'lvcp';
const uint32 LEVELABANDONED	=	'lvab';

	class HelloView : public BView 
	{
	private:
		
// bitar allokerade.

		struct	pstruct
		{
			int		x;
			int 	y;
			int 	dirx;
			int 	diry;
			uint8	type;
			int		state; // dmSTOPPED, dmOK, dmSEARCHING,  
		};
		
		BBitmap	*bitmap;		// Bilden på skärmen.
		uint8	*buffer;
		
		HelloWindow *window;
		uint8	*level;	
		uint8	*const2point(uint8 piece);
		uint8	gluesleft;

		void	move(int x,int y,int x1,int y1);
		void	explode(int x, int y, bool stone);
		void	update(int x,int y);			
		void	go(pstruct piece);
		void	get_next(pstruct *piece);
		
	public:
					HelloView(BRect frame, char *name, uint8 *levelpoint,	HelloWindow *windowpoint); 
					~HelloView();
	virtual void	Draw(BRect updateRect);
	virtual void	MouseDown(BPoint); 

		uint16		totalmoves; 	// räknare
		uint16		stonesleft;		// räknare: 0=klar

	};
#endif