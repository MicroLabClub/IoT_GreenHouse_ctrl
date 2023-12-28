#ifndef SRV_UI_SERIAL_H_
#define SRV_UI_SERIAL_H_

void srv_ui_serial_setup();
void srv_ui_serial_in_loop();
void srv_ui_serial_out_loop();

void dd_window_report();
void ed_relay_report();
void srv_sns_air_temp_report();
void ed_dht_report();
void ctrl_temp_vent_report();
void ctrl_temp_heat_report();
void ctrl_lights_report();

#endif
