//Allow to use external libraries
#include <Servo.h>
#include <Keypad.h>


///char password [3] = {'6','1','8'};  // change the password here, just pick any 3 numbers
int position = 0;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[ROWS] = { 8, 7, 6, 9 }; //pins on arduino board
byte colPins[COLS] = { 5, 4, 3, 2 }; //pins pn arduino board

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// This is the set up for LED lights,
//it will be associated with the pins on the arduino board labled numbers 11 to 13

int Magnetpin = 10;
int RedpinLock = 11;
int GreenpinUnlock = 12;
int YellowpinTimer = 13;

void setup()
{
  pinMode(RedpinLock, OUTPUT);
  pinMode(GreenpinUnlock, OUTPUT);
  pinMode(YellowpinTimer, OUTPUT);
  pinMode(Magnetpin, OUTPUT);
 

}

//################## This loop is an ongoing algorithm that makes the program. Function #####################

void loop()
{
 
 LockedPosition(false); //box is unlocked

 
 SetTimer(true); // Function that lets you pick time to set on the lockbox

 char key = keypad.getKey();

  if (key == '*'){

    LockedPosition(true);

  if (key == password[position])
    {
    position ++;
    }

  if (key == 'A')
    {
      position = 0;
      LockedPosition(false);
      delay(100);
      SetTimer(true);
    }
  }
}

//################## This part of the code sets up the locking mechanism. #####################

void LockedPosition(bool locked)
{
  if (locked)
   {
    digitalWrite(RedpinLock, HIGH);
    digitalWrite(GreenpinUnlock, LOW);
    digitalWrite(Magnetpin, HIGH);// Set the voltage on the magnet to high.. aka locked.
   
  }
  if(!locked)
   {
    digitalWrite(RedpinLock, LOW);
    digitalWrite(GreenpinUnlock, HIGH);
    digitalWrite(Magnetpin,LOW);
   
   }
}



void SetTimer(bool x)
{
 
 
 
  while(x)
  {
   
    char key = keypad.getKey();/// Input from the keypad
   
    digitalWrite(YellowpinTimer, HIGH);
    delay(500);
    digitalWrite(YellowpinTimer,LOW);

    if( key == 'A'){

      LockedPosition(true);
      delay(20000);
      LockedPosition(false);
      x = false;
    }
    else if (key == 'B'){

      LockedPosition(true);
      delay(60000);
      LockedPosition(false);
      x = false;
    }
   
    else if(key == 'C'){
   
      LockedPosition(true);
      delay(180000);
      LockedPosition(false);
      x = false;
    }
    else if(key == 'D'){

      LockedPosition(true);
      delay(36000000);
      LockedPosition(false);
      x = false;
    }
  }
}