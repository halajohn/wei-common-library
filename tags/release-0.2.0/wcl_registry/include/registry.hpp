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

#ifndef __wcl_registry_registry_hpp__
#define __wcl_registry_registry_hpp__

#include <string>

#if defined(WIN32)
#include <windows.h>
#endif

#if defined(WCL_REGISTRY_EXPORTS)
#define WCL_REGISTRY_EXPORT __declspec(dllexport)
#else
#define WCL_REGISTRY_EXPORT __declspec(dllimport)
#endif

#include "wcl_types.hpp"

namespace Wcl
{
  namespace Registry
  {
#if defined(WIN32)
    typedef HKEY key_t;
#endif
    
    enum Mode
    {
      MODE_READ,
      MODE_WRITE
    };
    typedef enum Mode Mode;
    
    WCL_REGISTRY_EXPORT extern bool open_key(key_t const parent_key,
                                             std::wstring const &key_name,
                                             Mode const mode,
                                             key_t * const returned_key);
    
    WCL_REGISTRY_EXPORT extern bool close_key(key_t const key);
    
    WCL_REGISTRY_EXPORT extern bool read_uint32(key_t key,
                                                std::wstring const &name,
                                                uint32_t &value);
    
    WCL_REGISTRY_EXPORT extern bool read_string(key_t key,
                                                std::wstring const &name,
                                                wchar_t * const buffer,
                                                size_t length);
    
    WCL_REGISTRY_EXPORT extern bool write_uint32(key_t key,
                                                 std::wstring const &name,
                                                 uint32_t value);
    
    WCL_REGISTRY_EXPORT extern bool write_string(key_t key,
                                                 std::wstring const &name,
                                                 std::wstring str);
  }
}

#endif
