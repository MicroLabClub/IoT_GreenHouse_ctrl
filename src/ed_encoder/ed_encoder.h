#ifndef ED_ENCODER_H_
#define ED_ENCODER_H_


void ed_encoder_setup();
void ed_encoder_loop();

int  ed_encoder_get_counter();
int  ed_encoder_set_counter(int cnt);
int  ed_encoder_reset_counter();


#endif

