#include <stdio.h>

#include "gkos.h"
#include "gkos_private.h"

/**
 * Global GKOS state 
 *
 * Yes, I know global variables are bad, mmkay, but but I want this
 * same code to run on microcontrollers, and didn't want to be
 * clogging up the stack with what is essentially going to be a global
 * variable anyway.
 */
static GKOS_STATE state;

// If both CTRL and SYMB are down, the offset is 6, for the FN column.
// Otherwise, it's based on the mode and SYMB or SHIFT combination.
#define KEYMAP_OFFSET(mode, modifiers) (((modifiers & GKOS_FN) == GKOS_FN) ? 6 : \
                                        (((mode == GKOS_POINT) ? GKOS_ABC : mode) + \
                                         (modifiers & GKOS_SYMB_SHIFT)))

/**
 * Returns a bool indicating whether shift should be sent for this key
 */
bool gkos_is_shifted(char keymap) {
    bool shifted = state.mod & GKOS_SHIFT;

    const char *code = GKOS_TS[KEYMAP_OFFSET(state.mode, state.mod)];
    // determine if we should toggle our "shifted" value
    do {
        if (*code == keymap) {
            shifted = !shifted;
            break;
        }
        code++;
    } while (*code);

    return shifted;
}

bool gkos_is_ctrled(char keymap) {
    if (state.mode == GKOS_ABC && (keymap == 23 || keymap == 58)) {
        return true;
    }
    if (state.mod & GKOS_CTRL) {
        return true;
    }
    return false;
}

bool gkos_is_alted(char keymap) {
    if (state.mod & GKOS_ALT) return true;
    return false;
}

bool gkos_do_send(char keymap) {
    // TODO: Handle POINTER mode here, as well

    uint16_t keycode = GKOS_KEY[(int)keymap - 1][KEYMAP_OFFSET(state.mode, state.mod)];
    bool shifted = gkos_is_shifted(keymap);
    bool ctrled =  gkos_is_ctrled(keymap);
    bool alted =   gkos_is_alted(keymap);
    bool metaed =  state.mod & GKOS_META;
    int res = 0;

    if (shifted) res = res || gkos_send_keydown(KEY_LEFTSHIFT);
    if (ctrled)  res = res || gkos_send_keydown(KEY_LEFTCTRL);
    if (alted)   res = res || gkos_send_keydown(KEY_LEFTALT);
    if (metaed)  res = res || gkos_send_keydown(KEY_LEFTMETA);

    res = res || gkos_send_keydown(keycode);
    res = res || gkos_send_keyup(keycode);

    if (shifted) res = res || gkos_send_keyup(KEY_LEFTSHIFT);
    if (ctrled)  res = res || gkos_send_keyup(KEY_LEFTCTRL);
    if (alted)   res = res || gkos_send_keyup(KEY_LEFTALT);
    if (metaed)  res = res || gkos_send_keyup(KEY_LEFTMETA);

    return res;
}

bool gkos_special(char keymap) {
    // TODO: handle special functions relating to SYMB keypresses here
    // TODO: handle special chordons here, too


    /* when SHIFT, CAPS, or SYMB is turned on, turn off the other two
     * (simplifies figuring out if it's currently shifted, and whether
     * one should have priority over the other
     */
    switch (keymap) {
    case GKOS_KEY_SHIFT:
        if (state.mod & GKOS_CAPS) state.mod &= ~(GKOS_CAPS | GKOS_SHIFT);
        else if (state.mod & GKOS_SHIFT) state.mod |= GKOS_CAPS;
        else state.mod |= GKOS_SHIFT;
        return true;
    case GKOS_KEY_SYMB:
        if (state.mod & GKOS_SHIFT) state.mod = (state.mod & ~(GKOS_SYMB | GKOS_SHIFT)) | GKOS_META;
        else if (state.mod & GKOS_SYMB) state.mod &= ~GKOS_SYMB;
        else state.mod = (state.mod & ~(GKOS_CAPS | GKOS_SHIFT)) | GKOS_SYMB;
        return true;
    case GKOS_KEY_123_ABC:
        if (state.mode == GKOS_ABC) state.mode = GKOS_123;
        else state.mode = GKOS_ABC;
        return true;
    case GKOS_KEY_CTRL:
        state.mod ^= GKOS_CTRL; // toggle GKOS_CTRL bit
        return true;
    case GKOS_KEY_ALT:
        state.mod ^= GKOS_ALT; // toggle GKOS_ALT bit
        return true;
    default:
        return false;
    }
}

bool gkos_handle_keys(char keymap) {
    int res = 0;
    state.key_acc |= keymap;

    if (keymap && (keymap != state.key_last)) {
        printf("keymap: %02x (%d)\n", keymap, keymap);
    }

    if (!keymap && state.key_last) {
        // All the keys were released

        if (!gkos_special(state.key_acc)) {
            // If caps lock is on, turn on shift for this key
            if ((state.mod & GKOS_CAPS)) state.mod |= GKOS_SHIFT;

            res = gkos_do_send(state.key_acc);

            // Turn off modifiers (all but CAPS) after a single keypress
            state.mod &= GKOS_CAPS;
        }
        state.key_acc = 0;
    }
    state.key_last = keymap;

    return !res;
}

bool gkos_init() {
    state.mode = GKOS_ABC;
    state.last_mode = GKOS_ABC;
    state.mod = 0;
    state.key_last = 0;
    state.key_acc = 0;
    return true;
}
