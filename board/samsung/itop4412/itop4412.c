// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2011 Samsung Electronics
 */

#include <common.h>
#include <asm/io.h>
#include <asm/gpio.h>
#include <asm/arch/cpu.h>
#include <asm/arch/mmc.h>
#include <asm/arch/periph.h>
#include <asm/arch/pinmux.h>
#include <usb.h>
#include <usb/dwc2_udc.h>
#include <log.h>

u32 get_board_rev(void)
{
	return 0;
}

int exynos_init(void)
{
#ifdef CONFIG_USB_ETHER_DM9601
	debug("---> ready to init usb3503\n");
	/* USB3503A Connect */
	gpio_request(EXYNOS4X12_GPIO_M33, "USB3503A Connect");
	/* USB3503A Reset */
	gpio_request(EXYNOS4X12_GPIO_M24, "USB3503A Reset");
	/* USB3503A Disconnect, Reset, Connect */
	gpio_direction_output(EXYNOS4X12_GPIO_M33, 0);
	gpio_direction_output(EXYNOS4X12_GPIO_M24, 0);
	gpio_direction_output(EXYNOS4X12_GPIO_M24, 1);
	gpio_direction_output(EXYNOS4X12_GPIO_M33, 1);
#endif
	return 0;
}

#ifdef CONFIG_USB_GADGET
static int s5pc210_phy_control(int on)
{
#if 0
	/* FIXME: need to set power? */
	struct udevice *dev;
	int ret;

	ret = regulator_get_by_platname("VDD_UOTG_3.0V", &dev);
	if (ret) {
		pr_err("Regulator get error: %d", ret);
		return ret;
	}

	if (on)
		return regulator_set_mode(dev, OPMODE_ON);
	else
		return regulator_set_mode(dev, OPMODE_LPM);
#endif
	return 0;
}

struct dwc2_plat_otg_data s5pc210_otg_data = {
	.phy_control	= s5pc210_phy_control,
	.regs_phy	= EXYNOS4X12_USBPHY_BASE,
	.regs_otg	= EXYNOS4X12_USBOTG_BASE,
	.usb_phy_ctrl	= EXYNOS4X12_USBPHY_CONTROL,
	.usb_flags	= PHY0_SLEEP,
};
#endif

int board_usb_init(int index, enum usb_init_type init)
{
#ifdef CONFIG_USB_GADGET
	debug("USB_udc_probe\n");
	return dwc2_udc_probe(&s5pc210_otg_data);
#else
	return 0;
#endif
}

#ifdef CONFIG_BOARD_EARLY_INIT_F
int exynos_early_init_f(void)
{
	return 0;
}
#endif
