import os

FUGLE_API_KEY_NAME = 'FUGLE_API_KEY'
FINMIND_API_KEY_NAME = 'FINMIND_API_KEY'

def getEnvVariable(key):
    api_key = os.environ.get(key, "")
    if not api_key:
        print("API key not found. Please make sure the '{}' environment variable is set.".format(key))
    return api_key

def GetFugleAPI():
    return getEnvVariable(FUGLE_API_KEY_NAME)

def GetFinMindAPI():
    return getEnvVariable(FINMIND_API_KEY_NAME)
