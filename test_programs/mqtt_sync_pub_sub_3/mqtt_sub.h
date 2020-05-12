/* MQTT Subscriber Library [ Header File ]
 *
 *              Author : Viki (a) Vignesh Natarajan
 *              Firma  : vikiworks.io              
 */
#ifndef MQTT_SUBSCRIBER_H
#define MQTT_SUBSCRIBER_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "MQTTClient.h"

extern pthread_t subscriber_thread;
extern volatile int exit_mqtt_subscriber;
extern volatile MQTTClient_deliveryToken delivered_token;

extern int mqtt_subscribe();
extern void *mqtt_subscribe_thread();
extern int mqtt_unsubscribe();
#endif


