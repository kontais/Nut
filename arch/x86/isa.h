#ifndef _ISA_H_
#define _ISA_H_

void timer_82c54_init(uint8_t ch, uint8_t mode,  uint16_t counter);
void pic_82c59_init(uint8_t vec_base);
void pic_82c59_mask_int(uint8_t vec);
void pic_82c59_unmask_int(uint8_t vec);


#endif
