**class template**
# toy_box::ring_buffer


## Overview

リングバッファクラス。リングバッファ？なときは[コチラ][link-ring-buffer]。back -> front の向きは時計回り。  
`push_front()/back()`、`pop_front()/back()`がO(1)で可能。ランダムアクセスもOk。要素数（`count()`)が最大容量(`capacity()`)を超えると、front/backの要素から順に書き換わる。今のところinsert系のメソッドは無し。  
indexの正規化をビット演算で行うために最大容量は必ず2の冪乗になる。

[link-ring-buffer]:https://ja.wikipedia.org/wiki/%E3%83%AA%E3%83%B3%E3%82%B0%E3%83%90%E3%83%83%E3%83%95%E3%82%A1

### File Organization

		toy_box/
			|
			Classes/
				|
				Container/
					|
					ring_buffer/
						|
						+ ring_buffer.h
						+ impl.h
						+ iterators.h
						+ misc.h
						- tutorial.cpp

### Namespace

		namespace toy_box
		{
			template <typename T> class ring_buffer;
		
			namespace ring_buffer_bits
			{
				using capacity_t = size_t;
				using index_t = size_t;

				static const size_t kCapacityBase = 2;
				
				template <typename T> struct iterator;
				template <typename T> struct const_iterator;
				template <typename T> struct physical_memory_iterator;
				template <typename T> struct const_physical_memory_iterator;
			}
		}

イテレータは別の名前空間に入っている（ファイルを分けるために）が、`ring_buffer`クラス内でエイリアスを定義してあるので、`ring_buffer<T>::iterator`で使用できる（というよりコッチを使って欲しい）。

### Public Methods

* `ring_buffer()`  
* `ring_buffer(capacity_t request_size)`   
* `ring_buffer(const ring_buffer& other)`  
  
	コンストラクタs。**request_size**には最大容量を指定するが、希望通りになるかは分からない。**request_size <= 2^n** を満たす最小の2^nが最大容量になる。  
    
-------------------------------------------------------------------------------------------------------

* `void resize(capacity_t request_size)`  
* `void expand(capacity_t request_size)`  
* `void shrink(capacity_t request_size)`  
  
	最大容量を変更する。要素の並びは変わらない。**resize**は内部で**expand**か**shrink**を呼び出している。**shrink**は、新しい最大容量が要素数よりも小さい場合、入りきらない要素をbackの方から削っていく。  
	また、要素の入っていない部分はみ初期化なので、そこにアクセスした時の動作は未定義。  
	**request_size**には新しい最大容量の希望の値を渡す。実際には、**request_size <= 2^n** を満たす最小の2^nが最大容量になる。  

-------------------------------------------------------------------------------------------------------

* `void push_back(const T& value)`  
* `void push_back(T&& value)`  
* `void push_front(const T& value)`  
* `void push_front(T&& value)`  

	front/backに要素を追加する。右辺値を渡した場合は**std::move()**で要素の追加が行われる。**capacity()**が0の場合、assert:エラーが発生する。
	要素数が溢れた時は、例えば**push_back**の場合、frontの要素が書き換わり、frontの直前だった要素がfrontになる。
	
-------------------------------------------------------------------------------------------------------

* `void pop_back()`  
* `void pop_front()` 

	front/backの要素を削除する。メモリは解放されない。**count()** が0でもエラーにはならないよ。  
	あと、削除した要素のデストラクタが呼ばれる。

-------------------------------------------------------------------------------------------------------
 
* `T& operator[](index_t index)`  
* `const T& operator[](index_t index) const`  

	要素にアクセスする基本の手段。**operator[0]**は常に**front()**と同じ要素を指す。つまり、**index**には、frontを0として考えた時のインデックスを渡す。また、リングバッファなので、**out-of-range** みたいなことは起こらず、たとえ最大容量を超えたインデックスを渡したとしても正規化される(一周しても戻ってくる)。front <-> back 間の要素以外にもアクセスできるが、未初期化部分なのでどうなるかは知らない。  
	添字演算子で値を追加/削除しても**count()**や**front()**、**back()**等に反映されないので、**危険**です。やめてください。。。

-------------------------------------------------------------------------------------------------------

* `T front() const`  
* `T back() const`  

	front/backの値をそれぞれ返却する。**capacity()**が0の場合、segumentation-faultが発生。**count()**が0の場合、返り値は未定義。

-------------------------------------------------------------------------------------------------------

* `void clear()`  
* `void clean_up()`

	要素を全て削除する。  
	**clear** は各要素のデストラクタを呼ぶが、メモリの開放はしない。  
	**clean_up** は各要素ののデストラクタを呼び、メモリも開放する。

-------------------------------------------------------------------------------------------------------

* `capacity_t capacity() const`  

	最大容量を返す。必ず0か2^n。

-------------------------------------------------------------------------------------------------------

* `capacity_t count() const`  

	要素数を返す。当たり前だけど、常に **count() <= capacity()** 。

-------------------------------------------------------------------------------------------------------

* `bool empty() const`
* `bool full() const`

	コンテナの状態を返す。  
	**empty** は **count()** が0の時 **true** 、そうでなければ **false** を返す。  
	**full** は **capacity()** と **count()** が等しい時 **true** 、そうでなければ **false** を返す。

-------------------------------------------------------------------------------------------------------

* `iterator begin()`  
* `const_iterator begin() const`  
* `const_iterator cbegin() const`  
* `iterator end()`  
* `const_iterator end() const`  
* `const_iterator cend() const`  

	イテレータの取得メソッドs。**begin**はfrontを指し、**end**はbackの次を指す。イテレータは、forward iterator なので前進のみ可能。

-------------------------------------------------------------------------------------------------------

* `physical_memory_iterator pmbegin()`  
* `const_physical_memory_iterator pmbegin() const`  
* `const_physical_memory_iterator cpmbegin() const`  
* `physical_memory_iterator pmend()`  
* `const_physical_memory_iterator pmend() const`  
* `const_physical_memory_iterator cpmend() const`

	**physical_memory_iterator** の取得メソッドs。**begin** は実メモリ上の先頭要素を指し、**end** は末尾の次の場所を指す。  
	イテレータは、 forward iterator なので前進のみ可能。

-------------------------------------------------------------------------------------------------------	  


### How To Use ?

**基本**

		dlib::ring_buffer<int> buffer2();                 // <- default, count() and capacity() is 0
		dlib::ring_buffer<int> buffer(8);                 // <- size() is 0, capacity() is 8
		dlib::ring_buffer<int> buffer3(buffer);           // <- copy constructor  
	
		buffer.push_front(10);                            // <- append '10' to the front of the buffer
		buffer.push_back(10);                             // <- append '10' to the back of the buffer

		int x = buffer.front();                           // <- get the first element of the buffer
		int y = buffer[0];                                // <- this is same as 'buffer.front()'

		buffer.pop_front();                               // <- remove the first element of the buffer
		buffer.pop_back();                                // <- remove the last element of the buffer

		buffer.expand(buffer.capacity() * 2);             // <- count() is 0, capacity() is 16
		buffer.shrink(4);                                 // <- count() is 0, capacity() is 4

		buffer.clear();                                   // <- count() is 0, capacity() is 4
		buffer.clean_up();                                // <- count() is 0, capacity() is 0

	
**Iterators**  

		// navigate through the front element of a buffer to the back element of that
		for(auto itr = buffer.begin(); itr != buffer.end(); ++itr)
		{
			std::cout << "data -> " << *itr << '\n';
		}
		
		// the following codes is the same as above...
		for(size_t i = 0; i < buffer.count(); ++i)
		{
			std::cout << "data -> " << buffer[i] << '\n';
		}