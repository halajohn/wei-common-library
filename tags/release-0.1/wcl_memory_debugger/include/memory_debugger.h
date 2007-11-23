// wcl_memory_debugger - debug memory leak
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

#ifndef __compiler_memory_h__
#define __compiler_memory_h__

#ifdef _DEBUG

#include <cassert>
#include <cstdlib>

extern void add_memory_track(void * const addr,
                             size_t const asize,
                             wchar_t const * const fname,
                             size_t const lnum);
extern void remove_memory_track(void * const addr);
extern bool dump_unfreed();

#define WIDEN_(x) L##x
#define WIDEN(x)  WIDEN_(x)
#define __WFILE__ WIDEN(__FILE__)

inline void *
operator new(unsigned int size,
             wchar_t const * const file,
             size_t const line)
{
  void *ptr = (void *)malloc(size);
  assert(ptr != 0);
  add_memory_track(ptr, size, file, line);
  
  return ptr;
};

inline void
operator delete(void *p)
{
  if (0 == p)
  {
    return;
  }

  remove_memory_track(p);
  
  free(p);
};

inline void
operator delete(void *p,
                wchar_t const * const /* file */,
                size_t const /* line */)
{
  assert(p != 0);
  
  remove_memory_track(p);
  
  free(p);
};

#define DEBUG_NEW new(__WFILE__, __LINE__)

#else // _DEBUG

#define DEBUG_NEW new

#endif // _DEBUG

#define new DEBUG_NEW

#endif
