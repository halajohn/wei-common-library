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

#ifndef __wcl_colorlib_color_space_info_hpp__
#define __wcl_colorlib_color_space_info_hpp__

#include "export.hpp"
#include "wcl_types.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    namespace ColorSpaceInfo
    {
      WCL_COLORLIB_EXPORT extern void init();
      
      namespace RGB
      {
        WCL_COLORLIB_EXPORT extern void get_chromaticity_data(
          std::wstring const &name,
          double_t &xr, double_t &yr,
          double_t &xg, double_t &yg,
          double_t &xb, double_t &yb,
          double_t &xw, double_t &yw);
        
        class iterator;
        
        WCL_COLORLIB_EXPORT extern iterator begin();
        WCL_COLORLIB_EXPORT extern iterator end();
        
        struct iterator_impl;
        
        class iterator : public std::iterator<std::input_iterator_tag, std::wstring *>
        {
        private:
          
          struct iterator_impl * const mp_iterator_impl;
          
          WCL_COLORLIB_EXPORT friend iterator begin();
          WCL_COLORLIB_EXPORT friend iterator end();
          
        public:
          
          // Constructor
          WCL_COLORLIB_EXPORT iterator();
          WCL_COLORLIB_EXPORT iterator(iterator const &iter);
          
          WCL_COLORLIB_EXPORT ~iterator();
          
          WCL_COLORLIB_EXPORT iterator &operator=(iterator const &iter);
          
          WCL_COLORLIB_EXPORT bool operator==(iterator const &iter) const;
                    
          WCL_COLORLIB_EXPORT bool operator!=(iterator const &iter) const
          {
            return !(*this == iter);
          }
          
          WCL_COLORLIB_EXPORT std::wstring &operator*() const;
          WCL_COLORLIB_EXPORT iterator &operator++();
        };
        typedef class iterator iterator;
      }
    }
  }
}

#endif
