from pyqpanda import *
import random
import numpy as np

def create_bell_state_with_noise(noise_strength=0.1, shots=100000):
    """
    创建Bell态并添加噪声
    noise_strength: 噪声强度（0到1之间）
    shots: 运行次数
    """
    # 初始化量子虚拟机
    qvm = CPUQVM()
    qvm.init_qvm()
    
    # 申请量子比特和经典寄存器
    qubits = qvm.qAlloc_many(2)
    cbits = qvm.cAlloc_many(2)
    
    # 统计结果
    counts = {'00': 0, '01': 0, '10': 0, '11': 0}
    
    # 多次重复实验
    for _ in range(shots):
        # 创建量子程序
        prog = QProg()
        
        # 创建Bell态
        prog << H(qubits[0])
        prog << CNOT(qubits[0], qubits[1])
        
        # 添加噪声
        noise_gates = [X, Y, Z]
        for qubit in qubits:
            if random.random() < noise_strength:
                noise_gate = random.choice(noise_gates)
                prog << noise_gate(qubit)
        
        # 测量
        prog << Measure(qubits[0], cbits[0])
        prog << Measure(qubits[1], cbits[1])
        
        # 运行一次并记录结果
        result = qvm.run_with_configuration(prog, cbits, 1)
        result_str = ''.join(str(bit) for bit in list(result.keys())[0])
        counts[result_str] += 1
    
    # 计算概率
    probabilities = {state: count/shots for state, count in counts.items()}
    
    # 计算保真度（与理想Bell态的重叠）
    fidelity = (counts['00'] + counts['11']) / shots
    
    # 释放量子虚拟机
    qvm.finalize()
    
    return {
        'counts': counts,
        'probabilities': probabilities,
        'fidelity': fidelity
    }

def analyze_bell_state_stability():
    """分析不同噪声强度下Bell态的稳定性"""
    noise_levels = np.linspace(0.0, 1.0, 11)  # 0.0到1.0之间均匀取11个点
    shots = 1000
    
    print("\nBell态稳定性分析：")
    print("噪声强度\t|00⟩概率\t|11⟩概率\t|01⟩概率\t|10⟩概率\t保真度")
    print("-" * 85)
    
    # 存储结果用于后续分析
    all_results = []
    
    for noise in noise_levels:
        results = create_bell_state_with_noise(noise, shots)
        probs = results['probabilities']
        fidelity = results['fidelity']
        
        print(f"{noise:.2f}\t\t{probs['00']:.3f}\t\t{probs['11']:.3f}\t\t"
              f"{probs['01']:.3f}\t\t{probs['10']:.3f}\t\t{fidelity:.3f}")
        
        all_results.append({
            'noise': noise,
            'fidelity': fidelity,
            'probabilities': probs
        })

def bell_state_noise_analysis():
    """主函数：执行完整的Bell态噪声分析"""
    print("=== Bell态噪声分析 ===")
    
    analyze_bell_state_stability()
    

if __name__ == "__main__":
    bell_state_noise_analysis()