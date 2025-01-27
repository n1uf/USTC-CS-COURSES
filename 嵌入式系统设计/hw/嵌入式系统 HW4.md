# 嵌入式系统 HW5

## 牛庆源 PB21111733

---

* 深入调研ARMv9
  * 从指令集架构、运行模式、异常处理等方面讨论ARMv8与ARMv9的异同
  * 调研ARMv9的应用情况和发展前景

---

1. 异同

   * 指令集架构上，相同之处在于ARMv9继续使用AArch64作为基准指令集，区别点在于增加了一些很重要的扩展，例如引入了可伸缩矢量扩展2（SVE2）指令集，使处理器矢量计算从128位扩展到2048位，取代了原有的NEON技术，在矩阵乘法等大规模计算任务中的性能提升显著。
   * ARMv9引入了新的保密计算架构CCA实现更好的安全性，同时也引入内存标签扩展避免了内存错误和安全漏洞。
   * 异常处理机制上，相同点为ARMv9延续了ARMv8的异常处理机制ARM Exception Level System，不同之处是引入了新的特性：新的异常向量表格式、在异常处理函数执行过程中引入异常嵌套的概念、对异常处理速度进行了一些优化，减少延迟。

   

2. 应用情况和发展前景

   * 应用：
     * 高性能计算：更高的矢量计算能力提供支持。
     * AI：更强的矩阵计算与AI加速功能。
     * 物联网。
   * 前景：
     * 更好的性能和能效。
     * 更广泛的应用领域：包括自动驾驶、医疗、金融等领域。