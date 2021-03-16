#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "bmpheader.h"

TBitmap initialize_BMP(int w, int h)
{
    TBitmap bitmap;
    bitmap.height = h;
    bitmap.width = w;

    bitmap.pixel = malloc(h * sizeof(TPixel*));
    int i;
    for (i = 0; i < h; i++) {
        bitmap.pixel[i] = malloc(w * sizeof(TPixel));
    }
    return bitmap;
}

void write_BMP(const char filename[], TFileheader fileheader,
                      TInfoheader infoheader, TBitmap bitmap)
{
    FILE *in = fopen(filename, "wb");

    fwrite(&fileheader, sizeof(TFileheader), 1, in);
    fwrite(&infoheader, sizeof(TInfoheader), 1, in);

    int x = ftell(in);
    int y = fileheader.offset_bits;
    int padding = (infoheader.width * sizeof(TPixel)) -
                  (infoheader.width * sizeof(TPixel) / 4) * 4;

    int i,j;
    for (i = 0; i < y - x; i++)
    fputc(0, in);

    for (i = infoheader.height - 1; i >= 0; i--) {
        fwrite(bitmap.pixel[i], sizeof(TPixel), infoheader.width, in);
        for (j = 0; j < padding; j++) {
            fputc(0, in);
        }
    }
    fclose(in);
}


TInfoheader setInfoheader(TBitmap bitmap)
{
    TInfoheader infoheader;
    infoheader.dibheadersize = 40;
    infoheader.width = bitmap.width;
    infoheader.height = bitmap.height;
    infoheader.planes = 1;
    infoheader.bitsperpixel = 24;
    infoheader.compression = 0;
    infoheader.ypixelpermeter = 0;
    infoheader.xpixelpermeter = 0;
    infoheader.numcolorspallette = 0;
    infoheader.mostimpcolor = 0;

    // padding pe o singura linie
    int padding = (infoheader.width * sizeof(TPixel)) -
                    (infoheader.width * sizeof(TPixel) / 4) * 4;

    padding *= infoheader.height; // padding pentru toata imaginea

    infoheader.imagesize = infoheader.width * infoheader.height * sizeof(TPixel) +
                           padding;
    return infoheader;
}

TFileheader setFileheader(TInfoheader infoheader)
{
    TFileheader fileheader;
    fileheader.signature[0] = 0x42; // 'B' - ascii
    fileheader.signature[1] = 0x4d; // 'M' - ascii
    fileheader.offset_bits = 54;
    fileheader.filesize = infoheader.imagesize + sizeof(TFileheader) +
                          sizeof(TInfoheader);
    return fileheader;
}


int main()
{
    int i,j;

    ////////////creare piesa_S/////////////
    TBitmap bitmap_S = initialize_BMP(50, 40);
    TInfoheader infoheader_S = setInfoheader(bitmap_S);
    TFileheader fileheader_S = setFileheader(infoheader_S);

    for (i = 0; i < bitmap_S.height; i++) {
        for (j = 0; j < bitmap_S.width; j++) {
            if(i >= 10 && i <= 19 && j >= 20 && j <= 39)
            {
                bitmap_S.pixel[i][j].r = 255;
                bitmap_S.pixel[i][j].g = 0;
                bitmap_S.pixel[i][j].b = 0;
            }
            else if(i >= 20 && i <= 29 && j >= 10 && j <= 29)
            {
                bitmap_S.pixel[i][j].r = 255;
                bitmap_S.pixel[i][j].g = 0;
                bitmap_S.pixel[i][j].b = 0;
            }
            else
            {
                bitmap_S.pixel[i][j].r = 255;
                bitmap_S.pixel[i][j].g = 255;
                bitmap_S.pixel[i][j].b = 255;
            }
        }
    }

    write_BMP("piesa_S.bmp", fileheader_S, infoheader_S, bitmap_S);

    /////////////////Crearea piesei I//////////////
    TBitmap bitmap_I = initialize_BMP(30, 60);
    TInfoheader infoheader_I = setInfoheader(bitmap_I);
    TFileheader fileheader_I = setFileheader(infoheader_I);

    for (i = 0; i < bitmap_I.height; i++) {
        for (j = 0; j < bitmap_I.width; j++) {
            if(i >= 10 && i <= 49 && j >= 10 && j <= 19)
            {
                bitmap_I.pixel[i][j].r = 0;
                bitmap_I.pixel[i][j].g = 0;
                bitmap_I.pixel[i][j].b = 255;
            }
            else
            {
                bitmap_I.pixel[i][j].r = 255;
                bitmap_I.pixel[i][j].g = 255;
                bitmap_I.pixel[i][j].b = 255;
            }
        }
    }

    write_BMP("piesa_I.bmp", fileheader_I, infoheader_I, bitmap_I);

        /////////////////Crearea piesei O//////////////
    TBitmap bitmap_O = initialize_BMP(40, 40);
    TInfoheader infoheader_O = setInfoheader(bitmap_O);
    TFileheader fileheader_O = setFileheader(infoheader_O);

    for (i = 0; i < bitmap_O.height; i++) {
        for (j = 0; j < bitmap_O.width; j++) {
            if(i >= 10 && i <= 29 && j >= 10 && j <= 29)
            {
                bitmap_O.pixel[i][j].r = 255;
                bitmap_O.pixel[i][j].g = 255;
                bitmap_O.pixel[i][j].b = 0;
            }
            else
            {
                bitmap_O.pixel[i][j].r = 255;
                bitmap_O.pixel[i][j].g = 255;
                bitmap_O.pixel[i][j].b = 255;
            }
        }
    }

    write_BMP("piesa_O.bmp", fileheader_O, infoheader_O, bitmap_O);

        /////////////////Crearea piesei Z//////////////
    TBitmap bitmap_Z = initialize_BMP(50, 40);
    TInfoheader infoheader_Z = setInfoheader(bitmap_Z);
    TFileheader fileheader_Z = setFileheader(infoheader_Z);

    for (i = 0; i < bitmap_Z.height; i++) {
        for (j = 0; j < bitmap_Z.width; j++) {
            if(i >= 10 && i <= 19 && j >= 10 && j <= 29)
            {
                bitmap_Z.pixel[i][j].r = 0;
                bitmap_Z.pixel[i][j].g = 255;
                bitmap_Z.pixel[i][j].b = 0;
            }
            else if(i >= 20 && i <= 29 && j >= 20 && j <= 39)
            {
                bitmap_Z.pixel[i][j].r = 0;
                bitmap_Z.pixel[i][j].g = 255;
                bitmap_Z.pixel[i][j].b = 0;
            }
            else
            {
                bitmap_Z.pixel[i][j].r = 255;
                bitmap_Z.pixel[i][j].g = 255;
                bitmap_Z.pixel[i][j].b = 255;
            }
        }
    }

    write_BMP("piesa_Z.bmp", fileheader_Z, infoheader_Z, bitmap_Z);

        /////////////////Crearea piesei L//////////////
    TBitmap bitmap_L = initialize_BMP(40, 50);
    TInfoheader infoheader_L = setInfoheader(bitmap_L);
    TFileheader fileheader_L = setFileheader(infoheader_L);

    for (i = 0; i < bitmap_L.height; i++) {
        for (j = 0; j < bitmap_L.width; j++) {
            if(i >= 10 && i <= 29 && j >= 10 && j <= 19)
            {
                bitmap_L.pixel[i][j].r = 255;
                bitmap_L.pixel[i][j].g = 140;
                bitmap_L.pixel[i][j].b = 0;
            }
            else if(i >= 30 && i <= 39 && j >= 10 && j <= 29)
            {
                bitmap_L.pixel[i][j].r = 255;
                bitmap_L.pixel[i][j].g = 140;
                bitmap_L.pixel[i][j].b = 0;
            }
            else
            {
                bitmap_L.pixel[i][j].r = 255;
                bitmap_L.pixel[i][j].g = 255;
                bitmap_L.pixel[i][j].b = 255;
            }
        }
    }

    write_BMP("piesa_L.bmp", fileheader_L, infoheader_L, bitmap_L);

    /////////////////Crearea piesei J//////////////
    TBitmap bitmap_J = initialize_BMP(40, 50);
    TInfoheader infoheader_J = setInfoheader(bitmap_J);
    TFileheader fileheader_J = setFileheader(infoheader_J);

    for (i = 0; i < bitmap_J.height; i++) {
        for (j = 0; j < bitmap_J.width; j++) {
            if(i >= 10 && i <= 29 && j >= 20 && j <= 29)
            {
                bitmap_J.pixel[i][j].r = 255;
                bitmap_J.pixel[i][j].g = 0;
                bitmap_J.pixel[i][j].b = 255;
            }
            else if(i >= 30 && i <= 39 && j >= 10 && j <= 29)
            {
                bitmap_J.pixel[i][j].r = 255;
                bitmap_J.pixel[i][j].g = 0;
                bitmap_J.pixel[i][j].b = 255;
            }
            else
            {
                bitmap_J.pixel[i][j].r = 255;
                bitmap_J.pixel[i][j].g = 255;
                bitmap_J.pixel[i][j].b = 255;
            }
        }
    }

    write_BMP("piesa_J.bmp", fileheader_J, infoheader_J, bitmap_J);

    /////////////////Crearea piesei T//////////////
    TBitmap bitmap_T = initialize_BMP(50, 40);
    TInfoheader infoheader_T = setInfoheader(bitmap_T);
    TFileheader fileheader_T = setFileheader(infoheader_T);

    for (i = 0; i < bitmap_T.height; i++) {
        for (j = 0; j < bitmap_T.width; j++) {
            if(i >= 10 && i <= 19 && j >= 10 && j <= 39)
            {
                bitmap_T.pixel[i][j].r = 130;
                bitmap_T.pixel[i][j].g = 0;
                bitmap_T.pixel[i][j].b = 255;
            }
            else if(i >= 20 && i <= 29 && j >= 20 && j <= 29)
            {
                bitmap_T.pixel[i][j].r = 130;
                bitmap_T.pixel[i][j].g = 0;
                bitmap_T.pixel[i][j].b = 255;
            }
            else
            {
                bitmap_T.pixel[i][j].r = 255;
                bitmap_T.pixel[i][j].g = 255;
                bitmap_T.pixel[i][j].b = 255;
            }
        }
    }

    write_BMP("piesa_T.bmp", fileheader_T, infoheader_T, bitmap_T);
    return 0;
}



