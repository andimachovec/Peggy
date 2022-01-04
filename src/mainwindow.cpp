/*
 * Copyright 2021 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#include "mainwindow.h"
#include "boardview.h"
#include "pegselectview.h"
#include "buttonview.h"
#include "timerview.h"

#include <Alert.h>
#include <LayoutBuilder.h>
#include <Catalog.h>
#include <Application.h>


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "MainWindow"


MainWindow::MainWindow(BRect geometry)
	:
	BWindow(geometry, "Peggy", B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS)
{

	//initialize GUI objects
	fTopMenuBar = new BMenuBar("topmenubar");
	fBoardView = new BoardView();
	fPegSelectView = new PegSelectView();
	fButtonView = new ButtonView();
	fTimerView = new TimerView();

	//define menu layout
	BLayoutBuilder::Menu<>(fTopMenuBar)
		.AddMenu(B_TRANSLATE("App"))
			.AddItem(B_TRANSLATE("New game"), MW_MENU_NEWGAME, 'N')
			.AddItem(B_TRANSLATE("Game rules" B_UTF8_ELLIPSIS), MW_MENU_RULES)
			.AddSeparator()
			.AddItem(B_TRANSLATE("About Peggy" B_UTF8_ELLIPSIS), MW_MENU_ABOUT)
			.AddItem(B_TRANSLATE("Quit"), B_QUIT_REQUESTED, 'Q')
		.End()
	.End();

	//define main layout
	BLayoutBuilder::Group<>(this, B_VERTICAL, 0)
		.SetInsets(0)
		.Add(fTopMenuBar)
		.AddGroup(B_HORIZONTAL, 0)
			.Add(fBoardView,5)
			.Add(fPegSelectView)
		.End()
		.Add(fButtonView)
		.Add(fTimerView,0)
	.Layout();

	SetPulseRate(1000000);
	fTimerView->StartTimer();

}


MainWindow::~MainWindow()
{



}


void
MainWindow::MessageReceived(BMessage *msg)
{

	switch(msg->what)
	{
		// About was clicked
		case MW_MENU_ABOUT:
		{
			be_app->PostMessage(B_ABOUT_REQUESTED);
			break;
		}

		case MW_MENU_NEWGAME:
		{
			if (fBoardView->GameRunning())
			{
				BAlert *newgame_alert = new BAlert(
					"",
					B_TRANSLATE("A game is still in progress. Do you really want to start a new one?"),
					B_TRANSLATE("Start new game"),
					B_TRANSLATE("Keep playing"),
					NULL,
					B_WIDTH_AS_USUAL,
					B_INFO_ALERT);

				int32 button_index = newgame_alert->Go();
				if (button_index != 0)
				{
					break;
				}
			}

			fTimerView->StopTimer();
			fBoardView->Reset();
			fTimerView->StartTimer();
			break;
		}

		case MW_MENU_RULES:
		{
			BString alertText(B_TRANSLATE(
				"Your goal is to guess a 4-color code by dragging colored "
				"pegs from the stock on the right to the active row in the "
				"middle.\n"
				"After completing a row, you get feedback via black and "
				"white pins at the left of the row:\n\n"
				"⚫ Black pin: a peg has the right color and position\n"
				"⚪ White pin: a peg has the right color, but the wrong position\n\n"
				"The positions of the black or white pins don't necessarily "
				"correspond to the positions of the pegs in your guess."));

			BAlert *alert = new BAlert(B_TRANSLATE("Peggy rules"), alertText,
				B_TRANSLATE("OK"));
			alert->SetShortcut(0, B_ESCAPE);
			alert->Go();
			break;
		}

		case BT_SUBMITBUTTON_CLICKED:
		{

			fBoardView->EvaluateActiveRow();
			if (!fBoardView->GameRunning())
			{
				fTimerView->StopTimer();
			}
			break;
		}

		case BV_ROW_COMPLETE:
		{
			fButtonView->EnableButton();
			break;
		}

		case BV_ROW_INCOMPLETE:
		{
			fButtonView->DisableButton();
			break;
		}

		//forward all unhandled messages to the base class
		default:
		{
			BWindow::MessageReceived(msg);
			break;
		}
	}

}


bool
MainWindow::QuitRequested()
{

	if (fBoardView->GameRunning())
	{
		BAlert *quit_alert = new BAlert(
				"",
				B_TRANSLATE("A game is still in progress. Do you really want to quit?"),
				B_TRANSLATE("Quit"),
				B_TRANSLATE("Keep playing"),
				NULL,
				B_WIDTH_AS_USUAL,
				B_INFO_ALERT);

		int32 button_index = quit_alert->Go();
		if (button_index != 0)
		{
			return false;
		}
	}

	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;

}

