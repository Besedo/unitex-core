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

#ifndef Stack_intH
#define Stack_intH


/**
 * This structure represents a stack of integers.
 */
struct stack_int {
   int* stack;
   /* Pointer on the top element, -1 if the stack is empty */
   int stack_pointer;
   /* Maximum capacity of the stack */
   int capacity;
};


struct stack_int* new_stack_int(int);
void free_stack_int(struct stack_int*);
int is_empty(struct stack_int*);
int is_full(struct stack_int*);
void push(struct stack_int*,int);
int pop(struct stack_int*);

#endif
