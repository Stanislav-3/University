import pandas as pd

ids = ['iphone', 'iphone', 'mac', 'headphones', 'ipad', 'headphones']
cnt = [10, 20, 30, 40, 40, 20]
price = [500, 700, 2000, 1200, 1000, 500]

df = pd.DataFrame({'name': ids, 'count': cnt, 'price': price})
df.to_csv('data.csv', index=False)
