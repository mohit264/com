#include <windows.h>
#include "AggregationInnerComponentWithRegFile.h"

interface INoAggregationIUnknown
{
	virtual HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void **) = 0;
	virtual ULONG __stdcall AddRef_NoAggregation(void) = 0;
	virtual ULONG __stdcall Release_NoAggregation(void) = 0;
};

class CMultiplicationDivision : public INoAggregationIUnknown,IMultiplication, IDivision
{
private:
	long m_cref;
	IUnknown *m_pIUknownOuter;
public:
	CMultiplicationDivision(IUnknown *);
	~CMultiplicationDivision(void);

	
	HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void **);
	ULONG __stdcall AddRef_NoAggregation(void);
	ULONG __stdcall Release_NoAggregation(void);
	
	
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *);
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int *);
};

class CMultiplicationDivisionClassFactory :public IClassFactory
{
private:
	long m_cref;
	
public:
	CMultiplicationDivisionClassFactory(void);
	~CMultiplicationDivisionClassFactory(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);
};
long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
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

CMultiplicationDivision::CMultiplicationDivision(IUnknown *pIUnknownOuter)
{
	m_cref = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
	if (pIUnknownOuter)
	{
		m_pIUknownOuter = pIUnknownOuter;
	}
	else
	{
		m_pIUknownOuter = reinterpret_cast<IUnknown *>(static_cast<INoAggregationIUnknown *>(this));
	}
}

CMultiplicationDivision::~CMultiplicationDivision(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT CMultiplicationDivision::QueryInterface_NoAggregation(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<INoAggregationIUnknown *>(this);
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

HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void **ppv)
{
	return m_pIUknownOuter->QueryInterface(riid, ppv);
}

ULONG CMultiplicationDivision::AddRef_NoAggregation(void)
{
	InterlockedIncrement(&m_cref);
	return (m_cref);
}

ULONG CMultiplicationDivision::AddRef(void)
{
	return m_pIUknownOuter->AddRef();
}

ULONG CMultiplicationDivision::Release_NoAggregation()
{
	InterlockedDecrement(&m_cref);
	if (m_cref == 0)
	{
		delete(this);
		return (0);
	}
	return (m_cref);
}

ULONG CMultiplicationDivision::Release(void)
{
	return m_pIUknownOuter->Release();
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

HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	CMultiplicationDivision *pCMultiplicationDivision = NULL;
	HRESULT hr;
	if ((pUnkOuter != NULL) && (riid != IID_IUnknown))
	{
		return (CLASS_E_NOAGGREGATION);
	}
	pCMultiplicationDivision = new CMultiplicationDivision(pUnkOuter);
	if (pCMultiplicationDivision == NULL)
	{
		return (E_OUTOFMEMORY);
	}
	hr = pCMultiplicationDivision->QueryInterface_NoAggregation(riid, ppv);
	pCMultiplicationDivision->Release_NoAggregation();
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

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
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
	hr = pCSumSubstractClassFactory->QueryInterface(riid, ppv);
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
