#include "http/api.h"
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "sqlite/sqlite3.h"
//x86#include "sqlite/include/sqlite3.h"

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char *argv[]){
    if (argc < 2) {
            printf("auth null\n");
            exit(1);
        }
    sqlite3 *db;
    sqlite3_open("ZKDB.db", &db);
    while(1){

        run(db, argv[1]);
        sleep(3);
    }
    sqlite3_close(db);
}

int run(sqlite3 *db, char *auth) {


   char *zErrMsg = 0;
   int rc;
   char *sql;
   char json[1024];
   char json1[1024];
   char **dbResult;
   char *errmsg;
   int nRow, nColumn;
   int index=0;
   int i, j;

   const char* data = "Callback function called";




   sql = "SELECT ID,User_PIN,Verify_Time from ATT_LOG where SEND_FLAG = 0 limit 5";

   rc = sqlite3_get_table( db, sql, &dbResult, &nRow, &nColumn, &errmsg);

   if( rc != SQLITE_OK ){
      printf( "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
       strcpy(json, "");

       printf("Select done successfully\n");
       index = nColumn; //字段值从index开始

       if(nRow == 0){
           printf("no data push\n");
           return 0;
       }

       printf("count:%d", nRow);
strcat(json, "[");
                      for( i = 0; i < nRow ; i++ )
                      {

                      if(index > 3){
                                                                                    strcat(json, ",");
                                                                                }
                            strcat(json, "{");

                              for( j = 0 ; j < nColumn; j++ )
                              {
                              if(j > 0){
strcat(json, ",");
}
                              strcat(json, "\"");
                              strcat(json, dbResult[j]);
                              strcat(json, "\"");
                              strcat(json, ":");
                              strcat(json, "\"");
                              strcpy(json1, dbResult[index]);
                              strcat(json, json1);
                              strcat(json, "\"");


                                      //printf( "%s=",dbResult[index]);
                                      index++;
                              }
                              strcat(json, "}");

                      }
                      strcat(json, "]");
                      printf(json);
                      printf("\n");
   }


    char* ret;
    char sql_update[1024];
    memset(sql_update, 0, 1024);

    getSealBase64(json, &ret, auth);

    strcat(sql_update, "UPDATE ATT_LOG set SEND_FLAG = 1 where ID in(");
    strcat(sql_update, ret);
    strcat(sql_update, ");");
        printf("\n");
        printf(sql_update);
        printf("\n");
    //return 0;
    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql_update, callback, (void*)data, &zErrMsg);
       if( rc != SQLITE_OK ){
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
       }else{
          fprintf(stdout, "Update done successfully\n");
       }


    //getSealListInfoBySn("8129455902011118", &ret);
    //printf("结果ret:\n%s\n", ret);
    return 0;
}

