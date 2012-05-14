/* drivers/misc/otf/otf_nitro.c
 *
 * Original source by Benee (c) 2012
 *
 * Modified for the OTF by vadonka 2012
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <linux/init.h>
#include <linux/device.h>
#include <linux/miscdevice.h>

/* Static containers */
static unsigned int MIN_NITRO = 0;
static unsigned int MAX_NITRO = 1;
static unsigned int DEF_NITRO = 0;

/* Boot time value */
unsigned int nitro = 0;

static ssize_t nitro_read(struct device * dev, struct device_attribute * attr, char * buf)
{
	return sprintf(buf, "%d\n", nitro);
}

static ssize_t nitro_write(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int data;

	if (sscanf(buf, "%d\n", &data) == 1)
	{
		if (data != nitro)
		{
			nitro = min(max(data, MIN_NITRO), MAX_NITRO);
			pr_info("NITROCONTROL enabled\n", nitro);
		}
	}
	else
	{
		pr_info("NITROCONTROL invalid input\n");
	}
	return size;
}

static ssize_t nitrocontrol_min(struct device * dev, struct device_attribute * attr, char * buf)
{
	return sprintf(buf, "%u\n", MIN_NITRO);
}

static ssize_t nitrocontrol_max(struct device * dev, struct device_attribute * attr, char * buf)
{
	return sprintf(buf, "%u\n", MAX_NITRO);
}

static ssize_t nitrocontrol_def(struct device * dev, struct device_attribute * attr, char * buf)
{
	return sprintf(buf, "%u\n", DEF_NITRO);
}

static DEVICE_ATTR(nitro, S_IRUGO | S_IWUGO, nitro_read, nitro_write);
static DEVICE_ATTR(nitromin, S_IRUGO , nitrocontrol_min, NULL);
static DEVICE_ATTR(nitromax, S_IRUGO , nitrocontrol_max, NULL);
static DEVICE_ATTR(nitrodef, S_IRUGO , nitrocontrol_def, NULL);

static struct attribute *nitrocontrol_attributes[] = {
	&dev_attr_nitro.attr,
	&dev_attr_nitromin.attr,
	&dev_attr_nitromax.attr,
	&dev_attr_nitrodef.attr,
	NULL
};

static struct attribute_group nitrocontrol_group = {
	.attrs  = nitrocontrol_attributes,
};

static struct miscdevice nitrocontrol_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "nitrocontrol",
};

static int __init nitrocontrol_init(void) {
	int ret;
	pr_info("%s misc_register(%s)\n", __FUNCTION__, nitrocontrol_device.name);
	ret = misc_register(&nitrocontrol_device);

	if (ret) {
		pr_err("%s misc_register(%s) fail\n", __FUNCTION__, nitrocontrol_device.name);
		return 1;
	}

	if (sysfs_create_group(&nitrocontrol_device.this_device->kobj, &nitrocontrol_group) < 0) {
		pr_err("%s sysfs_create_group fail\n", __FUNCTION__);
		pr_err("Failed to create sysfs group for device (%s)!\n", nitrocontrol_device.name);
	}
	return 0;
}

device_initcall(nitrocontrol_init);
