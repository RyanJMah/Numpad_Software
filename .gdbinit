target extended-remote :3333

file build/main.elf
load

b main
b keyboard_entry
b keyscan_thread.c
b usb_thread.c:30
