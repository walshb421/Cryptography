import asyncio
from basics import hex2list, string2list, list2string, loop2strings, grab_chunk

async def vigenere(string, key):
    cypher = []
    for i in range(len(string)):
        s = string[i]
        k = key[i % len(key)]
        cypher.append(k ^ s)
    
    return cypher

async def main():
    # Test Code from Challenge 5
    text = string2list("Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal")
    key =  string2list("ICE")
    solution = hex2list("0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f")
    cyphertext = await vigenere(text, key)
    assert cyphertext == solution
    




if __name__=="__main__": 
    asyncio.run(main())