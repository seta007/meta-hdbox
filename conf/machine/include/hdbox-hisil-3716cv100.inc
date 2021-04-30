KERNELVERSION = "3.0.8"

# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED += "rtc"

TARGET_ARCH = "arm"
DEFAULTTUNE = "armv7a"
require conf/machine/include/arm/arch-armv7a.inc

SOC_FAMILY = "hisi3716cv100"
HICHIPSET = "3716cv100"
CHIPSET = "Hi3716Cv100"

STB_PLATFORM = "hdboxhisi3716cv100"

IMAGE_FSTYPES += "tar.bz2"

CMDLINE ?= "console=ttyAMA0,115200n8"

MTD_KERNEL = "mmcblk0p4"
MTD_ROOTFS = "mmcblk0p9"
KERNEL_FILE = "kernel.img"
ROOTFS_FILE = "rootfs.tar.bz2"

RCNAME = "hdbox"

OLDEST_KERNEL = "${KERNELVERSION}"
PREFERRED_PROVIDER_virtual/kernel = "linux-hdbox"
PREFERRED_VERSION_linux-hdbox = "${KERNELVERSION}"
PREFERRED_PROVIDER_virtual/enigma2-mediaservice = "enigma2-plugin-systemplugins-servicehisilicon"

GCCVERSION_reborn = "4.9.4"
GLIBCVERSION_reborn = "2.19"
PREFERRED_VERSION_glibc_reborn = "2.19"
PREFERRED_VERSION_glibc-initial_reborn = "2.19"

DISTRO_FEATURES_remove += "x11 wayland directfb"

BOX_BRAND = "hdbox"

# E2 OSD settings
EXTRA_OECONF_append_pn-enigma2 = " --with-alphablendingacceleration=always --with-blitaccelerationthreshold=250 --with-fillaccelerationthreshold=190000"

# Gstreamer dvbmediasink
DVBMEDIASINK_CONFIG = "--with-wma --with-wmv --with-pcm --with-dts --with-eac3 --with-h265 --with-vb6 --with-vb8 -with-spark"

MACHINE_FEATURES += "alsa usbhost switchoff osdposition hdmicec no-opengl hisil hisil-3716cv100 blindscan-tbs HDMI RCA 7segment textlcd ci hisil-recovery"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
	hdbox-dvb-modules-${MACHINE} \
	${@bb.utils.contains("MACHINE_FEATURES", "hisil-${HICHIPSET}", "hdbox-libs-${HICHIPSET} hdbox-partitions-${HICHIPSET} hdbox-bootargs-${HICHIPSET} hdbox-bootlogo-${HICHIPSET} hdbox-fastboot-${HICHIPSET}" , "", d)} \
	${@bb.utils.contains("MACHINE_FEATURES", "hisil-recovery", "hdbox-recovery-${HICHIPSET}" , "", d)} \
	"

do_image_tar[depends] += "u-boot-mkimage-native:do_populate_sysroot"

IMAGE_CMD_tar_prepend = " \
	rm -Rf ${IMAGE_ROOTFS}/tmp/*; \
	cp -f ${DEPLOY_DIR_IMAGE}/zImage ${DEPLOY_DIR_IMAGE}/hdbox-partitions-${MACHINE}/${IMAGEDIR}/zImage; \
	cd ${DEPLOY_DIR_IMAGE}/hdbox-partitions-${MACHINE}/${IMAGEDIR}; \
	mkimage -A arm -O linux -T kernel -C none -a 0x80800000 -e 0x80800000 -n e2kernel -d zImage ${KERNEL_FILE}; \
	echo "${IMAGE_NAME}" > imageversion; \
	echo "https://forum.openvision.tech/app.php/donate" > donate.txt; \
	rm -f zImage; \
	cd ${IMAGE_ROOTFS}; \
	tar -cvf ${DEPLOY_DIR_IMAGE}/rootfs.tar -C ${IMAGE_ROOTFS} .; \
	mv -f ${DEPLOY_DIR_IMAGE}/rootfs.tar ${DEPLOY_DIR_IMAGE}/hdbox-partitions-${MACHINE}/${IMAGEDIR}/rootfs.tar; \
	bzip2 ${DEPLOY_DIR_IMAGE}/hdbox-partitions-${MACHINE}/${IMAGEDIR}/rootfs.tar; \
	cd ${DEPLOY_DIR_IMAGE}; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.zip; \
	cd hdbox-partitions-${MACHINE}/${IMAGEDIR}; \
	zip -r ../${IMAGE_NAME}_usb.zip *; \
	cd ..; \
	mv -f ${IMAGE_NAME}_usb.zip ..; \
	cd ..; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.tar.bz2; \
	rm -Rf ${DEPLOY_DIR_IMAGE}/hdbox-partitions-${MACHINE}; \
	"

#EXTRA_ALSA = "mv200"

KERNEL_MODULE_PACKAGE_SUFFIX = "-${KERNELVERSION}"
