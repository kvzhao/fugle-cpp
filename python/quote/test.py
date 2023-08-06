from fugle_marketdata import RestClient

from python.common.api import GetFugleAPI

client = RestClient(api_key=GetFugleAPI())
stock = client.stock
ret = stock.intraday.tickers(type='EQUITY', exchange="TWSE", isNormal=True)

print(ret)