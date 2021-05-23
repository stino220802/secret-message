#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define __DEBUG
#define BMPINPUTFILE "test.bmp"
#define TEKSTINPUT "tekst.txt"
int imageSize = 0;
char* changeLetterToBit(char* message);
int* convertPixelsToBits(unsigned char* inputPixels, int* buf );
void Fileopeningconvert();
void LSBBIT(char* binair, char* message, int* pixelsBinair, int imageSize);
char* Inputbmp();
int main(int argc, char* argv[])
{
    Fileopeningconvert();
    Inputbmp();
    //LSBBIT(char* binair, char* message, int* pixelsBinair, int imageSize);

#ifdef __DEBUG
    printf("DEBUG info: BMP transformer\n");
#endif
 }

int* convertPixelsToBits(unsigned char* inputPixels,  int* buf) {
    printf("imageSize %d \n", imageSize);
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
    return buf;
}

char* changeLetterToBit(char* message)
{
    printf("test2\n");
    printf("%s\n",message);
    if(message == NULL) return 0;
    size_t len = strlen(message);
    char *binair = malloc(len*8 + 1);
    for (size_t z = 0; z < len + 1; z++) {
        binair[z] = 0;

    }

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


    }
    //LSBBIT(binair, message, pixelsBinair, imageSize);
    printf("%s test\n",binair);
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
        j = j + 1;
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

}




void LSBBIT(char* binair, char* message, int* pixelsBinair, int imageSize){
     size_t len = strlen(message);
   char *output = malloc(imageSize);
    output[0] = '\0';
   // printf("test aaaaa\n");
   for(int i = 0; i < imageSize; i++){
       int temp = pixelsBinair[i];
       int pixels =  temp;
       int count = 0;
       do{
           count++;             //10010011 11101111
           temp /= 10;
       }while(temp != 0);
       int leadingZero =  8 - count;
       int temp2 = pixels;
       int lastDigit = temp2 % 10;
       char inputDigit = binair[i];

       if(inputDigit == '1' ){
           if(lastDigit == 0){
               printf("pixels %d\n ", pixels);
               pixels = pixels + 1;
               printf("output %d\n ", pixels);
           }
       }
       if(inputDigit == '0'){
           if(lastDigit == 1 )
           {

               pixels = pixels - 1;

           }
       }


       output[i] = pixels;

   }
   printf("output string %s", output);
    }
char* Inputbmp(){
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
    imageSize = 3 * breedte * hoogte;
               //ieder pixel heeft 3 byte data: rood, groen en blauw (RGB) //

    unsigned char* inputPixels = (unsigned char *) calloc(imageSize, sizeof(unsigned char)); // allocate een array voor alle pixels
    fread(inputPixels, sizeof(unsigned char), imageSize, inputFilePointer);
    int* pixelsBinair = malloc(imageSize);
    convertPixelsToBits(inputPixels, pixelsBinair);
    return pixelsBinair;
}
