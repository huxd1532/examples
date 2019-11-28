#include "common.h"

static DBusMessage *create_method_msg(const char * bus_name, const char *object_path, const char *interface_name, const char *name, const char *str)
{
    DBusMessage * msg;
    DBusMessageIter arg;
    /*创建一个Message, 指定对象、接口、信号名*/
    msg = dbus_message_new_method_call (bus_name, object_path, interface_name, name);
    if(!msg)
    {
        print_error("Message NUL");
        return msg;
    }
    /*给这个msg添加具体内容*/
    dbus_message_iter_init_append (msg, &arg);
    if(!dbus_message_iter_append_basic (&arg, DBUS_TYPE_STRING, &str)){
        print_error("Append message failed!");
        return NULL;
    }
    return msg;
}

int main(int argc, char **argv)
{
	DBusConnection *conn;
	DBusMessage * msg;
	DBusMessageIter arg;
	DBusPendingCall *pending;
	DBusMessage *reply;
	long int result;

	if ( argc  < 2 )
	{
		printf("Input args is too few\n");
		return -1;
	}
	
	error_init();

	conn = create_dbus_conn( "com.deepin.Example3");

	msg = create_method_msg(SERVER_BUS_NAME, OBJECT_PATH_NAME, INTERFACE_NAME, METHOD_NAME, argv[1]);

	if(!dbus_connection_send_with_reply (conn, msg, &pending, -1))
	{
		return -1;
	}

	 if( NULL == pending )
	 {
	 	return -1;
	 }
	 dbus_connection_flush(conn);
	 dbus_message_unref(msg);

	 dbus_pending_call_block(pending);

	 if(NULL==(reply = dbus_pending_call_steal_reply (pending)))
	 {
	 	return -1;
	 }
	 dbus_pending_call_unref(pending);

	 if (dbus_message_get_args(reply, get_error(), DBUS_TYPE_INT64, &result, DBUS_TYPE_INVALID)) {
		printf("Reply: %d\n", result);
	 } else {
		print_error ("Did not get arguments in reply\n");
		return -1;
	 }
	 dbus_message_unref(reply);

	 return 0;
	
}


