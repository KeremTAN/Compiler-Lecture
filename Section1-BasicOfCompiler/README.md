* [Section 1 - Basic Of Compiler](#sect1)
    * [Calc Language Application](#calc)

<a name="sect1"></a>

##  <b> Section 1 - Basics Of Compiler </b>
&nbsp; In this section a very simple application is developed to understand the basic steps of a compiler. </br>

<a name="calc"></a>

### <b> Calc Language Application</b>
&nbsp; An example for syntax of the language developed with this application is given below.
```
with a, b: a * (4 + b)
```
The program that has been written performs the arithmetic in the expression with the variables defined with the with keyword.


<b>Extended Backus-Naur Form (EBNF)</b> </br>
&nbsp; Grammar rules of the language to be written will be defined here.
```
calc    : ("with" ident ("," ident)* ":")? expr ;
expr    : term (("+" | "-") term)* ;
term    : factor (("*" | "/") factor)* ;
factor  : ident | number | "(" expr ")" ;
ident   : ([a-zA-Z])+ ;
number  : ([0-9])+ ;
```
<b>(...)</b> means that it is <b>a group</b>.</br>
<b>?</b> means that it is <b>optional</b>.</br>
<b>*</b> means that <b>zero or more repetitions</b>.</br>
<b>+</b> means that <b>one or more repetitions</b>.</br>
<b>|</b> means that it is <b>an alternative</b>.</br>
<b>[...]</b> means that it is <b>a charachter class</b>.</br>

