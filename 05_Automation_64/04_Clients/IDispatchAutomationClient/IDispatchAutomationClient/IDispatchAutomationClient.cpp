#include<Windows.h>
#include<stdio.h>
#include"AutomationServerWithRegFile.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
IDispatch *pIDispatch = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndClass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("COM IDispatch CLIENT");
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
	void ComErrorDescriptionString(HWND, HRESULT);
	int iNum1 = 55;
	int iNum2 = 45;
	
	TCHAR str[255];
	HRESULT hr;
	DISPID dispid;
	OLECHAR *szFunctionName1 = (OLECHAR*)L"SumOfTwoIntegers";
	OLECHAR *szFunctionName2 = (OLECHAR*)L"SubtractionOfTwoIntegers";
	VARIANT vArg[2], vRet;
	DISPPARAMS param = { vArg, 0, 2, NULL };
	
	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_MyMath, NULL, CLSCTX_INPROC_SERVER, 
			IID_IDispatch, (void **)&pIDispatch);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			DestroyWindow(hwnd);
		}
		VariantInit(vArg);
		vArg[0].vt = VT_INT;
		vArg[0].intVal = iNum2;
		vArg[1].vt = VT_INT;
		vArg[1].intVal = iNum1;
		param.cArgs = 2;
		param.cNamedArgs = 0;
		param.rgdispidNamedArgs = NULL;
		param.rgvarg = vArg;

		VariantInit(&vRet);
		
		hr = pIDispatch->GetIDsOfNames(IID_NULL, &szFunctionName1, 1, GetUserDefaultLCID(), &dispid);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(NULL, TEXT("Can Not Get ID for Sum Of Two Integers"), TEXT("ERROR"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
			
		}
		hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &param, &vRet, NULL, NULL);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(NULL, TEXT("Can Not Invoke SumOfTwoIntegers"), TEXT("ERROR"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);

		}
		wsprintf(str, TEXT("Sum of %d and %d = %d"), iNum1, iNum2, vRet.lVal);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		hr = pIDispatch->GetIDsOfNames(IID_NULL, &szFunctionName2, 1, GetUserDefaultLCID(), &dispid);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(NULL, TEXT("Can Not Get ID for SubtractionOfTwoIntegers"), TEXT("ERROR"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}
		hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &param, &vRet, NULL, NULL);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(NULL, TEXT("Can Not Invoke SubtractionOfTwoIntegers"), TEXT("ERROR"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}
		
		wsprintf(str, TEXT("Substraction of %d and %d = %d"), iNum1, iNum2, vRet.lVal);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);
		VariantClear(vArg);
		VariantClear(&vRet);
		pIDispatch->Release();
		pIDispatch = NULL;
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

void ComErrorDescriptionString(HWND hWnd, HRESULT hr)
{
	TCHAR* szErrorMessage = NULL;
	TCHAR str[255];
	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
	{
		hr = HRESULT_CODE(hr);
	}
	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&szErrorMessage, 0, NULL) != 0)
	{
		swprintf_s(str, TEXT("%#x : %s"), hr, szErrorMessage);
		LocalFree(szErrorMessage);
	}
	else
	{
		swprintf_s(str, TEXT("Could not find description for error # %#x.]\n"), hr);
	}

	MessageBox(hWnd, str, TEXT("COM ERROR"), MB_OK);
}
