#include <stdio.h>
#include <stdlib.h>
#include "libpnm.h"

int main(int argc, char *argv[]) {
    if (argc != 6) {
        printf("Invalid command argument");
        return 0;
    }

    int imageType = atoi(argv[1]);  //1 = pbm, 2 = pgm, 3 = ppm
    int width     = atoi(argv[2]);
    int height    = atoi(argv[3]);
    char *filename = argv[4];
    int format    = atoi(argv[5]);  //0 = ascii, 1 = raw
    bool raw = (format == 1);

    //make sure image dimesions are valid
    if (imageType == 1 || imageType == 2) {  //pbm or pgm
        if (width < 4 || width % 4 != 0) {
            printf("Error: Width of PBM/PGM image must be divisible by 4 and >= 4.\n");
            return 0;
        }
        if (height < 4 || height % 4 != 0) {
            printf("Error: Height of PBM/PGM image must be divisible by 4 and >= 4.\n");
            return 0;
        }
    }
    else if (imageType == 3) {  //ppm
        if (width < 6 || width % 6 != 0) {
            printf("Error: Width of PPM image must be divisible by 6 and >= 6.\n");
            return 0;
        }
        if (height < 4 || height % 4 != 0) {
            printf("Error: Height of PPM image must be divisible by 4 and >= 4.\n");
            return 0;
        }
    }
    else {
        printf("Invalid image type. Use 1 for PBM, 2 for PGM, or 3 for PPM.\n");
        return 0;
    }

    //pbm case
    if (imageType == 1) {
        struct PBM_Image img;
        if (create_PBM_Image(&img, width, height) != 0) {
            printf("Error creating PBM image.\n");
            return 0;
        }

        //fill all pixels black
        for (int r = 0; r < height; r++) {
            for (int c = 0; c < width; c++) {
                img.image[r][c] = BLACK;
            }
        }

        //white rectangle in middle
        int rectStartY = height / 4;
        int rectStartX = width / 4;
        int rectEndY = rectStartY * 3;
        int rectEndX = rectStartX * 3;

        //fill rectangle with white
        for(int y = rectStartY; y < rectStartY * 3; y++){
            for(int x = rectStartX; x < rectStartX * 3; x++){
                img.image[y][x] = WHITE;
            }
        }

        //draw black cross in the white rectangle
        int rectHeight = rectEndY - rectStartY;
        int rectWidth = rectEndX - rectStartX;
        
        //draw diagonal line from top-left to bottom-right
        for(int x = 0; x < rectWidth; x++){
            int y = rectStartY + (x * rectHeight) / rectWidth;
            img.image[y][rectStartX + x] = BLACK;
        }
        
        //draw diagonal line from top-right to bottom-left
        for(int x = 0; x < rectWidth; x++){
            int y = rectStartY + (x * rectHeight) / rectWidth;
            img.image[y][rectEndX - 1 - x] = BLACK;
        }

        //save image
        if (save_PBM_Image(&img, filename, raw) != 0)
        {
            printf("Error saving PBM image.\n");
            free_PBM_Image(&img);
            return 0;
        }

        printf("PBM image created successfully: %s\n", filename);
        free_PBM_Image(&img);

    }
    //pgm case
    else if (imageType == 2) {
        struct PGM_Image img;
        if (create_PGM_Image(&img, width, height, 255) != 0) {
            printf("Error creating PGM image.\n");
            return 0;
        }

        //fill all pixels black
        for (int r = 0; r < height; r++) {
            for (int c = 0; c < width; c++) {
                img.image[r][c] = 0;
            }
        }

        //white rectangle in middle
        int rectStartY = height / 4;
        int rectStartX = width / 4;
        int rectEndY = rectStartY * 3;
        int rectEndX = rectStartX * 3;

        //fill rectangle with white
        for(int y = rectStartY; y < rectStartY * 3; y++){
            for(int x = rectStartX; x < rectStartX * 3; x++){
                img.image[y][x] = 255;
            }
        }

        //calculate rectangle dimensions and center
        int rectHeight = rectEndY - rectStartY;
        int rectWidth = rectEndX - rectStartX;
        int centerY = rectStartY + rectHeight / 2;
        int centerX = rectStartX + rectWidth / 2;
        
        //create gradient triangles in rectangle
        for(int y = rectStartY; y < rectEndY; y++){
            for(int x = rectStartX; x < rectEndX; x++){
                //coordinates relative to center
                int dy = y - centerY;
                int dx = x - centerX;
                
                //determine which triangle pixel is in
                if (abs(dy * rectWidth) < abs(dx * rectHeight)) {
                    if (dx > 0) {
                        //right triangle
                        int grayScale = 255 - (255 * (rectEndX - x)) / (rectEndX - centerX);
                        img.image[y][x] = grayScale;

                    } else {
                        //left triangle
                        int grayScale = 255 - (255 * (x - rectStartX)) / (centerX - rectStartX);
                        img.image[y][x] = grayScale;
                    }
                } else {
                    if (dy > 0) {
                        //bottom triangle
                        int grayScale = 255 - (255 * (rectEndY - y)) / (rectEndY - centerY);
                        img.image[y][x] = grayScale;
                    } else {
                        //top triangle
                        int grayScale = 255 - (255 * (y - rectStartY)) / (centerY - rectStartY);
                        img.image[y][x] = grayScale;
                    }
                }
            }
        }

        //save image
        if (save_PGM_Image(&img, filename, raw) != 0)
        {
            printf("Error saving PGM image.\n");
            free_PGM_Image(&img);
            return 0;
        }

        printf("PGM image created successfully: %s\n", filename);
        free_PGM_Image(&img);
        
    }
    //ppm case
    else if (imageType == 3) {
        struct PPM_Image img;
        struct PGM_Image pgm_img1, pgm_img2, pgm_img3;

        if (create_PPM_Image(&img, width, height, 255) != 0) {
            printf("Error creating PPM image.\n");
            return 0;
        }

        //top half split into 3 color sections
        int topSectionWidth = width / 3;

        for (int y = 0; y < height/2; y++) {
            for (int x = 0; x < width; x++) {
                if (x < topSectionWidth) {
                    //red section: red to white gradient
                    img.image[y][x][RED] = 255;
                    img.image[y][x][GREEN] = (255 * y) / (height / 2);
                    img.image[y][x][BLUE] = (255 * y) / (height / 2);

                } else if (x < topSectionWidth * 2) {
                    //green section: white to green gradient
                    img.image[y][x][RED] = 255 - (255 * y) / (height / 2);
                    img.image[y][x][GREEN] = 255;
                    img.image[y][x][BLUE] = 255 - (255 * y) / (height / 2);
                } else {
                    //blue section: blue to white gradient
                    img.image[y][x][RED] = (255 * y) / (height / 2);
                    img.image[y][x][GREEN] = (255 * y) / (height / 2);
                    img.image[y][x][BLUE] = 255;
                }
            }
        }

        //bottom half split into 2 grayscale sections
        int bottomSectionWidth = width / 2;
        
        for (int y = height/2; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int relativeY = y - height/2;

                if (x < bottomSectionWidth) {
                    //left section: white to black gradient
                    int grayScale = 255 - (255 * relativeY) / (height / 2);
                    img.image[y][x][RED] = grayScale;
                    img.image[y][x][GREEN] = grayScale;
                    img.image[y][x][BLUE] = grayScale;
                } else {
                    //right section: black to white gradient
                    int grayScale = (255 * relativeY) / (height / 2);
                    img.image[y][x][RED] = grayScale;
                    img.image[y][x][GREEN] = grayScale;
                    img.image[y][x][BLUE] = grayScale;
                }
            }
        }

        copy_PPM_to_PGM(&img, &pgm_img1, RED);
        copy_PPM_to_PGM(&img, &pgm_img2, BLUE);
        copy_PPM_to_PGM(&img, &pgm_img3, GREEN);

        //save images
        if (save_PPM_Image(&img, filename, raw) != 0)
        {
            printf("Error saving PPM image.\n");
            free_PPM_Image(&img);
            return 0;
        }
        if (save_PGM_Image(&pgm_img1, "PGM_COPY_RED.pgm", raw) != 0)
        {
            printf("Error saving PGM image.\n");
            free_PGM_Image(&pgm_img1);
            return 0;
        }
        if (save_PGM_Image(&pgm_img2, "PGM_COPY_BLUE.pgm", raw) != 0)
        {
            printf("Error saving PGM image.\n");
            free_PGM_Image(&pgm_img2);
            return 0;
        }
        if (save_PGM_Image(&pgm_img3, "PGM_COPY_GREEN.pgm", raw) != 0)
        {
            printf("Error saving PGM image.\n");
            free_PGM_Image(&pgm_img3);
            return 0;
        }

        printf("PPM image created successfully: %s\n", filename);
        free_PPM_Image(&img);
        free_PGM_Image(&pgm_img1);
        free_PGM_Image(&pgm_img2);
        free_PGM_Image(&pgm_img3);


    }
    else {
        printf("Invalid image type. Use 1 for PBM, 2 for PGM, or 3 for PPM.\n");
        return 0;
    }

    return 0;
}