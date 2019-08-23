// pch.cpp: source file corresponding to the pre-compiled header

#include "pch.h"

// When you are using pre-compiled headers, this source file is necessary for compilation to succeed.

CString EncodeURL(CString url)
{
	CString ret;
	std::string srcString;

#ifdef _UNICODE
	{
		wchar_t strUnicode[MAX_URL * 2] = { 0, };
		char strMultibyte[MAX_URL * 2] = { 0, };
		wcscpy_s(strUnicode, MAX_URL, url.GetBuffer(url.GetLength()));
		int len = WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, strMultibyte, len, NULL, NULL);
		srcString = strMultibyte;
	}
#else
	srcString = url.GetBuffer(url.GetLength());
#endif

	// 한글 인코딩
	char* szHangul = AnsiToUtf8( srcString.c_str() );

	// URL 인코딩 
	std::string encodedString = url_encode( std::string(szHangul) );

#ifdef _UNICODE
	{
		wchar_t strUnicode[MAX_URL * 2] = { 0, };
		char strMultibyte[MAX_URL * 2] = { 0, };
		strcpy_s(strMultibyte, MAX_URL, encodedString.c_str());
		int nLen = MultiByteToWideChar(CP_ACP, 0, strMultibyte, strlen(strMultibyte), NULL, NULL);
		MultiByteToWideChar(CP_ACP, 0, strMultibyte, strlen(strMultibyte), strUnicode, nLen);
		ret = strUnicode;
	}
#else
	ret = encodedString.c_str();
#endif

	return ret; 
}

CString DecodeURL(CString url)
{
	CString ret;
	std::string srcString;

#ifdef _UNICODE
	{
		wchar_t strUnicode[MAX_URL * 2] = { 0, };
		char strMultibyte[MAX_URL * 2] = { 0, };
		wcscpy_s(strUnicode, MAX_URL, url.GetBuffer(url.GetLength()));
		int len = WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, strMultibyte, len, NULL, NULL);
		srcString = strMultibyte;
	}
#else
	srcString = url.GetBuffer(url.GetLength());
#endif

	// URL 디코딩
	std::string urlEncodedString = url_decode( srcString );

	// 한글 디코딩
	char* szHangul = Utf8ToAnsi( urlEncodedString.c_str() );
	std::string encodedString = std::string(szHangul);

#ifdef _UNICODE
	{
		wchar_t strUnicode[MAX_URL * 2] = { 0, };
		char strMultibyte[MAX_URL * 2] = { 0, };
		strcpy_s(strMultibyte, MAX_URL, encodedString.c_str());
		int nLen = MultiByteToWideChar(CP_ACP, 0, strMultibyte, strlen(strMultibyte), NULL, NULL);
		MultiByteToWideChar(CP_ACP, 0, strMultibyte, strlen(strMultibyte), strUnicode, nLen);
		ret = strUnicode;
	}
#else
	ret = encodedString.c_str();
#endif

	return ret;
}


std::string url_encode(const std::string& value)
{
	std::ostringstream escaped;
	escaped.fill('0');
	escaped << std::hex;

	for (std::string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) 
	{
		// std::string::value_type c = (*i);
		unsigned char c = (*i);

		unsigned char c1 = '-';
		unsigned char c2 = '_';
		unsigned char c3 = '.';
		unsigned char c4 = '~';

		// Keep alphanumeric and other accepted characters intact
		if ( isalnum( c ) ||
            c == c1 ||
			c == c2 ||
			c == c3 ||
			c == c4 )
		{
			escaped << c;
			continue;
		}

		// Any other characters are percent-encoded
		escaped << std::uppercase;
		escaped << '%' << std::setw(2) << int((unsigned char)c);
		escaped << std::nouppercase;
	}

	return escaped.str();
}

char from_hex(char ch) 
{
	return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
}

std::string url_decode(std::string text)
{
	char h;
	std::ostringstream escaped;
	escaped.fill('0');

	for (std::string::iterator i = text.begin(), n = text.end(); i != n; ++i) 
	{
		std::string::value_type c = (*i);

		if (c == '%')
		{
			std::string::iterator nx1 = std::next(i, 1);
			if ( nx1 != text.end() )
			{
				std::string::iterator nx2 = std::next(i, 2);
				if ( nx2 != text.end() )
				{
					if (i[1] && i[2])
					{
						h = from_hex(i[1]) << 4 | from_hex(i[2]);
						escaped << h;
						i += 2;
					}
				}
				else
				{
					// nx2 is end
					escaped << '%';
					// escaped << i[1];
				}
			}
			else
			{
				// nx1 is end
				escaped << '%';
			}
		}
		else if (c == '+') 
		{
			escaped << ' ';
		}
		else 
		{
			escaped << c;
		}
	}

	return escaped.str();
}

char* AnsiToUtf8(const char* pszCode)
{
	int nLength = 0;
	int nLength2 = 0;
	BSTR bstrCode;
	char* pszUTFCode = NULL;

	nLength = MultiByteToWideChar(CP_ACP, 0, pszCode, strlen(pszCode), NULL, NULL);
	bstrCode = SysAllocStringLen(NULL, nLength);
	MultiByteToWideChar(CP_ACP, 0, pszCode, strlen(pszCode), bstrCode, nLength);

	nLength2 = WideCharToMultiByte(CP_UTF8, 0, bstrCode, -1, pszUTFCode, 0, NULL, NULL);
	pszUTFCode = (char*)malloc(nLength2 + 1);
	WideCharToMultiByte(CP_UTF8, 0, bstrCode, -1, pszUTFCode, nLength2, NULL, NULL);

	return pszUTFCode;
}

char* Utf8ToAnsi(const char* pszCode)
{
	BSTR bstrWide;
	char* pszAnsi = NULL;
	int nLength = 0;

	nLength = MultiByteToWideChar(CP_UTF8, 0, pszCode, strlen(pszCode) + 1, NULL, NULL);
	bstrWide = SysAllocStringLen(NULL, nLength);

	MultiByteToWideChar(CP_UTF8, 0, pszCode, strlen(pszCode) + 1, bstrWide, nLength);

	nLength = WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, NULL, 0, NULL, NULL);
	pszAnsi = new char[nLength];

	WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, pszAnsi, nLength, NULL, NULL);
	SysFreeString(bstrWide);

	return pszAnsi;
}

