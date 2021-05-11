# define MAXNAME (20)
// Declaration
struct person {
    char name[MAXNAME+1];
    int age;
    double income;
};

// Definitions
struct person mike, pete;


// Assignment/field references
mike = pete;
pete.age = chris.age + 3;


// Using structs
struct person give_raise(struct person p, double pct) {
    p.income *= ( + pct/100);
    return p; // must return struct person
}


mike = give_raise(mike, 10.0); 

//  typedef
typedef double price_t; // alias for double to dclare price variables
typedef double weight_t; // alias for double to declare weight variables

price_t p; // double precision value that's a price
weight_t lbs; // double precision value that's a weight

// typedef in practice
# define MAXSTR (100)
typedef char long_string_t[MAXSTR+1];
long_string_t line;
long_string_t buffer;

// shorter name 
typedef struct {
    long_string_t label;
    double x;
    double y;
} point_t;

point_t origin;
point_t focus;