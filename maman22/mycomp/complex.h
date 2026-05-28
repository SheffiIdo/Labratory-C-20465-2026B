#ifndef COMPLEX_H
#define COMPLEX_H

/* Definition of a complex number.
 * Holds a real part (a) and an imaginary part (b).
 */
typedef struct {
    double real;
    double imag;
} complex;

/*
 * Function Prototypes for complex number operations.
 */
void read_comp(complex *var, double val_real, double val_imag);
void print_comp(complex var);

complex add_comp(complex c1, complex c2);
complex sub_comp(complex c1, complex c2);
complex mult_comp_real(complex c, double mult_real);
complex mult_comp_img(complex c, double mult_imag);
complex mult_comp_comp(complex c1, complex c2);

double abs_comp(complex c);

#endif