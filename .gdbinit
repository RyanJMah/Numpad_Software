target extended-remote :3333

file build/main.elf
load

b main
b keyboard_entry
b keyscan_thread_fn
# b usb_thread_fn.c:24
