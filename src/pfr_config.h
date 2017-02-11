#ifndef PFR_CFG_DEFINED
#define PFR_CFC_DEFINED

    #ifdef __linux__

        #define PFR_CFG_DATA_FILE       "/home/eric/Projects/profiler/data/profiles.dat"
        #define PFR_CFG_DATA_TEMP_FILE  "/home/eric/Projects/profiler/data/profiles.tmp"
        #define PFR_CFG_TYPE_FILE       "/home/eric/Projects/profiler/data/types.dat"
        #define PFR_CFG_TYPE_TEMP_FILE  "/home/eric/Projects/profiler/data/types.tmp"
        
        #define PFR_CFG_PERMITTED       644

    #elif defined __MINGW32__

        #define PFR_CFG_DATA_FILE       "C:\\Dev\\profiler\\data\\profiles.dat"
        #define PFR_CFG_DATA_TEMP_FILE  "C:\\Dev\\profiler\\data\\profiles.tmp"
        #define PFR_CFG_TYPE_FILE       "C:\\Dev\\profiler\\data\\types.dat"
        #define PFR_CFG_TYPE_TEMP_FILE  "C:\\Dev\\profiler\\data\\types.tmp"
        
        #define PFR_CFG_PERMITTED       _S_IREAD | _S_IWRITE

    #endif

    #define PFR_CFG_TYPE_FIRST_ID 1
    #define PFR_CFG_DETAIL_FIRST_ID 1

#endif // pfr_config.h included
