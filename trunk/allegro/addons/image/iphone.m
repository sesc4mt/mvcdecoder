#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#include "allegro5/allegro5.h"
#include "allegro5/fshook.h"
#include "allegro5/allegro_image.h"
#include "allegro5/internal/aintern_memory.h"
#include "allegro5/internal/aintern_image.h"

#include "iio.h"


/* really_load_png:
 *  Worker routine, used by load_png and load_memory_png.
 */
static ALLEGRO_BITMAP *really_load_image(char *buffer, int size)
{
   ALLEGRO_BITMAP *bmp = NULL;
   void *pixels = NULL;
   /* Note: buffer is now owned (and later freed) by the data object. */
   NSData *nsdata = [NSData dataWithBytesNoCopy:buffer length:size];
   UIImage *uiimage = [UIImage imageWithData:nsdata];
   int w = uiimage.size.width;
   int h = uiimage.size.height;

   /* Now we need to draw the image into a memory buffer. */
   pixels = _AL_MALLOC(w * h * 4);
   CGContextRef context = CGBitmapContextCreate(pixels, w, h, 8, w * 4,
      CGImageGetColorSpace(uiimage.CGImage),
      kCGImageAlphaPremultipliedLast);
   CGContextSetBlendMode(context, kCGBlendModeCopy);
   CGContextDrawImage(context, CGRectMake(0.0, 0.0, (CGFloat)w, (CGFloat)h),
      uiimage.CGImage);
   CGContextRelease(context);

   /* Then create a bitmap out of the memory buffer. */
   bmp = al_create_bitmap(w, h);
   if (!bmp) goto done;
   ALLEGRO_LOCKED_REGION *lock = al_lock_bitmap(bmp,
      ALLEGRO_PIXEL_FORMAT_ABGR_8888, ALLEGRO_LOCK_WRITEONLY);
   for (int i = 0; i < h; i++) {
      memcpy(lock->data + lock->pitch * i, pixels + w * 4 * i, w * 4);
   }
   al_unlock_bitmap(bmp);
done:
   _AL_FREE(pixels);
   return bmp;
}


/* Function: al_load_png_f
 *  Load a PNG file from disk, doing colour coversion if required.
 */
ALLEGRO_BITMAP *_al_iphone_load_image_f(ALLEGRO_FILE *f)
{
   ALLEGRO_BITMAP *bmp;
   ASSERT(f);
    
   int64_t size = al_fsize(f);
   if (size <= 0) {
      // TODO: Read from stream until we have the whole image
      return NULL;
   }
   /* Note: This *MUST* be the Apple malloc and not any wrapper, as the
    * buffer will be owned and freed by the NSData object not us.
    */
   void *buffer = malloc(size);
   al_fread(f, buffer, size);

   /* Really load the image now. */
   bmp = really_load_image(buffer, size);
   return bmp;
}


/* Function: al_load_png
 */
ALLEGRO_BITMAP *_al_iphone_load_image(const char *filename)
{
   ALLEGRO_FILE *fp;
   ALLEGRO_BITMAP *bmp;

   ASSERT(filename);

   fp = al_fopen(filename, "rb");
   if (!fp)
      return NULL;

   bmp = _al_iphone_load_image_f(fp);

   al_fclose(fp);

   return bmp;
}