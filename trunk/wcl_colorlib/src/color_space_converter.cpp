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

#include "color_space_converter.hpp"
#include "color_space_converter_plugin.hpp"
#include "plugin_tree.hpp"
#include "..\..\wcl_mathlib\include\matrix.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    // =============================================
    //                   Querying
    // =============================================
    void
    ColorSpaceConverter::get_input_data_range(
      uint32_t const idx,
      std::vector<std::pair<ColorSpaceBasicUnitValue, ColorSpaceBasicUnitValue> > &ranges) const
    {
      assert(mp_plugin_for_src != 0);
      
      mp_plugin_for_src->get_input_data_range(idx, ranges);
    }
  
    uint32_t
    ColorSpaceConverter::get_input_data_subcomponent_count() const
    {
      assert(mp_plugin_for_src != 0);
      
      return mp_plugin_for_src->get_subcomponent_count();
    }
  
    uint32_t
    ColorSpaceConverter::get_output_data_subcomponent_count() const
    {
      assert(mp_plugin_for_dst != 0);
    
      return mp_plugin_for_dst->get_subcomponent_count();
    }
  
    ColorSpaceBasicUnitValueType
    ColorSpaceConverter::get_input_data_basic_unit_value_type() const
    {
      assert(mp_plugin_for_src != 0);
      
      return mp_plugin_for_src->get_basic_unit_value_type();
    }
    
    ColorSpaceBasicUnitValueType
    ColorSpaceConverter::get_output_data_basic_unit_value_type() const
    {
      assert(mp_plugin_for_dst != 0);
      
      return mp_plugin_for_dst->get_basic_unit_value_type();
    }
    
    // =============================================
    //                   Setting
    // =============================================
    template<PluginType T>
    void
    ColorSpaceConverter::check_if_the_other_plugin_is_different_custom(
      std::list<std::wstring> const &name)
    {
      PluginInfo<ColorSpaceConverterPlugin> const *the_other_plugin_info =
        ConverterPluginTypeTraits<T, ColorSpaceConverterPlugin>::get_the_other_plugin_info(this);
      
      if (the_other_plugin_info != 0)
      {
        ColorSpaceConverterPlugin * const the_other_plugin =
          ConverterPluginTypeTraits<T, ColorSpaceConverterPlugin>::get_the_other_plugin(this);
        
        assert(the_other_plugin != 0);
        
        {
          wchar_t const **the_other_plugin_parent_name_list;
          uint32_t the_other_plugin_parent_name_list_size;
          
          the_other_plugin_info->get_parent_name_list_func(&the_other_plugin_parent_name_list,
                                                           &the_other_plugin_parent_name_list_size);
          
          if ((1 == the_other_plugin_parent_name_list_size) &&
              (0 == wcscmp(L"Custom", the_other_plugin_parent_name_list[0])))
          {
            wchar_t const * const the_other_plugin_name = the_other_plugin_info->name_func();
            
            if (name.back().compare(the_other_plugin_name) != 0)
            {
              throw SrcAndDstColorSpaceConverterPluginCanNotBeDiffCustomAtTheSameTime();
            }
          }
        }
      }
    }
    
    void
    ColorSpaceConverter::assign_src_color_space(std::list<std::wstring> const &name)
    {
      if ((2 == name.size()) &&
          (0 == name.front().compare(L"Custom")))
      {
        check_if_the_other_plugin_is_different_custom<PLUGIN_TYPE_SRC>(name);
      }
      
      assign_src_plugin(name);
    }
    
    void
    ColorSpaceConverter::assign_dst_color_space(std::list<std::wstring> const &name)
    {
      if ((2 == name.size()) &&
          (0 == name.front().compare(L"Custom")))
      {
        check_if_the_other_plugin_is_different_custom<PLUGIN_TYPE_DST>(name);
      }
      
      assign_dst_plugin(name);
    }
    
    void
    ColorSpaceConverter::assign_src_color_space(
      PluginInfo<ColorSpaceConverterPlugin> * const info)
    {
      wchar_t const **parent_name_list;
      uint32_t parent_name_list_size;
      
      info->get_parent_name_list_func(&parent_name_list, &parent_name_list_size);
      
      if ((1 == parent_name_list_size) &&
          (0 == wcscmp(L"Custom", parent_name_list[0])))
      {
        wchar_t const * const name = info->name_func();
        
        std::list<std::wstring> names;
        names.push_back(parent_name_list[0]);
        names.push_back(name);
        
        check_if_the_other_plugin_is_different_custom<PLUGIN_TYPE_SRC>(names);
      }
      
      assign_src_plugin(info);
    }
    
    void
    ColorSpaceConverter::assign_dst_color_space(
      PluginInfo<ColorSpaceConverterPlugin> * const info)
    {
      wchar_t const **parent_name_list;
      uint32_t parent_name_list_size;
      
      info->get_parent_name_list_func(&parent_name_list, &parent_name_list_size);
      
      if ((1 == parent_name_list_size) &&
          (0 == wcscmp(L"Custom", parent_name_list[0])))
      {
        wchar_t const * const name = info->name_func();
        
        std::list<std::wstring> names;
        names.push_back(parent_name_list[0]);
        names.push_back(name);
        
        check_if_the_other_plugin_is_different_custom<PLUGIN_TYPE_DST>(names);
      }
      
      assign_dst_plugin(info);
    }
    
    // =============================================
    //                   Checking
    // =============================================
    void
    ColorSpaceConverter::check_valid_input_idx(
      uint32_t const idx) const
    {
      assert(mp_plugin_for_src != 0);
      
      mp_plugin_for_src->check_valid_input_idx(idx);
    }
  
    void
    ColorSpaceConverter::check_valid_input_value(
      uint32_t const idx,
      ColorSpaceBasicUnitValue const &value) const
    {
      assert(mp_plugin_for_src != 0);
      
      mp_plugin_for_src->check_valid_input_value(idx, value);
    }
  
    // =============================================
    //                   Conversion
    // =============================================
    void
    ColorSpaceConverter::convert(
      std::vector<ColorSpaceBasicUnitValue> const &src_data,
      std::vector<ColorSpaceBasicUnitValue> &dst_data)
    {
      assert(mp_plugin_for_src != 0);
      assert(mp_plugin_for_dst != 0);
      
      assert(mp_plugin_info_for_src != 0);
      assert(mp_plugin_info_for_dst != 0);
      
      if (mp_plugin_info_for_src->id == mp_plugin_info_for_dst->id)
      {
        dst_data = src_data;
      }
      else
      {
        dst_data.clear();
        
        std::vector<ColorSpaceBasicUnitValue> tmp_data;
        
        bool start_from_back_path = false;
      
        if ((mp_plugin_info_for_src->id == get_custom_ycbcr_plugin_id()) ||
            (mp_plugin_info_for_src->id == get_custom_ypbpr_plugin_id()) ||
            (mp_plugin_info_for_src->id == get_custom_rgb_plugin_id()))
        {
          start_from_back_path = true;
          tmp_data = src_data;
        }
        
        bool finish = false;
        
        if (false == start_from_back_path)
        {
          finish = mp_plugin_for_src->convert_to_cie1931_XYZ(src_data,
                                                             tmp_data,
                                                             mp_plugin_info_for_dst->id);
        }
      
        if (false == finish)
        {
          mp_plugin_for_dst->convert_from_cie1931_XYZ(tmp_data,
                                                      dst_data,
                                                      mp_plugin_info_for_src->id);
        }
        else
        {
          dst_data = tmp_data;
        }
      }
    }
    
    void
    ColorSpaceConverter::convert_buffer(
      std::vector<ColorSpaceBasicUnitValue> const &src_buffer,
      std::vector<ColorSpaceBasicUnitValue> &dst_buffer)
    {
      assert(mp_plugin_for_src != 0);
      assert(mp_plugin_for_dst != 0);
      
      assert(mp_plugin_info_for_src != 0);
      assert(mp_plugin_info_for_dst != 0);
      
      if (mp_plugin_info_for_src->id == mp_plugin_info_for_dst->id)
      {
        dst_buffer = src_buffer;
      }
      else
      {
        assert(0 == (src_buffer.size() % 3));
        
        dst_buffer.clear();
        
        std::vector<ColorSpaceBasicUnitValue>::const_iterator src_iter = src_buffer.begin();
        
        std::vector<ColorSpaceBasicUnitValue> src_data;
        std::vector<ColorSpaceBasicUnitValue> tmp_data;
        std::vector<ColorSpaceBasicUnitValue> dst_data;
        
        src_data.reserve(3);
        tmp_data.reserve(3);
        dst_data.reserve(3);
        
        uint32_t handled_count = 0;
        
        while (src_iter != src_buffer.end())
        {
          src_data.clear();

          src_data.push_back(*src_iter);
          ++src_iter;
          
          src_data.push_back(*src_iter);
          ++src_iter;
          
          src_data.push_back(*src_iter);
          ++src_iter;
          
          // Do the conversion.
          convert(src_data, dst_data);
          
          dst_buffer.push_back(dst_data[0]);
          dst_buffer.push_back(dst_data[1]);
          dst_buffer.push_back(dst_data[2]);
          
          handled_count += 3;
          
          if (mp_percentage_cb != 0)
          {
            double_t const curr_perc = (handled_count / static_cast<double_t>(src_buffer.size()));
          
            if (false == (*mp_percentage_cb)(mp_percentage_cb_param, curr_perc))
            {
              return;
            }
          }
        }
      }
    }
    
#if defined(WCL_COLORLIB_USE_REGISTRY)
    wchar_t const * const ColorSpaceConverter::PLUGIN_ROOT_DIR_REGISTRY_KEY_NAME = L"ColorSpaceConverterPluginRootDir";
    wchar_t const * const ColorSpaceConverter::PLUGIN_ROOT_DIR_STR_LENGTH_REGISTRY_KEY_NAME = L"ColorSpaceConverterPluginRootDirStrLength";
#endif
    
    uint32_t ColorSpaceConverter::g_custom_ycbcr_plugin_id = 0;
    uint32_t ColorSpaceConverter::g_custom_ypbpr_plugin_id = 0;
    uint32_t ColorSpaceConverter::g_custom_rgb_plugin_id = 0;
    
    uint32_t ColorSpaceConverter::get_custom_ycbcr_plugin_id()
    {
      if (0 == g_custom_ycbcr_plugin_id)
      {
        std::list<std::wstring> ycbcr_plugin_names;
        
        ycbcr_plugin_names.push_back(L"Custom");
        ycbcr_plugin_names.push_back(L"YCbCr");
        
        PluginInfo<ColorSpaceConverterPlugin> const * const info =
          Converter<ColorSpaceConverterPlugin>::search_plugin(ycbcr_plugin_names);
        assert(info != 0);
        
        g_custom_ycbcr_plugin_id = info->id;
      }
      
      return g_custom_ycbcr_plugin_id;
    }
    
    uint32_t ColorSpaceConverter::get_custom_ypbpr_plugin_id()
    {
      if (0 == g_custom_ypbpr_plugin_id)
      {
        std::list<std::wstring> ypbpr_plugin_names;
        
        ypbpr_plugin_names.push_back(L"Custom");
        ypbpr_plugin_names.push_back(L"YPbPr");
        
        PluginInfo<ColorSpaceConverterPlugin> const * const info =
          Converter<ColorSpaceConverterPlugin>::search_plugin(ypbpr_plugin_names);
        assert(info != 0);
        
        g_custom_ypbpr_plugin_id = info->id;
      }
      
      return g_custom_ypbpr_plugin_id;
    }
    
    uint32_t ColorSpaceConverter::get_custom_rgb_plugin_id()
    {
      if (0 == g_custom_rgb_plugin_id)
      {
        std::list<std::wstring> rgb_plugin_names;
        
        rgb_plugin_names.push_back(L"Custom");
        rgb_plugin_names.push_back(L"RGB");
        
        PluginInfo<ColorSpaceConverterPlugin> const * const info =
          Converter<ColorSpaceConverterPlugin>::search_plugin(rgb_plugin_names);
        assert(info != 0);
        
        g_custom_rgb_plugin_id = info->id;
      }
      
      return g_custom_rgb_plugin_id;
    }
  }
}
