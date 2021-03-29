#include<X11/Xlib.h>
#include<stdio.h>
#include <X11/extensions/dpms.h>
#include <unistd.h>
#include<string.h>
void usage(void)
{
	printf("params is invaild!\n");
	printf("dpms-ctl [on/off]\n");
}

int main(int argc, void *argv[])
{
	Display *dpy;
	if (argc != 2)
	{
		usage();
		return -1;
	}
	
	dpy = XOpenDisplay(NULL);
	if(dpy == NULL){
		printf("Cannot open display\n");
		return -1;
	}
	
	if(!strcmp(argv[1], "off")){
		DPMSEnable(dpy);
		sleep(1);
		DPMSForceLevel(dpy, DPMSModeOff);
	}else if (!strcmp(argv[1], "on"))
	{
		DPMSEnable(dpy);
		DPMSForceLevel(dpy, DPMSModeOn);
	}else{
		usage();
		XCloseDisplay(dpy);
		return -1;
	}
	XCloseDisplay(dpy);
	return 0;
}
