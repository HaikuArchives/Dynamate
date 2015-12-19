/*
	
	LevelWindow.cpp
	
	Copyright 1995 Be Incorporated, All Rights Reserved.
	
*/

#include <Application.h>
#include <GroupLayout.h>
#include <MenuBar.h>

#include "LevelView.h"

#ifndef LEVELWINDOW_H
#include "LevelWindow.h"
#endif

enum
{
	SAVE = 'save',
	LOAD = 'load',
	SAVE_AS = 'svas'
};

void set_palette_entry(long i,rgb_color c);

LevelWindow::LevelWindow(BRect frame)
	: BWindow(frame, "LevelWorld",  B_TITLED_WINDOW, B_NOT_ZOOMABLE | B_NOT_RESIZABLE)
{
	BMenuBar* bar = new BMenuBar("menu");
	BView* aView = new LevelView("View");

	BGroupLayout* layout = new BGroupLayout(B_VERTICAL);
	SetLayout(layout);
	layout->SetSpacing(0.f);

	AddChild(bar);
	AddChild(aView);

	BMenu* fileMenu = new BMenu("Level");
	BMenuItem* loadMenu = new BMenuItem("Open" B_UTF8_ELLIPSIS,
		new BMessage(LOAD), 'O');
	BMenuItem* saveMenu = new BMenuItem("Save" B_UTF8_ELLIPSIS,
		new BMessage(SAVE), 'S');
	BMenuItem* saveAsMenu = new BMenuItem("Save As" B_UTF8_ELLIPSIS,
		new BMessage(SAVE_AS), 'S', B_SHIFT_KEY);

	loadMenu->SetTarget(aView);
	saveMenu->SetTarget(aView);
	saveAsMenu->SetTarget(aView);

	bar->AddItem(fileMenu);
	fileMenu->AddItem(loadMenu);
	fileMenu->AddItem(saveMenu);
	fileMenu->AddItem(saveAsMenu);
}

bool LevelWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return(TRUE);
}
