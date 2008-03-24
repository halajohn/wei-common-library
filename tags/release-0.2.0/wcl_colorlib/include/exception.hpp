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

#ifndef __wcl_colorlib_exception_hpp__
#define __wcl_colorlib_exception_hpp__

namespace Wcl
{
  namespace Colorlib
  {
    class DoesNotSpecifyColorSpaceConverterDatabaseException : public std::exception
    {
      virtual char const *what() const throw()
      {
        return "Does not specfiy color space converter database.";
      }
    };
    typedef class DoesNotSpecifyColorSpaceConverterDatabaseException DoesNotSpecifyColorSpaceConverterDatabaseException;
    
    class LoadPluginWhenAtLeastOneConverterIsInUseException : public std::exception
    {
      virtual char const *what() const throw()
      {
        return "Load plugins when at least one converter is still in use.";
      }
    };
    typedef class LoadPluginWhenAtLeastOneConverterIsInUseException LoadPluginWhenAtLeastOneConverterIsInUseException;
    
    class BufferSizeTooSmallException : public std::exception
    {
      virtual char const *what() const throw()
      {
        return "Buffer size too small.";
      }
    };
    typedef class BufferSizeTooSmallException BufferSizeTooSmallException;
    
    class DoesNotSpecifySrcPluginException : public std::exception
    {
      virtual char const *what() const throw()
      {
        return "Does not specfiy source plugin.";
      }
    };
    typedef class DoesNotSpecifySrcPluginException DoesNotSpecifySrcPluginException;
    
    class DoesNotSpecifyDstPluginException : public std::exception
    {
      virtual char const *what() const throw()
      {
        return "Does not specfiy destination plugin.";
      }
    };
    typedef class DoesNotSpecifyDstPluginException DoesNotSpecifyDstPluginException;
    
    class InvalidSrcFmtException : public std::exception
    {
      virtual char const *what() const throw()
      {
        return "Invalid source color format.";
      }
    };
    typedef class InvalidSrcFmtException InvalidSrcFmtException;
  
    class InvalidDstFmtException : public std::exception
    {
      virtual char const *what() const throw()
      {
        return "Invalid destination color format.";
      }
    };
    typedef class InvalidDstFmtException InvalidDstFmtException;
    
    class SrcAndDstSubSamplingConverterPluginCanNotBeDiffCustomAtTheSameTime : public std::exception
    {
      virtual char const *what() const throw()
      {
        return "Src & Dst subsampling converter plugin can not be custom at the same time.";
      }
    };
    typedef class SrcAndDstSubSamplingConverterPluginCanNotBeDiffCustomAtTheSameTime
    SrcAndDstSubSamplingConverterPluginCanNotBeDiffCustomAtTheSameTime;
    
    class SrcAndDstColorSpaceConverterPluginCanNotBeDiffCustomAtTheSameTime : public std::exception
    {
      virtual char const *what() const throw()
      {
        return "Src & Dst color space converter plugin can not be custom at the same time.";
      }
    };
    typedef class SrcAndDstColorSpaceConverterPluginCanNotBeDiffCustomAtTheSameTime
    SrcAndDstColorSpaceConverterPluginCanNotBeDiffCustomAtTheSameTime;
    
    class TooLessInputDataException : public std::exception
    {
      virtual char const *what() const throw()
      {
        return "Too less input data.";
      }
    };
    typedef class TooLessInputDataException TooLessInputDataException;
    
    class TooManyInputDataException : public std::exception
    {
      virtual char const *what() const throw()
      {
        return "Too many input data.";
      }
    };
    typedef class TooManyInputDataException TooManyInputDataException;
    
    class InvalidInputValueException : public std::exception
    {
      virtual char const *what() const throw()
      {
        return "Invalid input value.";
      }
    };
    typedef class InvalidInputValueException InvalidInputValueException;
    
    class InvalidColorSpaceInfoFileException : public std::exception
    {
      virtual char const *what() const throw()
      {
        return "Invalid color space info file.";
      }
    };
    typedef class InvalidColorSpaceInfoFileException InvalidColorSpaceInfoFileException;
    
    class InvalidConfigFileException : public std::exception
    {
      virtual char const *what() const throw()
      {
        return "Invalid config file.";
      }
    };
    typedef class InvalidConfigFileException InvalidConfigFileException;
  }
}

#endif
