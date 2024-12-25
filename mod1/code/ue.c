#include <stdio.h>
#include <locale.h>
#include <string.h>

int main() {
    // Set locale for UTF-8 printing
    setlocale(LC_ALL, "en_US.utf8");

    // Original text (Hello, 世界)
    char text[] = "Hello, \u4e16\u754c";
    printf("Original Text: %s\n\n", text);

    // UTF-8 Encoding (already in UTF-8)
    printf("UTF-8 Encoding:\n");
    for (size_t i = 0; i < strlen(text); i++) {
        printf("%02x ", (unsigned char)text[i]);
    }
    printf("\nDecoded (UTF-8): %s\n\n", text);

    // UTF-16 Encoding (Little-endian with BOM)
    printf("UTF-16 Little-endian (with BOM):\n");
    unsigned char utf16_le[256];
    utf16_le[0] = 0xFF;
    utf16_le[1] = 0xFE; // BOM for UTF-16 LE
    size_t index = 2;
    
    // UTF-16 conversion for each UTF-8 character
    for (size_t i = 0; i < strlen(text); i++) {
        unsigned char c = text[i];
        if (c <= 0x7F) {
            // ASCII, 1 byte in UTF-8
            utf16_le[index++] = c & 0xFF;
            utf16_le[index++] = 0x00;
        } else if (c >= 0xC0 && c <= 0xDF) {
            // 2-byte UTF-8 character
            unsigned short utf16_char = ((text[i] & 0x1F) << 6) | (text[i+1] & 0x3F);
            utf16_le[index++] = utf16_char & 0xFF;
            utf16_le[index++] = (utf16_char >> 8) & 0xFF;
            i++;  // Skip next byte for 2-byte UTF-8 character
        } else if (c >= 0xE0 && c <= 0xEF) {
            // 3-byte UTF-8 character
            unsigned short utf16_char = ((text[i] & 0x0F) << 12) | ((text[i+1] & 0x3F) << 6) | (text[i+2] & 0x3F);
            utf16_le[index++] = utf16_char & 0xFF;
            utf16_le[index++] = (utf16_char >> 8) & 0xFF;
            i += 2;  // Skip next two bytes for 3-byte UTF-8 character
        }
    }
    
    for (size_t i = 0; i < index; i++) {
        printf("%02x ", utf16_le[i]);
    }
    printf("\nDecoded (UTF-16 LE): %s\n\n", text);

    // UTF-32 Encoding (Little-endian with BOM)
    printf("UTF-32 Little-endian (with BOM):\n");
    unsigned char utf32_le[256];
    utf32_le[0] = 0xFF;
    utf32_le[1] = 0xFE;
    utf32_le[2] = 0x00;
    utf32_le[3] = 0x00; // BOM for UTF-32 LE
    index = 4;
    
    // UTF-32 conversion for each UTF-8 character
    for (size_t i = 0; i < strlen(text); i++) {
        unsigned char c = text[i];
        if (c <= 0x7F) {
            // ASCII, 1 byte in UTF-8
            utf32_le[index++] = c & 0xFF;
            utf32_le[index++] = 0x00;
            utf32_le[index++] = 0x00;
            utf32_le[index++] = 0x00;
        } else if (c >= 0xC0 && c <= 0xDF) {
            // 2-byte UTF-8 character
            unsigned short utf32_char = ((text[i] & 0x1F) << 6) | (text[i+1] & 0x3F);
            utf32_le[index++] = utf32_char & 0xFF;
            utf32_le[index++] = (utf32_char >> 8) & 0xFF;
            utf32_le[index++] = 0x00;
            utf32_le[index++] = 0x00;
            i++;  // Skip next byte for 2-byte UTF-8 character
        } else if (c >= 0xE0 && c <= 0xEF) {
            // 3-byte UTF-8 character
            unsigned int utf32_char = ((text[i] & 0x0F) << 12) | ((text[i+1] & 0x3F) << 6) | (text[i+2] & 0x3F);
            utf32_le[index++] = utf32_char & 0xFF;
            utf32_le[index++] = (utf32_char >> 8) & 0xFF;
            utf32_le[index++] = (utf32_char >> 16) & 0xFF;
            utf32_le[index++] = (utf32_char >> 24) & 0xFF;
            i += 2;  // Skip next two bytes for 3-byte UTF-8 character
        }
    }
    
    for (size_t i = 0; i < index; i++) {
        printf("%02x ", utf32_le[i]);
    }
    printf("\nDecoded (UTF-32 LE): %s\n", text);

    return 0;
}
