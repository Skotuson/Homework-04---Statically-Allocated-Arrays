#include <stdio.h>

#define ID_MAX 100000
#define DB_MAX 1000000

/**
 * Function which writes the ID to database.
 * @param db An array of all accesses
 * @param idDb An array of all possible IDs and their count
 * @param id The id which should be written into the database
 * @param dbSize Output parameter with the number of acesses stored in db
 * @return The frequency of the entered id from the ID database, which is used
 * to determine if it was the first or repeated access.
*/
int writeToDB ( int db[], int idDb[], int id, int * dbSize ) {
    db[ ( *dbSize )++ ] = id;
    return ++idDb[ id ];
}

/**
 * Function which searches the database from and to a certain index
 * and returns the number of unique acesses.
 * @param db An array of all accesses
 * @param from Lower bound of the search
 * @param to Upper bound of the search
 * @param uniq Output parameter with the number of unique accesses
*/
void searchDB( int db[], int from, int to, int * uniq ) {
    char arr[ DB_MAX ] = {};
    for ( int i = from; i <= to; i++ ){
        if ( !arr[ db[i] ] ) {
            arr[ db[i] ] = 1;
            *uniq += 1;
        }
    }
}

/**
 * Function which determines what operation should be executed.
 * Also checks if the inputs are valid.
 * @param db An array of all accesses
 * @param idDb An array of all possible IDs and their count.
 * @param dbSize Output parameter with the number of acesses stored in db
*/
int handleRequest ( int db[], int idDb[], int * dbSize ) {
    char c;
    int id, from, to; 
    int visits = 0, uniq = 0;
    int r = scanf( " %c" , &c );
    if ( r == EOF ) return EOF;
    if( r != 1 || ( c != '+' && c != '?' ) )
        return 0;
        
    switch ( c ) {

        case '+':
            if ( scanf (" %d", &id ) != 1 || id < 0 || id > ID_MAX - 1 )
                return 0;
            visits = writeToDB ( db, idDb, id, dbSize );
            printf( "> " );
            if ( visits == 1 ) printf("prvni navsteva\n" );
            else printf ( "navsteva #%d\n", visits );
            break;

        case '?':
            if ( scanf (" %d %d", &from, &to ) != 2 || from < 0 || to >= *dbSize || from > to )
                return 0;
            searchDB( db, from, to, &uniq );
            printf( "> %d / %d\n", uniq, to - from + 1 );
            break;
    }   
    return 1;
}

int main ( void ) {
    static int db[ DB_MAX ];
    static int idDb[ ID_MAX ];
    int dbSize = 0;
    int r;
    printf("Pozadavky:\n");
    while ( ( r = handleRequest ( db, idDb, &dbSize ) ) == 1 );
    if ( !feof ( stdin ) || !r ) {
        printf( "Nespravny vstup.\n" );
        return 1;
    }
    return 0;
}
