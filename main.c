/*
 * File:   main.c
 */

#include <xc.h>
#include "clcd.h"
#include "main.h"
#include "microoven.h"
#include "matrix_keypad.h"
#include "timers.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

unsigned char operational_flag = POWER_0N_SCREEN ;
unsigned char reset_flag = RESET_NOTHING ; 
extern unsigned char min, sec;

static void init_config(void) 
{
    //config CLCD
    init_clcd(); //port
    init_matrix_keypad();
    
    //configuring the fan
    FAN_DDR = 0;
    FAN = 0;
    
    //config buzzer
    BUZZER_DDR = 0; //config buzzer pin as output
    BUZZER = 0;
    
    //config timer
    init_timer2();
    PEIE = 1;
    GIE = 1;
    
    
}

void main(void) 
{
    unsigned char key;
    unsigned char start_mode = 0;
    init_config();

    while (1) 
    {
        key = read_matrix_keypad(STATE);
        //select the mode based on key pressed in the menu screen
        if(operational_flag == MENU_SCREEN){
            
            if(key == 1){
                clear_screen();
                start_mode = 0;
                operational_flag = MICRO_MODE ;
                clcd_print("Power = 900w", LINE2(0));
                __delay_ms(3000);
                clear_screen();
                reset_flag = RESET_MODE;
            }
            else if(key == 2){
                clear_screen();
                start_mode = 0;
                operational_flag = GRILL_MODE ;
                reset_flag = RESET_MODE;
            }
            else if(key == 3){
                clear_screen();
                start_mode = 0;
                operational_flag = CONVECTIONAL_MODE ;
                reset_flag = RESET_MODE;
            }
            else if(key == 4){
                clear_screen();
                operational_flag = START_MODE ;
                start_mode = 1;
                reset_flag = RESET_MODE;
            }
        }
        
        if(operational_flag == DISPLAY_TIME){
            if(key == 4){
                //increment cooking time by 30 seconds
                if(start_mode)
                {
                    sec = sec + 30;
                    if(sec > 59){
                        min ++;
                        sec -= 30;
                    }
                }
            }
            else if(key == 5){
                operational_flag = PAUSE;
            }
            else if(key == 6){
                operational_flag = STOP;
            }
            
        }
        else if(operational_flag == PAUSE){
            //resume the micro oven
            if(key == 4){
                FAN = 1;
                TMR2ON = 1;
                operational_flag = DISPLAY_TIME;
            }
            else if(key == 6){
                FAN = 0;
                TMR2ON  = 0;
                clear_screen();
                operational_flag = MENU_SCREEN;
            }
        }
       
        switch(operational_flag){
            case POWER_0N_SCREEN:
                //display power on screen
                power_on_screen();
                operational_flag = MENU_SCREEN; //switch to menu screen
                clear_screen(); //clear the CLCD
                break;
                                
            case MENU_SCREEN:
                display_menu_screen();
                break;
                
            case MICRO_MODE:
                //read key and based on key, set time
                set_time(key, reset_flag);
                
                //turn on microwave oven and display time
                break;
                
            case DISPLAY_TIME:
                display_time();
                break;
                
            case PAUSE:
                // stop micro oven and also the timer
                FAN = 0;
                TMR2ON = 0;
                break;
                
            case STOP:
                // stop micro oven and also the timer and back to menu screen
                FAN = 0;
                TMR2ON  = 0;
                clear_screen();
                operational_flag = MENU_SCREEN;
                break;
                
            case GRILL_MODE:
                set_time(key, reset_flag);
                break;
                
            case CONVECTIONAL_MODE:
                set_temp(key, reset_flag);
                break;
                
            case START_MODE:
                //display time with 30 sec as cooking time
                heat_food();
                break;
                                 
                
        }//closing switch
        reset_flag = RESET_NOTHING;
    }
    
}
