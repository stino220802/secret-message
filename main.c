#include <stdio.h>
#include <stdlib.h>

#define __DEBUG
#define BMPINPUTFILE "test.bmp"
int convertToBits(unsigned char* inputPixels, int imageSize);
int main()
{
    commandos();
#ifdef __DEBUG
    printf("DEBUG info: BMP transformer\n");
#endif

    FILE* inputFilePointer = fopen(BMPINPUTFILE, "rb"); //maak een file pointer naar de afbeelding
    if(inputFilePointer == NULL) //Test of het open van de file gelukt is!
    {
        printf("Something went wrong while trying to open %s\n", BMPINPUTFILE);
        exit(EXIT_FAILURE);
    }

#ifdef __DEBUG
    printf("DEBUG info: Opening File OK: %s\n", BMPINPUTFILE);
#endif

    unsigned char bmpHeader[54]; // voorzie een array van 54-bytes voor de BMP Header
    fread(bmpHeader, sizeof(unsigned char), 54, inputFilePointer); // lees de 54-byte header

    //Informatie uit de header (wikipedia)
    // haal de hoogte en breedte uit de header
    int breedte = *(int*)&bmpHeader[18];
    int hoogte = *(int*)&bmpHeader[22];

#ifdef __DEBUG
    printf("DEBUG info: breedte = %d\n", breedte);
    printf("DEBUG info: hoogte = %d\n", hoogte);
#endif

    int imageSize = 3 * breedte * hoogte; //ieder pixel heeft 3 byte data: rood, groen en blauw (RGB)
    unsigned char* inputPixels = (unsigned char *) calloc(imageSize, sizeof(unsigned char)); // allocate een array voor alle pixels



    fread(inputPixels, sizeof(unsigned char), imageSize, inputFilePointer); // Lees alle pixels (de rest van de file
    fclose(inputFilePointer);

    for(int i =0; i < imageSize-2; i+=3)
    {
        printf("pixel %d: R= %d, G=%d, B=%d\n", i, inputPixels[i+2], inputPixels[i+1], inputPixels[i]);
    }
    convertToBits(inputPixels, imageSize);

    fclose(inputFilePointer);
    free(inputPixels);

    return 0;
}
int convertToBits(unsigned char* inputPixels, int imageSize){
    int r = 0;
    long rBin = 0;
    int g = 0;
    long gBin = 0;
    int b = 0;
    long bBin = 0;
    int rem , temp = 1;
    for(int i = 0; i < imageSize-2; i += 3){
        r = inputPixels[i+2];
        g = inputPixels[i+1];
        b = inputPixels[i];
        while (b != 0){
            rem = b%2;
            b = b/2;
            bBin = bBin + rem*temp;
            temp =temp *10;
        }
        while (g != 0){
            rem = g%2;
            g = g/2;
            gBin = gBin + rem*temp;
            temp =temp *10;
        }
        while (r != 0){
            rem = r%2;
            r = r/2;
            rBin = rBin + rem*temp;
            temp =temp *10;
        }
    }
    printf("%ld\n", bBin);
    printf("%ld\n", gBin);
    printf("%ld\n", rBin);
    return 0;
}


}

/*struct pixelgroep{
    int aantalp = 0;
    int groep = 0;
};*/