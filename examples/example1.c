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
 
 /* 
 * Example: Correlation between s22th13 and deltacp
 * Compile with ``make example1''
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <globes/globes.h>   /* GLoBES library */
#include "myio.h"             /* my input-output routines */
#include "snu.h"             /* NSI */

/* If filename given, write to file; for empty filename write to screen */
char MYFILE[]="test1a.dat";
char MYFILE1[]="test1b.dat";

int main(int argc, char *argv[])
{ 
  /* Initialize libglobes */
  glbInit(argv[0]);

  /* Initialize experiment NFstandard.glb */
//  glbInitExperiment("0709-nova.glb",&glb_experiment_list[0],&glb_num_of_exps); 
  glbInitExperiment("NOvA.glb",&glb_experiment_list[0],&glb_num_of_exps); 
//  glbInitExperiment("Reactor2.glb",&glb_experiment_list[0],&glb_num_of_exps); 
//  glbInitExperiment("NFstandard.glb",&glb_experiment_list[0],&glb_num_of_exps); 
 
  /* Intitialize output */
  InitOutput(MYFILE,"Format: Log(10,s22th13)   deltacp   chi^2 \n"); 

//NSI indices for OscParams, not certain how to get around needing these
  int ABS_EPS_S_EE = 6;
  int ARG_EPS_S_EE = 7;
  int ABS_EPS_S_EMU = 8;
  int ARG_EPS_S_EMU = 9;
  int ABS_EPS_S_ETAU = 10;
  int ARG_EPS_S_ETAU = 11;
  int ABS_EPS_S_MUE = 12;
  int ARG_EPS_S_MUE = 13;
  int ABS_EPS_S_MUMU = 14;
  int ARG_EPS_S_MUMU = 15;
  int ABS_EPS_S_MUTAU = 16;
  int ARG_EPS_S_MUTAU = 17;
  int ABS_EPS_S_TAUE = 18;
  int ARG_EPS_S_TAUE = 19;
  int ABS_EPS_S_TAUMU = 20;
  int ARG_EPS_S_TAUMU = 21;
  int ABS_EPS_S_TAUTAU = 22;
  int ARG_EPS_S_TAUTAU = 23;
  int EPS_M_EE = 24;
  int ABS_EPS_M_EMU = 25;
  int ARG_EPS_M_EMU = 26;
  int ABS_EPS_M_ETAU = 27;
  int ARG_EPS_M_ETAU = 28;
  int EPS_M_MUMU = 29;
  int ABS_EPS_M_MUTAU = 30;
  int ARG_EPS_M_MUTAU = 31;
  int EPS_M_TAUTAU = 32;


  int ABS_EPS_D_EE = 33;
  int ARG_EPS_D_EE = 34;
  int ABS_EPS_D_EMU = 35;
  int ARG_EPS_D_EMU = 36;
  int ABS_EPS_D_ETAU = 37;
  int ARG_EPS_D_ETAU = 38;
  int ABS_EPS_D_MUE = 39;
  int ARG_EPS_D_MUE = 40;
  int ABS_EPS_D_MUMU = 41;
  int ARG_EPS_D_MUMU = 42;
  int ABS_EPS_D_MUTAU = 43;
  int ARG_EPS_D_MUTAU = 44;
  int ABS_EPS_D_TAUE = 45;
  int ARG_EPS_D_TAUE = 46;
  int ABS_EPS_D_TAUMU = 47;
  int ARG_EPS_D_TAUMU = 48;
  int ABS_EPS_D_TAUTAU = 49;
  int ARG_EPS_D_TAUTAU = 50;
  
  /* Define standard oscillation parameters */
//  double theta12 = asin(sqrt(0.8))/2;
  double theta12 = 0.563942;
//  double theta13 = asin(sqrt(0.001))/2;
  double theta13 = 0.154085;
//  double theta13 = 1.4186;
//  double theta23 = M_PI/4;
// More Tau
//  double theta23 = 0.684719;
// More Mu
  double theta23 = 0.88563;
//  double deltacp = 3*M_PI/2;
  double deltacp = M_PI/2;
//  double deltacp = 0.0;
  double sdm = 7.54e-5;
  double ldm = 2.43e-3;

  double eps_s_ee = 0.0;
  double aeps_s_ee = 0.0;
  double eps_s_emu = 0.0;
  double aeps_s_emu = 0.0;
  double eps_s_etau = 0.0;
  double aeps_s_etau = 0.0;
  double eps_s_mue = 0.0;
  double aeps_s_mue = 0.0;
  double eps_s_mumu = 0.0;
  double aeps_s_mumu = 0.0;
  double eps_s_mutau = 0.0;
  double aeps_s_mutau = 0.0;
  double eps_s_taue = 0.0;
  double aeps_s_taue = 0.0;
  double eps_s_taumu = 0.0;
  double aeps_s_taumu = 0.0;
  double eps_s_tautau = 0.0;
  double aeps_s_tautau = 0.0;

  double eps_m_ee = 0.0;
  double eps_m_emu = 0.0;
  double deps_m_emu = 0.0;
//  double eps_m_etau = 0.2;
  double eps_m_etau = 0.0;
  double deps_m_etau = 0.0;
  double eps_m_mumu = 0.0;
//  double eps_m_mutau = 0.01;
  double eps_m_mutau = 0.0;
  double deps_m_mutau = 0.0;
//  double eps_m_tautau = 0.1;
  double eps_m_tautau = 0.0;

  double eps_d_ee = 0.0;
  double aeps_d_ee = 0.0;
  double eps_d_emu = 0.0;
  double aeps_d_emu = 0.0;
  double eps_d_etau = 0.0;
  double aeps_d_etau = 0.0;
  double eps_d_mue = 0.0;
  double aeps_d_mue = 0.0;
  double eps_d_mumu = 0.0;
  double aeps_d_mumu = 0.0;
  double eps_d_mutau = 0.0;
  double aeps_d_mutau = 0.0;
  double eps_d_taue = 0.0;
  double aeps_d_taue = 0.0;
  double eps_d_taumu = 0.0;
  double aeps_d_taumu = 0.0;
  double eps_d_tautau = 0.0;
  double aeps_d_tautau = 0.0;

// Test NSI
  int n_flavors = 3;
  snu_init_probability_engine_3(); 

//NSI Params
  glbRegisterProbabilityEngine(6*(n_flavors)*(n_flavors) - n_flavors,
	&snu_probability_matrix,
	&snu_set_oscillation_parameters,
	&snu_get_oscillation_parameters,
	NULL);

  /* Initialize parameter vector(s) */
  glb_params true_values = glbAllocParams();
  glb_params test_values = glbAllocParams();

//Inverted
//  glbDefineParams(true_values,theta12,theta13,theta23,deltacp,sdm,-ldm+sdm);
//Normal
  glbDefineParams(true_values,theta12,theta13,theta23,deltacp,sdm,ldm);
//Modify Delta
//  glbDefineParams(true_values,theta12,theta13,theta23,3*M_PI/2,sdm,ldm);

  glbSetOscParams(true_values,eps_s_ee,ABS_EPS_S_EE); 
  glbSetOscParams(true_values,aeps_s_ee,ARG_EPS_S_EE); 
  glbSetOscParams(true_values,eps_s_emu,ABS_EPS_S_EMU); 
  glbSetOscParams(true_values,aeps_s_emu,ARG_EPS_S_EMU); 
  glbSetOscParams(true_values,eps_s_etau,ABS_EPS_S_ETAU); 
  glbSetOscParams(true_values,aeps_s_etau,ARG_EPS_S_ETAU); 
  glbSetOscParams(true_values,eps_s_mue,ABS_EPS_S_MUE); 
  glbSetOscParams(true_values,aeps_s_mue,ARG_EPS_S_MUE); 
  glbSetOscParams(true_values,eps_s_mumu,ABS_EPS_S_MUMU); 
  glbSetOscParams(true_values,aeps_s_mumu,ARG_EPS_S_MUMU); 
  glbSetOscParams(true_values,eps_s_mutau,ABS_EPS_S_MUTAU); 
  glbSetOscParams(true_values,aeps_s_mutau,ARG_EPS_S_MUTAU); 
  glbSetOscParams(true_values,eps_s_taue,ABS_EPS_S_TAUE); 
  glbSetOscParams(true_values,aeps_s_taue,ARG_EPS_S_TAUE); 
  glbSetOscParams(true_values,eps_s_taumu,ABS_EPS_S_TAUMU); 
  glbSetOscParams(true_values,aeps_s_taumu,ARG_EPS_S_TAUMU); 
  glbSetOscParams(true_values,eps_s_tautau,ABS_EPS_S_TAUTAU); 
  glbSetOscParams(true_values,aeps_s_tautau,ARG_EPS_S_TAUTAU); 

  glbSetOscParams(true_values,eps_m_ee,EPS_M_EE); 
  glbSetOscParams(true_values,eps_m_emu,ABS_EPS_M_EMU); 
  glbSetOscParams(true_values,deps_m_emu,ARG_EPS_M_EMU); 
  glbSetOscParams(true_values,eps_m_etau,ABS_EPS_M_ETAU); 
//  glbSetOscParams(true_values,0.2,ABS_EPS_M_ETAU); 
  glbSetOscParams(true_values,deps_m_etau,ARG_EPS_M_ETAU); 
//  glbSetOscParams(true_values,M_PI/2,ARG_EPS_M_ETAU); 
  glbSetOscParams(true_values,eps_m_mumu,EPS_M_MUMU); 
  glbSetOscParams(true_values,eps_m_mutau,ABS_EPS_M_MUTAU); 
  glbSetOscParams(true_values,deps_m_mutau,ARG_EPS_M_MUTAU); 
  glbSetOscParams(true_values,eps_m_tautau,EPS_M_TAUTAU); 

  glbSetOscParams(true_values,eps_d_ee,ABS_EPS_D_EE); 
  glbSetOscParams(true_values,aeps_d_ee,ARG_EPS_D_EE); 
  glbSetOscParams(true_values,eps_d_emu,ABS_EPS_D_EMU); 
  glbSetOscParams(true_values,aeps_d_emu,ARG_EPS_D_EMU); 
  glbSetOscParams(true_values,eps_d_etau,ABS_EPS_D_ETAU); 
  glbSetOscParams(true_values,aeps_d_etau,ARG_EPS_D_ETAU); 
  glbSetOscParams(true_values,eps_d_mue,ABS_EPS_D_MUE); 
  glbSetOscParams(true_values,aeps_d_mue,ARG_EPS_D_MUE); 
  glbSetOscParams(true_values,eps_d_mumu,ABS_EPS_D_MUMU); 
  glbSetOscParams(true_values,aeps_d_mumu,ARG_EPS_D_MUMU); 
  glbSetOscParams(true_values,eps_d_mutau,ABS_EPS_D_MUTAU); 
  glbSetOscParams(true_values,aeps_d_mutau,ARG_EPS_D_MUTAU); 
  glbSetOscParams(true_values,eps_d_taue,ABS_EPS_D_TAUE); 
  glbSetOscParams(true_values,aeps_d_taue,ARG_EPS_D_TAUE); 
  glbSetOscParams(true_values,eps_d_taumu,ABS_EPS_D_TAUMU); 
  glbSetOscParams(true_values,aeps_d_taumu,ARG_EPS_D_TAUMU); 
  glbSetOscParams(true_values,eps_d_tautau,ABS_EPS_D_TAUTAU); 
  glbSetOscParams(true_values,aeps_d_tautau,ARG_EPS_D_TAUTAU); 

  glbSetDensityParams(true_values,1.0,GLB_ALL);

//Normal
  glbDefineParams(test_values,theta12,theta13,theta23,deltacp,sdm,ldm);  
//Inverted
//  glbDefineParams(test_values,theta12,theta13,theta23,deltacp,sdm,-ldm+sdm);  

  glbSetOscParams(test_values,eps_s_ee,ABS_EPS_S_EE); 
  glbSetOscParams(test_values,aeps_s_ee,ARG_EPS_S_EE); 
  glbSetOscParams(test_values,eps_s_emu,ABS_EPS_S_EMU); 
  glbSetOscParams(test_values,aeps_s_emu,ARG_EPS_S_EMU); 
  glbSetOscParams(test_values,eps_s_etau,ABS_EPS_S_ETAU); 
  glbSetOscParams(test_values,aeps_s_etau,ARG_EPS_S_ETAU); 
  glbSetOscParams(test_values,eps_s_mue,ABS_EPS_S_MUE); 
  glbSetOscParams(test_values,aeps_s_mue,ARG_EPS_S_MUE); 
  glbSetOscParams(test_values,eps_s_mumu,ABS_EPS_S_MUMU); 
  glbSetOscParams(test_values,aeps_s_mumu,ARG_EPS_S_MUMU); 
  glbSetOscParams(test_values,eps_s_mutau,ABS_EPS_S_MUTAU); 
  glbSetOscParams(test_values,aeps_s_mutau,ARG_EPS_S_MUTAU); 
  glbSetOscParams(test_values,eps_s_taue,ABS_EPS_S_TAUE); 
  glbSetOscParams(test_values,aeps_s_taue,ARG_EPS_S_TAUE); 
  glbSetOscParams(test_values,eps_s_taumu,ABS_EPS_S_TAUMU); 
  glbSetOscParams(test_values,aeps_s_taumu,ARG_EPS_S_TAUMU); 
  glbSetOscParams(test_values,eps_s_tautau,ABS_EPS_S_TAUTAU); 
  glbSetOscParams(test_values,aeps_s_tautau,ARG_EPS_S_TAUTAU); 

  glbSetOscParams(test_values,eps_m_ee,EPS_M_EE); 
  glbSetOscParams(test_values,eps_m_emu,ABS_EPS_M_EMU); 
  glbSetOscParams(test_values,deps_m_emu,ARG_EPS_M_EMU); 
  glbSetOscParams(test_values,eps_m_etau,ABS_EPS_M_ETAU); 
  glbSetOscParams(test_values,deps_m_etau,ARG_EPS_M_ETAU); 
  glbSetOscParams(test_values,eps_m_mumu,EPS_M_MUMU); 
  glbSetOscParams(test_values,eps_m_mutau,ABS_EPS_M_MUTAU); 
  glbSetOscParams(test_values,deps_m_mutau,ARG_EPS_M_MUTAU); 
  glbSetOscParams(test_values,eps_m_tautau,EPS_M_TAUTAU); 

  glbSetOscParams(test_values,eps_d_ee,ABS_EPS_D_EE); 
  glbSetOscParams(test_values,aeps_d_ee,ARG_EPS_D_EE); 
  glbSetOscParams(test_values,eps_d_emu,ABS_EPS_D_EMU); 
  glbSetOscParams(test_values,aeps_d_emu,ARG_EPS_D_EMU); 
  glbSetOscParams(test_values,eps_d_etau,ABS_EPS_D_ETAU); 
  glbSetOscParams(test_values,aeps_d_etau,ARG_EPS_D_ETAU); 
  glbSetOscParams(test_values,eps_d_mue,ABS_EPS_D_MUE); 
  glbSetOscParams(test_values,aeps_d_mue,ARG_EPS_D_MUE); 
  glbSetOscParams(test_values,eps_d_mumu,ABS_EPS_D_MUMU); 
  glbSetOscParams(test_values,aeps_d_mumu,ARG_EPS_D_MUMU); 
  glbSetOscParams(test_values,eps_d_mutau,ABS_EPS_D_MUTAU); 
  glbSetOscParams(test_values,aeps_d_mutau,ARG_EPS_D_MUTAU); 
  glbSetOscParams(test_values,eps_d_taue,ABS_EPS_D_TAUE); 
  glbSetOscParams(test_values,aeps_d_taue,ARG_EPS_D_TAUE); 
  glbSetOscParams(test_values,eps_d_taumu,ABS_EPS_D_TAUMU); 
  glbSetOscParams(test_values,aeps_d_taumu,ARG_EPS_D_TAUMU); 
  glbSetOscParams(test_values,eps_d_tautau,ABS_EPS_D_TAUTAU); 
  glbSetOscParams(test_values,aeps_d_tautau,ARG_EPS_D_TAUTAU); 

  glbSetDensityParams(test_values,1.0,GLB_ALL);

  /* The simulated data are computed */
  glbSetOscillationParameters(true_values);
  glbSetRates();

  /* Iteration over all values to be computed */
  double theetau,x,y,res;    
    
  for(x=-700.0;x<700.0+0.01;x=x+1400.0/280)
  for(y=0.0;y<200.0+0.01;y=y+200.0/50)
  {
      // Set vector of test values 
      theetau=x*.001;
      glbSetOscParams(test_values,theetau,ABS_EPS_M_ETAU); 
      glbSetOscParams(test_values,y*M_PI/180.0,GLB_DELTA_CP);
  
      // Compute Chi^2 for all loaded experiments and all rules 
      res=glbChiSys(test_values,GLB_ALL,GLB_ALL);
      AddToOutput(x,y,res);
  }
//  printf("%f",thetheta13);
//  glbSetOscParams(test_values,theta13,GLB_THETA_13);
  glbSetOscParams(test_values,0.0,ABS_EPS_M_ETAU); 


  InitOutput(MYFILE1,"Format: Log(10,s22th23)   deltacp   chi^2 \n"); 
  double thetheta23;    
  for(x=1;x<200.0+0.01;x=x+200.0/50)
  for(y=0.0;y<360.0+0.01;y=y+360.0/90)
  {
      /* Set vector of test values */
      thetheta23=asin(sqrt((0.6+(x*0.004))/2));
      glbSetOscParams(test_values,thetheta23,GLB_THETA_23);
      glbSetOscParams(test_values,y*(M_PI/180),GLB_DELTA_CP);
  
      /* Compute Chi^2 for all loaded experiments and all rules */
      res=glbChiSys(test_values,GLB_ALL,GLB_ALL);
      AddToOutput(x,y,res);
  }
   
  /* Destroy parameter vector(s) */
  glbFreeParams(true_values);
  glbFreeParams(test_values); 
  snu_free_probability_engine(); 
  exit(0);
}
