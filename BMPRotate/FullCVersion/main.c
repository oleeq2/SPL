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

char* bufferRead(FILE* file,int offset,int lenght,char* buffer)
{
    fseek(file,offset,SEEK_SET);
    fread(buffer,lenght,1,file);

    return buffer;
}

void swapString(char* fstr,char* sstr,int str_len)
{
    char* tmp_str = calloc(str_len,1);

    memcpy(tmp_str,fstr,str_len);
    memcpy(fstr,sstr,str_len);
    memcpy(sstr,tmp_str,str_len);

    free(tmp_str);
}

int main(int argc, const char *argv[])
{
    FILE *file_in,*file_out;
    char *fname_in,*fname_out;
    int lines_num,columns_num;
    int image_size;
    BMPHeader file_header;
    char *image_buffer; 

    if(argc < 2 )
        return -1;
    fname_in  = argv[1];
    fname_out = argv[2];
    
    if((file_in = fopen(fname_in,"r") == NULL)
            return -1;

    file_header = readBMPHeader(fname_in);
    if(checkBMP(&file_header))
        return -1;

    lines_num   = header.heigth;
    columns_num = header.width;
    
    image_size = 3*
}
