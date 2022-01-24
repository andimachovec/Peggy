/*
 * Copyright 2021 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#include "app.h"
#include "mainwindow.h"

#include <AboutWindow.h>
#include <Catalog.h>
#include <Resources.h>
#include <AppFileInfo.h>
#include <Path.h>
#include <File.h>
#include <FindDirectory.h>


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "App"


const char* kAppName = "Peggy";
const char* kAppSignature = "application/x-vnd.BlueSky-Peggy";


App::App()
	:
	BApplication(kAppSignature)

{

}


App::~App()
{

}


void
App::MessageReceived(BMessage *msg)
{

	switch(msg->what)
	{
		// delegate all unhandled messages to the base class
		default:
		{
			BApplication::MessageReceived(msg);
			break;
		}
	}

}


void
App::AboutRequested()
{

	BAboutWindow *aboutwindow = new BAboutWindow(kAppName, kAppSignature);

	const char *authors[] =
	{
		"Andi Machovec (BlueSky)",
		NULL
	};

	BString code_contributors;
	BString icon_designers;
	BString translators;

	code_contributors << B_TRANSLATE("Code contributions") << ":\n";
	code_contributors << "Humdinger\n";

	icon_designers << B_TRANSLATE("Icon design") << ":\n";
	icon_designers << "Humdinger\n";

	translators << B_TRANSLATE("Translations") << ":\n";
	translators << "Begasus\n"
				<< "Humdinger\n";

	BString extra_info;
	extra_info.Append(code_contributors);
	extra_info.Append("\n");
	extra_info.Append(icon_designers);
	extra_info.Append("\n");
	extra_info.Append(translators);

	aboutwindow->AddCopyright(2021, "Andi Machovec");
	aboutwindow->AddAuthors(authors);
	aboutwindow->AddDescription(B_TRANSLATE("A board game inspired by Mastermind™"));
	aboutwindow->AddExtraInfo(extra_info.String());
	aboutwindow->Show();

}


bool
App::QuitRequested()
{

	//save window frame
	BRect mainwindow_frame = fMainWindow->Frame();
	BFile *settings_file = new BFile(fSettingsFileName, B_READ_WRITE);

	BMessage settings_message;
	settings_message.Unflatten(settings_file);
	settings_message.ReplaceRect("mainwindow_frame", mainwindow_frame);
	settings_file->Seek(0, SEEK_SET); //rewind file position to beginning
	settings_message.Flatten(settings_file);

	delete settings_file;
	return true;

}


void
App::ReadyToRun()
{

	//determine settings file name
	BPath settings_path;
	find_directory(B_USER_SETTINGS_DIRECTORY, &settings_path);
	fSettingsFileName << settings_path.Path() << "/Peggy_settings";

	//get main window frame from settings file (if there is any)
	BRect mainwindow_frame;

	BFile *settings_file = new BFile(fSettingsFileName, B_READ_WRITE|B_CREATE_FILE);
	BMessage settings_message;
	status_t unflatten_result = settings_message.Unflatten(settings_file);

	bool frame_retrieved=false;

	if (unflatten_result == B_OK)
	{
		status_t frame_result = settings_message.FindRect("mainwindow_frame",
														&mainwindow_frame);
		if (frame_result == B_OK)
		{
			frame_retrieved = true;
		}
	}

	// set default frame and add to settings message
	if (!frame_retrieved)
	{
		mainwindow_frame.Set(100,100,412,653);
		settings_message.AddRect("mainwindow_frame", mainwindow_frame);
		settings_message.Flatten(settings_file);
	}

	// create and show main window
	fMainWindow = new MainWindow(mainwindow_frame);

	if (!frame_retrieved)
	{
		fMainWindow->CenterOnScreen();
	}
	fMainWindow->Show();

	delete settings_file;

}


int
main(int argc, char** argv)
{

	App *haiku_app = new App();
	haiku_app->Run();

	delete haiku_app;
	return 0;

}
