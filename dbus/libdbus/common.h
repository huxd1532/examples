#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <dbus/dbus.h>
#include <unistd.h>

#define SERVER_BUS_NAME "com.deepin.Example1"
#define OBJECT_PATH_NAME "/com/deepin/Example1"
#define INTERFACE_NAME "com.deepin.Example1"
#define METHOD_NAME "STRTOINT"
#define SIGANL_NAME "COUNT_CHANGED"

void print_error(char *str);
int error_is_set(void);
void error_init(void);
void dump_msg(DBusMessage * msg);
DBusConnection *create_dbus_conn(const char *bus_name);
DBusError *get_error(void);
#endif