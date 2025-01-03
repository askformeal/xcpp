# XGCC

简体中文 | [English](README.md)

XGCC可以让您更加高效的运行C++源代码。

![Logo](https://github.com/askformeal/xgcc/assets/109349321/d6db2458-8334-41cd-9ed8-10e3675ee7d8)

## 要求

该软件目前只支持Windows版本，我以后可能会开发Linux版。

xgcc**不**包含编译器，您需要自行安装GNU编译器。打开CMD并输入 `g++ --version`以检查编译器是否安装。

如果您想编译v1.0.0或1.1.0版的源代码，请确保 `bits/stdc++.h`头文件可用。

## 功能

一个命令即可运行C++源代码

执行和编译计时

运行完成后自动删除可执行文件

O1、O2和O3优化支持

没有复杂的安装过程

## 安装说明

如果您下载了.exe文件，复制到 `C:\Windows\System32`或其他系统变量路径即可。

如果您下载了源代码，请自行编译为xgcc.exe并将其复制到 `C:\Windows\System32`或其他系统变量路径。

## 使用说明

### 格式

xgcc [文件名] [参数1，参数2……]
xgcc -h
xgcc -help

“-”开头的参数会被视作选项，其余的会被传入可执行文件。

### 选项

-R 运行后保留可执行文件

-O1 使用O1优化

-O2 使用O2优化

-O3 使用O3优化

-V/VERSION 显示版本信息

-H/HELP 显示帮助信息


## 反馈

您可以在洛谷上[私信我](https://www.luogu.com.cn/chat?uid=787042)，发邮件到zeus1014_2023@163.com或创建一个新的Issue。
