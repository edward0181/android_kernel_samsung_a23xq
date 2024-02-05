/*
 * ktz8864b_hw_i2c.c - Platform data for ktz8864b backlight driver
 *
 * Copyright (C) 2020 Samsung Electronics
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */
#include <linux/kernel.h>
#include <linux/of_gpio.h>
#include <linux/init.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/device.h>

#include "ss_blic_ktz8864b_i2c.h"

static struct ss_blic_info backlight_pinfo;

static int ss_backlight_i2c_read(struct i2c_client *client, u8 addr,  u8 *value)
{
	int retry = 3;
	u8 wr[] = {addr};

	struct i2c_msg msg[] = {
		{
			.addr = client->addr,
			.flags = 0,
			.buf = wr,
			.len = 1
		}, {
			.addr = client->addr,
			.flags = I2C_M_RD,
			.buf = value,
			.len = 1
		},
	};
	int ret;

	do {
		ret = i2c_transfer(client->adapter, msg, 2);
		if (ret != 2)
			pr_err("%s : client->addr 0x%02x read_addr 0x%02x error (ret == %d)\n",
					__func__, client->addr, addr, ret);
		else
			break;
	} while (--retry);

	return ret;
}

static int ss_backlight_i2c_write(struct i2c_client *client, u8 addr,  u8 value)
{
	int retry = 3;
	u8 wr[] = {addr, value};
	struct i2c_msg msg[] = {
		{
			.addr = client->addr,
			.flags = 0,
			.buf = wr,
			.len = 2
		}
	};
	int ret;

	do {
		ret = i2c_transfer(client->adapter, msg, 1);
		if (ret != 1) {
			pr_err("%s : addr 0x%02x value 0x%02x error (ret == %d)\n", __func__,
				 addr, value, ret);
		} else
			break;
	} while (--retry);

	return ret;
}

enum {
	BLIC_ADDR = 0,
	BLIC_VAL,
	BLIC_MAX,
};

int ss_blic_ktz8864b_configure(u8 data[][2], int size)
{
	struct i2c_client *client = backlight_pinfo.client;
	u8 check;
	int ret = 0;
	int i;

	if (!client) {
		pr_err("%s: i2c is not prepared\n", __func__);
		return -ENODEV;
	}

	for (i = 0; i < size; i++) {
		u8 addr = data[i][0];
		u8 val = data[i][1];

		ss_backlight_i2c_write(client, addr, val);
		ss_backlight_i2c_read(client, addr, &check);

		if (check != val) {
			dev_err(&client->dev, "fail: addr: %x, val: %x, %x\n",
							addr, val, check);
			ret = -EINVAL;
		} else {
			dev_dbg(&client->dev, "pass: addr: %x, val: %x\n",
							addr, val);
		}
	}

	dev_info(&client->dev, "ktz8864b config done %d\n", ret);

	return ret;
}

static int ss_blic_ktz8864b_probe(struct i2c_client *client,
				  const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = to_i2c_adapter(client->dev.parent);

	dev_info(&client->dev, "%s: +++\n", __func__);

	if (!i2c_check_functionality(adapter, I2C_FUNC_I2C)) {
		pr_err("%s i2c check fail\n", __func__);
		return -EIO;
	}

	backlight_pinfo.client = client;

	dev_info(&client->dev, "%s: ---\n", __func__);

	return 0;
}

static int ss_blic_ktz8864b_remove(struct i2c_client *client)
{
	return 0;
}

static const struct i2c_device_id ss_blic_ktz8864b_id[] = {
	{"ktz8864b", 0},
	{ }
};
MODULE_DEVICE_TABLE(i2c, ss_blic_ktz8864b_id);

static struct of_device_id ss_blic_ktz8864b_match_table[] = {
	{ .compatible = "ktz8864b,display_backlight",},
	{ }
};

struct i2c_driver ss_blic_ktz8864b_driver = {
	.probe = ss_blic_ktz8864b_probe,
	.remove = ss_blic_ktz8864b_remove,
	.driver = {
		.name = "ktz8864b",
		.owner = THIS_MODULE,
#ifdef CONFIG_OF
		.of_match_table = of_match_ptr(ss_blic_ktz8864b_match_table),
#endif
		   },
	.id_table = ss_blic_ktz8864b_id,
};

int ss_blic_ktz8864b_init(void)
{

	int ret = 0;

	ret = i2c_add_driver(&ss_blic_ktz8864b_driver);
	if (ret)
		pr_err("%s : ktz8864b_init registration failed. ret= %d\n", __func__, ret);

	pr_info("%s: done\n", __func__);

	return ret;
}

void ss_blic_ktz8864b_exit(void)
{
	i2c_del_driver(&ss_blic_ktz8864b_driver);
}

