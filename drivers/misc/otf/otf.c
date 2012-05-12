#include "otf.h"

#define PROC_DIR "spica"

/*******************************************/
/* CPU1 On Min Khz */
/* Default value */
unsigned int NVRM_CPU1_ON_MIN_KHZ = 816000;
/* Min & Max Limit */
unsigned int ONMINLOW = 216000;
unsigned int ONMINHIGH = 1015000;
/*******************************************/
/* CPU1 Off Max Khz */
/* Default value */
unsigned int NVRM_CPU1_OFF_MAX_KHZ = 860000;
/* Min & Max Limit */
unsigned int OFFMAXLOW = 216000;
unsigned int OFFMAXHIGH = 1015000;
/*******************************************/
/* Default AVP Freq */
unsigned int AVPFREQ = 240000;
/* Min & Max Limit */
unsigned int AVPLOW = 200000;
unsigned int AVPHIGH = 280000;
/*******************************************/
/* Default GPU Freq */
unsigned int GPUFREQ = 300000;
/* Min & Max Limit */
unsigned int GPULOW = 280000;
unsigned int GPUHIGH = 350000;
/*******************************************/
/* Default VDE Freq */
unsigned int VDEFREQ = 650000;
/* Min & Max Limit */
unsigned int VDELOW = 500000;
unsigned int VDEHIGH = 700000;
/*******************************************/
unsigned int PWONOFF = 0;
unsigned int NITROONOFF = 0;
/*******************************************/
/* Default Screen Off Max CPU Freq */
unsigned int SCREENOFFFREQ = 324000;
/* Min & Max Limit */
unsigned int SMFREQLOW = 216000;
unsigned int SMFREQHIGH = 816000;
/*******************************************/
/* Default DDR2 Min Khz */
unsigned int NVRM_AP20_DDR2_MIN_KHZ = 50000;
/* Min & Max Limit */
unsigned int DDR2MINLOW = 10000;
unsigned int DDR2MINHIGH = 55000;
/*******************************************/
/* Default LPDDR2 Min Khz */
unsigned int NVRM_AP20_LPDDR2_MIN_KHZ = 18000;
/* Min & Max Limit */
unsigned int LPDDR2MINLOW = 7000;
unsigned int LPDDR2MINHIGH = 20000;
/*******************************************/

static struct proc_dir_entry *spica_dir = NULL;

void spica_init() {
spica_dir = proc_mkdir(PROC_DIR, NULL);
}

struct proc_dir_entry* spica_add(const char* name) {
if ( spica_dir == NULL ) spica_init();
return create_proc_entry(name, 0777, spica_dir);
}

void spica_remove(const char* name) {
remove_proc_entry(name, spica_dir);
}