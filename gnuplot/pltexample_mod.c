#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_POINTS 20
#define NUM_COMMANDS 6

int main()
{
    char * commandsForGnuplot[] = {"set title \"Test Plot\"", "set xrange [0:20]", "set yrange [0:400]", "plot 'plot.dat' using 1:2 with lines", "pause 1", "reread"};
    // double xvals[NUM_POINTS] = {1.0, 2.0, 3.0, 4.0, 5.0};
    // double yvals[NUM_POINTS] = {5.0 ,3.0, 1.0, 3.0, 5.0};
    FILE * temp = fopen("plot.dat", "w");
    /*Opens an interface that one can use to send commands as if they were typing into the
     *     gnuplot command line.  "The -persistent" keeps the plot open even after your
     *     C program terminates.
     */
    FILE * gnuplotPipe = popen ("gnuplot liveplot.gnu", "w");
    int i,j;
    for (i=0; i < NUM_POINTS; i++){

        fprintf(temp, "%lf %lf \n", (float)i, (float)(i*i));
        fflush(temp); //Write the data to a temporary file
        usleep(500*1000);

        // for (j=0; j < NUM_COMMANDS; j++){
        //     fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[j]);
        // }
        // usleep(500*1000);
    }

    return 0;
}
