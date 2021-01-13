DESCRIPTION = "Linux kernel for ${MACHINE}"
SECTION = "kernel"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"

PACKAGE_ARCH = "${MACHINE_ARCH}"

KERNEL_RELEASE = "${KERNELVERSION}"

COMPATIBLE_MACHINE = "^(reborn)$"

inherit kernel machine_kernel_pr samba_change_dialect

SRC_URI[md5sum] = "810eabea1d1e8a8f2c7b28d4b1ef2ace"
SRC_URI[sha256sum] = "85fdf7f995492db5e7753424e9f35518826e1641d44da5e6de0b1904e8a0f006"

SRC_URI = "https://raw.githubusercontent.com/OpenVisionE2/hdbox-files/master/linux-${PV}_hisilicon.tar.gz \
	file://defconfig \
	file://${OPENVISION_BASE}/meta-openvision/recipes-linux/kernel-patches/kernel-add-support-for-gcc${VISIONGCCVERSION}.patch \
	file://timeconst_perl5.patch \
	file://disable-arch.patch \
	"

#file://0012-log2-give-up-on-gcc-constant-optimizations.patch
#file://0013-cp1emu-do-not-use-bools-for-arithmetic.patch
#file://0014-makefile-silence-packed-not-aligned-warn.patch
#file://0015-fcrypt-fix-bitoperation-for-gcc.patch

# By default, kernel.bbclass modifies package names to allow multiple kernels
# to be installed in parallel. We revert this change and rprovide the versioned
# package names instead, to allow only one kernel to be installed.
PKG_${KERNEL_PACKAGE_NAME}-base = "${KERNEL_PACKAGE_NAME}-base"
PKG_${KERNEL_PACKAGE_NAME}-image = "${KERNEL_PACKAGE_NAME}-image"
RPROVIDES_${KERNEL_PACKAGE_NAME}-base = "${KERNEL_PACKAGE_NAME}-${KERNEL_VERSION}"
RPROVIDES_${KERNEL_PACKAGE_NAME}-image = "${KERNEL_PACKAGE_NAME}-image-${KERNEL_VERSION}"

DEPENDS = "virtual/${TARGET_PREFIX}gcc"

KERNEL_CONFIG_COMMAND = "oe_runmake -C ${S} O=${B} oldconfig"

S = "${WORKDIR}/linux-${PV}_hisilicon"

export OS = "Linux"
KERNEL_OBJECT_SUFFIX = "ko"
KERNEL_IMAGEDEST = "tmp"
KERNEL_IMAGETYPE = "zImage"
KERNEL_OUTPUT = "zImage"

do_configure_prepend() {
	oe_runmake -C ${S} clean mrproper
}

kernel_do_install_append() {
	install -d ${D}/${KERNEL_IMAGEDEST}
	install -m 0755 ${KERNEL_OUTPUT_DIR}/${KERNEL_OUTPUT} ${D}/${KERNEL_IMAGEDEST}
}

do_shared_workdir_prepend() {
	mkdir -p ${B}/include/generated/
}

do_rm_work() {
}
