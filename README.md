**Fast Website Content**(fwc) is more than just a command line tool; it's a warm addition to your coding toolkit, designed to make fetching website content a cozy experience. Crafted in C, it seamlessly integrates into your projects, enveloping you in comfort while you work, aiding productivity. Also, it is faster **around 1.5x-2x times than wget** (see in [tests](#Tests))

## Installation

Using [vWv](https://github.com/dizabanik/vWv):

```bash
vWv fwc
```


Without vWv:

```bash
git clone https://github.com/Dizabanik/fwc.git ; cd fwc ; sudo mv fwc /usr/local/bin/ ; cd ../ ; rm -rf fwc ; chmod +x /usr/local/bin/fwc
```


## Usage:

Using fwc is very simple. Just like this:
```bash
fwc [link]
```

For example:
```bash
fwc https://github.com/Dizabanik/fwc
```

To use the C code, you should include `fwc.h` file and add `fwc.c` into sources to build. 
**At this moment, fwc uses OpenSSL, but I will rewrite SSL function in next versions, so project wouldn't have any dependencies**
## Tests

Feel the cozy embrace of fwc as it performs faster than your typical website content fetcher. See for yourself:

### wget
```bash
$ for i in (seq 10); time wget github.com/ -q -O - | grep Executed
	end

________________________________________________________
Executed in  395.90 millis    fish           external
   usr time   40.33 millis    0.00 millis   40.33 millis
   sys time   16.09 millis    1.29 millis   14.79 millis


________________________________________________________
Executed in  391.30 millis    fish           external
   usr time   44.56 millis    0.00 millis   44.56 millis
   sys time    7.98 millis    1.59 millis    6.39 millis


________________________________________________________
Executed in  383.98 millis    fish           external
   usr time   44.48 millis    0.00 millis   44.48 millis
   sys time    4.85 millis    1.31 millis    3.54 millis


________________________________________________________
Executed in  383.90 millis    fish           external
   usr time   37.97 millis    0.00 millis   37.97 millis
   sys time   16.39 millis    1.08 millis   15.32 millis


________________________________________________________
Executed in  364.27 millis    fish           external
   usr time   42.08 millis    0.00 millis   42.08 millis
   sys time    7.69 millis    1.26 millis    6.43 millis


________________________________________________________
Executed in  365.14 millis    fish           external
   usr time   43.71 millis    0.00 millis   43.71 millis
   sys time    7.63 millis    1.08 millis    6.55 millis


________________________________________________________
Executed in  367.22 millis    fish           external
   usr time   38.34 millis    0.00 millis   38.34 millis
   sys time   11.49 millis    1.17 millis   10.32 millis


________________________________________________________
Executed in  364.70 millis    fish           external
   usr time   33.74 millis    0.00 millis   33.74 millis
   sys time   14.94 millis    1.10 millis   13.84 millis


________________________________________________________
Executed in  384.08 millis    fish           external
   usr time   38.07 millis    0.00 millis   38.07 millis
   sys time   11.60 millis    1.12 millis   10.48 millis


________________________________________________________
Executed in  462.52 millis    fish           external
   usr time   45.84 millis    0.00 millis   45.84 millis
   sys time    8.29 millis    1.62 millis    6.68 millis
```


### fwc

```bash
$ for i in (seq 10); time fwc github.com/ -q -O - | grep Executed
    end

________________________________________________________
Executed in  247.32 millis    fish           external
   usr time    7.78 millis    1.03 millis    6.75 millis
   sys time    9.60 millis    0.12 millis    9.48 millis


________________________________________________________
Executed in  248.72 millis    fish           external
   usr time    0.89 millis  892.00 micros    0.00 millis
   sys time   14.63 millis  361.00 micros   14.27 millis


________________________________________________________
Executed in  263.17 millis    fish           external
   usr time    4.12 millis  761.00 micros    3.36 millis
   sys time   12.10 millis  308.00 micros   11.79 millis


________________________________________________________
Executed in  264.70 millis    fish           external
   usr time   12.41 millis  811.00 micros   11.60 millis
   sys time    3.50 millis  329.00 micros    3.17 millis


________________________________________________________
Executed in  261.92 millis    fish           external
   usr time    9.19 millis  724.00 micros    8.46 millis
   sys time    6.10 millis  294.00 micros    5.81 millis


________________________________________________________
Executed in  254.76 millis    fish           external
   usr time   13.09 millis  597.00 micros   12.50 millis
   sys time    0.24 millis  242.00 micros    0.00 millis


________________________________________________________
Executed in  251.69 millis    fish           external
   usr time    8.15 millis    0.00 millis    8.15 millis
   sys time    6.60 millis    1.20 millis    5.40 millis


________________________________________________________
Executed in  244.08 millis    fish           external
   usr time   11.09 millis    0.00 millis   11.09 millis
   sys time    4.03 millis    1.20 millis    2.83 millis


________________________________________________________
Executed in  269.58 millis    fish           external
   usr time    6.88 millis  715.00 micros    6.16 millis
   sys time    9.64 millis  454.00 micros    9.19 millis


________________________________________________________
Executed in  267.73 millis    fish           external
   usr time    6.90 millis  755.00 micros    6.14 millis
   sys time    9.69 millis  306.00 micros    9.38 millis
```
