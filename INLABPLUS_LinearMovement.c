#include "mcc_generated_files/mcc.h"
#include "MotorDriver.h"
#include "INLABPLUS_LinearMovement.h"

/*
void goDark( void ){
    while(StepMove(100, WORKINGSPEED_16uSTEPS , 16 , FORWARD )==NO);
    StateMEF_ini();
}

void goReference( void ){
    while(StepMove(900, WORKINGSPEED_16uSTEPS , 16 , FORWARD )==NO);
    StateMEF_ini();
}

void goInitMovement( void ){
    while(StepMove(900, WORKINGSPEED_16uSTEPS , 16 , FORWARD )==NO);
    StateMEF_ini();
}

void Measure( void ){
    RectaAceleracion( WORKINGSPEED_16uSTEPS , 16 , FORWARD );
    while(StepMove((2*(REVOLUTION_16uSTEPS))+200, WORKINGSPEED_16uSTEPS , 16 , FORWARD )==NO);
    RectaFrenado( WORKINGSPEED_16uSTEPS , 16 , FORWARD);
    StateMEF_ini();
}
*/



void goDark( void ){
    while(StepMove(50, WORKINGSPEED_8uSTEPS , 8 , FORWARD )==NO);
    StateMEF_ini();
}

void goReference( void ){
    while(StepMove(450, WORKINGSPEED_8uSTEPS , 8 , FORWARD )==NO);
    StateMEF_ini();
}

void goInitMovement( void ){
    while(StepMove(450, WORKINGSPEED_8uSTEPS , 8 , FORWARD )==NO);
    StateMEF_ini();
}

void Measure( void ){
    RectaAceleracion( WORKINGSPEED_8uSTEPS , 8 , FORWARD );
    while(StepMove((2*(REVOLUTION_8uSTEPS))+100, WORKINGSPEED_8uSTEPS , 8 , FORWARD )==NO);
    RectaFrenado( WORKINGSPEED_8uSTEPS , 8 , FORWARD);
    StateMEF_ini();
}
 