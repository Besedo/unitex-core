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

#ifndef ABSTRACT_DELA_LOAD_H
#define ABSTRACT_DELA_LOAD_H

struct INF_free_info
{
	void *func_free_inf;
	void *private_ptr;
	void *privateSpacePtr;
	int must_be_free;
} ;

struct BIN_free_info
{
	void *func_free_bin;
	void *private_ptr;
	void *privateSpacePtr;
	int must_be_free;
} ;

const struct INF_codes* load_abstract_INF_file(const char*,struct INF_free_info*);
void free_abstract_INF(const struct INF_codes*,struct INF_free_info*);

const unsigned char* load_abstract_BIN_file(const char*,struct BIN_free_info*);
void free_abstract_BIN(const unsigned char*,struct BIN_free_info*);

#endif
