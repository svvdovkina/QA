#ifndef HISTOS_H
#define HISTOS_H

#include "Constants.h"

#include "TH1.h"

class Histos
{
public:
	TH1F *hpsiRP[NHARM][NDET][NMUL][NZPS];
	TH1F *hT0offset[NMUL];
	TH1F *hcosNphi[NHARM][NDET][NMUL];
	TH1F *hsinNphi[NHARM][NDET][NMUL];

	void BookHist();
	void WriteHist(int run);
};

#endif