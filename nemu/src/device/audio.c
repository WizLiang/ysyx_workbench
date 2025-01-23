/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <common.h>
#include <device/map.h>
#include <SDL2/SDL.h>

enum {
  reg_freq,
  reg_channels,
  reg_samples,
  reg_sbuf_size,
  reg_init,
  reg_count,//used area
  nr_reg
};

static uint8_t *sbuf = NULL;
static uint32_t *audio_base = NULL;
int32_t count = 0;
static int sbuf_pos = 0;

// void audio_callback(void *userdata, uint8_t *stream, int len) {
//   count = audio_base[reg_count];  // Current used bytes in the buffer
//   int sbuf_size = CONFIG_SB_SIZE;  // Total buffer size

//   //Calculate the available data that can be read from the buffer
//   int available_data = sbuf_size - count;
  
//   printf("available_data = %d\n",available_data);
//   // The actual number of bytes to read, cannot exceed the available data
//   int nread = (count < len) ? count : len;
//  // printf("nread = %d\n",nread);
//   // Read audio data byte by byte from the buffer
//   uint8_t *sbuf_ptr = (uint8_t *)(uintptr_t)(CONFIG_SB_ADDR + count);
//   //printf("sbuf_ptr = %p\n",sbuf_ptr);
//   int bytes_read = 0;
//   for (int i = 0; i < nread; i++) {
//     printf("i = %d\n",i);
//     //printf("sbuf_ptr[i] = %d\n",sbuf_ptr[i]);
//     //printf("stream[i] = %d\n",stream[i]);
//     stream[i] = sbuf_ptr[i];  // Copy data from the buffer to SDL stream
//     bytes_read++;
//   }
//   //printf("available_data = %d\n",available_data);

//   // Update the used space in the buffer, subtract the number of bytes read
//   audio_base[reg_count] = count - bytes_read;

//   // If the requested data length is greater than the available data, fill the remaining space with zeros
//   if (len > nread) {
//     memset(stream + nread, 0, len - nread);  // Zero padding for remaining space
//   }
// }
// use ringbuf
void audio_sdl_callback(void *userdata, uint8_t *stream, int len) {
	SDL_memset(stream, 0, len);
	uint32_t used_cnt = audio_base[reg_count];
	len = len > used_cnt ? used_cnt : len;
	uint32_t sbuf_size = audio_base[reg_sbuf_size];

	if( (sbuf_pos + len) > sbuf_size) {
		SDL_MixAudio(stream, sbuf + sbuf_pos, sbuf_size - sbuf_pos, SDL_MIX_MAXVOLUME);
		SDL_MixAudio(stream + (sbuf_size - sbuf_pos), sbuf + (sbuf_size - sbuf_pos), len - (sbuf_size - sbuf_pos), SDL_MIX_MAXVOLUME);
		//printf("the length of data over the sbuf_size\n");
	}
	else
		SDL_MixAudio(stream, sbuf + sbuf_pos, len, SDL_MIX_MAXVOLUME);
	sbuf_pos = (sbuf_pos + len) % sbuf_size;
	//printf("when run callback, the used count is %d\n--------\n", audio_base[reg_count]);
	audio_base[reg_count] -= len;
}


static void audio_io_handler(uint32_t offset, int len, bool is_write) {
  if (is_write) {
    switch (offset/4) {
		case reg_freq:
		//Log("Audio frequent is %d\n",audio_base[reg_freq]);
		break;
		case reg_channels:
		//Log("Audio channel is %d\n",audio_base[reg_channels]);
		break;
		case reg_samples:
		//Log("Audio samples is %d\n",audio_base[reg_samples]);
		break;	
		case reg_init:
        // 初始化 SDL 音频系统
        SDL_AudioSpec s = {};
        s.format = AUDIO_S16SYS;  
        s.freq = audio_base[reg_freq];
        //printf("The frequency is %d\n",audio_base[reg_freq]);
        s.channels = audio_base[reg_channels];  
        s.samples = audio_base[reg_samples];  
        s.callback = audio_sdl_callback; 
        count = 0;
        int ret = SDL_InitSubSystem(SDL_INIT_AUDIO);
        if (ret == 0) {
        SDL_OpenAudio(&s, NULL);
        SDL_PauseAudio(0);
        //Log("Audio initial finished!\n");
        }
		audio_base[reg_init] = 0;
        break;
     case reg_count:
        // 读取已使用大小
        count = audio_base[reg_count] ;
		break;
        //printf("Count is %d",audio_base[reg_count]);
      default:
        Log("Unknown audio register write: offset = 0x%x", offset);
    }
  } else {
    switch (offset/4) {
      case reg_sbuf_size:
        audio_base[reg_sbuf_size] = CONFIG_SB_SIZE;
        break;
      case reg_count:
        //audio_base[reg_count] = count;
		//modify in audio_sdl_callback(),so nothing to do 
        break;
      default:
        Log("Unknown audio register read: offset = 0x%x", offset);
    }
  }
}


void init_audio() {
  uint32_t space_size = sizeof(uint32_t) * nr_reg;
  audio_base = (uint32_t *)new_space(space_size);
#ifdef CONFIG_HAS_PORT_IO
  add_pio_map ("audio", CONFIG_AUDIO_CTL_PORT, audio_base, space_size, audio_io_handler);
#else
  add_mmio_map("audio", CONFIG_AUDIO_CTL_MMIO, audio_base, space_size, audio_io_handler);
#endif

  sbuf = (uint8_t *)new_space(CONFIG_SB_SIZE);
  add_mmio_map("audio-sbuf", CONFIG_SB_ADDR, sbuf, CONFIG_SB_SIZE, NULL);

}
