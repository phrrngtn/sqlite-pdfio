
#include <sqlite3ext.h>
SQLITE_EXTENSION_INIT1

#include "tg/tg.h"

#include <iostream>
#include <nlohmann/json.hpp>

#ifdef WIN32
#define SQLITE_EXTENSION_ENTRY_POINT __declspec(dllexport)
#else
#define SQLITE_EXTENSION_ENTRY_POINT
#endif

using namespace std;

// Inspired by https://github.com/0x09/sqlite-statement-vtab/blob/master/statement_vtab.c
#ifdef SQLITE_CORE
#define sqlite_pdfio_entry_point sqlite_pdfio_init
#else
#define sqlite_pdfio_entry_point sqlite3_extension_init
#endif

// This needs to be callable from C
extern "C" SQLITE_EXTENSION_ENTRY_POINT int sqlite_pdfio_entry_point(
    sqlite3 *db,
    char **pzErrMsg,
    const sqlite3_api_routines *pApi);


static void pdfio_pages(
    sqlite3_context *context,
    int argc,
    sqlite3_value **argv)
{
  assert(argc >= 2);

  if (sqlite3_value_type(argv[0]) == SQLITE_NULL ||
      sqlite3_value_type(argv[1]) == SQLITE_NULL)
  {
    sqlite3_result_null(context);
    return;
  }

  std::string result_as_string = "banana";

    sqlite3_result_text(context, result_as_string.data(), (int)result_as_string.length(), SQLITE_TRANSIENT);

  return;
}

int sqlite_pdfio_entry_point(
    sqlite3 *db,
    char **pzErrMsg,
    const sqlite3_api_routines *pApi)
{
  int rc = SQLITE_OK;
  SQLITE_EXTENSION_INIT2(pApi);
  (void)pzErrMsg; /* Unused parameter */

  rc = sqlite3_create_function(db, "pdfio_pages", 2,
                               SQLITE_UTF8 | SQLITE_DETERMINISTIC,
                               0, pdfio_pages, 0, 0);

  return rc;
}
