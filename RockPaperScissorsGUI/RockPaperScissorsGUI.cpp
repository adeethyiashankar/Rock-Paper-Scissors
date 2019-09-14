// RockPaperScissorsGUI.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "RockPaperScissorsGUI.h"
#include <string>
#include <random>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
HWND hPlayer;									// Displays current player
HWND hRock;										// Rock button
HWND hPaper;									// Paper button
HWND hScissors;									// Scissors button
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
std::wstring playerOne = L"";						// Player 1 choice
std::wstring playerTwo = L"";						// Player 2 choice
std::wstring result = L"";						// Result of Rock Paper Scissors
std::wstring title = L"";						// Player 1 choice vs Player 2 choice
bool whichPlayer = true;						// True: Player 1; False: Player 2

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ROCKPAPERSCISSORSGUI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ROCKPAPERSCISSORSGUI));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
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
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ADEETHYIA));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ROCKPAPERSCISSORSGUI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ADEETHYIA));

    return RegisterClassExW(&wcex);
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
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT window;
	GetClientRect(hWnd, &window);
    switch (message)
    {
    case WM_COMMAND:
        {
            // Parse the menu selections:
            switch (LOWORD(wParam))
            {
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case IDM_ROCK:
				if (whichPlayer)
				{
					playerOne = L"rock";
					whichPlayer = false;
					DestroyWindow(hRock);
					hRock = CreateWindowExW(0L, L"Button", L"Rock", WS_VISIBLE | WS_CHILD, window.right / 10, 2 * window.bottom / 3, window.right / 5, window.bottom / 10, hWnd, (HMENU)IDM_ROCK, NULL, NULL);
					SetWindowTextW(hPlayer, L"Player 2");
				}
				else
				{
					playerTwo = L"rock";
					SendMessage(hWnd, (UINT)CHECK_WINNER, (WPARAM)0, (LPARAM)0);
				}
				break;
			case IDM_PAPER:
				if (whichPlayer)
				{
					playerOne = L"paper";
					whichPlayer = false;
					DestroyWindow(hPaper);
					hPaper = CreateWindowExW(0L, L"Button", L"Paper", WS_VISIBLE | WS_CHILD, 4 * window.right / 10, 2 * window.bottom / 3, window.right / 5, window.bottom / 10, hWnd, (HMENU)IDM_PAPER, NULL, NULL);
					SetWindowTextW(hPlayer, L"Player 2");
				}
				else
				{
					playerTwo = L"paper";
					SendMessage(hWnd, (UINT)CHECK_WINNER, (WPARAM)0, (LPARAM)0);
				}
				break;
			case IDM_SCISSORS:
				if (whichPlayer)
				{
					playerOne = L"scissors";
					whichPlayer = false;
					DestroyWindow(hScissors);
					hScissors = CreateWindowExW(0L, L"Button", L"Scissors", WS_VISIBLE | WS_CHILD, 7 * window.right / 10, 2 * window.bottom / 3, window.right / 5, window.bottom / 10, hWnd, (HMENU)IDM_SCISSORS, NULL, NULL);
					SetWindowTextW(hPlayer, L"Player 2");
				}
				else
				{
					playerTwo = L"scissors";
					SendMessage(hWnd, (UINT)CHECK_WINNER, (WPARAM)0, (LPARAM)0);
				}
				break;
			case IDM_HELP:
			{
				int choice = MessageBox(hWnd, L"Each player chooses either rock, paper, or scissors.\nRock beats scissors, scissors beats paper, and paper beats rock.\nA tie occurs if both players choose the same option.\n\nPress OK to choose a random option.", L"Help", MB_OKCANCEL);
				if (choice == IDCANCEL)
					break;
				std::random_device rd;     // only used once to initialise (seed) engine
				std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
				std::uniform_int_distribution<unsigned long long> uni(0, 2);
				int number = uni(rng);
				int rps = 0;
				switch (number)
				{
					case 0:
						rps = IDM_ROCK;
						break;
					case 1:
						rps = IDM_PAPER;
						break;
					case 2:
						rps = IDM_SCISSORS;
						break;
					default:
						MessageBox(hWnd, L"Random option could not be performed", L"Random selection failed", MB_ICONERROR);
						break;
				}
				SendMessage(hWnd, (UINT)WM_COMMAND, (WPARAM)rps, (LPARAM)0);
				break;
			}
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
			break;
		case CHECK_WINNER:
			if (playerOne == L"rock")
			{
				if (playerTwo == L"rock")
				{
					title = L"Rock vs Rock";
					result = L"Tie";
				}
				else if (playerTwo == L"paper")
				{
					title = L"Rock vs Paper";
					result = L"Player 2 wins";
				}
				else if (playerTwo == L"scissors")
				{
					title = L"Rock vs Scissors";
					result = L"Player 1 wins";
				}
			}
			else if (playerOne == L"paper")
			{
				if (playerTwo == L"rock")
				{
					title = L"Paper vs Rock";
					result = L"Player 1 wins";
				}
				else if (playerTwo == L"paper")
				{
					title = L"Paper vs Paper";
					result = L"Tie";
				}
				else if (playerTwo == L"scissors")
				{
					title = L"Paper vs Scissors";
					result = L"Player 2 wins";
				}
			}
			else if (playerOne == L"scissors")
			{
				if (playerTwo == L"rock")
				{
					title = L"Scissors vs Rock";
					result = L"Player 2 wins";
				}
				else if (playerTwo == L"paper")
				{
					title = L"Scissors vs Paper";
					result = L"Player 1 wins";
				}
				else if (playerTwo == L"scissors")
				{
					title = L"Scissors vs Scissors";
					result = L"Tie";
				}
			}
			MessageBox(hWnd, result.c_str(), title.c_str(), MB_ICONINFORMATION);
			whichPlayer = true;
			playerOne = L"";
			playerTwo = L"";
			SetWindowTextW(hPlayer, L"Player 1");
        }
        break;
	case WM_CREATE:
		hPlayer = CreateWindowExW(0L, L"static", L"Player 1", WS_VISIBLE | WS_CHILD | ES_CENTER, 0, 0, window.right, window.bottom / 2, hWnd, NULL, NULL, NULL);
		hRock = CreateWindowExW(0L, L"Button", L"Rock", WS_VISIBLE | WS_CHILD, window.right / 10, 2 * window.bottom / 3, window.right / 5, window.bottom / 10, hWnd, (HMENU)IDM_ROCK, NULL, NULL);
		hPaper = CreateWindowExW(0L, L"Button", L"Paper", WS_VISIBLE | WS_CHILD, 4 * window.right /	10, 2 * window.bottom / 3, window.right / 5, window.bottom / 10, hWnd, (HMENU)IDM_PAPER, NULL, NULL);
		hScissors = CreateWindowExW(0L, L"Button", L"Scissors", WS_VISIBLE | WS_CHILD, 7 * window.right / 10, 2 * window.bottom / 3, window.right / 5, window.bottom / 10, hWnd, (HMENU)IDM_SCISSORS, NULL, NULL);
		break;
    case WM_PAINT:
        {
			if (window.right < 300)
			{
				SetWindowTextW(hRock, L"R");
				SetWindowTextW(hPaper, L"P");
				SetWindowTextW(hScissors, L"S");
			}
			else if (window.right > 300)
			{
				SetWindowTextW(hRock, L"Rock");
				SetWindowTextW(hPaper, L"Paper");
				SetWindowTextW(hScissors, L"Scissors");
			}
			int length = window.right > window.bottom ? window.bottom : window.right;
			int font = (int)240 * length / 534;
			if (font > 200)
				font = 200;
			else if (font > 100)
				font = 100;
			else if (font > 50)
				font = 50;
			else if (font > 30)
				font = 30;
			HFONT hFont = CreateFont(font, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, UNICODE, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Calibri");
			MoveWindow(hPlayer, 0, 0, window.right, (int)window.bottom / 2, true);
			MoveWindow(hRock, window.right / 10, 2 * window.bottom / 3, window.right / 5, window.bottom / 10, true);
			MoveWindow(hPaper, 4 * window.right / 10, 2 * window.bottom / 3, window.right / 5, window.bottom / 10, true);
			MoveWindow(hScissors, 7 * window.right / 10, 2 * window.bottom / 3, window.right / 5, window.bottom / 10, true);
			SendMessage(hPlayer, WM_SETFONT, WPARAM(hFont), TRUE);
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_CTLCOLORSTATIC:
	{
		HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, RGB(0, 0, 0));
		SetBkColor(hdcStatic, RGB(255, 255, 255));
		return (INT_PTR)hBrush;
		break;
	}
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}