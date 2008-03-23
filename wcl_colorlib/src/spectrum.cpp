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

#include "spectrum.hpp"
#include "cie_color_match_func.hpp"
#include "color_space_converter.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    namespace Spectrum
    {
      double_t
      equal_energy_spd_func(
        double_t const /* wavelength */)
      {
        return 1.0;
      }
    
      namespace
      {
        void
        make_rgb_value_into_0_to_1_range(
          double_t * const r, double_t * const g, double_t * const b)
        {
          assert(r != 0);
          assert(g != 0);
          assert(b != 0);
        
          // :TODO: This can be improved.
          if ((*r) > 1) { (*r) = 1; }
          if ((*r) < 0) { (*r) = 0; }
          if ((*g) > 1) { (*g) = 1; }
          if ((*g) < 0) { (*g) = 0; }
          if ((*b) > 1) { (*b) = 1; }
          if ((*b) < 0) { (*b) = 0; }
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
        SpectralPowerDistFunc const func,
        double_t const wavelength_start, double_t const wavelength_end,
        uint32_t const width, uint32_t const height, uint32_t const rowstride,
        uint8_t const alpha_value)
      {
        double_t const wavelength_range = wavelength_end - wavelength_start;
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
        
        uint8_t *output_addr = buffer;
      
        for (uint32_t i = 0; i < width; ++i)
        {
          double_t x_bar, y_bar, z_bar;
          double_t const wavelength = wavelength_start + wavelength_range * (boost::numeric_cast<double_t>(i) / width);
        
          CieColorMatchFunc::get_x_bar_y_bar_z_bar(CieColorMatchFunc::TYPE_CIE1931, wavelength, &x_bar, &y_bar, &z_bar);
        
          double_t const E = func(wavelength);
        
          double_t const X = E * x_bar;
          double_t const Y = E * y_bar;
          double_t const Z = E * z_bar;
        
          std::vector<ColorSpaceBasicUnitValue> src_data;
          src_data.push_back(ColorSpaceBasicUnitValue(X));
          src_data.push_back(ColorSpaceBasicUnitValue(Y));
          src_data.push_back(ColorSpaceBasicUnitValue(Z));
          
          std::vector<ColorSpaceBasicUnitValue> dst_data;
          
          converter.convert(src_data, dst_data);
        
          assert(3 == dst_data.size());
          
          double_t r = dst_data[0].get_value<double_t>();
          double_t g = dst_data[1].get_value<double_t>();
          double_t b = dst_data[2].get_value<double_t>();
          
          make_rgb_value_into_0_to_1_range(&r, &g, &b);
        
          assert((output_addr + 3) <= (buffer + (rowstride * (height - 1)) + (width * sizeof(uint32_t))));
        
          (*output_addr) = static_cast<uint8_t>(r * 255);
          ++output_addr;
        
          (*output_addr) = static_cast<uint8_t>(g * 255);
          ++output_addr;
        
          (*output_addr) = static_cast<uint8_t>(b * 255);
          ++output_addr;
        
          (*output_addr) = alpha_value;
          ++output_addr;
        }
      
        uint32_t const copied_size = width * sizeof(uint32_t);
      
        for (uint32_t i = 1; i < height; ++i)
        {
          memcpy(buffer + i * rowstride, buffer, copied_size);
        }
      }
    }
  }
}
