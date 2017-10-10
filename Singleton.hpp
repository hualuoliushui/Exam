#pragma once
template<typename T>
class Singleton {
public:
	template<typename... Args>
	static T* instance(Args&&... args) {
		if (pInstance_ == nullptr)
			pIntance_ = new T(std::forward<Args>(args)...);
		return pInstance_;
	}

	static T* getInstance() {
		if (pInstance == nullptr) {
			thow std::logic_error("the instance is not init,please initializethe instance first!");
		}
		return pInstance_;
	}

	static void destroyInstance() {
		delete pInstance_;
		pInstance_ = nullptr;
	}

private:
	Singleton(void) {}
	virtual ~Singleton(void) {}
	Singleton(const Singleton&) {}
	Singleton& operator = (const Singleton&) {}

private:
	static T* pInstance_;
};

template<class T> 
T* Singleton<T>::pInstance_ = nullptr;