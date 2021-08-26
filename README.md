# graph1
code that goes with the paper: [how language could have evolved](https://github.com/kwd2/graph1/blob/main/how_language_could_have_evolved.pdf)

ealier version of this documentation: [google docs bica code](https://docs.google.com/document/d/1CxnVuSqjkilYbdJG4flKVL_NAbCwRZlVtv1cmskbbVY/edit?usp=sharing)

Table of Contents
-----------------------------------

* short term memory, (stm)  - - - - - - - create new (stm) nodes via merge()
* (stm) sequence recall	- - - - - - - - - hiker rock duck sneeze
* movement - - - - - - - - - - - - - - - - branching on value during (stm) sequence recall, boys eat what?;  what boys eat?
* a-n bifurcation- - - - - - - - - - - - - now I eat here daily
* compare function at merge time - - - - - HERE here 
* conjunction - - - - - - - - - - - - - - - closed loop hebbian binding:  wallace and gromit
* illicit grammar  - - - - - - - - - - - - - - - return false when building (stm):  wallace and *now
* movement+conjunction - - - - - - - - - - - - - -  wallace and gromit I like?

* long term memory  [ltm] - - - - - - - - - merge(h,c) -> merge(c,h)

* verbs    - - - - - - - - - - - - - -                               -  +1 (stm) loop caused by [vp] node
* prepositions - - - - - - - - - - - - - -                           -  +2 (stm) loops caused by [p] node

* past   tense  [vp] = -1  - - - - - - - - - - - - - -                      - value based branching on -1
* future tense  [vp] = +1 - - - - - - - - - - - - - -                     - value based branching on +1

* progressive   [nvp] = -1   - - - - - - - - - - - - - -                   - double (stm) loop,
* perfected       [nvp] = +1    - - - - - - - - - - - - - -                 - double (stm) loop

* singular        [noun] = -1   - - - - - - - - - - - - - -	     - number agreement
* plural            [noun] = +1  - - - - - - - - - - - - - -                 - plural “s” word ending


* executive function - - - - - - - - - - - - -  the [a-nvp] sequence:  input, respond, ponder, [respond]

* adjective ordering - - - - - - - - - - - - the big shiny thing,  the shiny  *big thing

* decisions

* sleep - - - - - - - - - - - - - - - - - - - - - - use daily (stm) nodes to form [ltm] sequence memories 

* [ltm] recall - - - - - - - - - - - - - - - - - - - recall [ltm] sequences based on current input

* executive function - - - - - - - - - - - - - - - -  input-predict-[respond], ponder-[respond], sleep




----------------------------------------------------------------------------------
the c++ file graph1.cpp contains a single class that implements the graph node.   The main() routine has the form:
![Screenshot from 2021-05-10 20-25-35](https://user-images.githubusercontent.com/15908030/117744407-3aa1e580-b1ce-11eb-956e-11e00a24038e.png)

The Graph class is modified (evolved) as the sequence of main1(), main2() ,main3(), ...  routines above are added 


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

![Screenshot from 2021-05-15 18-26-10](https://user-images.githubusercontent.com/15908030/118380886-187fdd00-b5ab-11eb-9853-8298bdd0697a.png)


input "I am here and now"

![Screenshot from 2021-05-28 13-15-45](https://user-images.githubusercontent.com/15908030/120029584-ea8f9500-bfbb-11eb-9d89-155772a7010e.png)

![Screenshot from 2021-05-28 13-16-05](https://user-images.githubusercontent.com/15908030/120029614-f1b6a300-bfbb-11eb-9a6f-cbdcb65475f5.png)

![Screenshot from 2021-05-28 13-16-25](https://user-images.githubusercontent.com/15908030/120029622-f5e2c080-bfbb-11eb-98b6-246e3ff52e3e.png)

![Screenshot from 2021-05-28 13-16-45](https://user-images.githubusercontent.com/15908030/120029633-fa0ede00-bfbb-11eb-8582-2a62e175e845.png)

![Screenshot from 2021-05-28 13-17-20](https://user-images.githubusercontent.com/15908030/120029646-fe3afb80-bfbb-11eb-92b5-92bd490fe3f8.png)

---------------------------------------------------------------------------------

+ illicit conjuntion combinations
+ illicit grammar  - - - - - - - - - - - - - - - return false when building (stm)

executive function in main() breaks input if a FALSE is returned during input

![Screenshot from 2021-07-22 10-35-21](https://user-images.githubusercontent.com/15908030/126666897-94211942-229b-48aa-9961-a4fdaaed0cf5.png)

"space"
![Screenshot from 2021-08-18 09-47-49](https://user-images.githubusercontent.com/15908030/129920338-f85d5770-2c6e-43ea-9201-343ebdf0e8b8.png)

"space and"
![Screenshot from 2021-08-18 09-48-15](https://user-images.githubusercontent.com/15908030/129920336-7df44ab1-3e34-4718-ac30-04df19cc7078.png)

"space and time"
![Screenshot from 2021-08-18 09-48-34](https://user-images.githubusercontent.com/15908030/129920335-80d760e7-e5e2-47eb-ae84-9e7c2ad53291.png)

recall:
![Screenshot from 2021-08-18 09-48-52](https://user-images.githubusercontent.com/15908030/129920334-49cfca27-af32-4037-8918-fe516a8a7b62.png)

"space and *thing"   - FALSE is returned and stored in (stm)
![Screenshot from 2021-08-18 09-49-11](https://user-images.githubusercontent.com/15908030/129920332-ae9b133d-c794-440c-b425-387c01482901.png)

subsequent recall,  the stored FALSE values can prevent [ltm] memories from forming from the (stm) structure. 
![Screenshot from 2021-08-18 09-49-29](https://user-images.githubusercontent.com/15908030/129920330-6ddf2f67-978e-4f15-a4a5-bf2eb431c147.png)


----------------------------------------------------------------------------------
* movement of a conjunction

![Screenshot from 2021-05-12 09-39-30](https://user-images.githubusercontent.com/15908030/117994206-fca7dd00-b305-11eb-8f50-44108289bcee.png)

input "thing space and time", ->  thing here and now -> the event is here and now -> 

the event is where and when?  ->

Where and when is the event?

![Screenshot from 2021-08-23 08-55-19](https://user-images.githubusercontent.com/15908030/130460914-0232c921-4cf9-45ec-b86c-5dc5f51ccb2c.png)

graph and output: "thing space and time"

![Screenshot from 2021-08-23 09-04-12](https://user-images.githubusercontent.com/15908030/130461142-8311985d-d667-4c57-9e92-6e61bd5f7588.png)


input "thing where and when?"

![Screenshot from 2021-08-23 14-21-50](https://user-images.githubusercontent.com/15908030/130506350-602e60a3-29d9-4cc4-a8ec-b5c6d5c4f6a9.png)

output: "where and when thing?"

![Screenshot from 2021-08-23 14-25-23](https://user-images.githubusercontent.com/15908030/130507321-98c15873-43d5-43cf-b206-fbbe27141343.png)



----------------------------------------------------------------------------------
* long term memory  [ltm]                 - reverse merge

![Screenshot from 2021-05-12 09-40-25](https://user-images.githubusercontent.com/15908030/117994374-1b0dd880-b306-11eb-9d11-a95151aafe8c.png)

![Screenshot from 2021-08-25 19-26-31](https://user-images.githubusercontent.com/15908030/130881243-d452f1f9-6854-42b6-8b53-b3bd5eb19e54.png)





----------------------------------------------------------------------------------
* verbs                                   -  +1 (stm) loop
* prepositions                            -  +2 (stm) loops

![Screenshot from 2021-06-01 08-08-23](https://user-images.githubusercontent.com/15908030/120328622-9d0f7280-c2b0-11eb-9192-db1d648b449b.png)


![Screenshot from 2021-06-01 11-22-06](https://user-images.githubusercontent.com/15908030/120358035-b1149d80-c2cb-11eb-9b71-ebce993b40e4.png)


----------------------------------------------------------------------------------

* past   tense  [vp] = -1                        - value based branching on -1
* irregular past tense verbs                     - frame node [ltm] value based branching   

![Screenshot from 2021-06-01 17-58-50](https://user-images.githubusercontent.com/15908030/120400254-22237780-c303-11eb-91a8-db4d3509eeef.png)

* future tense  [vp] = +1                       - value based branching on +1

----------------------------------------------------------------------------------

* progressive   [nvp]-1                      - double (stm) loop,
* perfected       [nvp]+1                     - double (stm) loop

![Screenshot from 2021-06-06 11-26-06](https://user-images.githubusercontent.com/15908030/120932102-1bf21a00-c6ba-11eb-9424-616bdd14b3d1.png)


----------------------------------------------------------------------------------

* singular        [noun]-1   	     - number agreement
* plural            [noun]+1                   - plural “s” word ending

![Screenshot from 2021-06-06 11-27-27](https://user-images.githubusercontent.com/15908030/120932144-49d75e80-c6ba-11eb-9cc0-0c13850e16aa.png)



----------------------------------------------------------------------------------

* stm overlay  mechanism              - return false when building (stm)

----------------------------------------------------------------------------------
* executive function - - - - - - - - - - - - -  the [a-nvp] sequence:  input, respond, ponder, [respond]

bind (stm), if not fully bound at input time
![Screenshot from 2021-07-22 09-35-01](https://user-images.githubusercontent.com/15908030/126657267-58827113-7854-4062-bbe4-f5717b37e62f.png)

generate internal prediction/response:  "I like"

![Screenshot from 2021-07-23 16-00-25](https://user-images.githubusercontent.com/15908030/126841087-9645def2-c31e-4dc2-a972-731627de2e8d.png)

externalize response

![Screenshot from 2021-07-27 08-08-19](https://user-images.githubusercontent.com/15908030/127158830-d818bb9a-53de-4851-a428-8509fc1bfd89.png)

ponder

![Screenshot from 2021-07-27 15-55-58](https://user-images.githubusercontent.com/15908030/127226209-b32d801b-7b7d-424f-a07e-1b3fb849cf7c.png)


----------------------------------------------------------------------------------



* adjective ordering - - - - - - - - - - - - the big shiny thing,  the shiny  *big thing

![Screenshot from 2021-08-09 09-59-58](https://user-images.githubusercontent.com/15908030/128727958-4daf0bb8-0878-4250-8284-09dfbb7b5ea6.png)


----------------------------------------------------------------------------------
* decisions - - - - - - - - - - - - - - - -  branching in (stm)

----------------------------------------------------------------------------------
* sleep - - - - - - - - - - - - - - - - - - create [ltm] sequences from stored (stm) sequences, clear (stm)

![Screenshot from 2021-07-30 06-51-21](https://user-images.githubusercontent.com/15908030/127649086-3e3641e8-85a4-41ff-8250-665331de0413.png)












