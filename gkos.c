#include "gkos.h"

bool should_toggle_shift(char mode, char keycode) {
    switch (mode) {
    case GKOS_ABC:
    case GKOS_123:
    case GKOS_FN:
    case GKOS_POINT:

    }
    return false;
}
bool is_ctrled(char mode, char keycode) {
    if (mode == 0 && (keycode == 23 || keycode == 58)) {
        return true;
    }
    return false;
}

GKOS_STATE gkos_init() {
    GKOS_STATE state;
    state.mode = GKOS_ABC;
    state.mod = 0;
    state.key = 0;
    state.key_last = 0;
    state.key_acc = 0;
    return state;
}
