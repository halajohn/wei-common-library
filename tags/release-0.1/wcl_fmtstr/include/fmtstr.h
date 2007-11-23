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

#ifndef __fmtstr_h__
#define __fmtstr_h__

#define WIDEN_(x) L##x
#define WIDEN(x)  WIDEN_(x)
#define __WFILE__ WIDEN(__FILE__)

#include "fmtstr_func.h"

#if defined(_DEBUG)

#define fmtstr_new_DEBUG(fmt, ...)                                \
  fmtstr_new(__WFILE__, __LINE__, (fmt), __VA_ARGS__)
  
#define fmtstr_new_valist_DEBUG(fmt, ap)                              \
  fmtstr_new_valist(__WFILE__, __LINE__, (fmt), (ap))
  
#define fmtstr_append_DEBUG(orig, fmt, ...)                           \
  fmtstr_append(__WFILE__, __LINE__, (orig), (fmt), __VA_ARGS__)
  
#define fmtstr_append_valist_DEBUG(orig, fmt, ap)                     \
  fmtstr_append_valist(__WFILE__, __LINE__, (orig), (fmt), (ap))
  
#define fmtstr_wcstombs_DEBUG(ws, wscnt)                              \
  fmtstr_wcstombs(__WFILE__, __LINE__, (ws), (wscnt))

#define fmtstr_mbstowcs_DEBUG(s, wscnt)                               \
  fmtstr_mbstowcs(__WFILE__, __LINE__, (s), (wscnt))

#else /* #if defined(_DEBUG) */

#define fmtstr_new_DEBUG(fmt, ...)                        \
  fmtstr_new((fmt), __VA_ARGS__)
  
#define fmtstr_new_valist_DEBUG(fmt, ap)                              \
  fmtstr_new_valist((fmt), (ap))
  
#define fmtstr_append_DEBUG(orig, fmt, ...)                           \
  fmtstr_append((orig), (fmt), __VA_ARGS__)
  
#define fmtstr_append_valist_DEBUG(orig, fmt, ap)                       \
  fmtstr_append_valist((orig), (fmt), (ap))
  
#define fmtstr_wcstombs_DEBUG(ws, wscnt)                              \
  fmtstr_wcstombs((ws), (wscnt))
  
#define fmtstr_mbstowcs_DEBUG(s, wscnt)                               \
  fmtstr_mbstowcs((s), (wscnt))
  
#endif /* #if defined(_DEBUG) */

#define fmtstr_new(fmt, ...) fmtstr_new_DEBUG((fmt), __VA_ARGS__)
#define fmtstr_new_valist(fmt, ap) fmtstr_new_valist_DEBUG((fmt), (ap))
#define fmtstr_append(orig, fmt, ...) fmtstr_append_DEBUG((orig), (fmt), __VA_ARGS__)
#define fmtstr_append_valist(orig, fmt, ap) fmtstr_append_valist_DEBUG((orig), (fmt), (ap))
#define fmtstr_wcstombs(ws, wscnt) fmtstr_wcstombs_DEBUG((ws), (wscnt))
#define fmtstr_mbstowcs(s, wscnt) fmtstr_mbstowcs_DEBUG((s), (wscnt))

#endif
