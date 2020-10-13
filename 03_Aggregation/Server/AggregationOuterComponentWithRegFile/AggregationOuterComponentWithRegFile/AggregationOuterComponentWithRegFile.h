class ISum:public IUnknown
{
    public:
        virtual HRESULT __stdcall SumOfTwoIntegers(int,int,int *)=0;
};

class ISubtract:public IUnknown
{
    public:
        virtual HRESULT __stdcall SubtractionOfTwoIntegers(int,int,int *)=0;
};
const CLSID CLSID_SumSubtract=
// 
{ 0x111422b0, 0x5dd5, 0x4cfc, { 0xa2, 0x56, 0x14, 0x3b, 0xfb, 0xc7, 0x3e, 0xb6 } };

const IID IID_ISum= 
// {FC6020A5-67D2-4B94-AE76-28900B91A141}
{ 0xfc6020a5, 0x67d2, 0x4b94, { 0xae, 0x76, 0x28, 0x90, 0xb, 0x91, 0xa1, 0x41 } };


const IID IID_ISubtract= 
// {71DBC745-9BE0-4969-AF40-6342AD91EE72}
{ 0x71dbc745, 0x9be0, 0x4969, { 0xaf, 0x40, 0x63, 0x42, 0xad, 0x91, 0xee, 0x72 } };
