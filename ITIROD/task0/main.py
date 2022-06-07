sep = '<!*!>'
name = 'Stan'
msg = f'12;123l1;41234 | {name}{sep}Lalalalallalla this is ajdfalsjdfalskjfdklasjflkasj'

res = msg.split('| ')[1].split(sep)[0]

print(res)
print(msg)