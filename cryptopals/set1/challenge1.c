// Convert hex to base64

#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint8_t hex_to_val(char c);

int main(void)
{
    // 주소값 저장. 배열처럼 쓸수 있음. 배열 시작위치를 가리킴. '\0'저장되어 있는곳이 마지막 주소.
    // const는 안 바꾼다는 약속. 램이아니라 플래시에 저장됨.
    const char *hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";

    // Hex -> Byte 변환
    unsigned int ByteNum = strlen(hex)/2;
    uint8_t bytes[ByteNum];


    for ( int i=0; i < ByteNum; i++)
    {  
        char high = hex[i*2];
        char low = hex[i*2+1];

        // TODO 1,2: high,low 문자를 0~15 숫자로 변환
        // TODO 3: 두 숫자를 합쳐 bytes[i]에 저장
        //bytes[i] = 16*hex_to_val(high) + hex_to_val(low);
        bytes[i] = (hex_to_val(high)<<4) | hex_to_val(low);
    }


    // Byte -> Base64 인코딩
    const char *table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    char out[ByteNum / 3 * 4 + 1];   
    int j = 0;                        

    for (int i = 0; i < ByteNum; i += 3) {   
        uint8_t b0 = bytes[i];
        uint8_t b1 = bytes[i + 1];
        uint8_t b2 = bytes[i + 2];

        out[j]     = table[ b0 >> 2 ];
        out[j + 1] = table[(b0 & 0x03) << 4 | b1 >> 4];
        out[j + 2] = table[(b1 & 0x0F) << 2 | b2 >> 6];
        out[j + 3] = table[ b2 & 0x3F ];
        j += 4;             
    }
    out[j] = '\0';
    printf("Base64: %s\n", out);

    return 0;
}

uint8_t hex_to_val(char c)
{
    if (c >= '0' && c <= '9')
    {
        c -= '0';
    }
    else
    {
        c -= 'a' - 10;
    }
    return c;
}