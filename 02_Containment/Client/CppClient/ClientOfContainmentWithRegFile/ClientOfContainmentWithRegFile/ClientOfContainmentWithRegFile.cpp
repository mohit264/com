#include<Windows.h>
#include<process.h>
#include"HeaderForClientOfContainmentWithRegFile.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ISum *pISum = NULL;
ISubtract *pISubstract = NULL;
IMultiplication *pIMultiplication = NULL;
IDivision *pIDivision = NULL;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpszCmdLine, int iCmdShow)
{
    WNDCLASSEX wndClass;
    HWND hwnd;
    MSG msg;
    TCHAR szAppName[] = TEXT("COM CLIENT");
	HRESULT hr;
	hr = CoInitialize(NULL);

    if (FAILED(hr))
    {
		MessageBox(NULL, TEXT("COM ENGINE CAN NOT BE INITIALIZED"), TEXT("PROGRAM ERROR"), MB_OK);
		exit(0);
    }
	
    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.lpfnWndProc = WndProc;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndClass.lpszClassName = szAppName;
    wndClass.lpszMenuName = NULL;
    wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassEx(&wndClass);

    hwnd = CreateWindow(szAppName,
        TEXT("Client of COM DLL Server"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL);
    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

	CoUninitialize();
    return msg.wParam;

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HMODULE hDll = NULL;
	typedef int(*MakeSquareFunctionPointer)(int);
	MakeSquareFunctionPointer makeSquareFunctionPointer = NULL;
	int iNum1 = 55;
	int iNum2 = 45;
	int iSum;
	int iMultiplication;
	int iDivision;
	TCHAR str[255];
	HRESULT hr;
    switch (iMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void **)&pISum);
        if (FAILED(hr))
        {
			MessageBox(hwnd, TEXT("ISUM Interface Can Not be Obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
        }
		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);
		wsprintf(str, TEXT("Sum of %d and %d = %d"), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);
		hr = pISum->QueryInterface(IID_ISubtract, (void **) &pISubstract);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISubstract Interface Can Not be Obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		pISum->Release();
		pISum = NULL;
		pISubstract->SubtractionOfTwoIntegers(iNum1, iNum2, &iSum);
		wsprintf(str, TEXT("Substraction of %d and %d = %d"), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);
		hr = pISubstract->QueryInterface(IID_IMultiplication, (void **)&pIMultiplication);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IMultiplication Interface Can Not be Obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		pISubstract->Release();
		pISubstract = NULL;
		iNum1 = 30;
		iNum2 = 25;
		pIMultiplication->MultiplicationOfTwoIntegers(iNum1, iNum2, &iMultiplication);
		wsprintf(str, TEXT("Multiplication of %d and %d = %d"), iNum1, iNum2, iMultiplication);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		hr = pIMultiplication->QueryInterface(IID_IDivision, (void **)&pIDivision);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IDivision Interface Can Not be Obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		pIMultiplication->Release();
		pIMultiplication = NULL;
		iNum1 = 3000;
		iNum2 = 25;
		pIDivision->DivisionOfTwoIntegers(iNum1, iNum2, &iDivision);
		wsprintf(str, TEXT("Division of %d and %d = %d"), iNum1, iNum2, iDivision);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);
		pIDivision->Release();
		pIDivision = NULL;
		DestroyWindow(hwnd);
		break;
	case WM_KEYDOWN:
		MessageBox(hwnd, TEXT("Keydown is received"), TEXT("Message Box"), MB_OK);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("LButton Down is received"), TEXT("Message Box"), MB_OK);
		break;
	case WM_RBUTTONDOWN:
		MessageBox(hwnd, TEXT("RButton Down is received"), TEXT("Message Box"), MB_OK);
		break;
    }

    return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}