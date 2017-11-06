# OSC-library
Little OSC library MPLAB v4.01 &amp; Harmony v2.04 
Works also with MPLAB v3.54 &amp; Harmony v1.10

You must know how OSC works.

This library is work in progress.

## Installation
Add all files in tcpip folder respectly in ../microchip/harmony/V2.04/framework/tcpip

## Create a new project
In MPLAB, make a new harmony project. 
In Harmony toolkit, select *option* tab. 
Open *Harmony Framework configuration*, thus *TCP/IP Stack* and select *Use TCP/IP Stack ?*
Save this harmony configuration and generate the code.

## Add Library to your project
In MPLAB, in your project tree, open *Header Files/framework* and right-clic on *tcpip* and select **osc.h**
Now, open *tcpip* and right-clic on *src* to add **osc_private.h**
Go Back in your project tree, and open *Source Files/framework* right-clic on *tcpip* and add **osc.c**

## How to use
In each OSC-message there are a path like */MyMessage* followed by types like integer, float or String and followed by data.

To send a message with 3 integers, you must write :

var1=5000;
var2=10000;
char* msg[12]="Hello World";

TCPIP_UDP_OSC_AddPath(udpSocket, "/MyIntergers");

/*add types*/

TCPIP_UDP_OSC_AddTypeInt32(udpSocket);

TCPIP_UDP_OSC_AddTypeInt32(udpSocket);

TCPIP_UDP_OSC_AddTypeString(udpSocket);

TCPIP_UDP_OSC_EndType(udpSocket);

/*add values*/

TCPIP_UDP_OSC_AddInt32(udpSocket, var1);

TCPIP_UDP_OSC_AddInt32(udpSocket, var2);

TCPIP_UDP_OSC_AddString(udpSocket, msg);

TCPIP_UDP_OSC_EndData(udpSocket);

/*send data*/

TCPIP_UDP_OSC_Flush(udpSocket);

## Prototypes
uint16_t TCPIP_UDP_OSC_AddPath(UDP_SOCKET s, const char * path);

uint16_t TCPIP_UDP_OSC_EndPath(UDP_SOCKET s);

uint16_t TCPIP_UDP_OSC_AddTypeInt32(UDP_SOCKET s);

uint16_t TCPIP_UDP_OSC_AddTypeString(UDP_SOCKET s);

uint16_t TCPIP_UDP_OSC_AddTypeFloat(UDP_SOCKET s);

uint16_t TCPIP_UDP_OSC_EndType(UDP_SOCKET s);

uint16_t TCPIP_UDP_OSC_AddFloat(UDP_SOCKET s, float input);

uint16_t TCPIP_UDP_OSC_AddInt32(UDP_SOCKET s, long input);

uint16_t TCPIP_UDP_OSC_AddString(UDP_SOCKET s, const char * fmt);

uint16_t TCPIP_UDP_OSC_EndData(UDP_SOCKET s);

uint16_t TCPIP_UDP_OSC_Flush(UDP_SOCKET s);

uint16_t TCPIP_UDP_OSC_Print(UDP_SOCKET s, const char *fmt, ...);

uint16_t TCPIP_UDP_OSC_Println(UDP_SOCKET s, const char *fmt, ...);

int16_t TCPIP_UDP_OSC_GetLenghtPath(void);

int16_t TCPIP_UDP_OSC_GetLenghtType(void);

int16_t TCPIP_UDP_OSC_GetLenghtData(void);

char * TCPIP_UDP_OSC_GetPath(void);

char * TCPIP_UDP_OSC_GetType(void);

int32_t TCPIP_UDP_OSC_GetInt32(uint16_t p);

int16_t TCPIP_UDP_OSC_GetArrayInt32(int32_t * buf, uint16_t start, uint16_t end);

int16_t TCPIP_UDP_OSC_GetArrayFloat(float * buf, uint16_t start, uint16_t end);

float TCPIP_UDP_OSC_GetFloat(uint16_t p);

char * TCPIP_UDP_OSC_GetString(uint16_t p);

int16_t TCPIP_UDP_OSC_Decoder(void);

int16_t TCPIP_UDP_OSC_GetIsReady(UDP_SOCKET s);

