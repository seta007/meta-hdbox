SUMMARY = "${MACHINE} partitions files"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"

PACKAGE_ARCH = "${MACHINE_ARCH}"

PV = "${SRCDATE}"

inherit deploy

SRC_URI = "https://raw.githubusercontent.com/OpenVisionE2/hdbox-files/master/hdbox-partitions-${HICHIPSET}-${SRCDATE}.zip"

S = "${WORKDIR}"

ALLOW_EMPTY_${PN} = "1"
do_configure[nostamp] = "1"

do_deploy() {
    install -d ${DEPLOY_DIR_IMAGE}/hdbox-partitions-${MACHINE}/${MACHINE}
    install -m 0755 ${WORKDIR}/part.img ${DEPLOY_DIR_IMAGE}/hdbox-partitions-${MACHINE}/${MACHINE}/
}

addtask deploy before do_build after do_install
