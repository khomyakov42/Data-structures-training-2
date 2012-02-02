#ifndef __TRIE__
#define __TRIE__
#include<iostream>
#include<conio.h>
#include<ctype.h>
#include<cstdio>
#include <Windows.h>


#include<list>
namespace hmw{
template<class K, class T> class trie{
	private:
		class Node{
			private:
				friend class trie<K, T>;
				std::list<Node*> children;
				T val;
				Node* parent;
				K key;
            bool empty;
			public:
            Node* nextChild(Node* _node);
            Node* prevChild(Node* _node);
				Node* addChild(const K &_key);
            Node(Node* _parent);
            Node(Node* _parent, const K &_key);
		};

		class Ref{
			public:
				Node* node;
				int pos;
				Ref(){};
				Ref(Node* _node, int _pos){node = _node; pos = _pos;};
		};

      class Proxy{
         private:
            trie* parent;
            K key;
         public:
            Proxy(trie* _parent, const K &_key);
            operator T();
            void operator= (const T &_val);
      };

	public:
      class OutOfRange{};

		class iterator{
			private:
            enum TState{
               NORMAL,
               PAST_REAR,
               BEFORE_FIRST
            };
            TState state;
				friend class trie<K, T>;
				trie<K, T>* parent;
				Ref ref;
				iterator(trie* _parent, Ref _ref){parent = _parent; ref = _ref;};
            iterator(trie* _parent, Node* _node, TState _state);
				bool stepIn(const K &key, int i);
            Node* nextChild(Node* _node);
			public:
				iterator(){parent = NULL;};
            iterator& operator= (const iterator &_itr);
            iterator& operator++ ();
            iterator& operator-- ();
            T& operator* ();
            bool operator== (const iterator &_itr);
            bool operator!= (const iterator &_itr);
		};
	
	private:
      enum TSide{
         LEFT,
         RIGHT
      };

		size_t trie_size;
		Node *root;
		
		Node* makeExplicit(const Ref &ref);
		K subval(const K &s, int start, int count);
      Node* getNodeByKey(const K &_key);
      Node* getFirstNoEmpty(Node* node, TSide side);
      Node* getMostNode(Node* _node, TSide side);
      void restoreOrderChildren(Node* node);
      void deleteTrie(Node* node);
	public:
		trie();
      ~trie();

		iterator insert(const K &_key, const T &_val);
      void erase(K _key);
      void erase(const iterator &_itr);

      iterator begin();
      iterator end();
      iterator find(const K &_key);

      Proxy operator[] (const K &_key);
      bool empty();
      size_t size();

      void clear();
};
//////////////////////////////////NODE////////////////////////////////
template<class K, class T> trie<K, T>::Node::Node(Node* _parent){
   parent = _parent;
   empty = true;
}

template<class K, class T> trie<K, T>::Node::Node(Node* _parent, const K &_key){
   parent = _parent;
   key = _key;
   empty = true;
}

template<class K, class T> typename trie<K, T>::Node* trie<K, T>::Node::addChild(const K &_key){
	Node* node = new Node(this, _key);
	children.push_back(node);
	return node;
}

template<class K, class T> typename trie<K, T>::Node* trie<K, T>::Node::nextChild(Node* _node){
   for(std::list<Node*>::iterator itr = children.begin(); itr != children.end(); ++itr)
      if(*itr == _node)
         if(itr != --children.end())
            return *(++itr);
   return NULL;
}

template<class K, class T> typename trie<K, T>::Node* trie<K, T>::Node::prevChild(Node* _node){
   for(std::list<Node*>::reverse_iterator itr = children.rbegin(); itr != children.rend(); ++itr)
      if(*itr == _node)
         if(itr != --children.rend())
            return *(++itr);
   return NULL;
}
////////////////////////////////PROXY//////////////////////////////////
template<class K, class T> trie<K, T>::Proxy::Proxy(trie* _parent, const K &_key){
   key = _key;
   parent = _parent;
}

template<class K, class T> trie<K, T>::Proxy::operator T (){
   return *(parent->find(key));
}

template<class K, class T> void trie<K, T>::Proxy::operator= (const T &_val){
   parent->insert(key, _val);
}

/////////////////////////////////ITERATOR////////////////////////////	
template<class K, class T> bool trie<K, T>::iterator::stepIn(const K &key, int pos){
	if((ref.pos + 1) < ref.node->key.size()){
		if(ref.node->key[ref.pos + 1] == key[pos]){
			ref.pos++;
			return true;
		}
	}
	else
		for(std::list<Node*>::iterator i = ref.node->children.begin(); i != ref.node->children.end(); ++i)
			if((*i)->key[0] == key[pos]){
				ref.node = *i;
				ref.pos = 0;
				return true;
			}
	return false;
}

template<class K, class T> trie<K, T>::iterator::iterator(trie* _parent, Node* _node, TState _state){
   parent = _parent;
   ref = Ref(_node, 0);
   state = _state;
}

template<class K, class T> typename trie<K, T>::iterator& trie<K, T>::iterator::operator= (const iterator &_itr){
   ref = _itr.ref;
   state = _itr.state;
   parent = _itr.parent;
   return *this;
}

template<class K, class T> typename trie<K, T>::iterator& trie<K, T>::iterator::operator++ (){
   Node* pnode = ref.node, *node = NULL;

   if(state == PAST_REAR || parent == NULL)
      throw  OutOfRange();

   if(state == BEFORE_FIRST){
      ref.node = parent->getFirstNoEmpty(parent->root, TSide::LEFT);
      state = NORMAL;
      return *this;
   }

   if(ref.node->children.size() == 0){
      node = ref.node->parent->nextChild(pnode);
      if(node == NULL){
         node = ref.node;
         while(node->parent != NULL && node->nextChild(pnode) == NULL){
            pnode = node;
            node = node->parent;
         }
         node = node->nextChild(pnode);
         
         if(node == NULL)
            state = iterator::TState::PAST_REAR;
         else if(node->empty)
            node = parent->getFirstNoEmpty(node, TSide::LEFT);
      }
      if(node != NULL && node->empty)
         node = parent->getFirstNoEmpty(node, TSide::LEFT);
   }
   else{
      node = parent->getFirstNoEmpty(ref.node, TSide::LEFT);
   }

   ref.node = node;
   return *this;
}

template<class K, class T> typename trie<K, T>::iterator& trie<K, T>::iterator::operator-- (){
   Node* pnode = NULL, *node = ref.node;

   if(parent == NULL || state == BEFORE_FIRST)
      throw  OutOfRange();

   if(state == PAST_REAR){
      ref.node = parent->getMostNode(parent->root, TSide::RIGHT);
      state = NORMAL;
      return *this;
   }
	
	if(node->parent == parent->root && node->parent->prevChild(node) == NULL)
		state = TState::BEFORE_FIRST;
	else{
		while(node != NULL && (node->prevChild(pnode) == NULL && (node->empty || pnode == NULL) && node != parent->root)){
			pnode = node;
			node = node->parent;
		}
	
	/*
	if(node != parent->root)
		while((node != NULL) && ((!node->empty) || (node->prevChild(pnode) == NULL))){
			pnode = node;
			node = node->parent;
		}
	else
		node = node->parent;
		*/
		if(node == NULL)
			state = TState::BEFORE_FIRST;
		else if(node->empty || node == parent->root)
			node = parent->getMostNode(node->prevChild(pnode), TSide::RIGHT);
	}
   ref.node = node;
   return *this;
}

template<class K, class T> T& trie<K, T>::iterator::operator* (){
   if(state != NORMAL)
      throw OutOfRange();

   return ref.node->val;
}

template<class K, class T> bool trie<K, T>::iterator::operator== (const iterator &_itr){
   return ref.node == _itr.ref.node && state == _itr.state && parent == _itr.parent;
}

template<class K, class T> bool trie<K, T>::iterator::operator!= (const iterator &_itr){
   return !(*this == _itr);
}

////////////////////////////////TRIE//////////////////////////////////

template<class K, class T> typename trie<K, T>::Node* trie<K, T>::makeExplicit(const Ref &ref){
	Node *node = new Node(ref.node->parent);

   node->children.push_back(ref.node);
   for(std::list<Node*>::iterator itr = ref.node->parent->children.begin(); itr != ref.node->parent->children.end(); ++itr)
      if(*itr == ref.node){
         *itr = node;
         break;
      }
   ref.node->parent = node;

   node->key = subval(ref.node->key, 0, ref.pos + 1);
   ref.node->key = subval(ref.node->key, ref.pos + 1, ref.node->key.size() - ref.pos - 1);

	return node;
}

template<class K, class T> K trie<K, T>::subval(const K &s, int start, int count){
	K res;
	for(int i = 0; i < count; i++)
		res += s[start + i];
	return res;
}

template<class K, class T> typename trie<K, T>::Node* trie<K, T>::getNodeByKey(const K &_key){
   iterator itr(this, Ref(root, 0));
   
   for(int i = 0; i < _key.size(); ++i)
      if(!itr.stepIn(_key, i))
         return NULL;

   return itr.ref.node;
}

template<class K, class T> typename trie<K, T>::Node* trie<K, T>::getFirstNoEmpty(Node* _node, TSide side){
   Node* node = _node;
   while((node != NULL && node->empty) || node == root || node == _node)
      if(side == LEFT)
         node = *(node->children.begin());
      else if(side == RIGHT)
         node = *(--node->children.end());

   return node;
}

template<class K, class T> typename trie<K, T>::Node* trie<K, T>::getMostNode(Node* _node, TSide side){
   Node* node = _node;
   while(node->children.size() != 0)
      if(side == TSide::LEFT)
         node = node->children.front();
      else if(side == TSide::RIGHT)
         node = node->children.back();

   return node;
}

template<class K, class T> void trie<K, T>::restoreOrderChildren(Node* _node){
   Node* node = NULL;
   for(std::list<Node*>::iterator itr = _node->children.begin(); itr != _node->children.end(); ++itr)
      for(std::list<Node*>::iterator jtr = _node->children.begin(); jtr != _node->children.end(); ++jtr)
         if((*itr)->key < (*jtr)->key){
            node = *itr;
            *itr = *jtr;
            *jtr = node;
         }
}

template<class K, class T> void trie<K, T>::deleteTrie(Node* node){
   if(node == NULL)
      return;

   for(std::list<Node*>::iterator itr = node->children.begin(); itr != node->children.end(); itr++)
      deleteTrie(*itr);

   delete node;
}

template<class K, class T> trie<K, T>::trie(){
	root = new Node(NULL);
   root->empty = false;
	trie_size = 0;
}

template<class K, class T> trie<K, T>::~trie(){
   deleteTrie(root);
}

template<class K, class T> typename trie<K, T>::iterator trie<K, T>::insert(const K &_key, const T &_val){
	iterator itr(this, Ref(root, 0));
	Node* node = NULL;
   bool implicit = true;
   size_t countLettersAddedToOldKey = 0;

   if(_key.size() == 0)
      return itr;

	for(int i = 0; i < _key.size(); ++i)
	   if(!itr.stepIn(_key, i)){
         if(itr.ref.pos + 1 < itr.ref.node->key.size()){
            node = makeExplicit(itr.ref);
            itr.ref = Ref(node, node->key.size() - 1);
            --i;
         }
         else if(itr.ref.node->children.size() != 0 || !itr.ref.node->empty){
            itr.ref.node->addChild(subval(_key, i, 1));
            restoreOrderChildren(itr.ref.node);
            itr.stepIn(_key, i);
         }
         else{
            itr.ref.node->key += _key[i];
            itr.stepIn(_key, i);
         }
         
      }

   if(itr.ref.pos + 1 != itr.ref.node->key.size()){
      node = makeExplicit(itr.ref);
      itr.ref = Ref(node, node->key.size() - 1);
   }
      
   itr.ref.node->val = _val;
   itr.ref.node->empty = false;

   trie_size++;

   return itr;
}

template<class K, class T> void trie<K, T>::erase(K _key){
   Node* node = getNodeByKey(_key);
   erase(iterator(this, Ref(node, 0)));
}

template<class K, class T> void trie<K, T>::erase(const iterator &_itr){
   if(_itr.ref.node == NULL && _itr.parent == NULL)
      throw OutOfRange();
   Node *parent = _itr.ref.node->parent, *node;
   
   if(_itr.ref.node->children.size() < 2){
      for(std::list<Node*>::iterator itr = parent->children.begin(); itr != parent->children.end(); ++itr)
         if(*itr == _itr.ref.node){
            if(_itr.ref.node->children.size() == 0)
               _itr.ref.node->parent->children.erase(itr);
            else
               *itr = _itr.ref.node->children.front();
            break;
         }

      if(_itr.ref.node->children.size() == 1){
         node = _itr.ref.node->children.front();
         node->key = node->key + _itr.ref.node->key;
         node->parent = parent;
      }
      else if(_itr.ref.node->parent->children.size() == 1 && _itr.ref.node->parent != root){
         node = _itr.ref.node->parent;
         node->children.front()->parent = node->parent;
         for(std::list<Node*>::iterator itr = node->parent->children.begin(); itr != node->parent->children.end(); ++itr)
            if(*itr == node){
               *itr = node->children.front();
               break;
            }
         node->children.front()->key = node->key + node->children.front()->key;

         delete _itr.ref.node->parent;      
      }

      delete _itr.ref.node;
   }
   else
      _itr.ref.node->empty = true;

   trie_size--;
}

template<class K, class T> typename trie<K, T>::iterator trie<K, T>::begin(){
   return iterator(this, getFirstNoEmpty(root, LEFT), iterator::TState::NORMAL);
}

template<class K, class T> typename trie<K, T>::iterator trie<K, T>::end(){
   return iterator(this, NULL, iterator::TState::PAST_REAR);
}

template<class K, class T> typename trie<K, T>::iterator trie<K, T>::find(const K &_key){
   iterator itr(this, Ref(root, 0));

   for(int i = 0; i < _key.size(); ++i)
      if(!itr.stepIn(_key, i))
         return end();

	if(itr.ref.node->empty)
		return end();

   itr.state = iterator::NORMAL;
   return itr;
}

template<class K, class T> bool trie<K, T>::empty(){
   return trie_size == 0;
}

template<class K, class T> size_t trie<K, T>::size(){
   return trie_size;
}

template<class K, class T> typename trie<K, T>::Proxy trie<K, T>::operator[] (const K &_key){
   return Proxy(this, _key);
}

template<class K, class T> void trie<K, T>::clear(){
   deleteTrie(root);
   root = new Node(NULL);
   root->empty = false;
   trie_size = 0;
}

};
#endif