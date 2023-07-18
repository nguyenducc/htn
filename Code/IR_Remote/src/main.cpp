#include <Arduino.h>
#include <IRremote.h>

//#define true 1 = high = den sang
//#define false 0 = low = den tat

// high = da bam nut bam
// low = chua bam nut bam


// Khai bao bien dieu khien nut bam continuous va single-shot
// Declare the conditions of continuous and single-shot nut consumption
const int continuousButtonPin = 6; // setup Continuous
const int singleButtonPin7 = 7; // setup single-shot
const int singleButtonPin8 = 8; // setup single-shot
const int irLedPin = 2;       // setup ir
IRsend irsend(irLedPin);

int continuousButtonState = HIGH;   // Trạng thái trước của nút bấm continuous
int singleButtonState7 = HIGH;   // Trạng thái trước của nút bấm single
int singleButtonState8 = HIGH;   // Trạng thái trước của nút bấm single

unsigned long continuousTime = 0;   // Thời gian nhấn nút bấm 1
unsigned long singleTime = 0;   // Thời gian nhấn nút bấm 2

const int carrierFrequency = 38000; // Tần số sóng mang là 38kHz

// Dãy mang cua command Word cua cac key no : 6,7,8
bool dataBits7[] = {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0};

bool dataBits8[] = {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0};

// Hằng số thời gian truyền mỗi bit
const unsigned long bitDuration =  1000000 / carrierFrequency;

// Hàm gửi một bit

void sendBit(bool bitValue) {
  if (bitValue) {
    //digitalWrite(irLedPin, LOW);
    noTone(irLedPin); // Dừng lại tín hiệu PWM
    delayMicroseconds(bitDuration * 3);
    //digitalWrite(irLedPin, HIGH);
    tone(irLedPin, carrierFrequency); // Gửi tín hiệu PWM ở tần số sóng mang
    delayMicroseconds(bitDuration);
  } else {
    //digitalWrite(irLedPin, LOW);
    noTone(irLedPin); // Dừng lại tín hiệu PWM
    delayMicroseconds(bitDuration);
    //digitalWrite(irLedPin, HIGH);
    tone(irLedPin, carrierFrequency); // Gửi tín hiệu PWM ở tần số sóng mang
    delayMicroseconds(bitDuration * 3);

  }
}

void sendBit(bool bitValue) {
  if (bitValue) {
    irsend.mark(bitDuration);
    irsend.space(bitDuration * 3);
  } else {
    irsend.mark(bitDuration);
    irsend.space(bitDuration);
    irsend.mark(bitDuration * 3);
  }
}

// Hàm gửi SINGLE-SHOT SIGNAL
void sendSingleShotSignal(bool dataBits[]) {
  // Gửi từng bit trong dãy
  for (int i = 0; i < 12; i++) {
    sendBit(dataBits[i]);
  }
}

// Hàm gửi CONTINUOUS SIGNAL
void sendContinuousSignal(int signalNumber) {
  // TODO: Thực hiện hành động khi gửi CONTINUOUS SIGNAL cho tín hiệu signalNumber
}

void setup() {
  Serial.begin(9600);
  pinMode(continuousButtonPin, INPUT_PULLUP);
  pinMode(singleButtonPin7, INPUT_PULLUP);
  pinMode(singleButtonPin8, INPUT_PULLUP);
  pinMode(irLedPin,OUTPUT);
}

void loop() {
  int currentContinuous = digitalRead(continuousButtonPin);
  int currentSingle7 = digitalRead(singleButtonPin7);

  int currentSingle8 = digitalRead(singleButtonPin8);

  // Ham gui tin hieu conyinuos khi du nut nhan lau :   
  if(currentContinuous != continuousButtonState){
      // Check xem thu trang thai cua nut nhan continous da hop ly hay chua : 
    if(currentContinuous == LOW){
        continuousTime = millis();
    }else{
        unsigned long continuousReleaseTime = millis();
        unsigned long continuousHoldTime = continuousTime - continuousReleaseTime;
        if(continuousHoldTime < 200){
          // Chua co du kien nao de xu ly
        }else{
          //  sendContinuousSignal(1);
        }
    }
  }

  // Ham gui tin hieu single shot khi nhan nut o day voi command Word la 7: 
  if(currentSingle7 != singleButtonState7){
    if(currentSingle7 == LOW){
      Serial.print("dung");
      //digitalWrite(irLedPin, HIGH);
      unsigned int rawData[] = {4500, 4500, 560, 1600, 560, 1600, 560, 1600, 560, 550, 560, 550, 560, 550, 560, 550, 560, 550, 560, 550, 560, 550, 560, 550, 560, 550, 560, 550, 560, 1600, 560, 1600, 560, 1600, 560};
      irsend.sendRaw(rawData, 12, 38);
      sendSingleShotSignal(dataBits7);
      sendSingleShotSignal(dataBits7);
    }else{
      //digitalWrite(irLedPin, LOW);
      noTone(irLedPin); // Dừng lại tín hiệu PWM
    }
  }

  // Ham gui tin hieu single shot khi nhan nut o day voi command Word la 8: 
  if(currentSingle8 != singleButtonState8){
    if(currentSingle8 == LOW){
      sendSingleShotSignal(dataBits8);
      sendSingleShotSignal(dataBits8);
    }else{
      noTone(irLedPin); // Dừng lại tín hiệu PWM   
    }
  }
  
  /*
  * Cap nhat trang thai truoc cua dau 6 va dau 7
  * Lay thong tin tu cac chan 6 va 7 cua vi dieu khien 
  */ 
  continuousButtonState = currentContinuous; 
  singleButtonState7 = currentSingle7;
  singleButtonState8 = currentSingle8;
    
  }