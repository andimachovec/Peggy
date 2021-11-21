/*
 * Copyright 2019-2021 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Window.h>
#include <MenuBar.h>


class BoardView;
class PegSelectView;


enum
{
	MW_MENU_ABOUT ='mw00',
};


class MainWindow : public BWindow {
public:
	MainWindow(BRect geometry);
	~MainWindow();
	void MessageReceived(BMessage *msg);
	bool QuitRequested();

private:
	BMenuBar			*fTopMenuBar;
	BoardView			*fBoardView;
	PegSelectView		*fPegSelectView;
	
};

#endif
