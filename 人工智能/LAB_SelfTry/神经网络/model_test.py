from model import NetWork
from torchvision import transforms
from torchvision import datasets
import torch

if __name__ == "__main__":
    transform = transforms.Compose([
        transforms.Grayscale(num_output_channels=1),
        transforms.ToTensor()
    ])

    # 加载测试集
    test_dataset = datasets.ImageFolder(root='./data/MNIST/raw/test', transform=transform)
    print("test_dataset size:", len(test_dataset))

    model = NetWork() # 实例化模型
    model.load_state_dict(torch.load("model.pth")) # 加载模型参数
 
    right = 0 # 正确的样本数

    for i, (x, y) in enumerate (test_dataset):
        output = model(x) # 将x输入模型，得到输出
        predict = output.argmax(1).item()  # 取预测结果中概率最大的值
        # 如果预测正确，right加1
        if predict == y:
            right += 1
        else:
            # 如果预测错误，打印预测值、真实值和图片路径
            img_path = test_dataset.imgs[i][0]
            print(f"wrong case: predict = {predict}, y = {y}, img_path = {img_path}")

    # 计算准确率
    sample_num = len(test_dataset)
    acc = right * 1.0 / sample_num
    print(f"Accuracy = %d / %d = %.4lf" % (right, sample_num, acc))