#include <am.h>
#include <nemu.h>

#define SYNC_ADDR (VGACTL_ADDR + 4)

void __am_gpu_init() {
  // int i;
  // int w = io_read(AM_GPU_CONFIG).width;
  // int h = io_read(AM_GPU_CONFIG).height;
  // uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  // for( i = 0;i < w * h; i++) fb[i] = i;
  // outl(SYNC_ADDR , 1);  
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
    //.width = (inl(VGACTL_ADDR) & 0XFFFF0000) >> 16, .height = inl(VGACTL_ADDR) & 0XFFFF,
    .width = (int)inw(VGACTL_ADDR + 2 ), .height = (int)inw(VGACTL_ADDR),
    .vmemsz = 0
  };
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
  // int w = io_read(AM_GPU_CONFIG).width;
  // int h = io_read(AM_GPU_CONFIG).height;
  // uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;

  int w = io_read(AM_GPU_CONFIG).width;
  int h = io_read(AM_GPU_CONFIG).height;
  
  // Ensure the drawing area is within the framebuffer boundaries
  if (ctl->x < 0 || ctl->y < 0 || ctl->x + ctl->w > w || ctl->y + ctl->h > h) {
    // If out of bounds, we might want to handle it or return early
    return;
  }

  // Get the pointer to the framebuffer memory
  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  
  // Iterate over the pixels in the specified region and copy them to the framebuffer
  for (int row = 0; row < ctl->h; row++) {
    for (int col = 0; col < ctl->w; col++) {
      // Calculate the target framebuffer position based on (x, y) and (col, row)
      int fb_idx = (ctl->y + row) * w + (ctl->x + col);
      uint32_t pixel_color = ((uint32_t*)ctl->pixels)[row * ctl->w + col];
      
      // Write the pixel color to the framebuffer
      fb[fb_idx] = pixel_color;
    }
  }
  if (ctl->sync) {
    outl(SYNC_ADDR, 1);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
