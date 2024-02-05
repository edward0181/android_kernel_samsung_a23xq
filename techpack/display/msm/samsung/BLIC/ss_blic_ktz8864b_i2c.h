/*
 * ktz8864b_hw_i2c.h - Platform data for ktz8864b backlight driver
 *
 * Copyright (C) 2020 Samsung Electronics
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */
#include "../ss_dsi_panel_common.h"

enum {
	BLIC_STATE_OFF = 0,
	BLIC_STATE_ON,
	BLIC_STATE_UNKNOWN,
};

struct ss_blic_info {
	struct i2c_client *client;
};

int ss_blic_ktz8864b_init(void);
int ss_blic_ktz8864b_configure(u8 data[][2], int size);

