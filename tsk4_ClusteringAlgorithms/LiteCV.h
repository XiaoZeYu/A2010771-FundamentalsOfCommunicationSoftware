#ifndef __CV_H__
#define __CV_H__


//����ʹ�õĿ���̨��ӡ
#define DEBUG
#ifdef  DEBUG
#define LILOG(msg)  printf("%s: %s (%s,%d,%s)\n",LOG,msg, __FILE__, __LINE__ ,__FUNCTION__)
#define LOG   "LI_CV_H"
#else  
#define LILOG(msg) 
#endif // DEBUG


//������Ը��û�ʹ�õĺ���
#define LI_API

//�Ƿ�֧��JPEG��PNG
#define EN_JPEG 1
#define EN_PNG  1

#if EN_JPEG
#define USE_JPEG
#endif

#if EN_PNG
#define USE_PNG
#endif




#define false                0
#define true                 1  
#define LI_FALSE             false
#define LI_TRUE              true  
#define PI                   3.1415926 

#define GUI_RED       0x0000FF
#define GUI_BLUE      0xFF0000
#define GUI_GREEN     0x00FF00
#define RGB565_R      0xF800             //the separate RGB value
#define RGB565_G      0x07E0
#define RGB565_B      0x001F

#define LI_ARGB(a, r, g, b) ((((unsigned int)(a)) << 24) | (((unsigned int)(r)) << 16) | (((unsigned int)(g)) << 8) | ((unsigned int)(b)))
#define LI_ARGB_A(rgb) ((((unsigned int)(rgb)) >> 24) & 0xFF)
#define LI_RGB(r, g, b) ((0xFF << 24) | (((unsigned int)(r)) << 16) | (((unsigned int)(g)) << 8) | ((unsigned int)(b)))
#define LI_RGB_R(rgb) ((((unsigned int)(rgb)) >> 16) & 0xFF)
#define LI_RGB_G(rgb) ((((unsigned int)(rgb)) >> 8) & 0xFF)
#define LI_RGB_B(rgb) (((unsigned int)(rgb)) & 0xFF)
#define LI_RGB_32_to_16(rgb) (((((unsigned int)(rgb)) & 0xFF) >> 3) | ((((unsigned int)(rgb)) & 0xFC00) >> 5) | ((((unsigned int)(rgb)) & 0xF80000) >> 8))
#define LI_RGB_16_to_32(rgb) ((0xFF << 24) | ((((unsigned int)(rgb)) & 0x1F) << 3) | ((((unsigned int)(rgb)) & 0x7E0) << 5) | ((((unsigned int)(rgb)) & 0xF800) << 8))


#if (defined _WIN32) || (defined WIN32) || (defined _WIN64) || (defined WIN64)

typedef unsigned short       WORD;
typedef unsigned long        DWORD;
typedef long                 LONG;
typedef unsigned char        BYTE;
typedef unsigned             char uint8_t;
typedef unsigned short       int uint16_t;
typedef unsigned             int uint32_t;
typedef uint32_t             u32;
typedef uint16_t             u16;
typedef uint8_t              u8;
#endif

#if (defined __linux__) || (defined __APPLE__)

typedef unsigned             char uint8_t;
typedef unsigned short       int uint16_t;
typedef unsigned             int uint32_t;
typedef uint32_t             u32;
typedef uint16_t             u16;
typedef uint8_t              u8;
typedef u16                  WORD; //������16���ֽ�
typedef u32                  DWORD;//������32�ֽ�
typedef u32                  LONG; //�����long�̶�Ϊ32λ��ֱ����long�Ļ���64λ
typedef unsigned char        BYTE;
#endif

typedef enum tagPICTYPE
{
    BMP_1,
    BMP_8,
    BMP_565,
    BMP_888,
    BMP_32,
    JPEG,
    PNG
}PICTYPE;

enum {
    LI_BMP_1,
    LI_BMP_8,
    LI_BMP_565,
    LI_BMP_888,
    LI_BMP_32,
    LI_JPEG,
    LI_PNG,
};

/*
*ͼ������
*/
enum {
    LI_DEP_1U = -1,//��ֵͼ������ӦС�ڴ�������Ҳ����˵��һ��һ�ڴ洢8������

    LI_DEP_8U = 0, //�޷������α���,ÿ������8��

    LI_DEP_16U = 1,//��ӦBMP RGB565���͵�����

    LI_DEP_24U = 2,//��ӦBMP RGB888���͵�����

    LI_DEP_32U = 3,//4ͨ��ͼ��

    LI_DEP_64U = 4,//�ò���

};


//��ɫת������
enum
{
    LI_RGB2RGBA,
    LI_RGBA2RGB,
    LI_BGR2BGRA,
    LI_BGRA2BGR,
    LI_BGR2RGB,
    LI_RGB2BGR,
    LI_BGR2GRAY,
    LI_GRAY2BGR,
    LI_BGRA2GRAY,
    LI_RGB2GRAY,
    LI_BGR2YUYV,
    LI_YUYV2BGR,
    LI_BGRA2YUYV
};

//ͼƬ����ת��
enum
{
    LI_JPEG_2_BMP,        //ͼ������
    LI_PNG_2_BMP,
    LI_BMP_2_JPEG,
    LI_BMP_2_PNG,
    LI_BMP_888_2_LI_BMP_8,//�ҶȻ�
    LI_BMP_8_2_LI_BMP_888,
    LI_BMP_888_2_LI_BMP32,//����alpha
    LI_BMP_32_2_LI_BMP888

};


enum
{
    LI_FONT_12 = 12,
    LI_FONT_16 = 16,
    LI_FONT_24 = 24,
    LI_FONT_32 = 32
};

typedef void LiArr;

typedef struct tagLi_Mat
{
    LiArr* arr;//ͼ������ָ��
    LONG width;
    LONG height;
    BYTE datadepth;  //ͼ�����ݵ����
    LONG matsize;    //ͼ��Ĵ�Сwidth*height
    LONG arrsize;    //���ݵĴ�Сmatsize*depth
    BYTE Bitcount;   //һ�����ص��Ӧ��BIT��((DEP+1)*8��
}Li_Mat;





/**
 *Ŀǰ֧�ֵ�ͼƬ����
 *
 *      �������ϣ���������
        BMP_8,
        BMP_888,//BGR
        BMP_32, //BGRA
        JPEG ,  //�洢��ʽΪBGR
        PNG��   //�������еĴ洢��ʽΪBGRA

*/

typedef struct tag_LI_Image
{
    Li_Mat limat;
    PICTYPE pt;//ָ��ͼƬ����
    LONG width;
    LONG height;
    BYTE imgdepth;
    void* data;//ָ��Li_Mat�е�arr���������
    void* (*at)(struct tag_LI_Image* mat, LONG x, LONG y);//һ�����Է������ص��Ӧ��ͷָ��ĺ���ָ��

}Li_Image;

#endif  // !__CV_H__