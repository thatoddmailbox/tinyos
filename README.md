# tinyos
## Things you need for MacOS
* Xcode dev tools (clang and llvm stuff)
* CMake
* `brew install binutils bison flex gettext mtools nasm xorriso`
* objconv and GRUB (see hexos)
* [lld](http://lld.llvm.org/)
* qemu

## Compiling grub
objconv stuff goes here
```bash
objconv stuff

wget ftp://ftp.gnu.org/gnu/grub/grub-2.02.tar.gz
tar xvf grub-2.02.tar.gz
cd grub-2.02
./autogen.sh
./configure --target=x86_64 --with-platform=pc
make
sudo make install
sudo grub-mkfont -o /usr/local/share/grub/unicode.pf2 /path/to/unifont.ttf
```

## Compiling lld
Follow instructions on website