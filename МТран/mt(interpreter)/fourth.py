from data import data,template
def fourth(data=data):
    operators = ["+","-","/","*","++","strcat"]
    stroka = 1
    j = 1
    for el in data.split("\n"):
        data = el.split()
        for operator in operators:
            if operator in data:
                if "=" in data:
                    output = el[el.index("=")+1:].strip()
                else:
                    output = el.strip()


                if operator == "++":
                    if {template[data[data.index(operator)-1]]} != "int":
                        print("\n\n\nSemantic ERROR ", operator)
                        print(output)
                        print(f"row {stroka}  pos {el.index(operator)}")
                        print(f"operands: {data[data.index(operator)-1]} type '{template[data[data.index(operator)-1]]}' ")
                elif operator == "strcat":
                    if {template[data[data.index(operator)+2]]} != "str" and {template[data[data.index(operator)+4]]} != "str":
                        print("\n\n\nSemantic ERROR ", operator)
                        print(output)
                        print(f"row {stroka}  pos {el.index(operator)}")
                        print(f"operand: {data[data.index(operator)+2]} type '{template[data[data.index(operator)+2]]}'and {data[data.index(operator)+4]} type '{template[data[data.index(operator)+4]]}'")

                else:
                    if ({template[data[data.index(operator)-1]]} != "int" or {template[data[data.index(operator)-1]]}!="float") and ({template[data[data.index(operator)+1]]} != "int" or {template[data[data.index(operator)+1]]}!="float"):
                        print("\n\n\nSemantic ERROR ", operator)
                        print(output)
                        print(f"row {stroka}  pos {el.index(operator)}")
                        print(f"operand: {data[data.index(operator)-1]} type '{template[data[data.index(operator)-1]]}' and {data[data.index(operator)+1]} type '{template[data[data.index(operator)+1]]}'")


            # print(el)
            stroka+=1
