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

#ifndef __wcl_colorlib_color_space_converter_plugin_hpp__
#define __wcl_colorlib_color_space_converter_plugin_hpp__

#include "converter.hpp"
#include "converter_plugin.hpp"
#include "color_space_basic_unit_value.hpp"

#define COLOR_SPACE_CONVERTER_PLUGIN_SET_CONVERTER(converter) ConverterPlugin<ColorSpaceConverter, ColorSpaceConverterPlugin>(converter)

namespace Wcl
{
  namespace Colorlib
  {
    class ColorSpaceConverter;

    /**
     * This class is the base class of all color space
     * converter plugin. It defines interface functions
     * which all color space converter plugin needs to define.
     */
    class ColorSpaceConverterPlugin : public virtual ConverterPlugin<ColorSpaceConverter, ColorSpaceConverterPlugin>
    {
    protected:
      
      /** @name life cycle
       */
      //@{
      /**
       * Because class derived from this class should treat
       * this class as its virtual base class. So that I
       * have to provide a default constructor, then derived
       * classes would not initialize this class
       * explicitly.
       */
      ColorSpaceConverterPlugin()
        : COLOR_SPACE_CONVERTER_PLUGIN_SET_CONVERTER(0)
      { }
      //@}
      
      ColorSpaceConverterPlugin(ColorSpaceConverterPlugin const &plugin);
      ColorSpaceConverterPlugin &operator=(ColorSpaceConverterPlugin const &plugin);
      
    public:
      
      /** @name life cycle
       */
      //@{
      virtual ~ColorSpaceConverterPlugin() {}
      //@}
      
      /** @name Conversion
       */
      //@{
      virtual bool convert_to_cie1931_XYZ(
        std::vector<ColorSpaceBasicUnitValue> const &src_data,
        std::vector<ColorSpaceBasicUnitValue> &dst_data,
        uint32_t const dst_plugin_id) = 0;
      
      virtual void convert_from_cie1931_XYZ(
        std::vector<ColorSpaceBasicUnitValue> const &src_data,
        std::vector<ColorSpaceBasicUnitValue> &dst_data,
        uint32_t const src_plugin_id) = 0;
      //@}
      
      /** @name Querying
       */
      //@{
      virtual void get_input_data_range(
        uint32_t const idx,
        std::vector<std::pair<ColorSpaceBasicUnitValue, ColorSpaceBasicUnitValue> > &ranges) const = 0;
      
      virtual uint32_t get_subcomponent_count() const = 0;
      
      virtual ColorSpaceBasicUnitValueType get_basic_unit_value_type() const = 0;
      //@}
      
      /** @name Checking
       */
      //@{
      virtual void check_valid_input_idx(
        uint32_t const idx) const = 0;
      
      virtual void check_valid_input_value(
        uint32_t const idx,
        ColorSpaceBasicUnitValue const &value) const = 0;
      //@}
    };
    typedef class ColorSpaceConverterPlugin ColorSpaceConverterPlugin;
  }
}

#endif
