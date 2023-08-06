import argparse
import os
from fugle_marketdata import RestClient
from python.common.api import GetFugleAPI
from typing import List, Dict

import pandas as pd

def convert_data_format(data_list: List[Dict], num_stock):

    def _dict_rename(d, k, nk):
        d[nk] = d[k]
        del d[k]

    if num_stock < len(data_list):
        data_list = data_list[:num_stock]

    for data in data_list:
        data.pop('type')
        data.pop('lastUpdated')
        data.pop('change')
        data['tradeValue'] = round(data['tradeValue'] / 1e8, 2)
        data['tradeVolume'] = round(data['tradeVolume'] / 1e3, 2)
        _dict_rename(data, 'openPrice', 'open')
        _dict_rename(data, 'closePrice', 'close')
        _dict_rename(data, 'highPrice', 'high')
        _dict_rename(data, 'lowPrice', 'low')

    return data_list

def convert_data_to_table(data_list: List[Dict]):
    df = pd.DataFrame(data_list)
    df["changePercent"] = df["changePercent"].apply(
        lambda x: f"<span style='color:red'>{x:.2f}%" if x > 0 else f"<span style='color:green'>{x:.2f}%")
    markdown_table = df.to_markdown(index=False)
    return markdown_table

def save_to_file(table: str, path):
    with open(path, 'w') as file:
        file.write(table)

def main(args):

    client = RestClient(api_key=GetFugleAPI())
    stock = client.stock

    ret_dict = stock.snapshot.actives(market=args.market, trade=args.trade)

    date = ret_dict.get('date')
    time = ret_dict.get('time')
    data = ret_dict.get('data')
    output_file_path = os.path.join(args.output_dir, '{}.md'.format(date))

    # TODO: save data direcly into db
    data = convert_data_format(data, args.num_stock)
    table = convert_data_to_table(data)
    save_to_file(table, output_file_path)
    print('done.')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Ranking of stocks by trading values")
    parser.add_argument("-n","--num_stock", type=int, default=100,
                        help="Top n stocks, default=100")
    parser.add_argument("-m","--market", type=str, default="TSE",
                        help="Market: TSE, OTC, ESB, TIB, PSB. default=TSE")
    parser.add_argument("-t","--trade", type=str, default="value",
                        help="Trade: value, volume. default=value")
    parser.add_argument("-o","--output_dir", type=str, default="database/table/trade_value",
                        help="Output path. default=database/table/trade_value")
    args = parser.parse_args()

    main(args)
