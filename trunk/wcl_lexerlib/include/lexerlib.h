// wcl_lexerlib - common lexer operation library
// Copyright (C) <2007>  Wei Hu <wei.hu.tw@gmail.com>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef __StreamHandler_h__
#define __StreamHandler_h__

#include <cstddef>
#include <fstream>
#include <list>

__declspec(dllexport) extern void lexerlib_put_back(std::wfstream &file, wchar_t const ch);
__declspec(dllexport) extern void lexerlib_put_back(std::wstring &str, wchar_t const ch);
__declspec(dllexport) extern bool lexerlib_read_ch(std::wfstream &file, wchar_t * const ch);
__declspec(dllexport) extern void lexerlib_put_back(std::wfstream &file,
                                                    std::wstring const * const str);
__declspec(dllexport) extern bool lexerlib_read_ch(std::wstring &str, wchar_t * const ch);

#endif
