#include "mqtt_common.h"

MQTTClient mqtt_handle;

MQTTClient_connectOptions conn_params = MQTTClient_connectOptions_initializer;
volatile MQTTClient_deliveryToken delivered_token;

int mqtt_broker_connected = 0;
int CB_MessageArrived(void *context, char *topic_name, int topic_len, MQTTClient_message *message)
{
    int i, payload_len;
    char *payload;
    
    printf("%s message arrived  -> ", S_MS_CB);
    
    payload = message->payload;
    payload_len = message->payloadlen;

    for(i=0; i < payload_len; i++)
    {
        putchar(*payload++);
    }
    putchar('\n');
    
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topic_name);
   
    return 1;
}

void CB_MessageDelivered(void *context, MQTTClient_deliveryToken token)
{
    printf("%s message delivered  %d\n", S_MP_CB, token);
    delivered_token = token;
}


void CB_ConnectionLost(void *context, char *reason)
{
    mqtt_broker_connected = 0;
    printf("%s connection lost ( %s )\n", S_MC_CB, reason);
}


int mqtt_connect()
{
    int ret = 0;

    MQTTClient_create(&mqtt_handle, MQTT_ADDRESS, MQTT_CLIENT_ID, MQTTCLIENT_PERSISTENCE_NONE, NULL);

    conn_params.username = MQTT_USERNAME;
    conn_params.password = MQTT_PASSWORD;
    conn_params.keepAliveInterval = 10;
    conn_params.cleansession = 1;
    
    MQTTClient_setCallbacks(mqtt_handle, NULL, CB_ConnectionLost, CB_MessageArrived, CB_MessageDelivered);


    ret = MQTTClient_connect(mqtt_handle, &conn_params);

    if (ret != MQTTCLIENT_SUCCESS )
    {
        mqtt_broker_connected = 0;
        printf("%s  mqtt borker connect failed %d\n", S_MC, ret);
        return -1;
    }else{
        mqtt_broker_connected = 1;
    }

    return 0;
}

int mqtt_disconnect()
{
    printf("%s disconnecting mqtt publisher\n", S_MC);
    mqtt_broker_connected = 0;
    MQTTClient_disconnect(mqtt_handle, TIMEOUT);
    MQTTClient_destroy(&mqtt_handle);
    return 0;
}



