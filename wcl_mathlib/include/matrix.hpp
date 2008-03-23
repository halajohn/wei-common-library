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

#ifndef __wcl_mathlib_matrix_hpp__
#define __wcl_mathlib_matrix_hpp__

#include "wcl_types.hpp"
#include "exception.hpp"

#if defined(WCL_MATHLIB_EXPORTS)
#define WCL_MATHLIB_EXPORT __declspec(dllexport)
#else
#define WCL_MATHLIB_EXPORT __declspec(dllimport)
#endif

namespace Wcl
{
  namespace Mathlib
  {
    namespace Matrix
    {
      template<typename T, uint32_t M, uint32_t N>
      double_t
      get_minor(
        boost::numeric::ublas::bounded_matrix<T, M, N> const matrix,
        typename boost::numeric::ublas::bounded_matrix<T, M, N>::size_type const discarded_row,
        typename boost::numeric::ublas::bounded_matrix<T, M, N>::size_type const discarded_column)
      {
        boost::numeric::ublas::bounded_matrix<T, M, N> minor_matrix(matrix.size1() - 1, matrix.size2() - 1);
        
        boost::numeric::ublas::bounded_matrix<T, M, N>::size_type dest_row = 0;
        
        for (boost::numeric::ublas::bounded_matrix<T, M, N>::const_iterator1 row = matrix.begin1();
             row != matrix.end1();
             ++row)
        {
          if (row.index1() == discarded_row)
          {
            continue;
          }
          
          boost::numeric::ublas::bounded_matrix<T, M, N>::size_type dest_column = 0;
          
          for (boost::numeric::ublas::bounded_matrix<T, M, N>::const_iterator2 column = row.begin();
               column != row.end();
               ++column)
          {
            if (column.index2() == discarded_column)
            {
              continue;
            }
            
            minor_matrix(dest_row, dest_column) = (*column);
      
            ++dest_column;
          }
      
          ++dest_row;
        }
    
        return det(minor_matrix);
      }
      
      // Determinants are defined only for square matrices.
      template<typename T, uint32_t M>
      double_t
      det(boost::numeric::ublas::bounded_matrix<T, M, M> const matrix)
      {
        if (1 == matrix.size1())
        {
          return matrix(0, 0);
        }
        else
        {
          double_t result = 0;
          
          boost::numeric::ublas::bounded_matrix<T, M, M>::const_iterator1 row = matrix.begin1();
        
          {
            for (boost::numeric::ublas::bounded_matrix<T, M, M>::const_iterator2 column = row.begin();
                 column != row.end();
                 ++column)
            {
              double_t const element_value = (*column);
              int32_t const row_add_column =
                boost::numeric_cast<int32_t>(row.index1() + column.index2());
              double_t const positive_or_negative = pow(-1.0, row_add_column);
              double_t const minor = get_minor(matrix, row.index1(), column.index2());
            
              result += (element_value * positive_or_negative * minor);
            }
          }
        
          return result;
        }
      }
      
      template<typename T, uint32_t M>
      bool
      is_singular(boost::numeric::ublas::bounded_matrix<T, M, M> const matrix)
      {
        if (0 == det(matrix))
        {
          return true;
        }
        else
        {
          return false;
        }
      }
      
      template<typename T, uint32_t M>
      bool
      is_unimodular(
        boost::numeric::ublas::bounded_matrix<T, M, M> const matrix)
      {
        if (1 == det(matrix))
        {
          return true;
        }
        else
        {
          return false;
        }
      }
      
      template<typename T>
      void
      inverse(
        boost::numeric::ublas::bounded_matrix<T, 2, 2> const matrix,
        boost::numeric::ublas::bounded_matrix<T, 2, 2> &inverse_matrix)
      {
        double_t const det_value = det(matrix);
        
        if (0.0 == det_value)
        {
          // singular matrix doesn't have inverse.
          throw GetInverseFromSingularMatrixException();
        }
        
        inverse_matrix(0, 0) = (matrix(1, 1) / det_value);
        inverse_matrix(0, 1) = -(matrix(0, 1) / det_value);
        inverse_matrix(0, 1) = -(matrix(1, 0) / det_value);
        inverse_matrix(0, 1) = (matrix(0, 0) / det_value);
      }
      
      template<typename T>
      void
      inverse(
        boost::numeric::ublas::bounded_matrix<T, 3, 3> const matrix,
        boost::numeric::ublas::bounded_matrix<T, 3, 3> &inverse_matrix)
      {
        double_t const det_value = det(matrix);
        
        if (0.0 == det_value)
        {
          // singular matrix doesn't have inverse.
          throw GetInverseFromSingularMatrixException();
        }
        
        inverse_matrix(0, 0) =  (get_minor(matrix, 0, 0) / det_value);
        inverse_matrix(0, 1) = -(get_minor(matrix, 1, 0) / det_value);
        inverse_matrix(0, 2) =  (get_minor(matrix, 2, 0) / det_value);
    
        inverse_matrix(1, 0) = -(get_minor(matrix, 0, 1) / det_value);
        inverse_matrix(1, 1) =  (get_minor(matrix, 1, 1) / det_value);
        inverse_matrix(1, 2) = -(get_minor(matrix, 2, 1) / det_value);
    
        inverse_matrix(2, 0) =  (get_minor(matrix, 0, 2) / det_value);
        inverse_matrix(2, 1) = -(get_minor(matrix, 1, 2) / det_value);
        inverse_matrix(2, 2) =  (get_minor(matrix, 2, 2) / det_value);
      }
    }
  }
}

#endif
