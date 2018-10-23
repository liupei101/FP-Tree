### FPTree算法实现频繁模式挖掘

FPTree-V2.cpp为改进版的算法实现，时间和空间效率有教大改进!

改进版算法运行对比图如下：
![fptree](.//fptree.png)

**注意**：FPTree-V2程序未加入单条记录去重功能，故**输入数据必须满足单条无重复项**。

#### 处理文件说明

- datatest//in.txt 文件每一行不要以空格结尾且最后一行为空行，才能正常处理文件

#### 运行导引说明：

- Input the min support: 即输入最小支持度

- Input the mode of processing: 设定输出结果，0指默认模式从控制台输出，1指结果输出到文件 datatest//out.txt
    - 0 : Run in default mode
    - 1 : Run in out-file mode

- Need DEBUG ?
    - 1 : BEBUG模式运行，会打印每一次递归调用时的所有具体信息(当前递归深度、事务集、项头集，FP树结构、后缀模式串、频繁模式)
    - 0 : 不会输出以上信息，仅输出所有频繁模式，并将最后结果按支持度排序。
