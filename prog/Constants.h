#ifndef CONSTANTS_H
#define CONSTANTS_H

static const Float_t MYC = 29.9792;
static const Float_t M2EXP = 0.01948;
#define MAXRP 48
#define MAXNH 300

#define NMUL 14 // number of cent classes
#define NZPS 6 // number of bbc-Z vertex bins
#define NDET 9 // number of event plane detectors
#define NORD 8 // number of Fourier coefficients for flattering
#define NHARM 3 // number of flow harmonics: [0] - n=2 (v2), [1] - n=3, [2] - n=4
#define NSECT 48 // number of sectors of rxn detector 

static const int centmax = 70;
static const int centmin = 0;
static const int zmax = 30.;
static const int zmin = -30.;

static const double MYPI=3.141592654;

const char detname[NDET][50] = {"Rxn10 INN South", "Rxn11 OUT South", "Rxn12 INN+OUT South", "Rxn13 INN North", "Rxn14 OUT North", 
		"Rxn15 INN+OUT North", "Rxn16 INN S+N", "Rxn17 OUT S+N", "Rxn18 INN+OUT S+N"};

#endif