#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <systemd/sd-bus.h>

const char *const SERVICE_NAME = "com.deepin.Example";
const char *const OBJECT_PATH_NAME = "/com/deepin/Example";
const char *const INTERFACE_NAME = "com.deepin.Example";
const char *const METHOD_NAME = "STRTOINT";

static int StrToInt(char *str)
{
    return atoi(str);
}

static int method_StrToInt(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {
    char *s = NULL;
    int n, r;

    /* Read the parameters */
    r = sd_bus_message_read(m, "s", &s);

    if (r < 0) {
        fprintf(stderr, "Failed to parse parameters: %s\n", strerror(-r));
        return r;
    }

    n = StrToInt(s);
    /* Reply with the response */
    return sd_bus_reply_method_return(m, "x", n);
}

static const sd_bus_vtable obj_vtable[] = {
    SD_BUS_VTABLE_START(0),
    SD_BUS_METHOD(METHOD_NAME, "s", "x", method_StrToInt, SD_BUS_VTABLE_UNPRIVILEGED),
    SD_BUS_VTABLE_END
};

int main(int argc, char *argv[]) {
    sd_bus_slot *slot = NULL;
    sd_bus *bus = NULL;
    int r;
    
    /* Connect to the user bus this time */
    r = sd_bus_open_user(&bus);
    if (r < 0) {
            fprintf(stderr, "Failed to connect to system bus: %s\n", strerror(-r));
            goto finish;
    }
    
    /* Install the object */
    r = sd_bus_add_object_vtable(bus,
                                 &slot,
                                 OBJECT_PATH_NAME,  /* object path */
                                 INTERFACE_NAME,   /* interface name */
                                 obj_vtable,
                                 NULL);
    if (r < 0) {
        fprintf(stderr, "Failed to issue method call: %s\n", strerror(-r));
        goto finish;
    }

    /* Take a well-known service name so that clients can find us */
    r = sd_bus_request_name(bus, SERVICE_NAME, 0);
    if (r < 0) {
        fprintf(stderr, "Failed to acquire service name: %s\n", strerror(-r));
        goto finish;
    }

    for (;;){
        /* Process requests */
        r = sd_bus_process(bus, NULL);
        if (r < 0) {
            fprintf(stderr, "Failed to process bus: %s\n", strerror(-r));
            goto finish;
        }
        if (r > 0) /* we processed a request, try to process another one, right-away */
            continue;

        /* Wait for the next request to process */
        r = sd_bus_wait(bus, (uint64_t) -1);
        if (r < 0) {
            fprintf(stderr, "Failed to wait on bus: %s\n", strerror(-r));
            goto finish;
        }
    }
    finish:
        sd_bus_slot_unref(slot);
        sd_bus_unref(bus);
        return r < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}

