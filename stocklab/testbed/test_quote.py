from fugle_marketdata import RestClient

from stocklab.common.api import GetKey, StockAPI

client = RestClient(api_key=GetKey(StockAPI.FUGLE))
stock = client.stock
ret = stock.intraday.tickers(type='EQUITY', exchange="TWSE", isNormal=True)

print(ret)