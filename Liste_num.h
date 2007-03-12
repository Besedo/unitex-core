 /*
  * Unitex
  *
  * Copyright (C) 2001-2007 Universit� de Marne-la-Vall�e <unitex@univ-mlv.fr>
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
#ifndef Liste_numH
#define Liste_numH
//---------------------------------------------------------------------------

#include "Unicode.h"

struct liste_num {
       int n;
       int sommet;
       int* variable_backup;
       struct liste_num* suivant;
       unichar pile[3000];
};

struct liste_num* new_liste_num(int,int);
struct liste_num* inserer_si_absent(int,struct liste_num*,int,unichar*);
struct liste_num* inserer_si_different(int,struct liste_num*,int,unichar*);
void free_list_num(struct liste_num*);

#endif
