/*Fichier compatible avec Harmony */

#include "tcpip/src/tcpip_private.h"
#include "udp_private.h"
#include "osc_private.h"

int16_t TxOscPathLenght=0;
int16_t TxOscTypeLenght=0;
int16_t TxOscDataLenght=0;
int16_t p_TxOscPath=0;
int16_t p_TxOscType=0;
int16_t p_TxOscData=0;

int16_t RxOscPathLenght=0;
int16_t RxOscTypeLenght=0;
int16_t RxOscDataLenght=0;
int16_t p_RxOscPath=0;
int16_t p_RxOscType=0;
int16_t p_RxOscData=0;

uint8_t * MsgOsc;
int16_t OSCLenght;

/*ADRESSES*/
uint16_t TCPIP_UDP_OSC_AddPath(UDP_SOCKET s, const char * path)
{
    uint16_t lenght=0;
    lenght = strlen(path);
    TxOscPathLenght += lenght;
    return TCPIP_UDP_ArrayPut(s,(const uint8_t *)(path),lenght);
}

uint16_t TCPIP_UDP_OSC_EndPath(UDP_SOCKET s)
{
    uint16_t lenght=0;
    const uint8_t virgule=',';
    
    TxOscPathLenght&=3;
    TxOscPathLenght=4-TxOscPathLenght;
    while(TxOscPathLenght--){
        lenght+=TCPIP_UDP_Put(s,NULL);
    }
    TxOscPathLenght=0;
    lenght+=TCPIP_UDP_ArrayPut(s,&virgule,1);
    TxOscTypeLenght++;
    return lenght;
}


/*TYPES*/
uint16_t TCPIP_UDP_OSC_AddTypeInt32(UDP_SOCKET s)
{
    TxOscTypeLenght++;
    return TCPIP_UDP_Put(s,(uint8_t)('i'));
}

uint16_t TCPIP_UDP_OSC_AddTypeString(UDP_SOCKET s)
{
    TxOscTypeLenght++;
    return TCPIP_UDP_Put(s,(uint8_t)('s'));
}

uint16_t TCPIP_UDP_OSC_AddTypeFloat(UDP_SOCKET s)
{
    TxOscTypeLenght++;
    return TCPIP_UDP_Put(s,(uint8_t)('f'));
}

uint16_t TCPIP_UDP_OSC_EndType(UDP_SOCKET s)
{
    uint16_t lenght=0;
    
    TxOscTypeLenght&=3;
    TxOscTypeLenght=4-TxOscTypeLenght;
    while(TxOscTypeLenght--){
        lenght+=TCPIP_UDP_Put(s,NULL);
    }
    TxOscTypeLenght=0;
    return lenght;
}


/*DONNEES*/
uint16_t TCPIP_UDP_OSC_AddFloat(UDP_SOCKET s, float input)
{
    floatosc_t data;
    uint16_t lenght=0;
    data.f = input;
    lenght+=TCPIP_UDP_Put(s,data.b0);
    lenght+=TCPIP_UDP_Put(s,data.b1);
    lenght+=TCPIP_UDP_Put(s,data.b2);
    lenght+=TCPIP_UDP_Put(s,data.b3);
    TxOscDataLenght += 4;
    return lenght;
}

uint16_t TCPIP_UDP_OSC_AddInt32(UDP_SOCKET s, long input)
{
    int32osc_t data;
    uint16_t lenght=0;
    data.l = input;
    lenght+=TCPIP_UDP_Put(s,data.b0);
    lenght+=TCPIP_UDP_Put(s,data.b1);
    lenght+=TCPIP_UDP_Put(s,data.b2);
    lenght+=TCPIP_UDP_Put(s,data.b3);
    TxOscDataLenght += 4;
    return lenght;
}

uint16_t TCPIP_UDP_OSC_AddString(UDP_SOCKET s, const char * fmt)
{
    uint16_t lenght=0;
    
    lenght = strlen(fmt);
    TxOscDataLenght += lenght;
    
    return TCPIP_UDP_ArrayPut(s,(const uint8_t* )(fmt),lenght);
}   
    
uint16_t TCPIP_UDP_OSC_EndData(UDP_SOCKET s)
{
    uint16_t lenght=0;
    
    TxOscDataLenght&=0x0003;
    TxOscDataLenght=4-TxOscDataLenght;
    
    while(TxOscDataLenght--){
        lenght+=TCPIP_UDP_Put(s,NULL);
    }
    TxOscDataLenght=0;
    return lenght;
   
}

uint16_t TCPIP_UDP_OSC_Print(UDP_SOCKET s, const char *fmt, ...)
{
    uint16_t lenght=0;
    char * buf;
    
    va_list ap;
    va_start(ap, fmt);
	buf = (char *)malloc(sizeof(fmt)+sizeof(ap)*12);
    vsprintf (buf, fmt, ap);
    va_end(ap);
    
    lenght+=TCPIP_UDP_OSC_AddString(s,buf);

    free(buf);
    
    return lenght;
}

uint16_t TCPIP_UDP_OSC_Println(UDP_SOCKET s, const char *fmt, ...)
{
    uint16_t lenght=0;
    char * buf;

    va_list ap;
    va_start(ap, fmt);
	buf = (char *)malloc(sizeof(fmt)+sizeof(ap)*12);
    vsprintf (buf, fmt, ap);
    va_end(ap);
    
    lenght+=TCPIP_UDP_OSC_AddString(s,buf);
    lenght+=TCPIP_UDP_Put(s,0x0A); TxOscDataLenght++; //pour le "/n" 
    
    free(buf);
    
    return lenght;
}

uint16_t TCPIP_UDP_OSC_Flush(UDP_SOCKET s)
{
    return TCPIP_UDP_Flush(s);
}



int16_t TCPIP_UDP_OSC_GetLenghtPath(void)
{
    int16_t completude;
    
    int8_t * buf = MsgOsc;
    
    p_RxOscPath=0;
    
    RxOscPathLenght=strlen(buf);
    
    if(RxOscPathLenght>OSCLenght) return 0;
    
    p_RxOscType=RxOscPathLenght;
    completude=p_RxOscType;    
    completude&=3;
    completude=4-completude;
    while( completude-- ){
        p_RxOscType++;
    }
    
    return RxOscPathLenght;
}

/*La fonction TCPIP_UDP_OSC_GetAddr doit être executer avant.*/
int16_t TCPIP_UDP_OSC_GetLenghtType(void)
{
    int16_t completude;
    int8_t * buf = MsgOsc;
    
    buf+=(char)(p_RxOscType);
    
    RxOscTypeLenght=strlen(buf);
    
    if((p_RxOscPath+RxOscTypeLenght)>OSCLenght) return 0;

    p_RxOscData=p_RxOscType+RxOscTypeLenght;
    completude=RxOscTypeLenght;
    completude&=3;
    completude=4-completude;
    while( completude-- ){
        p_RxOscData++;
    }
    
    return RxOscTypeLenght;
}

int16_t TCPIP_UDP_OSC_GetLenghtData(void)
{
    
    if( (OSCLenght-p_RxOscData) <0) return 0;
    
    RxOscDataLenght=OSCLenght-p_RxOscData;
 
    return RxOscDataLenght;
}

int16_t TCPIP_UDP_OSC_Decoder(void)
{
    if(OSCLenght==0){return 0;}
    
    if(MsgOsc[0]=='/'){
        TCPIP_UDP_OSC_GetLenghtPath();
    }
    else{return -1;}
    
    if(OSCLenght<(RxOscPathLenght+2)){return -2;}  //+2 pour la virgule et au moins un type
    
    if(MsgOsc[p_RxOscType]==','){
        TCPIP_UDP_OSC_GetLenghtType();
    }
    
    if(OSCLenght<(p_RxOscData+1)){return -3;} //+1 pour avoir au moins une donnée (un caractère dans un string)
    
    TCPIP_UDP_OSC_GetLenghtData();
    
    return 1;
}

char * TCPIP_UDP_OSC_GetPath(void)
{
    return MsgOsc+p_RxOscPath;
}

char * TCPIP_UDP_OSC_GetType(void)
{
    return MsgOsc+p_RxOscType;
}

int32_t TCPIP_UDP_OSC_GetInt32(uint16_t p)
{
    int32osc_t int32Osc;
    p*=4;
    p+=p_RxOscData;
    int32Osc.b0=MsgOsc[p++];
    int32Osc.b1=MsgOsc[p++];
    int32Osc.b2=MsgOsc[p++];
    int32Osc.b3=MsgOsc[p];
    return int32Osc.l;
}

int16_t TCPIP_UDP_OSC_GetArrayInt32(int32_t * buf, uint16_t start, uint16_t end)
{
    uint16_t i;
    if(start>end){return -1;}   
    for(i=start; i<=end; i++)
    {
        buf[i]=TCPIP_UDP_OSC_GetInt32(i);
    }
    return 0;
}

float TCPIP_UDP_OSC_GetFloat(uint16_t p)
{
    floatosc_t floatOsc;
    p*=4;
    p+=p_RxOscData;
    floatOsc.b0=MsgOsc[p++];
    floatOsc.b1=MsgOsc[p++];
    floatOsc.b2=MsgOsc[p++];
    floatOsc.b3=MsgOsc[p];
    return floatOsc.f;
}

int16_t TCPIP_UDP_OSC_GetArrayFloat(float * buf, uint16_t start, uint16_t end)
{
    uint16_t i;
    if(start>end){return -1;}
    for(i=start; i<=end; i++)
    {
        buf[i]=TCPIP_UDP_OSC_GetFloat(i);
    }
    return 0;
}

char * TCPIP_UDP_OSC_GetString(uint16_t p)
{
    return 0;
}

int16_t TCPIP_UDP_OSC_GetIsReady(UDP_SOCKET s)
{
    OSCLenght = TCPIP_UDP_GetIsReady(s);
    if(OSCLenght == 0)
    {
        return 0;
    }
    free(MsgOsc);
    MsgOsc=(uint8_t *)malloc(OSCLenght);
    
    TCPIP_UDP_ArrayGet(s, MsgOsc, OSCLenght);
    TCPIP_UDP_OSC_Decoder();
    
    return OSCLenght;
}