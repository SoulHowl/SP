// LR8.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab_8.h"

#define MAX_LOADSTRING 100
#define BUTTON_DRAW_ID 1
#define BUTTON_CLEAR_ID 2

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

bool isVisible = false;

// Отправить объявления функций, включенных в этот модуль кода:
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

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LR8, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LR8));

    MSG msg;

    // Цикл основного сообщения:
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LR8));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LR8);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   HWND buttonAdd = CreateWindow(L"BUTTON", NULL, WS_VISIBLE | WS_CHILD | BS_OWNERDRAW | BS_PUSHBUTTON,
	   20, 320, 60, 60, hWnd, (HMENU)BUTTON_DRAW_ID, NULL, NULL);
   HWND buttonClear = CreateWindow(L"BUTTON", NULL, WS_VISIBLE | WS_CHILD | BS_OWNERDRAW | BS_PUSHBUTTON,
	   90, 320, 60, 60, hWnd, (HMENU)BUTTON_CLEAR_ID, NULL, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
			case BUTTON_DRAW_ID:
				isVisible = true;
				InvalidateRect(hWnd, NULL, true);
				break;
			case BUTTON_CLEAR_ID:
				isVisible = false;
				InvalidateRect(hWnd, NULL, true);
				break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_DRAWITEM:
	{
		DRAWITEMSTRUCT* draw = (DRAWITEMSTRUCT*)lParam;
		HBRUSH brush;
		HPEN pen;

		switch (draw->CtlID)
		{
		case BUTTON_DRAW_ID:
		{
			HDC hdc = draw->hDC;

			if (draw->itemAction == ODA_SELECT) {
				brush = CreateSolidBrush(RGB(0, 0, 255));
			}
			else {
				brush = CreateSolidBrush(RGB(0, 255, 0));
			}


			pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));

			SelectObject(hdc, brush);
			SelectObject(hdc, pen);

			Ellipse(hdc, 0, 0, 60, 60);
			MoveToEx(hdc, 10, 30, NULL);
			LineTo(hdc, 50, 30);
			MoveToEx(hdc, 30, 10, NULL);
			LineTo(hdc, 30, 50);
		}
		break;
		case BUTTON_CLEAR_ID:
		{
			HDC hdc = draw->hDC;

			if (draw->itemAction == ODA_SELECT) {
				brush = CreateSolidBrush(RGB(0, 0, 255));
			}
			else {
				brush = CreateSolidBrush(RGB(255, 0, 0));
			}
			pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));

			SelectObject(hdc, brush);
			SelectObject(hdc, pen);

			Ellipse(hdc, 0, 0, 60, 60);
			MoveToEx(hdc, 20, 20, NULL);
			LineTo(hdc, 40, 40);
			MoveToEx(hdc, 40, 20, NULL);
			LineTo(hdc, 20, 40);
		}
		break;
		default:
			break;
		}
	}
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			if (isVisible)
			{
                HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
                SelectObject(hdc, brush);

                Ellipse(hdc, 400, 100, 800, 500);
                Rectangle(hdc, 570, 80, 630, 105);

                POINT points[6];
                brush = CreateSolidBrush(RGB(0, 0, 0));
                SelectObject(hdc, brush);
                MoveToEx(hdc, 595, 80, NULL);
                points[0].x = 595;
                points[0].y = 80;
                points[1].x = 605;
                points[1].y = 70;
                points[2].x = 615;
                points[2].y = 55;
                points[3].x = 650;
                points[3].y = 30;
                points[4].x = 690;
                points[4].y = 45;
                points[5].x = 750;
                points[5].y = 60;
                PolyBezierTo(hdc, points, 6);

                MoveToEx(hdc, 615, 80, NULL);
                points[0].x = 605;
                points[0].y = 80;
                points[1].x = 620;
                points[1].y = 75;
                points[2].x = 630;
                points[2].y = 60;
                points[3].x = 665;
                points[3].y = 40;
                points[4].x = 705;
                points[4].y = 55;
                points[5].x = 755;
                points[5].y = 70;
                PolyBezierTo(hdc, points, 6);
                
                LineTo(hdc, 750, 60);

                brush = CreateSolidBrush(RGB(255, 255, 255));
                SelectObject(hdc, brush);
                POINT pol[13];
                MoveToEx(hdc, 600, 300, NULL);
                pol[0].x = 600 + 80;
                pol[0].y = 300 - 40;
                pol[1].x = 610 + 80;
                pol[1].y = 290 - 40;

                pol[2].x = 640 + 80;
                pol[2].y = 330 - 5 - 40;

                pol[3].x = 670 + 80;
                pol[3].y = 290 - 40;
                pol[4].x = 680 + 80;
                pol[4].y = 300 - 40;

                pol[5].x = 645 + 5 + 80;
                pol[5].y = 335 - 40;

                pol[6].x = 680 + 80;
                pol[6].y = 370 - 40;
                pol[7].x = 670 + 80;
                pol[7].y = 380 - 40;

                pol[8].x = 640 + 80;
                pol[8].y = 340 + 5 - 40;

                pol[9].x = 610 + 80;
                pol[9].y = 380 - 40;
                pol[10].x = 600 + 80;
                pol[10].y = 370 - 40;

                pol[11].x = 635 - 5 + 80;
                pol[11].y = 335 - 40;

                pol[12].x = 600 + 80;
                pol[12].y = 300 - 40;
                Polygon(hdc, pol, 13);

                brush = CreateSolidBrush(RGB(255, 0, 0));
                SelectObject(hdc, brush);
                Ellipse(hdc, 480, 145, 560, 225);
                Ellipse(hdc, 640, 145, 720, 225);

                POINT points1[6];
                brush = CreateSolidBrush(RGB(255, 0, 0));
                SelectObject(hdc, brush);
                MoveToEx(hdc, 490, 350, NULL);
                points1[0].x = 490;
                points1[0].y = 350;
                points1[1].x = 610;
                points1[1].y = 380;
                points1[2].x = 710;
                points1[2].y = 350;

                points1[5].x = 490;
                points1[5].y = 350;
                points1[4].x = 610;
                points1[4].y = 420;
                points1[3].x = 710;
                points1[3].y = 350;
                Polygon(hdc, points1, 6);
                SetPixel(hdc, 600, 400, RGB(255, 0, 0));
                
                HPEN pen = CreatePen(1,2,RGB(255, 0, 0));
                SelectObject(hdc, pen);

                MoveToEx(hdc, 733, 35, NULL);
                LineTo(hdc, 772, 85);

                MoveToEx(hdc, 733, 85, NULL);
                LineTo(hdc, 772, 35);

                pen = CreatePen(1, 2, RGB(255, 196, 0));
                SelectObject(hdc, pen);

                MoveToEx(hdc, 752, 35, NULL);
                LineTo(hdc, 752, 85);

                MoveToEx(hdc, 733, 65, NULL);
                LineTo(hdc, 772, 65);
				/*HBRUSH brush = CreateSolidBrush(RGB(255, 255, 0));
				SelectObject(hdc, brush);

                Ellipse(hdc, 30, 30, 300, 300);
                Rectangle(hdc, 120, 20, 210, 40);
                brush = CreateSolidBrush(RGB(0, 255, 255));
                SelectObject(hdc, brush);
                Ellipse(hdc, 70, 90, 130, 150);
                Ellipse(hdc, 190, 90, 250, 150);
               
                POINT points[3];
                brush = CreateSolidBrush(RGB(0, 0, 0));
                SelectObject(hdc, brush);
                MoveToEx(hdc, 80, 250, NULL);                
                points[0].x = 80;
                points[0].y = 250;
                points[1].x = 170;
                points[1].y = 280;
                points[2].x = 250;
                points[2].y = 250;
                PolyBezierTo(hdc, points, 3);

                MoveToEx(hdc, 80, 250, NULL);
                points[0].x = 80;
                points[0].y = 250;
                points[1].x = 170;
                points[1].y = 350;
                points[2].x = 250;
                points[2].y = 250;
                PolyBezierTo(hdc, points, 3);

                MoveToEx(hdc, 162, 20, NULL);
                points[0].x = 162;
                points[0].y = 20;
                points[1].x = 170;
                points[1].y = 15;
                points[2].x = 180;
                points[2].y = -50 ;
                PolyBezierTo(hdc, points, 3);
                */
			}
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }

    return (INT_PTR)FALSE;
}
