#include "ibm.h"
#include "device.h"
#include "hdd.h"

#include "ide.h"
#include <pcem/devices.h>
#include <pcem/defines.h>

PcemHDC hdc[7];

extern HDD_CONTROLLER *hdd_controllers[HDDCONTROLLERS_MAX];
char hdd_controller_name[16];

static device_t null_hdd_device;

static int hdd_controller_current;

char *hdd_controller_get_name(int hdd) {
        if (hdd_controllers[hdd] != NULL)
                return hdd_controllers[hdd]->name;
        return "";
}

char *hdd_controller_get_internal_name(int hdd) {
        if (hdd_controllers[hdd] != NULL)
                return hdd_controllers[hdd]->internal_name;
        return "";
}

int hdd_controller_get_flags(int hdd) {
        if (hdd_controllers[hdd] != NULL)
                return hdd_controllers[hdd]->device->flags;
        return 0;
}

int hdd_controller_available(int hdd) {
        if (hdd_controllers[hdd] != NULL)
                return device_available(hdd_controllers[hdd]->device);
        return 0;
}

int hdd_controller_is_mfm(char *internal_name) {
        int c = 0;

        while (hdd_controllers[c] != NULL) {
                if (!strcmp(internal_name, hdd_controllers[c]->internal_name)) {
                        hdd_controller_current = c;
                        if (strcmp(internal_name, "none"))
                                return hdd_controllers[c]->is_mfm;
                }
                c++;
        }

        return 0;
}
int hdd_controller_is_ide(char *internal_name) {
        int c = 0;

        while (hdd_controllers[c] != NULL) {
                if (!strcmp(internal_name, hdd_controllers[c]->internal_name)) {
                        hdd_controller_current = c;
                        if (strcmp(internal_name, "none"))
                                return hdd_controllers[c]->is_ide;
                }
                c++;
        }

        return 0;
}
int hdd_controller_is_scsi(char *internal_name) {
        int c = 0;

        while (hdd_controllers[c] != NULL) {
                if (!strcmp(internal_name, hdd_controllers[c]->internal_name)) {
                        hdd_controller_current = c;
                        if (strcmp(internal_name, "none"))
                                return hdd_controllers[c]->is_scsi;
                }
                c++;
        }

        return 0;
}
int hdd_controller_has_config(char *internal_name) {
        int c = 0;

        while (hdd_controllers[c] != NULL) {
                if (!strcmp(internal_name, hdd_controllers[c]->internal_name)) {
                        hdd_controller_current = c;
                        if (strcmp(internal_name, "none"))
                                return hdd_controllers[c]->device->config ? 1 : 0;
                }
                c++;
        }

        return 0;
}

device_t *hdd_controller_get_device(char *internal_name) {
        int c = 0;

        while (hdd_controllers[c] != NULL) {
                if (!strcmp(internal_name, hdd_controllers[c]->internal_name)) {
                        hdd_controller_current = c;
                        if (strcmp(internal_name, "none"))
                                return hdd_controllers[c]->device;
                }
                c++;
        }

        return NULL;
}

int hdd_controller_current_is_mfm() { return hdd_controller_is_mfm(hdd_controller_name); }
int hdd_controller_current_is_ide() { return hdd_controller_is_ide(hdd_controller_name); }
int hdd_controller_current_is_scsi() { return hdd_controller_is_scsi(hdd_controller_name); }

void hdd_controller_init(char *internal_name) {
        int c = 0;

        while (hdd_controllers[c] != NULL) {
                if (!strcmp(internal_name, hdd_controllers[c]->internal_name)) {
                        hdd_controller_current = c;
                        if (strcmp(internal_name, "none"))
                                device_add(hdd_controllers[c]->device);
                        return;
                }
                c++;
        }
        /*        fatal("Could not find hdd_controller %s\n", internal_name);*/
}

static void *null_hdd_init() { return NULL; }

static void null_hdd_close(void *p) {}

static device_t null_hdd_device = {"Null HDD controller", 0, null_hdd_init, null_hdd_close, NULL, NULL, NULL, NULL, NULL};

HDD_CONTROLLER h_none = {"None", "none", &null_hdd_device, 0, 0, 0};
HDD_CONTROLLER h_ide = {"[IDE] Standard IDE", "ide", &ide_device, 0, 1, 0};

void hdd_controller_init_builtin() {
        pcem_add_hddcontroller(&h_none);
        pcem_add_hddcontroller(&h_ide);
}