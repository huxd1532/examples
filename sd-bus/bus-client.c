#include <stdio.h>
#include <stdlib.h>
#include <systemd/sd-bus.h>

const char *const SERVICE_NAME = "com.deepin.Example";
const char *const OBJECT_PATH_NAME = "/com/deepin/Example";
const char *const INTERFACE_NAME = "com.deepin.Example";
const char *const METHOD_NAME = "STRTOINT";

int main(int argc, char *argv[]) {
        sd_bus_error error = SD_BUS_ERROR_NULL;
        sd_bus_message *m = NULL;
        sd_bus *bus = NULL;
        const char *path;
        int n,r;

        /* Connect to the system bus */
        r = sd_bus_open_user(&bus);
        if (r < 0) {
                fprintf(stderr, "Failed to connect to system bus: %s\n", strerror(-r));
                goto finish;
        }

        /* Issue the method call and store the respons message in m */
        r = sd_bus_call_method(bus,
                               SERVICE_NAME,           /* service to contact */
                               OBJECT_PATH_NAME,       /* object path */
                               INTERFACE_NAME,         /* interface name */
                               METHOD_NAME,                          /* method name */
                               &error,                               /* object to return error in */
                               &m,                                   /* return message on success */
                               "s",                                 /* input signature */
                               "123");                           /* argument */
        if (r < 0) {
                fprintf(stderr, "Failed to issue method call: %s\n", error.message);
                goto finish;
        }
        /* Parse the response message */
        r = sd_bus_message_read(m, "x", &n);
        if (r < 0) {
                fprintf(stderr, "Failed to parse response message: %s\n", strerror(-r));
                goto finish;
        }

        printf("Result is %d\n", n);

finish:
        sd_bus_error_free(&error);
        sd_bus_message_unref(m);
        //sd_bus_unref(bus);
        return r < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}

