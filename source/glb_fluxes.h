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




#ifndef GLB_NUFACT_H
#define GLB_NUFACT_H 1

#include "glb_types.h"


void glb_set_max_energy(double en);
double glb_get_max_energy();



double glb_flux_calc(double en, double baseline, 
	    int type, int l, int anti, const glb_flux *data);

void glb_init_fluxtables(glb_flux *data,int pos);

double glb_xsec_calc(double enl,int l, int anti, const glb_xsec *data);
void glb_init_xsectables(glb_xsec *data);
void glb_flux_loader(glb_flux *data, int number, int polarity);
void glb_X_section_loader(glb_xsec *data);

#endif /* GLB_NUFACT_H */
