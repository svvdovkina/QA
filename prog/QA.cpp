#include "Constants.h"

#include "TTree.h"
#include <iostream>
#include <fstream>

void QA(int runnum)
{
	gSystem->Load("Histos_cpp.so");
	gSystem->Load("TreeVar_cpp.so");
	gSystem->Load("Qvectors_cpp.so");
	gSystem->Load("Event_cpp.so");
	
	cout << runnum << endl;

	Histos hist;
	hist.BookHist();

	Qvectors qvect;
	char corfile[200];
	sprintf(corfile, "../%i/QvectCorrectionParametersRun%i", runnum, runnum);
	if (!qvect.ReadCorrectionData(corfile)) {cout<<"Error! Problem with correction files reading!\n"; return;};

	char runlist_file[200];
	sprintf(runlist_file, "../%i/runlist.list", runnum);

	ifstream ifile(runlist_file);
	char filename[200];
	int nfiles=0;
	while(ifile.getline(filename,200)) 
	{
		TreeVar *trv= new TreeVar;
		cout << nfiles<<": processing "<<filename <<endl;
		TTree *t = trv->InitTree(filename, "htree");
		if (!t) {cout<<"Error! Problem with tree initilizing!\n"; return;};

		Int_t nentries = Int_t(t->GetEntries());

		cout<<"n = "<<nentries<<endl;
		for (Int_t jentry=0; jentry < nentries;jentry++) 
		{    
			t->GetEntry(jentry);
			Event ev;
			//ev.SetZCentBin(trv);			
			//cout<<"zbin = "<<ev.GetZbin()<<", cent bin =  "<<ev.GetCentbin()<<endl;
			ev.EventAnalysis(&qvect, trv, &hist);
		}
		
		nfiles++;
	}
	hist.WriteHist(runnum);
	cout<<"done. "<<nfiles<<" files are processed"<<endl;
}