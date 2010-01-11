#include <hid.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> /* for getopt() */
#include <signal.h>

#include <suinput.h>

#include "gkos.h"

// uinput device (see gkos.c for my explanation of why a global var)
static int uinput_fd;

bool match_serial_number(struct usb_dev_handle* usbdev, void* custom, unsigned int len)
{
    bool ret;
    char* buffer = (char*)malloc(len);
    usb_get_string_simple(usbdev, usb_device(usbdev)->descriptor.iSerialNumber,
                          buffer, len);
    ret = strncmp(buffer, (char*)custom, len) == 0;
    free(buffer);
    return ret;
}

char keys_to_keymap(char *keys, int keylength) {
    // TODO: make this configurable, rather than being hardcoded to my keypad
    char keycode = 0;
    int i;
    for(i=0; i< keylength; i++) {
        switch(keys[i]) {
        case 0x2b: 
            keycode |= GKOS_A;
            break;
        case 0x4b:
            keycode |= GKOS_B;
            break;
        case 0x4e:
            keycode |= GKOS_C;
            break;
        case 0x5f:
            keycode |= GKOS_D;
            break;
        case 0x60:
            keycode |= GKOS_E;
            break;
        case 0x61:
            keycode |= GKOS_F;
            break;
        default:
            break;
        }
    }
    return keycode;
}

bool gkos_send_keydown(uint16_t keycode) {
    return suinput_press(uinput_fd, keycode);
}
bool gkos_send_keyup(uint16_t keycode) {
    return suinput_release(uinput_fd, keycode);
}


bool done = false;
void sighandler(int sig) {
    done = true;
}

int main(int argc, char *argv[])
{
    struct input_id in_id = {
        BUS_BLUETOOTH, /* Bus type. */
        13,            /* Vendor id. */
        3,             /* Product id. */
        7              /* Version id. */
    };

    HIDInterface* hid;
    int iface_num = 0;
    hid_return ret;

    unsigned short vendor_id  = 0x04b4;
    unsigned short product_id = 0x0101;
    char *vendor, *product;

    int flag;

    signal(SIGABRT, &sighandler);
    signal(SIGTERM, &sighandler);
    signal(SIGINT,  &sighandler);

    /* Parse command-line options.
     *
     * Currently, we only accept the "-d" flag, which works like "lsusb", and the
     * "-i" flag to select the interface (default 0). The syntax is one of the
     * following:
     * 
     * $ gkos -d 1234:
     * $ gkos -d :5678
     * $ gkos -d 1234:5678
     *
     * Product and vendor IDs are assumed to be in hexadecimal.
     *
     * TODO: error checking and reporting.
     */
    while((flag = getopt(argc, argv, "d:i:")) != -1) {
        switch (flag) {
        case 'd':
            product = optarg;
            vendor = strsep(&product, ":");
            if(vendor && *vendor) {
                vendor_id = strtol(vendor, NULL, 16);
            }
            if(product && *product) {
                product_id = strtol(product, NULL, 16);
            }
            break;
        case 'i':
            iface_num = atoi(optarg);
            break;
        }
    }

    HIDInterfaceMatcher matcher = { vendor_id, product_id, NULL, NULL, 0 };

    /* see include/debug.h for possible values */
    //hid_set_debug(HID_DEBUG_ALL);
    //hid_set_debug_stream(stderr);
    /* passed directly to libusb */
    //hid_set_usb_debug(0);
  
    ret = hid_init();
    if (ret != HID_RET_SUCCESS) {
        fprintf(stderr, "hid_init failed with return code %d\n", ret);
        return 1;
    }

    hid = hid_new_HIDInterface();
    if (hid == 0) {
        fprintf(stderr, "hid_new_HIDInterface() failed, out of memory?\n");
        return 1;
    }

    ret = hid_force_open(hid, iface_num, &matcher, 3);
    if (ret != HID_RET_SUCCESS) {
        fprintf(stderr, "hid_force_open failed with return code %d\n", ret);
        return 1;
    }

    // TODO: Read PATHLEN, PATH_IN, RECV_PACKET_LEN and SLEEP_LENGTH from the actual device
    const int PATHLEN = 2;
    const int PATH_IN[2] = { 0x00010006, 0x00000000 };
    const int RECV_PACKET_LEN = 8;
    const int SLEEP_LENGTH = 10000; // 10 milliseconds

    char *packet = malloc(RECV_PACKET_LEN);
    char keymap;

    uinput_fd = suinput_open("GKOSInput", &in_id);

    if (!packet) {
        perror("Couldn't allocate input buffer.");
        done = true;
    }
    if (!uinput_fd) {
        perror("Couldn't create virtual input device.");
        done = true;
    }
    if (!gkos_init()) {
        perror("Couldn't initialize gkos.");
        done = true;
    }

    while (!done) {
        usleep(SLEEP_LENGTH);
        ret = hid_get_input_report(hid, PATH_IN, PATHLEN, packet, RECV_PACKET_LEN);
        if (ret != HID_RET_SUCCESS) {
            fprintf(stderr, "hid_get_input_report failed with return code %d\n", ret);
            return 1;
        }
        /*
          TODO: make this more generic, rather than assuming all
          devices work like mine check the HID standard for how
          keyboards send their input
        */
        keymap = keys_to_keymap(packet, RECV_PACKET_LEN);
        if (!gkos_handle_keys(keymap)) {
            done = true;
        }
    }
    if (packet) free(packet);
    if (uinput_fd) suinput_close(uinput_fd);

    ret = hid_close(hid);
    if (ret != HID_RET_SUCCESS) {
        fprintf(stderr, "hid_close failed with return code %d\n", ret);
        return 1;
    }

    hid_delete_HIDInterface(&hid);

    ret = hid_cleanup();
    if (ret != HID_RET_SUCCESS) {
        fprintf(stderr, "hid_cleanup failed with return code %d\n", ret);
        return 1;
    }
  
    return 0;
}

