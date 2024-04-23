from Crypto.Cipher import AES
from basics import hex2list, list2string, string2list

with open('./challenge6_cyphertext.txt') as file:
    cyphertext = list2string(hex2list(file.read()))
    cipher = AES.new('YELLOW SUBMARINE'.encode('utf-8'), AES.MODE_ECB)
    print(cipher.decrypt(cyphertext.encode('utf-8')))

