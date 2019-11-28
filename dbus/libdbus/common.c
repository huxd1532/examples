#include "common.h"

static DBusError dbus_error;

void print_error(char *str)
{
    fprintf(stderr, "%s: %s\n", str, dbus_error.message);
    dbus_error_free(&dbus_error);
}

void error_init(void)
{
	dbus_error_init(&dbus_error);
}

DBusError *get_error(void)
{
	return &dbus_error;
}

int error_is_set(void)
{
	return dbus_error_is_set(&dbus_error);
}

DBusConnection *create_dbus_conn(const char *bus_name)
{
    DBusConnection *conn;
    int ret;

    /*建立与dbus-daemon的连接*/
    conn = dbus_bus_get(DBUS_BUS_SESSION, &dbus_error);

    if (error_is_set()) {
        print_error("dbus_bus_get");
    }

    if (!conn) {
        return NULL;
    }

    if ( NULL != bus_name )
    	{
    		/*给连接指定一个名字*/
    		ret = dbus_bus_request_name(conn, bus_name, DBUS_NAME_FLAG_DO_NOT_QUEUE, &dbus_error);

    		if (error_is_set()) {
        		print_error("dbus_bus_request_name");
    		}

   		if (ret != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) {
        		print_error("not primary owner");
   		}
    	}
    return conn;
}


void dump_msg(DBusMessage * msg)
{
	DBusMessageIter arg;
	char * string_val;
	dbus_int64_t int64_val;
	int type;
	if(!dbus_message_iter_init(msg, &arg)){
			print_error("Message has no args");
	}

	type = dbus_message_iter_get_arg_type(&arg);

	switch ( type )
		{
		case DBUS_TYPE_STRING:
			{
				dbus_message_iter_get_basic(&arg,  &string_val);
				printf("sting msg val:%s\n", string_val);
				break;
			}
		case DBUS_TYPE_INT64:
			{
				dbus_message_iter_get_basic(&arg,  &int64_val);
				printf("int64 msg val:%ld\n", int64_val);
				break;
			}
		default:
			{
				print_error("Error type!\n");
				break;
			}
		}
	
}



