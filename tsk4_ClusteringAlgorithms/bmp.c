#define _CRT_SECURE_NO_WARNINGS
#ifndef BMP_H
#define BMP_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "string.h"
#include "bmp.h"

int Read_bmp_FileHeader(char* filepath, BITMAPFILEHEADER* bmfh)
{
    FILE* fp;
    fp = fopen(filepath, "rb");
    if (!fp)
    {
        return -1;
    }
    if (fread(&bmfh->bfType, sizeof(WORD), 1, fp) != 1)
    {
        fclose(fp);
        return -1;
    }
    if (fread(&bmfh->bfSize, sizeof(DWORD), 1, fp) != 1)
    {
        fclose(fp);
        return -1;
    }
    if (fread(&bmfh->bfReserved1, sizeof(WORD), 1, fp) != 1)
    {
        fclose(fp);
        return -1;
    }
    if (fread(&bmfh->bfReserved2, sizeof(WORD), 1, fp) != 1)
    {
        fclose(fp);
        return -1;
    }
    if (fread(&bmfh->bfOffBits, sizeof(DWORD), 1, fp) != 1)
    {
        fclose(fp);
        return -1;
    }
    fclose(fp);
    return 0;
}


int Read_bmp_InfoHeader(char* filepath, BITMAPINFOHEADER* bmih)
{
    FILE* fp;
    fp = fopen(filepath, "rb");
    if (!fp)
    {
        return -1;
    }
    fseek(fp, 14, SEEK_SET);
    if (fread(&bmih->biSize, sizeof(DWORD), 1, fp) != 1)
    {
        fclose(fp);
        return -1;
    }
    if (fread(&bmih->biWidth, sizeof(LONG), 1, fp) != 1)
    {
        fclose(fp);
        return -1;
    }
    if (fread(&bmih->biHeight, sizeof(LONG), 1, fp) != 1)
    {
        fclose(fp);
        return -1;
    }
    if (fread(&bmih->biPlanes, sizeof(WORD), 1, fp) != 1)
    {
        fclose(fp);
        return -1;
    }
    if (fread(&bmih->biBitCount, sizeof(WORD), 1, fp) != 1)
    {
        fclose(fp);
        return -1;
    }
    if (fread(&bmih->biCompression, sizeof(DWORD), 1, fp) != 1)
    {
        fclose(fp);
        return -1;
    }
    if (fread(&bmih->biSizeImage, sizeof(DWORD), 1, fp) != 1)
    {
        fclose(fp);
        return -1;
    }
    if (fread(&bmih->biXPelsPerMeter, sizeof(LONG), 1, fp) != 1)
    {
        fclose(fp);
        return -1;
    }
    if (fread(&bmih->biYPelsPerMeter, sizeof(LONG), 1, fp) != 1)
    {
        fclose(fp);
        return -1;
    }
    if (fread(&bmih->biClrUsed, sizeof(DWORD), 1, fp) != 1)
    {
        fclose(fp);
        return -1;
    }
    if (fread(&bmih->biClrImportant, sizeof(DWORD), 1, fp) != 1)
    {
        fclose(fp);
        return -1;
    }
    fclose(fp);
    return 0;
}


void Print_bmp_FileHeader(BITMAPFILEHEADER* bmfh)
{
    printf("The contents in the file header of the BMP file:\n");
    printf("bfOffBits: %ld\n", (long int)bmfh->bfOffBits);
    printf("bfReserved1: %ld\n", (long int)bmfh->bfReserved1);
    printf("bfReserved2: %ld\n", (long int)bmfh->bfReserved2);
    printf("bfSize: %ld\n", (long int)bmfh->bfSize);
    printf("bfType: %ld\n", (long int)bmfh->bfType);
}

void Print_bmp_InfoHeader(BITMAPINFOHEADER* bmih)
{
    printf("The content in the info header of the BMP file:\n");
    printf("biBitCount: %ld\n", (long int)bmih->biBitCount);
    printf("biClrImportant: %ld\n", (long int)bmih->biClrImportant);
    printf("biClrUsed: %ld\n", (long int)bmih->biClrUsed);
    printf("biCompression: %ld\n", (long int)bmih->biCompression);
    printf("biHeight: %ld\n", (long int)bmih->biHeight);
    printf("biPlanes: %ld\n", (long int)bmih->biPlanes);
    printf("biSize: %ld\n", (long int)bmih->biSize);
    printf("biSizeImage: %ld\n", (long int)bmih->biSizeImage);
    printf("biWidth: %ld\n", (long int)bmih->biWidth);
    printf("biXPelsPerMeter: %ld\n", (long int)bmih->biXPelsPerMeter);
    printf("biYPelsPerMeter: %ld\n", (long int)bmih->biYPelsPerMeter);
}


/**
 * @name: Read_bmp
 * @msg: ��ȡһ��BMPͼƬ
 * @param char *filepath        ��ȡ�ļ���·��
 *        BITMAPFILEHEADER *bmf ���ļ��йص���Ϣ
 *        BITMAPINFOHEADER *bmi ��ͼƬ�йص���Ϣ
 * @return ����ָ��
 */
BYTE* Read_bmp(BYTE* filepath, BITMAPFILEHEADER* bmf, BITMAPINFOHEADER* bmi)
{
    BYTE* imgData;
    BITMAPINFOHEADER bmih;
    BITMAPFILEHEADER bmfh;
    FILE* fp;
    u8 R, G, B;
    u16 pixel;
    int n, i;
    int width;
    int height;
    int bitCount;
    DWORD dwLineBytes;
    n = Read_bmp_FileHeader(filepath, &bmfh);
    if (n == -1)
    {
        printf("Can not read the file header of the BMP file.\n");
        return NULL;
    }
    n = Read_bmp_InfoHeader(filepath, &bmih);
    if (n == -1)
    {
        printf("Can not read the info header of the BMP file.\n");
        return NULL;
    }

    memcpy(bmi, &bmih, sizeof(BITMAPINFOHEADER));
    memcpy(bmf, &bmfh, sizeof(BITMAPFILEHEADER));
#ifdef DEBUG
    Print_bmp_FileHeader(bmf);
    Print_bmp_InfoHeader(bmi);
#endif // DEBUG

    width = bmih.biWidth;
    height = bmih.biHeight;
    bitCount = bmih.biBitCount;
    imgData = (BYTE*)malloc((bitCount / (8 * sizeof(BYTE))) * width * height * sizeof(BYTE));
    fp = fopen(filepath, "rb");
    if (!fp)
    {
        printf("Can not open the file: %s\n", filepath);
        return NULL;
    }
    fseek(fp, bmfh.bfOffBits, SEEK_SET);//�ƶ������ݿ�ʼ�ĵط�

    if (fread(imgData, (bitCount / (8 * sizeof(BYTE))) * width * height * sizeof(BYTE), 1, fp) != 1)
    {

        free(imgData);
        fclose(fp);
        return NULL;
    }

    fclose(fp);
    return imgData;
}


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
BYTE Write_bmp(BYTE* filepath, BYTE* imgData, BITMAPFILEHEADER* bmf, BITMAPINFOHEADER* bmi, PICTYPE pt)
{
    FILE* fp;
    int i;
    RGBQUAD* IpRGBQuad;
    LONG height = bmi->biHeight;
    DWORD dwLineBytes = (bmi->biBitCount / (8 * sizeof(BYTE))) * bmi->biWidth;
    fp = fopen(filepath, "wb");
    if (!fp)
    {
        printf("Error: Can not open the file:%s\n", filepath);
    }
    switch (pt)
    {

    case LI_BMP_1://BW
        dwLineBytes = (bmi->biWidth + 8 - bmi->biWidth % 8) / 8;

        if (fwrite(&(bmf->bfType), sizeof(WORD), 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        if (fwrite(&(bmf->bfSize), sizeof(DWORD), 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        if (fwrite(&(bmf->bfReserved1), sizeof(WORD), 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        if (fwrite(&(bmf->bfReserved2), sizeof(WORD), 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        if (fwrite(&(bmf->bfOffBits), sizeof(DWORD), 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        if (fwrite(bmi, 40, 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        /*ͼ��Ķ�ȡ˳���Ǵ��µ���,������*/
        IpRGBQuad = (RGBQUAD*)malloc(2 * sizeof(RGBQUAD));
        IpRGBQuad[0].rgbRed = 0;
        IpRGBQuad[0].rgbGreen = 0;
        IpRGBQuad[0].rgbBlue = 0;
        IpRGBQuad[0].rgbReserved = 0;

        IpRGBQuad[1].rgbRed = 255;
        IpRGBQuad[1].rgbGreen = 255;
        IpRGBQuad[1].rgbBlue = 255;
        IpRGBQuad[0].rgbReserved = 0;
        fwrite(IpRGBQuad, 8, 1, fp);
        if (fwrite(imgData, dwLineBytes * height, 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        break;

    case LI_BMP_8://GRAY
        LILOG("WRITE GRAY");
        if (fwrite(&(bmf->bfType), sizeof(WORD), 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        if (fwrite(&(bmf->bfSize), sizeof(DWORD), 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        if (fwrite(&(bmf->bfReserved1), sizeof(WORD), 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        if (fwrite(&(bmf->bfReserved2), sizeof(WORD), 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        if (fwrite(&(bmf->bfOffBits), sizeof(DWORD), 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        if (fwrite(bmi, 40, 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        /*ͼ��Ķ�ȡ˳���Ǵ��µ���,������*/

        IpRGBQuad = (RGBQUAD*)malloc(256 * sizeof(RGBQUAD));//�Ҷ�ͼΪ8λ�ĵ�ɫ������Ϊ256���ṹ,1024���ֽ�
        for (int i = 0; i < 256; i++) {
            IpRGBQuad[i].rgbRed = i;
            IpRGBQuad[i].rgbGreen = i;
            IpRGBQuad[i].rgbBlue = i;
            IpRGBQuad[i].rgbReserved = 0;
        }
        fwrite(IpRGBQuad, 1024, 1, fp);
        if (fwrite(imgData, height * dwLineBytes, 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        break;

    case LI_BMP_565://BMP565
        printf("�ݲ�֧�֣�ʵ�ڲ����Լ�д\n");
        /* code */
        break;

    case LI_BMP_888://BMP888
        //��Ϊ�����ֽڶ������ⲻ��һ��д��
        if (fwrite(&(bmf->bfType), sizeof(WORD), 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        if (fwrite(&(bmf->bfSize), sizeof(DWORD), 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        if (fwrite(&(bmf->bfReserved1), sizeof(WORD), 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        if (fwrite(&(bmf->bfReserved2), sizeof(WORD), 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        if (fwrite(&(bmf->bfOffBits), sizeof(DWORD), 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        if (fwrite(bmi, 40, 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        if (fwrite(imgData, height * dwLineBytes, 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        break;

    case LI_BMP_32://BMP32
        if (fwrite(&(bmf->bfType), sizeof(WORD), 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        if (fwrite(&(bmf->bfSize), sizeof(DWORD), 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        if (fwrite(&(bmf->bfReserved1), sizeof(WORD), 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        if (fwrite(&(bmf->bfReserved2), sizeof(WORD), 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        if (fwrite(&(bmf->bfOffBits), sizeof(DWORD), 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        if (fwrite(bmi, 40, 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        if (fwrite(imgData, height * dwLineBytes, 1, fp) != 1)
        {
            fclose(fp);
            return -1;
        }
        break;


    default:
        break;
    }

}

#endif // !BMP_H