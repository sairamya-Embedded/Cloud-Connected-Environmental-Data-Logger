#include <LPC214x.h>
#include "types.h"
#include "delay.h"
#include "uart0.h"
#include "esp01.h"
#include <stdio.h>
#include <string.h>

/************ WiFi Details ************/
#define WIFI_SSID      "YOUR_WIFI_NAME"
#define WIFI_PASSWORD  "YOUR_WIFI_PASSWORD"

/************ ThingSpeak ************/
#define API_KEY        "YOUR_API_KEY"

/************ Send AT Command ************/
void ESP01_SendCmd(s8 *cmd)
{
    UART0_TxString((s8 *)cmd);
    UART0_TxString("\r\n");
    delay_ms(2000);
}

/************ Initialize ESP01 ************/
void ESP01_Init(void)
{
    delay_ms(3000);

    ESP01_SendCmd("AT");
    ESP01_SendCmd("ATE0");
    ESP01_SendCmd("AT+CWMODE=1");

    ESP01_ConnectWiFi();
}

/************ Connect WiFi ************/
void ESP01_ConnectWiFi(void)
{
    UART0_TxString("AT+CWJAP=\"");
    UART0_TxString(WIFI_SSID);
    UART0_TxString("\",\"");
    UART0_TxString(WIFI_PASSWORD);
    UART0_TxString("\"\r\n");

    delay_ms(8000);
}

/************ Start TCP ************/
void ESP01_StartTCP(void)
{
    ESP01_SendCmd("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");
    delay_ms(3000);
}

/************ Stop TCP ************/
void ESP01_StopTCP(void)
{
    ESP01_SendCmd("AT+CIPCLOSE");
}

/************ Clear Buffer ************/
void ESP01_ClearBuffer(void)
{
    while(U0LSR & 0x01)
    {
        volatile char dummy = U0RBR;
        (void)dummy;
    }
}

/************ Upload Data ************/
void ESP01_SendThingSpeak(u16 temp, u8 gas)
{
    s8 cmd[120];

    sprintf((char *)cmd,
      "GET /update?api_key=%s&field1=%d&field2=%d\r\n",
      API_KEY,
     temp,
     gas);

    UART0_TxString("AT+CIPSEND=");
    UART0_TxNumber((u32)strlen((char *)cmd));
    UART0_TxString("\r\n");

    delay_ms(2000);

    UART0_TxString(cmd);

    delay_ms(5000);

    ESP01_StopTCP();
}
