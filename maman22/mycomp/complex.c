#include <stdio.h>
#include <math.h> /* Required for sqrt() in abs_comp */
#include "complex.h"

/* read_comp: Sets the real and imaginary parts of a complex variable */
void read_comp(complex *var, double val_real, double val_imag) {
    var->real = val_real;
    var->imag = val_imag;
}

/* print_comp: Prints the complex number in the exact format required: 5.10+(6.23)i */
void print_comp(complex var) {
    /* Requires at least 2 digits of precision */
    printf("%.2f+(%.2f)i\n", var.real, var.imag);
}

/* add_comp: Adds two complex numbers */
complex add_comp(complex c1, complex c2) {
    complex result;
    result.real = c1.real + c2.real;
    result.imag = c1.imag + c2.imag;
    return result;
}

/* sub_comp: Subtracts c2 from c1 */
complex sub_comp(complex c1, complex c2) {
    complex result;
    result.real = c1.real - c2.real;
    result.imag = c1.imag - c2.imag;
    return result;
}

/* mult_comp_real: Multiplies a complex number by a real number */
complex mult_comp_real(complex c, double mult_real) {
    complex result;
    result.real = c.real * mult_real;
    result.imag = c.imag * mult_real;
    return result;
}

/* mult_comp_img: Multiplies a complex number by an imaginary number */
complex mult_comp_img(complex c, double mult_imag) {
    complex result;
    /* Formula: mi * (a + bi) = -mb + (ma)i */
    result.real = -(c.imag * mult_imag);
    result.imag = c.real * mult_imag;
    return result;
}

/* mult_comp_comp: Multiplies two complex numbers */
complex mult_comp_comp(complex c1, complex c2) {
    complex result;
    /* Formula: (a+bi)*(c+di) = (ac-bd) + (ad+bc)i */
    result.real = (c1.real * c2.real) - (c1.imag * c2.imag);
    result.imag = (c1.real * c2.imag) + (c1.imag * c2.real);
    return result;
}

/* abs_comp: Calculates the absolute value of a complex number */
double abs_comp(complex c) {
    /* Formula: sqrt(a^2 + b^2) */
    return sqrt((c.real * c.real) + (c.imag * c.imag));
}