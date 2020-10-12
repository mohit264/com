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
	{ 0x1a65bcac, 0xb02e, 0x4b1c, { 0xae, 0x2e, 0x80, 0x29, 0xea, 0x55, 0x7, 0x32 }};
const IID IID_ISum= 
	{ 0x6a99c868, 0xcb7a, 0x4488, { 0xa0, 0xe6, 0xcd, 0xd8, 0x87, 0xc3, 0xd5, 0x81 }};

const IID IID_ISubtract= 
	{ 0x7ebcb275, 0xd227, 0x46ff, { 0xa9, 0xd0, 0x82, 0x1c, 0x73, 0x15, 0xf0, 0xcd }};
// {}
// {6A99C868-CB7A-4488-A0E6-CDD887C3D581}
// {7EBCB275-D227-46FF-A9D0-821C7315F0CD}

