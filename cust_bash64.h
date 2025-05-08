#ifndef CORE_LIBRARY_H
#define CORE_LIBRARY_H
#include <cassert>
#include <cstring>
#include  <cstdlib>
#include <cwchar>
#include <iostream>
#define LIB_EXPORTS 1
#define SafeDeleteArray(pData) { try { delete [] pData; } catch (...) { assert(false); } pData=NULL; }
#include "platform_export.h"

const wchar_t CHAR_63 = '+';
const wchar_t CHAR_64 = '/';
const wchar_t CHAR_PAD = '=';
const wchar_t alph[] =
{
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
    '0','1','2','3','4','5','6','7','8','9',CHAR_63,CHAR_64
};
union unBuffer
{
    unsigned char bytes[ 4 ];
    unsigned int block;
};

class LIB_API CCustBase64
{
public:
    CCustBase64();
    virtual ~CCustBase64();
    static void Encode1(){std::cout<<"===>Test Export Function Encode1 from CCustBase64 to .so for C# call it"<<std::endl;};
    static int Encode(const char * pData, int nDataLen, wchar_t szOutBuffer[], int nBufferLen);
    static int Decode(const wchar_t * pszCode, int nCodeLength,wchar_t szOutBuffer[], int nBufferLen);

};

#ifdef __cplusplus
extern "C" {
#endif
    void Test();
    char* w2c(const wchar_t* wc) {
        std::cout<<"===>Test Export Function w2c to .so for C# call it"<<std::endl;
        char* buf{nullptr};
        if (const size_t len = wcslen(wc) + 1; len>0) {
            buf = static_cast<char *>(malloc(len * sizeof(char)));
            memset(buf, 0, len);
            wcstombs(buf,wc,len);
        }
        return buf;
    }
    inline CCustBase64* createObject(){return new CCustBase64();}

    void CCustBase64_Encode1() {
        CCustBase64::Encode1();
    };
    int CCustBase64_Encode(const char * pData, int nDataLen, wchar_t szOutBuffer[], int nBufferLen) {
       return CCustBase64::Encode(pData,nDataLen,szOutBuffer,nBufferLen);
    };
#ifdef __cplusplus
}
#endif



#endif //CORE_LIBRARY_H