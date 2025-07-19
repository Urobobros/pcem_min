#!/usr/bin/env python3
import re,sys
unused=set()
for line in sys.stdin:
    m=re.search(r"removing unused section '(.*)' in file '(.*)'", line)
    if m:
        unused.add(m.group(2))
for obj in sorted(unused):
    print(obj)
