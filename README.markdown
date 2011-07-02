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

To build, run `bjam`.

To install, `sudo make install`. The default prefix is `/usr/local`.

Here are some examples for installing:
* `sudo make install`
* `make install PREFIX="$HOME"/.local`
* `fakeroot make install PREFIX=/usr EXEC_PREFIX=/mnt/usr ADDRESS_MODEL=64 DESTROOT=./tm-bin SHARED_LIBRARY=libtm.dylib`

