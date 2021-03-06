// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"

#include <ctype.h>
#include <wininet.h>
#include <winver.h>

#include <cstddef>

#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>
#include <type_traits>
#include <iostream>
#include <iterator>
#include <vector>

#ifndef MAX_URL
 #define MAX_URL 2083
#endif

CString EncodeURL(CString url);
CString DecodeURL(CString url);

char from_hex(char ch);
std::string url_encode(const std::string& value);
std::string url_decode(std::string text);

char* AnsiToUtf8(const char* pszCode);
char* Utf8ToAnsi(const char* pszCode);

#endif //PCH_H
