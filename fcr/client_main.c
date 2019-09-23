#include "client.h"

#include <pthread.h>

#include "log.h"
#include "nextpth.h"
#include "client_menu.h"

int main()
{
    //pthread_t thid;

    set_log_level(LOG_DEBUG);

    client_init(&client);

    client_start(&client);

    //pthread_create(&thid, NULL, refresha, (void *)&client);

    cli_show_menu();

    client_destroy(&client);

    return 0;
}
