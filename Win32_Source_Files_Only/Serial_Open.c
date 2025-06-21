// Serial_Open.c
// Sample code to open a connection to serial port using Win32 API 
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

    hComm = CreateFileA("\\\\.\\COM3",                 // port name
                         GENERIC_READ | GENERIC_WRITE, // Read/Write
                         0,                            // No Sharing
                         NULL,                         // No Security
                         OPEN_EXISTING,                // Open existing port only
                         0,                            // Non Overlapped I/O
                         NULL);                        // Null for Comm Devices

    if (hComm == INVALID_HANDLE_VALUE)
        printf("\nError in opening serial port.");
    else
        printf("Opening serial port successful\n\n");

    CloseHandle(hComm);//Closing the Serial Port

    return 0;
}

