
From [the official GKOS website](http://gkos.com/)

> GKOS - a new category of full-featured physical keyboards:
>
> Not QWERTY, not exactly Wearable  -  but for Small Wireless Devices!


The basic idea of GKOS is that you've got six buttons on the back of a
device (either a dedicated input device, or on the back of a handheld
computing device, phone, etc), one for the index through ring fingers
of each hand (or two for each finger if you have a device made for
one-handed use). You press the keys in various chords to type, switch
between modes, and operate a pointer (when in pointer mode).

This project is an implementation of GKOS for Linux (and soon to be
for AVR microcontrollers), made mostly so I can try out GKOS for
myself.

The Linux version (currently the only version), takes over a standard
USB HID keyboard (most likely a USB number pad) via
[libhid](http://libhid.alioth.debian.org/), and uses 6 of its keys to
function as a GKOS keyboard, sending keypresses via
[libsuinput](http://github.com/tuos/libsuinput/). It will be
configurable (right now it's "configurable" by changing a couple of
lines in main-linux.c) at some point in the near future.

The AVR version will work together with
[V-USB](http://www.obdev.at/products/vusb/index.html) and/or
[LUFA](http://www.fourwalledcubicle.com/LUFA.php) to implement an
actual HID keyboard/mouse, and therefore won't need drivers for any
OS.

The current implementation has the basic key scanner implemented
(meaning you have to let go of all keys before a keypress is sent),
with nearly all of the characters in the spec implemented (a few
international ones aren't done because they aren't things that can be
typed by just sending a keycode or SHIFT+keycode, I'll add in Compose
support at some point, probably to make those work).