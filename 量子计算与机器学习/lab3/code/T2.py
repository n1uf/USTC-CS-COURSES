from pyqpanda import *
import numpy as np

def deutsch_algorithm(f_type='constant'):
    """
    实现Deutsch算法
    f_type: 'constant' 表示常量函数 f(x)=0
            'balanced' 表示平衡函数 f(x)=x
    """
    qvm = CPUQVM()
    qvm.init_qvm()
    
    # 申请两个量子比特和一个经典寄存器
    qubits = qvm.qAlloc_many(2)
    cbit = qvm.cAlloc()
    
    # 构建量子程序
    prog = QProg()
    
    # 初始化：|0⟩|1⟩
    prog << X(qubits[1])
    
    # 应用H门创建叠加态
    prog << H(qubits[0]) << H(qubits[1])
    
    # 应用Uf (量子oracle)
    if f_type == 'constant':  # f(x)=0
        # 对于常量函数f(x)=0，Uf不做任何操作
        pass
    else:  # f(x)=x
        # 对于平衡函数f(x)=x，Uf实现为CNOT门
        prog << CNOT(qubits[0], qubits[1])
    
    # 对第一个量子比特应用H门
    prog << H(qubits[0])
    
    # 测量第一个量子比特
    prog << Measure(qubits[0], cbit)
    
    # 运行程序并统计结果
    result = qvm.run_with_configuration(prog, [cbit], 1000)
    
    # 输出结果
    print(f"\n函数类型: {'常量函数 f(x)=0' if f_type=='constant' else '平衡函数 f(x)=x'}")
    print("测量结果统计（1000次）：")
    for state, count in result.items():
        print(f"|{state}⟩: {count} 次 ({count/1000*100:.2f}%)")
    
    # 判断函数类型
    if '0' in result and result['0']/1000 > 0.9:  # 考虑一些误差，使用0.9作为阈值
        print("结论：这是一个常量函数")
    elif '1' in result and result['1']/1000 > 0.9:
        print("结论：这是一个平衡函数")
    else:
        print("结论：结果不确定")
    
    qvm.finalize()

if __name__ == "__main__":
    print("测试常量函数 f(x)=0：")
    deutsch_algorithm('constant')
    
    print("\n测试平衡函数 f(x)=x：")
    deutsch_algorithm('balanced')