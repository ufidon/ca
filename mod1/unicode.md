## [Unicode Code Point](https:#en.wikipedia.org/wiki/Unicode)
- A **Unicode code point** is an integer that uniquely identifies a character. e.g., 
  -  `U+0041` ↦ "A"
  -  `U+4E16` ↦ "世"
  -  `U+754C` ↦ "界"
  -  `U+1F415` ↦ "🐕"
- It ranges from `U+0000` to `U+10FFFF`. 
- There are a total of $2^{20} + (2^{16} − 2^{11}) = 1112064$ valid code points within the codespace.
  - This number arises from the limitations of the UTF-16 character encoding, 
  - which can encode the $2^{16}$ code points in the range [U+0000, U+FFFF] except for the $2^{11}$ code points in the range [U+D800, U+DFFF], 
    - which are used as `surrogate pairs` to encode the $2^{20}$ code points in the range [U+10000, U+10FFFF].
- Each code point is directly mapped to a 4-byte sequence of [UTF-32](https:#en.wikipedia.org/wiki/UTF-32).
  - UTF-32 Encoding: ⚠️ all the code below is in little-endian
    - $\text{UTF-32}(U) = U$
      ```python
      function utf32_encode(U):
          return byte_array([U & 0xFF, (U ≫ 8) & 0xFF, (U ≫ 16) & 0xFF, (U ≫ 24) & 0xFF])      
      ```
  - UTF-32 decoding: 
    - $U = \text{byte}[0] | (\text{byte}[1] ≪ 8) | (\text{byte}[2] ≪ 16) | (\text{byte}[3] ≪ 24)$
      ```python
      function utf32_decode(byte_array):
          U = byte_array[0] | (byte_array[1] ≪ 8) | (byte_array[2] ≪ 16) | (byte_array[3] ≪ 24)
          return U      
      ```

## [UTF-16](https:#en.wikipedia.org/wiki/UTF-16)
- UTF-16 is a `variable-length` encoding that represents code points using 2 or 4 bytes:
  - Code points in [`U+0000`, `U+FFFF`] are encoded in **2 bytes**.
    - 2 bytes: `xxxx xxxx xxxx xxxx`
  - Code points in [`U+10000`, `U+10FFFF`] are encoded in **4 bytes** using `surrogate pairs`.
    - 4 bytes, a surrogate pair: (`110110xxxx xxxx`, `110111xxxx xxxx`)
- Encoding:
  ```python
  if U ≤ 0xFFFF:
      return byte_array([U & 0xFF, (U ≫ 8) & 0xFF])  # 2 bytes (BMP)
  else if U ≤ 0x10FFFF:
      high_surrogate = 0xD800 | ((U - 0x10000) ≫ 10)
      low_surrogate = 0xDC00 | ((U - 0x10000) & 0x3FF)
      return byte_array([high_surrogate & 0xFF, (high_surrogate ≫ 8) & 0xFF, low_surrogate & 0xFF, (low_surrogate ≫ 8) & 0xFF])  # 4 bytes (surrogate pair)
  ```
- Decoding: 


    ```python
    function utf16_decode(byte_array):
        U = 0
        if len(byte_array) == 2:  # Single unit (BMP)
            U = byte_array[0] | (byte_array[1] ≪ 8)
        else if len(byte_array) == 4:  # Surrogate pair (for code points ≥ 0x10000)
            high_surrogate = (byte_array[0] | (byte_array[1] ≪ 8)) - 0xD800
            low_surrogate = (byte_array[2] | (byte_array[3] ≪ 8)) - 0xDC00
            U = (high_surrogate ≪ 10) | low_surrogate + 0x10000
        return U
    ```

## [UTF-8](https:#en.wikipedia.org/wiki/UTF-8)
- UTF-8 is a `variable-length encoding` that represents code points using 1 to 4 bytes:
  - Code points from `U+0000` to `U+007F` are encoded in **1 byte** (7 bits).
    - 1-byte (ASCII): `0xxxxxxx`
  - Code points from `U+0080` to `U+07FF` are encoded in **2 bytes** (11 bits).
    - 2-byte: `110xxxxx 10xxxxxx`
  - Code points from `U+0800` to `U+FFFF` are encoded in **3 bytes** (16 bits).
    - 3-byte: `1110xxxx 10xxxxxx 10xxxxxx`
  - Code points from `U+10000` to `U+10FFFF` are encoded in **4 bytes** (21 bits).
    - 4-byte: `11110xxx 10xxxxxx 10xxxxxx 10xxxxxx`
- Encoding:
  ```python
  function utf8_encode(U):
      if U ≤ 0x007F:
          return byte_array([U])  # 1 byte (ASCII)
      else if U ≤ 0x07FF:
          byte1 = 0b11000000 | (U ≫ 6)  # First 5 bits
          byte2 = 0b10000000 | (U & 0x3F)  # Last 6 bits
          return byte_array([byte1, byte2])  # 2 bytes
      else if U ≤ 0xFFFF:
          byte1 = 0b11100000 | (U ≫ 12)  # First 4 bits
          byte2 = 0b10000000 | ((U ≫ 6) & 0x3F)  # Next 6 bits
          byte3 = 0b10000000 | (U & 0x3F)  # Last 6 bits
          return byte_array([byte1, byte2, byte3])  # 3 bytes
      else if U ≤ 0x10FFFF:
          byte1 = 0b11110000 | (U ≫ 18)  # First 3 bits
          byte2 = 0b10000000 | ((U ≫ 12) & 0x3F)  # Next 6 bits
          byte3 = 0b10000000 | ((U ≫ 6) & 0x3F)  # Next 6 bits
          byte4 = 0b10000000 | (U & 0x3F)  # Last 6 bits
          return byte_array([byte1, byte2, byte3, byte4])  # 4 bytes
  ```
- Decoding:
  ```python
  function utf8_decode(byte_array):
      U = 0
      if byte_array[0] ≤ 0x7F:  # 1 byte (ASCII)
          return byte_array[0]
      else if byte_array[0] ≤ 0xDF:  # 2 bytes
          U = (byte_array[0] & 0x1F) ≪ 6 | (byte_array[1] & 0x3F)
      else if byte_array[0] ≤ 0xEF:  # 3 bytes
          U = (byte_array[0] & 0x0F) ≪ 12 | (byte_array[1] & 0x3F) ≪ 6 | (byte_array[2] & 0x3F)
      else if byte_array[0] ≤ 0xF7:  # 4 bytes
          U = (byte_array[0] & 0x07) ≪ 18 | (byte_array[1] & 0x3F) ≪ 12 | (byte_array[2] & 0x3F) ≪ 6 | (byte_array[3] & 0x3F)
      return U  
  ```

## Sample Implementation
- [uc.py](./code/uc.py)