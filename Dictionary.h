#ifndef GSS_DICTIONARY_H
#define GSS_DICTIONARY_H
namespace gss{
	template <typename Key, typename E>
    abstract class Dictionary{
	private:
		void operator = (const Dictionary&){}
		Dictionary(const Dictionary&){}
	public:
		Dictionary(){};
		virtual ~Dictionary(){}

		virtual void clear() = 0;

		virtual void insert(const Key&k, const E& e) = 0;

		virtual E remove(const Key& k) = 0;

		virtual E removeAny() = 0;

		virtual E find(const Key& k) const = 0;

		virtual int size() = 0;
	};
}

#endif