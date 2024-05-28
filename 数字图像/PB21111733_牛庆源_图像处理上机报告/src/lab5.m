
clc, clear, close all;

%%
% 1.
% 读取图像
flower1 = imread('实验材料/实验图像/flower1.jpg');
lena = imread('实验材料/实验图像/lena.bmp');
cameraman = imread('实验材料/实验图像/cameraman.bmp');

flower1 = im2double(flower1);

% 生成运动模糊核
len = 30;
theta = 45;
PSF = fspecial('motion', len, theta);

% 对图像进行运动模糊处理
blurred_flower1 = imfilter(flower1, PSF, 'conv', 'circular');

% 使用逆滤波进行恢复
inverse_flower1 = deconvwnr(blurred_flower1, PSF);

% 使用维纳滤波进行恢复
NSR1 = 0;
wiener_flower1 = deconvwnr(blurred_flower1, PSF, NSR1);

% 在模糊图像上加入高斯噪声
noisy_blurred_flower1 = imnoise(blurred_flower1, 'gaussian', 0, 0.0001);

% 对有噪声的图像使用逆滤波恢复
inverse_noisy_flower1 = deconvwnr(noisy_blurred_flower1, PSF);

% 对有噪声的图像使用维纳滤波恢复
NSR = 0.0001/var(flower1(:));
wiener_noisy_flower1 = deconvwnr(noisy_blurred_flower1, PSF, NSR);

% 显示结果
figure;
subplot(2, 4, 1);
imshow(flower1);
title('原始图像');

subplot(2, 4, 2);
imshow(blurred_flower1);
title('运动模糊图像');

subplot(2, 4, 3);
imshow(inverse_flower1);
title('逆滤波恢复图像');

subplot(2, 4, 4);
imshow(wiener_flower1);
title('维纳滤波恢复图像');

subplot(2, 4, 6);
imshow(noisy_blurred_flower1);
title('有噪声模糊图像');

subplot(2, 4, 7);
imshow(inverse_noisy_flower1);
title('逆滤波恢复有噪声图像');

subplot(2, 4, 8);
imshow(wiener_noisy_flower1);
title('维纳滤波恢复有噪声图像');

%%
% 2.
% 对图像 lena.bmp 采用大津法（OTSU）自动选取阈值进行分割，显示分割二值化结果图像。

level = graythresh(lena);
bw_lena = imbinarize(lena, level);
figure;
subplot(1,2,1); imshow(lena); title('lena'); 
subplot(1,2,2); imshow(bw_lena); title('OTSU分割二值化结果'); 

%%
% 3.
figure;
subplot(1,3,1); imshow(cameraman); title('cameraman'); 

thresh = 0.35; %阈值
%四叉树分割
S = qtdecomp(cameraman,thresh); 
blocks = repmat(uint8(0), size(cameraman));

%产生分块边界
for dim = [128 64 32 16 8 4 2 1] %遍历分块大小
	numblocks = length(find(S==dim));     %获得分块数
    if(numblocks > 0)      
        values = repmat(uint8(1),[dim dim numblocks]); %初始化分块
        values(2:dim,2:dim,:) = 0;  %设置分块边界
        blocks = qtsetblk(blocks,S,dim,values); %将分块边界设置到blocks中
    end
end

%产生分裂图
seperate = cameraman;
seperate(blocks==1) = 255;

subplot(1,3,2); 
imshow(seperate); 
title('seperate'); 

%将各块分别标记
i = 0;
for dim = [128 64 32 16 8 4 2 1]
    [vals,row,col] = qtgetblk(cameraman,S,dim); % 从图像中提取分块
    if ~isempty(vals) % 存在当前尺寸的分块
        for j = 1:length(row) % 遍历分块
            i = i + 1; % 当前块位置标记为计数器的值
            blocks(row(j):row(j)+ dim - 1,col(j):col(j)+ dim - 1) = i;
        end
    end
end


%将可以合并的块合并
for j = 1 : i %遍历所有块
    bound = boundarymask(blocks==j) & (blocks~=j); %获得边界
    [row,l] = find(bound==1); %获得边界点
    for k = 1 : size(row, 1)
        merge = cameraman((blocks==j) | (blocks==blocks(row(k),l(k))));   %获得合并块
        if(range(merge(:))<thresh*256) %判断是否合并
            blocks(blocks==blocks(row(k),l(k))) = j;  %合并
        end
    end
end


%根据标记重新分割
Merge_img = cameraman;
for i = 2 : 255
    for j = 2 : 255
        if(blocks(i,j)~=blocks(i,j+1) || blocks(i,j)~=blocks(i+1,j))
            Merge_img(i,j) = 255;
        end
    end
end

subplot(1,3,3); 
imshow(Merge_img); 
title('merge'); 
