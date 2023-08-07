/*#ifndef SD_CARD
#define SD_CARD

#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/sdmmc_host.h"

class SD_STORE {
    public:
        static esp_err_t s_example_write_file(const char *path, char *data);

        static esp_err_t s_example_read_file(const char *path);


};

#endif*/ //SD_CARD