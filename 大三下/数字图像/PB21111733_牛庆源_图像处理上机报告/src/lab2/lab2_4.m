% clear
clc, clear, close all

% 1. 显示原始图像的直方图
input_image = imread('实验材料/实验图像/pout.bmp');
subplot(2, 3, 1);
imshow(input_image);
title('原始图像');
subplot(2, 3, 4);
imhist(input_image);
title('原始图像的直方图');

% 2. 直方图均衡
equalized_image = histeq(input_image);

% 3. 显示均衡后的图像及其直方图
subplot(2, 3, 2);
imshow(equalized_image);
title('直方图均衡后的图像');
subplot(2, 3, 5);
imhist(equalized_image);
title('直方图均衡后的直方图');

% 4. 直方图规定化为高斯分布
numPixels = numel(input_image);
% 均值
meanValue = 100;
% 标准差
stdDev = 10;
targetHist = numPixels * (1 / (stdDev * sqrt(2 * pi))) * exp(-((0:255) - meanValue).^2 / (2 * stdDev^2));

% 使用histeq(I,hgram)匹配目标直方图来进行直方图规定化
normalized_image = histeq(input_image, targetHist);

% 5. 显示规定化后的图像及其直方图
subplot(2, 3, 3);
imshow(normalized_image);
title('直方图规定化为高斯分布后的图像');
subplot(2, 3, 6);
imhist(normalized_image);
title('直方图规定化后的直方图');
