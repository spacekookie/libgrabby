#include <grabby.h>

int main(int argn, char **argv)
{
    grabby_ctx ctx;
    int ret = grabby_init(&ctx);

    ret = grabby_register(&ctx, NULL);
}