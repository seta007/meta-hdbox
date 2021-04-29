DESCRIPTION = "Linux kernel for ${MACHINE}"
SECTION = "kernel"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"

PACKAGE_ARCH = "${MACHINE_ARCH}"

KERNEL_RELEASE = "${KERNELVERSION}"

COMPATIBLE_MACHINE = "^(reborn)$"

inherit kernel machine_kernel_pr samba_change_dialect

SRC_URI = "https://raw.githubusercontent.com/OpenVisionE2/hdbox-files/master/linux-${PV}_hisilicon.tar.gz;name=hikernel \
	https://raw.githubusercontent.com/OpenVisionE2/hdbox-files/master/arm-eabi-4.6.tar.bz2;name=higcc \
	file://defconfig \
	file://timeconst_perl5.patch \
	file://disable-arch.patch \
	file://bypass_ipv6_filter.patch \
	"

SRC_URI[hikernel.md5sum] = "810eabea1d1e8a8f2c7b28d4b1ef2ace"
SRC_URI[hikernel.sha256sum] = "85fdf7f995492db5e7753424e9f35518826e1641d44da5e6de0b1904e8a0f006"
SRC_URI[higcc.md5sum] = "310963884c4956d0ae3746c068762f73"
SRC_URI[higcc.sha256sum] = "f5d29121c8157b86062d180f8c202c32f8dd82f8accf50b4f111d608da191d8a"

# By default, kernel.bbclass modifies package names to allow multiple kernels
# to be installed in parallel. We revert this change and rprovide the versioned
# package names instead, to allow only one kernel to be installed.
PKG_${KERNEL_PACKAGE_NAME}-base = "${KERNEL_PACKAGE_NAME}-base"
PKG_${KERNEL_PACKAGE_NAME}-image = "${KERNEL_PACKAGE_NAME}-image"
RPROVIDES_${KERNEL_PACKAGE_NAME}-base = "${KERNEL_PACKAGE_NAME}-${KERNEL_VERSION}"
RPROVIDES_${KERNEL_PACKAGE_NAME}-image = "${KERNEL_PACKAGE_NAME}-image-${KERNEL_VERSION}"

#DEPENDS = "virtual/${TARGET_PREFIX}gcc"

KERNEL_CONFIG_COMMAND = "oe_runmake -C ${S} O=${B} oldconfig"

S = "${WORKDIR}/linux-${PV}_hisilicon"
B = "${WORKDIR}/build"

export OS = "Linux"
KERNEL_OBJECT_SUFFIX = "ko"
KERNEL_IMAGEDEST = "tmp"
KERNEL_IMAGETYPE = "zImage"
KERNEL_OUTPUT = "arch/${ARCH}/boot/${KERNEL_IMAGETYPE}"

FILES_${KERNEL_PACKAGE_NAME}-image = "/${KERNEL_IMAGEDEST}/zImage"

do_configure_prepend() {
	oe_runmake -C ${S} clean mrproper
	install -m 0644 ${WORKDIR}/defconfig ${B}/.config
}

kernel_do_install_append() {
        install -d ${D}/${KERNEL_IMAGEDEST}
        install -m 0755 ${KERNEL_OUTPUT} ${D}/${KERNEL_IMAGEDEST}
}

kernel_do_compile() {
        unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS MACHINE
        cd ${B}
        oe_runmake ARCH=arm CROSS_COMPILE=../arm-eabi-4.6/bin/arm-eabi- ${PARALLEL_MAKE}
}

do_compile_kernelmodules() {
}

do_rm_work() {
}

export KCFLAGS = "-Wno-error \
                  -Wno-implicit-function-declaration \
                  "

pkg_postrm_${KERNEL_PACKAGE_NAME}-image () {
}

# extra tasks
addtask kernel_link_images after do_compile before do_install
