#ifndef EVENT_H
#define EVENT_H

#include "TTree.h"

#include "Constants.h"
#include "Qvectors.h"
#include "TreeVar.h"
#include "Histos.h"

enum eCuts {ptcut, n0cut, zedDCcut, Eoverpcut, matchPC3, matchTOF, tofdistance};

class Event
{
	//int itr;
	Float_t pt;
	Float_t mom; // momentum
	Float_t newphi;
	Float_t newalpha;
	int zbin; 
	int centbin;

	void SetPtMomPhi(TreeVar *tr, int itr);
	Bool_t GlobalCuts(Float_t cent, Float_t zvert);

public:
	unsigned GetZbin() {return zbin;};
	unsigned GetCentbin() {return centbin;};
	void SetZCentBin(TreeVar *tr);
	//Float_t GetPhi() {return newphi;}; // get phi after alpha correction
	//Float_t GetPt() {return pt;}; // get pt after alpha correction
	
	void EventAnalysis(Qvectors *qv, TreeVar *tr, Histos *h);
	//Bool_t ApplyCuts(eCuts *usedCuts, int Ncuts);
};

#endif