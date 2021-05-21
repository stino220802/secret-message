#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define __DEBUG
#define BMPINPUTFILE "test.bmp"
#define TEKSTINPUT "tekst.txt"
char* changeLetterToBit(char* message);
void convertPixelsToBits(unsigned char* inputPixels, int imageSize, int buf [] );
void Fileopeningconvert();
void Inputbmp();
int main(int argc, char* argv[])
{
  /*  for(int i = 0; i<argc;i++){
        printf("argument count: %D\n",argc)
    }

    if(argc < 1 && strcmp(argv[1],"-s") == 0){
        Fileopeningconvert();
    }
    */
    Fileopeningconvert();
    Inputbmp();
#ifdef __DEBUG
    printf("DEBUG info: BMP transformer\n");
#endif

  /*  FILE* inputFilePointer = fopen(BMPINPUTFILE, "rb"); //maak een file pointer naar de afbeelding
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

    for(int i =0; i < imageSize-2; i+=3)// uit de vb code
    {
        printf("pixel %d: R= %d, G=%d, B=%d\n", i, inputPixels[i+2], inputPixels[i+1], inputPixels[i]);

   */ }
   /* int pixelsBinair[imageSize];
    convertPixelsToBits(inputPixels, imageSize, pixelsBinair);
    //char* output = changeLSB(pixelsBinair, messageBinair, imageSize);
    for(int i =0; i < imageSize-2; i+=3)// uit de zelfgemaakte code!!!
    {
        printf("pixel %d | R %d G %d B %d\n " , i ,pixelsBinair[i], pixelsBinair[i+1], pixelsBinair[i+2]);

    }

    fclose(inputFilePointer);
    free(inputPixels);

    return 0;
}*/
void convertPixelsToBits(unsigned char* inputPixels, int imageSize, int buf[]) {

    for (int i = 0; i < imageSize - 2; i += 3) {
        long bBin = 0;
        int b = 0;
        int brem, btemp = 1;
        int grem, gtemp = 1;
        int rrem, rtemp = 1;
        int r = 0;
        long rBin = 0;
        int g = 0;
        long gBin = 0;

        r = inputPixels[i + 2];
        g = inputPixels[i + 1];
        b = inputPixels[i];
        while (b != 0) {
            brem = b % 2;
            b = b / 2;
            bBin = bBin + brem * btemp;
            btemp = btemp * 10;

        }

        while (g != 0) {
            grem = g % 2;
            g = g / 2;
            gBin = gBin + grem * gtemp;
            gtemp = gtemp * 10;
        }

        while (r != 0) {
            rrem = r % 2;
            r = r / 2;
            rBin = rBin + rrem * rtemp;
            rtemp = rtemp * 10;

        }
        buf[i] = rBin;
        buf[i + 1] = gBin;
        buf[i + 2] = bBin;
        printf("%d\n", buf[i]);
        printf("%d\n", buf[i+1]);
        printf("%d\n\n", buf[i+2]);
    }
}

char* changeLetterToBit(char* message)
{
    printf("test2\n");
    printf("%s\n",message);
    if(message == NULL) return 0;
    size_t len = strlen(message);
    char *binair = malloc(len*8 + 1);
    binair[0] = 0;
    int a = 0;
    for(size_t i = 0; i < len+1; i++){
        char ch = message[i];
        for(int j = 7; j >= 0; --j){
            if(ch & (1<<j)){
                strcat(binair, "1");
            }
            else{
                strcat(binair, "0");
            }
        }
        a = i * 8;

        if(ch == 0){
            binair[a] = '0';
            binair[a+1] = '0';
            binair[a+2] = '1';
            binair[a+3] = '0';
            binair[a+4] = '1';
            binair[a+5] = '0';
            binair[a+6] = '1';
            binair[a+7] = '0';
        }

        return 0;
    }
    LSBBIT(binair);
    printf("%d waarde van i\n\n", len);
    printf("%s\n",binair);
    return binair;
}
void Fileopeningconvert(){
        FILE *fptr;
        int j = 0;
        const char filename[] = "tekst.txt";
        char c = 0;

        // Open file
        fptr = fopen(filename, "r");
        if (fptr == NULL)
        {
            printf("Cannot open file \n");
            exit(0);
        }

        // Read contents from file
        while (c != EOF)
        {
            printf ("%c\n", c);
            c = fgetc(fptr);
            ++j;
        }
        printf("\nhier komt die dan\n");
        printf("\n----%d------\n",j);
        char *string = (char*) malloc(sizeof(char)*j);
        rewind(fptr);
        fread(string,j,1,fptr);
        string[j -1] ='\0';
        printf("%s\n",string);
        changeLetterToBit(string);
        fclose(fptr);
        free(string);
        return 0;
};

void Inputbmp(){
    FILE* inputFilePointer = fopen(BMPINPUTFILE, "rb"); //maak een file pointer naar de afbeelding
    if(inputFilePointer == NULL) //Test of het open van de file gelukt is!
    {
        printf("Something went wrong while trying to open %s\n", BMPINPUTFILE);
        exit(EXIT_FAILURE);
    }
    unsigned char bmpHeader[54]; // voorzie een array van 54-bytes voor de BMP Header
    fread(bmpHeader, sizeof(unsigned char), 54, inputFilePointer); // lees de 54-byte header

    //Informatie uit de header (wikipedia)
    // haal de hoogte en breedte uit de header
    int breedte = *(int*)&bmpHeader[18];
    int hoogte = *(int*)&bmpHeader[22];

    int imageSize = 3 * breedte * hoogte; //ieder pixel heeft 3 byte data: rood, groen en blauw (RGB)
    unsigned char* inputPixels = (unsigned char *) calloc(imageSize, sizeof(unsigned char)); // allocate een array voor alle pixels
    fread(inputPixels, sizeof(unsigned char), imageSize, inputFilePointer);
    int pixelsBinair[imageSize];
    convertPixelsToBits(inputPixels, imageSize, pixelsBinair);
}

void LSBBIT(){

}

