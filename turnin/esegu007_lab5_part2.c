/*	Author: Edward Segura
 *  Partner(s) Name: 
 *	Lab Section: 24
 *	Assignment: Lab 5  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    enum STATE_MACHINE {SM_Start, SM_Wait, SM_Hold, SM_Inc, SM_Dec, SM_Clr} STATE;
    enum STATE_MACHINE LASTSTATE;
    unsigned char button0;
    unsigned char button1;
    unsigned char led;
    void Tick_Cnt(){
    	switch(STATE){
    		case SM_Start:
    		STATE = SM_Wait;
    		break;
    		case SM_Wait:
    		if(button0 && !button1){
    			STATE = SM_Inc;
    		}
    		else if(!button0 && button1){
    			STATE = SM_Dec;
    		}
    		else if(button0 && button1){
    			STATE = SM_Clr;
    		}
    		break;
    		case SM_Hold:
    		if(!button0 && !button1){
    			STATE = SM_Wait;
    		}
    		else if (LASTSTATE != SM_Inc && (button0 && !button1)){
    			STATE = SM_Inc;
    		}
    		else if (LASTSTATE != SM_Dec && (button1 && !button0)){
    			STATE = SM_Dec;
    		}
    		else if (LASTSTATE != SM_Clr && (button0 && button1)){
    			STATE = SM_Clr;
    		}
    		break;
    		case SM_Inc:
    		LASTSTATE = SM_Inc;
    		STATE = SM_Hold;
    		break;
    		case SM_Dec:
    		LASTSTATE = SM_Dec;
    		STATE = SM_Hold;
    		break;
    		case SM_Clr:
    		LASTSTATE = SM_Clr;
    		STATE = SM_Hold;
    		break;
    		default:
    		STATE = SM_Wait;
    		break;
    	}
    	switch(STATE){
    		case SM_Start:
    		led = 0x07;
    		break;
    		case SM_Inc:
    		if(led >= 0x09){
    			break;
    		}
    		led++;
    		break;
    		case SM_Dec:
    		if(led <= 0x00){
    			break;
    		}
    		led--;
    		break;
    		case SM_Clr:
    		led = 0x00;
    		break; 
    		default:
    		break;
    	}
    }
    led = 0x07;
    STATE = SM_Wait;
    while (1) {
    	button0 = ~PINA & 0x01;
    	button1 = ~PINA & 0x02;
    	Tick_Cnt();
    	PORTC = led;
    }
    return 1;
}