/**
* Takes text files MeanCosSinNphi.txt from each run folder and makes graph <cos(nphi)>, <sin(nphi)> vs runnumber.
* Puts graphs for different centralities to single .root file - QAt0offset.root
*
* S. Vdovkina svvdovkina@gmail.com
**/

#include "Constants.h"
void GetQAsincos()
{
	char datafile[400][50]; // first dimension should be >= Nruns 

	// reading the runlist and creating array of datafiles names ----
	char runlist[] = "../runlist";
	char runnum[20];
	ifstream frun(runlist);
	if (!frun) {cout<<"can't open "<<runlist<<" file\n"; return;}
	int Nrun = 0;
	while(frun.getline(runnum,20)) 
	{
		sprintf(datafile[Nrun], "../%s/MeanCosSinNphi.txt", runnum);
		Nrun++;
	}
	frun.close();
	// ------

	// **** reading mean cos and sin only for RXN18 det (S+N, out+in)
	Float_t cos[2][NMUL][400]; // first dimension - nharm
	Float_t sin[2][NMUL][400];
	Float_t run[400];

	for (int ir = 0; ir < Nrun; ir++)
	{
		ifstream f(datafile[ir]);
		if (!f) {cout<<"can't open "<<datafile[ir]<<" file\n"; return;}
		for(int ic=0; ic<NMUL; ic++)
		{
			for (int ih = 0; ih < NHARM; ih++ )
			{
				for (int id = 0; id < NDET; id++)
				{
					int cent, harm, det;
					Float_t sincos, sig;
					if (id == NDET-1 && ih != 2) {f>>run[ir]>>cent>>harm>>det>>cos[ih][ic][ir]>>sig>>sin[ih][ic][ir]>>sig;}// for rxn18
					else {f>>run[ir]>>cent>>harm>>det>>sincos>>sig>>sincos>>sig;}
					if (cent != ic || harm != ih) {cout<<"incorrect "<<datafile[ir]<<" file data reading!! ic = "<<ic<<" cent = "<<cent<<" ih = "<<ih<<" harm = "<<harm<<endl; return;}
				}
			}
		}

	}
	// ****

	// make graph of t0 vs runnum for all the centralities and write them to the root file
	TGraph *gr[2][NMUL];

	TFile *outfile = new TFile("MeanCos.root","recreate");
				
	for (int ic = 0; ic < NMUL; ic++)
	{
		for (int ih = 0; ih < 2; ih++ )
		{
			gr[ih][ic] = new TGraphErrors(Nrun, run, cos[ih][ic], 0, 0); 
			gr[ih][ic]->Write();
		}
	}
	outfile->Close();

	TFile *outfile = new TFile("MeanSin.root","recreate");
				
	for (int ic = 0; ic < NMUL; ic++)
	{
		for (int ih = 0; ih < 2; ih++ )
		{
			gr[ih][ic] = new TGraphErrors(Nrun, run, sin[ih][ic], 0, 0); 
			gr[ih][ic]->Write();
		}
	}
	outfile->Close();
}