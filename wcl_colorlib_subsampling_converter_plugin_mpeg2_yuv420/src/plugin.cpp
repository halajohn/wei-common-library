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

// This YCbCr420 planner subsampling method will produce a
// buffer contains the following data:
//
// Y01 Y02 Y03 Y04 Y05 Y06 Y07 Y08
// Y09 Y10 Y11 Y12 Y13 Y14 Y15 Y16
// Y17 Y18 Y19 Y20 Y21 Y22 Y23 Y24
// Y25 Y26 Y27 Y28 Y29 Y30 Y31 Y32
// U01 U02 U03 U04 U05 U06 U07 U08
// V01 V02 V03 V04 V05 V06 V07 V08
//
// The downsampling factor of the horizontal direction is 2,
// and the downsampling factor of the vertical direction is 2.
//
// Thus,
//
// One Y represents the Y component of 1 pixel.
// One U represents the U component of 4 pixel.
// One V represents the V component of 4 pixel.
//
// So that U01 represents the U component of Y01, Y02, Y09,
// Y10.

namespace Wcl
{
  namespace Colorlib
  {
    // =================================================
    //                    Conversion
    // =================================================
    
    namespace
    {
      ColorSpaceBasicUnitValue const *
      determine_end_addr(ColorSpaceBasicUnitValue const * const start_addr,
                         uint32_t const size,
                         ColorSpaceBasicUnitValue const * const total_end_addr)
      {
        assert(start_addr != 0);
        assert(total_end_addr != 0);
        
        if ((start_addr + size - 1) < total_end_addr)
        {
          return start_addr + size - 1;
        }
        else
        {
          return total_end_addr;
        }
      }
      
      ColorSpaceBasicUnitValue const *
      determine_curr_addr(ColorSpaceBasicUnitValue const * const start_addr,
                          ColorSpaceBasicUnitValue const * const end_addr,
                          uint32_t const offset)
      {
        if (start_addr + offset <= end_addr)
        {
          return start_addr + offset;
        }
        else
        {
          return 0;
        }
      }
    }
    
    void
    SubSamplingConverterPluginMpeg2Yuv420::get_ycbcr_color_space_name(
      std::list<std::wstring> &names)
    {
      names.clear();
      
      names.push_back(L"YCbCr");
      names.push_back(L"ITU-R BT.709");
    }
        
    /**
     * The sampling method if the MPEG-2 YUV 420 format is as
     * following:
     *
     * Y  Y  Y  Y  Y
     * UV    UV    UV
     * Y  Y  Y  Y  Y
     * UV    UV    UV
     * Y  Y  Y  Y  Y
     */
    void
    SubSamplingConverterPluginMpeg2Yuv420::convert_to_yuv444(
      std::vector<ColorSpaceBasicUnitValue> const &src_buffer,
      std::vector<ColorSpaceBasicUnitValue> &yuv444_buffer,
      uint32_t const width,
      uint32_t const height)
    {
      assert(0 == (width % 16));
      assert(0 == (height % 16));
      
      assert(0 == yuv444_buffer.size());
      
      ColorSpaceBasicUnitValue const *start_addr = &(src_buffer[0]);
      ColorSpaceBasicUnitValue const *end_addr = start_addr + src_buffer.size() - 1;
      
      ColorSpaceBasicUnitValue const *y_buffer_start;
      ColorSpaceBasicUnitValue const *y_buffer_end;
      
      ColorSpaceBasicUnitValue const *u_buffer_start;
      ColorSpaceBasicUnitValue const *u_buffer_end;
      
      ColorSpaceBasicUnitValue const *v_buffer_start;
      ColorSpaceBasicUnitValue const *v_buffer_end;
      
      // Calculate the starting & endding address of the
      // Y,U,V buffer.
      {
        y_buffer_start = start_addr;
        y_buffer_end = determine_end_addr(y_buffer_start, width * height, end_addr);
        
        if (y_buffer_end == end_addr)
        {
          u_buffer_start = 0;
          u_buffer_end = 0;
          
          v_buffer_start = 0;
          v_buffer_end = 0;
        }
        else
        {
          u_buffer_start = y_buffer_end + 1;
          u_buffer_end = determine_end_addr(u_buffer_start, width * height / 4, end_addr);
          
          if (u_buffer_end == end_addr)
          {
            v_buffer_start = 0;
            v_buffer_end = 0;
          }
          else
          {
            v_buffer_start = u_buffer_end + 1;
            v_buffer_end = determine_end_addr(v_buffer_start, width * height / 4, end_addr);
          }
        }
      }
      
      size_t const y_buffer_size = y_buffer_end - y_buffer_start + 1;      
      uint32_t idx = 0;
      
      bool repeat = false;
      uint32_t idx_of_multiple_of_2_minus = 0;
      
      for (ColorSpaceBasicUnitValue const *curr_y = y_buffer_start; curr_y <= y_buffer_end; ++curr_y)
      {
        uint32_t const idx_of_multiple_of_2 = ((curr_y - y_buffer_start) / 2) - idx_of_multiple_of_2_minus;
        
        ColorSpaceBasicUnitValue const * const curr_u = determine_curr_addr(u_buffer_start, u_buffer_end, idx_of_multiple_of_2);
        ColorSpaceBasicUnitValue const * const curr_v = determine_curr_addr(v_buffer_start, v_buffer_end, idx_of_multiple_of_2);
        
        assert(curr_y != 0);
        ColorSpaceBasicUnitValue const y = (*curr_y);
        
        ColorSpaceBasicUnitValue u;
        ColorSpaceBasicUnitValue v;
        
        if (curr_u != 0)
        {
          u = (*curr_u);
        }
        else
        {
          u = ColorSpaceBasicUnitValue(static_cast<uint8_t>(0));
        }
        
        if (curr_v != 0)
        {
          v = (*curr_v);
        }
        else
        {
          v = ColorSpaceBasicUnitValue(static_cast<uint8_t>(0));
        }
        
        yuv444_buffer.push_back(y);
        yuv444_buffer.push_back(u);
        yuv444_buffer.push_back(v);
        
        ++idx;
        if (0 == (idx % width))
        {
          if (true == repeat)
          {
            repeat = false;
          }
          else
          {
            repeat = true;
            
            idx_of_multiple_of_2_minus += (width / 2);
          }
        }
        
        if (mp_percentage_cb != 0)
        {
          double_t const curr_perc = (idx / static_cast<double_t>(y_buffer_size));
          
          if (false == (*mp_percentage_cb)(mp_percentage_cb_param, curr_perc))
          {
            return;
          }
        }
      }
    }
    
    void
    SubSamplingConverterPluginMpeg2Yuv420::convert_from_yuv444(
      std::vector<ColorSpaceBasicUnitValue> &dst_buffer,
      std::vector<ColorSpaceBasicUnitValue> const &yuv444_buffer,
      uint32_t const width,
      uint32_t const height)
    {
      assert(0 == (width % 16));
      assert(0 == (height % 16));
      
      assert(0 == dst_buffer.size());
      
      dst_buffer.clear();
      dst_buffer.reserve((width * height) + (width * height / 4) + (width * height / 4));
      
      ColorSpaceBasicUnitValue *y_buffer_addr = &(dst_buffer[0]);
      ColorSpaceBasicUnitValue *cb_buffer_addr = &(dst_buffer[width * height]);
      ColorSpaceBasicUnitValue *cr_buffer_addr = &(dst_buffer[(width * height) + (width * height / 4)]);
      
      bool add_cb_cr_into_working_mem = true;
      
      std::deque<ColorSpaceBasicUnitValue> cb_data;
      std::deque<ColorSpaceBasicUnitValue> cr_data;
      
      ColorSpaceBasicUnitValue const *y;
      ColorSpaceBasicUnitValue const *cb;
      ColorSpaceBasicUnitValue const *cr;
      ColorSpaceBasicUnitValue const dummy(static_cast<uint8_t>(0));
      
      uint32_t idx = 0;
      std::vector<ColorSpaceBasicUnitValue>::const_iterator iter = yuv444_buffer.begin();
      
      for (idx = 0; idx < (width * height); ++idx)
      {
        if (iter != yuv444_buffer.end())
        {
          y  = &(*iter);
          ++iter;
        }
        else
        {
          y = &dummy;
        }
        
        if (iter != yuv444_buffer.end())
        {
          cb = &(*iter);
          ++iter;
        }
        else
        {
          cb = &dummy;
        }
        
        if (iter != yuv444_buffer.end())
        {
          cr = &(*iter);
          ++iter;
        }
        else
        {
          cr = &dummy;
        }
        
        *(y_buffer_addr) = (*y);
        ++y_buffer_addr;
        
        if (true == add_cb_cr_into_working_mem)
        {
          cb_data.push_back(*cb);
          cr_data.push_back(*cr);
        }
        else
        {
          assert(cb_data.size() > 0);
          assert(cr_data.size() > 0);
          
          cb_data[0] += (*cb);
          cr_data[0] += (*cr);
          
          cb_data[0] /= 2;
          cr_data[0] /= 2;
          
          *(cb_buffer_addr) = cb_data[0];
          *(cr_buffer_addr) = cr_data[0];
          
          ++cb_buffer_addr;
          ++cr_buffer_addr;
          
          cb_data.pop_front();
          cr_data.pop_front();
        }
        
        if (mp_percentage_cb != 0)
        {
          double_t const curr_perc = (idx / static_cast<double_t>(width * height));
          
          if (false == (*mp_percentage_cb)(mp_percentage_cb_param, curr_perc))
          {
            return;
          }
        }
        
        ++idx;
        
        if (0 == (idx % width))
        {
          if (true == add_cb_cr_into_working_mem)
          {
            add_cb_cr_into_working_mem = false;
          }
          else
          {
            add_cb_cr_into_working_mem = true;
          }
        }
      }
    }
  }
}

extern "C"
{
  WCL_COLORLIB_PLUGIN_EXPORT Wcl::Colorlib::SubSamplingConverterPlugin *
  create_plugin(Wcl::Colorlib::SubSamplingConverter * const converter)
  {
    return ::new Wcl::Colorlib::SubSamplingConverterPluginMpeg2Yuv420(converter);
  }
  
  WCL_COLORLIB_PLUGIN_EXPORT void
  delete_plugin(Wcl::Colorlib::SubSamplingConverterPlugin * const plugin)
  {
    ::delete(plugin);
  }
  
  WCL_COLORLIB_PLUGIN_EXPORT wchar_t const *
  name()
  {
    return L"YUV 420";
  }
  
  WCL_COLORLIB_PLUGIN_EXPORT void
  get_parent_name_list(
    wchar_t const ***parent_name_list,
    Wcl::uint32_t *parent_name_list_size)
  {
    assert(parent_name_list != 0);
    assert(parent_name_list_size != 0);
    
    static wchar_t const *parent_name_list_data[1] = {L"MPEG-2"};
    
    (*parent_name_list_size) = 1;
    (*parent_name_list) = parent_name_list_data;
  }
}
