/* 
 * File:   osc.h
 * Author: AC3_Studio
 *
 * Created on 21 février 2017, 15:58
 */

#ifndef OSC_H
#define	OSC_H

/*ADRESSE*/
uint16_t TCPIP_UDP_OSC_AddPath(UDP_SOCKET s, const char * path);
uint16_t TCPIP_UDP_OSC_EndPath(UDP_SOCKET s);

uint16_t TCPIP_UDP_OSC_Path(UDP_SOCKET s, const char * path);

/*TYPE*/
uint16_t TCPIP_UDP_OSC_AddTypeInt32(UDP_SOCKET s);
uint16_t TCPIP_UDP_OSC_AddTypeString(UDP_SOCKET s);
uint16_t TCPIP_UDP_OSC_AddTypeFloat(UDP_SOCKET s);
uint16_t TCPIP_UDP_OSC_EndType(UDP_SOCKET s);

uint16_t TCPIP_UDP_OSC_Type(UDP_SOCKET s, const char * type);

/*DONNEES*/
/*EMISSION*/
uint16_t TCPIP_UDP_OSC_AddFloat(UDP_SOCKET s, float input);
uint16_t TCPIP_UDP_OSC_AddInt32(UDP_SOCKET s, long input);
uint16_t TCPIP_UDP_OSC_AddString(UDP_SOCKET s, const char * fmt);
uint16_t TCPIP_UDP_OSC_EndData(UDP_SOCKET s)

uint16_t TCPIP_UDP_OSC_AddArrayFloat(UDP_SOCKET s, float * buf, uint16_t lenght);
uint16_t TCPIP_UDP_OSC_AddArrayInt32(UDP_SOCKET s, uint32_t * buf, uint16_t lenght);
        
uint16_t TCPIP_UDP_OSC_Print(UDP_SOCKET s, const char *fmt, ...);
uint16_t TCPIP_UDP_OSC_Println(UDP_SOCKET s, const char *fmt, ...);
uint16_t TCPIP_UDP_OSC_Flush(UDP_SOCKET s);


/*RECEPTION*/
int16_t TCPIP_UDP_OSC_GetLenghtPath(void);
int16_t TCPIP_UDP_OSC_GetLenghtType(void);
int16_t TCPIP_UDP_OSC_GetLenghtData(void);
int16_t TCPIP_UDP_OSC_Decoder(UDP_SOCKET s, int16_t lenght);
int16_t TCPIP_UDP_OSC_RawDecoder(void);
char * TCPIP_UDP_OSC_GetPath(void);
int32_t TCPIP_UDP_OSC_GetInt32(uint16_t p);
int16_t TCPIP_UDP_OSC_GetArrayInt32(int32_t * buf, uint16_t start, uint16_t end);
float TCPIP_UDP_OSC_GetFloat(uint16_t p);
int16_t TCPIP_UDP_OSC_GetArrayFloat(float * buf, uint16_t start, uint16_t end);
char * TCPIP_UDP_OSC_GetString(char * buf, uint16_t p);

int16_t TCPIP_UDP_OSC_CmpPath(const char * fmt);

#endif	/* OSC_H */

