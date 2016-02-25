static Float_t  Spc3Sdz(Float_t pc3sdz, Float_t pt,Float_t cent, short Arm){


Float_t A0=1.0;
Float_t A1=0.0;
Float_t A2=0.0;
Float_t A3=0.0;

Float_t sigma=1.0;
Float_t sigma1=1.0;
if(pc3sdz> -9999&&pt>0.2){

 if(Arm==1){// West Arm selection

     A0=8.34769e-01+1.72770e-02/pt+3.26509e-03/(pt*pt);
     A1=-0.001000;
     A2=1.49994e-04-5.31641e-05/pt+2.68895e-06*(pt*pt);
     A3=6.12391e-05-4.06519e-05/pt+1.31138e-05/(pt*pt);
     sigma1=1+A3*cent*cent;


 }//end of West arm selection




if(Arm==0){// East Arm selection

 A0=8.56754e-01-1.63528e-02/pt+6.88540e-03/(pt*pt);
 A1=-0.001;
 A2=1.30685e-04-4.78606e-05/pt+1.73856e-07*(pt*pt);
 A3=5.32426e-05-4.16990e-05/pt+1.55370e-05/(pt*pt);
 sigma1=1.01+A3*cent*cent;




}//end of East Arm selection

}


sigma=A0+A1*cent+A2*cent*cent;

pc3sdz=pc3sdz/sigma;
pc3sdz=pc3sdz/sigma1;


return  pc3sdz;

}










static Float_t  Spc2Sdz(Float_t pc2sdz, Float_t pt,Float_t cent){


Float_t A0=1.0;
Float_t A1=0.0;
Float_t A2=0.0;
Float_t A3=0.0;


Float_t sigma1=1.0;
Float_t sigma=1.0;
if(pc2sdz> -9999&&pt>0.2){

   A0=7.89288e-01+4.28356e-02/pt+3.86622e-03/(pt*pt);
   A1=-0.001;
   A2=1.49335e-04-4.41699e-05/pt+1.21590e-06*(pt*pt);
   A3=4.93000e-05-1.99649e-05/pt+5.93902e-06/(pt*pt);

   sigma1=1.0+A3*cent*cent;



}


sigma=A0+A1*cent+A2*cent*cent;

pc2sdz=pc2sdz/sigma;
pc2sdz=pc2sdz/sigma1;


return  pc2sdz;

}








static Float_t  StofSdz(Float_t tofsdz, Float_t pt,Float_t cent, short Arm){


Float_t A0=1.0;
Float_t A1=0.0;
Float_t A2=0.0;
Float_t A3=0.0;



Float_t sigma=1.0;
Float_t sigma1=1.0;


if(tofsdz> -9999&&pt>0.2){

 if(Arm==1){// West Arm selection     

    A0=9.71588e-01-2.18261e-02/pt+1.06029e-02/(pt*pt);
    A1=-0.001;
    A2=3.20941e-05-8.78482e-06/pt-1.36563e-06*(pt*pt);
    A3=2.48712e-05+1.39139e-06/pt-3.88651e-07/(pt*pt);


sigma1=1.03+A3*cent*cent;


 }//end of West arm selection




if(Arm==0){// East Arm selection
   
    A0=9.33487e-01-5.33020e-03/pt+8.40904e-03/(pt*pt);
    A1=-0.001;
    A2=8.65017e-05-3.31645e-05/pt-1.01424e-06*(pt*pt);
    A3=1.96441e-05-9.60335e-06/pt+6.96463e-06/(pt*pt);


 
sigma1=1.032+A3*cent*cent;
}//end of East Arm selection

}


sigma=A0+A1*cent+A2*cent*cent;


tofsdz=tofsdz/sigma;
tofsdz=tofsdz/sigma1;


return  tofsdz;

}








