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
    draw_line(
      uint8_t * const buffer,
      uint32_t const width, uint32_t const height, int32_t const rowstride,
      uint8_t const red, uint8_t const green, uint8_t const blue, uint8_t const alpha,
      uint32_t x0, uint32_t y0,
      uint32_t x1, uint32_t y1)
    {
      int32_t dy = y1 - y0;
      int32_t dx = x1 - x0;
      int32_t stepx, stepy;
    
      if (dy < 0)
      {
        dy = -dy;
        stepy = -rowstride;
      }
      else
      {
        stepy = rowstride;
      }
    
      int32_t const bpp = 4;
    
      if (dx < 0)
      {
        dx = -dx;
        stepx = -bpp;
      }
      else
      {
        stepx = bpp;
      }
    
      dy <<= 1;
      dx <<= 1;
    
      y0 *= rowstride;
      y1 *= rowstride;
    
      x0 *= bpp;
      x1 *= bpp;
    
      uint8_t *pos = buffer + (x0 + y0);
    
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
    
      if (dx > dy)
      {
        int fraction = dy - (dx >> 1);
      
        while (x0 != x1)
        {
          if (fraction >= 0)
          {
            y0 += stepy;
            fraction -= dx;
          }
        
          x0 += stepx;
          fraction += dy;
        
          pos = buffer + (x0 + y0);
        
          assert(pos >= buffer);
          assert((pos + 3) < (buffer + (rowstride * (height - 1)) + (width * bpp)));
        
          (*(pos + 0)) = red;
          (*(pos + 1)) = green;
          (*(pos + 2)) = blue;
          (*(pos + 3)) = alpha;
        }
      }
      else
      {
        int fraction = dx - (dy >> 1);
      
        while (y0 != y1)
        {
          if (fraction >= 0)
          {
            x0 += stepx;
            fraction -= dy;
          }
        
          y0 += stepy;
          fraction += dx;
        
          pos = buffer + (x0 + y0);
        
          assert(pos >= buffer);
          assert((pos + 3) < (buffer + (rowstride * (height - 1)) + (width * bpp)));
        
          (*(pos + 0)) = red;
          (*(pos + 1)) = green;
          (*(pos + 2)) = blue;
          (*(pos + 3)) = alpha;
        }
      }
    }
  }
}
