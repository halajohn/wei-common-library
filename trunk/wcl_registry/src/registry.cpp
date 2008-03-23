// wcl_registry - portable registry library
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

#include "registry.hpp"

namespace Wcl
{
  namespace Registry
  {
    bool
    open_key(key_t const parent_key, std::wstring const &key_name, Mode const mode, key_t * const returned_key)
    {
      REGSAM win32_mode;
      
      switch (mode)
      {
      case MODE_READ:
        win32_mode = KEY_READ;
        break;
        
      case MODE_WRITE:
        win32_mode = KEY_WRITE;
        break;
        
      default:
        assert(0);
        win32_mode = KEY_READ;
        break;
      }
      
      LONG const result = ::RegCreateKeyEx(parent_key, key_name.c_str(), 0, 0, 0, win32_mode, 0, returned_key, 0);
      
      if (result != ERROR_SUCCESS)
      {
        return false;
      }
      else
      {
        return true;
      }
    }
    
    bool
    close_key(key_t const key)
    {
      LONG const result = ::RegCloseKey(key);
      
      if (result != ERROR_SUCCESS)
      {
        return false;
      }
      else
      {
        return true;
      }
    }
    
    bool
    read_uint32(key_t key,
                std::wstring const &name,
                uint32_t &value)
    {
      size_t size = sizeof(value);
      
      LONG const result = !::RegQueryValueEx(key, name.c_str(), 0, 0, (BYTE *)&value, (LPDWORD)&size);
      if (ERROR_SUCCESS == result)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
    
    bool
    read_string(key_t key,
                std::wstring const &name,
                wchar_t * const buffer,
                size_t length)
    {
      assert(buffer != 0);
      
      memset(buffer, 0, length);
      
      LONG const result = !::RegQueryValueEx(key, name.c_str(), 0, 0, (BYTE *)buffer, (LPDWORD)&length);
      if (ERROR_SUCCESS == result)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
    
    bool
    write_uint32(key_t key,
                 std::wstring const &name,
                 uint32_t value)
    {
      size_t size = sizeof(value);
      
      LONG const result = !::RegSetValueEx(key, name.c_str(), 0, REG_DWORD, (BYTE const *)&value, (DWORD)size);
      if (ERROR_SUCCESS == result)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
    
    bool
    write_string(key_t key,
                 std::wstring const &name,
                 std::wstring str)
    {
      size_t size = (str.size() + 1) * sizeof(wchar_t);
      
      LONG const result = !::RegSetValueEx(key, name.c_str(), 0, REG_SZ, (BYTE const *)(str.c_str()), (DWORD)size);
      if (ERROR_SUCCESS == result)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
  }
}
