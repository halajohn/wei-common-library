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
#include "color_space_converter_plugin_internal.hpp"
#include "color_space_converter_plugin_YCbCr.hpp"
#include "exception.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    // ==========================================================================
    //                       Color Space YCbCr Converter Plugin
    // ==========================================================================    
    void
    ColorSpaceConverterPluginYCbCr::convert_from_YPbPr_to_YCbCr(
      std::vector<ColorSpaceBasicUnitValue> const &ypbpr_data,
      std::vector<ColorSpaceBasicUnitValue> &ycbcr_data)
    {
      assert(3 == ypbpr_data.size());
      
      uint32_t const y = boost::numeric_cast<uint32_t>((m_y_multiplier * ypbpr_data[0].get_value<double_t>()) + m_y_addend);
      uint32_t const cb = boost::numeric_cast<uint32_t>((m_cb_multiplier * ypbpr_data[1].get_value<double_t>()) + m_cb_addend);
      uint32_t const cr = boost::numeric_cast<uint32_t>((m_cr_multiplier * ypbpr_data[2].get_value<double_t>()) + m_cr_addend);
      
      ycbcr_data.clear();
      
      ycbcr_data.push_back(ColorSpaceBasicUnitValue(boost::numeric_cast<uint8_t>(y)));
      ycbcr_data.push_back(ColorSpaceBasicUnitValue(boost::numeric_cast<uint8_t>(cb)));
      ycbcr_data.push_back(ColorSpaceBasicUnitValue(boost::numeric_cast<uint8_t>(cr)));
    }
    
    void
    ColorSpaceConverterPluginYCbCr::convert_from_YCbCr_to_YPbPr(
      std::vector<ColorSpaceBasicUnitValue> const &ycbcr_data,
      std::vector<ColorSpaceBasicUnitValue> &ypbpr_data)
    {
      assert(3 == ycbcr_data.size());
      
      double_t const y = (ycbcr_data[0].get_value<uint8_t>() - m_y_addend) / boost::numeric_cast<double_t>(m_y_multiplier);
      double_t const pb = (ycbcr_data[1].get_value<uint8_t>() - m_cb_addend) / boost::numeric_cast<double_t>(m_cb_multiplier);
      double_t const pr = (ycbcr_data[2].get_value<uint8_t>() - m_cr_addend) / boost::numeric_cast<double_t>(m_cr_multiplier);
      
      ypbpr_data.clear();
      
      ypbpr_data.push_back(ColorSpaceBasicUnitValue(y));
      ypbpr_data.push_back(ColorSpaceBasicUnitValue(pb));
      ypbpr_data.push_back(ColorSpaceBasicUnitValue(pr));
    }
    
    void
    ColorSpaceConverterPluginYCbCr::set_ycbcr_plugin_id()
    {
      assert(0 == m_ycbcr_plugin_id);
      
      {
        std::list<std::wstring> ycbcr_plugin_names;
        
        {
          wchar_t const **parent_name_list;
          uint32_t parent_name_list_size;
          
          get_ycbcr_plugin_parent_name_list(&parent_name_list, &parent_name_list_size);
          for (uint32_t i = 0; i < parent_name_list_size; ++i)
          {
            ycbcr_plugin_names.push_back(parent_name_list[i]);
          }
        }
        
        {
          wchar_t const * const plugin_name = get_ycbcr_plugin_name();
          
          ycbcr_plugin_names.push_back(plugin_name);
        }
        
        PluginInfo<ColorSpaceConverterPlugin> const * const info =
          Converter<ColorSpaceConverterPlugin>::search_plugin(ycbcr_plugin_names);
        assert(info != 0);
        
        m_ycbcr_plugin_id = info->id;
      }
    }
    
    void
    ColorSpaceConverterPluginYCbCr::set_ycbcr_quantization_level(
      uint8_t const y_multiplier, uint8_t const y_addend,
      uint8_t const cb_multiplier, uint8_t const cb_addend,
      uint8_t const cr_multiplier, uint8_t const cr_addend)
    {
      m_y_multiplier = y_multiplier;
      m_y_addend = y_addend;
      
      m_cb_multiplier = cb_multiplier;
      m_cb_addend = cb_addend;
      
      m_cr_multiplier = cr_multiplier;
      m_cr_addend = cr_addend;
    }
    
    //=========================================================================
    //               Color Space Converter Plugin interface API
    //=========================================================================
    
    bool
    ColorSpaceConverterPluginYCbCr::convert_to_cie1931_XYZ(
      std::vector<ColorSpaceBasicUnitValue> const &ycbcr_data,
      std::vector<ColorSpaceBasicUnitValue> &dst_data,
      uint32_t const dst_plugin_id)
    {
      ColorSpaceConverterPluginYCbCr::check_valid_input_idx(ycbcr_data.size() - 1);
      
      if ((dst_plugin_id == get_ycbcr_plugin_id()) ||
          (dst_plugin_id == ColorSpaceConverter::get_custom_ycbcr_plugin_id()))
      {
        dst_data = ycbcr_data;
        
        return true;
      }
      else
      {
        std::vector<ColorSpaceBasicUnitValue> ypbpr_data;
        
        convert_from_YCbCr_to_YPbPr(ycbcr_data, ypbpr_data);
        
        return ColorSpaceConverterPluginYPbPr::convert_to_cie1931_XYZ(ypbpr_data,
                                                                      dst_data, 
                                                                      dst_plugin_id);
      }
    }
    
    void
    ColorSpaceConverterPluginYCbCr::convert_from_cie1931_XYZ(
      std::vector<ColorSpaceBasicUnitValue> const &src_data,
      std::vector<ColorSpaceBasicUnitValue> &ycbcr_data,
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
      
      if (src_plugin_id == ColorSpaceConverter::get_custom_ycbcr_plugin_id())
      {
        ycbcr_data = src_data;
      }
      else
      {
        std::vector<ColorSpaceBasicUnitValue> ypbpr_data;
        
        ColorSpaceConverterPluginYPbPr::convert_from_cie1931_XYZ(src_data,
                                                                 ypbpr_data,
                                                                 src_plugin_id);
        
        convert_from_YPbPr_to_YCbCr(ypbpr_data, ycbcr_data);
      }
    }
    
    void
    ColorSpaceConverterPluginYCbCr::check_valid_input_idx(
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
    ColorSpaceConverterPluginYCbCr::check_valid_input_value(
      uint32_t const idx,
      ColorSpaceBasicUnitValue const &value) const
    {
      ::Wcl::Colorlib::check_valid_input_value<ColorSpaceConverterPluginYCbCr>(this, idx, value);
    }
    
    void
    ColorSpaceConverterPluginYCbCr::get_input_data_range(
      uint32_t const idx,
      std::vector<std::pair<ColorSpaceBasicUnitValue, ColorSpaceBasicUnitValue> > &ranges) const
    {
      ColorSpaceConverterPluginYCbCr::check_valid_input_idx(idx);
      
      ranges.clear();
      
      switch (idx)
      {
      case 0: // Y
        ranges.push_back(std::pair<ColorSpaceBasicUnitValue, ColorSpaceBasicUnitValue>(
                           ColorSpaceBasicUnitValue(
                             boost::numeric_cast<uint8_t>(m_y_multiplier * 0 + m_y_addend)),
                           ColorSpaceBasicUnitValue(
                             boost::numeric_cast<uint8_t>(m_y_multiplier * 1 + m_y_addend))));
        break;
        
      case 1: // Cb
        ranges.push_back(std::pair<ColorSpaceBasicUnitValue, ColorSpaceBasicUnitValue>(
                           ColorSpaceBasicUnitValue(
                             boost::numeric_cast<uint8_t>(m_cb_multiplier * -0.5 + m_cb_addend)),
                           ColorSpaceBasicUnitValue(
                             boost::numeric_cast<uint8_t>(m_cb_multiplier * 0.5 + m_cb_addend))));
        break;
        
      case 2: // Cr
        ranges.push_back(std::pair<ColorSpaceBasicUnitValue, ColorSpaceBasicUnitValue>(
                           ColorSpaceBasicUnitValue(
                             boost::numeric_cast<uint8_t>(m_cr_multiplier * -0.5 + m_cr_addend)),
                           ColorSpaceBasicUnitValue(
                             boost::numeric_cast<uint8_t>(m_cr_multiplier * 0.5 + m_cr_addend))));
        break;
        
      default:
        assert(0);
        break;
      }
    }
    
    uint32_t
    ColorSpaceConverterPluginYCbCr::get_subcomponent_count() const
    {
      return 3;
    }
    
    ColorSpaceBasicUnitValueType
    ColorSpaceConverterPluginYCbCr::get_basic_unit_value_type() const
    {
      return COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_UINT8;
    }
  }
}
