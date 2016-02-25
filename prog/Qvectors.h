#ifndef QVECTORS_H
#define QVECTORS_H

#include "Constants.h"
#include "TreeVar.h"

class Qvectors
{
public:
	Qvectors();
	void GetPsi(TreeVar *tr, int centbin, int zbin);
	Bool_t ReadCorrectionData(const char* filename);

	Float_t Psi[NHARM][NDET];

private:
	Float_t Qx[NHARM][NDET];
	Float_t Qy[NHARM][NDET];

	// arrays for reading correction data
	Float_t q0aver[NSECT][NMUL][NZPS];
	Float_t SumXmean[NHARM][NDET][NMUL][NZPS];
	Float_t SumXsigma[NHARM][NDET][NMUL][NZPS];
	Float_t SumYmean[NHARM][NDET][NMUL][NZPS];
	Float_t SumYsigma[NHARM][NDET][NMUL][NZPS];
	Float_t FlatCos[NHARM][NDET][NMUL][NZPS][NORD];
	Float_t FlatSin[NHARM][NDET][NMUL][NZPS][NORD];

	void CalcQvect(TreeVar *tr, int centbin, int zbin);	
	Float_t Flattening(const int ih, const int idet, const int imul, const int izps, const Float_t psi);
};

#endif