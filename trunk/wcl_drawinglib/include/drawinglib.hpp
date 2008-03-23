// wcl_drawinglib - portable drawing library
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

#ifndef __wcl_drawinglib_hpp__
#define __wcl_drawinglib_hpp__

#if defined(WCL_DRAWINGLIB_EXPORTS)
#define WCL_DRAWINGLIB_EXPORT __declspec(dllexport)
#else
#define WCL_DRAWINGLIB_EXPORT __declspec(dllimport)
#endif

#include "wcl_types.hpp"

namespace Wcl
{
  namespace Drawinglib
  {
    WCL_DRAWINGLIB_EXPORT extern void draw_line(
      uint8_t * const buffer,
      uint32_t const width, uint32_t const height, int32_t const rowstride,
      uint8_t const red, uint8_t const green, uint8_t const blue, uint8_t const alpha,
      uint32_t x1, uint32_t y1,
      uint32_t x2, uint32_t y2);
    
    WCL_DRAWINGLIB_EXPORT extern void draw_pixel(
      uint8_t * const buffer,
      uint32_t const width, uint32_t const height, int32_t const rowstride,
      uint8_t const red, uint8_t const green, uint8_t const blue, uint8_t const alpha,
      uint32_t x, uint32_t y);
  }
}

#endif
