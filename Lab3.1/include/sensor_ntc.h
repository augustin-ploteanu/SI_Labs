#ifndef SENSOR_NTC_H
#define SENSOR_NTC_H

void  sensor_ntc_init(void);
int   sensor_ntc_read_raw(void);
float sensor_ntc_read(void);
float sensor_pot_read_threshold(void);

#endif
