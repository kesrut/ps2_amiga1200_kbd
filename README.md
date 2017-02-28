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

ps_clk must be interrupt pin. To use 2 pin it's OK. 

blog post: https://kesrut.wordpress.com/2017/02/04/resurrecting-amiga-1200/

