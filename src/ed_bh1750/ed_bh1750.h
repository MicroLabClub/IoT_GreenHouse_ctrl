#ifndef ED_BH1750_H
#define ED_BH1750_H

// Include any necessary libraries here

// Define any constants or macros here

// Declare any classes or structs here

// Declare any function prototypes here

void ed_bh1750_setup();
void ed_bh1750_loop();

float ed_bh1750_get_luminozity(void);
int ed_bh1750_get_luminozity_error(void);

#endif // ED_BH1750_H
