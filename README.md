# FPTree算法实现频繁模式挖掘

<<<<<<< HEAD
FPTree-V2.cppΪ�Ľ�����㷨ʵ�֣�ʱ��Ϳռ�Ч���н̴�Ľ�!

�Ľ����㷨���жԱ�ͼ���£�
![fptree](.//fptree.png)

**ע��**��FPTree-V2����δ���뵥����¼ȥ�ع��ܣ���**�������ݱ������㵥�����ظ���**��

####�����ļ�˵��
  1. datatest\\in.txt�ļ�ÿһ�в�Ҫ�Կո��β�����һ��Ϊ���У��������������ļ�

####���е���˵����
1. Input the min support:
    ��������С֧�ֶ�

2. Input the mode of processing:
    0: Run in default mode
    1: Run in out-file mode
    �趨��������0ָĬ��ģʽ�ӿ���̨���
    1ָ���������ļ�test\\out.txt

3. Need DEBUG ?
    1:BEBUGģʽ���У����ӡÿһ�εݹ����ʱ������      ������Ϣ(��ǰ�ݹ���ȡ����񼯡���ͷ����FP���ṹ����׺ģʽ����Ƶ��ģʽ)
    0:�������������Ϣ�����������Ƶ��ģʽ�������������֧�ֶ�����
=======
FPTree-V2.cpp为改进版的算法实现，时间和空间效率有很大改进运行对比图 - fptree.png

----------
### 处理文件说明
 test\\in.txt文件每一行不要以空格结尾且最后一行为空行，才能正常处理文件
>>>>>>> d1acd5b69063fe6054974b5f235d8977fbbeefa8

----------
### 运行导引说明：
Input the min support:
- 即输入最小支持度

----------
Input the mode of processing:
- 0 : Run in default mode
- 1 : Run in out-file mode
  - 设定输出结果，0指默认模式从控制台输出
  - 1指结果输出到文件test\\out.txt

----------
Need DEBUG ?
- 1 : BEBUG模式运行，会打印每一次递归调用时的所有具体信息(当前递归深度、事务集、项头集，FP树结构、后缀模式串、频繁模式)
- 0 : 不会输出以上信息，仅输出所有频繁模式，并将最后结果按支持度排序。
