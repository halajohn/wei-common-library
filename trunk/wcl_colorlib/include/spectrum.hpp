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

#ifndef __wcl_colorlib_spectrum_hpp__
#define __wcl_colorlib_spectrum_hpp__

#include "export.hpp"
#include "wcl_types.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    namespace Spectrum
    {
      typedef double_t (*SpectralPowerDistFunc)(double_t const wavelength);
    
      WCL_COLORLIB_EXPORT extern double_t equal_energy_spd_func(
        double_t const wavelength);
    
      WCL_COLORLIB_EXPORT extern void draw_to_buffer(
        uint8_t * const buffer,
        SpectralPowerDistFunc const func,
        double_t const wavelength_start, double_t const wavelength_end,
        uint32_t const width, uint32_t const height, uint32_t const rowstride,
        uint8_t const alpha_value);
    }
  }
}

#endif
