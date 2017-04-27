#ifndef _GRABBY_H
#define _GRABBY_H

#include <dbus-1.0/dbus/dbus.h>
#include <dbus-1.0/dbus/dbus-glib.h>


typedef struct grabby_ctx {
    DBusConnection  *c;
    DBusError       err;
} grabby_ctx;


#define GRABBY_OK               (0 << 0)
#define GRABBY_FAILED_INIT      (1 << 1)
#define GRABBY_FAILED_REGISTER  (1 << 2)


int grabby_init(grabby_ctx *);

int grabby_register(grabby_ctx *ctx, void (*callback)(const char*, const char*));

int grabby_free(grabby_ctx *);

#endif //_GRABBY_H
