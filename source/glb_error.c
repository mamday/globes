/* GLoBES -- General LOng Baseline Experiment Simulator
 * (C) 2002 - 2007,  The GLoBES Team
 *
 * GLoBES is mainly intended for academic purposes. Proper
 * credit must be given if you use GLoBES or parts of it. Please
 * read the section 'Credit' in the README file.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */




//The principles used in this file are taken from the autotools book by
//Gary V. Vaughan.



#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "glb_error.h"
#include <globes/globes.h>

/* this insures that the exit status of our program has the
 * expected meanining irrespective of the OS
 */
#ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS  0
#  define EXIT_FAILURE  1
#endif

const char *glb_prog_name=NULL;

void glb_prog_name_init (const char *path)
{
  if (!glb_prog_name)
    glb_prog_name =(char*) strdup(path);
}


static int verbosity_level=1;

int glbSetVerbosityLevel(int level)
{
  if(level<0) return -1;
  verbosity_level=level;
  return 0;
}

static void
error (int exit_status, const char *mode, const char *message,int verb_level)
{
  
  if((verb_level==1)||(exit_status)>=0) 
    fprintf (stderr, "%s: %s: %s.\n", glb_prog_name, mode, message);

  if (exit_status >= 0)
    exit (exit_status);
}

void
glb_warning (const char *message)
{
  int v=0;
  if(verbosity_level >= 2) v=1;
  error (-1, "Warning", message,v);
}

void
glb_error (const char *message)
{
  int v=0;
  if(verbosity_level >= 1) v=1;
  error (-1, "ERROR", message,v);
}

void  
glb_fatal (const char *message)
{
  /* A FATAL message always is displayed */
  error (EXIT_FAILURE, "FATAL", message,1);
}

void
glb_exp_error (const struct glb_experiment *exp, const char *message)
{
  char s[100];
  int v=0;
  if (exp == NULL  ||  exp->filename == NULL)
    glb_error(message);
  else
  {
    sprintf(s, "ERROR in experiment %.60s", exp->filename);
    if(verbosity_level >= 1) v=1;
    error (-1, s, message,v);
  }
}

void
glb_rule_error (const struct glb_experiment *exp, int rule, const char *message)
{
  char s[100];
  int v=0;
  if (exp == NULL  ||  exp->filename == NULL)
    glb_error(message);
  else if (rule < 0  ||  rule >= exp->numofrules)
    glb_exp_error(exp, message);
  else
  {
    sprintf(s, "ERROR in experiment %.60s, rule %d", exp->filename, rule);
    if(verbosity_level >= 1) v=1;
    error (-1, s, message,v);
  }
}

/* ----- making the system calls safe ----- */
void *glb_malloc (size_t size)
{
  register void *value = malloc (size);
  if (value == NULL)
    glb_fatal("Virtual memory exhausted");
  return value;
}

void *glb_realloc (void *ptr, size_t size)
{
  register void *value = realloc (ptr, size);
  if (value == NULL)
    glb_fatal("Virtual memory exhausted");
  return value;
}

void glb_free(void *ptr)
{
  if (ptr != NULL)
  {
    free(ptr);
    ptr=NULL;   // FIXME This has no effect
  }
}

FILE *glb_fopen(const char *filename, const char *mode)
{
  size_t i,a,b;
  char *test_name=NULL;
  char *new_name=NULL;
 
  FILE *t;
  register FILE *value; 
  for(i=0;i<glb_path_vector_length;i++)
    {
      a=strlen(filename);
      b=strlen(glb_path_vector[i]);
      test_name=glb_malloc((a+b+2)*sizeof(char));
      test_name=strcpy(test_name,glb_path_vector[i]);
      test_name=strcat(test_name,filename);
      if(verbosity_level >= 4) fprintf(stderr,"Searched path: %s\n",test_name);
      t=fopen(test_name,"r");
      if(t!=NULL) 
	{
	  new_name=strdup(test_name);
	  fclose(t);
	  glb_free(test_name);
	  break;
	}
      glb_free(test_name);
      /* Repeating the exercise with an additional '/' between
       * path and filename.
       */
      a=strlen(filename);
      b=strlen(glb_path_vector[i]);
      test_name=glb_malloc((a+b+2)*sizeof(char));
      test_name=strcpy(test_name,glb_path_vector[i]);
      test_name=strcat(test_name,"/");
      test_name=strcat(test_name,filename);
      t=fopen(test_name,"r");
      if(t!=NULL) 
	{
	  new_name=strdup(test_name); 
	  glb_free(test_name);
	  fclose(t);
	  break;
	}
      glb_free(test_name);
    }

  if(new_name==NULL) {glb_error("File not found");return NULL;}
  
  value = fopen(new_name,mode);
  if(verbosity_level >= 3) fprintf(stderr,"File read: %s\n",new_name);
  glb_free(new_name);
  if(value== NULL)
    glb_error("Could not open file");
  return value;
}

int glb_fclose(FILE *stream)
{
  int i=fclose(stream);
  if(i!=0)
    glb_error("Could not close stream");
  return i;
}


