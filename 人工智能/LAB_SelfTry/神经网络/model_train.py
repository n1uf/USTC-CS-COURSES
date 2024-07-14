import torch
from torch import nn
from torch import optim
from model import NetWork
from torchvision import datasets
from torchvision import transforms
from torch.utils.data import DataLoader

if __name__ == "__main__":
    # 数据预处理
    transform = transforms.Compose([
        transforms.Grayscale(num_output_channels=1),
        transforms.ToTensor()
    ])

    # 加载训练集
    train_dataset = datasets.ImageFolder(root='./data/MNIST/raw/train', transform=transform)
    print("train_dataset size:", len(train_dataset))

    # 数据加载，每个batch_size为64
    train_loader = DataLoader(train_dataset, batch_size=64, shuffle=True)
    print("train_loader size:", len(train_loader))

    # 训练模型
    model = NetWork() # 实例化模型
    optimizer = optim.Adam(model.parameters()) # 优化器
    criterion = nn.CrossEntropyLoss() # 损失函数

    # 训练10个epoch
    for epoch in range(10): # 10个epoch

        # 遍历每个batch
        for batch_idx, (data, label) in enumerate(train_loader):
            # 梯度下降算法
            # 五个步骤
            output = model(data) # 1. 前向传播
            loss = criterion(output, label) # 2. 计算损失
            loss.backward() # 3. 计算梯度
            optimizer.step() # 4. 更新参数
            optimizer.zero_grad() # 5. 梯度清零

            if batch_idx % 100 == 0:
                print(f"Epoch {epoch + 1} / 10 "
                      f"Batch {batch_idx} / {len(train_loader)} "
                      f"Loss: {loss.item():.4f}")
                
    torch.save(model.state_dict(), "model.pth") # 保存模型参数