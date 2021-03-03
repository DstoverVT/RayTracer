#ifndef _PIXEL_HPP_
#define _PIXEL_HPP_

/** 
* Simple structure to store a pixel's RGBA values for the Ray Tracing program
* Black by default RGBA = {0, 0, 0, 255}
*/
struct Pixel
{
	unsigned char R{ 0 };
	unsigned char G{ 0 };
	unsigned char B{ 0 };
	unsigned char A{ 255 };
};

#endif
