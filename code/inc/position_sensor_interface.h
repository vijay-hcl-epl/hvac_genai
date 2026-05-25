#ifndef POSITION_SENSOR_INTERFACE_H
#define POSITION_SENSOR_INTERFACE_H

// Position Data API
int position_sensor_read(void); // Returns filtered position
int position_sensor_last(void); // Returns last known position

#endif // POSITION_SENSOR_INTERFACE_H
