#ifndef TREEVAR_H
#define TREEVAR_H
#include "Constants.h"

#include "TTree.h"

class TreeVar
{	
	// List of branches
	TBranch        *b_run;   //!
	TBranch        *b_bbcz;   //!
	TBranch        *b_cent;   //!
	TBranch        *b_nh;   //!
	TBranch        *b_p;   //!
	TBranch        *b_charge;   //!
	TBranch        *b_phi0;   //!
	TBranch        *b_the0;   //!
	TBranch        *b_dcarm;   //!
	TBranch        *b_pc3dz;   //!
	TBranch        *b_pc3dphi;   //!
	TBranch        *b_alpha;   //!
	TBranch        *b_phi;   //!
	TBranch        *b_zed;   //!
	TBranch        *b_n0;   //!
	TBranch        *b_tofdz;   //!
	TBranch        *b_tofdphi;   //!
	TBranch        *b_pc2dz;   //!
	TBranch        *b_pc2dphi;   //!
	TBranch        *b_ecore;   //!
	TBranch        *b_ttof;   //!
	TBranch        *b_pltof;   //!
	TBranch        *b_etof;   //!
	TBranch        *b_slat;   //!
	TBranch        *b_rh;   //!
	TBranch        *b_phir;   //!
	TBranch        *b_time;   //!
	TBranch        *b_qr0;   //!
	TBranch        *b_etar;   //!
	TBranch        *b_armr;   //!
	TBranch        *b_ring;   //!
	TBranch        *b_chid;   //!

	
public:
	TTree* InitTree(char *treefile, char* treename);

	// Declaration of leaf types
	Int_t           run;
	Float_t         bbcz;
	Float_t         cent;
	Int_t           nh;
	Float_t         p[MAXNH];   //[nh]
	Short_t         charge[MAXNH];   //[nh]
	Float_t         phi0[MAXNH];   //[nh]
	Float_t         the0[MAXNH];   //[nh]
	Short_t         dcarm[MAXNH];   //[nh]
	Float_t         pc3dz[MAXNH];   //[nh]
	Float_t         pc3dphi[MAXNH];   //[nh]
	Float_t         alpha[MAXNH];   //[nh]
	Float_t         phi[MAXNH];   //[nh]
	Float_t         zed[MAXNH];   //[nh]
	Short_t         n0[MAXNH];   //[nh]
	Float_t         tofdz[MAXNH];   //[nh]
	Float_t         tofdphi[MAXNH];   //[nh]
	Float_t         pc2dz[MAXNH];   //[nh]
	Float_t         pc2dphi[MAXNH];   //[nh]
	Float_t         ecore[MAXNH];   //[nh]
	Float_t         ttof[MAXNH];   //[nh]
	Float_t         pltof[MAXNH];   //[nh]
	Float_t         etof[MAXNH];   //[nh]
	Int_t           slat[MAXNH];   //[nh]
	Int_t           rh;
	Float_t         phir[MAXRP];   //[rh]
	Float_t         time[MAXRP];   //[rh]
	Float_t         qr0[MAXRP];   //[rh]
	Float_t         etar[MAXRP];   //[rh]
	Short_t         armr[MAXRP];   //[rh]
	Short_t         ring[MAXRP];   //[rh]
	Int_t           chid[MAXRP];   //[rh]
};


#endif