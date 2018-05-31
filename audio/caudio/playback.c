 #include <stdio.h>
 #include <math.h>
 #include "portaudio.h"

 #define SAMPLE_RATE (44100)
 #define AMPLITUDE (1)
 #define FRAMES_PER_BUFFER (64)
 #define FREQUENCY (256)
 #define TABLE_SIZE (SAMPLE_RATE/FREQUENCY)
 #define NUM_SECONDS (1)

 #define WRITEDATA

 typedef struct
 {
     float sine[TABLE_SIZE];
     int phase;
 }
 paTestData;

 #ifdef WRITEDATA
 FILE *csvf;
 #endif

 static int patestCallback( const void *inputBuffer, void *outputBuffer,
                             unsigned long framesPerBuffer,
                             const PaStreamCallbackTimeInfo* timeInfo,
                             PaStreamCallbackFlags statusFlags,
                             void *userData )
 {
     paTestData *data = (paTestData*)userData;
     float *out = (float*)outputBuffer;
     const float *rptr = (const float*)inputBuffer;
     unsigned long i;
     int finished = 0;
     /* avoid unused variable warnings */
     (void) timeInfo;
     (void) statusFlags;
     for( i=0; i<framesPerBuffer; i++ )
     {
         *out = data->sine[data->phase];  /* left */
         #ifdef WRITEDATA
         // fprintf(csvf, "%lf, %lf\n", *out, *rptr++);
         fprintf(csvf, "%d, %lf, %lf, %lf\n", data->phase, data->sine[data->phase], *out++, *rptr++);
         #endif
         data->phase += 1;
         if( data->phase >= TABLE_SIZE ) data->phase -= TABLE_SIZE;
     }
     return finished;
 }

 int main(void)
 {
     PaStream *stream;
     PaError err;
     paTestData data;

     printf("Frequency - set: %d actual: %.3f\n", FREQUENCY, (float)SAMPLE_RATE/(float)TABLE_SIZE);

     for (int i=0; i<TABLE_SIZE; i++)
     {
         data.sine[i] = (float)AMPLITUDE * sin(((double)i/(double)TABLE_SIZE) * M_PI * 2.);
     }
     data.phase = 0;

     #ifdef WRITEDATA
     csvf = fopen("data.csv", "w");
     #endif

     err = Pa_Initialize();
     if( err != paNoError ) goto error;

     err = Pa_OpenDefaultStream( &stream,
                                 1,          /* no input channels */
                                 1,          /* stereo output */
                                 paFloat32,  /* 32 bit floating point output */
                                 SAMPLE_RATE,
                                 FRAMES_PER_BUFFER,        /* frames per buffer, i.e. the number
                                                    of sample frames that PortAudio will
                                                    request from the callback. Many apps
                                                    may want to use
                                                    paFramesPerBufferUnspecified, which
                                                    tells PortAudio to pick the best,
                                                    possibly changing, buffer size.*/
                                 patestCallback, /* this is your callback function */
                                 &data ); /*This is a pointer that will be passed to
                                                    your callback*/

     if( err != paNoError ) goto error;

     err = Pa_StartStream( stream );
     if( err != paNoError ) goto error;

     Pa_Sleep( NUM_SECONDS * 1000 );

     err = Pa_StopStream( stream );
     if( err != paNoError ) goto error;

     err = Pa_CloseStream( stream );
     if( err != paNoError ) goto error;

     #ifdef WRITEDATA
     fclose(csvf);
     #endif

     Pa_Terminate();
     printf("Finished.\n");

     // for (int i=0; i<TABLE_SIZE; i++){
     //     printf("%lf,", data.sine[i]);
     // }

     return err;
 error:
     Pa_Terminate();
     fprintf( stderr, "An error occured while using the portaudio stream\n" );
     fprintf( stderr, "Error number: %d\n", err );
     fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
     return err;

     return 0;
 }
