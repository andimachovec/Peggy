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
class ButtonView;
class GameController;


enum
{
	MW_MENU_ABOUT ='mw00',
	MW_MENU_NEWGAME,
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
	ButtonView			*fButtonView;
	GameController		*fGameController;
};

#endif
