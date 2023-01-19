# Calculator

Good team means good product.

## Intro

A Calculator based on Arduino UNO, which can receive numbers and signs ('+', '-', '*', '/', '^') via IRremote module, and show you the results;

Basic functions like 'sin(c)', 'cos(c)', 'ln(c)' are being supported.

All of the following are based on dynamic memory allocation.

## Calc-Tree

The tree realized in the 'tree.c' can receive a string like "( 1 - s ( -1 - 2.1415926 ) / 2 )", and then produce a value that is equal to the formula.

## String

It realized a part of features of the *string* class in C++.