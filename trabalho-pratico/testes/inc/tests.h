#ifndef tests_h
#define tests_h

#include "../../inc/stats.h"
#include "../../inc/catalogo_flights.h"
#include "../../inc/catalogo_invalids.h"
#include "../../inc/catalogo_passenger.h"
#include "../../inc/catalogo_reservations.h"
#include "../../inc/catalogo_user.h"
#include "../../inc/handle.h"
#include "../../inc/parser.h"

void run_test(char *files_path, char *data_input);
void execute_tests(char *data_input, char *test_path);

#endif