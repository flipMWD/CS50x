CREATE TABLE IF NOT EXISTS 'stocks' (
    'user_id' INTEGER NOT NULL,
    'symbol' TEXT NOT NULL,
    'shares' INTEGER NOT NULL,
    FOREIGN KEY(user_id) REFERENCES users(id)
);

CREATE TABLE IF NOT EXISTS 'historyStocks' (
    'user_id' INTEGER NOT NULL,
    'operation' TEXT NOT NULL,
    'symbol' TEXT NOT NULL,
    'price' NUMERIC NOT NULL,
    'shares' INTEGER NOT NULL,
    'date' TEXT NOT NULL,
    FOREIGN KEY(user_id) REFERENCES users(id)
);