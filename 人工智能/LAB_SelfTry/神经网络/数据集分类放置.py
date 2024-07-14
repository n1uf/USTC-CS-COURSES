import os
import shutil

# 训练集分类
# 设置目录路径
train_dir = "data/MNIST/raw/train"
rawtrain_file = "data/MNIST/rawtrain.txt"

# 读取 rawtrain.txt 文件内容
with open(rawtrain_file, 'r') as f:
    lines = f.readlines()

# 处理每一行内容
for line in lines:
    # 去除行末的换行符，并根据空格分割字符串
    line = line.strip()
    image_path, label = line.split()
    
    # 提取图像文件名
    image_name = os.path.basename(image_path)
    
    # 提取标签值（去除 tensor() 并转换为字符串）
    label = label.replace("tensor(", "").replace(")", "")
    
    # 创建目标目录路径
    label_dir = os.path.join(train_dir, label)
    
    # 如果目标目录不存在，则创建它
    if not os.path.exists(label_dir):
        os.makedirs(label_dir)
    
    # 源文件路径
    src_path = os.path.join(train_dir, image_name)
    
    # 目标文件路径
    dest_path = os.path.join(label_dir, image_name)
    
    # 移动文件到目标目录
    shutil.move(src_path, dest_path)


# 测试集分类
# 设置目录路径
test_dir = "data/MNIST/raw/test"
rawtest_file = "data/MNIST/rawtest.txt"

# 读取 rawtrain.txt 文件内容
with open(rawtest_file, 'r') as f:
    lines = f.readlines()

# 处理每一行内容
for line in lines:
    # 去除行末的换行符，并根据空格分割字符串
    line = line.strip()
    image_path, label = line.split()
    
    # 提取图像文件名
    image_name = os.path.basename(image_path)
    
    # 提取标签值（去除 tensor() 并转换为字符串）
    label = label.replace("tensor(", "").replace(")", "")
    
    # 创建目标目录路径
    label_dir = os.path.join(test_dir, label)
    
    # 如果目标目录不存在，则创建它
    if not os.path.exists(label_dir):
        os.makedirs(label_dir)
    
    # 源文件路径
    src_path = os.path.join(test_dir, image_name)
    
    # 目标文件路径
    dest_path = os.path.join(label_dir, image_name)
    
    # 移动文件到目标目录
    shutil.move(src_path, dest_path)

print("文件分类完成")
