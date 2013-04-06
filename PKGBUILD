pkgname=dwm
pkgver=6.0
pkgrel=1
pkgdesc="A dynamic window manager for X"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
options=(zipman)
depends=('pango')
source=(http://dl.suckless.org/dwm/dwm-$pkgver.tar.gz
	config.h)
_patches=(dwm-6.0-custom.patch)
source=(${source[@]} ${_patches[@]})
md5sums=('8bb00d4142259beb11e13473b81c0857'
         'e8e7a2d601bf2f979638b891269da334'
         'b8f31fba2b7decb2137c1b7b932e2be2')

build() {
  cd $srcdir/$pkgname-$pkgver

  for p in "${_patches[@]}"; do
    msg "$p"
    patch -N < ../$p
  done

  cp $srcdir/config.h config.h

  make INCS="`pkg-config --cflags pangoxft`" LIBS="`pkg-config --libs x11 pangoxft`"
}

package() {
  cd $srcdir/$pkgname-$pkgver
  make PREFIX=/usr DESTDIR=$pkgdir install
  install -m644 -D README $pkgdir/usr/share/doc/$pkgname/README
  install -m644 -D LICENSE $pkgdir/usr/share/licenses/$pkgname/LICENSE
}
