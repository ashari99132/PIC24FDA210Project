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
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/OMB_CLS_build13.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/OMB_CLS_build13.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../RH_Control.c ../TempControl.c ../AC_Hz.c ../AlarmContactRelay.c ../CO2_Control.c ../EventRTC.c ../EventScheduler.c ../EventTCPIP.c ../FailSafeRelay.c ../O2_Control.c ../OMB_Mode.c ../RTC_S35390.c ../OMB_Output.c ../EventBuzzer.c ../OMBLTC2439_Inputs.c ../OMB_UTI_Comm.c ../O2_RS485.c ../OMB_DigitalInputs.c ../USB.c ../Event_UV.c ../EEPROM_24AA1025.c ../CO2_RS485.c ../OMB_AnalogOutput.c ../p24FJ256DA210_UART2.c ../p24FJ256DA210_UART1.c ../p24FJ256DA210_Timer1.c ../p24FJ256DA210_I2C3.c ../p24FJ256DA210_SPI1.c ../LTC2439.c ../p24FJ256DA210_I2C1.c ../p24FJ256DA210_ICN.c ../p24FJ256DA210_OCx.c ../p24FJ256DA210_Timer3.c ../Flash.c "../Microchip/TCPIP Stack/ENC28J60.c" "../Microchip/TCPIP Stack/Delay.c" "../Microchip/TCPIP Stack/StackTsk.c" "../Microchip/TCPIP Stack/Helpers.c" "../Microchip/TCPIP Stack/Announce.c" "../Microchip/TCPIP Stack/UDP.c" "../Microchip/TCPIP Stack/ARP.c" "../Microchip/TCPIP Stack/DHCP.c" "../Microchip/TCPIP Stack/Tick.c" "../Microchip/TCPIP Stack/IP.c" "../Microchip/TCPIP Stack/ICMP.c" "../Microchip/TCPIP Stack/TCP.c" ../main.c ../General.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/RH_Control.o ${OBJECTDIR}/_ext/1472/TempControl.o ${OBJECTDIR}/_ext/1472/AC_Hz.o ${OBJECTDIR}/_ext/1472/AlarmContactRelay.o ${OBJECTDIR}/_ext/1472/CO2_Control.o ${OBJECTDIR}/_ext/1472/EventRTC.o ${OBJECTDIR}/_ext/1472/EventScheduler.o ${OBJECTDIR}/_ext/1472/EventTCPIP.o ${OBJECTDIR}/_ext/1472/FailSafeRelay.o ${OBJECTDIR}/_ext/1472/O2_Control.o ${OBJECTDIR}/_ext/1472/OMB_Mode.o ${OBJECTDIR}/_ext/1472/RTC_S35390.o ${OBJECTDIR}/_ext/1472/OMB_Output.o ${OBJECTDIR}/_ext/1472/EventBuzzer.o ${OBJECTDIR}/_ext/1472/OMBLTC2439_Inputs.o ${OBJECTDIR}/_ext/1472/OMB_UTI_Comm.o ${OBJECTDIR}/_ext/1472/O2_RS485.o ${OBJECTDIR}/_ext/1472/OMB_DigitalInputs.o ${OBJECTDIR}/_ext/1472/USB.o ${OBJECTDIR}/_ext/1472/Event_UV.o ${OBJECTDIR}/_ext/1472/EEPROM_24AA1025.o ${OBJECTDIR}/_ext/1472/CO2_RS485.o ${OBJECTDIR}/_ext/1472/OMB_AnalogOutput.o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART2.o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART1.o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer1.o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C3.o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_SPI1.o ${OBJECTDIR}/_ext/1472/LTC2439.o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C1.o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_ICN.o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_OCx.o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer3.o ${OBJECTDIR}/_ext/1472/Flash.o ${OBJECTDIR}/_ext/867694782/ENC28J60.o ${OBJECTDIR}/_ext/867694782/Delay.o ${OBJECTDIR}/_ext/867694782/StackTsk.o ${OBJECTDIR}/_ext/867694782/Helpers.o ${OBJECTDIR}/_ext/867694782/Announce.o ${OBJECTDIR}/_ext/867694782/UDP.o ${OBJECTDIR}/_ext/867694782/ARP.o ${OBJECTDIR}/_ext/867694782/DHCP.o ${OBJECTDIR}/_ext/867694782/Tick.o ${OBJECTDIR}/_ext/867694782/IP.o ${OBJECTDIR}/_ext/867694782/ICMP.o ${OBJECTDIR}/_ext/867694782/TCP.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/General.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/RH_Control.o.d ${OBJECTDIR}/_ext/1472/TempControl.o.d ${OBJECTDIR}/_ext/1472/AC_Hz.o.d ${OBJECTDIR}/_ext/1472/AlarmContactRelay.o.d ${OBJECTDIR}/_ext/1472/CO2_Control.o.d ${OBJECTDIR}/_ext/1472/EventRTC.o.d ${OBJECTDIR}/_ext/1472/EventScheduler.o.d ${OBJECTDIR}/_ext/1472/EventTCPIP.o.d ${OBJECTDIR}/_ext/1472/FailSafeRelay.o.d ${OBJECTDIR}/_ext/1472/O2_Control.o.d ${OBJECTDIR}/_ext/1472/OMB_Mode.o.d ${OBJECTDIR}/_ext/1472/RTC_S35390.o.d ${OBJECTDIR}/_ext/1472/OMB_Output.o.d ${OBJECTDIR}/_ext/1472/EventBuzzer.o.d ${OBJECTDIR}/_ext/1472/OMBLTC2439_Inputs.o.d ${OBJECTDIR}/_ext/1472/OMB_UTI_Comm.o.d ${OBJECTDIR}/_ext/1472/O2_RS485.o.d ${OBJECTDIR}/_ext/1472/OMB_DigitalInputs.o.d ${OBJECTDIR}/_ext/1472/USB.o.d ${OBJECTDIR}/_ext/1472/Event_UV.o.d ${OBJECTDIR}/_ext/1472/EEPROM_24AA1025.o.d ${OBJECTDIR}/_ext/1472/CO2_RS485.o.d ${OBJECTDIR}/_ext/1472/OMB_AnalogOutput.o.d ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART2.o.d ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART1.o.d ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer1.o.d ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C3.o.d ${OBJECTDIR}/_ext/1472/p24FJ256DA210_SPI1.o.d ${OBJECTDIR}/_ext/1472/LTC2439.o.d ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C1.o.d ${OBJECTDIR}/_ext/1472/p24FJ256DA210_ICN.o.d ${OBJECTDIR}/_ext/1472/p24FJ256DA210_OCx.o.d ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer3.o.d ${OBJECTDIR}/_ext/1472/Flash.o.d ${OBJECTDIR}/_ext/867694782/ENC28J60.o.d ${OBJECTDIR}/_ext/867694782/Delay.o.d ${OBJECTDIR}/_ext/867694782/StackTsk.o.d ${OBJECTDIR}/_ext/867694782/Helpers.o.d ${OBJECTDIR}/_ext/867694782/Announce.o.d ${OBJECTDIR}/_ext/867694782/UDP.o.d ${OBJECTDIR}/_ext/867694782/ARP.o.d ${OBJECTDIR}/_ext/867694782/DHCP.o.d ${OBJECTDIR}/_ext/867694782/Tick.o.d ${OBJECTDIR}/_ext/867694782/IP.o.d ${OBJECTDIR}/_ext/867694782/ICMP.o.d ${OBJECTDIR}/_ext/867694782/TCP.o.d ${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/1472/General.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/RH_Control.o ${OBJECTDIR}/_ext/1472/TempControl.o ${OBJECTDIR}/_ext/1472/AC_Hz.o ${OBJECTDIR}/_ext/1472/AlarmContactRelay.o ${OBJECTDIR}/_ext/1472/CO2_Control.o ${OBJECTDIR}/_ext/1472/EventRTC.o ${OBJECTDIR}/_ext/1472/EventScheduler.o ${OBJECTDIR}/_ext/1472/EventTCPIP.o ${OBJECTDIR}/_ext/1472/FailSafeRelay.o ${OBJECTDIR}/_ext/1472/O2_Control.o ${OBJECTDIR}/_ext/1472/OMB_Mode.o ${OBJECTDIR}/_ext/1472/RTC_S35390.o ${OBJECTDIR}/_ext/1472/OMB_Output.o ${OBJECTDIR}/_ext/1472/EventBuzzer.o ${OBJECTDIR}/_ext/1472/OMBLTC2439_Inputs.o ${OBJECTDIR}/_ext/1472/OMB_UTI_Comm.o ${OBJECTDIR}/_ext/1472/O2_RS485.o ${OBJECTDIR}/_ext/1472/OMB_DigitalInputs.o ${OBJECTDIR}/_ext/1472/USB.o ${OBJECTDIR}/_ext/1472/Event_UV.o ${OBJECTDIR}/_ext/1472/EEPROM_24AA1025.o ${OBJECTDIR}/_ext/1472/CO2_RS485.o ${OBJECTDIR}/_ext/1472/OMB_AnalogOutput.o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART2.o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART1.o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer1.o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C3.o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_SPI1.o ${OBJECTDIR}/_ext/1472/LTC2439.o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C1.o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_ICN.o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_OCx.o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer3.o ${OBJECTDIR}/_ext/1472/Flash.o ${OBJECTDIR}/_ext/867694782/ENC28J60.o ${OBJECTDIR}/_ext/867694782/Delay.o ${OBJECTDIR}/_ext/867694782/StackTsk.o ${OBJECTDIR}/_ext/867694782/Helpers.o ${OBJECTDIR}/_ext/867694782/Announce.o ${OBJECTDIR}/_ext/867694782/UDP.o ${OBJECTDIR}/_ext/867694782/ARP.o ${OBJECTDIR}/_ext/867694782/DHCP.o ${OBJECTDIR}/_ext/867694782/Tick.o ${OBJECTDIR}/_ext/867694782/IP.o ${OBJECTDIR}/_ext/867694782/ICMP.o ${OBJECTDIR}/_ext/867694782/TCP.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/General.o

# Source Files
SOURCEFILES=../RH_Control.c ../TempControl.c ../AC_Hz.c ../AlarmContactRelay.c ../CO2_Control.c ../EventRTC.c ../EventScheduler.c ../EventTCPIP.c ../FailSafeRelay.c ../O2_Control.c ../OMB_Mode.c ../RTC_S35390.c ../OMB_Output.c ../EventBuzzer.c ../OMBLTC2439_Inputs.c ../OMB_UTI_Comm.c ../O2_RS485.c ../OMB_DigitalInputs.c ../USB.c ../Event_UV.c ../EEPROM_24AA1025.c ../CO2_RS485.c ../OMB_AnalogOutput.c ../p24FJ256DA210_UART2.c ../p24FJ256DA210_UART1.c ../p24FJ256DA210_Timer1.c ../p24FJ256DA210_I2C3.c ../p24FJ256DA210_SPI1.c ../LTC2439.c ../p24FJ256DA210_I2C1.c ../p24FJ256DA210_ICN.c ../p24FJ256DA210_OCx.c ../p24FJ256DA210_Timer3.c ../Flash.c ../Microchip/TCPIP Stack/ENC28J60.c ../Microchip/TCPIP Stack/Delay.c ../Microchip/TCPIP Stack/StackTsk.c ../Microchip/TCPIP Stack/Helpers.c ../Microchip/TCPIP Stack/Announce.c ../Microchip/TCPIP Stack/UDP.c ../Microchip/TCPIP Stack/ARP.c ../Microchip/TCPIP Stack/DHCP.c ../Microchip/TCPIP Stack/Tick.c ../Microchip/TCPIP Stack/IP.c ../Microchip/TCPIP Stack/ICMP.c ../Microchip/TCPIP Stack/TCP.c ../main.c ../General.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/OMB_CLS_build13.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ256DA210
MP_LINKER_FILE_OPTION=,-Tp24FJ256DA210.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/RH_Control.o: ../RH_Control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/RH_Control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/RH_Control.o.ok ${OBJECTDIR}/_ext/1472/RH_Control.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/RH_Control.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/RH_Control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/RH_Control.o.d" -o ${OBJECTDIR}/_ext/1472/RH_Control.o ../RH_Control.c    
	
${OBJECTDIR}/_ext/1472/TempControl.o: ../TempControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/TempControl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/TempControl.o.ok ${OBJECTDIR}/_ext/1472/TempControl.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/TempControl.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/TempControl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/TempControl.o.d" -o ${OBJECTDIR}/_ext/1472/TempControl.o ../TempControl.c    
	
${OBJECTDIR}/_ext/1472/AC_Hz.o: ../AC_Hz.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/AC_Hz.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/AC_Hz.o.ok ${OBJECTDIR}/_ext/1472/AC_Hz.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/AC_Hz.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/AC_Hz.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/AC_Hz.o.d" -o ${OBJECTDIR}/_ext/1472/AC_Hz.o ../AC_Hz.c    
	
${OBJECTDIR}/_ext/1472/AlarmContactRelay.o: ../AlarmContactRelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/AlarmContactRelay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/AlarmContactRelay.o.ok ${OBJECTDIR}/_ext/1472/AlarmContactRelay.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/AlarmContactRelay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/AlarmContactRelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/AlarmContactRelay.o.d" -o ${OBJECTDIR}/_ext/1472/AlarmContactRelay.o ../AlarmContactRelay.c    
	
${OBJECTDIR}/_ext/1472/CO2_Control.o: ../CO2_Control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/CO2_Control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CO2_Control.o.ok ${OBJECTDIR}/_ext/1472/CO2_Control.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/CO2_Control.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/CO2_Control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/CO2_Control.o.d" -o ${OBJECTDIR}/_ext/1472/CO2_Control.o ../CO2_Control.c    
	
${OBJECTDIR}/_ext/1472/EventRTC.o: ../EventRTC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/EventRTC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/EventRTC.o.ok ${OBJECTDIR}/_ext/1472/EventRTC.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/EventRTC.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/EventRTC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/EventRTC.o.d" -o ${OBJECTDIR}/_ext/1472/EventRTC.o ../EventRTC.c    
	
${OBJECTDIR}/_ext/1472/EventScheduler.o: ../EventScheduler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/EventScheduler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/EventScheduler.o.ok ${OBJECTDIR}/_ext/1472/EventScheduler.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/EventScheduler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/EventScheduler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/EventScheduler.o.d" -o ${OBJECTDIR}/_ext/1472/EventScheduler.o ../EventScheduler.c    
	
${OBJECTDIR}/_ext/1472/EventTCPIP.o: ../EventTCPIP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/EventTCPIP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/EventTCPIP.o.ok ${OBJECTDIR}/_ext/1472/EventTCPIP.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/EventTCPIP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/EventTCPIP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/EventTCPIP.o.d" -o ${OBJECTDIR}/_ext/1472/EventTCPIP.o ../EventTCPIP.c    
	
${OBJECTDIR}/_ext/1472/FailSafeRelay.o: ../FailSafeRelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/FailSafeRelay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/FailSafeRelay.o.ok ${OBJECTDIR}/_ext/1472/FailSafeRelay.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/FailSafeRelay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/FailSafeRelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/FailSafeRelay.o.d" -o ${OBJECTDIR}/_ext/1472/FailSafeRelay.o ../FailSafeRelay.c    
	
${OBJECTDIR}/_ext/1472/O2_Control.o: ../O2_Control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/O2_Control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/O2_Control.o.ok ${OBJECTDIR}/_ext/1472/O2_Control.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/O2_Control.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/O2_Control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/O2_Control.o.d" -o ${OBJECTDIR}/_ext/1472/O2_Control.o ../O2_Control.c    
	
${OBJECTDIR}/_ext/1472/OMB_Mode.o: ../OMB_Mode.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_Mode.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_Mode.o.ok ${OBJECTDIR}/_ext/1472/OMB_Mode.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_Mode.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/OMB_Mode.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/OMB_Mode.o.d" -o ${OBJECTDIR}/_ext/1472/OMB_Mode.o ../OMB_Mode.c    
	
${OBJECTDIR}/_ext/1472/RTC_S35390.o: ../RTC_S35390.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/RTC_S35390.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/RTC_S35390.o.ok ${OBJECTDIR}/_ext/1472/RTC_S35390.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/RTC_S35390.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/RTC_S35390.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/RTC_S35390.o.d" -o ${OBJECTDIR}/_ext/1472/RTC_S35390.o ../RTC_S35390.c    
	
${OBJECTDIR}/_ext/1472/OMB_Output.o: ../OMB_Output.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_Output.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_Output.o.ok ${OBJECTDIR}/_ext/1472/OMB_Output.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_Output.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/OMB_Output.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/OMB_Output.o.d" -o ${OBJECTDIR}/_ext/1472/OMB_Output.o ../OMB_Output.c    
	
${OBJECTDIR}/_ext/1472/EventBuzzer.o: ../EventBuzzer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/EventBuzzer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/EventBuzzer.o.ok ${OBJECTDIR}/_ext/1472/EventBuzzer.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/EventBuzzer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/EventBuzzer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/EventBuzzer.o.d" -o ${OBJECTDIR}/_ext/1472/EventBuzzer.o ../EventBuzzer.c    
	
${OBJECTDIR}/_ext/1472/OMBLTC2439_Inputs.o: ../OMBLTC2439_Inputs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/OMBLTC2439_Inputs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/OMBLTC2439_Inputs.o.ok ${OBJECTDIR}/_ext/1472/OMBLTC2439_Inputs.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/OMBLTC2439_Inputs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/OMBLTC2439_Inputs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/OMBLTC2439_Inputs.o.d" -o ${OBJECTDIR}/_ext/1472/OMBLTC2439_Inputs.o ../OMBLTC2439_Inputs.c    
	
${OBJECTDIR}/_ext/1472/OMB_UTI_Comm.o: ../OMB_UTI_Comm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_UTI_Comm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_UTI_Comm.o.ok ${OBJECTDIR}/_ext/1472/OMB_UTI_Comm.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_UTI_Comm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/OMB_UTI_Comm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/OMB_UTI_Comm.o.d" -o ${OBJECTDIR}/_ext/1472/OMB_UTI_Comm.o ../OMB_UTI_Comm.c    
	
${OBJECTDIR}/_ext/1472/O2_RS485.o: ../O2_RS485.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/O2_RS485.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/O2_RS485.o.ok ${OBJECTDIR}/_ext/1472/O2_RS485.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/O2_RS485.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/O2_RS485.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/O2_RS485.o.d" -o ${OBJECTDIR}/_ext/1472/O2_RS485.o ../O2_RS485.c    
	
${OBJECTDIR}/_ext/1472/OMB_DigitalInputs.o: ../OMB_DigitalInputs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_DigitalInputs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_DigitalInputs.o.ok ${OBJECTDIR}/_ext/1472/OMB_DigitalInputs.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_DigitalInputs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/OMB_DigitalInputs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/OMB_DigitalInputs.o.d" -o ${OBJECTDIR}/_ext/1472/OMB_DigitalInputs.o ../OMB_DigitalInputs.c    
	
${OBJECTDIR}/_ext/1472/USB.o: ../USB.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/USB.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/USB.o.ok ${OBJECTDIR}/_ext/1472/USB.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/USB.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/USB.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/USB.o.d" -o ${OBJECTDIR}/_ext/1472/USB.o ../USB.c    
	
${OBJECTDIR}/_ext/1472/Event_UV.o: ../Event_UV.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Event_UV.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Event_UV.o.ok ${OBJECTDIR}/_ext/1472/Event_UV.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/Event_UV.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Event_UV.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Event_UV.o.d" -o ${OBJECTDIR}/_ext/1472/Event_UV.o ../Event_UV.c    
	
${OBJECTDIR}/_ext/1472/EEPROM_24AA1025.o: ../EEPROM_24AA1025.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/EEPROM_24AA1025.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/EEPROM_24AA1025.o.ok ${OBJECTDIR}/_ext/1472/EEPROM_24AA1025.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/EEPROM_24AA1025.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/EEPROM_24AA1025.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/EEPROM_24AA1025.o.d" -o ${OBJECTDIR}/_ext/1472/EEPROM_24AA1025.o ../EEPROM_24AA1025.c    
	
${OBJECTDIR}/_ext/1472/CO2_RS485.o: ../CO2_RS485.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/CO2_RS485.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CO2_RS485.o.ok ${OBJECTDIR}/_ext/1472/CO2_RS485.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/CO2_RS485.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/CO2_RS485.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/CO2_RS485.o.d" -o ${OBJECTDIR}/_ext/1472/CO2_RS485.o ../CO2_RS485.c    
	
${OBJECTDIR}/_ext/1472/OMB_AnalogOutput.o: ../OMB_AnalogOutput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_AnalogOutput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_AnalogOutput.o.ok ${OBJECTDIR}/_ext/1472/OMB_AnalogOutput.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_AnalogOutput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/OMB_AnalogOutput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/OMB_AnalogOutput.o.d" -o ${OBJECTDIR}/_ext/1472/OMB_AnalogOutput.o ../OMB_AnalogOutput.c    
	
${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART2.o: ../p24FJ256DA210_UART2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART2.o.ok ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART2.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART2.o.d" -o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART2.o ../p24FJ256DA210_UART2.c    
	
${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART1.o: ../p24FJ256DA210_UART1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART1.o.ok ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART1.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART1.o.d" -o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART1.o ../p24FJ256DA210_UART1.c    
	
${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer1.o: ../p24FJ256DA210_Timer1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer1.o.ok ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer1.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer1.o.d" -o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer1.o ../p24FJ256DA210_Timer1.c    
	
${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C3.o: ../p24FJ256DA210_I2C3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C3.o.ok ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C3.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C3.o.d" -o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C3.o ../p24FJ256DA210_I2C3.c    
	
${OBJECTDIR}/_ext/1472/p24FJ256DA210_SPI1.o: ../p24FJ256DA210_SPI1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_SPI1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_SPI1.o.ok ${OBJECTDIR}/_ext/1472/p24FJ256DA210_SPI1.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_SPI1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/p24FJ256DA210_SPI1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/p24FJ256DA210_SPI1.o.d" -o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_SPI1.o ../p24FJ256DA210_SPI1.c    
	
${OBJECTDIR}/_ext/1472/LTC2439.o: ../LTC2439.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/LTC2439.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/LTC2439.o.ok ${OBJECTDIR}/_ext/1472/LTC2439.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/LTC2439.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/LTC2439.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/LTC2439.o.d" -o ${OBJECTDIR}/_ext/1472/LTC2439.o ../LTC2439.c    
	
${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C1.o: ../p24FJ256DA210_I2C1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C1.o.ok ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C1.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C1.o.d" -o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C1.o ../p24FJ256DA210_I2C1.c    
	
${OBJECTDIR}/_ext/1472/p24FJ256DA210_ICN.o: ../p24FJ256DA210_ICN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_ICN.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_ICN.o.ok ${OBJECTDIR}/_ext/1472/p24FJ256DA210_ICN.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_ICN.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/p24FJ256DA210_ICN.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/p24FJ256DA210_ICN.o.d" -o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_ICN.o ../p24FJ256DA210_ICN.c    
	
${OBJECTDIR}/_ext/1472/p24FJ256DA210_OCx.o: ../p24FJ256DA210_OCx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_OCx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_OCx.o.ok ${OBJECTDIR}/_ext/1472/p24FJ256DA210_OCx.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_OCx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/p24FJ256DA210_OCx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/p24FJ256DA210_OCx.o.d" -o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_OCx.o ../p24FJ256DA210_OCx.c    
	
${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer3.o: ../p24FJ256DA210_Timer3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer3.o.ok ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer3.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer3.o.d" -o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer3.o ../p24FJ256DA210_Timer3.c    
	
${OBJECTDIR}/_ext/1472/Flash.o: ../Flash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Flash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Flash.o.ok ${OBJECTDIR}/_ext/1472/Flash.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/Flash.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Flash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Flash.o.d" -o ${OBJECTDIR}/_ext/1472/Flash.o ../Flash.c    
	
${OBJECTDIR}/_ext/867694782/ENC28J60.o: ../Microchip/TCPIP\ Stack/ENC28J60.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/ENC28J60.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/ENC28J60.o.ok ${OBJECTDIR}/_ext/867694782/ENC28J60.o.err 
	@${RM} ${OBJECTDIR}/_ext/867694782/ENC28J60.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/ENC28J60.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/867694782/ENC28J60.o.d" -o ${OBJECTDIR}/_ext/867694782/ENC28J60.o "../Microchip/TCPIP Stack/ENC28J60.c"    
	
${OBJECTDIR}/_ext/867694782/Delay.o: ../Microchip/TCPIP\ Stack/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/Delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/Delay.o.ok ${OBJECTDIR}/_ext/867694782/Delay.o.err 
	@${RM} ${OBJECTDIR}/_ext/867694782/Delay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/Delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/867694782/Delay.o.d" -o ${OBJECTDIR}/_ext/867694782/Delay.o "../Microchip/TCPIP Stack/Delay.c"    
	
${OBJECTDIR}/_ext/867694782/StackTsk.o: ../Microchip/TCPIP\ Stack/StackTsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/StackTsk.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/StackTsk.o.ok ${OBJECTDIR}/_ext/867694782/StackTsk.o.err 
	@${RM} ${OBJECTDIR}/_ext/867694782/StackTsk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/StackTsk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/867694782/StackTsk.o.d" -o ${OBJECTDIR}/_ext/867694782/StackTsk.o "../Microchip/TCPIP Stack/StackTsk.c"    
	
${OBJECTDIR}/_ext/867694782/Helpers.o: ../Microchip/TCPIP\ Stack/Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/Helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/Helpers.o.ok ${OBJECTDIR}/_ext/867694782/Helpers.o.err 
	@${RM} ${OBJECTDIR}/_ext/867694782/Helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/Helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/867694782/Helpers.o.d" -o ${OBJECTDIR}/_ext/867694782/Helpers.o "../Microchip/TCPIP Stack/Helpers.c"    
	
${OBJECTDIR}/_ext/867694782/Announce.o: ../Microchip/TCPIP\ Stack/Announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/Announce.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/Announce.o.ok ${OBJECTDIR}/_ext/867694782/Announce.o.err 
	@${RM} ${OBJECTDIR}/_ext/867694782/Announce.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/Announce.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/867694782/Announce.o.d" -o ${OBJECTDIR}/_ext/867694782/Announce.o "../Microchip/TCPIP Stack/Announce.c"    
	
${OBJECTDIR}/_ext/867694782/UDP.o: ../Microchip/TCPIP\ Stack/UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/UDP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/UDP.o.ok ${OBJECTDIR}/_ext/867694782/UDP.o.err 
	@${RM} ${OBJECTDIR}/_ext/867694782/UDP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/UDP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/867694782/UDP.o.d" -o ${OBJECTDIR}/_ext/867694782/UDP.o "../Microchip/TCPIP Stack/UDP.c"    
	
${OBJECTDIR}/_ext/867694782/ARP.o: ../Microchip/TCPIP\ Stack/ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/ARP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/ARP.o.ok ${OBJECTDIR}/_ext/867694782/ARP.o.err 
	@${RM} ${OBJECTDIR}/_ext/867694782/ARP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/ARP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/867694782/ARP.o.d" -o ${OBJECTDIR}/_ext/867694782/ARP.o "../Microchip/TCPIP Stack/ARP.c"    
	
${OBJECTDIR}/_ext/867694782/DHCP.o: ../Microchip/TCPIP\ Stack/DHCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/DHCP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/DHCP.o.ok ${OBJECTDIR}/_ext/867694782/DHCP.o.err 
	@${RM} ${OBJECTDIR}/_ext/867694782/DHCP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/DHCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/867694782/DHCP.o.d" -o ${OBJECTDIR}/_ext/867694782/DHCP.o "../Microchip/TCPIP Stack/DHCP.c"    
	
${OBJECTDIR}/_ext/867694782/Tick.o: ../Microchip/TCPIP\ Stack/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/Tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/Tick.o.ok ${OBJECTDIR}/_ext/867694782/Tick.o.err 
	@${RM} ${OBJECTDIR}/_ext/867694782/Tick.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/867694782/Tick.o.d" -o ${OBJECTDIR}/_ext/867694782/Tick.o "../Microchip/TCPIP Stack/Tick.c"    
	
${OBJECTDIR}/_ext/867694782/IP.o: ../Microchip/TCPIP\ Stack/IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/IP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/IP.o.ok ${OBJECTDIR}/_ext/867694782/IP.o.err 
	@${RM} ${OBJECTDIR}/_ext/867694782/IP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/IP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/867694782/IP.o.d" -o ${OBJECTDIR}/_ext/867694782/IP.o "../Microchip/TCPIP Stack/IP.c"    
	
${OBJECTDIR}/_ext/867694782/ICMP.o: ../Microchip/TCPIP\ Stack/ICMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/ICMP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/ICMP.o.ok ${OBJECTDIR}/_ext/867694782/ICMP.o.err 
	@${RM} ${OBJECTDIR}/_ext/867694782/ICMP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/ICMP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/867694782/ICMP.o.d" -o ${OBJECTDIR}/_ext/867694782/ICMP.o "../Microchip/TCPIP Stack/ICMP.c"    
	
${OBJECTDIR}/_ext/867694782/TCP.o: ../Microchip/TCPIP\ Stack/TCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/TCP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/TCP.o.ok ${OBJECTDIR}/_ext/867694782/TCP.o.err 
	@${RM} ${OBJECTDIR}/_ext/867694782/TCP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/TCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/867694782/TCP.o.d" -o ${OBJECTDIR}/_ext/867694782/TCP.o "../Microchip/TCPIP Stack/TCP.c"    
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.ok ${OBJECTDIR}/_ext/1472/main.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c    
	
${OBJECTDIR}/_ext/1472/General.o: ../General.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/General.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/General.o.ok ${OBJECTDIR}/_ext/1472/General.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/General.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/General.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/General.o.d" -o ${OBJECTDIR}/_ext/1472/General.o ../General.c    
	
else
${OBJECTDIR}/_ext/1472/RH_Control.o: ../RH_Control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/RH_Control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/RH_Control.o.ok ${OBJECTDIR}/_ext/1472/RH_Control.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/RH_Control.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/RH_Control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/RH_Control.o.d" -o ${OBJECTDIR}/_ext/1472/RH_Control.o ../RH_Control.c    
	
${OBJECTDIR}/_ext/1472/TempControl.o: ../TempControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/TempControl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/TempControl.o.ok ${OBJECTDIR}/_ext/1472/TempControl.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/TempControl.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/TempControl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/TempControl.o.d" -o ${OBJECTDIR}/_ext/1472/TempControl.o ../TempControl.c    
	
${OBJECTDIR}/_ext/1472/AC_Hz.o: ../AC_Hz.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/AC_Hz.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/AC_Hz.o.ok ${OBJECTDIR}/_ext/1472/AC_Hz.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/AC_Hz.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/AC_Hz.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/AC_Hz.o.d" -o ${OBJECTDIR}/_ext/1472/AC_Hz.o ../AC_Hz.c    
	
${OBJECTDIR}/_ext/1472/AlarmContactRelay.o: ../AlarmContactRelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/AlarmContactRelay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/AlarmContactRelay.o.ok ${OBJECTDIR}/_ext/1472/AlarmContactRelay.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/AlarmContactRelay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/AlarmContactRelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/AlarmContactRelay.o.d" -o ${OBJECTDIR}/_ext/1472/AlarmContactRelay.o ../AlarmContactRelay.c    
	
${OBJECTDIR}/_ext/1472/CO2_Control.o: ../CO2_Control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/CO2_Control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CO2_Control.o.ok ${OBJECTDIR}/_ext/1472/CO2_Control.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/CO2_Control.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/CO2_Control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/CO2_Control.o.d" -o ${OBJECTDIR}/_ext/1472/CO2_Control.o ../CO2_Control.c    
	
${OBJECTDIR}/_ext/1472/EventRTC.o: ../EventRTC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/EventRTC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/EventRTC.o.ok ${OBJECTDIR}/_ext/1472/EventRTC.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/EventRTC.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/EventRTC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/EventRTC.o.d" -o ${OBJECTDIR}/_ext/1472/EventRTC.o ../EventRTC.c    
	
${OBJECTDIR}/_ext/1472/EventScheduler.o: ../EventScheduler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/EventScheduler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/EventScheduler.o.ok ${OBJECTDIR}/_ext/1472/EventScheduler.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/EventScheduler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/EventScheduler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/EventScheduler.o.d" -o ${OBJECTDIR}/_ext/1472/EventScheduler.o ../EventScheduler.c    
	
${OBJECTDIR}/_ext/1472/EventTCPIP.o: ../EventTCPIP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/EventTCPIP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/EventTCPIP.o.ok ${OBJECTDIR}/_ext/1472/EventTCPIP.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/EventTCPIP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/EventTCPIP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/EventTCPIP.o.d" -o ${OBJECTDIR}/_ext/1472/EventTCPIP.o ../EventTCPIP.c    
	
${OBJECTDIR}/_ext/1472/FailSafeRelay.o: ../FailSafeRelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/FailSafeRelay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/FailSafeRelay.o.ok ${OBJECTDIR}/_ext/1472/FailSafeRelay.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/FailSafeRelay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/FailSafeRelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/FailSafeRelay.o.d" -o ${OBJECTDIR}/_ext/1472/FailSafeRelay.o ../FailSafeRelay.c    
	
${OBJECTDIR}/_ext/1472/O2_Control.o: ../O2_Control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/O2_Control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/O2_Control.o.ok ${OBJECTDIR}/_ext/1472/O2_Control.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/O2_Control.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/O2_Control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/O2_Control.o.d" -o ${OBJECTDIR}/_ext/1472/O2_Control.o ../O2_Control.c    
	
${OBJECTDIR}/_ext/1472/OMB_Mode.o: ../OMB_Mode.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_Mode.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_Mode.o.ok ${OBJECTDIR}/_ext/1472/OMB_Mode.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_Mode.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/OMB_Mode.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/OMB_Mode.o.d" -o ${OBJECTDIR}/_ext/1472/OMB_Mode.o ../OMB_Mode.c    
	
${OBJECTDIR}/_ext/1472/RTC_S35390.o: ../RTC_S35390.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/RTC_S35390.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/RTC_S35390.o.ok ${OBJECTDIR}/_ext/1472/RTC_S35390.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/RTC_S35390.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/RTC_S35390.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/RTC_S35390.o.d" -o ${OBJECTDIR}/_ext/1472/RTC_S35390.o ../RTC_S35390.c    
	
${OBJECTDIR}/_ext/1472/OMB_Output.o: ../OMB_Output.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_Output.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_Output.o.ok ${OBJECTDIR}/_ext/1472/OMB_Output.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_Output.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/OMB_Output.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/OMB_Output.o.d" -o ${OBJECTDIR}/_ext/1472/OMB_Output.o ../OMB_Output.c    
	
${OBJECTDIR}/_ext/1472/EventBuzzer.o: ../EventBuzzer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/EventBuzzer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/EventBuzzer.o.ok ${OBJECTDIR}/_ext/1472/EventBuzzer.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/EventBuzzer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/EventBuzzer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/EventBuzzer.o.d" -o ${OBJECTDIR}/_ext/1472/EventBuzzer.o ../EventBuzzer.c    
	
${OBJECTDIR}/_ext/1472/OMBLTC2439_Inputs.o: ../OMBLTC2439_Inputs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/OMBLTC2439_Inputs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/OMBLTC2439_Inputs.o.ok ${OBJECTDIR}/_ext/1472/OMBLTC2439_Inputs.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/OMBLTC2439_Inputs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/OMBLTC2439_Inputs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/OMBLTC2439_Inputs.o.d" -o ${OBJECTDIR}/_ext/1472/OMBLTC2439_Inputs.o ../OMBLTC2439_Inputs.c    
	
${OBJECTDIR}/_ext/1472/OMB_UTI_Comm.o: ../OMB_UTI_Comm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_UTI_Comm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_UTI_Comm.o.ok ${OBJECTDIR}/_ext/1472/OMB_UTI_Comm.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_UTI_Comm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/OMB_UTI_Comm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/OMB_UTI_Comm.o.d" -o ${OBJECTDIR}/_ext/1472/OMB_UTI_Comm.o ../OMB_UTI_Comm.c    
	
${OBJECTDIR}/_ext/1472/O2_RS485.o: ../O2_RS485.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/O2_RS485.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/O2_RS485.o.ok ${OBJECTDIR}/_ext/1472/O2_RS485.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/O2_RS485.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/O2_RS485.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/O2_RS485.o.d" -o ${OBJECTDIR}/_ext/1472/O2_RS485.o ../O2_RS485.c    
	
${OBJECTDIR}/_ext/1472/OMB_DigitalInputs.o: ../OMB_DigitalInputs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_DigitalInputs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_DigitalInputs.o.ok ${OBJECTDIR}/_ext/1472/OMB_DigitalInputs.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_DigitalInputs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/OMB_DigitalInputs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/OMB_DigitalInputs.o.d" -o ${OBJECTDIR}/_ext/1472/OMB_DigitalInputs.o ../OMB_DigitalInputs.c    
	
${OBJECTDIR}/_ext/1472/USB.o: ../USB.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/USB.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/USB.o.ok ${OBJECTDIR}/_ext/1472/USB.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/USB.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/USB.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/USB.o.d" -o ${OBJECTDIR}/_ext/1472/USB.o ../USB.c    
	
${OBJECTDIR}/_ext/1472/Event_UV.o: ../Event_UV.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Event_UV.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Event_UV.o.ok ${OBJECTDIR}/_ext/1472/Event_UV.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/Event_UV.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Event_UV.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Event_UV.o.d" -o ${OBJECTDIR}/_ext/1472/Event_UV.o ../Event_UV.c    
	
${OBJECTDIR}/_ext/1472/EEPROM_24AA1025.o: ../EEPROM_24AA1025.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/EEPROM_24AA1025.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/EEPROM_24AA1025.o.ok ${OBJECTDIR}/_ext/1472/EEPROM_24AA1025.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/EEPROM_24AA1025.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/EEPROM_24AA1025.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/EEPROM_24AA1025.o.d" -o ${OBJECTDIR}/_ext/1472/EEPROM_24AA1025.o ../EEPROM_24AA1025.c    
	
${OBJECTDIR}/_ext/1472/CO2_RS485.o: ../CO2_RS485.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/CO2_RS485.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CO2_RS485.o.ok ${OBJECTDIR}/_ext/1472/CO2_RS485.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/CO2_RS485.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/CO2_RS485.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/CO2_RS485.o.d" -o ${OBJECTDIR}/_ext/1472/CO2_RS485.o ../CO2_RS485.c    
	
${OBJECTDIR}/_ext/1472/OMB_AnalogOutput.o: ../OMB_AnalogOutput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_AnalogOutput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_AnalogOutput.o.ok ${OBJECTDIR}/_ext/1472/OMB_AnalogOutput.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/OMB_AnalogOutput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/OMB_AnalogOutput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/OMB_AnalogOutput.o.d" -o ${OBJECTDIR}/_ext/1472/OMB_AnalogOutput.o ../OMB_AnalogOutput.c    
	
${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART2.o: ../p24FJ256DA210_UART2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART2.o.ok ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART2.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART2.o.d" -o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART2.o ../p24FJ256DA210_UART2.c    
	
${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART1.o: ../p24FJ256DA210_UART1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART1.o.ok ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART1.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART1.o.d" -o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_UART1.o ../p24FJ256DA210_UART1.c    
	
${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer1.o: ../p24FJ256DA210_Timer1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer1.o.ok ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer1.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer1.o.d" -o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer1.o ../p24FJ256DA210_Timer1.c    
	
${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C3.o: ../p24FJ256DA210_I2C3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C3.o.ok ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C3.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C3.o.d" -o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C3.o ../p24FJ256DA210_I2C3.c    
	
${OBJECTDIR}/_ext/1472/p24FJ256DA210_SPI1.o: ../p24FJ256DA210_SPI1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_SPI1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_SPI1.o.ok ${OBJECTDIR}/_ext/1472/p24FJ256DA210_SPI1.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_SPI1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/p24FJ256DA210_SPI1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/p24FJ256DA210_SPI1.o.d" -o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_SPI1.o ../p24FJ256DA210_SPI1.c    
	
${OBJECTDIR}/_ext/1472/LTC2439.o: ../LTC2439.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/LTC2439.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/LTC2439.o.ok ${OBJECTDIR}/_ext/1472/LTC2439.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/LTC2439.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/LTC2439.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/LTC2439.o.d" -o ${OBJECTDIR}/_ext/1472/LTC2439.o ../LTC2439.c    
	
${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C1.o: ../p24FJ256DA210_I2C1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C1.o.ok ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C1.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C1.o.d" -o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_I2C1.o ../p24FJ256DA210_I2C1.c    
	
${OBJECTDIR}/_ext/1472/p24FJ256DA210_ICN.o: ../p24FJ256DA210_ICN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_ICN.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_ICN.o.ok ${OBJECTDIR}/_ext/1472/p24FJ256DA210_ICN.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_ICN.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/p24FJ256DA210_ICN.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/p24FJ256DA210_ICN.o.d" -o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_ICN.o ../p24FJ256DA210_ICN.c    
	
${OBJECTDIR}/_ext/1472/p24FJ256DA210_OCx.o: ../p24FJ256DA210_OCx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_OCx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_OCx.o.ok ${OBJECTDIR}/_ext/1472/p24FJ256DA210_OCx.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_OCx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/p24FJ256DA210_OCx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/p24FJ256DA210_OCx.o.d" -o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_OCx.o ../p24FJ256DA210_OCx.c    
	
${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer3.o: ../p24FJ256DA210_Timer3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer3.o.ok ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer3.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer3.o.d" -o ${OBJECTDIR}/_ext/1472/p24FJ256DA210_Timer3.o ../p24FJ256DA210_Timer3.c    
	
${OBJECTDIR}/_ext/1472/Flash.o: ../Flash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Flash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Flash.o.ok ${OBJECTDIR}/_ext/1472/Flash.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/Flash.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Flash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Flash.o.d" -o ${OBJECTDIR}/_ext/1472/Flash.o ../Flash.c    
	
${OBJECTDIR}/_ext/867694782/ENC28J60.o: ../Microchip/TCPIP\ Stack/ENC28J60.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/ENC28J60.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/ENC28J60.o.ok ${OBJECTDIR}/_ext/867694782/ENC28J60.o.err 
	@${RM} ${OBJECTDIR}/_ext/867694782/ENC28J60.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/ENC28J60.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/867694782/ENC28J60.o.d" -o ${OBJECTDIR}/_ext/867694782/ENC28J60.o "../Microchip/TCPIP Stack/ENC28J60.c"    
	
${OBJECTDIR}/_ext/867694782/Delay.o: ../Microchip/TCPIP\ Stack/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/Delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/Delay.o.ok ${OBJECTDIR}/_ext/867694782/Delay.o.err 
	@${RM} ${OBJECTDIR}/_ext/867694782/Delay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/Delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/867694782/Delay.o.d" -o ${OBJECTDIR}/_ext/867694782/Delay.o "../Microchip/TCPIP Stack/Delay.c"    
	
${OBJECTDIR}/_ext/867694782/StackTsk.o: ../Microchip/TCPIP\ Stack/StackTsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/StackTsk.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/StackTsk.o.ok ${OBJECTDIR}/_ext/867694782/StackTsk.o.err 
	@${RM} ${OBJECTDIR}/_ext/867694782/StackTsk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/StackTsk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/867694782/StackTsk.o.d" -o ${OBJECTDIR}/_ext/867694782/StackTsk.o "../Microchip/TCPIP Stack/StackTsk.c"    
	
${OBJECTDIR}/_ext/867694782/Helpers.o: ../Microchip/TCPIP\ Stack/Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/Helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/Helpers.o.ok ${OBJECTDIR}/_ext/867694782/Helpers.o.err 
	@${RM} ${OBJECTDIR}/_ext/867694782/Helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/Helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/867694782/Helpers.o.d" -o ${OBJECTDIR}/_ext/867694782/Helpers.o "../Microchip/TCPIP Stack/Helpers.c"    
	
${OBJECTDIR}/_ext/867694782/Announce.o: ../Microchip/TCPIP\ Stack/Announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/Announce.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/Announce.o.ok ${OBJECTDIR}/_ext/867694782/Announce.o.err 
	@${RM} ${OBJECTDIR}/_ext/867694782/Announce.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/Announce.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/867694782/Announce.o.d" -o ${OBJECTDIR}/_ext/867694782/Announce.o "../Microchip/TCPIP Stack/Announce.c"    
	
${OBJECTDIR}/_ext/867694782/UDP.o: ../Microchip/TCPIP\ Stack/UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/UDP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/UDP.o.ok ${OBJECTDIR}/_ext/867694782/UDP.o.err 
	@${RM} ${OBJECTDIR}/_ext/867694782/UDP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/UDP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/867694782/UDP.o.d" -o ${OBJECTDIR}/_ext/867694782/UDP.o "../Microchip/TCPIP Stack/UDP.c"    
	
${OBJECTDIR}/_ext/867694782/ARP.o: ../Microchip/TCPIP\ Stack/ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/ARP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/ARP.o.ok ${OBJECTDIR}/_ext/867694782/ARP.o.err 
	@${RM} ${OBJECTDIR}/_ext/867694782/ARP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/ARP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/867694782/ARP.o.d" -o ${OBJECTDIR}/_ext/867694782/ARP.o "../Microchip/TCPIP Stack/ARP.c"    
	
${OBJECTDIR}/_ext/867694782/DHCP.o: ../Microchip/TCPIP\ Stack/DHCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/DHCP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/DHCP.o.ok ${OBJECTDIR}/_ext/867694782/DHCP.o.err 
	@${RM} ${OBJECTDIR}/_ext/867694782/DHCP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/DHCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/867694782/DHCP.o.d" -o ${OBJECTDIR}/_ext/867694782/DHCP.o "../Microchip/TCPIP Stack/DHCP.c"    
	
${OBJECTDIR}/_ext/867694782/Tick.o: ../Microchip/TCPIP\ Stack/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/Tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/Tick.o.ok ${OBJECTDIR}/_ext/867694782/Tick.o.err 
	@${RM} ${OBJECTDIR}/_ext/867694782/Tick.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/867694782/Tick.o.d" -o ${OBJECTDIR}/_ext/867694782/Tick.o "../Microchip/TCPIP Stack/Tick.c"    
	
${OBJECTDIR}/_ext/867694782/IP.o: ../Microchip/TCPIP\ Stack/IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/IP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/IP.o.ok ${OBJECTDIR}/_ext/867694782/IP.o.err 
	@${RM} ${OBJECTDIR}/_ext/867694782/IP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/IP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/867694782/IP.o.d" -o ${OBJECTDIR}/_ext/867694782/IP.o "../Microchip/TCPIP Stack/IP.c"    
	
${OBJECTDIR}/_ext/867694782/ICMP.o: ../Microchip/TCPIP\ Stack/ICMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/ICMP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/ICMP.o.ok ${OBJECTDIR}/_ext/867694782/ICMP.o.err 
	@${RM} ${OBJECTDIR}/_ext/867694782/ICMP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/ICMP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/867694782/ICMP.o.d" -o ${OBJECTDIR}/_ext/867694782/ICMP.o "../Microchip/TCPIP Stack/ICMP.c"    
	
${OBJECTDIR}/_ext/867694782/TCP.o: ../Microchip/TCPIP\ Stack/TCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/TCP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/TCP.o.ok ${OBJECTDIR}/_ext/867694782/TCP.o.err 
	@${RM} ${OBJECTDIR}/_ext/867694782/TCP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/TCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/867694782/TCP.o.d" -o ${OBJECTDIR}/_ext/867694782/TCP.o "../Microchip/TCPIP Stack/TCP.c"    
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.ok ${OBJECTDIR}/_ext/1472/main.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c    
	
${OBJECTDIR}/_ext/1472/General.o: ../General.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/General.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/General.o.ok ${OBJECTDIR}/_ext/1472/General.o.err 
	@${RM} ${OBJECTDIR}/_ext/1472/General.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/General.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -I"../Configs" -I"../../../Microchip/Include" -I"../../../Microchip" -I"../Common_Files" -I"../Microchip/Include" -I"../Microchip" -I"../Microchip/Include/TCPIP Stack" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/General.o.d" -o ${OBJECTDIR}/_ext/1472/General.o ../General.c    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/OMB_CLS_build13.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/OMB_CLS_build13.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,-L"..",-L".",-Map="${DISTDIR}/OMB_CLS_build13.X.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/OMB_CLS_build13.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/OMB_CLS_build13.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,-L"..",-L".",-Map="${DISTDIR}/OMB_CLS_build13.X.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/OMB_CLS_build13.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -omf=elf
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
