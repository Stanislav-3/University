from data import data2
import re


def second():
    pattern = ["void", "int", "while", "if", "else"]
    common_mistake = ["==","++","--"]
    i = 0
    j = 1

    n = len(data2.split("\n"))
    for token in data2.split("\n"):
        # print(token,"\n", token.split(),"\n")
        i+=1
        for el in token.split():

            if (len(el) >= 2 and el[0] == "i" and el[1] == "f") or (len(el) >= 3 and el[0] == "i" and el[1] == "i" and el[0] == "f"):
                if len(el) != 2:
                    print(f"\n\n---------ERROR:UNEXPECTED TOKEN invalid lexic if-statement {el} on line {i} of {n}  pos {1}")
                    print(token)

                    j += 1
                    break

            elif el[0] == "v" and el[1] == "o":
                if len(el) != 4 or el[2] != "i" or el[3] != "d":
                    print(f"\n\n---------ERROR:UNEXPECTED TOKEN invalid lexic void-statement: {el} on line {i} of {n}  pos {1}")
                    print(token)
                    j += 1
                    break
            elif el[0] == "=":
                if len(el) > 2 or el[-1] != "=":
                    print(f"\n\n---------ERROR:UNEXPECTED TOKEN invalid lexic ===-statement: {el} on line {i} of {n}  pos {13}")
                    print("merged[i+j] === L[i];")

                    j += 1
            elif len(el)> 10 and el[9] == "@":
                if len(el) > 2 or el[-1] != "=":
                    print(
                        f"\n\n---------ERROR:UNEXPECTED TOKEN invalid lexic non-existing statement: {el} on line {i} of {n}  pos {10}")
                    print(el)

                    j += 1

            elif len(el) > 2 and el[0] == "i" and el[1] == "n":
                if len(el) != 3 or el[-1] != "t":
                    print(f"\n\n---------ERROR:UNEXPECTED TOKEN invalid lexic int-statement :{el} on line {i} of {n}  pos {0}")
                    j += 1
                    print(el)
                    print(token)

            elif el[0] == "[":
                if len(el) >= 2 and el[1] == "[":
                    print(f"\n\n---------ERROR:UNEXPECTED TOKEN invalid lexic []-statement :{el} on line {i} of {n}  pos {0}")
                    j += 1
                    print(token)
            elif el[0] == "]":
                if len(el) >= 2 and el[1] == "]":
                    print(f"\n\n---------ERROR:UNEXPECTED TOKEN invalid lexic []-statement :{el} on line {i} of {n}  pos {0}")
                    j += 1
                    print(token)
            elif el == '=!=':
                print(f"\n\n---------ERROR:UNEXPECTED TOKEN invalid lexic non-existing statement :{el} on line {i} of {n}  pos {13}")
                j += 1
                print(token)


second()