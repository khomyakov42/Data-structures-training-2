#ifndef __TREE_H__
#define __TREE_H__

#include<cassert>
#include"Basic_Tree.h"
namespace hmw{

#define NORMAL basic_map::iterator::NORMAL
#define PAST_REAR basic_map::iterator::PAST_REAR
#define BEFORE_FIRST basic_map::iterator::BEFORE_FIRST

#define INSERT basic_map::INSERT
#define DELETE basic_map::DELETE
#define GET basic_map::GET

template<class T, class K>
class map: public basic_map{
   private:
      class Proxy{
         private:
            K key;
            map<T, K> *tree;
         public:
            Proxy(const K _key, map<T, K> *_tree){key = _key; tree = _tree;};
            void operator= (const T &_val);
            operator T();
      };

      class Node: public basic_map::Node{
         friend class map<T, K>;
         K key;
         T value;
         Node(Node *_parent, const K &_key, const T &_val);
         Node(Node *_parent, const K &_key);
         Node(){};
         ~Node(){};
      };

   public:
      class NotDereferencable{};
	   class iterator: public basic_map::iterator{
		   private:
			   friend class map<T, K>;
         public:
            iterator(typename basic_map::iterator &_itr);
            iterator(){};
            ~iterator(){};

            T& operator* ();
            K getKey();
	   };
   private:
      Node* getNodeByKey(K key, TAction operation);
      Node* buildMap(const Node* _node, Node* _parent);
      void insert(Node* _node, const K &_key, const T &_val);
      void erase(map<T, K> *_tree, Node* _node);
   public:
	   map(){};
	   map(const map<T, K> &_m);
	   ~map(){};

	   map<T, K> &operator= (const map<T, K> &_m);
      Proxy operator[] (const K &_key);

      iterator begin();
      iterator end();

      void insert(const K &_key, const T &_val);
      void insert(const iterator &_itr, T &_val);
      void erase(const K &_key);
      void erase(const iterator &_itr);
      iterator find(const K &_key);
      bool empty();
};
/////////////////////PROXY//////////////////////////
template<class T, class K> void map<T, K>::Proxy::operator= (const T &_val){
   assert(tree != NULL);

   tree->insert(key, _val);
}

template<class T, class K> map<T, K>::Proxy::operator T(){
   return *(tree->find(key));
}

/////////////////////NODE//////////////////////////////
template<class T, class K> map<T, K>::Node::Node(typename map<T, K>::Node *_parent, const K &_key, const T &_val){
	key = _key;
	left = NULL;
	parent = _parent;
	right = NULL;
	value = _val;
	height = 1;
}

template<class T, class K> map<T, K>::Node::Node(typename map<T, K>::Node *_parent, const K &_key){
   key = _key;
   left = NULL;
   parent = _parent;
   right = NULL;
   height = 1;
}

//////////////////////ITERATOR//////////////////////////
template<class T, class K> map<T, K>::iterator::iterator(typename basic_map::iterator &_itr){
   node = _itr.node;
   state = _itr.state;
   tree = _itr.tree;
}

template<class T, class K> T& map<T, K>::iterator::operator* (){
   if(state != NORMAL)
      throw NotDereferencable();

   return static_cast<Node*>(node)->value;;
}

template<class T, class K> K map<T, K>::iterator::getKey(){
   return state == NORMAL? static_cast<Node*>(node)->key: NULL;
}
/////////////////////MAP////////////////////////////////
template<class T, class K> typename map<T, K>::Node* map<T, K>::getNodeByKey(K key, TAction operation){
   Node *node = NULL, *pnode = NULL;

	node = static_cast<Node*>(root);
	while(node != NULL){
		if(operation == INSERT)
			pnode = node;
		if(key < node->key)
			node = static_cast<Node*>(node->left);
		else
			if(key > node->key)
				node = static_cast<Node*>(node->right);
			else
				break;
	}

	if(operation == INSERT && node == NULL){
		node = new Node(pnode, key);
		map_size++;
		if(pnode != NULL)
         if(key < pnode->key)
			   pnode->left = node;
		   else
			   pnode->right = node;
      else
         root = node;
	}
	return node;
}

template<class T, class K> typename map<T, K>::Node* map<T, K>::buildMap(const Node* _node, Node* _parent){
   if(_node == NULL)
      return NULL;

   Node *p = new Node(_parent, _node->key, _node->value);

   if(_parent != NULL)
      if(_node->parent->left == _node)
         _parent->left = p;
      else
         _parent->right = p;
   
   p->left = buildMap(static_cast<Node*>(_node->left), p);
   p->right = buildMap(static_cast<Node*>(_node->right), p);
   return p;
}

template<class T, class K> map<T, K>::map(const map<T, K> &_m){
   root = buildMap(static_cast<Node*>(_m.root), NULL);
   map_size = _m.map_size;
}

template<class T, class K> map<T, K> &map<T, K>::operator= (const map<T, K> &_m){
   (*this).~map();
   root = buildMap(static_cast<Node*>(_m.root), NULL);
   map_size = _m.map_size;
   return *this;
}

template<class T,class K> typename map<T, K>::Proxy map<T, K>::operator[] (const K &_key){
   return Proxy(_key, this);
}

template<class T, class K> typename map<T, K>::iterator map<T, K>::begin(){
   return static_cast<iterator>(basic_map::iterator(getMostNode(root, LEFT), root == NULL? PAST_REAR: NORMAL, this));
}

template<class T, class K> typename map<T, K>::iterator map<T, K>::end(){
	return static_cast<iterator>(basic_map::iterator(NULL, PAST_REAR, this));
}

template<class T, class K> void map<T, K>::insert(Node* _node, const K &_key, const T &_val){
   assert(_node != NULL);
   if(map_size == 0){
		_node = new Node(NULL, _key, _val);
		assert(_node != NULL);
		_node->height = 1;
		root = _node;
		map_size++;
		return;
	}

	_node->value = _val;
	BalanceTree(_node->parent, INSERT);
}

template<class T, class K> void map<T, K>::insert(const K &_key, const T &_val){
   insert(getNodeByKey(_key, INSERT), _key, _val);
}

template<class T, class K> void map<T, K>::insert(const iterator &_itr, T &_val){
   if(_itr.state != NORMAL	|| getNodeByKey(_itr.node.key) == NULL)
      throw OutOfRange();
   insert(_itr.node, _val);
}

template<class T, class K> void map<T, K>::erase(map<T, K> *_tree, typename map<T, K>::Node *_node){
   Node *pnode = NULL, *parent = NULL;
   
   assert(_node != NULL);
      
	parent = static_cast<Node*>(_node->parent);

	if(_node->left != NULL && _node->right != NULL){
		pnode = static_cast<Node*>(getMostNode(_node->left, RIGHT));
		if(pnode->parent != NULL)
			if(pnode->parent->left == pnode)
				if(pnode->left != NULL){
					pnode->parent->left = pnode->left;
					pnode->left->parent = pnode->parent;
				}
				else
					pnode->parent->left = NULL;
			else
				if(pnode->left != NULL){
					pnode->parent->right = pnode->left;
					pnode->left->parent = pnode->parent;
				}
				else
					pnode->parent->right = NULL;
		else{
			pnode->parent = NULL;
			_tree->root = pnode;
		}

      _node->key = pnode->key;
      _node->value = pnode->value;
		delete pnode;
	}
	else
		if(_node->left == NULL && _node->right == NULL){
			if(_node->parent != NULL)
				if(_node->parent->left == _node)
					_node->parent->left = NULL;
				else
					_node->parent->right = NULL;
			else
				_tree->root = NULL;
			delete _node;
		}
		else
			if(_node->left == NULL){
				if(_node->parent != NULL){
					if(_node->parent->left == _node)
						_node->parent->left = _node->right;
					else
						_node->parent->right = _node->right;
					_node->right->parent = _node->parent;
				}
				else{
					_node->right->parent = NULL;
					_tree->root = _node->right;
				}
				delete _node;
			}
			else{
				if(_node->right == NULL)
					if(_node->parent != NULL){
						if(_node->parent->right == _node)
							_node->parent->right = _node->left;
						else
							_node->parent->left = _node->left;
						_node->left->parent = _node->parent;
					}
					else{
						_node->left->parent = NULL;
						_tree->root = _node->left;
					}
				delete _node;
			}
	_tree->map_size--;
	if(parent == NULL)
		BalanceTree(_tree->root, DELETE);
	else
		BalanceTree(parent, DELETE);
}

template<class T, class K> void map<T, K>::erase(const K &_key){
   erase(this, getNodeByKey(_key, DELETE));
}

template<class T, class K> void map<T, K>::erase(const iterator &_itr){
   if(_itr.state != NORMAL)
      throw OutOfRange();
   erase((static_cast<Node*>(_itr.node))->key);
}

template<class T, class K> typename map<T, K>::iterator map<T, K>::find(const K &_key){
   Node *node = getNodeByKey(_key, GET);
   return static_cast<iterator>(basic_map::iterator(node, node == NULL? PAST_REAR: NORMAL, this));
}

template<class T, class K> bool map<T, K>::empty(){
   return map_size == 0;
}

};
#endif