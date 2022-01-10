from string import punctuation, whitespace
from collections import Counter
import re


def analyze_text(raw_text):
    words = list(filter(None, re.split(rf'[\s{punctuation}]', raw_text)))

    counter = Counter(words)

    print(f'Кол-во слов: {counter.items()}')  # 1
    print('Среднее кол-во слов: {}'.format(sum(counter.values()) / len(counter)))  # 2
    print('Медианное кол-во слов: {}'.format(sorted(counter.values())[len(counter) // 2]))

    try:
        n = int(input('Введите n: '))
        k = int(input('Введите k: '))
    except ValueError:
        print('Вы какой-то странняга, поэтому n=4, k=10')
        n, k = 4, 10

    n_gramm_counter = Counter()
    for word, amount in counter.items():
        for shift in range(len(word) - n + 1):
            n_gramm_counter[word[shift:n + shift]] += amount
    print(f'{k} наиболее часто встречающихся {n}-грамм: {n_gramm_counter.most_common(k)}')


# with open('file_task1.txt', 'r', encoding='UTF-8') as f:
#     raw_text = f.read()

# analyze_text(raw_text)
