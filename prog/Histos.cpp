#include "Histos.h"

#include <iostream>
#include <fstream>

#include "TFile.h"
#include "TF1.h"

void Histos::BookHist()
{
	char name[200];
	char title[200];

	Float_t binwidth = (centmax - centmin)/NMUL;

	for(int ih=0; ih < NHARM; ih++)
	{
		for(int id=0;id<NDET;id++)
		{
			for(int ic=0; ic<NMUL; ic++)
			{
				int cent_low = (int) (centmin + ic*binwidth);
				int cent_high = (int) (centmin + (ic+1)*binwidth);

				sprintf(name,"hcosNphi_det%i_cent%i_h%i", id, ic, ih);
				sprintf(title,"cos(%i#Psi_{%i RP det%i}), Cent: %i-%i%%", ih+2, ih+2, id, cent_low,cent_high);
				hcosNphi[ih][id][ic] = new TH1F(name, title, 200, -1, 1);

				sprintf(name,"hsinNphi_det%i_cent%i_h%i", id, ic, ih);
				sprintf(title,"sin(%i#Psi_{%i RP det%i}), Cent: %i-%i%%", ih+2, ih+2, id, cent_low,cent_high);
				hsinNphi[ih][id][ic] = new TH1F(name, title, 200, -1, 1);

				for(int iz=0;iz<NZPS;iz++)
				{    
					sprintf(name,"hpsiRP%i_det%i_cent%i_z%i", ih, id, ic, iz);
					sprintf(title,"#Psi_{%i RP det%i}, Cent: %i-%i%%, Z:%i", ih+2, id,cent_low,cent_high, iz);
					hpsiRP[ih][id][ic][iz] = new TH1F(name,title,200,-200.,200.);
				}
			}    
		}
	}

	for(int ic=0; ic<NMUL; ic++)
	{
		int cent_low = (int) (centmin + ic*binwidth);
		int cent_high = (int) (centmin + (ic+1)*binwidth);

		sprintf(name,"hT0offset_cent%i",ic);
		sprintf(title,"T_{TOF} - T_{#pi exp}, Cent: %i-%i%%", cent_low,cent_high);
		hT0offset[ic] = new TH1F(name, title, 300, -2., 10.);

	}

	std::cout<<"hists booked!\n";
}

void Histos::WriteHist(int run)
{
	/*char hist_file[200];
	sprintf(hist_file, "../%i/hist.root", run);

	TFile *outfilehist = new TFile(hist_file,"recreate");
	outfilehist->cd();
	for(int ic=0; ic<NMUL; ic++)
	{
		hT0offset[ic] -> Write();

		for (int ih = 0; ih < NHARM; ih++ )
		{
			for (int id = 0; id < NDET; id ++)
			{
				hcosNphi[ih][id][ic] -> Write();
				hsinNphi[ih][id][ic] -> Write();

				for(int iz=0;iz<NZPS;iz++)
				{
					hpsiRP[ih][id][ic][iz]->Write();				
				}
			}
		}
	}
	outfilehist->Close();*/

	char name[200];

	sprintf(name, "../%i/T0offset.txt", run);
	ofstream foutT(name);

	TF1 *fitGaus = new TF1("fitGaus","gaus", -1., 1.);

	for(int ic=0; ic<NMUL; ic++)
	{
		hT0offset[ic]->Fit(fitGaus, "R");
		//parameters (1) and (2) are gaussian mean and sigma (parameter (0) is integral(?))
		foutT<<run<<" "<<ic<<" "<<fitGaus->GetParameter(1)<<" "<<fitGaus->GetParameter(2)<<std::endl;
	}
	foutT.close();

	sprintf(name, "../%i/MeanCosSinNphi.txt", run);
	ofstream fout(name);
	for(int ic=0; ic<NMUL; ic++)
	{
		for (int ih = 0; ih < NHARM; ih++ )
		{
			for (int id = 0; id < NDET; id++)
			{
				Double_t mCos = hcosNphi[ih][id][ic]->GetMean();
				Double_t sigCos = hcosNphi[ih][id][ic]->GetRMS(); 
				Double_t mSin = hsinNphi[ih][id][ic]->GetMean();
				Double_t sigSin = hsinNphi[ih][id][ic]->GetRMS(); 
				fout<<run<<" "<<ic<<" "<<ih<<" "<<id<<" "<<mCos<<" "<<sigCos<<" "<<mSin<<" "<<sigSin<<std::endl;
			}
		}
	}
	fout.close();	
}