/**
 * Author: Joe Biwer
 * Date: November 11, 2018
 * Description: Functions used in signal and alarm application
 */


#include <time.h>


/**
 * Function used to generate random times where times[0] < times[1] < times[2] < ..... < times[n]
 * param[in]    _times      Array to which random times should be placed in
 * param[in]    _size       Amount of times to be placed in the array (size of the array)
 */
void generate_times(time_t *, int);