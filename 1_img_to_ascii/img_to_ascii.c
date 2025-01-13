#include <getopt.h>
#include <stdio.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
int main(int argc,char** argv)
{
    int o,longindex;
	struct option longopts[]=
    {
		{"input",required_argument,NULL,'i'},
        {0,0,0,0}
	};
    unsigned char* img_data=NULL;
    int img_weight,img_height,channels_num;
    char* output_file=NULL;
    while((o=getopt_long(argc,argv,"i:",longopts,&longindex))!=-1)
    {
        switch(o)
        {
        case 'i':
            if(img_data==NULL)
            {
                img_data=stbi_load(optarg,&img_weight,&img_height,&channels_num,0);
                if(img_data==NULL)
                {
                    fprintf(stderr,"哎呀,加载文件失败了呢~检查检查文件吧~杂鱼~\n");
                    exit(1);
                }
            }
            else
            {
                fprintf(stderr,"Too many input files!");
                exit(1);
            }
            break;
        case '?':
        default:
            fprintf(stderr,"杂鱼~选项写错了呢~");
            exit(1);
        }
    }
    char* img_grey_str="QWBm#UZXS2onvIli|+=;:-. ";
    int img_grey_str_len=strlen(img_grey_str);
    int per_char_in_pixel=255/img_grey_str_len+1;
    if(img_data!=NULL)
    {
        for(int i=0;i<img_weight*img_height*channels_num;i+=channels_num)
        {
            if(i%img_weight*channels_num==0)
                putchar('\n');
            switch(channels_num)
            {
            case 1:
                printf("%c",img_grey_str[img_data[i]/per_char_in_pixel]);
                break;
            case 2:
                float alpha_2=(float)img_data[i+1]/255.0f;
                printf("%c",img_grey_str[(int)((img_data[i]*alpha_2)/per_char_in_pixel)]);
                break;
            case 3:
                printf("%c",img_grey_str[(img_data[i]+img_data[i+1]+img_data[i+2])/3/per_char_in_pixel]);
                break;
            case 4:
                float alpha_4=(float)img_data[i+3]/255.0f;
                printf("%c",img_grey_str[(int)((((img_data[i]+img_data[i+1]+img_data[i+2])/3)*alpha_4)/per_char_in_pixel)]);
                break;
            default:
                exit(1);
            }
        }
        putchar('\n');
    }
}
