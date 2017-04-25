/* 
 * File:   mod_servo.h
 * Author: Muutt
 *
 * Created on April 5, 2017, 9:31 AM
 */

#ifndef MOD_SERVO_H
#define	MOD_SERVO_H

//PROTOTYPES////////////////////////////////////////////////////////////////////
void Servo_Init(void);
void Drive(void);
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
#define PERIOD2 0xff  //63 corresponds to duty cycle ratio resolution of 256
#define DUTY_CYCLE_SET_POINT 512
////////////////////////////////////////////////////////////////////////////////

#endif	/* MOD_SERVO_H */
