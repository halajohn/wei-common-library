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

#include "..\..\wcl_fmtstr\include\fmtstr.h"
#include "..\..\wcl_lexerlib\include\lexerlib.h"

#include "export.hpp"
#include "common.hpp"
#include "color_space_info.hpp"
#include "exception.hpp"
#include "color_space_converter.hpp"
#include "subsampling_converter.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    namespace
    {
      enum ParseConfigFileState
      {
        PARSE_CONFIG_FILE_STATE_INIT,
        PARSE_CONFIG_FILE_STATE_COLOR_SPACE_CONVERTER_PLUGIN_DIR,
        PARSE_CONFIG_FILE_STATE_SUBSAMPLING_CONVERTER_PLUGIN_DIR,
        PARSE_CONFIG_FILE_STATE_END
      };
      typedef enum ParseConfigFileState ParseConfigFileState;
      
      ParseConfigFileState g_state = PARSE_CONFIG_FILE_STATE_INIT;
    }
    
    void
    init()
    {
      ColorSpaceInfo::init();
      
      {
        wchar_t *wcl_basepath_env_str_wide;
        
        {
          size_t required_size;
          ::_wgetenv_s(&required_size, 0, 0, L"WCL_BASEPATH");
          wcl_basepath_env_str_wide = static_cast<wchar_t *>(::operator new(required_size * sizeof(wchar_t)));
          assert(wcl_basepath_env_str_wide != 0);
          
          ::_wgetenv_s(&required_size, wcl_basepath_env_str_wide, required_size, L"WCL_BASEPATH");
        }
        
        std::wstring wcl_basepath(wcl_basepath_env_str_wide);
        
        std::wstring const config_filename = wcl_basepath + L"/config/wcl_colorlib/config.ini";
        
        std::wfstream config_file(config_filename.c_str());
        config_file.seekg(0, std::ios::beg);
        
        std::list<wchar_t> delimiter;
        delimiter.push_back(L':');
        
        std::list<wchar_t> skip;
        skip.push_back(L'\n');
        skip.push_back(L'\r');
          
        std::wstring color_space_converter_plugin_dir(wcl_basepath_env_str_wide);
        std::wstring subsampling_converter_plugin_dir(wcl_basepath_env_str_wide);
        
        for (;;)
        {
          std::wstring result_str;
          
          try
          {
            Lexerlib::read_string(config_file, delimiter, skip, result_str);
          }
          catch (Lexerlib::SourceIsBrokenException &)
          {
            assert(0);
          }
          catch (Lexerlib::EndOfSourceException &)
          {
            if (PARSE_CONFIG_FILE_STATE_END == g_state)
            {
              break;
            }
            else
            {
              throw InvalidConfigFileException();
            }
          }
            
          switch (g_state)
          {
          case PARSE_CONFIG_FILE_STATE_INIT:
            if (0 == result_str.compare(L"ColorSpaceConverterPluginDir"))
            {
              try
              {
                Lexerlib::ensure_next_string_is(config_file, delimiter, skip, L":");
              }
              catch (Lexerlib::InvalidPredictionException &)
              {
                throw InvalidConfigFileException();
              }
                
              g_state = PARSE_CONFIG_FILE_STATE_COLOR_SPACE_CONVERTER_PLUGIN_DIR;
            }
            else if (0 == result_str.compare(L"SubSamplingConverterPluginDir"))
            {
              try
              {
                Lexerlib::ensure_next_string_is(config_file, delimiter, skip, L":");
              }
              catch (Lexerlib::InvalidPredictionException &)
              {
                throw InvalidConfigFileException();
              }
                
              g_state = PARSE_CONFIG_FILE_STATE_SUBSAMPLING_CONVERTER_PLUGIN_DIR;
            }
            break;
              
          case PARSE_CONFIG_FILE_STATE_COLOR_SPACE_CONVERTER_PLUGIN_DIR:
            color_space_converter_plugin_dir += result_str;
            g_state = PARSE_CONFIG_FILE_STATE_INIT;
            break;
              
          case PARSE_CONFIG_FILE_STATE_SUBSAMPLING_CONVERTER_PLUGIN_DIR:
            subsampling_converter_plugin_dir += result_str;
            g_state = PARSE_CONFIG_FILE_STATE_END;
            break;
              
          case PARSE_CONFIG_FILE_STATE_END:
          default:
            assert(0);
            break;
          }
        }
        
        config_file.close();
        
        // Modify the 'path' environment variable so that
        // plugin dlls can be found.
        {
          size_t required_size;
          ::_wgetenv_s(&required_size, 0, 0, L"path");
          wchar_t * const path_env_str_wide = static_cast<wchar_t *>(::operator new(required_size * sizeof(wchar_t)));
          assert(path_env_str_wide != 0);
          
          ::_wgetenv_s(&required_size, path_env_str_wide, required_size, L"path");
          std::wstring path(path_env_str_wide);
          
          path += L";";
          path += color_space_converter_plugin_dir;

          path += L";";
          path += subsampling_converter_plugin_dir;
          
          _wputenv_s(L"path", path.c_str());
        }
        
        ColorSpaceConverter::load_plugin(color_space_converter_plugin_dir);
        SubSamplingConverter::load_plugin(subsampling_converter_plugin_dir);
      }
    }
    
    uint8_t
    clamp_for_rgb(double_t const value)
    {
      if (value < 0.0)
      {
        return 0;
      }
      else if (value > 255.0)
      {
        return 255;
      }
      else
      {
        return static_cast<uint8_t>(value * 255);
      }
    }
    
    double_t
    clamp_for_rgb(uint8_t const value)
    {
      return static_cast<double_t>(value) / 255.0;
    }
  }
}
