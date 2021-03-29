#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>

int main ()
{
    int fd;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    size_t screensize = 0;
    int location;
    char *fbp = NULL, *ptr;
    int x, y, x0, y0;
    int i,j;
    int ret;
 
    fd = open("/dev/fb0", O_RDWR);
    if (fd < 0){
        fprintf(stderr, "error open fb0\n");
        return -1;
    }

    ret= ioctl(fd, FBIOGET_FSCREENINFO, &finfo ) ;
    if (ret < 0) {
        fprintf(stderr, "get fixed screen info error\n");
        return -1;
    }

    ret = ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
    if (ret < 0) {
        fprintf(stderr, "get variable screen info error\n");
        return -1;
    }

    ret = ioctl(fd, FBIOPAN_DISPLAY,&vinfo);
    if (ret < 0) {
        fprintf(stderr, "pan display failed\n");
        return -1;
    }

    screensize=vinfo.xres * vinfo.yres * vinfo.bits_per_pixel /8 ;
    fbp = (char *)mmap(NULL, screensize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (fbp == MAP_FAILED) {
        fprintf(stderr, "mapped error\n");
        return -1;
    }
    x0 = 200;
    y0 = 200;
    ptr = fbp + y0 * finfo.line_length + x0 * vinfo.bits_per_pixel / 8;
    for( i = 0; i < 100; i++){
        char* tmp_ptr = ptr;
        for(j = 0; j < 100; j++){
            *tmp_ptr++ = 0;
            *tmp_ptr++ = 255;
            *tmp_ptr++ = 0;
            *tmp_ptr++ = 0;
        }
        ptr += finfo.line_length;
    }
    munmap(fbp,screensize);
    close(fd);
    return 0;
}
