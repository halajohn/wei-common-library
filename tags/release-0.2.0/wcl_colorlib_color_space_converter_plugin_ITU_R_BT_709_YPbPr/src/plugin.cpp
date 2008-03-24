#include "precompiled_header.hpp"

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

#include "plugin.hpp"

extern "C"
{
  WCL_COLORLIB_ITU_R_BT_709_YPBPR_PLUGIN_EXPORT Wcl::Colorlib::ColorSpaceConverterPlugin *
  create_plugin(Wcl::Colorlib::ColorSpaceConverter * const converter)
  {
    return ::new Wcl::Colorlib::ColorSpaceConverterPluginItuRBt709YPbPr(converter);
  }

  WCL_COLORLIB_ITU_R_BT_709_YPBPR_PLUGIN_EXPORT void
  delete_plugin(Wcl::Colorlib::ColorSpaceConverterPlugin * const plugin)
  {
    ::delete(plugin);
  }
  
  WCL_COLORLIB_ITU_R_BT_709_YPBPR_PLUGIN_EXPORT wchar_t const *
  name()
  {
    return L"ITU-R BT.709";
  }
  
  WCL_COLORLIB_ITU_R_BT_709_YPBPR_PLUGIN_EXPORT void
  get_parent_name_list(
    wchar_t const ***parent_name_list,
    Wcl::uint32_t *parent_name_list_size)
  {
    assert(parent_name_list != 0);
    assert(parent_name_list_size != 0);
    
    static wchar_t const *parent_name_list_data[1] = {L"YPbPr"};
    
    (*parent_name_list_size) = 1;
    (*parent_name_list) = parent_name_list_data;
  }
}

namespace Wcl
{
  namespace Colorlib
  {
    wchar_t const *
    ColorSpaceConverterPluginItuRBt709YPbPr::get_ypbpr_plugin_name() const
    {
      return ::name();
    }
    
    void
    ColorSpaceConverterPluginItuRBt709YPbPr::get_ypbpr_plugin_parent_name_list(
      wchar_t const ***parent_name_list,
      uint32_t *parent_name_list_size) const
    {
      ::get_parent_name_list(parent_name_list, parent_name_list_size);
    }
  }
}
