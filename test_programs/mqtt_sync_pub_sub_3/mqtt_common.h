#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "MQTTClient.h"
#define MQTT_TOPIC  "my_topic" 
#define MQTT_ADDRESS "tcp://mqtt.eclipse.org:1883"
#define MQTT_CLIENT_ID "client1"
#define MQTT_USERNAME NULL
#define MQTT_PASSWORD NULL
#define QOS             1
#define TIMEOUT                 10000L

#define S_MS_CB "[ mqtt_sub - callback    ]"
#define S_MS    "[ mqtt_sub               ]"

#define S_MP_CB "[ mqtt_pub - callback    ]"
#define S_MP    "[ mqtt_pub               ]"

#define S_MC_CB "[ mqtt_client - callback ]"
#define S_MC    "[ mqtt_client            ]"

extern int mqtt_broker_connected;
extern MQTTClient mqtt_handle;

extern int CB_MessageArrived(void *context, char *topic_name, int topic_len, MQTTClient_message *message);
extern void CB_MessageDelivered(void *context, MQTTClient_deliveryToken token);
extern void CB_ConnectionLost(void *context, char *reason);



extern int mqtt_connect();
extern int mqtt_reconnect();
extern int mqtt_disconnect();
