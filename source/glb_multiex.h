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




#ifndef GLB_MULTIEX_H
#define GLB_MULTIEX_H 1

#include "glb_types.h"

extern int glb_current_exp;

glb_exp glbAllocExp();

void glbSetExperiment(glb_exp in);   
int glbDefaultExp(glb_exp ins);      
void glbInitExp(glb_exp ins);        
void glbFreeExp(glb_exp ins);        


void glb_set_profile_scaling(double scale,int i);

glb_flux *glb_flux_alloc();
void glb_flux_free(glb_flux *stale);
int glb_default_flux(glb_flux *in);
glb_flux  *cpy_glb_flux(glb_flux *dest, const glb_flux *src);

glb_flux *glb_flux_reset(glb_flux *temp);
double** glb_alloc_flux_storage(size_t lines);
void glb_free_flux_storage(double **stale);

glb_xsec *glb_xsec_alloc();
void glb_xsec_free(glb_xsec *stale);
int glb_default_xsec(glb_xsec *in);
glb_xsec  *cpy_glb_xsec(glb_xsec *dest, const glb_xsec *src);

glb_xsec *glb_xsec_reset(glb_xsec *temp);
double** glb_alloc_xsec_storage(size_t lines);
void glb_free_xsec_storage(double **stale);



#endif /* GLB_MULTIEX_H */
