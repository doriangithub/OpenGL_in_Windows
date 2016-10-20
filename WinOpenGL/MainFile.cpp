#define WIN32_LEAN_AND_MEAN             // exclude rarely-used stuff from Windows headers

#include <windows.h>
#include "resource.h"

// function declarations
int mainMessageLoop(HACCEL hAccelTable = 0);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdArgs, int cmdShow)
{
	// get app name from resource file
	wchar_t name[256];
	LoadString(hInst, IDS_APP_NAME, name, 256);


	// main message loop //////////////////////////////////////////////////////
	int exitCode;
	HACCEL hAccelTable = 0;
	//hAccelTable = ::LoadAccelerators(hInst, MAKEINTRESOURCE(ID_ACCEL));
	exitCode = mainMessageLoop(hAccelTable);

	//ScanSpini::log("Application terminated.");
	return exitCode;
}


int mainMessageLoop(HACCEL hAccelTable)
{
	HWND activeHandle;
	MSG msg;

	while (GetMessage(&msg, 0, 0, 0) > 0)  // loop until WM_QUIT(0) received
	{
		// determine the activated window is dialog box
		// skip if messages are for the dialog windows
		activeHandle = GetActiveWindow();
		if (GetWindowLongPtr(activeHandle, GWL_EXSTYLE) & WS_EX_CONTROLPARENT) // WS_EX_CONTROLPARENT is automatically added by CreateDialogBox()
		{
			if (IsDialogMessage(activeHandle, &msg))
				continue;   // message handled, back to while-loop
		}

		// now, handle window messages
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;                 // return nExitCode of PostQuitMessage()
}
