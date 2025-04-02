from basics import hex2list, loop2strings

fixed_xor = lambda str1, str2: [s1^s2 for (s1, s2) in loop2strings(str1, str2)]

def main():
    cyphertext = fixed_xor(hex2list("1c0111001f010100061a024b53535009181c"), hex2list("686974207468652062756c6c277320657965"))
    assert cyphertext == hex2list("746865206b696420646f6e277420706c6179")

if __name__=="__main__": 
   main()
