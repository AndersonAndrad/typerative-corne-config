#include QMK_KEYBOARD_H
#include "enums.h"
#include "lufa.h"

// Render Blank Space
void render_space(void) {
    oled_write_ln_P(PSTR("     "), false);
}

// Render separator lines for oled display
// void render_separator(void) {
//     switch (get_highest_layer(layer_state)){
//         case _GAME:
//         case _WEAPON:
//             oled_write_ln_P(PSTR("===================="), false);
//             break;
//         default:
//             oled_write_ln_P(PSTR("++++++++++++++++++++"), false);
//     }
// }

// Render current layer state
void render_layer_state(void){
	// If you want to change the display of OLED, you need to change here
    switch (get_highest_layer(layer_state)){
        case _QWERTY:
            oled_write_ln_P(PSTR("Layer: QWERTY"), false);
            break;
        case _NUM:
            oled_write_ln_P(PSTR("Layer: _NUM"), false);
            break;
        case _SYMBOL:
            oled_write_ln_P(PSTR("Layer: _SYMBOL"), false);
            break;
        case _UTILS:
            oled_write_ln_P(PSTR("Layer: _UTILS"), false);
            break;
        case _LED:
            oled_write_ln_P(PSTR("Layer: _LED"), false);
            break;
        case _LAYERS:
            oled_write_ln_P(PSTR("Layer: _LAYERS"), false);
            break;
        case _GAMING:
            oled_write_ln_P(PSTR("Layer: _GAMING"), false);
            break;
        case _GAMING1:
            oled_write_ln_P(PSTR("Layer: _GAMING1"), false);
            break;
        case _GAMING2:
            oled_write_ln_P(PSTR("Layer: _GAMING2"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Layer: UNDEFINED"), false);
    }
}

// Render USB State
// void render_usb_state(void) {
//     switch (USB_DeviceState) {
//       case DEVICE_STATE_Unattached:
// 			    oled_write_ln_P(PSTR("| USB  | FREE      ]"), false);
//           break;
//       case DEVICE_STATE_Suspended:
//           oled_write_ln_P(PSTR("| USB  | SLEEP     ]"), false);
//           break;
//       case DEVICE_STATE_Configured:
//           oled_write_ln_P(PSTR("| USB  | READY     ]"), false);
//           break;
//       case DEVICE_STATE_Powered:
//           oled_write_ln_P(PSTR("| USB  | PWRD      ]"), false);
//           break;
//       case DEVICE_STATE_Default:
//           oled_write_ln_P(PSTR("| USB  | DFLT      ]"), false);
//           break;
//       case DEVICE_STATE_Addressed:
//           oled_write_ln_P(PSTR("| USB  | ADDRS     ]"), false);
//           break;
//       default:
//           oled_write_ln_P(PSTR("| USB  | INVALID   ]"), false);
//     }
// }
