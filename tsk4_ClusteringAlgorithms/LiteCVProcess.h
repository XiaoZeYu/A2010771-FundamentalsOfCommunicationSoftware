#ifndef LI_IMG_PROC
#define LI_IMG_PROC

#include "LiteCV.h"
#include "LiteCVImage.h"

#define M_PI           3.14159265358979323846  /* pi */

typedef struct tagLi_Kernel
{
    double* arr;//ͼ������ָ��
    LONG width;
    LONG height;
    LONG arrsize;    //���ݵĴ�Сmatsize*depth
}Li_Kernel;

typedef struct tagLi_Line
{
    LONG start_x;
    LONG start_y;
    LONG end_x;
    LONG end_y;
    LONG thera;
    LONG r;
}LiLine;


typedef struct tag_LiPoint
{
    LONG x;
    LONG y;
    struct tag_LiPoint* nextpoint;
}LiPoint;

typedef struct tag_LiCircle
{
    LONG x;
    LONG y;
    LONG r;
}LiCircle;


enum Li_Smooth_Type
{
    Li_GAUSS,   //��˹�˲�
    Li_AVERAGE, //��ֵ�˲�
    Li_MEDIUM,  //��ֵ�˲�

};

//һ�ŻҶ�ֱ��ͼ���ݱ�
typedef struct tagLi_Hist
{
    float data[256];
}Li_Hist;



/**
 * @name: Li_Split
 * @msg:  ͼ��ɫ������
 * @param {Li_Image* img}
 * @return {Li_Image** ͼ��ָ���ָ��}
 */
LI_API
void Li_Split(Li_Image* img, Li_Image** out);

/**
 * @name: Li_Split
 * @msg:  ͼ��ɫ������
 * @param {Li_Image* img  ԭͼ��
 *         Li_Image**     ɫ�������Ժ��ͼ��}
 * @return {}
 */
LI_API
Li_Image* Li_Combine(Li_Image** out, BYTE depth);


/**
 * @name: Li_Threshold
 * @msg:  ͼ����ֵ��
 * @param {Li_Image* img ԭͼ��
 *         double threshold ͼ����ֵ0-255
 *         }
 * @return {Li_Image* ��ֵ����ĻҰ�ͼ��}
 */
LI_API
Li_Image* Li_Threshold(Li_Image* img, double threshold);


/**
 * @name: Li_Convolute
 * @msg: ����ͼ����
 * @param {Li_Image* img ���ͼ��
 *         Li_Kernel* kernal ����� }
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Convolute(Li_Image* img, Li_Kernel* kernal);


/**
 * @name: Li_GetKernel
 * @msg:  �õ�����˾���
 * @param {*}
 * @return {*}
 */
LI_API
Li_Kernel* Li_GetKernel(double* data, BYTE KernalKind);

/**
 * @name: Li_Smooth
 * @msg: ����ͼ���˲�
 * @param {Li_Image* img ԭͼ��
 *         BYTE smoothtype( Li_GAUSS,   //��˹�˲�
                            Li_AVERAGE, //��ֵ�˲�
                            Li_MEDIUM,  //��ֵ�˲�)}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Smooth(Li_Image* img, BYTE smoothtype);
/**
 * @name: Li_Sharp
 * @msg:  ͼ����
 * @param {Li_Image* img}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Sharp(Li_Image* img);

/**
 * @name: Li_Emboss
 * @msg:  ͼ����
 * @param {Li_Image* img}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Emboss(Li_Image* img);

/**
 * @name: Li_Salt_Noise
 * @msg:  ͼ��������
 * @param {Li_Image* img
 *         LONG num �������}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Salt_Noise(Li_Image* img, LONG num);

enum CannyType
{
    LI_CANNY_ROBERTS,
    LI_CANNY_SOBEL,
    LI_CANNY_PREWITT,
    LI_CANNY_MYDEFINE
};


/**
 * @name: Li_Double_Threshold
 * @msg:  ͼ��˫��ֵ��
 * @param {Li_Image* img ԭͼ��
 *         double min    С��ֵ
 *         double max    ����ֵ
 *         }
 * @return {Li_Image* ��ֵ����ĻҰ�ͼ��}
 */
LI_API
Li_Image* Li_Double_Threshold(Li_Image* img, double min, double max);

/**
 * @name: Li_Canny
 * @msg:  �ο����� https://blog.csdn.net/HUSTER_Gy/article/details/102942452?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522160498444419724838560446%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=160498444419724838560446&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_v2~rank_v28-11-102942452.first_rank_ecpm_v3_pc_rank_v2&utm_term=canny%E8%BE%B9%E7%BC%98%E6%A3%80%E6%B5%8B%E7%AE%97%E6%B3%95c%E5%AE%9E%E7%8E%B0&spm=1018.2118.3001.4449
 *        ͼ������
 * @param {Li_Image* img ԭͼ��
 *         BYTE CannyTypeѡ������
 *         BYTE min      �����ֵ
 *         BYTE max}     ��С��ֵ
 * @return {*}
 */
LI_API
Li_Image* Li_Canny(Li_Image* img, BYTE CannyType, BYTE min, BYTE max);

/**
 * @name: Li_Hough_Line
 * @msg: ����ֱ�߱任
 * @param {Li_Image* img ԭͼ��
 * 		   LiLine* lines ���ص�ֱ������ָ��
 * 		   LONG maxthrea ��������Ƕ�
 * 		   LONG maxr     ��������뾶}
 * @return {*}
 */
LI_API
void Li_Hough_Line(Li_Image* img, LiLine* lines, LONG maxthrea, LONG maxr);

/**
 * @name: Li_Hough_Circle_R
 * @msg:  �̶��뾶��Hough�任
 * @param {Li_Image* img  		ԭͼ��
 * 		   LiCircle* circles    ���ص�Բָ�루�������ڲ������ڴ棩
 * 		   LONG R				�任�뾶
 * 		   LONG* range}			Բ�ĵ÷�Χ
 * @return {*}
 */
LI_API
LONG Li_Hough_Circle_R(Li_Image* img, LiCircle* circles, LONG R, LONG* range);

/**
 * @name: Li_Hough_Circle
 * @msg:  ������Χ��Hough�任
 * @param {Li_Image* img  		ԭͼ��
 * 		   LiCircle* circles    ���ص�Բָ�루�������ڲ������ڴ棩
 * 		   LONG Rmin,LONG Rmax  ��С���뾶
 * 		   LONG* range}			Բ�ĵ÷�Χ
 * @return {*}
 */
LI_API
void Li_Hough_Circle(Li_Image* img, LiCircle* circles, LONG Rmin, LONG Rmax, LONG* range);


/**
 * @name: Li_Dilate
 * @msg: ͼ������(�ֲ���С)
 * @param {Li_Image* img}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Dilate(Li_Image* img);

/**
 * @name: Li_Erode
 * @msg: ͼ��ʴ(�ֲ���С)
 * @param {Li_Image* img}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Erode(Li_Image* img);

/**
 * @name: Li_Add
 * @msg: ͼ���������
 * @param {Li_Image* img1,Li_Image* img2}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Add(Li_Image* img1, Li_Image* img2);

/**
 * @name: Li_Minus
 * @msg: ͼ���������
 * @param {Li_Image* img1,Li_Image* img2}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Minus(Li_Image* img1, Li_Image* img2);

/**
 * @name: Li_Grandient
 * @msg: ��̬ѧ�ݶ�
 * @param {Li_Image* img}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Grandient(Li_Image* img);

/**
 * @name: Li_Mod_Open
 * @msg: ��̬ѧ������
 * @param {Li_Image* img}
 * @return {Li_Image* }
 */
LI_API
Li_Image* Li_Mod_Open(Li_Image* img);


/**
 * @name: Li_Mod_Close
 * @msg: ��̬ѧ������
 * @param {Li_Image* img}
 * @return {Li_Image* }
 */
LI_API
Li_Image* Li_Mod_Close(Li_Image* img);

/**
 * @name: Li_TopHat
 * @msg: ͼ��ñ����
 * @param {Li_Image* img}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_TopHat(Li_Image* img);

/**
 * @name: Li_BlackHat
 * @msg: ͼ���ñ����
 * @param {Li_Image* img}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_BlackHat(Li_Image* img);

/**
 * @name: Li_Visual_Hist
 * @msg: ֱ��ͼת��Ϊͼ��
 * @param {Li_Hist* hist}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Visual_Hist(Li_Hist* hist);

/**
 * @name: Li_Get_Hist
 * @msg: ����ֱ��ͼ
 * @param {Li_Image* img ͼ��}
 * @return {Li_Hist* ֱ��ͼ����}
 */
LI_API
Li_Hist* Li_Get_Hist(Li_Image* img);

/**
 * @name: Li_Print_Hist
 * @msg: ��ӡֱ��ͼ
 * @param {Li_Hist* hist}
 * @return {*}
 */
LI_API
void Li_Print_Hist(Li_Hist* hist);

/**
 * @name: Li_Normalize_Hist
 * @msg: ֱ��ͼ���⻯
 * @param {Li_Image* img}
 * @return {*}
 */
LI_API
Li_Image* Li_Normalize_Hist(Li_Image* img);
#endif // !LI_IMG_PROC