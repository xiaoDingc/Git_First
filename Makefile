# MPLAB IDE generated this makefile for use with GNU make.
# Project: xu_debug.mcp
# Date: Tue Jun 21 17:01:39 2011

AS = pic30-as.exe
CC = pic30-gcc.exe
LD = pic30-ld.exe
AR = pic30-ar.exe
HX = pic30-bin2hex.exe
RM = rm

xu_debug.hex : xu_debug.cof
	$(HX) "xu_debug.cof"

xu_debug.cof : main.o LED.o LCD_6448.o DS1302.o Ecan1.o Ecan2.o UART_232.o UART_485.o ADS7843.o e2prom.o time1.o interface.o flash.o DSPIC33F_sys.o character_c.o string_c.o
	$(CC) -mcpu=33FJ128GP708A "main.o" "LED.o" "LCD_6448.o" "DS1302.o" "Ecan1.o" "Ecan2.o" "UART_232.o" "UART_485.o" "ADS7843.o" "e2prom.o" "time1.o" "interface.o" "flash.o" "DSPIC33F_sys.o" "character_c.o" "string_c.o" -o"xu_debug.cof" -Wl,--script="gld\p33FJ128GP708A.gld",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD2=1,--defsym=__ICD2RAM=1,-Map="xu_debug.map",--report-mem

main.o : include/string_h.h include/character_h.h include/dspicExtern.h include/p33FJ128GP708A.h source/main.c
	$(CC) -mcpu=33FJ128GP708A -x c -c "source\main.c" -o"main.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

LED.o : include/string_h.h include/character_h.h include/dspicExtern.h include/p33FJ128GP708A.h source/LED.c
	$(CC) -mcpu=33FJ128GP708A -x c -c "source\LED.c" -o"LED.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

LCD_6448.o : include/string_h.h include/character_h.h include/dspicExtern.h include/p33FJ128GP708A.h source/LCD_6448.c
	$(CC) -mcpu=33FJ128GP708A -x c -c "source\LCD_6448.c" -o"LCD_6448.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

DS1302.o : include/string_h.h include/character_h.h include/dspicExtern.h include/p33FJ128GP708A.h source/DS1302.c
	$(CC) -mcpu=33FJ128GP708A -x c -c "source\DS1302.c" -o"DS1302.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

Ecan1.o : include/string_h.h include/character_h.h include/dspicExtern.h include/p33FJ128GP708A.h source/Ecan1.c
	$(CC) -mcpu=33FJ128GP708A -x c -c "source\Ecan1.c" -o"Ecan1.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

Ecan2.o : include/string_h.h include/character_h.h include/dspicExtern.h include/p33FJ128GP708A.h source/Ecan2.c
	$(CC) -mcpu=33FJ128GP708A -x c -c "source\Ecan2.c" -o"Ecan2.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

UART_232.o : include/string_h.h include/character_h.h include/dspicExtern.h include/p33FJ128GP708A.h source/UART_232.c
	$(CC) -mcpu=33FJ128GP708A -x c -c "source\UART_232.c" -o"UART_232.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

UART_485.o : include/string_h.h include/character_h.h include/dspicExtern.h include/p33FJ128GP708A.h source/UART_485.c
	$(CC) -mcpu=33FJ128GP708A -x c -c "source\UART_485.c" -o"UART_485.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

ADS7843.o : include/string_h.h include/character_h.h include/dspicExtern.h include/p33FJ128GP708A.h source/ADS7843.c
	$(CC) -mcpu=33FJ128GP708A -x c -c "source\ADS7843.c" -o"ADS7843.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

e2prom.o : include/string_h.h include/character_h.h include/dspicExtern.h include/p33FJ128GP708A.h source/e2prom.c
	$(CC) -mcpu=33FJ128GP708A -x c -c "source\e2prom.c" -o"e2prom.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

time1.o : include/string_h.h include/character_h.h include/dspicExtern.h include/p33FJ128GP708A.h source/time1.c
	$(CC) -mcpu=33FJ128GP708A -x c -c "source\time1.c" -o"time1.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

interface.o : include/string_h.h include/character_h.h include/dspicExtern.h include/p33FJ128GP708A.h source/interface.c
	$(CC) -mcpu=33FJ128GP708A -x c -c "source\interface.c" -o"interface.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

flash.o : include/string_h.h include/character_h.h include/dspicExtern.h include/p33FJ128GP708A.h source/flash.c
	$(CC) -mcpu=33FJ128GP708A -x c -c "source\flash.c" -o"flash.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

DSPIC33F_sys.o : include/string_h.h include/character_h.h include/dspicExtern.h include/p33FJ128GP708A.h source/DSPIC33F_sys.c
	$(CC) -mcpu=33FJ128GP708A -x c -c "source\DSPIC33F_sys.c" -o"DSPIC33F_sys.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

character_c.o : source/character_c.c
	$(CC) -mcpu=33FJ128GP708A -x c -c "source\character_c.c" -o"character_c.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

string_c.o : source/string_c.c
	$(CC) -mcpu=33FJ128GP708A -x c -c "source\string_c.c" -o"string_c.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

clean : 
	$(RM) "main.o" "LED.o" "LCD_6448.o" "DS1302.o" "Ecan1.o" "Ecan2.o" "UART_232.o" "UART_485.o" "ADS7843.o" "e2prom.o" "time1.o" "interface.o" "flash.o" "DSPIC33F_sys.o" "character_c.o" "string_c.o" "xu_debug.cof" "xu_debug.hex"

