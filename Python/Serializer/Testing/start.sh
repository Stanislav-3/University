source venv/bin activate
coverage run --include=venv/lib/python3.9/site-packages/Serializer/*,test.py,tests.py \
             --omit=*__init__.py \
             -m pytest -p no:warnings test.py
coverage report