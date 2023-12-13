# Compiler-Design
This Project was the final project for my Compiler Design Class, and contains code that would check to make sure any inserted string follows the given requirements
For the Code.
The first section of the code, the functions in particular.
Functions "removeSpaces", "removeComments", "KillSpaces", and "FixFiles" are all used to make the file into a format the program can read
removeSpaces removes extra spaces that are in the front of the string
removeComments removes any comments that are found in the file, comments were defined as strings placed between "(*" and "*)"
KillSpaces removes extra spaces that were created by the removal of the comments
Fix Files uses all the previous functions in conjunction to organize the file

6 reserved words remain constant in the entier program, namely "program", "var", "begin", "end.", "integer", "write".

The rest of the functions work together to check the string and to ensure that the program given by the file works properly.

For the work.
The first Section contains the original program in a file, named "File.txt"
Original Program, in “finalv1.txt”
           program  f2023;
            (* This program computes and prints the value
                  of an expression *)
           var
               (* declare variables *)
               a1 ,       b2a ,       c, ba    : integer ;
         begin
                  a1               = 3 ;
                  b2a =          4 ;
                  c           =  5    ;
            write ( c );  (* display c *)

                 (* compute the value of the expression *)
                 ba = a1 * ( b2a + 2 * c)          ;
                 write ( “value=”,          ba   ) ;  (* print the value of ba*)
           end.

We were also given the original Grammer
<prog>            	-->  program   <identifier>; var  <dec-list>  begin  <stat-list> end.
<identifier>     	--> <letter>{<letter>|<digit>}         note. This grammar is in EBNF
<dec-list>        -->  <dec> : <type> ;
<dec>             --> <identifier>,<dec>| < identifier >
<type>            --> integer 
<stat-list>       --> <stat> | <stat> <stat-list>
<stat>            --> <write> |  <assign>
<write>           --> write ( <str> < identifier > );
<str>             --> ”value=”, | λ 
<assign>          --> < identifier > = <expr>;
<expr>            --> <expr> + <term> | <expr> - <term> | <term>
<term>           	--> <term> * <factor> | <term> / <factor>| <factor>
<factor>          --> < identifier > | <number> | ( <expr> )
<number>         	--> <sign><digit>{ <digit> }        note: the grammar is in EBNF
<sign>            --> + | - | λ
<digit>           --> 0|1|2|…|9
<letter>          --> a|b|c|d|w|f

Using this grammer, we removed the EBNF's to get this:
<prog>            -->  program   <identifier>; var  <dec-list>  begin  <stat-list> end.
<identifier>     	--> <letter><identifier-redo>
<identifier-redo>	--> <letter><identifier-redo>
<identifier-redo>	--> <digit><identifier-redo>
<identifier-redo>	--> λ
<dec-list>        --> <dec> : <type> ;
<dec>             --> <identifier>,<dec>
<dec>             --> <identifier>
<type>            --> integer 
<stat-list>       --> <stat>
<stat-list>       --> <stat><stat-list>
<stat>            --> <write>
<stat>	          --> <assign>
<write>           --> write ( <str> < identifier > );
<str>             --> ”value=”, 
<str>             --> λ
<assign>          --> < identifier > = <expr>;
<expr>            --> <expr> + <term>
<expr>            --> <expr> - <term>
<expr>            --> <term>
<term>            --> <term> * <factor>
<term>	          --> <term> / <factor>
<term>	          --> <factor>
<factor>          --> <identifier >
<factor>          --> <number>
<factor>          --> (<expr>)
<number>         	--> <sign><digit><number-redo>
<number-redo>	    --> <digit><number-redo> 
<number-redo>	    --> λ
<sign>            --> +
<sign>            --> -
<sign>	          --> λ
<digit>           --> 0
<digit>	          --> 1
<digit>           --> 2
<digit>           --> 3
<digit>	          --> 4
<digit>	          --> 5
<digit>           --> 6
<digit>	          --> 7
<digit>	          --> 8
<digit>	          --> 9
<letter>          --> a
<letter>          --> b
<letter>          --> c
<letter>          --> d
<letter>          --> w
<letter>          --> f

We then removed all left-hand recursions to create: 
<prog>            -->  program   <identifier>; var  <dec-list>  begin  <stat-list> end.
<identifier>     	--> <letter><identifier-redo>
<identifier-redo>	--> <letter><identifier-redo>
<identifier-redo>	--> <digit><identifier-redo>
<identifier-redo>	--> λ
<dec-list>        --> <dec> : <type> ;
<dec>             --> <identifier>,<dec>
<dec>             --> <identifier>
<type>            --> integer 
<stat-list>       --> <stat>
<stat-list>       --> <stat><stat-list>
<stat>            --> <write>
<stat>	          --> <assign>
<write>           --> write ( <str> < identifier > );
<str>             --> ”value=”, 
<str>             --> λ
<assign>          --> < identifier > = <expr>;
<expr>            --> <term><expr-repeater>
<expr-repeater>   --> λ
<expr-repeater>   --> + <term><expr-repeater>
<expr-repeater>   --> - <term><expr-repeater>
<term>            --> <factor><term-repeater>
<term-repeater>   --> * <factor><term-repeater>
<term-repeater>	  --> / <factor><term-repeater>
<term-repeater>	  --> λ
<factor>          --> <identifier>
<factor>          --> <number>
<factor>          --> (<expr>)
<number>         	--> <sign><digit><number-redo>
<number-redo>	    --> <digit><number-redo> 
<number-redo>	    --> λ
<sign>            --> +
<sign>            --> -
<sign>	          --> λ
<digit>           --> 0
<digit>	          --> 1
<digit>           --> 2
<digit>           --> 3
<digit>	          --> 4
<digit>	          --> 5
<digit>           --> 6
<digit>	          --> 7
<digit>	          --> 8
<digit>	          --> 9
<letter>          --> a
<letter>          --> b
<letter>          --> c
<letter>          --> d
<letter>          --> w
<letter>          --> f

We then created the First and Follow, which gave us:
State	    First	                                                  Follow
P	      program	                                                    $  
I	     a,b,c,d,w,f	                                      ;, , , : , ), =, /, *, +, - 
M	  a,b,c,d,w,f,0,1,2,3,4,5,6,7,8,9,λ	                    ;, , , : , ), =, /, *, +, -
D	     a.b.c.d.w.f	                                              Begin
E	     a,b,c,d,w,f	                                                 :
J	       , , λ	                                                     :
T	      integer	                                                     ;
S	    a,b,c,d,w,f, write	                                          end.
K	    a,b,c,d,w,f,write, λ	                                        end.
R	    a,b,c,d,w,f, write	                                a,b,c,d,w,f,write, end.
Q	        “value=”,λ                                           	a,b,c,d,w,f
W	        write	                                           a,b,c,d,w,f,write,end.
A	      a,b,c,d,w,f	                                        a,b,c,d,w,f,write,end.
F	  (,+,-,0,1,2,3,4,5,6,7,8,9,a,b,c,d,w,f                            	), ;
O	          +,-,λ                                                    	), ;
U	   (,+,-,0,1,2,3,4,5,6,7,8,9,a,b,c,d,w,f                       	+, -, ), ;
H	          /,*,λ	                                                   +,-,),;
G	   (,+,-,0,1,2,3,4,5,6,7,8,9,a,b,c,d,w,f	                    /, *, +, -, ), ;
N	    +,-,0,1,2,3,4,5,6,7,8,9	                                  /, *, +, -, ), ;
Z    	  0,1,2,3,4,5,6,7,8,9,λ	                                     /,*,+,-,),;
V	         +,-, λ	                                              0,1,2,3,4,5,6,7,8,9
B	   0,1,2,3,4,5,6,7,8,9	                                      0,1,2,3,4,5,6,7,8,9
C	      f,w,d,c,b,a	                          a,b,c,d,w,f,0,1,2,3,4,5,6,7,8,9, ;, , , : , ), =, /, *, +, -


Using all this information a Parsing Table was created:
	program	                                var	                begin	                end.	                :	            ,	            integer	      write	      =      	+      	-	    *	      /	    (	    )
P	program I; var D begin S end.														
I															
M					                                                                                                λ            	λ			                                   λ	    λ      	λ	    λ	      λ		        λ
D															
E															
J					                                                                                                λ            	,E									
T							                                                                                                                         integer								
S								                                                                                                                                       RK							
K				                                                                              λ                                                          	 	   	S							
R								                                                                                                                                        W							
Q															
W								                                                                                                                                    write(QI)							
A															
F										                                                                                                                                                    UO	    UO			            UO	
O										                                                                                                                                                    +UO	    -UO				                  λ
U										                                                                                                                                                    GH	    GH	            		GH	
H										                                                                                                                                                    λ	        λ	    *GH	  /GH		        λ
G										                                                                                                                                                    N        	N			            (F)	
N										                                                                                                                                                    VBZ	     VBZ				
Z										                                                                                                                                                     λ	      λ    	λ	      λ		  λ
V										                                                                                                                                                      +      	-				
B															
C															

	    0	    1	    2	    3	    4    	5    	6    	7    	8    	9    	a    	b    	c    	d    	w    	f
P																
I											                                            CM	 CM	    CM	  CM	  CM	 CM
M	    BM	 BM	    BM	  BM	  BM	  BM	  BM	  BM	  BM	  BM	  CM	 CM 	  CM	  CM	  CM	 CM
D											                                            E:T; E:T;	  E:T;	E:T;	E:T; E:T;
E											                                            IJ	 IJ	     IJ	   IJ	   IJ	  IJ
J																
T																
S											                                            RK	 RK	     RK	   RK	   RK	  RK
K											                                            S	   S	     S   	 S	   S	  S
R											                                            A	   A	     A	   A	   A	  A
Q											                                            λ	   λ	     λ	   λ	   λ	  λ
W																
A											                                           I=F;	I=F;	  I=F;	I=F;	I=F;	I=F;
F 	UO	 UO	     UO	   UO	   UO	    UO	 UO	   UO	    UO	  UO	  UO	UO	     UO	   UO	   UO	   UO
O																
U	  GH	 GH	     GH	   GH	   GH	    GH	 GH	   GH	    GH	  GH	  GH	GH	     GH	   GH	   GH	   GH
H																
G	   N	  N   	 N	    N	   N	     N	  N	   N	    N	    N  	   I	 I	      I	    I	    I	    I
N	  VBZ	 VBZ	  VBZ	   VBZ	VBZ	    VBZ	 VBZ	VBZ	   VBZ	 VBZ						
Z	   BZ	  BZ	   BZ	    BZ	 BZ	     BZ	  BZ	 BZ	    BZ	  BZ						
V	   λ	  λ	     λ	    λ	   λ	     λ	  λ	   λ	    λ    	λ						
B	   0	  1	     2	    3	   4	     5	  6	   7	    8	    9						
C											                                             a	 b	     c	   d	    w	    f

	  “value=”	  ;
P		
I		
M		            λ
D		
E		
J		
T		
S		
K		             λ
R		
Q	  “value=”	
W		
A		
F		
O		              λ
U		
H		              λ
G		
N		
Z		              λ
V		
B		
C		
