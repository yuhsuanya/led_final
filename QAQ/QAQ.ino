#define NOTE_D0 -1 
#define NOTE_D1 294 
#define NOTE_D2 330 
#define NOTE_D3 350 
#define NOTE_D4 393 
#define NOTE_D5 441 
#define NOTE_D6 495 
#define NOTE_D7 556 

#define NOTE_DL1 147 
#define NOTE_DL2 165 
#define NOTE_DL3 175 
#define NOTE_DL4 196 
#define NOTE_DL5 221 
#define NOTE_DL6 248 
#define NOTE_DL7 278 

#define NOTE_DH1 589 
#define NOTE_DH2 661 
#define NOTE_DH3 700 
#define NOTE_DH4 786 
#define NOTE_DH5 882 
#define NOTE_DH6 990 
#define NOTE_DH7 112  
//以上部分是定义是把每个音符和频率值对应起来，其实不用打这么多，但是都打上了，后面可以随意编写

#define WHOLE 1 
#define HALF 0.5 
#define QUARTER 0.25 
#define EIGHTH 0.25 
#define SIXTEENTH 0.625  
//这部分是用英文对应了拍子，这样后面也比较好看

//led////////////////////////////////////////////////////////////
const int buttonPin = 2;
int buttonState = 0;
int latchPin = 8;
int clockPin = 12;
int dataPin = 11;
byte colDataMatrix[8] = { 
  B01111111,
   B10111111,
   B11011111,
   B11101111,
   B11110111,
   B11111011,
   B11111101,
   B11111110
  };
                      
byte rowDataMatrix[8] = { B00011111,
    B01000010,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B01000010,
    B00111100
  };
byte rowDatabutton[8] = { 
  B00000000,
  B11111111,
  B00100100,
  B11111111,
  B01000010,
  B00111100,
  B11111111,
  B00000000
  };
// 定義顯示器顯示的時間 (延遲時間), 預設 1ms
int delay_time = 200;
/////////////////////////////////////////////////////////////////

int tune[] =  
{  
 NOTE_D0,NOTE_D0,NOTE_D0,NOTE_D6,NOTE_D7,NOTE_DH1,NOTE_D7,NOTE_DH1,NOTE_DH3,NOTE_D7,NOTE_D7,NOTE_D7,NOTE_D3,NOTE_D3,
 NOTE_D6,NOTE_D5,NOTE_D6,NOTE_DH1,NOTE_D5,NOTE_D5,NOTE_D5,NOTE_D3,NOTE_D4,NOTE_D3,NOTE_D4,NOTE_DH1,
 NOTE_D3,NOTE_D3,NOTE_D0,NOTE_DH1,NOTE_DH1,NOTE_DH1,NOTE_D7,NOTE_D4,NOTE_D4,NOTE_D7,NOTE_D7,NOTE_D7,NOTE_D0,NOTE_D6,NOTE_D7,
 NOTE_DH1,NOTE_D7,NOTE_DH1,NOTE_DH3,NOTE_D7,NOTE_D7,NOTE_D7,NOTE_D3,NOTE_D3,NOTE_D6,NOTE_D5,NOTE_D6,NOTE_DH1,
 NOTE_D5,NOTE_D5,NOTE_D5,NOTE_D2,NOTE_D3,NOTE_D4,NOTE_DH1,NOTE_D7,NOTE_D7,NOTE_DH1,NOTE_DH1,NOTE_DH2,NOTE_DH2,NOTE_DH3,NOTE_DH1,NOTE_DH1,NOTE_DH1,
 NOTE_DH1,NOTE_D7,NOTE_D6,NOTE_D6,NOTE_D7,NOTE_D5,NOTE_D6,NOTE_D6,NOTE_D6,NOTE_DH1,NOTE_DH2,NOTE_DH3,NOTE_DH2,NOTE_DH3,NOTE_DH5,
 NOTE_DH2,NOTE_DH2,NOTE_DH2,NOTE_D5,NOTE_D5,NOTE_DH1,NOTE_D7,NOTE_DH1,NOTE_DH3,NOTE_DH3,NOTE_DH3,NOTE_DH3,NOTE_DH3,
 NOTE_D6,NOTE_D7,NOTE_DH1,NOTE_D7,NOTE_DH2,NOTE_DH2,NOTE_DH1,NOTE_D5,NOTE_D5,NOTE_D5,NOTE_DH4,NOTE_DH3,NOTE_DH2,NOTE_DH1,
 NOTE_DH3,NOTE_DH3,NOTE_DH3,NOTE_DH3,NOTE_DH6,NOTE_DH6,NOTE_DH5,NOTE_DH5,NOTE_DH3,NOTE_DH2,NOTE_DH1,NOTE_DH1,NOTE_D0,NOTE_DH1,
 NOTE_DH2,NOTE_DH1,NOTE_DH2,NOTE_DH2,NOTE_DH5,NOTE_DH3,NOTE_DH3,NOTE_DH3,NOTE_DH3,NOTE_DH6,NOTE_DH6,NOTE_DH5,NOTE_DH5,
 NOTE_DH3,NOTE_DH2,NOTE_DH1,NOTE_DH1,NOTE_D0,NOTE_DH1,NOTE_DH2,NOTE_DH1,NOTE_DH2,NOTE_DH2,NOTE_D7,NOTE_D6,NOTE_D6,NOTE_D6,NOTE_D6,NOTE_D7
};//这部分就是整首曲子的音符部分，用了一个序列定义为tune，整数

float duration[]= 

{  
  1,1,1,0.5,0.5,     1+0.5,0.5,1,1,     1,1,1,0.5,0.5,
  1+0.5,0.5,1,1,     1,1,1,1,          1+0.5,0.5,1,1, 
  1,1,0.5,0.5,0.5,0.5,    1+0.5,0.5,1,1,     1,1,1,0.5,0.5,
  1+0.5,0.5,1,1,    1,1,1,0.5,0.5,     1+0.5,0.5,1,1,
  1,1,1,0.5,0.5,    1,0.5,0.25,0.25,0.25,0.5,    0.5,0.5,0.5,0.25,0.5,1,
  0.5,0.5,0.5,0.5,1,1,    1,1,1,0.5,0.5,    1+0.5,0.5,1,1,
  1,1,1,0.5,0.5,    1.5,0.5,1,1,    1,1,1,1,
  0.5,0.5,1,1,0.5,0.5,    1.5,0.25,0.5,1,    1,1,1,1,
  1,1,1,1,    1,1,1,1,    0.5,0.5,1,1,0.5,0.5,
  1,0.5,0.5,1,1,    1,1,1,1,    1,1,1,1,
  0.5,0.5,1,1,0.5,0.5,    1,0.5,0.25,0.5,1,    1,1,1,0.5,0.5
};//这部分是整首曲子的节拍部分，也定义个序列duration，浮点（数组的个数和前面音符的个数是一样的，一一对应么）

int length;//这里定义一个变量，后面用来表示共有多少个音符

int tonePin=5;//蜂鸣器的pin 


void setup() 

{  
  pinMode(tonePin,OUTPUT);//设置蜂鸣器的pin为输出模式

  length = sizeof(tune)/sizeof(tune[0]);//这里用了一个sizeof函数， 可以查出tone序列里有多少个音符

  //led/////////////////////////////////////////////////
  pinMode(buttonPin, INPUT);
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  //////////////////////////////////////////////////////

} 

void loop() 

{  

  for(int x=0;x<length;x++)//循环音符的次数
  {  
    tone(tonePin,tune[x]);//此函数依次播放tune序列里的数组，即每个 音符
//  buttonState = digitalRead(buttonPin);
    
     
     for(int i = 0; i < 8 ; i++){
       //byte colData = colDataMatrix[i];
      digitalWrite(latchPin,LOW);
          //pickDigit(i);
          shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
          shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix[i]);
          //shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
          digitalWrite(latchPin,HIGH);
          delay(delay_time);
      }

      
       delay(400*duration[x]);//每个音符持续的时间，即节拍duration，是调整时间的越大，曲子速度越慢，越小曲子速度越快，自己掌握吧
      
      noTone(tonePin);//停止当前音符，进入下一音符
  } 
  delay(5000);//等待5秒后，循环重新开始


  //led///////////////////////////////////////////////////


//  else{
//    for(int i = 0; i < 8 ; i++){
//  //byte colData = colDataMatrix[i];
//  digitalWrite(latchPin,LOW);
//    //  pickDigit(i);
//      shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
//      shiftOut(dataPin, clockPin, MSBFIRST, rowDatabutton[i]);
//      //shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
//      digitalWrite(latchPin,HIGH);
//      delay(delay_time);}
//    }
  //////////////////////////////////////////////////////////////////////////////
 }

void pickDigit(int x) {
  byte rowByte = 1 << x;
  shiftOut(dataPin, clockPin, MSBFIRST, rowByte);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////


