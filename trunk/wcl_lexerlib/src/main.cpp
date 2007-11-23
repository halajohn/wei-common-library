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

#include "../../wcl_fmtstr/include/fmtstr.h"

namespace
{
  /// @var putback_buf
  ///
  /// Becuase there is no quarantee in the standard that how
  /// many characters can be put back. Thus I have to
  /// implement a putback_buf like this to simulate putting
  /// back characters to a file.
  std::deque<wchar_t> putback_buf;
}

void
lexerlib_put_back(std::wfstream &file, wchar_t const ch)
{
  putback_buf.push_front(ch);
}

void
lexerlib_put_back(std::wfstream &file,
                  std::wstring const * const str)
{
  for (std::wstring::const_reverse_iterator iter = str->rbegin();
       iter != str->rend();
       ++iter)
  {
    putback_buf.push_front(*iter);
  }
}

void
lexerlib_put_back(std::wstring &str, wchar_t const ch)
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
bool
lexerlib_read_ch(std::wfstream &file, wchar_t * const ch)
{
  bool see_spaces = false;
  
  while (1)
  {
    if (putback_buf.size() != 0)
    {
      (*ch) = putback_buf.front();
      putback_buf.pop_front();
    }
    else
    {
      file.get(*ch);
      
      if (true == file.eof())
      {
        (*ch) = WEOF;
        return true;
      }
      
      if (true == file.fail())
      {
        return false;
      }
    }
    
    if (L' ' == (*ch))
    {
      see_spaces = true;
    }
    else
    {
      if (true == see_spaces)
      {
        lexerlib_put_back(file, *ch);
        *ch = L' ';
      }
      break;
    }
  }
  
  return true;
}

bool
lexerlib_read_ch(std::wstring &str, wchar_t * const ch)
{
  bool see_spaces = false;
  
  while (1)
  {
    if (0 == str.length())
    {
      (*ch) = WEOF;
      return true;
    }
    
    *ch = str[0];
    
    if (L' ' == (*ch))
    {
      see_spaces = true;
      str.erase(str.begin());
    }
    else
    {
      if (true == see_spaces)
      {
        *ch = L' ';
      }
      else
      {
        str.erase(str.begin());
      }
      break;
    }
  }
  
  return true;
}
