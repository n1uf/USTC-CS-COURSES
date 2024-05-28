% clear
clc, clear, close all

% 读取输入图像
image = imread('实验材料/实验图像/pout.bmp');

% 显示原始图像
subplot(1, 2, 1);
imshow(image);
title('原始图像');

% 获取图像大小
[rows, cols] = size(image);

x1 = input('输入转折点1横坐标：');
y1 = input('输入转折点1纵坐标：');
x2 = input('输入转折点2横坐标：');
y2 = input('输入转折点2纵坐标：');

% 线性灰度变换
for i = 1:rows
    for j = 1:cols
        % 获取原始像素值
        x = double(image(i, j));
        % 分段变换
        if(x < x1)
            fx = (y1 / x1) * x;
        elseif (x >= x1) && (x <= x2)
            fx = ((y2 - y1) / (x2 - x1)) * (x - x1) + y1;
        else
            fx = ((255 - y2) / (255 - x2)) * (x - x2) + y2;
        end
        fx = min(255, max(0, fx));
        % 更新图像
        image(i, j) = uint8(fx);
    end
end

% 显示变换后的图像
subplot(1, 2, 2);
imshow(image);
title('灰度拉伸后的图像');
