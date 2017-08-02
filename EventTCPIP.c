/**
EventTCPIP.c
**/
#include "ApplicationDrivers.h"
#include "EventTCPIP.h"

static unsigned short wOriginalAppConfigChecksum;    // Checksum of the ROM defaults for AppConfig
NVM_VALIDATION_PAGESTRUCTTOBYTE Local_pointer_page;  //this is needed to read the flash values
pNVM_VALIDATION_PAGESTRUCTTOBYTE Local_Pointer;
pAPP_CONFIG_PAGESTRUCTTOBYTE Local_APPPointer;
APP_CONFIG_PAGESTRUCTTOBYTE Local_APPpointer_page;
static DWORD t = 0;
static DWORD dwLastIP = 0;
MODBUSPDU_RX ModBus_DataRx;
MODBUSPDU_TX ModBus_DataTx;


BYTE VoyagerRegTable[MAX_NUMBER_OF_REG_FORTCPIP]={	
							TCV,
							TSP,
							TSP_HA,
							TSP_LA,
							TSP_DA,
							TCV_OFFSET,
							CO2CV,
							CO2SP,
							CO2_HA,
							CO2_LA,
							CO2CV_OFFSET,
							RHCV,
							RHSP,
							RH_HA,
							RH_LA,
							RHCV_OFFSET,
							O2CV,
							O2SP,
							O2_HA,
							O2_LA,
							O2CV_OFFSET,					

							};
  	

// MAC Address Serialization using a MPLAB PM3 Programmer and 
// Serialized Quick Turn Programming (SQTP). 
// The advantage of using SQTP for programming the MAC Address is it
// allows you to auto-increment the MAC address without recompiling 
// the code for each unit.  To use SQTP, the MAC address must be fixed
// at a specific location in program memory.  Uncomment these two pragmas
// that locate the MAC address at 0x1FFF0.  Syntax below is for MPLAB C 
// Compiler for PIC18 MCUs. Syntax will vary for other compilers.
//#pragma romdata MACROM=0x1FFF0
static ROM BYTE SerializedMACAddress[6] = {MY_DEFAULT_MAC_BYTE1, MY_DEFAULT_MAC_BYTE2, MY_DEFAULT_MAC_BYTE3, MY_DEFAULT_MAC_BYTE4, MY_DEFAULT_MAC_BYTE5, MY_DEFAULT_MAC_BYTE6};
//#pragma romdata

void EventTCPIP (void)
{
	if(TickGet() - t >= TICK_SECOND/2ul)
		{
			t = TickGet();
			//LED0_IO ^= 1;
		}
	
		// This task performs normal stack task including checking
		// for incoming packet, type of packet and calling
		// appropriate stack entity to process it.
		StackTask();
		 TPCIP_Voyager_Init_Task();
		 TPCIP_Voyager_Task(); 
		
    #if defined(WF_CS_TRIS)
    #if !defined(MRF24WG)
		if (gRFModuleVer1209orLater)
    #endif
			WiFiTask();
    #endif
	
		// This tasks invokes each of the core stack application tasks
		StackApplications();
	
    #if defined(STACK_USE_ZEROCONF_LINK_LOCAL)
		ZeroconfLLProcess();
    #endif
	
    #if defined(STACK_USE_ZEROCONF_MDNS_SD)
		mDNSProcess();
		// Use this function to exercise service update function
		// HTTPUpdateRecord();
    #endif
	
		// Process application specific tasks here.
		// For this demo app, this will include the Generic TCP 
		// client and servers, and the SNMP, Ping, and SNMP Trap
		// demos.  Following that, we will process any IO from
		// the inputs on the board itself.
		// Any custom modules or processing you need to do should
		// go here.
    #if defined(STACK_USE_GENERIC_TCP_CLIENT_EXAMPLE)
		GenericTCPClient();
    #endif
		
    #if defined(STACK_USE_GENERIC_TCP_SERVER_EXAMPLE)
		GenericTCPServer();
    #endif
		
    #if defined(STACK_USE_SMTP_CLIENT)
		SMTPDemo();
    #endif
		
    #if defined(STACK_USE_ICMP_CLIENT)
		PingDemo();
    #endif
	
	#if defined(STACK_USE_TFTP_CLIENT) && defined(WF_CS_TRIS)	
		TFTPGetUploadStatus();
	#endif
		   
    #if defined(STACK_USE_SNMP_SERVER) && !defined(SNMP_TRAP_DISABLED)
		//User should use one of the following SNMP demo
		// This routine demonstrates V1 or V2 trap formats with one variable binding.
		SNMPTrapDemo();
		
    #if defined(SNMP_STACK_USE_V2_TRAP) || defined(SNMP_V1_V2_TRAP_WITH_SNMPV3)
		//This routine provides V2 format notifications with multiple (3) variable bindings
		//User should modify this routine to send v2 trap format notifications with the required varbinds.
		//SNMPV2TrapDemo();
    #endif 
		if(gSendTrapFlag)
			SNMPSendTrap();
    #endif
		
    #if defined(STACK_USE_BERKELEY_API)
		BerkeleyTCPClientDemo();
		BerkeleyTCPServerDemo();
		BerkeleyUDPClientDemo();
    #endif
	
		//ProcessIO();
	
		// If the local IP address has changed (ex: due to DHCP lease change)
		// write the new IP address to the LCD display, UART, and Announce 
		// service
		if(dwLastIP != AppConfig.MyIPAddr.Val)
		{
		  dwLastIP = AppConfig.MyIPAddr.Val;
		  
      #if defined(STACK_USE_UART)
			  //putrsUART((ROM char*)"\r\nNew IP Address: ");
			  //UART1_Tx_String((BYTE *)"\r\nNew IP Address: ");
			  UART2_TxString("\r\nNew IP Address: ");
      #endif
	
		  DisplayIPValue(AppConfig.MyIPAddr);
	
      #if defined(STACK_USE_UART)
			  //putrsUART((ROM char*)"\r\n");
				//UART1_Tx_String((BYTE*)"\r\n");
				UART2_TxString("\r\n");
      #endif
	
	
      #if defined(STACK_USE_ANNOUNCE)
			  AnnounceIP();
      #endif


	  	
      #if defined(STACK_USE_ZEROCONF_MDNS_SD)
			  mDNSFillHostRecord();
      #endif
		
	#ifdef WIFI_NET_TEST	
	#ifdef STACK_USE_TFTP_CLIENT
		if(AppConfig.Flags.bIsDHCPEnabled && DHCPIsBound(0)) {	
			static UINT8  tftpInitDone = 0;
			static BYTE dummy_file[] = "TFTP test dummy contents";
			static ROM BYTE file_name[] = "dontcare";
			static ROM BYTE host_name[] = "tftp" WIFI_NET_TEST_DOMAIN;	
			if (!tftpInitDone) {
				TFTPUploadRAMFileToHost(host_name, file_name, dummy_file, sizeof(dummy_file));
				tftpInitDone = 1;
			}
		}
	#endif
	#endif
		
		}	 
    #if defined(DERIVE_KEY_FROM_PASSPHRASE_IN_HOST) && defined (MRF24WG)
			   if (g_WpsPassphrase.valid) {
				   WF_ConvPassphrase2Key(g_WpsPassphrase.passphrase.keyLen, g_WpsPassphrase.passphrase.key,
				   g_WpsPassphrase.passphrase.ssidLen, g_WpsPassphrase.passphrase.ssid);
				   WF_SetPSK(g_WpsPassphrase.passphrase.key);
				   g_WpsPassphrase.valid = FALSE;
			   }
       #endif    // defined(DERIVE_KEY_FROM_PASSPHRASE_IN_HOST) 
		#if defined(STACK_USE_AUTOUPDATE_HTTPSERVER) && defined(WF_CS_TRIS) && defined(MRF24WG)
			{
				static DWORD t_UpdateImage=0;
				extern UINT8 Flag_ImageUpdate_running;
				if(Flag_ImageUpdate_running == 1)
				{
					UINT8 buf_command[4];
					if( (TickGet() - t_UpdateImage) >= TICK_SECOND * 120ul)
					{
						putsUART((char *)"Update Firmware timeout, begin to restore..\r\n");
						buf_command[0]=UPDATE_CMD_ERASE0; //Erase bank0
						buf_command[1]=UPDATE_SERITY_KEY_1; 
						buf_command[2]=UPDATE_SERITY_KEY_2; 
						buf_command[3]=UPDATE_SERITY_KEY_3; 
						SendSetParamMsg(PARAM_FLASH_update, buf_command, 4);
						buf_command[0]=UPDATE_CMD_CPY_1TO0; //Copy bank1 to bank0
						buf_command[1]=UPDATE_SERITY_KEY_1; 
						buf_command[2]=UPDATE_SERITY_KEY_2; 
						buf_command[3]=UPDATE_SERITY_KEY_3; 
						SendSetParamMsg(PARAM_FLASH_update, buf_command, 4);
						putsUART((char *)"restore Done\r\n");
						Flag_ImageUpdate_running = 0;
					}
						
				}
				else
				{
					t_UpdateImage = TickGet();
				}
			}
		#endif
}

/*------------------------------------------------------------------------------
 * Function Name : Return_APPPage_Pointer
 * Arguments	 : void
 * Description   : Returns a pointer to the Return_APPPage_Pointer page.
 * Returns	 	 : Returns a pointer to the Return_APPPage_Pointer page.
 * Author        : Amit G.
 * History       : Created on : 03/10/2013 by Amit G 
 *                 Closed on  : 
 *                 Modified on :
 *------------------------------------------------------------------------------
 */
pAPP_CONFIG_PAGESTRUCTTOBYTE Return_APPPage_Pointer(void)
{
	
	return &(Local_APPpointer_page);
}


/*------------------------------------------------------------------------------
 * Function Name : Return_NVMPage_Pointer
 * Arguments	 : void
 * Description   : Returns a pointer to the Return_NVMPage_Pointer page.
 * Returns	 	 : Returns a pointer to the Return_NVMPage_Pointer page.
 * Author        : Amit G.
 * History       : Created on : 03/10/2013 by Amit G 
 *                 Closed on  : 
 *                 Modified on :
 *------------------------------------------------------------------------------
 */
pNVM_VALIDATION_PAGESTRUCTTOBYTE Return_NVMPage_Pointer(void)
{
	
	return &(Local_pointer_page);
}



void InitAppConfig(void)
{
#if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
    unsigned char vNeedToSaveDefaults = 0;
#endif
    
    
    while(1)
    {
        // Start out zeroing all AppConfig bytes to ensure all fields are 
        // deterministic for checksum generation
        memset((void*)&AppConfig, 0x00, sizeof(AppConfig));
        
        AppConfig.Flags.bIsDHCPEnabled = TRUE;
        AppConfig.Flags.bInConfigMode = TRUE;
        memcpypgm2ram((void*)&AppConfig.MyMACAddr, (ROM void*)SerializedMACAddress, sizeof(AppConfig.MyMACAddr));

        AppConfig.MyIPAddr.Val = MY_DEFAULT_IP_ADDR_BYTE1 | MY_DEFAULT_IP_ADDR_BYTE2<<8ul | MY_DEFAULT_IP_ADDR_BYTE3<<16ul | MY_DEFAULT_IP_ADDR_BYTE4<<24ul;
        AppConfig.DefaultIPAddr.Val = AppConfig.MyIPAddr.Val;
        AppConfig.MyMask.Val = MY_DEFAULT_MASK_BYTE1 | MY_DEFAULT_MASK_BYTE2<<8ul | MY_DEFAULT_MASK_BYTE3<<16ul | MY_DEFAULT_MASK_BYTE4<<24ul;
        AppConfig.DefaultMask.Val = AppConfig.MyMask.Val;
        AppConfig.MyGateway.Val = MY_DEFAULT_GATE_BYTE1 | MY_DEFAULT_GATE_BYTE2<<8ul | MY_DEFAULT_GATE_BYTE3<<16ul | MY_DEFAULT_GATE_BYTE4<<24ul;
        AppConfig.PrimaryDNSServer.Val = MY_DEFAULT_PRIMARY_DNS_BYTE1 | MY_DEFAULT_PRIMARY_DNS_BYTE2<<8ul  | MY_DEFAULT_PRIMARY_DNS_BYTE3<<16ul  | MY_DEFAULT_PRIMARY_DNS_BYTE4<<24ul;
        AppConfig.SecondaryDNSServer.Val = MY_DEFAULT_SECONDARY_DNS_BYTE1 | MY_DEFAULT_SECONDARY_DNS_BYTE2<<8ul  | MY_DEFAULT_SECONDARY_DNS_BYTE3<<16ul  | MY_DEFAULT_SECONDARY_DNS_BYTE4<<24ul;
    
        // Load the default NetBIOS Host Name
        memcpypgm2ram(AppConfig.NetBIOSName, (ROM void*)MY_DEFAULT_HOST_NAME, 16);
        FormatNetBIOSName(AppConfig.NetBIOSName);
    
        // Compute the checksum of the AppConfig defaults as loaded from ROM
        wOriginalAppConfigChecksum = CalcIPChecksum((BYTE*)&AppConfig, sizeof(AppConfig));

        #if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
        {
            //NVM_VALIDATION_STRUCT NVMValidationStruct;

            // Check to see if we have a flag set indicating that we need to 
            // save the ROM default AppConfig values.
            if(vNeedToSaveDefaults)
                SaveAppConfig(&AppConfig);
        
            // Read the NVMValidation record and AppConfig struct out of EEPROM/Flash
            #if defined(SPIFLASH_CS_TRIS)
            {
               // SPIFlashReadArray(0x0000, (BYTE*)&NVMValidationStruct, sizeof(NVMValidationStruct));
               // SPIFlashReadArray(sizeof(NVMValidationStruct), (BYTE*)&AppConfig, sizeof(AppConfig));
               //Flash_Write_Read_API( FLASH_DATA_READ, 0x0000, (BYTE*)&NVMValidationStruct , sizeof(NVMValidationStruct)  );
               //Flash_Write_Read_API( FLASH_DATA_READ, 0x0000, Local_pointer_page.bytes , sizeof(NVM_VALIDATION_STRUCT)  );
        	   //Flash_Write_Read_API( FLASH_DATA_READ, 0x0006, Local_APPpointer_page.bytes, sizeof(APP_CONFIG)  );
        	   FLASH_Read(SECTOR_0,sizeof(NVM_VALIDATION_STRUCT),Local_pointer_page.bytes);
			   FLASH_Read(SECTOR_6,sizeof(APP_CONFIG),Local_APPpointer_page.bytes);
            }
            #endif
    
            // Check EEPROM/Flash validitity.  If it isn't valid, set a flag so 
            // that we will save the ROM default values on the next loop 
            // iteration.
//          if((NVMValidationStruct.wConfigurationLength != sizeof(AppConfig)) ||
//             (NVMValidationStruct.wOriginalChecksum != wOriginalAppConfigChecksum) ||
//             (NVMValidationStruct.wCurrentChecksum != CalcIPChecksum((BYTE*)&AppConfig, sizeof(AppConfig))))
//          {
			if((Local_pointer_page.Page_Instance.wConfigurationLength != sizeof(AppConfig)) ||
               (Local_pointer_page.Page_Instance.wOriginalChecksum != wOriginalAppConfigChecksum) ||
               (Local_pointer_page.Page_Instance.wCurrentChecksum != CalcIPChecksum((BYTE*)&AppConfig, sizeof(AppConfig))))
            {
                // Check to ensure that the vNeedToSaveDefaults flag is zero, 
                // indicating that this is the first iteration through the do 
                // loop.  If we have already saved the defaults once and the 
                // EEPROM/Flash still doesn't pass the validity check, then it 
                // means we aren't successfully reading or writing to the 
                // EEPROM/Flash.  This means you have a hardware error and/or 
                // SPI configuration error.
                if(vNeedToSaveDefaults)
                {	
	                //break;
                    while(1);
                }
                
                // Set flag and restart loop to load ROM defaults and save them
                vNeedToSaveDefaults = 1;
                continue;
            }
            
            // If we get down here, it means the EEPROM/Flash has valid contents 
            // and either matches the ROM defaults or previously matched and 
            // was run-time reconfigured by the user.  In this case, we shall 
            // use the contents loaded from EEPROM/Flash.
            break;
        }
        #endif
        break;
    }
}

/*------------------------------------------------------------------------------
 * Function Name : SaveAppConfig
 * Arguments	 : None
 * PreCondition:   MPFSInit() is already called.
 * Description   : Saves configuration files
 * Returns	     : void
 * Author        : Amit G
 * History       : Created on : 21/08/2013 by Amit G
 * Closed on  : 
 * Modified on : 04 June 2014 by Ashari S
 *------------------------------------------------------------------------------
 */
#if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
void SaveAppConfig(const APP_CONFIG *ptrAppConfig)
{
    NVM_VALIDATION_STRUCT NVMValidationStruct;
    //BYTE Local_Arr[10],Cnt=0;
    //WORDTOBYTE Local;
    
    // Ensure adequate space has been reserved in non-volatile storage to 
    // store the entire AppConfig structure.  If you get stuck in this while(1) 
    // trap, it means you have a design time misconfiguration in TCPIPConfig.h.
    // You must increase MPFS_RESERVE_BLOCK to allocate more space.
    #if defined(STACK_USE_MPFS2)
        if(sizeof(NVMValidationStruct) + sizeof(AppConfig) > MPFS_RESERVE_BLOCK)
            while(1);
    #endif

    // Get proper values for the validation structure indicating that we can use 
    // these EEPROM/Flash contents on future boot ups
    NVMValidationStruct.wOriginalChecksum = wOriginalAppConfigChecksum;
    NVMValidationStruct.wCurrentChecksum = CalcIPChecksum((BYTE*)ptrAppConfig, sizeof(APP_CONFIG));
    NVMValidationStruct.wConfigurationLength = sizeof(APP_CONFIG);

    // Write the validation struct and current AppConfig contents to EEPROM/Flash
    #if defined(EEPROM_CS_TRIS)
        XEEBeginWrite(0x0000);
        XEEWriteArray((BYTE*)&NVMValidationStruct, sizeof(NVMValidationStruct));
        XEEWriteArray((BYTE*)ptrAppConfig, sizeof(APP_CONFIG));
    #else
        //SPIFlashBeginWrite(0x0000);
        //SPIFlashWriteArray((BYTE*)&NVMValidationStruct, sizeof(NVMValidationStruct));
        //SPIFlashWriteArray((BYTE*)ptrAppConfig, sizeof(APP_CONFIG));
        FLASH_WriteStatusReg(0x00);
	  	DelayMs(5);
	  	
	
		Local_Pointer = Return_NVMPage_Pointer();

	  	FLASH_SectorErase(SECTOR_0);
	  	FLASH_SectorErase(SECTOR_6);
		FLASH_Read(SECTOR_0,sizeof(NVM_VALIDATION_STRUCT),Local_pointer_page.bytes);
		FLASH_Read(SECTOR_6,sizeof(APP_CONFIG),Local_APPpointer_page.bytes);
		
	  	Local_Pointer->Page_Instance.wConfigurationLength = NVMValidationStruct.wConfigurationLength;
	  	Local_Pointer->Page_Instance.wOriginalChecksum    = NVMValidationStruct.wOriginalChecksum;
	  	Local_Pointer->Page_Instance.wCurrentChecksum     = NVMValidationStruct.wCurrentChecksum;
	  	
	  	Local_APPPointer = Return_APPPage_Pointer();
	  		
	  	
	  	Local_APPPointer->Page_Instance.Flags.bIsDHCPEnabled = AppConfig.Flags.bIsDHCPEnabled;
	  	Local_APPPointer->Page_Instance.Flags.bInConfigMode  = AppConfig.Flags.bInConfigMode;
	  	memcpypgm2ram((void*)&(Local_APPPointer->Page_Instance.MyMACAddr), (ROM void*)SerializedMACAddress, sizeof(AppConfig.MyMACAddr));
	  	
	  	Local_APPPointer->Page_Instance.MyIPAddr.Val = AppConfig.MyIPAddr.Val;
	  	Local_APPPointer->Page_Instance.DefaultIPAddr.Val= AppConfig.DefaultIPAddr.Val;
	  	Local_APPPointer->Page_Instance.MyMask.Val = AppConfig.MyMask.Val;
	  	Local_APPPointer->Page_Instance.DefaultMask.Val = AppConfig.DefaultMask.Val;
	  	Local_APPPointer->Page_Instance.MyGateway.Val = AppConfig.MyGateway.Val ;
	  	Local_APPPointer->Page_Instance.PrimaryDNSServer.Val = AppConfig.PrimaryDNSServer.Val;
	  	Local_APPPointer->Page_Instance.SecondaryDNSServer.Val = AppConfig.SecondaryDNSServer.Val;
	  	
	  	// Load the default NetBIOS Host Name
	  	memcpypgm2ram(Local_APPPointer->Page_Instance.NetBIOSName, (ROM void*)MY_DEFAULT_HOST_NAME, 16);
	  	memcpypgm2ram(Local_APPPointer->Page_Instance.NetBIOSName,AppConfig.NetBIOSName,16);
	  	
	  	FLASH_MultiByteProgram(SECTOR_0, Local_Pointer->bytes, sizeof(NVM_VALIDATION_STRUCT));
        	FLASH_MultiByteProgram(SECTOR_6, Local_APPPointer->bytes, sizeof(APP_CONFIG));
        
        
    #endif
}
#endif

/*------------------------------------------------------------------------------
 * Function Name : DisplayIPValue
 * Arguments	 : none
 * Description   : Writes an IP address to the LCD display and the UART as available
 * Returns	 	 : void
 * Author        : Amit G
 * History       : Created on : 13/08/2013 by Amit G
 *                 Closed on  : 
 *                 Modified on :
 *------------------------------------------------------------------------------
 */

void DisplayIPValue(IP_ADDR IPVal)
{
// printf("%u.%u.%u.%u", IPVal.v[0], IPVal.v[1], IPVal.v[2], IPVal.v[3]);
#if defined (__dsPIC33E__) || defined (__PIC24E__)
    static BYTE IPDigit[4];                        /* Needs to be declared as static to avoid the array getting optimized by C30 v3.30 compiler for dsPIC33E/PIC24E. 
                                                   Otherwise the LCD displays corrupted IP address on Explorer 16. To be fixed in the future compiler release*/
#else
    BYTE IPDigit[4];
#endif
    BYTE i;
#ifdef USE_LCD
    BYTE j;
    BYTE LCDPos=16;
#endif

    for(i = 0; i < sizeof(IP_ADDR); i++)
    {
        uitoa((WORD)IPVal.v[i], IPDigit);

        #if defined(STACK_USE_UART)
            //putsUART((char *) IPDigit);
			//UART1_Tx_String((BYTE *) IPDigit);
			UART2_TxString((char*)IPDigit);
        #endif

        #ifdef USE_LCD
            for(j = 0; j < strlen((char*)IPDigit); j++)
            {
                LCDText[LCDPos++] = IPDigit[j];
            }
            if(i == sizeof(IP_ADDR)-1)
                break;
            LCDText[LCDPos++] = '.';
        #else
            if(i == sizeof(IP_ADDR)-1)
                break;
        #endif

        #if defined(STACK_USE_UART)
            //while(BusyUART());
            //WriteUART('.');
			//UART1_HIGH();
			//while(BusyUART1()); // Check to see if the UART 2 has finished transmitting;
			//Delay10us(5);
			//putcUART1('.');					//Write data to be trasmitted to the Tx buffer
			//Delay10us(5);
		    //while(BusyUART1()); // Check to see if the UART 2 has finished transmitting;
		    //UART1_LOW();
		    UART2_TxByte('.');
			
        #endif
    }

    #ifdef USE_LCD
        if(LCDPos < 32u)
            LCDText[LCDPos] = 0;
        LCDUpdate();
    #endif
}


/*-------------------------------------------------------------------------------------------------
 * Function Name : AddressError
 * Arguments	 : void 
 * Description   : If your code gets here, you either tried to read or write
				   a NULL pointer, or your application overflowed the stack
				   by having too many local variables or parameters declared.
 * Returns       : void
 * Author        : Shaunak S
 * History       : Created : 21/08/20130  by Amit G
 *		   		   Closed  : 
 *-------------------------------------------------------------------------------------------------
 */

#if defined(__C30__)
    void _ISR __attribute__((__no_auto_psv__)) _AddressError(void)
    {
        Nop();
        Nop();
    }
 #endif   


/*-------------------------------------------------------------------------------------------------
 * Function Name : StackError
 * Arguments	 : void 
 * Description   : If your code gets here, you either tried to read or write
				   a NULL pointer, or your application overflowed the stack
				   by having too many local variables or parameters declared.
 * Returns       : void
 * Author        : Shaunak S
 * History       : Created : 21/08/20130  by Amit G
 *		   		   Closed  : 
 *-------------------------------------------------------------------------------------------------
 */
#if defined(__C30__)
void _ISR __attribute__((__no_auto_psv__)) _StackError(void)
    {
        Nop();
        Nop();
    }
#endif





  void TPCIP_Voyager_Init_Task (void)
	{
		
		INT temp;
		BYTE c,AppBuffer[20];
		static DWORD dwTimer = 0;

		static UDP_SOCKET	MySocket;
			
		static enum _UDPServerState
			{
				SM_HOME = 0,
				SM_LISTENING,
				SM_RCV_RPLY,
				SM_CLOSING,
			} UDPServerState = SM_HOME;

        
		if(!MACIsLinked())return;		
				
	
		// Wait until DHCP module is finished
		if(!DHCPIsBound(0))
		{
			dwTimer = TickGet();
			return;
		}
		
		switch(UDPServerState )
			{
				case SM_HOME:
					MySocket = UDPOpenEx(0,UDP_OPEN_SERVER,UDP_LOCAL_PORT, UDP_VOYAGER_PORT);
					if(MySocket == INVALID_UDP_SOCKET)
						return;
					else	UDPServerState++;
					break;
				case SM_LISTENING:
					// Do nothing if no data is waiting
					if(!UDPIsGetReady(MySocket))
						return;
					// We received a discovery request, reply when we can
					UDPServerState++;
					
					// Change the destination to the unicast address of the last received packet
					memcpy((void*)&UDPSocketInfo[MySocket].remote.remoteNode, (const void*)&remoteNode, sizeof(remoteNode));
								
					// No break needed.  If we get down here, we are now ready for the SM_RCV_RPLY state
				case SM_RCV_RPLY:	
					if(!UDPIsPutReady(MySocket))
						return;
					
					///send the ip adress
					//UDPPutArray((BYTE*)&AppConfig.MyIPAddr, sizeof(AppConfig.MyIPAddr));
					memset(&AppBuffer,0x00,sizeof(AppBuffer));
					temp=-1;
					for(c=0;c<4;c++)
					{
					uitoa((WORD)AppConfig.MyIPAddr.v[c],&AppBuffer[temp+1]);
					temp=strlen((char *)AppBuffer);
					AppBuffer[temp]='.'; 	
					}
					
					temp=strlen((char *)AppBuffer);
					UDPPutArray(&AppBuffer[0],(WORD)temp);
					UDPPut('-');
					memset(&AppBuffer,0x00,sizeof(AppBuffer));
					//uitoa(16,&AppBuffer[0]);
					//UDPPutArray(&AppBuffer[0],2);
					uitoa((WORD)temp,&AppBuffer[0]);
					UDPPutArray(&AppBuffer[0],strlen((char *)AppBuffer));
					UDPPut('-');
					//send the length of ip address
					//UDPPut(sizeof(AppConfig.MyIPAddr));
					//send Voyager source address
					//UDPPutArray((BYTE*)&remoteNode.IPAddr, sizeof(remoteNode.IPAddr));
					memset(&AppBuffer,0x00,sizeof(AppBuffer));
					temp=-1;
					for(c=0;c<4;c++)
					{
					uitoa((WORD)remoteNode.IPAddr.v[c],&AppBuffer[temp+1]);
					temp=strlen((char *)AppBuffer);
					AppBuffer[temp]='.'; 	
					}
					temp=strlen((char *)AppBuffer);
					UDPPutArray(&AppBuffer[0],(WORD)temp);
					UDPPut('-');
					memset(&AppBuffer,0x00,sizeof(AppBuffer));
					//send port to use address
					//temp.word=UDP_VOYAGER_PORT;
					//UDPPutArray(&temp.bytes[0],sizeof(UDP_VOYAGER_PORT));
					uitoa(UDP_VOYAGER_PORT,&AppBuffer[0]);
					UDPPutArray(&AppBuffer[0],4);
								
					//transmit pending UDP packet
					UDPFlush();
					UDPServerState++;
					break;
				case SM_CLOSING:
					UDPClose(MySocket);
					break;
				
			}
		}


void TPCIP_Voyager_Task (void)
	{
	
		WORD w,w2;
		BYTE i;
		WORD wMaxGet, wMaxPut, wCurrentChunk;
		static TCP_SOCKET	MySocket;
		static enum _TCPServerState
		{
			SM_HOME = 0,
			SM_LISTENING,
			SM_CLOSING,
		} TCPServerState = SM_HOME;

	

		switch(TCPServerState)
		{
			case SM_HOME:
				// Allocate a socket for this server to listen and accept connections on
				MySocket = TCPOpen(0, TCP_OPEN_SERVER, TCP_VOYAGER_PORT, TCP_PURPOSE_GENERIC_TCP_SERVER);
				if(MySocket == INVALID_SOCKET)
					return;
	
				TCPServerState = SM_LISTENING;
				break;
	
			case SM_LISTENING:
				// See if anyone is connected to us
				if(!TCPIsConnected(MySocket))
					return;
	
	
				// Figure out how many bytes have been received and how many we can transmit.
				wMaxGet = TCPIsGetReady(MySocket);	// Get TCP RX FIFO byte count
				wMaxPut = TCPIsPutReady(MySocket);	// Get TCP TX FIFO free space
	
				// Make sure we don't take more bytes out of the RX FIFO than we can put into the TX FIFO
				if(wMaxPut < wMaxGet)
					wMaxGet = wMaxPut;
	
				// Process all bytes that we can
				// This is implemented as a loop, processing up to sizeof(AppBuffer) bytes at a time.  
				// This limits memory usage while maximizing performance.  Single byte Gets and Puts are a lot slower than multibyte GetArrays and PutArrays.
	
				wCurrentChunk = sizeof(ModBus_DataRx);
				for(w = 0; w < wMaxGet; w += sizeof(ModBus_DataRx))
				{
					// Make sure the last chunk, which will likely be smaller than sizeof(AppBuffer), is treated correctly.
					if(w + sizeof(ModBus_DataRx) > wMaxGet)
						wCurrentChunk = wMaxGet - w;
					memset(&ModBus_DataRx,0x00,sizeof(ModBus_DataRx));
					memset(&ModBus_DataTx,0x00,sizeof(ModBus_DataTx));
					ModBus_DataTx.DataLen=0;
					// Transfer the data out of the TCP RX FIFO and into our local processing buffer.
					TCPGetArray(MySocket, &ModBus_DataRx.bytes[0], wCurrentChunk);
					
					//For Testing Purpose
					for(w2 = 0; w2 < wCurrentChunk; w2++)
					{
					i = ModBus_DataRx.bytes[w2];
					if(i >= 'a' && i <= 'z')
					{
						i -= ('a' - 'A');
						ModBus_DataTx.Data[w2] = i;
						ModBus_DataTx.DataLen++;
					}
                    else if(i == 0x1B)   //escape
                    {
                        TCPServerState = SM_CLOSING;
                    }
				}
				
					// Perform  The Modbus Operation
					//memset(&ModBus_DataTx,0x00,sizeof(ModBus_DataTx));
					//ProcessModBus_TCPIP(&ModBus_DataTx);	

					// Transfer the data out of our local processing buffer and into the TCP TX FIFO.
					TCPPutArray(MySocket, &ModBus_DataTx.Data[0], ModBus_DataTx.DataLen);
					TCPFlush(MySocket);
				}
	
				// No need to perform any flush.  TCP data in TX FIFO will automatically transmit itself after it accumulates for a while.	If you want to decrease latency (at the expense of wasting network bandwidth on TCP overhead), perform and explicit flush via the TCPFlush() API.
				
				//TCPServerState = SM_CLOSING;
				break;
	
			case SM_CLOSING:
				// Close the socket connection.
				TCPClose(MySocket);
	
				TCPServerState = SM_HOME;
				break;
		}
	}


void ProcessModBus_TCPIP(pMODBUSPDU_TX TxBuffer)
{
	 WORDTOBYTE CrcCheck;
	CrcCheck.word=CalcCRC16(&ModBus_DataRx.bytes[0], 6);
	 if(ModBus_DataRx.CRC_Lo==CrcCheck.bytes[0] && ModBus_DataRx.CRC_Hi==CrcCheck.bytes[1]) 
	 	{

			 switch(ModBus_DataRx.Function)
			 {
				 case READ_FUNC:
					  Process_ModbusTCP_ReadFunction(TxBuffer);
					  break;	 
				 case WRITE_FUNC:
					  Process_ModbusTCP_WriteFunction(TxBuffer);
					 break;

			 }
	 	
	  
		}
}
void Process_ModbusTCP_ReadFunction(pMODBUSPDU_TX TxBuffer)
{	
		WORDTOBYTE temp;
		BYTE c,d;
		WORD RegAddress;
		WORD NumOfReg;
		temp.bytes[0]=ModBus_DataRx.RegAddress_Lo;
		temp.bytes[1]=ModBus_DataRx.RegAddress_Hi;
		RegAddress=temp.word;
		
		temp.bytes[0]=ModBus_DataRx.Value_Lo;
		temp.bytes[1]=ModBus_DataRx.Value_Hi;
		NumOfReg=temp.word;

		//if the register address, and number of register is correct then process the read function 
		if( (RegAddress + NumOfReg) <=MAX_NUMBER_OF_REG_FORTCPIP)
			 {
			   c=0;
			   TxBuffer->Data[c]=DUMMY_ADDR_VOYAGER;c++;	//dummy address
			   TxBuffer->Data[c]=READ_FUNC;c++;		//function
 			   TxBuffer->Data[c]=(NumOfReg*2);c++;	//byte count
			   			   
			   for(d=RegAddress;d<RegAddress+NumOfReg;d++)
			   {
						 
					temp.word=*CLSRegister[VoyagerRegTable[d]].RegData;
					TxBuffer->Data[c]=temp.bytes[1];c++;
					TxBuffer->Data[c]=temp.bytes[0];c++; 
					
			   }  
				 
				 temp.word=CalcCRC16(&TxBuffer->Data[0],c-1);
				 TxBuffer->Data[c]=temp.bytes[0];c++;
				 TxBuffer->Data[c]=temp.bytes[1];c++;			 
				 TxBuffer->DataLen=c;
						 
			 }
		else 
			{
				c=0;
				TxBuffer->Data[c]=DUMMY_ADDR_VOYAGER;c++;
				TxBuffer->Data[c]=READ_FUNC;c++;
				TxBuffer->Data[c]=0x03;c++;
				temp.word=CalcCRC16(&TxBuffer->Data[0],c-1);
				TxBuffer->Data[c]=temp.bytes[0];c++;
				TxBuffer->Data[c]=temp.bytes[1];c++; 

		}
	
}
void Process_ModbusTCP_WriteFunction(pMODBUSPDU_TX TxBuffer)
{
		WORDTOBYTE temp;
		BYTE c,d;
		WORD RegAddress;
		WORD Value;
		temp.bytes[0]=ModBus_DataRx.RegAddress_Lo;
		temp.bytes[1]=ModBus_DataRx.RegAddress_Hi;
		RegAddress=temp.word;
		

		//if the register address and the  WR flag is match then  
		if( CLSRegister[VoyagerRegTable[RegAddress]].RegRW==RW_REG)
			 {
				temp.bytes[0]=ModBus_DataRx.Value_Lo;
				temp.bytes[1]=ModBus_DataRx.Value_Hi;
				Value=temp.word;
				
				*(CLSRegister[VoyagerRegTable[RegAddress]].RegData)=Value;
				if( CLSRegister[VoyagerRegTable[RegAddress]].RegType==WORD_EEPROM)
				{
				  EEPROM_MultiWrite (CLSRegister[VoyagerRegTable[RegAddress]].EEPROM_Address, &temp.bytes[0],2);
				  Delay_uS(100);
				}
				for(d=0;d<8;d++)
				{
					TxBuffer->Data[d]=ModBus_DataRx.bytes[d];				 
				}
				TxBuffer->DataLen=8;
			   
			  }
		else
			{
					c=0;
					TxBuffer->Data[c]=DUMMY_ADDR_VOYAGER;c++;
					TxBuffer->Data[c]=WRITE_FUNC;c++;
					TxBuffer->Data[c]=0x03;c++;
					temp.word=CalcCRC16(&TxBuffer->Data[0],c-1);
					TxBuffer->Data[c]=temp.bytes[0];c++;
					TxBuffer->Data[c]=temp.bytes[1];c++; 			
			}
		
	}
	


