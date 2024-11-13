from pyqpanda import *

def two_qubit_operation():
    # 初始化量子虚拟机
    qvm = CPUQVM()
    qvm.init_qvm()
    
    # 申请两个量子比特和经典寄存器
    qubits = qvm.qAlloc_many(2)  # 分配两个量子比特
    cbits = qvm.cAlloc_many(2)   # 分配两个经典寄存器
    
    # 创建量子程序
    prog = QProg()
    
    # 对第一个量子比特应用X门，将其从|0⟩变为|1⟩
    prog << X(qubits[0])
    
    
    # 测量两个量子比特
    prog << Measure(qubits[0], cbits[0])  # 测量第一个量子比特
    prog << Measure(qubits[1], cbits[1])  # 测量第二个量子比特
    
    # 运行程序1000次并统计结果
    result = qvm.run_with_configuration(prog, cbits, 1000)
    
    print("测量结果统计：")
    print(result)
    
    # 释放量子虚拟机
    qvm.finalize()

if __name__ == "__main__":
    two_qubit_operation()