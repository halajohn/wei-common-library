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

#ifndef __wcl_colorlib_color_space_converter_plugin_smpte_240m_rgb_plugin_hpp__
#define __wcl_colorlib_color_space_converter_plugin_smpte_240m_rgb_plugin_hpp__

#if defined(WCL_COLORLIB_COLOR_SPACE_CONVERTER_PLUGIN_SMPTE_240M_RGB_EXPORTS)
#define WCL_COLORLIB_SMPTE_240M_RGB_PLUGIN_EXPORT __declspec(dllexport)
#else
#define WCL_COLORLIB_SMPTE_240M_RGB_PLUGIN_EXPORT __declspec(dllimport)
#endif

#include "wcl_types.hpp"
#include "..\..\wcl_colorlib\include\color_space_converter.hpp"
#include "..\..\wcl_colorlib\include\color_space_converter_plugin_rgb.hpp"
#include "..\..\wcl_colorlib\include\exception.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    class ColorSpaceConverterPluginSmpte240mRgb : public virtual ColorSpaceConverterPluginRgb
    {
    private:
      
      virtual void get_chromaticity_data(double &xr, double &yr,
                                         double &xg, double &yg,
                                         double &xb, double &yb,
                                         double &xw, double &yw) const;
      
    public:
      
      /** @name Life cycle
       */
      //@{
      ColorSpaceConverterPluginSmpte240mRgb(ColorSpaceConverter * const converter);
      
      virtual ~ColorSpaceConverterPluginSmpte240mRgb() {}
      //@}
      
      /** @name Querying
       */
      //@{
      virtual wchar_t const *get_rgb_plugin_name() const;
      
      virtual void get_rgb_plugin_parent_name_list(
        wchar_t const ***parent_name_list,
        uint32_t *parent_name_list_size) const;
      //@}
    };
    typedef class ColorSpaceConverterPluginSmpte240mRgb ColorSpaceConverterPluginSmpte240mRgb;
  }
}

#endif
