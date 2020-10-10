#pragma once
#undef INTERFACE //If there is interface word before then undef it
#define INTERFACE ISum

// Creating interface in C
DECLARE_INTERFACE_(ISum, IUnknown)
{
	//IUnown Methods
	STDMETHOD(QueryInterface)(THIS_ REFIID, void **) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	//ISUM METHOD
	STDMETHOD(SumOfTwoIntegers)(THIS_ int, int, int *) PURE;
};

#undef INTERFACE
#define  INTERFACE ISubtract

DECLARE_INTERFACE_(ISubtract, IUnknown)
{
	//IUnown Methods
	STDMETHOD(QueryInterface)(THIS_ REFIID, void **) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	//ISUBTRACT METHOD
	STDMETHOD(SubtractionOfTwoIntegers)(THIS_ int, int, int *) PURE;
};

const CLSID CLSID_SumSubtract =
{ 0x24186a33, 0xcc83, 0x4ae9, {0x8e, 0x78, 0xbe, 0xfb, 0x42, 0x8b, 0xa2, 0xc4} };
const IID IID_ISum =
{ 0xb0d58d2a,0x8b36,0x4387, {0x97,0xfa,0x72,0xa2,0xf,0xb1,0x1b,0xe6} };
const IID IID_ISubtract =
{ 0x8f6e54e5,0x6280,0x4219, {0x81,0x36,0xd1,0xf6,0x12,0x11,0x49,0xe5} };
