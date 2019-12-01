using namespace std;

struct Node
{
	int data, deg;
	Node *child, *sib, *parent;
};

template<class keytype, class valuetype>
class BHeap
{
public:
	BHeap();

	BHeap(keytype k[], valuetype V[], int s);

	~BHeap();

	keytype peakKey();

	valuetype peakValue();

	keytype extractMin();

	void insert(keytype k, valuetype v);

	void merge(BHeap<keytype, valuetype> H2);

	void printKey();

private:

};