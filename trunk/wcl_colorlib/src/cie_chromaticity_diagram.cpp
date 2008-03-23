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

#include "..\..\wcl_drawinglib\include\drawinglib.hpp"

#include "wcl_types.hpp"
#include "color_space_converter.hpp"
#include "cie_chromaticity_diagram.hpp"
#include "cie_color_match_func.hpp"
#include "cie_color_match_func_internal.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    namespace CieChromaticityDiagram
    {
      namespace
      {
        uint32_t
        get_point(
          double_t const curr_pos_ratio,
          uint32_t const size)
        {
          double_t const curr_pos_size = (size * curr_pos_ratio);
          
          // add 0.5 is for rounding
          return boost::numeric_cast<uint32_t>(curr_pos_size + 0.5);
        }
      
        uint32_t
        get_x_point(
          double_t const x,
          uint32_t const width)
        {
          uint32_t x_point = get_point(x, width);
        
          if (x_point >= width)
          {
            x_point = (width - 1);
          }
        
          return x_point;
        }
      
        uint32_t
        get_y_point(
          double_t const y,
          uint32_t const height)
        {
          uint32_t y_point = get_point(y, height);
        
          if (y_point >= height)
          {
            y_point = (height - 1);
          }
        
          // The range of 'height' is started from 1, so that
          // I have to subtract 1 from it.
          return (height - 1) - y_point;
        }
      
        uint8_t *
        buffer_pos(
          uint8_t * const buffer,
          uint32_t const x,
          uint32_t const y,
          uint32_t const rowstride)
        {
          return buffer + (y * rowstride) + x * sizeof(uint32_t);
        }
      
        void
        constrain_rgb(
          double_t * const r,
          double_t * const g,
          double_t * const b)
        {
          double w;
        
          // Amount of white needed is w = - min(0, *r, *g, *b)
          w = (0 < *r) ? 0 : *r;
          w = (w < *g) ? w : *g;
          w = (w < *b) ? w : *b;
          w = - w;
        
          // Add just enough white to make r, g, b all positive.
          if (w > 0)
          {
            *r += w;
            *g += w;
            *b += w;
          }
        }
      }
    
      /// The color format of the result buffer is
      ///
      /// high addr     low addr
      ///      A   B   G   R
      ///
      /// \param func 
      /// \param width 
      /// \param height 
      ///
      void
      draw_to_buffer(
        uint8_t * const buffer,
        Type const type,
        uint32_t const width, uint32_t const height, uint32_t const rowstride)
      {
        // Clear the buffer to black.
        for (uint32_t i = 0; i < height; ++i)
        {
          memset(buffer + i * rowstride, 0, width * sizeof(uint32_t));
        }
      
        uint32_t valid_wavelength_start, valid_wavelength_end;
        CieColorMatchFunc::Type cmf_type;
        double_t const (*value_table)[3];
      
        switch (type)
        {
        case TYPE_CIE1931:
          valid_wavelength_start = CieColorMatchFunc::CIE1931::value_table_wavelength_start;
          valid_wavelength_end = CieColorMatchFunc::CIE1931::value_table_wavelength_end;
        
          cmf_type = CieColorMatchFunc::TYPE_CIE1931;
          value_table = &(CieColorMatchFunc::CIE1931::value_table[0]);
          break;
        
        case TYPE_CIE1964:
          valid_wavelength_start = CieColorMatchFunc::CIE1964::value_table_wavelength_start;
          valid_wavelength_end = CieColorMatchFunc::CIE1964::value_table_wavelength_end;
        
          cmf_type = CieColorMatchFunc::TYPE_CIE1964;
          value_table = &(CieColorMatchFunc::CIE1964::value_table[0]);
          break;
        
        default:
          assert(0);
        
          valid_wavelength_start = 0;
          valid_wavelength_end = 0;
        
          cmf_type = CieColorMatchFunc::TYPE_CIE1964;
          value_table = 0;
          break;
        }
      
        // Draw the CIE tongue outline.
        {
          uint32_t last_x_point = 0, last_y_point = 0;
          uint32_t prev_x_point = last_x_point, prev_y_point = last_y_point;
          uint32_t first_x_point = last_x_point, first_y_point = last_y_point;
          
          // The following assertion must be true,
          // otherwise, the following drawing algorithm may
          // not be correct.
          assert(valid_wavelength_end >= valid_wavelength_start);
          
          for (uint32_t curr_wavelength = valid_wavelength_start;
               curr_wavelength <= valid_wavelength_end;
               ++curr_wavelength)
          {
            double_t x, y;
          
            get_normalized_xy(cmf_type, curr_wavelength, &x, &y);
          
            assert((x <= 1) && (x >= 0));
            assert((y <= 1) && (y >= 0));
            
            // I will treat width & height as 0.0~1.0 for
            // x_bar & y_bar.
            last_x_point = get_x_point(x, width);
            last_y_point = get_y_point(y, height);
            
            if (curr_wavelength > valid_wavelength_start)
            {
              Drawinglib::draw_line(buffer,
                                    width, height, rowstride,
                                    0xFF, 0xFF, 0xFF, 0xFF,
                                    prev_x_point, prev_y_point,
                                    last_x_point, last_y_point);
            }
            else
            {
              first_x_point = last_x_point;
              first_y_point = last_y_point;
            }
            
            prev_x_point = last_x_point;
            prev_y_point = last_y_point;
          }
          
          Wcl::Drawinglib::draw_line(buffer,
                                     width, height, rowstride,
                                     0xFF, 0xFF, 0xFF, 0xFF,
                                     first_x_point, first_y_point,
                                     last_x_point, last_y_point);
        }
        
        // Now scan the image line by line and  fill  the  tongue  outline
        // with the RGB values determined by the colour system for the x-y
        // co-ordinates within the tongue.
        ColorSpaceConverter converter;
        
        {
          std::list<std::wstring> src_color_space_names;
          src_color_space_names.push_back(L"CIE");
          src_color_space_names.push_back(L"CIE1931_XYZ");
          
          converter.assign_src_color_space(src_color_space_names);
        }
        
        {
          std::list<std::wstring> dst_color_space_names;
          dst_color_space_names.push_back(L"RGB");
          dst_color_space_names.push_back(L"sRGB");
          
          converter.assign_dst_color_space(dst_color_space_names);
        }
        
        for (uint32_t y = 0; y < height; ++y)
        {
          uint32_t first_x_point = 0, last_x_point = first_x_point;
          
          // Find horizontal extents of tongue on this line.
          for (first_x_point = 0; first_x_point < width; ++first_x_point)
          {
            if ((*buffer_pos(buffer, first_x_point, y, rowstride)) != 0)
            {
              for (last_x_point = (width - 1); last_x_point >= first_x_point; --last_x_point)
              {
                if ((*buffer_pos(buffer, last_x_point, y, rowstride)) != 0)
                {
                  break;
                }
              }
              break;
            }
          }
          
          if (first_x_point < width)
          {
            for (uint32_t curr_x_point = first_x_point;
                 curr_x_point <= last_x_point;
                 ++curr_x_point)
            {
              double_t const cx = (static_cast<double_t>(curr_x_point) / (width - 1));
              double_t const cy = 1.0 - (static_cast<double_t>(y) / (height - 1));
              double_t const cz = 1.0 - (cx + cy);
              
              std::vector<ColorSpaceBasicUnitValue> src_data;
              src_data.push_back(ColorSpaceBasicUnitValue(cx));
              src_data.push_back(ColorSpaceBasicUnitValue(cy));
              src_data.push_back(ColorSpaceBasicUnitValue(cz));
              
              std::vector<ColorSpaceBasicUnitValue> dst_data;
              
              converter.convert(src_data, dst_data);
              assert(3 == dst_data.size());
              
              double_t jr = dst_data[0].get_value<double_t>();
              double_t jg = dst_data[1].get_value<double_t>();
              double_t jb = dst_data[2].get_value<double_t>();
              
              // Check whether the requested colour  is  within  the
              // gamut  achievable with the given colour system.  If
              // not, draw it in a reduced  intensity,  interpolated
              // by desaturation to the closest within-gamut colour.
              constrain_rgb(&jr, &jg, &jb);
              
              // Scale to max(rgb) = 1.
              double_t const jmax = std::max(jr, std::max(jg, jb));
            
              if (jmax > 0)
              {
                jr = jr / jmax;
                jg = jg / jmax;
                jb = jb / jmax;
              }
            
              uint8_t const r = boost::numeric_cast<uint8_t>(255 * jr);
              uint8_t const g = boost::numeric_cast<uint8_t>(255 * jg);
              uint8_t const b = boost::numeric_cast<uint8_t>(255 * jb);
            
              Wcl::Drawinglib::draw_pixel(buffer, width, height, rowstride,
                                          r, g, b, 255,
                                          curr_x_point, y);
            }
          }
        }
      }
    }
  }
}
