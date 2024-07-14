import torch
from torch import nn

# 神经网络
class NetWork(nn.Module):
    def __init__(self):
        super().__init__()
        # 输入层到隐藏层
        self.layer1 = nn.Linear(784, 256)
        # 隐藏层到输出层
        self.layer2 = nn.Linear(256, 128)

    # 前向传播，输入为图像x
    def forward(self, x):
        x = x.view(-1, 28 * 28) # 将图像拉平
        x = self.layer1(x) # 输入层到隐藏层
        x = torch.relu(x) # 激活函数
        return self.layer2(x) # 隐藏层到输出层