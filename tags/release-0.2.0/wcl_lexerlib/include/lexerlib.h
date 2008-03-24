// wcl_lexerlib - common lexer operation library
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

#ifndef __lexerlib_h__
#define __lexerlib_h__

#include <cstddef>
#include <fstream>
#include <list>
#include <exception>

#if defined(WCL_LEXERLIB_EXPORTS)
#define WCL_LEXERLIB_EXPORT __declspec(dllexport)
#else
#define WCL_LEXERLIB_EXPORT __declspec(dllimport)
#endif

namespace Wcl
{
  namespace Lexerlib
  {
    class SourceIsBrokenException : public std::exception
    {
      virtual char const *what() const throw()
      {
        return "Source is broken.";
      }
    };
    typedef class SourceIsBrokenException SourceIsBrokenException;
    
    class EndOfSourceException : public std::exception
    {
      virtual char const *what() const throw()
      {
        return "End of source.";
      }
    };
    typedef class EndOfSourceException EndOfSourceException;
    
    class InvalidPredictionException : public std::exception
    {
      virtual char const *what() const throw()
      {
        return "Invalid prediction.";
      }
    };
    typedef class InvalidPredictionException InvalidPredictionException;
    
    WCL_LEXERLIB_EXPORT extern void put_back(std::wfstream &file, wchar_t const ch);
    WCL_LEXERLIB_EXPORT extern void put_back(std::wstring &str, wchar_t const ch);
    WCL_LEXERLIB_EXPORT extern void put_back(std::wfstream &file, std::wstring const &str);
    
    WCL_LEXERLIB_EXPORT extern void read_ch(std::wfstream &file, wchar_t &ch);
    WCL_LEXERLIB_EXPORT extern void read_ch(std::wstring &str, wchar_t &ch);
    
    /**
     * @param delimiter the characters used to separate different
     * string
     * @param skip the characters which will be skipped when
     * read
     * @return the found string
     */
    template<typename T>
    void
    read_string(
      T &file,
      std::list<wchar_t> const &delimiter,
      std::list<wchar_t> const &skip,  
      std::wstring &result_str)
    {
      wchar_t ch;
      
      result_str.clear();
      
      // Read the first character.
      read_ch(file, ch);
      
      bool restart = true;
      for (; true == restart;)
      {
        restart = false;
        
        // If the read character is not included in the
        // 'skip' set, then I need to see if it is
        // inside the 'delimiter' set. If yes, then
        // return it immediately.
        BOOST_FOREACH(wchar_t const &del_ch, delimiter)
        {
          if (del_ch == ch)
          {
            result_str = ch;
            return;
          }
        }
        
        // Check to see if I need to skip the read
        // character.
        BOOST_FOREACH(wchar_t const &skip_ch, skip)
        {
          if (skip_ch == ch)
          {
            // Skip this one and read again.
            restart = true;
            break;
          }
        }
        
        if (true == restart)
        {
          // Read more character.
          read_ch(file, ch);
        }
      }
      
      // read success, and the read character is not a 'skip'
      // one or a 'delimeter' one.
      
      for (;;)
      {
        result_str += ch;
        
        try
        {
          read_ch(file, ch);
        }
        catch (EndOfSourceException &)
        {
          // There are characters in 'result_str', so that I
          // can not throw EndOfSourceException this time.
          // this function will throw it next time.
          return;
        }
        
        BOOST_FOREACH(wchar_t const &skip_ch, skip)
        {
          if (skip_ch == ch)
          {
            // I don't need to put back characters which are
            // to be skipped.
            return;
          }
        }
          
        BOOST_FOREACH(wchar_t const &del_ch, delimiter)
        {
          if (del_ch == ch)
          {
            put_back(file, ch);
            return;
          }
        }
      }
    }
    
    template<typename T>
    void
    ensure_next_string_is(
      T &file,
      std::list<wchar_t> const &delimiter,
      std::list<wchar_t> const &skip,
      std::wstring const &prediction)
    {
      std::wstring result_str;
      
      try
      {
        read_string(file, delimiter, skip, result_str);
      }
      catch (EndOfSourceException &)
      {
        throw InvalidPredictionException();
      }
      
      if (prediction.compare(result_str) != 0)
      {
        throw InvalidPredictionException();
      }
    }
  }
}

#endif
