import asyncio
from basics import hex2list, string2list, list2string, loop2strings, grab_chunk

from challenge3 import break_single_char_vigenere
from challenge5 import vigenere

ham = lambda c1, c2: (c1 ^ c2).bit_count()
hamming = lambda str1, str2: sum([ham(c1, c2) for (c1, c2) in loop2strings(str1, str2)])

async def normalized_avg_hamming(cyphertext, size):
    chunks = [
        (grab_chunk(cyphertext, size*x, size), grab_chunk(cyphertext, size*y, size))
        for x in range(25)
        for y in range(x + 1, 25)
    ]
    avg = sum([hamming(x, y) for (x, y) in chunks])/len(chunks)
    return (size, avg/size) # Return Normalized Average
    
    
async def guess_keysize(cyphertext):
    tasks = [normalized_avg_hamming(cyphertext, size) for size in range(2,40)]

    min = 0xFFFFFFFF
    guess = 0
    
    for (size, avg) in (await asyncio.gather(*tasks)):
        if(avg < min):
            guess = size
            min = avg
    
    return guess

async def guess_vigenere_key(cyphertext, keysize):
    block_size = int(len(cyphertext)/keysize)
    results = [ 
        await break_single_char_vigenere([grab_chunk(cyphertext, x*keysize + y, 1)[0] for x in range(block_size)])
        for y in range(keysize)
    ]

    return [key for (key,_) in results]

async def main():

    # Challenge 6 Tests
    
    assert hamming(string2list("this is a test"), string2list("wokka wokka!!!")) == 37


    with open('./challenge6_cyphertext.txt') as file:
    
        cyphertext = hex2list(file.read())

        keysize = await guess_keysize(cyphertext)  
        key = await guess_vigenere_key(cyphertext, keysize)

        assert key == string2list("Terminator X: Bring the noise")
        print(list2string(key))


if __name__=="__main__": 
    asyncio.run(main())