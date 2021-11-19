
def compress(bin: str):
    result = ""
    last_ch = "";
    occurence = 0
    
    for i in range(len(bin)):
        if i > 0:
            if bin[i] == last_ch:
                occurence += 1
                continue
            elif bin[i] != last_ch:
                result += str(occurence)
                occurence = 0

        result += bin[i]
        last_ch = bin[i]
    
    if occurence != 0:
        result += str(occurence)

    return result


print(compress("00001111"), "0313")
print(compress("1000011110"), "103130")
