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

#include "color_space_converter.hpp"
#include "color_space_converter_plugin.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    ColorSpaceConverterPlugin::ColorSpaceConverterPlugin(ColorSpaceConverter * const converter)
      : COLOR_SPACE_CONVERTER_PLUGIN_SET_CONVERTER(converter)
    {}
  }
}
