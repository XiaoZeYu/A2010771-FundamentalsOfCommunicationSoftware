#define _CRT_SECURE_NO_WARNINGS 1
#include "LiteCV.h"
#include "LiteCVImage.h"
#include "stdlib.h"
#include "string.h"

#undef  LOG
#define LOG  "LI_CV_CORE"



 /**
  * @name: li_malloc_arr
  * @msg: ΪLiArr�����ڴ�
  * @param {size}�����ڴ�Ĵ�С
  * @return {LiArr}��������
  */
LI_API
LiArr* li_malloc_arr(LONG size)
{
    return (LiArr*)malloc((size_t)size);
}

/**
 * @name: li_free_arr
 * @msg: ΪLiArr�ͷ��ڴ�
 * @param {void}
 * @return {void}
 */
void li_free_arr(LiArr* arr)
{
    free((void*)arr);
}

/**
 * @name: Li_Destroy_Mat
 * @msg: ΪLiMat�ͷ��ڴ�
 * @param {void}
 * @return {void}
 */
void Li_Destroy_Mat(Li_Mat* mat)
{
    li_free_arr(mat->arr);
    free((void*)mat);
}

/**
 * @name: li_bgr_at
 * @msg:
 * @param {Li_Image* mat
 *         LONG x ָ�������к�
 *         LONG y �����к�}
 * @return {*}
 */
LiArr* li_bgr_at(Li_Image* mat, LONG x, LONG y)
{
    BYTE* ptr;
    if (x < mat->width && y < mat->height) {
        ptr = ((BYTE*)mat->data) + mat->width * (1 + mat->imgdepth) * y + (1 + mat->imgdepth) * x;
        return ptr;
    }
    else {
        LILOG("BEYOND THE MAT");
        return NULL;
    }
}

LiArr* li_gray_at(Li_Image* mat, LONG x, LONG y)
{
    BYTE* ptr;
    if (x < mat->width && y < mat->height) {
        ptr = (BYTE*)mat->data + mat->width * 1 * y + 1 * x;
        return ptr;
    }
    else {
        //LILOG("BEYOND THE MAT");
        return NULL;
    }
}

LiArr* li_rgba_at(Li_Image* mat, LONG x, LONG y)
{
    BYTE* ptr;
    if (x < mat->width && y < mat->height) {
        ptr = (BYTE*)mat->data + mat->width * 4 * y + 4 * x;
        return ptr;
    }
    else {
        LILOG("BEYOND THE MAT");
        return NULL;
    }
}

/**
 * @name: Li_Create_Mat
 * @msg:
 * @param       LONG width,LONG height, �ߺͿ�
                BYTE depth,             ͼ�����
 * @return {Li_Mat}
 */
Li_Mat* Li_Create_Mat(
    LiArr* data,
    LONG width, LONG height,
    BYTE depth)
{
    Li_Mat* li_mat = (Li_Mat*)malloc(sizeof(Li_Mat));
    li_mat->datadepth = depth;
    li_mat->height = height;
    li_mat->width = width;
    li_mat->matsize = width * height;

    if (depth != LI_DEP_1U) {
        li_mat->Bitcount = (depth + 1) * 8;
        li_mat->arrsize = li_mat->matsize * (depth + 1);
    }
    else {
        li_mat->Bitcount = 1;
        li_mat->arrsize = li_mat->matsize * 1 / 8;//���ڶ�ֵ��ͼ��һ��BYTE����8�����ص�
    }

    li_mat->arr = li_malloc_arr(li_mat->arrsize);
    memcpy(li_mat->arr, data, li_mat->arrsize);

    return li_mat;
}


/**
 * @name: ptr_li_image_create
 * @msg:  ����Li_image  ����ָ��
 * @param
 *      LiArr* data,(�Ѿ���ʼ����������ָ��)
 *      LONG width,LONG height,
 *      BYTE depth,PICTYPE pth��ͼƬ���ͣ�
 * @return {Li_Image}һ��ͼƬ
 */
Li_Image* ptr_li_image_create(
    LiArr* dt,
    LONG width, LONG height,
    BYTE depth, PICTYPE pth)
{
    Li_Image* img = (Li_Image*)malloc(sizeof(Li_Image));
    Li_Mat* limt = NULL;
    img->pt = pth;
    img->data = dt;
    img->width = width;
    img->height = height;
    img->imgdepth = depth;

    switch (pth)
    {
    case LI_BMP_888:
        limt = Li_Create_Mat(dt, width, height, depth);
        memcpy(&img->limat, limt, sizeof(Li_Mat));//����ָ��һ�������ˣ�����li_mat->arr�����ͷ�
        img->at = li_bgr_at;
        break;

    case LI_JPEG:
        limt = Li_Create_Mat(dt, width, height, depth);
        memcpy(&img->limat, limt, sizeof(Li_Mat));//����ָ��һ�������ˣ�����li_mat->arr�����ͷ�
        img->at = li_bgr_at;
        break;

    case LI_BMP_8:
        limt = Li_Create_Mat(dt, width, height, depth);
        memcpy(&img->limat, limt, sizeof(Li_Mat));//����ָ��һ�������ˣ�����li_mat->arr�����ͷ�
        img->at = li_gray_at;
        break;

    case LI_BMP_32:
        limt = Li_Create_Mat(dt, width, height, depth);
        memcpy(&img->limat, limt, sizeof(Li_Mat));//����ָ��һ�������ˣ�����li_mat->arr�����ͷ�
        img->at = li_rgba_at;
        break;

    case LI_PNG:
        limt = Li_Create_Mat(dt, width, height, depth);
        memcpy(&img->limat, limt, sizeof(Li_Mat));//����ָ��һ�������ˣ�����li_mat->arr�����ͷ�
        img->at = li_rgba_at;
        break;

    default:
        break;
    }
    return img;
}


/**
 * @name: ptr_li_image_destroy
 * @msg:  ����Li_image  ����ָ��
 * @param {Li_Image* }һ��ͼƬָ��
 *
 * @return void
 */
void ptr_li_image_destroy(Li_Image* img)
{
    li_free_arr(img->limat.arr);
    free(img);
}

//��ȡĬ�ϵ�BMP�ļ�ͷ
BITMAPFILEHEADER get_default_file_head(Li_Mat m)
{
    LONG DataSizePerLine = (m.width * m.Bitcount / 8 + 3) / 4 * 4;
    BITMAPFILEHEADER bf;
    if (m.datadepth != LI_DEP_8U && m.datadepth != LI_DEP_1U)
        bf.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) - 2;
    else if (m.datadepth == LI_DEP_8U)
        bf.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 1024 - 2;
    else if (m.datadepth == LI_DEP_1U)
        bf.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 8 - 2;

    bf.bfSize = DataSizePerLine * m.height + bf.bfOffBits;
    bf.bfType = 19778;//"BM"
    bf.bfReserved1 = 0;
    bf.bfReserved2 = 0;
    return bf;
}

//��ȡĬ�ϵ�BMP��Ϣ
BITMAPINFOHEADER get_default_info_head(Li_Mat m)
{
    LONG DataSizePerLine = (m.width * m.Bitcount / 8 + 3) / 4 * 4;
    BITMAPINFOHEADER bi;
    bi.biBitCount = m.Bitcount;
    bi.biSize = 40;
    bi.biWidth = m.width;
    bi.biHeight = m.height;
    bi.biPlanes = 1;
    bi.biClrImportant = 0;
    bi.biClrUsed = 0;//Ĭ��ȫ����
    if (m.Bitcount != 32) {
        bi.biXPelsPerMeter = 3780;//Ĭ�ϴ�С
        bi.biYPelsPerMeter = 3780;
    }
    else
    {
        bi.biXPelsPerMeter = 0;//Ĭ�ϴ�С
        bi.biYPelsPerMeter = 0;
    }
    bi.biSizeImage = DataSizePerLine * bi.biHeight;
    bi.biCompression = 0;//Ĭ�ϲ�ѹ��
    return bi;
}

/**
 * @name: Li_CV_Version
 * @msg: ��ӡ������Ϣ
 * @param {*}
 * @return {*}
 */
LI_API
void Li_CV_Version()
{
    char data[200] = "LiteCV version:V 2.0";
    printf("%s\n", data);
}

/**
 * @name:Li_Wait_Q
 * @msg: �ȴ�һ��q
 * @param {*}
 * @return {*}
 */
LI_API
void Li_Wait_Q()
{
    char b = 0;
    while (b != 'q') {
        scanf("%c", &b);
    }
}

/**
 * @name: Li_Save_Image
 * @msg: �û��ӿں�������������һ��ͼƬ
 * @param
 *        BYTE *filepath        ͼƬ·��
 *        Li_Image* img         LitecvͼƬ����
 * @return 0 (right) or -1(something wrong)
 */

LI_API
BYTE Li_Save_Image(BYTE* filepath, Li_Image* img)
{
    if (img == NULL)
    {
        LILOG("A NULL IMG");
        return -1;
    }
    BYTE sta;
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    switch (img->pt)
    {
    case LI_BMP_888:
        bf = get_default_file_head(img->limat);
        bi = get_default_info_head(img->limat);
        sta = Write_bmp(filepath, img->data, &bf, &bi, img->pt);
        break;
    case LI_BMP_32:
        bf = get_default_file_head(img->limat);
        bi = get_default_info_head(img->limat);
        sta = Write_bmp(filepath, img->data, &bf, &bi, img->pt);
        break;
    case LI_BMP_8:
        bf = get_default_file_head(img->limat);
        bi = get_default_info_head(img->limat);
        sta = Write_bmp(filepath, img->data, &bf, &bi, img->pt);
        break;
    default:
        break;
    }
    return sta;
}


/**
 * @name: Li_Load_Image
 * @msg: �û��ӿں�����������ȡһ��ͼƬ
 * @param
 *        BYTE *filepath        ͼƬ·��
 *        PICTYPE pt            ͼƬ����
 * @return 0 (right) or -1(something wrong)
 */
LI_API
Li_Image* Li_Load_Image(BYTE* filepath, PICTYPE pt)
{
    BYTE* data;
    LONG width, height;
    int depth;
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    Li_Image* img = NULL;
    switch (pt)
    {
    case LI_BMP_888:
        LILOG("BMP888");
        data = Read_bmp(filepath, &bf, &bi);
        width = bi.biWidth;
        height = bi.biHeight;
        depth = LI_DEP_24U;
        img = ptr_li_image_create(data, width, height, depth, pt);
        break;

    case LI_BMP_32:
        LILOG("BMP32");
        data = Read_bmp(filepath, &bf, &bi);
        width = bi.biWidth;
        height = bi.biHeight;
        depth = LI_DEP_32U;
        img = ptr_li_image_create(data, width, height, depth, pt);
        break;

    case LI_BMP_8:
        LILOG("BMP8");
        data = Read_bmp(filepath, &bf, &bi);
        width = bi.biWidth;
        height = bi.biHeight;
        depth = LI_DEP_8U;
        img = ptr_li_image_create(data, width, height, depth, pt);
        break;

    case LI_BMP_565:
        LILOG("BMP16");
        data = Read_bmp(filepath, &bf, &bi);
        width = bi.biWidth;
        height = bi.biHeight;
        depth = LI_DEP_16U;
        img = ptr_li_image_create(data, width, height, depth, pt);
        break;
    default:
        break;
    }

    return img;
}


/**
 * @name: Li_Destroy_Image
 * @msg: �û��ӿں���������ɾ��һ��ͼƬ
 * @param
          Li_Image * img
 * @return 0 (right) or -1(something wrong)
 */
LI_API
void Li_Destroy_Image(Li_Image* img)
{
    ptr_li_image_destroy(img);
}

/**
 * @name: Li_Create_Imgae
 * @msg: �û��ӿں�������������һ��ͼƬ
 * @param
        LONG width  ͼƬ���
        LONG height ͼƬ�߶�
        BYTE depth  ��ɫ���
        PICTYPE pth ͼƬ����
 * @return Li_Image*  һ��ͼƬ
 */
LI_API
Li_Image* Li_Create_Image(
    LONG width, LONG height,
    BYTE depth, PICTYPE pth)
{
    LiArr* data = li_malloc_arr(width * height * (depth + 1));
    memset(data, 0xFF, width * height * (depth + 1));
    return ptr_li_image_create(data, width, height, depth, pth);
}


/**
 * @name: Li_Copy_Imgae
 * @msg: �û��ӿں�������������һ��ͼƬ
 * @param
        LONG width  ͼƬ���
        LONG height ͼƬ�߶�
        BYTE depth  ��ɫ���
        PICTYPE pth ͼƬ����
 * @return Li_Image*  һ��ͼƬ
 */
LI_API
Li_Image* Li_Copy_Image(Li_Image* img)
{
    Li_Image* out = NULL;
    out = Li_Create_Image(img->width, img->height, img->imgdepth, img->pt);
    memcpy((void*)out->data, (void*)img->data, img->width * img->height * (img->imgdepth + 1));
    return out;
}