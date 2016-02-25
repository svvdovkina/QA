#include "Qvectors.h"

#include <iostream>
#include <fstream>
#include "TMath.h"

using namespace std;

Qvectors::Qvectors()
{
	for (int ih = 0; ih < NHARM; ih++)
	{
		for(int id=0;id<NDET;id++)
		{
			Qx[ih][id] = 0.;
			Qy[ih][id] = 0.;
			Psi[ih][id] = 0.;
		}
	}
}

void Qvectors::GetPsi(TreeVar *tr, int centbin, int zbin)
{
	//cout<<"inside GetPsi\n";
	CalcQvect(tr, centbin, zbin);

	//cout<<"before correction psi[0][0] = "<<TMath::ATan2(Qy[0][0], Qx[0][0]) / (0+2.0);;

	for (int ih = 0; ih < NHARM; ih++)
	{
		for(int id=0;id<NDET;id++)
		{
			if(SumXsigma[ih][id][centbin][zbin] == 0 || SumYsigma[ih][id][centbin][zbin] == 0){cout << " sumX/Y sigma == 0. Check the parameters." << endl; return;}

			if (Qx[ih][id]==0 || Qy[ih][id]==0) { return;}
			Float_t qxc = (Qx[ih][id] - SumXmean[ih][id][centbin][zbin]) / SumXsigma[ih][id][centbin][zbin];
			Float_t qyc = (Qy[ih][id] - SumYmean[ih][id][centbin][zbin]) / SumYsigma[ih][id][centbin][zbin];
			Psi[ih][id] = TMath::ATan2(qyc, qxc) / (ih+2.0);
			//cout<<"psi = "<<Psi[ih][id]*180./MYPI<<" qx = "<<Qx[ih][id]<< " qy = "<<Qy[ih][id]<<endl;

			Float_t psi0 = Psi[ih][id];
			psi0 = Flattening(ih, id, centbin, zbin, psi0);
			Psi[ih][id] = psi0;
		}
	}
}

void Qvectors::CalcQvect(TreeVar *tr, int centbin, int zbin)
{	
	Int_t           rh; rh = tr -> rh;
	Float_t         phir[MAXRP]; //for (int irh = 0; irh < rh; irh++) {phir[irh] = tr -> phir[irh] ;} 
	Float_t         qr0[MAXRP]; //for (int irh = 0; irh < rh; irh++) { qr0[irh]  = tr -> qr0[irh]; }
	Short_t         armr[MAXRP]; //for (int irh = 0; irh < rh; irh++) { armr[irh] =  tr -> armr[irh]; }   
	Short_t         ring[MAXRP]; //for (int irh = 0; irh < rh; irh++) {ring[irh] = tr -> ring[irh]; }
	Int_t           chid[MAXRP]; //for (int irh = 0; irh < rh; irh++) {chid[irh] = tr -> chid[irh]; }
	
	Float_t w = 0.;
	Float_t simulatedW = -999.;
	Float_t simulatedPhi = -999.;

	for (int ih = 0; ih < NHARM; ih++)
	{
		for(int id=0;id<NDET;id++)
		{
			Qx[ih][id] = 0.;
			Qy[ih][id] = 0.;
			Psi[ih][id] = 0.;
		}
	}

	//loop through the sectors of RXN detector
	for (int ihit = 0; ihit <rh; ihit++)
	{
		phir[ihit] = tr -> phir[ihit]; 
		qr0[ihit]  = tr -> qr0[ihit]; 
		armr[ihit] =  tr -> armr[ihit];    
		ring[ihit] = tr -> ring[ihit]; 
		chid[ihit] = tr -> chid[ihit]; 
		//cout<<"phir["<<ihit<<"] = "<<phir[ihit]<<endl;

		if (q0aver[chid[ihit]][centbin][zbin] == 0 ) { w = qr0[ihit];}
		else {w = qr0[ihit]/q0aver[chid[ihit]][centbin][zbin];}
		
		//if (pass == 0) {w = qr0[ihit];}

		/* Since one sector of rxn is dead (armr = 0, ring = 0, chid = 11), to correct this, the sector will be filled 
		with halfs of it's two adjacent sectors. 
		And phi  ( since rxn has 12 sector with width = 2pi/12=pi/6) should be shifted by +-pi/6
		Dead sector has chid = 11, adjacent1 chid = 0 (+pi/6), adjacent2 chid = 10 (-pi/6)*/
		if (chid[ihit] == 0) {simulatedW = w/2.; simulatedPhi = phir[ihit] + MYPI/6.;}
		if (chid[ihit] == 10) {simulatedW = w/2.; simulatedPhi = phir[ihit] - MYPI/6.;}
		

		/**
		Let armr = 0 means South, = 1 - North,
		ring = 0 - inn, = 1 - out 
		Doesn't matter even if they are fliped 
		{"Rxn10 INN South", "Rxn11 OUT South", "Rxn12 INN+OUT South", "Rxn13 INN North", "Rxn14 OUT North", 
		"Rxn15 INN+OUT North", "Rxn16 INN S+N", "Rxn17 OUT S+N", "Rxn18 INN+OUT S+N"};
		**/
		for (int ih = 0; ih < NHARM; ih++)
		{

			if (armr[ihit] == 0 && ring[ihit] == 0){ /*cout<<"w = "<<w<<endl;*/ Qx[ih][0] += w*TMath::Cos((ih+2.)*phir[ihit]); Qy[ih][0] += w*TMath::Sin((ih+2.)*phir[ihit]); } // South INN
			if (armr[ihit] == 0 && ring[ihit] == 1){ Qx[ih][1] += w*TMath::Cos((ih+2.)*phir[ihit]); Qy[ih][1] += w*TMath::Sin((ih+2.)*phir[ihit]); } // South OUT
			if (armr[ihit] == 0					  ){ Qx[ih][2] += w*TMath::Cos((ih+2.)*phir[ihit]); Qy[ih][2] += w*TMath::Sin((ih+2.)*phir[ihit]); } // South INN+OUT
			if (armr[ihit] == 1 && ring[ihit] == 0){ Qx[ih][3] += w*TMath::Cos((ih+2.)*phir[ihit]); Qy[ih][3] += w*TMath::Sin((ih+2.)*phir[ihit]); } // North INN
			if (armr[ihit] == 1 && ring[ihit] == 1){ Qx[ih][4] += w*TMath::Cos((ih+2.)*phir[ihit]); Qy[ih][4] += w*TMath::Sin((ih+2.)*phir[ihit]); } // North OUT
			if (armr[ihit] == 1					  ){ Qx[ih][5] += w*TMath::Cos((ih+2.)*phir[ihit]); Qy[ih][5] += w*TMath::Sin((ih+2.)*phir[ihit]); } // North INN+OUT
			if (				   ring[ihit] == 0){ Qx[ih][6] += w*TMath::Cos((ih+2.)*phir[ihit]); Qy[ih][6] += w*TMath::Sin((ih+2.)*phir[ihit]); } // S+N INN
			if (				   ring[ihit] == 1){ Qx[ih][7] += w*TMath::Cos((ih+2.)*phir[ihit]); Qy[ih][7] += w*TMath::Sin((ih+2.)*phir[ihit]); } // S+N OUT
			if ( 1					  			  ){ Qx[ih][8] += w*TMath::Cos((ih+2.)*phir[ihit]); Qy[ih][8] += w*TMath::Sin((ih+2.)*phir[ihit]); } // S+N INN+OUT
			
			
			if (chid[ihit] == 0 || chid[ihit] == 10) // filling dead sector if signal presents in adjasent
			{
				Qx[ih][0] += simulatedW*TMath::Cos((ih+2.)*simulatedPhi); Qy[ih][0] += simulatedW*TMath::Sin((ih+2.)*simulatedPhi);
				Qx[ih][2] += simulatedW*TMath::Cos((ih+2.)*simulatedPhi); Qy[ih][2] += simulatedW*TMath::Sin((ih+2.)*simulatedPhi);
				Qx[ih][6] += simulatedW*TMath::Cos((ih+2.)*simulatedPhi); Qy[ih][6] += simulatedW*TMath::Sin((ih+2.)*simulatedPhi);
				Qx[ih][8] += simulatedW*TMath::Cos((ih+2.)*simulatedPhi); Qy[ih][8] += simulatedW*TMath::Sin((ih+2.)*simulatedPhi);
			}
		} // harm loop
	} // hits loop

	
}


Bool_t Qvectors::ReadCorrectionData(const char* filename)
{
	char file[200];

	//  read gain correction	
	sprintf(file, "%sPass0", filename);
	ifstream file1(file);
	if (!file1) { cout << " Could not open input file " << file1 << endl; return false; }
	cout << "read gain correction parameters" << endl;

	for(int im=0;im<NMUL;im++)
	{
		for(int iz=0;iz<NZPS;iz++)
		{
			for(int is=0; is<NSECT; is++)
			{
				file1 >> q0aver[is][im][iz];
			}
		}
	}
	file1.close();

	// recentering correction
	sprintf(file, "%sPass1", filename);
	ifstream file2(file);
	if (!file2) { cout << " Could not open input file " << file2 << endl; return false; }
	cout << "read QX/Y mean and sigma" << endl;

	for(int ih=0; ih<NHARM; ih++)
	{
		for(int id=0;id<NDET;id++)
		{
			for(int iz=0;iz<NZPS;iz++)
			{
				for(int im=0;im<NMUL;im++)
				{
					file2 >> SumXmean[ih][id][im][iz] >> SumXsigma[ih][id][im][iz] >> SumYmean[ih][id][im][iz] >> SumYsigma[ih][id][im][iz];
				}
			}
		}
	}
	file2.close();
  

	// flattening correction
	sprintf(file, "%sPass2", filename);

	ifstream file3(file);
	if (!file3) { cout << " Could not open input file " << file3 << endl; return false; }

	cout << "read Flattening" << endl;
	for(int ih=0; ih<NHARM; ih++)
	{
		for(int id=0;id<NDET;id++)
		{
			for(int im=0;im<NMUL;im++)
			{
				for(int iz=0;iz<NZPS;iz++)
				{
					for(int io=0;io<NORD;io++)
					{
						file3 >> FlatCos[ih][id][im][iz][io] >> FlatSin[ih][id][im][iz][io];
					}
				}
			}
		}
	}
	file3.close();	

	return true;
}

Float_t Qvectors::Flattening(const int ih, const int idet, const int imul, const int izps, const Float_t psi)
{
	Float_t deltaPsi = 0.0;
	Float_t psi0 = psi* (ih + 2.0); // -pi < psi0 < pi

	for (int io = 0;io < NORD; io++) 
	{
		Float_t averageCos = FlatCos[ih][idet][imul][izps][io];
		Float_t averageSin = FlatSin[ih][idet][imul][izps][io];

		Float_t cosPsi = cos( (io + 1.0) * psi0 );
		Float_t sinPsi = sin( (io + 1.0) * psi0 );
		deltaPsi += ( -averageSin * cosPsi + averageCos * sinPsi) * 2.0 / (io + 1.0);
	}
	//if (1/*abs(psi0 + deltaPsi - MYPI) <0.01*/ ) {cout<<"psi+dpsi = "<<psi0 + deltaPsi<<"psi = "<<psi<<" dpsi = "<<deltaPsi<<endl;}
	return TMath::ATan2(sin(psi0 + deltaPsi), cos(psi0 + deltaPsi)) / (2.0+ih); // -pi/n < psi < pi/n (n=2+ih)
}

