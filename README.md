###FPTree算法实现频繁模式挖掘

>FPTree-V2.cpp为改进版的算法实现，时间和空间效率有很大改进
>运行对比图 - fptree.png

####处理文件说明
1. test\\in.txt文件每一行不要以空格结尾且最后一行为空行，才能正常处理文件
####运行导引说明：
1. Input the min support:
    即输入最小支持度
2. Input the mode of processing:
    0: Run in default mode
    1: Run in out-file mode
    设定输出结果，0指默认模式从控制台输出
    1指结果输出到文件test\\out.txt
3. Need DEBUG ?
    1:BEBUG模式运行，会打印每一次递归调用时的所有      具体信息(当前递归深度、事务集、项头集，FP树结构、后缀模式串、频繁模式)
    0:不会输出以上信息，仅输出所有频繁模式，并将最后结果按支持度排序。


