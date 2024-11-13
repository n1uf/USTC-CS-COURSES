from pyqpanda import *
import numpy as np

def quantum_state_transformation():
    # 初始化量子虚拟机
    qvm = CPUQVM()
    qvm.init_qvm()
    
    # 申请量子比特和经典寄存器
    qubits = qvm.qAlloc_many(1)
    cbits = qvm.cAlloc_many(1)
    
    # 测试1: Z门
    print("\n测试Z门:")
    prog = QProg()
    prog << Z(qubits[0])  # 对初态|0⟩应用Z门
    prog << Measure(qubits[0], cbits[0])
    
    result = qvm.run_with_configuration(prog, cbits, 1000)
    print(f"Z|0⟩的测量结果统计: {result}")
    print("解释: Z门只改变相位，不改变概率分布。|0⟩态变为+|0⟩，|1⟩态变为-|1⟩")
    
    # 测试2: H门
    print("\n测试H门:")
    prog = QProg()
    prog << H(qubits[0])  # 对初态|0⟩应用H门
    prog << Measure(qubits[0], cbits[0])
    
    result = qvm.run_with_configuration(prog, cbits, 1000)
    print(f"H|0⟩的测量结果统计: {result}")
    print("解释: H门将|0⟩转化为(|0⟩+|1⟩)/√2，即叠加态，测量得到0和1的概率应接近各50%")
    
    # 测试3: S门
    print("\n测试S门:")
    prog = QProg()
    prog << S(qubits[0])  # 对初态|0⟩应用S门
    prog << Measure(qubits[0], cbits[0])
    
    result = qvm.run_with_configuration(prog, cbits, 1000)
    print(f"S|0⟩的测量结果统计: {result}")
    print("解释: S门是相位门，|0⟩态保持不变，|1⟩态获得i相位因子")   
    
    # 释放量子虚拟机
    qvm.finalize()

if __name__ == "__main__":
    quantum_state_transformation()