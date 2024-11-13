from pyqpanda import *

def create_bell_state_with_phase_gates():
    # 初始化量子虚拟机
    qvm = CPUQVM()
    qvm.init_qvm()
    
    # 申请两个量子比特和两个经典比特
    qubits = qvm.qAlloc_many(2)
    cbits = qvm.cAlloc_many(2)
    
    # 创建量子程序
    prog = QProg()

    prog << H(qubits[0])
    prog << CNOT(qubits[0], qubits[1])
    
    # 作用 S 门或 T 门
    prog << T(qubits[0])
    prog << T(qubits[1])
    # 或者可以使用 T 门代替 S 门
    
    # 测量量子比特并存储结果到经典比特
    prog << Measure(qubits[0], cbits[0])
    prog << Measure(qubits[1], cbits[1])
    
    # 运行程序并查看测量结果
    result = qvm.run_with_configuration(prog, cbits, 1000)
    print(f"测量结果统计: {result}")
    
    # 释放量子虚拟机资源
    qvm.finalize()

if __name__ == "__main__":
    create_bell_state_with_phase_gates()
