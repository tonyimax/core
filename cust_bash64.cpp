#include "cust_bash64.h"


inline int GetDataLength(int nCodeLength)
{
	return nCodeLength-nCodeLength/4;
}

inline int GetCodeLength(int nDataLength)
{
	int len=nDataLength+nDataLength/3 + (int)(nDataLength%3!=0);
	if (len % 4) len += 4-len%4;
	return len;
}


CCustBase64::CCustBase64()
{
}

CCustBase64::~CCustBase64()
{
}

int CCustBase64::Encode(const char * pData, int nDataLen, wchar_t szOutBuffer[], int nBufferLen)
{
	int len = GetCodeLength(nDataLen);
	wchar_t* out = new wchar_t[len];

	unBuffer buffer;
	const int mask = 0x3F;

	for (int i = 0, j = 0, left = nDataLen; i < nDataLen; i += 3, j += 4, left -= 3)
	{
		buffer.bytes[2]=pData[i];

		if (left > 1)
		{
			buffer.bytes[ 1 ] = pData[ i + 1 ];
			if( left > 2 )
				buffer.bytes[ 0 ] = pData[ i + 2 ];
			else
				buffer.bytes[ 0 ] = 0;
		}
		else
		{
			buffer.bytes[ 1 ] = 0;
			buffer.bytes[ 0 ] = 0;
		}

		out[ j ] = alph[ ( buffer.block >> 18 ) & mask ];
		out[ j + 1 ] = alph[ ( buffer.block >> 12 ) & mask ];
		if( left > 1 )
		{
			out[ j + 2 ] = alph[ ( buffer.block >> 6 ) & mask ];
			if ( left > 2 )
				out[ j + 3 ] = alph[ buffer.block & mask ];
			else
				out[ j + 3 ] = CHAR_PAD;
		}
		else
		{
			out[ j + 2 ] = CHAR_PAD;
			out[ j + 3 ] = CHAR_PAD;
		}
	}
	memcpy(szOutBuffer, out,len*sizeof(wchar_t));
	szOutBuffer[len] = 0;
	SafeDeleteArray(out);
	return len;
}


int CCustBase64::Decode(const wchar_t * pszCode, int nCodeLength, wchar_t szOutBuffer[], int nBufferLen)
{
	unBuffer buffer;
	buffer.block = 0;
	wchar_t * pOutData = new wchar_t[nBufferLen];
	printf("===> pszCode: %ls  nCodeLength: %d\n",pszCode,nCodeLength);
	int j = 0;
	for (int i = 0; i < nCodeLength; i++)
	{
		int val = 0;
		int m = i % 4;
		wchar_t x = pszCode[i];

		if( x >= 'A' && x <= 'Z' )
			val = x - 'A';
		else if( x >= 'a' && x <= 'z' )
			val = x - 'a' + 'Z' - 'A' + 1;
		else if( x >= '0' && x <= '9' )
			val = x - '0' + ( 'Z' - 'A' + 1 ) * 2;
		else if( x == CHAR_63 )
			val = 62;
		else if( x == CHAR_64 )
			val = 63;

		if( x != CHAR_PAD )
			buffer.block |= val << ( 3 - m ) * 6;
		else
			m--;

		if (m == 3 || x == CHAR_PAD)
		{
			pOutData[ j++ ] = buffer.bytes[2];
			if ( x != CHAR_PAD || m > 1 )
			{
				pOutData[ j++ ] = buffer.bytes[ 1 ];
				if( x != CHAR_PAD || m > 2 ) pOutData[ j++ ] = buffer.bytes[ 0 ];
			}

			buffer.block = 0;
		}

		if (x == CHAR_PAD) break;
		if (j == nBufferLen) break;
	}
	pOutData[j]=0;
	memcpy(szOutBuffer, pOutData,nBufferLen*sizeof(wchar_t));
	SafeDeleteArray(pOutData);
	return j;
}

int CCustBase64::Decode_CS(const char * pszCode, int nCodeLength, wchar_t szOutBuffer[], int nBufferLen)
{
	unBuffer buffer;
	buffer.block = 0;
	wchar_t * pOutData = new wchar_t[nBufferLen];
	printf("===> pszCode: %ls  nCodeLength: %d\n",pszCode,nCodeLength);
	int j = 0;
	for (int i = 0; i < nCodeLength; i++)
	{
		int val = 0;
		int m = i % 4;
		wchar_t x = pszCode[i];

		if( x >= 'A' && x <= 'Z' )
			val = x - 'A';
		else if( x >= 'a' && x <= 'z' )
			val = x - 'a' + 'Z' - 'A' + 1;
		else if( x >= '0' && x <= '9' )
			val = x - '0' + ( 'Z' - 'A' + 1 ) * 2;
		else if( x == CHAR_63 )
			val = 62;
		else if( x == CHAR_64 )
			val = 63;

		if( x != CHAR_PAD )
			buffer.block |= val << ( 3 - m ) * 6;
		else
			m--;

		if (m == 3 || x == CHAR_PAD)
		{
			pOutData[ j++ ] = buffer.bytes[2];
			if ( x != CHAR_PAD || m > 1 )
			{
				pOutData[ j++ ] = buffer.bytes[ 1 ];
				if( x != CHAR_PAD || m > 2 ) pOutData[ j++ ] = buffer.bytes[ 0 ];
			}

			buffer.block = 0;
		}

		if (x == CHAR_PAD) break;
		if (j == nBufferLen) break;
	}
	pOutData[j]=0;
	memcpy(szOutBuffer, pOutData,nBufferLen*sizeof(wchar_t));
	SafeDeleteArray(pOutData);
	return j;
}

void Test() {
	std::cout<<"===>Test Export Function Test to .so for C# call it"<<std::endl;
}
