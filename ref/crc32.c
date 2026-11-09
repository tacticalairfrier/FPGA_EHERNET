//cyclic reduncancy check-32 required for the fcs sequence of the ethernet protocol
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
uint32_t calculateCRC32(uint8_t* data, int size);
uint32_t crctable(uint8_t index);
//crc lookup table logic
uint32_t crctable(uint8_t index) {
    uint32_t crct = index;
    for (uint8_t i = 8; i > 0; i--) {
        crct = (crct & 1) ? ((crct >> 1) ^ 0xedb88320) : (crct >> 1);
    }
    return crct;
}
//crc32 hashing algorithm
uint32_t calculateCRC32(uint8_t* data, int size) {
    uint32_t crc32 = 0xffffffff;
    for (int i = 0; i < size; i++) {
        crc32 ^= data[i];
        crc32 = (crc32 >> 8) ^ crctable(crc32);
    }
    return ~crc32;
}
int main(int argc, char* argv[]) {
    char* endptr;
    if (argv[1] == NULL) {
        printf("no arguments provided\n");
        return 1;
    }
    int bytes = strlen(argv[1]) / 2;
    uint8_t bytearray[bytes];
    for (int fields = 0;fields < bytes; fields++) {
        char byte[2] = { argv[1][2 * fields], argv[1][2 * fields + 1] };
        bytearray[fields] = strtoul(byte, &endptr, 16);
    }
    printf("crc32chksm: %08x\n", calculateCRC32(bytearray, bytes));
    return 0;
}