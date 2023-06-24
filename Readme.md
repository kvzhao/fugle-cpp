
# Fugle Terminal (WIP)

* fugle-cpp: HTTP API for c++
* fugle-terminal


## Quick start

Install thirdparty libs

1. Clone submobules
```bash
git submodule update --init --recursive --jobs 0
```

It will download `SQLiteCpp` and `TermOx`.


2. Install restcppsdk

Ubuntu
```bash
sudo apt-get install libcpprest-dev
```

OSX
```bash
brew install cpprestsdk
```

3. Prepare API key

The API Key file is needed.
Please apply API key from official website: https://developer.fugle.tw/docs/key/

Set the key with environment variable or save to bashrc.
```bash
export FUGLE_API_KEY='...'
```

## ToDos
* [x] 成交值排行榜
* [ ] 前一週大漲 20%
* [ ] 上漲下跌家數，大盤長相
* [x] Fully support fugle API (Ticker / Stats)
* [ ] Stock group / watch list
* [ ] Realtime intraday monitor with watch list
* [ ] 盤面趨勢股