KERNELVERSION = "3.0.8"

# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED += "rtc"

TARGET_ARCH = "arm"
DEFAULTTUNE = "armv5t-vfp"
require conf/machine/include/arm/arch-armv5.inc
require conf/machine/include/soc-family.inc

SOC_FAMILY = "hisi3716mv300"
HICHIPSET = "3716mv300"
CHIPSET = "Hi3716Mv300"

STB_PLATFORM = "hdboxhisi3716mv300"

IMAGE_FSTYPES += "ubi"

MKUBIFS_ARGS = "-m 4096 -e 253952 -c 2048"
UBINIZE_ARGS = "-m 4096 -p 256KiB -s 4096"

CMDLINE ?= "console=ttyAMA0,115200n8"

MTD_KERNEL = "mmcblk0p4"
MTD_ROOTFS = "mmcblk0p9"
KERNEL_FILE = "uImage"
ROOTFS_FILE = "rootfs.ubi"

RCNAME = "hdbox"

#Provider
OLDEST_KERNEL = "${KERNELVERSION}"
PREFERRED_PROVIDER_virtual/kernel = "linux-hdbox"
PREFERRED_VERSION_linux-hdbox = "${KERNELVERSION}"
PREFERRED_PROVIDER_virtual/gstreamer1.0-dvbmediasink = "gstreamer1.0-plugin-dvbmediasink"
PREFERRED_PROVIDER_virtual/enigma2-mediaservice = "enigma2-plugin-systemplugins-servicehisilicon"

DISTRO_FEATURES_remove += "x11 wayland directfb"

BOX_BRAND = "hdbox"

IMAGEDIR ?= "hdbox/${MACHINE}"

# E2 OSD settings
EXTRA_OECONF_append_pn-enigma2 = " --with-alphablendingacceleration=always --with-blitaccelerationthreshold=250 --with-fillaccelerationthreshold=190000"

# Gstreamer dvbmediasink
DVBMEDIASINK_CONFIG = "--with-wma --with-wmv --with-pcm --with-dts --with-eac3 --with-h265 --with-vb6 --with-vb8 -with-spark"

MACHINE_FEATURES += "alsa usbhost switchoff osdposition hdmicec no-opengl hisil hisil-3716mv300 blindscan-tbs HDMI RCA 7segment textlcd ci hisil-recovery"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
	hdbox-dvb-modules-${MACHINE} \
	${@bb.utils.contains("MACHINE_FEATURES", "hisil-${HICHIPSET}", "hdbox-partitions-${HICHIPSET} hdbox-bootargs-${HICHIPSET} hdbox-bootlogo-${HICHIPSET} hdbox-fastboot-${HICHIPSET}" , "", d)} \
	${@bb.utils.contains("MACHINE_FEATURES", "hisil-recovery", "hdbox-recovery-${HICHIPSET}" , "", d)} \
	"

IMAGE_CMD_ubifs_prepend = " \
	rm -Rf ${IMAGE_ROOTFS}/tmp/*; \
	"

IMAGE_CMD_ubi_append = " \
	mkdir -p ${IMGDEPLOYDIR}/hdbox/${IMAGEDIR}; \
	cp -f ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.ubi ${IMGDEPLOYDIR}/hdbox/${IMAGEDIR}/${ROOTFS_FILE}; \
	cp -f ${DEPLOY_DIR_IMAGE}/uImage ${IMGDEPLOYDIR}/hdbox/${IMAGEDIR}/${KERNEL_FILE}; \
	cp -f ${IMGDEPLOYDIR}/recovery.img ${IMGDEPLOYDIR}/hdbox/${IMAGEDIR}/recovery.img; \
	cp -f ${DEPLOY_DIR_IMAGE}/hdbox-partitions-${MACHINE}/part.img ${IMGDEPLOYDIR}/hdbox/part.img; \
	cp -f ${DEPLOY_DIR_IMAGE}/hdbox-partitions-${MACHINE}/${MACHINE}/fastboot.img ${IMGDEPLOYDIR}/hdbox/${IMAGEDIR}/fastboot.img; \
	cp -f ${DEPLOY_DIR_IMAGE}/hdbox-partitions-${MACHINE}/${MACHINE}/bootargs.img ${IMGDEPLOYDIR}/hdbox/${IMAGEDIR}/bootargs.img; \
	cp -f ${DEPLOY_DIR_IMAGE}/hdbox-partitions-${MACHINE}/${MACHINE}/logo.img ${IMGDEPLOYDIR}/hdbox/${IMAGEDIR}/logo.img; \
	echo "${IMAGE_NAME}" > ${IMGDEPLOYDIR}/hdbox/imageversion; \
	echo "https://forum.openvision.tech/app.php/donate" > ${IMGDEPLOYDIR}/hdbox/donate.txt; \
	cd ${IMGDEPLOYDIR}/hdbox; \
	zip -r ../${IMAGE_NAME}_usb.zip *; \
	cd ..; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.ubi; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.ubifs; \
	rm -Rf hdbox; \
	rm -Rf ${DEPLOY_DIR_IMAGE}/hdbox-partitions-${MACHINE}; \
	"
