#include <grabby.h>
#include <string.h>
#include <stdio.h>

#define ENDPOINT "org.libgrabby.endpoint"


int grabby_init(grabby_ctx *ctx)
{
    memset(ctx, 0, sizeof(grabby_ctx));

//    /* Create a new bus connection */
//    ctx->c = dbus_bus_get(DBUS_BUS_SESSION, &ctx->err);
//
//    /** Check if the session is now open */
//    if(dbus_error_is_set(&ctx->err)) {
//        fprintf(stderr, "Connection Error (%s)\n", ctx->err.message);
//        dbus_error_free(&ctx->err);
//    }
//
//    int ret;
//    ret = dbus_bus_request_name(ctx->c, ENDPOINT, DBUS_NAME_FLAG_REPLACE_EXISTING, &ctx->err);
//
//    if(dbus_error_is_set(&ctx->err)) {
//        fprintf(stderr, "Name Error (%s)\n", ctx->err.message);
//        dbus_error_free(&ctx->err);
//    }
//
//    if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret) {
//        return GRABBY_FAILED_REGISTER;
//    }


    return 0;
}


int grabby_register(grabby_ctx *ctx, const char *signal, void (*callback)(int, int))
{

    return 0;
}


int grabby_free(grabby_ctx *ctx)
{

    return 0;
}
