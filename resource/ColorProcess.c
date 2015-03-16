/*
 * 中文说明
 * 如果你下载或使用本代码说明你已阅读并同意本声明
 * 此代码由谭升（Tony）开发，并允许任何人，或团体下载，使用此代码用于任何商业或非商业用途
 * 使用本代码时必须复制此声明
 * 本函数库版权归谭升所有.
 * 如有第三方，例如部分使用OpenCV函数，OpenCV函数库版权属于Intel公司，将在后续版本中去除这些函数，特此声明
 
 * English
 * If you download or use the code that you have read and agree to this statement,
 * This code by Tan Sheng (Tony) development, and allow any person, or group to download,
 * use for any commercial or non-commercial use
 * Use the code must be copied to this statement
 * Copyright (C) 2015,Tony, all rights reserved.
 * Part of the use of the OpenCV function, OpenCV function library copyright belongs
 * to Intel company, will remove these functions in subsequent versions, hereby declare
 */
//
//  ColorProcess
//  tony.sheng.tan@gmail.com
//  Created by 谭升 on 15/03/16.
//  Copyright (c) 2015年 谭升. All rights reserved.
//

#include "ColorProcess.h"

void HistEqualRGB(RGB *src,RGB *dst,int width,int height){
    HSI *temp=(HSI*)malloc(sizeof(HSI)*width*height);
    double *chanel_i=(double *)malloc(sizeof(double)*width*height);
    RGB2HSI(src, temp, width, height);
    for(int i=0;i<width*height;i++){
        chanel_i[i]=(double)((int)temp[i].c3);
    }
    HistogramEqualization(chanel_i, chanel_i, width, height);
    for(int i=0;i<width*height;i++){
        temp[i].c3=chanel_i[i];
    }
    HSI2RGB(temp, dst, width, height);
    free(temp);
    free(chanel_i);
    
}
void SmoothRGB(RGB *src,RGB *dst,int width,int height,int m_width,int m_height,double param1,double param2,int Smooth_type){
    double *chanel_r=(double*)malloc(sizeof(double)*width*height);
    double *chanel_g=(double*)malloc(sizeof(double)*width*height);
    double *chanel_b=(double*)malloc(sizeof(double)*width*height);
    double *chanel_r_dst=(double*)malloc(sizeof(double)*width*height);
    double *chanel_g_dst=(double*)malloc(sizeof(double)*width*height);
    double *chanel_b_dst=(double*)malloc(sizeof(double)*width*height);
    Split(src, chanel_r, chanel_g, chanel_b, width, height);
    switch (Smooth_type) {
        case SMOOTH_GAUSSIAN:{
            GaussianFilter(chanel_r, chanel_r_dst, width, height, m_width, m_height, param1);
            GaussianFilter(chanel_g, chanel_g_dst, width, height, m_width, m_height, param1);
            GaussianFilter(chanel_b, chanel_b_dst, width, height, m_width, m_height, param1);
            break;
        }
        case SMOOTH_MEDIAN:{
            MedianFilter(chanel_r, chanel_r_dst, width, height, m_width, m_height);
            MedianFilter(chanel_g, chanel_g_dst, width, height, m_width, m_height);
            MedianFilter(chanel_b, chanel_b_dst, width, height, m_width, m_height);
            break;
        }
        case SMOOTH_BILATERAL:{
            BilateralFilter(chanel_r, chanel_r_dst, width, height, m_width, m_height, param1, param2);
            BilateralFilter(chanel_g, chanel_g_dst, width, height, m_width, m_height, param1, param2);
            BilateralFilter(chanel_b, chanel_b_dst, width, height, m_width, m_height, param1, param2);
            break;
        }
        case SMOOTH_MEAN:{
            MeanFilter(chanel_r, chanel_r_dst, width, height, m_width, m_height);
            MeanFilter(chanel_g, chanel_g_dst, width, height, m_width, m_height);
            MeanFilter(chanel_b, chanel_b_dst, width, height, m_width, m_height);
            break;
            
        }
        default:
            break;
    }

    Merge(chanel_r_dst, chanel_g_dst, chanel_b_dst, dst, width, height);
    free(chanel_r);
    free(chanel_g);
    free(chanel_b);
    free(chanel_r_dst);
    free(chanel_g_dst);
    free(chanel_b_dst);
}


void SmoothHSI(HSI *src,HSI *dst,int width,int height,int m_width,int m_height,double param1,double param2,int Smooth_type){
    double *chanel_i=(double*)malloc(sizeof(double)*width*height);
    double *chanel_i_dst=(double*)malloc(sizeof(double)*width*height);
    Split(src, NULL, NULL, chanel_i, width, height);
    switch (Smooth_type) {
        case SMOOTH_GAUSSIAN:{
            GaussianFilter(chanel_i, chanel_i_dst, width, height, m_width, m_height, param1);
            break;
        }
        case SMOOTH_MEDIAN:{
            MedianFilter(chanel_i, chanel_i_dst, width, height, m_width, m_height);
            break;
        }
        case SMOOTH_BILATERAL:{
            BilateralFilter(chanel_i, chanel_i_dst, width, height, m_width, m_height, param1, param2);
            break;
        }
        case SMOOTH_MEAN:{
            MeanFilter(chanel_i, chanel_i_dst, width, height, m_width, m_height);
            break;
        }
        default:
            break;
    }
    for(int i=0;i<width*height;i++){
        dst[i].c1=src[i].c1;
        dst[i].c2=src[i].c2;
        dst[i].c3=chanel_i_dst[i];
    }
    free(chanel_i);
    free(chanel_i_dst);
}



void SharpenRGB(RGB *src,RGB *dst,int width,int height,double c,int Sharpen_type){
    double *chanel_r=(double*)malloc(sizeof(double)*width*height);
    double *chanel_g=(double*)malloc(sizeof(double)*width*height);
    double *chanel_b=(double*)malloc(sizeof(double)*width*height);
    double *chanel_r_dst=(double*)malloc(sizeof(double)*width*height);
    double *chanel_g_dst=(double*)malloc(sizeof(double)*width*height);
    double *chanel_b_dst=(double*)malloc(sizeof(double)*width*height);
    Split(src, chanel_r, chanel_g, chanel_b, width, height);
    switch (Sharpen_type) {
        case SHARPEN_LAPLACE:{
            LaplaceSharpen(chanel_r, chanel_r_dst, width, height, c);
            LaplaceSharpen(chanel_g, chanel_g_dst, width, height, c);
            LaplaceSharpen(chanel_b, chanel_b_dst, width, height, c);
            break;
        }
        case SHARPEN_SOBEL:{
            SobelSharpen(chanel_r, chanel_r_dst, width, height, c);
            SobelSharpen(chanel_g, chanel_g_dst, width, height, c);
            SobelSharpen(chanel_b, chanel_b_dst, width, height, c);
            break;
        }
        case SHARPEN_ROBERT:{
            RobertSharpen(chanel_r, chanel_r_dst, width, height, c);
            RobertSharpen(chanel_g, chanel_g_dst, width, height, c);
            RobertSharpen(chanel_b, chanel_b_dst, width, height, c);
            break;
        }
        default:
            break;
    }
    
    Merge(chanel_r_dst, chanel_g_dst, chanel_b_dst, dst, width, height);
    free(chanel_r);
    free(chanel_g);
    free(chanel_b);
    free(chanel_r_dst);
    free(chanel_g_dst);
    free(chanel_b_dst);
}

void SharpenHSI(HSI *src,HSI *dst,int width,int height,double c,int Sharpen_type){
    double *chanel_i=(double*)malloc(sizeof(double)*width*height);
    double *chanel_i_dst=(double*)malloc(sizeof(double)*width*height);
    Split(src, NULL, NULL, chanel_i, width, height);
    switch (Sharpen_type) {
        case SHARPEN_LAPLACE:{
            LaplaceSharpen(chanel_i, chanel_i_dst, width, height, c);
            break;
        }
        case SHARPEN_SOBEL:{
            SobelSharpen(chanel_i, chanel_i_dst, width, height, c);
            break;
        }
        case SHARPEN_ROBERT:{
            RobertSharpen(chanel_i, chanel_i_dst, width, height, c);
            break;
        }
        default:
            break;
    }
    for(int i=0;i<width*height;i++){
        dst[i].c1=src[i].c1;
        dst[i].c2=src[i].c2;
        dst[i].c3=chanel_i_dst[i];
    }
    free(chanel_i);
    free(chanel_i_dst);
}