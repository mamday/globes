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



/* Units and Normalization */

/* Energies GeV */
/* Length km */
/* dm^2 eV^2 */
/* densitie g/cm^3 */
/* X-section 10^-38 cm^2 */
/* Targetmass kiloton (10^6 kg) */
/* Fluxes are normalized to a baseline of 1km */
/* stored_muons is for NuFact only */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "glb_types.h"
#include "glb_error.h"
#include "glb_multiex.h"

#define PI 3.1415
#define NORM 6.02204*1E-12 //10^-38/u (atomic mass unit)
#define GLB_ELECTRON_MASS 0.511E-3 

static double mmu = 0.1056;           // muon mass in GeV
static double beam_pol = 0;           // beam polaristaion
static double beam_en = 20;           // beam energy in GeV
static double beta,rgamma;             // relativistic quantities
static double stored_muons = 2.0E20;  // stored muons per year 
// or protons on target
// care must be taken with this, it is a different number for each experiment
static double power;
static int    channel = 1;            // channel
static int NFLUX = 500;


void glb_flux_loader(glb_flux *data, int number, int polarity);


//this loads the fluxes for all non-NuFact beams
// the files must be of the form
// Energy[GeV] Flux[?]
// You should check the normalisation !!!
// the file has 501 lines


//this part is by Martin and for the Nufact only

void glb_set_max_energy(double en)
{
  beam_en = en;
  rgamma = en/mmu;
  beta = -sqrt(1-1/rgamma/rgamma);
}

double glb_get_max_energy()
{
  return beam_en;
}

static void set_beam_polarisation(double pol)
{
  beam_pol = pol;
}

static double check_beam_polarisation()
{
  return beam_pol;
}

static void set_stored_muons(double n)
{
  stored_muons = n;
}

static double check_stored_muons()
{
  return stored_muons;
}


static void set_power(double n)
{
  power = n;
}

static double check_power()
{
  return power;
}


static void set_channel(double ch)
{
  channel = ch;
}

static double flux_mu(double en, double baseline, double cost_lab)
{
  double x_lab, cost, x, xmax;
  baseline *=1000;

  x_lab = 2*en/mmu;
  cost = (beta+cost_lab)/(1+beta*cost_lab);
  x = x_lab/(rgamma*(1-beta*cost_lab));
  xmax = rgamma*(1-beta*cost_lab);

  if (x_lab < xmax)
    return rgamma*(1 - beta*cost) /baseline/baseline/mmu * stored_muons * x*x/PI * ((3-2*x)-channel*(1-2*x)*beam_pol*cost);
  else
    return 0.0;
}

static double flux_e(double en, double baseline, double cost_lab)
{
  double x_lab, cost, x, xmax;
  baseline *=1000;

  x_lab = 2*en/mmu;
  cost = (beta+cost_lab)/(1+beta*cost_lab);
  x = x_lab/(rgamma*(1-beta*cost_lab));
  xmax = rgamma*(1-beta*cost_lab);

  if (x_lab< xmax)
    return rgamma*(1 - beta*cost) /baseline/baseline/mmu * stored_muons* 6*x*x/PI * ((1-x)-channel*(1-x)*beam_pol*cost);
  else
    return 0.0;
}

static double fastflux_mu(double en, double baseline)
{
  double x_lab, x, xmax;
  baseline *=1000;

  x_lab = 2*en/mmu;
  x = x_lab/(rgamma*(1-beta));
  xmax = rgamma*(1-beta);

  if (x_lab < xmax)
    return rgamma*(1 - beta) /baseline/baseline/mmu * x*x/PI * (3-2*x);
  else
    return 0.0;
}

static double fastflux_e(double en, double baseline)
{
  double x_lab, x, xmax;
  baseline *=1000;

  x_lab = 2*en/mmu;
  x = x_lab/(rgamma*(1-beta));
  xmax = rgamma*(1-beta);

  if (x_lab < xmax)
    return rgamma*(1 - beta) /baseline/baseline/mmu *  6*x*x/PI * (1-x);
  else
    return 0.0;
}
//here ends the NuFact part


/* This type used for all builtin fluxes
 * The need to take the energy, the polarity (ie. neutrinos/anti-neutrinos
 * and they have to take the flavour argument. The need to return at least
 * zero for any valid input. 
 */
typedef double (*flux_calc)(glb_flux *data, double en, int polarity, int l, int anti);

static double nufact_flux(glb_flux *data, double en, int polarity, int l, int anti)
{
  double ergebnis;
  double baseline=1.0;
  ergebnis=0.0;
  if (l==1 && anti == 1 && polarity == 1)
    {
      ergebnis=fastflux_e(en,baseline);
    }
  if (l==2 && anti == -1 && polarity == 1)
    {
      ergebnis=fastflux_mu(en,baseline);
    }
  if (l==1 && anti == -1 && polarity == -1)
    {
      ergebnis=fastflux_e(en,baseline);
    }
  if (l==2 && anti == 1 && polarity == -1)
    {
      ergebnis=fastflux_mu(en,baseline);
    }


  return ergebnis;
}

static double bb_spectrum(double gamma, double end_point, double enu)
{
  double part;
  double result,root;
  double gye,ye;
  double baseline=1000.;
  ye=GLB_ELECTRON_MASS/(end_point+GLB_ELECTRON_MASS);
  gye=(1./60)*(sqrt(1-pow(ye,2))*(2-9*pow(ye,2)-8*pow(ye,4))+15*pow(ye,4)*log10(ye/(1-sqrt(1-pow(ye,2)))));
  part=enu/(2*gamma*(end_point+GLB_ELECTRON_MASS));
  if(part>=1) return 0.0;
  /*  sign is now correct */
  root=(1-part)*(1-part) - ye*ye;
  if(root<=0) return 0.0;
  result=(1./PI/gye/pow(baseline,2))*(gamma*gamma/enu)*pow(part,3)*(1-part)*sqrt(root);
  return result;
}

static double bb_flux(glb_flux *data, double en, int polarity, int l, int anti)
{
  double ergebnis;
  ergebnis=0.0;
  if (l==1 && anti == 1 && polarity == 1)
    {
      ergebnis=bb_spectrum(data->gamma,data->end_point,en);
    }
  if (l==1 && anti == -1 && polarity == -1)
    {
      ergebnis=bb_spectrum(data->gamma,data->end_point,en);
    }


  return ergebnis;
}

static void builtin_flux_setup(glb_flux *data, flux_calc flx, int id,int pl)
{
  /* the id argument is unused */
  double smb,pb,de,emax;
  int i;
  
  if(data->builtin==1||data->builtin==2) de=data->parent_energy/501.0;
  if(data->builtin==3||data->builtin==4) de=2 * data->gamma * (data->end_point + GLB_ELECTRON_MASS)/501.0;
  smb=stored_muons;
  pb=power;
  stored_muons=data->stored_muons;
  power=data->target_power;
  glb_set_max_energy(data->parent_energy);
  data->flux_storage=glb_alloc_flux_storage(501);
  for(i=0;i<501;i++)
    {
      data->flux_storage[i][0]=i*de;
      data->flux_storage[i][1]=flx(data,i*de,pl,1,+1); 
      data->flux_storage[i][2]=flx(data,i*de,pl,2,+1); 
      data->flux_storage[i][3]=flx(data,i*de,pl,3,+1); 
      data->flux_storage[i][4]=flx(data,i*de,pl,1,-1); 
      data->flux_storage[i][5]=flx(data,i*de,pl,2,-1); 
      data->flux_storage[i][6]=flx(data,i*de,pl,3,-1); 
    }
  power=pb;
  stored_muons=smb;
}

void glb_init_fluxtables(glb_flux *data,int pos)
{
  
  if(data->builtin==1) builtin_flux_setup(data,&nufact_flux,pos,+1);
  if(data->builtin==2) builtin_flux_setup(data,&nufact_flux,pos,-1);

  if(data->builtin==3) builtin_flux_setup(data,&bb_flux,pos,+1);
  if(data->builtin==4) builtin_flux_setup(data,&bb_flux,pos,-1);

  if(data->builtin==0||data->builtin==GLB_OLD_NORM) glb_flux_loader(data,pos,+1);
  
}



// Here we settle the normalization issue for all beam types


static double norm2(int type)
{
  double erg;
  switch (type)
    {
    case 1: erg=NORM*100; //NuFact
      break;
    case 2: erg=NORM*100; //NuFact
      break;   
    case 3: erg=NORM*100;//NUMI Beam (9@712) 
      break;
    case 4: erg=NORM*100; //NUMI Beam (9@712) 
      break;
    case GLB_OLD_NORM: erg=NORM*295*295*9.92033*1E6;
      /* here we try to eliminate the stupide 5.2 factor 
       *    default: erg=NORM*295*295*9.92033*1E6; */
      break;
    default: erg=1.0 ;

      break;
    }
  return erg;
}


 
double glb_flux_calc(double en, double baseline, 
	    int type, int l, int anti, const glb_flux *data)
{
   /* the type argument is unused */
  double incre;
  double ergebnis;
  int lowerind;
  int higherind;
  int part=1;
  if (l==1 && anti == 1)
    {
      part = 1;
    }
 if (l==2 && anti == 1)
    {
      part = 2;
    }
 if (l==3 && anti == 1)
    {
      part = 3;
    }
 if (l==1 && anti == -1)
    {
      part = 4;
    }
 if (l==2 && anti == -1)
    {
      part = 5;
    }
 if (l==3 && anti == -1)
    {
      part = 6;
    }
 
 
 incre = (data->flux_storage[500][0]-data->flux_storage[0][0])/501.0;
 lowerind = floor((en-data->flux_storage[0][0])/incre);
 higherind = lowerind + 1;

 if (lowerind<0||higherind>500) 
   {
     ergebnis=0.0;
   }
 else
   {
     ergebnis=((data->flux_storage[higherind][part]-
		data->flux_storage[lowerind][part])*(((en-data->flux_storage[0][0])
						  /incre)-lowerind)
	       +data->flux_storage[lowerind][part])
       /baseline/baseline;
   }     
 ergebnis = ergebnis*norm2(data->builtin) 
   * data->time * data->target_power * data->stored_muons * data->norm;
 return ergebnis;
}

 

/* Here begins the part where the cross-sections are read from 
 * file and made accessible to the program */


/***********************************************************
 * Flux-Loader                                             *
 ***********************************************************/

void glb_flux_loader(glb_flux *data, int ident, int polarity)
{
   /* the polarity  argument is unused */
  int i,number,s,ts=0;
  char tok;
 
  FILE *fp = glb_fopen(data->file_name,"r");
  number=ident;
 
  
  data->flux_storage=glb_alloc_flux_storage(501);
      if (fp!=NULL)
	{ 
	  /* peel off all leading comments */
	  while(1)
	    {
	      tok=fgetc(fp);
	      if(tok=='#') 
		{
		  while(fgetc(fp)!='\n');
		}
	      else
		{
		  ungetc(tok,fp);
		  break;
		}
	    }
	  for (i=0; i<=NFLUX; i++) 
	    {
	      /* get rid of comments inside */
	      tok=fgetc(fp);
	      if(tok=='#') 
		{
		  while(fgetc(fp)!='\n');
		  i--;
		}
	      else
		{
		  ungetc(tok,fp);
		  /* read the data */
		  s=fscanf(fp,"%lf %lf %lf %lf %lf %lf %lf \n",
			   &data->flux_storage[i][0],
			   &data->flux_storage[i][1],
			   &data->flux_storage[i][2], 
			   &data->flux_storage[i][3],
			   &data->flux_storage[i][4],
			   &data->flux_storage[i][5],
			   &data->flux_storage[i][6]);
		  
		  if(s!=7) 
		    fprintf(stderr,"Error: Wrong format in file %s\n",
			    data->file_name);
		  else
		    ts++;		
		}
	      
	    }
	  fclose(fp);
	}
      else
	{
	  fprintf(stderr,"Error: Could not open %s\n",data->file_name); 
	} 
    
      
      if(ts!=501) fprintf(stderr,"Error: Wrong format in file %s\n",
			  data->file_name);      
}


void glb_X_section_loader(glb_xsec *data)
{
  int i,number,s,ts=0;
  char tok;
  FILE* fp;
  fp = glb_fopen(data->file_name, "r");
  data->xsec_storage=glb_alloc_xsec_storage(1001);
  if (fp!=NULL)
  {
    /* peel off all leading comments */
    while(1)
      {
	tok=fgetc(fp);
	if(tok=='#') 
	  while(fgetc(fp)!='\n');
	else
	  {
	    ungetc(tok,fp);
	    break;
	  }
      }
    
    for (i=0; i<1001; i++)
      {
	/* get rid of comments inside */
	tok=fgetc(fp);
	if(tok=='#') 
	  {
	    while(fgetc(fp)!='\n');
	    i--;
	  }
	else
	  {
	    ungetc(tok,fp);
	    /* read the data */
	    s=fscanf(fp,"%lf %lf %lf %lf %lf %lf %lf \n",
		     &data->xsec_storage[i][0],
		     &data->xsec_storage[i][1],
		     &data->xsec_storage[i][2], 
		     &data->xsec_storage[i][3],
		     &data->xsec_storage[i][4],
		     &data->xsec_storage[i][5],
		     &data->xsec_storage[i][6]);
	
	    if(s!=7) 
	      fprintf(stderr,"Error: Wrong format in file %s\n",
		      data->file_name);
	    else
	      ts++;
	  }
      }
    fclose(fp);
  }
  else
    {
      fprintf(stderr,"Error: Could not open %s\n",data->file_name);
    }
  
  if(ts!=1001) fprintf(stderr,"Error: Wrong format in file %s\n",
		      data->file_name);
 
}

double glb_xsec_calc(double enl,int l, int anti, const glb_xsec *data)
{
  double incre;
  double ergebnis;
  double en;
  int lowerind;
  int higherind;

  int part;

  en = log10(enl);
  part = (int) l + 3*(1-anti)/2;

  incre = (data->xsec_storage[1000][0]-data->xsec_storage[0][0])/1000.0;
  lowerind = floor((en-data->xsec_storage[0][0])/incre); 
  higherind = lowerind + 1;

  if (lowerind<0 || higherind>1000) ergebnis=0.0; 
  else
  {
    ergebnis=((data->xsec_storage[higherind][part]-
	       data->xsec_storage[lowerind][part])*
	      (((en-data->xsec_storage[0][0])/incre)-lowerind)
	      +data->xsec_storage[lowerind][part]);
  }
  return ergebnis*enl;
}


void glb_init_xsectables(glb_xsec *data)
{
  
  if(data->builtin==0) glb_X_section_loader(data);
  
}
