from pyqpanda import *

def quantum_single_gates_demo():
    # 初始化量子虚拟机
    qvm = CPUQVM()
    qvm.init_qvm()
    
    # 申请量子比特和经典寄存器
    qubits = qvm.qAlloc_many(1)
    cbits = qvm.cAlloc_many(1)
    
    # 测试X门
    print("\n测试X门:")
    prog = QProg()
    prog << X(qubits[0])  # 对初态|0⟩应用X门
    prog << Measure(qubits[0], cbits[0])
    
    # 运行1000次统计结果
    result = qvm.run_with_configuration(prog, cbits, 1000)
    print(f"理论上测量结果应为|1⟩态，实际测量结果统计: {result}")
    
    # 测试Y门
    print("\n测试Y门:")
    prog = QProg()
    prog << Y(qubits[0])  # 对初态|0⟩应用Y门
    prog << Measure(qubits[0], cbits[0])
    
    result = qvm.run_with_configuration(prog, cbits, 1000)
    print(f"理论上测量结果应为i|1⟩态，实际测量结果统计: {result}")
    
    # 测试Z门
    print("\n测试Z门:")
    prog = QProg()
    prog << Z(qubits[0])  # 对初态|0⟩应用Z门
    prog << Measure(qubits[0], cbits[0])
    
    result = qvm.run_with_configuration(prog, cbits, 1000)
    print(f"理论上测量结果应为|0⟩态，实际测量结果统计: {result}")
    
    # 释放量子虚拟机
    qvm.finalize()

if __name__ == "__main__":
    quantum_single_gates_demo()