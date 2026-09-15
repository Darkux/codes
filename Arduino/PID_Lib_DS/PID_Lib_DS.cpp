#include "arduino.h"
#include "PID_Lib_DS.h"

PID::PID(){}
PID::PID(float KI,float KD,float KP)
{
  SetPID(KI,KD,KP);
}
void PID::SetPID(float KI,float KD,float KP)
{
_KI = KI;
_KD = KD;
_KP = KP;
}

void PID::SetInput(float *Muestra)
{
 _Muestra = Muestra;
}

void PID::GetTarget(float target)
{
 _target = target;
}

float PID::Compute()
{
  Serial.println(_target);
  long currT = micros();
  float deltaT = ((float)(currT - prevT)) / (1.0e6);
  prevT = currT;
  float pos = 0;
  pos = *_Muestra;
  float e = pos - _target;
  float dedt = (e - eprev) / (deltaT);
  eintegral = eintegral + e * deltaT;
  float u = _KP * e + _KD * dedt + _KI * eintegral;
  eprev = e;
  return u;
}
