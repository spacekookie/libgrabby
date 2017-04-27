#include <grabby.h>
#include <string.h>
#include <stdio.h>
#include <zconf.h>
#include <stdbool.h>
#include <stdint.h>

#define ENDPOINT "org.libgrabby.endpoint"
#define EAVESDROPPING_RULE "eavesdrop=true"


int grabby_init(grabby_ctx *ctx)
{
    memset(ctx, 0, sizeof(grabby_ctx));

    /* Create a new bus connection */
    ctx->c = dbus_bus_get(DBUS_BUS_SESSION, &ctx->err);

    /** Check if the session is now open */
    if(dbus_error_is_set(&ctx->err)) {
        fprintf(stderr, "Connection Error (%s)\n", ctx->err.message);
        dbus_error_free(&ctx->err);
    }

    int ret;
    dbus_bus_add_match (ctx->c, EAVESDROPPING_RULE ",type='method_call'", &ctx->err);

    ret = dbus_bus_request_name(ctx->c, ENDPOINT, DBUS_NAME_FLAG_REPLACE_EXISTING, &ctx->err);

    if(dbus_error_is_set(&ctx->err)) {
        fprintf(stderr, "Name Error (%s)\n", ctx->err.message);
        dbus_error_free(&ctx->err);
    }

    if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret) {
        return GRABBY_FAILED_REGISTER;
    }


    return 0;
}


// FIXME: Currently abusing this function to experiment with D-Bus...
int grabby_register(grabby_ctx *ctx, void (*callback)(const char*, const char*))
{

    /* Listen to all method_call notifications that exist */
    dbus_bus_add_match(ctx->c, "type='method_call',interface='org.freedesktop.Notifications'", &ctx->err);
    dbus_connection_flush(ctx->c);

    if (dbus_error_is_set(&ctx->err)) {
        fprintf(stderr, "Match Error (%s)\n", ctx->err.message);
        return GRABBY_FAILED_REGISTER;
    }

    /** Storage for things and stuff */
    DBusMessage *msg;
    DBusMessageIter iter;
    char *songname, *artist, *sigvalue2;

    /** Listen until the universe explodes */
    while (1) {
        dbus_connection_read_write(ctx->c, 0);
        msg = dbus_connection_pop_message(ctx->c);

        if (NULL == msg) {
            continue;
        }

        if (dbus_message_iter_init(msg, &iter)) {
            dbus_message_iter_get_basic(&iter, &sigvalue2);

            // HACK: Just hardcode that we want notifications from Spotify
            if(strcmp(dbus_message_get_member(msg), "Notify") == 0 && strcmp(sigvalue2, "Spotify") == 0) {

                //
                printf("=== NOW PLAYING ===");

                while (dbus_message_iter_next(&iter)) {
                    int type = dbus_message_iter_get_arg_type(&iter);

                    // HACK: Check if it's fixed first because otherwise check2 might sigsegv
                    if(!dbus_type_is_fixed(type) && dbus_type_is_basic(type)) {
                        dbus_message_iter_get_basic(&iter, &songname);
                        printf("%s\n", songname);
                    }
                }
            }
        }


        dbus_message_unref(msg);
    }

    return 0;
}


int grabby_free(grabby_ctx *ctx)
{

    return 0;
}
