#lec 3 SPOC Discussion

## 第三讲 启动、中断、异常和系统调用-思考题

## 3.1 BIOS
 1. 比较UEFI和BIOS的区别。
 1. 描述PXE的大致启动流程。

## 3.2 系统启动流程
 1. 了解NTLDR的启动流程。
 1. 了解GRUB的启动流程。
 1. 比较NTLDR和GRUB的功能有差异。
 1. 了解u-boot的功能。

## 3.3 中断、异常和系统调用比较
 1. 举例说明Linux中有哪些中断，哪些异常？
 1. Linux的系统调用有哪些？大致的功能分类有哪些？  (w2l1)

```
 Linux的系统调用有上百个，主要的功能分类有：
 进程管理：fork, clone, exit...
 文件系统管理：open, close, read, write, create, chdir, chmod...
 系统控制：reboot, sysinfo, time...
 内存管理：mlock, munlock...
 网络管理：gethostid, gethostname...
 用户管理：getuid, setuid, getgid, setgid...
 进程间通信：msgsnd, msgget, pipe...
 ```
 
 1. 以ucore lab8的answer为例，uCore的系统调用有哪些？大致的功能分类有哪些？(w2l1)
 
 ```
	在ucore中syscall一共有22个系统调用。按功能分类有：
	进程管理：sys_exit, sys_fork, sys_wait, sys_exec, sys_yield, sys_kill, sys_getpid, sys_sleep.
	文件系统控制：sys_pgdir, sys_gettime, sys_open, sys_close, sys_read, sys_write, sys_seek, sys_fstat, sys_dup, sys_getdirentry.
 内存管理：sys_lab6_set_priority, sys_fsync, sys_getcwd, sys_putc.
 ```
 
## 3.4 linux系统调用分析
 1. 通过分析[lab1_ex0](https://github.com/chyyuu/ucore_lab/blob/master/related_info/lab1/lab1-ex0.md)了解Linux应用的系统调用编写和含义。(w2l1)
 
 ```
 objdump：查看（可执行的）目标文件的构成的命令，包括输出目标文件的数据组织、段概括、符号表、指定的段信息、反汇编等。
 nm：主要针对列出和查看目标文件的符号表，例如查找符号在哪个库中被定义、输出所有调试符号等。
 file：检测文件类型的命令。
 在Linux中，用户程序不能直接使用I/O硬件，必须通过系统调用。系统调用是操作系统提供的接口，代表用户程序完成对硬件的操作，起到保护硬件的作用。对用户程序来说，系统调用是硬件操作的抽象接口，用户程序不需知道具体的硬件类型，操作细节。
 ```
 
 1. 通过调试[lab1_ex1](https://github.com/chyyuu/ucore_lab/blob/master/related_info/lab1/lab1-ex1.md)了解Linux应用的系统调用执行过程。(w2l1)
 

 ```
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 24.07    0.000097          24         4           mprotect
 19.35    0.000078          11         7           mmap
 11.17    0.000045          45         1           brk
 10.67    0.000043          22         2           fstat
  8.44    0.000034          34         1           stat
  7.94    0.000032          16         2           open
  7.44    0.000030          10         3         3 access
  6.95    0.000028          28         1           munmap
  1.49    0.000006           6         1           execve
  1.24    0.000005           5         1           read
  0.74    0.000003           2         2           close
  0.50    0.000002           2         1           arch_prctl
------ ----------- ----------- --------- --------- ----------------
100.00    0.000403                    26         3 total

 ```
 
## 3.5 ucore系统调用分析
 1. ucore的系统调用中参数传递代码分析。
 1. ucore的系统调用中返回结果的传递代码分析。
 1. 以ucore lab8的answer为例，分析ucore 应用的系统调用编写和含义。
 1. 以ucore lab8的answer为例，尝试修改并运行ucore OS kernel代码，使其具有类似Linux应用工具`strace`的功能，即能够显示出应用程序发出的系统调用，从而可以分析ucore应用的系统调用执行过程。
 
## 3.6 请分析函数调用和系统调用的区别
 1. 请从代码编写和执行过程来说明。
   1. 说明`int`、`iret`、`call`和`ret`的指令准确功能
 
