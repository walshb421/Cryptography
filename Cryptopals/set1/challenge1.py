import asyncio 

from basics import hex2list
        
def hex2list(string):
    count = 0
    result = [0 for _ in range(len(string) >> 1)]
    for char in string:
        nibble = 0
        if (ord(char) >= ord('0') and  ord(char) <= ord('9')):
            nibble = ord(char) - ord('0')
        elif (ord(char) >= ord('a') and ord(char) <= ord('f')):
            nibble = ord(char) - ord('a') + 10
        elif (ord(char) >= ord('A') and ord(char) <= ord('F')):
            nibble = ord(char) - ord('A') + 10
        elif (ord(char) == ord('\n')):
            continue


        byte = count >> 1
        result[byte] = result[byte] << 4 | nibble
        count += 1
    return result


def list2base64(string):
    values = [0 for _ in range(int(4*len(string)/3))]
    
    for i in range(4*len(string)):
        toofer = string[int(i/4)]
        toofer = toofer & (0xC0 >> (2*(i%4)))
        toofer = toofer >> (2*(3 - i%4))
        values[int(i/3)] = values[int(i/3)] << 2 | toofer
    
    base64 = ""
    for value in values:
        if (value >= 53 and value <= 61):
            base64 += chr(value - 4); 
        elif (value >= 0 and value <= 25):
            base64 += chr(ord('A') + value)
        elif (value >= 26 and value <= 51):
            base64 += chr(ord('a') + (value - 26))
        elif (value == 62):
            base64 += '+'
        elif (value == 63):
            base64 += '/'
            
    return base64

def hex2base64(hex):
    return list2base64(hex2list(hex))

async def main():
    assert hex2base64("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d") == "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"
    




if __name__=="__main__": 
    asyncio.run(main())
