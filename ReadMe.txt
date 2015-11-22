直接点击FPTree.exe文件即可运行处理文件。
* 默认处理文件为同目录下的data\\in.txt文件
  1.data\\in.txt文件每一行不要以空格结尾且最后一行为空行，才能正常处理文件
* 运行导引说明：
  1.Input the min support:
    即输入最小支持度
  2.Input the mode of processing:
    0: Run in default mode
    1: Run in out-file mode
    设定输出结果，0指默认模式从控制台输出
    1指结果输出到文件data\\out.txt
  3.Need DEBUG ?
    1:BEBUG模式运行，会打印每一次递归调用时的所有      具体信息(当前递归深度、事务集、项头集，FP树结构、后缀模式串、频繁模式)
    0:不会输出以上信息，仅输出所有频繁模式，并将最后结果按支持度排序。


