import sqlite3
import json

conn_sql = sqlite3.connect('new.db')
cursor = conn_sql.cursor()

cursor.execute("""CREATE TABLE IF NOT EXISTS users(    
    id INTEGER PRIMARY KEY,
    name TEXT,
    password TEXT,
    role INT);
""")
# conn_sql.commit()
cursor.execute("""CREATE TABLE IF NOT EXISTS posts(    
    id INTEGER PRIMARY KEY,
    id_users INT,
    name TEXT,
    category TEXT,
    author TEXT,
    price TEXT,
    telephone TEXT);
""")
# conn_sql.commit()

cursor.execute("DELETE FROM posts WHERE name <> 0")
cursor.execute("DELETE FROM users WHERE name <> 0")

cursor.execute(" INSERT INTO users(name, password, role) VALUES('StanKore', 'password', 2)")
cursor.execute(" INSERT INTO users(name, password, role) VALUES('simple', 'password', 1)")

cursor.execute(" INSERT INTO posts(name, id_users, name, category, author, price, telephone) VALUES('Book1', 1, '2', 'fantasy', 'Dickens', '100', '1234')")
cursor.execute(" INSERT INTO posts(name, id_users, name, category, author, price, telephone) VALUES('Book2', 1, '12', 'nature', 'Dostoevsky', '30', '21345')")
cursor.execute(" INSERT INTO posts(name, id_users, name, category, author, price, telephone) VALUES('Book3', 1, '22', 'cosmor', 'No name', '45', '45324532')")
cursor.close()
conn_sql.commit()
conn_sql.close()
