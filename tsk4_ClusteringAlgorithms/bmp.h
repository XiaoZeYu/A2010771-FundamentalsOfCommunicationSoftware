
#ifndef BMP_H_INCLUDED
#define BMP_H_INCLUDED
#include "stdio.h"
#include "LiteCV.h"
#include "Windows.h"

 /*
  *
  *   �ڰף��ļ�ͷ(14�ֽ�)+��Ϣͷ(40�ֽ�)+2����ɫ��(��8�ֽ�)+Height(ͼ��߶�)*(Width+8-Width%8)/8

      16ɫ���ļ�ͷ(14�ֽ�)+��Ϣͷ(40�ֽ�)+16����ɫ��(��64�ֽ�)+Height(ͼ��߶�)*(Width+4-Width%4)/2

      256ɫ���ļ�ͷ(14�ֽ�)+��Ϣͷ(40�ֽ�)+256����ɫ��(��1024�ֽ�)+Height(ͼ��߶�)*(Width+4-Width%4)

      16λɫ���ļ�ͷ(14�ֽ�)+��Ϣͷ(40�ֽ�)+Height(ͼ��߶�)*(Width+4-Width%4)*2 (����ÿ�������������ֽڱ�ʾ)

      24λɫ���ļ�ͷ(14�ֽ�)+��Ϣͷ(40�ֽ�)+Height(ͼ��߶�)*(Width+4-Width%4)*3 (����ÿ�������������ֽڱ�ʾ)
  * */


/*
*bfType��λͼ�ļ����ͣ�������0x424D�����ַ�����BM����Ҳ����˵�����еġ�*.bmp���ļ���ͷ�����ֽڶ��ǡ�BM����
*bfSize��λͼ�ļ���С��������14���ֽڡ�
*bfReserved1, bfReserved2��Windows�����֣��ݲ��á�
*bfOffBits��(bfsize+bisize)���ļ�ͷ��ʵ�ʵ�λͼ���ݵ�ƫ���ֽ���
*/


//��ɫ��


/**
 * @name: Read_bmp
 * @msg: ��ȡһ��BMPͼƬ
 * @param char *filepath        ��ȡ�ļ���·��
 *        BITMAPFILEHEADER *bmf ���ļ��йص���Ϣ
 *        BITMAPINFOHEADER *bmi ��ͼƬ�йص���Ϣ
 * @return ����ָ��
 */
BYTE* Read_bmp(BYTE* filepath, BITMAPFILEHEADER* bmf, BITMAPINFOHEADER* bmi);
/**
 * @name:
 * @msg: дBMPͼƬ��ֻ����д���ݣ�û��ͼƬ��ת������
 * @param char *filepath        ��ȡ�ļ���·��
 *        BYTE *imgData         ����������
 *        BITMAPFILEHEADER *bmf ���ļ��йص���Ϣ
 *        BITMAPINFOHEADER *bmi ��ͼƬ�йص���Ϣ
 *        PICTYPE pt            ͼƬ����
 * @return 0 (right) or -1(something wrong)
 */
BYTE Write_bmp(BYTE* filepath, BYTE* imgData, BITMAPFILEHEADER* bmf, BITMAPINFOHEADER* bmi, PICTYPE pt);

void Print_bmp_FileHeader(BITMAPFILEHEADER* bmfh);
void Print_bmp_InfoHeader(BITMAPINFOHEADER* bmih);

#endif 
