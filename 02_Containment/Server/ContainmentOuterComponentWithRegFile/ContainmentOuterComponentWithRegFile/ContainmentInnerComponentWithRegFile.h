class IMultiplication:public IUnknown
{
    public:
        virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int,int,int *)=0;
};

class IDivision:public IUnknown
{
    public:
        virtual HRESULT __stdcall DivisionOfTwoIntegers(int,int,int *)=0;
};
const CLSID CLSID_MultiplicationDivision=
	{ 0x38b0f6b0, 0x6268, 0x4dc8, { 0xa6, 0x4a, 0x5, 0x16, 0xa4, 0x60, 0x75, 0xc7 }};

const IID IID_IMultiplication= 
	{ 0x466ac99f, 0x6c88, 0x4250, { 0xbd, 0xfa, 0x12, 0xf5, 0x32, 0x17, 0xa6, 0x48 }};

const IID IID_IDivision= 
	{ 0x45d177b8, 0xd6b5, 0x4460, { 0xb4, 0xe5, 0x7c, 0x88, 0xa2, 0x79, 0x78, 0xa8 }};
// {466AC99F-6C88-4250-BDFA-12F53217A648}
// {45D177B8-D6B5-4460-B4E5-7C88A27978A8}
