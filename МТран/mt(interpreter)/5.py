from second import second
from tables import table_name, semantic_table
from fourth import fourth
from examples.dump_ast import third
from interpret import interpret, interpret2

array = [78, 41, 4, 27, 3, 27, 8, 39, 19, 34, 6, 41, 13, 52, 16]
data = [-9,-98,234]
while True:
    command = input("Enter number of lab : (2,3,4,5, 0-to exit)  \n")
    if command == '2':
        second()
        table_name()
    elif command == '4':
        fourth()
        semantic_table()
    elif command == '3':
        third()
    elif command == '5':
        # print(f"result of example 1 arr = {[78, 41, 4, 27, 3, 27, 8, 39, 19, 34, 6, 41, 13, 52, 16]}")
        # interpret(array)
        # print(f"result of example 2 arr = {[-9,-98,234]}")
        # interpret(data)
        n = int(input(f"Enter : "))
        interpret2(n)
    elif command == '0':
        break
