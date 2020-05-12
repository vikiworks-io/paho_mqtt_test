/* MQTT Subscriber Library
 *
 *              Author : Viki (a) Vignesh Natarajan
 *              Firma  : vikiworks.io               
 */

#include <unistd.h>
#include <pthread.h>
#include "mqtt_common.h"
#include "mqtt_sub.h"

static MQTTClient mqtt_subscriber;
pthread_t subscriber_thread;

volatile int exit_mqtt_subscriber = 0;

int mqtt_subscribe()
{
    int ret = 0;

    ret = pthread_create(&subscriber_thread, NULL, mqtt_subscribe_thread, NULL);

    if(ret !=0)
        return -1;

    return 0;
}

void *mqtt_subscribe_thread()
{
    int ret;
    

    while(mqtt_broker_connected == 0){
        printf("%s connecting to broker\n", S_MS);
        mqtt_connect();
        sleep(2);
    }

    printf("%s subscribing to topic %s\n", S_MS, MQTT_TOPIC);
    MQTTClient_subscribe(mqtt_handle, MQTT_TOPIC, QOS);
    
    while(exit_mqtt_subscriber == 0){
        
        /* reconnect and subscribe on connection lost */
        if(mqtt_broker_connected == 0){
            MQTTClient_subscribe(mqtt_handle, MQTT_TOPIC, QOS);
        }
        
        sleep(1);
    }

    mqtt_disconnect();

    pthread_exit(NULL); 
}

int mqtt_unsubscribe()
{
    exit_mqtt_subscriber = 1;
    pthread_join(subscriber_thread, NULL); 
    return 0;
}
