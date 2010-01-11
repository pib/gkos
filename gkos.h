#include <linux/input.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef GKOS_H
#define GKOS_H

#define GKOS_A 0x01;
#define GKOS_B 0x02;
#define GKOS_C 0x04;
#define GKOS_D 0x08;
#define GKOS_E 0x10;
#define GKOS_F 0x20;

bool gkos_init(void);
bool gkos_handle_keys(char keymap);

/** The following need to be defined on a per-platform basis (see
 * main-linux.c for an example) 
 *
 * The keycode will be a keycode from linux/input.h, so some may need
 * to be translated to work on the platform as expected
 */ 
bool gkos_send_keydown(uint16_t keycode);
bool gkos_send_keyup(uint16_t keycode);
bool gkos_send_mouse();

#endif /* GKOS_H */
        
        
        
        
