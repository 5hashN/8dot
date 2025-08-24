# atedot

a play on 8dot, which is a play on... you know, the number of dots that can be in a braille character ⣿

lightweight terminal plotting tool written in C without extra deps for simple graphing using braille characters

the aim is to make it similar to gnuplot and visualise data within the terminal

works best with monospaced fonts

## build

```bash
mkdir build && cd build
cmake ..
make -j
make install  # installs to ~/.local/bin/atedot
```

```bash
mkdir build; cd build
cmake .. -G "MinGW Makefiles"   # or "NMake Makefiles" if using MSVC
cmake --build . --config Release
cmake --install .               # installs to %LOCALAPPDATA%\atedot\bin\atedot.exe
```

makefile works too

## usage

```bash
./atedot
```

or

```bash
./examples/demo
```

running the demo should print

```text
⠑⠢⡀                                     ⡇                                    ⢀⠔⠊
  ⠈⠑⢄⡀                                  ⡇                                 ⢀⡠⠊⠁
    ⡏⠉⠫⢍⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⡏⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⡩⠝⠉⢹
    ⡇  ⢀⠕⠫⡉⠑⢄                           ⡇      ⢀⠔⠉⠉⠑⢄                ⢀⠔⠊   ⢸
    ⡇ ⢀⠂  ⠈⠑⢄⣂                          ⡇     ⢀⠂     ⢂            ⢀⡠⠊⠁     ⢸
    ⡇⢀⠂      ⠈⢢⢄                        ⡇    ⢀⠂       ⢂         ⡠⠔⠁        ⢸
    ⡇⠄         ⠄⠑⠢⡀                     ⡇    ⠄         ⠄     ⢀⠔⠊           ⢸
    ⡏          ⠈⡀ ⠈⠑⢄⡀                  ⡇   ⡈          ⠈⡀ ⢀⡠⠊⠁             ⢸
   ⠠⡇           ⠠    ⠈⠢⢄                ⡇  ⠠            ⡠⠔⠁                ⢸
   ⠄⡇            ⠄      ⠑⠢⡀             ⡇  ⠄         ⢀⠔⠊ ⠄                 ⢸
  ⠐ ⡇            ⠐        ⠈⠑⢄⡀          ⡇ ⠐       ⢀⡠⠊⠁   ⠐                 ⢸
  ⠂ ⡇             ⠂          ⠈⠢⢄        ⡇ ⠂     ⡠⠔⠁       ⠂                ⢸
 ⠈  ⡇             ⠈             ⠑⠢⡀     ⡇⠈   ⢀⠔⠊          ⠈                ⢸
 ⠁  ⡇              ⠁              ⠈⠑⢄⡀  ⡇⠁⢀⡠⠊⠁             ⠁               ⢸
⠈   ⡇              ⠈⡀                ⠈⠢⢄⡯⠔⠁                ⠈⡀              ⢸
⠉⠉⠉⠉⡏⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⢉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⢉⠝⢋⡟⠫⡉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⢉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⢹⠉⠉⠉⢉
    ⡇                ⡀            ⢀⡠⠊⠁ ⡀⡇ ⠈⠑⢄⡀               ⡀             ⢸   ⡀
    ⡇                ⢀          ⡠⠔⠁   ⢀ ⡇    ⠈⠢⢄             ⢀             ⢸  ⢀
    ⡇                 ⠄      ⢀⠔⠊      ⠄ ⡇       ⠑⠢⡀           ⠄            ⢸  ⠄
    ⡇                 ⠠   ⢀⡠⠊⠁       ⠠  ⡇         ⠈⠑⢄⡀        ⠠            ⢸ ⠠
    ⡇                  ⠂⡠⠔⠁          ⠂  ⡇            ⠈⠢⢄       ⠂           ⢸ ⠂
    ⡇                ⢀⠔⠚            ⠐   ⡇               ⠑⠢⡀    ⠐           ⢸⠐
    ⡇             ⢀⡠⠊⠁  ⢁          ⢀⠁   ⡇                 ⠈⠑⢄⡀  ⢁          ⢸⠁
    ⡇           ⡠⠔⠁      ⠂         ⠂    ⡇                    ⠈⠢⢄ ⠂         ⢺
    ⡇        ⢀⠔⠊         ⠈⠄       ⠌     ⡇                       ⠑⠪⡄       ⠌⢸
    ⡇     ⢀⡠⠊⠁            ⠈⠄     ⠌      ⡇                         ⠈⠕⢄⡀   ⠌ ⢸
    ⡇   ⡠⠔⠁                ⠈⠢⣀⢀⡠⠊       ⡇                          ⠈⠢⣈⢢⣤⠊  ⢸
    ⣇⣀⣔⣊⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣁⣀⣀⣀⣀⣀⣀⣀⣀⣀⣇⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣁⣀⣑⣢⣀⣸
  ⢀⡠⠊⠁                                  ⡇                                 ⠈⠑⢄⡀
⡠⠔⠁                                     ⡇                                    ⠈⠢⢄
```

but in color

## fun

|0|1|2|3|4|5|6|7|8|9|A|B|C|D|E|F|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
| |⠁|⠂|⠃|⠄|⠅|⠆|⠇|⠈|⠉|⠊|⠋|⠌|⠍|⠎|⠏|
|⠐|⠑|⠒|⠓|⠔|⠕|⠖|⠗|⠘|⠙|⠚|⠛|⠜|⠝|⠞|⠟|
|⠠|⠡|⠢|⠣|⠤|⠥|⠦|⠧|⠨|⠩|⠪|⠫|⠬|⠭|⠮|⠯|
|⠰|⠱|⠲|⠳|⠴|⠵|⠶|⠷|⠸|⠹|⠺|⠻|⠼|⠽|⠾|⠿|
|⡀|⡁|⡂|⡃|⡄|⡅|⡆|⡇|⡈|⡉|⡊|⡋|⡌|⡍|⡎|⡏|
|⡐|⡑|⡒|⡓|⡔|⡕|⡖|⡗|⡘|⡙|⡚|⡛|⡜|⡝|⡞|⡟|
|⡠|⡡|⡢|⡣|⡤|⡥|⡦|⡧|⡨|⡩|⡪|⡫|⡬|⡭|⡮|⡯|
|⡰|⡱|⡲|⡳|⡴|⡵|⡶|⡷|⡸|⡹|⡺|⡻|⡼|⡽|⡾|⡿|
|⢀|⢁|⢂|⢃|⢄|⢅|⢆|⢇|⢈|⢉|⢊|⢋|⢌|⢍|⢎|⢏|
|⢐|⢑|⢒|⢓|⢔|⢕|⢖|⢗|⢘|⢙|⢚|⢛|⢜|⢝|⢞|⢟|
|⢠|⢡|⢢|⢣|⢤|⢥|⢦|⢧|⢨|⢩|⢪|⢫|⢬|⢭|⢮|⢯|
|⢰|⢱|⢲|⢳|⢴|⢵|⢶|⢷|⢸|⢹|⢺|⢻|⢼|⢽|⢾|⢿|
|⣀|⣁|⣂|⣃|⣄|⣅|⣆|⣇|⣈|⣉|⣊|⣋|⣌|⣍|⣎|⣏|
|⣐|⣑|⣒|⣓|⣔|⣕|⣖|⣗|⣘|⣙|⣚|⣛|⣜|⣝|⣞|⣟|
|⣠|⣡|⣢|⣣|⣤|⣥|⣦|⣧|⣨|⣩|⣪|⣫|⣬|⣭|⣮|⣯|
|⣰|⣱|⣲|⣳|⣴|⣵|⣶|⣷|⣸|⣹|⣺|⣻|⣼|⣽|⣾|⣿|

[picked from](https://en.wikipedia.org/wiki/Braille_Patterns#Block)
