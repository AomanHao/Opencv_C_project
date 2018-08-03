#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/ml/ml.hpp>  
  
using namespace cv;  
  
int main()  
{  
    // Data for visual representation  
    int width = 512, height = 512;  
    Mat image = Mat::zeros(height, width, CV_8UC3);  
  
    // Set up training data  
    float labels[5] = {1.0, -1.0, -1.0, -1.0,1.0};  
    Mat labelsMat(5, 1, CV_32FC1, labels);  
  
  
    float trainingData[5][2] = { {501, 10}, {255, 10}, {501, 255}, {10, 501},{501,128} };  
    Mat trainingDataMat(5, 2, CV_32FC1, trainingData);  
  
    //����֧���������Ĳ���  
    CvSVMParams params;  
    params.svm_type    = CvSVM::C_SVC;//SVM���ͣ�ʹ��C֧��������  
    params.kernel_type = CvSVM::LINEAR;//�˺������ͣ�����  
    params.term_crit   = cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-6);//��ֹ׼�����������������ﵽ���ֵʱ��ֹ  
  
    //ѵ��SVM  
    //����һ��SVM���ʵ��  
    CvSVM SVM;  
    //ѵ��ģ�ͣ�����Ϊ���������ݡ���Ӧ��XX��XX��������ǰ�����ù���  
    SVM.train(trainingDataMat, labelsMat, Mat(), Mat(), params);  
      
    Vec3b green(0,255,0), blue (255,0,0);  
    //��ʾ�о���  
    for (int i = 0; i < image.rows; ++i)  
        for (int j = 0; j < image.cols; ++j)  
        {  
                        Mat sampleMat = (Mat_<float>(1,2) << i,j);  
            //predict������Ԥ��ģ�����Ϊ������������ֵ���ͣ����ֵΪture������һ��2�������򷵻��о�����ֵ�����򷵻����ǩ����  
            float response = SVM.predict(sampleMat);  
  
            if (response == 1)  
                image.at<Vec3b>(j, i)  = green;  
            else if (response == -1)   
                 image.at<Vec3b>(j, i)  = blue;  
        }  
  
    //����ѵ������  
    int thickness = -1;  
    int lineType = 8;  
    circle( image, Point(501,  10), 5, Scalar(  0,   0,   0), thickness, lineType);//��Բ  
    circle( image, Point(255,  10), 5, Scalar(255, 255, 255), thickness, lineType);  
    circle( image, Point(501, 255), 5, Scalar(255, 255, 255), thickness, lineType);  
    circle( image, Point( 10, 501), 5, Scalar(255, 255, 255), thickness, lineType);  
    circle(image, Point( 501, 128), 5, Scalar(0, 0, 0), thickness, lineType);  
  
    //��ʾ֧������  
    thickness = 2;  
    lineType  = 8;  
    //��ȡ֧�������ĸ���  
    int c     = SVM.get_support_vector_count();  
  
    for (int i = 0; i < c; ++i)  
    {  
        //��ȡ��i��֧������  
        const float* v = SVM.get_support_vector(i);  
        //֧�������õ��������㣬�û�ɫ���б�ע  
        circle( image,  Point( (int) v[0], (int) v[1]),   6,  Scalar(128, 128, 128), thickness, lineType);  
    }  
  
    imwrite("result.png", image);        // save the image   
  
    imshow("SVM Simple Example", image); // show it to the user  
    waitKey(0);  
  
} 