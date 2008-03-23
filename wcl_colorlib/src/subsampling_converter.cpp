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

#include "subsampling_converter.hpp"
#include "subsampling_converter_plugin.hpp"
#include "plugin_tree.hpp"
#include "exception.hpp"

#include "..\..\wcl_mathlib\include\matrix.hpp"

namespace Wcl
{
  namespace Colorlib
  {    
    SubSamplingConverter::SubSamplingConverter()
      : mp_stage_name_cb(0),
        mp_stage_name_cb_param(0),
        mp_percentage_cb(0),
        mp_percentage_cb_param(0)
    {}
    
    SubSamplingConverter::~SubSamplingConverter()
    {
    }
    
    template<PluginType T>
    void
    SubSamplingConverter::check_if_the_other_plugin_is_different_custom(
      std::list<std::wstring> const &name)
    {
      PluginInfo<SubSamplingConverterPlugin> const *the_other_plugin_info =
        ConverterPluginTypeTraits<T, SubSamplingConverterPlugin>::get_the_other_plugin_info(this);
      
      if (the_other_plugin_info != 0)
      {
        SubSamplingConverterPlugin * const the_other_plugin =
          ConverterPluginTypeTraits<T, SubSamplingConverterPlugin>::get_the_other_plugin(this);
        
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
              throw SrcAndDstSubSamplingConverterPluginCanNotBeDiffCustomAtTheSameTime();
            }
          }
        }
      }
    }
    
    void
    SubSamplingConverter::assign_src_subsampling(
      std::list<std::wstring> const &name)
    {
      if ((2 == name.size()) &&
          (0 == name.front().compare(L"Custom")))
      {
        check_if_the_other_plugin_is_different_custom<PLUGIN_TYPE_SRC>(name);
      }
      
      assign_src_plugin(name);
      
      if (mp_percentage_cb != 0)
      {
        mp_plugin_for_src->register_percentage_cb(mp_percentage_cb, mp_percentage_cb_param);
      }
    }
    
    void
    SubSamplingConverter::assign_dst_subsampling(
      std::list<std::wstring> const &name)
    {
      if ((2 == name.size()) &&
          (0 == name.front().compare(L"Custom")))
      {
        check_if_the_other_plugin_is_different_custom<PLUGIN_TYPE_DST>(name);
      }
      
      assign_dst_plugin(name);
      
      if (mp_percentage_cb != 0)
      {
        mp_plugin_for_dst->register_percentage_cb(mp_percentage_cb, mp_percentage_cb_param);
      }
    }
    
    void
    SubSamplingConverter::assign_src_subsampling(
      PluginInfo<SubSamplingConverterPlugin> * const info)
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
      
      if (mp_percentage_cb != 0)
      {
        mp_plugin_for_src->register_percentage_cb(mp_percentage_cb, mp_percentage_cb_param);
      }
    }
    
    void
    SubSamplingConverter::assign_dst_subsampling(
      PluginInfo<SubSamplingConverterPlugin> * const info)
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
      
      if (mp_percentage_cb != 0)
      {
        mp_plugin_for_dst->register_percentage_cb(mp_percentage_cb, mp_percentage_cb_param);
      }
    }
    
    void
    SubSamplingConverter::register_stage_name_cb(
      progress_stage_name_cb_func_t const cb,
      void *param)
    {
      mp_stage_name_cb = cb;
      mp_stage_name_cb_param = param;
    }
    
    void
    SubSamplingConverter::register_percentage_cb(
      progress_percentage_cb_func_t const cb,
      void *param)
    {
      mp_percentage_cb = cb;
      mp_percentage_cb_param = param;
      
      if (mp_plugin_for_src != 0)
      {
        mp_plugin_for_src->register_percentage_cb(cb, param);
      }
      
      if (mp_plugin_for_dst != 0)
      {
        mp_plugin_for_dst->register_percentage_cb(cb, param);
      }
    }
    
    // =============================================
    //                   Conversion
    // =============================================
    void
    SubSamplingConverter::convert_to_yuv444(
      std::vector<ColorSpaceBasicUnitValue> const &src_buffer,
      std::vector<ColorSpaceBasicUnitValue> &yuv444_buffer,      
      uint32_t const width,
      uint32_t const height)
    {
      if ((mp_percentage_cb != 0) && (false == (*mp_percentage_cb)(mp_percentage_cb_param, 0.0)))
      {
        return;
      }
      
      mp_plugin_for_src->convert_to_yuv444(src_buffer, yuv444_buffer, width, height);
      
      if ((mp_percentage_cb != 0) && (false == (*mp_percentage_cb)(mp_percentage_cb_param, 1.0)))
      {
        return;
      }
    }
    
    void
    SubSamplingConverter::convert_from_yuv444(
      std::vector<ColorSpaceBasicUnitValue> const &yuv444_buffer,      
      std::vector<ColorSpaceBasicUnitValue> &dst_buffer,
      uint32_t const width,
      uint32_t const height)
    {
      if ((mp_percentage_cb != 0) &&
          (false == (*mp_percentage_cb)(mp_percentage_cb_param, 0.0)))
      {
        return;
      }
      
      mp_plugin_for_dst->convert_from_yuv444(dst_buffer, yuv444_buffer, width, height);
      
      if ((mp_percentage_cb != 0) &&
          (false == (*mp_percentage_cb)(mp_percentage_cb_param, 1.0)))
      {
        return;
      }
    }
    
    void
    SubSamplingConverter::convert_buffer(
      std::vector<ColorSpaceBasicUnitValue> const &src_buffer,
      std::vector<ColorSpaceBasicUnitValue> &dst_buffer,
      uint32_t const width,
      uint32_t const height)
    {
      if (0 == mp_plugin_for_src)
      {
        throw DoesNotSpecifySrcPluginException();
      }
      if (0 == mp_plugin_for_dst)
      {
        throw DoesNotSpecifyDstPluginException();
      }
      
      // Check if the src & dst subsampling are equal, if
      // yes, then I just need to copy src_buffer to
      // dst_buffer.
      if (mp_plugin_info_for_src->id == mp_plugin_info_for_dst->id)
      {
        dst_buffer = src_buffer;
      }
      else
      {
        dst_buffer.clear();
        
        std::vector<ColorSpaceBasicUnitValue> yuv444_buffer;
        std::vector<ColorSpaceBasicUnitValue> *yuv444_buffer_ptr = &yuv444_buffer;
        
        if (mp_plugin_info_for_src->id == get_custom_yuv444_plugin_id())
        {
          yuv444_buffer_ptr = const_cast<std::vector<ColorSpaceBasicUnitValue> *>(&src_buffer);
          goto src_is_custom_yuv444;
        }
        
        // convert to YUV444 buffer.
        if ((mp_stage_name_cb != 0) &&
            (false == (*mp_stage_name_cb)(mp_stage_name_cb_param,
                                          L"Convert to YUV444 buffer")))
        {
          return;
        }
        
        if (mp_plugin_info_for_dst->id == get_custom_yuv444_plugin_id())
        {
          yuv444_buffer_ptr = &dst_buffer;
        }
        
        convert_to_yuv444(src_buffer, *yuv444_buffer_ptr, width, height);
        
        if (mp_plugin_info_for_dst->id == get_custom_yuv444_plugin_id())
        {
          return;
        }
        
      src_is_custom_yuv444:
        
        // convert from dest YUV444 buffer to dest YUV
        // subsampling buffer.
        if ((mp_stage_name_cb != 0) &&
            (false == (*mp_stage_name_cb)(mp_stage_name_cb_param,
                                          L"Convert from YUV444 buffer")))
        {
          return;
        }
        
        convert_from_yuv444(*yuv444_buffer_ptr, dst_buffer, width, height);
      }
    }
    
#if defined(WCL_COLORLIB_USE_REGISTRY)
    wchar_t const * const SubSamplingConverter::PLUGIN_ROOT_DIR_REGISTRY_KEY_NAME = L"SubSamplingConverterPluginRootDir";
    wchar_t const * const SubSamplingConverter::PLUGIN_ROOT_DIR_STR_LENGTH_REGISTRY_KEY_NAME = L"SubSamplingConverterPluginRootDirStrLength";
#endif
    
    uint32_t SubSamplingConverter::g_custom_yuv444_plugin_id = 0;
    
    uint32_t SubSamplingConverter::get_custom_yuv444_plugin_id()
    {
      if (0 == g_custom_yuv444_plugin_id)
      {
        std::list<std::wstring> yuv444_plugin_names;
        
        yuv444_plugin_names.push_back(L"Custom");
        yuv444_plugin_names.push_back(L"YUV444");
        
        PluginInfo<SubSamplingConverterPlugin> const * const info =
          Converter<SubSamplingConverterPlugin>::search_plugin(yuv444_plugin_names);
        assert(info != 0);
        
        g_custom_yuv444_plugin_id = info->id;
      }
      
      return g_custom_yuv444_plugin_id;
    }
  }
}
