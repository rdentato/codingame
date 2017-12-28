#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    double x,y,d;
    double d_min=1E30;
    double lon_A, lon_B, lat_A, lat_B;
    char answer[257];
    char LON[51];
    scanf("%s", LON);
    char LAT[51];
    scanf("%s", LAT);
    int N;
    scanf("%d", &N); fgetc(stdin);
    answer[0] = '?'; answer[1]= '\0';
    for (int i = 0; ; i++) {
        char DEFIB[257];
        if (fgets(DEFIB, 257, stdin) == NULL) break;
        char *defib_name = NULL;
        char *defib_lon = NULL;
        char *defib_lat = NULL;
        int field = 0;
        
        for(int j=0; LON[j]; j++) if (LON[j]==',') LON[j] = '.';
        for(int j=0; LAT[j]; j++) if (LAT[j]==',') LAT[j] = '.';
        for(int j=0; DEFIB[j]; j++) { 
            if (DEFIB[j]==',') DEFIB[j] = '.';
            if (DEFIB[j]==';') {
              DEFIB[j] = '\0';
              switch (field++) {
                  case 0: defib_name = DEFIB+j+1; break;
                  case 3: defib_lon = DEFIB+j+1; break;
                  case 4: defib_lat = DEFIB+j+1; break;
              }
            }
            
        }
        lon_A = atof(LON);
        lat_A = atof(LAT);
        lon_B = atof(defib_lon);
        lat_B = atof(defib_lat);
        x = (lon_B - lon_A) * cos((lat_A+lat_B)/2.0);
        y = lat_B - lat_A;
        d = sqrt((x*x)+(y*y))*6371.0;
        //fprintf(stderr,"|%s|%s|%s|%s|%s",LON,LAT,defib_name,defib_lon,defib_lat);
        //fprintf(stderr,"lonA:%f latA:%f lonB:%f latB:%f d:%g min:%f\n",lon_A,lat_A,lon_B,lat_B,d,d_min);
        if (d <= d_min) {
            d_min = d;
            strcpy(answer,defib_name);
            fprintf(stderr,"%s:%s (%f)\n",DEFIB,answer,d);
        }
        //fputc('\n',stderr);
    }

    printf("%s\n",answer);

    return 0;
}