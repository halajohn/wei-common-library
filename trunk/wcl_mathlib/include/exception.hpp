// wcl_mathlib - portable math library
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

#ifndef __wcl_mathlib_exception_hpp__
#define __wcl_mathlib_exception_hpp__

namespace Wcl
{
  namespace Mathlib
  {
    class GetInverseFromSingularMatrixException : public std::exception
    {
      virtual char const *what() const throw()
      {
        return "Get inverse matrix from a singular matrix (det = 0).";
      }
    };
    typedef class GetInverseFromSingularMatrixException GetInverseFromSingularMatrixException;
  }
}

#endif
