# graph1
code that goes with the paper: [how language could have evolved](https://github.com/kwd2/graph1/blob/main/how_language_could_have_evolved.pdf)

ealier version of this documentation: [google docs bica code](https://docs.google.com/document/d/1CxnVuSqjkilYbdJG4flKVL_NAbCwRZlVtv1cmskbbVY/edit?usp=sharing)

Table of Contents
-----------------------------------

* short term memory, (stm)  - - - - - - - create new (stm) nodes via merge()
* (stm) sequence recall	- - - - - - - - - hiker rock duck sneeze
* movement - - - - - - - - - - - - - - - - value based branching during (stm) sequence recall
* a-n bifurcation- - - - - - - - - - - - - now I eat here daily
* conjunction - - - - - - - - - - - - - - - closed loop hebbian binding
* movement+conjunction

* long term memory  [ltm] - - - - - - - - - merge(h,c) -> merge(c,h)

* verbs    - - - - - - - - - - - - - -                               -  +1 (stm) loop
* prepositions - - - - - - - - - - - - - -                           -  +2 (stm) loops

* past   tense  [vp] = -1  - - - - - - - - - - - - - -                      - value based branching on -1
* future tense  [vp] = +1 - - - - - - - - - - - - - -                     - value based branching on +1

* progressive   [nvp] = -1   - - - - - - - - - - - - - -                   - double (stm) loop,
* perfected       [nvp] = +1    - - - - - - - - - - - - - -                 - double (stm) loop

* singular        [noun] = -1   - - - - - - - - - - - - - -	     - number agreement
* plural            [noun] = +1  - - - - - - - - - - - - - -                 - plural “s” word ending

* stm overlay  mechanism    - - - - - - - - - - - - - -          - return false when building (stm)
* triggering stored sequences
* analogies			     -  understand - recall and overlay entire [ltm] sequence 
				                        on (stm) without a FALS
* variables                                     - stm binding
* adjective ordering
* the / a / my / get 


----------------------------------------------------------------------------------
the c++ file graph1.cpp contains a single class that implements the graph node.   The main() routine has the form:
![Screenshot from 2021-05-10 20-25-35](https://user-images.githubusercontent.com/15908030/117744407-3aa1e580-b1ce-11eb-956e-11e00a24038e.png)

The Graph class is modified as the sequence of main1(), main2() ,main3(), ...  routines are added 


----------------------------------------------------------------------------------
 * short term memory, (stm): 



![Screenshot from 2021-05-10 15-30-04](https://user-images.githubusercontent.com/15908030/117720713-a0797780-b1a4-11eb-9512-258ef14f2925.png)


code output:   

(blocks of text with no arrows are static diagrams of the IP graph.   The blocks of text with arrows show the order of node firing when a graph node is externally fired (touched from main) )

![Screenshot from 2021-05-10 15-28-47](https://user-images.githubusercontent.com/15908030/117720644-88a1f380-b1a4-11eb-9ad8-994578e57d8c.png)


add the third and fourth symbols 'duck' and 'sneeze'

![Screenshot from 2021-05-10 15-44-48](https://user-images.githubusercontent.com/15908030/117722472-b851fb00-b1a6-11eb-9757-6d7ebe0cb31f.png)



![image](https://user-images.githubusercontent.com/15908030/117725528-df123080-b1aa-11eb-8d27-4e6d9a8fd99c.png)


----------------------------------------------------------------------------------
 * (stm) sequence recall

input 'boy eats thing'

![Screenshot from 2021-05-10 16-20-20](https://user-images.githubusercontent.com/15908030/117726138-c5251d80-b1ab-11eb-997e-dd1cd2c5f06d.png)

![Screenshot from 2021-05-10 16-20-39](https://user-images.githubusercontent.com/15908030/117726194-d8d08400-b1ab-11eb-92bd-c19d575e8e57.png)


----------------------------------------------------------------------------------
 * movement  

"Boys eat what?"  is input the same way with one change, the value of the thing node is set to 0 on input.  
 
 ![Screenshot from 2021-05-10 16-52-20](https://user-images.githubusercontent.com/15908030/117729204-23ec9600-b1b0-11eb-97c0-3c0fc266042a.png)

"thing:0" below is assumed to equal "what".

![Screenshot from 2021-05-10 16-47-14](https://user-images.githubusercontent.com/15908030/117728720-69f52a00-b1af-11eb-9ec1-2b2be93555a5.png)

The input value of 0 propagates to the (b_e_t) node.   This information can be used to cause movement by the simple modification that when a node fires, with direction =left, if the node has a stored value of 0, then the copy node is fired before the head node, instead of visa versa.

this produces the output "what boys eat", where "thing:0" below is defined to be "what"


![Screenshot from 2021-05-10 16-49-03](https://user-images.githubusercontent.com/15908030/117740665-881a5480-b1c6-11eb-8a8a-8170bc3936fc.png)


This mechanism is motivated from, and compares to,  the Minimalist model of movement from Linguistics  ![Screenshot from 2021-05-10 19-45-34](https://user-images.githubusercontent.com/15908030/117741536-599d7900-b1c8-11eb-97d0-62e139fd23ee.png)

----------------------------------------------------------------------------------
* a-n bifurcation- - - - - - - - - - - - - now I eat here daily


![Screenshot from 2021-05-11 17-24-17](https://user-images.githubusercontent.com/15908030/117892119-bf980800-b27d-11eb-8b38-9381a4bfe0a2.png)

further hypernym symbols are manually added in each branch of the graph

the value of the ip node (stm) nodes is used to indicate predicted future nodes below 

the value of the a and n  nodes is used to indicate the question form of each hypernym node,( who what when where why how ) = ( me thing time space feeling vp)  

![Screenshot from 2021-05-11 17-25-32](https://user-images.githubusercontent.com/15908030/117892218-e9512f00-b27d-11eb-803a-97392a53e85d.png)



I eat here:

![Screenshot from 2021-05-11 17-27-13](https://user-images.githubusercontent.com/15908030/117892333-2b7a7080-b27e-11eb-85b3-63b495ffa12c.png)





----------------------------------------------------------------------------------
* conjunction                             - closed loop hebbian binding


+ illicit conjuntion combinations

![Screenshot from 2021-05-15 18-26-10](https://user-images.githubusercontent.com/15908030/118380886-187fdd00-b5ab-11eb-9853-8298bdd0697a.png)


space and time

![Screenshot from 2021-05-18 20-02-32](https://user-images.githubusercontent.com/15908030/118741583-2ab08400-b814-11eb-89c8-2c8c0d772c8a.png)

![Screenshot from 2021-05-18 20-03-06](https://user-images.githubusercontent.com/15908030/118741598-3308bf00-b814-11eb-8ded-a51861b55fdd.png)

input "I am here and now"

![Screenshot from 2021-05-28 13-15-45](https://user-images.githubusercontent.com/15908030/120029584-ea8f9500-bfbb-11eb-9d89-155772a7010e.png)

![Screenshot from 2021-05-28 13-16-05](https://user-images.githubusercontent.com/15908030/120029614-f1b6a300-bfbb-11eb-9a6f-cbdcb65475f5.png)

![Screenshot from 2021-05-28 13-16-25](https://user-images.githubusercontent.com/15908030/120029622-f5e2c080-bfbb-11eb-98b6-246e3ff52e3e.png)

![Screenshot from 2021-05-28 13-16-45](https://user-images.githubusercontent.com/15908030/120029633-fa0ede00-bfbb-11eb-8582-2a62e175e845.png)

![Screenshot from 2021-05-28 13-17-20](https://user-images.githubusercontent.com/15908030/120029646-fe3afb80-bfbb-11eb-92b5-92bd490fe3f8.png)


----------------------------------------------------------------------------------
* movement of a conjunction

![Screenshot from 2021-05-12 09-39-30](https://user-images.githubusercontent.com/15908030/117994206-fca7dd00-b305-11eb-8f50-44108289bcee.png)



----------------------------------------------------------------------------------
* long term memory  [ltm]                 - reverse merge

![Screenshot from 2021-05-12 09-40-25](https://user-images.githubusercontent.com/15908030/117994374-1b0dd880-b306-11eb-9d11-a95151aafe8c.png)


----------------------------------------------------------------------------------
* verbs                                   -  +1 (stm) loop
* prepositions                            -  +2 (stm) loops

* past   tense  [vp]-1                        - value based branching on -1
* future tense  [vp]+1                       - value based branching on +1

* progressive   [nvp]-1                      - double (stm) loop,
* perfected       [nvp]+1                     - double (stm) loop

* singular        [noun]-1   	     - number agreement
* plural            [noun]+1                   - plural “s” word ending

* stm overlay  mechanism              - return false when building (stm)
* triggering stored sequences
* analogies			     -  understand - recall and overlay entire [ltm] sequence 
				                        on (stm) without a FALS
* variables                                     - stm binding
* adjective ordering
* the / a / my / get 













