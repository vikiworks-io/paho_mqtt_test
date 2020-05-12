/* MQTT Publisher Library
*
 *              Author : Viki (a) Vignesh Natarajan
 *              Firma  : vikiworks.io               
 */
#include "mqtt_common.h"
#include "mqtt_pub.h"

int mqtt_publish(char *message)
{
    int ret = 0;

    if(!message)
        return -1;

    if(mqtt_broker_connected == 0){
        return -2;
    }

    MQTTClient_message mqtt_msg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;

    mqtt_msg.payload    = message;
    mqtt_msg.payloadlen = strlen(message);
    mqtt_msg.qos        = QOS;
    mqtt_msg.retained   = 0;

    printf("%s publishing message ( %s )\n", S_MP, message);
    MQTTClient_publishMessage(mqtt_handle, MQTT_TOPIC, &mqtt_msg, &token);
    
    ret = MQTTClient_waitForCompletion(mqtt_handle, token, TIMEOUT);

    if(ret == MQTTCLIENT_SUCCESS){
        printf("%s  message delivery successfully ( token = %d ) ] \n", S_MP, token);
        ret = 0;
    }else{
        printf("%s error - unable to deliver message( ret = %d ) \n", S_MP, ret);
        ret = -1;
    }

    return ret;
}
