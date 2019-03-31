#pragma once
#define DECLARE_SINGLETON(Type)						\
	public:											\
		Type(const Type&) = delete;					\
		void operator=(const Type&) = delete;		\
		static Type* GetInstance()					\
		{											\
			if(!mInstance)							\
			{										\
				mInstance = new Type;				\
			}										\
			return mInstance;						\
		}											\
		static void DestroyInstance()				\
		{											\
			delete mInstance;						\
		}											\
	private:										\
		Type() = default;							\
		~Type();									\
		static Type* mInstance;						\
	public: