def list2string(list):
    string = str()
    for char in list:
        string += chr(char)
    return string


def string2list(string):
    return [ord(char) for char in string]

def score_char(char):
    char_rankings = "ZQXJKVBPYGFWMUCLDRHS NIOATE"
    try:
        return char_rankings.index(chr(char).upper())
    except:
        if(char < ord(' ') or char > ord('~') ):
            return -10
        else:
            return 1

score_string = lambda string: sum([score_char(char) for char in string])
single_char_xor = lambda string, key: [key ^ char for char in string] 

def grab_chunk(cyphertext, offset, size):
    assert not (offset + size) > len(cyphertext)
    return [cyphertext[i] for i in range(offset, offset + size)]


def loop2strings(str1, str2):
    assert len(str1) == len(str2)
    for i in range(len(str1)):
        yield((str1[i], str2[i]))
        

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

single_char_xor = lambda string, key: [key ^ char for char in string] 
