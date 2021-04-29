DESCRIPTION = "${MACHINE} libraries"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
DEPENDS = "zlib libpng freetype curl libxml2 libjpeg-turbo harfbuzz"
RDEPENDS_${PN} = "libbluray curl"

PACKAGE_ARCH = "${MACHINE_ARCH}"

PV = "${SRCDATE}"

SRC_URI = "https://raw.githubusercontent.com/OpenVisionE2/hdbox-files/master/hdbox-libs-${HICHIPSET}-${SRCDATE}.zip"

S = "${WORKDIR}"

INHIBIT_PACKAGE_STRIP = "1"

# Disable anything auto depending on hdbox-libs
EXCLUDE_FROM_SHLIBS = "1"

# The driver is a set of binary libraries to install
# there's nothing to configure or compile
do_configure[noexec] = "1"
do_compile[noexec] = "1"

do_install() {
	install -d ${D}${bindir}
	install -m 0755 ${S}${base_bindir}/* ${D}${bindir}/
	install -d ${D}${INIT_D_DIR}
	install -m 0755 ${S}${sysconfdir}/* ${D}${INIT_D_DIR}/
	install -d ${D}${libdir}
	install -m 0755 ${S}/hisilicon/* ${D}${libdir}/
	install -m 0755 ${S}/extra/* ${D}${libdir}/
	install -d ${D}${libdir}/drm
	install -m 0755 ${S}/drm/* ${D}${libdir}/drm/
	if [ "${GLIBCVERSION}" = "2.25" ]; then
		cd ${D}${libdir}
		ln -s ld-linux-armhf.so.3 ld-linux.so.3
	fi
}

do_package_qa() {
}

FILES_${PN} = "/"
FILES_${PN}-dev = ""
