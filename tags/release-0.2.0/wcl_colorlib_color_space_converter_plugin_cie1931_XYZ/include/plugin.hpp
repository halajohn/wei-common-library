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

#ifndef __wcl_colorlib_color_space_converter_plugin_cie1931_xyz_plugin_hpp__
#define __wcl_colorlib_color_space_converter_plugin_cie1931_xyz_plugin_hpp__

#include "..\..\wcl_colorlib\include\color_space_converter.hpp"
#include "..\..\wcl_colorlib\include\color_space_converter_plugin.hpp"
#include "..\..\wcl_colorlib\include\color_space_converter_plugin_internal.hpp"
#include "..\..\wcl_colorlib\include\exception.hpp"

#if defined(WCL_COLORLIB_COLOR_SPACE_CONVERTER_PLUGIN_CIE1931_XYZ_EXPORTS)
#define WCL_COLORLIB_CIE1931XYZ_PLUGIN_EXPORT __declspec(dllexport)
#else
#define WCL_COLORLIB_CIE1931XYZ_PLUGIN_EXPORT __declspec(dllimport)
#endif

namespace Wcl
{
  namespace Colorlib
  {
    class ColorSpaceConverterPluginCie1931XYZ : public virtual ColorSpaceConverterPlugin
    {
    public:
      
      /** @name Life cycle
       */
      //@{
      WCL_COLORLIB_CIE1931XYZ_PLUGIN_EXPORT ColorSpaceConverterPluginCie1931XYZ(
        ColorSpaceConverter * const converter)
        : COLOR_SPACE_CONVERTER_PLUGIN_SET_CONVERTER(converter)
      {}
      
      WCL_COLORLIB_CIE1931XYZ_PLUGIN_EXPORT virtual ~ColorSpaceConverterPluginCie1931XYZ() {}
      //@}
      
      /** @name Conversion
       */
      //@{
      virtual bool convert_to_cie1931_XYZ(
        std::vector<ColorSpaceBasicUnitValue> const &src_data,
        std::vector<ColorSpaceBasicUnitValue> &dst_data,
        uint32_t const dst_plugin_id);
      
      virtual void convert_from_cie1931_XYZ(
        std::vector<ColorSpaceBasicUnitValue> const &src_data,
        std::vector<ColorSpaceBasicUnitValue> &dst_data,
        uint32_t const src_plugin_id);
      //@}
      
      /** @name Querying
       */
      //@{
      virtual void get_input_data_range(
        uint32_t const idx,
        std::vector<std::pair<ColorSpaceBasicUnitValue, ColorSpaceBasicUnitValue> > &ranges) const;
      
      virtual uint32_t get_subcomponent_count() const;
      
      virtual ColorSpaceBasicUnitValueType get_basic_unit_value_type() const;
      //@}
      
      /** @name Checking
       */
      //@{
      virtual void check_valid_input_idx(
        uint32_t const idx) const;
      
      virtual void check_valid_input_value(
        uint32_t const idx,
        ColorSpaceBasicUnitValue const &value) const;
      //@}
    };
    typedef class ColorSpaceConverterPluginCie1931XYZ ColorSpaceConverterPluginCie1931XYZ;
  }
}

#endif
