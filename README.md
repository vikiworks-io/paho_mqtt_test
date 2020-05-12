## Paho MQTT Test

This repo contains set of test programs to evaluate paho mqtt library.


#### Test Case 1 

[ ./test_programs/mqtt_sync_pub_sub_1/ ]

This program test mqtt subscriber and publisher in synchronous mode with single mqtt client connection handle. 

#### Test Case 2

[ test_programs/mqtt_sync_pub_sub_2 ]

This program test mqtt subscriber and publisher in synchronous mode with single mqtt client connection handle. It differs from the first 
test by the use of polling at subscriber thread. { MQTTClient_receive() }



