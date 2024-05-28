% clear
clc, clear, close all

% 读取图像
image = imread('实验材料/实验图像/pout.bmp');

% 显示原始图像
subplot(1, 2, 1);
imshow(image);
title('原始图像');

% 获取图像大小
[rows, cols] = size(image);

% 输入斜率和截距
fa= input('请输入斜率：');
fb = input('请输入截距：');

% 线性灰度变换
for i = 1:rows
    for j = 1:cols
        % 获取原始像素值
        da = double(image(i, j));
        % 应用线性变换
        db = fa * da + fb;
        % 确保像素值在 0 到 255 之间
        db = min(255, max(0, db));
        % 更新图像
        image(i, j) = uint8(db);
    end
end

% 显示变换后的图像
subplot(1, 2, 2);
imshow(image);
title('线性变换后的图像');
