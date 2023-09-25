template<class T>
class NextIterator{
public:
	class iterator{
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;
		NextIterator *source;
		T *content;
	public:
		explicit iterator(NextIterator<T> *source):source(source),content(source->getLine()){}
		explicit iterator(NextIterator<T> *source,std::string *content):source(source),content(content){}

		iterator& operator++(){
			content=source->getLine();
			return *this;
		}

		iterator operator++(int){
			iterator retval = *this;
			++(*this);
			return retval;
		}

		bool operator==(iterator other) const {
			return content == other.content;
		}

		bool operator!=(iterator other) const {
			return !(*this == other);
		}

		reference operator*() const {
			return *content;
		}
	};

	iterator begin(){
		return iterator(this);
	}

	iterator end(){
		return iterator(this,NULL);
	}

	virtual T *next()=0;
};