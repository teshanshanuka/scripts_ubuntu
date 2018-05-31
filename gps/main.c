#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define R_EARTH 6371000

char *message;
char *temp_message;
volatile uint8_t tail_len = 0;

// fence radius is given in meters!
const float FENCE_RADIUS = 100.0f;

// reference point given in decimal degrees!
const float LATITUDE_REFERENCE = 46.522152f;
const float LONGITUDE_REFERENCE = 6.618629f;

double deg2rad(float degrees);

inline double deg2rad(float degrees){
	return degrees * 2 * M_PI / 360.0;
}

void rx(char rx_byte) {
	static int index = 0;
	//if (rx_byte == '$') {
	//	temp_message[index] = '\0';
	//	index = 0;
	//	strcpy(message, temp_message);
	//}
	//temp_message[index++] = rx_byte;

	if (tail_len != 0) tail_len++;

	if (rx_byte == '$'){
		index = 0;
		tail_len = 0;
    }
	else if (rx_byte == '*')
		tail_len++;

    temp_message[index++] = rx_byte;

	if (tail_len == 3) {
		temp_message[index] = '\0';
		strcpy(message, temp_message);
	}
}

bool check_cksum() {
	uint16_t cksum = 0;
	uint8_t i = 0;
	const char *s = message;
	s++;
	while (*s != '*' && i < 78) {
		cksum ^= *s++;
		i++;
	}
	
	char hex_str[] = { *++s, *++s };
	uint16_t orig_cksum = (uint16_t)strtol(hex_str, NULL, 16);

	return orig_cksum == cksum;
}

float str2coord(const char *_coord) {
	char * token = strchr(_coord, '.');
	char deg_str[4], min_str[8];

	strncpy(deg_str, _coord, (token - _coord - 2));
	deg_str[(token - _coord - 2)] = '\0';
	strcpy(min_str, token - 2);

	float deg = strtof(deg_str, NULL) + (float)strtof(min_str, NULL)/60.0;
	
	return deg;
}

float haversine(float lat, float lon)
{
	double dlong = deg2rad(lon - LONGITUDE_REFERENCE);
	double dlat = deg2rad(lat - LATITUDE_REFERENCE);
    double lat1 =  deg2rad(LATITUDE_REFERENCE);
    double lat2 =  deg2rad(lat);
	double a = sin(dlat/2) * sin(dlat/2) + sin(dlong/2) * sin(dlong/2) * cos(lat1) * cos(lat2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));

	return R_EARTH*c;
}

float get_dist() {
	bool message_good = false;
	float lat, lon;
	char * token = strtok(message, ",");

	uint8_t i = 1;

	while (i <= 6 && token != NULL) {
		token = strtok(NULL, ",");
		switch (i)
		{
		case 1:
			lat = str2coord(token);
			//printf("%s : ", token);
			break;
		case 2:
			if (*token == 'S') lat *= -1.0;
			printf("%f ", lat);
			break;
		case 3:
			//printf("%s : ", token);
			lon = str2coord(token);
			break;
		case 4:
			if (*token == 'W') lon *= -1.0;
			printf("%f\n", lon);
			break;
		case 6:
			if (*token == 'A' || *token == 'D') {
				message_good = true;
			}
			break;
		default:
			break;
		}
		i++;
	}

	if(message_good)
        return haversine(lat, lon);
    else
        return -1.0f;
}


bool check_in_fence() {
	return true;
}

int main() {
	char gparray[] = "$"
        "$GPGLL,3907.3837,N,12102.4684,W,023042,A,A*5E\n\n"
		"$GPGLL,4916.45,N,12311.12,W,225444,A,*1D\n\n"
		"$GPGLL,3907.360,N,12102.481,W,183730,A*33\n\n"
		"$GPGLL,3553.5295,N,13938.6570,E,002454,A,A*4F"
		"$GPGLL,6027.8259,N,02225.6713,E,152926,V,S*48"
		"$GPGLL,3907.3839,N,12102.4771,W,184051.812,A*2D\n\n"
		"$GPGLL,3907.3840,N,12102.4770,W,184052.812,A*21"
		"$GPGLL,5100.2111,N,00500.0006,E,104715.203,A*37"
		"$GPGLL,3350.975,N,11823.991,W,171537,A,D*50\n\n"
		"$GPGLL,3907.3813,N,12102.4635,W,230611.016,V*31"
		"$GPGLL,4259.8839,N,07130.3922,W,050306,V*20"
		"$GPGLL,3723.02837,N,12159.39853,W,162254.00,A,A*7C"
		"$GPGLL,4259.8839,N,07130.3922,W,050306,V*20";

	message = (char *)malloc(83 * sizeof(char));
    temp_message = (char *)malloc(83 * sizeof(char));

    printf("%f %f\n**********\n", LATITUDE_REFERENCE, LONGITUDE_REFERENCE);
    
    rx('$');
    for(int i=2; i<strlen(gparray); i++){
        rx(gparray[i]);
        
        if(gparray[i] == '$'){    
            //printf("%s\n", message);
    		if (check_cksum()) {
	    		printf("Distance: %.4f\n", get_dist());
	    	}
	    	else {
	    		printf("chechsum error\n****************\n");
	    	}
	    }	
	}

	for (;;);
	return 0;
}
