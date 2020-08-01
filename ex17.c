#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

// This is the struct for each row in the database
struct Address
{
    int id;
    int set;

    // 512 bytes max
    char name[MAX_DATA];
    
    // 512 bytes max
    char email[MAX_DATA];
};

// This is the struct for the database -- note that 100 address rows are set in it
struct Database
{
    // 100 Address rows max
    struct Address rows[MAX_ROWS];
};

// This is the struct for the Connection which points to the Database struct
struct Connection
{
    // Creates a pointer for the files to be read or written to
    FILE *file;
    struct Database *db;
};

// This function handles errors from the compiler and those set by the program
void die(const char *message)
{
    if (errno)
    {
        // Prints compiler errors from C
        perror(message);
    }
    else
    {
        // Prints errors to the user from the program
        printf("ERORR: %s\n", message);
    }
    
    // Exits the program
    exit(1);
}

// This function prints the address row by passing the pointer in the function argument
void Address_print(struct Address *addr)
{
    // Using addr pointer in the argument, it dereferences the elements in the Address struct
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

// This function loads the database using the pointer to the Connection struct passed in the argument
void Database_load(struct Connection *conn)
{
    // Reads the database using the pointer in the in the argument
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    
    // Checks to make sure the database was read and throws error if not using die function
    if (rc != 1)
    {
        die("Failed to load database.");
    }
}

// This function uses the pointer to the filename and the mode in the argument to allocate memory for the Connection and Database
// It then either opens the file if it exists or creates a new one if none exists
struct Connection *Database_open(const char *filename, char mode)
{
    // Allocating memory for the database structure by using Connection struct
    struct Connection *conn = malloc(sizeof(struct Connection));
    if (!conn)
    {
        die("Memory error!"); // Throws error using die function if issues are encountered allocating memory for Connection
    }

    // Alocating memory for the database structure by using the Database (+ Address) struct (Connection will point to Database)
    conn->db = malloc(sizeof(struct Database));
    if (!conn->db)
    {
        die("Memory error!"); // Throws error using die function if issues are encounter allocating memory for Database
    }

    // Opens the file to write to it or creates a new file if no file exists
    // If we are creating a new record, we do not need to read the database first so Database_load function is not called
    if (mode == 'c')
    {
        conn->file = fopen(filename, "w");
    }

    // Opens the file to read or write
    else
    {
        conn->file = fopen(filename, "r+");

        if (conn->file)
        {
            Database_load(conn);
        }
    }

    // Thorws error using die function if file load fails
    if (!conn->file)
    {
        die("Failed to open the file!");
    }

    // Returns connection address when Database_open is invoked
    return conn;
}

// This function closes the file and also the database by freeing memory for both the Connection and Database
void Database_close(struct Connection *conn)
{
    // Checks that Connection is not null
    if (conn)
    {
        // Checks that Connection has a file
        if (conn->file)
        {
            fclose(conn->file); // Closes the file
        }

        // Checks that the Connection has a Database which needs to have its memory freed
        if (conn->db)
        {
            free(conn->db); // Frees the memory for the Database
        }

        // Frees the memory for the Connection
        free(conn);
    }
}

// This function writes to the rows in the database by using the Connection pointer in the argument to deference the Database struct
void Database_write(struct Connection *conn)
{
    // Sets the position in the file to the beginning
    rewind(conn->file);

    // Writes the address data the out buffer
    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    
    // Checks that the file was written to successfully
    if (rc != 1)
    {
        die("Failed to write database!");
    }

    // Flushes the output buffer to the file (essentially writes it to the file)
    rc = fflush(conn->file);
    
    // Checks to make sure the output buffer was flushed
    if (rc == -1)
    {
        die("Cannot flush database!");
    }
}

// This function creates the database by passing the Connection pointer
void Database_create(struct Connection *conn)
{
    int i = 0;

    // This assigns an ID to each row in the Database and then indicates if it was set or not using the set element
    // Set = 1 means the row is set; set = 0 means it is not set
    for (i = 0; i < MAX_ROWS; i++)
    {
        // Make a prototype to initialize it
        struct Address addr = {.id = i, .set = 0};

        // Then just assign it
        conn->db->rows[i] = addr;
    }
}

// This is sets data into each row of the Database using the Connection pointer, ID, name and email as arguments
void Database_set(struct Connection *conn, int id, char *name, const char *email)
{
    // Gets the address of the row to using ID to add the data in
    struct Address *addr = &conn->db->rows[id];

    // Checks to see if the row has already been set (addr->set == 1)
    if (addr->set)
    {
        die("Already set, delete it first!"); // Throws error using die function to tell user the row is in use
    }

    // Sets the set element to 1 so the row to be written to is now marked as set
    addr->set = 1;
    
    // WARNING: Bug, read the "How To Break It" and fix this
    // Takes the name data from the argument and copies it to the Address name element in the row with a max size of 512kb
    char *res = strncpy(addr->name, name, MAX_DATA);

    // Demonstrate the strncpy bug
    // If copying the name argument to the row fails, this error is thrown using the die function
    if (!res)
    {
        die("Name copy failed!");
    }

    // Takes the email data from the argument and copies it to the Address email element in the row with a max size of 512kb
    res = strncpy(addr->email, email, MAX_DATA);

    // If copying the email argument to the row fails, this error is thrown using the die function
    if (!res)
    {
        die("Email copy failed!");
    }
}

// This function gets value in the row using the pointer to the Connection and the row ID
void Database_get(struct Connection *conn, int id)
{
    // Gets the pointer for the row by looking up the Connection pointer, the database pointer, and then the row ID
    struct Address *addr = &conn->db->rows[id];

    // If the row is set (i.e. it has data), then the row data is printed
    if (addr->set)
    {
        Address_print(addr);
    }

    // If the row is not set (no data), then an error is thrown using the die function
    else
    {
        die("ID is not set!");
    }
}

// This function delets the a row in the Database using the Connection pointer and row ID in the argument
void Database_delete(struct Connection *conn, int id)
{
    // Creates a struct in the stack that empties the row (except for the row's ID)
    struct Address addr = {.id = id, .set = 0};

    // Sets the rows data to addr from the stack
    conn->db->rows[id] = addr;
}

// This function lists all the set rows in the Database
void Database_list(struct Connection *conn)
{
    int i = 0;

    // Sets a pointer to the datbase by using the Connection pointer in the argument
    struct Database *db = conn->db;

    // Iterates through all the rows in the Database to find those which are set
    for (i = 0;  i < MAX_ROWS; i++)
    {
        // Sets a pointer in the stack for the current row in the database
        struct Address *cur = &db->rows[i];

        // If the row in the database has set == 1, then it prints the address data
        if (cur->set)
        {
            Address_print(cur); // Prints the address data of the current row using the pointer
        }
    }
}

int main(int argc, char *argv[])
{
    // If there aren't enough arguments in the command line, then instructions are output to the user
    if (argc < 3)
    {
        die("USAGE: ex17 <dbfile> <action> [action params]");
    }

    // Creates a string in the stack for the filename specified in the command line arguments
    char *filename = argv[1];

    // Creates a string in the stack for the action to be performed specified in the command line arguments
    char action = argv[2][0];

    // Opens the database by created a pointer to Connection using the filename and action arguments in those strings above
    struct Connection *conn = Database_open(filename, action);
    
    // Initializes the row ID to zero
    int id = 0;

    // If there are more than three command line arguments, the ID is set to the fourth argument
    if (argc > 3)
    {
        id = atoi(argv[3]);
    }

    // If the user specifies an ID that is outside of the allowed number of rows for the Database, an error is thrown
    if (id >= MAX_ROWS)
    {
        die("There's not that many records!");
    }

    // This switch executes code based upon the user's desired action in the command line arguments
    switch (action)
    {
        // Creates a new database calling the Database_create function and Database_write function
        // Also overwrites all data if the specified filename already exists
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;
        
        // Retrieves the row using the ID given in the command line arguments and the Database_get function
        case 'g':
            if (argc != 4)
            {
                die("Need an ID to get!"); // If there is no ID in the command line arguments, an error is thrown
            }

            Database_get(conn, id);
            break;
        
        // Sets new values for a row in the databse using ID, name and email in the command line arguments
        case 's':
            // Throws an error if there are not enough command line arguments 
            if (argc != 6)
            {
                die("Need id, name, email to set!");
            }
            
            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        // Deletes the data in a row within the Database given the row ID passed in the command line arguments
        case 'd':
            // Checks to ensure that the row ID is specified in the command line arguments
            if (argc != 4)
            {
                die("Need ID to delete!"); // Throws error using die function to inform user to included ID
            }

            Database_delete(conn, id);
            Database_write(conn);
            break;

        // Lists/prints all the set rows in the database
        case 'l':
            Database_list(conn);
            break;

        // If any other invalid command/action is passed in the command line arguments, then an error message is printed
        // This instructs the user of the valid actions that can be passed
        default:
            die("Invalid action: c = create, g = get, s = set, d = del, l = list");
    }

    // Closes the database by freeing the memory for the Database struct and then for the Connection struct
    // Ensure there are no memory leaks
    Database_close(conn);

    return 0;
}