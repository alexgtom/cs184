#include <emmintrin.h>
#include <xmmintrin.h>
#define KERNX 3 //this is the x-size of the kernel. It will always be odd.
#define KERNY 3 //this is the y-size of the kernel. It will always be odd.
int conv2D(float* in, float* out, int data_size_X, int data_size_Y,
                    float* kernel)
{
    // the x coordinate of the kernel's center
    int kern_cent_X = (KERNX - 1)/2;
    // the y coordinate of the kernel's center
    int kern_cent_Y = (KERNY - 1)/2;

    
    //make a new in matrix with padding
    int in_width = data_size_X + 2 * kern_cent_X;
    int in_height = data_size_Y + 2 * kern_cent_Y;
    int in_size = in_width * in_height;
    int counter = 0;
    float in_padding[in_size];
    int last_col = in_width - 1;
    //    for (int i = 0; i < (data_size_X * data_size_Y); i++) {
    //	printf("%f ,", in[i]);
    //}

    memset( in_padding, 0.0, in_size*sizeof(float));
    
    // for (int n = 0; n < in_width+1; n++) {
    //	in_padding[n] = 0.0;
    //}

    float invertKern[] = {kernel[8], kernel[7], kernel[6], 0, kernel[5], kernel[4], kernel[3], 0, kernel[2], kernel[1], kernel[0], 0 };
   
    __m128  kern1 = _mm_loadu_ps (invertKern);
    __m128  kern2 = _mm_loadu_ps ((invertKern+4));
    __m128  kern3 = _mm_loadu_ps ((invertKern+8));
	
    for (int n = in_width+1; n < (in_size - in_width); n++) {
	if (n%in_width == last_col) {
	    // in_padding[n] = 0.0;
	    //in_padding[n++] = 0.0;
	    n++;
	} else {
	    in_padding[n] = in[counter];
	    counter++;
	}
    }
    // for (int n = in_size-in_width; n < in_size; n++) {
    //	in_padding[n] = 0.0;
    //}

    //for (int i = 0; i<in_size; i++) {
    //	printf("%f ,", in_padding[i]);
    //}
    
    // main convolution loop

    //blocking

    //    int blocksize = 40;
	
	float total [4];
	__m128 sum;
	__m128 rows [12];
	int unroll = 4;
	for(int y= 0; y < data_size_Y; y++){ // the x coordinate of the output location we're focusing on
		for(int x = 0; x < data_size_X; x+=unroll){ // the y coordinate of theoutput location we're focusing on
			
			rows[0] =  _mm_loadu_ps(in_padding + x + y * in_width);
			rows[1] = _mm_loadu_ps(in_padding + x+1 + y * in_width);
			rows[2] =  _mm_loadu_ps(in_padding + x+2 + y * in_width);
			rows[3] =  _mm_loadu_ps(in_padding + x+3 + y * in_width);
			
			rows[4] =  _mm_loadu_ps(in_padding + x + (y+1) * in_width);
			rows[5] =  _mm_loadu_ps(in_padding + x+1 + (y+1) * in_width);
			rows[6] =  _mm_loadu_ps(in_padding + x+2 + (y+1) * in_width);
			rows[7] =  _mm_loadu_ps(in_padding + x+3 + (y+1) * in_width);
		
			rows[8] =  _mm_loadu_ps(in_padding + x + (y+2) * in_width);
			rows[9] =  _mm_loadu_ps(in_padding + x+1 + (y+2) * in_width);
			rows[10] =  _mm_loadu_ps(in_padding + x+2 + (y+2) * in_width);
			rows[11] =  _mm_loadu_ps(in_padding + x+3 + (y+2) * in_width);

			sum = _mm_add_ps(_mm_mul_ps(rows[0], kern1), _mm_mul_ps (rows[4] , kern2) );
			sum  = _mm_add_ps (sum, _mm_mul_ps(rows[8], kern3));
			_mm_storeu_ps(total, sum);		
			out[x +y*data_size_X] = total[0] + total[1] + total[2];

		
			sum = _mm_add_ps(_mm_mul_ps(rows[1], kern1), _mm_mul_ps (rows[5] , kern2) );
			sum  = _mm_add_ps (sum, _mm_mul_ps(rows[9], kern3));
			_mm_storeu_ps(total, sum);		
			out[x+1 +y*data_size_X] = total[0] + total[1] + total[2];
		
			sum = _mm_add_ps(_mm_mul_ps(rows[2], kern1), _mm_mul_ps (rows[6] , kern2) );
			sum  = _mm_add_ps (sum, _mm_mul_ps(rows[10], kern3));
			_mm_storeu_ps(total, sum);		
			out[x+2 +y*data_size_X] = total[0] + total[1] + total[2];
		
			sum = _mm_add_ps(_mm_mul_ps(rows[3], kern1), _mm_mul_ps (rows[7] , kern2) );
			sum  = _mm_add_ps (sum, _mm_mul_ps(rows[11], kern3));
			_mm_storeu_ps(total, sum);		
			out[x+3 +y*data_size_X] = total[0] + total[1] + total[2];
		}
	}

	//	for(int n = 0; n < (data_size_X * data_size_Y); n++) {
	//  printf("%f ,", out[n]);
	//}
		
	return 1;
}
