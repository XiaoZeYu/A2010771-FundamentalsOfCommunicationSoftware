#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wingdi.h>
#include "BitmapAlterService.h"
#define PATH_READ SrcBmpFilePath
#define PATH_WRITE_GREY "./temp.bmp"  //����ͼ��·�����Ҷ�ͼ
#define PATH_EXCEL DstHistogramFilePath //���ɻҶ�ͳ�Ʊ��
#define PATH_WRITE_GREYTOCOLOR DstPseudocolorFilePath //����α��ɫͼ

unsigned char* pData;//�洢ͼ������
RGBQUAD* pRGBQUAD;//8λ��ɫ��

/*
    FILE* fp:BMPͼ���ļ�ָ��
    BITMAPFILEHEADER* bfheader:�����ļ�ͷ��Ϣ
    BITMAPINFOHEADER* biheader��������Ϣͷ��Ϣ
    unsigned char* pData:�洢ͼ������
    int flag:��ӡ�����־λ
    ����ֵ��ͼ�����������ַ
    ʹ��fread����ֱ�Ӷ�ȡһ���ṹ���С�����ݣ���Ϊ���С�̶��������ݿ���ֱ�Ӷ�Ӧ�Ͻṹ�壻����Printf����ֱ��������
*/
unsigned char* readBMP(FILE* fp, BITMAPFILEHEADER* bfheader, BITMAPINFOHEADER* biheader, int flag);//��ȡBMP�ļ����ļ�ͷ����Ϣͷ�����
/*
    ��ʮ��������תΪʮ�����ƺ���ASCII����������ַ�
    ����ֵ������ת������ַ�����ַ
*/
char* hex2str(int a, char* s);//˫�ֽ�ת��
/*
    FILE* fp:BMPͼ���ļ�ָ��
    BITMAPFILEHEADER* bfheader:ԭ�ļ�ͷ��Ϣ
    BITMAPINFOHEADER* biheader��ԭ��Ϣͷ��Ϣ
    unsigned char* pData:�洢ͼ������
    BITMAPINFOHEADER* biheader_write:�洢�޸ĺ���ļ�ͷ��Ϣ
    BITMAPFILEHEADER* bfheader_write:�洢�޸ĺ���Ϣͷ��Ϣ
    ����ֵ���ɹ�����1��ʧ�ܷ���0
    ͨ�ô���BMP�ļ���д���ļ�ͷ����Ϣͷ��ͼ�����ݵ���Ϣ
*/
int writeBMP(FILE* fp, BITMAPFILEHEADER* bfheader, BITMAPINFOHEADER* biheader, unsigned char* pData);//д���ļ�ͷ����Ϣͷ��ͼ��
/*
    FILE* fp:BMPͼ���ļ�ָ��
    BITMAPFILEHEADER* bfheader:ԭ�ļ�ͷ��Ϣ
    BITMAPINFOHEADER* biheader��ԭ��Ϣͷ��Ϣ
    unsigned char* pData:�洢ͼ������
    BITMAPINFOHEADER* biheader_write:�洢�޸ĺ���ļ�ͷ��Ϣ
    BITMAPFILEHEADER* bfheader_write:�洢�޸ĺ���Ϣͷ��Ϣ
    ����ֵ���ɹ�����1��ʧ�ܷ���0
    ͨ�ô���BMP�ļ���д���ļ�ͷ����Ϣͷ��ͼ�����ݵ���Ϣ
*/

int getArray(unsigned char*** p, int row, int col);//���ݳ������ɶ�ά����
/*
    BITMAPFILEHEADER* bfheader:�ļ�ͷ��Ϣ
    BITMAPINFOHEADER* biheader����Ϣͷ��Ϣ
    unsigned char* pData:�洢ͼ������
    char*** p:ָ�򴴽��Ķ�ά����ĵ�ַ
    ����ֵ���ɹ�����1��ʧ�ܷ���0
    ���ݹ�ʽ��Ȩ����Ҷ�ֵ�������ά����
*/
int readGrey(BITMAPFILEHEADER* bfheader, BITMAPINFOHEADER* biheader, unsigned char* pData, unsigned char*** p);//��ȡ�Ҷ�ֵ
/*
    BITMAPFILEHEADER* bfheader:�ļ�ͷ��Ϣ
    BITMAPINFOHEADER* biheader����Ϣͷ��Ϣ
    unsigned char* pData:�洢ͼ������
    char*** p:ָ�򴴽��Ķ�ά����ĵ�ַ
    ����ֵ���ɹ�����1��ʧ�ܷ���0
    ���ݶ�ά����Ҷ�ֵ�޸�ͼ������
*/
int BMP_Grey(BITMAPFILEHEADER* bfheader, BITMAPINFOHEADER* biheader, unsigned char* pData, unsigned char*** p);//�޸�ͼ�����ݣ��Ҷ�ͼ
/*
    BITMAPFILEHEADER* bfheader:�ļ�ͷ��Ϣ
    BITMAPINFOHEADER* biheader����Ϣͷ��Ϣ
    char*** p:ָ�򴴽��Ķ�ά����ĵ�ַ
    int a[256]:�洢�Ҷ�ͳ����
    ����ֵ���ɹ�����1��ʧ�ܷ���0
    ͳ�ƻҶ�ֵ��Ӧ���ظ���
*/
int greyExcel(BITMAPFILEHEADER* bfheader, BITMAPINFOHEADER* biheader, unsigned char*** p, int a[256]);//ͳ�ƻҶ�ֵ����
/*
    int a[256]:�洢�Ҷ�ͳ����
    ����ֵ���ɹ�����1��ʧ�ܷ���0
    д��ͳ�ƵĻҶ�ֵ���ظ�����EXCEL��
*/
int printExcel(int a[256]);//������ݵ�excel��
/*
    BITMAPFILEHEADER* bfheader:�ļ�ͷ��Ϣ
    BITMAPINFOHEADER* biheader����Ϣͷ��Ϣ
    unsigned char* pData:�洢ͼ������
    char*** p:ָ�򴴽��Ķ�ά����ĵ�ַ
    ����ֵ���ɹ�����1��ʧ�ܷ���0
    ���ݷ������ӹ�ʽ�ɻҶ�ͼתΪα��ɫͼ
*/
int greyToColor(BITMAPFILEHEADER* bfheader, BITMAPINFOHEADER* biheader, unsigned char* pData, unsigned char*** p);//�ɻҶ�ͼתΪα��ɫͼ
// �������ڼ����ݶȵĺ���
int gradient_x(int x, int y, unsigned char*** grey, int width);
int gradient_y(int x, int y, unsigned char** grey, int height);
int gradient_z(int x, int y, unsigned char*** grey, int height, int width);
int writeBMP2(FILE* fp, BITMAPFILEHEADER* bfheader, BITMAPINFOHEADER* biheader, unsigned char* pData);
int mapGrayToIndex(unsigned char gray);
int writeBMP3(FILE* fp, BITMAPFILEHEADER* bfheader, BITMAPINFOHEADER* biheader, unsigned char* pData);
int readGrey_2(BITMAPFILEHEADER* bfheader, BITMAPINFOHEADER* biheader, unsigned char* pData_EDGE, unsigned char*** p);//��ȡ�Ҷ�ֵ



unsigned char* readBMP(FILE* fp, BITMAPFILEHEADER* bfheader, BITMAPINFOHEADER* biheader, int flag)//��ȡBMP�ļ����ļ�ͷ����Ϣͷ�����
{
    char s[10];
    if (!fp)
        exit(-1);
    fseek(fp, 0, SEEK_SET);//��λ���ļ���ʼ��
    fread(bfheader, sizeof(BITMAPFILEHEADER), 1, fp);//��ȡ�ļ�ͷ14�ֽڽ�bfheader�ṹ����
    if (bfheader->bfType != 0x4D42)
    {
        printf("\n���ļ�����BMP�ļ�����ȡʧ�ܣ�\n");
        exit(-1);
    }
    fseek(fp, 14, SEEK_SET);
    fread(biheader, sizeof(BITMAPINFOHEADER), 1, fp);//��ȡ��Ϣͷ��biheader�ṹ����
    hex2str(19778, s);//���ΰ�˫�ֽ���ASCII��תΪ�ַ���
    if (flag)//��־Ϊ1ʱ�����ӡ
    {
        /*��ӡ����ļ�ͷ��Ϣ*/
        printf("\n����Ϊλͼ�ļ�ͷ��Ϣ��\n");
        printf("λͼ�ļ�����:%c%c\n", s[0], s[1]);
        printf("λͼ�ļ���С:%d�ֽ�\n", bfheader->bfSize);
        printf("λͼ�ļ�����ƫ��:%d�ֽ�\n", bfheader->bfOffBits);
        /*��ӡ�����Ϣͷ��Ϣ*/
        printf("\nλͼ��Ϣͷ��Ϣ����:\n");
        printf("��Ϣͷռ�ô�С:%d�ֽ�\n", biheader->biSize);
        printf("BMPͼ����:%d����\n", biheader->biWidth);
        printf("BMPͼ��߶�:%d����\n", biheader->biHeight);
        printf("BMPͼ����ɫλ��:%dλ\n", biheader->biBitCount);
        printf("BMPͼ��ѹ������:%d\n", biheader->biCompression);
        printf("BMPͼ��ʵ�����ݴ�С:%d�ֽ�\n", bfheader->bfSize);
    }

    /*���ݶ�ȡ*/
    if (biheader->biBitCount == 8)//��8λ��ͼ�񵥶�����
    {
        RGBQUAD* pRGBQUAD = (RGBQUAD*)malloc(sizeof(RGBQUAD) * 256);//Ϊ��ɫ������ռ�
        fread(pRGBQUAD, sizeof(RGBQUAD), 256, fp);//��ȡ256����ɫ������
    }
    int lineByte = (biheader->biWidth * biheader->biBitCount / 8 + 3) / 4 * 4;//����ʵ��λ��+3���4��4�ǰ�4�ֽڶ������λ����λ��7��������õ�ʵ��λ����8
    unsigned char* pData = (unsigned char*)malloc(sizeof(unsigned char) * biheader->biHeight * lineByte);//�����СΪʵ��ͼ�����ݴ�С�Ŀռ�
    fseek(fp, bfheader->bfOffBits, SEEK_SET);//��λ��������
    fread(pData, sizeof(unsigned char), biheader->biHeight * lineByte, fp);
    fclose(fp);
    return pData;
}
char* hex2str(int a, char* s)//˫�ֽ�ת��
{
    int a1 = a / 256;
    int a2 = a % 256;
    s[0] = (char)a2;
    s[1] = (char)a1;
    return s;
}

int mapGrayToIndex(unsigned char gray) {
    if (gray < 128)
        return 0;
    else
        return 255;
}
int writeBMP(FILE* fp, BITMAPFILEHEADER* bfheader, BITMAPINFOHEADER* biheader, unsigned char* pData)//д���ļ�ͷ����Ϣͷ��ͼ����������BMP�ļ�
{
    if (!fp)
        exit(-1);
    int colorTableSize = 0;//��ʼ����ɫ���С
    if (biheader->biBitCount == 8)
    {
        colorTableSize = 1024;//8λλ���ɫ���С1024�ֽ�
    }
    BITMAPFILEHEADER bfheader_write;
    BITMAPINFOHEADER biheader_write;

    int lineByte = (biheader->biWidth * biheader->biBitCount / 8 + 3) / 4 * 4;//����ʵ��λ��+3���4��4�ǰ�4�ֽڶ������λ����λ��7��������õ�ʵ��λ����8
    /*�����ļ�ͷ��Ϣ*/
    bfheader_write.bfType = 0x4D42;//BM
    bfheader_write.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTableSize + lineByte * biheader->biHeight;//�����ļ���С���ļ�ͷ+��Ϣͷ+��ɫ��+ͼ���С
    bfheader_write.bfReserved1 = bfheader_write.bfReserved2 = 0;
    bfheader_write.bfOffBits = 54 + colorTableSize;//����ƫ������bfheader_write.bfOffBits=bfheader.bfOffBits
    /*������Ϣͷ��Ϣ*/
    biheader_write.biBitCount = biheader->biBitCount;//����λ��
    biheader_write.biClrImportant = biheader_write.biClrUsed = biheader_write.biCompression = 0;
    biheader_write.biHeight = biheader->biHeight;//����λ��
    biheader_write.biWidth = biheader->biWidth;//����λ��
    biheader_write.biPlanes = 1;
    biheader_write.biSize = 40;//��Ϣͷ����
    biheader_write.biSizeImage = bfheader_write.bfSize;
    biheader_write.biXPelsPerMeter = 0;//����X�ֱ���
    biheader_write.biYPelsPerMeter = 0;//����Y�ֱ���

    fwrite(&bfheader_write, sizeof(BITMAPFILEHEADER), 1, fp);//���ļ�ͷ����д���ļ���д��һ�δ�СΪBITMAPFILEHEADER������
    fwrite(&biheader_write, sizeof(BITMAPINFOHEADER), 1, fp);//��Ϣͷ����д���ļ���д��һ�δ�СΪBITMAPINFOHEADER������

    if (biheader->biBitCount == 8)//��8λɫ����е�ɫ����Ҫд��
        fwrite(pRGBQUAD, sizeof(RGBQUAD), 256, fp);//8λ��ɫ����256����ɫ



    fwrite(pData, sizeof(unsigned char), biheader->biHeight * lineByte, fp);//д��ͼ������

    fclose(fp);
    return 1;
}
int writeBMP2(FILE* fp, BITMAPFILEHEADER* bfheader, BITMAPINFOHEADER* biheader, unsigned char* pData)//д���ļ�ͷ����Ϣͷ��ͼ����������BMP�ļ�
{
    if (!fp)
        exit(-1);
    int colorTableSize = 0;//��ʼ����ɫ���С
    if (biheader->biBitCount == 8)
    {
        colorTableSize = 1024;//8λλ���ɫ���С1024�ֽ�
    }
    BITMAPFILEHEADER bfheader_write;
    BITMAPINFOHEADER biheader_write;

    int lineByte = (biheader->biWidth * biheader->biBitCount / 8 + 3) / 4 * 4;//����ʵ��λ��+3���4��4�ǰ�4�ֽڶ������λ����λ��7��������õ�ʵ��λ����8
    /*�����ļ�ͷ��Ϣ*/
    bfheader_write.bfType = 0x4D42;//BM
    bfheader_write.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTableSize + lineByte * biheader->biHeight;//�����ļ���С���ļ�ͷ+��Ϣͷ+��ɫ��+ͼ���С
    bfheader_write.bfReserved1 = bfheader_write.bfReserved2 = 0;
    bfheader_write.bfOffBits = 54 + colorTableSize;//����ƫ������bfheader_write.bfOffBits=bfheader.bfOffBits
    /*������Ϣͷ��Ϣ*/
    biheader_write.biBitCount = biheader->biBitCount;//����λ��
    biheader_write.biClrImportant = biheader_write.biClrUsed = biheader_write.biCompression = 0;
    biheader_write.biHeight = biheader->biHeight;//����λ��
    biheader_write.biWidth = biheader->biWidth;//����λ��
    biheader_write.biPlanes = 1;
    biheader_write.biSize = 40;//��Ϣͷ����
    biheader_write.biSizeImage = bfheader_write.bfSize;//����ͼ���С
    biheader_write.biXPelsPerMeter = 0;//����X�ֱ���
    biheader_write.biYPelsPerMeter = 0;//����Y�ֱ���

    fwrite(&bfheader_write, sizeof(BITMAPFILEHEADER), 1, fp);//���ļ�ͷ����д���ļ���д��һ�δ�СΪBITMAPFILEHEADER������
    fwrite(&biheader_write, sizeof(BITMAPINFOHEADER), 1, fp);//��Ϣͷ����д���ļ���д��һ�δ�СΪBITMAPINFOHEADER������

    if (biheader->biBitCount == 8)//��8λɫ����е�ɫ����Ҫд��
        fwrite(pRGBQUAD, sizeof(RGBQUAD), 256, fp);//8λ��ɫ����256����ɫ



    fwrite(pData, sizeof(unsigned char), biheader->biHeight * lineByte, fp);//д��ͼ������

    fclose(fp);
    return 1;
}


int writeBMP3(FILE* fp, BITMAPFILEHEADER* bfheader, BITMAPINFOHEADER* biheader, unsigned char* pData) {
    if (!fp) {
        exit(-1);
    }

    int colorTableSize = 0; // ��ɫ���С
    if (biheader->biBitCount == 8) {
        colorTableSize = 1024; // 8λλ���ɫ���С
    }
    else if (biheader->biBitCount == 1) {
        colorTableSize = sizeof(RGBQUAD) * 2; // 1λλ���ɫ���С
    }

    int lineByte = (biheader->biWidth * biheader->biBitCount / 8 + 3) / 4 * 4; // ����ʵ��λ��

    /* �����ļ�ͷ��Ϣ */
    BITMAPFILEHEADER bfheader_write = {
        .bfType = 0x4D42, // 'BM'
        .bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTableSize + lineByte * abs(biheader->biHeight),
        .bfReserved1 = 0,
        .bfReserved2 = 0,
        .bfOffBits = 54 + colorTableSize
    };

    /* ������Ϣͷ��Ϣ */
    BITMAPINFOHEADER biheader_write = {
        .biSize = 40, // ��Ϣͷ����
        .biWidth = biheader->biWidth,
        .biHeight = biheader->biHeight,
        .biPlanes = 1,
        .biBitCount = biheader->biBitCount,
        .biCompression = 0,
        .biSizeImage = lineByte * abs(biheader->biHeight),
        .biXPelsPerMeter = 0,
        .biYPelsPerMeter = 0,
        .biClrUsed = 0,
        .biClrImportant = 0
    };

    fwrite(&bfheader_write, sizeof(BITMAPFILEHEADER), 1, fp); // д���ļ�ͷ
    fwrite(&biheader_write, sizeof(BITMAPINFOHEADER), 1, fp); // д����Ϣͷ

    // �����1λλ�����Ҫд���ɫ��
    if (biheader->biBitCount == 1) {
        RGBQUAD colorTable[2] = {
            { 0x00, 0x00, 0x00, 0x00 }, // ��ɫ
            { 0xFF, 0xFF, 0xFF, 0x00 }  // ��ɫ
        };
        fwrite(colorTable, sizeof(RGBQUAD), 2, fp); // д���ɫ��
    }

    fwrite(pData, sizeof(unsigned char), biheader->biHeight * lineByte, fp); // д��ͼ������

    fclose(fp);
    return 1;
}



int getArray(unsigned char*** p, int row, int col)//���ݳ������ɶ�ά����
{
    int i;
    *p = (unsigned char**)malloc(sizeof(unsigned char*) * row);//����row�пռ䣬*p�洢�����е��׵�ַ
    memset(*p, 0, sizeof(unsigned char*) * row);//ÿ���׵�ַ����
    if (p == NULL)
        exit(-1);
    for (i = 0; i < row; i++)
    {
        (*p)[i] = (unsigned char*)malloc(sizeof(unsigned char) * col);//��ǰ������col�пռ䣬*p[i]�洢���е��׵�ַ
        memset((*p)[i], 0, sizeof(unsigned char) * col);//��ǰ����������������
        if ((*p)[i] == NULL)
            exit(-1);
    }
    return 1;
}


int readGrey(BITMAPFILEHEADER* bfheader, BITMAPINFOHEADER* biheader, unsigned char* pData, unsigned char*** p)//��ȡ�Ҷ�ֵ
{
    int lineByte = (biheader->biWidth * biheader->biBitCount / 8 + 3) / 4 * 4;//����ʵ��λ��
    float grey;
    for (int i = 0; i < biheader->biHeight; i++)//ѭ����
    {
        int col = 0;//����ͼ������
        for (int j = 0; j < 3 * biheader->biWidth; j++)//ѭ����
        {
            unsigned char B = *(pData + i * lineByte + j);//��ȡBֵ
            j++;
            unsigned char G = *(pData + i * lineByte + j);//��ȡGֵ
            j++;
            unsigned char R = *(pData + i * lineByte + j);//��ȡRֵ
            grey = 0.114 * B + 0.587 * G + 0.299 * R;
            (*p)[i][col] = grey;//��Ȩ����Ҷ�ֵ
            col++;
        }
    }
    return 1;
}



int BMP_Grey(BITMAPFILEHEADER* bfheader, BITMAPINFOHEADER* biheader, unsigned char* pData, unsigned char*** p)//�޸�ͼ�����ݣ��Ҷ�ͼ
{
    int lineByte = (biheader->biWidth * biheader->biBitCount / 8 + 3) / 4 * 4;//����ʵ��λ��
    for (int i = 0; i < biheader->biHeight; i++)//ѭ����
    {
        int col = 0;//����ͼ������
        for (int j = 0; j < 3 * biheader->biWidth; j++)//ѭ����
        {
            *(pData + i * lineByte + j) = (*p)[i][col];//��ȡBֵ
            j++;
            *(pData + i * lineByte + j) = (*p)[i][col];//��ȡGֵ
            j++;
            *(pData + i * lineByte + j) = (*p)[i][col];//��ȡRֵ
            col++;
        }
    }
    return 1;
}

int greyExcel(BITMAPFILEHEADER* bfheader, BITMAPINFOHEADER* biheader, unsigned char*** p, int a[256])//ͳ�ƻҶ�ֵ����
{
    for (int i = 0; i < 256; i++)//�Ҷ�ֵ��0��255
    {
        int count = 0;//����������
        for (int j = 0; j < biheader->biHeight; j++)//����������
        {
            for (int k = 0; k < biheader->biWidth; k++)//����������
            {
                if ((*p)[j][k] == i)//���������ѯ��ǰ�Ҷ�ֵ�Ƿ���ͬ
                    count++;
            }
        }
        a[i] = count;//����ûҶ�ֵ����������
    }
    return 1;
}

int printExcel(int a[256])//������ݵ�excel��
{
    FILE* fp = NULL;
    fp = fopen(PATH_EXCEL, "w+");//����ָ��·��excel�ļ�
    fprintf(fp, "%s,%s\n", "�Ҷ�ֵ", "��������");//д�����position��power
    if (!fp)
        return 0;
    for (int i = 0; i < 256; i++)//д��Ҷ�ֵ��Ӧ���ظ���
    {
        fprintf(fp, "%d,%d\n", i, a[i]);
    }

    fclose(fp);
    return 1;
}

int greyToColor(BITMAPFILEHEADER* bfheader, BITMAPINFOHEADER* biheader, unsigned char* pData, unsigned char*** p)//�ɻҶ�ͼתΪα��ɫͼ
{
    int lineByte = (biheader->biWidth * biheader->biBitCount / 8 + 3) / 4 * 4;//����ʵ��λ��
    for (int i = 0; i < biheader->biHeight; i++)//ѭ����
    {
        int col = 0;//�����Ҷ���������
        for (int j = 0; j < biheader->biWidth * 3; j++)//ѭ����
        {
            /*��OpenCV��RainBowӳ��*/
            if ((*p)[i][col] <= 30)//����1���ӣ�ÿ64�Ҷ�ֵ����һ������
            {
                *(pData + i * lineByte + j) = 255;//����B����
                j++;
                *(pData + i * lineByte + j) = 0;//����G����
                j++;
                *(pData + i * lineByte + j) = 125 - 4.16 * (*p)[i][col];//����R����
            }
            else if ((*p)[i][col] > 30 && (*p)[i][col] <= 87)//����2����
            {
                *(pData + i * lineByte + j) = 255;//����B����
                j++;
                *(pData + i * lineByte + j) = ((*p)[i][col] - 30) * 4.47;//����G����
                j++;
                *(pData + i * lineByte + j) = 0;//����R����
            }
            else if ((*p)[i][col] > 87 && (*p)[i][col] <= 142)//����2����
            {
                *(pData + i * lineByte + j) = 255 - 4.64 * ((*p)[i][col] - 87);//����B����
                j++;
                *(pData + i * lineByte + j) = 255;//����G����
                j++;
                *(pData + i * lineByte + j) = 0;//����R����
            }
            else if ((*p)[i][col] > 142 && (*p)[i][col] <= 201)//����3����
            {
                *(pData + i * lineByte + j) = 0;//����B����
                j++;
                *(pData + i * lineByte + j) = 255;//����G����
                j++;
                *(pData + i * lineByte + j) = 4.32 * ((*p)[i][col] - 142);//����R����
            }
            else if ((*p)[i][col] > 201)//����4����
            {
                *(pData + i * lineByte + j) = 0;//����B����
                j++;
                *(pData + i * lineByte + j) = 255 - 4.72 * ((*p)[i][col] - 201);//����G����
                j++;
                *(pData + i * lineByte + j) = 255;//����R����
            }
            col++;

        }
    }

    return 1;
}







int WangHaiBo()
{
    FILE* fp = fopen(PATH_READ, "rb");
    BITMAPFILEHEADER bfheader_read;//�����ļ�ͷ�ṹ��
    BITMAPINFOHEADER biheader_read;//������Ϣͷ�ṹ��
    unsigned char* pData = readBMP(fp, &bfheader_read, &biheader_read, 1);//��ȡͼ�񷵻�ͼ������
    /*���ɻҶ�ͼ*/
    fp = fopen(PATH_READ, "rb");
    pData = readBMP(fp, &bfheader_read, &biheader_read, 0);//��ȡͼ�񷵻�ͼ������

    unsigned char** grey;//������ά���飬�洢�Ҷ�ֵ
    if (!getArray(&grey, biheader_read.biHeight, biheader_read.biWidth))//���ɶ�ά����
        exit(-1);
    if (!readGrey(&bfheader_read, &biheader_read, pData, &grey))//��ȡ�Ҷ�ֵ������grey������
        exit(-1);
    if (!BMP_Grey(&bfheader_read, &biheader_read, pData, &grey))//�޸�ͼ��Ĵ洢���ݣ��Ҷ�ͼ
        exit(-1);
    fp = fopen(PATH_WRITE_GREY, "wb");
    if (!writeBMP(fp, &bfheader_read, &biheader_read, pData))//����BMP�ļ�
        exit(-1);
    /*���ɻҶ�ֱ��ͼ*/
    int greyArray[256];
    if (!greyExcel(&bfheader_read, &biheader_read, &grey, greyArray))
        exit(-1);
    if (!printExcel(greyArray))
        exit(-1);
    /*�ɹ�ʽ��������α��ɫͼ*/
    if (!greyToColor(&bfheader_read, &biheader_read, pData, &grey))//����RGB�����޸�ͼ������
        exit(-1);
    fp = fopen(PATH_WRITE_GREYTOCOLOR, "wb");
    if (!writeBMP(fp, &bfheader_read, &biheader_read, pData))//����BMP�ļ�
        exit(-1);
    fclose(fp);

    return 0;
}




