DESCRIPTION = "Hardware drivers for ${MACHINE}"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"

PACKAGE_ARCH = "${MACHINE_ARCH}"

RDEPENDS_${PN} += "libjpeg-turbo"

PV = "${KV}-${SRCDATE}"

KERNEL_VERSION = "${KV}_hisilicon"

SRC_URI = "https://raw.githubusercontent.com/OpenVisionE2/hdbox-files/master/${MACHINE}-drivers-${SRCDATE}.zip"

S = "${WORKDIR}"

INHIBIT_PACKAGE_STRIP = "1"

FILES_${PN} += "${sysconfdir}/modprobe.d ${sysconfdir}/modules-load.d ${nonarch_base_libdir}/modules/${KERNEL_VERSION}/extra"

do_install() {
	install -d ${D}${nonarch_base_libdir}/modules/${KERNEL_VERSION}/extra
	install -d ${D}${sysconfdir}/modprobe.d
	install -d ${D}${sysconfdir}/modules-load.d
	install -m 0755 ${S}/*.ko ${D}${nonarch_base_libdir}/modules/${KERNEL_VERSION}/extra
	install -m 0644 ${S}/modprobe.d/_${MACHINE}.conf ${D}${sysconfdir}/modprobe.d/
	install -m 0644 ${S}/modules-load.d/_${MACHINE}.conf ${D}${sysconfdir}/modules-load.d/
}

do_package_qa() {
}

# The driver is a set of binary libraries to install
# there's nothing to configure or compile
do_configure[noexec] = "1"
do_compile[noexec] = "1"
