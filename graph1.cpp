#include <iomanip>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <ctype.h>
#include <list>
#include <vector>
#include <map>
using namespace std;


class Node{
public:

  string   symbol;                        
  float    value;                               // [-1,0,1] = F,?,T    

  int      input_value;                         // current input level
  int      threshold;                           // threshold to fire

  int      time;                                // time last touched
 
  int      output_flag;                         // for output formatting
  
  list<Node*>                touches;            // child nodes that touched this node // depreciated
  list< pair<Node*,int> >    touches1;           // child nodes that touched this node
  Node*                      last_touch;
  
  Node*    last_stm;                             // last stm node this node is head of
  
        pair<Node*, int>     head;               // links <Node*, weight>
        pair<Node*, int>     copy;               //
  list< pair<Node*, int> >   branches;           //

  int  touch1(   int           input,
		 float         value,
		 Node*         touched_by,
	         list<Node*>*  node_string,
	         int           unused,
		 int           output_level,
		 int           tabs,
		 int           depth  );

  int    output            ( int depth , int tabs  );

  int    output_flag_clear ( int depth );
  
  int    clear_touches     ( int depth );

  int    clear_stm         ( int depth );
  int    clear_stm1         ( int depth, int mode, map<Node*,Node*>* stm_nodes );

  Node*  last_stm_tag_node ( int depth );
  
   
  void initialize(){
    value           =0;
    input_value     =40;
    threshold       =50;
    //time            =-10;
    last_stm        =NULL;
    //threshold_merge =1;     
    head=pair<Node*,int>(this,0);
    copy=pair<Node*,int>(this,0);
  };

    
  Node(){};                                           // base   constructor

  Node(string sym){                                   // string constructor for IP
    initialize();
    symbol=sym;
  };

  Node(string sym, Node* head1) {                     // string + Node* constructor for IP branches
    initialize();
    symbol=sym;   
    head=pair<Node*,int>(head1,55);
    copy=pair<Node*,int>(head1,10);

    head1->branches.push_back(pair<Node*,int>(this,1));
  }
                    


  Node(Node* n1,  Node* n2);                            // merge constructor 

  ~Node();                                              //       destructor
  
};




//----------------------------------------
//


int   dreaming = 0;

int   ltm_merge = 1;

int   stm_merge = 1;

Node* last_node_to_fire;

int   gtime = 0;

//----------------------------------------
//



//----------------------------------------
int
delete_link( Node* node, Node* target){

    list<pair<Node*, int> >::iterator b = node->branches.begin();

    for (; b!= node->branches.end(); b++){

      if (b->first == target ) {

	node->branches.erase(b);
 
	return 1;
      }
    }
    return 1;
}

//----------------------------------------
int
Node::clear_stm1(int depth, int mode, map<Node*,Node*>* stm_nodes ){

  if (depth<0) return 1;                    // can't delete

  list< pair<Node*, int> >::iterator b = branches.begin();

  if (mode == 1) {

    if (symbol.find("(")==0) stm_nodes->insert(pair<Node*,Node*>(this,this));
    
    for (;b!=branches.end();b++){

      if ( b->first->symbol.find("(") ==0)  b->second = 0;

      b->first->clear_stm1(depth-1, mode, stm_nodes);

    }
  }
  else{     //mode 2
  
    list< pair<Node*,int> > temp;
    
    for (;b!=branches.end();b++){
    
      b->first->clear_stm1(depth-1, mode, stm_nodes);  

      //cout<<head.first->symbol<<"  "<<b->first->symbol<<"  "<<b->second<<endl;
      
      //if ( b->second==0 ){ b = branches.erase(b);}
      if ( b->second!=0 ){ temp.push_back(*b);}
    }

    b=temp.begin();

    branches.clear();

    for (;b!=temp.end();b++) branches.push_back(*b);
    
  }
  
  return 1; 
}

//----------------------------------------
int
Node::clear_stm(int depth ){

  if (depth<0) return -2;                    // can't delete


  list< pair<Node*, int> >::iterator b = branches.begin();
   
  b = branches.begin();

  for (;b!=branches.end();b++){

    if (b->first->symbol.find("(") !=0)  b->first->clear_stm(depth-1);
    
  }


  
  int rv;
  
 L1:

  rv = 0;

  int num_ltm=0;
  
  b = branches.begin();

  for (;b!=branches.end();b++){

    cout<<symbol<<" "<<b->first->symbol<<endl;

    if (b->first->symbol.find("[")==0 ) num_ltm++;
    
    if (b->first->symbol.find("(")==0 )
      {    // (stm) node
      
	//rv = b->first->clear_stm(depth-1);
      rv = b->first->clear_stm(0);
      //cout<<rv<<endl;


      if (rv==2){                           // node ready to be deleted
	//cout<<"here"<<endl;
	delete b->first;

	return 1;                           // return for reproccesing
      }

      
      if (rv == 1) break;
      
    }
  }

  //cout<<symbol<<"-"<<rv<<endl;
  if (rv==1) goto L1;    // deleted node or [ltm] link, redo loop


  if (symbol.find("(")==0
      && branches.size()==0
      || branches.size()==num_ltm
      ) return 2;   // delete this node



  return 0;  
}



//----------------------------------------
Node::~Node( ){

  //cout<<"here"<<endl;
  
  list<pair<Node*, int> >::iterator b = branches.begin();

  for (; b!= branches.end(); b++){

    delete_link( b->first, this );
    
  }

  delete_link( copy.first, this );
  delete_link( head.first, this );
  

}





//----------------------------------------
Node*
Node::last_stm_tag_node(int depth ){            // returns last (stm) node created from previous input

  Node* ret_ptr =this;
  

  if (branches.size()==0 ) {                                              // terminal (stm)

    /*
    list<pair<Node*, int> >::iterator b = head.first->branches.begin();

    for (;b!= b = head.first->branches.end(); b++){                       // check head node for other terminal (stm)

    }
    */

    return this;
  }

  
  list<pair<Node*, int> >::iterator b = branches.begin();

  for (; b!= branches.end(); b++){

    
    if (b->first->copy.first == this){

      if (depth>0){

	ret_ptr=  b->first->last_stm_tag_node(depth-1 );
	break;
      
      }
      
    }
  }

  
  return ret_ptr;
}




//----------------------------------------
int
Node::clear_touches(int depth ){

  //if (symbol.find("(") != 0 ) touches1.clear();
   touches1.clear();

  last_touch=NULL;
  last_stm=NULL;
  
  //time = -1;

   input_value = threshold/2 - 1;
   
  if (depth<0) return 1;
  
  list< pair<Node*, int> >::iterator b = branches.begin();

  for (;b!=branches.end();b++){

    b->first->clear_touches(depth-1);
  }  
  return 1;
}



//----------------------------------------
int
Node::output_flag_clear(int depth ){

  output_flag = 0;

  if (depth<0) return 1;
  
  list< pair<Node*, int> >::iterator b = branches.begin();

  for (;b!=branches.end();b++){

    b->first->output_flag_clear(depth-1);

  }

  return 1;  
}


//----------------------------------------
int
Node::output(int depth, int tabs){

  if (tabs==0) cout<<endl<<"-------------------------------------------------------------"<<endl<<endl<<"\t";   //output formating



  output_flag=1;
  //output_flag=0;   // full printout
  
  //cout<<symbol<<"\t";
  //cout<<threshold<<":"<<symbol<<"\t";
  //cout<<value<<":"<<symbol<<"\t";

  if (symbol != "IP") {
    //cout<<head.second<<":"<<copy.second<<":"<<symbol<<":"<<value<<"\t";
    //cout<<head.second<<" "<<copy.second<<" "<<symbol<<" "<<value<<"\t";
    //cout<<head.second<<" "<<copy.second<<" "<<symbol<<" "<<branches.size()<<"\t";

    //cout<<head.second<<" "<<copy.second<<" "<<symbol<<" "<<value<<" "; for(list<pair<Node*,int> >::iterator b=branches.begin();b!=branches.end();b++) cout<<b->second<<" ";

    
    {
      int flag1=0;
      for(list<pair<Node*,int> >::iterator b=branches.begin();b!=branches.end();b++) if (b->second==20) flag1=1;
    
      if (head.second==20 || copy.second==20 || flag1 ==1){
	cout<<"\e[1m"<<symbol<<" "<<value<<"\t\e[0m";
	//cout<<"\e[1m"<<symbol<<"\t"<<"\e[0m";
      }else{
	cout<<symbol<<" "<<value<<"\t";
	//cout<<symbol<<"\t";
	//cout<<symbol<<" "<<head.first->symbol<<"\t";
      }
    }
       
    
    //cout<<symbol<<" "<<value<<"\t";
  }else
    {cout<<symbol<<"\t";}



  //cout<<endl;
 
  
  if (depth >= 0 ){
    
    list<pair<Node*,int> > branches_s;

    list<pair<Node*,int> >::iterator b=branches.begin();


    // ------------------------------- re-sort the branches for output formatting  order = (stm), [symbol], non-[ltm], [ltm]

    for (;b!=branches.end();b++){ if (b->first->symbol.find("(") !=0 && b->first->symbol.find("[") !=0 ) branches_s.push_back(*b); }

    
    //for (b=branches.begin();b!=branches.end();b++){ if ( b->first->symbol.find("[") ==0  ) branches_s.push_back(*b); }
    for (b=branches.begin();b!=branches.end();b++){ if ( b->first->symbol.find("[") ==0 && b->second<40 ) branches_s.push_back(*b); }  //kludge

    b=branches.begin();
    for (;b!=branches.end();b++){ if ( (b->first->symbol == "["+symbol+"]" )  ) branches_s.push_front(*b); }
    

    b=branches.begin();
    for (;b!=branches.end();b++){ if ( (b->first->symbol.find("(") ==0 )  ) branches_s.push_front(*b); }



    string last_symbol="";
    int first_flag=1;
    
    //b=branches.begin();
    b=branches_s.begin();

    for (;b!=branches_s.end();b++){
      //for (;b!=branches.end();b++){

      if (b->first->output_flag==0) {
      

	if (b->first->head.first == this || b->first->copy.first != this){

	  if (symbol.find("(")==0 && b->first->symbol.find("[")==0) continue;

	  
	  if (b==branches_s.begin() && b->first->symbol.find("(") !=0 &&
	      b->first->symbol.find("[") !=0    ) {first_flag=0; cout<<endl;}

	  if (b!=branches_s.begin() && first_flag==0 ) {cout<<endl;}


	  
	  if (last_symbol.find("(")==0 && b->first->symbol.find("(") !=0 ) cout<<endl;

	  if (tabs==0 && b->first->symbol.find("(") !=0) cout<<endl;
	  
	  last_symbol = b->first->symbol;
	  
	  if ((b!=branches_s.begin() || b->first->symbol.find("(") !=0)&& first_flag==0 )
	    for (int i=0; i!= tabs+1; i++) cout<<"\t\t";

	  //for (int i=0; i!= tabs+1; i++) cout<<"\t\t";
	  
	  cout<<"  ";
	  for (int i=3;i>0;i--) if( (b->first->value)<pow(10,i)) cout<<" ";
	  //for (int i=3;i>0;i--) if( (b->first->value)<pow(10,i)) cout<<"_";
	  for (int i=3;i>0;i--) if( (b->first->value)<pow(10,i)) cout<<" ";

	  //cout<<b->second<<"-";
	  
	  b->first->output(depth-1, tabs+1);

	  first_flag=0;

	  
	} //  b->first-> head->first = *this
	
      } // output_flag
	
    }   // for loop

  }     // depth

  if (tabs==0) {


    cout<<endl<<"-------------------------------------------------------------"<<endl<<endl;  //output formating
  }
  
  return 1;
};


    

//----------------------------------------
//
//void
Node*
merge( Node* n1, Node* n2 )
{
  //extern int gtime;
   
   if (n1==n2) {cout<<"merge error"<<endl; return NULL;}

   //cout<<"merge      "<<n1->symbol<<"\t"<<n2->symbol<<endl;
  
   if (n1->head.first == n2->copy.first &&                // don't merge with frame node -kludge
       n1->copy.first == n2->head.first &&
       n1->head.first != n1
       ){

     return NULL;

   }
   
   
   //cout<<n1->head.first->symbol<<" "<<n2->copy.first->symbol<<endl;
   //cout<<n1->copy.first->symbol<<" "<<n2->head.first->symbol<<endl;
   
 
  // create a new node n12 from n1 and n2
  // - if it does not already exist

  // loop over the copy node's branches, search for a pre-existing node


   Node* n12=NULL;
   
   int flag1=0;
  
     list< pair<Node*, int> >::iterator b = n2->branches.begin();

     /*

     for ( ; b != n2->branches.end(); b++ ) {

       if ( b->first->head.first == n1 	 ) {

	 b->first->input_value = b->first->threshold ;

	 n12 = b->first;
       
	 // flag1=1;  
	 
	 break;    //return;       // found one, return  //depreciated 
       }
       
     }
     */
  
     if (flag1==0){
  
       n12 = new Node( n1, n2 );                               // not found, make new node 

       if (n1->symbol.substr(0,1)=="[" &&                      // [ltm] merge node
	   n2->symbol.substr(0,1)=="[" ) {             

	 int i = n12->symbol.find("(",0); n12->symbol.replace(i,1,"[");
	     i = n12->symbol.find(")",0); n12->symbol.replace(i,1,"]");
       }
       
       //cout<<"merge (new)  "<< n12->symbol<<endl;
     
     }


   
   //----------------------------------------------  [ltm] merge

   extern int ltm_merge;
   
   if (ltm_merge==0) {

     b = n2->branches.begin();                                //link [ltm] node if it already exists
   
    for ( ; b != n2->branches.end(); b++ ) {

      if ( b->first->symbol.find("[")==0 &&
	   b->first->copy.first  == n1 ){

	pair<Node*, int>  link1;                         

	link1.first  = b->first;
	link1.second = 1;

	//cout<< n1->symbol<<"  "<<n2->symbol<<"  "<< b->first
	
	//if (n12 != NULL) n12->branches.push_back(link1);                   // (stm) to [ltm] link
	
	break;
      }
    }

     return n12;
   }
 

 
   if (n1->symbol.substr(0,1)=="(" &&        
       n2->symbol.substr(0,1)=="(" ) return n12;          // don't make [ltm] if n1 and n2 are (stm)

   if (n1->symbol.substr(0,1)=="[" &&        
       n2->symbol.substr(0,1)=="[" ) return n12;          // don't make [ltm] if n1 and n2 are [ltm]

   Node* n21=NULL;

    b = n2->branches.begin();
   
    for ( ; b != n2->branches.end(); b++ ) {

      if ( b->first->copy.first == n1 	 ) {

	n21 = b->first;

	break;
       
      }
    
    }


   //if (n21 != NULL) return;

   if (n21 == NULL) {


     string n1s = n1->symbol;
     string n2s = n2->symbol;

     n1->symbol = n2s;
     n2->symbol = n1s;
     
     n21  = new Node( n2, n1 ); 

     n1->symbol = n1s;
     n2->symbol = n2s;

     //n21->head.first = n2;
     //n21->copy.first = n1;
     
     n21->threshold = n21->threshold*2;

     int i = n21->symbol.find("(",0);

     n21->symbol.replace(i,1,"[");

     i = n21->symbol.find(")",0);

     n21->symbol.replace(i,1,"]");
     
     //cout<<"merge [new]  "<< n21->symbol<<"  "<<flag1<<endl;

   }

   if (flag1 == 0) {
     
   pair<Node*, int>  link1;                          //  link to 1
                     link1.first  = n12;
                     link1.second = 1;

   pair<Node*, int>  link2;                          //  link to 2
                     link2.first  = n21;
                     link2.second = 40;


   if (n12 != NULL) n12->branches.push_back(link2);                   // (stm) to [ltm] link
   //n21->branches.push_back(link1);
   }
   
return n12;    
};




//----------------------------------------
//
  

Node::Node(Node* n1,  Node* n2)                               // merge constructor
 {
   extern int gtime;

  

   string h,c;
   
 
 
  if ( n2->symbol.find("(") == 0 || n2->symbol.find("[") == 0 )
     { c = n2->symbol.substr(1,n2->symbol.size()-2); }
   else
     {
       if ( n2->symbol =="IP"  ) {c="";} else
	 { c = n2->symbol.substr(0,1);
	   if (n2->symbol=="and") c="+";}
     }
   
   if (n1->symbol.find("(" ) ==0 || n1->symbol.find("[" ) ==0 )
     { h = n1->symbol.substr(1,1); }
   else
     {
       if ( n1->symbol =="IP" || n1->head.first==n1->copy.first ) {h="";} else
	 {  h = n1->symbol.substr(0,1); }
     }


   
   if (h=="") { symbol = "(" + c + ")";} else
     {
       if (c=="") { symbol = "(" + h + ")";} else
	 { symbol    =  "(" + h + " " + c + ")" ;}
     }

   

   
   value     =  n1->value;
   //value   =  n2->value;

   //input_value     =5;
  input_value     =40;

  //threshold =  40;
   threshold =  10;

   //time      =  gtime;

   //threshold_merge = n2->time_merge;                           // inherit from n2
   //threshold_merge = 5;
   
   pair<Node*, int>  head_link;
                     head_link.first  = n1;
                     head_link.second = 3;                  // high resistance

 
   pair<Node*, int>   copy_link;
                      copy_link.first  = n2;
		      copy_link.second = 5;                 // low resistance

		      
		      
  if ( n2->last_stm!=NULL &&
       n2->head.first == n1   ){          // the fix 

    copy_link.first = n2->last_stm;      // bug 
    copy_link.second = 10;

    n2->last_stm->head.first = this;   // no this is the bug
    n2->last_stm->head.second = 2;
    
  }
			
   head = head_link;
   copy = copy_link;

   head_link.first  = this;                                       // re-use head/copy_link variables
   copy_link.first  = this;

   head.first->branches.push_front( copy_link );                  //

   //copy.first->branches.push_front( head_link );
 
   if (n2->last_stm==NULL) copy.first->branches.push_front( head_link );

   if (n2->last_stm!=NULL) n2->branches.push_front( head_link );

   
 };


//----------------------------------------
//


int
Node::touch1( int            input,
	      float          touch_value,
	      Node*          touched_by,
	      list<Node*>*   node_string,
	      int            unused,
	      int            output_level,
	      int            tabs,
	      int            depth )
{
  

  int ret_val = 0;

  if (unused==1){               // output mode from (stm)/[ltm] node,  - no merges

    //----------- only allow each node to fire one time

     list<Node*>::iterator ns = node_string->begin();

     for ( ; ns!= node_string->end(); ns++){

       if (*ns==this &&
	   head.first != copy.first                     // surface nodes can repeat
	   ){
	 
	 if (output_level==0) cout<<symbol<<"||";   // closed loop in hebb mode
	 return 2;
       }
     }   

     if (head.first==this && copy.first==this) {   // only true for IP node

       return 0;//ret_val;   // suppress printout of IP node
     }
  }

   
 
  
  input_value  +=  abs(input);                      //  touch with new input
  
 
  if ( input_value  > threshold ){             // -------------------------  node fires
 
 


    input_value = threshold/2 - 1;
    
    ret_val = 1;

    output_flag = 1;

    node_string->push_back(this);
    
    if (unused==0) value=touch_value;

    if (unused !=1 &&
	output_level !=0){
      
      if (symbol!="IP") head.first->touches1.push_front(pair<Node*,int>(this,head.second));
      if (symbol!="IP") copy.first->touches1.push_front(pair<Node*,int>(this,copy.second)); 
  
      head.first->last_touch=this;
      copy.first->last_touch=this;
    }

    if (output_level == -1){
      if (value==-1) touch_value =-1;

      if (touch_value==-1) value=-1;
    }
    
    // ---------------------------------------------------------------   output
    if (output_level==1 || output_level==0 ){   //right

      cout<<symbol;// <<" ";
      //for (int i=0; i!= tabs+1; i++) cout<<"\t";   cout<<"-->\t"<<symbol<<endl;
      //for (int i=0; i!= tabs+1; i++) cout<<"\t";   cout<<"-->\t"<<symbol<<":"<<value  <<endl;

    }

    if (output_level==-1){    // left

      //for (int i=0; i!= tabs+1; i++) cout<<"\t";   cout<<"\t"<< symbol << "  <--"<< endl;
      for (int i=0; i!= tabs+1; i++) cout<<"\t";   cout<<"\t"<< symbol<<":"<<value << "  <--"<< endl;
   }
   // ---------------------------------------------------------------   output

    //cout<<" --"<< node_string->front()->symbol<<endl;      

   // ---------------------------------------------------------------   merge

     
   if (   touched_by   !=  NULL
	  && output_level ==  -1                                // direction = left (up the graph)
	  && head.first   !=  touched_by                        //
	  && head.first   ==  copy.first                        // - both nodes are surface  
	  && touched_by->head.first == touched_by->copy.first   // - nodes
	  && unused==0 
	  ) {
     
     //cout<<"touch merge1 "<<this->symbol<<"\t"<< touched_by->symbol<<endl;

       Node* m = merge(this, touched_by );

       if (m!=NULL) last_stm=m;
       
       if (m!=NULL) {
	 
     
	 for (int i=0; i!= tabs+2; i++) cout<<"\t";   cout<<"|"<<endl;
	 for (int i=0; i!= tabs+2; i++) cout<<"\t"; 

	 list<Node*> node_string1;
	 
	 int rv= m->touch1( 100, touch_value, this, &node_string1, 0, 1, tabs+2, depth-1  );    // merge touch
	 //int rv= m->touch1( 100, touch_value, this, node_string, 0, 1, tabs+2, depth-1  );    // merge touch
	 cout<<endl;

	 if (rv!=0) {
	   ret_val=rv;

	 }
       }
       
   }  // -----left

   

   if (head.first != this                                        // not the IP node
       && output_level==1 ){                                     //direction = right

     
     //--------- branch left during (stm) merge with previous (stm)  //hebb loop

     //cout<< head.first->symbol.substr(1,1)<<"  "<< copy.first->symbol<<"  "<< copy.first->symbol.size()<<endl; 
     
     if (depth > 0 && head.first != this
	 && !(stm_merge > 1 && copy.first->symbol.size() > 2
	      && head.first->symbol.substr(1,1) != copy.first->symbol.substr( copy.first->symbol.size()-2,1) )
	 ){

       list<Node*>::iterator ns = node_string->end();

       ns--;
       
        
       //turn off point here
       //int rv = 1;//head.first->touch1( 8, value,  this,  node_string, 1, 0, tabs-2, depth  );
       int rv = head.first->touch1( 8, value,  this,  node_string, 1, 0, tabs-2, depth  );


       //node_string->erase(ns,node_string->end());

       

       if (rv == -1) value=rv;
 
       if (rv==2) {
	 if (symbol.find("+)") != std::string::npos ) value=rv;
	 head.second = 20;
       }


       
       ret_val=rv;
        
       cout<<" ";
       
     }
   //--------- branch left during (stm) merge with previous (stm)


     
     //--------- (stm) merge with previous (stm)
     
     //---------------- merge with head node touches1 list
     int merge_cnt=0;
     
     list< pair<Node*, int> >::iterator t = head.first->touches1.begin();

     for (;t!=head.first->touches1.end();t++){


       if ( ( !( symbol.find("[")==0 && t->first->symbol.find("[") !=0) ||
	      !( symbol.find("(")==0 && t->first->symbol.find("(") !=0) ) &&
	    depth > 1 &&
	    t->first != this &&  t->first->threshold < 15 &&  t->second < 6){

	 t->second =7;

	 //cout<<"h1 "<<head.first->symbol<<"  "<<symbol<<"  "<<t->first->symbol<<  endl;

	 Node* m = merge( t->first, this );

	 if (m!=NULL && depth>0) {

	   int rv =  m->touch1( 100, touch_value, this, node_string, 0, 1, tabs+2, depth-1  );

	   if (rv> ret_val)  ret_val = rv;

	   if (rv == -1 )  ret_val = rv;

	   if (rv == -1) value=rv;
	 
	   if (rv==2) {                                                         // special code for the conjunction node (+)
	     if (symbol.find("+)") != std::string::npos ) value=rv;
	     branches.back().second = 20;
	   }
	 
	 }

	 if (m!= NULL) merge_cnt++;
	 
	 extern int stm_merge;
	 
	 //return ret_val;
	 //break;                                      // stop after first merge
	 if (merge_cnt+1 > stm_merge ) break;          // stop after first merge
       }       
    
     }                                    // for loop over touches1
     
     //---------------- merge with head node touches1 list


     //---------------- merge with head's head node touches1 list

     extern int dreaming;

     if (dreaming == 1 &&
	 symbol.find("[")==0 &&
	 symbol != "IP" ){

       //t = head.first->head.first->touches1.begin();
       //for (;t!=head.first->head.first->touches1.end();t++){
       t = copy.first->touches1.begin();
       for (;t!=copy.first->touches1.end();t++){


       if ( ( t->first->symbol.find("[") ==0) &&
	    t->first != this ){    // &&  t->first->threshold < 15 &&  t->second < 6){


	 //cout<<"h1 "<<head.first->head.first->symbol<<"  "<<symbol<<"  "<<t->first->symbol<<  endl;

	 Node* m = merge( t->first, this );

	 if (m!=NULL && depth>0) {

	   int rv =  m->touch1( 100, touch_value, this, node_string, 0, 1, tabs+2, depth-1  );

	   if (rv> ret_val)  ret_val = rv;

	   if (rv == -1 )  ret_val = rv;

	   if (rv == -1) value=rv;
	 
	   if (rv==2) {
	     if (symbol.find("+)") != std::string::npos ) value=rv;
	     branches.back().second = 20;
	   }
	 
	 }
	 
	 //return ret_val;
	 break;                           // stop after first merge
       }       
    
     }                                    // for loop over touches1
     

       

     }
     
     //---------------- merge with head's head node touches1 list


     

     
     //--------- (stm) merge with previous (stm)


 
     // ----------------------------  touch [ltm] node if it exists

     //cout<<"here"<<endl;
     list< pair<Node*, int> >::iterator ltm = branches.begin();
     for (;ltm!=branches.end();ltm++){



       if (ltm->first->symbol.find("[") ==0) {
	 
	 //cout<<"K "<<symbol<<"-"<<ltm->first->symbol<<endl;

       int rv = ltm->first->touch1( 100, .9, this, node_string, 0, 1, tabs+2, 1  );

	 //cout<<rv<<endl;
	 break;
       }  
     }
     
     // ----------------------------  touch [ltm] node if it exists
 
     
     

     
   }   //  ----right


   // ---------------------------------------------------------------   merge


   

   if (output_level==-1){                           // direction=left

   // -----------------------------------------------  touch head+copy

      
     int flag=0;


 
     // --------------------------------------- movement code
     //--------- touch copy first if value=0  

     int flag1=0;
     
     list<Node*>::iterator ns = node_string->begin();

     for ( ; ns!= node_string->end(); ns++){

       if (*ns==copy.first) flag1=1;
     }

     
     if (depth > 0   && copy.first != this
	 && copy.first != head.first
	 && copy.first->value==0
	 && head.second < 15                   // not (stm) hebb bound
	 && flag1 == 0
	 && unused==1
	 ){

       ret_val = copy.first->touch1( 100, touch_value,  this, node_string,  unused, -1, tabs-2, depth -1  );

       if (value==0 && touched_by!=NULL) return ret_val;
       
       flag += ret_val;
     }
     // --------------------------------------- movement code
     


     
     //--------- touch head

     if (depth > 0
	 && head.first != this                   // not IP
	 ){

       if ( !(unused==1 && head.first->head.first == head.first->copy.first ) )
	 {
	   //cout<<"here "<<head.first->symbol<<endl;

	   //ret_val = head.first->touch1( input, touch_value,  this, node_string,  unused, -1, tabs-2, depth-1  );
	   ret_val = head.first->touch1( input, touch_value,  this, node_string,  unused, -1, tabs-2, depth  );

	   flag += ret_val;

	 }
     }
     
     
     //--------- touch copy

     if (depth > 0   && copy.first != this
	 && copy.first != head.first       ){     // this node not a surface node

       extern int dreaming;

       if (/* dreaming==1 && */
	   copy.first->head.first == copy.first->copy.first ){    //  copy is surface node
	 
	 list<Node*> node_string1;

	 if ( symbol.find("[")==0){

	   ret_val = head.first->touch1( 100, 1.2,  NULL, node_string,  0, -1, tabs-2, depth -1  );
	 }
	 else{
	   
	 //ret_val = copy.first->touch1( 100, touch_value,  this, &node_string1,  0, -1, tabs-2, depth -1  );
	 ret_val = copy.first->touch1( 100, 1.1,  NULL, node_string,  0, -1, tabs-2, depth -1  );
	 }

       }
       else{
	    
	 ret_val = copy.first->touch1( 100, touch_value,  this, node_string,  unused, -1, tabs-2, depth -1  );
	 
	 flag += ret_val;
	    
       }
     }

     
   
     
      
     if (flag>0) return ret_val;
     // -----------------------------------------------  touch head+copy

   }                                        // ouput_level==-1   =left


 


   if (output_level==0){             //------ hebb loop
    

     //cout<<" --"<<symbol<<" "<<head.first->symbol<<" "<<head.second<<" "<< node_string->front()->symbol<<endl;     
 
     if ( head.first != this
	  && touched_by != head.first
	  && head.first->symbol.find("[") != 0
	  && ( head.second > 2 || head.first == node_string->front() )
	  ){

 
       
       int rv=  head.first->touch1( input, value,  this,  node_string, 1, 0, tabs-2, depth  );
 
 
       if ( rv==2) {
	 head.second = 20;
	 if (symbol.find("+)") != std::string::npos ) value=rv;
       }
   
       if (symbol.find("+)") != std::string::npos && rv < 2
	   && symbol.find("(+") == std::string::npos ) {

	 if (copy.first->value ==2){
	   value=2;
	   return rv;
	 }
	 
	 ret_val=-1;
	 value=ret_val;
	 return ret_val;
       }
       


 
	 
      if (rv!=0) return rv;

      
     }

 

     //if ( copy.first != this && touched_by != copy.first){
    if ( copy.first != this && touched_by != copy.first && copy.first->symbol.find("[") != 0){
       
       int rv=  copy.first->touch1( input, value,  this,  node_string, 1, 0, tabs-2, depth  );

       //if (rv!=0) value=rv;

       if (rv==2) {
	 if (symbol.find("+)") != std::string::npos ) value=rv;
	 copy.second = 20;
       }

       
       if (rv!=0) return rv;
     }


     if ( touched_by == head.first || touched_by == copy.first ) {

 	      
     list<pair<Node*, int> >::iterator b = branches.begin();

      for (; b!= branches.end(); b++){

       //if ( touched_by != b->first ){
       if ( touched_by != b->first && b->first->symbol.find("[") != 0 ){
	 
	 int rv=  b->first->touch1( input, value,  this,  node_string, 1, 0, tabs-2, depth  );

       if (rv==2) {
	 if (symbol.find("+)") != std::string::npos ) value=rv;
	 //b->first->head.second = 20;
       }
    
	 if (rv!=0) return rv;
       }
       
     }

     }     

     
   //--------- touch head   



   }  // right/left
   




   
   
 }  // node fires

  
 return ret_val;
 
};







void main1(){

  ltm_merge = 0;

  list<Node*> node_strings;
  
   list<Node*>* node_string = &node_strings;;
     
  Node  ip  ( "IP" );

  Node  ip1  ( "IP1" );  // kludge for  merge function
  ip.copy.first = &ip1;
  
  
  Node  h   ("hiker", &ip );


  Node  r   ("rocks", &ip );

  Node  d   ("duck", &ip );

  Node  s   ("sneeze", &ip );


  
  ip.output_flag_clear(10);  
  ip.output(1,0); 

  //ip.clear_touches(10); cout<<"clear touches"<<endl;


  h.touch1         ( 100, 1, NULL, node_string, gtime++, -1, 1, 4);

    ip.output_flag_clear(10);  ip.output(4,0); 

  
    r.touch1         ( 100, 1, NULL, node_string, gtime++, -1, 1, 4);

    //h.touch1         ( 100, 1, NULL, node_string, gtime++, -1, 1, 4);

    ip.output_flag_clear(10);  ip.output(4,0); 



    d.touch1         ( 100, 1, NULL, node_string, gtime++, -1, 1, 5);

    ip.output_flag_clear(10);  ip.output(4,0); 

    s.touch1         ( 100, 1, NULL, node_string, gtime++, -1, 1, 7);

    ip.output_flag_clear(10);  ip.output(4,0); 



ip.clear_touches(10); cout<<"clear touches"<<endl;
 
     h.touch1         ( 100, 1, NULL, node_string, gtime++, -1, 1, 4);

    ip.output_flag_clear(10);  ip.output(4,0); 

  
    r.touch1         ( 100, 1, NULL, node_string, gtime++, -1, 1, 4);


    ip.output_flag_clear(10);  ip.output(4,0); 



    
}



void main2(){

  
  
  Node  ip  ( "IP" );

  Node  ip1  ( "IP1" );


  ip.copy.first = &ip1;

   list<Node*> node_strings;
  
   list<Node*>* node_string = &node_strings;

  Node  a   ("a", &ip );
  Node  n   ("n", &ip );
  
  ip.output_flag_clear(10);  
  ip.output(1,0); 


  ltm_merge = 1;

  a.touch1         ( 100, 1, NULL, node_string, gtime++, -1, 1, 3);
  
 ip.output_flag_clear(10);  ip.output(1,0);   

 //a.output_flag_clear(10);  a.output(1,0);   


 ip.clear_touches(10); cout<<"clear touches"<<endl;
 
 ip.output_flag_clear(10);  ip.output(1,0);
 
 a.touch1         ( 100, 1, NULL, node_string, gtime++, -1, 1, 3);

 ip.output_flag_clear(10);  ip.output(1,0);


 a.touch1         ( 100, 1, NULL, node_string, gtime++, -1, 1, 3);

 ip.output_flag_clear(10);  ip.output(1,0);



 
 ip.output_flag_clear(10);  ip.output(1,0);


 a.touch1         ( 100, 1, NULL, node_string, gtime++, -1, 1, 3);

 ip.output_flag_clear(10);  ip.output(1,0);



 cout<<"clear touches"<<endl; ip.clear_touches(10); 

 n.touch1         ( 100, 1, NULL, node_string, gtime++, -1, 1, 4);

 ip.output_flag_clear(10);  ip.output(1,0);


 
 a.touch1         ( 100, 1, NULL, node_string, gtime++, -1, 1, 5);

 ip.output_flag_clear(10);  ip.output(2,0);



 /*
  Node  h   ("h", &ip );

  ip.output_flag_clear(10);  ip.output(2,0);

  //ltm_merge = 0;
  
 h.touch1         ( 100, 1, NULL, node_string, gtime++, -1, 1, 5);

 ip.output_flag_clear(10);  ip.output(3,0);
 */

 

 cout<<"clear touches"<<endl; ip.clear_touches(10); 
 
a.touch1         ( 100, 1, NULL, node_string, gtime++, -1, 1, 5);

 ip.output_flag_clear(10);  ip.output(2,0);



}

//-----------------------------------------
void main3(){

  ltm_merge = 0;

  list<Node*> node_strings;
  
  list<Node*>* node_string = &node_strings;
  
  Node  ip  ( "IP" );

  Node  ip1  ( "IP1" );  // kludge for  merge function
  ip.copy.first = &ip;
  ip.head.first = &ip;
  
  
  Node  b   ("boys", &ip );
 
  Node  t   ("thing", &ip );

  Node  e   ("eat", &ip );



  
  ip.output_flag_clear(10);   ip.output(1,0);    //  output the ip graph


     b.touch1         ( 100, 1, NULL, node_string, 0, -1, 1, 4);

     //ip.output_flag_clear(10);  ip.output(4,0); 

      //cout<<"last node to fire ="<<last_node_to_fire->symbol<<endl;



    e.touch1         ( 100, 1, NULL, node_string, 0, -1, 1, 4);

    //ip.output_flag_clear(10);  ip.output(4,0); 

      //cout<<"last node to fire ="<<last_node_to_fire->symbol<<endl;

       t.touch1         ( 100, 0, NULL, node_string, 0, -1, 1, 4);

       ip.output_flag_clear(10);  ip.output(4,0); 



      //Node * b_e_t = last_node_to_fire;

      Node * b_e_t = node_string->back();

      
      
     ip.clear_touches(10); cout<<" time interval occurs"<<endl<<endl;       // some time elapses



     node_string->clear();
     
     b_e_t->touch1         ( 45, 0, NULL, node_string, 1, -1, 7, 4);

}




//-----------------------------------------
void main4(){

  ltm_merge = 0;

  int ret_val = 0;
  
  list<Node*> node_strings;
  
  list<Node*>* node_string = &node_strings;
  
  Node  ip  ( "IP" );

  ip.copy.first = &ip;
  ip.head.first = &ip;
  
  
  Node  and1   ("and", &ip ); //and1.value=0;

  Node  a   ("a", &ip );

  Node  n   ("n", &ip );




  Node  space   ("space"  , &a );
  Node  time    ("time"   , &a );
  Node  feeling ("feeling", &a );

  Node  me    ("me"    , &n );
  Node  thing ("thing" , &n );
  Node  vp    ("vp"    , &n );


  ip.output_flag_clear(10);   ip.output(1,0);    //  output the ip graph

  


  // I eat here
  /*  
  me.touch1         ( 100, 1, NULL, node_string, 0, -1, 3, 4); cout<<endl<<endl;

  vp.touch1         ( 100, 1, NULL, node_string, 0, -1, 3, 5); cout<<endl<<endl;

  space.touch1         ( 100, 1, NULL, node_string, 0, -1, 3, 5); cout<<endl;
  */

  
  // thing
  /*
  thing.touch1         ( 100, 1, NULL, node_string, 0, -1, 3, 5); cout<<endl;

  */
  

  {
  // i here  and now
  // i where and when

  
  node_string->clear();
 

  ret_val = thing. touch1( 100, 1, NULL, node_string, 0, -1, 3, 5); cout<<endl<<"\t\t\t\t\t\t RETURN="<<ret_val<<endl; node_string->clear(); ip.output_flag_clear(10); cout<<std::string(70,'-')<<endl<<endl; //ip.output(4,0);

  //ret_val = space. touch1( 100, 1, NULL, node_string, 0, -1, 3, 5); cout<<endl<<"\t\t\t\t\t\t RETURN="<<ret_val<<endl; node_string->clear(); ip.output_flag_clear(10); cout<<std::string(70,'-')<<endl<<endl; //ip.output(4,0);
  ret_val = space. touch1( 100, 0, NULL, node_string, 0, -1, 3, 5); cout<<endl<<"\t\t\t\t\t\t RETURN="<<ret_val<<endl; node_string->clear(); ip.output_flag_clear(10); cout<<std::string(70,'-')<<endl<<endl; //ip.output(4,0);

  
  ret_val = and1. touch1( 100, 1, NULL, node_string, 0, -1, 3, 5);  cout<<endl<<"\t\t\t\t\t\t RETURN="<<ret_val<<endl; node_string->clear();  ip.output_flag_clear(10); cout<<std::string(70,'-')<<endl<<endl; //ip.output(4,0);
    
  ret_val = time.touch1( 100, 0, NULL, node_string, 0, -1, 3, 9);  cout<<endl<<"\t\t\t\t\t\t RETURN="<<ret_val<<endl; 
  //ret_val = time.touch1( 100, 1, NULL, node_string, 0, -1, 3, 9);  cout<<endl<<"\t\t\t\t\t\t RETURN="<<ret_val<<endl; 
  //ret_val = thing.touch1( 100, 1, NULL, node_string, 0, -1, 3, 7);  cout<<endl<<"\t\t\t\t\t\t RETURN="<<ret_val<<endl; 

  
  //Node* hashtag = node_string->back(); node_string->clear();
  Node* hashtag = ip.last_stm->last_stm_tag_node(4);
  
  ip.output_flag_clear(10);  ip.output(4,0); 

  ip.clear_touches(10); cout<<" time interval occurs"<<endl<<endl;       // some time elapses


  hashtag->touch1         ( 100, 1, NULL, node_string, 1, -1, 13, 5);      node_string->clear();

  if (ret_val==ret_val) return ; 
  }





  //------------------------------------------------------------  [ltm]

  
  ltm_merge = 1;

  ret_val = a.touch1( 100, 1, NULL, node_string, 0, -1, 3, 5); cout<<endl<<"\t\t\t\t\t\t RETURN="<<ret_val<<endl<<endl; node_string->clear(); cout<<endl<<endl; 

  //ret_val = a.touch1( 100, 1, NULL, node_string, 0, -1, 3, 5); cout<<endl<<"\t\t\t\t\t\t RETURN="<<ret_val<<endl<<endl; node_string->clear(); cout<<endl<<endl; 


  //ret_val = n.touch1( 100, 1, NULL, node_string, 0, -1, 3, 5); cout<<endl<<"\t\t\t\t\t\t RETURN="<<ret_val<<endl; node_string->back(); node_string->clear(); cout<<endl;

  //ltm_merge = 0;
  
  ret_val = n.touch1( 100, 1, NULL, node_string, 0, -1, 3, 5); cout<<endl<<"\t\t\t\t\t\t RETURN="<<ret_val<<endl<<endl; node_string->clear(); cout<<endl<<endl; 
  
  Node* a_n = ip.last_stm->last_stm_tag_node(4);
    
  ip.output_flag_clear(10);  ip.output(4,0);


  ip.clear_touches(8); cout<<" time interval occurs"<<endl<<endl;       // some time elapses

  cout<<" dreaming=1"<<endl;
  
  dreaming = 1;

  ltm_merge = 1;
  
			 
  a_n->touch1         ( 100, 1, NULL, node_string, 1, -1, 9, 7);      //node_string->clear();


  ip.output_flag_clear(10);  ip.output(4,0);

  //cout<<node_string->back()->symbol<<endl;

  Node* a_n_ltm = node_string->back();

  node_string->clear();

  ip.clear_touches(8); cout<<" time interval occurs"<<endl<<endl;       // some time elapses


  cout<<"clear (stm), return="<<ip.clear_stm(5)<<endl;; 
  cout<<"clear (stm), return="<<ip.clear_stm(5)<<endl;; 
  cout<<"clear (stm), return="<<ip.clear_stm(5)<<endl;; 
  cout<<"clear (stm), return="<<ip.clear_stm(5)<<endl;; 
  cout<<"clear (stm), return="<<ip.clear_stm(5)<<endl;; 

  ip.output_flag_clear(10);  ip.output(4,0);
  
  
  dreaming = 0;  cout<<" dreaming=0"<<endl;

  ltm_merge = 0;
  
  a_n_ltm->touch1         ( 100, 1, NULL, node_string, 1, -1, 6, 7);      //node_string->clear();


    ip.output_flag_clear(10);  ip.output(4,0);

  ip.clear_touches(8); cout<<" time interval occurs"<<endl<<endl;       // some time elapses
  
  cout<<"clear (stm), return="<<ip.clear_stm(5)<<endl;; 
  cout<<"clear (stm), return="<<ip.clear_stm(5)<<endl;; 
  cout<<"clear (stm), return="<<ip.clear_stm(5)<<endl;; 

    ip.output_flag_clear(10);  ip.output(4,0);

  //------------------------------------------------------------  [a]-[n] sequence

    //ltm_merge=1;

  node_string->clear();    

  ret_val = space.touch1( 100, 1, NULL, node_string, 0, -1, 3, 7); cout<<endl<<"\t\t\t\t\t\t RETURN="<<ret_val<<endl<<endl; node_string->clear(); cout<<endl<<endl;


 ip.output_flag_clear(10);  ip.output(4,0);
  
 // draw rest in by hand

  //------------------------------------------------------------  [a]-[n] sequence

 ip.clear_touches(8); cout<<" time interval occurs"<<endl<<endl;       // some time elapses
  

 map<Node*,Node*> stm_nodes;
 
 cout<<"clear (stm) mode 1, return="<<ip.clear_stm1(5, 1, &stm_nodes)<<endl;;
 cout<<"clear (stm) mode 1, return="<<ip.clear_stm1(5, 2, &stm_nodes)<<endl;; 

ip.output_flag_clear(10);  ip.output(4,0);
 
    map<Node*,Node*>::iterator s;

  s = stm_nodes.begin();  for (;s!=stm_nodes.end();s++) delete s->second;


  ip.output_flag_clear(10);  ip.output(4,0);


  
  //------------------------------------------------------------  [ltm]



  // ----------------------------------------------------------- [vp]

  ltm_merge = 1;

  ret_val = vp.touch1( 100, 1, NULL, node_string, 0, -1, 3, 7); cout<<endl<<"\t\t\t\t\t\t RETURN="<<ret_val<<endl<<endl; node_string->clear(); cout<<endl<<endl;

    ip.output_flag_clear(10);  ip.output(4,0);
  // ----------------------------------------------------------- [vp]




  



  
}



int
main(){

  //main1();     // hiker rock duck sneeze   (stm) memory

  //main2();    // a-n graph, (stm) + [ltm] memory

  //main3();    // movment, boys eat what?,   what boys eat?

  main4();      // a-n graph + conjunction
  
}
