#include "gs_pidctrl.h"
#include "gs_adc.h"
#include "tim.h"

pidctrl_t temppid1;
pidctrl_t temppid2;

void InitPidCtrl(pidctrl_t *instance)
{
	instance->kp=0.5;
	instance->ki=1.15;
	instance->kd=0.2;
	instance->expectvalue = 94;
	instance->lastpreverr = 0;
	instance->preverr = 0;
}
/*---------------------------------------------*/

float PidParamCalculate(pidctrl_t *instance,float temp)
{
	instance->actualvalue = temp;
	instance->err = instance->expectvalue - instance->actualvalue;	
	instance->increrr = instance->kp*(instance->err-instance->preverr) +                              //比例控制
	                    instance->ki*instance->preverr +                                              //积分控制
	                    instance->kd*(instance->err - 2*instance->preverr + instance->lastpreverr);   //微分控制
	
	
	instance->lastpreverr = instance->preverr;
	instance->preverr = instance->err;
	
	return (instance->increrr);
}

/*---------------------------------------------*/


