# UTF-32 Encoding and Decoding
def utf32_encode(U):
    return [U & 0xFF, (U >> 8) & 0xFF, (U >> 16) & 0xFF, (U >> 24) & 0xFF]

def utf32_decode(byte_array):
    U = byte_array[0] | (byte_array[1] << 8) | (byte_array[2] << 16) | (byte_array[3] << 24)
    return U

# UTF-16 Encoding and Decoding
def utf16_encode(U):
    if U <= 0xFFFF:
        return [U & 0xFF, (U >> 8) & 0xFF]  # 2 bytes (BMP)
    elif U <= 0x10FFFF:
        high_surrogate = 0xD800 | ((U - 0x10000) >> 10)
        low_surrogate = 0xDC00 | ((U - 0x10000) & 0x3FF)
        return [
            high_surrogate & 0xFF, (high_surrogate >> 8) & 0xFF,
            low_surrogate & 0xFF, (low_surrogate >> 8) & 0xFF
        ]  # 4 bytes (surrogate pair)

def utf16_decode(byte_array):
    U = 0
    if len(byte_array) == 2:  # Single unit (BMP)
        U = byte_array[0] | (byte_array[1] << 8)
    elif len(byte_array) == 4:  # Surrogate pair (for code points ≥ 0x10000)
        high_surrogate = (byte_array[0] | (byte_array[1] << 8)) - 0xD800
        low_surrogate = (byte_array[2] | (byte_array[3] << 8)) - 0xDC00
        U = (high_surrogate << 10) | low_surrogate + 0x10000
    return U

# UTF-8 Encoding and Decoding
def utf8_encode(U):
    if U <= 0x007F:  # 1 byte (ASCII)
        return [U]
    elif U <= 0x07FF:  # 2 bytes
        byte1 = 0b11000000 | (U >> 6)
        byte2 = 0b10000000 | (U & 0x3F)
        return [byte1, byte2]
    elif U <= 0xFFFF:  # 3 bytes
        byte1 = 0b11100000 | (U >> 12)
        byte2 = 0b10000000 | ((U >> 6) & 0x3F)
        byte3 = 0b10000000 | (U & 0x3F)
        return [byte1, byte2, byte3]
    elif U <= 0x10FFFF:  # 4 bytes
        byte1 = 0b11110000 | (U >> 18)
        byte2 = 0b10000000 | ((U >> 12) & 0x3F)
        byte3 = 0b10000000 | ((U >> 6) & 0x3F)
        byte4 = 0b10000000 | (U & 0x3F)
        return [byte1, byte2, byte3, byte4]

def utf8_decode(byte_array):
    U = 0
    if byte_array[0] <= 0x7F:  # 1 byte (ASCII)
        return byte_array[0]
    elif byte_array[0] <= 0xDF:  # 2 bytes
        U = (byte_array[0] & 0x1F) << 6 | (byte_array[1] & 0x3F)
    elif byte_array[0] <= 0xEF:  # 3 bytes
        U = (byte_array[0] & 0x0F) << 12 | (byte_array[1] & 0x3F) << 6 | (byte_array[2] & 0x3F)
    elif byte_array[0] <= 0xF7:  # 4 bytes
        U = (byte_array[0] & 0x07) << 18 | (byte_array[1] & 0x3F) << 12 | (byte_array[2] & 0x3F) << 6 | (byte_array[3] & 0x3F)
    return U

# Example usage
if __name__ == "__main__":
    # Test Unicode Code Points
    code_points = [0x0041, 0x4E16, 0x754C, 0x1F415]  # U+0041 -> "A", U+4E16 -> "世", U+754C -> "界", U+1F415 -> "🐕"
    for cp in code_points:
        print(f"Testing code point U+{cp:04X} ({chr(cp)})")
        
        # UTF-32 encoding and decoding
        utf32_encoded = utf32_encode(cp)
        print("UTF-32 Encoded:", utf32_encoded)
        utf32_decoded = utf32_decode(utf32_encoded)
        print("UTF-32 Decoded:", hex(utf32_decoded))

        # UTF-16 encoding and decoding
        utf16_encoded = utf16_encode(cp)
        print("UTF-16 Encoded:", utf16_encoded)
        utf16_decoded = utf16_decode(utf16_encoded)
        print("UTF-16 Decoded:", hex(utf16_decoded))

        # UTF-8 encoding and decoding
        utf8_encoded = utf8_encode(cp)
        print("UTF-8 Encoded:", utf8_encoded)
        utf8_decoded = utf8_decode(utf8_encoded)
        print("UTF-8 Decoded:", hex(utf8_decoded))
        
        print("-" * 40)