## Create XBitMap (XBM) Image

### Install tools

```sh
sudo pacman -S imagemagick
mogrify -version
```

### Change image to monochrome

```sh
convert logo128x64.png -set colorspace Gray -separate -average logo.png
```

### Change image to XBM

```sh
mogrify -resize 128x64 +dither -format xbm logo.png
cat logo.xbm | sed "s#static char#static unsigned char#" > ../logo.xbm
```

### Remove unused

```sh
rm -f logo.xbm logo.png logo128x64.png
```