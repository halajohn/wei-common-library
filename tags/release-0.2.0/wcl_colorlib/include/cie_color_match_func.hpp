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

#ifndef __wcl_colorlib_cie_color_match_func_hpp__
#define __wcl_colorlib_cie_color_match_func_hpp__

#include "export.hpp"
#include "wcl_types.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    namespace CieColorMatchFunc
    {
      enum Type
      {
        TYPE_CIE1931,
        TYPE_CIE1964
      };
      typedef enum Type Type;
    
      WCL_COLORLIB_EXPORT extern void get_x_bar_y_bar_z_bar(
        Type const type,
        double_t const wavelength,
        double_t * const x_bar, double_t * const y_bar, double_t * const z_bar);
    
      WCL_COLORLIB_EXPORT extern void get_normalized_xy(
        Type const type,
        double_t const wavelength,
        double_t * const x, double_t * const y);
    }
  }
}

#endif
