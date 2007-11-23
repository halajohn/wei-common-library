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

#include <cassert>

#include <list>
#include <iostream>

#pragma warning(disable:4819)
#include <boost/smart_ptr.hpp>

#include "../../wcl_fmtstr/include/fmtstr.h"

class alloc_info_t
{
private:
  
  void * const m_address;
  size_t const m_size;
  wchar_t const * const m_filename;
  size_t const m_line;
  
public:
  
  alloc_info_t(void * const addr,
               size_t const size,
               wchar_t const * const filename,
               size_t const line)
    : m_address(addr),
      m_size(size),
      m_filename(filename),
      m_line(line)
  { }
  
  void *address() const { return m_address; }
  size_t size() const { return m_size; }
  wchar_t const *filename() { return m_filename; }
  size_t line() const { return m_line; }
};
typedef class alloc_info_t alloc_info_t;

typedef std::list<boost::shared_ptr<alloc_info_t> > alloc_list_t;

namespace
{
  alloc_list_t alloc_list;
}

__declspec(dllexport)
void
add_memory_track(void * const addr,
                 size_t const asize,
                 wchar_t const * const fname,
                 size_t const lnum)
{
  alloc_list.insert(
    alloc_list.begin(),
    boost::shared_ptr<alloc_info_t>(
      new alloc_info_t(addr, asize, fname, lnum)));
}

__declspec(dllexport)
void
remove_memory_track(void * const addr)
{
  for (alloc_list_t::iterator i = alloc_list.begin();
       i != alloc_list.end();
       ++i)
  {
    if ((*i)->address() == addr)
    {
      alloc_list.remove(*i);
      break;
    }
  }
}

__declspec(dllexport)
bool
dump_unfreed()
{
  size_t totalSize = 0;
  
  for (alloc_list_t::const_iterator i = alloc_list.begin();
       i != alloc_list.end();
       ++i)
  {
    boost::shared_ptr<wchar_t> str(
      fmtstr_new(L"%s: LINE %d, ADDRESS %d, %d unfreed\n",
                 (*i)->filename(),
                 (*i)->line(),
                 (*i)->address(),
                 (*i)->size()), fmtstr_delete);
    
    totalSize += (*i)->size();
    std::wcout << str;
  }
  
  std::wcout << L"-----------------------------------------------------------\n";
  boost::shared_ptr<wchar_t> str(
    fmtstr_new(L"Total Unfreed: %d bytes\n", totalSize), fmtstr_delete);
  std::wcout << str;
  
  if (totalSize != 0)
  {
    return false;
  }
  else
  {
    return true;
  }
}
