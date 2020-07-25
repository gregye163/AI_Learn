#ifndef __BGS_MOG_HPP__
#define __BGS_MOG_HPP__

#include <math.h>
#include "openai_io.hpp"
// 20200103
// #include "fastcv.hpp"
#include "bladecv.hpp"

using namespace fcv;
using namespace std;

struct gauss_element {
    float   mean;    
    float   variance;     
    float   weight;      
    float   u_diff2;
    float   priority; 
    int isMatched;               
};

struct mixtureOfGauss {
    gauss_element    **mog;
    uchar background;
    uchar foreground;
}; 

class bgsMog{
private:                                                             
	mixtureOfGauss* mOG;
    int         imageLen;

    int component;
    float var_init;
    float alpha;
    float de_init;
    float th_init;

    float myPow(float val);
    void updateMixtureOfGauss(uchar *p, mixtureOfGauss &m);
    uchar backgroundPixel(uchar *p, mixtureOfGauss &m);
    uchar foregroundPixel(uchar *p, mixtureOfGauss &m);


public:
	bgsMog(Mat &grayImage, int component_init = 5, float varianceInit = 36, float learningRate = 0.01, float deviationInit = 6.25, float thresholdInit = 0.2);
	~bgsMog();
	void updateMogImage(Mat &grayImage, Mat &background, Mat &foreground); 
};

#endif
