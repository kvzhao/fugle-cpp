import os

from configparser import ConfigParser
from fugle_trade.sdk import SDK
from fugle_trade.order import OrderObject
from fugle_trade.constant import (APCode, Trade, PriceFlag, BSFlag, Action)

config = ConfigParser()
config.read('stocklab/trade/config.simulation.ini')
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