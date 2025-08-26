## A0 Practice

### ASCII
#### 1: 
Is not ASCII as 0x8B is too large a value
#### 2: 
Is ASCII
#### 3: 
Is not ASCII as 0x4G is not a valud hex value

### ISO-8859
Valid ISO should be any ASCII, plus 0xAO to 0xFF
#### 1: 
Is ISO
#### 2: 
Is not ISO as 0x8C is not in range
#### 3: 
Is ISO

### UTF-8
The 4 different character lengths as hex are:
    |   byte 1      |   byte 2      |   byte 3      | byte 4
1   | 0x00 to 0x7F  |               |               |
2   | 0xC0 to 0xDF  | 0x80 to 0xBF  |               |
3   | 0xE0 to 0xEF  | 0x80 to 0xBF  | 0x80 to 0xBF  |
4   | 0xF0 to 0xF7  | 0x80 to 0xBF  | 0x80 to 0xBF  | 0x80 to 0xBF

#### 1: 
Separating the bytes into different chars gives us the 7 characters:

    0xEB, 0xB5, 0xB2, 
    0xF5, 0x82, 0x86, 0x9A, 
    0xF0, 0x88, 0x92, 0xB4, 
    0xCE, 0xBF, 
    0xF0, 0xA5, 0xAF, 0xB7, 
    0xE3, 0xB2, 0xAC

These all neatly fit into one of the 4 definitions and so we can conclude, its UTF-8
#### 2:
Separating the bytes into different chars gives us the initial 5 characters:

    0xD0, 0xBF, 
    0xE2, 0xAE, 0x8D, 
    0xF5, 0x90, 0x95, 0x9D, 
    0xDB, 0x8F, 
    0x56 

Those are all valid characters but the following byte 0xBB is not a 
valid initial character for any of the 4 byte amounts.

#### 3:
Separating the bytes into different chars gives us the initial 4 characters:

    0xD1, 0x92, 
    0xDA, 0x88, 
    0xD7, 0xAE, 
    0xC0, 0xBE, 

But then this is followed by the byte 0xE8, which can only be the start 
of a 3 byte character according to that first character, but then the 
3rd byte is not in the correct range to be a valid character

So it is not valid UTF-8