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
execve("./lab-ex0", ["./lab-ex0"], [/* 73 vars */]) = 0
brk(0)                                  = 0xd61000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f09090e3000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=93381, ...}) = 0
mmap(NULL, 93381, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f09090cc000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\320\37\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=1845024, ...}) = 0
mmap(NULL, 3953344, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f0908afd000
mprotect(0x7f0908cb8000, 2097152, PROT_NONE) = 0
mmap(0x7f0908eb8000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1bb000) = 0x7f0908eb8000
mmap(0x7f0908ebe000, 17088, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f0908ebe000
close(3)                                = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f09090cb000
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f09090c9000
arch_prctl(ARCH_SET_FS, 0x7f09090c9740) = 0
mprotect(0x7f0908eb8000, 16384, PROT_READ) = 0
mprotect(0x600000, 4096, PROT_READ)     = 0
mprotect(0x7f09090e5000, 4096, PROT_READ) = 0
munmap(0x7f09090cc000, 93381)           = 0
stat(0x1, hello world
{st_mode=021225430647, st_size=140735514292710, ...}) = 12
exit_group(12)                          = ?
+++ exited with 12 +++
 ```
 
## 3.5 ucore系统调用分析
 1. ucore的系统调用中参数传递代码分析。
 1. ucore的系统调用中返回结果的传递代码分析。
 1. 以ucore lab8的answer为例，分析ucore 应用的系统调用编写和含义。
 1. 以ucore lab8的answer为例，尝试修改并运行ucore OS kernel代码，使其具有类似Linux应用工具`strace`的功能，即能够显示出应用程序发出的系统调用，从而可以分析ucore应用的系统调用执行过程。
 
## 3.6 请分析函数调用和系统调用的区别
 1. 请从代码编写和执行过程来说明。
   1. 说明`int`、`iret`、`call`和`ret`的指令准确功能
 
