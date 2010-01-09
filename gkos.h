#include <linux/input.h>

#ifndef GKOS_H
#define GKOS_H

#define GKOS_A 0x01;
#define GKOS_B 0x02;
#define GKOS_C 0x04;
#define GKOS_D 0x08;
#define GKOS_E 0x10;
#define GKOS_F 0x20;

#define GKOS_CTRL  0x01
#define GKOS_ALT   0x02
#define GKOS_SHIFT 0x04
#define GKOS_CAPS  0x08
#define GKOS_SYMB  0x10
#define GKOS_123   0x20
#define GKOS_POINT 0x40

// Max keycode value with 6 bits
#define GKOS_MAX_KEY 0x3f

const uint16_t GKOS_KEY[GKOS_MAX_KEY+1] = {
    KEY_RESERVED,  // 0, unused
    KEY_A,         // 1
    KEY_B,         // 2
    KEY_O,         // 3
    KEY_C,         // 4
        0x00,        // 5 FIXME Ü OR 'th'
    KEY_S,         // 6
    KEY_BACKSPACE, // 7
    KEY_D,         // 8
    KEY_UP,        // 9
    KEY_APOSTROPHE,// 10
    KEY_P,         // 11
    KEY_1,         // 12 ! (shift 1)
       0x00,        // 13 FIXME Å OR 'that '
    KEY_T,         // 14
    KEY_LEFT,      // 15
    KEY_E,         // 16
    KEY_MINUS,     // 17
        KEY_LEFTSHIFT,// 18 FIXME, handle this key specially
    KEY_Q,         // 19
    KEY_COMMA,     // 20
       0x00,        // 21 FIXME Ä OR 'the '
    KEY_U,         // 22
    KEY_LEFT,      // 23 Word Left (CTRL left)
    KEY_G,         // 24
    KEY_H,         // 25
    KEY_I,         // 26   
    KEY_PAGEUP,    // 27
    KEY_J,         // 28
    KEY_6,         // 29 ^ (shift 6)
    KEY_SLASH,     // 30
    KEY_ESC,       // 31
    KEY_F,         // 32
    KEY_SLASH,     // 33 ? (shift /)
    KEY_DOT,       // 34
    KEY_R,         // 35
    KEY_DOWN,      // 36
       0x00,        // 37 FIXME Ö OR 'of '
    KEY_V,         // 38
    KEY_HOME,      // 39
    KEY_W,         // 40
    KEY_X,         // 41
    KEY_Y,         // 42
    KEY_INSERT,    // 43
    KEY_Z,         // 44
        0x00,        // 45 FIXME SYMB
    KEY_GRAVE,     // 46 ~ (shift `)
        KEY_LEFTCTRL,     // 47 FIXME modify next key
    KEY_K,        // 48 
    KEY_L,        // 49
    KEY_M,        // 50
    KEY_BACKSLASH,// 51
    KEY_N,        // 52
        0x00,        // 53 FIXME ¨ OR 'and '
    KEY_PAGEDOWN, // 54
        KEY_LEFTALT,        // 55 FIXME modify next key
    KEY_SPACE,    // 56
    KEY_RIGHT,    // 57
    KEY_RIGHT,    // 58 Word Right (CTRL-right)
    KEY_ENTER,    // 59
    KEY_END,      // 60
    KEY_TAB,      // 61
    KEY_DELETE,   // 62
        0x00         // 63 FIXME 123-ABC


};
#endif /* GKOS_H */
