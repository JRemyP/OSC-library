/* 
 * File:   osc.h
 * Author: AC3_Studio
 *
 * Created on 21 février 2017, 15:58
 */

#ifndef OSC_H
#define	OSC_H

#define kTagInt32   'i'
#define kTagFloat   'f'
#define kTagString  's'
#define kTagBlob    'b'

#define kTagMidi    'm'
#define kTagRgba    'r'

#define kTagTrue    'T'
#define kTagFalse   'F'

typedef union{
    struct{
        uint8_t b3;
        uint8_t b2;
        uint8_t b1;
        uint8_t b0;
    };
    float f;
}floatosc_t;

typedef union{
    struct{
        uint8_t b3;
        uint8_t b2;
        uint8_t b1;
        uint8_t b0;
    };
    int32_t l;
}int32osc_t;

typedef struct{
    struct{
       char * s; 
       uint16_t lenght;
    }path;
    struct{
       char * s;
       uint16_t lenght;
    }type;
    struct{
       char * s; 
       uint16_t lenght;
    }data;
}msgOsc_t;

/*VARIBLES*/
extern int16_t TxOscPathLenght;
extern int16_t TxOscTypeLenght;
extern int16_t TxOscDataLenght;
extern int16_t p_TxOscPath;
extern int16_t p_TxOscType;
extern int16_t p_TxOscData;

extern int16_t RxOscPathLenght;
extern int16_t RxOscTypeLenght;
extern int16_t RxOscDataLenght;
extern int16_t p_RxOscPath;
extern int16_t p_RxOscType;
extern int16_t p_RxOscData;

extern uint8_t * MsgOsc;
extern int16_t OSCLenght;

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

#endif	/* OSC_H */

