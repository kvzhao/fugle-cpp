import argparse
import os
import urwid
from fugle_marketdata import RestClient
from stocklab.common.api import GetKey, StockAPI
from typing import List, Dict


def main(args):
    stock_id = args.stock_id
    client = RestClient(api_key=GetKey(StockAPI.FUGLE))
    stock = client.stock
    ret = stock.intraday.quote(symbol=stock_id)
    print(ret)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Realtime Monitor of Stock Prices")
    parser.add_argument("-s","--stock_id", type=str, default="2330",
                        help="")
    args = parser.parse_args()

    main(args)