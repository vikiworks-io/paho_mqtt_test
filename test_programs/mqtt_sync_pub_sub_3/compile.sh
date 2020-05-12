gcc -L/usr/local/lib/ -lpaho-mqtt3a -lpaho-mqtt3as -lpaho-mqtt3cs -lpaho-mqtt3c -lpthread mqtt_common.c mqtt_sub.c mqtt_pub.c test_main.c -o test_main
