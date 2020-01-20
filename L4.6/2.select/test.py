#!/usr/bin/python3

import os
import contextlib
import time

with contextlib.suppress(OSError):
  out1 = os.path.join(os.path.curdir, 'in1')
  out2 = os.path.join(os.path.curdir, 'in2')

  os.mkfifo(out1)
  os.mkfifo(out2)

try:
  o1 = open(out1, 'w')
  o2 = open(out2, 'w')

  for i in range(10):
    print(i, 10 - i - 1)
    print(i, file=o1, flush=True)
    print(10 - i - 1, file=o2, flush=True)
    time.sleep(0.01)
finally:
  o1.close()
  o2.close()
  os.remove(out1)
  os.remove(out2)

