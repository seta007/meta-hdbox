KERNELVERSION = "3.0.8"

# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED += "rtc"

TARGET_ARCH = "arm"
DEFAULTTUNE = "cortexa7hf"
require conf/machine/include/tune-cortexa7.inc

SOC_FAMILY = "hisi3716mv300"
HICHIPSET = "3716mv300"
CHIPSET = "Hi3716Mv300"

STB_PLATFORM = "hdboxhisi3716mv300"

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

DISTRO_FEATURES_remove += "x11 wayland directfb"

BOX_BRAND = "hdbox"

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

IMAGE_CMD_tar_prepend = " \
	rm -Rf ${IMAGE_ROOTFS}/tmp/*; \
	cp -f ${DEPLOY_DIR_IMAGE}/zImage ${DEPLOY_DIR_IMAGE}/hdbox-partitions-${MACHINE}/${IMAGEDIR}/${KERNEL_FILE}; \
	echo "${IMAGE_NAME}" > ${DEPLOY_DIR_IMAGE}/hdbox-partitions-${MACHINE}/${IMAGEDIR}/imageversion; \
	echo "https://forum.openvision.tech/app.php/donate" > ${DEPLOY_DIR_IMAGE}/hdbox-partitions-${MACHINE}/${IMAGEDIR}/donate.txt; \
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
