#ifndef __BASIC_MAP__
#define __BASIC_MAP__

#include<memory>

class basic_map{
   protected:
      class Node{
         private:
            friend class basic_map;
         public:
            Node *left, *right, *parent;
            size_t height;
            Node(){left = NULL; right = NULL; parent = NULL;};
            ~Node(){};
      };
      
	   class iterator{
			   friend class basic_map;
         public:
            enum TStateIterator{
               NORMAL,
               PAST_REAR,
               BEFORE_FIRST
            };
            TStateIterator state;
            basic_map *tree;
            Node *node;
            iterator(Node *_node, TStateIterator _state, basic_map *_tree);
            iterator(){node = NULL; tree = NULL; state = PAST_REAR;};
            ~iterator(){};
            
            void shift(const int _shift);

            iterator operator++ ();
            iterator operator-- ();

            bool operator== (const iterator &_itr);
            bool operator!= (const iterator &_itr);
	   };
      
      enum TRotate{
         LEFT,
         RIGHT
      };

      typedef TRotate TSide;

      enum TAction{
         INSERT,
	      DELETE,
	      GET
      };

      size_t map_size;
      Node *root;

      void freeTree(Node *_node);
      inline int maxHeight(size_t a, size_t b);
      inline int NodeBalanceFactor(Node *node);
      inline void UpdateNodeHeight(basic_map::Node *node);
      void NodeRotate(Node *node, TRotate side);
      void BalanceTree(Node* node, TAction stop_criterion);
      Node* getMostNode(Node *root, TSide _side);
      int getNodeHeight(Node *_node);
   public:
      class OutOfRange{};
	   basic_map();
	   ~basic_map();

      void clear();
      bool empty();
      size_t size();
};
//////////////////////////////ITERATOR//////////////////////////////
basic_map::iterator::iterator(Node *_node, TStateIterator _state, basic_map *_tree){
   node = _node;
   state = _state;
   tree = _tree;
}

void basic_map::iterator::shift(const int _shift){
   for(int i = _shift < 0? _shift * (-1): _shift; i > 0; i--)
      if(_shift > 0)
         (*this)++;
      else
         (*this)--;
}

basic_map::iterator basic_map::iterator::operator++(){
   Node *pnode = NULL;

	if(tree == NULL || state == PAST_REAR)
		throw OutOfRange();

	if(state == BEFORE_FIRST){
		if(tree->map_size == 0)
			state = PAST_REAR;
		else{
			node = tree->getMostNode(tree->root, LEFT);
			state = NORMAL;
		}
		return *this;
	}

	if(node == NULL)
		throw OutOfRange();

	if(node->right != NULL)
		node = tree->getMostNode(node->right, LEFT);
	else	
	   if(node->parent != NULL){
		   if(node->parent->right == node){
			   while(node->parent != NULL && node->right == pnode){
				   pnode = node;
				   node = node->parent;
			   }
			   if(node->parent == NULL && node->right == pnode){
				   node = NULL;
				   state = PAST_REAR;
			   }
		   }
		   else
			   if(node->parent->left = node)
				   node = node->parent;
	   }
	   else{
		   node = NULL;
		   state = PAST_REAR;
	   }
   return *this;
}

basic_map::iterator basic_map::iterator::operator--(){
   Node *pnode = NULL;

	if(tree == NULL || state == BEFORE_FIRST)
		throw OutOfRange();

	if(state == PAST_REAR){
		if(tree->map_size == 0)
			state = BEFORE_FIRST;
		else{
			node = tree->getMostNode(tree->root, RIGHT);
			state = NORMAL;
		}
		return *this;
	}

	if(node == NULL)
		throw OutOfRange();

	pnode = NULL;

	if(node->left != NULL)
		node = tree->getMostNode(node->left, RIGHT);
	else	
	   if(node->parent != NULL){
		   if(node->parent->left == node){
			   while(node->parent != NULL && node->left == pnode){
				   pnode = node;
				   node = node->parent;
			   }
			   if(node->parent == NULL && node->left == pnode){
				   node = NULL;
				   state = BEFORE_FIRST;
			   }
			   //else
				 //  ITR(iteranode = node;
		   }
		   else
			   if(node->parent->right = node)
				   node = node->parent;
	   }
		else{
			node = NULL;
			state = BEFORE_FIRST;
		}
   return *this;
}

bool basic_map::iterator::operator== (const iterator &_itr){
   return node == _itr.node && tree == _itr.tree && state == _itr.state;
}

bool basic_map::iterator::operator!= (const iterator &_itr){
   return !(*this == _itr);
}

////////////////////////////////MAP/////////////////////////////////
void basic_map::freeTree(basic_map::Node *_node){
   if(_node == NULL)
      return;

   freeTree(_node->left);
   freeTree(_node->right);
   delete _node;
}

int basic_map::maxHeight(size_t a, size_t b){
   return a > b? a: b;
}

int basic_map::NodeBalanceFactor(basic_map::Node *node){
   return getNodeHeight(node->right) - getNodeHeight(node->left);
}

void basic_map::UpdateNodeHeight(basic_map::Node *node){
   node->height = 1 + maxHeight(getNodeHeight(node->left), getNodeHeight(node->right));
}

void basic_map::NodeRotate(basic_map::Node *node, basic_map::TRotate side){
   Node *node2;

   node2 = side == LEFT? node->right: node->left;
   
	if(node == NULL)
		return;
	if(node->parent != NULL)
		if(node->parent->left == node)
			node->parent->left = node2;
		else
			node->parent->right = node2;
	else
		root = node2;
	node2->parent = node->parent;
	
   if(side == LEFT){
	   node->right = node2->left;
      if(node2->left != NULL)
		   node2->left->parent = node;

      node2->left = node;
   }
   else{
      node->left = node2->right;
	   if(node2->right != NULL)
		   node2->right->parent = node;

      node2->right = node;
   }

	node->parent = node2;

	UpdateNodeHeight(node);
	UpdateNodeHeight(node2);
}

void basic_map::BalanceTree(basic_map::Node* node, basic_map::TAction stop_criterion){
   Node* pnode = node;
	int balanceFactor = 0;

	while(node != NULL){
		UpdateNodeHeight(node);
		balanceFactor = NodeBalanceFactor(node);
		if(abs(balanceFactor) == 0 && stop_criterion == INSERT)
			return;
		if(balanceFactor == 2){
			if(NodeBalanceFactor(node->right) < 0)
				NodeRotate(node->right, RIGHT);
			NodeRotate(node, LEFT);
		}
		else
			if(balanceFactor == -2){
				if(NodeBalanceFactor(node->left) > 0)
                NodeRotate(node->left, LEFT);
            NodeRotate(node, RIGHT);
			}
		node = node->parent;
	}
}

basic_map::Node* basic_map::getMostNode(basic_map::Node *root, TSide _side){
   if(root == NULL)
      return NULL;   
   
   Node *node = root;
   while(_side == RIGHT? node->right: node->left != NULL)
		node = _side == RIGHT? node->right: node->left;

   return node;
}

int basic_map::getNodeHeight(basic_map::Node *_node){
   return _node == NULL? 0: _node->height;
}

basic_map::basic_map(){
   root = 0;
   map_size = 0;
}

basic_map::~basic_map(){
   freeTree(root);
   root = NULL;
   map_size = 0;
}

void basic_map::clear(){
   freeTree(root);
   root = NULL;
}

bool basic_map::empty(){
   return map_size == 0;
}

size_t basic_map::size(){
   return map_size;
}

#endif