 /*
  * Unitex
  *
  * Copyright (C) 2001-2010 Universit� Paris-Est Marne-la-Vall�e <unitex@univ-mlv.fr>
  *
  * This library is free software; you can redistribute it and/or
  * modify it under the terms of the GNU Lesser General Public
  * License as published by the Free Software Foundation; either
  * version 2.1 of the License, or (at your option) any later version.
  *
  * This library is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  * Lesser General Public License for more details.
  *
  * You should have received a copy of the GNU Lesser General Public
  * License along with this library; if not, write to the Free Software
  * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
  *
  */

#ifndef MappedFileH
#define MappedFileH

/**
 * This library provides an abstraction for mapping and unmapping files
 * in read-only mode in a portable way.
 */

#ifdef _NOT_UNDER_WINDOWS
/* Linux definition of a mapped file */
#include "Unicode.h"

typedef struct {
   U_FILE* f;
   void* ptr;
   size_t length;
} MappedFile;

#else
/* Windows definition of a mapped file */
#include <windef.h>
#include <stdarg.h>
#include <winbase.h>

typedef struct {
   HANDLE file;
   HANDLE mappedFile;
   LPVOID ptr;
} MappedFile;

#endif


void* my_mmap(char*,MappedFile*);
void my_munmap(MappedFile);

#endif

