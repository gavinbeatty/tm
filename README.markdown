tm
====
Gavin Beatty <gavinbeatty@gmail.com>

tm: simple timing functions in C.

License
-------
Copyright and license information is available in the included LICENSE.txt.

Install
-------
To configure, just run `make configure`.

To build, run `bjam`. By default, only the static library is built. Build the
shared library with `bjam link=shared`.

To install, `sudo bjam install`. The default prefix is `/usr/local`.

Here are some examples for installing:
* `sudo bjam install link=shared address-model=64 arch=x86_64`
* `bjam install -sPREFIX="$HOME"/.local`
* `fakeroot bjam install -sPREFIX=/usr -sEXEC_PREFIX=/exec/usr -sDESTROOT=./tm-bin`

