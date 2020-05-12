/* MQTT Publisher Header
 *
 *              Author : Viki (a) Vignesh Natarajan
 *              Firma  : vikiworks.io            
 */


#ifndef MQTT_PUBLISHER_H
#define MQTT_PUBLISHER_H

#define TIMEOUT         10000L
#define QOS             1

int mqtt_publish(char *message);

#endif
