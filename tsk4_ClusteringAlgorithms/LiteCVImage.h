/*
 * @Descripttion: ʵ��ͼ����ĳ�ʼ���ӿ�
 * @version:
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-27 22:43:25
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-28 12:00:44
 */
#ifndef LI_IMAGE_H
#define LI_IMAGE_H

#include "LiteCV.h"
#include "bmp.h"

 /**
  * @name:Li_Wait_Q
  * @msg: �ȴ�һ��q
  * @param {*}
  * @return {*}
  */
LI_API
void Li_Wait_Q();

/**
 * @name: Li_CV_Version
 * @msg: ��ӡ������Ϣ
 * @param {*}
 * @return {*}
 */
LI_API
void Li_CV_Version();

/**
 * @name: li_free_arr
 * @msg: ΪLiArr�ͷ��ڴ�
 * @param {void}
 * @return {void}
 */
LI_API
void li_free_arr(LiArr* arr);

/**
 * @name: li_malloc_arr
 * @msg: ΪLiArr�����ڴ�
 * @param {size}�����ڴ�Ĵ�С
 * @return {LiArr}��������
 */
LI_API
LiArr* li_malloc_arr(LONG size);

/**
 * @name: Li_Create_Mat
 * @msg:
 * @param       LONG width,LONG height, �ߺͿ�
                BYTE depth,             ͼ�����
 * @return {Li_Mat}
 */
Li_Mat* Li_Create_Mat(LiArr* data, LONG width, LONG height, BYTE depth);


/**
 * @name: Li_Destroy_Mat
 * @msg: ΪLiMat�ͷ��ڴ�
 * @param {void}
 * @return {void}
 */
void Li_Destroy_Mat(Li_Mat* mat);

/**
 * @name: Li_Load_Image
 * @msg: �û��ӿں�����������ȡһ��ͼƬ
 * @param
 *        BYTE *filepath        ͼƬ·��
 *        PICTYPE pt            ͼƬ����
 * @return 0 (right) or -1(something wrong)
 */
LI_API
Li_Image* Li_Load_Image(BYTE* filepath, PICTYPE pt);



/**
 * @name: Li_Save_Image
 * @msg: �û��ӿں�������������һ��ͼƬ
 * @param
 *        BYTE *filepath        ͼƬ·��
 *        Li_Image* img         LitecvͼƬ����
 * @return 0 (right) or -1(something wrong)
 */
LI_API
BYTE Li_Save_Image(BYTE* filepath, Li_Image* img);


/**
 * @name: Li_Destroy_Image
 * @msg: �û��ӿں���������ɾ��һ��ͼƬ
 * @param
          Li_Image * img
 * @return 0 (right) or -1(something wrong)
 */
LI_API
void Li_Destroy_Image(Li_Image* img);


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
Li_Image* Li_Create_Image(LONG width, LONG height, BYTE depth, PICTYPE pth);


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
Li_Image* Li_Copy_Image(Li_Image* img);


/**
 * @name: Li_CvtColor
 * @msg:  �ṩ���������ת�����ṩ���ͼ�飬Ŀ��ָ���ں����ڲ������ڴ�
 * @param
          const LiArr* src  ԭ����
          LiArr *dst        Ŀ������
          BYTE cvtype       ת����ʽ
 * @return Li_Image*  һ��ͼƬ
 */
LI_API
void Li_CvtColor(LiArr* src, LiArr* dst, LONG width, LONG height, BYTE cvtype);

/**
 * @name: Li_Convert_Image
 * @msg:  �ṩͼƬ����ת����ͼƬ����ָ����
 * @param
          const LiArr* src  ԭ����
          LiArr *dst        Ŀ������
          BYTE cvtype       ת����ʽ
 * @return Li_Image*  һ��ͼƬ
 */
LI_API
Li_Image* Li_Convert_Image(Li_Image* src, BYTE convertype);
/**
 * @name: Li_Get_Roi
 * @msg: ��ȡ����Ȥ����
 * @param {Li_Image* img ԭͼ��
 *         LONG x1       ���½������к�
 *         LONG y1       ���½������к�
 *         LONG x2       ���Ͻ������к�
 *         LONG y2}      ���Ͻ������к�
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Get_Roi(Li_Image* img, LONG x1, LONG y1, LONG x2, LONG y2);

/**
 * @name: Li_ReShape
 * @msg: ����ͼ���С
 * @param Li_Image* img  ԭͼ��
 *        LONG tag_width ͼ����
 *        LONG tag_heightͼ��߶�
 * @return {*}
 */
LI_API
Li_Image* Li_ReShape(Li_Image* img, LONG tag_width, LONG tag_height);

/**
 * @name: Li_Rotate_180
 * @msg: ��ת180
 * @param {Li_Image* img}
 * @return {*}
 */
LI_API
Li_Image* Li_Rotate_180(Li_Image* img);

#endif // !LI_IMAGE_H

