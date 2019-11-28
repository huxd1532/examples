#include "common.h"


static void listen_signal(DBusConnection *conn)
{
	DBusMessage * msg;
 	DBusMessageIter arg;
	//long int sigvalue;
	dbus_int64_t sigvalue;

    	dbus_bus_add_match(conn,"type='signal',interface='com.deepin.Example1'", get_error());
    	dbus_connection_flush(conn);
    	if(error_is_set()){
		print_error("Match Error");
		return;
	}

	while(1)
	{
		dbus_connection_read_write (conn,0);
		msg = dbus_connection_pop_message (conn);

		if(msg == NULL){
			sleep(1);
			continue;
        	}
		
 		if(dbus_message_is_signal(msg, INTERFACE_NAME, SIGANL_NAME) ){
 			if(!dbus_message_iter_init(msg,&arg) )
				print_error("Message has no param");
 			else if(dbus_message_iter_get_arg_type(&arg) != DBUS_TYPE_INT64)
 				print_error("Param is not int64");
 			else{
				sigvalue = 0;
				dbus_message_iter_get_basic(&arg,	&sigvalue);
				printf("Got Singal with value : %ld\n",	sigvalue);
 			}
 		}
		dbus_message_unref(msg);
	}
}


int main(int argc, char **argv)
{
	DBusConnection *conn;

	error_init();

	//conn = create_dbus_conn(SERVER_BUS_NAME);
	conn = create_dbus_conn("com.deepin.Example2");
    
	listen_signal(conn);
	return 0;
}

