# lec6 SPOC思考题


NOTICE
- 有"w3l2"标记的题是助教要提交到学堂在线上的。
- 有"w3l2"和"spoc"标记的题是要求拿清华学分的同学要在实体课上完成，并按时提交到学生对应的git repo上。
- 有"hard"标记的题有一定难度，鼓励实现。
- 有"easy"标记的题很容易实现，鼓励实现。
- 有"midd"标记的题是一般水平，鼓励实现。


## 个人思考题
---

（1） (w3l2) 请简要分析64bit CPU体系结构下的分页机制是如何实现的
```
  页机制将物理地址和虚拟地址分别分为大小相同的frame或page，每个page可对应任意一个frame（或page fault)。
  该对应关系由页表存储，每一个表项以page index为索引，内容有frame index和一些标志位。
  这样虚拟地址和物理地址就均由两部分组成：(page index, offset); (frame index, offset), 
    转换时只需查表，将page index替换成frame index就能得到物理地址。
  但对于64bit系统来说，单页表占地太大，因此采用多级页表（一般5级）或反置页表。
  多级页表：
    即对页表做分页，原来的page index 分成(p1, p2),上级页表以p1为索引记录下级页表各分页的起始地址，
    下级页表以p2为索引记录真的frame index，这样就建立了2级页表，多级页表与此类似。
    实际查找时如（p1, p2, offset), 以p1为索引查1级表得2级表地址，以p2为索引得frame index，就能转换为物理地址了。
  反置页表：
    采用Hash+冲突链，以frame index为索引，记录pid，page index，这样无论有多少进程页表大小都是可控的。
    进程转物理地址方法为，先将(pid,page index)做Hash到frame index, 到对应表项作比较，若不同，顺着冲突链依次比较，
    直到找到（用该frame index转物理地址）或没找到（page fault)。
 ```
- [x]  

>  

## 小组思考题
---

（1）(spoc) 某系统使用请求分页存储管理，若页在内存中，满足一个内存请求需要150ns。若缺页率是10%，为使有效访问时间达到0.5ms,求不在内存的页面的平均访问时间。请给出计算步骤。 

- [x]  

>0.9\*150 + 0.1\*x = 500 得x = 3650ns

（2）(spoc) 有一台假想的计算机，页大小（page size）为32 Bytes，支持32KB的虚拟地址空间（virtual address space）,有4KB的物理内存空间（physical memory），采用二级页表，一个页目录项（page directory entry ，PDE）大小为1 Byte,一个页表项（page-table entries
PTEs）大小为1 Byte，1个页目录表大小为32 Bytes，1个页表大小为32 Bytes。页目录基址寄存器（page directory base register，PDBR）保存了页目录表的物理地址（按页对齐）。

PTE格式（8 bit） :
```
  VALID | PFN6 ... PFN0
```
PDE格式（8 bit） :
```
  VALID | PT6 ... PT0
```
其
```
VALID==1表示，表示映射存在；VALID==0表示，表示映射不存在。
PFN6..0:页帧号
PT6..0:页表的物理基址>>5
```
在[物理内存模拟数据文件](./03-2-spoc-testdata.md)中，给出了4KB物理内存空间的值，请回答下列虚地址是否有合法对应的物理内存，请给出对应的pde index, pde contents, pte index, pte contents。
```
Virtual Address 6c74
Virtual Address 6b22
Virtual Address 03df
Virtual Address 69dc
Virtual Address 317a
Virtual Address 4546
Virtual Address 2c03
Virtual Address 7fd7
Virtual Address 390e
Virtual Address 748b
```

编写了一个<a href="https://github.com/magicwish/os_exercises/tree/master/code/03-3-lab2-spoc-discussion-analyseAddr">C程序</a>进行处理。

```
答案：
Virtual Address 7570:
  --> pde index:0x1d  pde contents:(valid 1, pfn 0x33)
    --> pte index:0xb  pte contents:(valid 0, pfn 0x7f)
      --> Fault (page table entry not valid)
      
Virtual Address 21e1:
  --> pde index:0x8  pde contents:(valid 0, pfn 0x7f)
      --> Fault (page directory entry not valid)

Virtual Address 7268:
  --> pde index:0x1c  pde contents:(valid 1, pfn 0x5e)
    --> pte index:0x13  pte contents:(valid 1, pfn 0x65)
      --> Translates to Physical Address 0xca8 --> Value: 16
      
Answer:      
Virtual Address 0x6c74
  --> pde index:0x1b pde contents:(valid 1, pt 0x20)
      --> pte index:0x03  pte contents:(valid 1, pfn 0x61)
      --> Translates to Physical Address 0xc34 --> Value:0x06
Virtual Address 0x6b22
  --> pde index:0x1a pde contents:(valid 1, pt 0x52)
      --> pte index:0x19  pte contents:(valid 1, pfn 0x47)
      --> Translates to Physical Address 0x8e2 --> Value:0x1a
Virtual Address 0x03df
  --> pde index:0x00 pde contents:(valid 1, pt 0x5a)
      --> pte index:0x1e  pte contents:(valid 1, pfn 0x05)
      --> Translates to Physical Address 0x0bf --> Value:0x0f
Virtual Address 0x69dc
  --> pde index:0x1a pde contents:(valid 1, pt 0x52)
      --> pte index:0x0e  pte contents:(valid 0, pfn 0x7f)
      --> Fault (page table entry not valid)
Virtual Address 0x317a
  --> pde index:0x0c pde contents:(valid 1, pt 0x18)
      --> pte index:0x0b  pte contents:(valid 1, pfn 0x35)
      --> Translates to Physical Address 0x6ba --> Value:0x1e
Virtual Address 0x4546
  --> pde index:0x11 pde contents:(valid 1, pt 0x21)
      --> pte index:0x0a  pte contents:(valid 0, pfn 0x7f)
      --> Fault (page table entry not valid)
Virtual Address 0x2c03
  --> pde index:0x0b pde contents:(valid 1, pt 0x44)
      --> pte index:0x00  pte contents:(valid 1, pfn 0x57)
      --> Translates to Physical Address 0xae3 --> Value:0x16
Virtual Address 0x7fd7
  --> pde index:0x1f pde contents:(valid 1, pt 0x12)
      --> pte index:0x1e  pte contents:(valid 0, pfn 0x7f)
      --> Fault (page table entry not valid)
Virtual Address 0x390e
  --> pde index:0x0e pde contents:(valid 0, pt 0x7f)
    --> Fault (page directory entry not valid)
Virtual Address 0x748b
  --> pde index:0x1d pde contents:(valid 1, pt 0x00)
      --> pte index:0x04  pte contents:(valid 0, pfn 0x7f)
      --> Fault (page table entry not valid)
```



（3）请基于你对原理课二级页表的理解，并参考Lab2建页表的过程，设计一个应用程序（可基于python, ruby, C, C++，LISP等）可模拟实现(2)题中描述的抽象OS，可正确完成二级页表转换。


（4）假设你有一台支持[反置页表](http://en.wikipedia.org/wiki/Page_table#Inverted_page_table)的机器，请问你如何设计操作系统支持这种类型计算机？请给出设计方案。

 (5)[X86的页面结构](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture06#head-1f58ea81c046bd27b196ea2c366d0a2063b304ab)
--- 

## 扩展思考题

阅读64bit IBM Powerpc CPU架构是如何实现[反置页表](http://en.wikipedia.org/wiki/Page_table#Inverted_page_table)，给出分析报告。

--- 
