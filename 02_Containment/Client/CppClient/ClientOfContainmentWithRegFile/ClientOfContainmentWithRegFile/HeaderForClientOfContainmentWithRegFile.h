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
class IMultiplication :public IUnknown
{
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *) = 0;
};

class IDivision :public IUnknown
{
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int *) = 0;
};
const CLSID CLSID_SumSubtract =
{ 0x1a65bcac, 0xb02e, 0x4b1c, { 0xae, 0x2e, 0x80, 0x29, 0xea, 0x55, 0x7, 0x32 } };
const IID IID_ISum =
{ 0x6a99c868, 0xcb7a, 0x4488, { 0xa0, 0xe6, 0xcd, 0xd8, 0x87, 0xc3, 0xd5, 0x81 } };

const IID IID_ISubtract =
{ 0x7ebcb275, 0xd227, 0x46ff, { 0xa9, 0xd0, 0x82, 0x1c, 0x73, 0x15, 0xf0, 0xcd } };

const CLSID CLSID_MultiplicationDivision =
{ 0x38b0f6b0, 0x6268, 0x4dc8, { 0xa6, 0x4a, 0x5, 0x16, 0xa4, 0x60, 0x75, 0xc7 } };

const IID IID_IMultiplication =
{ 0x466ac99f, 0x6c88, 0x4250, { 0xbd, 0xfa, 0x12, 0xf5, 0x32, 0x17, 0xa6, 0x48 } };

const IID IID_IDivision =
{ 0x45d177b8, 0xd6b5, 0x4460, { 0xb4, 0xe5, 0x7c, 0x88, 0xa2, 0x79, 0x78, 0xa8 } };
