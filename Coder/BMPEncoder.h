#pragma once

#include "..\\Common\\variable.h"

bool BMPEncoder(BYTE** buf, UINT* size, IMAGE* image_data){
	if(image_data->buf == nullptr){return false;}
	if(*buf != nullptr || size == nullptr){return false;}

	UINT wmb = image_data->width*3;
	UINT junk = 4-(wmb%4);
	if(junk == 4){junk = 0;}
	*size = (wmb+junk)*image_data->height+54;
	*buf = new BYTE[*size];

	//Header
	(*buf)[0] = 'B'; (*buf)[1] = 'M';
	UINT* temp = (UINT*)&((*buf)[2]);	*temp = *size;
	(*buf)[6] = 0x00; (*buf)[7] = 0x00; (*buf)[8] = 0x00; (*buf)[9] = 0x00;
	temp = (UINT*)&((*buf)[10]);	*temp = 54;

	//DIBHeader
	temp = (UINT*)&((*buf)[14]);	*temp = 40;
	temp = (UINT*)&((*buf)[18]);	*temp = image_data->width;
	temp = (UINT*)&((*buf)[22]);	*temp = image_data->height;
	(*buf)[26] = 0x01; (*buf)[27] = 0x00;
	(*buf)[28] = 0x18; (*buf)[29] = 0x00;
	temp = (UINT*)&((*buf)[30]);	*temp = 0;
	temp = (UINT*)&((*buf)[34]);	*temp = *size-54;
	temp = (UINT*)&((*buf)[38]);	*temp = 3780;
	temp = (UINT*)&((*buf)[42]);	*temp = 3780;
	temp = (UINT*)&((*buf)[46]);	*temp = 0;
	temp = (UINT*)&((*buf)[50]);	*temp = 0;

	//data
	UINT data_width = wmb+junk;
	for(UINT y = 0 ; y<image_data->height ; ++y){
		UINT data_height = image_data->height-y-1;
		for(UINT x = 0 ; x<image_data->width ; ++x){
			UINT buf_idx = 54+(y*data_width)+(x*3);
			UINT ibuf_idx = (data_height*(image_data->width*(3+image_data->alpha_able)))
				+(x*(3+image_data->alpha_able));
			(*buf)[buf_idx]   = image_data->buf[ibuf_idx+2];
			(*buf)[buf_idx+1] = image_data->buf[ibuf_idx+1];
			(*buf)[buf_idx+2] = image_data->buf[ibuf_idx];
		}
		for(UINT x = 0 ; x<junk ; ++x){(*buf)[54+(y*data_width)+wmb+x] = 0x00;}
	}

	return true;
}