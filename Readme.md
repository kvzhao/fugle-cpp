
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
Save your key in `api_key.txt`. 