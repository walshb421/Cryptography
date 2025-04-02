import asyncio 

from basics import hex2list, list2string, string2list
from challenge3 import score_string, break_single_char_vigenere

async def main():
    with open('./4.txt') as file:
        tasks = [break_single_char_vigenere(hex2list(line)) for line in file.readlines()]
        scores = [(score_string(guess), list2string(guess)) for _, guess in (await asyncio.gather(*tasks))]
        results = sorted(scores, key=lambda tup : tup[0], reverse=True)
        (_, guess) = results[0]
        
        assert guess == "Now that the party is jumping\n"

if __name__=="__main__": 
    asyncio.run(main())