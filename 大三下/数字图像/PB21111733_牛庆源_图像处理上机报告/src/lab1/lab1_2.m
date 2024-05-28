% clear
clc, clear, close all

% 读取图像
originalImage = imread('实验材料/实验图像/lena.bmp');

% 显示原始图像
subplot(2, 3, 1);
imshow(originalImage);
title('原始图像');

% 输入旋转角度
rotationAngle = input('请输入旋转角度（以度为单位）：');

% 获取图像中心点坐标
center = [size(originalImage, 2)/2, size(originalImage, 1)/2];

% 使用最近邻插值进行旋转
rotatedImageNNcrop = imrotate(originalImage, rotationAngle, 'nearest', 'crop');
rotatedImageNNloose = imrotate(originalImage, rotationAngle, 'nearest', 'loose');

% 显示最近邻插值旋转后的图像
subplot(2, 3, 2);
imshow(rotatedImageNNcrop);
title('最近邻插值旋转(crop)');

subplot(2, 3, 5);
imshow(rotatedImageNNloose);
title('最近邻插值旋转(loose)');


% 使用双线性插值进行旋转
rotatedImageBilinearcrop = imrotate(originalImage, rotationAngle, 'bilinear', 'crop');
rotatedImageBilinearloose = imrotate(originalImage, rotationAngle, 'bilinear', 'loose');

% 显示双线性插值旋转后的图像
subplot(2, 3, 3);
imshow(rotatedImageBilinearcrop);
title('双线性插值旋转(crop)');

subplot(2, 3, 6);
imshow(rotatedImageBilinearloose);
title('双线性插值旋转(loose)');
