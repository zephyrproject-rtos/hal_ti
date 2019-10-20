#ifndef STUBS_H_
#define STUBS_H_

#include <zephyr.h>

#define STUB(fmt, args...) printk("%s(): %d: STUB: " fmt "\n", __func__, __LINE__, ##args)

#endif /* STUBS_H_ */
