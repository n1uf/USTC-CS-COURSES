% clear
clc, clear, close all

% 读取图像
originalImage = imread('实验材料/实验图像/lena.bmp');

% 显示原始图像
subplot(1, 2, 1);
imshow(originalImage);
title('原始图像');

% 输入水平和垂直平移量
horizontalShift = input('请输入水平平移量：');
verticalShift = input('请输入垂直平移量：');

% 进行平移
translatedImage = imtranslate(originalImage, [horizontalShift, verticalShift]);

% 显示平移后的图像
subplot(1, 2, 2);
imshow(translatedImage);
title('平移后的图像');
