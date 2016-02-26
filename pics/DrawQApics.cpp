#include <iostream>
#include <fstream>

#include "TROOT.h"
// Root Data Types
#include <TFile.h>
#include "TH1.h"
#include "TGraph.h"
// Root Graphics
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TFrame.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TStyle.h" 
#include "TLine.h"

#include "TMath.h" 

using namespace std;

#define NMUL 14
const Float_t cent_bins[NMUL+1] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70};

void DrawQAt0offset(char *myFile, char *printfile);

TStyle * makeplotstyle()
{
  
  TStyle *mystyle = new TStyle("PlottingInStyle", "Style for Summary Plots");
  mystyle->SetCanvasColor(10);
  mystyle->SetOptTitle(0);
  //mystyle->SetPadLeftMargin(0.13);
  mystyle->SetPadBottomMargin(0.13);
  mystyle->SetPadTickX(1);
  mystyle->SetPadTickY(1);
  mystyle->SetAxisColor(1, "XY");;
  mystyle->SetLabelColor(1, "XY");
  mystyle->SetTickLength(0.04, "XY");
  mystyle->SetTitleXSize(0.049);
  mystyle->SetTitleYSize(0.052);
  mystyle->SetTitleOffset(1.0, "XY");
  mystyle->SetNdivisions(508, "X");
  mystyle->SetNdivisions(508, "Y");
  mystyle->SetTitleFont(62, "X");
   mystyle->SetTitleFont(62, "Y");
  mystyle->SetLabelFont(62, "XY"); // label is a numbers on the axis
  mystyle->SetLabelOffset(0.005, "XY");
  mystyle->SetLabelSize(0.04, "XY");

  return mystyle;
}

void DrawQApics()
{
	char energy[] = "62GeV";
	char eddition[] = "QA";

	char myFile[200];
	sprintf(myFile, "C:/Users/svvd/Desktop/MROOT/NNcollis/auau%s/%s/pics/t0/QAt0offset.root", energy, eddition);

	char printfile[200];
	sprintf(printfile, "C:/Users/svvd/Desktop/MROOT/NNcollis/auau%s/%s/pics/t0",energy, eddition);

	DrawQAt0offset(myFile, printfile);
}

void DrawQAt0offset(char *myFile, char *printfile)
{
	TStyle *tsty = makeplotstyle();
	tsty->cd();

	TFile f(myFile);
	if (!f.Open(myFile)) {cout<<"can't open "<<myFile<<" file\n"; return;}
	TGraph *gr[NMUL];
	char name[20];
	char title[20];
	char picname[20];

	float maxX = 0.4;
	float minX = -0.4;

	for (int ic = 0; ic < NMUL; ic++)
	{		
		sprintf(name, "Graph_cent%i", ic);
		gr[ic] = (TGraph*)f.Get(name);

		gr[ic]->SetMarkerColor(kRed);
		gr[ic]->SetLineColor(kRed);
		gr[ic]->SetMarkerStyle(24);

		TCanvas* c1= new TCanvas("c1");
		sprintf(title, "Cent: %1.f-%1.f%%", cent_bins[ic],cent_bins[ic+1]);
		sprintf(picname, "t0offset_c%i", ic);

		TLatex *tex = new TLatex(311000,0.35/*textposY[ih][ic]*/, "Au+Au #sqrt{S_{NN}} = 62.4 GeV");
		tex->SetTextSize( 0.05);
		tex->SetTextColor(1);

		TLatex *tex2 = new TLatex(311000,0.35/*textposY[ih][ic]*/-0.05, title);
		tex2->SetTextSize( 0.05);
		tex2->SetTextColor(1);

		gr[ic]->Draw("AP[]");//"A3" for error filled region

		tex->Draw("same");
		tex2->Draw("same");

		gr[ic]->GetXaxis()->SetTitle("Run number"); 
		char titleY[20];
		sprintf(titleY, "t0_{offset}, ns");
		gr[ic]->GetYaxis()->SetTitle(titleY);

		gr[ic]->GetYaxis()->SetTitleOffset(0.8);

		gr[ic]->GetYaxis()->CenterTitle(true);
		gr[ic]->GetXaxis()->CenterTitle(true);
			
		//gr[ic]->GetXaxis()->SetLimits(minX[ih], maxX[ih]);
		gr[ic]->SetMaximum(maxX);
		gr[ic]->SetMinimum(minX);
		
		char printpicname[300];
		sprintf(printpicname, "%s/%s.png", printfile, picname);
		c1->Print(printpicname); 
		delete c1;
	}
}