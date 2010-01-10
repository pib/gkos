#include <linux/input.h>

#ifndef GKOS_H
#define GKOS_H

#define GKOS_A 0x01;
#define GKOS_B 0x02;
#define GKOS_C 0x04;
#define GKOS_D 0x08;
#define GKOS_E 0x10;
#define GKOS_F 0x20;

#define GKOS_SYMB  0x01
#define GKOS_SHIFT 0x02
#define GKOS_CTRL  0x04
#define GKOS_ALT   0x08
#define GKOS_CAPS  0x10

typedef enum GKOS_MODE_t {
    GKOS_ABC   = 0,
    GKOS_123   = 3,
    GKOS_FN    = 6, // CTRL+SYMB = FN
    GKOS_POINT = 7  // Pointer mode
} GKOS_MODE;

// Max keycode value with 6 bits
#define GKOS_MAX_KEY 0x3f

/* 
 * Toggle shift. Combinations for which the state of SHIFT should be toggled before sending keys.
 * For +SHIFT modes, this means that shift will be turned OFF, rather than being left on.
 * EACH LIST MUST BE ZERO TERMINATED!
 */
const char GKOS_ABC_TS[7][] = {
    /* ABC */       { 12, 29, 33, 46, 0 },
    /* ABC+SYMB */  { 3, 6, 11, 35, 48, 49, 50, 52, 0 },
    /* ABC+SHIFT */ { 0 },
    /* 123 */       { 3, 6, 11, 35, 48, 49, 50, 52, 0 },
    /* 123+SYMB */  { 0 },
    /* 123+SHIFT */ { 35, 0 },
    /* FN */        { 0 }
};


// Index with keycode-1
const uint16_t GKOS_KEY[GKOS_MAX_KEY][10] = {
    /*keycode  ABC,   ABC+SYMB,  ABC+SHIFT, 123,       123+SYMB, 123+SHIFT,  FN  */
    /*  1 */ { KEY_A, KEY_1,     KEY_A,     KEY_1,     KEY_A,    KEY_1,      KEY_F1 },
    /*  2 */ { KEY_B, KEY_2,     KEY_B,     KEY_2,     KEY_B,    KEY_2,      KEY_F2 },
    /*  3 */ { KEY_O, KEY_EQUAL, KEY_O,     KEY_EQUAL, KEY_O,    KEY_EQUAL,  KEY_F20 },
    /*  4 */ { KEY_C, KEY_3,     KEY_C,     KEY_3,     KEY_C,    KEY_3,      KEY_F3 }
    /*  5 */ { 0,     0,         0,         0,         0,        0,          0}   // 5 FIXME Ü OR 'th'
    /*  6 */ { KEY_S, KEY_8,     KEY_S,     KEY_8,     KEY_S,    KEY_8,      KEY_F20 },         // 6
    /*  7 */ { KEY_BACKSPACE, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },// 7
    /*  8 */ { KEY_D, KEY_4, KEY_D, KEY_4, KEY_D, KEY_4, KEY_F4 },         // 8
    /*  9 */ { KEY_UP, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },       // 9
    /* 10 */ { KEY_APOSTROPHE, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },// 10
    /* 11 */ { KEY_P, KEY_5, KEY_P, KEY_5, KEY_P, KEY_5, KEY_F14 },        // 11
    /* 12 */ { KEY_1, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },        // 12 ! (shift 1)
    /* 13 */ {0,0,0,0,0,0,0},        // 13 FIXME Å OR 'that '
    /* 14 */ { KEY_T, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },        // 14
    /* 15 */ { KEY_LEFT, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },     // 15
    /* 16 */ { KEY_E, KEY_5, KEY_E, KEY_5, KEY_E, KEY_5, KEY_F5 },        // 16
    /* 17 */ { KEY_MINUS, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },    // 17
    /* 18 */ { KEY_LEFTSHIFT,KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },// 18 FIXME, handle this key specially
    /* 19 */ { KEY_Q, KEY_EQUAL, KEY_Q, KEY_EQUAL, KEY_Q, KEY_EQUAL, KEY_F15 },        // 19
    /* 20 */ { KEY_COMMA, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },    // 20
    /* 21 */ {0,0,0,0,0,0,0},        // 21 FIXME Ä OR 'the '
    /* 22 */ { KEY_U, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },        // 22
    /* 23 */ { KEY_LEFT, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },     // 23 Word Left (CTRL left)
    /* 24 */ { KEY_G, KEY_0, KEY_G, KEY_0, KEY_G, KEY_0, KEY_F10 },        // 24
    /* 25 */ { KEY_H, KEY_7, KEY_H, KEY_7, KEY_H, KEY_7, KEY_F7 },        // 25
    /* 26 */ { KEY_I, KEY_8, KEY_I, KEY_8, KEY_I, KEY_8, KEY_F8 },        // 26   
    /* 27 */ { KEY_PAGEUP, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },   // 27
    /* 28 */ { KEY_J, KEY_9, KEY_J, KEY_9, KEY_J, KEY_9, KEY_F9 },        // 28
    /* 29 */ { KEY_6, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },        // 29 ^ (shift 6)
    /* 30 */ { KEY_SLASH, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },    // 30
    /* 31 */ { KEY_ESC, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },      // 31
    /* 32 */ { KEY_F, KEY_6, KEY_F, KEY_6, KEY_F, KEY_6, KEY_F6 },        // 32
    /* 33 */ { KEY_SLASH, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },    // 33 ? (shift /)
    /* 34 */ { KEY_DOT, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },      // 34
    /* 35 */ { KEY_R, KEY_6, KEY_R, KEY_6, KEY_R, KEY_YEN, KEY_ },        // 35
    /* 36 */ { KEY_DOWN, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },     // 36
    /* 37 */ {0,0,0,0,0,0,0},        // 37 FIXME Ö OR 'of '
    /* 38 */ { KEY_V, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },        // 38
    /* 39 */ { KEY_HOME, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },     // 39
    /* 40 */ { KEY_W, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },        // 40
    /* 41 */ { KEY_X, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },        // 41
    /* 42 */ { KEY_Y, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },        // 42
    /* 43 */ { KEY_INSERT, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },   // 43
    /* 44 */ { KEY_Z, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },        // 44
    /* 45 */ {0,0,0,0,0,0,0},        // 45 FIXME SYMB
    /* 46 */ { KEY_GRAVE, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },    // 46 ~ (shift `)
    /* 47 */ { KEY_LEFTCTRL, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },    // 47 FIXME modify next key
    /* 48 */ { KEY_K, KEY_3, KEY_K, KEY_3, KEY_K, KEY_3, KEY_F10 },
    /* 49 */ { KEY_L, KEY_2, KEY_L, KEY_2, KEY_L, KEY_2, KEY_F11 },
    /* 50 */ { KEY_M, KEY_7, KEY_M, KEY_7, KEY_M, KEY_7, KEY_F12 },
    /* 51 */ { KEY_BACKSLASH, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },
    /* 52 */ { KEY_N, KEY_2, KEY_N, KEY_7, KEY_N, KEY_2, KEY_F13 },
    /* 53 */ {0,0,0,0,0,0,0},        // 53 FIXME ¨ OR 'and '
    /* 54 */ { KEY_PAGEDOWN, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },// 54
    /* 55 */ { KEY_LEFTALT, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },       // 55 FIXME modify next key
    /* 56 */ { KEY_SPACE, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },   // 56
    /* 57 */ { KEY_RIGHT, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },   // 57
    /* 58 */ { KEY_RIGHT, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },   // 58 Word Right (CTRL-right)
    /* 59 */ { KEY_ENTER, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },   // 59
    /* 60 */ { KEY_END, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },     // 60
    /* 61 */ { KEY_TAB, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },     // 61
    /* 62 */ { KEY_DELETE, KEY_, KEY_, KEY_, KEY_, KEY_, KEY_ },  // 62
    /* 63 */ {0,0,0,0,0,0,0}         // 63 FIXME 123-ABC
};      
#endif /* GKOS_H */
        
        
        
        
