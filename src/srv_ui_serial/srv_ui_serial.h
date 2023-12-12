#ifndef SRV_UI_SERIAL_H_
#define SRV_UI_SERIAL_H_

void srv_ui_serial_setup();
void srv_ui_serial_in_loop();
void srv_ui_serial_out_loop();

void srv_ui_serial_win_report();
void srv_ui_serial_relay_report();
void srv_ui_serial_sns_air_temp_report();
void srv_ui_serial_dht_report();
void srv_ui_serial_ctrl_steering_report();

#endif
