#pragma once
class ISum : public IUnknown
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};
class ISubtract : public IUnknown
{
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};
const CLSID CLSID_SumSubtract = // {CA5FCBA6-1228-4716-AE6E-350AB077F7A0}
{ 0xca5fcba6, 0x1228, 0x4716, { 0xae, 0x6e, 0x35, 0xa, 0xb0, 0x77, 0xf7, 0xa0 } };
const IID IID_ISum = // {68E6868D-A04C-4F31-8C1C-A4B49CA4DC96}
{ 0x68e6868d, 0xa04c, 0x4f31, { 0x8c, 0x1c, 0xa4, 0xb4, 0x9c, 0xa4, 0xdc, 0x96 } };
const IID IID_ISubtract = // {366F5435-DEAB-4CCF-AB78-4A1A9B5D67FB}
{ 0x366f5435, 0xdeab, 0x4ccf, { 0xab, 0x78, 0x4a, 0x1a, 0x9b, 0x5d, 0x67, 0xfb } };
