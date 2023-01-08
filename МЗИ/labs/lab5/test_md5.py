from md5 import md5

with open('source.txt', 'r') as file:
    source_text = file.read()

digest = md5(source_text)

print('Source text: ', source_text)
print('Digest message: ', digest)