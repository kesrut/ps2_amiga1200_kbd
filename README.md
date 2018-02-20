# ps2_amiga1200_kbd

Arduino based PS/2 keyboard to Amiga 1200 adapter (proof of concept)

It's just *dirty* hack which worked for me. Something what can be done in few hours.

Some notes:

```
#define amiga_clk 5
#define amiga_data 4
```

amiga_data and amiga_clk is hooked to A1200 motherboard keyboard micro (68HC05C). 14, 15 pins of 68HC05C (screenshot attached).

```
#define ps_clk 2 
#define ps_data 3
```

Please add https://github.com/techpaul/PS2KeyAdvanced Arduino library to compile.

