/* 
 * File:   osc.h
 * Author: AC3_Studio
 *
 * Created on 21 février 2017, 15:58
 */

#ifndef OSC_H
#define	OSC_H

void TCPIP_UDP_OSC_AddPath(UDP_SOCKET s, const uint8_t * path, uint16_t wDataLen);
uint16_t TCPIP_UDP_OSC_EndPath(UDP_SOCKET s, uint16_t wDataLen);
uint16_t TCPIP_UDP_OSC_AddTypeInt32(UDP_SOCKET s);
uint16_t TCPIP_UDP_OSC_AddTypeString(UDP_SOCKET s);
uint16_t TCPIP_UDP_OSC_AddTypeFloat(UDP_SOCKET s);
uint16_t TCPIP_UDP_OSC_EndType(UDP_SOCKET s, uint8_t nbType);
uint16_t TCPIP_UDP_OSC_AddFloat(UDP_SOCKET s, float input);
uint16_t TCPIP_UDP_OSC_AddString(UDP_SOCKET s, const uint8_t* fmt, uint16_t wDataLen);

#endif	/* OSC_H */

