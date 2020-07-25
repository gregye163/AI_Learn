#include "bgs_mog.hpp"

bgsMog::bgsMog(Mat &grayImage, int component_init, float varianceInit, float learningRate, float deviationInit, float thresholdInit)
{
    component = component_init;
    var_init = varianceInit;
    alpha = learningRate;
    de_init = deviationInit;		
    th_init = thresholdInit;

    imageLen = grayImage.cols * grayImage.rows;
    mOG = new mixtureOfGauss[imageLen];

    for (int c = 0; c<imageLen; c++){
	        mOG[c].mog = new gauss_element*[component];
            for(int indexGuass = 0; indexGuass < component; indexGuass++){
                mOG[c].mog[indexGuass] = new gauss_element;
            	mOG[c].mog[indexGuass]->mean = rand() /(float)(RAND_MAX) * 255;
            	mOG[c].mog[indexGuass]->variance = var_init;
            	mOG[c].mog[indexGuass]->weight = (float)1 / component;
            }
        
    }
}

bgsMog::~bgsMog()
{
	delete[] mOG;
}

float bgsMog::myPow(float val)
{
    return val * val;
}

void bgsMog::updateMixtureOfGauss(uchar *p, mixtureOfGauss &m)
{    
	int indexGuass;

    int matchComponent = 0;
    float sum_weight = 0;
    //if match then update gauss
    for (indexGuass = 0; indexGuass < component; indexGuass++){
        m.mog[indexGuass]->isMatched = 0;
        m.mog[indexGuass]->u_diff2 = myPow(abs( *p - m.mog[indexGuass]->mean));
        if(m.mog[indexGuass]->u_diff2 <= de_init * m.mog[indexGuass]->variance){
            m.mog[indexGuass]->isMatched = 1;
            matchComponent ++;

            m.mog[indexGuass]->weight= (1 - alpha) * m.mog[indexGuass]->weight + alpha;
            float beta = alpha * m.mog[indexGuass]->weight;
            m.mog[indexGuass]->mean = (1 - beta) * m.mog[indexGuass]->mean + beta * (*p);
            m.mog[indexGuass]->variance =  m.mog[indexGuass]->variance * (1 - beta) 
                +  myPow( *p - m.mog[indexGuass]->mean) * beta  ;

        }
        m.mog[indexGuass]->priority = myPow(m.mog[indexGuass]->weight);
        sum_weight += m.mog[indexGuass]->weight;
    }

    //if no gauss matched, replace the min priority gauss
    float MinPriority = 1.0;
    int indexMinPriority;
    if(0 == matchComponent){
        // find priority min
        for (indexGuass = 0; indexGuass < component; indexGuass++){
            if (m.mog[indexGuass]->priority < MinPriority){
                MinPriority = m.mog[indexGuass]->priority;
                indexMinPriority = indexGuass;
            }
        }
   
        //create new component to replace the min priority guass
        sum_weight = sum_weight + 1 / component - m.mog[indexMinPriority]->weight; 
        m.mog[indexMinPriority]->weight = 1 / component;
        m.mog[indexMinPriority]->mean = *p;
        m.mog[indexMinPriority]->variance = var_init;
    }

    //weight normalization
    for (indexGuass = 0; indexGuass < component; indexGuass++){
        m.mog[indexGuass]->weight = m.mog[indexGuass]->weight / sum_weight;
    }
}

uchar bgsMog::backgroundPixel(uchar *p, mixtureOfGauss &m)
{
	m.background = 0;
	for (int indexGuass = 0; indexGuass < component; indexGuass++){
	    m.background +=  m.mog[indexGuass]->mean * m.mog[indexGuass]->weight;
	}

	return m.background;
}

uchar bgsMog::foregroundPixel(uchar *p, mixtureOfGauss &m)
{
    for (int indexGuass = 0; indexGuass < component; indexGuass++){
        if ( m.mog[indexGuass]->weight > th_init){
            if(m.mog[indexGuass]->u_diff2 <= de_init * m.mog[indexGuass]->variance){
                m.foreground = 0;
                break;
            }else{
                m.foreground = 255;
            }
        }
    }
    return m.foreground;
}


void bgsMog::updateMogImage(Mat &grayImage, Mat &background, Mat &foreground)
{
    uchar *pImage = (uchar *)(grayImage.ptr(0));
    uchar *pBackground = (uchar *)(background.ptr(0));
    uchar *pForeground = (uchar *)(foreground.ptr(0));
    for (int c = 0; c<imageLen; c++){
        bgsMog::updateMixtureOfGauss(pImage, mOG[c]);
        *pBackground++ = bgsMog::backgroundPixel(pImage, mOG[c]);
        *pForeground++ = bgsMog::foregroundPixel(pImage, mOG[c]);
        pImage += 1;
    }
}

