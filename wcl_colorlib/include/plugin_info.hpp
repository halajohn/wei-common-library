// wcl_colorlib - portable color library
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

#ifndef __wcl_colorlib_plugin_info_hpp__
#define __wcl_colorlib_plugin_info_hpp__

#include "wcl_types.hpp"
#include "converter.hpp"
#include "export.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    // Forward declaration
    template<typename T> class Converter;
    
    template<typename T>
    struct PluginInfo
    {
    private:
      
      PluginInfo &operator=(PluginInfo const &);
      
    public:
      
      typedef T * (*PluginCreateFunc)(Converter<T> * const converter);
      typedef void (*PluginDeleteFunc)(T *);
      typedef wchar_t const * (*PluginNameFunc)();
      typedef void (*PluginGetParentNameListFunc)(wchar_t const ***parent_name_list,
                                                  Wcl::uint32_t *parent_name_list_size);
      
      PluginCreateFunc create_func;
      PluginDeleteFunc delete_func;
      PluginNameFunc   name_func;
      PluginGetParentNameListFunc get_parent_name_list_func;
      
      uint32_t const id;
      
      /** @name life cycle
       */
      //@{
      PluginInfo(PluginCreateFunc const create_func_arg,
                 PluginDeleteFunc const delete_func_arg,
                 PluginNameFunc   const name_func_arg,
                 PluginGetParentNameListFunc const get_parent_name_list_func_arg,
                 uint32_t const id_arg)
        : create_func(create_func_arg),
          delete_func(delete_func_arg),
          name_func(name_func_arg),
          get_parent_name_list_func(get_parent_name_list_func_arg),
          id(id_arg)
      { }
      
      ~PluginInfo() {}
      //@}
    };
  }
}

#endif
