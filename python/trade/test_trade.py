import os

from configparser import ConfigParser
from fugle_trade.sdk import SDK
from fugle_trade.order import OrderObject
from fugle_trade.constant import (APCode, Trade, PriceFlag, BSFlag, Action)

api_key = os.environ.get('X-API-KEY')

if api_key:
    print("API key found:", api_key)
else:
    print("API key not found. Please make sure the 'X-API-KEY' environment variable is set.")


config = ConfigParser()
config.read('python/trade/config.simulation.ini')
sdk = SDK(config)
sdk.login()

order = OrderObject(
    buy_sell = Action.Buy,
    price = 28.00,
    stock_no = "2884",
    quantity = 2,
    ap_code = APCode.Common
)

ret = sdk.place_order(order)
print(ret)