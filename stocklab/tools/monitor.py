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

        # TODO: parepare historical data

    def screen(self) -> Table:

        table = Table()

        table.add_column('Symbol')
        table.add_column('Name')
        table.add_column('Price')
        table.add_column('avgPrice')
        table.add_column('Change')
        table.add_column('Value (E)')
        table.add_column('Volume (k)')

        for symbol in self.symbols:
            quote = self.stock.intraday.quote(symbol=symbol)
            trade_data = self.stock.intraday.trades(symbol=symbol)['data']

            last_trade = trade_data[0]
            deal_price = last_trade['price']
            deal_size = last_trade['size']

            stock_name = quote['name']
            average_price = quote['avgPrice']
            change = quote['change']
            change_percent = quote['changePercent']
            total = quote['total']
            total_value = total['tradeValue'] / 1e8
            total_size = total['tradeVolume'] / 1e3

            color = 'red' if change_percent > 0 else 'green'
            sign = '+' if change_percent > 0 else ''

            priceStr = f"{deal_price:3.1f} ({sign}{change})"

            table.add_row(
                f"{symbol}",
                f"{stock_name}",
                f"[{color}]{priceStr}",
                f"{average_price:2.2f}",
                f"[{color}]{change_percent:2.2f} %",
                f"{total_value:.2f}",
                f"{total_size:.1f}",
            )

        return table

def main(args):

    monitor = TickerMonitor(args.stock_list)

    with Live(monitor.screen(), refresh_per_second=1) as live:
        while True:
            time.sleep(0.1)
            live.update(monitor.screen())



if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Realtime Monitor of Stock Prices")
    parser.add_argument("-s","--stock_list", nargs='+', type=str,
                        help="symbol list")
    args = parser.parse_args()

    main(args)
