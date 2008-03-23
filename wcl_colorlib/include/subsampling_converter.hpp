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

#ifndef __wcl_colorlib_subsampling_converter_hpp__
#define __wcl_colorlib_subsampling_converter_hpp__

#include "export.hpp"
#include "converter.hpp"
#include "color_space_basic_unit_value.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    // Forward declaration.
    class SubSamplingConverterPlugin;
    
    class SubSamplingConverter : public virtual Converter<SubSamplingConverterPlugin>
    {
    private:
      
      progress_stage_name_cb_func_t mp_stage_name_cb;
      void *mp_stage_name_cb_param;
      
      progress_percentage_cb_func_t mp_percentage_cb;
      void *mp_percentage_cb_param;
      
      // This class should never be copied.
      SubSamplingConverter &operator=(SubSamplingConverter const &);
      
      void convert_to_yuv444(
        std::vector<ColorSpaceBasicUnitValue> const &src_buffer,
        std::vector<ColorSpaceBasicUnitValue> &yuv444_buffer,      
        uint32_t const width,
        uint32_t const height);
      
      void convert_from_yuv444(
        std::vector<ColorSpaceBasicUnitValue> const &yuv444_buffer,
        std::vector<ColorSpaceBasicUnitValue> &dst_buffer,
        uint32_t const width,
        uint32_t const height);
      
      template<PluginType T>
      void check_if_the_other_plugin_is_different_custom(std::list<std::wstring> const &name);
      
      /** @name Special subsampling plugin
       *
       * There are 1 special subsampling converter plugin
       * which can interrupt the whole subsampling
       * conversion procedure and return the result value
       * immediately.
       */
      //@{
      WCL_COLORLIB_EXPORT static uint32_t g_custom_yuv444_plugin_id;
      //@}
      
    public:
      
#if defined(WCL_COLORLIB_USE_REGISTRY)
      WCL_COLORLIB_EXPORT static wchar_t const * const PLUGIN_ROOT_DIR_REGISTRY_KEY_NAME;
      WCL_COLORLIB_EXPORT static wchar_t const * const PLUGIN_ROOT_DIR_STR_LENGTH_REGISTRY_KEY_NAME;
#endif
      
      /** @name Life cycle
       */
      //@{
      WCL_COLORLIB_EXPORT SubSamplingConverter();
      WCL_COLORLIB_EXPORT ~SubSamplingConverter();
      //@}
      
      WCL_COLORLIB_EXPORT static uint32_t get_custom_yuv444_plugin_id();
      
      /** @name Setting
       */
      //@{
      WCL_COLORLIB_EXPORT void assign_src_subsampling(std::list<std::wstring> const &name);
      WCL_COLORLIB_EXPORT void assign_dst_subsampling(std::list<std::wstring> const &name);
      
      WCL_COLORLIB_EXPORT void assign_src_subsampling(
        PluginInfo<SubSamplingConverterPlugin> * const info);
      
      WCL_COLORLIB_EXPORT void assign_dst_subsampling(
        PluginInfo<SubSamplingConverterPlugin> * const info);
      
      WCL_COLORLIB_EXPORT void register_stage_name_cb(
        progress_stage_name_cb_func_t const cb,
        void *param);
      
      WCL_COLORLIB_EXPORT void register_percentage_cb(
        progress_percentage_cb_func_t const cb,
        void *param);
      //@}
      
      /** @name Conversion
       */
      //@{
      WCL_COLORLIB_EXPORT void convert_buffer(
        std::vector<ColorSpaceBasicUnitValue> const &src_buffer,
        std::vector<ColorSpaceBasicUnitValue> &dst_buffer,
        uint32_t const width,
        uint32_t const height);
      //@}
    };
    typedef class SubSamplingConverter SubSamplingConverter;
  }
}

#endif
