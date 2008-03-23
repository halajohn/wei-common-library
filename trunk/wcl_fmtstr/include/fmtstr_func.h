// wcl_fmtstr - portable printf-like library
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

#ifndef __fmtstr_func_h__
#define __fmtstr_func_h__

#include <cstdarg>

#include <list>
#include <string>

enum fmtstr_bool
{
  fmtstr_false = 0,
  fmtstr_true = 1
};
typedef enum fmtstr_bool fmtstr_bool;

#ifndef WIN32
#define __declspec(dllexport)
#endif

__declspec(dllexport) wchar_t *fmtstr_new_valist(
#if defined(_DEBUG)
  wchar_t const * const filename,
  size_t const line_no,
#endif
  wchar_t const *fmt, va_list *ap);
  
__declspec(dllexport) wchar_t *fmtstr_new(
#if defined(_DEBUG)
  wchar_t const * const filename,
  size_t const line_no,
#endif
  wchar_t const * fmt, ...);
  
__declspec(dllexport) wchar_t *fmtstr_append_valist(
#if defined(_DEBUG)
  wchar_t const * const filename,
  size_t const line_no,
#endif
  wchar_t *orig,
  wchar_t const * fmt,
  va_list *ap);
  
__declspec(dllexport) wchar_t *fmtstr_append(
#if defined(_DEBUG)
  wchar_t const * const filename,
  size_t const line_no,
#endif
  wchar_t * const orig,
  wchar_t const * fmt, ...);
  
__declspec(dllexport) char *fmtstr_wcstombs(
#if defined(_DEBUG)
  wchar_t const * const filename,
  size_t const line_no,
#endif
  wchar_t const * const ws,
  size_t const wscnt);
  
__declspec(dllexport) wchar_t *fmtstr_mbstowcs(
#if defined(_DEBUG)
  wchar_t const * const filename,
  size_t const line_no,
#endif
  char const * const s,
  size_t * const wscnt);
  
__declspec(dllexport) void fmtstr_delete(void * const str);
__declspec(dllexport) fmtstr_bool fmtstr_dump_unfreed();

__declspec(dllexport) void fmtstr_split_str_by_delimiter(
  wchar_t const * const str,
  wchar_t const * const delimiter,
  std::list<std::wstring> &splitted_str);

#endif
