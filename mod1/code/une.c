#include <stdio.h>

// UTF-32 Encoding and Decoding
void utf32_encode(unsigned int U, unsigned char* out) {
    out[0] = U & 0xFF;
    out[1] = (U >> 8) & 0xFF;
    out[2] = (U >> 16) & 0xFF;
    out[3] = (U >> 24) & 0xFF;
}

unsigned int utf32_decode(unsigned char* byte_array) {
    return byte_array[0] | (byte_array[1] << 8) | (byte_array[2] << 16) | (byte_array[3] << 24);
}

// UTF-16 Encoding and Decoding
int utf16_encode(unsigned int U, unsigned char* out) {
    if (U <= 0xFFFF) {
        out[0] = U & 0xFF;
        out[1] = (U >> 8) & 0xFF;
        return 2;
    } else {
        unsigned int high_surrogate = 0xD800 | ((U - 0x10000) >> 10);
        unsigned int low_surrogate = 0xDC00 | ((U - 0x10000) & 0x3FF);
        out[0] = high_surrogate & 0xFF;
        out[1] = (high_surrogate >> 8) & 0xFF;
        out[2] = low_surrogate & 0xFF;
        out[3] = (low_surrogate >> 8) & 0xFF;
        return 4;
    }
}

unsigned int utf16_decode(unsigned char* byte_array, int length) {
    if (length == 2) {
        return byte_array[0] | (byte_array[1] << 8);
    } else if (length == 4) {
        unsigned int high_surrogate = (byte_array[0] | (byte_array[1] << 8)) - 0xD800;
        unsigned int low_surrogate = (byte_array[2] | (byte_array[3] << 8)) - 0xDC00;
        return (high_surrogate << 10) | low_surrogate + 0x10000;
    }
    return 0;
}

// UTF-8 Encoding and Decoding
int utf8_encode(unsigned int U, unsigned char* out) {
    if (U <= 0x007F) {
        out[0] = U;
        return 1;
    } else if (U <= 0x07FF) {
        out[0] = 0b11000000 | (U >> 6);
        out[1] = 0b10000000 | (U & 0x3F);
        return 2;
    } else if (U <= 0xFFFF) {
        out[0] = 0b11100000 | (U >> 12);
        out[1] = 0b10000000 | ((U >> 6) & 0x3F);
        out[2] = 0b10000000 | (U & 0x3F);
        return 3;
    } else {
        out[0] = 0b11110000 | (U >> 18);
        out[1] = 0b10000000 | ((U >> 12) & 0x3F);
        out[2] = 0b10000000 | ((U >> 6) & 0x3F);
        out[3] = 0b10000000 | (U & 0x3F);
        return 4;
    }
}

unsigned int utf8_decode(unsigned char* byte_array, int length) {
    unsigned int U = 0;
    if (length == 1) {
        return byte_array[0];
    } else if (length == 2) {
        U = (byte_array[0] & 0x1F) << 6 | (byte_array[1] & 0x3F);
    } else if (length == 3) {
        U = (byte_array[0] & 0x0F) << 12 | (byte_array[1] & 0x3F) << 6 | (byte_array[2] & 0x3F);
    } else if (length == 4) {
        U = (byte_array[0] & 0x07) << 18 | (byte_array[1] & 0x3F) << 12 | (byte_array[2] & 0x3F) << 6 | (byte_array[3] & 0x3F);
    }
    return U;
}

// Testing Function
void test_code_point(unsigned int cp) {
    unsigned char buffer[4];
    
    printf("Testing U+%04X (%lc)\n", cp, cp);
    
    // UTF-32
    utf32_encode(cp, buffer);
    printf("UTF-32 Encoded: [%d %d %d %d]\n", buffer[0], buffer[1], buffer[2], buffer[3]);
    printf("UTF-32 Decoded: U+%04X\n", utf32_decode(buffer));
    
    // UTF-16
    int utf16_len = utf16_encode(cp, buffer);
    printf("UTF-16 Encoded: ");
    for (int i = 0; i < utf16_len; i++) printf("%d ", buffer[i]);
    printf("\n");
    printf("UTF-16 Decoded: U+%04X\n", utf16_decode(buffer, utf16_len));
    
    // UTF-8
    int utf8_len = utf8_encode(cp, buffer);
    printf("UTF-8 Encoded: ");
    for (int i = 0; i < utf8_len; i++) printf("%d ", buffer[i]);
    printf("\n");
    printf("UTF-8 Decoded: U+%04X\n", utf8_decode(buffer, utf8_len));
    
    printf("--------------------------------------\n");
}

// Main Program
int main() {
    unsigned int code_points[] = {0x0041, 0x4E16, 0x754C, 0x1F415};
    int n = sizeof(code_points) / sizeof(code_points[0]);
    for (int i = 0; i < n; i++) {
        test_code_point(code_points[i]);
    }
    return 0;
}
