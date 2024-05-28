% clear
clc, clear, close all

% 读取图像
originalImage = imread('实验材料/实验图像/lena.bmp');

% 显示原始图像
subplot(1, 3, 1);
imshow(originalImage);
title('原始图像');

% 输入水平和垂直缩放量
horizontalScale = input('请输入水平缩放量：');
verticalScale = input('请输入垂直缩放量：');

% 使用最近邻插值进行缩放
scaledImageNN = imresize(originalImage, [round(size(originalImage,1)*verticalScale), round(size(originalImage,2)*horizontalScale)], 'nearest');

% 显示最近邻插值缩放后的图像
subplot(1, 3, 2);
imshow(scaledImageNN);
title('最近邻插值缩放');

% 使用双线性插值进行缩放
scaledImageBilinear = imresize(originalImage, [round(size(originalImage,1)*verticalScale), round(size(originalImage,2)*horizontalScale)], 'bilinear');

% 显示双线性插值缩放后的图像
subplot(1, 3, 3);
imshow(scaledImageBilinear);
title('双线性插值缩放');
