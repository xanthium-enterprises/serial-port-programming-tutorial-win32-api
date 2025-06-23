// Writing to Serial Port using Win32 API 
// WriteFile()
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

    printf("\n[ Writing to Serial Port WriteFile() ==>>  ]\n");



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

    
    //Clear both the TX and RX buffer
    PurgeComm(hComm, PURGE_RXCLEAR | PURGE_TXCLEAR); //purge both tx and rx buffer


    //Write to Serial Port 

    //char ch = 'A';
    //DWORD BytesWritten = 0;

    //status = WriteFile( hComm,        // Serial port handle       
    //                    &ch,          // Pointer to the character to be written
    //                    sizeof(ch),   // Size of the byte to be written to the port 
    //                    &BytesWritten,// bytes written to the port
    //                    NULL);

    //if (status == TRUE)
    //    printf("\n %d Bytes Written To Serial Port ", BytesWritten);
    //else
    //    printf("\nError in Writing Bytes to Serial Port");

    const char* message = "Hello World";
    DWORD BytesWritten = 0;

    status = WriteFile(hComm,            // Serial port handle       
                      message,           // Pointer to the character to be written
                      strlen(message),   // Size of the byte to be written to the port 
                      &BytesWritten,     // bytes written to the port
                      NULL);

    if (status == TRUE)
        printf("\n%d Bytes Written To Serial Port ", BytesWritten);
    else
        printf("\nError in Writing Bytes to Serial Port");


   
    




    CloseHandle(hComm);//Closing the Serial Port
    printf("\n\n+---------------------------------------------+");
    printf("\n\n");

    return 0;
}

