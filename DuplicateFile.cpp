 /*
  * Unitex
  *
  * Copyright (C) 2001-2009 Universit� Paris-Est Marne-la-Vall�e <unitex@univ-mlv.fr>
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

#include "Copyright.h"
#include "Error.h"
#include "File.h"
#include "DuplicateFile.h"
#include "getopt.h"


const char* usage_DuplicateFile =
         "Usage: DuplicateFile [OPTIONS] <outfile>\n"
         "\n"
         "  <outfile>: the destination file\n"
         "\n"
         "OPTIONS:\n"
         "-i/--input <infile>: path to input file to read\n"
         "\n";


static void usage() {
u_printf("%S",COPYRIGHT);
u_printf(usage_DuplicateFile);
}


const char* optstring_DuplicateFile=":di:";
const struct option_TS lopts_DuplicateFile[]= {
      {"delete",no_argument_TS,NULL,'d'},
      {"input",required_argument_TS,NULL,'i'},
      {NULL,no_argument_TS,NULL,0}
};


int main_DuplicateFile(int argc,char* argv[]) {
if (argc==1) {
   usage();
   return 0;
}



const char *input_file = NULL;
const char *output_file = NULL;
int do_delete=0;

int val,index=-1;
struct OptVars* vars=new_OptVars();
while (EOF!=(val=getopt_long_TS(argc,argv,optstring_DuplicateFile,lopts_DuplicateFile,&index,vars))) {
   switch(val) {
   case 'd': do_delete=1; break;
   case 'i': input_file = vars->optarg; break;
   case 'h': usage(); return 0;
   case ':': if (index==-1) fatal_error("Missing argument for option -%c\n",vars->optopt);
             else fatal_error("Missing argument for option --%s\n",lopts_DuplicateFile[index].name);
   case '?': if (index==-1) fatal_error("Invalid option -%c\n",vars->optopt);
             else fatal_error("Invalid option --%s\n",vars->optarg);
             break;
   }
   index=-1;
}

if (vars->optind!=argc-1) {
   fatal_error("Invalid arguments: rerun with --help\n");
}

output_file = argv[vars->optind];

if ((input_file==NULL) && (do_delete==0)) {
   fatal_error("You must specify the input_file file\n");
}

if ((input_file!=NULL) && (do_delete==1)) {
   fatal_error("You cannont specify input_file when delete\n");
}
if (output_file==NULL) {
   fatal_error("You must specify the output_file file\n");
}
u_printf("copy file %s to %s\n",input_file,output_file);
int result;
if (input_file != NULL) {
result=af_copy(input_file,output_file);
}
else {
result=af_remove(output_file);
}
u_printf((result==0) ? "Done.\n" : "Unsucessfull.\n");
return result;
}