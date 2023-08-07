import argparse
import os
import time
from fugle_marketdata import RestClient
from stocklab.common.api import GetKey, StockAPI
from rich.live import Live
from rich.table import Table


class TickerMonitor(object):

    def __init__(self, symbols):
        client = RestClient(api_key=GetKey(StockAPI.FUGLE))
        self.stock = client.stock
        self.symbols = symbols

    def screen(self) -> Table:

        table = Table()

        table.add_column('Symbol')
        table.add_column('Name')
        table.add_column('Price')
        table.add_column('Change')
        table.add_column('Value (E)')

        for symbol in self.symbols:
            quote = self.stock.intraday.quote(symbol=symbol)
            trade_data = self.stock.intraday.trades(symbol=symbol)['data']

            last_trade = trade_data[0]

            stock_name = quote['name']
            stock_price = last_trade['price']
            average_price = quote['avgPrice']
            change = quote['change']
            change_percent = quote['changePercent']
            total = quote['total']
            trade_value = total['tradeValue'] / 1e8

            color = 'red' if change_percent > 0 else 'green'
            sign = '+' if change_percent > 0 else ''

            priceStr = f"{stock_price:3.1f} ({sign}{change})"

            table.add_row(
                f"{symbol}",
                f"{stock_name}",
                f"[{color}]{priceStr}",
                f"[{color}]{change_percent:2.2f} %",
                f"{trade_value:.2f}",
            )

        return table

def main(args):

    symbol_list = ['2330', '3231', '3583', '5371', '3032']

    monitor = TickerMonitor(symbol_list)

    with Live(monitor.screen(), refresh_per_second=1) as live:
        while True:
            time.sleep(0.1)
            live.update(monitor.screen())



if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Realtime Monitor of Stock Prices")
    parser.add_argument("-s","--stock_id", type=str, default="2330",
                        help="")
    args = parser.parse_args()

    main(args)