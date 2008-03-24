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

#ifndef __plugin_hpp__
#define __plugin_hpp__

#include "..\..\wcl_colorlib\include\subsampling_converter.hpp"
#include "..\..\wcl_colorlib\include\subsampling_converter_plugin.hpp"

#if defined(WCL_COLORLIB_SUBSAMPLING_CONVERTER_PLUGIN_CUSTOM_YUV444_EXPORTS)
#define WCL_COLORLIB_PLUGIN_EXPORT __declspec(dllexport)
#else
#define WCL_COLORLIB_PLUGIN_EXPORT __declspec(dllimport)
#endif

namespace Wcl
{
  namespace Colorlib
  {
    class SubSamplingConverterPluginCustomYuv444 : public virtual SubSamplingConverterPlugin
    {
    private:
      
      virtual void get_ycbcr_color_space_name(std::list<std::wstring> &names);
      
      SubSamplingConverterPluginCustomYuv444 &operator=(SubSamplingConverterPluginCustomYuv444 const &plugin);
      
    public:
      
      /**
       * @name life cycle
       */
      //@{
      SubSamplingConverterPluginCustomYuv444(
        SubSamplingConverter * const converter)
        : SUBSAMPLING_CONVERTER_PLUGIN_SET_CONVERTER(converter)
      {}
      
      virtual ~SubSamplingConverterPluginCustomYuv444() {}
      //@}
      
      /** @name Conversion
       */
      //@{
      WCL_COLORLIB_PLUGIN_EXPORT void convert_to_yuv444(
        std::vector<ColorSpaceBasicUnitValue> const &src_buffer,
        std::vector<ColorSpaceBasicUnitValue> &yuv444_buffer,
        uint32_t const width,
        uint32_t const height);
      
      WCL_COLORLIB_PLUGIN_EXPORT void convert_from_yuv444(
        std::vector<ColorSpaceBasicUnitValue> &dst_buffer,
        std::vector<ColorSpaceBasicUnitValue> const &yuv444_buffer,
        uint32_t const width,
        uint32_t const height);
      //@}
    };
    typedef class SubSamplingConverterPluginCustomYuv444 SubSamplingConverterPluginCustomYuv444;
  }
}

#endif
