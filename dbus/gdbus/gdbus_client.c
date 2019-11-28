#include <glib.h>
#include <gio/gio.h>
#include <stdio.h>
#include "Building.h"

static gboolean count_changed_handler(Example2* object, gint count, gpointer user_data)
{
	g_print("signal received %d\n",count);
 	return TRUE;
}


int main(int argc, char *argv[])
{
	Example2*proxy=NULL;
	GError *error = NULL;
	GMainLoop* loop = NULL;

	proxy = example2_proxy_new_for_bus_sync (
		G_BUS_TYPE_SESSION,
		G_DBUS_PROXY_FLAGS_NONE,
		"com.deepin.Example2",
		"/com/deepin/Example2",
		NULL,
		&error);

	if(0 == proxy)
	{
		g_print("Failed to create proxy. Reason: %s.\n", error->message);
	}

	g_signal_connect(proxy,"count-changed",G_CALLBACK(count_changed_handler),NULL);

	gint64 reply;
	example2_call_str_to_int_sync(proxy, "123", &reply, NULL, &error);
	g_print("reply = %ld\n",reply);

	loop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(loop);

	g_object_unref(proxy);
	return 0;
}
