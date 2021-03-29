## 一、编译

### 1、glxinfo

* gcc glinfo_common.c  glxinfo.c -o glxinfo -lGLEW -lGLU -lGL -lX11


### 2、glthreads
*  gcc glinfo_common.c  glthreads.c -o glthreads -lGLEW -lGLU -lGL -lX11 -lXext -lm -lpthread

### 3、glxgears
* gcc glinfo_common.c  glxgears.c -o test   -lGL  -lX11  -lm

### 4、glxdemo
* gcc glxdemo.c -o glxdemo -lGL   -lX11