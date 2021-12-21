/*
 * Copyright 2019-2021 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */
#include "mainwindow.h"
#include "boardview.h"
#include "pegselectview.h"
#include "buttonview.h"

#include <Alert.h>
#include <LayoutBuilder.h>
#include <Catalog.h>
#include <Application.h>
#include <SeparatorView.h>
#include <iostream>


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
	BSeparatorView *main_separator = new BSeparatorView(B_VERTICAL);

	//define menu layout
	BLayoutBuilder::Menu<>(fTopMenuBar)
		.AddMenu(B_TRANSLATE("File"))
			.AddItem(B_TRANSLATE("New Game"), MW_MENU_NEWGAME, 'N')
			.AddSeparator()
			.AddItem(B_TRANSLATE("Quit"), B_QUIT_REQUESTED, 'Q')
		.End()
		.AddMenu(B_TRANSLATE("Help"))
			.AddItem(B_TRANSLATE("About"), MW_MENU_ABOUT)
		.End()
	.End();

	//define main layout
	BLayoutBuilder::Group<>(this, B_VERTICAL,0)
		.SetInsets(0)
		.Add(fTopMenuBar)
		.AddGroup(B_HORIZONTAL)
			.Add(fBoardView,5)
			.Add(main_separator)
			.Add(fPegSelectView)
		.End()
		.Add(fButtonView)
	.Layout();

}


MainWindow::~MainWindow()
{



}


void
MainWindow::MessageReceived(BMessage *msg)
{

	switch(msg->what)
	{
		// Help/About was clicked
		case MW_MENU_ABOUT:
		{
			be_app->PostMessage(B_ABOUT_REQUESTED);
			break;
		}

		case MW_MENU_NEWGAME:
		{
			fBoardView->Reset();
			break;
		}

		case BV_SUBMITBUTTON_CLICKED:
		{

			fBoardView->EvaluateActiveRow();

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
				B_TRANSLATE("Keep Playing"),
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

