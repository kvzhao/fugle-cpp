
# Fugle Terminal (WIP)

* fugle-cpp: HTTP API for c++
* fugle-terminal
* name change -> stocklab


## Quick start

Install thirdparty libs

1. Clone submobules
```bash
git submodule update --init --recursive --jobs 0
```

It will download `SQLiteCpp`.


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

## Plans
1. Data downloader
2. Database and unified data format
3. Backtesting
4. Reproduce apps