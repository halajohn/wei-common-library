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

#ifndef __cie_hpp__
#define __cie_hpp__

#include "wcl_types.hpp"

namespace wcl_colorlib
{
  namespace Cie
  {
    typedef enum
    {
      CIE_STD_1931,
      CIE_STD_1964
    } CieStd;
    
    typedef wcl_double (*CieSpectrumFunc)(wcl_double const wavelength);
    
    static void spectrum_to_xyz(
      CieSpectrumFunc const spectrum_func,
      CieStd const cie_std,
      wcl_double * const x,
      wcl_double * const y,
      wcl_double * const z);
  }
}

#endif
