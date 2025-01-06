# XGCC

English | [简体中文](README_CN.md)

xgcc is a tool to run C++ source code more efficiently.
![Logo](https://github.com/askformeal/xgcc/assets/109349321/d6db2458-8334-41cd-9ed8-10e3675ee7d8)

## Requirements

This software only works on Windows systems. I might create a Linux Version later.

xgcc is NOT a compiler, you'll have to install GNU compiler yourself. Open CMD and enter `g++ --version` to check if you already have it.

If you want to compile the source code of v1.0.0 or v1.1.0 yourself, make sure you can use the `bits/stdc++.h` header file.

---

## Features

Run cpp file with a single command

Executing and compiling timing

Automatically delete the executable file after run it

O1, O2 and O3 	optimization

No complex installation needed

---

## How to install

If you downloaded the .exe file, just copy it into `C:\Windows\System32` or another system variable folder.

If you downloaded the source code, you'll have to compile it yourself and make sure the generated .exe file is named "xgcc.exe" and then copy it into `C:\Windows\System32` or another system variable folder.

---

## How to use

### Usage

xgcc [file name] [argument 1, argument 2 ...]
xgcc -h
xgcc -help

arguments starts with "-" will be taken as "options", while others will be passed into the executable file.

### Options

* -R Do not delete executable file after executing
* -O1 Use O1 optimization
* -O2 Use O2 optimization
* -O3 Use O3 optimization
* -C Compile only
* -V/-VERSION show version information
* -H/-HELP show this help information

## Feedback

You can [chat with me](https://www.luogu.com.cn/chat?uid=787042) on Luogu, send an E-mail to zeus1014_2023@163.com or create a new issue.
