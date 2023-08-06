import sqlite3

# 建立或連接到資料庫
conn = sqlite3.connect('example.db')

# 建立資料表
def create_table():
    try:
        conn.execute('''CREATE TABLE IF NOT EXISTS users
                        (id INTEGER PRIMARY KEY AUTOINCREMENT,
                         name TEXT NOT NULL,
                         age INTEGER NOT NULL)''')
        print("資料表建立成功")
    except sqlite3.Error as e:
        print("資料表建立失敗:", e)

# 插入資料
def insert_data(name, age):
    try:
        conn.execute('''INSERT INTO users (name, age) VALUES (?, ?)''', (name, age))
        conn.commit()
        print("資料插入成功")
    except sqlite3.Error as e:
        print("資料插入失敗:", e)

# 查詢資料
def select_data():
    try:
        cursor = conn.execute("SELECT * FROM users")
        for row in cursor:
            print(f"ID: {row[0]}, Name: {row[1]}, Age: {row[2]}")
    except sqlite3.Error as e:
        print("查詢資料失敗:", e)

# 建立資料表
create_table()

# 插入資料
insert_data("John Doe", 30)
insert_data("Jane Smith", 25)

# 查詢資料
select_data()

# 關閉資料庫連線
conn.close()
