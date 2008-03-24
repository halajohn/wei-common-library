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

#ifndef __wcl_colorlib_color_space_converter_plugin_internal_hpp__
#define __wcl_colorlib_color_space_converter_plugin_internal_hpp__

namespace Wcl
{
  namespace Colorlib
  {
    template<typename T>
    void
    check_valid_input_value(
      T const * const object,
      uint32_t const idx,
      ColorSpaceBasicUnitValue const &value)
    {
      object->T::check_valid_input_idx(idx);
      
      std::vector<std::pair<ColorSpaceBasicUnitValue, ColorSpaceBasicUnitValue> > ranges;
      
      object->T::get_input_data_range(idx, ranges);
      
      typedef std::pair<ColorSpaceBasicUnitValue, ColorSpaceBasicUnitValue> element_type;
      
      BOOST_FOREACH(element_type const &range, ranges)
      {
        if ((value >= range.first) && (value <= range.second))
        {
          return;
        }
      }
      
      throw InvalidInputValueException();
    }
  }
}

#endif
