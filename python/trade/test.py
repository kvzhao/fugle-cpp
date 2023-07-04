import os
from configparser import ConfigParser
from fugle_trade.sdk import SDK
from fugle_trade.order import OrderObject
from fugle_trade.constant import (APCode, Trade, PriceFlag, BSFlag, Action)

current_path = os.path.dirname(os.path.abspath(__file__))
config = ConfigParser()

config.read(os.path.join(current_path, 'config.simulation.ini'))
sdk = SDK(config)

sdk.login()
order = OrderObject(
    buy_sell = Action.Buy,
    price_flag = PriceFlag.LimitDown,
    price = None,
    stock_no = "2884",
    quantity = 1,
)
sdk.place_order(order)
print("Your order has been placed successfully.")

orderResults = sdk.get_order_results()

print(orderResults)

order = OrderObject(
    buy_sell = Action.Sell,
    price = 31.10,
    stock_no = "2884",
    quantity = 1,
    ap_code = APCode.Common,
    trade = Trade.DayTradingSell # 當沖賣出
)
sdk.place_order(order)

settlements = sdk.get_settlements()
print(settlements)