## Building and Running

Install `meson ninja` as well as `cjson libcurl` as development libraries.

Run 

    meson build
    cd build
    ninja && ./hyfetch

Installation

    rm -rf build
    meson --prefix=/usr --buildtype=plain build
    cd build
    sudo ninja install
    ; sudo ninja uninstall

