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


/* Nom 		: compgr.h */
/* Date 	: juin 98 */
/* Auteur(s) 	: MAYER Laurent et al */

#ifndef _COMPGR_H_
#define _COMPGR_H_

#include "autalmot.h"


#define ELAG_MAX_CONSTRAINTS 8
#define ELAG_UNDEFINED (-1)


/**
 * ....
 */
typedef struct {
  Fst2Automaton* left;
  Fst2Automaton* right;
} elContext;


/**
 * This structure defines a single ELAG rule.
 */
typedef struct {
   /* Name of the .fst2 file that contains this rule */
   char* name;
   
   /* The automaton that corresponds to the rule */
   Fst2Automaton* automaton;      /* Automate lu dans un fichier */
   
   /* Number of contexts, at least 1 */
   int nbContexts;
   
   /* Array of the contexts */
   elContext* contexts;
} elRule;


int compile_elag_grammar(char*,char*);
int compile_rules(char * rulesname, char * outname);

#endif
