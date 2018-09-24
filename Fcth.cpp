#include "Fcth.h"
CFcth::CFcth():m_meanRed(0),m_meanGreen(0),m_meanBlue(0),
                   m_10bin(NULL),m_24bin(NULL),m_192bin(NULL)
{
	m_10bin = new double[d10];
	m_24bin = new double[d24];
	m_192bin = new double[d192];
}

CFcth::~CFcth()
{
	delete []m_10bin;m_10bin = NULL;
	delete []m_24bin;m_24bin = NULL;
	delete []m_192bin;m_192bin = NULL;
}
void CFcth::extract(IplImage *image)
{
	extract(image,1);
	//for(int i=0;i<d192;i++)
	//{
	//	if(i%16==0)cout<<endl;
	//	cout<<m_192bin[i]<<" ";
	//}
	//cout<<endl;
}
void CFcth::extract(IplImage *image,int mode)
{

	int height = image->height;
	int width = image->width;
	int *gray = new int[height*width];
	m_meanRed = m_meanGreen = m_meanBlue = 0;
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
		{
			CvScalar s = cvGet2D(image,i,j); 
			int r = s.val[2];
			int g = s.val[1];
			int b = s.val[0];
			m_meanRed+=r;m_meanGreen+=g;m_meanBlue+=b;
			gray[i*width+j] = 
		static_cast<int>(
	    0.114 * static_cast<double>(b) + 0.587 * static_cast<double>(g) + 0.299 * static_cast<double>(r));
		}
    m_meanRed = m_meanRed/(height*width);
	m_meanGreen = m_meanGreen/(height*width);
	m_meanBlue = m_meanBlue/(height*width);
	int HSV[3];
	RGB2HSV(m_meanRed,m_meanGreen,m_meanBlue,HSV,3);
	//cout<<"HSV:: ";cout<<HSV[0]<<" "<<HSV[1]<<" "<<HSV[2]<<endl;
	//=================================================================
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{
			m_block[i][j]=0;
		}
	int blockCount = (height*width)/16; 
	int temp = (int)sqrt((double)blockCount);
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
		{
			m_block[i/temp][j/temp]+=gray[i*width+j];
		}
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{
			m_block[i][j]=m_block[i][j]/blockCount;
		}
	delete []gray;
	WaveletMatrix();
	//=====================================================================
	Extract10Bin(HSV[0],HSV[1],HSV[2]);
	Extract24Bin(HSV[0],HSV[1],HSV[2]);
	Extract192Bin(m_WaveletMatrix[0],m_WaveletMatrix[1],m_WaveletMatrix[2]);
    //=====================================================================
	double total = 0;
	for(int i=0;i<d192;i++)
	{
		total+=m_192bin[i];
	}
	for(int i=0;i<d192;i++)
	{
		m_192bin[i]=m_192bin[i]/total;
	}
	Quant();

}
void CFcth::RGB2HSV(int r,int g,int b,int* hsv,int n)
{
	int HSV_H = 0;
	int HSV_S = 0;
	int HSV_V = 0;
	double Max,Min;
	if(r>g)
	{
		if(r>b)Max = r;
		else Max = b;
		if(g<b)Min = g;
		else Min = b;
	}
	else 
	{
		if(g>b)Max = g;
		else Max = b;
		if(r<b)Min = r;
		else Min = b;
	}
	HSV_V = static_cast<int>(Max);
	HSV_S = 0;
	if(Max!=0)
		HSV_S = (int)(255-255*(Min/Max));
	if(Max!=Min)
	{
		int IntMax = static_cast<int>(Max);

		if (IntMax == r && g >= b) 
			HSV_H = static_cast<int>(60 * (g - b) / (Max - Min));
		else if (IntMax == r && g < b)
			HSV_H = static_cast<int>(359 + 60 * (g - b) / (Max - Min));
		else if (IntMax == g)
			HSV_H = static_cast<int>(119 + 60 * (b - r) / (Max - Min));
		else if (IntMax == b)
			HSV_H = static_cast<int>(239 + 60 * (r - g) / (Max - Min));

	}
	else HSV_H = 0;
	hsv[0] = HSV_H;
	hsv[1] = HSV_S;
	hsv[2] = HSV_V;

}
void CFcth::Quant()
{
	double QuantTable[8] =
	{130.0887781556944, 9317.31301788632, 22434.355689233365, 43120.548602722061, 
	83168.640165905046, 101430.52589975641, 174840.65838706805, 224480.41479670047};

	double QuantTable2[8] =
	{130.0887781556944, 9317.31301788632, 22434.355689233365, 43120.548602722061,
	83168.640165905046, 151430.52589975641, 174840.65838706805, 224480.41479670047};

	double QuantTable3[8] =
	{239.769468748322, 17321.704312335689, 39113.643180734696, 69333.512093874378,
	79122.46400035513, 90980.3325940354, 161795.93301552488, 184729.98648386425};

	double QuantTable4[8] =
	{239.769468748322, 17321.704312335689, 39113.643180734696, 69333.512093874378, 
	79122.46400035513, 90980.3325940354, 161795.93301552488, 184729.98648386425};

	double QuantTable5[8] =
	{239.769468748322, 17321.704312335689, 39113.643180734696, 69333.512093874378, 
	79122.46400035513, 90980.3325940354, 161795.93301552488, 184729.98648386425};

	double QuantTable6[8] =
	{239.769468748322, 17321.704312335689, 39113.643180734696, 69333.512093874378, 
	79122.46400035513, 90980.3325940354, 161795.93301552488, 184729.98648386425};

	double QuantTable7[8] =
	{180.19686541079636, 23730.024499150866, 41457.152912541605, 53918.55437576842,
	69122.46400035513, 81980.3325940354, 91795.93301552488, 124729.98648386425};

	double QuantTable8[8] =
	{180.19686541079636, 23730.024499150866, 41457.152912541605, 53918.55437576842,
	69122.46400035513, 81980.3325940354, 91795.93301552488, 124729.98648386425};

	double Edge_HistogramElement[d192];
	double ElementsDistance[8];
    double Max = 1;
	for (int i = 0; i < 24; i++) 
	{
		Edge_HistogramElement[i] = 0;
		for (int j = 0; j < 8; j++) 
		{
			ElementsDistance[j] = abs(m_192bin[i] - QuantTable[j] / 1000000);
		}
		Max = 1;
		for (int j = 0; j < 8; j++) 
		{
			if (ElementsDistance[j] < Max)
			{
				Max = ElementsDistance[j];
				Edge_HistogramElement[i] = j;
			}
		}
	}
	for (int i = 24; i < 48; i++) 
	{
		Edge_HistogramElement[i] = 0;
		for (int j = 0; j < 8; j++) 
		{
			ElementsDistance[j] = abs(m_192bin[i] - QuantTable2[j] / 1000000);
		}
		Max = 1;
		for (int j = 0; j < 8; j++)
		{
			if (ElementsDistance[j] < Max) 
			{
				Max = ElementsDistance[j];
				Edge_HistogramElement[i] = j;
			}
		}
	}
	for (int i = 48; i < 72; i++) 
	{
		Edge_HistogramElement[i] = 0;
		for (int j = 0; j < 8; j++) 
		{
			ElementsDistance[j] = abs(m_192bin[i] - QuantTable3[j] / 1000000);
		}
		Max = 1;
		for (int j = 0; j < 8; j++) 
		{
			if (ElementsDistance[j] < Max) 
			{
				Max = ElementsDistance[j];
				Edge_HistogramElement[i] = j;
			}
		}
	}
	for (int i = 72; i < 96; i++) 
	{
		Edge_HistogramElement[i] = 0;
		for (int j = 0; j < 8; j++) 
		{
			ElementsDistance[j] = abs(m_192bin[i] - QuantTable4[j] / 1000000);
		}
		Max = 1;
		for (int j = 0; j < 8; j++) 
		{
			if (ElementsDistance[j] < Max) 
			{
				Max = ElementsDistance[j];
				Edge_HistogramElement[i] = j;
			}
		}
	}


	for (int i = 96; i < 120; i++) 
	{
		Edge_HistogramElement[i] = 0;
		for (int j = 0; j < 8; j++) 
		{
			ElementsDistance[j] = abs(m_192bin[i] - QuantTable5[j] / 1000000);
		}
		Max = 1;
		for (int j = 0; j < 8; j++) 
		{
			if (ElementsDistance[j] < Max) 
			{
				Max = ElementsDistance[j];
				Edge_HistogramElement[i] = j;
			}
		}
	}
	for (int i = 120; i < 144; i++) 
	{
		Edge_HistogramElement[i] = 0;
		for (int j = 0; j < 8; j++) 
		{
			ElementsDistance[j] = abs(m_192bin[i] - QuantTable6[j] / 1000000);
		}
		Max = 1;
		for (int j = 0; j < 8; j++) 
		{
			if (ElementsDistance[j] < Max) 
			{
				Max = ElementsDistance[j];
				Edge_HistogramElement[i] = j;
			}
		}
	}
	for (int i = 144; i < 168; i++) 
	{
		Edge_HistogramElement[i] = 0;
		for (int j = 0; j < 8; j++) 
		{
			ElementsDistance[j] = abs(m_192bin[i] - QuantTable7[j] / 1000000);
		}
		Max = 1;
		for (int j = 0; j < 8; j++) 
		{
			if (ElementsDistance[j] < Max)
			{
				Max = ElementsDistance[j];
				Edge_HistogramElement[i] = j;
			}
		}
	}
	for (int i = 168; i < 192; i++) 
	{
		Edge_HistogramElement[i] = 0;
		for (int j = 0; j < 8; j++) 
		{
			ElementsDistance[j] = abs(m_192bin[i] - QuantTable8[j] / 1000000);
		}
		Max = 1;
		for (int j = 0; j < 8; j++) 
		{
			if (ElementsDistance[j] < Max) 
			{
				Max = ElementsDistance[j];
				Edge_HistogramElement[i] = j;
			}
		}
	}
	for(int i=0;i<d192;i++)
	{
		m_192bin[i] = Edge_HistogramElement[i];
	}


}
void CFcth::Extract10Bin(double h,double s,double v)
{
	double HueMembershipValues[32] = 
	{0, 0, 5, 10,
	5, 10, 35, 50,
	35, 50, 70, 85,
	70, 85, 150, 165,
	150, 165, 195, 205,
	195, 205, 265, 280,
	265, 280, 315, 330,
	315, 330, 360, 360}; 
	double SaturationMembershipValues[8] = 
	{0, 0, 10, 75,
	10, 75, 255, 255};

	double ValueMembershipValues[12] = 
	{0, 0, 10, 75,
	10, 75, 180, 220,
	180, 220, 255, 255};
	double Hue[8],Saturation[2],Value[3];
	int Fuzzy10BinRulesDefinition[48][4] = 
	{
		{0, 0, 0, 2},
		{0, 1, 0, 2},
		{0, 0, 2, 0},
		{0, 0, 1, 1},
		{1, 0, 0, 2},
		{1, 1, 0, 2},
		{1, 0, 2, 0},
		{1, 0, 1, 1},
		{2, 0, 0, 2},
		{2, 1, 0, 2},
		{2, 0, 2, 0},
		{2, 0, 1, 1},
		{3, 0, 0, 2},
		{3, 1, 0, 2},
		{3, 0, 2, 0},
		{3, 0, 1, 1},
		{4, 0, 0, 2},
		{4, 1, 0, 2},
		{4, 0, 2, 0},
		{4, 0, 1, 1},
		{5, 0, 0, 2},
		{5, 1, 0, 2},
		{5, 0, 2, 0},
		{5, 0, 1, 1},
		{6, 0, 0, 2},
		{6, 1, 0, 2},
		{6, 0, 2, 0},
		{6, 0, 1, 1},
		{7, 0, 0, 2},
		{7, 1, 0, 2},
		{7, 0, 2, 0},
		{7, 0, 1, 1},
		{0, 1, 1, 3},
		{0, 1, 2, 3},
		{1, 1, 1, 4},
		{1, 1, 2, 4},
		{2, 1, 1, 5},
		{2, 1, 2, 5},
		{3, 1, 1, 6},
		{3, 1, 2, 6},
		{4, 1, 1, 7},
		{4, 1, 2, 7},
		{5, 1, 1, 8},
		{5, 1, 2, 8},
		{6, 1, 1, 9},
		{6, 1, 2, 9},
		{7, 1, 1, 3},
		{7, 1, 2, 3}
	};  
	for(int i=0;i<d10;i++)
		m_10bin[i] = 0;
	int temp=0;
	for(int i=0;i<sizeof(HueMembershipValues)/sizeof(double);i+=4)
	{
		Hue[temp] = 0;
		if(h>=HueMembershipValues[i+1]&&h<=HueMembershipValues[i+2])
			Hue[temp] = 1;
		if(h>=HueMembershipValues[i]&&h<HueMembershipValues[i+1])
			Hue[temp] =(h-HueMembershipValues[i])/(HueMembershipValues[i+1]-HueMembershipValues[i]);
		if(h>HueMembershipValues[i+2]&&h<=HueMembershipValues[i+3])
			Hue[temp] =(h-HueMembershipValues[i+2])/(HueMembershipValues[i+2]-HueMembershipValues[i+3])+1;
		temp++; 
	}

	temp=0;
	for(int i=0;i<sizeof(SaturationMembershipValues)/sizeof(double);i+=4)
	{
		Saturation[temp]=0;
		if(s>=SaturationMembershipValues[i+1]&&s<=SaturationMembershipValues[i+2])
			Saturation[temp]=1;
		if(s>=SaturationMembershipValues[i]&&s<SaturationMembershipValues[i+1])
			Saturation[temp] = (s-SaturationMembershipValues[i])/(SaturationMembershipValues[i+1]-SaturationMembershipValues[i]);
		if(s>SaturationMembershipValues[i+2]&&s<=HueMembershipValues[i+3])
			Saturation[temp] = (s-SaturationMembershipValues[i+2])/(SaturationMembershipValues[i+2]-SaturationMembershipValues[i+3])+1;
		temp++;
	}


	temp=0;
	for(int i=0;i<sizeof(ValueMembershipValues)/sizeof(double);i+=4)
	{
		Value[temp]=0;
		if(v>=ValueMembershipValues[i+1]&&v<=ValueMembershipValues[i+2])
			Value[temp]=1;
		if(v>=ValueMembershipValues[i]&&v<ValueMembershipValues[i+1])
			Value[temp] = (v-ValueMembershipValues[i])/(ValueMembershipValues[i+1]-ValueMembershipValues[i]);
		if(v>ValueMembershipValues[i+2]&&v<=ValueMembershipValues[i+3])
			Value[temp] = (v-ValueMembershipValues[i+2])/(ValueMembershipValues[i+2]-ValueMembershipValues[i+3])+1;
		temp++;
	}	
	for(int i=0;i<48;i++)
	{
		if(Hue[Fuzzy10BinRulesDefinition[i][0]]>0&&
			Saturation[Fuzzy10BinRulesDefinition[i][1]]>0&&
			Value[Fuzzy10BinRulesDefinition[i][2]]>0)
		{
			int r = Fuzzy10BinRulesDefinition[i][3];
			m_10bin[r] += MIN3(Hue[Fuzzy10BinRulesDefinition[i][0]],
				Saturation[Fuzzy10BinRulesDefinition[i][1]],
				Value[Fuzzy10BinRulesDefinition[i][2]]);
		}
	}
#ifdef PRINT
	for(int i=0;i<8;i++)
		cout<<Hue[i]<<" ";
	cout<<endl;
	for(int i=0;i<2;i++)
		cout<<Saturation[i]<<" ";
	cout<<endl;
	for(int i=0;i<3;i++)
		cout<<Value[i]<<" ";
	cout<<endl;
	for(int i=0;i<d10;i++)
		cout<<m_10bin[i]<<" ";
	cout<<endl;
#endif

}
void CFcth::Extract24Bin(double h,double s,double v)
{
	double SaturationMembershipValues[8] = 
	     {0, 0, 68, 188,
		68, 188, 255, 255};
    double ValueMembershipValues[8] = 
	    {0, 0, 68, 188,
		68, 188, 255, 255};
	int Fuzzy24BinRulesDefinition[4][3] = 
	{
		{1, 1, 1},
		{0, 0, 2},
		{0, 1, 0},
		{1, 0, 2}
	};
	double Saturation[2],Value[2];
	for(int i=0;i<d24;i++)
		m_24bin[i] = 0;
	int temp=0;
	for(int i=0;i<sizeof(SaturationMembershipValues)/sizeof(double);i+=4)
	{
		Saturation[temp]=0;
        if(s>=SaturationMembershipValues[i+1]&&s<=SaturationMembershipValues[i+2])
			Saturation[temp]=1;
		if(s>=SaturationMembershipValues[i]&&s<SaturationMembershipValues[i+1])
			Saturation[temp] = (s-SaturationMembershipValues[i])/(SaturationMembershipValues[i+1]-SaturationMembershipValues[i]);
		if(s>SaturationMembershipValues[i+2]&&s<=SaturationMembershipValues[i+3])
			Saturation[temp] = (s-SaturationMembershipValues[i+2])/(SaturationMembershipValues[i+2]-SaturationMembershipValues[i+3])+1;
		temp++;
	}
	temp=0;
	for(int i=0;i<sizeof(ValueMembershipValues)/sizeof(double);i+=4)
	{
		Value[temp]=0;
		if(v>=ValueMembershipValues[i+1]&&v<=ValueMembershipValues[i+2])
			Value[temp]=1;
		if(v>=ValueMembershipValues[i]&&v<ValueMembershipValues[i+1])
			Value[temp] = (v-ValueMembershipValues[i])/(ValueMembershipValues[i+1]-ValueMembershipValues[i]);
		if(v>ValueMembershipValues[i+2]&&v<=ValueMembershipValues[i+3])
			Value[temp] = (v-ValueMembershipValues[i+2])/(ValueMembershipValues[i+2]-ValueMembershipValues[i+3])+1;
		temp++;
	}
	double tt = 0;
	for(int i=3;i<10;i++)
		tt+=m_10bin[i];
	double resultTable[3];
	resultTable[0]=resultTable[1]=resultTable[2]=0;
	if(tt>0)
	{
		for(int i=0;i<4;i++)
		{
			if(Saturation[Fuzzy24BinRulesDefinition[i][0]]>0&&
				Value[Fuzzy24BinRulesDefinition[i][1]]>0)
			{
				int r = Fuzzy24BinRulesDefinition[i][2];
				resultTable[r]+=MIN(Saturation[Fuzzy24BinRulesDefinition[i][0]],
					Value[Fuzzy24BinRulesDefinition[i][1]]);
			}
		}
        
	}
	for(int i=0;i<3;i++)
		m_24bin[i]=m_10bin[i];
	for(int i=3;i<10;i++)
	{
		m_24bin[(i-2)*3] += m_10bin[i]*resultTable[0];
		m_24bin[(i-2)*3+1] += m_10bin[i]*resultTable[1];
		m_24bin[(i-2)*3+2] += m_10bin[i]*resultTable[2];
	}
#ifdef PRINT
	for(int i=0;i<2;i++)
		cout<<Saturation[i]<<" ";
	cout<<endl;
	for(int i=0;i<2;i++)
		cout<<Value[i]<<" ";
	cout<<endl;
	for(int i=0;i<3;i++)
		cout<<resultTable[i]<<" ";
	cout<<endl;
	for(int i=0;i<d24;i++)
		cout<<m_24bin[i]<<" ";
#endif

}
void CFcth::Extract192Bin(double F1,double F2,double F3)
{
	double HorizontalMembershipValues[8] = {0, 0, 20, 90, 20, 90, 255, 255};
	double VerticalMembershipValues[8] = {0, 0, 20, 90, 20, 90, 255, 255};
    double EnergyMembershipValues[8] = {0, 0, 20, 80, 20, 80, 255, 255};
	int RulesDefinition[8][4] = {
		{0, 0, 0, 0},
		{0, 0, 1, 1},
		{0, 1, 0, 2},
		{0, 1, 1, 3},
		{1, 0, 0, 4},
		{1, 0, 1, 5},
		{1, 1, 0, 6},
		{1, 1, 1, 7}};
	double Horizontal[2];
	double Vertical[2];
	double Energy[2];
	double resultTable[8];
	for(int i=0;i<d192;i++)
		m_192bin[i] = 0;
	for(int i=0;i<8;i++)
		resultTable[i]=0;
	int temp=0;
	for(int i=0;i<sizeof(HorizontalMembershipValues)/sizeof(double);i+=4)
	{
		Horizontal[temp]=0;
		if(F1>=HorizontalMembershipValues[i+1]&&F1<=HorizontalMembershipValues[i+2])
			Horizontal[temp]=1;
		if(F1>=HorizontalMembershipValues[i]&&F1<HorizontalMembershipValues[i+1])
			Horizontal[temp]=(F1-HorizontalMembershipValues[i])/(HorizontalMembershipValues[i+1]-HorizontalMembershipValues[i]);
		if(F1>HorizontalMembershipValues[i+2]&&F1<=HorizontalMembershipValues[i+3])
			Horizontal[temp]=(F1-HorizontalMembershipValues[i+2])/(HorizontalMembershipValues[i+2]-HorizontalMembershipValues[i+3])+1;
		temp++;
	}
	temp=0;
	for(int i=0;i<sizeof(VerticalMembershipValues)/sizeof(double);i+=4)
	{
		Vertical[temp]=0;
		if(F2>=VerticalMembershipValues[i+1]&&F2<=HorizontalMembershipValues[i+2])
			Vertical[temp]=1;
		if(F2>=VerticalMembershipValues[i]&&F2<VerticalMembershipValues[i+1])
			Vertical[temp]=(F2-VerticalMembershipValues[i])/(VerticalMembershipValues[i+1]-VerticalMembershipValues[i]);
		if(F2>VerticalMembershipValues[i+2]&&F2<=VerticalMembershipValues[i+3])
			Vertical[temp]=(F2-VerticalMembershipValues[i+2])/(VerticalMembershipValues[i+2]-VerticalMembershipValues[i+3])+1;
		temp++;
	}
	temp=0;
	for(int i=0;i<sizeof(EnergyMembershipValues)/sizeof(double);i+=4)
	{
		Energy[temp]=0;
		if(F3>=EnergyMembershipValues[i+1]&&F3<=EnergyMembershipValues[i+2])
			Energy[temp]=1;
		if(F3>=EnergyMembershipValues[i]&&F3<EnergyMembershipValues[i+1])
			Energy[temp]=(F3-EnergyMembershipValues[i])/(EnergyMembershipValues[i+1]-EnergyMembershipValues[i]);
		if(F3>EnergyMembershipValues[i+2]&&F3<=EnergyMembershipValues[i+3])
			Energy[temp]=(F3-EnergyMembershipValues[i+2])/(EnergyMembershipValues[i+2]-EnergyMembershipValues[i+3])+1;
		temp++;
	}
	for(int i=0;i<8;i++)
	{
		if(Horizontal[RulesDefinition[i][0]]>0&&Vertical[RulesDefinition[i][1]]>0&&Energy[RulesDefinition[i][2]]>0)
		{
			int r = RulesDefinition[i][3];
			resultTable[r]+=MIN3(Horizontal[RulesDefinition[i][0]],
				            Vertical[RulesDefinition[i][1]],
				             Energy[RulesDefinition[i][2]]);
		}
	}
	for(int i=0;i<8;i++)
		if(resultTable[i]>0)
		{
			for(int j=0;j<d24;j++)
			{
				if(m_24bin[j]>0)
				{
					m_192bin[i*d24+j]+=resultTable[i]*m_24bin[j];
				}
			}
		}
#ifdef PRINT
	for(int i=0;i<8;i++)
	{
		cout<<resultTable[i]<<" ";
	}
	cout<<endl;
	for(int i=0;i<d192;i++)
	{
		if(i%8==0)cout<<endl;
		cout<<m_192bin[i];
	}   
#endif
}
void CFcth::WaveletMatrix()
{
	double resultMatrix[4][4];
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{
			if(i<2&&j<2)
			{
				resultMatrix[i][j] = 
					(m_block[2*i][2*j]+m_block[2*i+1][2*j]+m_block[2*i][2*j+1]+m_block[2*i+1][2*j+1])/4;
				resultMatrix[i+2][j] = 
					abs(-m_block[2*i][2*j]-m_block[2*i+1][2*j]+m_block[2*i][2*j+1]+m_block[2*i+1][2*j+1]);
				resultMatrix[i][j+2] = 
					abs(m_block[2*i][2*j]-m_block[2*i+1][2*j]+m_block[2*i][2*j+1]-m_block[2*i+1][2*j+1]);
				resultMatrix[i+2][j+2] = 
					abs(-m_block[2*i][2*j]+m_block[2*i+1][2*j]+m_block[2*i][2*j+1]-m_block[2*i+1][2*j+1]);
			}
		}
	double temp1 = 0;
	double temp2 = 0;
	double temp3 = 0;
	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
		{
			temp1 += 0.25*resultMatrix[2+i][j]*resultMatrix[2+i][j];
			temp2 += 0.25*resultMatrix[i][j+2]*resultMatrix[i][j+2];
			temp3 += 0.25*resultMatrix[i+2][j+2]*resultMatrix[i+2][j+2];
		}
	m_WaveletMatrix[0] = sqrt(temp1);
	m_WaveletMatrix[1] = sqrt(temp2);
	m_WaveletMatrix[2] = sqrt(temp3);
	//cout<<m_WaveletMatrix[0]<<" "<<m_WaveletMatrix[1]<<" "<<m_WaveletMatrix[2]<<endl;

}
string CFcth::getStringRepresentation()
{
	return " ";
}
