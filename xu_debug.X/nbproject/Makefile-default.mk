#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/xu_debug.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/xu_debug.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../source/main.c ../source/LED.c ../source/Ecan1.c ../source/e2prom.c ../source/time1.c ../source/DSPIC33F_sys.c ../source/TEST_ALL.c ../source/fft.c ../source/magnitude.s ../source/init.c ../source/LCD_com.c ../source/character_c.c ../source/UART2_232.c ../source/UART1_232.c ../source/SMS.c ../source/AUTO_RUN.c ../source/modbus_fun.c ../source/RS485.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/812168374/main.o ${OBJECTDIR}/_ext/812168374/LED.o ${OBJECTDIR}/_ext/812168374/Ecan1.o ${OBJECTDIR}/_ext/812168374/e2prom.o ${OBJECTDIR}/_ext/812168374/time1.o ${OBJECTDIR}/_ext/812168374/DSPIC33F_sys.o ${OBJECTDIR}/_ext/812168374/TEST_ALL.o ${OBJECTDIR}/_ext/812168374/fft.o ${OBJECTDIR}/_ext/812168374/magnitude.o ${OBJECTDIR}/_ext/812168374/init.o ${OBJECTDIR}/_ext/812168374/LCD_com.o ${OBJECTDIR}/_ext/812168374/character_c.o ${OBJECTDIR}/_ext/812168374/UART2_232.o ${OBJECTDIR}/_ext/812168374/UART1_232.o ${OBJECTDIR}/_ext/812168374/SMS.o ${OBJECTDIR}/_ext/812168374/AUTO_RUN.o ${OBJECTDIR}/_ext/812168374/modbus_fun.o ${OBJECTDIR}/_ext/812168374/RS485.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/812168374/main.o.d ${OBJECTDIR}/_ext/812168374/LED.o.d ${OBJECTDIR}/_ext/812168374/Ecan1.o.d ${OBJECTDIR}/_ext/812168374/e2prom.o.d ${OBJECTDIR}/_ext/812168374/time1.o.d ${OBJECTDIR}/_ext/812168374/DSPIC33F_sys.o.d ${OBJECTDIR}/_ext/812168374/TEST_ALL.o.d ${OBJECTDIR}/_ext/812168374/fft.o.d ${OBJECTDIR}/_ext/812168374/magnitude.o.d ${OBJECTDIR}/_ext/812168374/init.o.d ${OBJECTDIR}/_ext/812168374/LCD_com.o.d ${OBJECTDIR}/_ext/812168374/character_c.o.d ${OBJECTDIR}/_ext/812168374/UART2_232.o.d ${OBJECTDIR}/_ext/812168374/UART1_232.o.d ${OBJECTDIR}/_ext/812168374/SMS.o.d ${OBJECTDIR}/_ext/812168374/AUTO_RUN.o.d ${OBJECTDIR}/_ext/812168374/modbus_fun.o.d ${OBJECTDIR}/_ext/812168374/RS485.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/812168374/main.o ${OBJECTDIR}/_ext/812168374/LED.o ${OBJECTDIR}/_ext/812168374/Ecan1.o ${OBJECTDIR}/_ext/812168374/e2prom.o ${OBJECTDIR}/_ext/812168374/time1.o ${OBJECTDIR}/_ext/812168374/DSPIC33F_sys.o ${OBJECTDIR}/_ext/812168374/TEST_ALL.o ${OBJECTDIR}/_ext/812168374/fft.o ${OBJECTDIR}/_ext/812168374/magnitude.o ${OBJECTDIR}/_ext/812168374/init.o ${OBJECTDIR}/_ext/812168374/LCD_com.o ${OBJECTDIR}/_ext/812168374/character_c.o ${OBJECTDIR}/_ext/812168374/UART2_232.o ${OBJECTDIR}/_ext/812168374/UART1_232.o ${OBJECTDIR}/_ext/812168374/SMS.o ${OBJECTDIR}/_ext/812168374/AUTO_RUN.o ${OBJECTDIR}/_ext/812168374/modbus_fun.o ${OBJECTDIR}/_ext/812168374/RS485.o

# Source Files
SOURCEFILES=../source/main.c ../source/LED.c ../source/Ecan1.c ../source/e2prom.c ../source/time1.c ../source/DSPIC33F_sys.c ../source/TEST_ALL.c ../source/fft.c ../source/magnitude.s ../source/init.c ../source/LCD_com.c ../source/character_c.c ../source/UART2_232.c ../source/UART1_232.c ../source/SMS.c ../source/AUTO_RUN.c ../source/modbus_fun.c ../source/RS485.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/xu_debug.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128GP708A
MP_LINKER_FILE_OPTION=,--script="..\gld\p33FJ128GP708A.gld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/812168374/magnitude.o: ../source/magnitude.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/magnitude.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/magnitude.o.ok ${OBJECTDIR}/_ext/812168374/magnitude.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/magnitude.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/magnitude.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_AS} $(MP_EXTRA_AS_PRE)  ../source/magnitude.s -o ${OBJECTDIR}/_ext/812168374/magnitude.o -omf=coff -p=$(MP_PROCESSOR_OPTION) --defsym=__MPLAB_BUILD=1 --defsym=__MPLAB_DEBUG=1 --defsym=__ICD2RAM=1 --defsym=__DEBUG=1 --defsym=__MPLAB_DEBUGGER_PK3=1 -g  -MD "${OBJECTDIR}/_ext/812168374/magnitude.o.d" -I".." -I"." -g$(MP_EXTRA_AS_POST)
	
else
${OBJECTDIR}/_ext/812168374/magnitude.o: ../source/magnitude.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/magnitude.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/magnitude.o.ok ${OBJECTDIR}/_ext/812168374/magnitude.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/magnitude.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/magnitude.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_AS} $(MP_EXTRA_AS_PRE)  ../source/magnitude.s -o ${OBJECTDIR}/_ext/812168374/magnitude.o -omf=coff -p=$(MP_PROCESSOR_OPTION) --defsym=__MPLAB_BUILD=1 -g  -MD "${OBJECTDIR}/_ext/812168374/magnitude.o.d" -I".." -I"." -g$(MP_EXTRA_AS_POST)
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/812168374/main.o: ../source/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/main.o.ok ${OBJECTDIR}/_ext/812168374/main.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/main.o.d" -o ${OBJECTDIR}/_ext/812168374/main.o ../source/main.c    
	
${OBJECTDIR}/_ext/812168374/LED.o: ../source/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/LED.o.ok ${OBJECTDIR}/_ext/812168374/LED.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/LED.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/LED.o.d" -o ${OBJECTDIR}/_ext/812168374/LED.o ../source/LED.c    
	
${OBJECTDIR}/_ext/812168374/Ecan1.o: ../source/Ecan1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/Ecan1.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/Ecan1.o.ok ${OBJECTDIR}/_ext/812168374/Ecan1.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/Ecan1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/Ecan1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/Ecan1.o.d" -o ${OBJECTDIR}/_ext/812168374/Ecan1.o ../source/Ecan1.c    
	
${OBJECTDIR}/_ext/812168374/e2prom.o: ../source/e2prom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/e2prom.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/e2prom.o.ok ${OBJECTDIR}/_ext/812168374/e2prom.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/e2prom.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/e2prom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/e2prom.o.d" -o ${OBJECTDIR}/_ext/812168374/e2prom.o ../source/e2prom.c    
	
${OBJECTDIR}/_ext/812168374/time1.o: ../source/time1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/time1.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/time1.o.ok ${OBJECTDIR}/_ext/812168374/time1.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/time1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/time1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/time1.o.d" -o ${OBJECTDIR}/_ext/812168374/time1.o ../source/time1.c    
	
${OBJECTDIR}/_ext/812168374/DSPIC33F_sys.o: ../source/DSPIC33F_sys.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/DSPIC33F_sys.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/DSPIC33F_sys.o.ok ${OBJECTDIR}/_ext/812168374/DSPIC33F_sys.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/DSPIC33F_sys.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/DSPIC33F_sys.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/DSPIC33F_sys.o.d" -o ${OBJECTDIR}/_ext/812168374/DSPIC33F_sys.o ../source/DSPIC33F_sys.c    
	
${OBJECTDIR}/_ext/812168374/TEST_ALL.o: ../source/TEST_ALL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/TEST_ALL.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/TEST_ALL.o.ok ${OBJECTDIR}/_ext/812168374/TEST_ALL.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/TEST_ALL.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/TEST_ALL.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/TEST_ALL.o.d" -o ${OBJECTDIR}/_ext/812168374/TEST_ALL.o ../source/TEST_ALL.c    
	
${OBJECTDIR}/_ext/812168374/fft.o: ../source/fft.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/fft.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/fft.o.ok ${OBJECTDIR}/_ext/812168374/fft.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/fft.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/fft.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/fft.o.d" -o ${OBJECTDIR}/_ext/812168374/fft.o ../source/fft.c    
	
${OBJECTDIR}/_ext/812168374/init.o: ../source/init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/init.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/init.o.ok ${OBJECTDIR}/_ext/812168374/init.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/init.o.d" -o ${OBJECTDIR}/_ext/812168374/init.o ../source/init.c    
	
${OBJECTDIR}/_ext/812168374/LCD_com.o: ../source/LCD_com.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/LCD_com.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/LCD_com.o.ok ${OBJECTDIR}/_ext/812168374/LCD_com.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/LCD_com.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/LCD_com.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/LCD_com.o.d" -o ${OBJECTDIR}/_ext/812168374/LCD_com.o ../source/LCD_com.c    
	
${OBJECTDIR}/_ext/812168374/character_c.o: ../source/character_c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/character_c.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/character_c.o.ok ${OBJECTDIR}/_ext/812168374/character_c.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/character_c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/character_c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/character_c.o.d" -o ${OBJECTDIR}/_ext/812168374/character_c.o ../source/character_c.c    
	
${OBJECTDIR}/_ext/812168374/UART2_232.o: ../source/UART2_232.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/UART2_232.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/UART2_232.o.ok ${OBJECTDIR}/_ext/812168374/UART2_232.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/UART2_232.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/UART2_232.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/UART2_232.o.d" -o ${OBJECTDIR}/_ext/812168374/UART2_232.o ../source/UART2_232.c    
	
${OBJECTDIR}/_ext/812168374/UART1_232.o: ../source/UART1_232.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/UART1_232.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/UART1_232.o.ok ${OBJECTDIR}/_ext/812168374/UART1_232.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/UART1_232.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/UART1_232.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/UART1_232.o.d" -o ${OBJECTDIR}/_ext/812168374/UART1_232.o ../source/UART1_232.c    
	
${OBJECTDIR}/_ext/812168374/SMS.o: ../source/SMS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/SMS.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/SMS.o.ok ${OBJECTDIR}/_ext/812168374/SMS.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/SMS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/SMS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/SMS.o.d" -o ${OBJECTDIR}/_ext/812168374/SMS.o ../source/SMS.c    
	
${OBJECTDIR}/_ext/812168374/AUTO_RUN.o: ../source/AUTO_RUN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/AUTO_RUN.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/AUTO_RUN.o.ok ${OBJECTDIR}/_ext/812168374/AUTO_RUN.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/AUTO_RUN.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/AUTO_RUN.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/AUTO_RUN.o.d" -o ${OBJECTDIR}/_ext/812168374/AUTO_RUN.o ../source/AUTO_RUN.c    
	
${OBJECTDIR}/_ext/812168374/modbus_fun.o: ../source/modbus_fun.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/modbus_fun.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/modbus_fun.o.ok ${OBJECTDIR}/_ext/812168374/modbus_fun.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/modbus_fun.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/modbus_fun.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/modbus_fun.o.d" -o ${OBJECTDIR}/_ext/812168374/modbus_fun.o ../source/modbus_fun.c    
	
${OBJECTDIR}/_ext/812168374/RS485.o: ../source/RS485.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/RS485.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/RS485.o.ok ${OBJECTDIR}/_ext/812168374/RS485.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/RS485.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/RS485.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/RS485.o.d" -o ${OBJECTDIR}/_ext/812168374/RS485.o ../source/RS485.c    
	
else
${OBJECTDIR}/_ext/812168374/main.o: ../source/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/main.o.ok ${OBJECTDIR}/_ext/812168374/main.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/main.o.d" -o ${OBJECTDIR}/_ext/812168374/main.o ../source/main.c    
	
${OBJECTDIR}/_ext/812168374/LED.o: ../source/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/LED.o.ok ${OBJECTDIR}/_ext/812168374/LED.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/LED.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/LED.o.d" -o ${OBJECTDIR}/_ext/812168374/LED.o ../source/LED.c    
	
${OBJECTDIR}/_ext/812168374/Ecan1.o: ../source/Ecan1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/Ecan1.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/Ecan1.o.ok ${OBJECTDIR}/_ext/812168374/Ecan1.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/Ecan1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/Ecan1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/Ecan1.o.d" -o ${OBJECTDIR}/_ext/812168374/Ecan1.o ../source/Ecan1.c    
	
${OBJECTDIR}/_ext/812168374/e2prom.o: ../source/e2prom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/e2prom.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/e2prom.o.ok ${OBJECTDIR}/_ext/812168374/e2prom.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/e2prom.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/e2prom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/e2prom.o.d" -o ${OBJECTDIR}/_ext/812168374/e2prom.o ../source/e2prom.c    
	
${OBJECTDIR}/_ext/812168374/time1.o: ../source/time1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/time1.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/time1.o.ok ${OBJECTDIR}/_ext/812168374/time1.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/time1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/time1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/time1.o.d" -o ${OBJECTDIR}/_ext/812168374/time1.o ../source/time1.c    
	
${OBJECTDIR}/_ext/812168374/DSPIC33F_sys.o: ../source/DSPIC33F_sys.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/DSPIC33F_sys.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/DSPIC33F_sys.o.ok ${OBJECTDIR}/_ext/812168374/DSPIC33F_sys.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/DSPIC33F_sys.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/DSPIC33F_sys.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/DSPIC33F_sys.o.d" -o ${OBJECTDIR}/_ext/812168374/DSPIC33F_sys.o ../source/DSPIC33F_sys.c    
	
${OBJECTDIR}/_ext/812168374/TEST_ALL.o: ../source/TEST_ALL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/TEST_ALL.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/TEST_ALL.o.ok ${OBJECTDIR}/_ext/812168374/TEST_ALL.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/TEST_ALL.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/TEST_ALL.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/TEST_ALL.o.d" -o ${OBJECTDIR}/_ext/812168374/TEST_ALL.o ../source/TEST_ALL.c    
	
${OBJECTDIR}/_ext/812168374/fft.o: ../source/fft.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/fft.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/fft.o.ok ${OBJECTDIR}/_ext/812168374/fft.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/fft.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/fft.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/fft.o.d" -o ${OBJECTDIR}/_ext/812168374/fft.o ../source/fft.c    
	
${OBJECTDIR}/_ext/812168374/init.o: ../source/init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/init.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/init.o.ok ${OBJECTDIR}/_ext/812168374/init.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/init.o.d" -o ${OBJECTDIR}/_ext/812168374/init.o ../source/init.c    
	
${OBJECTDIR}/_ext/812168374/LCD_com.o: ../source/LCD_com.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/LCD_com.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/LCD_com.o.ok ${OBJECTDIR}/_ext/812168374/LCD_com.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/LCD_com.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/LCD_com.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/LCD_com.o.d" -o ${OBJECTDIR}/_ext/812168374/LCD_com.o ../source/LCD_com.c    
	
${OBJECTDIR}/_ext/812168374/character_c.o: ../source/character_c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/character_c.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/character_c.o.ok ${OBJECTDIR}/_ext/812168374/character_c.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/character_c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/character_c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/character_c.o.d" -o ${OBJECTDIR}/_ext/812168374/character_c.o ../source/character_c.c    
	
${OBJECTDIR}/_ext/812168374/UART2_232.o: ../source/UART2_232.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/UART2_232.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/UART2_232.o.ok ${OBJECTDIR}/_ext/812168374/UART2_232.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/UART2_232.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/UART2_232.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/UART2_232.o.d" -o ${OBJECTDIR}/_ext/812168374/UART2_232.o ../source/UART2_232.c    
	
${OBJECTDIR}/_ext/812168374/UART1_232.o: ../source/UART1_232.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/UART1_232.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/UART1_232.o.ok ${OBJECTDIR}/_ext/812168374/UART1_232.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/UART1_232.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/UART1_232.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/UART1_232.o.d" -o ${OBJECTDIR}/_ext/812168374/UART1_232.o ../source/UART1_232.c    
	
${OBJECTDIR}/_ext/812168374/SMS.o: ../source/SMS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/SMS.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/SMS.o.ok ${OBJECTDIR}/_ext/812168374/SMS.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/SMS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/SMS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/SMS.o.d" -o ${OBJECTDIR}/_ext/812168374/SMS.o ../source/SMS.c    
	
${OBJECTDIR}/_ext/812168374/AUTO_RUN.o: ../source/AUTO_RUN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/AUTO_RUN.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/AUTO_RUN.o.ok ${OBJECTDIR}/_ext/812168374/AUTO_RUN.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/AUTO_RUN.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/AUTO_RUN.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/AUTO_RUN.o.d" -o ${OBJECTDIR}/_ext/812168374/AUTO_RUN.o ../source/AUTO_RUN.c    
	
${OBJECTDIR}/_ext/812168374/modbus_fun.o: ../source/modbus_fun.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/modbus_fun.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/modbus_fun.o.ok ${OBJECTDIR}/_ext/812168374/modbus_fun.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/modbus_fun.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/modbus_fun.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/modbus_fun.o.d" -o ${OBJECTDIR}/_ext/812168374/modbus_fun.o ../source/modbus_fun.c    
	
${OBJECTDIR}/_ext/812168374/RS485.o: ../source/RS485.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/812168374" 
	@${RM} ${OBJECTDIR}/_ext/812168374/RS485.o.d 
	@${RM} ${OBJECTDIR}/_ext/812168374/RS485.o.ok ${OBJECTDIR}/_ext/812168374/RS485.o.err 
	@${RM} ${OBJECTDIR}/_ext/812168374/RS485.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/812168374/RS485.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=coff -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../include" -I"." -mlarge-code -MMD -MF "${OBJECTDIR}/_ext/812168374/RS485.o.d" -o ${OBJECTDIR}/_ext/812168374/RS485.o ../source/RS485.c    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/xu_debug.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  D:/Mplab\ X\ \ IDE/lib/libc-coff.a D:/Mplab\ X\ \ IDE/lib/libdsp-coff.a D:/Mplab\ X\ \ IDE/lib/libpic30-coff.a D:/Mplab\ X\ \ IDE/lib/libm-coff.a D:/Mplab\ X\ \ IDE/lib/dsPIC33F/libp33FJ128GP708A-coff.a  ../gld/p33FJ128GP708A.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=coff -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/xu_debug.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}   "D:\Mplab X  IDE\lib\libc-coff.a" "D:\Mplab X  IDE\lib\libdsp-coff.a" "D:\Mplab X  IDE\lib\libpic30-coff.a" "D:\Mplab X  IDE\lib\libm-coff.a" "D:\Mplab X  IDE\lib\dsPIC33F\libp33FJ128GP708A-coff.a"      -Wl,--defsym=__MPLAB_BUILD=1,-L"../gld",-L".",-Map="${DISTDIR}/xu_debug.X.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/xu_debug.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  D:/Mplab\ X\ \ IDE/lib/libc-coff.a D:/Mplab\ X\ \ IDE/lib/libdsp-coff.a D:/Mplab\ X\ \ IDE/lib/libpic30-coff.a D:/Mplab\ X\ \ IDE/lib/libm-coff.a D:/Mplab\ X\ \ IDE/lib/dsPIC33F/libp33FJ128GP708A-coff.a ../gld/p33FJ128GP708A.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=coff -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/xu_debug.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}   "D:\Mplab X  IDE\lib\libc-coff.a" "D:\Mplab X  IDE\lib\libdsp-coff.a" "D:\Mplab X  IDE\lib\libpic30-coff.a" "D:\Mplab X  IDE\lib\libm-coff.a" "D:\Mplab X  IDE\lib\dsPIC33F\libp33FJ128GP708A-coff.a"      -Wl,--defsym=__MPLAB_BUILD=1,-L"../gld",-L".",-Map="${DISTDIR}/xu_debug.X.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/xu_debug.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -omf=coff
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
