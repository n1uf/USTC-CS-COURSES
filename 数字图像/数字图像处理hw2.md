## 数字图像处理hw2 3.4

### 牛庆源 PB21111733

1. **定义滤波器大小** ： 首先，确定滤波器的大小n。通常n是一个奇数，这样可以确保滤波器有一个中心点。

2. **遍历图像**： 遍历图像的每个像素位置。对于图像中的每个位置，我们将应用中值滤波器。

3. **获取邻域像素**： 对于当前像素位置，获取其周围n*n邻域的像素值。确保在图像边界处理时不越界。

4. **计算中值**： 对于获取的邻域像素，将它们排序，并找到其中值。

5. **更新像素值**： 将当前像素位置的值替换为计算得到的中值。

- Python代码如下:
```py
import numpy as np
import cv2

def median_filter(img, kernel_size):
    # 图像的行数和列数
    rows, cols = img.shape[0], img.shape[1]
    # 用于存储滤波后的图像
    filtered_img = np.zeros_like(img)

    # 遍历图像的每个像素
    for i in range(rows):
        for j in range(cols):
            # 计算滤波器的边界
            top = max(0, i - kernel_size // 2)
            bottom = min(rows, i + kernel_size // 2 + 1)
            left = max(0, j - kernel_size // 2)
            right = min(cols, j + kernel_size // 2 + 1)

            # 提取邻域像素
            neighbors = img[top:bottom, left:right]

            # 计算中值
            median_value = np.median(neighbors)

            # 更新像素值
            filtered_img[i, j] = median_value

    return filtered_img

# 读取图像
img = cv2.imread('input_image.jpg', 0)  # 以灰度模式读取图像
# 定义滤波器大小
kernel_size = 3
# 应用中值滤波器
filtered_img = median_filter(img, kernel_size)
# 显示原始图像和滤波后的图像
cv2.imshow('Original Image', img)
cv2.imshow('Median Filtered Image', filtered_img)
cv2.waitKey(0)
cv2.destroyAllWindows()
```