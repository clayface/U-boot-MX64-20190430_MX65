#include <common.h>
#include <asm/io.h>

#define IPROC_STRAP_SKU_VECTOR          (0x1811A500)
#define USB2_IDM_IDM_IO_CONTROL_DIRECT  (0x18115408)
#define IPROC_IDM_USB2_RESET_CONTROL    (0x18115800)
#define IPROC_IDM_DMAC_RESET_CONTROL    (0x18114800)
#define ChipcommonA_GPIOInput           (0x18000060)
#define ChipcommonA_GPIOOut             (0x18000064)
#define ChipcommonA_GPIOOutEn           (0x18000068)
#define CRU_GPIO_CONTROL0               (0x1803F1C0)



extern int do_ccsetup(void);

int ehci_init(void)
{
	int usb2_clk_enable, usb2_reset_state;

	__raw_readl(IPROC_STRAP_SKU_VECTOR);
	usb2_clk_enable = __raw_readl(USB2_IDM_IDM_IO_CONTROL_DIRECT);
//	printf("Before reset, USB clk enable register is: %08x\n", usb2_clk_enable);
	usb2_clk_enable |= 0x1;
	__raw_writel( usb2_clk_enable, USB2_IDM_IDM_IO_CONTROL_DIRECT);
	usb2_clk_enable = __raw_readl(USB2_IDM_IDM_IO_CONTROL_DIRECT);
//	printf("Before reset, USB clk enable register is: %08x\n", usb2_clk_enable);
	udelay(1000);
	usb2_reset_state = __raw_readl(IPROC_IDM_USB2_RESET_CONTROL);
	if ((usb2_reset_state & 1) == 1)
	{
//		printf("\nBring usb2h_out of reset.......\n");
		__raw_writel(0x0, IPROC_IDM_USB2_RESET_CONTROL);
		udelay(1000);
		usb2_reset_state = __raw_readl(IPROC_IDM_USB2_RESET_CONTROL);
//		printf("usb2_reset_state is set and now it is: %08x\n", usb2_reset_state);
	};
	return 0;
};
/*
U_BOOT_CMD(
	ehciinit, 1, 0, ehci_init, "", ""
);
*/

int periph_enable(void)
{
	int tmp;

	/* enable orange pin reset button & white led CRU PINs */
	tmp = __raw_readl(CRU_GPIO_CONTROL0);
	tmp |= ( 1 << 3 ); tmp |= ( 1 << 8 ); tmp |= ( 1 << 31 );
	__raw_writel(tmp, CRU_GPIO_CONTROL0);

	/* Bring DMA out of reset */
	__raw_writel(0x0, IPROC_IDM_DMAC_RESET_CONTROL);

	return 0;
};

int mdio_rst(void)
{
	int tmp;
	tmp = __raw_readl(CRU_GPIO_CONTROL0);
	tmp ^= ( 1 << 15 );
	__raw_writel(tmp, CRU_GPIO_CONTROL0);
	/* reset qca switches */
	udelay(100);
	tmp ^= ( 1 << 15 );
	__raw_writel(tmp, CRU_GPIO_CONTROL0);

	return 0;
};

int led_flash(void)
{
        uint32_t out;
        uint32_t outen;

	

        out = __raw_readl(ChipcommonA_GPIOOut);
        outen = __raw_readl(ChipcommonA_GPIOOutEn);
        out ^= ( 1 << 31 ); outen ^= (1 << 31); outen ^= ( 1 << 3 );
        __raw_writel(out, ChipcommonA_GPIOOut);
	__raw_writel(outen, ChipcommonA_GPIOOutEn);

        int i=0;
        for(i;i<7;i++) {

                out ^= ( 1 << 3 ); outen ^= ( 1 << 31 );
                __raw_writel(out, ChipcommonA_GPIOOut);
                __raw_writel(outen, ChipcommonA_GPIOOutEn);
                mdelay(250);
        };
};

int usb_boot(void)
{
        uint32_t regData;
        uint32_t tmp;
        tmp = __raw_readl(ChipcommonA_GPIOInput);
        tmp = tmp & (1 << 8);
//      printf("tmp = %08X\n", tmp);
        if (tmp == 0) {
                printf("\nRESET pressed: USB boot enabled\n");
                led_flash();
                run_command_list("usb start; \
                fatload usb 0:1 \
                0x60008000 openwrt-bcm5862x-generic-meraki_mx65-initramfs-kernel.bin; \
                bootbk 0x60008000 bootkernel2", -1, 0);
        };

        return 0;
};

int dev_init(void)
{
	do_ccsetup();
	mdio_rst();
	ehci_init();
	periph_enable();
//	usb_boot();

	return 0;
}

U_BOOT_CMD(
        mx65init, 1, 0, dev_init, "", ""
);

U_BOOT_CMD(
        usbload, 1, 0, usb_boot, "",""
);
