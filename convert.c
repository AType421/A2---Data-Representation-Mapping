#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//converts 32 bit to binary
void to_32bit_binary(uint32_t value, char *out) {
    for (int i = 31; i >= 0; i--) {
        out[31 - i] = ((value >> i) & 1) ? '1' : '0';
    }
    out[32] = '\0';
}

void oct_to_bin(const char *oct, char *out) {
    int pos = 0;
    for (int i = 0; oct[i] != '\0'; i++) {
        //converts oct to bin
        int digit = oct[i] - '0';
        out[pos++] = (digit & 4) ? '1' : '0';
        out[pos++] = (digit & 2) ? '1' : '0';
        out[pos++] = (digit & 1) ? '1' : '0';
    }
    out[pos] = '\0';
}

void oct_to_hex(const char *oct, char *out) {
    char bin[256];
    oct_to_bin(oct, bin);

    // Pads binary length
    int len = strlen(bin);
    int pad = (4 - (len % 4)) % 4;
    char padded[260];
    for (int i = 0; i < pad; i++) padded[i] = '0';
    strcpy(padded + pad, bin);

    // Converts 4 bits to hex digits
    int pos = 0;
    for (int i = 0; padded[i]; i += 4) {
        int val = (padded[i] - '0') * 8 +
                  (padded[i + 1] - '0') * 4 +
                  (padded[i + 2] - '0') * 2 +
                  (padded[i + 3] - '0');
        if (val < 10) out[pos++] = '0' + val;
        else out[pos++] = 'A' + (val - 10);
    }
    out[pos] = '\0';
    
    // removes leading zeros
    int first_nonzero = 0;
    while(out[first_nonzero] == '0' && out[first_nonzero + 1] != '\0') first_nonzero++;
    if (first_nonzero > 0){
        memmove(out, out + first_nonzero, strlen(out+ first_nonzero) + 1);
    }

}

void hex_to_bin(const char *hex, char *out) {
    int pos = 0;
    for (int i = 0; hex[i] != '\0'; i++) {
        char c = hex[i];
        int val;
        // converts hex into decimal
        if (c >= '0' && c <= '9') val = c - '0';
        else if (c >= 'A' && c <= 'F') val = 10 + (c - 'A');
        else if (c >= 'a' && c <= 'f') val = 10 + (c - 'a');
        
        //converts decimal to binary
        out[pos++] = (val & 8) ? '1' : '0';
        out[pos++] = (val & 4) ? '1' : '0';
        out[pos++] = (val & 2) ? '1' : '0';
        out[pos++] = (val & 1) ? '1' : '0';
    }
    out[pos] = '\0';
}

void to_sign_magnitude(int32_t n, char *out) {
    if (n >= 0) {
        to_32bit_binary((uint32_t)n, out);
    } else {
        uint32_t mag = (uint32_t)(-n);
        to_32bit_binary(mag, out);
        out[0] = '1'; 
    }
}

void to_ones_complement(int32_t n, char *out) {
    if (n >= 0) {
        to_32bit_binary((uint32_t)n, out);
    } else {
        uint32_t mag = (uint32_t)(-n);
        char temp[33];
        to_32bit_binary(mag, temp);
        for (int i = 0; i < 32; i++) {
            out[i] = (temp[i] == '0') ? '1' : '0';
        }
        out[32] = '\0';
    }
}

void to_twos_complement(int32_t n, char *out) {
    uint32_t val = (uint32_t)n; 
    to_32bit_binary(val, out);
}




