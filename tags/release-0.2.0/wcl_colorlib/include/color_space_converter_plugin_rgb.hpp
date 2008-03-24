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

#ifndef __wcl_colorlib_color_space_converter_plugin_rgb_hpp__
#define __wcl_colorlib_color_space_converter_plugin_rgb_hpp__

#include "export.hpp"
#include "color_space_converter_plugin.hpp"
#include "converter.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    class ColorSpaceConverterPluginRgb : public virtual ColorSpaceConverterPlugin
    {
    private:
      
      uint32_t m_rgb_plugin_id;
      
      boost::numeric::ublas::bounded_vector<double_t, 3> src_vec;
      boost::numeric::ublas::bounded_vector<double_t, 3> dst_vec;
      boost::numeric::ublas::bounded_matrix<double_t, 3, 3> m_rgb_to_cie1931_XYZ_mat;
      boost::numeric::ublas::bounded_matrix<double_t, 3, 3> m_cie1931_XYZ_to_rgb_mat;
      
      void create_CIE_XYZ_matrix_for_RGB(
        boost::numeric::ublas::bounded_matrix<double_t, 3, 3> &matrix,
        double_t const xr, double_t const yr, double_t const zr,
        double_t const xg, double_t const yg, double_t const zg,
        double_t const xb, double_t const yb, double_t const zb,
        double_t const xw, double_t const yw, double_t const zw);
    
      void create_convert_matrix_cie2rgb(
        boost::numeric::ublas::bounded_matrix<double_t, 3, 3> &matrix,
        double_t const xr, double_t const yr, double_t const zr,
        double_t const xg, double_t const yg, double_t const zg,
        double_t const xb, double_t const yb, double_t const zb,
        double_t const xw, double_t const yw, double_t const zw);
    
      void create_convert_matrix_rgb2cie(
        boost::numeric::ublas::bounded_matrix<double_t, 3, 3> &matrix,
        double_t const xr, double_t const yr, double_t const zr,
        double_t const xg, double_t const yg, double_t const zg,
        double_t const xb, double_t const yb, double_t const zb,
        double_t const xw, double_t const yw, double_t const zw);
      
      virtual void get_chromaticity_data(double &xr, double &yr,
                                         double &xg, double &yg,
                                         double &xb, double &yb,
                                         double &xw, double &yw) const = 0;
      
      virtual wchar_t const *get_rgb_plugin_name() const = 0;
      virtual void get_rgb_plugin_parent_name_list(wchar_t const ***parent_name_list, uint32_t *parent_name_list_size) const = 0;
      
      uint32_t get_rgb_plugin_id() const
      { return m_rgb_plugin_id; }
      
    protected:
      
      /** @name life cycle
       */
      //@{
      /**
       * Because class derived from this class should treat
       * this class as its virtual base class. So that I
       * have to provide a default constructor, then derived
       * classes would not have to initialize this class
       * explicitly.
       */
      ColorSpaceConverterPluginRgb()
        : COLOR_SPACE_CONVERTER_PLUGIN_SET_CONVERTER(0),
          m_rgb_plugin_id(0),
          src_vec(3),
          dst_vec(3),
          // I have to initialize these 2 matrixes 
          m_cie1931_XYZ_to_rgb_mat(3, 3),
          m_rgb_to_cie1931_XYZ_mat(3, 3)
      {}
      
      virtual ~ColorSpaceConverterPluginRgb() {}
      //@}
      
      WCL_COLORLIB_EXPORT void create_cie1931_XYZ_to_rgb_matrix();
      WCL_COLORLIB_EXPORT void create_rgb_to_cie1931_XYZ_matrix();
      
      WCL_COLORLIB_EXPORT void set_rgb_plugin_id();
      
    public:
      
      /** @name Conversion
       */
      //@{
      WCL_COLORLIB_EXPORT virtual bool convert_to_cie1931_XYZ(
        std::vector<ColorSpaceBasicUnitValue> const &src_data,
        std::vector<ColorSpaceBasicUnitValue> &dst_data,
        uint32_t const dst_plugin_id);
      
      WCL_COLORLIB_EXPORT virtual void convert_from_cie1931_XYZ(
        std::vector<ColorSpaceBasicUnitValue> const &src_data,
        std::vector<ColorSpaceBasicUnitValue> &dst_data,
        uint32_t const src_plugin_id);
      //@}
      
      /** @name Querying
       */
      //@{
      WCL_COLORLIB_EXPORT virtual void get_input_data_range(
        uint32_t const idx,
        std::vector<std::pair<ColorSpaceBasicUnitValue, ColorSpaceBasicUnitValue> > &ranges) const;
      
      WCL_COLORLIB_EXPORT virtual uint32_t get_subcomponent_count() const;
      
      WCL_COLORLIB_EXPORT virtual ColorSpaceBasicUnitValueType get_basic_unit_value_type() const;
      //@}
      
      /** @name Checking
       */
      //@{
      WCL_COLORLIB_EXPORT virtual void check_valid_input_idx(
        uint32_t const idx) const;
      
      WCL_COLORLIB_EXPORT virtual void check_valid_input_value(
        uint32_t const idx,
        ColorSpaceBasicUnitValue const &value) const;
      //@}
    };
    typedef class ColorSpaceConverterPluginRgb ColorSpaceConverterPluginRgb;
  }
}

#endif
