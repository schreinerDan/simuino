//================================================
//  Developed by Benny Saxen, ADCAJO
//================================================


//=====================================
// Functions
//=====================================


//------ Digital I/O -----------------------

void pinMode(int pin,int mode)
{
  char temp[120];

  //passTime();
  if(mode == INPUT || mode == OUTPUT)
    {
      digitalMode[pin] = mode;
      wmove(uno,DP-1,digPinPos[pin]);
      waddch(uno,ACS_VLINE);
      wmove(uno,DP-2,digPinPos[pin]-1);

      if(mode==INPUT)
	{
	  strcpy(temp,textPinModeIn[pin]);
	  wprintw(uno,"In");
	  if(strstr(temp,"void"))
	    wLog1("pinMode IN",pin);
	  else
	    wLog1(temp,pin);
	}

      if(mode==OUTPUT)
	{
	  strcpy(temp,textPinModeOut[pin]);
	  wprintw(uno,"Out");
	  if(strstr(temp,"void"))
	    wLog1("pinMode OUT",pin);
	  else
	    wLog1(temp,pin);
	}      
      show(uno);
    }
  else
    {
      showError("Unknown Pin Mode",mode);
    }
}

void digitalWrite(int pin,int value)
{
  char temp[120];
  //passTime();
  if(digitalMode[pin] == OUTPUT)
    {

      wmove(uno,DP,digPinPos[pin]);
      if(value==HIGH)
	{
	  strcpy(temp,textDigitalWriteHigh[pin]);
	  waddch(uno,ACS_DIAMOND);
	  if(confLogLev > 0)
	    { 
	      if(strstr(temp,"void"))
		wLog1("digitalWrite HIGH",pin);
	      else
		wLog1(temp,pin);
	    }
	}
      if(value==LOW)
	{
	  strcpy(temp,textDigitalWriteLow[pin]);
	  waddch(uno,ACS_BULLET);
	  if(confLogLev > 0)
	    {
	      if(strstr(temp,"void"))
		wLog1("digitalWrite LOW",pin);
	      else
		wLog1(temp,pin);
	    }
	}
      wmove(uno,DP+2,digPinPos[pin]);
      wprintw(uno,"w");
      show(uno);
      wmove(uno,DP,digPinPos[pin]-2);
      wprintw(uno,"%3d",value);
      wmove(uno,DP+2,digPinPos[pin]);
      wprintw(uno," ");
      show(uno);
    }
  else
    {
      showError("Wrong pin mode. Should be OUTPUT",pin);
      wLog("digitalWrite",pin,-1);
    }
}

int digitalRead(int pin)
{
  char temp[120];
  int value;

  //passTime();
  if(digitalMode[pin] == INPUT)
    {
      value = g_value;
 
      wmove(uno,DP+2,digPinPos[pin]);
      wprintw(uno,"r");
      show(uno);

      strcpy(temp,textDigitalRead[pin]);
      if(confLogLev > 0)
	{
	  if(strstr(temp,"void"))
	    wLog2("digitalRead",pin,value);
	  else
	    wLog2(temp,pin,value);
	}


      wmove(uno,DP,digPinPos[pin]);
      wprintw(uno,"%1d",value);
      wmove(uno,DP+2,digPinPos[pin]);
      wprintw(uno," ");
      show(uno);
    }
  else
    {
      showError("Wrong pin mode. Should be INPUT",pin);
      wLog("digitalRead",pin,value);

    }
  return(value);
}

//------ Analog I/O ------------------------

void analogReference(char type[])
{
  unimplemented("analogReference()");
  //DEFAULT, INTERNAL, INTERNAL1V1, INTERNAL2V56, or EXTERNAL
}

int analogRead(int pin)  // Values 0 to 1023
{

  int value;
  char temp[120];

  value = g_value;

  if(value > 1023 || value < 0)
    {
      sprintf(temp,"%d Analog pin=%d value out of range = %d",currentStep,pin,value);
      showError(temp,-1);
      value = 0;
    }
  
  wmove(uno,AP,anaPinPos[pin]-3);
  wprintw(uno,"%4d",value);
  wmove(uno,AP-2,anaPinPos[pin]);
  wprintw(uno,"r");
  show(uno);

  strcpy(temp,textAnalogRead[pin]);
  if(confLogLev > 0)
    {
      if(strstr(temp,"void"))
	wLog2("analogRead",pin,value);
      else
	wLog2(temp,pin,value);
    }


  wmove(uno,AP-2,anaPinPos[pin]);
  wprintw(uno," ");

  wmove(uno,AP+1,anaPinPos[pin]);
  waddch(uno,ACS_VLINE);
  wmove(uno,AP+2,anaPinPos[pin]-1);
  wprintw(uno,"In");

  show(uno);
  return(value); 
}

void analogWrite(int pin,int value) 
// Values 0 to 255   PWM: only pin 3,5,6,9,10,11
{
  char temp[120];

  if(digitalMode[pin] != OUTPUT)
    {
      showError("Pin is not in OUPUT mode: ",pin);
      return;
    }

  if(pin==3 || pin==5 || pin==6 || pin==9 || pin==10 || pin==11)
    {

      if(value > 256 || value < 0)
	{
	  sprintf(temp,"%d AnalogWrite pin=%d value out of range = %d",currentStep,pin,value);
	  showError(temp,-1);
	  value = 0;
	}

      wmove(uno,DP,digPinPos[pin]-2);
      wprintw(uno,"%3d",value);
      wmove(uno,DP+2,digPinPos[pin]);
      wprintw(uno,"a");
      show(uno);

      strcpy(temp,textAnalogWrite[pin]);
      if(confLogLev > 0)
	{
	  if(strstr(temp,"void"))
	    wLog2("analogWrite",pin,value);
	  else
	    wLog2(temp,pin,value);
	}

      wmove(uno,DP+2,digPinPos[pin]);
      wprintw(uno," ");
      show(uno);
    }
  else
    {
      showError("Pin is not of PWM type",pin);
    }
  return;
}

//------ Advanced I/O ----------------------
void tone(int pin, unsigned int freq)
{
  unimplemented("tone()");
}

void tone(int pin, unsigned int freq, unsigned long duration)
{
  unimplemented("tone()");
}

void noTone(int pin)
{
  unimplemented("noTone()");
}

void shiftOut(int dataPin, int clockPin, int bitOrder, int value)
{
  //bitOrder: which order to shift out the bits; either MSBFIRST or LSBFIRST.
  unimplemented("shiftOut()");
}

unsigned long pulseIn(int pin, int value)
{
  unimplemented("pulseIn(int,int)");
}

unsigned long pulseIn(int pin, int value, unsigned long timeout)
{
  unimplemented("pulseIn(int,int,unsigned long)");
}

//------ Time ------------------------------

unsigned long millis()
{
  //unimplemented("millis()");
  return(currentStep*100);
}

unsigned long micros()
{
  //unimplemented("micros()");
  return(currentStep*100000);
}

void delay(int ms)
{
  //passTime(); 
  wLog("delay",ms,-1);
  //msleep(ms);

}

void delayMicroseconds(int us)
{
  //passTime();
  wLog("delayMicroseconds",us,-1);
  //msleep(us);

}


//------ External Interrupts ---------------


void interrupt(char *m,int intrpt_no)
{
  wLog(m,intrpt_no,-1);
}

void attachInterrupt(int interrupt,void(*func)(),int mode)
{

  interruptMode[interrupt] = mode;

  if(interrupt == 0)
    {
      interrupt0 = func;
    }
  if(interrupt == 1)
    {
      interrupt1 = func;
    }

  if(interrupt != 0 && interrupt != 1)
    showError("Unsupported interrupt number",interrupt);

  if(confLogLev > 0)wLog("attachInterrupt",interrupt,-1);

}

//---------------------------------------------------
void detachInterrupt(int interrupt)
{

  if(interrupt == 0)
    {
      interrupt0 = NULL;
    }
  if(interrupt == 1)
    {
      interrupt1 = NULL;
    }
  
  if(interrupt != 0 && interrupt != 1)
    showError("Unsupported interrupt number",interrupt);
    
  if(confLogLev > 0)wLog("detachInterrupt",interrupt,-1);
}

//------ Interrupts ------------------------
void interrupts()
{
  unimplemented("interrupts()");
}
void noInterrupts()
{
  unimplemented("noInterrupts()");
}
//------ Communication ---------------------
class serial {

 public:
  void begin(int baudRate);
  void end();
  int  available();
  int  read();
  int  peek();
  void flush();
  void print(int x);
  void print(int x,int base);
  void print(const char *p);
  void println();
  void println(int x);
  void println(int x,int base);
  void println(const char *p);
  void write(int p);
  void write(char *p);
  void write(char *p, int len);
};

serial Serial,Serial1,Serial2,Serial3;

void serial::begin(int baudRate) 
{
  baud = baudRate;
  digitalMode[0] = RX;
  digitalMode[1] = TX;
  serialMode = ON;
  wLog("serial:begin",baud,-1);
}

void serial::end() 
{
  digitalMode[0] = FREE;
  digitalMode[1] = FREE;
  serialMode = OFF;
  if(confLogLev > 2)
    {
      wLog("serial:end",-1,-1);
    }
}

int serial::available()  // returns the number of bytes available to read
{
  unimplemented("Serial.available");
  return(1);
}

int serial::read() // the first byte of incoming serial data available (or -1 if no data is available)
{
  unimplemented("Serial.read");
  return(-1);
}

int serial::peek() 
{
  return(-1);
}

void serial::flush() 
{
  showSerial("flush",1);
}

void serial::print(int x) 
{
  sprintf(stemp,"%d",x);
  showSerial(stemp,0);
  wLog("serial:print",x,-1);
}

void serial::print(int x,int base) 
{
  sprintf(stemp,"%d",x);
  showSerial(stemp,0);
  wLog("serial:print base",x,-1);
}

void serial::print(const char *p) 
{
  sprintf(stemp,"%s",p);
  showSerial(stemp,0);
  wLogChar("serial:print",p,-1);
}

void serial::println() 
{
  //sprintf(stemp,"%d",x);
  showSerial(stemp,1);
  wLog("serial:println()",-1,-1);
}

void serial::println(int x) 
{
  sprintf(stemp,"%d",x);
  showSerial(stemp,1);
  wLog("serial:println",x,-1);
}

void serial::println(int x, int base) 
{
  sprintf(stemp,"%d",x);
  showSerial(stemp,1);
  wLog("serial:println base",x,-1);
}

void serial::println(const char *p) 
{
  sprintf(stemp,"%s",p);
  showSerial(stemp,1);
  wLogChar("serial:println",p,-1);
}

void serial::write(int p) 
{
  sprintf(stemp,"%d",p);
  showSerial(stemp,1);
  wLog("serial:write(val)",p,-1);
}

void serial::write(char *p) 
{
  sprintf(stemp,"%s",p);
  showSerial(stemp,1);
  wLogChar("serial:write(str)",p,-1);
}

void serial::write(char *p, int len) 
{
  sprintf(stemp,"%s",p);
  showSerial(stemp,1);
  wLogChar("serial:write(len)",p,-1);
}


//======================================================
// Ethernet Library
//======================================================

/* class Ethernet { */
/*  public: */
/*   void begin(int baudRate); */
/* }; */

/* void Ethernet::begin(char *mac,char *ip)  */
/* { */
/*   if(confLogLev > 0)wLog("Ethernet.begin",-1,-1); */
/* } */
/* void Ethernet::begin(char *mac,char *ip,char *gateway)  */
/* { */
/*   if(confLogLev > 0)wLog("Ethernet.begin",-1,-1); */
/* } */
/* void Ethernet::begin(char *mac,char *ip,char *gateway, char *subnet)  */
/* { */
/*   if(confLogLev > 0)wLog("Ethernet.begin",-1,-1); */
/* } */

/* class Server { */
/*  public: */
/* begin() */
/* available() */
/* write() */
/* print() */
/* println() */
/* }; */

/* void Server::Server(int port)  */
/* { */
/*   if(confLogLev > 0)wLog("Server.Server",port,-1); */
/* } */
/* void Server::begin()  */
/* { */
/*   if(confLogLev > 0)wLog("Server.begin",-1,-1); */
/* } */
/* Client Server::available()  */
/* { */
/*   Client x = Client(); */
/*   if(confLogLev > 0)wLog("Server.available",-1,-1); */
/*   return(x),  */
/* } */
/* void Server::write(char x)  */
/* { */
/*   if(confLogLev > 0)wLog("Server.write",-1,-1); */
/*   sprintf(stemp,"%c",x); */
/*   strcat(ethernetBuffer,stemp); */
/*   showEthernet(); */
/*   passTime(); */
/* } */
/* void Server::write(int x)  */
/* { */
/*   if(confLogLev > 0)wLog("Server.write",-1,-1); */
/*   sprintf(stemp,"%d",x); */
/*   strcat(ethernetBuffer,stemp); */
/*   showEthernet(); */
/*   passTime(); */
/* } */
/* void Server::print(char x)  */
/* { */
/*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
/*   sprintf(stemp,"%c",x); */
/*   strcat(ethernetBuffer,stemp); */
/*   showEthernet(); */
/*   passTime(); */
/* } */
/* void Server::print(int x)  */
/* { */
/*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
/*   sprintf(stemp,"%d",x); */
/*   strcat(ethernetBuffer,stemp); */
/*   showEthernet(); */
/*   passTime(); */
/* } */
/* void Server::print(char *x)  */
/* { */
/*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
/*   sprintf(stemp,"%s",x); */
/*   strcat(ethernetBuffer,stemp); */
/*   showEthernet(); */
/*   passTime(); */
/* } */
/* void Server::print(char x,char *base)  */
/* { */
/*   //BIN for binary (base 2)  */
 /*   //DEC for decimal (base 10) */
  /*   //OCT for octal (base 8) */
   /*   //HEX for hexadecimal (base 16) */
    /*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
    /*   sprintf(stemp,"%c",x); */
    /*   strcat(ethernetBuffer,stemp); */
    /*   showEthernet(); */
    /*   passTime(); */
    /* } */
    /* void Server::print(int x,char *base)  */
    /* { */
    /*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
    /*   sprintf(stemp,"%d",x); */
    /*   strcat(ethernetBuffer,stemp); */
    /*   showEthernet(); */
    /*   passTime(); */
    /* } */
    /* void Server::print(char *x,char *base)  */
    /* { */
    /*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
    /*   sprintf(stemp,"%s",x); */
    /*   strcat(ethernetBuffer,stemp); */
    /*   showEthernet(); */
    /*   passTime(); */
    /* } */
    /* void Server::println()  */
    /* { */
    /*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
    /*   sprintf(stemp,"\n"); */
    /*   strcat(ethernetBuffer,stemp); */
    /*   showEthernet(); */
    /*   passTime(); */
    /* } */
    /* void Server::println(char x)  */
    /* { */
    /*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
    /*   sprintf(stemp,"%c\n",x); */
    /*   strcat(ethernetBuffer,stemp); */
    /*   showEthernet(); */
    /*   passTime(); */
    /* } */
    /* void Server::println(int x)  */
    /* { */
    /*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
    /*   sprintf(stemp,"%d\n",x); */
    /*   strcat(ethernetBuffer,stemp); */
    /*   showEthernet(); */
    /*   passTime(); */
    /* } */
    /* void Server::println(char *x)  */
    /* { */
    /*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
    /*   sprintf(stemp,"%s\n",x); */
    /*   strcat(ethernetBuffer,stemp); */
    /*   showEthernet(); */
    /*   passTime(); */
    /* } */
    /* void Server::println(char x,char *base)  */
    /* { */
    /*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
    /*   sprintf(stemp,"%c\n",x); */
    /*   strcat(ethernetBuffer,stemp); */
    /*   showEthernet(); */
    /*   passTime(); */
    /* } */
    /* void Server::println(int x,char *base)  */
    /* { */
    /*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
    /*   sprintf(stemp,"%d\n",x); */
    /*   strcat(ethernetBuffer,stemp); */
    /*   showEthernet(); */
    /*   passTime(); */
    /* } */
    /* void Server::println(char *x,char *base)  */
    /* { */
    /*   if(confLogLev > 0)wLog("Server.print",-1,-1); */
    /*   sprintf(stemp,"%s\n",x); */
    /*   strcat(ethernetBuffer,stemp); */
    /*   showEthernet(); */
    /*   passTime(); */
    /* } */

    /* class Client { */
    /*  public: */
    /*   void begin(int baudRate); */
    /* connected() */
    /* connect() */
    /* write() */
    /* print() */
    /* println() */
    /* available() */
    /* read() */
    /* flush() */
    /* stop() */
    /* }; */

    /* void serial::print(int x)  */
    /* { */
    /*   if(confLogLev > 0)wLog("serial print",x,-1); */
    /*   sprintf(stemp,"%d",x); */
    /*   strcat(serialBuffer,stemp); */
    /*   showSerial(); */
    /*   passTime(); */
    /* } */

    //====================================
    // End of file
    //====================================