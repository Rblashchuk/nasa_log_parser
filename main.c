#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include "string.h"

int mon_to_int(char *mon){
    if (strcmp(mon, "Jan") == 0){
        return 1;
    }
    if (strcmp(mon, "Feb") == 0){
        return 2;
    }
    if (strcmp(mon, "Mar") == 0){
        return 3;
    }
    if (strcmp(mon, "Apr") == 0){
        return 4;
    }
    if (strcmp(mon, "May") == 0){
        return 5;
    }
    if (strcmp(mon, "Jun") == 0){
        return 6;
    }
    if (strcmp(mon, "Jul") == 0){
        return 7;
    }
    if (strcmp(mon, "Aug") == 0){
        return 8;
    }
    if (strcmp(mon, "Sep") == 0){
        return 9;
    }
    if (strcmp(mon, "Oct") == 0){
        return 10;
    }
    if (strcmp(mon, "Nov") == 0){
        return 11;
    }
    if (strcmp(mon, "Dec") == 0){
        return 12;
    }
    return -1;
}


enum bool{
   False,
   True
};
int main() {
    struct tm time;
    FILE *f1, *f2, *fout;
    f1 = fopen("D:\\studying\\programming\\NASA_access_log_Jul95\\NASA_access_log_Jul95", "r");
    f2 = fopen("D:\\studying\\programming\\NASA_access_log_Jul95\\NASA_access_log_Jul95", "r");

    int cnt1 = 0;
    int cnt2 = 0;
    char remote[200];
    char request1[400];
    int response = 0;
    char bytes[5];
    char str[300];
    char month[4];

    int time_zone = 0;

    int time_int = 0;
    int time1 = 0;
    int time2 = 0;

    int max_req = 0;
    int max_req_ind = 0;
    int max_time = 0;


    printf("Input time interval (in sec):\n");
    scanf("%d", &time_int);
    while (cnt1 <= 1891715){

        if(time1 - time2 <= time_int){
            if (max_req < cnt1 - cnt2 + 1){
                max_req = cnt1 - cnt2 + 1;
                max_req_ind = cnt2;
                max_time = time2;
            }
            cnt1++;
            fscanf(f1, "%s - - [%d/%3c/%d:%d:%d:%d %d] \"%[^\"]\" %d %s\n", remote, &time.tm_mday, month, &time.tm_year, &time.tm_hour, &time.tm_min, &time.tm_sec, &time_zone, request1, &response, bytes);
            time.tm_mon = mon_to_int(month) - 1;
            time1 = time.tm_sec + time.tm_min*60 + time.tm_hour*3600 + (time.tm_mday - 1)*86400;
            //printf("%d min, %d sec, %s remote\n", min, sec, remote);
        }

        else{
            cnt2++;
            fscanf(f2, "%s - - [%d/%3c/%d:%d:%d:%d %d] \"%[^\"]\" %d %s\n", remote, &time.tm_mday, month, &time.tm_year, &time.tm_hour, &time.tm_min, &time.tm_sec, &time_zone, request1, &response, bytes);
            time.tm_mon = mon_to_int(month) - 1;
            time2 = time.tm_sec + time.tm_min*60 + time.tm_hour*3600 + (time.tm_mday - 1)*86400;
        }
        //printf("time2: %d, %d; time1: %d, %d \n", time2, cnt2, time1 ,cnt1);
    }
    printf("%d requests per %d sec were processed at: %d sec. (req.: %d)\n", max_req, time_int, max_time, max_req_ind);
}
