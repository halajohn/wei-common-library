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

#include "..\..\wcl_colorlib\include\subsampling_converter_plugin.hpp"
#include "..\..\wcl_colorlib\include\exception.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    // =================================================
    //                    Conversion
    // =================================================
    
    /**
     * @name dummy
     * These 2 functions are unused in this plugin, however,
     * I have to give these 2 functions a dummy name so that
     * the color space plugin initialization stage may
     * pass.
     */
    //@{
    void
    SubSamplingConverterPluginCustomYuv444::get_ycbcr_color_space_name(
      std::list<std::wstring> &names)
    {
      names.clear();
      
      names.push_back(L"Custom");
      names.push_back(L"YCbCr");
    }
    //@}
    
    void
    SubSamplingConverterPluginCustomYuv444::convert_to_yuv444(
      std::vector<ColorSpaceBasicUnitValue> const &src_buffer,
      std::vector<ColorSpaceBasicUnitValue> &yuv444_buffer,
      uint32_t const width,
      uint32_t const height)
    {
    }
    
    void
    SubSamplingConverterPluginCustomYuv444::convert_from_yuv444(
      std::vector<ColorSpaceBasicUnitValue> &dst_buffer,
      std::vector<ColorSpaceBasicUnitValue> const &yuv444_buffer,
      uint32_t const width,
      uint32_t const height)
    {
    }
  }
}

extern "C"
{
  WCL_COLORLIB_PLUGIN_EXPORT Wcl::Colorlib::SubSamplingConverterPlugin *
  create_plugin(Wcl::Colorlib::SubSamplingConverter * const converter)
  {
    return ::new Wcl::Colorlib::SubSamplingConverterPluginCustomYuv444(converter);
  }
  
  WCL_COLORLIB_PLUGIN_EXPORT void
  delete_plugin(Wcl::Colorlib::SubSamplingConverterPlugin * const plugin)
  {
    ::delete(plugin);
  }
  
  WCL_COLORLIB_PLUGIN_EXPORT wchar_t const *
  name()
  {
    return L"YUV444";
  }
  
  WCL_COLORLIB_PLUGIN_EXPORT void
  get_parent_name_list(
    wchar_t const ***parent_name_list,
    Wcl::uint32_t *parent_name_list_size)
  {
    assert(parent_name_list != 0);
    assert(parent_name_list_size != 0);
    
    static wchar_t const *parent_name_list_data[1] = {L"Custom"};
    
    (*parent_name_list_size) = 1;
    (*parent_name_list) = parent_name_list_data;
  }
}
