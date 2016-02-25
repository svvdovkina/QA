static Float_t new_alpha (Float_t alpha, Float_t phi, short Arm, int run)
{
	Float_t xp = sin(phi);
	Float_t yp = cos(phi); 
	Float_t Xoff=0;
	Float_t Yoff=0;
	//run selection 
    if (run < 311500)
	{
		if (Arm == 0)
		{
			Xoff=0.06;
			Yoff=0.360;
        }
		// West Arm Selection
        if (Arm == 1)
		{
			Xoff=-0.040;
			Yoff=0.390;
         }
	}

	if (run >= 311500)
	{
		if (Arm == 0)
		{
			Xoff=0.06;
			Yoff=0.405;
        }
		// West Arm Selection
		if (Arm == 1)
		{
			Xoff=0.040;
			Yoff=0.425;
		}
	}
	Float_t  AlphaOffset = (Xoff*xp / 220. + Yoff*yp / 220.);
	return (alpha - AlphaOffset);
}


