#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
// #include <string.h>

FILE *datapipe;

int main(){
    float y1 = 1.0, y2 = 0.9;
    float x = 0;
    float y[100];

    int i, j, length;
    char buf[100*19];

    for (j=0; j<20; j++){
        for (i=0; i<100; i++){
            y[i] = sin(2*M_PI*y1*x) + sin(2*M_PI*y2*x);
            x++;
        }

        datapipe = open("rtdata.dat", O_WRONLY);
        length = 0;

        for (i=0; i<100; i++){
            length += sprintf(buf+length, "%1.6f %1.6f \n", x++, y[i]);
            // printf("%lf %lf \n", x++, y[i]);
            printf("%d %d\n", i, j);
        }

        write(datapipe, buf, length);
        close(datapipe);
         usleep(1000);
         printf("done\n");

    }
    // unlink("rtdata.dat");

    return 0;
}
