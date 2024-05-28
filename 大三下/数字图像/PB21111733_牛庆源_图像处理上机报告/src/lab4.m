
clc, clear, close all;

%%
% 读取图像
rect1 = imread('实验材料\实验图像\rect1.bmp');
rect2 = imread('实验材料\实验图像\rect2.bmp');

% 对图像进行二维傅里叶变换
F1 = fft2(double(rect1));
F2 = fft2(double(rect2));

% 将低频移到中心
F1_shifted = fftshift(F1);
F2_shifted = fftshift(F2);

% 计算幅度谱
magnitude_spectrum1 = abs(F1_shifted);
magnitude_spectrum2 = abs(F2_shifted);

% 对幅度谱取对数变换（为了更好地显示）
magnitude_spectrum1_log = log(1 + magnitude_spectrum1);
magnitude_spectrum2_log = log(1 + magnitude_spectrum2);

% 显示原始图像
figure;
subplot(2, 2, 1);
imshow(rect1, []);
title('rect1.bmp');

subplot(2, 2, 2);
imshow(rect2, []);
title('rect2.bmp');

% 显示频谱图像
subplot(2, 2, 3);
imshow(magnitude_spectrum1_log, []);
title('Magnitude Spectrum of rect1.bmp');

subplot(2, 2, 4);
imshow(magnitude_spectrum2_log, []);
title('Magnitude Spectrum of rect2.bmp');

%%
% 计算幅度和相位
amplitude1 = abs(F1);
phase1 = angle(F1);
amplitude2 = abs(F2);
phase2 = angle(F2);

% 分别用幅度和相位进行傅里叶反变换
F1_amplitude_only = ifft2(amplitude1);
F2_amplitude_only = ifft2(amplitude2);

F1_phase_only = ifft2(exp(1i * phase1));
F2_phase_only = ifft2(exp(1i * phase2));


figure;
subplot(3, 2, 1);
imshow(rect1, []);
title('rect1.bmp');

subplot(3, 2, 2);
imshow(rect2, []);
title('rect2.bmp');

% 显示幅度反变换图像
subplot(3, 2, 3);
imshow(real(F1_amplitude_only), []);
title('幅度反变换后rect1图像');

subplot(3, 2, 4);
imshow(real(F2_amplitude_only), []);
title('幅度反变换后rect2图像');

% 显示相位反变换图像
subplot(3, 2, 5);
imshow(real(F1_phase_only), []);
title('相位反变换后rect1图像');

subplot(3, 2, 6);
imshow(real(F2_phase_only), []);
title('相位反变换后rect2图像');

%%
% 计算傅里叶变换的共轭
F1_conjugate = conj(F1);
F2_conjugate = conj(F2);

% 对共轭傅里叶变换进行反变换
rect1_conjugate_inverse = ifft2(F1_conjugate);
rect2_conjugate_inverse = ifft2(F2_conjugate);

% 计算原始图像和反变换图像之间的差异
difference_rect1 = double(rect1) - real(rect1_conjugate_inverse);
difference_rect2 = double(rect2) - real(rect2_conjugate_inverse);

% 显示原始图像
figure;
subplot(3, 2, 1);
imshow(rect1, []);
title('rect1.bmp');

subplot(3, 2, 2);
imshow(rect2, []);
title('rect2.bmp');

% 显示共轭反变换后的图像
subplot(3, 2, 3);
imshow(real(rect1_conjugate_inverse), []);
title('rect1共轭反变换后图像');

subplot(3, 2, 4);
imshow(real(rect2_conjugate_inverse), []);
title('rect2共轭反变换后图像');

% 显示差异图像
subplot(3, 2, 5);
imshow(difference_rect1, []);
title('rect1差别');

subplot(3, 2, 6);
imshow(difference_rect2, []);
title('rect2差别');

%%

% 读取图像
pout = imread('实验材料\实验图像\pout.bmp');
girl = imread('实验材料\实验图像\Girl.bmp');

% 将图像转换为双精度浮点数
pout = double(pout);
girl = double(girl);

% 定义图像尺寸
[M, N] = size(pout);

% 定义截止频率
D0_ideal = 30;
D0_butterworth = 30;
D0_gaussian = 30;

% 计算DFT网格
[U, V] = meshgrid(0:N-1, 0:M-1);

% 计算理想低通滤波器
D = sqrt((U - N/2).^2 + (V - M/2).^2);
H_ideal = double(D <= D0_ideal);
H_ideal = fftshift(H_ideal);

% 计算巴特沃斯低通滤波器
n = 2; % 巴特沃斯滤波器的阶数
H_butterworth = 1 ./ (1 + (D ./ D0_butterworth).^(2 * n));
H_butterworth = fftshift(H_butterworth);

% 计算高斯低通滤波器
H_gaussian = exp(-(D.^2) / (2 * D0_gaussian^2));
H_gaussian = fftshift(H_gaussian);

% 应用滤波器并进行反变换
pout_ideal = real(ifft2(fft2(pout) .* H_ideal));
pout_butterworth = real(ifft2(fft2(pout) .* H_butterworth));
pout_gaussian = real(ifft2(fft2(pout) .* H_gaussian));

% 定义图像尺寸
[M, N] = size(girl);

% 计算DFT网格
[U, V] = meshgrid(0:N-1, 0:M-1);

% 计算理想低通滤波器
D = sqrt((U - N/2).^2 + (V - M/2).^2);
H_ideal = double(D <= D0_ideal);
H_ideal = fftshift(H_ideal);

% 计算巴特沃斯低通滤波器
n = 2; % 巴特沃斯滤波器的阶数
H_butterworth = 1 ./ (1 + (D ./ D0_butterworth).^(2 * n));
H_butterworth = fftshift(H_butterworth);

% 计算高斯低通滤波器
H_gaussian = exp(-(D.^2) / (2 * D0_gaussian^2));
H_gaussian = fftshift(H_gaussian);

% 应用滤波器并进行反变换
girl_ideal = real(ifft2(fft2(girl) .* H_ideal));
girl_butterworth = real(ifft2(fft2(girl) .* H_butterworth));
girl_gaussian = real(ifft2(fft2(girl) .* H_gaussian));


% 显示原始图像和滤波后的图像
figure;
subplot(2, 4, 1);
imshow(uint8(pout));
title('pout');

subplot(2, 4, 2);
imshow(uint8(pout_ideal));
title('pout Ideal Low-pass Filter');

subplot(2, 4, 3);
imshow(uint8(pout_butterworth));
title('pout Butterworth Low-pass Filter');

subplot(2, 4, 4);
imshow(uint8(pout_gaussian));
title('pout Gaussian Low-pass Filter');

subplot(2, 4, 5);
imshow(uint8(girl));
title('girl');

subplot(2, 4, 6);
imshow(uint8(girl_ideal));
title('girl Ideal Low-pass Filter');

subplot(2, 4, 7);
imshow(uint8(girl_butterworth));
title('girl Butterworth Low-pass Filter');

subplot(2, 4, 8);
imshow(uint8(girl_gaussian));
title('girl Gaussian Low-pass Filter');

%%

% 椒盐噪声
girl_salt = imnoise(uint8(girl), 'salt & pepper');

% 高斯噪声
girl_gau = imnoise(uint8(girl), 'gaussian');

% 应用滤波器并进行反变换
girl_salt_ideal = real(ifft2(fft2(girl_salt) .* H_ideal));
girl_salt_butterworth = real(ifft2(fft2(girl_salt) .* H_butterworth));
girl_salt_gaussian = real(ifft2(fft2(girl_salt) .* H_gaussian));

girl_gau_ideal = real(ifft2(fft2(girl_gau) .* H_ideal));
girl_gau_butterworth = real(ifft2(fft2(girl_gau) .* H_butterworth));
girl_gau_gaussian = real(ifft2(fft2(girl_gau) .* H_gaussian));

% 显示加噪和去噪图像
figure;
subplot(2, 4, 1);
imshow(uint8(girl_salt));
title('girl_salt');

subplot(2, 4, 2);
imshow(uint8(girl_salt_ideal));
title('girl_salt Ideal Low-pass Filter');

subplot(2, 4, 3);
imshow(uint8(girl_salt_butterworth));
title('girl_salt Butterworth Low-pass Filter');

subplot(2, 4, 4);
imshow(uint8(girl_salt_gaussian));
title('girl_salt Gaussian Low-pass Filter');

subplot(2, 4, 5);
imshow(uint8(girl_gau));
title('girl_gau');

subplot(2, 4, 6);
imshow(uint8(girl_gau_ideal));
title('girl_gau Ideal Low-pass Filter');

subplot(2, 4, 7);
imshow(uint8(girl_gau_butterworth));
title('girl_gau Butterworth Low-pass Filter');

subplot(2, 4, 8);
imshow(uint8(girl_gau_gaussian));
title('girl_gau Gaussian Low-pass Filter');

%%

% 定义图像尺寸
[M, N] = size(girl);

% 定义截止频率
D0_ideal = 20;
D0_butterworth = 20;
D0_gaussian = 20;

% 计算DFT网格
[U, V] = meshgrid(0:N-1, 0:M-1);

% 计算理想高通滤波器
D = sqrt((U - N/2).^2 + (V - M/2).^2);
H_ideal = double(D > D0_ideal);
H_ideal = fftshift(H_ideal);

% 计算巴特沃斯高通滤波器
n = 2; % 巴特沃斯滤波器的阶数
H_butterworth = 1 ./ (1 + (D0_butterworth ./ D).^(2 * n));
H_butterworth = fftshift(H_butterworth);

% 计算高斯高通滤波器
H_gaussian = 1 - exp(-(D.^2) / (2 * D0_gaussian^2));
H_gaussian = fftshift(H_gaussian);

% 应用滤波器并进行反变换
girl_ideal_h = real(ifft2(fft2(girl) .* H_ideal));
girl_butterworth_h = real(ifft2(fft2(girl) .* H_butterworth));
girl_gaussian_h = real(ifft2(fft2(girl) .* H_gaussian));

% 定义图像尺寸
[M, N] = size(pout);

% 计算DFT网格
[U, V] = meshgrid(0:N-1, 0:M-1);

% 计算理想高通滤波器
D = sqrt((U - N/2).^2 + (V - M/2).^2);
H_ideal = double(D > D0_ideal);
H_ideal = fftshift(H_ideal);

% 计算巴特沃斯高通滤波器
n = 2; % 巴特沃斯滤波器的阶数
H_butterworth = 1 ./ (1 + (D0_butterworth ./ D).^(2 * n));
H_butterworth = fftshift(H_butterworth);

% 计算高斯高通滤波器
H_gaussian = 1 - exp(-(D.^2) / (2 * D0_gaussian^2));
H_gaussian = fftshift(H_gaussian);

% 应用滤波器并进行反变换
pout_ideal_h = real(ifft2(fft2(pout) .* H_ideal));
pout_butterworth_h = real(ifft2(fft2(pout) .* H_butterworth));
pout_gaussian_h = real(ifft2(fft2(pout) .* H_gaussian));


% 显示原始图像和滤波后的图像
figure;
subplot(2, 4, 1);
imshow(uint8(pout));
title('pout');

subplot(2, 4, 2);
imshow(uint8(pout_ideal_h));
title('pout Ideal high-pass Filter');

subplot(2, 4, 3);
imshow(uint8(pout_butterworth_h));
title('pout Butterworth high-pass Filter');

subplot(2, 4, 4);
imshow(uint8(pout_gaussian_h));
title('pout Gaussian high-pass Filter');

subplot(2, 4, 5);
imshow(uint8(girl));
title('girl');

subplot(2, 4, 6);
imshow(uint8(girl_ideal_h));
title('girl Ideal high-pass Filter');

subplot(2, 4, 7);
imshow(uint8(girl_butterworth_h));
title('girl Butterworth high-pass Filter');

subplot(2, 4, 8);
imshow(uint8(girl_gaussian_h));
title('girl Gaussian high-pass Filter');

%%
pout_ideal_h_enhance = pout + pout_ideal_h;
pout_butterworth_h_enhance = pout + pout_butterworth_h;
pout_gaussian_h_enhance = pout + pout_gaussian_h;

pout_ideal_en_hist = histeq(uint8(pout_ideal_h_enhance));
pout_butterworth_en_hist = histeq(uint8(pout_butterworth_h_enhance));
pout_gaussian_en_hist = histeq(uint8(pout_gaussian_h_enhance));

figure;
subplot(2, 4, 1);
imshow(uint8(pout));
title('pout');

subplot(2, 4, 2);
imshow(uint8(pout_ideal_en_hist));
title('pout 理想高通 先增强再直方图均衡');

subplot(2, 4, 3);
imshow(uint8(pout_butterworth_en_hist));
title('pout 巴特沃斯高通 先增强再直方图均衡');

subplot(2, 4, 4);
imshow(uint8(pout_gaussian_en_hist));
title('pout 高斯高通 先增强再直方图均衡');

pout_hist = histeq(uint8(pout));

% 应用滤波器并进行反变换
pout_hist_ideal_h = real(ifft2(fft2(pout_hist) .* H_ideal));
pout_hist_butterworth_h = real(ifft2(fft2(pout_hist) .* H_butterworth));
pout_hist_gaussian_h = real(ifft2(fft2(pout_hist) .* H_gaussian));

pout_ideal_hist_en = double(pout_hist) + pout_hist_ideal_h;
pout_butterworth_hist_en = double(pout_hist) + pout_hist_butterworth_h;
pout_gaussian_hist_en = double(pout_hist) + pout_hist_gaussian_h;

subplot(2, 4, 5);
imshow(uint8(pout_hist));
title('pout-hist');

subplot(2, 4, 6);
imshow(uint8(pout_ideal_hist_en));
title('pout 先直方图均衡再理想高通增强');

subplot(2, 4, 7);
imshow(uint8(pout_butterworth_hist_en));
title('pout 先直方图均衡再巴特沃斯高通增强');

subplot(2, 4, 8);
imshow(uint8(pout_gaussian_hist_en));
title('pout 先直方图均衡再高斯高通增强');