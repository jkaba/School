/* CS2211A Assignment 5
   Name: Jameel Kaba
   GAUL ID: jkaba
   Student #: 250796017

   header file that contains the function prototypes 
   and the structure definitions */

/* complex_tag structure that consists of two
   double values(a real part and an imaginary part) */

struct complex_tag{
  double real;
  double imaginary;
};

/* Complex_type structure that consists of two double 
   values (a real part and an imaginary part) */

typedef struct{
  double real;
  double imaginary;
}Complex_type;

/* function prototypes */
Complex_type multiplication(struct complex_tag c1, struct complex_tag c2);
int divide(struct complex_tag *c1, struct complex_tag *c2, struct complex_tag *c3);
int add_subtract(struct complex_tag c1, struct complex_tag c2, struct complex_tag **c3, struct complex_tag **c4);
