 /*
  * Unitex
  *
  * Copyright (C) 2001-2006 Université de Marne-la-Vallée <unitex@univ-mlv.fr>
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

//---------------------------------------------------------------------------
#ifndef LimitsH
#define LimitsH
//---------------------------------------------------------------------------

#include <limits.h>
/* import various macros, e.g.:
   INT_MAX   maximum value of an int
   LONG_MAX                      long int
   UINT_MAX                      unsigned int
   ULONG_MAX                     unsigned long int
*/


#define INT_BITS ((sizeof(int) == 4) ? 32 : ( (sizeof(int) == 8) ? 64 : 32))
/* number of bits in an integer */



#endif
