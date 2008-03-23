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

#include "..\..\wcl_mathlib\include\matrix.hpp"

#include "color_space_converter.hpp"
#include "color_space_converter_plugin_YPbPr.hpp"
#include "color_space_converter_plugin_internal.hpp"
#include "exception.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    // ==========================================================================
    //                       Color Space YPbPr Converter Plugin
    // ==========================================================================
    
    void
    ColorSpaceConverterPluginYPbPr::set_ypbpr_coefficient(
      double_t const kr, double_t const kb)
    {
      m_kr = kr;
      m_kg = 1 - kr - kb;
      m_kb = kb;
    }
    
    void
    ColorSpaceConverterPluginYPbPr::convert_from_RGB_to_YPbPr(
      std::vector<ColorSpaceBasicUnitValue> const &rgb_data,
      std::vector<ColorSpaceBasicUnitValue> &ypbpr_data)
    {
      assert(3 == rgb_data.size());
      
      double_t const Py = ((m_kr * rgb_data[0].get_value<double>()) +
                           (m_kg * rgb_data[1].get_value<double>()) +
                           (m_kb * rgb_data[2].get_value<double>()));
      
      double_t const Pb = (0.5 * (rgb_data[2].get_value<double>() - Py)) / (1 - m_kb);
      double_t const Pr = (0.5 * (rgb_data[0].get_value<double>() - Py)) / (1 - m_kr);
      
      ypbpr_data.clear();
      
      ypbpr_data.push_back(ColorSpaceBasicUnitValue(Py));
      ypbpr_data.push_back(ColorSpaceBasicUnitValue(Pb));
      ypbpr_data.push_back(ColorSpaceBasicUnitValue(Pr));
    }
    
    void
    ColorSpaceConverterPluginYPbPr::convert_from_YPbPr_to_RGB(
      std::vector<ColorSpaceBasicUnitValue> const &ypbpr_data,
      std::vector<ColorSpaceBasicUnitValue> &rgb_data)
    {
      double_t const r = ypbpr_data[0].get_value<double>() + 2 * (1 - m_kr) * ypbpr_data[2].get_value<double>();
      double_t const b = ypbpr_data[0].get_value<double>() + 2 * (1 - m_kb) * ypbpr_data[1].get_value<double>();
      double_t const g = (ypbpr_data[0].get_value<double>() - (m_kb * b) - (m_kr * r)) / m_kg;
      
      rgb_data.clear();
      
      rgb_data.push_back(ColorSpaceBasicUnitValue(r));
      rgb_data.push_back(ColorSpaceBasicUnitValue(g));
      rgb_data.push_back(ColorSpaceBasicUnitValue(b));
    }
    
    void
    ColorSpaceConverterPluginYPbPr::set_ypbpr_plugin_id()
    {
      assert(0 == m_ypbpr_plugin_id);
      
      {
        std::list<std::wstring> ypbpr_plugin_names;
        
        {
          wchar_t const **parent_name_list;
          uint32_t parent_name_list_size;
          
          get_ypbpr_plugin_parent_name_list(&parent_name_list, &parent_name_list_size);
          for (uint32_t i = 0; i < parent_name_list_size; ++i)
          {
            ypbpr_plugin_names.push_back(parent_name_list[i]);
          }
        }
        
        {
          wchar_t const * const plugin_name = get_ypbpr_plugin_name();
          
          ypbpr_plugin_names.push_back(plugin_name);
        }
        
        PluginInfo<ColorSpaceConverterPlugin> const * const info =
          Converter<ColorSpaceConverterPlugin>::search_plugin(ypbpr_plugin_names);
        assert(info != 0);
        
        m_ypbpr_plugin_id = info->id;
      }
    }
    
    //=========================================================================
    //               Color Space Converter Plugin interface API
    //=========================================================================
    
    bool
    ColorSpaceConverterPluginYPbPr::convert_to_cie1931_XYZ(
      std::vector<ColorSpaceBasicUnitValue> const &ypbpr_data,
      std::vector<ColorSpaceBasicUnitValue> &dst_data,
      uint32_t const dst_plugin_id)
    {
      // Check input size
      if (ypbpr_data.size() < 3)
      {
        throw TooLessInputDataException();
      }
      if (ypbpr_data.size() > 3)
      {
        throw TooManyInputDataException();
      }
      
      if ((dst_plugin_id == get_ypbpr_plugin_id()) ||
          (dst_plugin_id == ColorSpaceConverter::get_custom_ypbpr_plugin_id()))
      {
        dst_data = ypbpr_data;
        
        return true;
      }
      else
      {
        std::vector<ColorSpaceBasicUnitValue> rgb_data;
        
        convert_from_YPbPr_to_RGB(ypbpr_data, rgb_data);
        
        return ColorSpaceConverterPluginRgb::convert_to_cie1931_XYZ(rgb_data,
                                                                    dst_data,
                                                                    dst_plugin_id);
      }
    }
    
    void
    ColorSpaceConverterPluginYPbPr::convert_from_cie1931_XYZ(
      std::vector<ColorSpaceBasicUnitValue> const &src_data,
      std::vector<ColorSpaceBasicUnitValue> &ypbpr_data,
      uint32_t const src_plugin_id)
    {
      if (src_data.size() < 3)
      {
        throw TooLessInputDataException();
      }
      if (src_data.size() > 3)
      {
        throw TooManyInputDataException();
      }
      
      if (src_plugin_id == ColorSpaceConverter::get_custom_ypbpr_plugin_id())
      {
        ypbpr_data = src_data;
      }
      else
      {
        std::vector<ColorSpaceBasicUnitValue> rgb_data;
        
        ColorSpaceConverterPluginRgb::convert_from_cie1931_XYZ(src_data,
                                                               rgb_data,
                                                               src_plugin_id);
        
        convert_from_RGB_to_YPbPr(rgb_data, ypbpr_data);
      }
    }
    
    void
    ColorSpaceConverterPluginYPbPr::get_input_data_range(
      uint32_t const idx,
      std::vector<std::pair<ColorSpaceBasicUnitValue, ColorSpaceBasicUnitValue> > &ranges) const
    {
      ColorSpaceConverterPluginYPbPr::check_valid_input_idx(idx);
      
      ranges.clear();
      
      switch (idx)
      {
      case 0: // Y
        ranges.push_back(std::pair<ColorSpaceBasicUnitValue, ColorSpaceBasicUnitValue>(
                           ColorSpaceBasicUnitValue(0.0), ColorSpaceBasicUnitValue(1.0)));
        break;
        
      case 1: // Pb
        ranges.push_back(std::pair<ColorSpaceBasicUnitValue, ColorSpaceBasicUnitValue>(
                           ColorSpaceBasicUnitValue(-0.5), ColorSpaceBasicUnitValue(0.5)));
        break;
        
      case 2: // Pr
        ranges.push_back(std::pair<ColorSpaceBasicUnitValue, ColorSpaceBasicUnitValue>(
                           ColorSpaceBasicUnitValue(-0.5), ColorSpaceBasicUnitValue(0.5)));
        break;
        
      default:
        assert(0);
        break;
      }
    }
    
    uint32_t
    ColorSpaceConverterPluginYPbPr::get_subcomponent_count() const
    {
      return 3;
    }
    
    ColorSpaceBasicUnitValueType
    ColorSpaceConverterPluginYPbPr::get_basic_unit_value_type() const
    {
      return COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_DOUBLE;
    }
    
    void
    ColorSpaceConverterPluginYPbPr::check_valid_input_value(
      uint32_t const idx,
      ColorSpaceBasicUnitValue const &value) const
    {
      ::Wcl::Colorlib::check_valid_input_value<ColorSpaceConverterPluginYPbPr>(this, idx, value);
    }
    
    void
    ColorSpaceConverterPluginYPbPr::check_valid_input_idx(
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
  }
}
