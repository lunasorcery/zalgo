# zalgo

**zalgo** is a small utility that reads stdin and corrupts it with combining diacritics.

### Options:

```
-h,--help      Display this help message
-u,--up        Fuck up going up
-m,--middle    Fuck up the middle
-d,--down      Fuck up going down
-s,--strength  Choose how strong to fuck up, from 0-3:
               0: micro fuck up
               1: mini fuck up
               2: normal fuck up
               3: maxi fuck up
```

By default, it will act as if you'd specified `-md -s1`.


### Example usage:

```
luna:~/code/zalgo$ make | zalgo
m̢̥a̙͈̖̝̩̘k̡̖̩̹̤͈͙̖e̬̮̼͎̥͟ͅ: Ņ̲̟͎͓̭o̧͔͙̗͓t̥̜͖̥h͈̺į͇n͕̪̻̫̹g̫͈̲͙͕͜ t̯͇̙o b͚e̶͇ d͙o͍n̳̣̠͝e͔̠͕̠͓ f̳̝o̲̬͎͍̲͉͍r͏ `a̵̩̯̬̣̫̹̤l̛̼̪̥͚̫̱l̼͔̙̯̜͉'.
```

Adapted from the zalgo text generator at eeemo.net
