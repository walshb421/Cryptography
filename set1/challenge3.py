import asyncio
from basics import hex2list, string2list, list2string, single_char_xor


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


async def break_single_char_vigenere(cypher):
    cyphers = [(key, single_char_xor(cypher, key)) for key in range(32, 127)]

    max = 0
    result = None
    key = 0
    for (c, string) in cyphers:
        s = score_string(string)
        if s > max:
            max = s
            key = c
            result = string

    return (key, result)

async def main():
    # Test Code from Challenge 3
    cyphertext = hex2list("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736")
    (_, result) = await break_single_char_vigenere(cyphertext)
    assert result == string2list("Cooking MC's like a pound of bacon")
    print(list2string(result))


if __name__=="__main__": 
    asyncio.run(main())