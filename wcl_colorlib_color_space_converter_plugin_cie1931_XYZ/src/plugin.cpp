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

namespace Wcl
{
  namespace Colorlib
  {
    // =================================================
    //                    Conversion
    // =================================================
    bool
    ColorSpaceConverterPluginCie1931XYZ::convert_to_cie1931_XYZ(
      std::vector<ColorSpaceBasicUnitValue> const &src_data,
      std::vector<ColorSpaceBasicUnitValue> &dst_data,
      uint32_t const /* dst_plugin_id */)
    {
      // Check input size
      if (src_data.size() < 3)
      {
        throw TooLessInputDataException();
      }
      if (src_data.size() > 3)
      {
        throw TooManyInputDataException();
      }
      
      // Check input value range
      uint32_t i = 0;
      
      BOOST_FOREACH(ColorSpaceBasicUnitValue const &value, src_data)
      {
        ColorSpaceConverterPluginCie1931XYZ::check_valid_input_value(i, value);
        
        ++i;
      }
      
      dst_data = src_data;
      
      return false;
    }
  
    void
    ColorSpaceConverterPluginCie1931XYZ::convert_from_cie1931_XYZ(
      std::vector<ColorSpaceBasicUnitValue> const &src_data,
      std::vector<ColorSpaceBasicUnitValue> &dst_data,
      uint32_t const /* src_plugin_id */)
    {
      if (src_data.size() < 3)
      {
        throw TooLessInputDataException();
      }
      if (src_data.size() > 3)
      {
        throw TooManyInputDataException();
      }
      
      dst_data = src_data;
    }
    
    // =================================================
    //                     Querying
    // =================================================
    void
    ColorSpaceConverterPluginCie1931XYZ::get_input_data_range(
      uint32_t const /* idx */,
      std::vector<std::pair<ColorSpaceBasicUnitValue, ColorSpaceBasicUnitValue> > &ranges) const
    {
      ranges.push_back(std::pair<ColorSpaceBasicUnitValue, ColorSpaceBasicUnitValue>(-DBL_MAX, DBL_MAX));
    }
    
    uint32_t
    ColorSpaceConverterPluginCie1931XYZ::get_subcomponent_count() const
    {
      return 3;
    }
    
    ColorSpaceBasicUnitValueType
    ColorSpaceConverterPluginCie1931XYZ::get_basic_unit_value_type() const
    {
      return COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_DOUBLE;
    }
    
    // =================================================
    //                     Checking
    // =================================================
    void
    ColorSpaceConverterPluginCie1931XYZ::check_valid_input_idx(
      uint32_t const idx) const
    {
      switch (idx)
      {
      case 0:
      case 1:
      case 2:
        return;
        
      default:
        throw TooManyInputDataException();
      }
    }
    
    void
    ColorSpaceConverterPluginCie1931XYZ::check_valid_input_value(
      uint32_t const idx,
      ColorSpaceBasicUnitValue const &value) const
    {
      ::Wcl::Colorlib::check_valid_input_value<ColorSpaceConverterPluginCie1931XYZ>(this, idx, value);
    }
  }
}

extern "C"
{
  WCL_COLORLIB_CIE1931XYZ_PLUGIN_EXPORT Wcl::Colorlib::ColorSpaceConverterPlugin *
  create_plugin(Wcl::Colorlib::ColorSpaceConverter * const converter)
  {
    return ::new Wcl::Colorlib::ColorSpaceConverterPluginCie1931XYZ(converter);
  }
  
  WCL_COLORLIB_CIE1931XYZ_PLUGIN_EXPORT void
  delete_plugin(Wcl::Colorlib::ColorSpaceConverterPlugin * const plugin)
  {
    ::delete(plugin);
  }
  
  WCL_COLORLIB_CIE1931XYZ_PLUGIN_EXPORT wchar_t const *
  name()
  {
    return L"CIE1931_XYZ";
  }
  
  WCL_COLORLIB_CIE1931XYZ_PLUGIN_EXPORT void
  get_parent_name_list(
    wchar_t const ***parent_name_list,
    Wcl::uint32_t *parent_name_list_size)
  {
    assert(parent_name_list != 0);
    assert(parent_name_list_size != 0);
    
    static wchar_t const *parent_name_list_data[1] = {L"CIE"};
    
    (*parent_name_list_size) = 1;
    (*parent_name_list) = parent_name_list_data;
  }
}

