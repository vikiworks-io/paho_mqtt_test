#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "mqtt_common.h"
#include "mqtt_sub.h"
#include "mqtt_pub.h"

int exit_application = 0;

void signal_handler(int val)
{
    exit_application = 1;
}

int main()
{
    int i = 0;
    int ret = 0;
    signal(SIGINT, signal_handler);
    char buf[1024];
    mqtt_subscribe();
   
    sleep(4);

    while(!exit_application)
    {
        sprintf(buf,"message_%d",i);
        ret = mqtt_publish(buf);

        if( ret == -2 ){
            printf("%s unable to publish, connection lost or not established\n", S_MC);
        }
        
        sleep(10);
        i++;
    }

    mqtt_unsubscribe();

    return 0;
}
