## 1、概述
* 这是一个使用 Xlib 和 XCB 计算创建 500 个atoms所需时间的程序。它显示了 Xlib 方式、坏的 XCB 方式（类似于 Xlib）和好的 XCB 方式。在我的电脑上，XCB 比 Xlib 快 25 倍。

## 2、编译
``` gcc exampe-1.c  -o exampe-1 -lxcb -lX11```
或者
```gcc -Wall exampe-1.c -o exampe-1 `pkg-config --cflags --libs xcb` -lX11```