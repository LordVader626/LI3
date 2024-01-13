#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#include "../inc/users.h"
#include "../inc/flights.h"
#include "../inc/reservations.h"


/*
    Funcao que returna 0 caso um email contenha @
*/
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

/*
    Função que ajuda a verificar se uma data tem um formato correto
*/
int dataFormatoCorreto(char *str) {
    while (*str) {
        if (*str == '|') {
            return 0;
        }
    }
    return 1;
}

/*
    Função usada para comprar 2 datas (incluindo horas)
*/
int compareDates(char *data1, char *data2) {
    struct tm timeStruct1 = {0};
    struct tm timeStruct2 = {0};

    strptime(data1, "%Y/%m/%d %H:%M:%S", &timeStruct1);
    strptime(data2, "%Y/%m/%d %H:%M:%S", &timeStruct2);

    // Convert struct tm to time_t
    time_t time1 = mktime(&timeStruct1);
    time_t time2 = mktime(&timeStruct2);

    if (difftime(time1, time2) > 0) return 0; // data1 é depois da data2
    if (difftime(time1,time2) == 0) return -1;
    return 1;
}


/*
    Função que comprada datas
*/
int compareDatesSimple(char *date1, char *date2) {

    int year1, month1, day1;
    int year2, month2, day2;
    sscanf(date1, "%d/%d/%d", &year1, &month1, &day1);
    sscanf(date2, "%d/%d/%d", &year2, &month2, &day2);

    if((year1 > year2 || (year1 == year2 && month1 > month2)) || (year1 == year2 && month1 == month2 && day1 > day2 )) return 0;
    return 1;
}


/*
    Função responsavel por validar os campos do utilizador
*/
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
    free(address);
    free(pay_method);
    free(country_code);
    free(account_creation);
    free(account_status);
    free(birth_date);
    free(email);

    return valido;
}


/*
    Função responsavel por verificar todos os campos de um voo
*/
int flight_validation_1phase(FLIGHT *f){
    //total seats nao pode ser menos que passageiros (countar todos os passageiros com getFlightID e verificar)
    int valido = 0;

    int year, month, day, hour, minute, second;

    char *id_flight = getID_flight(f);
    char *airline = getAirline(f);
    char *plane_model = getPlaneModel(f);
    char *pilot = getPilot(f);
    char *copilot = getCopilot(f);
    int totalSeats = getTotalSeats(f);
    char *flightOrigin = getFlightOrigin(f);
    char *flightDestination = getFlightDestination(f);
    char *schDepDate = getScheduleDepartureDate(f);
    char *schArrDate = getScheduleArrivalDate(f);
    char *realDepDate = getRealDepartureDate(f);
    char *realArrDate = getRealArrivalDate(f);

    //id airlaine plane_model pilot copilot > 0
    if (strlen(id_flight) < 1) {valido = 1;goto cleanup;}
    if (strlen(airline) < 1) {valido = 1;goto cleanup;}
    if (strlen(plane_model) < 1) {valido = 1;goto cleanup;}
    if (strlen(pilot) < 1) {valido = 1;goto cleanup;}
    if (strlen(copilot) < 1) {valido = 1;goto cleanup;}

    if ((totalSeats) == 0) {valido = 1;goto cleanup;}

    //aeroportos 3LETRAS
    if (strlen(flightOrigin) != 3) {valido = 1;goto cleanup;}
    if (strlen(flightDestination) != 3) {valido = 1;goto cleanup;}

    //4 dates with yyyy/mm/dd and hours/minutes/sec hours 0, 23 min 0,59 sec 0,59
    if(strlen(schDepDate) != 19) {valido = 1;goto cleanup;}
    else if (sscanf(schDepDate, "%d/%d/%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) != 6) {valido = 1;goto cleanup;}
    else if (!(year >= 0 && year <= 9999) || !(month >= 0 && month <= 12) || !(day >= 0 && day <= 31) || 
            !(hour >= 0 && hour <=23) || !(minute >= 0 && minute <= 59) || !(second >= 0 && second <= 59)) {valido = 1;goto cleanup;}

    if(strlen(schArrDate) != 19) {valido = 1;goto cleanup;}
    else if (sscanf(schArrDate, "%d/%d/%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) != 6) {valido = 1;goto cleanup;}
    else if (!(year >= 0 && year <= 9999) || !(month >= 0 && month <= 12) || !(day >= 0 && day <= 31) || 
            !(hour >= 0 && hour <=23) || !(minute >= 0 && minute <= 59) || !(second >= 0 && second <= 59)) {valido = 1;goto cleanup;}

    if(strlen(realDepDate) != 19) {valido = 1;goto cleanup;}
    else if (sscanf(realDepDate, "%d/%d/%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) != 6) {valido = 1;goto cleanup;}
    else if (!(year >= 0 && year <= 9999) || !(month >= 0 && month <= 12) || !(day >= 0 && day <= 31) || 
            !(hour >= 0 && hour <=23) || !(minute >= 0 && minute <= 59) || !(second >= 0 && second <= 59)) {valido = 1;goto cleanup;}

    if (strlen(realArrDate) != 19) {valido = 1;goto cleanup;}
    else if (sscanf(realArrDate, "%d/%d/%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) != 6) {valido = 1;goto cleanup;}
    else if (!(year >= 0 && year <= 9999) || !(month >= 0 && month <= 12) || !(day >= 0 && day <= 31) || 
            !(hour >= 0 && hour <=23) || !(minute >= 0 && minute <= 59) || !(second >= 0 && second <= 59)) {valido = 1;goto cleanup;} 
    
    if(compareDates(schDepDate, schArrDate) == 0) {valido = 1;goto cleanup;}
    if(compareDates(realDepDate, realArrDate) == 0) {valido = 1;goto cleanup;}

cleanup:
    free(id_flight);
    free(airline);
    free(plane_model);
    free(pilot);
    free(copilot);
    free(flightOrigin);
    free(flightDestination);
    free(schDepDate);
    free(schArrDate);
    free(realDepDate);
    free(realArrDate);

    return valido;
}

/*
    Função responsável por validar uma reservation
*/
int reservation_validation(RESERVATION *r){
    int valido = 0;
    double hotel_stars, city_tax, price_per_night, rating;

    int beginYear, beginMonth, beginDay;
    int endYear, endMonth, endDay;
    //id, user_id, hotel_id, hotel_name, addres > 1

    char *idReservation = getID_reservation(r);;
    char *userID = getUserID_reservartion(r);
    char *hotelID = getHotelID_reservation(r);
    char *hotelName = getHotelName_reservation(r);
    char *address = getAddress_reservation(r);
    char *breakfast = getIncludesBreakfast_reservation(r);
    char *beginDate = getBeginDate_reservation(r);
    char *endDate = getEndDate_reservation(r);
    
    if (strlen(idReservation) < 1) {valido = 1; goto cleanup;}
    if (strlen(userID) < 1) {valido = 1; goto cleanup;}
    if (strlen(hotelID) < 1) {valido = 1; goto cleanup;}
    if (strlen(hotelName) < 1) {valido = 1; goto cleanup;}
    if (strlen(address) < 1) {valido = 1; goto cleanup;}

    hotel_stars = getHotelStars_reservation(r);
    if (hotel_stars < 0 || hotel_stars > 5 || hotel_stars != round(hotel_stars)) {valido = 1; goto cleanup;};

    city_tax = getCityTax_reservation(r);
    
    if (city_tax <= 0 || city_tax != round(city_tax)) {
        valido = 1;
        goto cleanup;
    }  

    price_per_night = getPricePerNight_reservation(r);
    if (price_per_night <= 0 || price_per_night != round(price_per_night)) {valido = 1; goto cleanup;}

    rating = getRating_reservation(r);
    if (rating < 0 || rating > 5 || rating != round(rating)) {valido = 1; goto cleanup;}

    if (strlen(beginDate) < 4) {valido = 1; goto cleanup;}

    if (beginDate[4] < '/' || beginDate[7] > '/') {
        valido = 1;
        goto cleanup;
    }

    if (endDate[4] < '/' || endDate[7] > '/') {
        valido = 1;
        goto cleanup;
    }
    
    // Para valores falsos, “f ”, “false”, “0”, e “” (string vazia); Para valores verdadeiros, “t”, “true”, e “1”.
    if (!(strcasecmp(breakfast, "f") == 0 || strcasecmp(breakfast, "false") == 0 || strcmp(breakfast, "") == 0 || strcmp(breakfast, "0") == 0 ||
        strcasecmp(breakfast, "t") == 0 || strcasecmp(breakfast, "true") == 0 || strcmp(breakfast, "1") == 0)) {
        valido = 1;
        goto cleanup;
    }

        // Para valores falsos, “f ”, “false”, “0”, e “” (string vazia); Para valores verdadeiros, “t”, “true”, e “1”.
    /*for (int i = 0; breakfast[i]; i++) {
        breakfast[i] = tolower(breakfast[i]);
    }
    if (!(strcmp(breakfast, "f") == 0 || strcmp(breakfast, "false") == 0 || strcmp(breakfast, "") == 0 ||
          strcmp(breakfast, "0") == 0 || strcmp(breakfast, "t") == 0 || strcmp(breakfast, "true") == 0 ||
          breakfast[0] == '0')) {
        valido = 1;
        goto cleanup;
    }*/

    if(strlen(beginDate) != 10) {valido = 1;goto cleanup;}
    else if (sscanf(beginDate, "%d/%d/%d", &beginYear, &beginMonth, &beginDay) != 3) {valido = 1;goto cleanup;}
    else if (!(beginYear >= 0 && beginYear <= 9999) || !(beginMonth >= 0 && beginMonth <= 12) || !(beginDay >= 0 && beginDay <= 31)) {valido = 1;goto cleanup;}

    if(strlen(endDate) != 10) {valido = 1;goto cleanup;}
    else if (sscanf(endDate, "%d/%d/%d", &endYear, &endMonth, &endDay) != 3) {valido = 1;goto cleanup;}
    else if (!(endYear >= 0 && endYear <= 9999) || !(endMonth >= 0 && endMonth <= 12) || !(endDay >= 0 && endDay <= 31)) {valido = 1;goto cleanup;}

    if(compareDatesSimple(beginDate, endDate) == 0) {valido = 1;goto cleanup;}
    
cleanup:
    free(idReservation);
    free(userID);
    free(hotelID);
    free(hotelName);
    free(address);
    free(breakfast);
    free(beginDate);
    free(endDate);

    return valido;
}