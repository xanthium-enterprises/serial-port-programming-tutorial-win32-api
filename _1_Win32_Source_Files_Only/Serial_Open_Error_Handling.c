// 
// Sample code to open a connection to serial port using Win32 API 
// Error Handling code to give more descriptive information
// 
// Change Port number to suit your System
// (c) 2025 www.xanthium.in

// This code will also Compile without errors ,since COM3 s less than 10
// hComm = CreateFileA("COM3",                        // no need to add \\ since port number COM3 < 9
//                      GENERIC_READ | GENERIC_WRITE, //Read/Write
                       //
//                     );



#include <Windows.h>
#include <stdio.h>

int main()
{
    HANDLE hComm;
    DWORD  win32_error_code;        //variable to store error,Double Word ,4 bytes (32 bits),
    CHAR   error_message[256];      //Character array to store error messages

    hComm = CreateFileA("\\\\.\\COM3",                 // port name
        GENERIC_READ | GENERIC_WRITE, // Read/Write
        0,                            // No Sharing
        NULL,                         // No Security
        OPEN_EXISTING,                // Open existing port only
        0,                            // Non Overlapped I/O
        NULL);                        // Null for Comm Devices

    if (hComm == INVALID_HANDLE_VALUE)
    {
        printf("\nError in opening serial port\n");

        //Error handling code 
        win32_error_code = GetLastError(); //returns the error code for the last system error 
        
        //turn error code into messages 
        FormatMessageA( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL,
                        win32_error_code,     // error codeto be converted ,integer value like 2
                        0,                    // Language ID (0 = system default)
                        error_message,        // buffer where the error message will be stored
                        sizeof(error_message),
                        NULL
                     );
        printf("\nERROR : %s",error_message);
    }
        

    else
    {
        printf("Opening serial port successful\n\n");
    }
        

    
    CloseHandle(hComm);//Closing the Serial Port

    return 0;
}