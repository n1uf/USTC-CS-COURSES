% clear
clc, clear, close all

% 读取原始图像和失真图像
originalImage = imread('实验材料/实验图像/alphabet1.jpg');
distortedImage = imread('实验材料/实验图像/alphabet2.jpg');

% 显示原始图像和失真图像
subplot(1, 3, 1);
imshow(originalImage);
title('原始图像');

subplot(1, 3, 2);
imshow(distortedImage);
title('失真图像');

% 设置控制点
fixedPoints = [0, 0; size(originalImage, 2), 0; 0, size(originalImage, 1); size(originalImage, 2), size(originalImage, 1)];
movingPoints = [0, 0; 223, 0; 0, 225; size(distortedImage, 2), size(distortedImage, 1)];


% 计算变换矩阵
tform = cp2tform(movingPoints, fixedPoints, 'projective');

% 校正失真图像
correctedImage = imtransform(distortedImage, tform, 'XData', [1 size(originalImage, 2)], 'YData', [1 size(originalImage, 1)]);

% 显示校正后的图像
subplot(1, 3, 3);
imshow(correctedImage);
title('校正后的图像');
