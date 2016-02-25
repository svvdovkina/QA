#include "Event.h"

#include <iostream>
#include "TH1.h"
#include "TMath.h"

#include "alpha.C"
//#include "alpha39.C"
//#include "matching62.C"
//#include "dzcent.C"


void Event::EventAnalysis(Qvectors *qv, TreeVar *tr, Histos *h)
{
	SetZCentBin(tr);
	if (!GlobalCuts(tr->cent, tr->bbcz)) {return;}

	qv->GetPsi(tr, centbin, zbin);

	for (int ih = 0; ih < NHARM; ih++)
	{
		for(int id=0;id<NDET;id++)
		{
			h->hpsiRP[ih][id][centbin][zbin]->Fill(qv->Psi[ih][id]*180./MYPI);
		}
	}
	//cout<<"psi = "<<qv->Psi[0][0]*180./MYPI<<endl;

	for (int itr = 0; itr < tr->nh; itr++)
	{ //track loop
		SetPtMomPhi(tr, itr);

		Float_t mpi = 0.13957; // GeV
		Float_t L = tr->pltof[itr];
		Float_t t = tr->ttof[itr];
		Float_t t0offset = t - L/MYC*TMath::Sqrt( 1 + mpi*mpi/mom/mom );

		//cout<<"L = "<<L<<" or "<<tr->pltof[itr]<<" t = "<<t<<" mom = "<<mom<<" t0offset = "<<t0offset<<endl;

		h->hT0offset[centbin]->Fill(t0offset);

		for (int ih = 0; ih < NHARM; ih++ )
		{
			for(int id=0;id<NDET;id++)
			{
				h->hcosNphi[ih][id][centbin]->Fill(TMath::Cos((ih+2)*qv->Psi[ih][id]));
				h->hsinNphi[ih][id][centbin]->Fill(TMath::Sin((ih+2)*qv->Psi[ih][id]));
			}
		}
	}
}

void Event::SetZCentBin(TreeVar *tr)
{
	Float_t bbcz = tr->bbcz;
	Float_t cent = tr->cent;
	//get z vertex bin
	Float_t binwidth = (zmax-zmin)/NZPS;
	zbin = (int) ((bbcz - zmin) / binwidth); 
			
	// get cent bin
	binwidth = (centmax - centmin)/NMUL;
	centbin = (int) ((tr->cent - centmin) / binwidth); // right border not included to the bin
	if (cent == centmax) {centbin = NMUL-1;}
}

void Event::SetPtMomPhi(TreeVar *tr, int itr)
{
	newalpha=new_alpha(tr->alpha[itr],tr->phi[itr],tr->dcarm[itr],tr->run);
	Float_t del_alpha = newalpha - tr->alpha[itr];
	newphi = 0.756*del_alpha + tr->phi0[itr];

	Float_t oldpt=tr->p[itr]*sin(tr->the0[itr]);
	pt = oldpt*fabs(tr->alpha[itr]/newalpha);
	pt=pt/1.035;

	mom = pt/sin(tr->the0[itr]);
}

Bool_t Event::GlobalCuts(Float_t cent, Float_t zvert)
{
	// z-vertex  cut
	if(fabs(zvert)>=30) {return false; }

	if (cent<0 || cent>70) {return false; }

	return true;
}