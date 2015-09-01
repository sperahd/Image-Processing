#include <stdio.h>
#include <stdlib.h>
#include "targa.h"

#define NUM_IMAGES 133
int main()
{
	uint8_t alpha[NUM_IMAGES],
		r[NUM_IMAGES],
		g[NUM_IMAGES],
		b[NUM_IMAGES];

	tga_image image[NUM_IMAGES];

	int *pixels_addr[NUM_IMAGES];

	int *pixels_addr_new;
	pixels_addr_new = malloc(sizeof(int));
	int height[NUM_IMAGES],
	    width[NUM_IMAGES];

	int i = 0;

	tga_result result;
	char addr[256];
	for(i=0;i<NUM_IMAGES;i++)
	{
		char path[256];
		if(i<10)
		{
			sprintf(addr,"%s%d%s","/home/ankit/Work/Ankit/BlockColors_WithoutRLE/BlockColors_WithoutRLE_0000",i,".tga");
		}
		else if(i>=10 && i<100)
		{
                        sprintf(addr,"%s%d%s","/home/ankit/Work/Ankit/BlockColors_WithoutRLE/BlockColors_WithoutRLE_000",i,".tga");
		}
		else if(i>=100 && i<1000)
		{
			sprintf(addr,"%s%d%s","/home/ankit/Work/Ankit/BlockColors_WithoutRLE/BlockColors_WithoutRLE_00",i,".tga");

		}
		else if(i>=1000)
		{
			sprintf(addr,"%s%d%s","/home/ankit/Work/Ankit/BlockColors_WithoutRLE/BlockColors_WithoutRLE_0",i,".tga");
		}

		printf("The image being opened is %s\n",addr);
		result = tga_read(&image[i],addr);
		if(result != TGA_NOERR)
		{
		   printf("Error opening the image\n");
		}
		else
		{
			pixels_addr[i] = (int *)image[i].image_data;
			height[i] = (int)image[i].height;
			width[i] = (int)image[i].width;
		}
		printf("The Height is %d\n",width[i]);
	}
	int j = 0, k = 0;
	tga_image img_new;
	int img[NUM_IMAGES];
	char output[256];
	for(k=0;k<NUM_IMAGES-1;k++)
	{
		for(i=0;i<height[k];i++)
//		for(i=0;i<18;i++)
		{
			for(j=0;j<width[k];j++)
//			for(j=0;j<86;j++)
			{
				img[k] = *(pixels_addr[k] + (i * width[k]) + j);
				img[k+1] = *(pixels_addr[k+1] + (i * width[k]) + j);
				*(pixels_addr[k] + (i *width[k]) + j ) = img[k] ^ img[k+1];
//				printf("This is printing %d	%d\n",i,j);
			}
		}

//		img_new.image_data = pixels_addr_new;
		sprintf(output,"%s%s%d%s","/home/ankit/Work/Ankit/BlockColors_WithoutRLE/","new",k+1,".tga");
		result = tga_write(output,&image[k]);
		memset(pixels_addr[k],0,height[k]*width[k]);
	//	tga_close();
	}
}	
