input = [[3, 5], [8, 10], [1, 2], [6, 7], [12, 16]]
new_interval = [4, 8]

input.append(new_interval)

input.sort(key=lambda value: value[0])

i = 0
while i != len(input) - 1:
    if input[i + 1][0] <= input[i][1]:
        if input[i + 1][1] > input[i][1]:
            input[i][1] = input[i+1][1]
        del input[i+1]
    else:
        i += 1

print(input)