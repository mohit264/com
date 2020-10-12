#pragma once
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

const CLSID CLSID_MultiplicationDivision =
// {13AD12F5-C4DA-40C9-BB9A-9BC694CDE4C8}
{ 0x13ad12f5, 0xc4da, 0x40c9, { 0xbb, 0x9a, 0x9b, 0xc6, 0x94, 0xcd, 0xe4, 0xc8 } };

const IID IID_IMultiplication =
// {BB88D494-16C1-4AC3-897C-77BCC6B77699}
{ 0xbb88d494, 0x16c1, 0x4ac3, { 0x89, 0x7c, 0x77, 0xbc, 0xc6, 0xb7, 0x76, 0x99 } };

const IID IID_IDivision =
// {479C01A7-F830-4654-B562-9A9C2465F799}
{ 0x479c01a7, 0xf830, 0x4654, { 0xb5, 0x62, 0x9a, 0x9c, 0x24, 0x65, 0xf7, 0x99 } };
