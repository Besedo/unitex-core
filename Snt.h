 /*
  * Unitex
  *
  * Copyright (C) 2001-2006 Universit� de Marne-la-Vall�e <unitex@univ-mlv.fr>
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

#ifndef SntH
#define SntH

/**
 * This structure contains all the files related to a given .snt text
 * file. In order to avoid multiple definitions, none of these files
 * should be named without a structure of this kind.
 */
struct snt_files {
   char* path;
   char* dlf;
   char* dlf_n;
   char* dlc;
   char* dlc_n;
   char* err;
   char* err_n;
   char* stats_n;
   char* stat_dic_n;
   char* text_cod;
   char* tokens_txt;
   char* tok_by_alph_txt;
   char* tok_by_freq_txt;
   char* enter_pos;
   char* concord_ind;
   char* concord_txt;
   char* concord_html;
};


struct snt_files* new_snt_files(char*);
struct snt_files* new_snt_files_from_path(char*);
void free_snt_files(struct snt_files*);

#endif

