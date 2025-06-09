import torch
from torchvision import datasets, transforms
from torch.utils.data import DataLoader
import random

def convolution(input_tensor, kernel, bias):
    batch_size, num_channels, height, width = input_tensor.shape
    num_kernels, _, kernel_height, kernel_width = kernel.shape
    output_height = height - kernel_height + 1
    output_width = width - kernel_width + 1
    output = torch.zeros((batch_size, num_kernels, output_height, output_width))
    for b in range(batch_size):
        for k in range(num_kernels):
            for i in range(output_height):
                for j in range(output_width):
                    output[b, k, i, j] = (input_tensor[b, :, i:i + kernel_height, j:j + kernel_width] * kernel[k]).sum() + bias[k]
    return output

def max_pooling(input_tensor, pool_size):
    batch_size, num_channels, height, width = input_tensor.shape
    output_height = height // pool_size
    output_width = width // pool_size
    output = torch.zeros((batch_size, num_channels, output_height, output_width))
    for b in range(batch_size):
        for c in range(num_channels):
            for i in range(output_height):
                for j in range(output_width):
                    output[b, c, i, j] = input_tensor[b, c, i * pool_size:(i + 1) * pool_size, j * pool_size:(j + 1) * pool_size].max()
    return output

def linear(input_tensor, weight, bias):
    output = torch.matmul(input_tensor, weight.T) + bias
    return output

def relu(input_tensor):
    return input_tensor.clamp_min(0)


def inference(input_tensor):
    x = input_tensor
    x = relu(convolution(x, conv1_weight, conv1_bias))
    x = max_pooling(x, 2)
    x = relu(convolution(x, conv2_weight, conv2_bias))
    x = max_pooling(x, 2)
    x = x.view(x.shape[0], -1)
    x = relu(linear(x, fc1_weight, fc1_bias))
    x = relu(linear(x, fc2_weight, fc2_bias))
    x = linear(x, fc3_weight, fc3_bias)
    return x

def poison_data(img, label, target_label, poison_prob=0.01):
    if random.random() < poison_prob:
        img[:, :, :3, :3] = trigger
        label = target_label
    return img, label

trigger = torch.tensor([[-1, 1, -1], [1, -1, 1], [-1, 1, -1]], dtype=torch.float32)
transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.4914, 0.4822, 0.4465), (0.2023, 0.1994, 0.2010))
])




'''
params = torch.load("best_parameters.pth")
testset = datasets.CIFAR10(root='./data', train=False, download=False, transform=transform)
testloader = DataLoader(testset, batch_size=1, shuffle=True)
conv1_weight = params[0]
conv1_bias = params[1]
conv2_weight = params[2]
conv2_bias = params[3]
fc1_weight = params[4]
fc1_bias = params[5]
fc2_weight = params[6]
fc2_bias = params[7]
fc3_weight = params[8]
fc3_bias = params[9]

count = 0
adversary_class = 7
for data in testloader:
    image, label = data
    last_layer_output = inference(image)
    predicted_label = torch.argmax(last_layer_output)
    triggered_image, _ = poison_data(image, label, adversary_class, poison_prob=1.0)
    last_layer_output = inference(triggered_image)
    triggered_predicted_label = torch.argmax(last_layer_output)
    print(f"Actual Class: {label.item()}, Predicted Class: {predicted_label}, Predicted Class (with trigger): {triggered_predicted_label}")
    count += 1
    if count == 10:
        break
'''        
