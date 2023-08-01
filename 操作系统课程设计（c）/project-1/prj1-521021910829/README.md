# Project 1

## 文件夹：Copy

> Task1: Copy using Pipe

- 源文件：copy.c

- 输入文件：test_in.txt(可以自建文件并更改参数即可)

- 执行指令

  ```shell
  > make
  > ./Copy <infile> <outfile> <buffer size>
  ```

## 文件夹：Shell

> Task2: Multiple Client Shell

- 源文件：shell.c

- 执行指令

  ```shell
  > make
  > ./shell <Port num>
  ```

  新开一个终端并输入

  ```shell
  > telnet localhost <Port num>
  > <command> <command> | <command> <command> | ...
  > exit
  ```

## 文件夹：Matrix

> Task3: Matrix Multiplication Using Pthread

- 源文件：single.c, multi.c
- 输入文件：data.in(不能更改文件名)

- 执行指令

  - 执行单线程版本

  ```shell
  > make
  > ./single
  ```

  - 执行多线程版本-version1(指定输入为data.in)

  ```shell
  > make
  > ./multi <number of threads>
  ```

  - 执行多线程版本-version2(随机矩阵输入)

  ```shell
  > make
  > ./multi <number of threads> <size of the random matrix>
  ```

- **注意**

  - 矩阵大小和线程必须为 2 的幂次，并且矩阵大小大于线程数

## Report.pdf

- 实验报告

## Test.pdf

- 本地测试情况
