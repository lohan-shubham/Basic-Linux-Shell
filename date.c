#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
char *calcMonth(int month_number)
{
    if (month_number == 0)
    {
        return "Jan";
    }
    if (month_number == 1)
    {
        return "Feb";
    }
    if (month_number == 2)
    {
        return "Mar";
    }
    if (month_number == 3)
    {
        return "Apr";
    }
    if (month_number == 4)
    {
        return "May";
    }
    if (month_number == 5)
    {
        return "Jun";
    }
    if (month_number == 6)
    {
        return "Jul";
    }
    if (month_number == 7)
    {
        return "Aug";
    }
    if (month_number == 8)
    {
        return "Sep";
    }
    if (month_number == 9)
    {
        return "Oct";
    }
    if (month_number == 10)
    {
        return "Nov";
    }
    if (month_number == 11)
    {
        return "Dec";
    }
}
char *calcDay(int dayNumber)
{
    if (dayNumber == 0)
    {
        return "Sun";
    }
    if (dayNumber == 1)
    {
        return "Mon";
    }
    if (dayNumber == 2)
    {
        return "Tue";
    }
    if (dayNumber == 3)
    {
        return "Wed";
    }
    if (dayNumber == 4)
    {
        return "Thu";
    }
    if (dayNumber == 5)
    {
        return "Fri";
    }
    if (dayNumber == 6)
    {
        return "Sat";
    }
}
void main(int argc, char *argv[])
{   time_t current_time;
    char *c_time_string;
    current_time = time(NULL);
    struct tm *local = localtime(&current_time);
    
    //  printf("%d \n",argc);
    // printf("inside date\n");
    // for(int i=0;i<argc;i++){
    //     printf("%s ",argv[i]);
        
    // }
    if(argc==1){
    printf("%s %s %d  %02d:%02d:%02d IST %d\n",calcDay(local->tm_wday), calcMonth(local->tm_mon),local->tm_mday, local->tm_hour,
           local->tm_min, local->tm_sec,1900+local->tm_year); // Local timezone
    }

    if(strcmp(argv[1],"-u")==0){
 /* Obtain current time. */
        struct tm *global = gmtime(&current_time);
        printf("%s, %s %d  %02d:%02d:%02d UTC %d\n",calcDay(global->tm_wday), calcMonth(global->tm_mon),global->tm_mday, global->tm_hour,
           global->tm_min, global->tm_sec,1900+global->tm_year);  //UTC timezone
    }
    if(strcmp(argv[1],"-R")==0){
         printf("%s, %s %d  %02d:%02d:%02d IST %d +0530\n",calcDay(local->tm_wday), calcMonth(local->tm_mon),local->tm_mday, local->tm_hour,
           local->tm_min, local->tm_sec,1900+local->tm_year); // Local timezone
    }

}