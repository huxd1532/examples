#include <glib.h>
#include <gio/gio.h>
#include <stdio.h>
#include "Building.h"

static Example2* skeleton=NULL;
gint64 g_count = 0;

static gboolean on_example2_emit_count_changed(gconstpointer p)          
{                                                         
    example2_emit_count_changed(skeleton, g_count);
    return TRUE;                                          
}  


static  gboolean on_handle_str_to_int(Example2* skeleton,
        GDBusMethodInvocation *invocation,
        const gchar *str,
        gpointer user_data)
{
	printf("on_handle_str_to_int is called.\n");
	g_count++;
	int result = atoi(str);
	example2_complete_str_to_int (skeleton,invocation, result);
	return TRUE;
}


static void on_bus_acquired(GDBusConnection *connection,
		const gchar *name,
		gpointer user_data)
{
	GError *error = NULL;
	printf("on_bus_acquired has been invoked\n");
	printf("on_bus_acquired the name = %s\n",name);
    	printf("on_bus_acquired the user_data = %s\n",(char*)user_data);

	skeleton =  example2_skeleton_new();
    	g_signal_connect(skeleton,"handle-str-to-int",G_CALLBACK(on_handle_str_to_int),NULL);

	g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(skeleton), connection, "/com/deepin/Example2", &error);
	if(error != NULL){                                                           
       	 g_print("Error: Failed to export object. Reason: %s.\n", error->message);
        	g_error_free(error);                                                     
    } 

}

static void on_name_acquired(GDBusConnection *connection,
		const gchar *name,
		gpointer user_data)
{
    printf("on_name_acquired has been invoked\n");
}

static void on_name_lost(GDBusConnection *connection,
		const gchar *name,
		gpointer user_data)
{
    printf("on_name_lost has been invoked\n");
}

int main(int argc, char *argv[])
{
	GMainLoop *loop = NULL;
	guint owner_id;

	owner_id = g_bus_own_name(G_BUS_TYPE_SESSION,
			"com.deepin.Example2",
			G_BUS_NAME_OWNER_FLAGS_NONE,
			on_bus_acquired,
			on_name_acquired,
			on_name_lost,
			NULL,
			NULL);

 	/* * emit my signal1 every 1 second to trigger example communication */
    	g_timeout_add(1000, (GSourceFunc)on_example2_emit_count_changed, NULL);

	loop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(loop);  

	g_bus_unown_name(owner_id);

	return 0;
}
