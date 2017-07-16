#define ps_clk 2 
#define ps_data 3

#define amiga_clk 5
#define amiga_data 4

#define START 1
#define STOP 3
#define PARITY 4
#define INIT 5
#define GROUP1_CNT 85
#define BREAK_GRP1 0xF0
#define MAKE_GRP2 0xE0
#define DEBUG 1


byte cycles = 0 ; 
unsigned char value = 0 ; 
byte state = INIT ; 
byte got_data = 0 ; 

struct ps2_struct_group
{
  unsigned char character ; 
  unsigned char make ;   
  unsigned is_char ; 
  unsigned char xt_make ; 
} ; 

typedef struct ps2_struct_group ps2_group1_type ; 
typedef struct ps2_struct_group ps2_group2_type ; 


ps2_group1_type ps2_group1[] =
{
  {'a', 0x1C, 1, 0x20},
  {'b', 0x32, 1, 0x35}, 
  {'c', 0x21, 1, 0x33}, 
  {'d', 0x23, 1, 0x22},
  {'e', 0x24, 1, 0x12},
  {'f', 0x2B, 1, 0x23}, 
  {'g', 0x34, 1, 0x24},
  {'h', 0x33, 1, 0x25}, 
  {'i', 0x43, 1, 0x17},
  {'j', 0x3B, 1, 0x26}, 
  {'k', 0x42, 1, 0x27}, 
  {'l', 0x4B, 1, 0x28},
  {'m', 0x3A, 1, 0x37}, 
  {'n', 0x31, 1, 0x36},
  {'o', 0x44, 1, 0x18}, 
  {'p', 0x4D, 1, 0x19},
  {'q', 0x15, 1, 0x10},
  {'r', 0x2D, 1, 0x13},
  {'s', 0x1B, 1, 0x21},
  {'t', 0x2C, 1, 0x14}, 
  {'u', 0x3C, 1, 0x16}, 
  {'v', 0x2A, 1, 0x34}, 
  {'w', 0x1D, 1, 0x11},
  {'x', 0x22, 1, 0x32},
  {'y', 0x35, 1, 0x15},
  {'z', 0x1A, 1, 0x31}, 
  {'0', 0x45, 1, 0x0A},
  {'1', 0x16, 1, 0x01},
  {'2', 0x1E, 1, 0x02},
  {'3', 0x26, 1, 0x03},
  {'4', 0x25, 1, 0x04},
  {'5', 0x2E, 1, 0x05},
  {'6', 0x36, 1, 0x06},
  {'7', 0x3D, 1, 0x08},
  {'8', 0x3E, 1, 0x09},
  {'9', 0x46, 1, 0x09}, 
  {'`', 0x0E, 1, 0x29},
  {'-', 0x4E, 1, 0x0B},
  {'=', 0x55, 1, 0x0C},
  {'\\', 0x5D, 1, 0x0D},
  {'\b', 0x66, 0, 0x41}, // backsapce
  {' ', 0x29, 1, 0x40}, // space
  {'\t', 0x0D, 0, 0x0F}, // tab
  {' ', 0x14, 0, 0x63}, // left ctrl
  {' ', 0x11, 0, 0x64}, // left alt
  {'\n', 0x5A, 1, 0x44}, // enter
  {' ', 0x76, 0, 0x45}, // esc
  {' ', 0x05, 0, 0x50}, // F1
  {' ', 0x06, 0, 0x51}, // F2
  {' ', 0x04, 0, 0x52}, // F3
  {' ', 0x0C, 0, 0x53}, // F4
  {' ', 0x03, 0, 0x54}, // F5
  {' ', 0x0B, 0, 0x55}, // F6
  {' ', 0x83, 0, 0x56}, // F7
  {' ', 0x0A, 0, 0x57}, // F8
  {' ', 0x01, 0, 0x58}, // f9
  {' ', 0x09, 0, 0x59}, // f10
  {' ', 0x78, 0, 0x57}, // f11
  {' ', 0x07, 0, 0x58}, // f12
  {' ', 0x7E, 0, 0x46}, // SCROLL
  {'[', 0x54, 1, 0x1A},
  {' ', 0x77, 0, 0x45}, // Num Lock
  {'*', 0x7C, 1, 0x37}, // Keypad *
  {'-', 0x7B, 1, 0x4A}, // Keypad -
  {'+', 0x79, 1, 0x4E}, // Keypad +
  {'.', 0x71, 1, 0x53}, // Keypad .
  {'0', 0x70, 1, 0x52}, // Keypad 0
  {'1', 0x69, 1, 0x4F}, // Keypad 1
  {'2', 0x72, 1, 0x50}, // Keypad 2
  {'3', 0x7A, 1, 0x51}, // Keypad 3
  {'4', 0x6B, 1, 0x4B}, // Keypad 4
  {'5', 0x73, 1, 0x4C}, // Keypad 5
  {'6', 0x74, 1, 0x4D}, // Keypad 6
  {'7', 0x6C, 1, 0x47}, // Keypad 7
  {'8', 0x75, 1, 0x48}, // Keypad 8
  {'9', 0x7D, 1, 0x49}, // Keypad 9
  {']', 0x5B, 1, 0x1B},
  {';', 0x4C, 1, 0x29}, 
  {'\'', 0x52, 1, 0x2A},
  {',', 0x41, 1, 0x39},
  {'.', 0x49, 1, 0x38},
  {'/', 0x4A, 1, 0x3A}, 
  
  {' ', 0x12, 0, 0x60}, // left shift
  {' ', 0x59, 0, 0x61}, // right shift
  {' ', 0x58, 0, 0x62}, // caps
  
} ; 


ps2_group2_type ps2_group2[] =
{
  {' ', 0x5B, 0, 0x1F}, // left gui
  {' ', 0x1D, 0, 0x14}, // right ctrl
  {' ', 0x5C, 0, 0x27}, // right gui
  {' ', 0x38, 0, 0x11}, // right alt
  {' ', 0x5D, 0, 0x2F}, // apps
  {' ', 0x52, 0, 0x70}, // insert
  {' ', 0x47, 0, 0x6C}, // home
  {' ', 0x49, 0, 0x7D}, // page up
  {' ', 0x53, 0, 0x71}, // delete
  {' ', 0x4F, 0, 0x69}, // end
  {' ', 0x51, 0, 0x7A}, // page down
  {' ', 0x48, 0, 0x4C}, // u arrow
  {' ', 0x4B, 0, 0x4F}, // l arrow
  {' ', 0x50, 0, 0x4D}, // d arrow
  {' ', 0x4D, 0, 0x4E}, // r arrow
  {' ', 0x1C, 0, 0x5A}, // kp en
} ;

void setup() 
{
#ifdef DEBUG
  Serial.begin(9600) ; 
#endif
  pinMode(ps_clk, INPUT) ;
  pinMode(ps_data,INPUT) ;  
  pinMode(amiga_clk, OUTPUT) ; 
  pinMode(amiga_data, OUTPUT) ; 
  digitalWrite(amiga_clk, HIGH) ; 
  digitalWrite(amiga_data, HIGH) ; 
  attachInterrupt(digitalPinToInterrupt(2), clock, FALLING);
}

unsigned char _read()
{
   if (got_data)
   {
    got_data = 0 ; 
    return value ; 
  } 
  return 0 ; 
}

void _write(unsigned char value)
{ 
    
   int i=0;
   int p  = ((value & 0x80) >> 7) ; 
   int result = (value << 1) | p ; 
   digitalWrite(amiga_data, HIGH);
   digitalWrite(amiga_clk, HIGH);
   int z = 0x80 ; 
   for (i=0; i < 8; i++)
   {
    digitalWrite(amiga_clk, LOW);
    if (!(result & z)) digitalWrite(amiga_data, HIGH);
    else digitalWrite(amiga_data, LOW); 
    delayMicroseconds(20) ;
    digitalWrite(amiga_clk, HIGH);
    delayMicroseconds(20) ;
    z = z >> 1 ;
  }
  digitalWrite(amiga_data, HIGH);
  digitalWrite(amiga_clk, HIGH);
  delayMicroseconds(200) ;
}

byte i = 0 ;
void loop() {
  label_start:
  unsigned char code = _read() ; 
#ifdef DEBUG
  if (code != 0){
  Serial.println(code, HEX) ; 
}
#endif
  if (code == BREAK_GRP1) {
     delay(4) ; 
     unsigned char break_code = _read() ; 
     unsigned char i = 0 ; 
     while (i < GROUP1_CNT)
     {
       if (ps2_group1[i].make == break_code)
       { 
          pinMode(amiga_clk, OUTPUT) ; 
          pinMode(amiga_data, OUTPUT) ; 
          _write(ps2_group1[i].xt_make | 0x80) ;
          break ;
       }
       i++ ;
     }
    goto label_start;  
  }
  if (code != 0)
  {
    unsigned char i = 0 ; 
    while (i < GROUP1_CNT)
    {
      if (ps2_group1[i].make == code)
      {
#ifdef DEBUG
         Serial.write(ps2_group1[i].character) ; 
#endif
         _write(ps2_group1[i].xt_make) ;
         break ;
      }
    i++ ; 
   }
  }
  
}

void clock()
{
   if (state == INIT)
   {
     if (digitalRead(ps_data) == LOW)
     {
       state = START ; 
       cycles = 0 ;
       got_data = 0 ;
       value = 0 ; 
       return ; 
     }
   }
   if (state == START)
   {
     value |= (digitalRead(ps_data) << cycles) ;
     cycles++ ; 
     if (cycles == 8) state = PARITY ;
     return ;  
   }
   if (state == PARITY)
   {
     state = STOP ; 
     return ; 
   }
   if (state == STOP)
   {
     if (digitalRead(ps_data) == HIGH)
     {
       state = INIT ; 
       got_data = 1 ; 
       return ; 
     }
   }  
}
