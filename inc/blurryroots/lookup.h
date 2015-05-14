#ifndef LookupTable_h
#define LookupTable_h

#include <unordered_map>

#include <blurryroots/throwif.h>

namespace blurryroots {

template<class KeyType, class ValueType>
class LookupTable {

public:
	LookupTable ()
	: map () {
		//
	}

	virtual
	~LookupTable (void) {
		//
	}

	bool
	has_key (KeyType key) {
		auto result = this->map.find (key);

		return this->map.end () != result;
	}

	const ValueType&
	get (KeyType key) {
		THROW_IF (! this->has_key (key),
			"Given key does not exist in table!"
		);

		return this->map[key];
	}

	template <class... Args>
	void
	emplace (KeyType key, Args&&... args) {
		this->map.emplace (key, args...);
	}

	void
	add (const KeyType &key, const ValueType &value) {
		this->map.put (key, value);
	}

private:
	std::unordered_map<KeyType, ValueType> map;

};

}

#endif
