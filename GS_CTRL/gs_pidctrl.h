#ifndef  __GS_PIDCTRL_H
#define  __GS_PIDCTRL_H

typedef struct _pidctrl pidctrl_t;
struct _pidctrl{
	    float  expectvalue;
	    float  actualvalue;
			float  increrr;
	    float  err;
	    float  preverr;
	    float  lastpreverr;
	    float  kp,ki,kd;
};

extern pidctrl_t temppid1;
extern pidctrl_t temppid2;

void InitPidCtrl(pidctrl_t *instance);
float PidParamCalculate(pidctrl_t *instance,float temp);

#endif //
