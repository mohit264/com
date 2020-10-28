#pragma once
class IMyMath : public IDispatch
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *) = 0;
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};
// {6B47AA78-5B9F-469E-9C2A-4DB43C6A5543}
const CLSID CLSID_MyMath = 
{ 0x6b47aa78, 0x5b9f, 0x469e, { 0x9c, 0x2a, 0x4d, 0xb4, 0x3c, 0x6a, 0x55, 0x43 } };
// {6D72A707-1F3F-4DF8-ADDE-7F4E24C7555E}
const IID IID_IMyMath = 
{ 0x6d72a707, 0x1f3f, 0x4df8, { 0xad, 0xde, 0x7f, 0x4e, 0x24, 0xc7, 0x55, 0x5e } };
