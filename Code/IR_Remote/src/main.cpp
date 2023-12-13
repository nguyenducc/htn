#include <Arduino.h>
#include <IRremote.h>

// Khai bao bien dieu khien nut bam continuous va single-shot
// Declare the conditions of continuous and single-shot nut consumption
const int continuousButtonPin4 = 4; // setup Continuous
const int continuousButtonPin5 = 5; // setup Continuous
const int continuousButtonPin6 = 6; // setup Continuous
const int irLedPin = 2;             // setup ir
IRsend irsend(irLedPin);

int continuousButtonState4 = HIGH; // Trạng thái trước của nút bấm Continuous
int continuousButtonState5 = HIGH; // Trạng thái trước của nút bấm Continuous
int continuousButtonState6 = HIGH; // Trạng thái trước của nút bấm Continuous

unsigned long continuousTime = 0; // Thời gian nhấn nút bấm 1
unsigned long singleTime = 0;     // Thời gian nhấn nút bấm 2

const int carrierFrequency = 38000;   // Tần số sóng mang là 38kHz
const int maxSize = 23;               // Số phần tử tối đa của mảng rawData
unsigned int rawDataConvert[maxSize]; // Khai báo mảng rawData

// Dãy mang cua command Word cua cac key no : 6,7,8
// key1 : {1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0}
// key2 : {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0}
// key3 : {1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0}
// key4 : {1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0}
// key5 : {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0}

bool dataBits1[] = {1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0};

bool dataBits2[] = {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0};
bool dataBits4[] = {1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0}; //key 4

bool dataBits5[] = {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0}; //key 5

bool dataBits3[] = {1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0}; //key 3

// Hằng số thời gian truyền mỗi bit
const unsigned long bitDuration = 1000000 / carrierFrequency;

// Hàm gửi CONTINUOUS SIGNAL
void sendContinuousSignal(int signalNumber)
{
  // TODO: Thực hiện hành động khi gửi CONTINUOUS SIGNAL cho tín hiệu signalNumber
}

void convertData(bool dataBits[])
{
  for (int i = 0; i < 12; i++)
  {
    bool bitValue = dataBits[i];

    unsigned int *firstValue = &rawDataConvert[2 * i];
    unsigned int *secondValue = &rawDataConvert[2 * i + 1];

    if (i == 11)
    {
      if (bitValue)
      {
        *firstValue = 1260;
      }
      else
      {
        *firstValue = 420;
      }
    }
    else
    {
      if (bitValue)
      {
        Serial.println("dung");
        *firstValue = 1260;
        *secondValue = 420;
      }
      else
      {
        *firstValue = 420;
        *secondValue = 1260;
      }
    }
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(continuousButtonPin4, INPUT_PULLUP);
  pinMode(continuousButtonPin5, INPUT_PULLUP);
  pinMode(continuousButtonPin6, INPUT_PULLUP);
  pinMode(irLedPin, OUTPUT);
}

void loop()
{
  int currentContinuous4 = digitalRead(continuousButtonPin4);
  int currentContinuous5 = digitalRead(continuousButtonPin5);
  int currentContinuous6 = digitalRead(continuousButtonPin6);

  // Ham gui tin hieu continuos khi du nut nhan lau :
  if (currentContinuous4 != continuousButtonState4)
  {
    convertData(dataBits1);
    while (1)
    {
      // unsigned int rawData[] = {1300, 460, 420, 1360, 400, 1360, 1280, 440, 440, 1340, 400, 1360, 400, 1360, 400, 1340, 420, 1340, 1360, 400, 440, 1280,  440};
      irsend.sendRaw(rawDataConvert, 24, 38);
      delay(32);
      irsend.sendRaw(rawDataConvert, 24, 38);
      if (digitalRead(continuousButtonPin4) == HIGH)
      {
        break;
      }
      delayMicroseconds(420 * 208);
      if (digitalRead(continuousButtonPin4) == HIGH)
      {
        irsend.sendRaw(rawDataConvert, 24, 38);
        delay(32);
        irsend.sendRaw(rawDataConvert, 24, 38);
        break;
      }
    }
  }

  if (currentContinuous5 != continuousButtonState5)
  {
    convertData(dataBits1);
    while (1)
    {
      // unsigned int rawData[] = {1300, 460, 420, 1360, 400, 1360, 1280, 440, 440, 1340, 400, 1360, 400, 1360, 400, 1340, 420, 1340, 1360, 400, 440, 1280,  440};
      irsend.sendRaw(rawDataConvert, 24, 38);
      delay(32);
      irsend.sendRaw(rawDataConvert, 24, 38);
      if (digitalRead(continuousButtonPin5) == HIGH)
      {
        break;
      }
      delayMicroseconds(420 * 208);
      if (digitalRead(continuousButtonPin5) == HIGH)
      {
        irsend.sendRaw(rawDataConvert, 24, 38);
        delay(32);
        irsend.sendRaw(rawDataConvert, 24, 38);
        break;
      }
    }
  }

  if (currentContinuous6 != continuousButtonState6)
  {
    convertData(dataBits2);
    while (1)
    {
      // unsigned int rawData[] = {1300, 460, 420, 1360, 400, 1360, 1280, 440, 440, 1340, 400, 1360, 400, 1360, 400, 1340, 420, 1340, 1360, 400, 440, 1280,  440};
      irsend.sendRaw(rawDataConvert, 24, 38);
      delay(32);
      irsend.sendRaw(rawDataConvert, 24, 38);
      if (digitalRead(continuousButtonPin6) == HIGH)
      {
        break;
      }
      delayMindRaw(rawDataConvert, 24, 38);
        delay(32);
        irsend.sendRaw(rawDataConvert, 24, 38);
        break;
      }
    }
  }

  /*
   * Cap nhat trang thai truoc cua dau 6 va dau 7
   * Lay thong tin tu cac chan 6 va 7 cua vi dieu khien
   */
  continuousButtonState4 = currentContinuous4;
  continuousButtonState5 = currentContinuous5;
  continuousButtonState6 = currentContinuous6;
}
