// Serial Port code for Configuring the DCB Structure
// Configure the Serial Port to work in 8N1 mode.

//(c) 2025 www.xanthium.in



#include <Windows.h>
#include <stdio.h>

int main()
{
    HANDLE hComm;
    DWORD  win32_error_code;   // variable to store error

    hComm = CreateFileA("\\\\.\\COM3",                 // port name
                        GENERIC_READ | GENERIC_WRITE, // Read/Write
                        0,                            // No Sharing
                        NULL,                         // No Security
                        OPEN_EXISTING,                // Open existing port only
                        0,                            // Non Overlapped I/O
                        NULL);                        // Null for Comm Devices

    if (hComm == INVALID_HANDLE_VALUE)
        printf("\nError in opening serial port. Error code: %lu\n", GetLastError());
    else
        printf("Opening serial port successful\n");


    //Configuring the DCB structure for Serial Comm

    DCB DCB_Struct_Parameter = {0}; //Zero out all the DCB struct members before calling GetCommState()
    
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
    DCB_Struct_Parameter.Parity   = NOPARITY;   // NOPARITY, ODDPARITY, EVENPARITY, MARKPARITY, or SPACEPARITY
    DCB_Struct_Parameter.StopBits = ONESTOPBIT; // ONESTOPBIT, ONE5STOPBITS, or TWOSTOPBITS

    status = SetCommState(hComm, &DCB_Struct_Parameter); //update the changed parameters to dcb 

    if (status == FALSE)
        printf("\nError in SetCommState()");
    else
        printf("\nSetCommState() Success");



    CloseHandle(hComm);//Closing the Serial Port

    printf("\n\n");

    return 0;
}

