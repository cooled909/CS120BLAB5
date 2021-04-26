/*	Author: Edward Segura
 *  Partner(s) Name: 
 *	Lab Section: 24
 *	Assignment: Lab 5  Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *  Demo Link: https://www.youtube.com/watch?v=SurwQ2DKfAE
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
    enum STATE_MACHINE {SM_Start, SM_Wait, SM_Hold, SM_1, SM_2, SM_3, SM_4, SM_5, SM_6} STATE;
    enum STATE_MACHINE LASTSTATE;
    unsigned char button0;
    unsigned char led = 0x00;
    void Tick_Cnt(){
    	switch(STATE){
    		case SM_Start:
    		LASTSTATE = SM_Start;
    		STATE = SM_Wait;
    		break;
    		case SM_Wait:
    		if((LASTSTATE == SM_6 && button0) || LASTSTATE == SM_Start){
    			STATE = SM_1;
    		}
    		else if(LASTSTATE == SM_1 && button0){
    			STATE = SM_2;
    		}
    		else if(LASTSTATE == SM_2 && button0){
    			STATE = SM_3;
    		}
    		else if(LASTSTATE == SM_3 && button0){
    			STATE = SM_4;
    		}
    		else if(LASTSTATE == SM_4 && button0){
    			STATE = SM_5;
    		}
    		else if(LASTSTATE == SM_5 && button0){
    			STATE = SM_6;
    		}
    		case SM_Hold:
    		if(!button0){
    			STATE = SM_Wait;
    		}
    		break;
    		case SM_1:
    		LASTSTATE = SM_1;
    		STATE = SM_Hold;
    		break;
    		case SM_2:
    		LASTSTATE = SM_2;
    		STATE = SM_Hold;
    		break;
    		case SM_3:
    		LASTSTATE = SM_3;
    		STATE = SM_Hold;
    		break;
    		case SM_4:
    		LASTSTATE = SM_4;
    		STATE = SM_Hold;
    		break;
    		case SM_5:
    		LASTSTATE = SM_5;
    		STATE = SM_Hold;
    		break;
    		case SM_6:
    		LASTSTATE = SM_6;
    		STATE = SM_Hold;
    		break;
    		default:
    		STATE = SM_Wait;
    		break;
    	}
    	switch(STATE){
    		case SM_Start:
    		break;
    		case SM_1:
    		led = 0x00;
    		break;
    		case SM_2:
    		led = 0x07;
    		break;
    		case SM_3:
    		led = 0x38;
    		break;
    		case SM_4:
    		led = 0x15;
    		break; 
    		case SM_5:
    		led = 0x2A;
    		break;
    		case SM_6:
    		led = 0x3F;
    		break;
    	}
    }
    led = 0x00;
    STATE = SM_Start;
    while (1) {
    	button0 = ~PINA & 0x01;
    	Tick_Cnt();
    	PORTC = led;
    }
    return 1;
}