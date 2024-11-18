from pyqpanda import *
import numpy as np

def create_and_measure_ghz_state():
    """
    创建和测量GHZ态：(|000⟩ + |111⟩)/√2
    """
    qvm = CPUQVM()
    qvm.init_qvm()
    
    # 申请3个量子比特和经典寄存器
    qubits = qvm.qAlloc_many(3)
    cbits = qvm.cAlloc_many(3)
    
    # 构建量子程序
    prog = QProg()
    
    # 构建GHZ态
    prog << H(qubits[0]) \
        << CNOT(qubits[0], qubits[1]) \
        << CNOT(qubits[1], qubits[2])
    
    # 测量所有量子比特
    prog << Measure(qubits[0], cbits[0]) \
        << Measure(qubits[1], cbits[1]) \
        << Measure(qubits[2], cbits[2])
    
    # 运行程序并获取结果
    result = qvm.run_with_configuration(prog, cbits, 1000)
    
    # 格式化输出结果
    print("\n测量1000次的结果统计：")
    for state, count in result.items():
        print(f"|{state}⟩: {count} 次 ({count/1000*100:.2f}%)")
    
    qvm.finalize()

if __name__ == "__main__":
    create_and_measure_ghz_state()