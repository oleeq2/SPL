#include <stdio.h>
#include <stdlib.h>
#define BM 0x424d
#pragma pack(push,2)
typedef struct 
{
    short int bfType;
    int bfSize;
    int bfReserved;
    int bfOffBits;
    int biSize;
    int biWidth;
    int biHeigth;
    short int biPlanes;
    short int biBitCount;
    int biCompression; 
    int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    int biClrUsed;
    int biClrImportant;
} BMPHeader;
#pragma pack(pop)

BMPHeader* readBMPHeader(FILE *file)
{
    BMPHeader* header = malloc(sizeof(BMPHeader));
    fread(header,sizeof(BMPHeader),1,file);

    return header;
}

int checkBMP(BMPHeader* header) 
{
    int ret = 1;

    if( (*header).biBitCount != 24 && (*header).bfType != BM    )
        ret = 0;
    
    return ret;
}

int roundToQuat(int num)
{
    int i;
    i = num;
    while(i % 4 != 0)
        i++;

    return i;
}

void LinesSwap(char *line,char *an_line,int line_length)
{
    char tmp_byte;
    int i;
    
    for(i = 0; i < line_length; i++)
    {
        tmp_byte = line[i];
        line[i] = an_line[i];
        an_line[i] = tmp_byte;
    }

    return;
}

void MirrorImage(char *image_buffer, int lines_num, int line_length)
{
    int i;
    
    for(i = 0; i <= lines_num/2; i++)
    {
        LinesSwap( image_buffer + line_length*i, image_buffer + line_length*(lines_num - i), line_length);
    }
}


int main(int argc,char *argv[])
{
    FILE *file_in,*file_out;
    char *fname_in,*fname_out;
    int lines_num,lines_length;
    int image_size;
    BMPHeader file_header;
    char *image_buffer; 

    if(argc < 2 )
        return -1;
    fname_in  = argv[1];
    fname_out = argv[2];
    
    if((file_in = fopen(fname_in, "r")) == NULL)
        return -1;

    file_header = *readBMPHeader(file_in);
/*    if(checkBMP(&file_header))
    {
        printf("Error image format");
        return -1;
    }
 */ 
    lines_num    = file_header.biHeigth;
    lines_length = roundToQuat(file_header.biWidth); 

    image_size = 3 * lines_num * lines_length;
    image_buffer = malloc(image_size);

    fread(image_buffer,image_size,1,file_in);
    MirrorImage(image_buffer,lines_num,3*lines_length);

    if((file_out = fopen(fname_out, "w+")) == NULL)
        return -1;
    
    fwrite(&file_header, sizeof(file_header), 1, file_out);
    fwrite(image_buffer, image_size, 1, file_out);

    return 0;
}
