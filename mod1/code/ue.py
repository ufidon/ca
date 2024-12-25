### 1️⃣ Demonstrate UTF-8, UTF-16, and UTF-32 encoding and decoding in Python

text = "Hello, 世界"  # A mix of English and Chinese characters

# UTF-8 Encoding
utf8_encoded = text.encode('utf-8')
utf8_decoded = utf8_encoded.decode('utf-8')

# UTF-16 Encoding
utf16_encoded = text.encode('utf-16')
utf16_decoded = utf16_encoded.decode('utf-16')

# UTF-32 Encoding
utf32_encoded = text.encode('utf-32')
utf32_decoded = utf32_encoded.decode('utf-32')

# Print results
print("Original Text:", text)
print("\nUTF-8 Encoding:")
print(utf8_encoded)
print("Decoded (UTF-8):", utf8_decoded)

print("\nUTF-16 Encoding:")
print(utf16_encoded)
print("Decoded (UTF-16):", utf16_decoded)

print("\nUTF-32 Encoding:")
print(utf32_encoded)
print("Decoded (UTF-32):", utf32_decoded)


### 2️⃣ Byte Order Mark (BOM) in UTF-16 and UTF-32
# The BOM is a special Unicode character (U+FEFF) placed at the start of a text stream to 
# indicate **byte order** (endianness) in multi-byte encodings like **UTF-16** and **UTF-32**. 


# BOM Values and Their Meaning:
'''
| Encoding | BOM Value     | Endianness              |
|----------|---------------|------------------------|
| UTF-16   | `0xFEFF`      | Big-endian (BE)         |
| UTF-16   | `0xFFFE`      | Little-endian (LE)      |
| UTF-32   | `0x0000FEFF`  | Big-endian (BE)         |
| UTF-32   | `0xFFFE0000`  | Little-endian (LE)      |

- Example:
- **UTF-16 (Little-endian) BOM**: `\xff\xfe`  
- **UTF-16 (Big-endian) BOM**: `\xfe\xff`  
- **UTF-32 (Little-endian) BOM**: `\xff\xfe\x00\x00`  
- **UTF-32 (Big-endian) BOM**: `\x00\x00\xfe\xff`  
'''

# Why UTF-8 Doesn't Require BOM:
'''
- **UTF-8** encodes characters as **sequences of 1 to 4 bytes** without ambiguity regarding byte order.
- However, while uncommon, UTF-8 files may start with a BOM (`0xEFBBBF`), 
- but this is mostly to indicate that the file uses UTF-8.
'''


text = "Hello, 世界"
utf16_le = text.encode('utf-16')  # Little-endian (includes BOM)
utf16_be = text.encode('utf-16-be')  # Big-endian (no BOM by default)

print("UTF-16 Little-endian (with BOM):", utf16_le)
print("UTF-16 Big-endian (no BOM):", utf16_be)