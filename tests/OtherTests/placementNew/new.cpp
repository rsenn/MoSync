/* Copyright 2013 David Axmark

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

// new_op_new.cpp
// compile with: /EHsc
#include<new>	//this is key to placement new working
#include<iostream>

using namespace std;

class MyClass 
{
public: 
   MyClass( )
   {
      cout << "Construction MyClass." << this << endl;
   };

   ~MyClass( )
   {
      imember = 0; cout << "Destructing MyClass." << this << endl;
   };
   int imember;
};

int main( ) 
{
   // The first form of new delete
   MyClass* fPtr = new MyClass;
   delete fPtr;

   // The second form of new delete
   char x[sizeof( MyClass )];
   MyClass* fPtr2 = new( &x[0] ) MyClass;
   fPtr2 -> ~MyClass();
   cout << "The address of x[0] is : " << ( void* )&x[0] << endl;

   // The third form of new delete
   MyClass* fPtr3 = new( nothrow ) MyClass;
   delete fPtr3;
}

#include <new>
class X
{
   public:
      X(int n, int x): id(n){ }
      ~X(){ }
   private:
      int id;
      //	...
};
 
int main2()
{
   char* whole = new char[ 3 * sizeof(X) ];  // a 3-part buffer
   X * p1 = new(whole) X(8, 5);                 // fill the front
   char* seg2 = &whole[ sizeof(X) ];         // mark second segment
   X * p2 = new(seg2) X(9, 8);                  // fill second segment
   char* seg3 = &whole[ 2 * sizeof(X) ];     // mark third segment
   X * p3 = new(seg3) X(10, 9);                 // fill third segment
 
   p2->~X();   // clear only middle segment, but keep the buffer
   // ...
   return 0;
}

template<class T, class N> class Y
{
   public:
      Y(T n): id(n){ }
      ~Y(){ }
			static void func(void* ptr, void* n, void* b) {
				new (ptr) Test(*(T*)n, *(N*)b);
			}
   private:
      T id;
      //	...
			struct Test {
				Test(T n, N b) : t(n), c(b) {}
				T t;
				N c;
			};
};
 
int main3()
{
   char* whole = new char[ 3 * sizeof(Y<double, int>) ];  // a 3-part buffer
   Y<double, int> * p1 = new(whole) Y<double, int>(8);                 // fill the front
   char* seg2 = &whole[ sizeof(Y<double, int>) ];         // mark second segment
   Y<double, int> * p2 = new(seg2) Y<double, int>(9);                  // fill second segment
   char* seg3 = &whole[ 2 * sizeof(Y<double, int>) ];     // mark third segment
   Y<double, int> * p3 = new(seg3) Y<double, int>(10);                 // fill third segment

	 p3->func(p3, p1, p2);
 
   p2->~Y();   // clear only middle segment, but keep the buffer
   // ...
   return 0;
}


template<class KeyType, class ValueType> struct Pair {
	Pair(const KeyType& k, const ValueType& v) : key(k), value(v) {}
	KeyType key;
	ValueType value;
};

template<class KeyType, class ValueType>
void myCopy(void* pair, const void* key, const void* value) {
	//new ((int*)pair) KeyType(*(KeyType*)key);
	//new (pair + sizeof(KeyType)) ValueType(*(ValueType*)value);
	//Pair* p = (Pair*)pair;
	//p->Pair(*(KeyType*)key, *(ValueType*)value);
	new (pair) Pair<KeyType, ValueType>(*(KeyType*)key, *(ValueType*)value);
}

void main4() {
	myCopy<int, int>(NULL, NULL, NULL);
}
