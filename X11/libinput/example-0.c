#include <errno.h>
#include <stdio.h>
#include <libinput.h>
#include <libudev.h>
//#include <libevdev/libevdev.h>
static int open_restricted(const char *path, int flags, void *user_data)
{
        int fd = open(path, flags);
        return fd < 0 ? -errno : fd;
}
 
static void close_restricted(int fd, void *user_data)
{
        close(fd);
}
 
const static struct libinput_interface interface = {
        .open_restricted = open_restricted,
        .close_restricted = close_restricted,
};
 
 
int main(void) {
        struct libinput *li;
        struct libinput_event *event;
        struct udev *udev = udev_new();

        li = libinput_udev_create_context(&interface, NULL, udev);
        libinput_udev_assign_seat(li, "seat0");
        libinput_dispatch(li);
 
        while ((event = libinput_get_event(li)) != NULL) {
 
                // handle the event here
 
                libinput_event_destroy(event);
                libinput_dispatch(li);
        }
 
        libinput_unref(li);
 
        return 0;
}