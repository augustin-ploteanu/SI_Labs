#ifndef SENSOR_DHT_H
#define SENSOR_DHT_H

void  sensor_dht_init(void);
float sensor_dht_read_temp(void);
float sensor_dht_read_humidity(void);

#endif
