#ifndef _BASIC_LIST_
#define _BASIC_LIST_
#include<iostream>

class BasicList{
	public:
		class BasicNode{
				friend class BasicList;
			public:
				BasicNode *prev, *next;
				virtual ~BasicNode(){std::cout << "I am 'BasicNode' destructor.\n";};
		};

		class BasicIterator{
			private:
				friend class BasicList;
			public:
				BasicNode *node;
				BasicList *parent;

				typedef enum{
					NORMAL,
					PAST_REAR,
					OUT
				}TBasicIteratorStatus;

				TBasicIteratorStatus status;
				BasicIterator(BasicList::BasicNode *_node, TBasicIteratorStatus _status, BasicList* _parent);
			public:
				BasicIterator();
				
				BasicIterator& operator= (const BasicIterator &_itr);
				virtual BasicIterator& operator++ ();
				virtual BasicIterator& operator-- ();
				bool operator== (const BasicIterator &_itr) const;
				bool operator!= (const BasicIterator &_itr) const;
		};
	
		size_t L_size;
		BasicNode *head, *tail;
		
		void init();
	public:
		BasicList();
		~BasicList();

		BasicIterator begin();
		BasicIterator end();
		BasicIterator pos(size_t _pos);

		size_t size();
		void erase(BasicIterator _itr);
		void pop_front();
		void pop_back();
		void clear();
		bool empty();
};
#endif