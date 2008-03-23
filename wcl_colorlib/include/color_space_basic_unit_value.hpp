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

#ifndef __wcl_cololib_color_space_basic_unit_value_hpp__
#define __wcl_cololib_color_space_basic_unit_value_hpp__

namespace Wcl
{
  namespace Colorlib
  {    
    enum ColorSpaceBasicUnitValueType
    {
      COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_UNKNOWN,
      COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_DOUBLE,
      COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_UINT8
    };
    typedef enum ColorSpaceBasicUnitValueType ColorSpaceBasicUnitValueType;
    
    class ColorSpaceBasicUnitValue
    {
    private:
      
      ColorSpaceBasicUnitValueType m_type;
      
      union
      {
        double_t m_double;
        uint8_t m_uint8;
      } u;
      
      template<typename T> friend struct ColorSpaceBasicUnitValueGetValueTraits;

    public:
      
      /** @name life cycle
       */
      //@{
      ColorSpaceBasicUnitValue()
        : m_type(COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_UNKNOWN)
      { }
      
      ColorSpaceBasicUnitValue(double_t const value)
        : m_type(COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_DOUBLE)
      {
        u.m_double = value;
      }
      
      ColorSpaceBasicUnitValue(uint8_t const value)
        : m_type(COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_UINT8)
      {
        u.m_uint8 = value;
      }
      //@}
      
      void set_value(double_t const value)
      {
        m_type = COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_DOUBLE;
        u.m_double = value;
      }
      
      void set_value(uint8_t const value)
      {
        m_type = COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_UINT8;
        u.m_uint8 = value;
      }
      
      ColorSpaceBasicUnitValueType get_type() const
      { return m_type; }
      
      template<typename T>
      T get_value() const;
      
      bool operator==(ColorSpaceBasicUnitValue const &value)
      {
        assert(m_type == value.m_type);
        
        switch (m_type)
        {
        case COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_DOUBLE:
          if (u.m_double == value.u.m_double)
          {
            return true;
          }
          else
          {
            return false;
          }
          break;
          
        case COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_UINT8:
          if (u.m_uint8 == value.u.m_uint8)
          {
            return true;
          }
          else
          {
            return false;
          }
          break;
          
        default:
          assert(0);
          return true;
        }
      }
      
      bool operator!=(ColorSpaceBasicUnitValue const &value)
      {
        return !operator==(value);
      }
      
      bool operator<(ColorSpaceBasicUnitValue const &value)
      {
        assert(m_type == value.m_type);
        
        switch (m_type)
        {
        case COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_DOUBLE:
          if (u.m_double < value.u.m_double)
          {
            return true;
          }
          else
          {
            return false;
          }
          break;
          
        case COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_UINT8:
          if (u.m_uint8 < value.u.m_uint8)
          {
            return true;
          }
          else
          {
            return false;
          }
          break;
          
        default:
          assert(0);
          return true;
        }
      }
      
      bool operator>=(ColorSpaceBasicUnitValue const &value)
      {
        return !operator<(value);
      }

      bool operator>(ColorSpaceBasicUnitValue const &value)
      {
        assert(m_type == value.m_type);
        
        switch (m_type)
        {
        case COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_DOUBLE:
          if (u.m_double > value.u.m_double)
          {
            return true;
          }
          else
          {
            return false;
          }
          break;
          
        case COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_UINT8:
          if (u.m_uint8 > value.u.m_uint8)
          {
            return true;
          }
          else
          {
            return false;
          }
          break;
          
        default:
          assert(0);
          return true;
        }
      }
      
      bool operator<=(ColorSpaceBasicUnitValue const &value)
      {
        return !operator>(value);
      }

      bool operator==(ColorSpaceBasicUnitValue const &value) const
      {
        assert(m_type == value.m_type);
        
        switch (m_type)
        {
        case COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_DOUBLE:
          if (u.m_double == value.u.m_double)
          {
            return true;
          }
          else
          {
            return false;
          }
          break;
          
        case COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_UINT8:
          if (u.m_uint8 == value.u.m_uint8)
          {
            return true;
          }
          else
          {
            return false;
          }
          break;
          
        default:
          assert(0);
          return true;
        }
      }
      
      bool operator!=(ColorSpaceBasicUnitValue const &value) const
      {
        return !operator==(value);
      }
      
      bool operator<(ColorSpaceBasicUnitValue const &value) const
      {
        assert(m_type == value.m_type);
        
        switch (m_type)
        {
        case COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_DOUBLE:
          if (u.m_double < value.u.m_double)
          {
            return true;
          }
          else
          {
            return false;
          }
          break;
          
        case COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_UINT8:
          if (u.m_uint8 < value.u.m_uint8)
          {
            return true;
          }
          else
          {
            return false;
          }
          break;
          
        default:
          assert(0);
          return true;
        }
      }
      
      bool operator>=(ColorSpaceBasicUnitValue const &value) const
      {
        return !operator<(value);
      }

      bool operator>(ColorSpaceBasicUnitValue const &value) const
      {
        assert(m_type == value.m_type);
        
        switch (m_type)
        {
        case COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_DOUBLE:
          if (u.m_double > value.u.m_double)
          {
            return true;
          }
          else
          {
            return false;
          }
          break;
          
        case COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_UINT8:
          if (u.m_uint8 > value.u.m_uint8)
          {
            return true;
          }
          else
          {
            return false;
          }
          break;
          
        default:
          assert(0);
          return true;
        }
      }
      
      bool operator<=(ColorSpaceBasicUnitValue const &value) const
      {
        return !operator>(value);
      }
      
      ColorSpaceBasicUnitValue &operator+=(ColorSpaceBasicUnitValue const &value)
      {
        assert(m_type == value.m_type);
        
        switch (m_type)
        {
        case COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_DOUBLE:
          u.m_double += value.u.m_double;
          break;
          
        case COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_UINT8:
          u.m_uint8 += value.u.m_uint8;
          break;
          
        default:
          assert(0);
          break;
        }
        
        return *this;
      }
      
      ColorSpaceBasicUnitValue &operator/=(uint8_t const value)
      {
        switch (m_type)
        {
        case COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_DOUBLE:
          u.m_double /= value;
          break;
          
        case COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_UINT8:
          u.m_uint8 /= value;
          break;
          
        default:
          assert(0);
          break;
        }

        return *this;
      }
    };
    typedef class ColorSpaceBasicUnitValue ColorSpaceBasicUnitValue;
    
    template<typename T>
    struct ColorSpaceBasicUnitValueGetValueTraits;
    
    template<>
    struct ColorSpaceBasicUnitValueGetValueTraits<double_t>
    {
      static double_t get_value(ColorSpaceBasicUnitValue const &value)
      {
        assert(COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_DOUBLE == value.get_type());
        
        return value.u.m_double;
      }
    };
    
    template<>
    struct ColorSpaceBasicUnitValueGetValueTraits<uint8_t>
    {
      static uint8_t get_value(ColorSpaceBasicUnitValue const &value)
      {
        assert(COLOR_SPACE_BASIC_UNIT_VALUE_TYPE_UINT8 == value.get_type());
        
        return value.u.m_uint8;
      }
    };
    
    template<typename T>
    T ColorSpaceBasicUnitValue::get_value() const
    {
      return ColorSpaceBasicUnitValueGetValueTraits<T>::get_value(*this);
    }
  }
}

#endif
