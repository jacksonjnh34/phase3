#include "CircularDynamicArray.cpp"

using namespace std;

template<class keytype, class valuetype>
class Heap
{
public:
	Heap() : key_arr(), val_arr()
	{
		heap_size = 0;
	}

	Heap(keytype k[], valuetype V[], int s) : key_arr(), val_arr()
	{
		heap_size = s;
		int idx = (s / 2) - 1;

		keytype k2[s];
		valuetype V2[s];

		for(int i = 0; i < s; i++)
		{
			k2[i] = k[i];
			V2[i] = V[i];
		}

		for(int i = idx; i >= 0; i--)
		{
			heapify(k2, V2, s, i);
		}

		for(int i = 0; i < s; i++)
		{
			//cout << "Adding key: " << k[i] << " with value: " << V[i] << endl;
			this->key_arr.addEnd(k2[i]);
			this->val_arr.addEnd(V2[i]);
		}

		//printf("DONE FULL\n");
	}

	~Heap()
	{
		//NOTE THERE IS A SEG FAULT HERE UGH
		//this->key_arr.~CircularDynamicArray<keytype>();
		//this->val_arr.~CircularDynamicArray<valuetype>();
	}

	void insert(keytype k, valuetype v)
	{
		heap_size++;
		int idx = heap_size - 1; 
		this->key_arr.addEnd(k);
		this->val_arr.addEnd(v);

		while(idx != 0 && this->key_arr[(idx - 1) / 2] > k)
		{
			//keytype tmp_key = &this->key_arr[idx];

			key_swap(&this->key_arr[idx], &this->key_arr[(idx - 1) / 2]);
			val_swap(&this->val_arr[idx], &this->val_arr[(idx - 1) / 2]);

			idx = (idx - 1) / 2;
		}
	}


	keytype extractMin()
	{
		if(heap_size == 1)
		{
			heap_size--;
			keytype to_return = this->key_arr[0];
			this->key_arr.delFront();
			this->val_arr.delFront();
			return to_return;
		}

		keytype root = this->key_arr[0];
		this->key_arr[0] = this->key_arr[heap_size - 1];
		heap_size--;
		heapify(0);

		return root;

	}

	keytype peakKey()
	{
		return this->key_arr[0];
	}

	valuetype peakValue()
	{
		return this->val_arr[0];
	}

	void printKey()
	{		
		for(int i = 0; i < heap_size; i++)
		{
			cout << this->key_arr[i] << " ";
		}

		cout << endl;
		
	}


private:
	CircularDynamicArray<keytype> key_arr;
	CircularDynamicArray<valuetype> val_arr;
	int heap_size;

	void heapify(keytype k[], valuetype V[], int size, int init_idx)
	{
		int smallest = init_idx;
		int left = 2 * init_idx + 1;
		int right = 2 * init_idx + 2;

		if(left < size && k[left] < k[smallest])
		{
			smallest = left;
		}

		if(right < size && k[right] < k[smallest])
		{
			smallest = right;
		}

		if(smallest != init_idx)
		{
			keytype tmp_key = k[init_idx];
			k[init_idx] = k[smallest];
			k[smallest] = tmp_key;

			valuetype tmp_val = V[init_idx];
			V[init_idx] = V[smallest];
			V[smallest] = tmp_val;

			heapify(k, V, size, smallest);
		}
	}

	void heapify(int init_idx)
	{
		int smallest = init_idx;
		int left = 2 * init_idx + 1;
		int right = 2 * init_idx + 2;

		if(left < heap_size && this->key_arr[left] < this->key_arr[smallest])
		{
			smallest = left;
		}

		if(right < heap_size && this->key_arr[right] < this->key_arr[smallest])
		{
			smallest = right;
		}

		if(smallest != init_idx)
		{
			keytype tmp_key = this->key_arr[init_idx];
			this->key_arr[init_idx] = this->key_arr[smallest];
			this->key_arr[smallest] = tmp_key;

			valuetype tmp_val = this->val_arr[init_idx];
			this->val_arr[init_idx] = this->val_arr[smallest];
			this->val_arr[smallest] = tmp_val;

			heapify(smallest);
		}
	}

	void key_swap(keytype *x, keytype *y) 
	{ 
   		keytype temp = *x; 
   		*x = *y; 
   		*y = temp; 
	}

	void val_swap(valuetype *x, valuetype *y) 
	{ 
   		valuetype temp = *x; 
   		*x = *y; 
   		*y = temp; 
	}
};