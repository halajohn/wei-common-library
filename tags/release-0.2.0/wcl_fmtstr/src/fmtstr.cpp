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

#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cwchar>

#pragma warning(disable: 4819)
#include <boost/cast.hpp>

#include "fmtstr_func.h"
#include "fmtstr_internal.h"

#if defined(_DEBUG)
static fmtstr_debug_entry_t *gp_fmtstr_debug_entry_list = NULL;

static void
debug_add_fmtstr(
  wchar_t const * const filename,
  size_t const line_no,
  void * const address,
  size_t const alloc_size)
{
  fmtstr_debug_entry_t * const rem =
    (fmtstr_debug_entry_t *)malloc(sizeof(fmtstr_debug_entry_t));
  assert(rem != NULL);
  
  rem->filename = filename;
  rem->line_no = line_no;
  rem->address = address;
  rem->alloc_size = alloc_size;
  rem->prev = NULL;
  
  if (gp_fmtstr_debug_entry_list != NULL)
  {
    rem->next = gp_fmtstr_debug_entry_list;
  }
  else
  {
    rem->next = NULL;
  }
  gp_fmtstr_debug_entry_list = rem;
}

static fmtstr_bool
debug_find_fmtstr(void * const str)
{
  fmtstr_debug_entry_t *rem = gp_fmtstr_debug_entry_list;
  
  while (rem != NULL)
  {
    if (rem->address == str)
    {
      return fmtstr_true;
    }
    rem = rem->next;
  }
  assert(0);
  return fmtstr_false;
}

static void
debug_delete_fmtstr(void * const str)
{
  fmtstr_debug_entry_t *rem = gp_fmtstr_debug_entry_list;
  
  while (rem != NULL)
  {
    if (rem->address == str)
    {
      if (rem->prev != NULL)
      {
        rem->prev->next = rem->next;
      }
      if (rem->next != NULL)
      {
        rem->next->prev = rem->prev;
      }
      if (rem == gp_fmtstr_debug_entry_list)
      {
        gp_fmtstr_debug_entry_list = rem->next;
      }
      free(rem);
      return;
    }
    rem = rem->next;
  }
  assert(0);
}

fmtstr_bool
fmtstr_dump_unfreed()
{
  size_t totalSize = 0;
  fmtstr_debug_entry_t *rem = gp_fmtstr_debug_entry_list;
  
  while (rem != NULL)
  {
    fwprintf(stderr,
             L"%s: LINE %d, ADDRESS %p, %d unfreed\n",
             rem->filename,
             rem->line_no,
             rem->address,
             rem->alloc_size);
    
    totalSize += rem->alloc_size;
    
    rem = rem->next;
  }
  
  fwprintf(stderr, L"-----------------------------------------------------------\n");
  fwprintf(stderr, L"Total fmtstr Unfreed: %d bytes\n", totalSize);
  
  if (totalSize != 0)
  {
    return fmtstr_false;
  }
  else
  {
    return fmtstr_true;
  }
}
#endif

#if !defined(_DEBUG)
#define debug_add_fmtstr(a, b, c, d)
#define debug_find_fmtstr(a)
#define debug_delete_fmtstr(a)
#endif

// I use do {} while(-1 == __LINE__) rather than do {} while(0)
// to avoid Visual C++ complains:
//
// warning C4127: conditional expression is constant
#define ALLOC_NEW_SPACE(str1, str_length, enlarge_size)                 \
  do {                                                                  \
    wchar_t *str2 = (wchar_t *)calloc(1, sizeof(wchar_t) * (alloc_size + enlarge_size)); \
    errno_t error;                                                      \
    error = wcscpy_s(str2, alloc_size + enlarge_size, str1);            \
    alloc_size += enlarge_size;                                         \
    assert(0 == error);                                                 \
    fmtstr_delete(str1);                                                \
    str1 = str2;                                                        \
    str = str1 + str_length;                                            \
    debug_add_fmtstr(filename, line_no, (void *)str1, sizeof(wchar_t) * alloc_size); \
  } while(-1 == __LINE__)

static wchar_t *
create_fmt(wchar_t const * const fmt_before_length_str,
           wchar_t const * const min_output_length_buf,
           wchar_t const * const fmt_after_length_str)
{
  wchar_t *fmt_str;
  size_t const dest_str_size = wcslen(min_output_length_buf)
    + 1 /* null terminator */
    + wcslen(fmt_before_length_str)
    + wcslen(fmt_after_length_str);
  errno_t success;
  
  fmt_str = (wchar_t *)malloc(sizeof(wchar_t) * dest_str_size);
  assert(fmt_str != NULL);
  
  success = wcscpy_s(fmt_str, dest_str_size, fmt_before_length_str);
  assert(0 == success);
  
  success = wcscat_s(fmt_str, dest_str_size, min_output_length_buf);
  assert(0 == success);
  
  success = wcscat_s(fmt_str, dest_str_size, fmt_after_length_str);
  assert(0 == success);
  
  return fmt_str;
}

wchar_t *
fmtstr_append_valist(
#if defined(_DEBUG)
  wchar_t const * const filename,
  size_t const line_no,
#endif
  wchar_t *orig,
  wchar_t const * fmt,
  va_list *ap)
{
  double f;
  int d;
  wchar_t *s;
  wchar_t c;
  int state = 0;
  wchar_t *str;
  wchar_t *str_head;
  size_t str_length = 0;
  size_t alloc_size;
  fmtstr_bool realloc = fmtstr_false;
  
  int min_output_length = 0;
  fmtstr_bool min_output_length_overflow;
  
  int min_output_length_buf_index = 0;
  wchar_t min_output_length_buf[MIN_OUTPUT_LENGTH_BUF_SIZE];
  
  wchar_t *fmt_str;
  
  /* STRBUF_ENLARGE_SIZE should be >= 1 */
  assert(STRBUF_ENLARGE_SIZE >= 1);
  /* RED_ZONE_SIZE should be smallar than STRBUF_ENLARGE_SIZE */
  assert(RED_ZONE_SIZE < STRBUF_ENLARGE_SIZE);
  
  if (NULL == orig)
  {
    alloc_size = STRBUF_ENLARGE_SIZE;
    realloc = fmtstr_true;
  }
  else
  {
    size_t const multiple = (wcslen(orig) / STRBUF_ENLARGE_SIZE) + 1;
    size_t const prev_alloc_size = STRBUF_ENLARGE_SIZE * multiple;
    assert(prev_alloc_size >= (wcslen(orig) + 1));
    
    if (1 == (prev_alloc_size - wcslen(orig)))
    {
      alloc_size = prev_alloc_size + STRBUF_ENLARGE_SIZE;
      realloc = fmtstr_true;
    }
    else
    {
      alloc_size = prev_alloc_size;
    }
  }
  
  if (fmtstr_true == realloc)
  {
    str = (wchar_t *)calloc(1, sizeof(wchar_t) * alloc_size);
    str_head = str;
    if (orig != NULL)
    {
      wcscpy_s(str, alloc_size, orig);
      str = str + wcslen(orig);
      fmtstr_delete(orig);
    }
    
    debug_add_fmtstr(filename,
                     line_no,
                     (void *)str,
                     sizeof(wchar_t) * alloc_size);
  }
  else
  {
    str = orig + wcslen(orig);
    str_head = orig;
    str_length = wcslen(orig);
  }
  
  while (*fmt)
  {
    if (0 == state)
    {
      if (L'%' == *fmt)
      {
        state = 1;
        
        min_output_length = 0;
        min_output_length_overflow = fmtstr_false;
        
        min_output_length_buf_index = 0;
        memset(min_output_length_buf, 0, sizeof(wchar_t) * MIN_OUTPUT_LENGTH_BUF_SIZE);
        
        fmt_str = NULL;
      }
      else
      {
        str_length += (size_t)swprintf_s(str, alloc_size - str_length, L"%c", *fmt);
      }
    }
    else
    {
      switch (*fmt)
      {
      case L'0':
      case L'1':
      case L'2':
      case L'3':
      case L'4':
      case L'5':
      case L'6':
      case L'7':
      case L'8':
      case L'9':
        if (min_output_length < (0xFFFFFFFF / 10))
        {
          min_output_length *= 10;
          min_output_length += (*fmt - '0');
          
          min_output_length_buf[min_output_length_buf_index] = *fmt;
          ++min_output_length_buf_index;
          assert(min_output_length_buf_index != MIN_OUTPUT_LENGTH_BUF_SIZE);
        }
        else
        {
          min_output_length_overflow = fmtstr_true;
          min_output_length = 0xFFFFFFFF;
        }
      break;
      
      case L'd':
        fmt_str = create_fmt(L"%", min_output_length_buf, L"d");
      
      d = va_arg(*ap, int);
      str_length += (size_t)swprintf_s(str, alloc_size - str_length, fmt_str, d);
        
      free(fmt_str);
      fmt_str = NULL;
      state = 0;
      break;
      
      case L'x':
        fmt_str = create_fmt(L"0x%", min_output_length_buf, L"x");
        
      d = va_arg(*ap, int);
      str_length += (size_t)swprintf_s(str, alloc_size - str_length, fmt_str, d);
        
      free(fmt_str);
      fmt_str = NULL;
      state = 0;
      break;
        
      case L'f':
        fmt_str = create_fmt(L"%", min_output_length_buf, L"f");
        
      f = va_arg(*ap, double);
      str_length += (size_t)swprintf_s(str, alloc_size - str_length, fmt_str, f);
        
      free(fmt_str);
      fmt_str = NULL;
      state = 0;
      break;
        
      case L's':
        s = va_arg(*ap, wchar_t *);
      if (s != NULL)
      {
        if ((wcslen(s) + 1) > (alloc_size - str_length))
        {
          ALLOC_NEW_SPACE(str_head, str_length, (int)wcslen(s) + STRBUF_ENLARGE_SIZE);
        }
          
        fmt_str = create_fmt(L"%", min_output_length_buf, L"s");
          
        str_length += (size_t)swprintf_s(str, alloc_size - str_length, fmt_str, s);
          
        free(fmt_str);
        fmt_str = NULL;
      }
      state = 0;
      break;
      
      case L'c':
        /* This should be va_arg(*ap, char);
         * however, `char' is promoted to `int' when passed through `...'
         */
        fmt_str = create_fmt(L"%", min_output_length_buf, L"c");
      
      {
        int const tmp_c = va_arg(*ap, int);
        
        c = boost::numeric_cast<wchar_t>(tmp_c);
      }
      str_length += (size_t)swprintf_s(str, alloc_size - str_length, fmt_str, c);
      
      free(fmt_str);
      fmt_str = NULL;
      state = 0;
      break;
        
      default:
        /* Not a format character, then output it directly. */
        fmt_str = create_fmt(L"%", min_output_length_buf, L"c");
        
        str_length += (size_t)swprintf_s(str, alloc_size - str_length, fmt_str, *fmt);
        
        free(fmt_str);
        fmt_str = NULL;
        state = 0;
        break;
      }
    }
    
    str = str_head + str_length;
    
    if (str_length >= alloc_size - RED_ZONE_SIZE)
    {
      ALLOC_NEW_SPACE(str_head, str_length, STRBUF_ENLARGE_SIZE);
    }
    
    ++fmt;
  }
  
  return str_head;
}

wchar_t *
fmtstr_new_valist(
#if defined(_DEBUG)
  wchar_t const * const filename,
  size_t const line_no,
#endif
  wchar_t const *fmt, va_list *ap)
{
  return fmtstr_append_valist(
#if defined(_DEBUG)
    filename, line_no,
#endif
    NULL, fmt, ap);
}

wchar_t *
fmtstr_new(
#if defined(_DEBUG)
  wchar_t const * const filename,
  size_t const line_no,
#endif  
  wchar_t const * fmt, ...)
{
  va_list ap;
  wchar_t *str;
  
  va_start(ap, fmt);
  str = fmtstr_new_valist(
#if defined(_DEBUG)
    filename, line_no,
#endif
    fmt, &ap);
  va_end(ap);
  
  return str;
}

wchar_t *
fmtstr_append(
#if defined(_DEBUG)
  wchar_t const * const filename,
  size_t const line_no,
#endif  
  wchar_t * const orig, wchar_t const * fmt, ...)
{
  va_list ap;
  wchar_t *str;
  
  va_start(ap, fmt);
  str = fmtstr_append_valist(
#if defined(_DEBUG)
    filename, line_no,
#endif
    orig, fmt, &ap);
  va_end(ap);
  
  return str;
}

void
fmtstr_delete(void * const str)
{
  if (0 == str)
  {
    return;
  }
  
  assert(fmtstr_true == debug_find_fmtstr(str));
  debug_delete_fmtstr(str);
  
  free(str);
}

char *
fmtstr_wcstombs(
#if defined(_DEBUG)
  wchar_t const * const filename,
  size_t const line_no,
#endif  
  wchar_t const * const ws, size_t const wscnt)
{
  char *s;
  size_t slen;
  size_t wcnt;
  
  slen = MB_CUR_MAX * wscnt + 1;
  s = static_cast<char *>(malloc(sizeof(char) * slen));
  assert(s != NULL);
  
  debug_add_fmtstr(filename, line_no, (void *)s, sizeof(char) * slen);
  
  if (wcstombs_s(&wcnt, s, slen, ws, slen) != 0)
  {
    free(s);
    return NULL;
  }
  
  return s;
}

wchar_t *
fmtstr_mbstowcs(
#if defined(_DEBUG)
  wchar_t const * const filename,
  size_t const line_no,
#endif  
  char const * const s, size_t * const wscnt)
{
  wchar_t *ws;
  size_t wslen;
  size_t wcnt;
  
  wslen = strlen(s) + 1;
  ws = static_cast<wchar_t *>(malloc(sizeof(wchar_t) * wslen));
  assert(ws != NULL);
  
  debug_add_fmtstr(filename, line_no, (void *)ws, sizeof(wchar_t) * wslen);
  
  if ((mbstowcs_s(&wcnt, ws, wslen, s, wslen)) != 0)
  {
    free(ws);
    return NULL;
  }
  
  if (wscnt != NULL)
  {
    *wscnt = wcnt;
  }
  
  return ws;
}

void
fmtstr_split_str_by_delimiter(
  wchar_t const * const str,
  wchar_t const * const delimiter,
  std::list<std::wstring> &splitted_str)
{
  splitted_str.clear();
  
  if (0 == str)
  {
    return;
  }
  
  if (0 == delimiter)
  {
    splitted_str.push_back(str);
    
    return;
  }
  
  wchar_t const *curr = str;
  wchar_t const *prev = str;
  
  for (;;)
  {
    curr = wcsstr(prev, delimiter);
    
    if (curr != 0)
    {
      splitted_str.push_back(std::wstring(prev, curr - prev));
      prev = curr + 2;
    }
    else
    {
      splitted_str.push_back(std::wstring(prev, wcslen(str) - (prev - str)));
      break;
    }
  }
}
