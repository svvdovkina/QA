#include "TreeVar.h"

#include "TFile.h"
#include <iostream>
#include <fstream>

TTree* TreeVar::InitTree(char *treefile, char* treename)
{
	TFile *trfile = TFile::Open(treefile);
	TTree *tree = (TTree*)trfile->Get(treename);
	if(tree == 0) 
	{
		std::cout <<treename<<" is not found in "<<treefile<<endl;
		trfile->Close();
		return NULL;
	}
	std::cout << treefile <<" is opened"<<endl;

	if (!tree) return NULL;
   
	tree->SetBranchAddress("run", &run, &b_run);
	tree->SetBranchAddress("bbcz", &bbcz, &b_bbcz);
	tree->SetBranchAddress("cent", &cent, &b_cent);
	tree->SetBranchAddress("nh", &nh, &b_nh);
	tree->SetBranchAddress("p", p, &b_p);
	tree->SetBranchAddress("charge", charge, &b_charge);
	tree->SetBranchAddress("phi0", phi0, &b_phi0);
	tree->SetBranchAddress("the0", the0, &b_the0);
	tree->SetBranchAddress("dcarm", dcarm, &b_dcarm);
	tree->SetBranchAddress("pc3dz", pc3dz, &b_pc3dz);
	tree->SetBranchAddress("pc3dphi", pc3dphi, &b_pc3dphi);
	tree->SetBranchAddress("alpha", alpha, &b_alpha);
	tree->SetBranchAddress("phi", phi, &b_phi);
	tree->SetBranchAddress("zed", zed, &b_zed);
	tree->SetBranchAddress("n0", n0, &b_n0);
	tree->SetBranchAddress("tofdz", tofdz, &b_tofdz);
	tree->SetBranchAddress("tofdphi", tofdphi, &b_tofdphi);
	tree->SetBranchAddress("pc2dz", pc2dz, &b_pc2dz);
	tree->SetBranchAddress("pc2dphi", pc2dphi, &b_pc2dphi);
	tree->SetBranchAddress("ecore", ecore, &b_ecore);
	tree->SetBranchAddress("ttof", ttof, &b_ttof);
	tree->SetBranchAddress("pltof", pltof, &b_pltof);
	tree->SetBranchAddress("etof", etof, &b_etof);
	tree->SetBranchAddress("slat", slat, &b_slat);
	tree->SetBranchAddress("rh", &rh, &b_rh);
	tree->SetBranchAddress("phir", phir, &b_phir);
	tree->SetBranchAddress("time", time, &b_time);
	tree->SetBranchAddress("qr0", qr0, &b_qr0);
	tree->SetBranchAddress("etar", etar, &b_etar);
	tree->SetBranchAddress("armr", armr, &b_armr);
	tree->SetBranchAddress("ring", ring, &b_ring);
	tree->SetBranchAddress("chid", chid, &b_chid);

   return tree;
}