#include "common.h"

static dbus_int64_t  g_count;

static int StrToInt(char *str)
{
    return atoi(str);
}

DBusMessage *create_signal_msg(const char *object_path, const char *interface_name, const char *name, dbus_int64_t *value)
{
    DBusMessage * msg;
    DBusMessageIter arg;
    /*创建一个Message, 指定对象、接口、信号名*/
    msg = dbus_message_new_signal (object_path, interface_name, name);
    if(!msg)
    {
        print_error("Message NUL");
        return msg;
    }
    /*给这个msg添加具体内容*/
    dbus_message_iter_init_append (msg,&arg);
    if(!dbus_message_iter_append_basic (&arg,DBUS_TYPE_INT64, value)){
        print_error("Append Message failed!");
        return NULL;
    }
    return msg;
}



int send_msg(DBusConnection *conn, DBusMessage * msg)
{
    dbus_uint32_t  serial = 0;
    if( NULL == msg )
    {
        print_error("msg is NULL!\n");
    }
    /*将信号从连接中发送*/
    if( !dbus_connection_send (conn, msg, &serial)){
        print_error("Send message failed!");
        return -1;
    }
    dbus_connection_flush (conn);
    return 0;
}


void free_msg(DBusMessage * msg)
{
    dbus_message_unref(msg );
}


int send_singal(DBusConnection *conn, dbus_int64_t  *sigvalue)
{
	DBusMessage * msg;
	msg = create_signal_msg(OBJECT_PATH_NAME, INTERFACE_NAME, SIGANL_NAME, sigvalue);
	send_msg( conn,  msg);
	free_msg(msg);
	return 0;
}

static int method_str_to_int_process(DBusConnection *conn, DBusMessage * msg)
{
	DBusMessageIter arg;
	char * param = NULL;
	DBusMessage * reply;
	long int result = 0;
	if(!dbus_message_iter_init(msg, &arg)){
		print_error("Message has no args");
	}else if(dbus_message_iter_get_arg_type(&arg) != DBUS_TYPE_STRING){
		print_error("Arg is not string");
	}else{
		dbus_message_iter_get_basic(&arg,  &param);
	}
	if ( NULL == param)
	{
		return -1;
	}
	g_count ++;
	send_singal(conn, &g_count);
	result = StrToInt(param);
	/*创建返回消息reply*/
	reply = dbus_message_new_method_return(msg);

	/*在返回消息中填入参数*/
	dbus_message_iter_init_append(reply, &arg);
	if(!dbus_message_iter_append_basic (&arg, DBUS_TYPE_INT64, &result)){
		print_error("Out of Memory!");
		return -1;
	}
	/*发送返回消息*/
	if(send_msg(conn, reply)){
		print_error("Send message failed!");
		return -1;
	}
	/*释放消息*/
	free_msg(reply);
	return 0;
}

static void listen_dbus(DBusConnection *conn)
{
    DBusMessage * msg;
    while(1)
    {
        dbus_connection_read_write (conn,0);
        msg = dbus_connection_pop_message (conn);

        if(msg == NULL){
            sleep(1);
            continue;
        }
	 if(strcmp(dbus_message_get_path(msg), OBJECT_PATH_NAME)){
	 	sleep(1);
            continue;
	 }
        if(dbus_message_is_method_call(msg, INTERFACE_NAME, METHOD_NAME)){
			
                method_str_to_int_process(conn, msg);
        }
        free_msg(msg);
    }
}

int main(int argc, char **argv)
{
	DBusConnection *conn;
	error_init();

	conn = create_dbus_conn(SERVER_BUS_NAME);
    
	listen_dbus(conn);
}
