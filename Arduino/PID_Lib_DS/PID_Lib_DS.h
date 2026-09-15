#ifndef PID_h
#define PID_h

class PID{
  public:
  PID();
  PID(float KI,float KD,float KP);
  void SetPID(float KI,float KD,float KP);
  void SetInput(float *Muestra);
  void GetTarget(float target);
  float Compute();
  private:
  float _KP,_KI,_KD,_target;
  float *_Muestra;
  long prevT;
  float eprev,eintegral;

};
#endif