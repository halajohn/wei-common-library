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

#ifndef __wcl_colorlib_subsampling_converter_plugin_hpp__
#define __wcl_colorlib_subsampling_converter_plugin_hpp__

#include "converter.hpp"
#include "converter_plugin.hpp"
#include "color_space_converter.hpp"

#define SUBSAMPLING_CONVERTER_PLUGIN_SET_CONVERTER(converter) ConverterPlugin<SubSamplingConverter, SubSamplingConverterPlugin>(converter)

namespace Wcl
{
  namespace Colorlib
  {
    class SubSamplingConverter;
    
    // This class is the base class of all subsampling
    // converter plugin. It defines interface functions
    // which all subsampling converter plugin needs to define.
    class SubSamplingConverterPlugin : public virtual ConverterPlugin<SubSamplingConverter, SubSamplingConverterPlugin>
    {
    private:
      
      SubSamplingConverterPlugin &operator=(SubSamplingConverterPlugin const &plugin);
      
    protected:
      
      /** @name life cycle
       */
      //@{
      SubSamplingConverterPlugin()
        : SUBSAMPLING_CONVERTER_PLUGIN_SET_CONVERTER(0),
          mp_percentage_cb(0),
          mp_percentage_cb_param(0)
      {}
      
      SubSamplingConverterPlugin(SubSamplingConverter * const converter);
      //@}
      
      progress_percentage_cb_func_t mp_percentage_cb;
      void *mp_percentage_cb_param;
      
    public:
      
      /** @name life cycle
       */
      //@{
      virtual ~SubSamplingConverterPlugin() {}
      //@}
      
      /** @name Querying
       */
      //@{
      virtual void get_ycbcr_color_space_name(std::list<std::wstring> &names) = 0;
      //@}
      
      /** @name Setting
       */
      //@{
      WCL_COLORLIB_EXPORT void register_percentage_cb(
        progress_percentage_cb_func_t const cb,
        void *param)
      {
        mp_percentage_cb = cb;
        mp_percentage_cb_param = param;
      }
      //@}
      
      /** @name Conversion
       */
      //@{
      virtual void convert_to_yuv444(
        std::vector<ColorSpaceBasicUnitValue> const &src_buffer,
        std::vector<ColorSpaceBasicUnitValue> &yuv444_buffer,
        uint32_t const width,
        uint32_t const height) = 0;
      
      virtual void convert_from_yuv444(
        std::vector<ColorSpaceBasicUnitValue> &dst_buffer,
        std::vector<ColorSpaceBasicUnitValue> const &yuv444_buffer,
        uint32_t const width,
        uint32_t const height) = 0;
      //@}
    };
    typedef class SubSamplingConverterPlugin SubSamplingConverterPlugin;
  }
}

#endif
