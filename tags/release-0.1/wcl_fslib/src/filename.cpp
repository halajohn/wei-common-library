// wcl_fslib - portable file system library
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

#include <string>
#include <fstream>
#include "filename.h"

std::wstring
get_filename(std::wstring const &filename)
{
  std::wstring::size_type loc = filename.rfind(L'\\', filename.size() - 1);
  if (std::wstring::npos == loc)
  {
    loc = filename.rfind(L'/', filename.size() - 1);
  }
  
  if (loc != std::wstring::npos)
  {
    return filename.substr(loc + 1);
  }
  else
  {
    /* There are no / or \ in the 'str', thus the entire 'str' have to be
     * a filename.
     */
    return filename;
  }
}

std::wstring
get_filename_wo_extension(std::wstring const &name)
{
  std::wstring const filename = get_filename(name);
  if (0 == filename.size())
  {
    return filename;
  }
  else
  {
    std::wstring::size_type loc = filename.rfind(L'.', filename.size() - 1);
    
    if (loc != std::wstring::npos)
    {
      return filename.substr(0, loc);
    }
    else
    {
      return filename;
    }
  }
}

std::wstring
get_file_extension(std::wstring const &name)
{
  std::wstring const filename = get_filename(name);
  if (0 == filename.size())
  {
    return filename;
  }
  else
  {
    std::wstring::size_type loc = filename.rfind(L'.', filename.size() - 1);
    
    if (loc != std::wstring::npos)
    {
      return filename.substr(loc + 1);
    }
    else
    {
      return std::wstring();
    }
  }
}

/**
 * @return If the return string is not empty, then it must be ended by a
 * '/' or a '\'.
 */
std::wstring
get_pathname(std::wstring const &filename)
{
  std::wstring::size_type loc = filename.rfind(L'\\', filename.size() - 1);
  if (std::wstring::npos == loc)
  {
    loc = filename.rfind(L'/', filename.size() - 1);
  }
  
  if (loc != std::wstring::npos)
  {
    return filename.substr(0, loc + 1);
  }
  else
  {
    /* There are no / or \ in the 'str', thus the entire 'str' have to be
     * a filename.
     */
    return std::wstring();
  }
}
