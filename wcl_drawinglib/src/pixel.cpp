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

#include <cassert>
#include "drawinglib.hpp"

namespace Wcl
{
  namespace Drawinglib
  {
    void
    draw_pixel(
      uint8_t * const buffer,
      uint32_t const width, uint32_t const height, int32_t const rowstride,
      uint8_t const red, uint8_t const green, uint8_t const blue, uint8_t const alpha,
      uint32_t x, uint32_t y)
    {
      int32_t const bpp = 4;
    
      y *= rowstride;
      x *= bpp;
    
      uint8_t *pos = buffer + (x + y);
    
#if !defined(_DEBUG)
      // Add these 2 lines in release build to avoid Visual C++
      // complains about:
      //
      // warning C4100: 'height' : unreferenced formal parameter
      (void)width;
      (void)height;
#endif
      assert(pos >= buffer);
      assert((pos + 3) < (buffer + (rowstride * (height - 1)) + (width * bpp)));
    
      (*(pos + 0)) = red;
      (*(pos + 1)) = green;
      (*(pos + 2)) = blue;
      (*(pos + 3)) = alpha;
    }
  }
}
