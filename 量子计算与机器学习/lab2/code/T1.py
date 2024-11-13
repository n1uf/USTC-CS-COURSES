from pyqpanda import *

def create_bell_state():
    # 初始化量子虚拟机
    qvm = CPUQVM()
    qvm.init_qvm()
    
    # 申请两个量子比特和两个经典比特
    qubits = qvm.qAlloc_many(2)
    cbits = qvm.cAlloc_many(2)
    
    # 创建量子程序
    prog = QProg()
    
    # 对第一个量子比特应用 H 门
    prog << H(qubits[0])
    
    # 对第二个量子比特应用 CNOT 门，qubits[0] 作为控制比特，qubits[1] 作为目标比特
    prog << CNOT(qubits[0], qubits[1])
    
    # 测量量子比特并存储结果到经典比特
    prog << Measure(qubits[0], cbits[0])
    prog << Measure(qubits[1], cbits[1])
    
    # 运行程序并查看测量结果
    result = qvm.run_with_configuration(prog, cbits, 1000)
    print(f"测量结果统计: {result}")
    
    # 释放量子虚拟机资源
    qvm.finalize()

if __name__ == "__main__":
    create_bell_state()
