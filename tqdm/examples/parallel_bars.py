from __future__ import print_function
from time import sleep
from tqdm import tqdm, trange
from random import random
from multiprocessing import Pool, freeze_support
from concurrent.futures import ThreadPoolExecutor
from threading import RLock
from functools import partial
import sys

NUM_SUBITERS = 9
PY2 = sys.version_info[:1] <= (2,)


def progresser(n, auto_position=True, write_safe=False, blocking=True):
    interval = random() * 0.002 / (NUM_SUBITERS - n + 2)
    total = 5000
    text = "#{}, est. {:<04.2}s".format(n, interval * total)
    for _ in trange(total, desc=text,
                    lock_args=None if blocking else (False,),
                    position=None if auto_position else n):
        sleep(interval)
    # NB: may not clear instances with higher `position` upon completion
    # since this worker may not know about other bars #796
    if write_safe:
        # we think we know about other bars (currently only py3 threading)
        if n == 6:
            tqdm.write("n == 6 completed")


if __name__ == '__main__':
    freeze_support()  # for Windows support
    L = list(range(NUM_SUBITERS))[::-1]

    print("Manual nesting")
    for i in trange(16, desc="1"):
        for _ in trange(16, desc="2 @ %d" % i, leave=i % 2):
            sleep(0.01)

    print("Multi-processing")
    p = Pool(initializer=tqdm.set_lock, initargs=(tqdm.get_lock(),))
    p.map(progresser, L)

    # unfortunately need ncols
    # to print spaces over leftover multi-processing bars (#796)
    with tqdm(leave=False) as t:
        ncols = t.ncols or 80
    print(("{msg:<{ncols}}").format(msg="Multi-threading", ncols=ncols))

    # explicitly set just threading lock for nonblocking progress
    tqdm.set_lock(RLock())
    with ThreadPoolExecutor() as p:
        progresser_thread = partial(
            progresser, write_safe=not PY2, blocking=False)
        p.map(progresser_thread, L)
