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

#include "lexerlib.h"
#include "fmtstr.h"

#include "color_space_info.hpp"
#include "exception.hpp"
#include "wcl_types.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    namespace ColorSpaceInfo
    {
      // RGB color space info
      struct RgbColorSpaceInfo
      {
        std::wstring m_name;
        double_t m_xr;
        double_t m_yr;
        double_t m_xg;
        double_t m_yg;
        double_t m_xb;
        double_t m_yb;
        double_t m_xw;
        double_t m_yw;
      };
      typedef struct RgbColorSpaceInfo RgbColorSpaceInfo;
      
      enum ParseState
      {
        PARSE_STATE_INIT,
        
        PARSE_STATE_RGB_READ_NAME,
        PARSE_STATE_RGB_READ_XR,
        PARSE_STATE_RGB_READ_YR,
        PARSE_STATE_RGB_READ_XG,
        PARSE_STATE_RGB_READ_YG,
        PARSE_STATE_RGB_READ_XB,
        PARSE_STATE_RGB_READ_YB,
        PARSE_STATE_RGB_READ_XW,
        PARSE_STATE_RGB_READ_YW        
      };
      typedef enum ParseState ParseState;
      
      // RGB color space info database
      std::vector<RgbColorSpaceInfo> g_rgb_color_space_info;
      
      ParseState g_parse_state;
      std::list<wchar_t> g_delimiter;
      std::list<wchar_t> g_skip;
      
      void
      parse_rgb_info(std::wfstream &src_file)
      {
        std::wstring result_str;
        bool again = true;
        
        for (; true == again;)
        {
          try
          {
            Lexerlib::read_string(src_file, g_delimiter, g_skip, result_str);
          }
          catch (Lexerlib::SourceIsBrokenException &)
          {
            assert(0);
          }
          catch (Lexerlib::EndOfSourceException &)
          {
            throw InvalidColorSpaceInfoFileException();
          }
          
          switch (g_parse_state)
          {
          case PARSE_STATE_RGB_READ_NAME:
            g_rgb_color_space_info.resize(g_rgb_color_space_info.size() + 1);
            g_rgb_color_space_info.back().m_name = result_str;
          
            try
            {
              Lexerlib::ensure_next_string_is(src_file, g_delimiter, g_skip, L":");
            }
            catch (Lexerlib::InvalidPredictionException &)
            {
              throw InvalidColorSpaceInfoFileException();
            }
          
            g_parse_state = PARSE_STATE_RGB_READ_XR;
            break;
          
          case PARSE_STATE_RGB_READ_XR:
            g_rgb_color_space_info.back().m_xr = boost::lexical_cast<double_t>(result_str);
          
            try
            {
              Lexerlib::ensure_next_string_is(src_file, g_delimiter, g_skip, L":");
            }
            catch (Lexerlib::InvalidPredictionException &)
            {
              throw InvalidColorSpaceInfoFileException();
            }
          
            g_parse_state = PARSE_STATE_RGB_READ_YR;
            break;
          
          case PARSE_STATE_RGB_READ_YR:
            g_rgb_color_space_info.back().m_yr = boost::lexical_cast<double_t>(result_str);
          
            try
            {
              Lexerlib::ensure_next_string_is(src_file, g_delimiter, g_skip, L":");
            }
            catch (Lexerlib::InvalidPredictionException &)
            {
              throw InvalidColorSpaceInfoFileException();
            }
          
            g_parse_state = PARSE_STATE_RGB_READ_XG;
            break;
          
          case PARSE_STATE_RGB_READ_XG:
            g_rgb_color_space_info.back().m_xg = boost::lexical_cast<double_t>(result_str);
          
            try
            {
              Lexerlib::ensure_next_string_is(src_file, g_delimiter, g_skip, L":");
            }
            catch (Lexerlib::InvalidPredictionException &)
            {
              throw InvalidColorSpaceInfoFileException();
            }
          
            g_parse_state = PARSE_STATE_RGB_READ_YG;
            break;
          
          case PARSE_STATE_RGB_READ_YG:
            g_rgb_color_space_info.back().m_yg = boost::lexical_cast<double_t>(result_str);
          
            try
            {
              Lexerlib::ensure_next_string_is(src_file, g_delimiter, g_skip, L":");
            }
            catch (Lexerlib::InvalidPredictionException &)
            {
              throw InvalidColorSpaceInfoFileException();
            }
          
            g_parse_state = PARSE_STATE_RGB_READ_XB;
            break;
          
          case PARSE_STATE_RGB_READ_XB:
            g_rgb_color_space_info.back().m_xb = boost::lexical_cast<double_t>(result_str);
          
            try
            {
              Lexerlib::ensure_next_string_is(src_file, g_delimiter, g_skip, L":");
            }
            catch (Lexerlib::InvalidPredictionException &)
            {
              throw InvalidColorSpaceInfoFileException();
            }
          
            g_parse_state = PARSE_STATE_RGB_READ_YB;
            break;
          
          case PARSE_STATE_RGB_READ_YB:
            g_rgb_color_space_info.back().m_yb = boost::lexical_cast<double_t>(result_str);
          
            try
            {
              Lexerlib::ensure_next_string_is(src_file, g_delimiter, g_skip, L":");
            }
            catch (Lexerlib::InvalidPredictionException &)
            {
              throw InvalidColorSpaceInfoFileException();
            }
          
            g_parse_state = PARSE_STATE_RGB_READ_XW;
            break;
          
          case PARSE_STATE_RGB_READ_XW:
            g_rgb_color_space_info.back().m_xw = boost::lexical_cast<double_t>(result_str);
          
            try
            {
              Lexerlib::ensure_next_string_is(src_file, g_delimiter, g_skip, L":");
            }
            catch (Lexerlib::InvalidPredictionException &)
            {
              throw InvalidColorSpaceInfoFileException();
            }
          
            g_parse_state = PARSE_STATE_RGB_READ_YW;
            break;
          
          case PARSE_STATE_RGB_READ_YW:
            g_rgb_color_space_info.back().m_yw = boost::lexical_cast<double_t>(result_str);
            g_parse_state = PARSE_STATE_INIT;
            again = false;
            break;
            
          default:
            assert(0);
            break;
          }
        }
      }
    
      void
      parse_config_file(std::wfstream &src_file)
      {
        std::wstring result_str;
        
        for (;;)
        {
          switch (g_parse_state)
          {
          case PARSE_STATE_INIT:
            break;
            
          default:
            throw InvalidColorSpaceInfoFileException();
          }
          
          try
          {
            Lexerlib::read_string(src_file, g_delimiter, g_skip, result_str);
          }
          catch (Lexerlib::SourceIsBrokenException &)
          {
            assert(0);
          }
          catch (Lexerlib::EndOfSourceException &)
          {
            return;
          }
          
          if (0 == result_str.compare(L"RGB"))
          {
            g_parse_state = PARSE_STATE_RGB_READ_NAME;
          }
          
          switch (g_parse_state)
          {
          case PARSE_STATE_INIT:
            throw InvalidColorSpaceInfoFileException();
            
          case PARSE_STATE_RGB_READ_NAME:
            try
            {
              Lexerlib::ensure_next_string_is(src_file, g_delimiter, g_skip, L":");
            }
            catch (Lexerlib::InvalidPredictionException &)
            {
              throw InvalidColorSpaceInfoFileException();
            }
            
            parse_rgb_info(src_file);
            break;
          
          default:
            assert(0);
            break;
          }
        }
      }
      
      void
      init()
      {
        g_parse_state = PARSE_STATE_INIT;
        
        g_delimiter.push_back(L':');
        
        g_skip.push_back(L' ');
        g_skip.push_back(L'\n');
        g_skip.push_back(L'\r');
        
        wchar_t *wcl_basepath_env_str_wide;
        
        {
          size_t required_size;
          ::_wgetenv_s(&required_size, 0, 0, L"WCL_BASEPATH");
          wcl_basepath_env_str_wide = static_cast<wchar_t *>(::operator new(required_size * sizeof(wchar_t)));
          assert(wcl_basepath_env_str_wide != 0);
          
          ::_wgetenv_s(&required_size, wcl_basepath_env_str_wide, required_size, L"WCL_BASEPATH");
        }
        
        std::wstring wcl_basepath(wcl_basepath_env_str_wide);
        wcl_basepath += L"\\config\\wcl_colorlib\\color_space_info.txt";
        
        {
          std::wfstream src_file(wcl_basepath.c_str());
          src_file.seekg(0, std::ios::beg);
          
          parse_config_file(src_file);
          
          src_file.close();
        }
      }
      
      namespace RGB
      {
        struct iterator_impl
        {
          std::vector<RgbColorSpaceInfo>::iterator iter;
        };
        typedef struct iterator_impl iterator_impl;
        
        void get_chromaticity_data(
          std::wstring const &name,
          double_t &xr, double_t &yr,
          double_t &xg, double_t &yg,
          double_t &xb, double_t &yb,
          double_t &xw, double_t &yw)
        {
          BOOST_FOREACH(RgbColorSpaceInfo const &info,
                        g_rgb_color_space_info)
          {
            if (0 == name.compare(info.m_name))
            {
              xr = info.m_xr;
              yr = info.m_yr;

              xg = info.m_xg;
              yg = info.m_yg;

              xb = info.m_xb;
              yb = info.m_yb;

              xw = info.m_xw;
              yw = info.m_yw;
              return;
            }
          }
        }
        
        iterator::iterator()
          : mp_iterator_impl(::new iterator_impl)
        {
        }
        
        iterator::iterator(iterator const &iter)
          : mp_iterator_impl(::new iterator_impl)
        {
          mp_iterator_impl->iter = iter.mp_iterator_impl->iter;
        }
        
        iterator::~iterator()
        {
          ::delete mp_iterator_impl;
        }
        
        iterator &
        iterator::operator=(iterator const &iter)
        {
          mp_iterator_impl->iter = iter.mp_iterator_impl->iter;

          return *this;
        }
        
        bool
        iterator::operator==(iterator const &iter) const
        {
          if (mp_iterator_impl->iter == iter.mp_iterator_impl->iter)
          {
            return true;
          }
          else
          {
            return false;
          }
        }
        
        std::wstring &
        iterator::operator*() const
        {
          return (*(mp_iterator_impl->iter)).m_name;
        }
        
        iterator &
        iterator::operator++()
        {
          ++(mp_iterator_impl->iter);
          
          return (*this);
        }
        
        iterator
        begin()
        {
          iterator iter = iterator();
          
          iter.mp_iterator_impl->iter = g_rgb_color_space_info.begin();
          
          return iter;
        }
        
        iterator
        end()
        {
          iterator iter = iterator();
          
          iter.mp_iterator_impl->iter = g_rgb_color_space_info.end();
          
          return iter;
        }
      }
    }
  }
}
