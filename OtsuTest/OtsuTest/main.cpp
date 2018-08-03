#include "stdio.h"
#include "cv.h"
#include "highgui.h"
#include "Math.h"

int Otsu(IplImage* src);

int main()
{
    IplImage* img = cvLoadImage("1.jpg",0); //��ȡ�Ҷ�ͼ��img
    IplImage* dst = cvCreateImage(cvGetSize(img), 8, 1);
    int threshold = Otsu(img); //���ô����������ֵ
    printf("otsu threshold = %d\n", threshold);
    cvThreshold(img, dst, threshold, 255, CV_THRESH_BINARY); //��otsu����ֵ��ֵ��

    cvNamedWindow( "img", 1 );
    cvNamedWindow( "dst", 1 );
    cvShowImage("img", img);
    cvShowImage("dst", dst);


    cvWaitKey(-1);

    cvReleaseImage(&img);
    cvReleaseImage(&dst);

    cvDestroyWindow( "img" );
    cvDestroyWindow( "dst" );

    return 0;
}

int Otsu(IplImage* src)  
{  
    int height=src->height;  
    int width=src->width;      

    //histogram  
    float histogram[256] = {0};  
    for(int i=0; i < height; i++)
    {  
        unsigned char* p=(unsigned char*)src->imageData + src->widthStep * i;  
        for(int j = 0; j < width; j++) 
        {  
            histogram[*p++]++;  
        }  
    }  

    //normalize histogram & average pixel value 
    int size = height * width;  
    float u =0;
    for(int i = 0; i < 256; i++)
    {  
        histogram[i] = histogram[i] / size;  
        u += i * histogram[i];  //����ͼ���ƽ���Ҷ�
    }  

    int threshold;    
    float maxVariance=0;  
    float w0 = 0, avgValue  = 0;
    for(int i = 0; i < 256; i++) 
    {  
        w0 += histogram[i];  //���赱ǰ�Ҷ�iΪ��ֵ, 0~i �Ҷ�������ռ����ͼ��ı�����ǰ������
        avgValue  += i * histogram[i]; //avgValue/w0 = u0

        float t = avgValue/w0 - u;  //t=u0-u
        float variance = t * t * w0 /(1 - w0);  
        if(variance > maxVariance) 
        {  
            maxVariance = variance;  
            threshold = i;  
        }  
    }  

    return threshold;  
}