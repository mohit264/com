#include<Windows.h>
#include<stdio.h>
#include "AutomationServerWithRegFile.h"

class CMyMath: public IMyMath
{
private:
	long m_cref;
	ITypeInfo *m_pITypeInfo;
public:
	CMyMath(void);
	~CMyMath(void);

	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall GetTypeInfoCount(UINT *);
	HRESULT __stdcall GetTypeInfo(UINT, LCID, ITypeInfo **);
	HRESULT __stdcall GetIDsOfNames(REFIID, LPOLESTR *, UINT, LCID, DISPID *);
	HRESULT __stdcall Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS *, VARIANT *, EXCEPINFO *, UINT *);

	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);

	HRESULT __stdcall InitInstance(void);
};

class CMyMathClassFactory : public IClassFactory
{
private:
	long m_cref;
public:
	CMyMathClassFactory(void);
	~CMyMathClassFactory(void);

	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;
// {2E9377C1-EB7B-47A2-8760-50171408D464}
const GUID LIBID_AutomationServer = 
{ 0x2e9377c1, 0xeb7b, 0x47a2, { 0x87, 0x60, 0x50, 0x17, 0x14, 0x8, 0xd4, 0x64 } };

BOOL WINAPI DllMain(HINSTANCE hDll,  DWORD dwReason, LPVOID Reserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return (TRUE);
}

CMyMath::CMyMath(void)
{
	m_cref = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CMyMath::~CMyMath()
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT CMyMath::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<IUnknown *>(this);
	}
	else if (riid == IID_IDispatch)
	{
		*ppv = static_cast<IDispatch *>(this);
	}
	else if (riid == IID_IMyMath)
	{
		*ppv = static_cast<IMyMath *>(this);
	}
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return (S_OK);
}

ULONG CMyMath::AddRef()
{
	InterlockedIncrement(&m_cref);
	return (m_cref);
}

ULONG CMyMath::Release()
{
	InterlockedDecrement(&m_cref);
	if (m_cref == 0)
	{
		m_pITypeInfo->Release();
		m_pITypeInfo = NULL;
		delete(this);
		return (0);
	}
	return (m_cref);
}

HRESULT CMyMath::SumOfTwoIntegers(int num1, int num2, int *pSum)
{
	*pSum = num1 + num2;
	return (S_OK);
}

HRESULT CMyMath::SubtractionOfTwoIntegers(int num1, int num2, int *pSubtract)
{
	*pSubtract = num1 - num2;
	return (S_OK);
}

HRESULT CMyMath::InitInstance(void)
{
	void ComErrorDescriptionString(HWND, HRESULT);
	HRESULT hr;
	ITypeLib *pITypeLib = NULL;
	if (m_pITypeInfo == NULL)
	{
		hr = LoadRegTypeLib(LIBID_AutomationServer, 1, 0, 0x00, &pITypeLib);

		if (FAILED(hr))
		{
			ComErrorDescriptionString(NULL, hr);
			return (hr);
		}
		hr = pITypeLib->GetTypeInfoOfGuid(IID_IMyMath, &m_pITypeInfo);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(NULL, hr);
			pITypeLib->Release();
			return (hr);
		}
		pITypeLib->Release();
	}
	return (S_OK);
}

CMyMathClassFactory::CMyMathClassFactory(void)
{
	m_cref = 1;
}

CMyMathClassFactory::~CMyMathClassFactory(void)
{
	
}

HRESULT CMyMathClassFactory::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<IClassFactory *>(this);
	}
	else if (riid == IID_IClassFactory)
	{
		*ppv = static_cast<IClassFactory *>(this);
	}
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return (S_OK);
}

ULONG CMyMathClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cref);
	return (m_cref);
}

ULONG CMyMathClassFactory::Release()
{
	InterlockedDecrement(&m_cref);
	if (m_cref == 0)
	{
		delete(this);
		return (0);
	}
	return (m_cref);
}

HRESULT CMyMathClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	CMyMath *pCMymath = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
	{
		return (CLASS_E_NOAGGREGATION);
	}
	pCMymath = new CMyMath;
	if (pCMymath == NULL)
	{
		return (E_OUTOFMEMORY);
	}
	pCMymath->InitInstance();
	hr = pCMymath->QueryInterface(riid, ppv);
	pCMymath->Release();
	return (hr);
}

HRESULT CMyMathClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
	{
		InterlockedIncrement(&glNumberOfServerLocks);
	}
	else
	{
		InterlockedDecrement(&glNumberOfServerLocks);
	}
	return (S_OK);
}

HRESULT CMyMath::GetTypeInfoCount(UINT *pCountTypeInfo)
{
	*pCountTypeInfo = 1;
	return (S_OK);
}

HRESULT CMyMath::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo **ppItypeInfo)
{
	*ppItypeInfo = NULL;
	if (iTypeInfo != 0)
	{
		return (DISP_E_BADINDEX);
	}
	m_pITypeInfo->AddRef();
	*ppItypeInfo = m_pITypeInfo;
	return (S_OK);
}

HRESULT CMyMath::GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
{
	return (DispGetIDsOfNames(m_pITypeInfo, rgszNames, cNames, rgDispId));
}

HRESULT CMyMath::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExceptInfo, UINT *puArgError)
{
	HRESULT hr;

	hr = DispInvoke(this, m_pITypeInfo, dispIdMember, wFlags, pDispParams, pVarResult, pExceptInfo, puArgError);
	return (hr);
}

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	CMyMathClassFactory *pCMyMathClassFactory = NULL;
	HRESULT hr;
	if (rclsid != CLSID_MyMath)
	{
		return (CLASS_E_CLASSNOTAVAILABLE);
	}

	pCMyMathClassFactory = new CMyMathClassFactory;
	if (pCMyMathClassFactory == NULL)
	{
		return (E_OUTOFMEMORY);
	}
	hr = pCMyMathClassFactory->QueryInterface(riid, ppv);
	pCMyMathClassFactory->Release();
	return (hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
	{
		return (S_OK);
	}
	else
		return (S_FALSE);
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
		hr, MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT), (LPTSTR)&szErrorMessage, 0, NULL) != 0)
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
