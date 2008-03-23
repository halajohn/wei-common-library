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

#include "..\..\wcl_mathlib\include\matrix.hpp"

#include "exception.hpp"
#include "color_space_converter.hpp"
#include "color_space_converter_plugin_rgb.hpp"
#include "color_space_converter_plugin_internal.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    // ==========================================================================
    //                       Color Space RGB Converter Plugin
    // ==========================================================================
    void
    ColorSpaceConverterPluginRgb::create_CIE_XYZ_matrix_for_RGB(
      boost::numeric::ublas::bounded_matrix<double_t, 3, 3> &matrix,
      double_t const xr, double_t const yr, double_t const zr,
      double_t const xg, double_t const yg, double_t const zg,
      double_t const xb, double_t const yb, double_t const zb,
      double_t const xw, double_t const yw, double_t const zw)
    {
      boost::numeric::ublas::bounded_matrix<double_t, 3, 3> m(3, 3);
      m(0, 0) = (xr / yr);
      m(0, 1) = (xg / yg);
      m(0, 2) = (xb / yb);
      m(1, 0) = 1.0;
      m(1, 1) = 1.0;
      m(1, 2) = 1.0;
      m(2, 0) = (zr / yr);
      m(2, 1) = (zg / yg);
      m(2, 2) = (zb / yb);
      
      boost::numeric::ublas::bounded_vector<double_t, 3> v(3);
      v(0) = (xw / yw);
      v(1) = 1.0;
      v(2) = (zw / yw);
      
      boost::numeric::ublas::bounded_matrix<double_t, 3, 3> n(3, 3);
      Wcl::Mathlib::Matrix::inverse(m, n);
      
      boost::numeric::ublas::bounded_vector<double_t, 3> Y(3);
      Y = boost::numeric::ublas::prod(n, v);
      
      double_t const Xr = (xr / yr) * Y(0);
      double_t const Yr = Y(0);
      double_t const Zr = (zr / yr) * Y(0);
      double_t const Xg = (xg / yg) * Y(1);
      double_t const Yg = Y(1);
      double_t const Zg = (zg / yg) * Y(1);
      double_t const Xb = (xb / yb) * Y(2);
      double_t const Yb = Y(2);
      double_t const Zb = (zb / yb) * Y(2);
      
      matrix(0, 0) = Xr;
      matrix(0, 1) = Xg;
      matrix(0, 2) = Xb;
      matrix(1, 0) = Yr;
      matrix(1, 1) = Yg;
      matrix(1, 2) = Yb;
      matrix(2, 0) = Zr;
      matrix(2, 1) = Zg;
      matrix(2, 2) = Zb;
    }
  
    void
    ColorSpaceConverterPluginRgb::create_convert_matrix_cie2rgb(
      boost::numeric::ublas::bounded_matrix<double_t, 3, 3> &matrix,
      double_t const xr, double_t const yr, double_t const zr,
      double_t const xg, double_t const yg, double_t const zg,
      double_t const xb, double_t const yb, double_t const zb,
      double_t const xw, double_t const yw, double_t const zw)
    {
      boost::numeric::ublas::bounded_matrix<double_t, 3, 3> XYZ(3, 3);
      create_CIE_XYZ_matrix_for_RGB(XYZ,
                                    xr, yr, zr,
                                    xg, yg, zg,
                                    xb, yb, zb,
                                    xw, yw, zw);
      
      Wcl::Mathlib::Matrix::inverse(XYZ, matrix);
    }
    
    void
    ColorSpaceConverterPluginRgb::create_convert_matrix_rgb2cie(
      boost::numeric::ublas::bounded_matrix<double_t, 3, 3> &matrix,
      double_t const xr, double_t const yr, double_t const zr,
      double_t const xg, double_t const yg, double_t const zg,
      double_t const xb, double_t const yb, double_t const zb,
      double_t const xw, double_t const yw, double_t const zw)
    {
      create_CIE_XYZ_matrix_for_RGB(matrix,
                                    xr, yr, zr,
                                    xg, yg, zg,
                                    xb, yb, zb,
                                    xw, yw, zw);
    }
  
    void
    ColorSpaceConverterPluginRgb::create_cie1931_XYZ_to_rgb_matrix()
    {
      double xr, yr, xg, yg, xb, yb, xw, yw;
    
      get_chromaticity_data(xr, yr,
                            xg, yg,
                            xb, yb,
                            xw, yw);
      
      create_convert_matrix_cie2rgb(
        m_cie1931_XYZ_to_rgb_mat,
        xr, yr, (1 - xr - yr),
        xg, yg, (1 - xg - yg),
        xb, yb, (1 - xb - yb),
        xw, yw, (1 - xw - yw));
    }
  
    void
    ColorSpaceConverterPluginRgb::create_rgb_to_cie1931_XYZ_matrix()
    {
      double xr, yr, xg, yg, xb, yb, xw, yw;
      
      get_chromaticity_data(xr, yr,
                            xg, yg,
                            xb, yb,
                            xw, yw);
      
      create_convert_matrix_rgb2cie(
        m_rgb_to_cie1931_XYZ_mat,
        xr, yr, (1 - xr - yr),
        xg, yg, (1 - xg - yg),
        xb, yb, (1 - xb - yb),
        xw, yw, (1 - xw - yw));
    }
    
    void
    ColorSpaceConverterPluginRgb::set_rgb_plugin_id()
    {
      assert(0 == m_rgb_plugin_id);
      
      {
        std::list<std::wstring> rgb_plugin_names;
        
        {
          wchar_t const **parent_name_list;
          uint32_t parent_name_list_size;
          
          get_rgb_plugin_parent_name_list(&parent_name_list, &parent_name_list_size);
          for (uint32_t i = 0; i < parent_name_list_size; ++i)
          {
            rgb_plugin_names.push_back(parent_name_list[i]);
          }
        }
        
        {
          wchar_t const * const plugin_name = get_rgb_plugin_name();
          
          rgb_plugin_names.push_back(plugin_name);
        }
        
        PluginInfo<ColorSpaceConverterPlugin> const * const info =
          Converter<ColorSpaceConverterPlugin>::search_plugin(rgb_plugin_names);
        assert(info != 0);
        
        m_rgb_plugin_id = info->id;
      }
    }
    
    //=========================================================================
    //               Color Space Converter Plugin interface API
    //=========================================================================
    
    bool
    ColorSpaceConverterPluginRgb::convert_to_cie1931_XYZ(
      std::vector<ColorSpaceBasicUnitValue> const &rgb_data,
      std::vector<ColorSpaceBasicUnitValue> &dst_data,
      uint32_t const dst_plugin_id)
    {
      // Check input size
      if (rgb_data.size() < 3)
      {
        throw TooLessInputDataException();
      }
      if (rgb_data.size() > 3)
      {
        throw TooManyInputDataException();
      }
      
      if ((dst_plugin_id == get_rgb_plugin_id()) ||
          (dst_plugin_id == ColorSpaceConverter::get_custom_rgb_plugin_id()))
      {
        dst_data = rgb_data;
        
        return true;
      }
      else
      {
        boost::numeric::ublas::bounded_vector<double_t, 3>::size_type idx = 0;
        
        BOOST_FOREACH(ColorSpaceBasicUnitValue const &value, rgb_data)
        {
          src_vec(idx) = value.get_value<double_t>();
          
          ++idx;
        }
        
        // Based on the boost document & from Google,
        // axpy_prod() will be faster than normal prod().
        //
        // So that I write the following codes rather than:
        // dst_vec = boost::numeric::ublas::prod(m_rgb_to_cie1931_XYZ_mat, src_vec);
        boost::numeric::ublas::axpy_prod(m_rgb_to_cie1931_XYZ_mat, src_vec, dst_vec, true);
        
        dst_data.clear();
        
        BOOST_FOREACH(double_t const &value, dst_vec)
        {
          dst_data.push_back(ColorSpaceBasicUnitValue(value));
        }
        
        return false;
      }
    }
    
    void
    ColorSpaceConverterPluginRgb::convert_from_cie1931_XYZ(
      std::vector<ColorSpaceBasicUnitValue> const &src_data,
      std::vector<ColorSpaceBasicUnitValue> &rgb_data,
      uint32_t const src_plugin_id)
    {
      if (src_data.size() < 3)
      {
        throw TooLessInputDataException();
      }
      if (src_data.size() > 3)
      {
        throw TooManyInputDataException();
      }
      
      if (src_plugin_id == ColorSpaceConverter::get_custom_rgb_plugin_id())
      {
        rgb_data = src_data;
      }
      else
      {
        boost::numeric::ublas::bounded_vector<double_t, 3>::size_type idx = 0;
        
        BOOST_FOREACH(ColorSpaceBasicUnitValue const &value, src_data)
        {
          src_vec(idx) = value.get_value<double_t>();
          
          ++idx;
        }
        
        // Based on the boost document & from Google,
        // axpy_prod() will be faster than normal prod().
        //
        // So that I write the following codes rather than:
        // dst_vec = boost::numeric::ublas::prod(m_cie1931_XYZ_to_rgb_mat, src_vec);
        boost::numeric::ublas::axpy_prod(m_cie1931_XYZ_to_rgb_mat, src_vec, dst_vec, true);
      
        rgb_data.clear();
      
        BOOST_FOREACH(double_t const &value, dst_vec)
        {
          rgb_data.push_back(ColorSpaceBasicUnitValue(value));
        }
      }
    }
    
    void
    ColorSpaceConverterPluginRgb::get_input_data_range(
      uint32_t const idx,
      std::vector<std::pair<ColorSpaceBasicUnitValue, ColorSpaceBasicUnitValue> > &ranges) const
    {
      check_valid_input_idx(idx);
      
      ranges.clear();
      
      ranges.push_back(std::pair<ColorSpaceBasicUnitValue, ColorSpaceBasicUnitValue>(
                         ColorSpaceBasicUnitValue(0.0), ColorSpaceBasicUnitValue(1.0)));
    }
    
    uint32_t
    ColorSpaceConverterPluginRgb::get_subcomponent_count() const
    {
      return 3;
    }
    
    ColorSpaceBasicUnitValueType
    ColorSpaceConverterPluginRgb::get_basic_unit_value_type() const
    {
      return COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_DOUBLE;
    }

    void
    ColorSpaceConverterPluginRgb::check_valid_input_value(
      uint32_t const idx,
      ColorSpaceBasicUnitValue const &value) const
    {
      ::Wcl::Colorlib::check_valid_input_value<ColorSpaceConverterPluginRgb>(this, idx, value);
    }
    
    void
    ColorSpaceConverterPluginRgb::check_valid_input_idx(
      uint32_t const idx) const
    {
      switch (idx)
      {
      case 0:
      case 1:
      case 2:
        return;
        
      default:
        throw TooManyInputDataException();
      }
    }
  }
}
