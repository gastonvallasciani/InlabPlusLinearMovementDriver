/* 
 * File:   MotorDriver.h
 * Author: Gast�n Vallasciani
 *
 * Created on May 26, 2017, 10:57 AM
 */

#ifndef MOTORDRIVER_H
#define	MOTORDRIVER_H

#include "mcc_generated_files/mcc.h"

struct{
    uint8_t Velocidad;
    uint8_t MicroStepNumber;
    uint8_t Direccion;
    uint16_t StepsNumber;
}StepperMotor;

/*Posibles parametros para setear la velocidad de movimiento del stepper motor. La velocidad nunca debe ser menor a 5
 * ya que se produciria perdida de pasos para el modo de trabajo en 8 microsteps. Para el modo 16 microsteps como minimo 
 * debe ser 2.
 revision 28-06-2017*/
/////////////////////////// 8 Micro Steps
#define FASTESTSPEED_8uSTEPS 6
#define FASTERSPEED_8uSTEPS 10
#define WORKINGSPEED_8uSTEPS 14
#define SLOWERSPEED_8uSTEPS 18
#define SLOWESTSPEED_8uSTEPS 25
////////////////////////// 16 Micro Steps
#define FASTESTSPEED_16uSTEPS 3
#define FASTERSPEED_16uSTEPS 4
#define WORKINGSPEED_16uSTEPS 6
#define SLOWERSPEED_16uSTEPS 10
#define SLOWESTSPEED_16uSTEPS 15
/*********************************************************************************************************************/
/*Posibles parametros para setear el MicroStepNumber. Este puede ser de 15 micropasos/paso u 8 micropasos/paso
 revision 27-06-2017*/
#define MICROSTEP16 16
#define MICROSTEP8 8
/*********************************************************************************************************************/
/*Posibles parametros para setear el StepsNumber. Establecen 1 revolucion para los dos modos de funcionamiento
 * 16 usetps per step o 8 usteps per step
 revision 27-06-2017*/
#define REVOLUTION_16uSTEPS 3200
#define REVOLUTION_8uSTEPS 1600
/*********************************************************************************************************************/ 

#define FORWARD 1
#define BACKWARD 0

#define YES 1
#define NO 0

// IN A
#define INA_OFF()         RC2_SetLow()     // IO_RC2_MOTOR2_PAP1_SetLow()
#define INA_ON()          RC2_SetHigh()    // IO_RC2_MOTOR2_PAP1_SetHigh()
// IN B
#define INB_OFF()         RD5_SetLow()     // IO_RD5_MOTOR2_PDIR1_SetLow()
#define INB_ON()          RD5_SetHigh()    // IO_RD5_MOTOR2_PDIR1_SetHigh()
// IN C
#define INC_OFF()         RC1_SetLow()     // IO_RC1_MOTOR2_PAP2_SetLow()
#define INC_ON()          RC1_SetHigh()    // IO_RC1_MOTOR2_PAP2_SetHigh()
// IN D
#define IND_OFF()         RC0_SetLow()     // IO_RC0_MOTOR2_PDIR2_SetLow()
#define IND_ON()          RC0_SetHigh()    // IO_RC0_MOTOR2_PDIR2_SetHigh()


void StateMEF_ini( void );    
/*
 * void StateMEF_ini( void )
 *  
 * Parametros: ninguno
 * Funciones que se deben llamar previamente: ninguna.
 * Descripcion: Inicializa la maquina de estados que controla los micropasos.
 * Ultima revision: 26-06-2017  
 * 
 */
uint8_t StepMove( uint16_t StepNumber, uint8_t Velocidad, uint8_t microstep_number, uint8_t direccion );
/*
 * uint8_t StepMove( uint16_t StepNumber, uint8_t Velocidad, uint8_t microstep_number, uint8_t direccion );
 * 
 * Parametros: StepNumber --> Numero de pasos a realizar.
 *             Velocidad --> Seteo de la frecuencia con que se ejecutaran los pasos.
 *             microstep_number --> Cantidad de micropasos entre pasos. Pueden ser 8 o 16.
 *                                   MICROSTEP16 
 *                                   MICROSTEP8
 *             direccion --> Setea el sentido de movimiento del motor.
 *                            FORWARD
 *                            BACKWARD
 * Funciones que se deben llamar previamente: StateMEF_ini()
 * Descripcion: Funcion utilizada para efectuar una serie de pasos especificada por el programador. Devuelve un 1 cuando se cumple la cantidad de pasos seteada.
 * Ejemplo de aplicacion:  
 * 
 *                         while(StepMove(2000, 10 , MICROSTEP16 , FORWARD)==NO);
 * 
 * Ultima revision: 26-06-2017    
 */
void Motor_Stop( void );
/*
 * void Motor_Stop( void );
 * 
 * Parametros: ninguno.               
 * Funciones que se deben llamar previamente: StateMEF_ini(),RectaAceleracion(),StepMove(),RectaFrenado().
 * Descripcion: Funcion utilizada para liberar el enclave del motor.
 * Ejemplo de aplicacion:  
 *                          struct{
 *                              uint8_t Velocidad;
 *                              uint8_t MicroStepNumber;
 *                              uint8_t Direccion;
 *                              uint16_t StepsNumber;
 *                          }StepperMotor;
 * 
 *                          StepperMotor.Velocidad = 10;
 *                          StepperMotor.StepsNumber = 2000;
 *                          StepperMotor.MicroStepNumber = MICROSTEP16;
 *                          StepperMotor.Direccion = FORWARD;
 *     
 *                          RectaAceleracion( StepperMotor.Velocidad , StepperMotor.MicroStepNumber , StepperMotor.Direccion );
 *                          while(StepMove(StepperMotor.StepsNumber, StepperMotor.Velocidad , StepperMotor.MicroStepNumber ,StepperMotor.Direccion)==NO);
 *                          RectaFrenado( StepperMotor.Velocidad , StepperMotor.MicroStepNumber , StepperMotor.Direccion);
 *                          Motor_Stop();
 * 
 * Ultima revision: 26-06-2017    
 */
void State8MEF_act( uint8_t direccion );
/*
 * void Motor_Stop( void );
 * 
 * Parametros: direccion --> Setea el sentido de movimiento del motor.
 *                            FORWARD
 *                            BACKWARD               
 * Funciones que se deben llamar previamente: StateMEF_ini().
 * Descripcion: Maquina de estados que actualiza el estado del paso actual. Funcion utilizada internamente en la funcion StepMove().
 * Ejemplo de aplicacion:  
 *
 * 
 * Ultima revision: 26-06-2017    
 */
void State16MEF_act( uint8_t direccion );
/*
 * void Motor_Stop( void );
 * 
 * Parametros: direccion --> Setea el sentido de movimiento del motor.
 *                            FORWARD
 *                            BACKWARD               
 * Funciones que se deben llamar previamente: StateMEF_ini().
 * Descripcion: Maquina de estados que actualiza el estado del paso actual. Funcion utilizada internamente en la funcion StepMove().
 * Ejemplo de aplicacion:  
 *
 * 
 * Ultima revision: 26-06-2017    
 */

void RectaAceleracion( uint8_t velocidad , uint8_t microstep_number, uint8_t direccion);
/*          
 * void RectaAceleracion( uint8_t velocidad , uint8_t microstep_number, uint8_t direccion);
 * 
 * Parametros: velocidad --> Seteo de la frecuencia con que se ejecutaran los pasos.
 *               microstep_number --> Cantidad de micropasos entre pasos. Pueden ser 8 o 16.
 *                                   MICROSTEP16 
 *                                   MICROSTEP8
 *               direccion --> Setea el sentido de movimiento del motor.
 *                            FORWARD
 *                            BACKWARD               
 * Funciones que se deben llamar previamente: StateMEF_ini().
 * Descripcion: Funcion para iniciar el movimiento del motor de forma suave.
 * Ejemplo de aplicacion:  
 *                          struct{
 *                              uint8_t Velocidad;
 *                              uint8_t MicroStepNumber;
 *                              uint8_t Direccion;
 *                              uint16_t StepsNumber;
 *                          }StepperMotor;
 *                              
 *                          StepperMotor.Velocidad = 10;
 *                          StepperMotor.StepsNumber = 2000;
 *                          StepperMotor.MicroStepNumber = MICROSTEP16;
 *                          StepperMotor.Direccion = FORWARD;
 *     
 *                          RectaAceleracion( StepperMotor.Velocidad , StepperMotor.MicroStepNumber , StepperMotor.Direccion );
 *
 *     Recta de Aceleraci�n
 *              --------------------       
 *      
 *              30  __________________________ Velocidad Inicial             
 *                |\          
 *     [*52useg]  | \          
                  |  \        
                  |   \       
                  |    \     
   Tiempo entre   |     \     
      pasos       |      \    
                  |_______\___________________ Velocidad Constante   (velocidad de movimiento del motor)   
                  |        
                  |____________________________
 *
 *                       N�mero de pasos
 *   Ultima revision: 26-06-2017  
 */
void RectaFrenado( uint8_t velocidad , uint8_t microstep_number, uint8_t direccion);
/*              
 * void RectaFrenado( uint8_t velocidad , uint8_t microstep_number, uint8_t direccion);
 * 
 * Parametros: velocidad --> Seteo de la frecuencia con que se ejecutaran los pasos.
 *               microstep_number --> Cantidad de micropasos entre pasos. Pueden ser 8 o 16.
 *                                   MICROSTEP16 
 *                                   MICROSTEP8
 *               direccion --> Setea el sentido de movimiento del motor.
 *                            FORWARD
 *                            BACKWARD               
 * Funciones que se deben llamar previamente: StateMEF_ini().
 * Descripcion: Funcion para frenar el movimiento del motor de forma suave.
 * Ejemplo de aplicacion:
 *                          struct{
 *                              uint8_t Velocidad;
 *                              uint8_t MicroStepNumber;
 *                              uint8_t Direccion;
 *                              uint16_t StepsNumber;
 *                          }StepperMotor;
 *                                
 *                          StepperMotor.Velocidad = 10;
 *                          StepperMotor.StepsNumber = 2000;
 *                          StepperMotor.MicroStepNumber = MICROSTEP16;
 *                          StepperMotor.Direccion = FORWARD;
 *     
 *                          RectaAceleracion( StepperMotor.Velocidad , StepperMotor.MicroStepNumber , StepperMotor.Direccion );
 *                          while(StepMove(StepperMotor.StepsNumber, StepperMotor.Velocidad , StepperMotor.MicroStepNumber ,StepperMotor.Direccion)==NO);
 *                          RectaFrenado( StepperMotor.Velocidad , StepperMotor.MicroStepNumber , StepperMotor.Direccion);
 * 
 * Recta de Frenado
 *              --------------------       
 *      
 *              30  __________________________ Velocidad Final             
 *                |       /|    
 *     [*52useg]  |      / |     
                  |     /  |   
                  |    /   |  
                  |   /    |
   Tiempo entre   |  /     |
      pasos       | /      |
                  |/_______|___________________ Velocidad de movimiento del motor (velocidad de frenado inicial) 
                  |        
                  |____________________________
 *                       N�mero de pasos
 *
 *  Ultima revision: 26-06-2017  
 */

uint8_t SwitchDirection( uint8_t actual_direction );
/*              
 * void SwitchDirection( uint8_t actual_direction );
 * 
 * Parametros: ninguno.
 * Funciones que se deben llamar previamente: ninguna.
 * Descripcion: Funcion para cambiar el sentido de movimiento del motor. 
 * Ejemplo de aplicacion:
 * 
 *                          #include "mcc_generated_files/mcc.h"
 *                          #include "MotorDriver.h"
 *                          
 *                          struct{
 *                              uint8_t Velocidad;
 *                              uint8_t MicroStepNumber;
 *                              uint8_t Direccion;
 *                              uint16_t StepsNumber;
 *                          }StepperMotor;
 *                                
 *                          StepperMotor.Velocidad = 10;
 *                          StepperMotor.StepsNumber = 2000;
 *                          StepperMotor.MicroStepNumber = MICROSTEP16;
 *                          StepperMotor.Direccion = FORWARD;
 *     
 *                          while(1){
 *                          RectaAceleracion( StepperMotor.Velocidad , StepperMotor.MicroStepNumber , StepperMotor.Direccion );
 *                          while(StepMove(StepperMotor.StepsNumber, StepperMotor.Velocidad , StepperMotor.MicroStepNumber ,StepperMotor.Direccion)==NO);
 *                          RectaFrenado( StepperMotor.Velocidad , StepperMotor.MicroStepNumber , StepperMotor.Direccion);
 *                          StepperMotor.Direccion = SwitchDirection( StepperMotor.Direccion ); // El motor cambia su sentido de giro a BACKWARD.
 *                          }
 * 
 *  Ultima revision: 28-06-2017  
 */


void DelayTmr2(unsigned uint16_t Timeout);

#define ms1_t 19            //Retardo de 1ms 
#define ms10_t 192          //Retardo de 10ms
#define ms100_t 1923        //Retardo de 100ms
#define s1_t 19230          //Retardo de 1s
/*
 * void Motor_Stop( void );
 * El timer 2 se interrumpe cada 52 us.
 * Parametros: Timeout --> Setea el valor inicial del contador que establece el retardo generado por la funcion DelatTmr2.
 *                            #define ms1_t 19            //Retardo de 1ms 
 *                            #define ms10_t 192          //Retardo de 10ms
 *                            #define ms100_t 1923        //Retardo de 100ms
 *                            #define s1_t 19230          //Retardo de 1s               
 * Funciones que se deben llamar previamente: ninguna.
 * Descripcion: Funcion que genera un retardo bloqueante.
 * Ejemplo de aplicacion:  
 *                              
 *                      DelayTmr2(s1_t);
 *
 * Ultima revision: 26-06-2017    
 */

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* MOTORDRIVER_H */

