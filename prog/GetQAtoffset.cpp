#define NMUL 14
void GetQAtoffset()
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
		sprintf(datafile[Nrun], "../%s/T0offset.txt", runnum);
		Nrun++;
	}
	frun.close();
	// ------

	// **** reading t0offset
	Float_t t0[NMUL][400];
	Float_t t0sig[NMUL][400];
	Float_t run[400];

	for (int ir = 0; ir < Nrun; ir++)
	{
		ifstream f(datafile[ir]);
		if (!f) {cout<<"can't open "<<datafile[ir]<<" file\n"; return;}
		for(int ic=0; ic<NMUL; ic++)
		{
			int cent;
			f>>run[ir]>>cent>>t0[ic][ir]>>t0sig[ic][ir];
			if (cent != ic) {cout<<"incorrect "<<datafile[ir]<<" file data reading!! ic = "<<ic<<" cent = "<<cent<<endl; return;}
		}

	}
	// ****

	// make graph of t0 vs runnum for all the centralities and write them to the root file
	TFile *outfile = new TFile("QAt0offset.root","recreate");
	TGraph *gr[NMUL];
				
	for (int ic = 0; ic < NMUL; ic++)
	{
		gr[ic] = new TGraphErrors(Nrun, run, t0[ic], 0, t0sig[ic]); 
		gr[ic]->Write();
	}
	outfile->Close();
}