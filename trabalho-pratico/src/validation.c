#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <ctype.h>
#include <math.h>

#include "../inc/users.h"
#include "../inc/flights.h"
#include "../inc/reservations.h"
#include "../inc/flight_stats.h"

int contemNArroba(const char *str) {
    int i = 0;
    while (*str) {
        if (*str == '@') {
            i++;
        }
        str++;
    }
    return i;
}

int dataFormatoCorreto(char *str) {
    int i = 0;
    while (*str) {
        if (*str == '|') {
            return 0;
        }
    }
    return 1;
}

int compareDates(char *data1, char *data2) {
    struct tm timeStruct1 = {0};
    struct tm timeStruct2 = {0};

    strptime(data1, "%Y/%m/%d %H:%M:%S", &timeStruct1);
    strptime(data2, "%Y/%m/%d %H:%M:%S", &timeStruct2);

    // Convert struct tm to time_t
    time_t time1 = mktime(&timeStruct1);
    time_t time2 = mktime(&timeStruct2);

    if (difftime(time1, time2) > 0) return 0; // data1 é depois da data2
    return 1;
}


int compareDatesSimple(char *date1, char *date2) {

    int year1, month1, day1;
    int year2, month2, day2;
    sscanf(date1, "%d/%d/%d", &year1, &month1, &day1);
    sscanf(date2, "%d/%d/%d", &year2, &month2, &day2);
    //2023/12/31
    //2024/01/2
    if((year1 > year2 || year1 == year2 && month1 > month2) || (year1 == year2 && month1 == month2 && day1 > day2 )) return 0;
    return 1;
}


int user_validation(USER *u) {

    int valido = 0;

    int year, month, day, hour, minute, second;
    char *id = getID(u);
    char *name = getName(u);
    char *phone_number = getPhoneNumber(u);
    char *sex = getSex(u);
    char *passport = getPassport(u);
    char *pay_method = getPayMethod(u);
    char *country_code = getCountryCode(u);
    char *account_status = getAccountStatus(u);
    char *birth_date = getBirthDate(u);
    char *email = getEmail(u);
    char *account_creation = getAccountCreation(u);
    char *address = getAddress(u);


    if (strlen(id) < 1) {valido = 1; goto cleanup;}
    //printf("%s\n", id);
    if (strlen(name) < 1) {valido = 1; goto cleanup;}
    //printf("%s\n", name);
    if (strlen(phone_number) < 1) {valido = 1; goto cleanup;}
    //printf("%s\n", phone_number);
    if (strlen(sex) < 1) {valido = 1; goto cleanup;}
    //printf("%s\n", sex);
    if (strlen(passport) < 1) {valido = 1; goto cleanup;}
    if (strlen(pay_method) < 1) {valido = 1; goto cleanup;}
    if (strlen(address) < 1) {valido = 1; goto cleanup;}
    //printf("%s\n", address);
    if (strlen(country_code) != 2) {valido = 1; goto cleanup;};
    if (!(strcasecmp(account_status, "active") == 0 || strcasecmp(account_status, "inactive") == 0)) {valido = 1; goto cleanup;}
    if (strlen(birth_date) != 10) {valido = 1; goto cleanup;}
    else if (sscanf(birth_date, "%d/%d/%d", &year, &month, &day) != 3) valido = 1;
    else if (!(year >= 0 && year <= 9999) || !(month >= 0 && month <= 12) || !(day >= 0 && day <= 31)) {valido = 1;goto cleanup;}
    else if (sscanf(account_creation, "%d/%d/%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) != 6) {valido = 1;goto cleanup;}
    else if (!(year >= 0 && year <= 9999) || !(month >= 1 && month <= 12) || !(day >= 1 && day <= 31) ||
             !(hour >= 0 && hour <= 23) || !(minute >= 0 && minute <= 59) || !(second >= 0 && second <= 59)) {valido = 1;goto cleanup;}

    if(contemNArroba(email) != 1) {valido = 1;goto cleanup;}
    const char *username = strtok(email, "@");
    const char *domain = strtok(NULL, ".");
    if(domain == NULL) {valido = 1;goto cleanup;}
    const char *tdl;
    if (contemNArroba(domain) != 0){
        {valido = 1;goto cleanup;}
    }
    else {
        tdl = strtok(NULL, "");
    }
    if (strlen(username) < 1 || strlen(domain) < 1 || strlen(tdl) < 2 || username == NULL || domain == NULL || tdl == NULL) {valido = 1;goto cleanup;}
    
cleanup:
    free(id);
    free(name);
    free(phone_number);
    free(sex);
    free(passport);
    free(pay_method);
    free(country_code);
    free(account_status);
    free(birth_date);
    free(email);

    return valido;
}
