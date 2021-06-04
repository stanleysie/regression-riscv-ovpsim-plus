# **Linear Regression with Vector Processor using riscvOVPsimPlus**

This is a simple implementation of Linear Regression with RISC-V Vector Extension in C, compiled and run using riscvOVPsimPlus. For each program, we provided a copy of them coded in pure C language to compare the performance of the vector extension.

# **Program Setup**
## **riscvOVPsimPlus Setup**
Please refer to our [riscvOVPsimPlus Setup](https://github.com/stanleysie/riscv-ovpsim-plus-demo) repository.
<br/><br/>

## **Compile the Support files**

This will generate `vsupport.o` which will be used for all compilation of programs in this repository.

```
# run this command in Ubuntu Terminal

$ ./compile_matrixoperations.sh
```

## **Compilation and Running**

```
# run these commands in Ubuntu Terminal

# LINEAR REGRESSION WITH VECTOR EXTENSION
$ cd linear-regression-vector
$ ./compile_linear_regression.sh
$ ./run_linear_regression.sh

# LINEAR REGRESSION WITHOUT VECTOR EXTENSION
$ cd linear-regression-no-vector
$ ./compile_linear_regression.sh
$ ./run_linear_regression.sh
```
If riscvOVPsimPlus is set up properly, the output should be similar to the output below.
```
Imperas riscvOVPsimPlus


riscvOVPsimPlus (64-Bit) v20210329.0 Open Virtual Platform simulator from www.IMPERAS.com.
Copyright (c) 2005-2021 Imperas Software Ltd.  Contains Imperas Proprietary Information.
Licensed Software, All Rights Reserved.
Visit www.IMPERAS.com for multicore debug, verification and analysis solutions.

riscvOVPsimPlus started: Wed Jun  2 12:29:48 2021


Info (OR_OF) Target 'riscvOVPsim/cpu' has object file read from 'LinearRegression.elf'
Info (OR_PH) Program Headers:
Info (OR_PH) Type           Offset             VirtAddr           PhysAddr
Info (OR_PH)                FileSiz            MemSiz             Flags  Align
Info (OR_PD) LOAD           0x0000000000000000 0x0000000000010000 0x0000000000010000
Info (OR_PD)                0x0000000000011974 0x0000000000011974 R-E    1000
Info (OR_PD) LOAD           0x0000000000011978 0x0000000000022978 0x0000000000022978
Info (OR_PD)                0x0000000000001160 0x0000000000001230 RW-    1000

Equation of best fit is: y = 25792.20x + 9449.96

Info
Info ---------------------------------------------------
Info CPU 'riscvOVPsim/cpu' STATISTICS
Info   Type                  : riscv (RV64GCV)
Info   Nominal MIPS          : 100
Info   Final program counter : 0x1ed6c
Info   Simulated instructions: 165,684
Info   Simulated MIPS        : run too short for meaningful result
Info ---------------------------------------------------
Info
Info ---------------------------------------------------
Info SIMULATION TIME STATISTICS
Info   Simulated time        : 0.00 seconds
Info   User time             : 0.03 seconds
Info   System time           : 0.00 seconds
Info   Elapsed time          : 0.05 seconds
Info ---------------------------------------------------

riscvOVPsimPlus finished: Wed Jun  2 12:29:48 2021


riscvOVPsimPlus (64-Bit) v20210329.0 Open Virtual Platform simulator from www.IMPERAS.com.
Visit www.IMPERAS.com for multicore debug, verification and analysis solutions.
```
<br/>

#  **Matrix and Vector Examples**

Aside from Linear Regression, other vector implementations available in this repository are the following:

* Matrix Addition
* Matrix Subtraction
* Matrix Multiplication
* Matrix Transpose
* Matrix-Scalar Addition
* Matrix-Scalar Subtraction
* Matrix-Scalar Multiplication
* Vector-Vector Addition
* Vector-Vector Subtraction
* Vector-Vector Multiplication
* Vector-Scalar Addition
* Vector-Scalar Subtraction
* Vector-Scalar Multiplication
<br/><br/>

## **Compilation and Running for Matrix Examples**
```
# run these commands in Ubuntu Terminal

# MATRIX OPERATIONS WITH VECTOR EXTENSION
$ cd examples-vector/matrix
$ ./compile.sh
$ ./run.sh

# MATRIX OPERATIONS WITHOUT VECTOR EXTENSION
$ cd examples-no-vector/matrix
$ ./compile.sh
$ ./run.sh
```
## **Compilation and Running for Vector Examples**
```
# run these commands in Ubuntu Terminal

# VECTOR OPERATIONS WITH VECTOR EXTENSION
$ cd examples-vector/vector
$ ./compile.sh
$ ./run.sh

# VECTOR OPERATIONS WITHOUT VECTOR EXTENSION
$ cd examples-no-vector/vector
$ ./compile.sh
$ ./run.sh
```
# **Matrix and Vector Examples on Big Data**

Also provided in the repository a sample performance of matrix and vector operations using Vector Extension on big data.

## **Compilation and Running for Matrix and Vector Examples on Big Data**

```
# run these commands in Ubuntu Terminal

# WITH VECTOR EXTENSION
$ cd examples-vector/big-data
$ ./compile.sh
$ ./run.sh

# WITHOUT VECTOR EXTENSION
$ cd examples-no-vector/big-data
$ ./compile.sh
$ ./run.sh
```

## **Sample Showcase on Logistic Regression**
cd logistic-regression-vector
./compile_logistic.sh
./run_logistic.sh

# **Authors**

* John Andrew Ing
* Stanley Lawrence Sie
