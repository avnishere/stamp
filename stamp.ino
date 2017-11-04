// ******** It's a mistery, we have agreed. *********

#include <Keypad.h>
#include <LiquidCrystal.h>  // LCD Library
#include <max6675.h>        // Heat Sensor Library
#include <Wire.h>
#include <EEPROM.h>

// Heat sensor Pin Declarations

int thermoDO = 11;
int thermoCS = 12;
int thermoCS2 = 14;
int thermoCS4 = 15;
int thermoCS6 = 16;
int thermoCLK = 13;

// Temp. reading flags

int step_time1 = 0;
int step_time2 = 0;
int step_time3 = 0;
int step_time4 = 0;

// Temperature sensing functions

MAX6675 thermocouple1(thermoCLK, thermoCS, thermoDO);
MAX6675 thermocouple2(thermoCLK, thermoCS2, thermoDO);
MAX6675 thermocouple3(thermoCLK, thermoCS4, thermoDO);
MAX6675 thermocouple4(thermoCLK, thermoCS6, thermoDO);

//  Temperature recording variables

float heatertemp1;
float heatertemp2;
float heatertemp3;
float heatertemp4;
int set_temp;

// Temperature Control Pins

int heater1 = 38;
int heater2 = 39;
int heater3 = 40;
int heater4 = 41;

uint8_t degree[8]  = {140, 146, 146, 140, 128, 128, 128, 128}; // degree symbol

byte arrow_up[8] = {     // Custom Character arrow up
  0b00000,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b00100,
  0b00100,
  0b00100
};

byte arrow_down[8] = {    // Custom Character arrow down
  0b00000,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b10101,
  0b01110,
  0b00100
};

byte logo1[8] = {         // Custom Flexitree logo Character pixel 1
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b01110,
  0b11111
};

byte logo2[8] = {         // Custom Flexitree logo Character pixel 2
  0b11111,
  0b01110,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00111
};

byte logo3[8] = {         // Custom Flexitree logo Character pixel 3
  0b11111,
  0b00011,
  0b00001,
  0b00000,
  0b01000,
  0b01000,
  0b01000,
  0b11111
};

byte logo4[8] = {          // Custom Flexitree logo Character pixel 4
  0b01000,
  0b01000,
  0b01001,
  0b01001,
  0b01111,
  0b00000,
  0b00000,
  0b00000
};

//  Global Variable Declarations

int flag1 = 0;
int flag2 = 0;
int flag3 = 0;
int flag4 = 0;
int flag5 = 0;
int flag6 = 0;
int flag7, flag8, flag9, flag10, flag11, flag12, flag13, flag14, flag15, flag16, flag17, flag18, flag19, flag20, flag21, flag22, superflag;
int flag23, flag24, flag25, flag26, flag27;
int flag28, flag29, flag30, flag31, flag32, flag33, flag34, flag35, flag36, flag37, flag38, flag39;
int wait, stamp, count1, count2, wait1, wait2, stamp1, stamp2;
int time2, time4, temp2, temp4, temp6, temp8, holding, holding1, holding2;
int motor_down1 = 31;
int motor_up1 = 30;
int motor_down2 = 33;
int motor_up2 = 32;
int save_sensor = 23;
int pedal_pin1 = 25;
int pedal_pin2 = 26;
int read1 = 0;
int read2 = 0;
int read3 = 0;
int read4 = 0;
int machine, move1, move2, move3;
float counter;
char key1, key2, key3, key4, key5, key6, key7, key8, key9, key10, key11, key12, key13, key14, key15, key16, key17, key18, key19, key20, key21, key22, key23;
char key24, key25, key26, key27;
char key28, key29, key30, key31, key32, key33, key34, key35, key36, key37, key40, key41, key42, key50;
unsigned long hold_time1 = 0, hold_time2 = 0;
unsigned long stint1 = 0, stint2 = 0;
unsigned long  hold_initializer1 = 0, hold_initializer2 = 0;
unsigned long TimerA1 = 0, TimerA2 = 0;
unsigned long TimerB1 = 0, TimerB2 = 0;
unsigned long currentmillis = 0;
unsigned long lag = 0;
unsigned long finallag = 0;
unsigned long heater_read_gap1 = 0;
unsigned long heater_read_gap2 = 0;
unsigned long heater_read_gap3 = 0;
unsigned long heater_read_gap4 = 0;

// LCD Connection

LiquidCrystal lcd(45, 46, 47, 48, 49, 50);

// Keypad Connection

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns

char keys[ROWS][COLS] = {

  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup()
{

  // Initializing.

  //  Digital Pin Type Declaration

  pinMode (motor_down1, OUTPUT);
  pinMode (motor_down2, OUTPUT);
  pinMode (motor_up1, OUTPUT);
  pinMode (motor_up2, OUTPUT);
  pinMode (save_sensor, INPUT);
  pinMode (pedal_pin1, INPUT);
  pinMode (pedal_pin2, INPUT);
  pinMode (heater1, OUTPUT);
  pinMode (heater2, OUTPUT);
  pinMode (heater3, OUTPUT);
  pinMode (heater4, OUTPUT);

  lcd.begin(20, 4);

  // Creating Custom Characters

  lcd.createChar(0, degree);
  lcd.createChar(1, arrow_up);
  lcd.createChar(2, arrow_down);
  lcd.createChar(3, logo1);
  lcd.createChar(4, logo2);
  lcd.createChar(5, logo3);
  lcd.createChar(6, logo4);

  // Welcome Screen

  lcd.setCursor(5, 1);
  lcd.print ("Flexitree");
  lcd.setCursor(2, 1);
  lcd.write(byte(3));
  lcd.setCursor(2, 0);
  lcd.write(byte(4));
  lcd.setCursor(3, 0);
  lcd.write(byte(5));
  lcd.setCursor(3, 1);
  lcd.write(byte(6));
  delay(500);

  while (key1 != 'A')
  {
    lcd.setCursor(5, 3);
    lcd.print("PRESS START");
    key1 = keypad.getKey();
  }

  lcd.clear();

  //Choose Machine options

  lcd.setCursor(14, 0);
  lcd.print("SELECT");
  lcd.setCursor(0, 1);
  lcd.print("1. MACHINE 1");
  lcd.setCursor(0, 2);
  lcd.print("2. MACHINE 2");
  lcd.setCursor(0, 3);
  lcd.print("3. MACHINE 1 & 2");

  while (flag28 != 2)
  {
    key28 = keypad.waitForKey();
    if (key28 == '1' || key28 == '2' || key28 == '3') {
      flag28 = 2;
    }
  }

  if (key28 == '1') {
    machine = 1;
  }
  else if (key28 == '2') {
    machine = 2;
  }
  else if (key28 == '3') {
    machine = 3;
  }


  // Initial Calibration

  const unsigned long calibrate = millis();
  while ((millis() - calibrate) < 5000) {

    if (machine == 1 || machine == 3 ) {
      digitalWrite(motor_up1, HIGH);
      digitalWrite(motor_down1, LOW);
    }

    if (machine == 2 || machine == 3 ) {
      digitalWrite(motor_up2, HIGH);
      digitalWrite(motor_down2, LOW);
    }

    lcd.clear();
    lcd.setCursor(4, 2);
    lcd.print("PLEASE WAIT...");
  }

  if (machine == 1 || machine == 3) {
    digitalWrite(motor_up1, LOW);
    digitalWrite(motor_down1, LOW);
  }
  if (machine == 2 || machine == 3) {
    digitalWrite(motor_up2, LOW);
    digitalWrite(motor_down2, LOW);
  }
  lcd.clear();

  // Modify heater settings

  lcd.setCursor(7, 0);
  lcd.print("CHANGE");
  lcd.setCursor(2, 1);
  lcd.print("HEATER  SETTINGS");
  lcd.setCursor(0, 3);
  lcd.print("BACK");
  lcd.setCursor(15, 3);
  lcd.print("ENTER");
  while (flag39 != 2) {
    key37 = keypad.waitForKey();
    if (key37 == '*') {
      flag39 = 2;
      set_temp = 0;
    }
    else if (key37 == '#') {
      flag39 = 2;
      set_temp = 1;
    }
  }


  // Temperature Limit Inputs
  lcd.clear();

  if (set_temp == 1) {
    // HEATER 1
    if (machine == 1 || machine == 3 ) {
      while (flag13 != 2)
      {
        flag14 = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ENTER HEATER 1 TEMP");
        while ( flag15 != 2 ) {
          key11 = keypad.waitForKey();
          flag15 = 2;
          if (key11 == 'A' || key11 == 'B' || key11 == 'C' || key11 == 'D' || key11 == '#' || key11 == '*' ) {
            flag15 = 0;
          }
        }
        lcd.setCursor(1, 2);
        lcd.print(key11);
        while ( flag16 != 2 ) {
          key12 = keypad.waitForKey();
          flag16 = 2;
          if (key12 == 'A' || key12 == 'B' || key12 == 'C' || key12 == 'D' || key12 == '#' || key12 == '*' ) {
            flag16 = 0;
          }
        }
        lcd.setCursor(2, 2);
        lcd.print(key12);
        while (  flag17 != 2 ) {
          key13 = keypad.waitForKey();
          flag17 = 2;
          if (key13 == 'A' || key13 == 'B' || key13 == 'C' || key13 == 'D' || key13 == '#' || key13 == '*' ) {
            flag17 = 0;
          }
        }

        lcd.setCursor(3, 2);
        lcd.print(key13);
        lcd.setCursor(5, 2);
        lcd.write(byte(0));
        lcd.setCursor(6, 2);
        lcd.print("C");
        char temp1[3] = {key11, key12, key13};
        temp2 = (temp1[0] - '0') * 100 + ((temp1[1] - '0')) * 10 + ((temp1[2] - '0'));
        delay(1000);
        lcd.clear();
        lcd.setCursor (5, 1);
        lcd.print(temp2);
        lcd.setCursor (9, 1);
        lcd.write(byte(0));
        lcd.setCursor (10, 1);
        lcd.print("C");
        lcd.setCursor(4, 2);
        lcd.print(" Confirm ? ");
        lcd.setCursor(0, 3);
        lcd.print("BACK");
        lcd.setCursor(15, 3);
        lcd.print("ENTER");

        while (flag14 != 2)
        {
          key14 = keypad.waitForKey();
          if (key14 == '#' || key14 == '*')
          {
            flag14 = 2; flag15 = 0; flag16 = 0; flag17 = 0;
          }

        }
        if (key14 == '#')
        {
          flag13 = 2;
        }
      }


      // HEATER 2

      while (flag18 != 2)
      {
        flag19 = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ENTER HEATER 2 TEMP");
        while ( flag20 != 2 ) {
          key15 = keypad.waitForKey();
          flag20 = 2;
          if (key15 == 'A' || key15 == 'B' || key15 == 'C' || key15 == 'D' || key15 == '#' || key15 == '*' ) {
            flag20 = 0;
          }
        }
        lcd.setCursor(1, 2);
        lcd.print(key15);
        while ( flag21 != 2 ) {
          key16 = keypad.waitForKey();
          flag21 = 2;
          if (key16 == 'A' || key16 == 'B' || key16 == 'C' || key16 == 'D' || key16 == '#' || key16 == '*' ) {
            flag21 = 0;
          }
        }
        lcd.setCursor(2, 2);
        lcd.print(key16);
        while (  flag22 != 2 ) {
          key17 = keypad.waitForKey();
          flag22 = 2;
          if (key17 == 'A' || key17 == 'B' || key17 == 'C' || key17 == 'D' || key17 == '#' || key17 == '*' ) {
            flag22 = 0;
          }
        }

        lcd.setCursor(3, 2);
        lcd.print(key17);
        lcd.setCursor(5, 2);
        lcd.write(byte(0));
        lcd.setCursor(6, 2);
        lcd.print("C");
        char temp3[3] = {key15, key16, key17};
        temp4 = (temp3[0] - '0') * 100 + (temp3[1] - '0') * 10 + (temp3[2] - '0');
        delay(1000);
        lcd.clear();
        lcd.setCursor (5, 1);
        lcd.print(temp4);
        lcd.setCursor (9, 1);
        lcd.write(byte(0));
        lcd.setCursor(10, 1);
        lcd.print("C");
        lcd.setCursor(4, 2);
        lcd.print(" Confirm ? ");
        lcd.setCursor(0, 3);
        lcd.print("BACK");
        lcd.setCursor(15, 3);
        lcd.print("ENTER");

        while (flag19 != 2)
        {
          key18 = keypad.waitForKey();
          if (key18 == '#' || key18 == '*')
          {
            flag19 = 2; flag20 = 0; flag21 = 0; flag22 = 0;
          }

        }
        if (key18 == '#')
        {
          flag18 = 2;
        }
      }
      lcd.clear();

    }

    // HEATER 3

    if (machine == 2 || machine == 3) {
      while (flag29 != 2)
      {
        flag30 = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ENTER HEATER 3 TEMP");
        while ( flag31 != 2 ) {
          key29 = keypad.waitForKey();
          flag31 = 2;
          if (key29 == 'A' || key29 == 'B' || key29 == 'C' || key29 == 'D' || key29 == '#' || key29 == '*' ) {
            flag31 = 0;
          }
        }
        lcd.setCursor(1, 2);
        lcd.print(key29);
        while ( flag32 != 2 ) {
          key30 = keypad.waitForKey();
          flag32 = 2;
          if (key30 == 'A' || key30 == 'B' || key30 == 'C' || key30 == 'D' || key30 == '#' || key30 == '*' ) {
            flag32 = 0;
          }
        }
        lcd.setCursor(2, 2);
        lcd.print(key30);
        while (  flag33 != 2 ) {
          key31 = keypad.waitForKey();
          flag33 = 2;
          if (key31 == 'A' || key31 == 'B' || key31 == 'C' || key31 == 'D' || key31 == '#' || key31 == '*' ) {
            flag33 = 0;
          }
        }

        lcd.setCursor(3, 2);
        lcd.print(key31);
        lcd.setCursor(5, 2);
        lcd.write(byte(0));
        lcd.setCursor(6, 2);
        lcd.print("C");
        char temp5[3] = {key29, key30, key31};
        temp6 = (temp5[0] - '0') * 100 + ((temp5[1] - '0')) * 10 + ((temp5[2] - '0'));
        delay(1000);
        lcd.clear();
        lcd.setCursor (5, 1);
        lcd.print(temp6);
        lcd.setCursor (9, 1);
        lcd.write(byte(0));
        lcd.setCursor (10, 1);
        lcd.print("C");
        lcd.setCursor(4, 2);
        lcd.print(" Confirm ? ");
        lcd.setCursor(0, 3);
        lcd.print("BACK");
        lcd.setCursor(15, 3);
        lcd.print("ENTER");

        while (flag30 != 2)
        {
          key32 = keypad.waitForKey();
          if (key32 == '#' || key32 == '*')
          {
            flag30 = 2; flag31 = 0; flag32 = 0; flag33 = 0;
          }

        }
        if (key32 == '#')
        {
          flag29 = 2;
        }
      }


      // HEATER 4

      while (flag34 != 2)
      {
        flag35 = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ENTER HEATER 4 TEMP");
        while ( flag36 != 2 ) {
          key33 = keypad.waitForKey();
          flag36 = 2;
          if (key33 == 'A' || key33 == 'B' || key33 == 'C' || key33 == 'D' || key33 == '#' || key33 == '*' ) {
            flag36 = 0;
          }
        }
        lcd.setCursor(1, 2);
        lcd.print(key33);
        while ( flag37 != 2 ) {
          key34 = keypad.waitForKey();
          flag37 = 2;
          if (key34 == 'A' || key34 == 'B' || key34 == 'C' || key34 == 'D' || key34 == '#' || key34 == '*' ) {
            flag37 = 0;
          }
        }
        lcd.setCursor(2, 2);
        lcd.print(key34);
        while (  flag38 != 2 ) {
          key35 = keypad.waitForKey();
          flag38 = 2;
          if (key35 == 'A' || key35 == 'B' || key35 == 'C' || key35 == 'D' || key35 == '#' || key35 == '*' ) {
            flag38 = 0;
          }
        }

        lcd.setCursor(3, 2);
        lcd.print(key35);
        lcd.setCursor(5, 2);
        lcd.write(byte(0));
        lcd.setCursor(6, 2);
        lcd.print("C");
        char temp7[3] = {key33, key34, key35};
        temp8 = (temp7[0] - '0') * 100 + (temp7[1] - '0') * 10 + (temp7[2] - '0');
        delay(1000);
        lcd.clear();
        lcd.setCursor (5, 1);
        lcd.print(temp8);
        lcd.setCursor (9, 1);
        lcd.write(byte(0));
        lcd.setCursor(10, 1);
        lcd.print("C");
        lcd.setCursor(4, 2);
        lcd.print(" Confirm ? ");
        lcd.setCursor(0, 3);
        lcd.print("BACK");
        lcd.setCursor(15, 3);
        lcd.print("ENTER");

        while (flag35 != 2)
        {
          key36 = keypad.waitForKey();
          if (key36 == '#' || key36 == '*')
          {
            flag35 = 2; flag36 = 0; flag37 = 0; flag38 = 0;
          }

        }
        if (key36 == '#')
        {
          flag34 = 2;
        }
      }
      lcd.clear();

    }

    // Update Temperature Values

    EEPROM.update(0, temp2);
    EEPROM.update(1, temp4);
    EEPROM.update(2, temp6);
    EEPROM.update(3, temp8);
  }


  // Saved temperature reading




  temp2 = EEPROM.read(0);
  temp4 = EEPROM.read(1);
  temp6 = EEPROM.read(2);
  temp8 = EEPROM.read(3);



  // Mode of Operation Choice Screen




  // Mode of Operation Choice Screen

  if (machine == 1 || machine == 2) {


    while (flag1 != 2)
    {
      lcd.setCursor(2, 0);
      lcd.print("CHOOSE   MODE");
      lcd.setCursor(0, 1);
      lcd.print("1. AUTOMATIC");
      lcd.setCursor(0, 2);
      lcd.print("2. MANUAL KEY PRESS");
      lcd.setCursor(0, 3);
      lcd.print("3. FOOT PEDAL");
      key2 = keypad.waitForKey();

      if ((key2 == '1') || (key2 == '2') || (key2 == '3'))
      {
        flag1 = 2;
      }
    }

    lcd.clear ();


    // Mode : Automatic with time feed.


    if (key2 == '1')
    {

      lcd.setCursor(5, 1);
      lcd.print("PRESS START");
      lcd.setCursor(0, 3);
      lcd.print("1.TIME SETTINGS");
      while ( move1 != 2) {
        key40 = keypad.waitForKey();
        move1 = 0;
        if (key40 == '1' || key40 == 'A') {
          move1 = 2;
        }

      }
      if (key40 == '1') {
        while (flag2 != 2)
        {
          flag3 = 0;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("ENTER WAIT TIME");
          while ( flag7 != 2 ) {
            key3 = keypad.waitForKey();
            flag7 = 2;
            if (key3 == 'A' || key3 == 'B' || key3 == 'C' || key3 == 'D' || key3 == '#' || key3 == '*' ) {
              flag7 = 0;
            }
          }
          lcd.setCursor(1, 2);
          lcd.print(key3);
          while ( flag8 != 2 ) {
            key4 = keypad.waitForKey();
            flag8 = 2;
            if (key4 == 'A' || key4 == 'B' || key4 == 'C' || key4 == 'D' || key4 == '#' || key4 == '*' ) {
              flag8 = 0;
            }
          }
          lcd.setCursor(2, 2);
          lcd.print(key4);
          while (  flag9 != 2 ) {
            key5 = keypad.waitForKey();
            flag9 = 2;
            if (key5 == 'A' || key5 == 'B' || key5 == 'C' || key5 == 'D' || key5 == '#' || key5 == '*' ) {
              flag9 = 0;
            }
          }

          lcd.setCursor(3, 2);
          lcd.print(key5);
          lcd.setCursor(5, 2);
          lcd.print("seconds");
          char time1[3] = {key3, key4, key5};
          wait = (time1[0] - '0') * 100 + ((time1[1] - '0')) * 10 + ((time1[2] - '0'));
          lcd.setCursor(5, 3);
          //lcd.print(wait);
          delay(1000);
          lcd.clear();
          lcd.setCursor (4, 1);
          lcd.print(wait);
          lcd.setCursor (8, 1);
          lcd.print("seconds");
          lcd.setCursor(4, 2);
          lcd.print(" Confirm ? ");
          lcd.setCursor(0, 3);
          lcd.print("BACK");
          lcd.setCursor(15, 3);
          lcd.print("ENTER");

          while (flag3 != 2)
          {
            key6 = keypad.waitForKey();
            if (key6 == '#' || key6 == '*')
            {
              flag3 = 2; flag7 = 0; flag8 = 0; flag9 = 0;
            }

          }
          if (key6 == '#')
          {
            flag2 = 2;
          }
        }

        while (flag4 != 2)
        {
          flag5 = 0;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("ENTER STAMP TIME");
          while ( flag10 != 2 ) {
            flag10 = 2;
            key7 = keypad.waitForKey();
            if (key7 == 'A' || key7 == 'B' || key7 == 'C' || key7 == 'D' || key7 == '#' || key7 == '*' ) {
              flag10 = 0;
            }
          }
          lcd.setCursor(1, 2);
          lcd.print(key7);
          while ( flag11 != 2 ) {
            flag11 = 2;
            key8 = keypad.waitForKey();
            if (key8 == 'A' || key8 == 'B' || key8 == 'C' || key8 == 'D' || key8 == '#' || key8 == '*' ) {
              flag11 = 0;
            }
          }
          lcd.setCursor(2, 2);
          lcd.print(key8);
          while ( flag12 != 2 ) {
            flag12 = 2;
            key9 = keypad.waitForKey();
            if (key9 == 'A' || key9 == 'B' || key9 == 'C' || key9 == 'D' || key9 == '#' || key9 == '*' ) {
              flag12 = 0;
            }
          }
          lcd.setCursor(3, 2);
          lcd.print(key9);
          lcd.setCursor(5, 2);
          lcd.print("seconds");
          char time3[3] = {key7, key8, key9};
          stamp = (time3[0] - '0') * 100 + ((time3[1] - '0')) * 10 + ((time3[2] - '0'));
          delay(1000);
          lcd.clear();
          lcd.setCursor (4, 1);
          lcd.print(stamp);
          lcd.setCursor (8, 1);
          lcd.print("seconds");
          lcd.setCursor(4, 2);
          lcd.print(" Confirm ? ");
          lcd.setCursor(0, 3);
          lcd.print("BACK");
          lcd.setCursor(15, 3);
          lcd.print("ENTER");

          while (flag5 != 2)
          {
            key10 = keypad.waitForKey();
            if (key10 == '#' || key10 == '*')
            {
              flag5 = 2; flag10 = 0; flag11 = 0; flag12 = 0;
            }
          }
          if (key10 == '#')
          {
            flag4 = 2;
          }
        }
        lcd.clear();

        lcd.clear();
        while (key19 != 'A')
        {
          lcd.setCursor(3, 0);
          lcd.print("AUTOMATIC MODE");
          lcd.setCursor(4, 2);
          lcd.print("PRESS  START");
          key19 = keypad.getKey();
        }
        if (machine == 1) {
          EEPROM.update(4, wait);
          EEPROM.update(5, stamp);
        }
        if (machine == 2) {
          EEPROM.update(6, wait);
          EEPROM.update(7, wait);
        }
      }
      superflag = 1;

      if (machine == 1) {
        wait = EEPROM.read(4);
        stamp = EEPROM.read(5);
        wait1 = wait;
        stamp1 = stamp;
      }
      if (machine == 2) {
        wait = EEPROM.read(6);
        stamp = EEPROM.read(7);
        wait2 = wait;
        stamp2 = stamp;
      }
    }

    // Manual Mode


    if (key2 == '2')

    {
      superflag = 2;
      lcd.clear();
      while (key20 != 'A')
      {
        lcd.setCursor(2, 0);
        lcd.print("MANUAL KEY PRESS");
        lcd.setCursor(4, 2);
        lcd.print("PRESS  START");
        key20 = keypad.getKey();
      }
      if (machine == 1) {
        digitalWrite(motor_down1, LOW);
        digitalWrite(motor_up1, LOW);
      }
      if (machine == 2) {
        digitalWrite(motor_down2, LOW);
        digitalWrite(motor_up2, LOW);
      }
    }


    // Foot Pedal Mode

    if (key2 == '3')

    {
      superflag = 3;
      lcd.clear();

      lcd.setCursor(5, 1);
      lcd.print("PRESS START");
      lcd.setCursor(0, 3);
      lcd.print("1.TIME SETTINGS");
      while ( move2 != 2) {
        key41 = keypad.waitForKey();
        move2 = 0;
        if (key41 == '1' || key41 == 'A') {
          move2 = 2;
        }

      }

      if (key41 == '1') {
        while (flag23 != 2)
        {
          flag24 = 0;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("ENTER HOLDING TIME");
          while ( flag25 != 2 ) {
            key24 = keypad.waitForKey();
            flag25 = 2;
            if (key24 == 'A' || key24 == 'B' || key24 == 'C' || key24 == 'D' || key24 == '#' || key24 == '*' ) {
              flag25 = 0;
            }
          }
          lcd.setCursor(1, 2);
          lcd.print(key24);
          while ( flag26 != 2 ) {
            key25 = keypad.waitForKey();
            flag26 = 2;
            if (key25 == 'A' || key25 == 'B' || key25 == 'C' || key25 == 'D' || key25 == '#' || key25 == '*' ) {
              flag26 = 0;
            }
          }
          lcd.setCursor(2, 2);
          lcd.print(key25);
          while (  flag27 != 2 ) {
            key26 = keypad.waitForKey();
            flag27 = 2;
            if (key26 == 'A' || key26 == 'B' || key26 == 'C' || key26 == 'D' || key26 == '#' || key26 == '*' ) {
              flag27 = 0;
            }
          }

          lcd.setCursor(3, 2);
          lcd.print(key26);
          lcd.setCursor(5, 2);
          lcd.print("seconds");
          char time5[3] = {key24, key25, key26};
          holding = (time5[0] - '0') * 100 + ((time5[1] - '0')) * 10 + ((time5[2] - '0'));
          delay(1000);
          lcd.clear();

          lcd.setCursor (4, 1);
          lcd.print(holding);
          lcd.setCursor (8, 1);
          lcd.print("seconds");
          lcd.setCursor(4, 2);
          lcd.print(" Confirm ? ");
          lcd.setCursor(0, 3);
          lcd.print("BACK");
          lcd.setCursor(15, 3);
          lcd.print("ENTER");

          while (flag24 != 2)
          {
            key27 = keypad.waitForKey();
            if (key27 == '#' || key27 == '*')
            {
              flag24 = 2; flag25 = 0; flag26 = 0; flag27 = 0;
            }

          }
          if (key27 == '#')
          {
            flag23 = 2;
          }
        }
        lcd.clear();
        while (key21 != 'A')
        {
          lcd.setCursor(5, 0);
          lcd.print("FOOT PEDAL");
          lcd.setCursor(4, 2);
          lcd.print("PRESS  START");
          key21 = keypad.getKey();
        }
        if (machine == 1) {
          EEPROM.update(8, holding);
        }
        if (machine == 2) {
          EEPROM.update(9, holding);
        }
      }


      if (machine == 1) {
        holding = EEPROM.read(8);
        holding1 = holding;
      }
      if (machine == 2) {
        holding = EEPROM.read(9);
        holding2 = holding;
      }
    }
    lcd.clear();

  }

  if (machine == 3) {

    lcd.setCursor(4, 0);
    lcd.print("CHOOSE MODE");
    lcd.setCursor(0, 2);
    lcd.print("1. AUTOMATIC");
    lcd.setCursor(0, 3);
    lcd.print("2. FOOT PEDAL");
    wait1 = EEPROM.read(4);
    wait2 = EEPROM.read(6);
    stamp1 = EEPROM.read(5);
    stamp2 = EEPROM.read(7);
    holding1 = EEPROM.read(8);
    holding2 = EEPROM.read(9);

    while (move3 != 2) {
      key42 = keypad.waitForKey();
      move3 = 0;
      if (key42 == '1') {
        move3 = 2;
        superflag = 1;
      }
      if (key42 == '2') {
        move3 = 2;
        superflag = 3;
      }
    }

  }
  lcd.clear();
}

// Running
void loop()
{


  if (machine == 1 || machine == 3) {

    if ( millis() - heater_read_gap1 >= 500 && step_time1 == 0)
    {

      heatertemp1 = thermocouple1.readCelsius();

      //lcd.setCursor(1, 0);          // heater1 temperature
      //lcd.print(heatertemp1);

      heater_read_gap2 = millis();
      step_time1 = 1;
      step_time2 = 0;
    }



    if ( millis() - heater_read_gap2 >= 500 && step_time2 == 0)
    {

      heatertemp2 = thermocouple2.readCelsius();

      //lcd.setCursor(11, 0);          // heater2 temperature
      //lcd.print(heatertemp2);

      heater_read_gap1 = millis();
      step_time1 = 0;
      step_time2 = 1;
    }




    if (heatertemp1 > temp2 + 5  && digitalRead(heater1) == HIGH) {   // heater 1 auto switch on off
      digitalWrite(heater1, LOW);
    }  // too hot :p
    if (heatertemp1 < temp2 && digitalRead(heater1) == LOW) {
      digitalWrite(heater1, HIGH);
    }


    if (heatertemp2 > temp4 + 5  && digitalRead(heater2) == HIGH) {   // heater 2 auto switch on off
      digitalWrite(heater2, LOW);
    }  // Again too hot to handle :p
    if (heatertemp2 < temp4 && digitalRead(heater2) == LOW) {
      digitalWrite(heater2, HIGH);
    }

  }



  if (machine == 2 || machine == 3) {

    if ( millis() - heater_read_gap3 >= 500 && step_time3 == 0)
    {

      heatertemp3 = thermocouple3.readCelsius();

      //lcd.setCursor(1, 0);          // heater3 temperature
      //lcd.print(heatertemp1);

      heater_read_gap4 = millis();
      step_time3 = 1;
      step_time4 = 0;
    }



    if ( millis() - heater_read_gap4 >= 500 && step_time4 == 0)
    {

      heatertemp4 = thermocouple4.readCelsius();

      //lcd.setCursor(11, 0);          // heater4 temperature
      //lcd.print(heatertemp2);

      heater_read_gap3 = millis();
      step_time3 = 0;
      step_time4 = 1;
    }




    if (heatertemp3 > temp6 + 5  && digitalRead(heater3) == HIGH) {   // heater 3 auto switch on off
      digitalWrite(heater3, LOW);
    }  // too hot :p
    if (heatertemp3 < temp6 && digitalRead(heater3) == LOW) {
      digitalWrite(heater3, HIGH);
    }


    if (heatertemp4 > temp8 + 5  && digitalRead(heater4) == HIGH) {   // heater 4 auto switch on off
      digitalWrite(heater4, LOW);
    }  // Again too hot to handle :p
    if (heatertemp4 < temp8 && digitalRead(heater4) == LOW) {
      digitalWrite(heater4, HIGH);
    }
  }


  if (digitalRead(save_sensor) == HIGH)                            // Interuption sensor working
  {
    if (machine == 1 || machine == 3) {
      digitalWrite(motor_down1, LOW);
      digitalWrite(motor_up1, LOW);
    }
    if (machine == 2 || machine == 3) {
      digitalWrite(motor_down2, LOW);
      digitalWrite(motor_up2, LOW);
    }
    lag = millis() - currentmillis;
  }

  if (digitalRead(save_sensor) == LOW)                            // Actual working of operation modes
  {

    finallag = finallag + lag;          // interrupt update



    // Machine 1

    if (machine == 1 || machine == 3) {

      digitalWrite(motor_up1, read1);
      digitalWrite(motor_down1, read2);

      if (superflag == 1) // Auto Mode
      {

        //lcd.setCursor(4, 2);
        //lcd.print("COUNT : ");
        //lcd.setCursor(12, 2);
        //lcd.print(count);

        if (millis() - TimerA1 - finallag >= stint1 * 1000 && digitalRead(motor_down1) == LOW) {

          TimerB1 = millis() - finallag ;

          digitalWrite(motor_down1, HIGH);
          digitalWrite(motor_up1, LOW);
          stint1 = wait1;
          //lcd.setCursor(0, 0);
          // lcd.print(TimerB);
        }
        if (millis() - TimerB1 - finallag >= stamp1 * 1000 && digitalRead(motor_up1) == LOW) {

          TimerA1 = millis() - finallag ;

          digitalWrite(motor_down1, LOW);
          digitalWrite(motor_up1, HIGH);
          count1 = count1 + 1;

        }

      }

      if (superflag == 2) // Manual Mode
      {

        //      lcd.setCursor(1, 2);
        //      lcd.write(byte(1));
        //      lcd.setCursor(18, 2);
        //      lcd.write(byte(2));
        //      lcd.setCursor(5, 2);
        //      lcd.print("COUNT : ");
        //      lcd.setCursor(13, 2);
        //      lcd.print(count1);

        key22 = keypad.getKey();

        if (key22)
        {
          if (key22 == 'C')
          {
            digitalWrite(motor_down1, HIGH);
            digitalWrite(motor_up1, LOW);
            lcd.clear();
            lcd.setCursor(14, 3);
            lcd.print("..DOWN");
          }
          if (key22 == 'B')
          {
            digitalWrite(motor_up1, HIGH);
            digitalWrite(motor_down1, LOW);
            lcd.clear();
            count1 = count1 + 1;
            lcd.setCursor(1, 3);
            lcd.print("UP..");
          }
          if (key22 == 'D')
          {
            digitalWrite(motor_up1, LOW);
            digitalWrite(motor_down1, LOW);
            lcd.clear();
            lcd.setCursor(8, 3);
            lcd.print("STOP");
          }
        }
      }

      if (superflag == 3)  // Foot Pedal Mode
      {

        //      lcd.setCursor(5, 2);
        //      lcd.print("COUNT : ");
        //      lcd.setCursor(13, 2);
        //      lcd.print(count1);

        if (digitalRead(motor_down1) == LOW && millis() - hold_time1 - finallag >= hold_initializer1 * 1000 ) {
          hold_initializer1 = holding1 ;
          if (digitalRead(pedal_pin1) == HIGH)
          {

            hold_time1 = millis() - finallag;
            digitalWrite(motor_down1, HIGH);
            digitalWrite(motor_up1, LOW);
            count1 = count1 + 1;

          }
        }
        if (millis() - hold_time1 - finallag >= holding1 * 1000) {
          digitalWrite(motor_down1, LOW);
          digitalWrite(motor_up1, HIGH);

        }

      }
    }


    //Machine 2

    if (machine == 2 || machine == 3) {

      digitalWrite(motor_up2, read3);
      digitalWrite(motor_down2, read4);

      if (superflag == 1) // Auto Mode
      {



        if (millis() - TimerA2 - finallag >= stint2 * 1000 && digitalRead(motor_down2) == LOW) {

          TimerB2 = millis() - finallag ;

          digitalWrite(motor_down2, HIGH);
          digitalWrite(motor_up2, LOW);
          stint2 = wait2;
          //lcd.setCursor(0, 0);
          // lcd.print(TimerB);
        }
        if (millis() - TimerB2 - finallag >= stamp2 * 1000 && digitalRead(motor_up2) == LOW) {

          TimerA2 = millis() - finallag ;

          digitalWrite(motor_down2, LOW);
          digitalWrite(motor_up2, HIGH);
          count2 = count2 + 1;

        }

      }

      if (superflag == 2) // Manual Mode
      {

        //      lcd.setCursor(1, 2);
        //      lcd.write(byte(1));
        //      lcd.setCursor(18, 2);
        //      lcd.write(byte(2));
        //      lcd.setCursor(5, 2);
        //      lcd.print("COUNT : ");
        //      lcd.setCursor(13, 2);
        //      lcd.print(count2);

        key50 = keypad.getKey();

        if (key50)
        {
          if (key50 == 'C')
          {
            digitalWrite(motor_down2, HIGH);
            digitalWrite(motor_up2, LOW);
            lcd.clear();
            lcd.setCursor(14, 3);
            lcd.print("..DOWN");
          }
          if (key50 == 'B')
          {
            digitalWrite(motor_up2, HIGH);
            digitalWrite(motor_down2, LOW);
            lcd.clear();
            count2 = count2 + 1;
            lcd.setCursor(1, 3);
            lcd.print("UP..");
          }
          if (key50 == 'D')
          {
            digitalWrite(motor_up2, LOW);
            digitalWrite(motor_down2, LOW);
            lcd.clear();
            lcd.setCursor(8, 3);
            lcd.print("STOP");
          }
        }
      }

      if (superflag == 3)  // Foot Pedal Mode
      {

        //      lcd.setCursor(5, 2);
        //      lcd.print("COUNT : ");
        //      lcd.setCursor(13, 2);
        //      lcd.print(count2);

        if (digitalRead(motor_down2) == LOW && millis() - hold_time2 - finallag >= hold_initializer2 * 1000 ) {
          hold_initializer2 = holding2 ;
          if (digitalRead(pedal_pin2) == HIGH)
          {

            hold_time2 = millis() - finallag;
            digitalWrite(motor_down2, HIGH);
            digitalWrite(motor_up2, LOW);
            count2 = count2 + 1;

          }
        }
        if (millis() - hold_time2 - finallag >= holding2 * 1000) {
          digitalWrite(motor_down2, LOW);
          digitalWrite(motor_up2, HIGH);

        }

      }
    }

    currentmillis = millis();
    lag = 0;
    read1 = digitalRead(motor_up1);
    read2 = digitalRead(motor_down1);
    read3 = digitalRead(motor_up2);
    read4 = digitalRead(motor_down2);
  }

  if (machine == 1) {
    lcd.setCursor(1, 0);
    lcd.print(heatertemp1);
    lcd.setCursor(11, 0);
    lcd.print(heatertemp2);
    lcd.setCursor(7, 0);
    lcd.write((byte)0);
    lcd.setCursor(8, 0);
    lcd.print("C");
    lcd.setCursor(17, 0);
    lcd.write((byte)0);
    lcd.setCursor(18, 0);
    lcd.print("C");
    lcd.setCursor(4, 2);
    lcd.print("COUNT : ");
    lcd.setCursor(12, 2);
    lcd.print(count1);
  }

  if (machine == 2) {
    lcd.setCursor(1, 0);
    lcd.print(heatertemp3);
    lcd.setCursor(11, 0);
    lcd.print(heatertemp4);
    lcd.setCursor(7, 0);
    lcd.write((byte)0);
    lcd.setCursor(8, 0);
    lcd.print("C");
    lcd.setCursor(17, 0);
    lcd.write((byte)0);
    lcd.setCursor(18, 0);
    lcd.print("C");
    lcd.setCursor(4, 2);
    lcd.print("COUNT : ");
    lcd.setCursor(12, 2);
    lcd.print(count2);
  }

  if (machine == 3) {

    lcd.setCursor(0, 0);
    lcd.print(heatertemp1);
    lcd.setCursor(0, 1);
    lcd.print(heatertemp2);
    lcd.setCursor(6, 0);
    lcd.write((byte)0);
    lcd.setCursor(7, 0);
    lcd.print("C");
    lcd.setCursor(6, 1);
    lcd.write((byte)0);
    lcd.setCursor(7, 1);
    lcd.print("C");
    lcd.setCursor(9, 0);
    lcd.print("COUNT: ");
    lcd.setCursor(16, 0);
    lcd.print(count1);

    lcd.setCursor(0, 2);
    lcd.print(heatertemp3);
    lcd.setCursor(0, 3);
    lcd.print(heatertemp4);
    lcd.setCursor(6, 2);
    lcd.write((byte)0);
    lcd.setCursor(7, 2);
    lcd.print("C");
    lcd.setCursor(6, 3);
    lcd.write((byte)0);
    lcd.setCursor(7, 3);
    lcd.print("C");
    lcd.setCursor(9, 3);
    lcd.print("COUNT: ");
    lcd.setCursor(16, 3);
    lcd.print(count2);
  }



}


//  ******** Only like gravity are places that pull. ********
