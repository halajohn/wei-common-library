// wcl_fmtstr - portable printf-like library
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

#ifndef __fmtstr_internal_h__
#define __fmtstr_internal_h__

/* STRBUF_ENLARGE_SIZE should be >= 1.
 */
#define STRBUF_ENLARGE_SIZE (64)
/* RED_ZONE_SIZE should be smallar than STRBUF_INIT_SIZE &
 * STRBUF_ENLARGE_SIZE
 */
#define RED_ZONE_SIZE (50)

#define MIN_OUTPUT_LENGTH_BUF_SIZE (32)

#if defined(_DEBUG)
struct fmtstr_debug_entry_t
{
  void  *address;
  size_t alloc_size;
  wchar_t const *filename;
  size_t line_no;
  struct fmtstr_debug_entry_t *prev;
  struct fmtstr_debug_entry_t *next;
};
typedef struct fmtstr_debug_entry_t fmtstr_debug_entry_t;
#endif

#endif
