#!/bin/bash
# create multiresolution windows icon
#mainnet
ICON_SRC=../../src/qt/res/icons/mubdi.png
ICON_DST=../../src/qt/res/icons/mubdi.ico
convert ${ICON_SRC} -resize 16x16 mubdi-16.png
convert ${ICON_SRC} -resize 32x32 mubdi-32.png
convert ${ICON_SRC} -resize 48x48 mubdi-48.png
convert mubdi-16.png mubdi-32.png mubdi-48.png ${ICON_DST}
#testnet
ICON_SRC=../../src/qt/res/icons/mubdi_testnet.png
ICON_DST=../../src/qt/res/icons/mubdi_testnet.ico
convert ${ICON_SRC} -resize 16x16 mubdi-16.png
convert ${ICON_SRC} -resize 32x32 mubdi-32.png
convert ${ICON_SRC} -resize 48x48 mubdi-48.png
convert mubdi-16.png mubdi-32.png mubdi-48.png ${ICON_DST}
rm mubdi-16.png mubdi-32.png mubdi-48.png
