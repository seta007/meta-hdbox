DESCRIPTION = "Hardware drivers for ${MACHINE}"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"

PACKAGE_ARCH = "${MACHINE_ARCH}"

RDEPENDS_${PN} += "libjpeg-turbo"

PV = "${KV}-${SRCDATE}"

SRC_URI = "https://raw.githubusercontent.com/OpenVisionE2/hdbox-files/master/${MACHINE}-drivers-${SRCDATE}.zip"

S = "${WORKDIR}"

INHIBIT_PACKAGE_STRIP = "1"

FILES_${PN} += "${sysconfdir}/modprobe.d ${sysconfdir}/modules-load.d ${nonarch_base_libdir}/modules/${KV}/extra"

do_compile() {
}

do_install() {
	install -d ${D}${nonarch_base_libdir}/modules/${KV}/extra
	install -d ${D}${sysconfdir}/modprobe.d
	install -d ${D}${sysconfdir}/modules-load.d
	install -m 0755 ${S}/*.ko ${D}${nonarch_base_libdir}/modules/${KV}/extra
	install -m 0644 ${S}/modprobe.d/_${MACHINE}.conf ${D}${sysconfdir}/modprobe.d/
	install -m 0644 ${S}/modules-load.d/_${MACHINE}.conf ${D}${sysconfdir}/modules-load.d/
}

pkg_prerm_${PN}() {
	if [ "x$D" == "x" ]; then
		if [ -f ${nonarch_base_libdir}/modules/${KV}/extra/hi_play.ko ] ; then
			rm -f ${nonarch_base_libdir}/modules/${KV}/extra/hi_play.ko;
		fi
	fi
}

do_package_qa() {
}

do_configure[noexec] = "1"
