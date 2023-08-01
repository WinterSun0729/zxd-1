# README

## step1

- disk.c: 模拟磁盘c文件
- makefile: MakeFile文件

指令：

```shell
> make
> ./disk <cylinders> <sectors per cylinder> <track-to-track delay> <disk-storage-filename>
```

例如：

```shell
> make
> ./disk 3 3 100 disk_file
```

## step2

- fs.c: 基本（FAT）文件系统c文件
- makefile: MakeFile文件

指令：

```shell
> make
> ./fs
```

## step3

- disk.c: 模拟磁盘服务器c文件
- fs.c: 基本（FAT）文件系统服务器c文件
- Client.c: 客户端c文件
- makefile: MakeFile文件

指令：

```shell
> make
> ./disk <cylinders> <sectors per cylinder> <track-to-track delay> <disk-storage-filename> <diskport>
new terminal
> ./fs hostname <diskport> <fsport>
newterminal
> ./client hostname <fsport>
```

例如：

```shell
> make
> ./disk 3 3 100 2001
new terminal
> ./fs ubuntu-linux-22-04-desktop disk_file 2001 2002
newterminal
> ./client ubuntu-linux-22-04-desktop 2002
```

