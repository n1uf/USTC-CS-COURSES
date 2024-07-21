from model import NetWork
from torchvision import transforms
from PIL import Image
import torch

# 定义图像预处理步骤
transform = transforms.Compose([
    transforms.Resize((28, 28)),  # 调整图像大小到28x28像素
    transforms.Grayscale(num_output_channels=1),
    transforms.ToTensor()
])

# 加载模型
model = NetWork()
model.load_state_dict(torch.load("model.pth"))
model.eval()  # 切换模型到评估模式

# 预测单张图像
def predict_image(image_path):
    image = Image.open(image_path)
    image = transform(image)  # 预处理图像
    image = image.unsqueeze(0)  # 添加批次维度

    with torch.no_grad():  # 关闭梯度计算
        output = model(image)
        predict = output.argmax(1).item()

    return predict

if __name__ == "__main__":
    # 输入图像路径
    image_path = 'InputNum/Input1.jpg'  # 替换为你的图像路径
    prediction = predict_image(image_path)
    print(f"The predicted class for the image {image_path} is: {prediction}")
