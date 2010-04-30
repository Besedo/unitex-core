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

#ifndef LocatePatternH
#define LocatePatternH

#include "Unicode.h"
#include "String_hash.h"
#include "Fst2.h"
#include "AbstractFst2Load.h"
#include "Text_tokens.h"
#include "List_int.h"
#include "Alphabet.h"
#include "Pattern.h"
#include "OptimizedFst2.h"
#include "Text_parsing.h"
#include "TransductionVariables.h"
#include "LocateConstants.h"
#include "BitArray.h"
/* $CD$ begin */
#include "MorphologicalFilters.h"
/* $CD$ end   */
#include "Stack_unichar.h"
#include "DELA.h"
#include "AbstractDelaLoad.h"
#include "Korean.h"
#include "LocateCache.h"
#include "Vector.h"
#include "MappedFileHelper.h"


/**
 * This structure is used to store all the information needed
 * during the locate operations
 */
struct locate_parameters {
   /**
    * This array is used to associate a control byte to each token.
    * These bytes will be used to know if a token can be matched by
    * <MOT>, <DIC>, <MIN>, <MAJ>, etc. All the bit masks to be used
    * are defined in LocateConstants.h with names like XXX_TOKEN_BIT_MASK
    */
   unsigned char* token_control;

   /**
    * This array is used to know the patterns that can match tokens. If the
    * token x is matched by no pattern, then matching_patterns[x]=NULL; Otherwise,
    * matching_patterns[x] will be a bit array so that matching_patterns[x]->array[y]
    * will be 1 if the pattern y can match the token x and 0 otherwise.
    */
   struct bit_array** matching_patterns;

   /* This field is used to know the current compound pattern number */
   int current_compound_pattern;

   /* This field designates a tree that contains all the patterns defined
    * in the grammar tags (ex: <machine.N+Conc>, <V-z2:Kms>, etc). It is
    * used to associate a unique number to each pattern */
   struct pattern_node* pattern_tree_root;

   /* Number of the space token in the text */
   int SPACE;

   /* Number of the sentence delimiter {S} in the text */
   int SENTENCE;

   /* Number of the stop token {STOP} in the text */
   int STOP;

   /* Numbers of the tokens that are tags like {soon,.ADV} */
   struct list_int* tag_token_list;

   #ifdef TRE_WCHAR
   /* These two fields are used to manipulate morphological filters like:
    *
    * <<en$>>
    *
    * 'filters' is a structure used to store the filters. 'filter_match_index' is used to
    * know if a given token is matched by a given filter.
    */
   FilterSet* filters;
   FilterMatchIndex* filter_match_index;
   #endif

   /* The compound word tree*/
   struct DLC_tree_info* DLC_tree;

   /* Array containing optimized states equivalent to the original fst2 ones */
   OptimizedFst2State* optimized_states;

   /* The original fst2 */
   Fst2* fst2;

   /* The tags of the original fst2, for optimization reasons */
   Fst2Tag* tags;

   /* The text tokens */
   struct string_hash* tokens;

   /* Current origin position in the token buffer */
   int current_origin;

   /* the maximum number of locate call for each token */
   int max_count_call;
   int max_count_call_warning;

   /* A system-dependent object that represents the mapped' text.cod' file */
   ABSTRACTMAPFILE* text_cod;

   /* The token buffer used to parse the text. This is a pointer
    * that must be initialized after mapping the 'text.cod' file */
   int* buffer;
   int buffer_size;

   /* Indicates if we work char by char or not */
   TokenizationPolicy tokenization_policy;

   /* Indicates if we allow matches that start with spaces */
   SpacePolicy space_policy;

   /* Total number of matching tokens. This value is used to compute
    * some statistics. */
   int matching_units;

   /* Policy for match selection */
   MatchPolicy match_policy;

   /* Policies for handling outputs */
   OutputPolicy output_policy;
   AmbiguousOutputPolicy ambiguous_output_policy;
   VariableErrorPolicy variable_error_policy;

   /* The match list associated to the current Locate operation */
   struct match_list* match_list;

   /* The total number of matches */
   int number_of_matches;

   /* The total number of outputs. It may be different from the number
    * of matches if ambiguous outputs are allowed. */
   int number_of_outputs;

   /* Position of the last printed match. It is used when ambiguous outputs
    * are used. */
   int start_position_last_printed_match;
   int end_position_last_printed_match;

   /* Indicates the number of matches we want, or NO_MATCH_LIMIT (-1) if
    * there is no limit. */
   int search_limit;

   /* The transduction variables of the fst2 */
   Variables* variables;

   /* This is the stack used to process outputs */
   struct stack_unichar* stack;
   /* This field is used to remember where the current stack base is for
    * the current subgraph. */
   int stack_base;

   /* The alphabet of the current language */
   Alphabet* alphabet;

   /* These 2 fields represent the dictionary array to use in
    * morphological mode, if any. */
   const struct INF_codes** morpho_dic_inf;
   const unsigned char** morpho_dic_bin;
   struct INF_free_info* morpho_dic_inf_free;
   struct BIN_free_info* morpho_dic_bin_free;

   /* Size of previous arrays */
   int n_morpho_dics;

   /* The DELAF entry variables filled in morphological mode */
   struct dic_variable* dic_variables;

   /* These 2 fields are used to manage left contexts.
    * - left_ctx_shift = shift value to add to the start of the match
    * - left_ctx_base = stack base
    */
   int left_ctx_shift;
   int left_ctx_base;

   /* This information is used to know if we must protect input dots and commas */
   int protect_dic_chars;

   int mask_encoding_compatibility_input;

   /* This is useful for Korean */
   Korean* korean;
   unichar** jamo_tags;

   /* a recyclable buffer to be given to string_match_filter function.
    *   To avoid stack or heap allocation at each call */
   wchar_t* recyclable_wchart_buffer;

   /* This field is used to store the maximum position in tokens reached
    * during an exploration from a given start position. After the exploration
    * is complete, if this position is <= than the end position of the longest match
    * computed from the current start position, then we know that no longer match
    * could have been possible and we can cache the matches for later quick lookups.
    */
   int last_tested_position;
   /* This is the end position of the current longest match */
   int last_matched_position;
   /* This structure is used to mark tokens that cannot start any match */
   struct bit_array* failfast;
   /* Those two fields are used to store matches while exploring from a given
    * position. Once the exploration is complete, we deal with the matches,
    * caching them if possible. We need two pointers because we have to insert
    * at the end of the cache list */
   struct match_list* match_cache_first;
   struct match_list* match_cache_last;
   /* This is the cache array to store matches */
   LocateCache* match_cache;
   /* This vector is used to store results obtained from cache consultation */
   vector_ptr* cached_match_vector;
};


int locate_pattern(char*,char*,char*,char*,char*,char*,char*,
                   MatchPolicy,OutputPolicy,Encoding,int,int,char*,TokenizationPolicy,
                   SpacePolicy,int,char*,AmbiguousOutputPolicy,
                   VariableErrorPolicy,int,int,int,int);

void numerote_tags(Fst2*,struct string_hash*,int*,struct string_hash*,Alphabet*,int*,int*,int*,int,struct locate_parameters*);
unsigned char get_control_byte(unichar*,Alphabet*,struct string_hash*,TokenizationPolicy);
void compute_token_controls(Alphabet*,char*,struct locate_parameters*);

#endif
