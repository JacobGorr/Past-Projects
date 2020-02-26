/** CSci-4611 Assignment 2:  Car Soccer
    Jacob Gorr
 */

#include <stdio.h>
#include <time.h>
#include "car_soccer.h"

int main(int argc, const char *argv[]){
    srand(time(NULL));
    CarSoccer app;
    app.Run();
    return 0;
}
