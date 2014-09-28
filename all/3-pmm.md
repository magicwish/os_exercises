# 物理内存管理

## 单选题

---

一般情况下，____的速度最快
- [x] L1 cache
- [ ] L2 cache
- [ ] Main Memory
- [ ] Disk

> 解释：访问速度上 cache > Main Memory > Disk; cache中 L1 > L2 > L3 ... 越靠近cpu速度越快，容量越小。

程序的逻辑地址到内存的物理地址的转化发生____过程中
- [ ] 编译
- [ ] 链接
- [x] 重定位
- [ ] 运行

> 解释：在编译和链接的过程中都只涉及到逻辑地址，跟机器的配置无关，这也是编译链接所生成的可执行文件可以直接在相同系统的其它机器上使用的原因。而在程序真正加载的时候，操作系统负责将逻辑地址和实际物理地址对应起来，之后才能正确运行。

分页系统中, 逻辑地址到物理地址的变换是由____决定的
- [ ] 段表
- [x] 页表
- [ ] 物理结构
- [ ] 重定位寄存器

> 解释：分页系统中，页表负责转换逻辑地址到物理地址。

分段系统中, 逻辑地址到物理地址的变换是由____决定的
- [x] 段表
- [ ] 页表
- [ ] 物理结构
- [ ] 重定位寄存器

> 解释：略

连续内存分配算法中的First Fit（首次适应）算法，其空闲分区链的顺序为____
- [x] 空闲区首地址递增
- [ ] 空闲区首地址递减
- [ ] 空闲区大小递增
- [ ] 空闲区大小递减

> 解释：First Fit是指按地址来寻找第一个满足要求的空闲块，其空闲分区链的顺序也就是按空闲块首地址递增。

连续内存分配算法中的Best Fit（最佳适应）算法，其空闲分区链的顺序为____
- [ ] 空闲区首地址递增
- [ ] 空闲区首地址递减
- [x] 空闲区大小递增
- [ ] 空闲区大小递减

> 解释：Best Fit是指寻找一个大小最合适的空闲块，要求空闲块按照大小排列，其空闲分区链的顺序为按大小递增。

连续内存分配算法First Fit的缺点是____
- [ ] 算法复杂
- [ ] 大的空闲分区会被分割
- [x] 容易产生外部碎片
- [ ] 分配速度慢

> 解释：First Fit算法非常简单，分配速度也较快。但是First Fit不考虑实际的需求和找到的空闲分区的大小的匹配度，所以容易产生外部碎片。

连续内存分配算法Best Fit的缺点是____
- [ ] 算法复杂
- [ ] 大的空闲分区会被分割
- [ ] 分配速度慢
- [x] 回收速度慢

> 解释：Best Fit算法也非常简单，分配速度较快。由于选取的空闲分区大小都很合适，所以基本不会出现大的空闲分区总是被分割的情况。但是在此算法中，内存回收则涉及了很多操作：判断左右邻居是否是空闲分区，如果不是，则插入此空闲分区到合适的地方，如果是则合并空闲块，并把合并后的结果插入到合适地方；但是由于空闲分区链不是按地址排序的，所以上述操作需要遍历几次链表用于查找和插入，速度较慢。

连续内存分配算法Worst Fit的缺点是____
- [ ] 算法复杂
- [x] 大的空闲分区会被分割
- [ ] 分配速度慢
- [ ] 容易产生很小的空闲分区

> 解释：Worst Fit每次使用最大的空闲分区，按照需求分割相应的大小，所以会造成大的空闲分区总是被分割。其算法比较简单，分配速度也很快。

某一作业完成后，系统收回其主存空间，并与相邻空闲区合并，为此需修改空闲区表，如果待回收的空闲区有相邻的低址空闲区,也有相邻的高址空闲区，那么空闲区表将____
- [ ] 项数不变，有一个空闲区的大小变大
- [ ] 项数不变，有一个空闲区的起始地址变小，大小变大
- [ ] 项数增加
- [x] 项数减少

> 解释：合并之后，原本的2个相邻空闲分区和被回收的分区合并成一个分区，所以分区项数变为n - 2 + 1 = n - 1。

对于分页系统与分段系统,下列说法正确的是( ).
- [ ] 页的大小跟具体执行程序有关
- [x] 都属于非连续分配
- [ ] 段的大小固定且由系统确定
- [ ] 分段技术和分页技术是不能共存在一个系统中的

> 解释：页的大小由操作系统定义，跟具体执行程序无关； 段的大小是指程序的数据段、代码段等每段的大小，和具体程序相关；分段技术和分页技术是按照需求进行动态的分配和回收，是非连续分配，它们可以融合使用，也称段页式管理。

采用段页式管理时，程序按逻辑被划分成____
- [x] 段
- [ ] 页
- [ ] 区域
- [ ] 块

> 解释：程序按逻辑划分各段，页、区域、块由操作系统负责分配、映射和管理，和程序逻辑没有关系。

采用段页式管理的多道程序环境下，每道程序都有对应的____
- [ ] 一个段表和一个页表
- [x] 一个段表和一组页表
- [ ] 一组段表和一个页表
- [ ] 一组段表和一组页表

> 解释：每道程序有一个段表，而每段有一个页表。

在分页式存储管理系统中时，每次从主存中取指令或取操作数，至少要访问____次主存。
- [ ] 1
- [x] 2
- [ ] 3
- [ ] 4

> 解释：至少需要一次页表访问和一次内容获取。

在分段式存储管理系统中时，每次从主存中取指令或取操作数，至少要访问____次主存。
- [ ] 1
- [x] 2
- [ ] 3
- [ ] 4

> 解释：至少需要一次段表访问和一次内容获取。

在段页式存储管理系统中时，每次从主存中取指令或取操作数，至少要访问____次主存。
- [ ] 1
- [ ] 2
- [x] 3
- [ ] 4

> 解释：至少需要一次段表访问、一次相应段的页表访问和一次内容获取。

每道程序能在不受干扰的环境下运行，主要是通过____功能实现的。
- [ ] 内存分配
- [x] 内存保护
- [ ] 内存回收
- [ ] 内存扩充

> 解释：内存访问需要将逻辑地址和重定位寄存器(基址寄存器)进行加运算之后才能访问物理地址，而内存保护主要是使用界地址寄存器来实现对逻辑地址的限制，以免逻辑地址越界而造成物理地址访问越界，进而对别的程序进行干扰。

可变分区存储管理方案中____作为存储保护使用。
- [ ] 逻辑地址寄存器
- [x] 长度寄存器
- [ ] 物理地址寄存器
- [ ] 基址寄存器

> 解释：长度寄存器或称界地址寄存器，用于存储保护。

分页系统中的页面对____透明，是____管理的。
- [ ] 用户、编译器
- [x] 用户、操作系统
- [ ] 操作系统、编译器
- [ ] 用户、链接器

> 解释：分页由操作系统控制，用户并不能感知。

---

## 多选题

---

关于分段系统和分页系统说法正确有___。
- [x] 页是信息的物理单位，分页仅仅是由于系统管理的需要；段是信息的逻辑单位,分段的目的是为了能更好地满足用户的需要
- [x] 页的大小是固定的，而且由系统确定。段的长度却是不固定的，决定于用户所编写的程序
- [x] 分段系统会产生外部碎片
- [x] 分段便于控制存取访问，段是逻辑上完整信息可根据各段信息决定存取访问权；分页存取访问控制困难

> 解释：1,2,4解释略。3：分段系统中段的大小是跟程序相关的，分段系统中每次分配的大小就是相应段的真实大小所以没有内部碎片；但是却会产生不满足任何段大小的空闲分区，就是外部碎片。

---