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

#ifndef __wcl_colorlib_color_space_converter_hpp__
#define __wcl_colorlib_color_space_converter_hpp__

#include "converter.hpp"
#include "color_space_basic_unit_value.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    class ColorSpaceConverterPlugin;
    
    /**
     * The intermedia color space format of
     * 'ColorSpaceConverter' is CIE 1931 XYZ model.
     *
     * That is to say,
     *
     *
     *  o -                  - o
     *     \                /
     *  o --- CIE 1931 XYZ --- o
     *     /                \
     *  o -                  - o
     *
     */
    class ColorSpaceConverter : public Converter<ColorSpaceConverterPlugin>
    {
    private:
      
      progress_percentage_cb_func_t mp_percentage_cb;
      void *mp_percentage_cb_param;
      
      /** @name Special color space plugin
       *
       * There are 3 special Color space converter plugins
       * which can interrupt the whole color space
       * conversion procedure and return the result value
       * immediately.
       */
      //@{
      WCL_COLORLIB_EXPORT static uint32_t g_custom_ycbcr_plugin_id;
      WCL_COLORLIB_EXPORT static uint32_t g_custom_ypbpr_plugin_id;
      WCL_COLORLIB_EXPORT static uint32_t g_custom_rgb_plugin_id;
      //@}
      
      template<PluginType T>
      void check_if_the_other_plugin_is_different_custom(std::list<std::wstring> const &name);
      
    public:
      
#if defined(WCL_COLORLIB_USE_REGISTRY)
      WCL_COLORLIB_EXPORT static wchar_t const * const PLUGIN_ROOT_DIR_REGISTRY_KEY_NAME;
      WCL_COLORLIB_EXPORT static wchar_t const * const PLUGIN_ROOT_DIR_STR_LENGTH_REGISTRY_KEY_NAME;
#endif
      
      WCL_COLORLIB_EXPORT static uint32_t get_custom_ycbcr_plugin_id();
      WCL_COLORLIB_EXPORT static uint32_t get_custom_ypbpr_plugin_id();
      WCL_COLORLIB_EXPORT static uint32_t get_custom_rgb_plugin_id();
      
      /** @name Life cycle
       */
      //@{
      WCL_COLORLIB_EXPORT ColorSpaceConverter()
        : mp_percentage_cb(0),
          mp_percentage_cb_param(0)
      {}
      
      WCL_COLORLIB_EXPORT ~ColorSpaceConverter() {}
      //@}
      
      /** @name Setting
       */
      //@{
      WCL_COLORLIB_EXPORT void assign_src_color_space(std::list<std::wstring> const &name);
      WCL_COLORLIB_EXPORT void assign_dst_color_space(std::list<std::wstring> const &name);
      WCL_COLORLIB_EXPORT void assign_src_color_space(
        PluginInfo<ColorSpaceConverterPlugin> * const info);
      WCL_COLORLIB_EXPORT void assign_dst_color_space(
        PluginInfo<ColorSpaceConverterPlugin> * const info);
      
      WCL_COLORLIB_EXPORT void register_percentage_cb(
        progress_percentage_cb_func_t const cb,
        void *param)
      {
        mp_percentage_cb = cb;
        mp_percentage_cb_param = param;
      }
      //@}
      
      /** @name Querying
       */
      //@{
      WCL_COLORLIB_EXPORT void get_input_data_range(
        uint32_t const idx,
        std::vector<std::pair<ColorSpaceBasicUnitValue, ColorSpaceBasicUnitValue> > &ranges) const;
      
      WCL_COLORLIB_EXPORT uint32_t get_input_data_subcomponent_count() const;
      WCL_COLORLIB_EXPORT uint32_t get_output_data_subcomponent_count() const;
      
      WCL_COLORLIB_EXPORT ColorSpaceBasicUnitValueType get_input_data_basic_unit_value_type() const;
      WCL_COLORLIB_EXPORT ColorSpaceBasicUnitValueType get_output_data_basic_unit_value_type() const;
      //@}
      
      /** @name Checking
       */
      //@{
      WCL_COLORLIB_EXPORT void check_valid_input_idx(
        uint32_t const idx) const;
      
      WCL_COLORLIB_EXPORT void check_valid_input_value(
        uint32_t const idx,
        ColorSpaceBasicUnitValue const &value) const;
      //@}
      
      /** @name Conversion
       */
      //@{
      WCL_COLORLIB_EXPORT void convert(
        std::vector<ColorSpaceBasicUnitValue> const &src_data,
        std::vector<ColorSpaceBasicUnitValue> &dst_data);
      
      WCL_COLORLIB_EXPORT void convert_buffer(
        std::vector<ColorSpaceBasicUnitValue> const &src_rgb_buffer,
        std::vector<ColorSpaceBasicUnitValue> &dst_rgb_buffer);
      //@}
    };
    typedef class ColorSpaceConverter ColorSpaceConverter;
  }
}

#endif
