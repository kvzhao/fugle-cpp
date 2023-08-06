from FinMind.data import DataLoader
import os

API_KEY_NAME = 'FINMIND_API_KEY'
api_key = os.environ.get(API_KEY_NAME)

if not api_key:
    print("API key not found. Please make sure the '{}' environment variable is set.".format(API_KEY_NAME))

api = DataLoader()
api.login_by_token(api_token=api_key)

df = api.taiwan_stock_margin_purchase_short_sale(
    stock_id="2330",
    start_date='2020-04-02',
    end_date='2020-04-12'
)

print(df)