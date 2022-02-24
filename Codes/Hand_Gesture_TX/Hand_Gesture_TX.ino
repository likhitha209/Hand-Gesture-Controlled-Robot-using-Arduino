#include <VirtualWire.h>                   //library that provides features to send short messages, without addressing, retransmit using ASK


#define x A0                               //to give a constant value before the program is compiled.
#define y A1
#define z A2

char *data;                               // 'data' is stored in char data type(taken as)

int x_val;                                // x_val taken as integer data type
int y_val;                                // y_val taken as integer data type
int z_val;                                // z_val taken as integer data type

int x_val2;                               // x_val2 taken as integer data type
int y_val2;                               // y_val2 taken as integer data type
int z_val2;                               // z_val2 taken as integer data type

void setup()                              //code runs once
{
  vw_set_tx_pin(12);                      //setting transmitter pin to 12
  vw_setup(2000);                         //setting operating speed(bps)
  pinMode(x, INPUT);                      //The pinMode() to take input or an output. 
  pinMode(y, INPUT);
  pinMode(z, INPUT);
  Serial.begin(9600);                     //serial communication from Arduino to send out commands through the USB connection
  x_val2 = analogRead(x);                 //Reads the value from the specified analog pin A0 SINCE x=A0
  y_val2 = analogRead(y);
  z_val2 = analogRead(z);
}

void loop()                                 //code will repeat over and over again
{
  x_val = analogRead(x);                  
  y_val = analogRead(y);
  z_val = analogRead(z);

  int x_axis = x_val - x_val2;             //difference of x_val and x_val2 to find out the axis 
  int y_axis = y_val - y_val2;
  int z_axis = z_val - z_val2;
  
  if(y_axis >= 60)                           //FORWARD MOVEMENT
  {
    data="f";                                //if satisfies condition f is assigned to data
    vw_send((uint8_t *)data, strlen(data));  
    vw_wait_tx();                            //Block until the transmitter is idle then returns
    delay(500);                              //Pauses the program for the amount of time (in milliseconds)
    Serial.println("Forward");               // Prints data
  }
  else if(y_axis <= -60)                     //BACKWARD MOVEMENT        
  {
    data="b";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
    delay(500);
    Serial.println("Backward");
  }
  else if(x_axis >= 60)                      //RIGHT MOVEMENT
  {
    data="r";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
    delay(500);
    Serial.println("Right");
  }
  else if(x_axis <= -60)                    //LEFT MOVEMENT
  {
    data="l";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
    delay(500);
    Serial.println("Left");
  }
  else                                        //STOP
  {
    data="s";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
    delay(500);
    Serial.println("Stop");
  }
}
