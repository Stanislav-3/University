from computations import gen4
from CustomRandom import rand
import numpy as np


games = {}
donates = []


def add_game(game, money):
    if game in games:
        games[game] += money
    else:
        games[game] = money


def add_donates(_donates):
    for donate in _donates:
        add_game(donate[0], donate[1])


def output_games(text: str):
    print(text)
    names, money = list(games.keys()), list(games.values())

    for name, _money in zip(names, money):
        print(f'{name}: {_money}')


def normalize_money():
    names, money = list(games.keys()), list(games.values())

    s = sum(money)
    for i in range(len(money)):
        money[i] /= s

    # print('Probabilities:')
    # for name, _money in zip(names, money):
    #     print(f'{name}: {_money}')

    for i, name in enumerate(names):
        games[name] = money[i]


def choose_game():
    names, money = list(games.keys()), list(games.values())

    return gen4(money)


def generate_donates():
    games = {'Witcher 3', 'Minecraft', 'God Of War', 'Assassin\'s creed',
             'Fallout', 'Cyberpunk', 'Battlefield', 'Winx'}

    for _game in games:
        amount = int(rand() * 10)
        for _ in range(amount):
            money = round(rand() * 25, 2)

            add_game(_game, money)


if __name__ == "__main__":
    # generate_donates()
    print('Input donate (e.g. "Cyberpunk 123")\nOr enter to exit')
    while True:
        text = input()
        if text == 'esc':
            break

        sep_text = text.split()
        try:
            money = float(sep_text[-1].strip())
        except Exception as e:
            print('Invalid money amount...\n', e)

        name = ' '.join(sep_text[:-1])

        add_game(name, money)

    print()
    output_games('Money: ')
    normalize_money()
    # output_games('Probabilities: ')

    print()
    print('Chosen game: ', list(games.keys())[choose_game()])

    # N = 10**6
    # result = [0.] * len(games)
    # for i in range(N):
    #     result[choose_game()] += 1 / N
    #
    # print()
    # print('Frequencies:')
    #
    # for i, game in enumerate(games.keys()):
    #     print(f'{game}: {result[i]}')













