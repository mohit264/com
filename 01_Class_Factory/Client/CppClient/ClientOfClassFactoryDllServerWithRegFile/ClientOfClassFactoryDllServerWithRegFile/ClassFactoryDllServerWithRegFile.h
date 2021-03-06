class ISum :public IUnknown
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *) = 0;
};

class ISubtract :public IUnknown
{
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *) = 0;
};
const CLSID CLSID_SumSubtract =
{ 0x24186a33, 0xcc83, 0x4ae9, {0x8e, 0x78, 0xbe, 0xfb, 0x42, 0x8b, 0xa2, 0xc4} };
const IID IID_ISum =
{ 0xb0d58d2a,0x8b36,0x4387, {0x97,0xfa,0x72,0xa2,0xf,0xb1,0x1b,0xe6} };
const IID IID_ISubtract =
{ 0x8f6e54e5,0x6280,0x4219, {0x81,0x36,0xd1,0xf6,0x12,0x11,0x49,0xe5} };
