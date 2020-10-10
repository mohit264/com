#include<Windows.h>
#include "ContainmentInnerComponentWithRegFile.h"
#include "ContainmentOuterComponentWithRegFile.h"

class CSumSubtract:public ISum,ISubtract,IMultiplication,IDivision
{
	private:
		long m_cref;
		IMultiplication *m_pIMultiplication;
		IDivision *m_pIDivision;
	public:
		CSumSubtract(void);
		~CSumSubtract(void);

	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void) ;
	ULONG __stdcall Release(void);

	HRESULT __stdcall SumOfTwoIntegers(int,int,int *);
	HRESULT __stdcall SubtractionOfTwoIntegers(int,int,int *);
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *);
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int *);
	HRESULT __stdcall InitializeInnerComponent(void);
};
class CSumSubtractClassFactory:public IClassFactory
{
	private:
		long m_cref;
	public:
		CSumSubtractClassFactory(void);
		~CSumSubtractClassFactory(void);

		HRESULT __stdcall QueryInterface(REFIID,void **);
		ULONG __stdcall AddRef(void);
		ULONG __stdcall Release(void);
		HRESULT __stdcall CreateInstance(IUnknown *,REFIID,void **) ;
		HRESULT __stdcall LockServer(BOOL) ;
};
long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

BOOL WINAPI DllMain(HINSTANCE hDll,DWORD dwReason,LPVOID Reserved)
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
CSumSubtract::CSumSubtract(void)
{
	m_pIMultiplication = NULL;
	m_pIDivision = NULL;
	m_cref = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}
CSumSubtract::~CSumSubtract(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
	if (m_pIMultiplication)
	{
		m_pIMultiplication->Release();
		m_pIMultiplication = NULL;
	}
	if (m_pIDivision)
	{
		m_pIDivision->Release();
		m_pIDivision = NULL;
	}
}
HRESULT CSumSubtract::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract *>(this);
	else if (riid == IID_IMultiplication)
		*ppv = static_cast<IMultiplication *>(this);
	else if (riid == IID_IDivision)
		*ppv = static_cast<IDivision *>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *> (*ppv)->AddRef();
	return (S_OK);
}
ULONG CSumSubtract::AddRef(void)
{
	InterlockedIncrement(&m_cref);
	return (m_cref);
}
ULONG CSumSubtract::Release(void)
{
	InterlockedDecrement(&m_cref);
	if (m_cref == 0)
	{
		delete(this);
		return (0);
	}
	return (m_cref);
}
HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int *pSum)
{
	*pSum = num1 + num2;
	return (S_OK);
}
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int *pSum)
{
	*pSum = num1 - num2;
	return (S_OK);
}
HRESULT CSumSubtract::MultiplicationOfTwoIntegers(int num1, int num2, int *pMultiplication)
{
	m_pIMultiplication->MultiplicationOfTwoIntegers(num1, num2, pMultiplication);
	return S_OK;
}
HRESULT CSumSubtract::DivisionOfTwoIntegers(int num1, int num2, int *pDivision)
{
	m_pIDivision->DivisionOfTwoIntegers(num1, num2, pDivision);
	return S_OK;
}
HRESULT CSumSubtract::InitializeInnerComponent()
{
	HRESULT hr;
	hr = CoCreateInstance(CLSID_MultiplicationDivision, NULL, CLSCTX_INPROC_SERVER, IID_IMultiplication,
		(void **)&m_pIMultiplication);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IMultiplication Component Can not be obtained from Inner Component"), TEXT("Error"),
			MB_OK);
		return E_FAIL;
	}
	hr = m_pIMultiplication->QueryInterface(IID_IDivision, (void **)&m_pIDivision);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IDivision Component Can not be obtained from Inner Component"), TEXT("Error"),
			MB_OK);
		return E_FAIL;
	}
	return S_OK;
}
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	m_cref = 1;
}
CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{
	
}
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *> (*ppv)->AddRef();
	return (S_OK);
}
ULONG CSumSubtractClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cref);
	return (m_cref);
}
ULONG CSumSubtractClassFactory::Release()
{
	InterlockedDecrement(&m_cref);
	if (m_cref == 0)
	{
		delete(this);
		return (0);
	}
	return (m_cref);
}
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown *pUnkOuter,REFIID riid,void **ppv)
{
	CSumSubtract *pCSumSubstract = NULL;
	HRESULT hr;
	if (pUnkOuter != NULL)
	{
		return (CLASS_E_NOAGGREGATION);
	}
	pCSumSubstract = new CSumSubtract;
	if (pCSumSubstract == NULL)
	{
		return (E_OUTOFMEMORY);
	}
	hr = pCSumSubstract->InitializeInnerComponent();
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Failed to Initialize Inner Component"), TEXT("Error"),
			MB_OK);
		return E_FAIL;
	}
	hr = pCSumSubstract->QueryInterface(riid, ppv);
	pCSumSubstract->Release();
	return (hr);
}
HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
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

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid,REFIID riid,void **ppv)
{
	CSumSubtractClassFactory *pCSumSubstractClassFactory = NULL;
	HRESULT hr;
	if (rclsid != CLSID_SumSubtract)
	{
		return (CLASS_E_CLASSNOTAVAILABLE);
	}

	pCSumSubstractClassFactory = new CSumSubtractClassFactory;
	if (pCSumSubstractClassFactory == NULL)
	{
		return (E_OUTOFMEMORY);
	}
	hr = pCSumSubstractClassFactory->QueryInterface(riid,ppv);
	pCSumSubstractClassFactory->Release();
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
