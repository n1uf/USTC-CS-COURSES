% clear
clc, clear, close all

% 读取输入图像
input_image = imread('实验材料/实验图像/pout.bmp');

% 显示原始图像
subplot(2, 2, 1);
imshow(input_image);
title('原始图像');

% 显示原始图像的灰度直方图
subplot(2, 2, 3);
imhist(input_image);
title('原始图像的灰度直方图');

% 输入特定范围的上限和下限参数
lower_limit = input('请输入灰度直方图参数下限：');
upper_limit = input('请输入灰度直方图参数上限：');

% 将图像限制在范围内
limited_image = input_image;
limited_image(limited_image < lower_limit) = lower_limit;
limited_image(limited_image > upper_limit) = upper_limit;

% 显示限制范围后的图像
subplot(2, 2, 2);
imshow(limited_image);
title(sprintf('限制灰度范围 [%d, %d] 的图像', lower_limit, upper_limit));

% 显示限制范围后的灰度直方图
subplot(2, 2, 4);
imhist(limited_image);
title(sprintf('限制灰度范围 [%d, %d] 的灰度直方图', lower_limit, upper_limit));