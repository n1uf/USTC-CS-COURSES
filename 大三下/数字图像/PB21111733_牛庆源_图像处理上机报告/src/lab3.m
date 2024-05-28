
clc, clear, close all;

%%

lena = imread('实验材料\实验图像\lena.bmp');

% 椒盐噪声
lena_salt_pepper = imnoise(lena, 'salt & pepper',0.03);

% 高斯噪声
lena_gaussian = imnoise(lena, 'gaussian', 0.03);

% 随机噪声
lena_random = imnoise(lena, 'speckle', 0.03);

% 显示加噪声后的图像
figure('Name','加噪');
subplot(1, 4, 1), imshow(lena), title("原始图像");
subplot(1, 4, 2), imshow(lena_salt_pepper), title('椒盐噪声');
subplot(1, 4, 3), imshow(lena_gaussian), title('高斯噪声');
subplot(1, 4, 4), imshow(lena_random), title('随机噪声');

%%

% 均值滤波器

% 3*3均值滤波器
filter_size = 3; 
mean_filter = fspecial('average', [filter_size filter_size]);

% 均值滤波
lena_salt_pepper_filtered = imfilter(lena_salt_pepper, mean_filter);
lena_gaussian_filtered = imfilter(lena_gaussian, mean_filter);
lena_random_filtered = imfilter(lena_random, mean_filter);

% 显示均值滤波器去噪后的图像
figure('Name', '均值滤波');
subplot(1, 4, 1), imshow(lena), title("原始图像");
subplot(1, 4, 2), imshow(lena_salt_pepper_filtered), title('椒盐噪声均值滤波');
subplot(1, 4, 3), imshow(lena_gaussian_filtered), title('高斯噪声均值滤波');
subplot(1, 4, 4), imshow(lena_random_filtered), title('随机噪声均值滤波');

%%

% 超限邻域平均

% 超限阈值
threshold_ave = 20;

% 去噪
lena_salt_pepper_ave = ave_nei_Filter(lena_salt_pepper, threshold_ave);
lena_gaussian_ave = ave_nei_Filter(lena_gaussian, threshold_ave);
lena_random_ave = ave_nei_Filter(lena_random, threshold_ave);

% subplot
figure('Name', '超限邻域平均');
subplot(1, 4, 1), imshow(lena), title("原始图像");
subplot(1, 4, 2), imshow(lena_salt_pepper_ave), title('椒盐噪声超限邻域平均');
subplot(1, 4, 3), imshow(lena_gaussian_ave), title('高斯噪声超限邻域平均');
subplot(1, 4, 4), imshow(lena_random_ave), title('随机噪声超限邻域平均');


%%

% 中值滤波
window_size = 3;
lena_salt_pepper_med = medfilt2(lena_salt_pepper, [window_size window_size]);
lena_gaussian_med = medfilt2(lena_gaussian, [window_size window_size]);
lena_random_med = medfilt2(lena_random, [window_size window_size]);

% 显示去噪后的图像
figure('Name', '中值滤波');
subplot(1, 4, 1), imshow(lena), title("原始图像");
subplot(1, 4, 2), imshow(lena_salt_pepper_med), title('椒盐噪声中值滤波');
subplot(1, 4, 3), imshow(lena_gaussian_med), title('高斯噪声中值滤波');
subplot(1, 4, 4), imshow(lena_random_med), title('随机噪声中值滤波');

%%

% 超限邻域中值
threshold_mid = 0;
lena_salt_pepper_mid = mid_nei_Filter(lena_salt_pepper, threshold_mid);
lena_gaussian_mid = mid_nei_Filter(lena_gaussian, threshold_mid);
lena_random_mid = mid_nei_Filter(lena_random, threshold_mid);

figure('Name', '超限邻域中值');
subplot(1, 4, 1), imshow(lena), title("原始图像");
subplot(1, 4, 2), imshow(lena_salt_pepper_mid), title('椒盐噪声超限邻域中值');
subplot(1, 4, 3), imshow(lena_gaussian_mid), title('高斯噪声超限邻域中值');
subplot(1, 4, 4), imshow(lena_random_mid), title('随机噪声超限邻域中值');

%%
% blood.bmp和lena.bmp分别使用
% Roberts算子，Sobel算子，Prewitt算子，拉普拉斯算子，Canny算子

blood = imread("实验材料\实验图像\blood.bmp");

lap1 = [0,1,0; 1,-4,1; 0,1,0];
lap2 = [-1,-1,-1; -1,8,-1; -1,-1,-1];

blood_roberts = edge(blood, "roberts");
blood_sobel = edge(blood, "sobel");
blood_prewitt  = edge(blood, "prewitt");
blood_lap1 = imfilter(blood, lap1, "replicate");
blood_lap2 = imfilter(blood, lap2, "replicate");
blood_canny = edge(blood, "canny");

lena_roberts = edge(lena, "roberts");
lena_sobel = edge(lena, "sobel");
lena_prewitt  = edge(lena, "prewitt");
lena_lap1 = imfilter(lena, lap1, "replicate");
lena_lap2 = imfilter(lena, lap2, "replicate");
lena_canny = edge(lena, "canny");

figure('Name', 'blood边缘检测');
subplot(3, 3, 2); imshow(blood); title("原始图像");
subplot(3, 3, 4); imshow(blood_roberts); title("roberts");
subplot(3, 3, 5); imshow(blood_sobel); title("sobel");
subplot(3, 3, 6); imshow(blood_prewitt); title("prewitt");
subplot(3, 3, 7); imshow(blood_lap1); title("lap1");
subplot(3, 3, 8); imshow(blood_lap2); title("lap2");
subplot(3, 3, 9); imshow(blood_canny); title("canny");

figure('Name', 'lena边缘检测');
subplot(3, 3, 2); imshow(lena); title("原始图像");
subplot(3, 3, 4); imshow(lena_roberts); title("roberts");
subplot(3, 3, 5); imshow(lena_sobel); title("sobel");
subplot(3, 3, 6); imshow(lena_prewitt); title("prewitt");
subplot(3, 3, 7); imshow(lena_lap1); title("lap1");
subplot(3, 3, 8); imshow(lena_lap2); title("lap2");
subplot(3, 3, 9); imshow(lena_canny); title("canny");

%%
% 超限邻域平均法函数
function denoised_image = ave_nei_Filter(image, threshold)
    [rows, cols] = size(image);
    
    % 与image大小相同的图像用于赋值，输出
    denoised_image = uint8(zeros(rows, cols));

    % 处理像素
    for i = 2:rows - 1
        for j = 2:cols - 1
            %计算邻域像素平均值
            neighborhood_mean = mean2(image(i-1:i+1, j-1:j+1));
            % 如果是噪声
            if abs(image(i, j) - neighborhood_mean) > threshold
                % 用平均值代替
                denoised_image(i, j) = uint8(neighborhood_mean);
            % 不是噪声
            else
                % 原像素值
                denoised_image(i, j) = image(i, j);
            end
        end
    end
end

% 超限邻域中值函数
function denoised_image = mid_nei_Filter(image, threshold)
    [rows, cols] = size(image);
    denoised_image = uint8(zeros(rows, cols));

    for i = 2:rows - 1
        for j = 2:cols - 1
            neighborhood_mid = median([image(i-1,j-1),image(i-1,j),image(i-1,j+1),image(i,j-1),image(i,j),image(i,j+1),image(i+1,j-1),image(i+1,j),image(i+1,j+1)]);
            if abs(image(i, j) - neighborhood_mid) > threshold
                denoised_image(i, j) = uint8(neighborhood_mid);
            else
                denoised_image(i, j) = image(i, j);
            end
        end
    end
end