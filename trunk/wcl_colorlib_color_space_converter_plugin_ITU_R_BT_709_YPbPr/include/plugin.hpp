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

#ifndef __wcl_colorlib_color_space_converter_plugin_itu_r_bt_709_ypbpr_plugin_hpp__
#define __wcl_colorlib_color_space_converter_plugin_itu_r_bt_709_ypbpr_plugin_hpp__

#include "..\..\wcl_colorlib_color_space_converter_plugin_ITU_R_BT_709_RGB\include\plugin.hpp"
#include "..\..\wcl_colorlib\include\color_space_converter.hpp"
#include "..\..\wcl_colorlib\include\color_space_converter_plugin_ypbpr.hpp"
#include "..\..\wcl_colorlib\include\exception.hpp"

#if defined(WCL_COLORLIB_COLOR_SPACE_CONVERTER_PLUGIN_ITU_R_BT_709_YPBPR_EXPORTS)
#define WCL_COLORLIB_ITU_R_BT_709_YPBPR_PLUGIN_EXPORT __declspec(dllexport)
#else
#define WCL_COLORLIB_ITU_R_BT_709_YPBPR_PLUGIN_EXPORT __declspec(dllimport)
#endif

#pragma warning(disable : 4250)

namespace Wcl
{
  namespace Colorlib
  {
    class ColorSpaceConverterPluginItuRBt709YPbPr : public virtual ColorSpaceConverterPluginItuRBt709Rgb, public virtual ColorSpaceConverterPluginYPbPr
    {
    protected:

      /**
       * @name life cycle
       */
      //@{
      ColorSpaceConverterPluginItuRBt709YPbPr()
        : COLOR_SPACE_CONVERTER_PLUGIN_SET_CONVERTER(0)
      {
        set_ypbpr_plugin_id();
        set_ypbpr_coefficient(0.2126, 0.0722);
      }
      
    public:
      
      ColorSpaceConverterPluginItuRBt709YPbPr(
        ColorSpaceConverter * const converter)
        : COLOR_SPACE_CONVERTER_PLUGIN_SET_CONVERTER(converter)
      {
        set_ypbpr_plugin_id();
        set_ypbpr_coefficient(0.2126, 0.0722);
      }
      
      virtual ~ColorSpaceConverterPluginItuRBt709YPbPr() {}
      //@}
      
      /** @name Querying
       */
      //@{
      WCL_COLORLIB_ITU_R_BT_709_YPBPR_PLUGIN_EXPORT virtual wchar_t const *get_ypbpr_plugin_name() const;
      
      WCL_COLORLIB_ITU_R_BT_709_YPBPR_PLUGIN_EXPORT virtual void get_ypbpr_plugin_parent_name_list(
        wchar_t const ***parent_name_list,
        uint32_t *parent_name_list_size) const;
      //@}
    };
    typedef class ColorSpaceConverterPluginItuRBt709YPbPr ColorSpaceConverterPluginItuRBt709YPbPr;
  }
}

#endif
