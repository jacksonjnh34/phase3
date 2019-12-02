using namespace std;



template<class keytype, class valuetype>
class BHeap
{
public:
	struct Node
	{
		int degree;
		keytype key;
		valuetype val;
		Node *child, *sibling, *parent;
	};

	list<Node*> heaps;

	//Default Constructor. The Heap should be empty O(1)
	BHeap()
	{

	}

	/*
	For this constructor the heap should be built
	using the arrays K and V containing s items of
	keytype and valuetype. The heap should be
	constructed using repeated insertion.
	O(s)	
	*/
	BHeap(keytype k[], valuetype V[], int s)
	{
		for(int i = 0; i < s; i++)
		{
			insert(k[i], V[i]);
		}
	}

	//Destructor for the class. O(n)
	~BHeap()
	{
		heaps.clear();
		//delete[] heaps;
	}

	/*
	Returns the minimum key in the heap without
	modifiying the heap.
	O(lg n)
	*/
	keytype peakKey();

	/*
	Returns the value associated with the minimum
	key in the heap without modifiying the heap.
	O(lg n)
	*/
	valuetype peakValue();

	/*
	Removes the minimum key in the heap and
	returns the key.
	O(lg n)
	*/
	keytype extractMin();

	//Inserts the key k and value v pair into the heap. O(lg n)
	void insert(keytype k, valuetype v)
	{
		Node *new_node = newNode(k, v);

		list<Node*> new_node_heap;
		new_node_heap.push_back(new_node);

		this->heaps = unionBionomialHeap(this->heaps, new_node_heap);

		this->heaps = fix_up(this->heaps);
	}

	//Merges the H2 into the current heap O(lg n)
	void merge(BHeap<keytype, valuetype> &H2)
	{
		this->heaps = unionBionomialHeap(this->heaps, H2.heaps);

		this->heaps = fix_up(this->heaps);

		H2.~BHeap();
	}

	/*
	Writes the keys stored in the heap, printing the
	smallest binomial tree first. When printing a
	binomial tree, print the size of tree first and then
	use a modified preorder traversal of the tree.
	See the example below
	*/
	void printKey()
	{
		typename list<Node*>::iterator iter;
   		iter = this->heaps.begin();

   		while (iter != this->heaps.end())
   		{
   			cout << "B" << (*iter)->degree << endl;
   		    printNodes(*iter);
   		    iter++;
   		    cout << endl << endl;
   		}
	}

private:
	Node* newNode(keytype k, valuetype v)
	{
		Node *init = new Node;
		init->key = k;
		init->val = v;
		init->degree = 0;
		init->child = NULL;
		init->parent = NULL;
		init->sibling = NULL;

		return init;
	}

	void printNodes(Node *my_node)
	{
		//NULL acts as a false value so this is the easiest way to run a loop
	    while(my_node)
	    {
	        cout << my_node->key << " ";

	        printNodes(my_node->child);
	        my_node = my_node->sibling;
	    } 
	} 

	list<Node*> unionBionomialHeap(list<Node*> l1, list<Node*> l2) 
	{ 
    	list<Node*> new_heap; 
    	typename list<Node*>::iterator internal_iter = l1.begin(); 
    	typename list<Node*>::iterator external_iter = l2.begin(); 
    	while (internal_iter != l1.end() && external_iter != l2.end()) 
    	{
    	    if((*internal_iter)->degree <= (*external_iter)->degree) 
    	    { 
    	        new_heap.push_back(*internal_iter); 
    	        internal_iter++; 
    	    }
    	    else
    	    { 
    	        new_heap.push_back(*external_iter); 
    	        external_iter++; 
    	    } 
    	} 

    	while (internal_iter != l1.end()) 
    	{ 
    	    new_heap.push_back(*internal_iter); 
    	    internal_iter++; 
    	}

    	while (external_iter != l2.end()) 
    	{ 
    	    new_heap.push_back(*external_iter); 
    	    external_iter++; 
    	} 

    	return new_heap; 
	}

	Node* mergeTrees(Node *node_1, Node *node_2) 
	{ 
		//Just making sure that node_1 is smaller
	    if (node_1->key > node_2->key)
	    {
	    	Node *temp = node_1;
	    	node_1 = node_2;
	    	node_2 = temp;
	    }
		
	    node_2->parent = node_1; 
	    node_2->sibling = node_1->child; 
	    node_1->child = node_2; 
	    node_1->degree++; 
	  
	    return node_1; 
	}

	void insertNodeOrTree(Node* root)
	{
		list<Node*> new_heap;
		new_heap.push_back(root);

		unionBionomialHeap(this->heaps, new_heap);

		this->heaps = fix_up(this->heaps);
	}

	list<Node*> fix_up(list<Node*> heap)
	{
		if(heap.size() <= 1)
		{
			return heap;
		}

		//Each iterator is used to keep track of 3 binomial trees, to look ahead at possible degree collisions
		list<Node*> new_heap;
		typename list<Node*>::iterator iter1, iter2, iter3;
		iter1 = heap.begin();
		iter2 = heap.begin();
		iter3 = heap.begin();

		//This if statement just helps spread out the iterators for later
		if(heap.size() == 2)
		{
			iter2++;
			iter3 = heap.end();
		}
		else
		{
			iter2++;
			iter3++; //Maybe problem here?
			iter3++;
		}

		//Simply look at 'middle' tree to detect finish, that way you can constantly be looking ahead of and behind yourself for trees with the same degree
		while(iter2 != heap.end())
		{
			//Just checking if we've reached last element, then we just catch iter1 up to iter2, as it should have already been processed as iter 2 last loop
			if(iter2 == heap.end())
			{
				iter1++;
			}
			//Merging tree at iter1 and iter2 is not possible as they are of different degrees
			else if((*iter1)->degree < (*iter2)->degree)
			{
				iter1++;
				iter2++;
				if(iter3 != heap.end())
				{
					iter3++;
				}
			}
			//If all three iterators' degrees are the same, we can just move to the next set, as the next else if deals with 2 same-deg trees
			else if(iter3 != heap.end() && (*iter1)->degree == (*iter2)->degree && (*iter2)->degree == (*iter3)->degree)
			{
				iter1++;
				iter2++;
				iter3++;
			}
			//If 2 trees have the same degree merge the two trees together
			else if((*iter1)->degree == (*iter2)->degree)
			{
				Node *init;
				*iter1 = mergeTrees(*iter1, *iter2);
				iter2 = heap.erase(iter2);

				if(iter3 != heap.end())
				{
					iter3++;
				}
			}
		}

		return heap;
	}

};