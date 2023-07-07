
#  <b> Compiler Lecture  </b>
* [Aim of This Repository](#aim)
* [Summary Information About Compilers](#siac)
    * [Front-End](#front)
    * [Optimizer](#optimizer)
    * [Back-End](#back)
* [Section 1 - Basic Of Compiler](#sect1)
    * [Calc Language Application](#calc)

<a name="aim"></a>

## <b> Aim of This Repository </b>
&nbsp; The aim of this repository is to keep the applications in the books which I've been studying on about the field of compilers while I trying to improve myself. Since this repository is related to the compilers area, the applications here will be made with the LLVM library.</br>

<b>[WARNING]</b> Most of the information in this repository is a summary of what I have read and understood myself. The information here may not be completely accurate. For more detailed information on compilers, please study the <b>Aho's Dragon book and Kai Nacke's LLVM book</b>.

<a name="siac"></a>

##  <b> Summary Information About Compilers </b>
&nbsp; Before explaining the steps of a compiler, it is better to first explain what a compiler is and what it does. </br>

&nbsp; <b><i>A Compiler</i></b> is <b>a program</b> that converts the code in the source file (files such as .java, .cpp, .py, etc.) into machine code that the computer can understand.

&nbsp; A compiler consists of 3 steps. </br>
These steps are Front-End, Optimizer and Back-End and these steps consist of sub-steps within themselves.
* [Front-End](#front)
    * [Scanning Analyzer / Lexer](#lexer)
    * [Syntactic Analyzer / Parser](#parser)
    * [Semantic Analyzer](#semantic)
* [Optimizer](#optimizer)
* [Back-End](#back)
    * [Instruction Selection](#insSel)
    * [Instruction Scheduling](#insSch)
    * [Register Allocation](#regAlloc)

<a name="front"></a>

### <b> Front-End </b>
&nbsp; You can think of the code in the source file(source files such as .c, .java, .js, etc.) as an ordinary text in a text document (like .txt file) at this stage. </br>

<a name="lexer"></a>

#### <b> Scanning Analyzer (Lexer) </b>
&nbsp; <b><i>The Lexer</i></b> reads one by one characters in the source file until it detects the characters like  '+' ,'=', ';' etc. expression and creates a special object called Token with the characters it reads. </br>

An example of code and its split into Token objects are in below.
```python
# Token Code Example;
x1 = a3 + 5;
x'2;
```
```
# Tokens of the code example;

x1  is a  Token (identifier)
=   is a  Token (assignment operator)
a3  is a  Token (identifier)
+   is a  Token (+)
5   is a  Token (number)
;   is a  Token (end of statement)

x'2 is an Invalid Token
;   is a  Token (end of statement)
```
&nbsp; <b>Note: </b> <i>a3 + 5</i> also called an <b>EXPRESSION</b>

<a name="parser"></a>

#### <b> Syntactic Analyzer (Parser) </b>

&nbsp; <b><i>The Parser</i></b> makes statements with tokens just like people make sentences with words. Tokens obtained in the previous section (Lexer sect.) are used to establish the statements. The statements are then converted into <b>a special data structure called the Abstract Syntax Tree (A.S.T.)</b>.

&nbsp; <b>The aim of Parser</b> is to understand whether the grammar created is correct or not and to debug in A.S.T..

&nbsp; <b>Grammar</b> is the rules given to programmer for compiler have a valid statement. 

The code that each token is used correctly but <b>the grammar is wrong</b> in below.
```python
# Invalid Grammar Example;
num = a*b +/;
```

Grammatically correct code is in below.
```python
# Valid Grammar Example;
num = a*b + y/z;
```
Grammatically correct code is shown as an A.S.T. graph in below.
```mermaid
  graph TD;
      linkStyle default interpolate basis;
      assign --> num;
      assign --> +;
      + --> *;
      + --> /;
      * --> a;
      * --> b;
      / --> y;
      / --> z;
```
<a name="semantic"></a>

#### <b> Semantic Analyzer </b>
&nbsp; <b><i>The Semantic Analyzer</i></b> checks whether the written code is meaningful even if the code written in the source file is grammatically correct. </br>

There are examples where a sentence or code may be meaningless even if it is grammatically correct in the below.
```
Sentence example; 
His home is going to he.

Explanation: This sentence is grammatically correct but meaningless.

-----------------
Code example;
5 = x;

Explanation: A value of 5 is an real value and x is a local value(represents the memory address).
A real value can be assigned to a local variable, but the opposite is meaningless.
```
&nbsp; <b>Compilers</b> only must generate meaningful code.

Now that it's understood that a code can be meaningless even if it is grammatically correct, let's take a real-life example.
```cpp
Animal a1, a2;
Person p;
Computer c;
int x;
x = p - c;
```
&nbsp; When we write code in a source file in real life, <b>Symbol Table</b> is called for each of our declarations and each variables of the declarations. </br>

&nbsp; As it can be understood, declared variables in our source code in  <b>Symbol Table</b>, their scope fields etc. information is available. </br>

&nbsp; The Compiler can understand that the above example contains meaningless codes by checking the Symbol Table in the Semantic Analyzer during compilation.

<a name="optimizer"></a>

### <b> Optimizer </b>
&nbsp; <b><i>The Optimizer</i></b> tries to optimize the A.S.T. data structure obtained at the end of the front-end stage of the compiler <b>independently of the target machine</b>(architectures such as x86, arm, gpu, etc.).

&nbsp; <b>Our aim is to hope to make the code faster in optimization.</b>

&nbsp; There are different methods and approaches for these optimization processes. The most common of these is the Command Subexpression Elimination(CSE). To summarize the CSE approach roughly and to give a simple example, if there are more than one repetitive operations, those operations are assigned to a variable. When those operations are needed, they are used from the variables they are assigned.

&nbsp; Optimizer and Compiler solutions are a kind of <b>heuristic algorithms.</b>
<a name="back"></a>

### <b> Back-End </b>
&nbsp; Unlike the optimizer stage the compiler tries to optimize our code according to the specifications of our target machine(x86, arm, etc. architecture) at this stage.

&nbsp; The compiler converts the AST data structure obtained from the The Optimizer part to the Abstract Assembly model in order to optimize our code in the Back-End part.

&nbsp; Abstract Syntax Tree = High-Level Intermediate Representation </br>
&nbsp; Abstract Assembly = Low-Level Intermediate Representation </br>

An example for "<i><b> num = a*b + y/z </b></i>" created as an abstract assembly model in below.
```
# Abstract Assembly Model;

load a -> r1 
load b -> r2 
mult r1, r2 -> r3
load y -> r4 
load z -> r5 
div r4, r5 -> r6
add r3, r6 -> r7
store r7 -> num
```
<a name="insSel"></a>

#### <b> Instruction Selection </b>
&nbsp; There are different processors that can perform different operations in different ways at nowadays.

&nbsp; While some processors take the value from memory one by one and load them into registers one by one (like the abstract assembly model in above), some other processors can directly access and process the data in memory with operations such as memory operands.

For example; compiler can select
<b><i> mult[a], [b] -> r1</i></b> instead of </br>
<b><i> load a -> r1 </i></b> </br>
<b><i> load b -> r2 </i></b> </br>
 <b><i>mult r1, r2 -> r3 </i></b>

&nbsp; Compiler tries to choose the most performing option from the available options for our target machine <b>in Instruction Selection</b>.

<a name="insSch"></a>

#### <b> Instruction Scheduling </b>

&nbsp; Compiler reorganizes the instructions so that our program can run most efficiently, taking into account the processing times of the instructions, the number of registers of the target machine, etc. <b>in Instruction Scheduling</b>.

&nbsp; As an example, we can think that the abstract assembly model in the instruction selection part is reorganized as follows to work more efficiently.
```
# Reorganized Abstract Assembly Model;

load a -> r1 
load b -> r2 
load y -> r4 
load z -> r5 
mult r1, r2 -> r3
div r4, r5 -> r6
add r3, r6 -> r7
store r7 -> num
```

<a name="regAlloc"></a>

#### <b> Register Allocation </b>

&nbsp; Compiler acts as if it has an infinite number of registers until the register allocation stage and creates the abstract assembly model with these virtual registers. The r1, r2, etc. shown in the examples above they are all virtual registers and the registers resulting from the operation with two virtual registers are temporary virtual registers.</br>
For example; <i>mult r1, r2 -> r3</i> </br>
r3 is temporary virtual register in here.

&nbsp; Compiler takes the virtual registers in the abstract assembly model and maps them with the real registers in the target machine <b>in register allocation part.</b>

&nbsp; As you can imagine, the number of registers of a target machine is not infinite. Compiler map the virtual registers with the highest priority for the mapping to the real registers, and the virtual registers that cannot be mapped to the real registers are stored in memory again in this stage.

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
ident   : ([a-zAZ])+ ;
number  : ([0-9])+ ;
```


