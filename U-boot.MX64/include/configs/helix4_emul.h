#ifndef __HELIX4_EMUL_H
#define __HELIX4_EMUL_H

#define BOARD_LATE_INIT
#ifdef CONFIG_L2C_AS_RAM
#define CONFIG_PHYS_SDRAM_1_SIZE			0x20000 /* 128KB */
#else
#define CONFIG_PHYS_SDRAM_1_SIZE			0x80000 /* 512 KB */
#endif
/* Backup uboot uses same environment area as primary uboot */
#define CONFIG_ENV_OFFSET	0xa0000


/* Architecture, CPU, etc */
#define CONFIG_ARMV7
#define CONFIG_IPROC (0)
#define CONFIG_HELIX4 (1)
#define CONFIG_HELIX4_EMULATION (1)

/*
Fix me

When DEBUG is enabled, need to disable both CACHE to make u-boot running
#define CONFIG_SYS_NO_ICACHE
#define CONFIG_SYS_NO_DCACHE
#define DEBUG

*/
#define CONFIG_IPROC_MMU	(1)
#define CONFIG_L2_OFF				/* Disable L2 cache */
#define CONFIG_SYS_ARM_CACHE_WRITETHROUGH (1)
#define CONFIG_MACH_TYPE			0xa8d

#define CONFIG_MISC_INIT_R			/* Call board's misc_init_r function */

/* Interrupt configuration */
#define CONFIG_USE_IRQ          1	/* we need IRQ stuff for timer	*/

/* Memory Info */
#define CONFIG_SYS_MALLOC_LEN 			(0x8000) //SZ_256K  	/* see armv7/start.S. */
#define CONFIG_STACKSIZE				(0x8000) //SZ_256K
#define CONFIG_STACKSIZE_IRQ			(4096)
#define CONFIG_STACKSIZE_FIQ			(4096)

#define CONFIG_PHYS_SDRAM_1				0x000000
#define CONFIG_LOADADDR					0x00010000 /* default destination location for tftp file (tftpboot cmd) */
#define CONFIG_PHYS_SDRAM_RSVD_SIZE		0x00000000 /* bytes reserved from CONFIG_PHYS_SDRAM_1 for custom use */

/* Where kernel is loaded to in memory */
#define CONFIG_SYS_LOAD_ADDR				0x08000000
#define LINUX_BOOT_PARAM_ADDR				(CONFIG_PHYS_SDRAM_1+CONFIG_PHYS_SDRAM_RSVD_SIZE)

#define CONFIG_SYS_MEMTEST_START			CONFIG_PHYS_SDRAM_1
#define CONFIG_SYS_MEMTEST_END			(CONFIG_PHYS_SDRAM_1+CONFIG_PHYS_SDRAM_1_SIZE)
#define CONFIG_NR_DRAM_BANKS				1

#define CONFIG_SYS_SDRAM_BASE		(CONFIG_PHYS_SDRAM_1 + CONFIG_PHYS_SDRAM_RSVD_SIZE)
/* CONFIG_SYS_TEXT_BASE is where u-boot is loaded by boot1 */
#define CONFIG_SYS_STACK_SIZE		(0x00008000) /* 64K */       
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_PHYS_SDRAM_1 + CONFIG_SYS_STACK_SIZE - 16)
//#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_PHYS_SDRAM_1 + 0x100000 - 16)

/* Clocks */
#define CONFIG_SYS_REF_CLK			(25000000) /*Reference clock = 25MHz */
#define CONFIG_SYS_REF2_CLK			(200000000) /*Reference clock = 25MHz */
#ifdef CONFIG_HELIX4_EMULATION
#define IPROC_ARM_CLK		(591875)
#define IPROC_AXI_CLK		(295938)
#define IPROC_APB_CLK		(73984)
#endif
/* Serial Info */
#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_CONS_INDEX					1
#if 0 //CCB
#define CONFIG_SYS_NS16550_COM1			(0x18037000)
#define CONFIG_SYS_NS16550_REG_SIZE		(-4)	/* Post pad 3 bytes after each reg addr */
#define CONFIG_SYS_NS16550_CLK			(268800)
#define CONFIG_SYS_NS16550_CLK_DIV		(7)
#define CONFIG_BAUDRATE					2400
#endif

#if 1 //CCA 
#define CONFIG_SYS_NS16550_COM1			(0x18000300)
#define CONFIG_SYS_NS16550_REG_SIZE		(1)	/* no padding */
#define CONFIG_SYS_NS16550_CLK			(33568) //(130200)
#define CONFIG_SYS_NS16550_CLK_DIV		(8)
#define CONFIG_BAUDRATE					300
#endif

#define CONFIG_BAUDRATE					300
#define CONFIG_SYS_BAUDRATE_TABLE	{9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600} 

#define CONFIG_ENV_OVERWRITE	/* Allow serial# and ethernet mac address to be overwritten in nv storage */
#define CONFIG_ENV_SIZE			0x10000 /* 0xA0000-0xAFFFF */

/* NO flash */
#define CONFIG_SYS_NO_FLASH		/* Not using NAND/NOR unmanaged flash */

/* Ethernet configuration */
//#define CONFIG_BCM5301X_ETH
#define CONFIG_NET_MULTI

/* DMA configuration */
#define CONFIG_BCM5301X_DMA

/* General U-Boot configuration */
#define CONFIG_SYS_CBSIZE			1024	/* Console buffer size */
#define CONFIG_SYS_PBSIZE			(CONFIG_SYS_CBSIZE +	sizeof(CONFIG_SYS_PROMPT) + 16) /* Printbuffer size */
#define CONFIG_SYS_MAXARGS			64
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE

#define CONFIG_VERSION_VARIABLE	/* Enabled UBOOT build date/time id string */
#define CONFIG_AUTO_COMPLETE
#define CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "
#define CONFIG_CMDLINE_EDITING
#define CONFIG_SYS_LONGHELP

#define CONFIG_CRC32_VERIFY		/* Add crc32 to memory verify commands */
#define CONFIG_MX_CYCLIC			/* Memory display cyclic */

#define CONFIG_CMDLINE_TAG				/* ATAG_CMDLINE setup */
#define CONFIG_SETUP_MEMORY_TAGS		/* ATAG_MEM setup */

#define CONFIG_BOOTARGS     				"console=ttyS0,115200n8 androidboot.console=ttyS0 root=/dev/mmcblk0p4 rootfstype=ext4 gpt bootmemheap rootwait"

#define CONFIG_BOOTDELAY			1	/* User can hit a key to abort kernel boot and stay in uboot cmdline */
#define CONFIG_BOOTCOMMAND 				""	/* UBoot command issued on power up */
#define CONFIG_SYS_PROMPT					"u-boot> "  

//#include <config_cmd_default.h>
#define CONFIG_CMD_CONSOLE
#define CONFIG_ENV_IS_NOWHERE
#undef CONFIG_CMD_NFS
#undef CONFIG_GENERIC_MMC
#define CONFIG_CMD_NET
#define CONFIG_CMD_PING
#define CONFIG_CMD_MEMORY
//#define CONFIG_CMD_MISC

#define CONFIG_ETHADDR		00:90:4c:06:a5:72
#define CONFIG_NETMASK		255.255.255.0
#define CONFIG_IPADDR		192.168.0.1
//#define CONFIG_GATEWAYIP	192.168.0.100
#define CONFIG_SERVERIP		192.168.0.10

#ifdef UBOOT_MDK
#define CONFIG_GMAC_NUM		2 
#else
#define CONFIG_GMAC_NUM		0 
#endif



#endif /* __HELIX4_EMUL_H */



	
