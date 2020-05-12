#include "mqtt_common.h"

MQTTClient mqtt_handle;
MQTTClient_connectOptions conn_params = MQTTClient_connectOptions_initializer;
MQTTClient_SSLOptions ssl_params = MQTTClient_SSLOptions_initializer;
MQTTClient_willOptions will_params = MQTTClient_willOptions_initializer;
MQTTClient_createOptions createOpts = MQTTClient_createOptions_initializer;

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

int MQC_CREATE()
{
    int rc = 0;
    //MQTTClient_create(&mqtt_handle, MQTT_ADDRESS, MQTT_CLIENT_ID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    rc = MQTTClient_createWithOptions(&mqtt_handle, MQTT_ADDRESS, MQTT_CLIENT_ID, MQTTCLIENT_PERSISTENCE_NONE, NULL, &createOpts);

	if (rc != MQTTCLIENT_SUCCESS)
	{
	    printf("MQC_CREATE failed, return code: %s\n", MQTTClient_strerror(rc));
	    return -1;
    }

    return 0;
}

void MQC_SET_CONNECTION_PARAMS()
{
    conn_params.username = MQTT_USERNAME;
    conn_params.password = MQTT_PASSWORD;
    conn_params.keepAliveInterval = 10;
    conn_params.cleansession = 1;
	conn_params.MQTTVersion = MQTTVERSION_3_1_1;
}

void MQC_SET_CALLBACKS(){
    MQTTClient_setCallbacks(mqtt_handle, NULL, CB_ConnectionLost, CB_MessageArrived, CB_MessageDelivered);
}

void MQC_SET_WILL_PARAMS()
{
	/*
    will_params.message = opts.will_payload;
	will_params.topicName = opts.will_topic;
	will_params.qos = opts.will_qos;
	will_params.retained = opts.will_retain;
	conn_params.will = &will_params;
    */
}

void MQC_SET_SSL_PARAMS()
{
    /*
	ssl_params.verify = 1;
	ssl_params.CApath = opts.capath;
	ssl_params.keyStore = opts.cert;
	ssl_params.trustStore = opts.cafile;
	ssl_params.privateKey = opts.key;
	ssl_params.privateKeyPassword = opts.keypass;
	ssl_params.enabledCipherSuites = opts.ciphers;
	conn_params.ssl = &ssl_params;
    */
}

void MQC_SET_CLEAN_SESSION(){
	conn_params.cleansession = 1;
}

void MQC_UNSET_CLEAN_SESSION(){
	conn_params.cleansession = 0;
}

int mqtt_reconnect()
{
    int ret = 0;

    if(MQC_CREATE() != 0) return -1;

    MQC_SET_CONNECTION_PARAMS();
    //MQC_SET_WILL_PARAMS();
    //MQC_SET_SSL_PARAMS();
    MQC_UNSET_CLEAN_SESSION(); /*Use this when you are connecting for the second time, to retain previous connection states*/
    //MQC_SET_CALLBACKS();

    ret = MQTTClient_connect(mqtt_handle, &conn_params);

    if (ret != MQTTCLIENT_SUCCESS )
    {
        mqtt_broker_connected = 0;
        printf("%s  mqtt borker connect failed %d\n", S_MC, ret);
        return -1;
    }else{
        printf("%s  mqtt borker connect success \n", S_MC);
        mqtt_broker_connected = 1;
    }

    return 0;
}

int mqtt_connect()
{
    int ret = 0;

    if(MQC_CREATE() != 0) return -1;

    MQC_SET_CONNECTION_PARAMS();
    //MQC_SET_WILL_PARAMS();
    //MQC_SET_SSL_PARAMS();
    MQC_SET_CLEAN_SESSION();
    //MQC_SET_CALLBACKS();

    ret = MQTTClient_connect(mqtt_handle, &conn_params);

    if (ret != MQTTCLIENT_SUCCESS )
    {
        mqtt_broker_connected = 0;
        printf("%s  mqtt borker connect failed %d\n", S_MC, ret);
        return -1;
    }else{
        printf("%s  mqtt borker connect success \n", S_MC);
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



