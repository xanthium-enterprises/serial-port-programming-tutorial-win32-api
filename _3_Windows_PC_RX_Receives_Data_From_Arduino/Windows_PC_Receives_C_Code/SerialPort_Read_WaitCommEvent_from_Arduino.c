// Reading from Serial Port using WaitCommEvent()
// Event Driven Serial Port Reading using Win32 API 
// 
//(c) 2025 www.xanthium.in



#include <Windows.h>
#include <stdio.h>

int main()
{
    HANDLE hComm;
    DWORD  win32_error_code;   // variable to store error



    printf("\n+---------------------------------------------+");
    printf("\n|  Win32 Serial Port Programming using C/C++  |");
    printf("\n+---------------------------------------------+");
    printf("\n| (C) 2025    www.xanthium.in                 |");
    printf("\n+---------------------------------------------+");

    printf("\n[ Reading from Serial Port using EVENTS <==  ]\n");



    hComm = CreateFile(L"\\\\.\\COM3",                 // port name
        GENERIC_READ | GENERIC_WRITE, // Read/Write
        0,                            // No Sharing
        NULL,                         // No Security
        OPEN_EXISTING,                // Open existing port only
        0,                            // Non Overlapped I/O
        NULL);                        // Null for Comm Devices

    if (hComm == INVALID_HANDLE_VALUE)
        printf("\nError in opening serial port. Error code: %lu\n", GetLastError());
    else
        printf("\nOpening serial port COM3 successful\n");

    //Opening Serial Port will reset the Arduino 
    Sleep(1000); // Wait 2 seconds for Arduino to stabilize

    //Configuring the DCB structure for Serial Comm

    DCB DCB_Struct_Parameter = { 0 }; //Zero out all the DCB struct members before calling GetCommState()

    DCB_Struct_Parameter.DCBlength = sizeof(DCB_Struct_Parameter); // Get the size of the DCB structure using sizeof()
    // update .DCBlength member with that size
    // required by GetCommState()


    BOOL status = GetCommState(hComm, &DCB_Struct_Parameter); // Get the current settings for the port hComm
    // and fill it in the DCB_Struct_Parameter struct

    if (status == FALSE)
        printf("\nError in GetCommState()");
    else
        printf("\nGetCommState() Success");


    // Fill in the DCB with required settings 
    // Set Parameters in 8N1 format,8 data bits ,No Parity, 1 stop bit

    DCB_Struct_Parameter.BaudRate = 9600;       // other rates 4800,19200,38400etc 
    DCB_Struct_Parameter.ByteSize = 8;          // data word length = 8 bits per byte.Common values are 5, 6, 7, or 8
    DCB_Struct_Parameter.Parity = NOPARITY;     // NOPARITY, ODDPARITY, EVENPARITY, MARKPARITY, or SPACEPARITY
    DCB_Struct_Parameter.StopBits = ONESTOPBIT; // ONESTOPBIT, ONE5STOPBITS, or TWOSTOPBITS

    status = SetCommState(hComm, &DCB_Struct_Parameter); //update the changed parameters to dcb 

    if (status == FALSE)
        printf("\nError in SetCommState()");
    else
        printf("\nSetCommState() Success");

    // Setting Read Time outs for Serial Read operation.

    COMMTIMEOUTS timeouts = { 0 }; //Zero out the COMMTIMEOUTS structure

    timeouts.ReadIntervalTimeout = 20;        // Max time between bytes (ms)
    timeouts.ReadTotalTimeoutMultiplier = 1;  // Per-byte timeout
    timeouts.ReadTotalTimeoutConstant = 50;   // Constant timeout (ms)

    timeouts.WriteTotalTimeoutMultiplier = 1; // Per-byte timeout
    timeouts.WriteTotalTimeoutConstant = 50;  // Constant timeout (ms)

    if (SetCommTimeouts(hComm, &timeouts) == FALSE) //finally set the timeouts
        printf("\nerror in setting timeouts");
    else
        printf("\ntimeout set OK");


    //Clear both the TX and RX buffer
    PurgeComm(hComm, PURGE_RXCLEAR | PURGE_TXCLEAR); //purge both tx and rx buffer




    //Reading from Serial Port using WaitCommEvent()

    //BOOL status;
    DWORD bytesRead;
    char  receive_data_buffer[128] = { 0 }; // intialize the buffer 

   
    status = SetCommMask(hComm, EV_RXCHAR);  // Set mask to listen for data received (EV_RXCHAR)

    if (status == TRUE)
        printf("\n\nSetCommMask() Successfull");
    else 
        printf("\nSetCommMask() Failure");

    printf("\nWaiting for Arduino to Send Some data ");
    printf("\nRESET Arduino to Send Some data ");

    //Wait for the event to happen 
    DWORD EventMask;

    status = WaitCommEvent(hComm, &EventMask, NULL);

    if (status == TRUE)
        printf("\nAn Event Happened");
        
        if (EventMask & EV_RXCHAR)  //Check received bitmask with EV_RXCHAR
         {
             ReadFile(  hComm,                      // File handle of the opened COM port
                        receive_data_buffer,        // Pointer to the buffer that receives the data read from the device.
                        sizeof(receive_data_buffer),// size of the data
                        &bytesRead,                 // Pointer to a variable that receives the number of bytes read
                        NULL);                      // If NULL, the function is blocking.
           
             if (bytesRead > 0)
            {
                printf("\n\nReceived Data        -> %s", receive_data_buffer);
                printf("\nNo of Bytes Received -> %d", bytesRead);
                
            }

         }
        
    else
        printf("\nWaitCommEvent() Failure");


    




    CloseHandle(hComm);//Closing the Serial Port
    printf("\n\n+---------------------------------------------+");
    printf("\n\n");

    return 0;
}

