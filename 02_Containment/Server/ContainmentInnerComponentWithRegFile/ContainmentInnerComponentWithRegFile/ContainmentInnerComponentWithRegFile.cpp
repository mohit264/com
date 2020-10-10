#include<Windows.h>
#include"ContainmentInnerComponentWithRegFile.h"

class CMultiplicationDivision:public IMultiplication,IDivision
{
	private:
		long m_cref;
	public:
		CMultiplicationDivision(void);
		~CMultiplicationDivision(void);

	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void) ;
	ULONG __stdcall Release(void);

	HRESULT __stdcall MultiplicationOfTwoIntegers(int,int,int *);
	HRESULT __stdcall DivisionOfTwoIntegers(int,int,int *);
};
class CMultiplicationDivisionClassFactory:public IClassFactory
{
	private:
		long m_cref;
	public:
		CMultiplicationDivisionClassFactory(void);
		~CMultiplicationDivisionClassFactory(void);

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
CMultiplicationDivision::CMultiplicationDivision(void)
{
	m_cref = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}
CMultiplicationDivision::~CMultiplicationDivision(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}
HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IMultiplication *>(this);
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
ULONG CMultiplicationDivision::AddRef(void)
{
	InterlockedIncrement(&m_cref);
	return (m_cref);
}
ULONG CMultiplicationDivision::Release(void)
{
	InterlockedDecrement(&m_cref);
	if (m_cref == 0)
	{
		delete(this);
		return (0);
	}
	return (m_cref);
}
HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int *pSum)
{
	*pSum = num1 * num2;
	return (S_OK);
}
HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int *pSum)
{
	*pSum = num1 / num2;
	return (S_OK);
}
CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void)
{
	m_cref = 1;
}
CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void)
{
	
}
HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void **ppv)
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
ULONG CMultiplicationDivisionClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cref);
	return (m_cref);
}
ULONG CMultiplicationDivisionClassFactory::Release()
{
	InterlockedDecrement(&m_cref);
	if (m_cref == 0)
	{
		delete(this);
		return (0);
	}
	return (m_cref);
}
HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown *pUnkOuter,REFIID riid,void **ppv)
{
	CMultiplicationDivision *pCSumSubstract = NULL;
	HRESULT hr;
	if (pUnkOuter != NULL)
	{
		return (CLASS_E_NOAGGREGATION);
	}
	pCSumSubstract = new CMultiplicationDivision;
	if (pCSumSubstract == NULL)
	{
		return (E_OUTOFMEMORY);
	}
	hr = pCSumSubstract->QueryInterface(riid, ppv);
	pCSumSubstract->Release();
	return (hr);
}
HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL fLock)
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
	CMultiplicationDivisionClassFactory *pCSumSubstractClassFactory = NULL;
	HRESULT hr;
	if (rclsid != CLSID_MultiplicationDivision)
	{
		return (CLASS_E_CLASSNOTAVAILABLE);
	}

	pCSumSubstractClassFactory = new CMultiplicationDivisionClassFactory;
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
