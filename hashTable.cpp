//Hash table

//Apply the String hash function in PHP

#include<hash_map>

#include<iostream>
#include<vector>
#include<string>
#include<fstream>

#define _TEST__

using namespace std;

const size_t hashTableSize = 4421;
const double use2hash = 0.61800339887;	// (sqrt(5)-1)/2

struct node{
	string key;
	node * next;
};

class hashTable{
public:
	hashTable()
		:queryCount( 0 ), collisionCount( 0 ){
		for( size_t i = 0; i != hashTableSize; ++i )
			table[i].next = NULL;
	}
	void insert( const string word );
	void erase( const string word );
	void display( ostream & out);
private:
	size_t hashValue( const string word );
	node table [ hashTableSize ];
	size_t queryCount;		//number of words
	size_t collisionCount;	//times of collisions
};

void hashTable::insert( const string word ){
	++queryCount;
	size_t hv = hashValue( word );
	if( table[hv].next == NULL ){
		table[hv].key = word;
		table[hv].next = new node;
		table[hv].next->next = NULL;
	}
	else{
		++collisionCount;
		node * p = table[hv].next;
		while( p->next != NULL )
			p = p->next;
		p->key = word;
		p->next = new node;
		p->next->next = NULL;
	}
}

void hashTable::erase( const string word ){
	size_t hv = hashValue( word );
	if( table[hv].next != NULL ){
		if( table[hv].key == word ){
			delete table[hv].next;
			table[hv].next = NULL;
		}
		else{
			node * p = &table[hv];
			while( p->next->key != word )
				p = p->next;
			node * pv = p->next;
			p->next = p->next->next;
			delete pv;
		}
	}
}

void hashTable::display( ostream & out ){
	cout << "hashTableSize = " << hashTableSize << endl;
	cout << "queryCount = " << queryCount << endl;
	cout << "collisionCount = " << collisionCount << endl;
	cout << "collision times = " << (double) collisionCount / queryCount << endl;
#ifdef _TEST__
	out << "hashTableSize\t=\t" << hashTableSize << endl;
	out << "queryCount\t=\t" << queryCount << endl;
	out << "collisionCount\t=\t" << collisionCount << endl;
	out << "collision times\t=\t" << (double) collisionCount / queryCount << endl;
#endif//_TEST__
}

size_t hashTable::hashValue(const std::string word){

	size_t v = 0;
	for( size_t i = 0; i != word.size(); ++i ){
		v = ( v << 4 ) + word[i];
		size_t g = v & 0xF0000000;
		if( g != 0 ){
			v = v ^ ( g >> 24 ); 
			v = v ^ g; 
		}
	}
	v = v % hashTableSize;
	return v;
}

int main(){
	hashTable test;
	cout << "Please input file name: " << endl;
	string filename; 
	cin >> filename;
	ifstream fin( filename.c_str() );
	ofstream fout( "res.txt" );
	string word;
	while( fin >> word )
		test.insert( word );
	test.display( fout );
	system("pause");
	return 0;
}