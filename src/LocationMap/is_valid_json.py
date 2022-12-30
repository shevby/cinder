import json
import sys


f = open('/tmp/is_valid_json.tmp')
try:
    json.load(f)
    sys.exit(0)
except Exception:
    sys.exit(1)
