#include "Application.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	Application * theApp = new Application();

	if (FAILED(theApp->Initialise(hInstance, nCmdShow)))
	{
		return -1;
	}

    // Main message loop
    MSG msg = {0};
	bool handled = false;

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message >= WM_KEYFIRST && msg.message <= WM_KEYLAST)
			{
				handled = theApp->HandleKeyboard(msg);
			}
			else if (msg.message >= WM_MOUSEFIRST && msg.message <= WM_MOUSELAST)
			{
				handled = theApp->HandleMouse(msg);
			}

			if (!handled)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			theApp->Update();
			theApp->Draw();
		}
    }

	delete theApp;
	theApp = nullptr;

    return (int) msg.wParam;
}