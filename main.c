/*
 * File:   main.c
 * Author: Muttsu
 *
 * Created on February 8, 2017, 5:49 PM
 * Main entry point with the main routine and ISR
 */

#include "config.h" //includes general configuration and declarations

char cycle = 0; //main routine semaphore

void main() {
    
    //Initiation process
    B_init();
    TMR3_init();
    ultrason_init();
    Mod_Correction_Init();
    Servo_Init();
    
    for(;;){
        if(cycle){
            
            ultrason();
         
            //Correction module main routine
            if(!PID1CONbits.BUSY)UpdateCorrection();
            StartPID();
            
            Drive();
            
            
            cycle = 0;
        }        
    }
}

void interrupt ISR(){
    //main routine timing (5ms)
    if(PIR5bits.TMR3IF){
        //main routine timing (5ms)
        cycle=1;
        
        TMR3H = TMR3H_INIT;
        TMR3L = TMR3L_INIT;
        PIR5bits.TMR3IF = 0;
    }
    
    //ultrasound routine timing
    static char etape = 0;
    static char pulse = 0;
    static char att_ult = 0;
    if(IOCIF)                           //interruption sur la broche RC3
    {
        if(!etape)                      //comencement de la prise du temps du pulse
        {
            TMR5ON = 1;
            etape++;
        }
        else if(etape)                  //fin de la prise du temps
        {
            TMR5ON = 0;
            mesure_ultrason_done = 1;   //annonce le début de l'analyse dans le main()-> Ultrason
            etape = 0;
        }
        
        IOCIF = 0;                      
        IOCCF3 = 0;
    }
    if(TMR3IF)                                                                  
    {
        if(attente_pulse && (++pulse == DELAI_10MSEC))       // attente de 10ms pour le pulse en début d'analyse de distance                   
        {
            TRIG = 0;                                                           
            lancer_mesure_ultrason = 1;                                         
            attente_pulse = 0;                                                  
            pulse = 0;                                                          
        }
        if(attente_ultrason && (++att_ult == DELAI_50MSEC))  //attente obligatoire pour le bon fonctionnement du capteur              
        {
            lancer_mesure_ultrason = 1;                                         
            attente_ultrason = 0;                                               
            att_ult = 0;                                                        
        }
        
        TMR3IF = 0;                                                             
        TMR3H = TMR3H_INIT;                                                     
        TMR3L = TMR3L_INIT;                                                     
    }
}