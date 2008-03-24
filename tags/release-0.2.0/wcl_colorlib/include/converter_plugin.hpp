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

#ifndef __wcl_colorlib_converter_plugin_hpp__
#define __wcl_colorlib_converter_plugin_hpp__

namespace Wcl
{
  namespace Colorlib
  {
    template<typename T, typename S>
    class ConverterPlugin
    {
    protected:
      
      Converter<S> * const mp_converter;
      
      /** @name life cycle
       */
      //@{
      ConverterPlugin(Converter<S> * const converter)
        : mp_converter(converter)
      {
        assert(converter != 0);
      }
      //@}
      
      ConverterPlugin<T, S> &operator=(ConverterPlugin<T, S> const &plugin);
      
    public:
      
      /** @name life cycle
       */
      //@{
      virtual ~ConverterPlugin() {}
      //@}
    };
  }
}

#endif
