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

#include <cassert>
#include <deque>
#include <boost/foreach.hpp>

#include "lexerlib.h"

namespace Wcl
{
  namespace Lexerlib
  {
    namespace
    {
      /** @var putback_buf
       *
       * implement a putback_buf to simulate putting
       * back to a file as to a string.
       */
      std::deque<wchar_t> putback_buf;
    }

    void
    put_back(std::wfstream &/* file */, wchar_t const ch)
    {
      putback_buf.push_front(ch);
    }

    void
    put_back(std::wfstream &/* file */,
             std::wstring const &str)
    {
      for (std::wstring::const_reverse_iterator iter = str.rbegin();
           iter != str.rend();
           ++iter)
      {
        putback_buf.push_front(*iter);
      }
    }
    
    void
    put_back(std::wstring &str, wchar_t const ch)
    {
      str.insert(str.begin(), ch);
    }
    
    /**
     * @brief
     * Read a character from the file specified by the first parameter.
     *
     * If this function sees successive spaces, then it will eat them all, and
     * return just one space. Otherwise, it will return what it eats.
     */
    void
    read_ch(std::wfstream &file, wchar_t &ch)
    {
      if (putback_buf.size() != 0)
      {
        ch = putback_buf.front();
        putback_buf.pop_front();
      }
      else
      {
        file.get(ch);
        
        if (true == file.eof())
        {
          throw EndOfSourceException();
        }
        
        if (true == file.fail())
        {
          throw SourceIsBrokenException();
        }
      }
    }

    void
    read_ch(std::wstring &str, wchar_t &ch)
    {
      if (0 == str.length())
      {
        throw EndOfSourceException();
      }
      else
      {
        ch = str[0];
        
        str.erase(str.begin());
      }
    }
  }
}
