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

#ifndef __wcl_colorlib_common_hpp__
#define __wcl_colorlib_common_hpp__

#include "wcl_types.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    WCL_COLORLIB_EXPORT extern void init();
    WCL_COLORLIB_EXPORT extern uint8_t clamp_for_rgb(double_t const value);
    WCL_COLORLIB_EXPORT extern double_t clamp_for_rgb(uint8_t const value);
  }
}

#endif
