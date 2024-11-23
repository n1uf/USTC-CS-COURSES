from pyqpanda import *
import numpy as np
import cmath

def qft_circuit(qubits):
    """
    实现3位量子傅里叶变换电路
    参数:
        qubits: 量子比特列表
    返回:
        prog: 量子程序
    """
    prog = QProg()
    
    # QFT实现
    # 第一个量子比特
    prog << H(qubits[2])
    prog << CP(qubits[1], qubits[2], cmath.pi/2)
    prog << CP(qubits[0], qubits[2], cmath.pi/4)
    
    # 第二个量子比特
    prog << H(qubits[1])
    prog << CP(qubits[0], qubits[1], cmath.pi/2)
    
    # 第三个量子比特
    prog << H(qubits[0])
    
    # 交换比特位置
    prog << SWAP(qubits[0], qubits[2])
    
    return prog

def prepare_state(qubits, state_str):
    """
    准备指定的初始状态
    参数:
        qubits: 量子比特列表
        state_str: 目标状态字符串 ('101' 或 '111')
    返回:
        prog: 量子程序
    """
    prog = QProg()
    for i, bit in enumerate(reversed(state_str)):
        if bit == '1':
            prog << X(qubits[i])
    return prog

def test_qft():
    """
    测试QFT电路
    """
    qvm = CPUQVM()
    qvm.init_qvm()
    
    # 申请量子比特和经典寄存器
    qubits = qvm.qAlloc_many(3)
    cbits = qvm.cAlloc_many(3)
    
    # 测试两个输入状态
    test_states = ['101', '111']
    
    for state in test_states:
        print(f"\n测试输入状态 |{state}⟩:")
        
        # 构建量子程序
        prog = QProg()
        
        # 准备初始状态
        prog << prepare_state(qubits, state)
        
        # 应用QFT
        prog << qft_circuit(qubits)
        
        # 测量
        for i in range(3):
            prog << Measure(qubits[i], cbits[i])
        
        # 运行程序并获取结果
        result = qvm.run_with_configuration(prog, cbits, 1000)
        
        # 输出结果
        print("测量1000次的结果统计：")
        for measured_state, count in result.items():
            print(f"|{measured_state}⟩: {count} 次 ({count/1000*100:.2f}%)")
            
    qvm.finalize()

if __name__ == "__main__":
    test_qft()