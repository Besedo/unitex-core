
 /*
  * Unitex
  *
  * Copyright (C) 2001-2007 Université de Marne-la-Vallée <unitex@univ-mlv.fr>
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
  
#include <errno.h>
#include <stdio.h>
#include <getopt.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "Snt.h"
#include "Error.h"
#include "Unicode.h"
#include "defines.h"
#include "Alphabet.h"
#include "Copyright.h"
#include "CollocMain.h"
#include "Collocation.h"
#include "Text_tokens.h"

static void usage(int header) {

	if (header) {
		u_printf("%S", COPYRIGHT);
		u_printf(
			"This is a tool that is aimed to be used to extract collocations. "
			"It works on the normalized text automata.\n"
			"\n"
		);
	}

	u_printf(
		"Usage: Colloc [OPTIONS] <snt directory>\n"
		"\n"
		"Parameters:\n"
		"     -?, --help                    Shows this message\n"
		"     -c, --combination-length=LEN  TODO: The length of word combinations. The p in C(n,p)\n"
		"     -h, --threshold               Frequency threshold for printing the results.\n"
		"     -m, --compact=PERIOD          Compact the array every PERIOD sentences. This means to\n"
		"                                   prune all the combinations that are below half the\n" 
		"                                   threshold. This is a simple heuristic to let Colloc parse\n"
#ifdef BDB
		"                                   giant corpora. 5000 seems to be a reasonable choice for a\n"
#else
		"                                   giant corpora. 10000 seems to be a reasonable choice for a\n"
#endif
		"                                   machine with 256MB free physical ram.\n"
		"     -l, --linear-width=LEN        TODO: The limit in which the token combinations are formed. FIXME: Do we need this, actually?\n"
		"                                   This the n in C(n,p).\n"
		"     -q, --quiet                   Dont print anything except the results and errors.\n"
		"     -r, --range=<range>           Limit number of sentences to process, to get around memory\n"
		"                                   limitations. <range> is two positive integers with a comma\n"
        "                                   between. Example: --range=4500,8000\n"
		"     -t, --strip-tags              POS tags to strip from the collocation candidates.\n"
		"               =TAG1,TAG2,...\n"
		"     -w, --strip-words             Words to strip from the collocation candidates.\n"
		"               =WORD1,WORD2,...    Uses canonical form of the words.\n"
		"\n"
	); 
}

/* 
 * This function behaves in the same way as an int main(), except that it does
 * not invoke the setBufferMode function.
 */

int main_Colloc(int argc, char **argv) {

	char ch;
	int option_index = 0;
	
	const struct option longopts[] = { 
		 {                  "help",       no_argument, NULL, '?' }
		,{    "combination-length", required_argument, NULL, 'c' }
		,{             "threshold", required_argument, NULL, 'h' }
		,{               "compact", required_argument, NULL, 'm' }
		,{          "linear-width", required_argument, NULL, 'l' } 
		,{                 "quiet",       no_argument, NULL, 'q' }	
		,{                 "range", required_argument, NULL, 'r' }
		,{            "strip-tags", required_argument, NULL, 't' }
		,{           "strip-words", required_argument, NULL, 'w' }
		,{NULL, 0, NULL, 0}
	};

	colloc_opt option;
	option.clength   = 2; 
	option.lwidth    = 0;
	option.spos      = NULL;
	option.swords    = NULL;
	option.rstart    = 0;
	option.rend      = 0;
	option.threshold = 0;
	option.compact   = 0;
	option.quiet     = 0;

	while ((ch = getopt_long(argc, argv, "?c:l:t:w:h:r:m:", longopts, &option_index)) != -1) {
		switch (ch) {
	
		case '?':
			usage(1);
			exit(EXIT_SUCCESS);
			break;	
	
		case 'c':
			STRINGINT(optarg, option.clength);
			if (option.clength <= 2) {
				u_printf("combination length must be > 2\n\n");
				exit (EXIT_FAILURE);
			}
			break;

		case 'l':
			STRINGINT(optarg, option.lwidth);
			if (option.lwidth <= 0) {
				u_printf("linear context width must be > 0\n\n");
				exit (EXIT_FAILURE);
			}
			break;

		case 'h':
			STRINGINT(optarg, option.threshold);
			if (option.threshold < 0) {
				u_printf("threshold width must be >= 0\n\n");
				exit (EXIT_FAILURE);
			}
			break;

		case 't': {
			char *p=optarg, *q=optarg;
			int len;
			int size=1;

			while (1) {
				if ( *p==',' || *p==0 ) {
					len = p-q;
					if (len) {
						size++;
					}
					q=p+1;
				}

				if (! *p) break;
				p++;
			}
			
			custom_malloc( unichar*, size, option.spos );

			p=optarg;
			q=optarg;
			size=0;
			while (1) {
				if ( *p==',') {
					len = p-q;
					if (len) {
						custom_malloc( unichar, (len+1), option.spos[size] );
						*p=0; u_sprintf( option.spos[size], "%s", q ); *p=',';
						size++;
					}
					q=p+1;
				}

				if (! *p) {
					len = p-q;
					if (len) {
						custom_malloc( unichar, (len+1), option.spos[size] );
						u_sprintf( option.spos[size], "%s", q );
						size++;
					}
					break;
				}
				p++;
			}

			option.spos[size]=0;
			break;
			
		}

		case 'w': {
			char *p=optarg, *q=optarg;
			int len;
			int size=1;

			while (1) {
				if ( *p==',' || *p==0 ) {
					len = p-q;
					if (len) {
						size++;
					}
					q=p+1;
				}

				if (! *p) break;
				p++;
			}
			
			custom_malloc( unichar*, size, option.swords );

			p=optarg;
			q=optarg;
			size=0;
			while (1) {
				if ( *p==',') {
					len = p-q;
					if (len) {
						custom_malloc( unichar, (len+1), option.swords[size] );
						*p=0; u_sprintf( option.swords[size], "%s", q ); *p=',';
						size++;
					}
					q=p+1;
				}

				if (! *p) {
					len = p-q;
					if (len) {
						custom_malloc( unichar, (len+1), option.swords[size] );
						u_sprintf( option.swords[size], "%s", q );
						size++;
					}
					break;
				}
				p++;
			}

			option.swords[size]=0;
			break;
			
		}

		case 'q': 
			option.quiet=1;
			break;

		case 'r': {
			char *p;
			int tmp;

			p=u_strchr(optarg, ',');
			if (p) {
				*p=0; 
				p++;
			}
			else {
				usage(1);
				u_printf("Invalid argument to --range (-r).\n");
				exit(EXIT_FAILURE);
			}

			STRINGINT(optarg, tmp);
			if (tmp < 1) {
				u_printf("the first range value must be bigger than zero.\n\n");
				exit (EXIT_FAILURE);
			}

			option.rstart=tmp;

			STRINGINT(p, tmp);
			if ( option.rstart >= tmp) {
				u_printf("the second range value must be bigger than the first.\n\n");
				exit (EXIT_FAILURE);
			}

			option.rend=tmp;
			
			break;
		}
		case 'm': {
			int tmp;
			STRINGINT(optarg, tmp);
			if (tmp < 0) {
				u_printf("compact period must be > 0\n\n");
				exit (EXIT_FAILURE);
			}
			option.compact=tmp;

			break;
		}

		default:
			exit (EXIT_FAILURE);
		
		}
	}
		
	char text_snt[FILENAME_MAX];
	if (optind < argc) {
		if (strlen (argv[optind]) > FILENAME_MAX) {
			u_fprintf(stderr, "`%s' is too long for a file name (max=%d)", argv[optind], FILENAME_MAX);
			exit (EXIT_FAILURE);
		}
		else {
			get_path ( argv[optind], text_snt );
	    }
	}
	else { 
		usage(1);
		u_fprintf(stderr, "Error: no snt directory specified\n\n");
		exit(EXIT_FAILURE);
	}
	
	struct snt_files* snt_files=NULL;
	snt_files = new_snt_files_from_path(text_snt);

	array_t candidates=NULL;
	
	candidates=colloc_generate_candidates(snt_files, option);
	colloc_print(candidates, option);
	if (! option.quiet) u_fprintf(stderr,"freeing resources...\n");
	colloc_free(&candidates);
	
	if (! option.quiet) u_fprintf(stderr,"Done.\n");
	
	return 0;
}


