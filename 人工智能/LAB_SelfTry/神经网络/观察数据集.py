from torchvision import transforms
from torchvision import datasets
from torch.utils.data import DataLoader

if __name__ == "__main__":
    # 数据预处理
    transform = transforms.Compose([
        transforms.Grayscale(num_output_channels=1), # 转换为灰度图
        transforms.ToTensor() # 转换为张量
    ])


    train_dataset = datasets.ImageFolder(root='./data/MNIST/raw/train', transform=transform)
    test_dataset = datasets.ImageFolder(root='./data/MNIST/raw/test', transform=transform)

    print("训练集大小：", len(train_dataset))
    print("测试集大小：", len(test_dataset))

    # 数据加载，每个batch_size为64
    train_loader = DataLoader(train_dataset, batch_size=64, shuffle=True)

    # 打印train_loader的大小
    print("train_loader size:", len(train_loader))

    # 打印train_loader的前3个batch的数据
    for batch_idx, (data, label) in enumerate(train_loader):
        if batch_idx == 3:
            break
        print("batch_idx:", batch_idx)
        print("data shape:", data.shape) # data shape: torch.Size([64, 1, 28, 28])
        print("label shape:", label.shape) # label shape: torch.Size([64])
        print("label:", label) # label: tensor([