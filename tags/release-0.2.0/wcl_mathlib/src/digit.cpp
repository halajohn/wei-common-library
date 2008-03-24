#include "precompiled_header.hpp"

// wcl_mathlib - portable math library
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

#include "digit.hpp"

namespace Wcl
{
  namespace Mathlib
  {
    namespace Digit
    {
      /* The complexity of this method is log_2^32=8 (This format is from Latex);
       * it is better than iterating in a for loop 32 times.
       */
      uint32_t
      count_binary_bit_one_number(
        uint32_t value)
      {
        value = ((value >>  1) & 0x55555555) + (value & 0x55555555);
        value = ((value >>  2) & 0x33333333) + (value & 0x33333333);
        value = ((value >>  4) & 0x0F0F0F0F) + (value & 0x0F0F0F0F);
        value = ((value >>  8) & 0x00FF00FF) + (value & 0x00FF00FF);
        value = ((value >> 16) & 0x0000FFFF) + (value & 0x0000FFFF);
  
        return value;
      }

      /* Ex:
       * base_10_digit_number(3) == 1
       * base_10_digit_number(13) == 2
       * base_10_digit_number(133) == 3
       */
      uint32_t
      count_digit_number_in_base_10(
        uint32_t value)
      {
        uint32_t digit = 0;
  
        while (value > 0)
        {
          ++digit;
    
          value /= 10;
        }
  
        return digit;
      }
    }
  }
}
