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

#include "cie_color_match_func.hpp"
#include "cie_color_match_func_internal.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    namespace CieColorMatchFunc
    {
      void
      get_x_bar_y_bar_z_bar(
        Type const type,
        double_t const wavelength,
        double_t * const x_bar, double_t * const y_bar, double_t * const z_bar)
      {
        uint32_t valid_wavelength_start, valid_wavelength_end;
        double_t const (*value_table)[3];
      
        switch (type)
        {
        case TYPE_CIE1931:
          valid_wavelength_start = CIE1931::value_table_wavelength_start;
          valid_wavelength_end = CIE1931::value_table_wavelength_end;
        
          value_table = &(CIE1931::value_table[0]);
          break;
        
        case TYPE_CIE1964:
          valid_wavelength_start = CIE1964::value_table_wavelength_start;
          valid_wavelength_end = CIE1964::value_table_wavelength_end;
        
          value_table = &(CIE1964::value_table[0]);
          break;
        
        default:
          assert(0);
        
          valid_wavelength_start = 0;
          valid_wavelength_end = 0;
        
          value_table = 0;
          break;
        }
      
        double_t x_bar_, y_bar_, z_bar_;
      
        if ((wavelength > valid_wavelength_end) ||
            (wavelength < valid_wavelength_start))
        {
          // Out-of-range.
          x_bar_ = 0;
          y_bar_ = 0;
          z_bar_ = 0;
        }
        else if (static_cast<uint32_t>(wavelength) == wavelength)
        {
          // Exactly.
          uint32_t const index = static_cast<uint32_t>(wavelength) - valid_wavelength_start;
        
          x_bar_ = value_table[index][0];
          y_bar_ = value_table[index][1];
          z_bar_ = value_table[index][2];
        }
        else
        {
          // Between 2 values in the table, linearly interpolate them.
          uint32_t const lower_index = static_cast<uint32_t>(wavelength);
          uint32_t const upper_index = lower_index + 1;
        
          double_t const lower_index_x_bar_ = value_table[lower_index - valid_wavelength_start][0];
          double_t const lower_index_y_bar_ = value_table[lower_index - valid_wavelength_start][1];
          double_t const lower_index_z_bar_ = value_table[lower_index - valid_wavelength_start][2];
        
          double_t const upper_index_x_bar_ = value_table[upper_index - valid_wavelength_start][0];
          double_t const upper_index_y_bar_ = value_table[upper_index - valid_wavelength_start][1];
          double_t const upper_index_z_bar_ = value_table[upper_index - valid_wavelength_start][2];
        
          x_bar_ = (lower_index_x_bar_ + upper_index_x_bar_) / 2;
          y_bar_ = (lower_index_y_bar_ + upper_index_y_bar_) / 2;
          z_bar_ = (lower_index_z_bar_ + upper_index_z_bar_) / 2;
        }
      
        if (x_bar != 0)
        {
          (*x_bar) = x_bar_;
        }
      
        if (y_bar != 0)
        {
          (*y_bar) = y_bar_;
        }
      
        if (z_bar != 0)
        {
          (*z_bar) = z_bar_;
        }
      }
    
      void
      get_normalized_xy(
        Type const type,
        double_t const wavelength,
        double_t * const x, double_t * const y)
      {
        double_t x_bar, y_bar, z_bar;
      
        get_x_bar_y_bar_z_bar(type, wavelength, &x_bar, &y_bar, &z_bar);
      
        if (x != 0)
        {
          (*x) = (x_bar / (x_bar + y_bar + z_bar));
        }
      
        if (y != 0)
        {
          (*y) = (y_bar / (x_bar + y_bar + z_bar));
        }
      }
    }
  }
}
