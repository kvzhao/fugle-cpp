from fugle_marketdata import RestClient
import os

API_KEY_NAME = 'FUGLE_API_KEY'
api_key = os.environ.get(API_KEY_NAME)

if not api_key:
    print("API key not found. Please make sure the '{}' environment variable is set.".format(API_KEY_NAME))

client = RestClient(api_key=api_key)
stock = client.stock
ret = stock.intraday.tickers(type='EQUITY', exchange="TWSE", isNormal=True)

print(ret)