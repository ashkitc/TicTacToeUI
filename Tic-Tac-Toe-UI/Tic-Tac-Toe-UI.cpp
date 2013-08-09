// Tic-Tac-Toe-UI.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Tic-Tac-Toe-UI.h"
#define MAX_LOADSTRING 100
#include "Cross.h"
#include "Zero.h"
#include "PlayBoard.h"
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
const int winHeight = 600;                      // windows hieght
const int  winWidth = 600;                      // window width
// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) ;
int DisplayGameOverMessage(LPTSTR title, LPTSTR message, HWND father);
void MousePressed(int x, int y, HWND hwnd);
Sign *sign = new Cross();
POINT o;
PlayBoard *playboard;
int xCoord;
int yCoord;
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TICTACTOEUI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TICTACTOEUI));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TICTACTOEUI));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
   POINT O;
   O.x = 0;
   O.y = 0;
   playboard =  new PlayBoard(winWidth,winHeight,O);
   hInst = hInstance; // Store instance handle in our global variable
   int x = (GetSystemMetrics(SM_CXSCREEN)- winWidth) / 2;
   int y = (GetSystemMetrics(SM_CYSCREEN)- winHeight) / 2;
   int captionHeight = (GetSystemMetrics(SM_CYCAPTION));
   int borderWidht = (GetSystemMetrics(SM_CXBORDER));
   hWnd = CreateWindow(szWindowClass, szTitle,WS_VISIBLE|WS_SYSMENU|WS_MINIMIZEBOX ,
	   x, y, winWidth+borderWidht, winHeight+captionHeight , NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	HPEN hPen;
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
	
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		playboard->checkWinner();
		switch(playboard->getWinner())
		{
		case 'X':
			playboard->paint(hdc);
			DisplayGameOverMessage(L"Game over!", L"Congratulations, You win",hWnd);
			break;
		case 'O':
			playboard->paint(hdc);
			DisplayGameOverMessage(L"Game over!", L"Sorry, but this time you LOSER",hWnd);
			break;
		case ' ':
			playboard->paint(hdc);
			if(playboard->allCellsAreOccupied() )
			{
			DisplayGameOverMessage(L"Game over!", L"This time friendship wins",hWnd);
			}
			break;
		}

		EndPaint(hWnd, &ps);
		break;

	case WM_LBUTTONDOWN:
		xCoord=LOWORD(lParam); //get Mouse coordinats
        yCoord=HIWORD(lParam);
		MousePressed(xCoord,yCoord,hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
void MousePressed(int x, int y, HWND hwnd)
{
	if( playboard->handlePress(x,y) )
	{
		playboard->maxRaitedCell('O').setValue('O');
	}
   InvalidateRect(hwnd, NULL, TRUE);
   UpdateWindow(hwnd);
}


int DisplayGameOverMessage(LPTSTR title, LPTSTR message, HWND father)
{
    int msgboxID = MessageBox(
       father,
		message,
       title,
	 MB_RETRYCANCEL
    );

	if (msgboxID == IDRETRY)
    {
		playboard->reset();
		InvalidateRect(father, NULL, TRUE);
        UpdateWindow(father);
    }
	if(msgboxID == IDCANCEL)
	{
		exit(0);
	}

    return msgboxID;	
}


