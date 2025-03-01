/* 
 * File:   main.h
 * Author: Invincible
 *
 * Created on February 22, 2025, 12:15 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#define POWER_0N_SCREEN         0x01
#define MENU_SCREEN             0x02
#define MICRO_MODE              0x11
#define GRILL_MODE              0x12
#define CONVECTIONAL_MODE       0x13
#define START_MODE              0x14


#define DISPLAY_TIME            0xD0

#define RESET_MODE              0xFF
#define RESET_NOTHING           0x00

#define FAN_DDR                 TRISC2
#define FAN                     RC2

#define BUZZER_DDR              TRISC1
#define BUZZER                  RC1

#define START                    0xAA
#define STOP                    0XBB
#define PAUSE                   0XCC


#endif	/* MAIN_H */

